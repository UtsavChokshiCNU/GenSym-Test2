package com.gensym.classtools;

import java.io.*;

public class Constant implements Cloneable, RuntimeConstants
{
  protected int type;
  
  public int getType()
  {
    return type;
  }

  protected int size;
  
  public int getSize()
  {
    return size;
  }
  
  protected int slots = 1;
  public int getSlots()
  {
      return slots;
  }

  private static String[] typeNames =
  { "<notype>", "UTF8" , "UNICODE", "INTEGER", "FLOAT",
    "LONG" , "DOUBLE", "CLASS", "STRING", "FIELD_REF",
    "METHOD_REF", "INTERFACE_METHOD_REF", "NAME_AND_TYPE"};
  private static boolean trace = false;
  private int where = -1;
  
  protected int rawData1;
  public int getRawData1()
  {
      return rawData1;
  }

  protected int rawData2;
  public int getRawData2()
  {
      return rawData2;
  }
  
  protected int rawData3;
  public int getRawData3()
  {
      return rawData3;
  }
  
  protected int rawData4;
  public int getRawData4()
  {
      return rawData4;
  }
  
  protected String stringData;
  protected Constant cloneInProgress;
  boolean normalized = false;
  ConstantPool constantPool;
 
  protected Constant(int type) { 
    this.type = type;
  }
  
  protected Constant()  { 
  }

  private Constant(int type, Constant[] pool, int index) { 
    this.type = type;
    pool[index] = this;
  }
  
  private static int readU2(byte[] bytes, int index)
       throws ArrayIndexOutOfBoundsException {
	 return ((bytes[index] & 0xFF) << 8) + (bytes[index + 1] & 0xFF);
  }

  private static String readUTFString(byte[] bytes, int start, int length)
       throws ClassException {
	 StringBuffer buffer = new StringBuffer();
	 int i = start;
	 char unicode = 0;

	 while (i < (start + length)) {
	   char byte1 = (char) (bytes[i] & 0xFF);
	   if ((byte1 & 0x80) == 0)
	     {
	       if (byte1 == 0)
		 throw new ClassException("Bad null Char");
	       unicode = byte1;
	       i += 1;
	     }
	   else {
	     char high3bits = (char) (byte1 >> 5);
	     char byte2 =  (char) (bytes[i+1] & 0xFF);
	     if (high3bits == 6)
	       {
		 unicode = (char) (((byte1 & 0x1F) << 6) +
				   (byte2 & 0x3F));
		 i += 2;
	       }
	     else  {
	       char byte3 =  (char) (bytes[i+2] & 0xFF);
	       unicode = (char) (((byte1 & 0x0F) << 12) +
				 ((byte2 & 0x3F) << 6) +
				 (byte3 & 0x3F));
	       i += 3;
	     }
	   }
	   buffer.append(unicode);
	 }
	 return buffer.toString();
  }
 
  static Constant readConstantIntoPool
       (final Constant[] pool, final int poolIndex,
    		   final byte[] bytes, final int index)
       throws ArrayIndexOutOfBoundsException, ClassException {
	 int type = (bytes[index] & 0xFF);
	 int localIndex = index;
	 localIndex++;
	 if (trace)
	   System.out.println("  reading constant of type "+typeNames[type]);
	 Constant constant = null;
	 switch(type) {
	 case CONSTANT_UTF8: 		
	   constant = new Constant(type,pool,poolIndex);
	   int length = readU2(bytes,localIndex);
	   constant.size = length + 3;
	   constant.stringData = readUTFString(bytes, localIndex+2, length);
	   if (trace)
	     System.out.println("  UTF decode to \""+ 
				constant.stringData +"\"");
	   break;
	 case CONSTANT_UNICODE:		
	   throw new ClassException("Did not expect UNICODE constant type at: "
				    + (localIndex - 1));
	 case CONSTANT_INTEGER:		
	 case CONSTANT_FLOAT:	
	 case CONSTANT_FIELD_REF:		
	 case CONSTANT_METHOD_REF:		
	 case CONSTANT_INTERFACE_METHOD_REF:
	 case CONSTANT_NAME_AND_TYPE:	 
	   constant = new Constant(type,pool,poolIndex);
	   constant.size = 5;
	   constant.rawData1 = readU2(bytes,localIndex);
	   constant.rawData2 = readU2(bytes,localIndex+2);
	   break;
	 case CONSTANT_LONG: 		
	 case CONSTANT_DOUBLE:		
	   constant = new Constant(type,pool,poolIndex);
	   constant.size = 9;
	   constant.rawData1 = readU2(bytes,localIndex);
	   constant.rawData2 = readU2(bytes,localIndex+2);
	   constant.rawData3 = readU2(bytes,localIndex+4);
	   constant.rawData4 = readU2(bytes,localIndex+6);
	   constant.slots = 2;
	   break;
	 case CONSTANT_CLASS:		
	 case CONSTANT_STRING:		
	   constant = new Constant(type,pool,poolIndex);
	   constant.size = 3;
	   constant.rawData1 = readU2(bytes,localIndex);
	   break;
	 default: 
	   throw 
	     new ClassException("Internal error: Unknown CONSTANT pool type: "+
				type + " at " +
				(localIndex - 1));
	 }
	 return constant;
  }

  static int fillConstantPool(final ConstantPool pool, final byte[] bytes, 
			      final int index, final int number)
       throws ClassException  {
	 int i = 1; 
	 Constant[] temppool = new Constant[number];
	 int indexLocal = index;
	 if (trace)
	   System.out.println("pool length "+pool.getLength());
	 while (i < number)
	   {
	     if (trace)
	       System.out.println("reading constant i="+i+
				  " at index = "+indexLocal);
	     Constant constant =  readConstantIntoPool(temppool,i,bytes,indexLocal);
	     constant.constantPool = pool;
	     i += constant.slots;
	     indexLocal += constant.size;
	     if (trace)
	       System.out.println("read constant " + constant);
	   }
	 pool.setPool(temppool);
	 return indexLocal;
  }


  // More evidence that this needs to be abstracted fully
  // into subclasses. 
  public String getName() {
    try{
      if (type == CONSTANT_CLASS)
	return getClassName();
      if (type == CONSTANT_FIELD_REF)
	return getFieldName();
      if (type == CONSTANT_UTF8)
	return getUTF8String();
    }
    catch (Exception e) { }
    return "UnNamedConstant";
  }

  public String getClassName()
       throws ClassException {
	 if (type == CONSTANT_CLASS)
	   {
	     Constant utfConstant = constantPool.getPool(rawData1);
	     if (utfConstant == null)
	       throw new ClassException("Class Constant has no name");
	     else if (utfConstant.type != CONSTANT_UTF8)
	       throw new ClassException("Class Constant name is corrupt");
	     else
	       return utfConstant.stringData;
	   }
	 else
	   throw new ClassException("Not a CLASS constant");
  }

  public String getFieldName()
       throws ClassException {
	 if (type == CONSTANT_FIELD_REF)
	   {
	     Constant utfConstant = constantPool.getPool(rawData1);
	     if (utfConstant == null)
	       throw new ClassException("Field Constant has no name");
	     else if (utfConstant.type != CONSTANT_UTF8)
	       throw new ClassException("Field Constant name is corrupt");
	     else
	       return utfConstant.stringData;
	   }
	 else
	   throw new ClassException("Not a FIELD_REF constant");
  }

  public String getUTF8String()
       throws ClassException {
	 if (type != CONSTANT_UTF8)
	   throw new ClassException("Field Constant name is corrupt");
	 else
	   return stringData;
  }

  public void setUTF8String(String string)
  {
      stringData = string;
  }

  @Override

  public String toString()  {
    return "<Constant type="+typeNames[type]+ " name=" + getName() + 
      " Rawbytes=" + "(1) " + rawData1 + " (2) "   + rawData2 + " (3) " + 
      rawData3 + " (4) " + rawData4 + ">";
  }

  public static final void toStdout(Constant[] pool) {
    System.out.println("Summary of Constant Pool");
    for(int i = 0; i < pool.length; i++)
      System.out.println("" + i + ") " + pool[i]);
  }
             
 
  /** A simple byte-by byte equality of constants. Will not work on constants
   * that refer to diferring constant pools but are still equivalent. See
   * equal() below for the semantic equality check
   **/
  public final boolean eq(Constant c) {
    if (this.equals(c))
      return true;
    if( this.type != c.type ||
	this.size != c.size )
      return false;
    if ((c.rawData1 == rawData1) && 
	(c.rawData2 == rawData2) && 
	(c.rawData3 == rawData3) &&
	(c.rawData4 == rawData4))
      switch (type)  {
      /*case CONSTANT_CLASS:
      case CONSTANT_FIELD_REF: */
      case CONSTANT_UTF8:
	return c.getName().equals(getName());
      default:
	return true;
      }
    return false;
  }

  
  /** Semantic equality.  Can only be done in reference to particular 
   * constant pools
   */
  public boolean equalSemantic(ConstantPool pool1, ConstantPool pool2, Constant c) {  
    if (c == this)
      return true;
    switch(type) { 	  
    case CONSTANT_CLASS:
    case CONSTANT_STRING: {	
      if (trace)
	System.out.println("About to compare " + this + " and " + c);
      try {
	if (c.type != type) {
	  if (trace)
	    System.out.println("Returning false based on type");
	  return false;
	}
	else {
	  if (trace) {
          
          System.out.println(constantPool + " vs " + c.constantPool);
          System.out.println(rawData1 + " vs " + c.rawData1);

	    System.out.println("Comparing" + constantPool.getPool(rawData1) +
			       " and " + c.constantPool.getPool(c.rawData1));

        }
	  boolean result = 
	    constantPool.getPool(rawData1).equalSemantic(constantPool,
						  pool2,
				     c.constantPool.getPool(c.rawData1));  
	  if (trace)
	    System.out.println("Returning " + result + " based on analysis");
	  return result;
	}
      }
      catch (Exception e) {
	return false;
      }
    }
    case CONSTANT_FIELD_REF:	
    case CONSTANT_METHOD_REF:
    case CONSTANT_INTERFACE_METHOD_REF:
    case CONSTANT_NAME_AND_TYPE: {
      if (c.type != type) { 
	return false;
      }
      if (trace) {
	System.out.println("Comparing " + pool1.getPool(rawData1) + "at " + 
			   rawData1 + " and " +
			   pool2.getPool(c.rawData1) + " at " + 
			   c.rawData1);
	System.out.println("Comparing " + pool1.getPool(rawData2) + "at " + 
			   rawData2 + " and " +
			   pool2.getPool(c.rawData2) + " at " + 
			   c.rawData2);
	System.out.println("Pool1 =");
	constantPool.toStdout();
	System.out.println("Pool2 =");
	pool2.toStdout();
      }
      boolean result 
	= (constantPool.getPool(rawData1).equalSemantic(constantPool,
						 pool2,
				   c.constantPool.getPool(c.rawData1)) &&
			constantPool.getPool(rawData2).equalSemantic(constantPool,
							      pool2,
				       c.constantPool.getPool(c.rawData2)));
      if (trace)
	System.out.println("And the result was " + result);
      return result;
    }
    default: 
      return eq(c);  // This being the right thing to do here
    }
  }
      

  
  public boolean equalString(String s) {
    return s.equals(stringData);
  }

 
  /** Emit method for constants will emit the bytes for this constant into
   * an existing DataOutputStream
   *
   * @exception  IOException 
   *     failure when writing to output stream
   *
   * @exception ClassException
   *     failure due to unexpected constant type
   */
  void emit(DataOutputStream out)
       throws IOException, ClassException {
	  
	 // Emit the tag byte
	 out.write(type);

	 // Depending upon the type of the Constant, emit the info structure
	 // Just using rawbytes right now - may want to do this in a more
	 // structured way.

	 switch(type) {
	 case CONSTANT_UTF8: 		
	   //out.writeInt(this.size - 3);
	   out.writeUTF(this.stringData);
	   break;
    
	 case CONSTANT_UNICODE:		
	   throw new ClassException("Did not expect UNICODE constant type");

	 case CONSTANT_LONG:
	 case CONSTANT_DOUBLE:		
	   out.writeShort(rawData1);
	   out.writeShort(rawData2);
	   out.writeShort(rawData3);
	   out.writeShort(rawData4);
	   break;
    
	 case CONSTANT_CLASS:		
	 case CONSTANT_STRING:		
	   out.writeShort(rawData1);
	   break;
 
	 default:
	   out.writeShort(rawData1);
	   out.writeShort(rawData2);
	   break;
	 }
  }

  /** Is the type of a constant a value type? (long, float, double, integer 
   *  or string)
   */
  public boolean isValue() {
    switch(this.type) {
    case CONSTANT_INTEGER : 
    case CONSTANT_FLOAT :
    case CONSTANT_DOUBLE : 
    case CONSTANT_LONG : 
    case CONSTANT_STRING:
      return true ;
    default :
      return false;
    }
  }

  /** Since constants can contain references to other constants
   * then they require a localization method. This method will find the
   * existing reference to a constant inside of a pool and return the index.
   * It will recursively update all the references this constant makes to be
   * references for equal() constants that are already in the locals pool.
   *
   * @exception ClassException
   *      Failure during localization the second argument
   */
  int localize(ConstantPool locals, ConstantPool normals) 
       throws ClassException {
	 // Check for the constant itself first
	 int localindex = locals.member(normals,this);
	 int index = -100;
	 
	 // If it is present then have to check that the required ones are
	 // also present
	 if (localindex != -1) {
	   switch(type) {	  
	   case CONSTANT_CLASS:
	   case CONSTANT_STRING: {
	     index = locals.member(constantPool.getPool(rawData1));
	     rawData1 = index;
	     break;
	   }
	   case CONSTANT_FIELD_REF:	
	   case CONSTANT_METHOD_REF:
	   case CONSTANT_INTERFACE_METHOD_REF:
	   case CONSTANT_NAME_AND_TYPE: {
	     index = locals.member(constantPool,constantPool.getPool(rawData1));
	     rawData1 = index;
	     index = locals.member(constantPool,constantPool.getPool(rawData2));
	     rawData2 = index;
	     break;
	   }
	   default:
	   }
	 }
	 else {
	   System.out.println("Localize failed" + this);
	   locals.toStdout(); 
	   ClassMergeException e =  new ClassMergeException();
	   e.printStackTrace();
	   throw new ClassMergeException("Localize failed due to " + e);
	 }
	 constantPool = locals;
	 normalized = false;
       where = localindex;
	 return localindex;
  }


  /** Since constants can contain references to other constants
   * then they require a normalize() method.  If the constants referred
   * to are not present in the normals then this will add them.  The index 
   * returned is either the one passed in or the location of this constant.
   * This constant will always be put on the end, any other required constants
   *  will be added before that.
   */
  int normalize(final ConstantPool locals, final ConstantPool normals, final int index) {  
    int normalindex = normals.member(constantPool,this);
    int newRawData1  = rawData1;
    int newRawData2 = rawData2;
    int localIndex = index;
    if (trace)
      System.out.println("Normal index found:" + normalindex + " Nomalized = "
                          + normalized);
    if (normalindex == -1) {
      // Add - do different things for compound types
      switch(type) {	  
      case CONSTANT_CLASS:
      case CONSTANT_STRING: 
	{
		localIndex = constantPool.getPool(rawData1).normalize(constantPool,normals,localIndex);
        newRawData1 = normals.member(locals,constantPool.getPool(rawData1));
	  break;
	}
      case CONSTANT_FIELD_REF:	
      case CONSTANT_METHOD_REF:
      case CONSTANT_INTERFACE_METHOD_REF:
      case CONSTANT_NAME_AND_TYPE: {					 

    localIndex = constantPool.getPool(rawData1).normalize(constantPool,
							normals, localIndex);
	newRawData1 = normals.member(constantPool,constantPool.getPool(rawData1));
     	
	localIndex = constantPool.getPool(rawData2).normalize(constantPool,
							 normals, localIndex);
	newRawData2 =  normals.member(constantPool,
				   constantPool.getPool(rawData2));
	break;				
      }
      default:
      }
    
      normals.add(this, false);
      localIndex++;
      if (trace) 
	System.out.println("Adding into constant pool " +this + " at " + localIndex);
      //constantPool = normals;
      normalized = true;
      rawData1 = newRawData1;
      rawData2 = newRawData2;
      where = localIndex;
      constantPool = normals;
      return localIndex;
    }
    else {
      return normalindex;
    }
  }

  @Override

  public Object clone() {
    return clone(true);
  }

  public Object clone(boolean clonePool) {
    if (cloneInProgress != null)
      return cloneInProgress;
    Constant clone = new Constant(this.type);		
    return cloneWork(clone,clonePool);
  }

  protected Object cloneWork(Constant clone,boolean clonePool) {
    clone.rawData1 = rawData1;
    clone.rawData2 = rawData2;
    clone.rawData3 = rawData3;
    clone.rawData4 = rawData4;
    cloneInProgress = clone;
    clone.stringData = "" + stringData;
    if (clonePool)
      clone.constantPool = (ConstantPool) constantPool.clone();
    else clone.constantPool = constantPool;
    cloneInProgress = null;
    return clone;
  }

  /** Return the location of this constant in the constantPool field
   */
  public int getWhere() {	
    return where;
  }

  void setWhere(int where) {
    this.where = where; 
  }
}
