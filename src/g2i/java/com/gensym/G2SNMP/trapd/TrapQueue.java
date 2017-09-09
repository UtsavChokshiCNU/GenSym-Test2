package com.gensym.G2SNMP.trapd;

import com.adventnet.snmp.snmp2.SnmpPDU;
import java.util.Vector;
import com.gensym.G2SNMP.JsnmpBridge;
import com.adventnet.snmp.snmp2.SnmpAPI;

/**
   This class implements graceful logging of incoming traps. FIFO buffer.
*/
class TrapQueue {
    /**
       This is the capacity of the buffer cache (how
       many PDUs we can hold in memory in buffered mode).
     */
    private int cacheCapacity;
    /**
       Specifies the maximum number of PDUs to store
       in non-buffered mode. Any PDUs exceeding this number
       will be rejected.
     */
    private static final int maximumCacheCapacity = 18000;
    /**
       Specifies the number of PDUs to be retrieved from the buffer at a time.
    */
    private static final int batchSize = 20;
    /**
       The number of PDUs that have been lost due to the last cache overflow.
       (For non-buffered mode only)
     */
    private int lostPDUs;
    private boolean isBuffered;
    private Vector vector;
    private TrapBuffer buffer;

    /**
       This method adds the given SnmpPDU to the end of the queue.
       @roseuid 365A74E00027
     */
    public synchronized void putLast(SnmpPDU pdu) {

        JsnmpBridge.debugOut("TrapQueue.putLast(pdu)");

        if (isBuffered) {
            if (vector.size() == cacheCapacity)
                try {
                    buffer.addElement(pdu);
                } catch (BufferIOException e) {
                    System.err.println("Warning (trap queue): can't add PDU");
                    JsnmpBridge.debugOut(e.toString());
                }
            else
                vector.addElement(pdu);
        } else {
            if (vector.size() < maximumCacheCapacity) {
                vector.addElement(pdu);
                if (lostPDUs > 0) {
                    System.err.println("Warning (trap queue): " + lostPDUs + " PDU(s) lost due to buffer overflow, continuing normally");
                    lostPDUs = 0;
                }
            } else {
                if (lostPDUs == 0) {    // first time rejecting a PDU
                    System.err.println("Warning (trap queue): buffer overflow detected, PDU rejected");
                }
                lostPDUs++;
            }
        }

    }

    /**
       This method should retrieve the first PDU from the queue.
       @roseuid 365A7562007E
     */
    public synchronized SnmpPDU getFirst() throws ArrayIndexOutOfBoundsException {

        JsnmpBridge.debugOut("TrapQueue.getFirst()");

        if ((vector.isEmpty()) && isBuffered) {
            try {
                buffer.flushTo(vector, batchSize);
            } catch (BufferIOException e) {
                System.err.println("Warning (trap queue): can't read trap buffer");
                JsnmpBridge.debugOut(e.toString());
            }
        }
        SnmpPDU pdu = (SnmpPDU)vector.elementAt(0);
        vector.removeElementAt(0);
        return pdu;

    }

    /**
       Returns the number of elements in the queue.
       @roseuid 365A75BC033A
     */
    public synchronized int getCount() {
        return vector.size() + (isBuffered ? buffer.size() : 0);
    }

    /**
       This method should empty the queue.
       @roseuid 365AD4F3018B
     */
    public synchronized void clear() {

        JsnmpBridge.debugOut("TrapQueue.clear()");

        vector.removeAllElements();
        if (isBuffered) {
            try {
                buffer.removeAllElements();
            } catch (BufferIOException e) {
                System.err.println("Warning (trap queue): can't clear trap buffer");
                JsnmpBridge.debugOut(e.toString());
            }
        }

    }

    /**
       This constructor should create FIFO buffer for PDUs.
       @roseuid 365D3305004D
     */
    public TrapQueue(int capacity, SnmpAPI snmpApi, boolean buffered) {
        cacheCapacity = capacity;
        lostPDUs = 0;
        vector = new Vector(capacity);
        try {
            buffer = buffered ? new TrapBuffer(snmpApi) : null;
            isBuffered = buffered;
        } catch (BufferIOException e) {
            isBuffered = false;
            System.err.println("Warning (trap queue): can't create trap buffer");
            JsnmpBridge.debugOut(e.toString());
        }
        if (isBuffered)
            JsnmpBridge.stateOut("Trap queue: buffered mode, cache size: " + cacheCapacity);
        else {
            JsnmpBridge.stateOut("Trap queue: non-buffered mode, maximum allowable traps in queue: " + maximumCacheCapacity);
        }
    }

    /**
       @roseuid 3678BB430218
     */
    public TrapQueue(int capacity, SnmpAPI snmpApi) {
        this(capacity, snmpApi, true);
    }
}
