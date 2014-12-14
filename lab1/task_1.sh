#!/bin/bash

source "utils.sh"


# By default, ps selects all processes with the same effective user ID (euid=EUID) as the current user and
# associated with the same terminal as the invoker. It displays the process ID (pid=PID), the terminal
# associated with the process (tname=TTY), the cumulated CPU time in [DD-]hh:mm:ss format (time=TIME),
# and the executable name (ucmd=CMD). Output is unsorted by default.
echo ps
generic_pause

ps

echo ps -A
generic_pause

# -A Select all processes. Identical to -e.

ps -A

echo ps -a
generic_pause

# -a Select all processes except both session leaders (see getsid(2)) and processes not associated with a terminal.


ps -a

echo ps -u"${USER}"
generic_pause

# -u userlist
#    Select by effective user ID (EUID) or name. This selects the processes whose effective user name or ID is in userlist.
#    The effective user ID describes the user whose file access permissions are used by the process (see geteuid(2)). Identical to U and --user.


ps -u"${USER}"

echo ps -CSciTE
generic_pause

# -C cmdlist
#    Select by command name. This selects the processes whose executable name is given in cmdlist.
#    Displays all the processes with the given name.

SciTE & SciTE & SciTE &

ps -CSciTE

echo ps -CSciTE -opid -oppid -ogid -otty
generic_pause

# Display proces id, parent id, group id, associated terminal

ps -CSciTE -opid -oppid -ogid -otty

echo ps -Af
generic_pause

# Display all processes. The kernel threads are enclosed in brackets []. Notice that their parent is kthreadd with PID=2.

ps -Af

# As a consequence the kernel threads can be found like this:

echo ps --ppid 2
generic_pause

ps --ppid 2

echo ps -AH
generic_pause

# Tree structure.

ps -AH

echo ps -AHf
generic_pause

# -m Show threads after processes.
#ps -m

# Display a tree with threads/

ps -AHf

echo ps -Cinit -oppid
generic_pause

# Init process. Its parent has pid=0. The parent is a privileged process (a process with effective ID = 0 bypasses permission restrictions).
# When booting the system, the kernel creates a special process called init, the �parent
# of all processes,� which is derived from the program file  /sbin/init . All processes
# on the system are created (using fork()) either by init or by one of its descendants.
# The init process always has the process ID 1 and runs with superuser privileges. The
# init process can�t be killed (not even by the superuser), and it terminates only when
# the system is shut down. The main task of init is to create and monitor a range of
# processes required by a running system. 

ps -Cinit -oppid

# Identyfikator - rodzaj symbolu u�ywanego do rozpoznawania jakiej� istoty.
# Identyfikator u�ytkownika - ka�dy u�ytkownik w systemie ma unikalny logn oraz 
#         odpowiadaj�cy mu unikalny numer UID. (informacja przechowywana w /etc/passwd)
# Identyfikator procesu - unikalna liczba przypisana procesowi.
# Identyfikator rodzica - unikalna liczba przypisana procesowi-rodzicowi (ten co wykona� fork()).
# Grupa procesu - Wszystkie procesy w pipeline (np. ls -l | sort -k5n | less) maj� przydzielon� grup�.
#         Numer grupy jest taki sam jak pid jednego z proces�w z tej grupy zwanego liderem grupy.
#         Kernel pozwala na wykonywanie pewnego zbioru dzia�a� na grupach, np. mo�na wys�a� sygna� do
#         ka�dego programu w grupie lub u�pi� wszystkie procesy w grupie.
# Grupa - u�ytkownicy mog� by� przypisani do wielu grup. Taka organizacja pozwala
#         lepiej kontrolowa� dost�p do plik�w i innych zasob�w systemu. Przyk�adowo
#         osoby pracuj�ce w zespole mog� wsp�dzieli� pewien zbi�r plik�w.
#         Ka�da grupa w systemie jest opisana w pojedy�czej linijce w pliku /etc/group,
#         kt�ry zawiera nast�puj�ce informacje: nazwa grupy, GID (group id), lista login�w u�ytkownik�w.
# Terminal steruj�cy (controlling terminal) - terminal (tname=TTY), kt�ry zosta� uruchomiony jako pierwszy przez lidera sesji. 
#         Przyk�adowo pts/1. Mo�e te� by� ? je�li proces nie by� uruchomiony z terminala.
# Rodzic procesu - proces, kt�ry wywo�a� fork().
# Jest podzia� na effective i real ID. Real ID identyfikuje prawdziwego u�ytkownika, do kt�rego nale�y
# proces. Effective ID jest u�ywany do obliczania uprawnie� w przypadku dost�pu do jakiego� zasobu.
# Dzi�ki temu mechanizmowi proces mo�e u�ywa� zasob�w innego u�ytkownika itp.
