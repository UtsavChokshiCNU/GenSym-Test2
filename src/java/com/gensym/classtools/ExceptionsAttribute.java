package com.gensym.classtools;

import java.io.*;

public class ExceptionsAttribute extends Attribute 
{
	private int number_of_exceptions;
	
      private int[] exception_index_table;
	public int[] getExceptionIndexTable() 
      {
        if (exception_index_table == null)
          return new int[] { };
        int length = exception_index_table.length;
        int[] copy = new int[length];
        for (int i =0; i < length; i++)
          copy[i] = exception_index_table[i];
        return copy;
      }

      private String[] exception_names;
      public String[] getExceptionNames()
      {
        if (exception_names == null)
          return new String[] { };
        int length = exception_names.length;
        String[] copy = new String[length];
        for (int i =0; i < length; i++)
          copy[i] = exception_names[i];
        return copy;
      }
      
      private static final boolean trace = false;


	/** Create an ExceptionsAttribute by completing the partial parse of the 
	*  attribute that was started by Attribute.readAttribute();
    *
    * @exception ClassException
    *     Failure during parsing of byte buffer.
	*/
   ExceptionsAttribute(final int nameIndex,
		  final ConstantPool constantPool, final byte[] bytes, final int start)
	              throws ClassException  
	{
		super(nameIndex, constantPool);
		int startIndex = start;
		number_of_exceptions = Attribute.readU2(bytes,startIndex);
		exception_index_table = new int[number_of_exceptions];
		startIndex +=2;
		exception_names = new String[number_of_exceptions];
		for (int i = 0; i < number_of_exceptions; i++) {
			int index = Attribute.readU2(bytes, startIndex);
			exception_names[i] = 
				constantPool.getPool(index).getClassName();
			exception_index_table[i] = index;
			startIndex +=2;
		}
	}

   public ExceptionsAttribute(ConstantPool pool, ClassConstant[] exception_classes) {
	 super("Exceptions",pool);
	 number_of_exceptions = exception_classes.length;
	 exception_index_table =  new int[number_of_exceptions];
	 exception_names =  new String[number_of_exceptions];
	 for (int i = 0; i < number_of_exceptions; i++) {
			exception_index_table[i] = exception_classes[i].getWhere();
			exception_names[i] = exception_classes[i].getName();
	 }
	 length =  2 + (number_of_exceptions * 2);
	 //size = length +  6;
	 normalizedConstants = pool;
 }
 
 @Override
 void emit(DataOutputStream out) 
    throws IOException
  {
	  super.emit(out);
      if (trace)
		  System.out.println("Emitting exception entries " + 
			                    number_of_exceptions);
	  out.writeShort(number_of_exceptions);
      for (int i = 0; i < number_of_exceptions; i++) {
		if (trace) 
			System.out.println("Emitting exception index table entry " + 
			exception_index_table[i]);
        out.writeShort(exception_index_table[i]);
	  }	  	  
}

 /** The normalize method on ExceptionsAttribute, completes adding to normals any
  * constants that are referenced in the Attribute and have not already
  * been added to the normals array.  This method uses the normalize() method
  * defined in the Attribute superclass.
  *
  * @exception ClassException
  *        Failure during normalization of this Attribute
  */
  @Override
  int normalize(final ConstantPool locals, final ConstantPool normals, final int index) 
     throws ClassException
  {
	  	  int normalizedIndex = super.normalize(locals,normals,index);
		  for (int i =0; i < number_of_exceptions; i++){
			  Constant exceptc = locals.getPool(exception_index_table[i]);
		  	  normalizedIndex = exceptc.normalize(locals,normals,normalizedIndex);
			  exception_index_table[i] = normals.member(normals,exceptc);
		  }	           
		  return normalizedIndex;
  }


  /**
  * @exception ClassException
  *        Failure during localization of this Attribute
  */
@Override
void localize(ConstantPool locals, ConstantPool normals)
    throws ClassException {
	  super.localize(locals,normals);
	  localConstants = locals;
	  for (int i =0; i < number_of_exceptions; i++){
		  Constant exceptc = normals.getPool(exception_index_table[i]);
		  exception_index_table[i] =  exceptc.localize(locals,normals);
	  }
}

@Override
public String toString() {
		return "<ExceptionsAttribute, number=" + number_of_exceptions + 
			    ", attributeinfo=" + super.toString() + ">";
}

@Override
public void toStdout(String prefix) {
		super.toStdout(prefix);
		String newprefix = prefix + "    ";
		for (int i = 0; i < exception_index_table.length; i ++) {
				if(i < exception_names.length) {
					System.out.println(newprefix + "index in constant pool=" + exception_index_table[i] +
											",exception name=" + exception_names[i]);
				}
		}
		System.out.println("");
}

}
