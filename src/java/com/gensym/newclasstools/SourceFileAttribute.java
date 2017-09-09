package com.gensym.newclasstools;

import java.io.*;


public class SourceFileAttribute extends Attribute 
{
  private UTF8Constant sourceconst;
	
  public SourceFileAttribute(String fileName) throws ClassException
  {
    super("SourceFile");
    sourceconst = new UTF8Constant(fileName);
    length = 2;
  }

  SourceFileAttribute(UTF8Constant nameConstant, ConstantPool constantPool,byte[] bytes, int start)
    throws ClassException
  {
    super(nameConstant); 
    int sourcefile_index = Attribute.readU2(bytes,start);
    sourceconst = (UTF8Constant)constantPool.getConstant(sourcefile_index);
  }
 
  @Override
  void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {
    super.emit(out, cp);
    out.writeShort(cp.getIndex(sourceconst));
  }

  @Override
  public String toString () {	
    return "<SourceFileAttribute, file=" + sourceconst.getString() + 
      ", attributeinfo =" + super.toString() + ">";
  }
}


    
    
