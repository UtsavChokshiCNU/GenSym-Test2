package com.gensym.nols.data;

import java.io.*;
import java.nio.charset.Charset;

/**
 * BufferedRandomAccessFile
 * @version     1.0 October 28, 1998
 * @author      Brian O. Bush
 **/
public class BufferedRandomAccessFile extends RandomAccessFile {
	static final long serialVersionUID = 1L;
	byte buffer[];
	int BUF_SIZE = 256;  // not used, see constructor
	int buf_end = 0;
	int buf_pos = 0;
	long real_pos = 0;

	public BufferedRandomAccessFile(File filename, String mode, int bufsize) throws IOException {
		super(filename,mode);
		invalidate();
		BUF_SIZE = bufsize;
		buffer = new byte[BUF_SIZE];    
	}

	@Override
	public final int read() throws IOException{
		if(buf_pos >= buf_end) {
			if(fillBuffer() < 0)   // attempt to (re-)fill buffer
				return -1;
		}
		if(buf_end == 0) {
			  return -1;
		} else {
			return buffer[buf_pos++];
		}
	}

	private int fillBuffer() throws IOException {
		int n = super.read(buffer, 0, BUF_SIZE);
		if(n >= 0) {
		  real_pos +=n;
		  buf_end = n;
		  buf_pos = 0;
		}

		return n;
	}

	private void invalidate() throws IOException {
		buf_end = 0;
		buf_pos = 0;
		real_pos = super.getFilePointer();
	}

	@Override
	public final int read(byte b[], int off, int len) throws IOException {
		int leftover = buf_end - buf_pos;
		if(len <= leftover) {
			 System.arraycopy(buffer, buf_pos, b, off, len);
			 buf_pos += len;
			 return len;
		}

		for(int i = 0; i < len; i++) {
				int c = this.read();
				if(c != -1)
						b[off+i] = (byte)c;
				else {
						return i;
				}
		}
		return len;
	}
  

	@Override
	public final long getFilePointer() throws IOException{
		long l = real_pos;
		return (l - buf_end + buf_pos) ;
	}

	@Override
	public final void seek(long pos) throws IOException {
		int n = (int)(real_pos - pos);
		if(n >= 0 && n <= buf_end) {
		  buf_pos = buf_end - n;
		} else {
		  super.seek(pos);
		  invalidate();
		}
	}

	public final int countLines() throws IOException {
		// counts lines in file.  Leaves file pointer at end of file.
		seek(0l);  // rewinds
		int lines = 0;
		// MK 3/11/99 -- changed the count so if the last line lacks a \n, it still gets counted
		boolean newline = true;
		while(fillBuffer() >= 0) {
			for(int i = buf_pos; i < buf_end; i++) {
				//System.out.println("char = "+new String(buffer,i,1));
				if(newline) {
					lines++;
					newline = false;
				}
				if(buffer[i] == '\n'){
					newline = true;
				}
			}
		}
		return lines;
	}

	public void reset() throws IOException {
		// sets file pointer to top
		buf_pos = 0;
		buf_end = 0;
		real_pos = 0;
		super.seek(0l);
	}

	/**
	* return a next line in String
	*
	* This method replaces the readLine method. getNextLine method first decides if the buffer
	* still containes unread contents. If it doesn't, the buffer needs to be filled up. If the newline
	* delimiter can be found in the buffer, then a new line isread from the buffer and converted to String.
	* Otherwise, it will simply call the read method to read byte by byte. Performance is better
	* here than in the original since the read method is buffered.
	*/

	public final String getNextLineAsString() throws IOException {
		String str = null;

		if(buf_end - buf_pos <= 0) {
			if(fillBuffer() < 0) {
			//	 throw new IOException("error in filling buffer!");
				return null;
			}
		}
                             
		int lineend = -1;
    
		for(int i = buf_pos; i < buf_end; i++) {
			if(buffer[i] == '\n') {
				lineend = i;
				break;
			}
		}
    
//		System.out.println("lineend="+lineend);
		if(lineend < 0) {
			 StringBuffer input = new StringBuffer(256);
			 int c;

			 while (((c = read()) != -1) && (c != '\n')) {
				  input.append((char)c);
			 }
//			 System.out.print("*less than zero* c="+c+"  ");
			 if ((c == -1) && (input.length() == 0)) {
//				System.out.println("returning null");
				return null;
			 }
			 return input.toString();
		}

		Charset charset = Charset.defaultCharset();
		if(lineend > 0 && buffer[lineend-1] == '\r')
			 str = new String(buffer, buf_pos, lineend - buf_pos -1, charset);
		else str = new String(buffer, buf_pos, lineend - buf_pos, charset);
    
		buf_pos = lineend +1;
		return str;
	}



	/**
	* return a next line in StringBuffer
	*
	* This method replaces the readLine method. getNextLine method first decides if the buffer
	* still containes unread contents. If it doesn't, the buffer needs to be filled up. If the newline
	* delimiter can be found in the buffer, then a new line isread from the buffer and converted to String.
	* Otherwise, it will simply call the read method to read byte by byte. Performance is better
	* here than in the original since the read method is buffered.
	*/

	public final StringBuffer getNextLine() throws IOException {
		String str = null;
		StringBuffer strBuff = null;

		if(buf_end-buf_pos <= 0) {
			if(fillBuffer() < 0) {
				// throw new IOException("error in filling buffer!");
				return null;
			}
		}
                             
		int lineend = -1;
    
		for(int i = buf_pos; i < buf_end; i++) {
		  if(buffer[i] == '\n') {
				lineend = i;
				break;
		  }
		}
    
		if(lineend < 0) {
			 StringBuffer input = new StringBuffer(256);
			 int c;

			 while (((c = read()) != -1) && (c != '\n')) {
				  input.append((char) c);
			 }
			 if ((c == -1) && (input.length() == 0)) {
				 System.out.println("returning null: buffer empty");
				 return null;
			 }
			 return input;
		}

		Charset charset = Charset.defaultCharset();
		if(lineend > 0 && buffer[lineend-1] == '\r')
			 str = new String(buffer, buf_pos, lineend - buf_pos -1, charset);
		else str = new String(buffer, buf_pos, lineend - buf_pos, charset);

		buf_pos = lineend +1;
		strBuff = new StringBuffer(str);    
		return strBuff;
	}

}