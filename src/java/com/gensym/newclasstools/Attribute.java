package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class Attribute extends Info
{
  protected int length;
  public int getLength() {
	  return length;
  }

  private static final boolean trace = false;
 
  Attribute(String name)
	  throws ClassException
  { 
	  super(name);
  }

  Attribute(UTF8Constant nameConstant)
	  throws ClassException
  { 
	  super(nameConstant);
  }

  @Override
  void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {
    super.emit(out, cp);
    if(trace)
      System.out.println("Emitting Attrbute length:" + length);
    out.writeInt(length);
  }

  static void emit(Vector attributes, DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {	
    Info.emit(attributes, out, cp);
  }


  static int readU2(byte[] bytes, int index)
       throws ArrayIndexOutOfBoundsException
  {
    return ((bytes[index] & 0xFF) << 8) + (bytes[index + 1] & 0xFF);
  }
  
  static int readU4(byte[] bytes, int index) 
       throws ArrayIndexOutOfBoundsException 
  {
    int high = readU2(bytes,index);
    int low = readU2(bytes,index + 2);
    return (high << 16) + low;
  }

  static Attribute readAttribute(ConstantPool constantPool,
					   byte[] bytes, int start)
       throws ClassException
  {
    int attributeNameIndex = readU2(bytes,start);
    int attributeDataLength = readU4(bytes,start+2);
    UTF8Constant nameConstant =  (UTF8Constant)constantPool.getConstant(attributeNameIndex);
    String name = nameConstant.getString();
    //int size = attributeDataLength + 6;
    int length = attributeDataLength;
    int nextstart = start + 6;
    
    Attribute attribute;
    
    if (trace) {
    System.out.println("Attribute name:" + name);
    System.out.println("Attribute length:" + attributeDataLength);
    }
    
    if (name.equals("Code")) {
      attribute = new CodeAttribute(nameConstant,constantPool,bytes,nextstart);
    } else {
      if (name.equals("SourceFile")) {
	attribute = new SourceFileAttribute(nameConstant, constantPool, bytes, nextstart);
      } else {
	if (name.equals("Exceptions")) {
	  attribute = new ExceptionsAttribute(nameConstant, constantPool,bytes,nextstart);
	} else {
	  if (name.equals("LineNumberTable")) {
	    attribute = new LineNumberTableAttribute(nameConstant, bytes, nextstart);
	  } else {
	    if (name.equals("ConstantValue")) {
	      attribute = new ConstantValueAttribute(nameConstant, constantPool, bytes, nextstart);
	      
	    } else {
	      if (name.equals("LocalVariableTable")) {
		attribute = new LocalVariableTableAttribute(nameConstant ,constantPool, bytes, nextstart);
	      } else {
		attribute = new Attribute(nameConstant);
		if (trace)
		  System.out.println("Warning: found unknown attribute"  + name);
	      }
	    }
	  }
	}
      }
    }
    
    attribute.length = length;
    attribute.nameConstant = nameConstant;

    if (trace)
      System.out.println("  found attribute "+attribute.getName()+" with length=" +
			 attributeDataLength);
    return attribute;
  }

 public static void toStdout(Vector attributes,String prefix) {
	  System.out.println(prefix + "Attributes");
	  System.out.println(prefix + "----------");
	  Info.toStdout(attributes, prefix);
 }

 @Override
 public String toString() {
		return "<Attribute, name=" + getName() +
					", length=" + length + ">";
 }
}
