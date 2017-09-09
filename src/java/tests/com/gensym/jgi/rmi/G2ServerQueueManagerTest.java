package com.gensym.jgi.rmi;

import com.gensym.classes.ImplAccess;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpAccessStub;
import com.gensym.classes.VariableOrParameter;
import com.gensym.jgi.*;
import com.gensym.jgi.download.G2AccessStub;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.util.*;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Matchers;
import org.mockito.Mock;
import org.mockito.Mockito;
import org.mockito.verification.VerificationMode;
import org.powermock.api.mockito.PowerMockito;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.reflect.Whitebox;

import java.io.PrintWriter;
import java.rmi.ConnectException;
import java.rmi.RemoteException;
import java.util.Hashtable;
import java.util.Vector;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ Trace.class })
public class G2ServerQueueManagerTest {

    private G2ServerQueueManager g2serverQueueManager;
    private G2Access g2Access;
    private RMIEventQueueProcessor remoteClient;

    @Before
    public void setUp() {

        g2Access = Mockito.mock(G2AccessStub.class);
        remoteClient = Mockito.mock(RMIEventQueueProcessor.class);

        g2serverQueueManager = new G2ServerQueueManager(g2Access, remoteClient);
    }

    @After
    public void tearDown() { g2serverQueueManager = null; g2Access = null; remoteClient = null; }

    private void testProcessQueueVerifiesOnRaiseException(String sqmrun, Throwable detail) throws Exception {

        // Arrange
        Vector queueCopy = new Vector();
        RemoteException remoteEx = Mockito.mock(RemoteException.class);

        remoteEx.detail = detail;

        PowerMockito.mockStatic(Trace.class);

        Mockito.doThrow(remoteEx).when(remoteClient).processEventQueue(queueCopy);

        // Act
        g2serverQueueManager.processQueue(queueCopy);

        // Assert
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq("sqmrun1"), Matchers.any());
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq("sqmrun3"), Matchers.any());
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq(sqmrun), Matchers.any());
        PowerMockito.verifyStatic();
        Trace.exception(Matchers.any(Exception.class));
    }

    @Test
    public void test_addSource_newSourceOfEvents_returnsTrue() {

        // Arrange
        Object source = new Object();
        Hashtable eventSources = new Hashtable();

        // Act
        boolean actualResult = g2serverQueueManager.addSource(source, eventSources);

        // Assert
        Assert.assertTrue(actualResult);
        Assert.assertEquals(Boolean.TRUE, eventSources.get(source));
    }

    @Test
    public void test_addSource_existingSourceOfEvents_returnsFalse() {

        // Arrange
        Object source = new Object();
        Hashtable eventSources = new Hashtable();
        eventSources.put(source, "test");

        // Act
        boolean actualResult = g2serverQueueManager.addSource(source, eventSources);

        // Assert
        Assert.assertFalse(actualResult);
    }

    @Test
    public void test_subscribeToItem_onCall_returnSetStructure() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Structure structure = new Structure();

        Mockito.when(((ImplAccess)item).addItemListenerRetrievingState(Matchers.any(ItemListener.class)))
                .thenReturn(structure);

        // Act
        Structure actualResult = g2serverQueueManager.subscribeToItem(item);

        // Assert
        Assert.assertEquals(structure, actualResult);
    }

    @Test (expected = G2AccessException.class)
    public void test_subscribeToItem_G2AccessException_returnSetStructure() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);

        Mockito.when(((ImplAccess) item).addItemListenerRetrievingState(Matchers.any(ItemListener.class)))
                .thenThrow(G2AccessException.class);

        // Act
        g2serverQueueManager.subscribeToItem(item);
    }

    @Test
    public void test_subscribeToItemMultiple_onCall_returnSetSequence() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Sequence denotation_sequences = new Sequence();
        Sequence sequence = new Sequence();

        Mockito.when(item.addItemListenerRetrievingStateMultiple(Matchers.any(ItemListener.class)
                , Matchers.eq(denotation_sequences))).thenReturn(sequence);

        // Act
        Sequence actualResult = g2serverQueueManager.subscribeToItemMultiple(item, denotation_sequences);

        // Assert
        Assert.assertEquals(sequence, actualResult);
    }

    @Test (expected = G2AccessException.class)
    public void test_subscribeToItemMultiple_G2AccessException_returnSetStructure() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Sequence denotation_sequences = new Sequence();

        Mockito.when(item.addItemListenerRetrievingStateMultiple(Matchers.any(ItemListener.class)
                , Matchers.eq(denotation_sequences))).thenThrow(G2AccessException.class);

        // Act
        g2serverQueueManager.subscribeToItemMultiple(item, denotation_sequences);
    }

    @Test
    public void test_unsubscribeToItemMultiple_itemEventSourcesExists_returnsTrue() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Sequence subscriptionHandles = new Sequence();
        Hashtable itemEventSources = new Hashtable();
        itemEventSources.put(item, "test");

        Mockito.doNothing().when(item).removeItemListenerForThreeTiers(Matchers.any(ItemListener.class)
                , Matchers.eq(subscriptionHandles));

        Whitebox.setInternalState(g2serverQueueManager, "itemEventSources", itemEventSources);

        // Act
        boolean actualResult = g2serverQueueManager.unsubscribeToItemMultiple(item, subscriptionHandles);

        // Assert
        Assert.assertTrue(actualResult);
        Assert.assertEquals(0, itemEventSources.size());
    }

    @Test
    public void test_unsubscribeToItemMultiple_itemEventSourcesNotExists_returnsFalse() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Sequence subscriptionHandles = new Sequence();

        Mockito.doNothing().when(item).removeItemListenerForThreeTiers(Matchers.any(ItemListener.class)
                , Matchers.eq(subscriptionHandles));

        // Act
        boolean actualResult = g2serverQueueManager.unsubscribeToItemMultiple(item, subscriptionHandles);

        // Assert
        Assert.assertFalse(actualResult);
    }

    @Test
    public void test_unsubscribeToItem_itemEventSourcesExists_returnsTrue() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);
        Hashtable itemEventSources = new Hashtable();
        itemEventSources.put(item, "test");

        Whitebox.setInternalState(g2serverQueueManager, "itemEventSources", itemEventSources);

        // Act
        boolean actualResult = g2serverQueueManager.unsubscribeToItem(item);

        // Assert
        Assert.assertTrue(actualResult);
        Assert.assertEquals(0, itemEventSources.size());
    }

    @Test
    public void test_unsubscribeToItem_itemEventSourcesNotExists_returnsFalse() throws G2AccessException {

        // Arrange
        Item item = Mockito.mock(ItemImpAccessStub.class);

        // Act
        boolean actualResult = g2serverQueueManager.unsubscribeToItem(item);

        // Assert
        Assert.assertFalse(actualResult);
    }

    @Test
    public void test_startVariableValueListening_onCall_putsVariableEventSourcesExistsAndReturnsSetStructure()
            throws G2AccessException {

        // Arrange
        VariableOrParameter itm = Mockito.mock(VariableOrParameter.class);
        Structure expectedResult = new Structure();
        Hashtable variableEventSources = new Hashtable();

        Whitebox.setInternalState(g2serverQueueManager, "variableEventSources", variableEventSources);

        Mockito.when(itm.addVariableValueListenerRetrievingState(Matchers.any(VariableValueListener.class)))
                .thenReturn(expectedResult);

        // Act
        Structure actualResult = g2serverQueueManager.startVariableValueListening(itm);

        // Assert
        Assert.assertEquals(expectedResult, actualResult);
        Assert.assertEquals(Boolean.TRUE, variableEventSources.get(itm));
    }

    @Test
    public void test_stopVariableValueListening_onCall_removesVariableEventSourcesExists()
            throws G2AccessException {

        // Arrange
        VariableOrParameter itm = Mockito.mock(VariableOrParameter.class);
        Hashtable variableEventSources = new Hashtable();
        variableEventSources.put(itm, "test");

        Whitebox.setInternalState(g2serverQueueManager, "variableEventSources", variableEventSources);

        Mockito.doNothing().when(itm).removeVariableValueListener(Matchers.any(VariableValueListener.class));

        // Act
        g2serverQueueManager.stopVariableValueListening(itm);

        // Assert
        Assert.assertEquals(0, variableEventSources.size());
        Assert.assertNull(variableEventSources.get(itm));
    }

    @Test
    public void test_startConnectionListening_onCall_addG2ConnectionListener()
            throws G2AccessException {

        // Act
        g2serverQueueManager.startConnectionListening();

        // Assert
        Mockito.verify(g2Access).addG2ConnectionListener(Matchers.any(G2ConnectionListener.class));
    }

    @Test
    public void test_stopConnectionListening_onCall_removeG2ConnectionListener()
            throws G2AccessException {

        // Arrange
        Whitebox.setInternalState(g2serverQueueManager, "connectionListening", Boolean.TRUE);

        // Act
        g2serverQueueManager.stopConnectionListening();

        // Assert
        Mockito.verify(g2Access).removeG2ConnectionListener(Matchers.any(G2ConnectionListener.class));
    }

    @Test
    public void test_disconnectClient_onCall_setConnectionListeningFalse()
            throws G2AccessException, RemoteException {

        // Arrange
        LoopProcessingException ex = Mockito.mock(LoopProcessingException.class);
        Item item = Mockito.mock(ItemImpAccessStub.class);
        VariableOrParameter itm = Mockito.mock(VariableOrParameter.class);

        Hashtable variableEventSources = new Hashtable();
        variableEventSources.put(itm, "test1");

        Hashtable itemEventSources = new Hashtable();
        itemEventSources.put(item, "test2");

        Whitebox.setInternalState(g2serverQueueManager, "connectionListening", true);
        Whitebox.setInternalState(g2serverQueueManager, "itemEventSources", itemEventSources);
        Whitebox.setInternalState(g2serverQueueManager, "variableEventSources", variableEventSources);

        // Act
        g2serverQueueManager.disconnectClient(ex);

        // Assert
        Mockito.verify(ex).printFullStackTrace(Matchers.any(PrintWriter.class));
        Assert.assertEquals(0, itemEventSources.size());
        Assert.assertNull(itemEventSources.get(item));
        Assert.assertEquals(0, variableEventSources.size());
        Assert.assertNull(variableEventSources.get(item));
        Mockito.verify(item).removeItemListener(Matchers.any(ItemListener.class));
        Mockito.verify(itm).removeVariableValueListener(Matchers.any(VariableValueListener.class));
        Mockito.verify(remoteClient).receiveServerDisconnectEvent(Matchers.any(MessageEvent.class));
    }

    @Test
    public void test_disconnectClient_raiseException_verifiesTraceException() throws Exception {

        // Arrange
        Exception ex = Mockito.mock(Exception.class);
        Item item = Mockito.mock(ItemImpAccessStub.class);

        Hashtable itemEventSources = new Hashtable();
        itemEventSources.put(item, "test");

        Whitebox.setInternalState(g2serverQueueManager, "connectionListening", true);
        Whitebox.setInternalState(g2serverQueueManager, "itemEventSources", itemEventSources);

        Mockito.doThrow(G2AccessException.class).when(item).removeItemListener(Matchers.any(ItemListener.class));

        PowerMockito.mockStatic(Trace.class);

        Mockito.doThrow(Exception.class).when(ex).printStackTrace(Matchers.any(PrintWriter.class));
        Mockito.doThrow(Exception.class).when(remoteClient).receiveServerDisconnectEvent(Matchers.any(MessageEvent.class));

        // Act
        g2serverQueueManager.disconnectClient(ex);

        // Assert
        PowerMockito.verifyStatic(Mockito.times(4));
        Trace.exception(Matchers.any(Exception.class));
    }

    @Test
    public void test_processQueue_onCall_verifiesRemoteClientCall() throws Exception {

        // Arrange
        Vector queueCopy = new Vector();

        PowerMockito.mockStatic(Trace.class);

        // Act
        g2serverQueueManager.processQueue(queueCopy);

        // Assert
        Mockito.verify(remoteClient).processEventQueue(queueCopy);
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq("sqmrun1"), Matchers.any());
    }

    @Test
    public void test_processQueue_ConnectException_verifiesTraceException() throws Exception {

        // Arrange
        Vector queueCopy = new Vector();

        PowerMockito.mockStatic(Trace.class);

        Mockito.doThrow(ConnectException.class).when(remoteClient).processEventQueue(queueCopy);

        // Act
        g2serverQueueManager.processQueue(queueCopy);

        // Assert
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq("sqmrun1"), Matchers.any());
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class), Matchers.eq("sqmrun2"), Matchers.any());
        PowerMockito.verifyStatic();
        Trace.exception(Matchers.any(Exception.class));
        Mockito.verify(remoteClient).receiveServerDisconnectEvent(Matchers.any(MessageEvent.class));
    }

    @Test
    public void test_processQueue_NotError_verifiesWarnServer() throws Exception {

        // Arrange
        String sqmrun = "sqmrun6";
        Throwable detail = Mockito.mock(Exception.class);

        // Act & Assert
        testProcessQueueVerifiesOnRaiseException(sqmrun, detail);
    }

    @Test
    public void test_processQueue_Error_verifiesWarnServer() throws Exception {

        // Arrange
        String sqmrun = "sqmrun5";
        Throwable detail = Mockito.mock(Error.class);

        // Act & Assert
        testProcessQueueVerifiesOnRaiseException(sqmrun, detail);
    }

    @Test
    public void test_processQueue_LoopProcessingException_verifiesWarnServer() throws Exception {

        // Arrange
        String sqmrun = "sqmrun4";
        LoopProcessingException loopEx = Mockito.mock(LoopProcessingException.class);

        // Act
        testProcessQueueVerifiesOnRaiseException(sqmrun, loopEx);

        // Assert
        Mockito.verify(loopEx).printFullStackTrace(Matchers.any(PrintWriter.class));
    }

    @Test
    public void test_deleteInstance_onCall_addEvent() throws Exception {

        // Arrange
        G2JavaStubControllerEvent e = Mockito.mock(G2JavaStubControllerEvent.class);

        PowerMockito.mockStatic(Trace.class);

        // Act
        g2serverQueueManager.deleteInstance(e);

        // Assert
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class)
                , Matchers.eq("vqmaddEvent"), Matchers.anyObject(), Matchers.anyObject());
    }

    @Test
    public void test_callMethod_trueRunning_addEvent() throws Exception {

        // Arrange
        G2JavaStubControllerEvent e = Mockito.mock(G2JavaStubControllerEvent.class);

        g2serverQueueManager.setRunning(true);

        PowerMockito.mockStatic(Trace.class);

        // Act
        g2serverQueueManager.callMethod(e);

        // Assert
        PowerMockito.verifyStatic();
        Trace.send(Matchers.eq(30), Matchers.any(MessageKey.class), Matchers.any(Resource.class)
                , Matchers.eq("vqmaddEvent"), Matchers.anyObject(), Matchers.anyObject());
    }

    @Test (expected = ConnectionNotAvailableException.class)
    public void test_callMethod_falseRunning_throwsConnectionNotAvailableException() throws Exception {

        // Arrange
        G2JavaStubControllerEvent e = Mockito.mock(G2JavaStubControllerEvent.class);

        Whitebox.setInternalState(g2serverQueueManager, "running", false);

        // Act
        g2serverQueueManager.callMethod(e);
    }
}
