package com.gensym.classtools;

import java.io.*;

import java.util.Vector;

public class LocalVariableTableAttribute extends Attribute 
{
      private Vector local_variable_table;

      public LocalVariableTableEntry[] getLocalVariableTable()
      {
        if (local_variable_table == null)
          return new LocalVariableTableEntry[] { };
        LocalVariableTableEntry[] copy = 
          new LocalVariableTableEntry[local_variable_table.size()];
        local_variable_table.copyInto(copy);
        return copy;         
      }

	/** Create a LocalVariableTableAttribute by completing the partial parse of the 
	*  attribute that was started by Attribute.readAttribute();
	*
	*  @exception ClassException 
	*       Failure in parsing of byte buffer.
	*/
	LocalVariableTableAttribute(final int nameIndex,
			final ConstantPool constantPool, final byte[] bytes, final int start)
	              throws ClassException  
	{
	super(nameIndex,constantPool);
	int startIndex = start;
	int local_variable_table_length = Attribute.readU2(bytes, startIndex);
	startIndex += 2;
	local_variable_table = new Vector();
      for(int i = 0; i< local_variable_table_length; i++) {
		local_variable_table.addElement(new LocalVariableTableEntry(constantPool,bytes, startIndex));
		startIndex += 10;
	}
}

 @Override
 void emit(DataOutputStream out) 
    throws IOException
  {
   super.emit(out);
   int local_variable_table_length = local_variable_table.size();
   out.writeShort(local_variable_table_length);
   for(int i = 0; i < local_variable_table_length; i++) {
     ((LocalVariableTableEntry) local_variable_table.elementAt(i)).emit(out);
   }
 }

/**
* @exception ClassException
*     Failure in normalization of this Attribute
*/
@Override
int normalize(final ConstantPool locals, final ConstantPool normals, final int index)
  throws ClassException {
  int indexLocal = index;
  int local_variable_table_length =  local_variable_table.size();
  for(int i = 0; i < local_variable_table_length; i++) {
	  indexLocal = 
      ((LocalVariableTableEntry) 
        local_variable_table.elementAt(i)).normalize(locals,normals,indexLocal);
  }
  return indexLocal;
}
/**
* @exception ClassException
*     Failure in localization of this Attribute
*/
@Override
void localize(ConstantPool locals, ConstantPool normals)
throws ClassException {
  int local_variable_table_length =  local_variable_table.size();
  for(int i = 0; i < local_variable_table_length; i++) {
    ((LocalVariableTableEntry) 
        local_variable_table.elementAt(i)).localize(locals,normals);
  }
}

 @Override
 public void toStdout(String prefix) {
    super.toStdout(prefix);
    String newPrefix = prefix + "    ";
    int size = local_variable_table.size();
    for (int i = 0; i < size; i++) {
        ((LocalVariableTableEntry) 
          local_variable_table.elementAt(i)).toStdout(newPrefix);
    }
  }

@Override
public String toString() 
 {
   return "<LocalVariableTableAttribute, table_length=" + local_variable_table.size() + 
     ", attributeinfo=" + super.toString() + ">";
  }
}
