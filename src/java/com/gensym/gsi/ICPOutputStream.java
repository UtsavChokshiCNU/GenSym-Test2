
package com.gensym.gsi;

import java.util.*;
import java.io.*;

public class ICPOutputStream extends ICPStream {
    OutputStream strm;
    BufferedOutputStream bstrm;    
    boolean bstrm_in_use = false;
    Queue messageSeriesList = new Queue();
    ByteArrayOutputStream currentMessageSeriesStream = null;

    ICPOutputStream(ICPSocket sck, OutputStream strm) {
	this.sck = sck;
	this.strm = strm;
	this.bstrm = new BufferedOutputStream(strm);
    }

    private void basicWriteICPByte(short b) throws IOException {
	bstrm_in_use = true;
	bstrm.write(b>>8);
	bstrm.write(b&0xff);
    }

    void basicWriteMessageSeries(ByteArrayOutputStream messageSeriesStream)
	throws IOException {
	if (messageSeriesStream == null)
	    basicWriteICPByte((short)1);
	else {
	    int size = messageSeriesStream.size()+1;
	    if (size > 0xffff) throw new IOException();
	    basicWriteICPByte((short)size);
	    if (size > 64) {
		bstrm.flush();
		bstrm_in_use = false;
		messageSeriesStream.writeTo(strm);
	    } else
		messageSeriesStream.writeTo(bstrm);
	}
    }

    @Override
    public void run () {
	try {
	    while (true) {
		ByteArrayOutputStream messageSeries 
		    = (ByteArrayOutputStream)(messageSeriesList.getNextMessage());
		basicWriteMessageSeries(messageSeries);
		if (!messageSeriesList.nextMessageAvailable() && bstrm_in_use)
		    bstrm.flush();
	    }
	} catch (IOException e) {}
	try {close();}
	catch (IOException e) {}
    }

    public void close () throws IOException {
	strm.close();
    }



    void startMessageGroup() {
	currentMessageSeriesStream = null;
    }

    void writeMessageSeries() {
	messageSeriesList.enqueueMessage(currentMessageSeriesStream);
	currentMessageSeriesStream = null;
    }

    public void endICPMessageGroup () throws IOException {
	if (currentMessageSeriesStream != null &&
	    currentMessageSeriesStream.size() > 0) {
	    messageSeriesList.enqueueMessage(currentMessageSeriesStream);
	}
	messageSeriesList.enqueueMessage(null);
	currentMessageSeriesStream = null;
    }

    public void writeICPByte(short b) throws IOException {
	if (currentMessageSeriesStream == null)
	    currentMessageSeriesStream = new ByteArrayOutputStream();
	else if (currentMessageSeriesStream.size() > (63000 - 2048))
	    writeMessageSeries();
	currentMessageSeriesStream.write(b>>8);
	currentMessageSeriesStream.write(b&0xff);
    }

    public void writeICPBoolean (boolean b) throws IOException {
	writeICPByte((short)(b?1:0));
    }

    private void writeICPLargeInteger (int i) throws IOException {
	if (i<-536870912 || i>536870911)
	    throw new InvalidICPInteger(i);
	boolean negative = i<0;
	if (negative) i = -i;
	short upperBits = (short)((i>>15)&0x7fff);
	short lowerBits = (short)(i&0x7fff);
	if (upperBits == 0) {
	    writeICPByte((short)(1 + 63000 + (negative?500:0)));
	    writeICPByte(lowerBits);
	} else {
	    writeICPByte((short)(2 + 63000 + (negative?500:0)));
	    writeICPByte(upperBits);
	    writeICPByte(lowerBits);
	}
    }
	    
    public void writeICPUnsignedInteger (int i) throws IOException {
	if ( i < 0 )
	    throw new InvalidICPInteger(i);
	if ( i <= 63000 )
	    writeICPByte((short)i);
	else
	    writeICPLargeInteger(i);
    }

    public void writeICPInteger (int i) throws IOException {
	if ( i >= -63000/2 && i <= 63000/2 )
	    writeICPByte((short)(i + 63000/2));
	else
	    writeICPLargeInteger(i);
    }

    public void writeICPString (String s) throws IOException {
	int length = s.length();
	writeICPUnsignedInteger(length);
	for ( int i=0; i<length; i++ ) {
	    writeICPByte((short)(s.charAt(i)));
	}
    }

    public void writeICPGensymString (String s) throws IOException {
	int length = s.length();
	writeICPUnsignedInteger(length);
	int even_length = length & ~1;
	int i=0;
	for ( ; i<even_length; )
	    writeICPByte((short)(((s.charAt(i++)&0xff)<<8) +
				 (s.charAt(i++)&0xff)));
	if (i < length) 
	    writeICPByte((short)(s.charAt(i++)&0xff));
    }

    public void writeICPByteArray (short[] s) throws IOException {
	int length = s.length;
	writeICPUnsignedInteger(length);
	for ( int i=0; i<length; i++ ) {
	    writeICPByte(s[i]);
	}
    }

    public void writeICPByteArrayAsCharArray (char[] s) throws IOException {
	int length = s.length;
	writeICPUnsignedInteger(length);
	for ( int i=0; i<length; i++ ) {
	    writeICPByte((short)s[i]);
	}
    }

    public void writeICPDouble (double d) throws IOException {
	long bits = Double.doubleToLongBits(d);
	writeICPByte((short)(bits>>48));
	writeICPByte((short)((bits>>32)&0xffff));
	writeICPByte((short)((bits>>16)&0xffff));
	writeICPByte((short)(bits&0xffff));
    }

    public void writeICPMessage(ICPMessage m) throws IOException {
	synchronized (standardIndexSpace) {
	    m.write(this);
	}
    }

}
