package com.gensym.classtools;
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

  private int name_index;

  public int getNameIndex()
  {
    return name_index;
  }

  private int descriptor_index;
  public int getDescriptorIndex()
  {
      return descriptor_index;
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

  private String name;
  public String getName()
  {
      return name;
  }

  LocalVariableTableEntry(ConstantPool constantPool,byte [] bytes, 
    int start) 
    throws ClassException	
  {
    start_pc = Attribute.readU2(bytes,start);
    length = Attribute.readU2(bytes,start+2);
    name_index = Attribute.readU2(bytes,start+4);
    descriptor_index = Attribute.readU2(bytes,start+6);
    index = Attribute.readU2(bytes,start+8);	
    descriptor = constantPool.getPool(descriptor_index).getUTF8String(); 
    name = constantPool.getPool(name_index).getUTF8String(); 
  }

  void emit(DataOutputStream out) 
    throws IOException
  {
    out.writeShort(start_pc);
    out.writeShort(length);
    out.writeShort(name_index);
    out.writeShort(index);
  }

  int normalize(final ConstantPool locals, final ConstantPool normals, final int index)
    throws ClassException
  {	
	int indexLocal = index;
    Constant descriptorc = locals.getPool(descriptor_index);
    indexLocal = descriptorc.normalize(locals,normals,indexLocal);
    descriptor_index = normals.member(normals,descriptorc);
    descriptor = normals.getPool(descriptor_index).getName();    
    Constant namec = locals.getPool(name_index);
    indexLocal = namec.normalize(locals,normals,indexLocal);  
    name_index = normals.member(normals,namec);
    name = normals.getPool(name_index).getName(); 
    return indexLocal;
  }
  
  void localize(ConstantPool locals, ConstantPool normals)
    throws ClassException
  {
    Constant descriptorc = normals.getPool(descriptor_index);
    descriptor_index =  descriptorc.localize(locals,normals);
    descriptor = locals.getPool(descriptor_index).getName(); 
    
    Constant namec = normals.getPool(name_index);
    name_index =  descriptorc.localize(locals,normals);
    name = locals.getPool(name_index).getName(); 
  }

  public void toStdout(String prefix) {
    System.out.println(prefix + this);
  }
      
  @Override
      
  public String toString() {
      return "<LocalVariableTableEntry, start_pc=" + start_pc +
               ", length=" + length + 
               ", name_index =" + name_index +
               ", descriptor_index = " + descriptor_index +
               ", index =" + index +
               ">";
  }

}
