package com.gensym.newclasstools;

import java.io.*;

/**
 * Technically ClassOutput is not a stream, but it manages two separate
 * streams which are public fields of the class.   This was the simplest way
 * I found to mixin the power of DataOutputStream and the advantages of maintaining
 * an array in ByteOutputStream.
 * Usage of an instance of this class:
 *    cout = new ClassOutput(1000);
 *    cout.out.writeInt(10);
 *    System.out.prinlnt("An integer = " + cout.bytes.size() + " bytes.");
 * @see	Class
*/
public class ClassOutput {
  public ByteArrayOutputStream bytes;
  public DataOutputStream out;
  private static final int DEFAULT_BUFFER_SIZE = 10000;
  
  /**
   *Create a ClassOutput object with an initial buffer size of length.
   * This is just an initial size and is not a limit on the the number of bytes
   * that can be emitted into the out stream.
   */
  public ClassOutput(int length) {
    bytes = new ByteArrayOutputStream(length);
    out = new DataOutputStream(bytes);
  }
  
  public ClassOutput() {
    bytes = new ByteArrayOutputStream(DEFAULT_BUFFER_SIZE);
    out = new DataOutputStream(bytes);
  }
  
}
