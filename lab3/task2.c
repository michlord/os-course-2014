#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int period_mt_amt;
    int max_mt_amt;
    int reader_prob;
} config_t;

config_t config;

void get_options(int argc, char **argv) {
    int   c;
    
    config.period_mt_amt = 10;
    config.max_mt_amt    = 100;
    config.reader_prob   = 50;
    
    while ((c = getopt(argc, argv, "n:m:p:")) != -1) {
        switch (c) {
            case 'n' :
                sscanf(optarg, "%d", &config.period_mt_amt);
                break;
            case 'm' :
                sscanf(optarg, "%d", &config.max_mt_amt);
                break;
            case 'p' :
                sscanf(optarg, "%d", &config.reader_prob);
                break;
        }
    }
}

typedef struct {
    int counter;
    pthread_mutex_t mutex;
    int last_m_err;
    int last_s_err;
} lightswitch_t;

void ligthswitch_init(lightswitch_t *l) {
    l->counter = 0;
    l->last_m_err = pthread_mutex_init(&l->mutex, NULL);
    l->last_s_err = 0;
}

void lightswitch_destroy(lightswitch_t *l) {
    pthread_mutex_destroy(&l->mutex);
}

void lightswitch_lock(lightswitch_t *l, pthread_mutex_t *s) {
    int res;
   
    res = pthread_mutex_lock(&l->mutex);
    if (res != 0) {
        l->last_m_err = res;
        return;
    }
    
    l->counter += 1;
    if (l->counter == 1) {
        res = pthread_mutex_lock(s);
        if (res != 0) {
            l->last_s_err = res;
            return;
        }
    }
    
    res = pthread_mutex_unlock(&l->mutex);
    if (res != 0) {
        l->last_m_err = res;
        return;
    }
}

void lightswitch_unlock(lightswitch_t *l, pthread_mutex_t *s) {
    int res;
    
    res = pthread_mutex_lock(&l->mutex);
    if (res != 0) {
        l->last_m_err = res;
        return;
    }
    
    l->counter -= 1;
    if (l->counter == 0) {
        res = pthread_mutex_unlock(s);
        if (res != 0) {
            l->last_s_err = res;
            return;
        }
    }
    
    res = pthread_mutex_unlock(&l->mutex);
    if (res != 0) {
        l->last_m_err = res;
        return;
    }
}

typedef struct {
    lightswitch_t   read_switch;
    pthread_mutex_t room_empty;
    pthread_mutex_t turnstile;
} readers_writers_sync_t;

void readers_writers_sync_init(readers_writers_sync_t *rw) {
    ligthswitch_init(&rw->read_switch);
    pthread_mutex_init(&rw->room_empty, NULL);
    pthread_mutex_init(&rw->turnstile, NULL);
}

void readers_writers_sync_destroy(readers_writers_sync_t *rw) {
    lightswitch_destroy(&rw->read_switch);
    pthread_mutex_destroy(&rw->room_empty);
    pthread_mutex_destroy(&rw->turnstile);
}

readers_writers_sync_t rwsync; /* don't forget to init!!! */

void exit_on_mtx_error(int res, const char *msg) {
    if (res != 0) {
        fprintf(stderr, "Error %s.\n", msg);
        exit(EXIT_FAILURE);
    }
}

void writer_fun() {
    int res;
    
    res = pthread_mutex_lock(&rwsync.turnstile);
    exit_on_mtx_error(res, "locking turnstile");
    
    res = pthread_mutex_lock(&rwsync.room_empty);
    exit_on_mtx_error(res, "locking room_empty");
    
    /* critical section for writer */
    
    res = pthread_mutex_unlock(&rwsync.turnstile);
    exit_on_mtx_error(res, "unlocking turnstile");
    
    res = pthread_mutex_unlock(&rwsync.room_empty);
    exit_on_mtx_error(res, "unlocking room_empty");
}

void reader_fun() {
    int res;
    
    res = pthread_mutex_lock(&rwsync.turnstile);
    exit_on_mtx_error(res, "locking turnstile");
    res = pthread_mutex_unlock(&rwsync.turnstile);
    exit_on_mtx_error(res, "unlocking turnstile");
    
    lightswitch_lock(&rwsync.read_switch, &rwsync.room_empty);
    exit_on_mtx_error(rwsync.read_switch.last_m_err, "m lightswitch");
    exit_on_mtx_error(rwsync.read_switch.last_s_err, "s lightswitch");
    
    /* critical section for reader */
    
    lightswitch_unlock(&rwsync.read_switch, &rwsync.room_empty);
    exit_on_mtx_error(rwsync.read_switch.last_m_err, "m lightswitch");
    exit_on_mtx_error(rwsync.read_switch.last_s_err, "s lightswitch");
}

pthread_mutex_t wait_time_mtx = PTHREAD_MUTEX_INITIALIZER;
double max_wait_time = 0.0;

double max_val(double a, double b) {
    return a < b ? b : a;
}


#define MT_AMT 1000
volatile int    thread_active[MT_AMT];
pthread_t       thread_buff[MT_AMT];


void *thread_fun(void *params) {
    int     id = (int)params;
    int     res;
    
    //clock_t start_time;
    //clock_t wait_time;
    struct timespec delay_tim;
    struct timespec measure_tim_start;
    struct timespec measure_tim_stop;
    double accum;
    
    //printf("my id: %d\n", id);
    
    //start_time = clock();
    
    if (clock_gettime(CLOCK_REALTIME, &measure_tim_start) == -1){
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }
    
    delay_tim.tv_sec = 0;
    delay_tim.tv_nsec = rand() % 100 + 10;
    nanosleep(&delay_tim, NULL);
    

    /* do your thing */
    if(rand() % 100 <= config.reader_prob) {
        /* reader */
        reader_fun();
    } else {
        /* writer */
        writer_fun();
    }
    
    //wait_time = clock() - start_time;
    if (clock_gettime(CLOCK_REALTIME, &measure_tim_stop) == -1){
        perror("clock gettime");
        exit(EXIT_FAILURE);
    }
    
    accum = ( measure_tim_stop.tv_sec - measure_tim_start.tv_sec )
          + ( measure_tim_stop.tv_nsec - measure_tim_start.tv_nsec )
            / 1000000000.0;
    
    res = pthread_mutex_lock(&wait_time_mtx);
    exit_on_mtx_error(res, "locking wait_time");
    
    max_wait_time = max_val(accum, max_wait_time);
    
    res = pthread_mutex_unlock(&wait_time_mtx);
    exit_on_mtx_error(res, "unlocking wait_time");
    
    thread_active[id] = 2;
    
    return NULL;
}



int main(int argc, char **argv) {
    time_t          start_time;
    int             threads_running = 0;
    pthread_attr_t  attr;
    int             res;
    
    struct timespec tim;

    get_options(argc, argv);
    
    srand(time(NULL));
    
    printf("N: %d M: %d P: %d\n", config.period_mt_amt, config.max_mt_amt, config.reader_prob);
    
    readers_writers_sync_init(&rwsync);
    
    
    res  = pthread_attr_init(&attr);  
    /*
    res |= pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (res != 0) {
        fprintf(stderr, "Error setting thread detached state");
        exit(EXIT_FAILURE);
    }
    */
    
    start_time = time(NULL);
    
    while(time(NULL) < start_time + 3) {
        tim.tv_sec = 0;
        tim.tv_nsec = rand() % 800;
        nanosleep(&tim, NULL);

        for (int i = 0; i < config.max_mt_amt; ++i) {
            if (thread_active[i] == 0) {
                thread_active[i] = 1;
                res = pthread_create(thread_buff + i, &attr, thread_fun, (void*)i);
                if (res > 0) {
                    perror("Thread creation failed");
                    exit(EXIT_FAILURE);
                }
                threads_running += 1;
            }
            if (threads_running >= config.period_mt_amt) {
                break;
            }
        }
        
        do {
            for (int i = 0; i < config.max_mt_amt; ++i) {
                if (thread_active[i] == 2) {
                    if (pthread_join(thread_buff[i], NULL) > 0) {
                        perror("Thread joining failed");
                    }
                    thread_active[i] = 0;
                    threads_running -= 1;
                }
            }
        } while (threads_running >= config.max_mt_amt);
    }
    
    while (threads_running > 0) {
        for (int i = 0; i < config.max_mt_amt; ++i) {
            if (thread_active[i] == 2) {
                if (pthread_join(thread_buff[i], NULL) > 0) {
                    perror("Thread joining failed");
                }
                thread_active[i] = 0;
                threads_running -= 1;
            }
        }
    }
    
    readers_writers_sync_destroy(&rwsync);
    
    printf("Max wait time is %lf\n", max_wait_time);
    
    exit(EXIT_SUCCESS);
}