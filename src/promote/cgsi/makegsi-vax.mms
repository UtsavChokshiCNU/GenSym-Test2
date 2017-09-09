# Sample makefile for GSI programs.
#   GSI Version 3.2.
# Machine type: Vax VMS
 
C_DIR = 
OBJ_DIR = 
EXE_DIR = 
PURGE = purge
H_DIR = 
CCFLAGS = /NOWARNING/DEFINE=("CC$mixed_float")
LIB_DIR = 
 
# WARNING: LIBS should use the library that supports the network
# protocols that are available on your machine.
# Default is to use LIBDEC.  See gsioptions.opt.
 
LIBS =  ,gsioptions/opt
 
H_FILES = $(H_DIR)gsi.h $(H_DIR)icp.h
EXECUTABLES = $(EXE_DIR)filetest.exe $(EXE_DIR)typetest.exe $(EXE_DIR)skeleton.exe
FILETEST_FILES = $(OBJ_DIR)filetest.obj, $(OBJ_DIR)rpcfuncs.obj
TYPETEST_FILES = $(OBJ_DIR)typetest.obj, $(OBJ_DIR)gsi_main.obj
SKELETON_FILES = $(OBJ_DIR)skeleton.obj, $(OBJ_DIR)gsi_main.obj
 
ALL : $(EXECUTABLES)
     $(PURGE) $(OBJ_DIR)
     $(PURGE) $(EXE_DIR)
 
$(EXE_DIR)filetest.exe : $(FILETEST_FILES)
	link/executable=$(EXE_DIR)filetest.exe $(FILETEST_FILES) $(LIBS)
 
$(EXE_DIR)skeleton.exe : $(SKELETON_FILES)
	link/executable=$(EXE_DIR)skeleton.exe $(SKELETON_FILES) $(LIBS)
 
$(EXE_DIR)typetest.exe : $(TYPETEST_FILES)
	link/executable=$(EXE_DIR)typetest.exe $(TYPETEST_FILES) $(LIBS)
 
$(OBJ_DIR)filetest.obj : $(C_DIR)filetest.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)filetest.c
 
$(OBJ_DIR)typetest.obj : $(C_DIR)typetest.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)typetest.c
 
$(OBJ_DIR)rpcfuncs.obj : $(C_DIR)rpcfuncs.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)rpcfuncs.c
 
$(OBJ_DIR)skeleton.obj : $(C_DIR)skeleton.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)skeleton.c
 
$(OBJ_DIR)gsi_main.obj : $(C_DIR)gsi_main.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gsi_main.c
