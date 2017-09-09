package com.gensym.SocketManager;

import com.gensym.core.Product;
import com.gensym.core.ProductManager;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.mockito.Mockito;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.io.IOException;
import java.io.PrintStream;
import java.net.InetAddress;
import java.net.Socket;
import java.util.*;

import static com.gensym.helpers.ObjectsFactory.*;
import static org.junit.Assert.*;
import static org.powermock.api.mockito.PowerMockito.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest({G2JavaLog.class, ProductManager.class, G2Gateway.class})
public class JavaG2SocketManagerTest {

    private static JavaG2SocketManager javaG2SocketManager;
    private static G2ConnectionEvent g2ConnectionEvent;
    private static G2Connection connection;
    private static G2CommunicationErrorEvent g2CommunicationErrorEvent;
    private static Sequence intSequence;

    private static String intf;
    private static int port;
    private static String refID;
    private static Sequence socketAttrs;
    private static Sequence msgAttrs;

    private G2ServerSocket mockServerReturn = mock(G2ServerSocket.class);
    private G2ClientSocket mockClientReturn = mock(G2ClientSocket.class);

    @BeforeClass
    public static void initClass() throws IOException {

        connection =  Mockito.mock(G2Connection.class);
        javaG2SocketManager = new JavaG2SocketManager(connection, anyString());
        g2ConnectionEvent = mockG2ConnectionEvent();
        g2CommunicationErrorEvent = mockG2CommunicationErrorEvent();
        javaG2SocketManager.g2ConnectionInitialized(g2ConnectionEvent);

        intSequence = new Sequence();
        intSequence.add(anyInteger());
        intSequence.add(anyInteger());
        intSequence.add(true);
        intSequence.add(anyInteger());

        intf = anyString();
        port = anyInteger() * 100;
        refID = "9876";
        socketAttrs = anyStringsSequence();
        msgAttrs = createStringSequence(11);

        javaG2SocketManager.bCreateServerSocket(intf,port,refID,intSequence,msgAttrs);
        javaG2SocketManager.iCreateClientSocket(intf,"localhost",port,refID,intSequence,msgAttrs);
    }

    @Before
    public void init() {

        mockStatic(G2JavaLog.class);

        javaG2SocketManager.serverSocketsMap = mockServerSockerMap();
        javaG2SocketManager.clientSocketsMap = mockClientSockerMap();
    }

    @Test
    public void test_enumerateActiveServerClients_hasMatchingSocketUuid_returnsStringArray(){

        // Arrange
        String socketUuid = "ServerMapKey";

        // Act
        String[] actualResult = javaG2SocketManager.sEnumerateActiveServerClients(socketUuid);

        // Assert
        assertEquals(1,actualResult.length);
        assertEquals("ID: ClientRefID local port: 44 remote port: 43", actualResult[0].trim());
    }

    @Test
    public void test_bResetSocketIO_socketUuidExistsInServerSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ServerMapKey";

        // Act
        boolean actualResult = javaG2SocketManager.bResetSocketIO(socketUuid);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bResetSocketIO_socketUuidExistsInClientSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ClientMapKey";

        // Act
        boolean actualResult = javaG2SocketManager.bResetSocketIO(socketUuid);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bResetSocketIO_socketUuidNotExistsInSocketsMap_returnsFalse(){

        // Arrange
        String socketUuid = "NotKey";

        // Act
        boolean actualResult = javaG2SocketManager.bResetSocketIO(socketUuid);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_enumerateActiveThreads_onCall_returnsThreadsActiveCountArray(){

        // Arrange
        String[] expResult = new String[Thread.activeCount()];

        // Act
        String[] actualResult =javaG2SocketManager.sEnumerateActiveThreads();

        // Assert
        assertEquals(expResult.length, actualResult.length);
    }

    @Test
    public void test_enumerateClientSocketMappings_notEmptyClientSocketsMap_returnsSetString(){

        // Act
        String actualResult = javaG2SocketManager.enumerateClientSocketMappings();

        // Assert
        assertEquals("Client mappings = ClientMapKey,", actualResult);
    }

    @Test
    public void test_enumerateClientSocketMappings_emptyClientSocketsMap_returnsSetString(){

        // Arrange
        javaG2SocketManager.clientSocketsMap = Collections.emptyMap();

        // Act
        String actualResult = javaG2SocketManager.enumerateClientSocketMappings();

        // Assert
        assertEquals("No mappings for Client sockets.", actualResult);
    }

    @Test
    public void test_enumerateServerSocketMappings_notEmptyClientSocketsMap_returnsSetString(){

        // Act
        String actualResult = javaG2SocketManager.enumerateServerSocketMappings();

        // Assert
        assertEquals("Server mappings = ServerMapKey,", actualResult);
    }

    @Test
    public void test_enumerateServerSocketMappings_emptyClientSocketsMap_returnsSetString(){

        // Arrange
        javaG2SocketManager.serverSocketsMap = Collections.emptyMap();

        // Act
        String actualResult = javaG2SocketManager.enumerateServerSocketMappings();

        // Assert
        assertEquals("No mappings for Server sockets.", actualResult);
    }


    @Test
    public void test_sEnumerateSocketMappings_onCall_returnsSetString(){

        // Act
        String actualResult = javaG2SocketManager.sEnumerateSocketMappings();

        // Assert
        assertEquals("Server mappings = ServerMapKey,\n" +
                "Client mappings = ClientMapKey,", actualResult);
    }

    @Test
    public void test_sEnumerateActiveServerClients_noMatchingServerSocketUuid_returnsNullStringArray(){

        // Arrange
        String socketUuid = "NoKey";

        // Act
        String[] actualResult = javaG2SocketManager.sEnumerateActiveServerClients(socketUuid);

        // Assert
        assertEquals(1, actualResult.length);
        assertEquals("NULL", actualResult[0]);
    }

    @Test
    public void test_sEnumerateSocketConnections_ExistsInServerSocketsMapEmptyClientDetails_returnEmptyString() {

        // Arrange
        String intf = "intf";
        String socketUuid = "ServerMapKey";

        // Act
        String actualResult = javaG2SocketManager.sEnumerateSocketConnections(intf, socketUuid);

        // Assert
        assertEquals(actualResult, "");
    }

    @Test
    public void test_sEnumerateSocketConnections_ExistsInClientSocketsMapEmptyClientDetails_returnEmptyString() {

        // Arrange
        String intf = "intf";
        String socketUuid = "ClientMapKey";

        // Act
        String actualResult = javaG2SocketManager.sEnumerateSocketConnections(intf, socketUuid);

        // Assert
        assertEquals(actualResult, "");
    }

    @Test
    public void test_sEnumerateSocketConnections_NotExistsInClientSocketsMap_returnSetString() {

        // Arrange
        String intf = "intf";
        String socketUuid = "NotMapKey";

        // Act
        String actualResult = javaG2SocketManager.sEnumerateSocketConnections(intf, socketUuid);

        // Assert
        assertEquals("Could not find socket as an active mapped socket", actualResult);
    }

    @Test
    public void test_bUpdateSocket_socketUuidExistsInServerSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ServerMapKey";
        Sequence attributeSeq = new Sequence();

        // Act
        boolean actualResult = javaG2SocketManager.bUpdateSocket(socketUuid, attributeSeq);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bUpdateSocket_socketUuidExistsInServerSocketsMapRaiseException_returnsFalse(){

        // Arrange
        String socketUuid = "ServerMapKey";
        Sequence attributeSeq = new Sequence();

        Mockito.doThrow(Exception.class).when(mockClientReturn).updateSocketAttributes(attributeSeq);

        // Act
        boolean actualResult = javaG2SocketManager.bUpdateSocket(socketUuid, attributeSeq);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_bUpdateSocket_socketUuidExistsInClientSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ClientMapKey";
        Sequence attributeSeq = new Sequence();

        // Act
        boolean actualResult = javaG2SocketManager.bUpdateSocket(socketUuid, attributeSeq);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bUpdateSocket_socketUuidExistsInClientSocketsMapRaiseException_returnsFalse(){

        // Arrange
        String socketUuid = "ClientMapKey";
        Sequence attributeSeq = new Sequence();

        Mockito.doThrow(Exception.class).when(mockClientReturn).updateSocketAttributes(attributeSeq);

        // Act
        boolean actualResult = javaG2SocketManager.bUpdateSocket(socketUuid, attributeSeq);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_bUpdateSocket_socketUuidNotExistsInSocketsMap_returnsFalse(){

        // Arrange
        String socketUuid = "NotKey";
        Sequence attributeSeq = new Sequence();

        // Act
        boolean actualResult = javaG2SocketManager.bUpdateSocket(socketUuid, attributeSeq);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_closeAllSockets_onCall_returnsTrue(){

        // Act
        boolean actualResult = javaG2SocketManager.bCloseAllSockets();

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_getJavaLinkVersion_onCall_returnsProductSetDisplayVersion(){

        // Arrange
        mockStatic(ProductManager.class);

        Product product = Mockito.mock(Product.class);

        Mockito.when(product.getDisplayVersion()).thenReturn("setVersion");

        when(ProductManager.getProduct("javalink")).thenReturn(product);

        //Act
        String actualResult = JavaG2SocketManager.getJavaLinkVersion();

        // Assert
        assertEquals("setVersion", actualResult);
    }

    @Test
    public void test_getJavaLinkVersion_raiseException_returnsSetExceptionString(){

        // Arrange
        mockStatic(ProductManager.class);

        Product product = Mockito.mock(Product.class);

        Mockito.doThrow(Exception.class).when(product).getDisplayVersion();

        when(ProductManager.getProduct("javalink")).thenReturn(product);

        //Act
        String actualResult = JavaG2SocketManager.getJavaLinkVersion();

        // Assert
        assertEquals("the product named 'javalink' is unknown", actualResult);
    }

    @Test
    public void test_readBlockage_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.readBlockage(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Error reading from G2");
    }

    @Test
    public void test_writeBlockage_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.writeBlockage(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Error writing to G2");
    }

    @Test
    public void test_communicationError_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.communicationError(g2CommunicationErrorEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2/Java communication error: "
                + g2CommunicationErrorEvent.getMessage());
    }

    @Test
    public void test_g2MessageReceived_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2MessageReceived(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Message received from G2: "
                + g2ConnectionEvent.getMessage());
    }

    @Test
    public void test_g2ConnectionClosed_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2ConnectionClosed(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2 connection closed - close sockets");
    }

    @Test
    public void test_g2IsStarted_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2IsStarted(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "G2 has (re)started - connection established");
    }

    @Test
    public void test_g2IsPaused_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2IsPaused(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "G2 is paused - awaiting resume");
    }

    @Test
    public void test_g2IsReset_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2IsReset(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "G2 has been reset - closing all open sockets & awaiting restart");
    }

    @Test
    public void test_g2IsResumed_onCall_verifysG2JavaLogCall(){

        // Act
        javaG2SocketManager.g2IsResumed(g2ConnectionEvent);

        // Assert
        verifyStatic();
        G2JavaLog.log(G2JavaLog.G2_JAVA_CONNECTION, "G2 has resumed");
    }

    @Test
    public void test_mainClass_onCall_startG2Gateway() throws Exception {

        // Arrange
        PrintStream printStream = Mockito.mock(PrintStream.class);
        Product product = Mockito.mock(Product.class);

        System.setOut(printStream);

        mockStatic(ProductManager.class);
        mockStatic(G2Gateway.class);

        Mockito.when(product.getDisplayVersion()).thenReturn("setVersion");
        PowerMockito.when(ProductManager.getProduct("javalink")).thenReturn(product);

        // Act
        javaG2SocketManager.main(new String[]{"-port", String.valueOf(anyInteger()), "-debug", "5", "-encoding", "UTF-8"});

        // Assert
        Mockito.verify(printStream).println("JavaLink version: setVersion");
        verifyStatic();
        G2Gateway.startup();
        verifyStatic();
        G2Gateway.setConnectionHandlerFactory(Matchers.any(G2ConnectionHandlerFactory.class));
        verifyStatic();
        G2Gateway.initialize(Matchers.any(String[].class));
    }

    @Test
    public void test_bCloseSocket_socketUuidExistsInServerSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ServerMapKey";

        // Act
        boolean actualResult = javaG2SocketManager.bCloseSocket(socketUuid);

        // Assert
        assertTrue(actualResult);
        Mockito.verify(mockServerReturn).closeSocketImpl();
    }

    @Test
    public void test_bCloseSocket_socketUuidExistsInClientSocketsMap_returnsTrue(){

        // Arrange
        String socketUuid = "ClientMapKey";

        // Act
        boolean actualResult = javaG2SocketManager.bCloseSocket(socketUuid);

        // Assert
        assertTrue(actualResult);
        Mockito.verify(mockClientReturn).closeSocketImpl();
    }

    @Test
    public void test_bCloseSocket_socketUuidNotExistsInSocketsMap_returnsFalse(){

        // Arrange
        String socketUuid = "NotKey";

        // Act
        boolean actualResult = javaG2SocketManager.bCloseSocket(socketUuid);

        // Assert
        assertFalse(actualResult);
        verifyStatic();
        G2JavaLog.log(G2JavaLog.MANDATORY_INFORMATION, "Could not locate socket with ID " + socketUuid);
    }

    @Test
    public void test_bSendDataToSocket_equalCnxIDServerSocketsMapContainsKey_returnsTrue(){

        // Arrange
        String socketUuid = "ServerMapKey";
        String cnxID = "setCnxID";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_notEqualCnxIDServerSocketsMapContainsKey_returnsFalse(){

        // Arrange
        String socketUuid = "ServerMapKey";
        String cnxID = "Not-SetCnxID";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_emptyCnxIDNullG2ClientSocketServerSocketsMapContainsKey_returnsFalse(){

        // Arrange
        String socketUuid = "ServerMapKey";
        String cnxID = "";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        mockClientReturn.client = null;

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_emptyCnxIDNotNullG2ClientSocketServerSocketsMapContainsKey_returnsTrue(){

        // Arrange
        String socketUuid = "ServerMapKey";
        String cnxID = "";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        mockClientReturn.client = new Socket();

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_notNullG2ClientSocketOutClientSocketsMapContainsKey_returnsTrue(){

        // Arrange
        String socketUuid = "ClientMapKey", cnxID = "";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        mockClientReturn.socketOut = mockG2OutputThread(mock(G2ClientSocket.class));

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertTrue(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_nullG2ClientSocketOutClientSocketsMapContainsKey_returnsFalse(){

        // Arrange
        String socketUuid = "ClientMapKey", cnxID = "";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        mockClientReturn.socketOut = null;

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertFalse(actualResult);
    }

    @Test
    public void test_bSendDataToSocket_socketsMapContainsNoMatchingKey_returnsFalse(){

        // Arrange
        String socketUuid = "NotMapKey", cnxID = "";
        Sequence seqTextCodes = new Sequence();
        seqTextCodes.add(anyInteger());

        // Act
        boolean actualResult = javaG2SocketManager.bSendDatatoSocket(socketUuid, cnxID, seqTextCodes);

        // Assert
        assertFalse(actualResult);
    }

    private Map mockServerSockerMap(){

        HashMap serverMap = new HashMap();
        Hashtable mockHashtable = new Hashtable();
        ServerSocketThread mockSocketThread = mock(ServerSocketThread.class);
        InetAddress mockAddress = mock(InetAddress.class);

        mockClientReturn.socketIn = mockG2InputThread(mockClientReturn);
        mockClientReturn.socketRead = mockG2ReadThread(mockClientReturn);
        mockClientReturn.socketOut = mockG2OutputThread(mockClientReturn);
        mockClientReturn.socketWrite = mockG2WriteThread(mockClientReturn);

        mockHashtable.put("ServerClientsKey", mockClientReturn);

        mockServerReturn.serverClients = mockHashtable;
        mockServerReturn.serverThread = mockSocketThread;
        mockServerReturn.refID = "SetServerRefID";
        mockClientReturn.remoteAddress = mockAddress;
        mockClientReturn.client = new Socket();
        mockClientReturn.cnxID = "setCnxID";
        mockClientReturn.remotePort = 41;
        mockClientReturn.localPort = 42;
        mockClientReturn.refID = "SetClientRefID";

        mockSocketThread.isActive = true;

        serverMap.put("ServerMapKey", mockServerReturn);

        return serverMap;
    }

    private Map mockClientSockerMap(){

        HashMap clientMap = new HashMap();
        Set hashSet = new HashSet();
        hashSet.add(anyString());
        Hashtable mockHashtable = new Hashtable();
        ServerSocketThread mockSocketThread = mock(ServerSocketThread.class);
        InetAddress mockAddress = mock(InetAddress.class);

        mockClientReturn.socketIn = mockG2InputThread(mockClientReturn);
        mockClientReturn.socketRead = mockG2ReadThread(mockClientReturn);
        mockClientReturn.socketOut = mockG2OutputThread(mockClientReturn);
        mockClientReturn.socketWrite = mockG2WriteThread(mockClientReturn);

        mockServerReturn.serverClients = mockHashtable;
        mockServerReturn.serverThread = mockSocketThread;
        mockServerReturn.refID = "ServerRefID";
        mockClientReturn.remoteAddress = mockAddress;
        mockClientReturn.remotePort = 43;
        mockClientReturn.localPort = 44;
        mockClientReturn.refID = "ClientRefID";

        mockSocketThread.isActive = true;

        mockHashtable.put("ClientMapKey", mockClientReturn);

        clientMap.put("ClientMapKey", mockClientReturn);

        return clientMap;
    }

    private G2InputThread mockG2InputThread(G2ClientSocket mockClientReturn){
        G2InputThread mockInputThread = new G2InputThread(mockClientReturn);
        mockInputThread.setName(anyString());
        mockInputThread.isActive = true;
        return mockInputThread;
    }

    private G2ReadThread mockG2ReadThread(G2ClientSocket mockClientReturn){
        G2ReadThread mockReadThread = new G2ReadThread(mockClientReturn);
        mockReadThread.setName(anyString());
        mockReadThread.isActive = true;
        return mockReadThread;
    }

    private G2WriteThread mockG2WriteThread(G2ClientSocket mockClientReturn){
        G2WriteThread mockWriteThread = new G2WriteThread(mockClientReturn);
        mockWriteThread.setName(anyString());
        mockWriteThread.isActive = true;
        return mockWriteThread;
    }

    private G2OutputThread mockG2OutputThread(G2ClientSocket mockClientReturn){
        G2OutputThread mockOutputThread = new G2OutputThread(mockClientReturn);
        mockOutputThread.setName(anyString());
        mockOutputThread.isActive = true;
        return mockOutputThread;
    }

    private static G2ConnectionEvent mockG2ConnectionEvent(){
        G2ConnectionEvent g2ConnectionEvent = mock(G2ConnectionEvent.class);
        return g2ConnectionEvent;
    }

    private static G2CommunicationErrorEvent mockG2CommunicationErrorEvent(){
        G2CommunicationErrorEvent g2CommunicationErrorEvent = mock(G2CommunicationErrorEvent.class);
        return g2CommunicationErrorEvent;
    }

    private static Sequence createStringSequence(int amount){
        Sequence ret = new Sequence(amount);
        for (int i = 0; i < amount; i++){
            ret.add(anyString());
        }
        return ret;
    }
}