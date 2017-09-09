package com.gensym.G2SNMP.trapd;

import java.io.*;
import com.gensym.G2SNMP.JsnmpBridge;
import com.adventnet.snmp.snmp2.*;
import java.util.Vector;
import java.util.Enumeration;
import java.net.InetAddress;


/**
   This class implements a file-based FIFO buffer for graceful logging.
*/

public class TrapBuffer {
    protected int size;
    protected boolean dirty;
    protected static volatile SnmpAPI snmpApi;
    protected File file;
    protected DataOutputStream out;
    protected DataInputStream in;

    /**
       This method adds a given SnmpPDU to the end of the file.
       @roseuid 3678BB480113
     */
    public synchronized void addElement(SnmpPDU pdu) throws BufferIOException {

        JsnmpBridge.debugOut("TrapBuffer.addElement(pdu)");

        try {
            writePDU(pdu);
            size++;
            dirty = true;
        } catch (IOException e) {
            throw new BufferIOException("TrapBuffer.addElement(): " + e.toString());
        }

    }

    /**
       This method flushes the first <capacity> elements from the buffer file
       (or less, depending on the file size) to the specified vector.
       @roseuid 3678BB48011C
     */
    public synchronized int flushTo(Vector vector, int capacity) throws BufferIOException {

        int i = 0;

        vector.removeAllElements();
        try {
            out.flush();
            for (i = 0; i < capacity; i++) {
                JsnmpBridge.debugOut("TrapBuffer.flushTo(): reading item " + i);
                SnmpPDU pdu = readPDU();
                vector.addElement(pdu);
                size--;
            }
        } catch (EOFException e) {
            JsnmpBridge.debugOut("TrapBuffer.flushTo(): out of items");
            if (dirty)
                resetBuffer();
            return i;
        } catch (IOException e) {
            throw new BufferIOException("TrapBuffer.flushTo(): " + e.toString());
        }

        if (size == 0) {
            JsnmpBridge.debugOut("TrapBuffer.flushTo(): out of items");
            if (dirty)
                resetBuffer();
        }

        return i;
    }

    /**
       This method returns the number of elements stored in the file.
       @roseuid 3678BB48011F
     */
    public synchronized int size() {
        return size;
    }

    /**
       This method empties the buffer.
       @roseuid 3678BB480120
     */
    public synchronized void removeAllElements() throws BufferIOException {
        resetBuffer();
    }

    /**
       This constructor creates a file to store incoming PDUs.
       @roseuid 3678BB480125
     */
    public TrapBuffer(SnmpAPI api) throws BufferIOException {

    	snmpApi = api; // static field, should be the same for all instances
		file = new File(new File("."), "traps.tmp");
        resetBuffer();

    }

    /**
       @roseuid 3678BB480127
     */
    protected synchronized void resetBuffer() throws BufferIOException {
        try {
            JsnmpBridge.debugOut("TrapBuffer.resetBuffer()");
            if (out != null) {
                out.close();
            }
            if (in != null)
                in.close();
        } catch (IOException e) {
            JsnmpBridge.debugOut("TrapBuffer.resetBuffer(): " + e.toString());
            // no need to throw exceptions here
        }
        try {
            out = new DataOutputStream(new FileOutputStream(file));
            in = new DataInputStream(new FileInputStream(file));
        } catch (IOException e) {
            // fatal: failed to create one of the streams
            throw new BufferIOException("TrapBuffer.resetBuffer(): " + e.toString());
        }
        size = 0;
        dirty = false;
    }

    /**
       @roseuid 3678BB480128
     */
    protected void finalize() {
        try {
            in.close();
            out.close();
            file.delete();
            JsnmpBridge.debugOut("TrapBuffer.finalize(): ok");
        } catch (IOException e) {
            JsnmpBridge.debugOut("TrapBuffer.finalize(): " + e.toString());
        }
    }

    protected void writeString(String string) throws IOException {
        if (string == null)
            out.writeByte(0);
        else {
            out.writeByte(1);
            out.writeUTF(string);
        }
    }

    protected String readString() throws IOException {
        byte flag = in.readByte();
        if (flag == 0)
            return null;
        else
            return in.readUTF();
    }

    protected void writeByteArray(byte[] bytes) throws IOException {
        if (bytes == null)
            out.writeInt(-1);
        else {
            int len = bytes.length;
            out.writeInt(len);
            out.write(bytes, 0, len);
        }
    }

    protected byte[] readByteArray() throws IOException {
        int len = in.readInt();
        if (len == -1)
            return null;
        else {
            byte[] bytes = new byte[len];
            in.read(bytes, 0, len);
            return bytes;
        }
    }

    protected void writeInetAddress(InetAddress iAddr) throws IOException {

        if (iAddr == null)
            out.writeByte(0);
        else {
            out.writeByte(1);
            byte[] addr = iAddr.getAddress();
            out.writeByte(addr[0]);
            out.writeByte(addr[1]);
            out.writeByte(addr[2]);
            out.writeByte(addr[3]);
        }

    }

    protected InetAddress readInetAddress() throws IOException {

        byte flag = in.readByte();
        if (flag == 0)
            return null;
        else {
            byte b1 = in.readByte();
            byte b2 = in.readByte();
            byte b3 = in.readByte();
            byte b4 = in.readByte();
            return InetAddress.getByName(
                ((int)b1 & 0xFF) + "." +
                ((int)b2 & 0xFF) + "." +
                ((int)b3 & 0xFF) + "." +
                ((int)b4 & 0xFF));
        }

    }

    protected void writePDU(SnmpPDU pdu) throws IOException {

        //APIv4
        UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();

        // APIv3->writeInetAddress(pdu.getAddress());
        writeInetAddress(opt.getRemoteAddress());
        //APIv3->writeString(pdu.getRemoteHost());
        writeString(opt.getRemoteHost());
        //APIv3->out.writeInt(pdu.getRemotePort());
        out.writeInt(opt.getRemotePort());
        out.writeByte(pdu.getCommand());
        out.writeInt(pdu.getReqid());
        out.writeInt(pdu.getErrstat());
        out.writeInt(pdu.getErrindex());

        writeOID(pdu.getEnterprise());

        writeInetAddress(pdu.getAgentAddress());
        out.writeInt(pdu.getTrapType());
        out.writeInt(pdu.getSpecificType());
        out.writeLong(pdu.getUpTime());

        out.writeInt(pdu.getVariableBindings().size());
        for (Enumeration e = pdu.getVariableBindings().elements(); e.hasMoreElements(); ) {
            SnmpVarBind varbind = (SnmpVarBind)e.nextElement();
            writeVarBind(varbind);
        }

        writeString(pdu.getCommunity());
        writeString(pdu.getWriteCommunity());
        out.writeInt(pdu.getTimeout());
        out.writeInt(pdu.getRetries());
        writeByteArray(pdu.getData());
        out.writeInt(pdu.getVersion());
    }

    protected SnmpPDU readPDU() throws IOException {

        SnmpPDU pdu = new SnmpPDU();

        //APIv4
        UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();

        //APIv3->pdu.setAddress(readInetAddress());
        opt.setRemoteAddress(readInetAddress());
        //APIv3->pdu.setRemoteHost(readString());
        opt.setRemoteHost(readString());
        //APIv3->pdu.setRemotePort(in.readInt());
        opt.setRemotePort(in.readInt());
        pdu.setCommand(in.readByte());
        pdu.setReqid(in.readInt());
        pdu.setErrstat(in.readInt());
        pdu.setErrindex(in.readInt());

        pdu.setEnterprise(readOID());

        pdu.setAgentAddress(readInetAddress());
        pdu.setTrapType(in.readInt());
        pdu.setSpecificType(in.readInt());
        pdu.setUpTime(in.readLong());

        int pduSize = in.readInt();

        for (int i = 0; i < pduSize; i++) {
            pdu.addVariableBinding(readVarBind());
        }

        pdu.setCommunity(readString());
        pdu.setWriteCommunity(readString());
        pdu.setTimeout(in.readInt());
        pdu.setRetries(in.readInt());
        pdu.setData(readByteArray());
        pdu.setVersion(in.readInt());

        return pdu;

    }

    protected void writeVarBind(SnmpVarBind snmpVarBind) throws IOException {

        writeOID(snmpVarBind.getObjectID());
        writeVar(snmpVarBind.getVariable());
        out.writeInt(snmpVarBind.getErrindex());

    }

    protected SnmpVarBind readVarBind() throws IOException {

        SnmpVarBind snmpVarBind = new SnmpVarBind(readOID(), readVar());
        return snmpVarBind;

    }

    protected void writeOID(SnmpOID oid) throws IOException {

        out.writeUTF(oid.toString());

    }

    protected SnmpOID readOID() throws IOException {

        return new SnmpOID(in.readUTF());

    }

    protected void writeVar(SnmpVar snmpVar) throws IOException {

        out.writeByte(snmpVar.getType());

        switch (snmpVar.getType()) {
            case SnmpAPI.INTEGER:
                out.writeInt(((SnmpInt)snmpVar).intValue());
                break;
            case SnmpAPI.STRING:
            case SnmpAPI.OPAQUE:
                writeByteArray(((SnmpString)snmpVar).toBytes());
                break;
            case SnmpAPI.OBJID:
            case SnmpAPI.IPADDRESS:
                out.writeUTF(snmpVar.toString());
                break;
            case SnmpAPI.COUNTER64:
                long[] value = (long[])(((SnmpCounter64)snmpVar).toValue());
                out.writeLong(value[0]);
                out.writeLong(value[1]);
                break;
            case SnmpAPI.COUNTER:
            case SnmpAPI.UNSIGNED32:
            case SnmpAPI.TIMETICKS:
                out.writeLong(((SnmpUnsignedInt)snmpVar).longValue());
                break;
            case SnmpAPI.NULLOBJ:
            default:
                break;
        }

    }

    protected SnmpVar readVar() throws IOException {

        SnmpVar snmpVar = null;

        byte type = in.readByte();

        switch (type) {
            case SnmpAPI.INTEGER:
                snmpVar = new SnmpInt(in.readInt());
                break;
            case SnmpAPI.STRING:
                snmpVar = new SnmpString(readByteArray());
                break;
            case SnmpAPI.NULLOBJ:
                snmpVar = new SnmpNull();
                break;
            case SnmpAPI.OBJID:
                snmpVar = new SnmpOID(in.readUTF());
                break;
            case SnmpAPI.IPADDRESS:
                snmpVar = new SnmpIpAddress(in.readUTF());
                break;
            case SnmpAPI.COUNTER64:
                long[] value = new long[2];
                value[0] = in.readLong();
                value[1] = in.readLong();
                snmpVar = new SnmpCounter64(value);
                break;
            case SnmpAPI.COUNTER:
                snmpVar = new SnmpCounter(in.readLong());
                break;
            case SnmpAPI.UNSIGNED32:
                snmpVar = new SnmpUnsignedInt(in.readLong());
                break;
            case SnmpAPI.TIMETICKS:
                snmpVar = new SnmpTimeticks(in.readLong());
                break;
            case SnmpAPI.OPAQUE:
                snmpVar = new SnmpOpaque(readByteArray());
                break;
            default:
                System.err.println("Warning (trap buffer): failed to create SNMP variable");
                break;
        }

        return snmpVar;

    }

}
