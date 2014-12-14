# renice - alter priority of running processes

# run this in several terminals
echo "" | awk '{for(;;) {}}'

# run evince
evince

# -20 means highest priority
# 20 means lowest priority

# renice -n priority -p pid
renice -n 10 -p 15703 #przewijanie bardzo wolno działa

# Jedynie root może zwiększyć z powrotem priorytet programu.
renice -n 0 -p 15703

# Users other than the super-user may only alter the priority of processes they own, and can only monotonically
# increase their ``nice value'' (for security reasons) within the range 0 to PRIO_MAX (20), unless a nice resource
# limit is set (Linux 2.6.12 and higher).  The super-user may alter the priority of any process and set the priority
# to any value in the range PRIO_MIN (-20) to PRIO_MAX.  Useful priorities are: 20 (the affected processes
# will run only when nothing else in the system wants to), 0 (the ``base'' scheduling priority), anything negative
# (to make things go very fast).