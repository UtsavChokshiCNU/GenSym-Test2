/*
 * @(#)G2BinaryInputStream.java 97/9/27
 * 
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */

package com.gensym.util;

import java.io.IOException;
import java.io.InputStream;
import com.gensym.classes.Item;
import com.gensym.classes.MediaBin;
/**
 * This class implements a binary input streams to read G2 media bins.  It 
 * is assumed that media objects (gif's, avi's, jpg's) and serialized java
 * objects, and maybe even .class files could be stored in G2 with this
 * facility.  The media-bin class in G2 defines objects that act like
 * hierarchical file systems that are stored in G2 KB's.
 * <p>

 * @author  Joe Devlin
 * @see     java.io.BufferedInputStream
 * @see     java.io.ByteArrayInputStream
 * @see     java.io.DataInputStream
 * @see     java.io.FilterInputStream
 * @see     java.io.InputStream
 *
 */
public class G2BinaryInputStream extends InputStream {
  static final int bufferLength = 2048; // must be even!!
  int bytesAvailable = 0;
  int readPointer = 0;
  int bytesRead = 0;
  int fileSize;
  byte[] buffer;
  boolean haveMetaData = false;
  boolean internalEOF = false;
  int fd;
  private static final Symbol sizeKey = Symbol.intern("SIZE-IN-BYTES");
  MediaBin mediaBin; // eventually the real thing


  public G2BinaryInputStream(MediaBin mbw, int fd)
  {
    this.mediaBin = mbw;
    this.fd = fd;
    buffer = new byte[bufferLength];
  }

  /**
   * Read one byte from Stream
   *
   * @exception  IOException  if an I/O error occurs.
   */
  @Override
  public synchronized int read() throws IOException
  {
    if (readPointer < bytesAvailable)
      {
	int result = buffer[readPointer++];
	if (result < 0) {
		result += 256;
	}
	return result;
      }
    else
      {
	boolean moreDataAvailable = getMoreData();
	// System.out.println("refreshing internal buffer moreData="+
	// 		   moreDataAvailable);
	if (readPointer < bytesAvailable)
	  {
	    int result = buffer[readPointer++];
	    if (result < 0) {
	    	result += 256 ;
	    }
	    return result;
	  }
	else
	  {
	    // System.out.println("return -1 as EOF");
	    return -1;
	  }  
      }
  }

  /* This is a convenience method for the version below that takes
   * length and offset argumnets.
   *
   */
  @Override
  public synchronized int read(byte b[]) throws IOException
  {
    return read(b, 0, b.length);
  }

  /**
   * Reads up to <code>len</code> bytes of data from this input stream 
   * into an array of bytes. This method blocks until some input is 
   * available. If the first argument is <code>null,</code> up to 
   * <code>len</code> bytes are read and discarded. 
   * <p>
  
   * @param      b     the buffer into which the data is read.
   * @param      off   the start offset of the data.
   * @param      len   the maximum number of bytes read.
   * @return     the total number of bytes read into the buffer, or
   *             <code>-1</code> if there is no more data because the end of
   *             the stream has been reached.
   * @exception  IOException  if an I/O error occurs.
   * @see        java.io.InputStream#read()
   */
  @Override
  public synchronized int read(byte b[], int off, int len) 
       throws IOException 
  {
    if (len > 0)
      {
	int dataPointer = off;
	int dataEnd = off + len;
	
	if (bytesAvailable > readPointer)
	  {
	    int sourceLength = Math.min(len, bytesAvailable - readPointer);
	    //System.out.println("off "+off+" len "+len+" bAvble "+bytesAvailable+
	    // " readPntr "+readPointer+" dataPntr "+dataPointer+
	    // " sourceLen "+sourceLength);
	    System.arraycopy(buffer,readPointer,b,dataPointer,sourceLength);
	    dataPointer += sourceLength;
	    readPointer += sourceLength;
	  }
	if (dataPointer < dataEnd)
	  {
	    int i;
	    int wholeBufferCount 
	      =(dataEnd - dataPointer) / bufferLength;
	    for (i=0; i<wholeBufferCount ; i++)
	      {
		boolean moreDataAvailable = getMoreData();
		if (!moreDataAvailable) 
		  {
		    System.arraycopy(buffer,0,b,dataPointer,bytesAvailable);
		    readPointer = bytesAvailable;
		    dataPointer += bytesAvailable;
		    return dataPointer - off; // actual # bytes read
		  }
		System.arraycopy(buffer,0,b,dataPointer,bufferLength);
		dataPointer += bufferLength;
		readPointer = bufferLength;
	      }
	  }
	if (dataPointer < dataEnd )  // partial buffer at end
	  {
	    boolean moreDataAvailable = getMoreData();
	    int desiredLength = dataEnd - dataPointer;
	    int copyLength = Math.min(desiredLength, bytesAvailable);
	    
	    System.arraycopy(buffer,0,b,dataPointer,copyLength);
	    readPointer = copyLength;
	    dataPointer += copyLength;
	    return dataPointer - off; // actual # bytes read
	  }
	else
	  return dataPointer - off;
      }
    else
      return 0;
  }

  private boolean getMoreData()
       throws IOException
  {
    if (internalEOF)
      {
	bytesAvailable = 0;
	readPointer = 0;
	return false;
      }
    else
      {
	if (!haveMetaData)
	  {
	    Structure metaData = mediaBin.describe(fd);
	    Integer size
	      = (Integer) metaData.getAttributeValue(sizeKey,sizeKey);
	    fileSize = size.intValue();
	    // System.out.println("fileSize = " + fileSize);
	    
	    haveMetaData = true;
	  }
	/* get low level data */
	char[] newData = mediaBin.read(fd,bufferLength/2);
	// System.out.println("got new data len="+newData.length);
	for (int i = 0; i<newData.length ; i++)
	  {
	    char ch = newData[i];
	    buffer[2*i] = (byte) (ch & 255);
	    buffer[(2*i)+1] = (byte) (ch >> 8);
	  }
	bytesAvailable = (2 * newData.length);
	readPointer = 0;
	bytesRead += bytesAvailable;
	if (bytesRead >= fileSize) 
	  {
	    internalEOF = true;
	    if (bytesRead > fileSize)
	      bytesAvailable--;
	  }
	
	return !internalEOF;
      }
  }
    
  /**
   * Skips over and discards <code>n</code> bytes of data from this 
   * input stream. The <code>skip</code> method may, for a variety of 
   * reasons, end up skipping over some smaller number of bytes, 
   * possibly <code>0</code>. The actual number of bytes skipped is 
   * returned. 
   * <p>
   *
   *
   * @param      n   the number of bytes to be skipped.
   * @return     the actual number of bytes skipped.
   * @exception  IOException  if an I/O error occurs.
   */
  @Override
  public synchronized long skip(long n)
       throws IOException 
  {
    /* ensure that the number is a positive int */
    byte data[] = new byte[(int) (n & 0xEFFFFFFF)];
    return read(data);
  }
  
   /**
    * Returns the number of bytes that can be read from this input 
    * stream without blocking.
    *
    * @return     the number of bytes that can be read from this input stream
    *             without blocking.
    * @exception  IOException  if an I/O error occurs.
    */
  @Override
  public synchronized int available() 
       throws IOException 
  {
    return bytesAvailable;
  }
  
  /**
   * Closes this input stream and releases any system resources 
   * associated with the stream. 
   * <p>
   *
   * @exception  IOException  if an I/O error occurs.
   */
  @Override
  public synchronized void close() 
       throws IOException 
  {
     mediaBin.closeStream(fd);
  }
  
  /**
   * Placeholder for method that may eventually support marking.
   */
  @Override
  public synchronized void mark(int readlimit)
  {
  }
  
  /**
   * reset() does nothing for <code>G2BinaryInputStream</code> until
   * support for marks is written.
   */
  @Override
  public synchronized void reset() throws IOException 
  {
    throw new IOException("mark/reset not supported");
  }
  
  /**
   * Marks are not yet supported on <code>G2BinaryInputStream</code>.
   * This will return false.
   */
  @Override
  public boolean markSupported() 
  {
    return false;
  }
}
