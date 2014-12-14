#!/bin/bash

source "utils.sh"
ex_program=SciTE

# Kill expects pid of a process to kill. It can be found with pgrep.

echo kill
generic_pause

${ex_program} &
generic_pause
kill $(pgrep ${ex_program})

# Select window of a program that you want to kill with your cursor.

echo xkill
${ex_program} &
xkill

# The pkill command works in almost exactly the same way as kill, but it operates on a process name instead:

echo pkill
generic_pause

${ex_program} &
generic_pause
pkill ${ex_program}

echo pgrep
generic_pause

# Pgrep usage:
# pgrep [options] pattern

# List all processes pids run as root:
pgrep -u root

# List all processes pids which names start with b
pgrep ^b

# Kill domyślnie wysyła sygnał TERM. Aby wymusić zatrzymanie procesu należy uruchomić:
# kill -9 -1 # SIGKILL i SIGHUP