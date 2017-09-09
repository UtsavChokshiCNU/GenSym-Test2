package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class ConstantParser implements RuntimeConstants
{
  private byte[] bytes;
  private int index;

  public ConstantParser(byte[] bytes, int index) {
    this.bytes = bytes;
    this.index = index;
  }

  byte currentByte() {
    return bytes[index];
  }
  
  void incIndex() {
    index++;
  }

  void incIndex(int increment) {
    index+= increment;
  }

  int getIndex() {
    return index;
  }

  
  int readU2()
       throws ArrayIndexOutOfBoundsException
  {
    int hi = bytes[index];
    int lo = bytes[index + 1];
    index += 2;
    return ((hi & 0xFF) << 8) + (lo & 0xFF);
  }

  long readLong()
       throws ArrayIndexOutOfBoundsException
  {
    int hi = readInt();
    int lo = readInt();
    return (((long)hi << 32) + lo);
  }

  double readDouble()
         throws ArrayIndexOutOfBoundsException
  {
    return Double.longBitsToDouble(readLong());
  }

  int readInt()
       throws ArrayIndexOutOfBoundsException
  {
    int b1 = bytes[index];
    int b2 = bytes[index + 1];
    int b3 = bytes[index + 2];
    int b4 = bytes[index + 3];
    index += 4;
    return ((b1 & 0xFF) << 24) + ((b2 & 0xFF) << 16) + ((b3 & 0xFF) << 8) + (b4 & 0xFF);
  }

  float readFloat()
       throws ArrayIndexOutOfBoundsException
  {
    return Float.intBitsToFloat(readInt());
  }


  String readUTFString(int length)
       throws ClassException
  {
    StringBuffer buffer = new StringBuffer();
    int end = index + length;
    char unicode = 0;
    
    while (index < end) {
      char byte1 = (char) (bytes[index] & 0xFF);
      if ((byte1 & 0x80) == 0)
	{
	  if (byte1 == 0)
	    throw new ClassException("Bad null Char");
	  unicode = byte1;
	  index += 1;
	}
      else {
	char high3bits = (char) (byte1 >> 5);
	char byte2 =  (char) (bytes[index+1] & 0xFF);
	if (high3bits == 6)
	  {
	    unicode = (char) (((byte1 & 0x1F) << 6) +
			      (byte2 & 0x3F));
	    index += 2;
	  }
	else  {
	  char byte3 =  (char) (bytes[index+2] & 0xFF);
	  unicode = (char) (((byte1 & 0x0F) << 12) +
			    ((byte2 & 0x3F) << 6) +
			    (byte3 & 0x3F));
	  index += 3;
	}
      }
      buffer.append(unicode);
    }
    return buffer.toString();
  }
 
}
