# Sample makefile for foreign images to connect to G2.
# Machine type: Vax VMS
 
C_DIR = 
OBJ_DIR = 
EXE_DIR = 
TEMPLATE_DIR = $(C_DIR)
PURGE = purge
H_DIR = 
CCFLAGS = /NOWARNING/DEFINE=("CC$mixed_float")
LIB_DIR = 
 
LIBS =  ,$(LIB_DIR)libforgn.olb/lib
 
H_FILES = $(H_DIR)foreign.h
EXECUTABLES = $(EXE_DIR)fgntest.fgn
FGNTEST_FILES = $(OBJ_DIR)fgntest.obj, $(OBJ_DIR)fgnover.obj
 
ALL : $(EXECUTABLES)
     $(PURGE) $(OBJ_DIR)
     $(PURGE) $(EXE_DIR)
 
$(EXE_DIR)fgntest.fgn : $(FGNTEST_FILES)
	link/executable=$(EXE_DIR)fgntest.fgn $(FGNTEST_FILES) $(LIBS)
 
$(OBJ_DIR)fgntest.obj : $(C_DIR)fgntest.c $(H_FILES)
	CC /OBJECT=$(OBJ_DIR)fgntest.obj $(CCFLAGS) $(C_DIR)fgntest.c
 
$(OBJ_DIR)fgnover.obj : $(C_DIR)fgnover.c $(H_FILES)
	CC /OBJECT=$(OBJ_DIR)fgnover.obj $(CCFLAGS) $(C_DIR)fgnover.c
 
$(C_DIR)fgnover.c : $(TEMPLATE_DIR)fgntest.tpl
	overlay $(TEMPLATE_DIR)fgntest.tpl  $(C_DIR)fgnover.c
