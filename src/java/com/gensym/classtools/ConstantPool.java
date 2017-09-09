package com.gensym.classtools;

import java.io.*;
import java.util.*;

public class ConstantPool implements RuntimeConstants {	
  private Vector pool;
  private static final boolean trace = false;
  private int numberOfConstants = 0;
  protected static int DEFAULT_INITIAL_SIZE = 20;
  protected static int DEFAULT_INCREMENT_SIZE = 5;

  ConstantPool() {
    pool = new Vector(DEFAULT_INITIAL_SIZE,DEFAULT_INCREMENT_SIZE);
    // Empty 0th element of all constant pools
    pool.addElement(null);
    numberOfConstants ++;
  }

  ConstantPool(int length) {
    pool = new Vector(length,DEFAULT_INCREMENT_SIZE);
    // Empty 0th element of all constant pools
    pool.addElement(null);
    numberOfConstants ++;
  }

  public Constant[] getPool() {
    Constant[] ret = new Constant[pool.size()];
    pool.copyInto(ret);
    return ret;
  }

  public Constant getPool(int index) {
    return (Constant)pool.elementAt(index);
  }

  void setPool(Constant[] pool) {
    this.pool = new Vector(pool.length);
    for (int i = 0; i < pool.length; i++) 
      this.pool.addElement(pool[i]);
    numberOfConstants = pool.length;
  }

  void setPool(int index, Constant entry) {
    pool.setElementAt(entry,index);
  }

  public int getLength() {
    return pool.size();
  }

  /**
   * A method to check whether a Constant.eq() is a member
   * of this ConstantPool.  If it is this method will return the
   * integer index into the constantpool. If not this method will
   * return -1
   */
  public int member(Constant con) {
    int index = -1;
    for (int j = 0; j < getLength(); j++) {
      if ((getPool(j) != null) && (con != null)) {
	if(con.eq(getPool(j))) {
	  return j;
	}
      }
    }
    return index;	
  }

  /**
   *  A method to check whether a Constant.equal() is a member
   * of the second argument.  If it is this method will return the
   * integer index into the constantpool. If not this method will
   * return -1
   */
  public int member(ConstantPool pool1, Constant con) {
    int index = -1;
    ConstantPool pool2 = pool1;
    for (int j = 0; j < getLength(); j++) {
      if ((getPool(j) != null) && (con != null)) {
	if(con.equalSemantic(pool2,this,getPool(j))) {
	  return j;
	}
      }
    }
    return index;	
  }

  /* Add a constant to the ConstantPool return location either where it
   * was found or added. Note this simply adds the constant into the next
   * available location, and returns the location of the added constant, or
   * -1 to indicate failure
   */
  final int add(Constant con, boolean firsttime) {
    if (con == null) {
      Object o =  pool.lastElement();
      if (o != null) {
	Constant lastConstant =(Constant)  o;
	if (lastConstant.getType() == CONSTANT_LONG 
	    || lastConstant.getType() == CONSTANT_DOUBLE)
	  pool.addElement(null);		
      }
      return (pool.size() -1);
    }
    if ((! firsttime) && this == con.constantPool)
      return con.getWhere();
    else {
      int where = -1;
      if (trace) {
	System.out.println("Attempting to add " + con);
	toStdout();
      }
      if(con == null) 
	return where;
      else {
	boolean present = false;
	for (int j = 1; j < getLength(); j++) {
	  if (getPool(j) != null) {
	    if(trace)
	      System.out.println("Pool = " + getPool(j).constantPool + 
				 "Constant = " + getPool(j));
	    if ((con == getPool(j)) ||
              (con.equalSemantic(this,getPool(j).constantPool,
			   getPool(j)))) {
	      where = j;	   
	      if (trace) {
		System.out.println(">>>> Found in pool " + 
				   con + " at " + where); 
            System.out.println(this);
            }
	      present = true;
	      break;
	    }
	    else {
	      if (trace) 
		System.out.println("Does not equal" + con + " " + getPool(j));
	    }
	  }
	}	
	if(! present) { 
	  pool.addElement(con);
	  where = (pool.size() - 1);
	  con.setWhere(where);
	  if (trace) { 
	    System.out.println(">>>> Adding into pool " + con + 
			       " At " + where);
          System.out.println(this);
        }
	  numberOfConstants ++;
	}
	return where;
      }
    }
  }
 
  /** Add the contents of another pool into this one
   */
  final void add(ConstantPool pool2) throws ClassException {
    if (pool2 != this) {
      int added = 0;
      boolean present;

      // Add in each new constant to the constantpool
      for (int i = 1; i < pool2.getLength(); i++) {
	add(pool2.getPool(i),false);
      }

      // Localize each new constant to the constantpool
      for (int i = 1; i < pool2.getLength(); i++) {
	if (trace) {
	  System.out.println("Would like to localize" + pool2.getPool(i) +
			     " to" + this);
	  System.out.println("NB it is from" + pool2 + "which is/isnot eq" +
			     (pool2 == this));
	}
	Constant c = pool2.getPool(i);
	if (c != null)
	  c.localize(this,pool2);
	if (trace) {
	  System.out.println("After it is from" +
			     pool2.getPool(i).constantPool);
	  System.out.println("And it is" + pool2.getPool(i));
	  System.out.println("");
	}
      }
    }
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
	 out.writeShort(getLength());
	  
	 for(int i = 1; i < getLength(); i++) {
	   if (getPool(i) != null) {
	     if (trace)
	       System.out.println("Start emitting constant #" + 
				  i + " " + getPool(i));
	     getPool(i).emit(out);
	   } 
	 }
	 if (trace)
	   System.out.println("Completed Emitting constantPool");
  }

  public void toStdout() {
    if (trace) 
      System.out.println("Summary of Constant Pool " + this);
    else System.out.println("Summary of Constant Pool ");
    for(int i = 0; i < getLength(); i++)
      if (trace)
	System.out.println("" + i + ") " + 
			   ((getPool(i) != null)? getPool(i).getWhere() : i) +
			   ") " + getPool(i));
      else System.out.println("" + i + ") " + getPool(i));
  }
    
  @Override
    
  public Object clone() {
    int length = getLength();
    ConstantPool clone =  new ConstantPool(length);
    for (int i = 1; i < length; i++) { 
      Constant c = (Constant) getPool(i).clone(false);
      if (trace)
	System.out.println("Clone result = " + c);
      clone.add(c,true);
    }
    length = clone.getLength();
    for (int i = 1; i < length; i++)
    {
       Constant c = (Constant) clone.getPool(i);
       c.constantPool = clone;
    }
    return clone;
  }
}


