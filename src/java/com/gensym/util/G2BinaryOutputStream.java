package com.gensym.util;

import java.io.IOException;
import java.io.OutputStream;
import com.gensym.classes.Item;
import com.gensym.classes.MediaBin;


/**
 * This class implements a binary output streams into G2 media bins.  It 
 * is assumed that media objects (gif's, avi's, jpg's) and serialized java
 * objects, and maybe even .class files could be stored in G2 with this
 * facility.  The media-bin class in G2 defines objects that act like
 * hierarchical file systems that are stored in G2 KB's.
 * <p>

 * @author  Joe Devlin
 * @version 1.0
 * @see     java.io.BufferedOutputStream
 * @see     java.io.ByteArrayOutputStream
 * @see     java.io.DataOutputStream
 * @see     java.io.FilterOutputStream
 * @see     java.io.InputStream
 * @see     java.io.OutputStream#write(int)
 */
public class G2BinaryOutputStream extends OutputStream
{
  MediaBin mediaBin; // eventually really a MediaBin
  int fd;
  byte[] buffer;
  static final int bufferLength = 2048; // must be even!!
  int fillPointer = 0;
  private boolean isClosed = false;
  
  public G2BinaryOutputStream(MediaBin mbw, int fd)
  {
    this.mediaBin = mbw;
    this.fd = fd;
    buffer = new byte[bufferLength];
  }

  @Override
  public synchronized void write(int b) 
       throws IOException
  {
    buffer[fillPointer++] = (byte) b;
    if (fillPointer == bufferLength)
      flush(false);
  }

   
  @Override
  public void write(byte b[]) 
       throws IOException 
  {
    write(b,0,b.length);
  }
  
  
  @Override
  public synchronized void write(byte b[], int off, int len) 
       throws IOException
  {
    int dataPointer = off;
    int dataEnd = off + len;
    if (len > 0)
      {
	int sourceLength = Math.min(len, 
				    bufferLength - fillPointer);
	System.arraycopy(b,dataPointer,buffer,fillPointer,sourceLength);
	dataPointer += sourceLength;
	fillPointer += sourceLength;
	if (fillPointer == bufferLength)
	  flush(false);
	int i;
	int wholeBufferCount 
	  = (dataEnd - dataPointer) /  bufferLength;
	for (i=0; i<wholeBufferCount ; i++)
	  {
	    System.arraycopy(b,dataPointer,buffer,0,bufferLength);
	    flush(false);
	    dataPointer += bufferLength;
	  }
	if (dataPointer < dataEnd)
	  {
	    sourceLength = dataEnd - dataPointer;
	    System.arraycopy(b,dataPointer,buffer,0,sourceLength);
	    fillPointer = sourceLength;
	  }
      }
  }

  
  /**
   * Flushes this output stream and forces any buffered output bytes 
   * to be written out.  G2BinaryOutputStream is buffered.  Single 
   * bytes are never flushed except if the file is being closed.  This
   * limitation is due to the fact that this class is built on
   * 16-bit byte transport.
   * <p>
   *
   * @exception  IOException  if an I/O error occurs.
   */  
  @Override
  public synchronized void flush() 
       throws IOException
  {
    flush(false);
  }

  private void flush(boolean closing)
       throws IOException
  {
    if (isClosed)
      return;

    if (fillPointer > 0)
      {
	boolean oddLength = ((fillPointer % 2) ==1) ? true : false;
	byte lastByte = buffer[fillPointer - 1];
	int charBufferLimit;
	if (closing && oddLength)
	  charBufferLimit = (fillPointer + 1) / 2;
	else if (!closing && oddLength)
	  charBufferLimit = (fillPointer - 1) / 2;
	else
	  charBufferLimit = fillPointer / 2;

	char[] charBuffer = new char[charBufferLimit];

	for (int i = 0; i<charBufferLimit ; i++)
	  {
	    int lowByte = buffer[(2*i)];
	    int highByte = buffer[(2*i)+1];
	   
	    if (lowByte < 0) {
	    	lowByte += 256;
	    }
	    if (highByte < 0) {
	    	highByte += 256;
	    }
	    charBuffer[i] = (char) ((highByte << 8) + lowByte);
	    
	  }

	mediaBin.write(fd,charBuffer);

	if (closing)
	  {
	    if (oddLength)
	      mediaBin.setIgnoreLastByte(fd);
	  }
	else if (oddLength)
	  {
	    fillPointer = 1;
	    buffer[0] = lastByte;
	  }
	else 
	  {
	    fillPointer = 0;
	  }
      }
  }

  /**
   * Closes this output stream and releases any system resources 
   * associated with this stream. 
   * <p>
   *
   * @exception  IOException  if an I/O error occurs.
   */
  @Override
  public synchronized void close() throws IOException 
  {
    if (!isClosed)
      {
	flush(true);
	mediaBin.closeStream(fd);
      }
    isClosed = true;
  }
}
