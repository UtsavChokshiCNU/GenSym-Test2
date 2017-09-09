package com.gensym.classtools;

import java.io.*;

import java.util.Vector;

public class LineNumberTableAttribute extends Attribute 
{
  private Vector line_number_table;
    
  public LineNumberTableEntry[] getLineNumberTable()
  {
    if (line_number_table == null)
      return new LineNumberTableEntry[] { };
    LineNumberTableEntry[] copy = new LineNumberTableEntry[line_number_table.size()];
    line_number_table.copyInto(copy);
    return copy;         
  }

  Vector getLineNumberTableVector()
  {
      return line_number_table;
  }

  private static final boolean trace = false;
	
  LineNumberTableAttribute(Vector entries)
    throws ClassException
  {
    super("LineNumberTable", new ConstantPool());    
    if (entries == null)
      throw new ClassException("LineNumberTableAttribute null passed to constructor");
    normalizedConstants = localConstants;
    localConstants = null;
    normalized = true;
    line_number_table = entries;
    length = (entries.size() * 4) + 2;
  }

  /** Create a LineNumberTableAttribute by completing the partial parse of the 
  *  attribute that was started by Attribute.readAttribute();
  *
  *  @exception ClassException  
  *       Failure in parsing of byte buffer.
  */
  LineNumberTableAttribute(final int nameIndex,
    final ConstantPool constantPool, final byte[] bytes, final int start)  
  	              throws ClassException  
  {
    super(nameIndex,constantPool);
    int startIndex = start;
    int line_number_table_length = Attribute.readU2(bytes, startIndex);
    startIndex += 2;
    line_number_table = new Vector();
    for(int i = 0; i< line_number_table_length; i++) {
      line_number_table.addElement(new LineNumberTableEntry(bytes, startIndex));
      startIndex += 4;
    }
    if (trace)  
      System.out.println("LineNumberTable read");
  }

 @Override
 void emit(DataOutputStream out) 
    throws IOException
 {
   super.emit(out);
   int line_number_table_length = line_number_table.size();
   out.writeShort(line_number_table_length);
   for(int i = 0; i < line_number_table_length; i++) {
     ((LineNumberTableEntry) line_number_table.elementAt(i)).emit(out);
   }  
  }

 @Override
 public void toStdout(String prefix) {
    super.toStdout(prefix);
    String newPrefix = prefix + "    ";
    int size = line_number_table.size();
    for (int i = 0; i < size; i++) {
        ((LineNumberTableEntry) 
          line_number_table.elementAt(i)).toStdout(newPrefix);
    }
  }

 @Override
 public String toString() 
 {
   return "<LineNumberTableAttrubute, table_length=" + line_number_table.size() + 
     ", attributeinfo=" + super.toString() + ">";
  }
}
