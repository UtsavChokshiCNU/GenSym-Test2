LIBOBJS = ./c/sbn.o ./c/sbn_config.o ./c/sbn_log.o
BRIDGEOBJS = ./c/g2sbn.o ./c/callbacks.o
LIBTARGET = libsbn.a

CFLAGS = -I./c/ -I../gsi/c/
LDFLAGS = -L../../dst/gsi/opt/ -L../../dst/rtl/opt -L../../dst/ext/opt -L./

TESTSOURCE = ./tests/c/src/test_sbn.cpp
TESTOBJS = ./tests/c/src/test_sbn.o
TESTINCLUDE = -I./tests/c/include
TESTLIBPATH = -L./
TESTLIB = -lsbn
TESTTARGET = sbn_tests

debug: CFLAGS += -g
debug: g2sbn $(TESTTARGET)

release: CFLAGS += -DNDEBUG -O2
release: g2sbn $(TESTTARGET)

g2sbn: LDLIBS = -lsbn -lgsi -lrtl -ltcp -ldl -lm
g2sbn: $(BRIDGEOBJS) $(LIBTARGET)
	$(CC) $(LDFLAGS) $(BRIDGEOBJS) $(LDLIBS) -o $@

$(LIBTARGET): $(LIBOBJS)
	$(AR) $(ARFLAGS) $@ $(LIBOBJS)

$(TESTTARGET): $(TESTOBJS) $(LIBTARGET)
	${CXX} -o $@ $^ $(TESTLIBPATH) $(TESTLIB) $(LDFLAGS)

$(TESTOBJS): $(TESTSOURCE)
	${CXX} -o $@ $(TESTINCLUDE) $(CFLAGS) -c $<

./c/sbn.o: ./c/sbn.h
./c/sbn_config.o: ./c/sbn.h
./c/sbn_log.o: ./c/sbn.h
./c/callbacks.o: ./c/sbn.h ./c/g2sbn.h
./c/g2sbn.o: ./c/sbn.h ./c/g2sbn.h
./tests/c/src/test_sbn.o: ./c/sbn.h 

clean:
	rm -fr ./c/*.o
	rm -fr *.a
	rm -fr g2sbn
	rm -fr $(TESTTARGET)
