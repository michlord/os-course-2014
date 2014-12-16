#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* Utility procedures. */

pthread_t make_thread(const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) {
    int res;
    pthread_t thread;
    
    res = pthread_create(&thread, attr, start_routine, arg);
    if (res != 0) {
        perror("pthread_create failed");
        exit(EXIT_FAILURE);
    }
    
    return thread;
}

void join_thread(pthread_t thread) {
    int res;
    
    res = pthread_join(thread, NULL);
    if (res == -1) {
        perror("pthread_join failed");
        exit(EXIT_FAILURE);
    }
}

void my_nanosleep(long int nsec) {
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = nsec;
    nanosleep(&tim, NULL);
}

void rand_delay() {
    my_nanosleep(rand() % 300 + 20);
}

void lock_mutex(pthread_mutex_t *mutex) {
    int res;
    
    res = pthread_mutex_lock(mutex);
    if (res != 0) {
        perror("pthread_mutex_lock failed");
        exit(EXIT_FAILURE);
    }
}

void unlock_mutex(pthread_mutex_t *mutex) {
    int res;
    
    res = pthread_mutex_unlock(mutex);
    if (res != 0) {
        perror("pthread_mutex_unlock failed");
        exit(EXIT_FAILURE);
    }
}

void wait_cond(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex) {
    int res;
    
    res = pthread_cond_wait(cond, mutex);
    if (res != 0) {
        perror("pthread_cond_wait failed");
        exit(EXIT_FAILURE);
    }
}

void signal_cond(pthread_cond_t *cond) {
    int res;
    
    res = pthread_cond_signal(cond);
    if (res != 0) {
        perror("pthread_cond_signal failed");
        exit(EXIT_FAILURE);
    }
}

/* Consumer and producer procedures. */

#define MAX 1000000

int buffer[MAX];
int fill_idx  = 0; /* Points to the next index to put an item in the buffer. */
int use_idx   = 0; /* Points to the next index to retrieve an item from the buffer. */
int count = 0; /* The count of the items in the buffer. */

pthread_cond_t  empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t  fill = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(int value) {
    buffer[fill_idx] = value;
    fill_idx = (fill_idx + 1) % MAX;
    count += 1;
}

int get() {
    int tmp = buffer[use_idx];
    use_idx = (use_idx + 1) % MAX;
    count -= 1;
    return tmp;
}

void *producer(void *params) {
    int i;
    int loops = (int) params;
    
    for (i = 0; i < loops; ++i) {
        rand_delay();
        lock_mutex(&mutex);
        while (count == MAX) {
            wait_cond(&empty, &mutex);
        }
        put(i);
        printf("Produced: %d\n", i);
        signal_cond(&fill);
        unlock_mutex(&mutex);
    }
    
    return NULL;
}

void *consumer(void *params) {
    int i;
    int loops = (int) params;
    
    for (i = 0; i < loops; ++i) {
        rand_delay();
        lock_mutex(&mutex);
        while (count == 0) {
            wait_cond(&fill, &mutex);
        }
        int tmp = get();
        printf("Consumed: %d\n", tmp);
        signal_cond(&empty);
        unlock_mutex(&mutex);
    }
    
    return NULL;
}


/* To monitor the threads you could use ps -Lf -Ctask5 */
int main() {
    int       i;
    int       producer_amt = 6;
    int       consumer_amt = 6;
    pthread_t thread_buff[producer_amt + consumer_amt];
    int       thread_buff_count = 0;
    int       remaining_loops = MAX;
    int       loops;
    pthread_t tmp_thread;
    
    for (i = 0; i < producer_amt + consumer_amt; ++i) {
        if (i % 2) {
            loops = (MAX / consumer_amt) - (rand() % 100000);
            remaining_loops -= loops;
            if (i + 1 >= producer_amt + consumer_amt) {
                loops = remaining_loops;
            }
            tmp_thread = make_thread(NULL, consumer, (void *)loops);
        } else {
            tmp_thread = make_thread(NULL, producer, (void *) (MAX / producer_amt));
        }
        thread_buff[thread_buff_count++] = tmp_thread;
    }
    
    for (i = 0; i < thread_buff_count; ++i) {
        join_thread(thread_buff[i]);
    }

    exit(EXIT_SUCCESS);
}




