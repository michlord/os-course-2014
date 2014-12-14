vim
ps -Cxeyes
xeyes_pid=13908
cd /proc/${xeyes_pid}
ls
cat cmdline
cat environ

# Zmienne œrodowiskowe - Each process has an environment list, which is a set of environment variables that are
# maintained within the user-space memory of the process. Each element of this list
# consists of a name and an associated value.


# Strony w podrêczniku na temat maps
#/proc/PID/maps file, 225, 842, 1006, 1008,
#1019, 1025, 1041, 1115
#example of use, 1046

#Przydatna strona 1008


# 08048000-081f0000 r-xp 00000000 08:01 145947     /usr/bin/vim.basic
# 081f0000-081f1000 r--p 001a7000 08:01 145947     /usr/bin/vim.basic
# 081f1000-081ff000 rw-p 001a8000 08:01 145947     /usr/bin/vim.basic
# 081ff000-08209000 rw-p 00000000 00:00 0 
# 08b07000-08b6d000 rw-p 00000000 00:00 0          [heap]
# b73f0000-b73fa000 r-xp 00000000 08:01 29627      /lib/i386-linux-gnu/libnss_files-2.13.so
# b73fa000-b73fb000 r--p 00009000 08:01 29627      /lib/i386-linux-gnu/libnss_files-2.13.so
# b73fb000-b73fc000 rw-p 0000a000 08:01 29627      /lib/i386-linux-gnu/libnss_files-2.13.so
# b73fc000-b7405000 r-xp 00000000 08:01 29629      /lib/i386-linux-gnu/libnss_nis-2.13.so
# b7405000-b7406000 r--p 00008000 08:01 29629      /lib/i386-linux-gnu/libnss_nis-2.13.so
# b7406000-b7407000 rw-p 00009000 08:01 29629      /lib/i386-linux-gnu/libnss_nis-2.13.so
# b7407000-b741a000 r-xp 00000000 08:01 29624      /lib/i386-linux-gnu/libnsl-2.13.so
# b741a000-b741b000 r--p 00012000 08:01 29624      /lib/i386-linux-gnu/libnsl-2.13.so
# b741b000-b741c000 rw-p 00013000 08:01 29624      /lib/i386-linux-gnu/libnsl-2.13.so
# b741c000-b741e000 rw-p 00000000 00:00 0 
# b741e000-b7424000 r-xp 00000000 08:01 29625      /lib/i386-linux-gnu/libnss_compat-2.13.so
# b7424000-b7425000 r--p 00005000 08:01 29625      /lib/i386-linux-gnu/libnss_compat-2.13.so
# b7425000-b7426000 rw-p 00006000 08:01 29625      /lib/i386-linux-gnu/libnss_compat-2.13.so
# b7434000-b75ab000 r--p 00000000 08:01 132305     /usr/lib/locale/locale-archive
# b75ab000-b75ac000 rw-p 00000000 00:00 0 
# b75ac000-b75b0000 r-xp 00000000 08:01 64         /lib/i386-linux-gnu/libattr.so.1.1.0
# b75b0000-b75b1000 r--p 00003000 08:01 64         /lib/i386-linux-gnu/libattr.so.1.1.0
# b75b1000-b75b2000 rw-p 00004000 08:01 64         /lib/i386-linux-gnu/libattr.so.1.1.0
# b75b2000-b75b3000 rw-p 00000000 00:00 0 
# b75b3000-b75b5000 r-xp 00000000 08:01 29621      /lib/i386-linux-gnu/libdl-2.13.so
# b75b5000-b75b6000 r--p 00001000 08:01 29621      /lib/i386-linux-gnu/libdl-2.13.so
# b75b6000-b75b7000 rw-p 00002000 08:01 29621      /lib/i386-linux-gnu/libdl-2.13.so
# b75b7000-b76ff000 r-xp 00000000 08:01 29618      /lib/i386-linux-gnu/libc-2.13.so
# b76ff000-b7701000 r--p 00148000 08:01 29618      /lib/i386-linux-gnu/libc-2.13.so
# b7701000-b7702000 rw-p 0014a000 08:01 29618      /lib/i386-linux-gnu/libc-2.13.so
# b7702000-b7705000 rw-p 00000000 00:00 0 
# b7705000-b770a000 r-xp 00000000 08:01 145823     /usr/lib/i386-linux-gnu/libgpm.so.2
# b770a000-b770b000 rw-p 00004000 08:01 145823     /usr/lib/i386-linux-gnu/libgpm.so.2
# b770b000-b7713000 r-xp 00000000 08:01 66         /lib/i386-linux-gnu/libacl.so.1.1.0
# b7713000-b7714000 r--p 00007000 08:01 66         /lib/i386-linux-gnu/libacl.so.1.1.0
# b7714000-b7715000 rw-p 00008000 08:01 66         /lib/i386-linux-gnu/libacl.so.1.1.0
# b7715000-b7733000 r-xp 00000000 08:01 49         /lib/i386-linux-gnu/libselinux.so.1
# b7733000-b7734000 r--p 0001d000 08:01 49         /lib/i386-linux-gnu/libselinux.so.1
# b7734000-b7735000 rw-p 0001e000 08:01 49         /lib/i386-linux-gnu/libselinux.so.1
# b7735000-b7736000 rw-p 00000000 00:00 0 
# b7736000-b7753000 r-xp 00000000 08:01 51         /lib/i386-linux-gnu/libtinfo.so.5.9
# b7753000-b7755000 r--p 0001c000 08:01 51         /lib/i386-linux-gnu/libtinfo.so.5.9
# b7755000-b7756000 rw-p 0001e000 08:01 51         /lib/i386-linux-gnu/libtinfo.so.5.9
# b7756000-b777a000 r-xp 00000000 08:01 29622      /lib/i386-linux-gnu/libm-2.13.so
# b777a000-b777b000 r--p 00023000 08:01 29622      /lib/i386-linux-gnu/libm-2.13.so
# b777b000-b777c000 rw-p 00024000 08:01 29622      /lib/i386-linux-gnu/libm-2.13.so
# b7783000-b778a000 r--s 00000000 08:01 197813     /usr/lib/i386-linux-gnu/gconv/gconv-modules.cache
# b778a000-b778c000 rw-p 00000000 00:00 0 
# b778c000-b778d000 r-xp 00000000 00:00 0          [vdso]
# b778d000-b77a9000 r-xp 00000000 08:01 29615      /lib/i386-linux-gnu/ld-2.13.so
# b77a9000-b77aa000 r--p 0001b000 08:01 29615      /lib/i386-linux-gnu/ld-2.13.so
# b77aa000-b77ab000 rw-p 0001c000 08:01 29615      /lib/i386-linux-gnu/ld-2.13.so
# bfdf8000-bfe19000 rw-p 00000000 00:00 0          [stack]



# sterta - tam gdzie [heap]
# stos - tam gdzie [stack]
# segment text/data/bss - pierwsze trzy linijki odpowiadaj¹ kolejno text, data, bss.
# pozosta³oœci konsolidatora - ostatnie trzy linijki przed stack