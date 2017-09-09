cc -c -D$MACHINE gsi_brg.c
cc -c -D$MACHINE nsleep.c
ar ru tools.a gsi_brg.o nsleep.o
ranlib tools.a
