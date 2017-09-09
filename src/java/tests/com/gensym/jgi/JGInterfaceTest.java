package com.gensym.jgi;

import com.gensym.classes.Item;
import com.gensym.jgi.download.DefaultStubFactory;
import com.gensym.jgi.download.G2StubFactory;
import com.gensym.util.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.ArgumentCaptor;
import org.mockito.Mockito;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.lang.reflect.Field;
import java.util.Hashtable;

import static com.gensym.jgi.JGInterface.*;
import static org.junit.Assert.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest(GsiLoopThread.class)
public class JGInterfaceTest {

    private JGInterface jgInterface;
    private GsiLoopThread gsiLoopThread;
    private boolean isTaskHandlerStarted;

    @Before
    public void setUp() throws Exception { jgInterface = getJgInterfaceObj(); }

    @After
    public void tearDown() throws Exception { jgInterface = null; gsiLoopThread = null; resetStaticJGInterfaceFields(); }

    private JGInterface getJgInterfaceObj() throws Exception {

        isTaskHandlerStarted = false;
        String[] cmdline = new String[]
                {
                        LISTENER_PORT_OPTION,
                        GSI_LISTENER_PORT_OPTION,
                        GSI_TCPIP_EXACT_OPTION,
                        GSI_SECURE_OPTION,
                        GSI_CERT_OPTION,
                        GSI_NO_LISTENER_PORT_OPTION,
                        DEBUG_GATEWAY_SWITCH_OPTION
                };

        gsiLoopThread = PowerMockito.mock(GsiLoopThread.class);

        setPrivateStaticField("isInitialized", true);
        JGInterface.gsiLoopThread = gsiLoopThread;
        JGInterface.gsiLoopThreadPriority = Thread.NORM_PRIORITY;

        return JGInterface.getJGInterface(cmdline);
    }

    private void resetStaticJGInterfaceFields() throws Exception {

        setPrivateStaticField("stubFactorySet", false);
        setPrivateStaticField("gsiRunning", false);
        setPrivateStaticField("isInitialized", false);
        setPrivateStaticField("G2ConnectionDispatchDataServiceMethod", null);
        setPrivateStaticField("G2ConnectionDispatchMethod", null);
        setPrivateStaticField("g2connection_handler_factory", null);
        setPrivateStaticField("g2connection_interface_fullname", "com.gensym.jgi.G2Connection");
        setPrivateStaticField("g2connection_interface", null);
        setPrivateStaticField("jgi_interface", null);
        setPrivateStaticField("localRPCTable", new Hashtable());
        setPrivateStaticField("g2_connections_object_ids", new Hashtable());
        setPrivateStaticField("g2_connections", new Hashtable());
        setPrivateStaticField("methodDispatchHandler", null);

        JGInterface.gsiLoopThread = null;
        JGInterface.gsiLoopThreadPriority = Thread.NORM_PRIORITY;
        JGInterface.currentFactory = null;
        JGInterface.methodDispatcher = new Dispatcher();
        JGInterface.G2MethodExecutionsQueues = new Hashtable();
    }

    private static void setPrivateStaticField(String fieldName, Object newValue) throws Exception {

        Field field = JGInterface.class.getDeclaredField(fieldName);
        field.setAccessible(true);
        field.set(null, newValue);
    }

    @Test
    public void test_startupGSI_nullGsiLoopThread_setGsiLoopThredAndSetsPriority() {

        // Arrange
        boolean option_debug = true;
        String[] args = new String[]{};

        JGInterface.gsiLoopThread = null;
        JGInterface.gsiLoopThreadPriority = Thread.MIN_PRIORITY;

        // Act
        jgInterface.startupGSI(args, option_debug);

        // Assert
        assertNotNull(JGInterface.gsiLoopThread);
        assertEquals(Thread.MIN_PRIORITY, JGInterface.gsiLoopThread.getPriority());
    }

    @Test
    public void test_setGSILoopThreadPriority_maxPriority_setsGsiLoopThreadPriority() {

        // Arrange
        int priority = Thread.MAX_PRIORITY;

        // Act
        JGInterface.setGSILoopThreadPriority(priority);

        // Assert
        assertEquals(priority, JGInterface.gsiLoopThreadPriority);
    }

    @Test (expected = IllegalArgumentException.class)
    public void test_setGSILoopThreadPriority_priorityNotInRange_throwsIllegalArgumentException() {

        // Arrange
        int priority = Thread.MAX_PRIORITY + 1;

        // Act
        JGInterface.setGSILoopThreadPriority(priority);
    }

    @Test
    public void test_startup_onCall_setTrueGsiRunning() {

        // Act
        jgInterface.startup();

        // Assert
        Mockito.verify(gsiLoopThread).enableRunLoop();
    }

    @Test
    public void test_deregisterContextObject_onCall_removesG2ConnectionReferences() throws Exception {

        // Assert
        G2Gateway connection = new G2Gateway();

        Hashtable g2_connections = new Hashtable();
        g2_connections.put("Key1", connection);
        g2_connections.put("Key2", "someValue2");

        Hashtable g2_connections_object_ids = new Hashtable();
        g2_connections_object_ids.put("Key3", connection);
        g2_connections_object_ids.put("Key4", "someValue4");

        Hashtable queues = new Hashtable();
        queues.put(connection, jgInterface.new MethodCallQueue());

        setPrivateStaticField("g2_connections", g2_connections);
        setPrivateStaticField("g2_connections_object_ids", g2_connections_object_ids);
        JGInterface.G2MethodExecutionsQueues = queues;

        // Act
        jgInterface.deregisterContextObject(connection);

        // Assert
        assertEquals(1, g2_connections.size());
        assertEquals(1, g2_connections_object_ids.size());
        assertEquals(0, queues.size());
        assertNull(g2_connections.get("Key1"));
        assertNull(g2_connections.get("Key3"));
    }

    @Test (expected = RuntimeException.class)
    public void test_handleRegisterIncomingConnection_nullG2connectionHandlerFactory_throwsRuntimeException()
            throws Exception {

        // Arrange
        int context = 99;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";

        setPrivateStaticField("g2connection_handler_factory", null);

        // Act
        jgInterface.handleRegisterIncomingConnection(context, remote_process_string, context_object_id);
    }

    @Test (expected = RuntimeException.class)
    public void test_handleRegisterIncomingConnection_nullG2Connection_throwsRuntimeException()
            throws Exception {

        // Arrange
        int context = 0;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";

        G2ConnectionHandlerFactory fac = new G2ConnectionHandlerFactory() {
            @Override
            public G2Connection createG2Connection(String connection_data) {
                return null;
            }
        };

        setPrivateStaticField("g2connection_handler_factory", null);
        jgInterface.setConnectionHandlerFactory(fac);

        // Act
        jgInterface.handleRegisterIncomingConnection(context, remote_process_string, context_object_id);
    }

    @Test
    public void test_handleRegisterIncomingConnection_notNullG2Connection_setG2ConnectionToLive()
            throws Exception {

        // Arrange
        int context = 0;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";
        final G2Gateway g2Gateway = new G2Gateway();
        G2ConnectionInfo info = new G2ConnectionInfo();
        g2Gateway.setConnectionInfo(info);
        G2Gateway._nativeInterface = PowerMockito.mock(JGInterface.class);;

        G2ConnectionHandlerFactory fac = new G2ConnectionHandlerFactory() {
            @Override
            public G2Connection createG2Connection(String connection_data) {
                return g2Gateway;
            }
        };

        setPrivateStaticField("g2connection_handler_factory", null);
        jgInterface.setConnectionHandlerFactory(fac);

        // Act
        jgInterface.handleRegisterIncomingConnection(context, remote_process_string, context_object_id);

        // Assert
        assertTrue(g2Gateway.isAlive());
        assertNotNull(g2Gateway.getClassManager());
    }

    @Test
    public void test_G2InitializeConnection_onCall_enqueueWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context = 0;
        String remote_process_string = "remote_process_string";
        G2Gateway connection = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor.capture());

        // Act
        jgInterface.G2InitializeConnection(connection, context, remote_process_string);

        // Assert
        Work_dispatchG2ConnectionEvent work = argumentCaptor.getValue();
        assertEquals(connection, work.inner_connection);
        assertEquals(context, work.inner_context);
        assertEquals(G2ConnectionEvent.G2_CONNECTION_INITIALIZED, work.inner_event.getId());
        assertEquals(remote_process_string, work.inner_event.getMessage());
        assertEquals(connection, work.inner_event.getSource());
        assertFalse(work.inner_event.getState());
    }

    @Test
    public void test_registerIncomingConnection_onCall_verifyWorkIncomingConnectionToGsiLoopThread()
            throws Exception {

        // Arrange
        int context = 0;
        String remote_process_string = "remote_process_string";
        String context_object_id = "contextObjectId";

        ArgumentCaptor<Work_registerIncomingConnection> argumentCaptor
                = ArgumentCaptor.forClass(Work_registerIncomingConnection.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor.capture());

        // Act
        jgInterface.registerIncomingConnection(context, remote_process_string, context_object_id);

        // Assert
        Work_registerIncomingConnection work = argumentCaptor.getValue();
        assertEquals(remote_process_string, work.inner_process_string);
        assertEquals(context, work.inner_context);
        assertEquals(context_object_id, work.inner_object_id);
    }

    @Test
    public void test_dispatchG2ConnectionEvent_onCall_startsTaskHandler()
            throws Exception {

        // Arrange
        int context_num = 0;
        G2Gateway connection = new G2Gateway();
        G2ConnectionEvent event = new G2ConnectionEvent(connection,
                G2ConnectionEvent.G2_CONNECTION_INITIALIZED,
                "message",
                false);

        TaskHandler methodDispatchHandler = new TaskHandler() {
            @Override
            public boolean start(Runnable task, Object owner, boolean runInQueuedThreadRequest) {
                isTaskHandlerStarted = true;
                return false;
            }
        };

        setPrivateStaticField("methodDispatchHandler", methodDispatchHandler);

        // Act
        jgInterface.dispatchG2ConnectionEvent(connection, context_num, event);

        // Assert
        assertTrue(isTaskHandlerStarted);
    }

    @Test
    public void test_G2InitializeConnectionAbort_onCall_returnsSetG2Connection()
            throws Exception {

        // Arrange
        String error_txt = "error_txt";
        String context_object_id = "context_object_id";
        G2Gateway connection = new G2Gateway();
        Hashtable g2_connections_object_ids = new Hashtable();
        g2_connections_object_ids.put(context_object_id, connection);

        TaskHandler methodDispatchHandler = new TaskHandler() {
            @Override
            public boolean start(Runnable task, Object owner, boolean runInQueuedThreadRequest) {
                isTaskHandlerStarted = true;
                return false;
            }
        };

        setPrivateStaticField("methodDispatchHandler", methodDispatchHandler);
        setPrivateStaticField("g2_connections_object_ids", g2_connections_object_ids);

        // Act
        G2Connection actualResult = jgInterface.G2InitializeConnectionAbort(error_txt, context_object_id);

        // Assert
        assertTrue(isTaskHandlerStarted);
        assertEquals(connection, actualResult);
    }

    @Test
    public void test_G2ConnectionClosed_onCall_enqueueWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context = 0;
        G2Gateway connection = new G2Gateway();
        G2Access nativeCxn = Mockito.mock(G2Access.class);
        G2StubFactory[] factoryTable = new G2StubFactory[]{ new DefaultStubFactory(nativeCxn) };

        ArgumentCaptor<Work_dispatchG2ConnectionClose> argumentCaptor
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionClose.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor.capture());

        setPrivateStaticField("factoryTable", factoryTable);

        // Act
        jgInterface.G2ConnectionClosed(connection, context);

        // Assert
        Work_dispatchG2ConnectionClose work = argumentCaptor.getValue();
        assertEquals(connection, work.inner_connection);
        assertEquals(context, work.inner_context);
        assertEquals("", work.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_CONNECTION_CLOSED, work.inner_event.getId());
        assertFalse(work.inner_event.getState());
    }

    @Test
    public void test_handleG2ConnectionClosed_onCall_startsTaskHandler()
            throws Exception {

        // Arrange
        int context = 0;
        G2Gateway connection = new G2Gateway();
        G2ConnectionEvent event = new G2ConnectionEvent(connection,
                G2ConnectionEvent.G2_CONNECTION_INITIALIZED,
                "message",
                false);
        G2Access nativeCxn = Mockito.mock(G2Access.class);
        G2StubFactory currentFactory = new DefaultStubFactory(nativeCxn);
        JGInterface.currentFactory = currentFactory;
        G2StubFactory[] factoryTable = new G2StubFactory[]{ currentFactory };
        StubResolver[] stubResolverTable = new StubResolver[]{ new StubResolver(Mockito.mock(G2StubFactory.class)) };

        setPrivateStaticField("factoryTable", factoryTable);
        setPrivateStaticField("stubResolverTable", stubResolverTable);

        // Act
        jgInterface.handleG2ConnectionClosed(connection, context, event);

        // Assert
        assertNull(JGInterface.currentFactory);
        assertNull(jgInterface.getStubFactory(context));
        assertNull(stubResolverTable[0]);
    }

    @Test
    public void test_G2isPaused_onCall_enqueueG2IsPausedWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context0 = 0;
        G2Gateway connection0 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor0
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor0.capture());

        // Act
        jgInterface.G2isPaused(connection0, context0);

        // Assert
        Work_dispatchG2ConnectionEvent work0 = argumentCaptor0.getValue();
        assertEquals(connection0, work0.inner_connection);
        assertEquals(context0, work0.inner_context);
        assertNull(work0.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_IS_PAUSED, work0.inner_event.getId());
        assertFalse(work0.inner_event.getState());
    }

    @Test
    public void test_G2isResumed_onCall_enqueueG2IsResumedWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context1 = 1;
        G2Gateway connection1 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor1
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor1.capture());

        // Act
        jgInterface.G2isResumed(connection1, context1);

        // Assert
        Work_dispatchG2ConnectionEvent work1 = argumentCaptor1.getValue();
        assertEquals(connection1, work1.inner_connection);
        assertEquals(context1, work1.inner_context);
        assertNull(work1.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_IS_RESUMED, work1.inner_event.getId());
        assertFalse(work1.inner_event.getState());
    }

    @Test
    public void test_G2isReset_onCall_enqueueG2IsResetWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context2 = 2;
        G2Gateway connection2 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor2
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor2.capture());

        // Act
        jgInterface.G2isReset(connection2, context2);

        // Assert
        Work_dispatchG2ConnectionEvent work2 = argumentCaptor2.getValue();
        assertEquals(connection2, work2.inner_connection);
        assertEquals(context2, work2.inner_context);
        assertNull(work2.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_IS_RESET, work2.inner_event.getId());
        assertFalse(work2.inner_event.getState());
    }

    @Test
    public void test_G2isStarted_onCall_enqueueG2IsStartedWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context3 = 3;
        G2Gateway connection3 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor3
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor3.capture());

        // Act
        jgInterface.G2isStarted(connection3, context3);

        // Assert
        Work_dispatchG2ConnectionEvent work3 = argumentCaptor3.getValue();
        assertEquals(connection3, work3.inner_connection);
        assertEquals(context3, work3.inner_context);
        assertNull(work3.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_IS_STARTED, work3.inner_event.getId());
        assertFalse(work3.inner_event.getState());
    }

    @Test
    public void test_receiveMessage_onCall_enqueueG2MsgRecievedWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context4 = 4;
        String message4 = "SetMessage4";
        G2Gateway connection4 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor4
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor4.capture());

        // Act
        jgInterface.receiveMessage(connection4, context4, message4);

        // Assert
        Work_dispatchG2ConnectionEvent work4 = argumentCaptor4.getValue();
        assertEquals(connection4, work4.inner_connection);
        assertEquals(context4, work4.inner_context);
        assertEquals(message4, work4.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_MESSAGE_RECEIVED, work4.inner_event.getId());
        assertFalse(work4.inner_event.getState());
    }

    @Test
    public void test_writeCallback_onCall_enqueueG2WriteBlockageWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context5 = 5;
        boolean state5 = true;
        G2Gateway connection5 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor5
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor5.capture());

        // Act
        jgInterface.writeCallback(connection5, context5, state5);

        // Assert
        Work_dispatchG2ConnectionEvent work5 = argumentCaptor5.getValue();
        assertEquals(connection5, work5.inner_connection);
        assertEquals(context5, work5.inner_context);
        assertNull(work5.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_WRITE_BLOCKAGE, work5.inner_event.getId());
        assertTrue(work5.inner_event.getState());
    }

    @Test
    public void test_readCallback_onCall_enqueueG2ReadBlockageWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context6 = 6;
        boolean state6 = true;
        G2Gateway connection6 = new G2Gateway();

        ArgumentCaptor<Work_dispatchG2ConnectionEvent> argumentCaptor6
                = ArgumentCaptor.forClass(Work_dispatchG2ConnectionEvent.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor6.capture());

        // Act
        jgInterface.readCallback(connection6, context6, state6);

        // Assert
        Work_dispatchG2ConnectionEvent work6 = argumentCaptor6.getValue();
        assertEquals(connection6, work6.inner_connection);
        assertEquals(context6, work6.inner_context);
        assertNull(work6.inner_event.getMessage());
        assertEquals(G2ConnectionEvent.G2_READ_BLOCKAGE, work6.inner_event.getId());
        assertTrue(work6.inner_event.getState());
    }

    @Test
    public void test_getData_onCall_enqueueG2ReadBlockageWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context = 0;
        boolean incompleteStubConversion = true;
        Item[] items = new Item[]{};
        G2Gateway connection = new G2Gateway();

        // Act
        jgInterface.getData(connection, context, items, incompleteStubConversion);

        // Assert
        assertEquals(1, JGInterface.G2MethodExecutionsQueues.size());
        assertNotNull(JGInterface.G2MethodExecutionsQueues.get(connection));
        assertTrue(JGInterface.G2MethodExecutionsQueues.get(connection) instanceof JGInterface.MethodCallQueue);
    }

    @Test (expected = G2RemoteRPCNotPredeclaredException.class)
    public void test_callRPC_nullG2ProcedureHandle_throwsG2RemoteRPCNotPredeclaredException()
            throws Exception {

        // Arrange
        int context = 0;
        int timeout = 1;
        Object g2_procedure_handle = null;
        Item[] items = new Item[]{ };

        // Act
        jgInterface.callRPC(g2_procedure_handle, items, timeout, context);
    }

    @Test (expected = G2RemoteRPCNotPredeclaredException.class)
    public void test_callRPCAsynchronous_nullG2ProcedureHandle_throwsG2RemoteRPCNotPredeclaredException()
            throws Exception {

        // Arrange
        int context = 0;
        Object g2_procedure_handle = null;
        Item[] items = new Item[]{ };

        // Act
        jgInterface.callRPCAsynchronous(g2_procedure_handle, items, context);
    }

    @Test
    public void test_callRPCAsynchronous_notNullG2ProcedureHandle_enqueueCallRPCNativeWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context = 0;
        Object g2_procedure_handle = new Long(1);
        Item[] items = new Item[]{ };

        ArgumentCaptor<Work_callRPCNative> argumentCaptor
                = ArgumentCaptor.forClass(Work_callRPCNative.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor.capture());

        // Act
        jgInterface.callRPCAsynchronous(g2_procedure_handle, items, context);

        // Assert
        Work_callRPCNative work = argumentCaptor.getValue();
        assertEquals((long)1, work.inner_function_handle);
        assertEquals(context, work.inner_context);
        assertArrayEquals(items, work.inner_arguments);
        assertFalse(work.inner_start_proc);
        assertNull(work.inner_user_data);
    }

    @Test (expected = G2RemoteRPCNotPredeclaredException.class)
    public void test_startRPC_nullG2ProcedureHandle_throwsG2RemoteRPCNotPredeclaredException()
            throws Exception {

        // Arrange
        int context = 0;
        Object g2_procedure_handle = null;
        Item[] items = new Item[]{ };

        // Act
        jgInterface.startRPC(g2_procedure_handle, items, context);
    }

    @Test
    public void test_startRPC_notNullG2ProcedureHandle_enqueueCallRPCNativeWorkToGsiLoopThread()
            throws Exception {

        // Arrange
        int context1 = 0;
        Object g2_procedure_handle1 = new Long(1);
        Item[] items1 = new Item[]{ };

        ArgumentCaptor<Work_callRPCNative> argumentCaptor1
                = ArgumentCaptor.forClass(Work_callRPCNative.class);

        Mockito.doNothing().when(gsiLoopThread).enqueue(argumentCaptor1.capture());

        // Act
        jgInterface.startRPC(g2_procedure_handle1, items1, context1);

        // Assert
        Work_callRPCNative work1 = argumentCaptor1.getValue();
        assertEquals((long)1, work1.inner_function_handle);
        assertEquals(context1, work1.inner_context);
        assertArrayEquals(items1, work1.inner_arguments);
        assertTrue(work1.inner_start_proc);
        assertNull(work1.inner_user_data);
    }
}
