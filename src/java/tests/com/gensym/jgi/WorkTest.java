package com.gensym.jgi;

import com.gensym.classes.Item;
import com.gensym.message.Trace;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import static org.powermock.api.mockito.PowerMockito.mockStatic;

@RunWith(PowerMockRunner.class)
@PrepareForTest({GsiLoopThread.class})
public class WorkTest {

    private GsiLoopThread gsiLoopThread;
    private JGInterface jgInterface;

    @Before
    public void setUp() { initializeToVerifyStaticMethod(); }

    @After
    public void tearDown() {
        gsiLoopThread = null;
        jgInterface = null;
    }

    private void initializeToVerifyStaticMethod() {

        mockStatic(GsiLoopThread.class);

        gsiLoopThread = new GsiLoopThread(Mockito.mock(JGInterface.class), new String[]{ }, true);
        GsiLoopThread.invocation = gsiLoopThread;
    }

    private void initializeToVerifyNonStaticMethod() {

        gsiLoopThread = PowerMockito.mock(GsiLoopThread.class);
        jgInterface = PowerMockito.mock(JGInterface.class);

        GsiLoopThread.invocation = gsiLoopThread;
        GsiLoopThread.intrface = jgInterface;
    }

    @Test
    public void test_workSetFullDebug_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        boolean state = true;
        Work_setFulldebug work = new Work_setFulldebug(state);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.setFulldebug (state);
    }

    @Test
    public void test_workStartCollectingRPCStats0_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Work_startCollectingRPCStats0 work = new Work_startCollectingRPCStats0();

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.startCollectingRPCStats0();
    }

    @Test
    public void test_workStopCollectingRPCStats0_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Work_stopCollectingRPCStats0 work = new Work_stopCollectingRPCStats0();

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.stopCollectingRPCStats0();
    }

    @Test
    public void test_workClearProfilingData0_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Work_clearProfilingData0 work = new Work_clearProfilingData0();

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.clearProfilingData0();
    }

    @Test
    public void test_workWriteRPCStats0_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        String fileName = "SetFileName";
        Work_writeRPCStats0 work = new Work_writeRPCStats0(fileName);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.writeRPCStats0(fileName);
    }

    @Test
    public void test_workCheckHandleType_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        int handle = 1;
        Work_checkHandleType workWithContext = new Work_checkHandleType(context, handle);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).checkHandleType(context, handle);
    }

    @Test
    public void test_workCloseConnectionNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        Work_closeConnectionNative workWithContext = new Work_closeConnectionNative(context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).closeConnectionNative(context);
    }

    @Test
    public void test_workDeclareLocalRPCNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Symbol g2_RPD_name = Symbol.intern("TestName");
        boolean connectionSpecific = true;
        Work_declareLocalRPCNative work = new Work_declareLocalRPCNative(g2_RPD_name, connectionSpecific);

        initializeToVerifyNonStaticMethod();

        // Act
        work.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).declareLocalRPCNative(g2_RPD_name, connectionSpecific);
    }

    @Test
    public void test_workInitializeStatBuffers0_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int numCalls = 1;
        Work_initializeStatBuffers0 work = new Work_initializeStatBuffers0(numCalls);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.initializeStatBuffers0(numCalls);
    }

    @Test
    public void test_workReportLogBookErrorMessage_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Symbol error_symbol = Symbol.intern("TestName");
        String error_message = "TestErrorMessage";
        int context = 1;
        Work_reportLogBookErrorMessage workWithContext = new Work_reportLogBookErrorMessage(error_symbol, error_message, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).reportLogBookErrorMessage(error_symbol, error_message, context);
    }

    @Test
    public void test_workReturnAttrs_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Item variable = Mockito.mock(Item.class);
        Structure attributesArray = new Structure();
        Object values = new Object();
        int statusValues = 1;
        int context = 2;
        Work_returnAttrs workWithContext = new Work_returnAttrs(variable, attributesArray, values, statusValues, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).returnAttrs(variable, attributesArray, values, statusValues, context);
    }

    @Test
    public void test_workReturnMessage_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        String message = "TestMessage";
        int context = 1;
        Work_returnMessage workWithContext = new Work_returnMessage(message, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).returnMessage(message, context);
    }

    @Test
    public void test_workSetGSIContextLimit_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int limit = 1;
        Work_setGSIContextLimit work = new Work_setGSIContextLimit(limit);

        initializeToVerifyNonStaticMethod();

        // Act
        work.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).setGSIContextLimit(limit);
    }

    @Test
    public void test_workNativeRegisterContextObject_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        String remote_process_string = "TestMessage";
        G2Connection context_object = Mockito.mock(G2Connection.class);
        Work_nativeRegisterContextObject workWithContext = new Work_nativeRegisterContextObject(context_object, context, remote_process_string);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).nativeRegisterContextObject(context_object, context, remote_process_string);
    }

    @Test
    public void test_workReturnRPCValue_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        long call_index = new Long(1);
        Object result = new Object();
        boolean force_return_value = true;
        boolean error = true;
        Symbol error_symbol = Symbol.intern("ErrorSymbolTest");
        String error_text = "TestErrorText";
        int context = 2;
        Work_returnRPCValue workWithContext = new Work_returnRPCValue(call_index, result, force_return_value, error, error_symbol, error_text, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).returnRPCValue(call_index, result, force_return_value, error, error_symbol, error_text, context);
    }

    @Test
    public void test_workReturnValues_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Object[] variables = new Object[]{ new Object() };
        Structure[] attributesArray = new Structure[]{ new Structure() };
        Object[] values = new Object[]{ new Object() };
        int[] statusValues = new int[]{ 1 };
        int context = 2;
        Work_returnValues workWithContext = new Work_returnValues(variables, attributesArray, values, statusValues, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).returnValues(variables, attributesArray, values, statusValues, context);
    }

    @Test
    public void test_workSetFundebug_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        boolean state = true;
        Work_setFundebug work = new Work_setFundebug(state);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.setFundebug (state);
    }

    @Test
    public void test_workSetConvdebug_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        boolean state = true;
        Work_setConvdebug work = new Work_setConvdebug(state);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.setConvdebug(state);
    }

    @Test
    public void test_workInterfaceOutput_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        boolean state = true;
        Work_setInterfaceOutput work = new Work_setInterfaceOutput(state);

        // Act
        work.invoke();

        // Assert
        PowerMockito.verifyStatic();
        GsiLoopThread.setInterfaceOutput(state);
    }

    @Test
    public void test_workStartInterface_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Object intrface = new Object();
        String[] command = new String[]{ "testCommand" };
        Work_startInterface work = new Work_startInterface(intrface, command);

        initializeToVerifyNonStaticMethod();

        // Act
        work.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).startInterface(intrface, command);
    }

    @Test
    public void test_workSetRPCRemoteReturnValueKindNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        long g2_function_handle = new Long(1);
        int return_value_index = 2;
        int return_value_type = 3;
        int context = 4;
        Work_setRPCRemoteReturnValueKindNative workWithContext = new Work_setRPCRemoteReturnValueKindNative(g2_function_handle, return_value_index, return_value_type, context);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).setRPCRemoteReturnValueKindNative(g2_function_handle, return_value_index, return_value_type, context);
    }

    @Test
    public void test_workSetRPCRemoteReturnValueKindNative_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        long g2_function_handle = new Long(1);
        int return_value_index = 2;
        int return_value_type = 3;
        int context = 4;
        Work_setRPCRemoteReturnValueKindNative workWithContext = new Work_setRPCRemoteReturnValueKindNative(g2_function_handle, return_value_index, return_value_type, context);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_setRPCRemoteReturnValueKindNative.class.getName() + "@"));
        assertTrue(actualResult.endsWith("[1(2,3)]"));
    }

    @Test
    public void test_workSetReceiveRegistrations_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        boolean status = true;
        Work_setReceiveRegistrations workWithContext = new Work_setReceiveRegistrations(context, status);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).setReceiveRegistrations(context, status);
    }

    @Test
    public void test_workGetCurrentContext_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Return_int inner_synchronizer = new Return_int();
        Work_getCurrentContext work = new Work_getCurrentContext(inner_synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.getCurrentContext()).thenReturn(99);

        // Act
        work.invoke();

        // Assert
        assertTrue(inner_synchronizer.isValueSet());
        assertEquals(99, inner_synchronizer.value);
        Mockito.verify(gsiLoopThread).getCurrentContext();
    }

    @Test
    public void test_workDeclareRemoteRPCNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int remote_arg_count = 1;
        int return_arg_count = 2;
        int context = 3;
        String g2_procedure_name = "g2_procedure_name";
        String java_receiver_method_name = "java_receiver_method_name";
        Return_long synchronizer = new Return_long();
        Work_declareRemoteRPCNative workWithContext = new Work_declareRemoteRPCNative(g2_procedure_name, remote_arg_count, return_arg_count, java_receiver_method_name, context, synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.declareRemoteRPCNative(g2_procedure_name, remote_arg_count, return_arg_count, java_receiver_method_name, context)).thenReturn(new Long(99));

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).declareRemoteRPCNative(g2_procedure_name, remote_arg_count, return_arg_count, java_receiver_method_name, context);
        assertEquals((long)(99), synchronizer.value);
    }

    @Test
    public void test_workDeclareRemoteRPCNative_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        int remote_arg_count = 1;
        int return_arg_count = 2;
        int context = 3;
        String g2_procedure_name = "g2_procedure_name";
        String java_receiver_method_name = "java_receiver_method_name";
        Return_long synchronizer = new Return_long();
        Work_declareRemoteRPCNative workWithContext = new Work_declareRemoteRPCNative(g2_procedure_name, remote_arg_count, return_arg_count, java_receiver_method_name, context, synchronizer);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_declareRemoteRPCNative.class.getName() + "@"));
        assertTrue(actualResult.endsWith("[" + g2_procedure_name + "(1,2)]"));
    }

    @Test
    public void test_workGetListenerSocket_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        Return_int synchronizer = new Return_int();
        Work_getListenerSocket work = new Work_getListenerSocket(synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.getListenerSocket()).thenReturn(99);

        // Act
        work.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).getListenerSocket();
        assertEquals(99, synchronizer.value);
    }

    @Test
    public void test_workCallRPCNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 2;
        long function_handle = new Long(1);
        boolean start_proc = true;
        Object arguments[] = new Object[] { new Object() };
        Object user_data = new Object();
        Work_callRPCNative work = new Work_callRPCNative(function_handle,  arguments, start_proc, user_data, context);

        initializeToVerifyNonStaticMethod();

        // Act
        work.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).callRPCNative(function_handle,  arguments, start_proc, user_data, context);
    }

    @Test
    public void test_workCallRPCNative_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        int context = 2;
        long function_handle = new Long(1);
        boolean start_proc = true;
        Object arguments[] = new Object[] { new Object() };
        Object user_data = "testUserData";
        Work_callRPCNative work = new Work_callRPCNative(function_handle,  arguments, start_proc, user_data, context);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = work.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_callRPCNative.class.getName() + "@"));
        assertTrue(actualResult.endsWith("[1, " + user_data + "]"));
    }

    @Test
    public void test_workCheckForHandleOK_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        int handle = 2;
        Return_String synchronizer = new Return_String();
        Work_checkForHandleOK workWithContext = new Work_checkForHandleOK(context, handle, synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.checkForHandleOK(context, handle)).thenReturn("testValue");

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).checkForHandleOK(context, handle);
        assertEquals("testValue", synchronizer.getValue());
    }

    @Test
    public void test_workGetRemoteHostNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        Return_String synchronizer = new Return_String();
        Work_getRemoteHostNative workWithContext = new Work_getRemoteHostNative(context, synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.getRemoteHostNative(context)).thenReturn("testValue");

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).getRemoteHostNative(context);
        assertEquals("testValue", synchronizer.getValue());
    }

    @Test
    public void test_workInitiateConnectionNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        boolean secure = true;
        boolean keep_connection = true;
        String host = "host";
        String port = "port";
        String rpis = "rpis";
        String network = "network";
        String class_name = "class_name";
        String interface_name = "interface_name";
        String callback_identification = "callback_identification";
        Return_boolean synchronizer = new Return_boolean();
        Work_initiateConnectionNative workWithContext = new Work_initiateConnectionNative(interface_name, class_name
                , keep_connection, network, host, port, rpis, callback_identification, secure, synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.initiateConnectionNative(interface_name, class_name, keep_connection, network
                , host, port, rpis, callback_identification, secure)).thenReturn(true);

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(gsiLoopThread).initiateConnectionNative(interface_name, class_name, keep_connection, network
                , host, port, rpis, callback_identification, secure);
        assertTrue(synchronizer.getValue());
    }

    @Test
    public void test_workInitiateConnectionNative_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        boolean secure = true;
        boolean keep_connection = true;
        String host = "host";
        String port = "port";
        String rpis = "rpis";
        String network = "network";
        String class_name = "class_name";
        String interface_name = "interface_name";
        String callback_identification = "callback_identification";
        Return_boolean synchronizer = new Return_boolean();
        Work_initiateConnectionNative workWithContext = new Work_initiateConnectionNative(interface_name, class_name
                , keep_connection, network, host, port, rpis, callback_identification, secure, synchronizer);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_initiateConnectionNative.class.getName() + "@"));
        assertTrue(actualResult.endsWith("[" + callback_identification + "]"));
    }

    @Test
    public void test_workGetRemotePortNative_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        Return_int inner_synchronizer = new Return_int();
        Work_getRemotePortNative workWithContext = new Work_getRemotePortNative(context, inner_synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.getRemotePortNative(context)).thenReturn(99);

        // Act
        workWithContext.invoke();

        // Assert
        assertTrue(inner_synchronizer.isValueSet());
        assertEquals(99, inner_synchronizer.value);
        Mockito.verify(gsiLoopThread).getRemotePortNative(context);
    }

    @Test
    public void test_workGetRemoteSecureContext_onInvokeCall_VerifiesGsiLoopThreadMethodCall() throws Exception {

        // Arrange
        int context = 1;
        Return_int inner_synchronizer = new Return_int();
        Work_getRemoteSecureContext workWithContext = new Work_getRemoteSecureContext(context, inner_synchronizer);

        initializeToVerifyNonStaticMethod();

        Mockito.when(gsiLoopThread.getRemoteSecureContext(context)).thenReturn(99);

        // Act
        workWithContext.invoke();

        // Assert
        assertTrue(inner_synchronizer.isValueSet());
        assertEquals(99, inner_synchronizer.value);
        Mockito.verify(gsiLoopThread).getRemoteSecureContext(context);
    }

    @Test
    public void test_workCommunicationError_onInvokeCall_VerifiesJGInterfaceMethodCall() throws Exception {

        // Arrange
        int context = 1;
        int error_code = 2;
        String error_msg = "error_msg";
        String initiateConnectionId = "initiateConnectionId";
        Work_communicationError workWithContext
                = new Work_communicationError(context, error_code, error_msg, initiateConnectionId);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(jgInterface).handleCommunicationError(context, error_code, error_msg, initiateConnectionId);
    }

    @Test
    public void test_workDispatchG2ConnectionClose_onInvokeCall_VerifiesJGInterfaceMethodCall() throws Exception {

        // Arrange
        int context = 1;
        G2Connection connection = Mockito.mock(G2Connection.class);
        G2ConnectionEvent event = new G2ConnectionEvent(new G2Gateway(), 99);
        Work_dispatchG2ConnectionClose workWithContext
                = new Work_dispatchG2ConnectionClose(connection, context, event);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(jgInterface).handleG2ConnectionClosed(connection, context, event);
    }

    @Test
    public void test_workDispatchG2ConnectionClose_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        int context = 1;
        G2Connection connection = Mockito.mock(G2Connection.class);
        G2ConnectionEvent event = new G2ConnectionEvent(new G2Gateway(), 99);
        Work_dispatchG2ConnectionClose workWithContext
                = new Work_dispatchG2ConnectionClose(connection, context, event);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_dispatchG2ConnectionClose.class.getName() + "@"));
        assertTrue(actualResult.contains("[1," + G2ConnectionEvent.class.getName() + "[source=" + G2Gateway.class.getName() + "@"));
        assertTrue(actualResult.contains(G2Connection.class.getName()));
    }

    @Test
    public void test_workDispatchG2ConnectionEvent_onInvokeCall_VerifiesJGInterfaceMethodCall() throws Exception {

        // Arrange
        int context = 1;
        G2Connection connection = Mockito.mock(G2Connection.class);
        G2ConnectionEvent event = new G2ConnectionEvent(new G2Gateway(), 99);
        Work_dispatchG2ConnectionEvent workWithContext
                = new Work_dispatchG2ConnectionEvent(connection, context, event);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        Mockito.verify(jgInterface).dispatchG2ConnectionEvent(connection, context, event);
    }

    @Test
    public void test_workDispatchG2ConnectionEvent_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        int context = 1;
        G2Connection connection = Mockito.mock(G2Connection.class);
        G2ConnectionEvent event = new G2ConnectionEvent(new G2Gateway(), 99);
        Work_dispatchG2ConnectionEvent workWithContext
                = new Work_dispatchG2ConnectionEvent(connection, context, event);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_dispatchG2ConnectionEvent.class.getName() + "@"));
        assertTrue(actualResult.contains("[1," + G2ConnectionEvent.class.getName() + "[source=" + G2Gateway.class.getName() + "@"));
        assertTrue(actualResult.contains(G2Connection.class.getName()));
    }

    @Test
    public void test_workRegisterIncomingConnection_onInvokeCall_VerifiesJGInterfaceMethodCall() throws Exception {

        // Arrange
        int context = 1;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";
        Work_registerIncomingConnection workWithContext
                = new Work_registerIncomingConnection(context, remote_process_string, context_object_id);

        initializeToVerifyNonStaticMethod();

        // Act
        workWithContext.invoke();

        // Assert
        assertEquals(context, workWithContext.getContext());
        Mockito.verify(jgInterface).handleRegisterIncomingConnection(context, remote_process_string, context_object_id);
    }

    @Test
    public void test_workRegisterIncomingConnection_setToRaiseException_TraceException() throws Exception {

        // Arrange
        int context = 1;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";
        Work_registerIncomingConnection workWithContext
                = new Work_registerIncomingConnection(context, remote_process_string, context_object_id);

        initializeToVerifyNonStaticMethod();

        PowerMockito.doThrow(new Exception()).when(jgInterface).handleRegisterIncomingConnection(context, remote_process_string, context_object_id);

        mockStatic(Trace.class);

        // Act
        workWithContext.invoke();

        // Assert
        PowerMockito.verifyStatic();
        Trace.exception(Matchers.any(Exception.class));
    }

    @Test
    public void test_workRegisterIncomingConnection_toStringCall_ReturnsWorkClassString() throws Exception {

        // Arrange
        int context = 1;
        String remote_process_string = "remote_process_string";
        String context_object_id = "context_object_id";
        Work_registerIncomingConnection workWithContext
                = new Work_registerIncomingConnection(context, remote_process_string, context_object_id);

        initializeToVerifyNonStaticMethod();

        // Act
        String actualResult = workWithContext.toString();

        // Assert
        assertTrue(actualResult.startsWith(Work_registerIncomingConnection.class.getName() + "@"));
        assertTrue(actualResult.endsWith("[" + context + "]"));
    }
}