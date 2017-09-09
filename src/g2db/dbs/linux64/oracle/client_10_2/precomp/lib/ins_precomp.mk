# Entering /build/s630/precomp/install/cus_precomp.mk
include $(ORACLE_HOME)/precomp/lib/env_precomp.mk


MAKEFILE=$(PRECOMPLIB)ins_precomp.mk

cust_shlibs:$(LD_SHLIBS) $(DLOPEN_LIBS) $(NEW_LD_SHLIBS) $(NEW_DLOPENLIBS)\
	$(VARLIBS)

mk_softlinks:
	$(LNS) $(ORACLE_HOME)/lib/libsqlsh10.a $(ORACLE_HOME)/lib/libsql10.a

preinstall:
	$(CHMOD) $(EXE_PROT) $(ORACLE_HOME)/bin

install: preinstall $(INSTALL_TARGS)

clean_sh:
	$(RMF) $(ALL_EXECS)

$(INSTALL_SHORTCUT_TARGETS):
	$(MAKE) -f $(PRECOMPLIB)ins_precomp.mk relink EXENAME=$@

$(INSTALL_SHORTCUT_32_64_TARGETS):
	$(MAKE) -f $(PRECOMPLIB)ins_precomp.mk relink EXENAME=$@ $(PL_LINK_OVERRIDES)

$(INSTALL_RENAMED_32_64_TARGETS):
	$(MAKE) -f $(PRECOMPLIB)ins_precomp.mk relink EXENAME=$@ $(PL_LINK_OVERRIDES)
PRECOMPBIN=$(PRECOMPLIB)

relink:	$(PRECOMPBIN)$(EXENAME)
	$(RMF) $(BINHOME)$(EXENAME)
	$(MV) $(PRECOMPBIN)$(EXENAME) $(BINHOME)

rmlinks:
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) SQLCA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) ORACA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) SQLDA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) SQLCA.COB)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) ORACA.COB)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) SQLCA.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) ORACA.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) BNDDSC.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(RMF) SELDSC.FOR)

links:	rmlinks
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) sqlca.h SQLCA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) oraca.h ORACA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) sqlda.h SQLDA.H)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) sqlca.cob SQLCA.COB)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) oraca.cob ORACA.COB)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) sqlca.for SQLCA.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) oraca.for ORACA.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) bnddsc.for BNDDSC.FOR)
	($(CD) $(ORACLE_HOME)/precomp/public ; $(LNS) seldsc.for SELDSC.FOR)

comp_adalib:
	$(CD) $(PRECOMPADALIB) ; $(MAKE) -f $(PRECOMPLIB)ins_precomp.mk compile
dei_adalib:
	$(CD) $(PRECOMPADALIB) ; $(MAKE) -f $(PRECOMPLIB)ins_precomp.mk clean

.SUFFIXES: .a .ada

ADASRC= sqaqss.ada sqaosl.ada sqaoslb.ada
DEC_UN= sql_standard oracle_sqllib

compile: $(INS_ADA_COMPILE)

clean: $(INS_ADA_CLEAN)

compile_verdix: GVAS_table_verdix
	a.make -e -v -f $(ADASRC)
clean_verdix:
	$(ADACLEAN)
GVAS_table_verdix:	
	$(ECHO) 1 | a.mklib -i > /dev/null

alsys_prereq:
	-ada.mkfam $(ALSYS_FAMILY)
	-ada.mklib $(ALSYS_FAMILY) $(ALSYS_LIB)
compile_alsys: alsys_prereq
	ada.protect -u $(ALSYS_LIB)
	$(ADAMAKE) $(ALSYS_LIB) $(ADASRC)
clean_alsys:
	-ada.rmlib -f $(ALSYS_LIB)
	-ada.rmfam -f $(ALSYS_FAMLIY)

compile_dec: adalib
	ada -A@adalib $(CDEBUG) -v -y $(ADASRC)
	amake -A@adalib -C "$(CDEBUG)" -v $(DEC_UN)
clean_dec:
	$(RMRF) adalib
adalib:
	amklib adalib

compile_powerada: GVAS_table_powerada
	abuild -vF -p -Lalib.list $(ADASRC)
clean_powerada:
	alibrm -F adalib
GVAS_table_powerada:
	$(ECHO) 1 | alibinit > /dev/null
# Exiting /build/s630/precomp/install/cus_precomp.mk
# Entering link.mk

$(LOC_MODADA): $(LIBMOD) $(LIBPGP) $(PLSQLLIBS)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(MODADA_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

$(LOC_PROC): $(LIBPROC2) $(LIBPGP) $(LIBPLCN) $(PLSQLLIBS)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(PROC_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

$(LOC_PROCOB): $(LIBPROCOB2) $(LIBPGP) $(LIBPLCN) $(PLSQLLIBS)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(PROCOB_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

$(LOC_PROFOR): $(LIBPFO) $(LIBPCC) $(LIBPGP) $(LIBPLCN) $(PLSQLLIBS)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(PROFOR_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

$(LOC_PROPLI): $(LIBPPL) $(LIBPCC) $(LIBPGP) $(LIBPLCN) $(PLSQLLIBS)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(PROPLI_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

$(LOC_RTSORA): $(LIBSQL)
	$(SILENT)$(ECHO) "Linking $@"; \
	$(RMF) $@; \
	$(RTSORA_LINKLINE); \
	$(CHMOD) $(EXE_PROT) $@

# Exiting link.mk
