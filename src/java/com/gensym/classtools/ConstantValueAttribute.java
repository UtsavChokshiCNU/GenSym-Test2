package com.gensym.classtools;

import java.io.*;

public class ConstantValueAttribute extends Attribute {
   
   private int constantvalue_index;
   private Constant constt;

/** Create a ConstantValueAttribute by completing the partial parse of the 
*  attribute that was started by Attribute.readAttribute();
*
* @exception ClassException
*      Failure during parsing of the byte buffer.
*/
ConstantValueAttribute(int nameIndex,
		  ConstantPool constantPool,byte[] bytes, int start)
	              throws ClassException  
{
  super(nameIndex,constantPool);
  constantvalue_index = Attribute.readU2(bytes,start);
  constt = constantPool.getPool(constantvalue_index);
  if (! constt.isValue()) 
      throw new ClassException();
}

 /**
 * @exception IOException
 *       Failure during write to output stream
 */
 @Override
 void emit(DataOutputStream out) 
    throws IOException
  {
	  super.emit(out);
	  out.writeShort(constantvalue_index);
	  	  }
/**
* @exception ClassException
*    Failure during normalization of this constant
*/
@Override
int normalize(ConstantPool locals, ConstantPool normals, int index)
	  throws ClassException {
	  	   
	  Constant consta = locals.getPool(constantvalue_index);

	  int normalindex = locals.member(consta);
	  
	  if(normalindex == -1) {
	        // Really want to put a copy in here
		    // Illegal use of setPool tut tut.
		  normals.setPool(constantvalue_index = index++,consta); 
	  }
	  else {
		  constantvalue_index = index;
		  constt = normals.getPool(constantvalue_index);
	  }
	  	return index;

	}

/**
* @exception ClassException
*    Failure during localization of this constant
*/
@Override
void localize(ConstantPool locals, ConstantPool normals)
	  throws ClassException {
	   
	  Constant consta = normals.getPool(constantvalue_index);

	  int index = normals.member(consta);	  
	  if(index == -1) { 
		  throw new ClassMergeException();
	  }
	  else {
		  constantvalue_index = index;
		  constt = locals.getPool(constantvalue_index);
	  }

}

@Override
public String toString() {
		return "ConstantValueAttribute, attributeinfo=" + super.toString() + ">"; 
}

}



