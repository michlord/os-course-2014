# Przodek procesu - proces będący wyżej w drzewie procesów niż jego potomek.
# Uruchomienie w tle - program zostaje uruchomiony i wraca kontrola do powłoki.

#terminal 1

bash
xclock &
pstree

#terminal 2
ps -Cxclock -o pid,ppid
# ppid odpowiada pid nowego basha
kill -SIGKILL ppid #zegarek zostaje zaadoptowany przez init
pstree

kill -SIGHUP ppid #zegarek umiera razem z bashem
pstree


