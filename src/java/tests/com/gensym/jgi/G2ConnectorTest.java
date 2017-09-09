package com.gensym.jgi;

import com.gensym.classes.Item;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.awt.*;
import java.lang.reflect.Method;
import java.util.ArrayList;

import static com.gensym.helpers.ObjectsFactory.*;
import static org.junit.Assert.*;
import static org.mockito.Matchers.any;
import static org.powermock.api.mockito.PowerMockito.mock;

@RunWith(PowerMockRunner.class)
@PrepareForTest(G2Gateway.class)
public class G2ConnectorTest extends G2ConnectorTestHelper {
    @Before
    public void init() throws G2AccessException {
        this.sut = new G2Connector();

        this.connection = anyG2Gateway();
        this.connectionIsClosed = false;
        this.sut.setXn(this.connection);

        resetResponses();
    }

    @Test
    public void test_setBrokerURL_always_setsUrl() {
        // Arrange
        String url = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setBrokerURL(url);

        // Assert
        assertEquals(url, this.sut.getBrokerURL());
    }

    @Test
    public void test_setLogicalName_always_setsUrl() {
        // Arrange
        String logicalName = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setLogicalName(logicalName);

        // Assert
        assertEquals(logicalName, this.sut.getLogicalName());
    }

    @Test
    public void test_setHost_always_setsUrl() {
        // Arrange
        String host = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setHost(host);

        // Assert
        assertEquals(host, this.sut.getHost());
    }

    @Test
    public void test_setPort_always_setsUrl() {
        // Arrange
        String port = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setPort(port);

        // Assert
        assertEquals(port, this.sut.getPort());
    }

    @Test
    public void test_setConnectionClassName_always_setsUrl() {
        // Arrange
        String connectionClassName = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setConnectionClassName(connectionClassName);

        // Assert
        assertEquals(connectionClassName, this.sut.getConnectionClassName());
    }

    @Test
    public void test_setGsiInterfaceClassName_always_setsGsiInterfaceClassName() {
        // Arrange
        String className = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setGsiInterfaceClassName(className);

        // Assert
        assertEquals(className, this.sut.getGsiInterfaceClassName());
    }

    @Test
    public void test_setPermanent_always_setsPermanent() {
        // Arrange
        boolean isPermanent = anyBoolean();

        // Act
        this.sut.setPermanent(isPermanent);

        // Assert
        assertEquals(isPermanent, this.sut.isPermanent());
    }

    @Test
    public void test_setSharable_always_setsSharable() {
        // Arrange
        boolean isSharable = anyBoolean();

        // Act
        this.sut.setSharable(isSharable);

        // Assert
        assertEquals(isSharable, this.sut.isSharable());
    }

    @Test
    public void test_setForceNew_always_setsForceNew() {
        // Arrange
        boolean isForceNew = anyBoolean();

        // Act
        this.sut.setForceNew(isForceNew);

        // Assert
        assertEquals(isForceNew, this.sut.isForceNew());
    }

    @Test
    public void test_setGsiInterfaceName_always_setsGsiInterfaceName() {
        // Arrange
        String interfaceName = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setGsiInterfaceName(interfaceName);

        // Assert
        assertEquals(interfaceName, this.sut.getGsiInterfaceName());
    }

    @Test
    public void test_setRemoteProcessInitString_always_setsRemoteProcessInitString() {
        // Arrange
        String initString = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.setRemoteProcessInitString(initString);

        // Assert
        assertEquals(initString, this.sut.getRemoteProcessInitString());
    }

    @Test
    public void test_addG2ConnectionListener_always_addsListener() {
        // Arrange
        G2ConnectionListener listener = anyG2ConnectionListener();

        // Act
        this.sut.addG2ConnectionListener(listener);

        // Assert
        assertTrue(addedConnectionListeners.contains(listener));
    }

    @Test
    public void test_removeG2ConnectionListener_listenerExists_removesListener() {
        // Arrange
        G2ConnectionListener listener = anyG2ConnectionListener();
        this.sut.addG2ConnectionListener(listener);

        // Act
        this.sut.removeG2ConnectionListener(listener);

        // Assert
        assertFalse(addedConnectionListeners.contains(listener));
    }

    @Test
    public void test_removeG2ConnectionListener_listenerNotExist_doesNotThrowException() {
        // Arrange
        G2ConnectionListener listener = anyG2ConnectionListener();

        try {
            // Act
            this.sut.removeG2ConnectionListener(listener);
        } catch (Exception ex) {
            // Assert
            fail("removeG2ConnectionListener: Should not throw exception.");
        }
    }

    @Test
    public void test_addAllListeners_connectionExists_addsListeners() {
        // Arrange
        this.sut = new G2Connector();
        ArrayList<G2ConnectionListenerStub> listeners = addConnectionListeners();

        this.sut.setXn(this.connection);

        // Act
        this.sut.addAllListeners();

        // Assert
        for (G2ConnectionListener listener : listeners) {
            assertTrue(addedConnectionListeners.contains(listener));
        }
    }

    @Test
    public void test_addAllListeners_connectionNotExist_doesNotThrowException() {
        // Arrange
        this.sut = new G2Connector();
        addConnectionListeners();

        addAllListeners_assertExceptionIsNotThrown();
    }

    @Test
    public void test_removeAllListeners_connectionExists_removesListeners() {
        // Arrange
        this.sut = new G2Connector();
        ArrayList<G2ConnectionListenerStub> listeners = addConnectionListeners();

        this.sut.setXn(this.connection);

        // Act
        this.sut.removeAllListeners();

        // Assert
        for (G2ConnectionListener listener : listeners) {
            assertFalse(addedConnectionListeners.contains(listener));
        }
    }

    @Test
    public void test_removeAllListeners_connectionNotExist_doesNotThrowException() {
        // Arrange
        this.sut = new G2Connector();
        addConnectionListeners();

        removeAllListeners_assertExceptionIsNotThrown();
    }

    @Test
    public void test__getConnection_connectionExists_returnsConnection() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.connection, this.sut._getConnection());
    }

    // Assert
    @Test(expected = ConnectionNotAvailableException.class)
    public void test__getConnection_connectionNotExist_throwsException() {
        // Arrange
        this.sut = new G2Connector();

        // Act
        assertEquals(this.connection, this.sut._getConnection());
    }

    @Test
    public void test_getConnection_always_Connection() {
        // Arrange
        // Nothing to arrange

        // Act & Assert
        assertEquals(this.connection, this.sut.getConnection());
    }

    @Test
    public void test_closeConnection_connectionExists_closesConnection() {
        // Arrange
        this.connectionIsClosed = false;

        // Act
        this.sut.closeConnection();

        // Assert
        assertTrue(this.connectionIsClosed);
    }

    @Test
    public void test_closeConnection_connectionNotExist_doesNotThrowException() {
        // Arrange
        this.sut = new G2Connector();
        this.connectionIsClosed = false;

        closeConnection_assertExceptionIsNotThrown();
    }

    @Test
    public void test_closePrivateConnection_connectionExists_closesConnection() {
        // Arrange
        this.connectionIsClosed = false;

        // Act
        this.sut.closePrivateConnection();

        // Assert
        assertTrue(this.connectionIsClosed);
    }

    @Test
    public void test_closePrivateConnection_connectionNotExist_doesNotThrowException() {
        // Arrange
        this.sut = new G2Connector();
        this.connectionIsClosed = false;

        closePrivateConnection_assertExceptionIsNotThrown();
    }

    @Test
    public void test_createConnection_always_createsConnection() throws G2AccessException {
        // Arrange
        arrangeG2GatewayGetOrMakeConnection();

        // Act
        this.sut.createConnection();

        // Assert
        assertEquals(this.getOrMakeConnectionResponse, this.sut.getConnection());
    }

    @Test
    public void test_createConnection_connectionCreationThrowsException_doesNotThrowsException() {
        // Arrange
        arrangeG2GatewayGetOrMakeConnection();
        this.connectionCreationThrowsException = true;

        try {
            // Act
            this.sut.createConnection();
        } catch (Exception ex) {
            // Assert
            fail("createConnection: Should not throw exception.");
        }
    }

    @Test
    public void test_createConnection_success_initializesConnections() throws G2AccessException {
        // Arrange
        arrangeG2GatewayGetOrMakeConnection();
        addConnectionListeners();

        // Act
        this.sut.createConnection();

        // Assert
        for (G2ConnectionListenerStub listener : this.listeners) {
            assertTrue(listener.isConnectionInitialized());
        }
    }

    @Test
    public void test_createConnection_failure_communicatesError() throws G2AccessException {
        // Arrange
        arrangeG2GatewayGetOrMakeConnection();
        addConnectionListeners();
        this.connectionCreationThrowsException = true;

        // Act
        this.sut.createConnection();

        // Assert
        for (G2ConnectionListenerStub listener : this.listeners) {
            assertTrue(listener.isErrorCommunicated());
        }
    }

    @Test
    public void test_returnMessage_always_returnsMessage() {
        // Arrange
        String message = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.returnMessage(message);

        // Assert
        assertEquals(message, this.returnedMessage);
    }

    @Test
    public void test_reportLogBookErrorMessage_always_reportsErrorMessage() {
        // Arrange
        Symbol errorSymbol = anySymbol();
        String errorMessage = com.gensym.helpers.ObjectsFactory.anyString();

        // Act
        this.sut.reportLogBookErrorMessage(errorSymbol, errorMessage);

        // Assert
        assertEquals(errorSymbol, this.reportedErrorSymbol);
        assertEquals(errorMessage, this.reportedErrorMessage);
    }

    @Test
    public void test_registerJavaMethod_always_registersJavaMethod() {
        // Arrange
        Object target = new Object();
        String methodName = com.gensym.helpers.ObjectsFactory.anyString();
        Symbol rpdName = anySymbol();

        // Act
        this.sut.registerJavaMethod(target, methodName, rpdName);

        // Assert
        assertEquals(target, this.registeredTarget);
        assertEquals(methodName, this.registeredMethodName);
        assertEquals(rpdName, this.registeredRpdName);
    }

    @Test
    public void test_registerJavaMethodWithNewThred_always_registersJavaMethod() throws NoSuchMethodException {
        // Arrange
        Object target = new Object();
        Method method = this.getClass().getMethod("anyMethod");
        Symbol rpdName = anySymbol();
        boolean[] callInNewThreadTestCases = new boolean[]{true, false};

        for (boolean callInNewThread : callInNewThreadTestCases) {
            // Act
            this.sut.registerJavaMethod(target, method, rpdName, callInNewThread);

            // Assert
            assertEquals(target, this.registeredTarget);
            assertEquals(method, this.registeredMethod);
            assertEquals(rpdName, this.registeredRpdName);
            assertEquals(callInNewThread, this.registeredWithNewThread);
        }
    }

    @Test
    public void test_callRPC_always_callsRPC() throws G2AccessException {
        // Arrange
        Symbol g2ProcedureName = anySymbol();
        Object[] args = anyObjectsArray();
        int timeout = anyInteger();

        // Act
        this.sut.callRPC(g2ProcedureName, args, timeout);

        // Assert
        assertEquals(g2ProcedureName, this.calledG2ProcedureName);
        assertEquals(timeout, this.calledTimeout);
        assertEquals(args.length, this.calledArgs.length);

        for (int idx = 0; idx < args.length; idx++) {
            assertEquals(args[idx], this.calledArgs[idx]);
        }
    }

    @Test
    public void test_callRPCWithSequence_always_callsRPC() throws G2AccessException {
        // Arrange
        Symbol g2ProcedureName = anySymbol();
        Sequence args = anyObjectsSequence();
        int timeout = anyInteger();

        // Act
        this.sut.callRPC(g2ProcedureName, args, timeout);

        // Assert
        assertEquals(g2ProcedureName, this.calledG2ProcedureName);
        assertEquals(timeout, this.calledTimeout);
        assertEquals(args.size(), this.calledArgs.length);

        for (int idx = 0; idx < args.size(); idx++) {
            assertEquals(args.elementAt(idx), this.calledArgs[idx]);
        }
    }

    @Test
    public void test_startRPC_always_startsRpc() {
        // Arrange
        Symbol g2ProcedureName = anySymbol();
        Object[] items = anyObjectsArray();

        // Act
        this.sut.startRPC(g2ProcedureName, items);

        // Assert
        assertEquals(g2ProcedureName, this.startedRpcProcedureName);
        assertEquals(items.length, this.startedRpcItems.length);

        for (int idx = 0; idx < items.length; idx++) {
            assertEquals(items[idx], this.startedRpcItems[idx]);
        }
    }

    @Test
    public void test_startRPCWithSequence_always_startsRpc() {
        // Arrange
        Symbol g2ProcedureName = anySymbol();
        Sequence items = anyObjectsSequence();

        // Act
        this.sut.startRPC(g2ProcedureName, items);

        // Assert
        assertEquals(g2ProcedureName, this.startedRpcProcedureName);
        assertEquals(items.size(), this.startedRpcItems.length);

        for (int idx = 0; idx < items.size(); idx++) {
            assertEquals(items.elementAt(idx), this.startedRpcItems[idx]);
        }
    }

    @Test
    public void test_canCallRPC_always_callsRPC() {
        // Arrange
        boolean[] canCallRpcTestCases = new boolean[]{false, true};

        for (boolean canCallRpcTestCase : canCallRpcTestCases) {
            this.canCallRpc = canCallRpcTestCase;

            // Act & Assert
            assertEquals(this.sut.canCallRPC(), this.canCallRpc);
        }
    }

    @Test
    public void test_setRemoteRPCReturnKind_always_setsRemoteRPCReturnKind() {
        // Arrange
        Symbol g2ProcedureName = anySymbol();
        int returnValueType = anyInteger();

        // Act
        this.sut.setRemoteRPCReturnKind(g2ProcedureName, returnValueType);

        // Assert
        assertEquals(g2ProcedureName, this.remoteRpcG2ProcedureName);
        assertEquals(returnValueType, this.remoteRpcReturnValueType);
    }

    @Test
    public void test_getUniqueNamedItem_always_returnsUniqueNamedItem() throws G2AccessException {
        // Arrange
        Symbol itemClass = anySymbol();
        Symbol itemName = anySymbol();

        // Act
        this.sut.getUniqueNamedItem(itemClass, itemName);

        // Assert
        assertEquals(itemClass, this.uniqueItemClass);
        assertEquals(itemName, this.uniqueItemName);
    }

    @Test
    public void test_getAttributeAsText_always_returnsAttributeAsText() throws G2AccessException {
        // Arrange
        // No arrangement

        // Act & Assert
        assertEquals(this.attributeAsText, this.sut.getAttributeAsText(mock(Item.class), anySymbol(), anySymbol()));
    }

    @Test
    public void test_getAttributeDescriptions_always_returnsAttributeDescription() throws G2AccessException {
        // Arrange
        // No arrangement

        // Act
        Sequence result = this.sut.getAttributeDescriptions(any(Symbol.class), any(Sequence.class));

        // Assert
        assertEquals(this.attributeDescription.size(), result.size());

        for (int idx = 0; idx < this.attributeDescription.size(); idx++) {
            assertEquals(this.attributeDescription.elementAt(idx), result.elementAt(idx));
        }
    }

    @Test
    public void test_g2UnixTime_always_returnsUnixTime() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2UnixTime, this.sut.g2UnixTime(), Delta);
    }

    @Test
    public void test_g2UnixTimeAtStart_always_returnsUnixTimeAtStart() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2UnixTimeAtStart, this.sut.g2UnixTimeAtStart(), Delta);
    }

    @Test
    public void test_g2GetHostName_always_returnsHostName() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2HostName, this.sut.g2GetHostName());
    }

    @Test
    public void test_g2GetPortNumberOrName_always_returnsPortNumberOrName() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2PortNumberOrName, this.sut.g2GetPortNumberOrName());
    }

    @Test
    public void test_g2GetPortNumberOrNameGivenIndex_always_returnsPortNumber() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2PortNumberOrNameGivenIndex, this.sut.g2GetPortNumberOrNameGivenIndex(anyInteger()));
    }

    @Test
    public void test_g2GetSoftwareVersion_always_returnsSoftwareVersion() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2SoftwareVersion, this.sut.g2GetSoftwareVersion());
    }

    @Test
    public void test_getG2State_always_returnsState() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.g2State, this.sut.getG2State());
    }

    @Test
    public void test_setG2State_always_setsG2State() throws G2AccessException {
        // Arrange
        Symbol state = anySymbol();

        // Act
        Symbol result = this.sut.setG2State(state);

        // Assert
        assertEquals(state, this.setG2State);
        assertEquals(this.g2State, result);
    }

    @Test
    public void test_getStrictInstancesOfClass_always_returnsClassInstance() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act
        Sequence result = this.sut.getStrictInstancesOfClass(anySymbol());

        // Assert
        assertEquals(this.strictInstanceOfClass.size(), result.size());

        for (int idx = 0; idx < this.strictInstanceOfClass.size(); idx++) {
            assertEquals(this.strictInstanceOfClass.elementAt(idx), result.elementAt(idx));
        }
    }

    @Test
    public void test_getDirectSubclasses_always_returnsDirectSubclasses() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act
        Sequence result = this.sut.getDirectSubclasses(anySymbol());

        // Assert
        assertEquals(this.directSubclasses.size(), result.size());

        for (int idx = 0; idx < this.directSubclasses.size(); idx++) {
            assertEquals(this.directSubclasses.elementAt(idx), result.elementAt(idx));
        }
    }

    @Test
    public void test_setInterfaceDebugOptionsFlag_always_setsFlag() {
        // Arrange
        boolean[] testCases = new boolean[]{false, true};

        for (boolean testCase : testCases) {
            this.interfaceDebugFlag = !testCase;

            // Act
            this.sut.setInterfaceDebugOptions(testCase);

            // Assert
            assertEquals(testCase, this.interfaceDebugFlag);
        }
    }

    @Test
    public void test_setInterfaceDebugOptionsLevel_always_setsLevel() {
        // Arrange
        int level = anyInteger();

        // Act
        this.sut.setInterfaceDebugOptions(level);

        // Assert
        assertEquals(level, this.interfaceDebugLevel);
    }

    @Test
    public void test_getDefinition_always_returnsDefinition() throws G2AccessException {
        // Arrange
        // No arrangements

        // Act & Assert
        assertEquals(this.definition, this.sut.getDefinition(anySymbol()));
    }

    @Test
    public void test_getIconImage_always_returnsConnectorImage() {
        // Arrange
        Image expectedIcon = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("connector.gif"));

        // Act & Assert
        assertEquals(expectedIcon, this.sut.getIconImage());
    }

    @Test
    public void test_paint_always_paints() {
        // Arrange
        GraphicsStub graphics = anyGraphics();
        Image iconImage = this.sut.getIconImage();

        // Act
        this.sut.paint(graphics);

        // Assert
        assertEquals(1, graphics.drawnImages.size());
        DrawnImage drawnImage = graphics.drawnImages.get(0);
        assertEquals(iconImage, drawnImage.getImg());
        assertEquals(1, drawnImage.getX());
        assertEquals(1, drawnImage.getY());
        assertEquals(this.sut, drawnImage.getObserver());
    }

    @Test
    public void test_getPreferredSize_always_returnsPreferredSize() {
        // Arrange
        Image iconImg = this.sut.getIconImage();
        Dimension expected = new Dimension(iconImg.getWidth(this.sut) + 2, iconImg.getHeight(this.sut) + 2);

        // Act & Assert
        assertEquals(expected, this.sut.getPreferredSize());
    }

    @Test
    public void test_getMinimumSize_always_returnsMinimumSize() {
        // Arrange
        Image iconImg = this.sut.getIconImage();
        Dimension expected = new Dimension(iconImg.getWidth(this.sut) + 2, iconImg.getHeight(this.sut) + 2);

        // Act & Assert
        assertEquals(expected, this.sut.getMinimumSize());
    }

    public void anyMethod() {
    }
}