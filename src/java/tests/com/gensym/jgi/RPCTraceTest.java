package com.gensym.jgi;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.CharArrayWriter;
import java.util.Vector;
import org.junit.*;
import static org.junit.Assert.*;
import com.gensym.util.Symbol;

/**
 * RPCTrace Tester.
 *
 * @author Chaitanya Deepti
 * @since <pre>May 23, 2017</pre>
 * @version 1.0
 */
public class RPCTraceTest {
    /**
     * Run the RPCTrace() constructor test.
     */
    @Test
    public void testRPCTrace() {

        RPCTrace result = new RPCTrace();
        assertNotNull(result);
    }
    /**
     * Run the void emptyDataStorage() method test.
     */
    @Test(expected = Exception.class)
    public void testEmptyDataStorage() throws Exception {
        RPCTrace fixture = new RPCTrace();
        RPCTrace.emptyDataStorage();
        fixture.getRPCEntryByIndex(1);
    }
    /**
     * Run the Vector getAllRPCTraceEntry() method test.
     */
    @Test
    public void testGetAllRPCTraceEntry() {
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        RPCTrace fixture = new RPCTrace();
        Vector result = fixture.getAllRPCTraceEntry();
        assertNotNull(result);
        assertEquals(1, result.size());
    }

    /**
     * Run the long getRPCAverageDuration() method test.
     */
    @Test
    public void testGetRPCAverageDuration() {
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        long result = RPCTrace.getRPCAverageDuration();
        assertEquals(1, result);
    }
    /**
     * Run the long getRPCAverageDuration() method test.
     */
    @Test
    public void testGetRPCAverageDurationEmpty() {
        RPCTrace.emptyDataStorage();
        long result = RPCTrace.getRPCAverageDuration();
        assertEquals(0, result);
    }
    /**
     * Run the RPCTraceEntry getRPCEntryByIndex(int) method test.
     */
    @Test(expected = Exception.class)
    public void testGetRPCEntryByIndexException() throws Exception {
        RPCTrace.emptyDataStorage();
        int index = 5;
        RPCTraceEntry result = RPCTrace.getRPCEntryByIndex(index);
        assertNotNull(result);
    }
    /**
     * Run the RPCTraceEntry getRPCEntryByIndex(int) method test.
     */
    @Test
    public void testGetRPCEntryByIndex() throws Exception {
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        int index = 0;
        RPCTraceEntry result = RPCTrace.getRPCEntryByIndex(index);
        assertNotNull(result);
    }
    /**
     * Run the Vector getRPCProcedureByName(String) method test.
     */
    @Test
    public void testGetRPCProcedureByName() {
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        Vector result = RPCTrace.getRPCProcedureByName("Test");
        assertNotNull(result);
        assertEquals(1, result.size());
    }
    /**
     * Run the Vector getRPCProcedureWithMaxDuration() method test.
     */
    @Test
    public void testGetRPCProcedureWithMaxDuration() {
        RPCTrace.emptyDataStorage();
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        addRPCTraceData("Test", new Object[]{}, 2L);
        addRPCTraceData("Test", new Object[]{}, 4L);
        Vector result = RPCTrace.getRPCProcedureWithMaxDuration();
        assertEquals(1, result.size());
        assertEquals(4, ((RPCTraceEntry) result.get(0)).getDuration());
    }
    /**
     * Run the Vector getRPCProcedureWithMaxDuration() method test.
     */
    @Test
    public void testGetRPCProcedureWithMaxDurationEmpty() {
        RPCTrace.emptyDataStorage();
        Vector result = RPCTrace.getRPCProcedureWithMaxDuration();
        assertNull(result);
    }
    /**
     * Run the Vector getRPCProcedureWithMinDuration() method test.
     */
    @Test
    public void testGetRPCProcedureWithMinDuration() {
        RPCTrace.emptyDataStorage();
        addRPCTraceData("Test", new Object[]{}, 1L);
        addRPCTraceData("Test", new Object[]{}, 2L);
        addRPCTraceData("Test", new Object[]{}, 3L);
        Vector result = RPCTrace.getRPCProcedureWithMinDuration();
        assertEquals(1, result.size());
        assertEquals(1, ((RPCTraceEntry) result.get(0)).getDuration());
    }
    /**
     * Run the Vector getRPCProcedureWithMinDuration() method test.
     */
    @Test
    public void testGetRPCProcedureWithMinDurationEmpty() {
        RPCTrace.emptyDataStorage();
        Vector result = RPCTrace.getRPCProcedureWithMinDuration();
        assertNull(result);
    }
    /**
     * Run the boolean isEmptyDataOn() method test.
     */
    @Test
    public void testIsEmptyDataOn() {
        boolean on = true;
        RPCTrace.setEmptyDataOn(on);
        boolean result = RPCTrace.isEmptyDataOn();
        assertEquals(true, result);
    }
    /**
     * Run the boolean isReportOn() method test.
     */
    @Test
    public void testIsReportOn() {
        boolean on = true;
        RPCTrace.setReportOn(on);
        boolean result = RPCTrace.isReportOn();
        assertEquals(true, result);
    }
    /**
     * Run the boolean isStackOn() method test.
     */
    @Test
    public void testIsStackOn() {
        boolean on = true;
        RPCTrace.setStackOn(on);
        boolean result = RPCTrace.isStackOn();
        assertEquals(true, result);
    }
    /**
     * Run the boolean isTraceOn() method test.
     */
    @Test
    public void testIsTraceOn() {
        boolean on = true;
        RPCTrace.setTraceOn(on);
        boolean result = RPCTrace.isTraceOn();
        assertEquals(true, result);
    }
    /**
     * Run the void writeOutGeneralReport(BufferedWriter,boolean) method test.
     */
    @Test
    public void testWriteOutGeneralReport() throws Exception {
        addRPCTraceData("Test", new Object[]{}, 1L);
        BufferedWriter buff = new BufferedWriter(new CharArrayWriter());
        boolean includeStack = true;
        RPCTrace.writeOutGeneralReport(buff, includeStack);
        assertNotNull(buff);
    }
    /**
     * Run the void writeOutSummaryReport(BufferedWriter) method test.
     */
    @Test
    public void testWriteOutSummaryReport() throws Exception {
        addRPCTraceData("Test", new Object[]{}, 1L);
        BufferedWriter buff = new BufferedWriter(new CharArrayWriter());
        RPCTrace.writeOutSummaryReport(buff);
        assertNotNull(buff);
    }
    /**
     * Run the void writeOutSummaryReport(BufferedWriter) method test.
     */
    @Test(expected = NullPointerException.class)
    public void testWriteOutSummaryReportNull() throws Exception {
        RPCTrace.emptyDataStorage();
        BufferedWriter buff = new BufferedWriter(new CharArrayWriter());
        RPCTrace.writeOutSummaryReport(buff);
    }
    /**
     * Run the void writeReportToBuffer(BufferedWriter) method test.
     */
    @Test
    public void testWriteReportToBuffer() throws Exception {
        BufferedWriter buff = new BufferedWriter(new CharArrayWriter());
        RPCTrace.writeReportToBuffer(buff);
        assertNotNull(buff);
    }
    /**
     * Run the void writeReportToBuffer(BufferedWriter) method test.
     */
    @Test
    public void testWriteReportToBufferException() throws Exception {
        RPCTrace.emptyDataStorage();
        BufferedWriter buff = new BufferedWriter(new CharArrayWriter());
        RPCTrace.writeReportToBuffer(buff);
        assertNotNull(buff);
    }
    public void addRPCTraceData(String pName, Object[] obj, long duration) {
        RPCTrace.addRPCTraceData(Symbol.intern(pName), obj, duration);
    }
}