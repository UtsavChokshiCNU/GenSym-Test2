package com.gensym.newclasstools;

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
	LocalVariableTableAttribute(UTF8Constant nameConstant,
		  ConstantPool constantPool,byte[] bytes, int start)
	              throws ClassException  
	{
	super(nameConstant);
	int local_variable_table_length = Attribute.readU2(bytes, start);
	start+=2;
	local_variable_table = new Vector();
      for(int i = 0; i< local_variable_table_length; i++) {
		local_variable_table.addElement(new LocalVariableTableEntry(constantPool,bytes, start));
		start += 10;
	}
}

 @Override
 void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {
   super.emit(out, cp);
   int local_variable_table_length = local_variable_table.size();
   out.writeShort(local_variable_table_length);
   for(int i = 0; i < local_variable_table_length; i++) {
     ((LocalVariableTableEntry) local_variable_table.elementAt(i)).emit(out, cp);
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
