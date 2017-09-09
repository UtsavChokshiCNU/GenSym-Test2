package com.gensym.newclasstools;

import java.io.*;

public class ConstantValueAttribute extends Attribute {
   
   private Constant constt;

/** Create a ConstantValueAttribute by completing the partial parse of the 
*  attribute that was started by Attribute.readAttribute();
*
* @exception ClassException
*      Failure during parsing of the byte buffer.
*/
ConstantValueAttribute(UTF8Constant nameConstant,
		  ConstantPool constantPool,byte[] bytes, int start)
	              throws ClassException  
{
  super(nameConstant);
  int constantvalue_index = Attribute.readU2(bytes,start);
  constt = constantPool.getConstant(constantvalue_index);
  if (! constt.isValue()) 
      throw new ClassException();
}

 /**
 * @exception IOException
 *       Failure during write to output stream
 */
 @Override
 void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {
	  super.emit(out, cp);
	  out.writeShort(cp.getIndex(constt));
  }

@Override
public String toString() {
		return "ConstantValueAttribute, attributeinfo=" + super.toString() + ">"; 
}

}



