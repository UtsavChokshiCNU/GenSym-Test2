#
# nmake makefile for corbalink
#
!INCLUDE corba-win.def

MACHINE = intelnt
MACHINE_DIR = nt

BASE_PATH = .\ 
SRC_PATH = $(BASE_PATH)
OBJ_DIR  = $(BASE_PATH)$(MACHINE_DIR)
OBJ_PATH = $(OBJ_DIR)\ 
!ifndef GSI_PATH
GSI_PATH = k:/bt/ab/dst/intelnt/gsi/tape/
!endif
AUTHDR   = k:/bt/dw/g2db/c/authorize/
SPECFC   = k:/bt/ab/specific/intelnt/

PLATFORM_LIBS = advapi32.lib gdi32.lib user32.lib wsock32.lib rpcrt4.lib version.lib

LIBS = $(GSI_PATH)gsi_misc.obj $(GSI_PATH)libgsi.lib \
       $(GSI_PATH)libtcp.lib $(GSI_PATH)libnogsec.lib $(GSI_PATH)librtl.lib \
       $(GSI_PATH)libmmt.lib $(GSI_PATH)libircmt.lib $(PLATFORM_LIBS) \
       k:/bt/ab/specific/intelnt/spromeps.lib

COPTIONS = /nologo /ML /W3 /GX /O2 /Fo"$(OBJ_PATH)\" /c
CDEFINES = /DWIN32 /D$(MACHINE) /DCORBALINK_VER=\"$(CORBALINK_VER)\" /DG2KB_VER=\"$(G2KB_VER)\" /DG2KB_IDL_VER=\"$(G2IDL_VER)\"
CINCLUDES = /I$(SRC_PATH) /I$(GSI_PATH) /I$(AUTHDR)

CFLAGS = $(COPTIONS) $(CDEFINES) $(CINCLUDES)

LINKFLAGS = /nodefaultlib:libcmt.lib

GSI_HEADERS = $(GSI_PATH)gsi_main.h

COMMON_DEPS = $(GSI_HEADERS) $(SRC_PATH)corbalink-nt.mak $(SRC_PATH)corba-win.def

EXE_1 = $(OBJ_PATH)g2-corba.exe

EXECUTABLES = $(EXE_1)

EXE_1_CPP_OBJS = \
  $(OBJ_PATH)builder.obj \
  $(OBJ_PATH)code_tokens.obj \
  $(OBJ_PATH)connections.obj \
  $(OBJ_PATH)download_ir.obj \
  $(OBJ_PATH)encoding.obj \
  $(OBJ_PATH)error_handler.obj \
  $(OBJ_PATH)G2Container.obj \
  $(OBJ_PATH)G2CorbaContainer.obj \
  $(OBJ_PATH)g2item.obj \
  $(OBJ_PATH)g2string.obj \
  $(OBJ_PATH)gsi_compile_idl.obj \
  $(OBJ_PATH)gsi_fcns.obj \
  $(OBJ_PATH)iiop.obj \
  $(OBJ_PATH)init_context.obj \
  $(OBJ_PATH)ior.obj \
  $(OBJ_PATH)lex_1.obj \
  $(OBJ_PATH)locator.obj \
  $(OBJ_PATH)orbtype.obj \
  $(OBJ_PATH)parse.obj \
  $(OBJ_PATH)parse_tree_node.obj \
  $(OBJ_PATH)pause.obj \
  $(OBJ_PATH)recv_req.obj \
  $(OBJ_PATH)reg_obj.obj \
  $(OBJ_PATH)reg_proxy.obj \
  $(OBJ_PATH)send_req.obj \
  $(OBJ_PATH)shutdown_context.obj \
  $(OBJ_PATH)sockbase.obj \
  $(OBJ_PATH)startup.obj \
  $(OBJ_PATH)token.obj \
  $(OBJ_PATH)utils.obj

EXE_1_C_OBJS = \
  $(OBJ_PATH)ytab.obj \
  $(OBJ_PATH)gsi_brg.obj \
  $(SPECFC)nsleep.obj

EXE_1_RESOURCE = $(OBJ_PATH)g2corba.res

EXE_1_OBJS = $(EXE_1_CPP_OBJS) $(EXE_1_C_OBJS) $(EXE_1_RESOURCE)

#
# Everything depends on the executable
#
ALL: $(OBJ_DIR) auth $(EXECUTABLES)

auth:
	cl -o $(OBJ_PATH)gsi_brg.obj $(CFLAGS) $(AUTHDR)gsi_brg.c

.c{$(OBJ_PATH)}.obj:
	cl $(CFLAGS) $<

.cpp{$(OBJ_PATH)}.obj:
	cl $(CFLAGS) $<

.rc{$(OBJ_PATH)}.res:
	rc /l 0x409 /fo$@ /d "NDEBUG" $<


$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(EXE_1): $(EXE_1_OBJS)
	link $(LINKFLAGS) -out:$@ $(EXE_1_OBJS) $(LIBS)

$(EXE_1_CPP_OBJS): $(COMMON_DEPS)
$(EXE_1_C_OBJS): $(COMMON_DEPS)
