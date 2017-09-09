package com.gensym.classtools;

import java.io.*;


public class SourceFileAttribute extends Attribute 
{
  private int sourcefile_index;
  private Constant sourceconst;
	
  public SourceFileAttribute(String fileName)
  {
    super("SourceFile",new ConstantPool());   
    normalized = true;
    normalizedConstants = localConstants;
    localConstants = null;
    sourceconst = new Utf8Constant(normalizedConstants,fileName);
    sourcefile_index = normalizedConstants.add(sourceconst,true);
    length = 2;
  }

  SourceFileAttribute(int nameIndex, ConstantPool constantPool,byte[] bytes, int start)
    throws ClassException
  {
    super(nameIndex, constantPool); 
    sourcefile_index = Attribute.readU2(bytes,start);
    sourceconst = constantPool.getPool(sourcefile_index);
  }
 
  @Override
  void emit(DataOutputStream out) 
    throws IOException 
  {
    super.emit(out);
    out.writeShort(sourcefile_index);
  }

  /**
  * @exception ClassException
  *     Failure in normalization of this Attribute
  **/	
  @Override
  int normalize(final ConstantPool locals, final ConstantPool normals, final int index)
    throws ClassException { 	      
    
    int indexLocal = super.normalize(locals,normals,index);
    Constant srcc = locals.getPool(sourcefile_index);
    srcc.normalize(locals,normals,indexLocal);
    sourcefile_index = normals.member(normals,srcc);
    sourceconst = normals.getPool(sourcefile_index);

    return indexLocal;
  } 
    
  /**
  * @exception ClassException
  *     Failure in localization of this Attribute
  **/	
  @Override
  void localize(ConstantPool locals, ConstantPool normals)
      throws ClassException {

    super.localize(locals,normals);
    Constant srcc = normals.getPool(sourcefile_index);
    sourcefile_index =  locals.add(srcc,false);
    sourceconst = locals.getPool(sourcefile_index);
 
  }
    
  @Override
  public String toString () {	
    return "<SourceFileAttribute, file=" + sourceconst.getName() + 
      ", attributeinfo =" + super.toString() + ">";
  }
}


    
    
