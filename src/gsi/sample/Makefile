##
# This is a sample Makefile for a GSI bridge.
# Use it as an example for making your own Makefiles,
# or other build scripts.
#
# It should be very portable, but, it was only tested
# on Linux with GNU Make.
#

# Set the path to `gsi_main.c` here (if you're using it).
# The `matrix.c` example uses it. You can also write your 
# own `main()`, if you wish, but do take a look at
# `gsi_main.c`, for reference.
PATH_TO_GSI_MAIN_C=.

# Set the path to GSI libraries here
PATH_TO_GSILIB=.

# Set the path to GSI sample here (obviously, relevant
# only for this sample Makefile)
PATH_TO_GSI_SAMPLE=.

GSI_LIBS=$(PATH_TO_GSILIB)/libgsi.a $(PATH_TO_GSILIB)/libtcp.a $(PATH_TO_GSILIB)/librtl.a $(PATH_TO_GSILIB)/libnogsec.a

all: matrix

# The `matrix` sample GSI bridge
matrix: $(PATH_TO_GSI_SAMPLE)/matrix.c $(PATH_TO_GSI_MAIN_C)/gsi_main.c
	$(CC) -Wno-deprecated-declarations -o matrix $(PATH_TO_GSI_SAMPLE)/matrix.c $(PATH_TO_GSI_MAIN_C)/gsi_main.c $(GSI_LIBS) -lm -ldl

clean:
	rm matrix
