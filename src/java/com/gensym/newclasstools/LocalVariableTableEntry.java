package com.gensym.newclasstools;
import java.io.*;

public class LocalVariableTableEntry 
{
  private int start_pc;
  
  public int getStartPc() 
  {
      return start_pc;
  }

  private int length;

  public int getLength()
  {
      return length;
  }

  private int index;
  public int getIndex()
  {
      return index;
  }
  

  private String descriptor;
  public String getDescriptor()
  {
      return descriptor;
  }

  private UTF8Constant nameConstant;
  public String getName()
  {
      return nameConstant.getString();
  }

  LocalVariableTableEntry(ConstantPool constantPool,byte [] bytes, 
    int start) 
    throws ClassException	
  {
    start_pc = Attribute.readU2(bytes,start);
    length = Attribute.readU2(bytes,start+2);
    int name_index = Attribute.readU2(bytes,start+4);
    int descriptor_index = Attribute.readU2(bytes,start+6);
    index = Attribute.readU2(bytes,start+8);	
    descriptor = ((UTF8Constant)constantPool.getConstant(descriptor_index)).getString(); 
    nameConstant = (UTF8Constant)constantPool.getConstant(name_index);
  }

  void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException
  {
    out.writeShort(start_pc);
    out.writeShort(length);
    out.writeShort(cp.getIndex(nameConstant));
    out.writeShort(index);
  }

  public void toStdout(String prefix) {
    System.out.println(prefix + this);
  }
      
  @Override
  public String toString() {
      return "<LocalVariableTableEntry, start_pc=" + start_pc +
               ", length=" + length + 
               ", name =" + nameConstant +
               ", descriptor = " + descriptor +
               ", index =" + index +
               ">";
  }

}
