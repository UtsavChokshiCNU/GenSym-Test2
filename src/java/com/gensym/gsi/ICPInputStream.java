
package com.gensym.gsi;

import java.util.*;
import java.io.*;

public class ICPInputStream extends ICPStream {
    private Map map;
    InputStream strm;
    Queue messages = new Queue();
    private int bytesRemainingInMessageSeries = -1;
    private int nextICPByte = -1;

    ICPInputStream(ICPSocket sck, Map map, InputStream strm) {
	this.sck = sck;
	this.map = map;
	this.strm = new BufferedInputStream(strm);
    }

    short basicReadICPByte() throws IOException {
	if (nextICPByte >= 0) {
	    int result = nextICPByte;
	    nextICPByte = -1;
	    return (short)result;
	} else
	    return (short)((strm.read()<<8)+strm.read());
    }

    short basicPeekICPByte() throws IOException {
	if (nextICPByte == -1)
	    nextICPByte = (strm.read()<<8)+strm.read();
	return (short)nextICPByte;
    }

    void beginICPMessageGroup() throws IOException {
	if (bytesRemainingInMessageSeries == -1)
	    bytesRemainingInMessageSeries = basicReadICPByte()-1;
	else
	    throw new ICPOutOfSynch(1);
    }

    public void readICPMessageGroupEnd () throws IOException {
	if (nextICPByte == -1) {
	    if (bytesRemainingInMessageSeries == -1)
		throw new ICPOutOfSynch(2);
	    if (bytesRemainingInMessageSeries == 0) {
		bytesRemainingInMessageSeries = basicReadICPByte()-1;
		if (bytesRemainingInMessageSeries != 0)
		    throw new ICPOutOfSynch(3);
	    }
	} else
	    throw new ICPOutOfSynch(4);
    }

    public short peekICPByte() throws IOException {
	if (nextICPByte == -1) {
	    if (bytesRemainingInMessageSeries == -1)
		throw new ICPOutOfSynch(5);
	    if (bytesRemainingInMessageSeries == 0) {
		bytesRemainingInMessageSeries = basicReadICPByte()-1;
		if (bytesRemainingInMessageSeries == 0)
		    throw new ICPOutOfSynch(6);
	    }
	    bytesRemainingInMessageSeries--;
	}
	return basicPeekICPByte();
    }

    public short readICPByte() throws IOException {
	if (nextICPByte == -1) {
	    if (bytesRemainingInMessageSeries == -1)
		throw new ICPOutOfSynch(7);
	    if (bytesRemainingInMessageSeries == 0) {
		bytesRemainingInMessageSeries = basicReadICPByte()-1;
		if (bytesRemainingInMessageSeries == 0)
		    throw new ICPOutOfSynch(8);
	    }
	    bytesRemainingInMessageSeries--;
	}
	return basicReadICPByte();
    }

    public boolean readICPBoolean () throws IOException {
	switch (readICPByte()) {
	case 0: return false;
	case 1: return true;
	default: throw new ICPOutOfSynch(9);
	}
    }

    private int readICPLargeInteger (int firstByte) throws IOException {
	firstByte -= 63000;
	boolean negative = firstByte > 500;
	if (negative) firstByte -= 500;
	if (firstByte == 3) 
	    return -536870912;
	else if (firstByte == 2) {
	    int num = readICPByte()>>15 + readICPByte();
	    return negative?(-num):num;
	} else {
	    int num = readICPByte();
	    return negative?-num:num;
	}
    }
	    
    public int readICPUnsignedInteger () throws IOException {
	int firstByte = readICPByte();
	if (firstByte > 63000)
	    return readICPLargeInteger(firstByte);
	else
	    return firstByte;
    }

    public int readICPInteger () throws IOException {
	int firstByte = readICPByte();
	if (firstByte > 63000)
	    return readICPLargeInteger(firstByte);
	else
	    return firstByte - 63000/2;
    }

    public String readICPString () throws IOException {
	int length = readICPUnsignedInteger();
	StringBuffer buffer = new StringBuffer(length);
	for ( int i=0; i<length; i++ ) {
	    buffer.setCharAt(i,(char)readICPByte());
	}
	return buffer.toString();
    }

    public String readICPGensymString () throws IOException {
	int length = readICPUnsignedInteger();
	StringBuffer buffer = new StringBuffer(length);
	int even_length = length & ~1;
	int i=0;
	for ( ; i < even_length; ) {
	    int icpbyte = readICPByte();
	    buffer.setCharAt(i++,(char)(icpbyte >> 8));
	    buffer.setCharAt(i++,(char)(icpbyte & 0xff));
	}
	if (i < length) {
	    int icpbyte = readICPByte();
	    buffer.setCharAt(i++,(char)(icpbyte & 0xff));
	}
	return buffer.toString();
    }

    public short[] readICPByteArray () throws IOException {
	int length = readICPUnsignedInteger();
	short[] buffer = new short[length];
	for ( int i=0; i<length; i++ ) {
	    buffer[i] = readICPByte();
	}
	return buffer;
    }

    public char[] readICPByteArrayAsCharArray () throws IOException {
	int length = readICPUnsignedInteger();
	char[] buffer = new char[length];
	for ( int i=0; i<length; i++ ) {
	    buffer[i] = (char)readICPByte();
	}
	return buffer;
    }

    public double readICPDouble () throws IOException {
	return Double.longBitsToDouble((readICPByte()<<48)+
				       (readICPByte()<<32)+
				       (readICPByte()<<16)+
				       readICPByte());
    }

    private void internalReadICPMessage() throws IOException {
	Class messageClass = (Class)(map.get(new Short(readICPByte())));
	if (messageClass == null) throw new ICPOutOfSynch(7);
	ICPMessage message = null;
	try {message = (ICPMessage)(messageClass.newInstance());}
	catch (Exception e) {throw new ICPOutOfSynch(8);}
	message.read(this);
	messages.enqueueMessage(message);
    }

    public ICPMessage readICPMessage() {
	return (ICPMessage)(messages.getNextMessage());
    }

    @Override
    public void run () {
	try {
	    while (true) {
		internalReadICPMessage();
	    }
	} catch (IOException e) {}
	try {close();}
	catch (IOException e) {}
    }

    public void close () throws IOException {
	strm.close();
    }
}
