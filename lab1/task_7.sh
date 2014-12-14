kill -l
# 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
# 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
# 11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
# 16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
# 21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
# 26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
# 31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
# 38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
# 43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
# 48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
# 53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
# 58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
# 63) SIGRTMAX-1	64) SIGRTMAX	

# SIGSTOP = 20 This is the sure stop signal. It can’t be blocked, ignored, or caught by a handler;
# thus, it always stops a process.

# SIGCONT = 18


ps -Cxeyes

# W podręczniku strona 716

kill -SIGSTOP PID

# Możemy przywrócić aplikację za pomocą:
fg
fg 1
bg 1 # W tle

# lub możemy wysłać sigcont

# W pliku /proc/pid/status
#SigPnd, ShdPnd: Number of signals pending for thread and for process as a whole (see pthreads(7) and signal(7)).
#SigBlk, SigIgn, SigCgt: Masks indicating signals being blocked, ignored, and caught (see signal(7)).
#SigPnd: 0000000000000000 ShdPnd: 0000000000000000 SigBlk: fffffffe7ffbfeff SigIgn: 0000000000000000 SigCgt: 0000000000000000

#lub

ps -C xeyes -o pid,comm,pending

# przykładowe wysyłanie sygnałów
kill -19 [pid] #stop
kill -18 [pid] #start
ps -C xeyes -o pid,comm,pending
kill -10 [pid] #sygnal USR1, po nim zapalony jest 10 bit maski
kill -12 [pid] #sygnal USR2, teraz zapalony jest 10 i 12 bit

