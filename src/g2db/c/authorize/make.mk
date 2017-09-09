#########################################################################
##
## tools.a       Bridge Licensing Module                       (rjf-5/99)
##
##  This file is used to build the Gensym Bridge Licensing Module. This
##  file and the files to which it refers are confidential and must not
##  be distributed outside of the Cambridge office. The sources referenced
##  herein are intended for AUTHORIZED PERSONNEL ONLY.     
##
##----------------------------------------------------------------------
##
SOURCE_DIR  = $(authorize_wrk)
OBJ_DIR     = $(authorize_wrk)

##  INPUT MACROS
##----------------------------------------------------------------------
# ex: make DEBUG=-g -f gdb-oracle.mms -- DEBUG set to -O otherwise
DEBUG       = $(OPTIMIZE)
DBG         = $(DEBUG:%=%)

CFLAGS      = $(DBG) -c -I$(SOURCE_DIR) -D$(cur_platform)
LFLAGS      = $(DBG) -O

CC          = cc

OBJS        = auth-test.o nsleep.o gsi_brg.o
ARCH_OBJS   = nsleep.o gsi_brg.o
TEST_EXE    = $(OBJ_DIR)auth-test
ARCHIVE     = $(OBJ_DIR)tools.a


##  COMPILE & LINK SOURCES
##--------------------------------------------------------------
##

ALL: settings $(ARCHIVE) $(TEST_EXE)

$(TEST_EXE): $(ARCHIVE) $(OBJS)
	$(CC) $(LFLAGS) -o $@ $@.c $(ARCHIVE)
	@echo ""

$(OBJS): $(SOURCE_DIR)$$(@F:.o=.c)
	$(CC) $(CFLAGS) $(SOURCE_DIR)$(@F:.o=.c)
	@echo ""

$(ARCHIVE): $(ARCH_OBJS)
	ar ru $(@F) $(ARCH_OBJS)
	ranlib $(ARCHIVE)
	@echo ""


settings:
	@echo " =================================="
	@echo "  BUILDING BRIDGE LICENSING MODULE"
	@echo "      on $(cur_platform)"
	@echo " =================================="
	@echo ""
	@echo " ENVIRONMENT"
	@echo "   Platform    : $(cur_platform)"
	@echo "   Source    : $(SOURCE_DIR)"
	@echo "   Objects   : $(OBJ_DIR)"
	@echo ""
	@echo " =================================="
	@echo ""
