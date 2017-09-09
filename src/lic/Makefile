### This is the make file for the client tools for accessing the
### Gensym Corp. licensing client.

# We have three types of files in here.
#   .c  -- C source files.
#   .o  -- object files
#   .c-crypt -- Encrypted C source.

.SUFFIXES: .c .o

# We prefer the GNU C compiler, and since
CC = gcc

# This code, having been written from scratch can be
# implemented very fastidiously, hence we can throw the
# -W switch.
CFLAGS = -W -g

# The encrypted source is decrypted only during the compile.
# presumably LS_CPW is the in the environment (consider M-X setenv).
#.c-crypt.o :
#	@ des -d -f -k ${LS_CPW} $< $*.c
#	$(COMPILE.c) $(OUTPUT_OPTION) $*.c
#	rm $*.c
.o :
	$(COMPILE.c) $(OUTPUT_OPTION) $*.c


# The two programs we build here:
#  licensing-client -- a program which contacts the licensing server to obtain
#                      licenses for Gensym products.
#  response -- a program used by the awk program to compute the response to a
#              password request.
all : licensing-client response


# Licensing-client is used by the corp database to generate codes.
licensing-client : licensing-client.o response-util.o
	gcc -o $@ licensing-client.o response-util.o

# Response is used by the original licensing client written in Perl.
response : response.o
	gcc -o $@ response.o


# Misc. inter-module dependencies.
response-util.o :  response-util.h
licensing-client.o :  response-util.h

clean :
	rm *.o
