package com.gensym.jgi;

import com.gensym.classes.*;
import com.gensym.jgi.dataservice.DataServiceHandler;
import com.gensym.jgi.download.DefaultStubFactory;
import com.gensym.jgi.download.StubClassLoader;
import com.gensym.ntw.TwGateway;
import com.gensym.util.*;
import org.junit.After;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.io.File;
import java.lang.Object;
import java.util.Hashtable;
import java.util.Vector;

import static com.gensym.jgi.G2Gateway.ITEM_CLASS;
import static com.gensym.jgi.G2Gateway.RUNNING_;
import static com.gensym.jgi.G2Gateway.SYMBOL_CLASS;
import static org.junit.Assert.*;

/**
 * The class <code>G2GatewayTest</code> contains tests for the class <code>{@link G2Gateway}</code>.
 */

@RunWith(PowerMockRunner.class)
@PrepareForTest({JGInterface.class})
public class G2GatewayTest {
    private G2Gateway fixture = new G2Gateway();
    private Symbol symbol = Symbol.intern ("MODIFY");
    private static DefaultStubFactory stub = Mockito.mock(DefaultStubFactory.class);
    private static JGInterface jgiInterfaceMock = Mockito.mock(JGInterface.class);

    @BeforeClass
    public static void onlyOnce() throws Exception {
        PowerMockito.mockStatic(JGInterface.class);
        PowerMockito.doReturn(jgiInterfaceMock).when(JGInterface.class, "getJGInterface", Mockito.any(String[].class));
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(new Sequence());
        Mockito.when(jgiInterfaceMock.initiateConnection(Mockito.any(String.class),Mockito.any(String.class),
                Mockito.anyBoolean(), Mockito.any(String.class), Mockito.any(String.class), Mockito.any(String.class),
                Mockito.any(String.class), Mockito.any(G2Connection.class), Mockito.any(String.class), Mockito.anyBoolean())).thenReturn(true);
        Mockito.when(jgiInterfaceMock.initiateConnectionNative(Mockito.any(String.class),Mockito.any(String.class),
                Mockito.anyBoolean(), Mockito.any(String.class), Mockito.any(String.class), Mockito.any(String.class),
                Mockito.any(String.class), Mockito.any(String.class), Mockito.anyBoolean())).thenReturn(true);
        Mockito.doNothing().when(jgiInterfaceMock).returnValues(Mockito.any(Object[].class),Mockito.any(Structure[].class),
                Mockito.any(Object[].class), Mockito.any(int[].class), Mockito.any(int.class));
        Mockito.when(jgiInterfaceMock.checkForHandleOK(Mockito.anyInt(), Mockito.anyInt())).thenReturn("test");
        G2Gateway.initialize(8080);
        G2ConnectionHandlerFactory fac = Mockito.mock(G2ConnectionHandlerFactory.class);
        G2Gateway.setConnectionHandlerFactory(fac);
        G2Gateway.startup();
        G2Gateway.setGSIContextLimit(1);
    }
    @Before
    public void before() {
        fixture.dispatchG2ConnectionEvent(new G2ConnectionEvent(new Object(), 11, "", true));
        fixture.setDefaultCommunicationTimeOut(20000);
        fixture.setDefaultDefaultCommunicationTimeOut(1L);
        fixture.setLoader(new StubClassLoader(new G2Gateway()));
        fixture.setConnectionInfo(new G2ConnectionInfo("127.0.0.1", "62394"));
        fixture.addG2ConnectionListener(new G2ConnectionAdapter());
        fixture.setConnectionID(1);
        fixture.initializeReceiveRegistrations();
        fixture.initializeInstance();
    }
    @After
    public void after() {
        fixture.unloadClass(symbol);
        fixture.removeG2ConnectionListener(new G2ConnectionAdapter());
        fixture.closeConnection();
    }
    /**
     * Run the Object HANDLESUBSCRIPTIONS(Symbol,Item,Sequence,Object,Object,int) method test.
     */
    @Test
    public void testHANDLESUBSCRIPTIONS() {
        Item item = Mockito.mock(Item.class);
        Sequence denotation = new Sequence();
        Object newValue = new Object();
        Object userData = new Object();
        int subscriptionHandle = 1;
        Object result = fixture.HANDLESUBSCRIPTIONS(symbol, item, denotation, newValue, userData, subscriptionHandle);
        assertNotNull(result);
    }
    /**
     * Run the boolean unsubscribeToItemMultiple(Sequence) method test
     *
     */
    @Test
    public void testUnsubscribeToItemMultiple() throws G2AccessException {
        DataServiceHandler dataServiceHandler = Mockito.mock(DataServiceHandler.class);
        fixture.setDataServiceHandler(dataServiceHandler);
        fixture.dispatchDataServiceHandlerEvent(new Object(), 1, new Object[]{});
        Sequence handles = new Sequence();
        handles.add(1);
        boolean result = fixture.unsubscribeToItemMultiple(handles);
        assertTrue(result);
    }
    /**
     * Run the boolean unsubscribeToItem(int) method test.
     */
    @Test
    public void testUnsubscribeToItem() throws G2AccessException {
        Sequence handles = new Sequence();
        handles.add(1);
        String fileName = "//Users//Dee//Desktop//file_list.txt";
        fixture.appendProcedureTable(fileName);
        boolean result = fixture.unsubscribeToItem(1);
        assertFalse(result);
    }
    /**
     * Run the Object callRPC(Symbol,Object[]) method test.
     *
     */
    @Test
    public void testCallRPC() throws G2AccessException {
        Object[] args = new Object[]{"-nolistener"};
        fixture.startRPC(symbol, args);
        Object result = fixture.callRPC(symbol, args);
        assertNotNull(result);
    }
    /**
     * Run the Object callRPC(Symbol,Object[]) method test.
     *
     */
    @Test
    public void testCallRPCInt() throws G2AccessException {
        Object[] args = new Object[]{"-nolistener"};
        Object result = fixture.callRPC(symbol, args, 1);
        assertNotNull(result);
    }
    /**
     *
     * Run the G2Connection getOrMakeConnection(G2ConnectionInfo) method test.
     *
     */
    //@Test
    public void testGetOrMakeConnection() throws G2AccessInitiationException {
        G2ConnectionInfo info = new G2ConnectionInfo("127.0.0.1", "62394");
        G2Connection result = G2Gateway.getOrMakeConnection(info);
        assertNotNull(result);
    }
    /**
     * Run the String toURLString() method test.
     *
     */
    @Test
    public void testToURLString() {
        String result = fixture.toURLString();
        assertNotNull(result);
        assertEquals("g2://127.0.0.1:62394", result);
    }
    @Test
    public void testToURLString_null() {
        fixture.reportLogBookErrorMessage(Symbol.intern(""), "");
        fixture.setConnectionInfo(null);
        G2Gateway fixture = new G2Gateway();
        String result = fixture.toURLString();
        assertNotNull(result);
        assertEquals("?", result);
    }
    /**
     * Run the String checkForHandleOK(int) method test.
     *
     */
    @Test
    public void testCheckForHandleOK() {
        Mockito.when(jgiInterfaceMock.checkForHandleOK(Mockito.anyInt(), Mockito.anyInt())).thenReturn("test");
        int type = 1;
        String result = fixture.checkForHandleOK(type);
        assertEquals("test", result);
    }
    /**
     * Run the Structure g2getVersionStructure() method test.
     *
     */
    @Test
    public void testG2getVersionStructure() throws G2AccessException, NoSuchAttributeException {
        Structure structure = getStructure();
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(structure);
        Structure result = fixture.g2getVersionStructure();
        assertEquals(result.getAttributeCount() , 6);
    }
    /**
     * Run the boolean connectedToSameG2(G2Gateway) method test.
     *
     */
    @Test
    public void testConnectedToSameG2() {
        G2Gateway otherGateway = new G2Gateway();
        boolean result = fixture.connectedToSameG2(otherGateway);
        assertFalse(result);
    }
    /**
     * Run the Item createItem(Symbol) method test.
     *
     */
    @Test
    public void testCreateItem() throws G2AccessException {
        Symbol symbol = Symbol.intern ("MODIFY");
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(Mockito.mock(Item.class));
        Item result = fixture.createItem(symbol);
        assertEquals(result.getItemHeight(), 0);
    }
    /**
     * Run the Item getUniqueNamedItem(Symbol,Symbol) method test.
     */
    @Test
    public void testGetUniqueNamedItem() throws G2AccessException {
        Symbol itmClass = Symbol.intern("MODIFY");
        Symbol itmName = Symbol.intern("MODIFY");
        Item item = Mockito.mock(Item.class);
        Mockito.when(item.getItemHeight()).thenReturn(1);
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(item);
        fixture.returnValues(new Item[] {}, new Object[] {}, new int[] {});
        fixture.returnMessage("test");
        Item result = fixture.getUniqueNamedItem(itmClass, itmName);
        assertEquals(result.getItemHeight(), 1);
    }
    /**
     * Run the Sequence getSystemClassInheritancePath(G2Definition) method test.
     *
     */
    @Test(expected = CorruptionException.class)
    public void testGetSystemClassInheritancePath() {
        G2Definition definition = Mockito.mock(G2Definition.class);
        try {
            Sequence result = fixture.getSystemClassInheritancePath(definition);
        } catch (G2AccessException e) {
            e.printStackTrace();
        }
    }
    /**
     * Run the G2Definition getDefinition(Item) method test.
     *
     */
    @Test(expected = CorruptionException.class)
    public void testGetDefinition() {
        Item item = Mockito.mock(Item.class);
        try {
            G2Definition result = fixture.getDefinition(item);
        } catch (G2AccessException e) {
            e.printStackTrace();
        }
    }
    /**
     * Run the G2Definition getDefinition(int, int) method test.
     *
     */
    @Test(expected = UnexpectedException.class)
    public void testGetDefinitionHandle() {
        try {
            fixture.getDefinition(1,1);
        } catch (G2AccessException e) {
            e.printStackTrace();
        }
    }
    /**
     * Run the Sequence getSystemClassInheritancePath(G2Definition) method test.
     *
     */
    @Test
    public void testGetDefinitionSymbol() throws G2AccessException {
        G2Definition def = Mockito.mock(G2Definition.class);
        Mockito.when(jgiInterfaceMock.getStubFactory(Mockito.anyInt())).thenReturn(stub);
        Mockito.when(stub.getOrLoadDefinition(Mockito.any(Symbol.class))).thenReturn(def);
        G2Definition result = fixture.getDefinition(symbol);
        assertNotNull(result);
    }
    /**
     * Run the long getDefaultCommunicationTimeOut() method test.
     *
     */
    @Test
    public void testGetDefaultCommunicationTimeOut() {
        fixture.setDefaultCommunicationTimeOut(20000);
        long result = fixture.getDefaultCommunicationTimeOut();
        assertEquals(20000, result);
    }
    /**
     * Run the Vector getG2ConnectionListeners() method test.
     *
     */
    @Test
    public void testGetG2ConnectionListeners() {
        Vector result = fixture.getG2ConnectionListeners();
        assertNotNull(result);
    }
    /**
     * Run the int getListenerSocket() method test.
     *
     */
    @Test
    public void testGetListenerSocket() {
        int result = G2Gateway.getListenerSocket();
        assertEquals(0, result);
    }
    /**
     * Run the boolean getSecureContext() method test.
     *
     */
    @Test
    public void testGetSecureContext() {
        boolean result = fixture.getSecureContext();
        assertFalse(result);
    }
    /**
     * Run the Sequence getDirectSubclasses(Symbol) method test.
     *
     */
    @Test
    public void testGetDirectSubclasses() throws G2AccessException {
        Sequence sequence = new Sequence();
        sequence.add("test");
        sequence.add("test1");
        sequence.add("test2");
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(new Sequence());
        Sequence result = fixture.getDirectSubclasses(symbol);
        assertNotNull(result.getContents());
    }
    /**
     * Run the Item getG2ProxyForJavaObject(String,Symbol,Object) method test.
     *
     */
    @Test
    public void testGetG2ProxyForJavaObject() throws G2AccessException {
        fixture.registerJavaMethod(new Object(), TwGateway.class,
                "HANDLETRENDCHARTSUBSCRIPTIONS",
                new Class[] {Integer.TYPE, ITEM_CLASS,
                        SYMBOL_CLASS, Structure.class},
                Symbol.intern ("HELLO"), true);
        fixture.setInterfaceDebugOptions(true);
        String g2ProxyClass = "test";
        Object javaObject = new Object();
        Item item = Mockito.mock(Item.class);
        Mockito.when(item.getItemHeight()).thenReturn(1);
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("Version.1.1.Rev.1.2015")
               .thenReturn("Version.1.1.Rev.1.2015").thenReturn("Version.1.1.Rev.1.2015").thenReturn(item);
        Item result = fixture.getG2ProxyForJavaObject(g2ProxyClass, symbol, javaObject);
        assertEquals(result.getItemHeight(),1);
    }
    /**
     * Run the Object getValue(Item,Denotation) method test.
     *
     */
    @Test
    public void testGetValue()throws G2AccessException  {
        Item itm = new ActionButtonImpl();
        Denotation denotation = new AttributeDenotation();
        Object result = fixture.getValue(itm, denotation);
        assertNotNull(result);
    }
    /**
     * Run the Item getItemWithUUID(String) method test.
     *
     */
    @Test
    public void testGetItemWithUUID() throws G2AccessException {
        String uuid = "test";
        Item item = new ActionButtonImpl();
        item.setPropertyValue(Symbol.intern("ITEM-HEIGHT"), 1);
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(item);
        Item result = fixture.getItemWithUUID(uuid);
        assertEquals(result.getItemHeight(), 1);
    }
    /**
     * Run the String getAttributeAsText(Item,Symbol,Symbol) method test.
     *
     */
    @Test
    public void testGetAttributeAsText() throws G2AccessException {
        Item itm = new ActionButtonImpl();
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("test");
        Symbol specificClassIfAny = null;
        String result = fixture.getAttributeAsText(itm, symbol, specificClassIfAny);
        assertEquals(result, "test");
    }
    /**
     * Run the int getGenerationMode() method test.
     */
    @Test
    public void testGetGenerationMode()
    {
        fixture.setGenerationMode(1);
        int result = fixture.getGenerationMode();
        assertEquals(1, result);
    }
    /**
     * Run the boolean getForceDownload() method test.
     *
     */
    @Test
    public void testGetForceDownload() {
        fixture.setForceDownload(true);
        boolean result = fixture.getForceDownload();
        assertTrue(result);
    }
    /**
     * Run the Class getInterfaceForG2Class(Symbol) method test.
     *
     */
    @Test
    public void testGetInterfaceForG2Class() {
        fixture.storeInterfaceForG2Class(Symbol.class);
        Class result = fixture.getInterfaceForG2Class(symbol);
        assertNull(result);
    }
    /**
     * Run the boolean makesOwnStubs() method test.
     *
     */
    @Test
    public void testMakesOwnStubs() {
        boolean result = fixture.makesOwnStubs();
        assertTrue(result);
    }
    /**
     * Run the Object getClassAttributeValue(Symbol,Symbol) method test.
     *
     */
    @Test
    public void testGetClassAttributeValue() throws G2AccessException {
        Symbol className = Symbol.intern("MODIFY");
        Symbol attrName = Symbol.intern("");
        Object result = fixture.getClassAttributeValue(className, attrName);
        assertNotNull(result);
    }
    /**
     * Run the Structure getClassAttributeValues(Symbol,Sequence) method test.
     *
     */
    @Test
    public void testGetClassAttributeValues() throws G2AccessException, NoSuchAttributeException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(getStructure());
        Sequence attrNames = new Sequence();
        attrNames.add(0, "test");
        Structure result = fixture.getClassAttributeValues(symbol, attrNames);
        assertEquals(result.getAttributeCount(), 6);
    }
    /**
     * Run the Sequence getAttributeDescriptions(Symbol,Sequence) method test.
     *
     */
    @Test
    public void testGetAttributeDescriptions() throws G2AccessException  {
        Sequence attributeNames = new Sequence();
        attributeNames.add(0, "test");
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(attributeNames);
        Sequence result = fixture.getAttributeDescriptions(symbol, attributeNames);
        assertEquals(result.get(0), "test");
    }
    /**
     * Run the double g2UnixTime() method test.
     *
     */
    @Test
    public void testG2UnixTime() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(1.0);
        double result = fixture.g2UnixTime();
        assertEquals(1.0, result, 0.1);
    }
    /**
     * Run the double g2UnixTimeAtStart() method test.
     *
     */
    @Test
    public void testG2UnixTimeAtStart() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(1.0);
        double result = fixture.g2UnixTimeAtStart();
        assertEquals(1.0, result, 0.1);
    }
    /**
     * Run the String g2GetHostName() method test.
     *
     */
    @Test
    public void testG2GetHostName() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("localhost");
        String result = fixture.g2GetHostName();
        assertEquals(result, "localhost");
    }
    /**
     * Run the String g2GetPortNumberOrName() method test.
     *
     */
    @Test
    public void testG2GetPortNumberOrName() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("5454");
        String result = fixture.g2GetPortNumberOrName();
        assertEquals(result, "5454");
    }
    /**
     * Run the String g2GetSoftwareVersion() method test.
     *
     */
    @Test
    public void testG2GetSoftwareVersion() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("1.0");
        String result = fixture.g2GetSoftwareVersion();
        assertEquals(result, "1.0");
    }
    /**
     * Run the Symbol getG2State() method test.
     *
     */
    @Test
    public void testGetG2State() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(Symbol.intern("Running"));
        fixture.setG2State(Symbol.intern("RUNNING"));
        Symbol result = fixture.getG2State();
        assertEquals(result.toString(), "Running");
    }
    /**
     * Run the Hashtable getSubscpnTable() method test.
     *
     */
    @Test
    public void testGetSubscpnTable() throws G2AccessException {
        Structure structure = new Structure();
        structure.setAttributeValue(Symbol.intern ("SUBSCRIPTION-HANDLE"), 1);
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(structure);
        fixture.subscribeToItem(getItem(), new Sequence(), new Object());
        Hashtable result = fixture.getSubscpnTable();
        assertEquals(result.size(), 1);
    }
    /**
     * Run the G2Version getMinimumVersion() method test.
     *
     */
    @Test
    public void testGetMinimumVersion() {
        G2Version result = fixture.getMinimumVersion();
        assertEquals(result.getMinorVersion(), 1);
    }
    /**
     * Run the G2Version getG2Version() method test.
     *
     */
    @Test
    public void testGetG2Version() throws G2AccessException {
        Structure structure = getStructure();
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn(structure);
        Mockito.when(jgiInterfaceMock.checkForHandleOK(Mockito.anyInt(), Mockito.anyInt())).thenReturn(null);
        fixture.dispatchG2ConnectionEvent(new G2ConnectionEvent(new Object(), 11, "", true));
        G2Version result = fixture.getG2Version();
        assertEquals(result.getMajorVersion(), 1);
    }
    /**
     * Run the G2Connection findConnection(G2ConnectionInfo) method test.
     */
    @Test
    public void testFindConnection() {
        G2ConnectionInfo connectionInfo = Mockito.mock(G2ConnectionInfo.class);
        fixture.storeOpenConnection();
        fixture.setConnectionInfo(connectionInfo);
        G2Connection result = G2Gateway.findConnection(connectionInfo);
        assertEquals(null, result);
    }
    /**
     * Run the String g2getBuildVersion() method test.
     *
     */
    @Test
    public void testG2getBuildVersion() throws G2AccessException {
        Mockito.when(jgiInterfaceMock.callRPC(Mockito.any(Object.class),Mockito.any(Object[].class),Mockito.anyInt(),Mockito.anyInt())).thenReturn("Version.1.1.Rev.1.2015");
        String result = fixture.g2getBuildVersion();
        assertEquals(result, "Version.1.1.Rev.1.2015");
    }
    /**
     * Run the Symbol[] getClassesReceived() method test.
     *
     */
    @Test
    public void testGetClassesReceived() {
        Symbol[] g2ClassNames = new Symbol[] {Symbol.intern("G2Gateway")};
        StubClassLoader stubClass = Mockito.mock(StubClassLoader.class);
        fixture.setLoader(stubClass);
        Mockito.when(stubClass.getStubClasses()).thenReturn(g2ClassNames);
        Mockito.when(jgiInterfaceMock.getStubFactory(Mockito.anyInt())).thenReturn(stub);
        boolean createThread = false;
        fixture.preloadG2Classes(g2ClassNames, createThread);
        Symbol[] result = fixture.getClassesReceived();
        assertEquals(result.length, 1);
    }

    public Structure getStructure() {
        Structure structure = new Structure();
        structure.setAttributeValue(com.gensym.util.Symbol.intern("MAJOR-VERSION-NUMBER"), 1);
        structure.setAttributeValue(com.gensym.util.Symbol.intern("MINOR-VERSION-NUMBER"), 1);
        structure.setAttributeValue(com.gensym.util.Symbol.intern("RELEASE-LEVEL"), Symbol.intern("Rev"));
        structure.setAttributeValue(com.gensym.util.Symbol.intern("REVISION"), 1);
        structure.setAttributeValue(com.gensym.util.Symbol.intern("PATCH-NUMBER"), 1);
        structure.setAttributeValue(com.gensym.util.Symbol.intern("BUILD-IDENTIFICATION"), "2015");
        return structure;
    }

    public Item getItem() throws G2AccessException {
        Item item = new ActionButtonImpl();
        item.setPropertyValue(Symbol.intern("ITEM-HEIGHT"), 1);
        return item;
    }

}


