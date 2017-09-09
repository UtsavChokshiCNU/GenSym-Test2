package com.gensym.newclasstools;

import java.io.*;
import java.util.*;

public class ConstantPool implements RuntimeConstants {	
  private Vector pool; 
  private static final boolean trace = false;
  protected static int DEFAULT_INITIAL_SIZE = 20;
  protected static int DEFAULT_INCREMENT_SIZE = 5;
  private Hashtable poolHashtable;
  private static Object dummyConstant = new Object();

  ConstantPool() {
    pool = new Vector(DEFAULT_INITIAL_SIZE,DEFAULT_INCREMENT_SIZE);
    poolHashtable = new Hashtable(DEFAULT_INITIAL_SIZE);
  }

  ConstantPool(int length) {
    pool = new Vector(length,DEFAULT_INCREMENT_SIZE);
    poolHashtable = new Hashtable(length);
  }

  public Constant getConstant(int index) {
    return (Constant)pool.elementAt(index - 1);
  }

  public int getIndex(Constant c) {
    return getIndex(c, false);
  }

  public int getIndex(Constant c, boolean force) {
    if (c == null)
      System.out.println("Looking for null constant");
    Integer wrappedIndex = ((Integer)poolHashtable.get(c));
    int index;
    if (wrappedIndex == null || force) {
      index = pool.size() + 1;
      pool.add(index - 1,c);
      poolHashtable.put(c, new Integer(index));
      if (c instanceof LongConstant || c instanceof DoubleConstant) {
	// Long and double constants use up two indices in the constant pool
	// "In retrospect, making 8-byte constants take two constant pool
	// entries was a poor choice" JVM spec, Page 108, footnote 2.
	pool.add(index, dummyConstant);
      }
      c.addSubsidiaryConstants(this);
    } else {
      index = wrappedIndex.intValue();
    }
    return index;
  }

  public int getLength() {
    return pool.size();
  }
	  
  /** Emit the bytes to a DataOutputStream for a pool of constants
   *
   * @exception  IOException 
   *     failure when writing to output stream
   *
   * @exception ClassException
   *     failure due to unexpected constant type
   */
  final void emit(DataOutputStream out) 
       throws IOException, ClassException  {
      
	 if (trace)
	   System.out.println("Start Emitting constantPool");
	 out.writeShort(getLength() + 1);
	  
	 for(int i = 0; i < getLength(); i++) {
	   if (trace)
	     System.out.println("Start emitting constant #" + 
				(i + 1) + "; " + pool.elementAt(i));
	   if (pool.elementAt(i) != dummyConstant) {
	     ((Constant)pool.elementAt(i)).emit(out, this);
	   }
	 } 
	 if (trace)
	   System.out.println("Completed Emitting constantPool");
  }

  public void toStdout() {
    if (trace) 
      System.out.println("Summary of Constant Pool " + this);
    else System.out.println("Summary of Constant Pool ");
    for(int i = 0; i < getLength(); i++) {
      if (pool.elementAt(i) != dummyConstant) {
	System.out.println("" + (i + 1) + ") " + 
			   pool.elementAt(i));
      }
    }
  }

  public static ConstantPool readConstantPool(ConstantParser cp) throws ClassException
  {
    int size = cp.readU2() - 1;
    ConstantPool result = new ConstantPool(size);
    for (int i = 1; i <= size; i++) {
      result.getIndex(Constant.readConstant(cp), true);
    }
    for (int i = 1; i <= size; i++) {
      if (result.pool.elementAt(i) != dummyConstant) {
	result.getConstant(i).finishReading(result);
      }
    }
    return result;
  }
  
  void clear() {
    pool = new Vector(DEFAULT_INITIAL_SIZE,DEFAULT_INCREMENT_SIZE);
    poolHashtable = new Hashtable(DEFAULT_INITIAL_SIZE);
  }
}

    



