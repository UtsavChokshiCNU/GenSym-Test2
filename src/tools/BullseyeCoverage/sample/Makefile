# Copyright (c) Bullseye Testing Technology
# Makefile to build sample programs

all: calc1.exe calc2.exe bounce.exe

run: calc1.exe calc2.exe
	echo 123 456 + 2 / = | calc1
	echo 123 + 456 / 2   | calc2

calc1.exe: calc1.cpp
	$(CC) calc1.cpp
calc2.exe: calc2.c
	$(CC) calc2.c
bounce.exe: bounce.cpp
	$(CC) bounce.cpp

clean:
	rm -f *.obj *.exe
