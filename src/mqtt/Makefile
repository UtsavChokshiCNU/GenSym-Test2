BIN = ./bin
MQTTDIR = .
LIBSOURCE = $(MQTTDIR)/lib/src/mqttSocket.c $(MQTTDIR)/lib/src/mqttclient.c $(MQTTDIR)/lib/src/mqttDataTrace.c $(MQTTDIR)/lib/src/mqttSessionTrace.c $(MQTTDIR)/lib/src/mqttTraceHelper.c 
TESTSOURCE = $(MQTTDIR)/tests/src/test_mqttclient.cpp

LIBOBJS = $(BIN)/mqttSocket.o $(BIN)/mqttclient.o $(BIN)/mqttDataTrace.o $(BIN)/mqttSessionTrace.o $(BIN)/mqttTraceHelper.o 
TESTOBJS = $(BIN)/test_mqttclient.o

LIBINCLUDE = -I$(MQTTDIR)/lib/include
TESTINCLUDE = -I$(MQTTDIR)/tests/include

TESTLIBPATH = -L$(BIN)
TESTLIB = -lmqttclient

LIBTARGET = $(BIN)/libmqttclient.a
TESTTARGET = $(BIN)/mqttclient_tests.exe

CC_FLAGS = -Wimplicit -fPIC 

debug: CC_FLAGS += -g
debug: $(LIBTARGET) $(TESTTARGET)

release: CC_FLAGS += -DNDEBUG -O2
release: $(LIBTARGET) $(TESTTARGET)


$(LIBTARGET): $(LIBOBJS)
	ar rcs $@ $(LIBOBJS)

$(BIN)/mqttSocket.o: $(MQTTDIR)/lib/src/mqttSocket.c
	${CC} -c $(LIBINCLUDE) -o $(BIN)/mqttSocket.o $(MQTTDIR)/lib/src/mqttSocket.c $(CC_FLAGS)

$(BIN)/mqttclient.o: $(MQTTDIR)/lib/src/mqttclient.c
	${CC} -c $(LIBINCLUDE) -o $(BIN)/mqttclient.o $(MQTTDIR)/lib/src/mqttclient.c $(CC_FLAGS)

$(BIN)/mqttDataTrace.o: $(MQTTDIR)/lib/src/mqttDataTrace.c
	${CC} -c $(LIBINCLUDE) -o $(BIN)/mqttDataTrace.o $(MQTTDIR)/lib/src/mqttDataTrace.c $(CC_FLAGS)

$(BIN)/mqttSessionTrace.o: $(MQTTDIR)/lib/src/mqttSessionTrace.c
	${CC} -c $(LIBINCLUDE) -o $(BIN)/mqttSessionTrace.o $(MQTTDIR)/lib/src/mqttSessionTrace.c $(CC_FLAGS)

$(BIN)/mqttTraceHelper.o: $(MQTTDIR)/lib/src/mqttTraceHelper.c
	${CC} -c $(LIBINCLUDE) -o $(BIN)/mqttTraceHelper.o $(MQTTDIR)/lib/src/mqttTraceHelper.c $(CC_FLAGS)
	

$(TESTTARGET): $(TESTOBJS) $(LIBTARGET)  
	${CXX} -o $@ $^ $(TESTLIBPATH) $(TESTLIB)	

$(TESTOBJS): $(TESTSOURCE)
	${CXX} -o $@ $(TESTINCLUDE) $(LIBINCLUDE) -c $<

clean: 
	rm -fr $(BIN)/*

