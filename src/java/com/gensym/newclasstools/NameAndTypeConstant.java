package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class NameAndTypeConstant extends Constant implements RuntimeConstants
{
  private UTF8Constant nameConstant;
  private int nameIndex;

  private Type fieldType = null;
  private Type returnType = null;
  private Type[] argumentTypes = null;

  private UTF8Constant descriptorConstant;
  private int descriptorIndex;
 
  private static final boolean trace = false;

  private NameAndTypeConstant (String name) {
    nameConstant = new UTF8Constant(name);
  }

  public NameAndTypeConstant(String name, Type fieldType) {
    this(name);
    this.fieldType = fieldType;
    init();
  }

  public NameAndTypeConstant(String name, Type returnType, Type[] argumentTypes) {
    this(name);
    if (trace)
      System.out.println("creating MethodRefConstant: for method " + name + ": " + argumentTypes.length + " argument Types specified");
    this.returnType = returnType;
    this.argumentTypes = argumentTypes;
    init();
  }

  NameAndTypeConstant () {}

  void init() {
    descriptorConstant = new UTF8Constant(descriptor());
    if (trace)
      System.out.println("Just created " + this);
  }

  public String getName() {
    return nameConstant.getString();
  }

  public Type getFieldType() {
    return fieldType;
  }

  public Type getReturnType() {
    return returnType;
  }

  public Type[] getArgumentTypes() {
    return argumentTypes;
  }

  @Override
  public byte getType() {
    return CONSTANT_NAME_AND_TYPE;
  }
    
  @Override
  public int hashCode() {
    return CONSTANT_NAME_AND_TYPE ^ nameConstant.hashCode() ^
      ((fieldType == null) ?
       (returnType.hashCode() ^ Type.hashTypeArray(argumentTypes)) :
       fieldType.hashCode());
  }

  @Override
  public boolean equals(Object c) {
    if (c instanceof NameAndTypeConstant &&
	nameConstant.equals(((NameAndTypeConstant)c).nameConstant)) {
      NameAndTypeConstant natc = (NameAndTypeConstant) c;
      if (fieldType == null) {
	if (natc.fieldType != null)
	  return false;
	if (argumentTypes.length != natc.argumentTypes.length)
	  return false;
	for (int i = 0; i < argumentTypes.length; i++) {
	  if (argumentTypes[i] != natc.argumentTypes[i])
	    return false;
	}
	return true;
      } else {
	return fieldType == natc.fieldType;
      }
    } else {
      return false;
    }
  }

  @Override
  public String stringRep() {
    return getName() + " with descriptor " + descriptor();
  }

  public String descriptor() {
    if (fieldType == null) {
      if (trace) {
	System.out.println("generating descriptor; Field Type is null, " + argumentTypes.length + " argument types");
      }
      return returnType.descriptor(argumentTypes);
    } else
      return fieldType.descriptor();
  }
  
  @Override
  void emit2(DataOutputStream out, ConstantPool cp) throws java.io.IOException
  {
    out.writeShort(cp.getIndex(nameConstant));
    out.writeShort(cp.getIndex(descriptorConstant));
  }

  @Override
  public void addSubsidiaryConstants(ConstantPool cp) {
    cp.getIndex(nameConstant);
    cp.getIndex(descriptorConstant);
  }

  @Override
  void read(ConstantParser cp) {
    nameIndex = cp.readU2();
    descriptorIndex = cp.readU2();
  }

  @Override
  void finishReading(ConstantPool cp) throws ClassException {
    nameConstant = (UTF8Constant)cp.getConstant(nameIndex);
    descriptorConstant = (UTF8Constant)cp.getConstant(descriptorIndex);
    String descriptor = descriptorConstant.getString();
    if (descriptor.charAt(0) == '(') {
      returnType = Type.parseReturnType(descriptor);
      argumentTypes = Type.makeTypeArray(Type.parseArgumentTypes(descriptor));
    } else {
      fieldType = Type.parseType(descriptor);
    }
  }
}
