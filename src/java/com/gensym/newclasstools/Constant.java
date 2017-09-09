package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public abstract class Constant implements RuntimeConstants
{
  public abstract byte getType();
  @Override
  public abstract int hashCode();
  @Override
  public abstract boolean equals(Object c);
  public abstract String stringRep();
  abstract void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException;


  // Reading in a constant pool is a two-phase operation; first all the
  // constants must be read in; then the constants in each constant can
  // be used to build up the actual internals of the constant.
  abstract void read(ConstantParser cp) throws ClassException;
  void finishReading(ConstantPool cp) throws ClassException {}

  void addSubsidiaryConstants(ConstantPool cp) {
  }

  private static String[] typeNames =
  { "<notype>", "UTF8" , "UNICODE", "INTEGER", "FLOAT",
    "LONG" , "DOUBLE", "CLASS", "STRING", "FIELD_REF",
    "METHOD_REF", "INTERFACE_METHOD_REF", "NAME_AND_TYPE"};

  private static boolean trace = false;

  static Constant readConstant(ConstantParser cp)
       throws ArrayIndexOutOfBoundsException, ClassException
  {
    int type = (cp.currentByte() & 0xFF);
    cp.incIndex();
    if (trace)
      System.out.println("  reading constant of type " + typeNames[type]);
    Constant result;
    switch(type) {
    case CONSTANT_UTF8: 		
      result = new UTF8Constant();
      break;
    case CONSTANT_INTEGER:		
      result = new IntegerConstant();
      break;
    case CONSTANT_FLOAT:		
      result = new FloatConstant();
      break;
    case CONSTANT_LONG: 		
      result = new LongConstant();
      break;
    case CONSTANT_DOUBLE:
      result = new DoubleConstant();
      break;
    case CONSTANT_CLASS:
      result = new ClassConstant();
      break;
    case CONSTANT_STRING:
      result = new StringConstant();
      break;
    case CONSTANT_FIELD_REF:
      result = new FieldRefConstant();
      break;
    case CONSTANT_METHOD_REF:
      result = new MethodRefConstant();
      break;
    case CONSTANT_INTERFACE_METHOD_REF:
      result = new InterfaceMethodRefConstant();
      break;
    case CONSTANT_NAME_AND_TYPE:
      result = new NameAndTypeConstant();
      break;
    default: 
      throw 
	new ClassException("Internal error: Unknown CONSTANT pool type: "+
			   type + " at " +
			   (cp.getIndex() - 1));
	 }
    result.read(cp);
    return result;
  }

  @Override
  public String toString() {
    return "<Constant type="+typeNames[getType()]+ " value=" + stringRep()
      + ">";
  }

  void emit(DataOutputStream out, ConstantPool cp) throws IOException, ClassException {
    
    // Emit the tag byte
    out.write(getType());
    // The rest is dependent on what type of constant this is.
    emit2(out, cp);
  }


  /** Is the type of a constant a value type? (long, float, double, integer 
   *  or string)
   */
  public boolean isValue() {
    switch(this.getType()) {
    case CONSTANT_INTEGER : 
    case CONSTANT_FLOAT :
    case CONSTANT_DOUBLE : 
    case CONSTANT_LONG : 
    case CONSTANT_STRING:
      return true ;
    default :
      return false;
    }
  }
}





