# Nie mam gedit, a instalacja 200MB zale¿noœci nie wchodzi w rachubê.
# Robiê na przyk³adzie evince.

# An open file may be a regular file, a directory, a block special file, a character special file, an  executing
# text reference, a library, a stream or a network file (Internet socket, NFS file or UNIX domain socket.)

# semantyka pliku - This means that the same system calls (open(), read(),write(), close(), and so on)
# are used to perform I/O on all types of files, including
# devices. (The kernel translates the application’s I/O requests into appropriate file-
# system or device-driver operations that perform I/O on the target file or device.)
# Thus, a program employing these system calls will work on any type of file


lsof -c evince

# Mo¿na podawaæ jakie typy plików chcemy, ¿eby nam wyœwietli³.

# pliki: REG

# katalogi: DIR

# urz¹dzenia - (device file is an interface for a device driver that appears
# in a file system as if it were an ordinary file).
# CHR (character special file), BLK (block special file), FIFO, PIPE

# gniazda - (sockets - can be used to transfer data from one process to another, either
# on the same host computer or on different hosts connected by a network).
# unix, sock, IPv4

# po otwarciu pliku dosz³o:
# evince  16317 michlord   15r   REG        8,1   220889  49694 /home/michlord/operating_systems/example.pdf

