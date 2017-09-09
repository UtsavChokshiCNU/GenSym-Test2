package com.gensym.classtools;

import java.io.*;
import java.util.Vector;

public class Attribute extends Info
{
  protected int length;
  public int getLength() {
	  return length;
  }

  private static final boolean trace = false;
 
  Attribute(int nameIndex, ConstantPool pool)
	  throws ClassException
  { 
	  super(nameIndex,pool);
  }

  Attribute(String name, ConstantPool pool) {	
	  super(pool);
	  nameIndex = pool.add(new Utf8Constant(name),true);
        this.name = name;
  }

  @Override
  void emit(DataOutputStream out) 
    throws IOException
  {
	  super.emit(out);
	  if(trace)
		  System.out.println("Emitting Attrbute length:" + length);
      out.writeInt(length);
	}

  static void emit(Vector attributes,DataOutputStream out) 
    throws IOException
  {	
	  Info.emit(attributes,out);
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
    String name = constantPool.getPool(attributeNameIndex).getName();	
	//int size = attributeDataLength + 6;
	int length = attributeDataLength;
	int nextstart = start + 6;

	Attribute attribute;

	if (trace) {
		System.out.println("Attribute name:" + name);
		System.out.println("Attribute length:" + attributeDataLength);
	}

	if (name.equals("Code")) {
		attribute = new CodeAttribute(attributeNameIndex,constantPool,bytes,nextstart);
	}
	else {
		if (name.equals("SourceFile")) {
			attribute = new SourceFileAttribute(attributeNameIndex,constantPool,bytes,nextstart);
		}
		else {
			if (name.equals("Exceptions")) {
				attribute = new ExceptionsAttribute(attributeNameIndex,constantPool,bytes,nextstart);
			}
		      else {
			  if (name.equals("LineNumberTable")) {
				attribute = new LineNumberTableAttribute(attributeNameIndex,constantPool,bytes,nextstart);
			  }
			  else {
			  if (name.equals("ConstantValue")) {
			    attribute = new ConstantValueAttribute(attributeNameIndex,constantPool,bytes,nextstart);

				}
				else {
				if (name.equals("LocalVariableTable")) {
				 attribute = new LocalVariableTableAttribute(attributeNameIndex,constantPool,bytes,nextstart);
				}
				else {
			    attribute = new Attribute(attributeNameIndex,constantPool);
				if (trace)
					System.out.println("Warning: found unknown attribute"  + name);
				}
			 }
			 }
			 }
		}
	}
	
	attribute.length = length;
    attribute.name = name;

	if (trace)
		System.out.println("  found attribute "+attribute.name+" with length="
		       +attributeDataLength);
    return attribute;
  }


 public static void toStdout(Vector attributes,String prefix) {
	  System.out.println(prefix + "Attributes");
	  System.out.println(prefix + "----------");
	  Info.toStdout(attributes, prefix);
 }

 @Override

 public String toString() {
		return "<Attribute, name=" + name +
					", length=" + length + ">";
 }
}
