package com.gensym.newclasstools;

import java.io.*;

public class ExceptionsAttribute extends Attribute 
{
  private int number_of_exceptions;
  
      private ClassConstant[] exception_names;

      public Type[] getExceptionTypes()
      {
        if (exception_names == null)
          return new Type[] { };
        int length = exception_names.length;
        Type[] copy = new Type[length];
        for (int i =0; i < length; i++)
          copy[i] = exception_names[i].getMyClass();
        return copy;
      }
      
      private final static boolean trace = false;


	/** Create an ExceptionsAttribute by completing the partial parse of the 
	*  attribute that was started by Attribute.readAttribute();
    *
    * @exception ClassException
    *     Failure during parsing of byte buffer.
	*/
   ExceptionsAttribute(UTF8Constant nameConstant,
		  ConstantPool constantPool,byte[] bytes, int start)
	              throws ClassException  
	{
	  super(nameConstant);
	  number_of_exceptions = Attribute.readU2(bytes,start);
	  start +=2;
	  exception_names = new ClassConstant[number_of_exceptions];
	  for (int i = 0; i < number_of_exceptions; i++) {
	    int index = Attribute.readU2(bytes,start);
	    exception_names[i] = 
	      (ClassConstant)constantPool.getConstant(index);
	    start +=2;
	  }
	}

   public ExceptionsAttribute(ClassConstant[] exception_classes) throws ClassException {
	 super("Exceptions");
	 number_of_exceptions = exception_classes.length;
	 exception_names =  new ClassConstant[number_of_exceptions];
	 for (int i = 0; i < number_of_exceptions; i++) {
	   exception_names[i] = exception_classes[i];
	 }
	 length =  2 + (number_of_exceptions * 2);
	 //size = length +  6;
 }
 
 @Override
 void emit(DataOutputStream out, ConstantPool cp) 
    throws IOException, ClassException
  {
    super.emit(out, cp);
    if (trace)
      System.out.println("Emitting exception entries " + 
			 number_of_exceptions);
    out.writeShort(number_of_exceptions);
    for (int i = 0; i < number_of_exceptions; i++) {
      if (trace) 
	System.out.println("Emitting exception index table entry " + 
			   exception_names[i]);
      out.writeShort(cp.getIndex(exception_names[i]));
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
    for (int i = 0; i < exception_names.length; i++) {
      if(i < exception_names.length) {
	System.out.println(newprefix + 
			   "exception name=" + exception_names[i]);
      }
    }
    System.out.println("");
  }

}
