# Sample makefile for GSPAN programs.
#   GSPAN Version 3.1.
# Machine type: DEC Alpha AXP/OpenVMS
 
C_DIR = 
OBJ_DIR = 
EXE_DIR = 
PURGE = purge
H_DIR = 
CCFLAGS = /NOWARNING/FLOAT=IEEE_FLOAT/STANDARD=VAXC/EXTERN=COMMON/SHARE
LIB_DIR = 
 
# WARNING: LIBS should use the library that supports the network
# protocols that are available on your machine.
# Default is to use LIBDEC.  See gsioptions.opt.
 
LIBS =  ,libgspan.olb/lib, gsioptions/opt
 
H_FILES = $(H_DIR)gspan.h $(H_DIR)icp.h $(H_DIR)xs_sys.h
EXECUTABLES= $(EXE_DIR)gsp_exm1.exe $(EXE_DIR)gsp_exm2.exe
GSP_EXM1_FILES = $(OBJ_DIR)gsp_exm1.obj, $(OBJ_DIR)gsp_mai1.obj, $(OBJ_DIR)gspan_main.obj
GSP_EXM2_FILES = $(OBJ_DIR)gsp_exm2.obj, $(OBJ_DIR)gsp_mai2.obj, $(OBJ_DIR)gspan_main.obj
 
ALL : $(EXECUTABLES)
     $(PURGE) $(OBJ_DIR)
     $(PURGE) $(EXE_DIR)
 
$(EXE_DIR)gsp_exm1.exe : $(GSP_EXM1_FILES)
	link/executable=$(EXE_DIR)gsp_exm1.exe $(GSP_EXM1_FILES) $(LIBS)
 
$(EXE_DIR)gsp_exm2.exe : $(GSP_EXM2_FILES)
	link/executable=$(EXE_DIR)gsp_exm2.exe $(GSP_EXM2_FILES) $(LIBS)
 
$(OBJ_DIR)gsp_exm1.obj : $(C_DIR)gsp_exm1.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gsp_exm1.c
 
$(OBJ_DIR)gsp_exm2.obj : $(C_DIR)gsp_exm2.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gsp_exm2.c
 
$(OBJ_DIR)gsp_mai1.obj : $(C_DIR)gsp_mai1.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gsp_mai1.c
 
$(OBJ_DIR)gsp_mai2.obj : $(C_DIR)gsp_mai2.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gsp_mai2.c
 
$(OBJ_DIR)gspan_main.obj : $(C_DIR)gspan_main.c $(H_FILES)
	CC $(CCFLAGS) $(C_DIR)gspan_main.c
