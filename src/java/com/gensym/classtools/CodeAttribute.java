package com.gensym.classtools;

import java.io.*;
import java.util.Vector;

public class CodeAttribute extends Attribute {
  
  //********************* Properties **************
  private int max_stack;
  public int getMaxStack()
  {
    return max_stack;
  }

  private int max_locals;
  public int getMaxLocals()
  {
    return max_locals;
  }

  private int code_length;  
  private byte[] code;
  public byte[] getCode() 
  {
    if (code == null)
      return null;
    int length = code.length;
    byte[] copy = new byte[length];
    for (int i =0; i < length; i++)
      copy[i] = code[i];
    return copy;
  }

  private Vector instructions;
  public Instruction[] getInstructions()
  {
    if (instructions == null)
      return new Instruction[] { };
    int length = instructions.size();
    Instruction[] copy = new Instruction[length];
    for (int i =0; i < length; i++)
      copy[i] = (Instruction) instructions.elementAt(i);
    return copy;
  }
  
  private int exception_table_length; 
  private Vector exception_table;
  public ExceptionTableEntry[] getExceptionTable()
  {
    if (exception_table == null)
      return new ExceptionTableEntry[] { };
    int length = exception_table.size();
    ExceptionTableEntry[] copy = new ExceptionTableEntry[length];
    for (int i =0; i < length; i++)
      copy[i] = (ExceptionTableEntry) exception_table.elementAt(i);
    return copy;    
  }

  private int attributes_count;
  private Vector attributes;
  public Attribute[] getAttributes() 
  {
    if (attributes == null)
      return new Attribute[] { };
    Attribute[] attributeArray = new Attribute[attributes.size()];
    attributes.copyInto(attributeArray);
    return attributeArray;        
  }
  
  
  private static boolean trace = false;

  /** Create a CodeAttribute by completing the partial parse of the 
   *  attribute that was started by Attribute.readAttribute();
   *  
   *  @exception ClassException
   *       A failure when parsing the bytes  
   */
  CodeAttribute(final int nameIndex,
		  final ConstantPool constantPool, final byte[] bytes, final int start) 
       throws ClassException
  {
    super(nameIndex,constantPool);
    int startIndex = start;
    max_stack = Attribute.readU2(bytes, startIndex);
    max_locals = Attribute.readU2(bytes, startIndex += 2);
    code_length = Attribute.readU4(bytes, startIndex += 2);

    if (trace) {
      System.out.println("Max stack: " + max_stack + " Max locals: " + 
			 max_locals);
      System.out.println("Code length: " + code_length);
    }

    code = new byte[code_length];
    if (trace) 
      System.out.println("Code starts at " + (startIndex + 4));
    System.arraycopy(bytes, startIndex += 4, code, 0, code_length);
    instructions =  Instruction.readInstructions(code,0,code_length);
		
    startIndex += code_length;
    exception_table_length = Attribute.readU2(bytes, startIndex);
    exception_table = new Vector(exception_table_length);
		
    if (trace)
      System.out.println("Exception Table length: " + 
			 exception_table_length);
		
    // Need to read in ExceptionTable here - note that the ExceptionTable
    // does it's own parsing.
    startIndex += 2;

    for(int i = 0; i < exception_table_length; i++) { 
      exception_table.addElement(new ExceptionTableEntry(constantPool,
							 bytes,code, startIndex));
      startIndex += 8;
    }

    attributes_count = Attribute.readU2(bytes, startIndex);
    startIndex += 2; 

    // Need to read in the Attributes of the Code Attribute here
    // Otherwise nothing will work - I expect.
    attributes = new Vector();

    for(int i = 0; i < attributes_count; i++) {
      attributes.addElement(Attribute.readAttribute(constantPool,
						    bytes, startIndex));
      if (trace)
	System.out.println("Found subattribute " + 
			   attributes.elementAt(i));
      startIndex += (((Attribute) attributes.elementAt(i)).length + 6);
    }
    if (trace)
      System.out.println("CodeAttribute completed with " + 
			 attributes_count + " Sub Attributes");

  }

  private boolean hasBeenLdcStripped = false;

  void stripLdcInstructions()
       throws ClassException
  {

    /* Below should probably be in its own method and
       called from localize() only when necessary
       */
    
    LineNumberTableAttribute lineAttr 
      = getLineNumberTableAttribute();
    Vector line_number_table;
    if (lineAttr == null)
      line_number_table = null; 
    else line_number_table = lineAttr.getLineNumberTableVector();
    
    EmitState state = 
      new EmitState((normalized ? normalizedConstants : localConstants),
		    instructions,
		    exception_table,
		    line_number_table);
      
    
    if (trace)
      {
	System.out.println("Before adding the jump targets");
	Instruction.toStdout(getInstructions(),"");
      }

    int increaseInSize = state.addAllLabels(true, false);
    
    if (trace)
      System.out.println("IncreaseInSize = " + increaseInSize);
       
    code_length += increaseInSize;
    length += increaseInSize;
    
    if (trace)
      {
	System.out.println("\n\nAfter adding the jump targets");
	Instruction.toStdout(getInstructions(),"");
      }

    state.resolveAllLabels();
    
    if (trace) {
      System.out.println("\n\nAfter replacing the jump targets");
      Instruction.toStdout(getInstructions(),"");
    }

    hasBeenLdcStripped = true;
  }
  
  public LineNumberTableAttribute getLineNumberTableAttribute()
  {
    if (attributes == null)
      return null;
    for (int i = 0; i < attributes.size(); i++)
      {
	Attribute attr = (Attribute) attributes.elementAt(i);
	if (attr instanceof LineNumberTableAttribute)
	  return (LineNumberTableAttribute) attr;
      }
    return null;
  }
  

  /** Create a CodeAttribute from it's constituent parts.
   */
  public CodeAttribute(ConstantPool constantPool,
		       Vector instructions,
		       Vector exception_table,
		       int max_stack,
		       int max_locals)
       throws ClassException
  {
    super("Code",constantPool);
    /*instructions.copyInto(this.instructions 
      = new Instruction[instructions.size()]);
      */
    this.instructions = (Vector) instructions.clone();
    this.exception_table = (Vector) exception_table.clone(); 
    /*
      exception_table.copyInto(this.exception_table 
      = new ExceptionTableEntry[exception_table.size()]);
      */
    this.max_locals = max_locals;
    this.max_stack = max_stack;
    normalizedConstants = constantPool;
  }

  Vector getRawInstructions()
  {
    return instructions;
  }

  Vector getRawExceptionTable()
  {
    return exception_table;
  }

  void add(Attribute attr) throws ClassException
  {
    if (attributes == null)
      attributes =  new Vector();
    ConstantPool toAdd = attr.getConstantPool();
    if (normalized) {
      normalizedConstants.add(toAdd);
      attr.localize(normalizedConstants,toAdd);
    }
    else { 
      localConstants.add(toAdd);
      attr.localize(localConstants,toAdd);
    }
    attributes.addElement(attr);
  }


  /** The normalize method on CodeAttribute, completes adding to normals any
   * constants that are referenced in the Attribute and have not already
   * been added to the normals array.  This method uses the normalize() method
   * defined in the Attribute superclass.  The major work that this method does
   * is to change the constant references inside the actual code bytes
   * themselves
   *
   *  @exception ClassException
   *       A failure when normalizing this attribute  
   */
  @Override
  int normalize(final ConstantPool locals, final ConstantPool normals, final int index)
       throws ClassException
  {
        
	
    stripLdcInstructions();

    int normalizedIndex = super.normalize(locals,normals,index);

    for(int i = 0; i < instructions.size(); i++) 
    	normalizedIndex = ((Instruction) instructions.elementAt(i)).normalize(locals,normals,normalizedIndex,code);
	
    if (trace)
      System.out.println("Length of exception table before normalization: " + exception_table.size());
    for(int i = 0; i < exception_table.size(); i++) 
    	normalizedIndex = ((ExceptionTableEntry) exception_table.elementAt(i)).normalize(locals,normals,normalizedIndex);
	

    for(int i = 0; i < attributes.size(); i++) 
    	normalizedIndex = ((Attribute) attributes.elementAt(i)).normalize(locals,
							      normals,
							      normalizedIndex);

    if (trace)
      System.out.println("Completed normalizing CodeAttribute");


    return normalizedIndex;
  }

  /** Localize assumes that all constants that are necessary will already
   * have been added to the locals.  If there is a constant that is missing
   * then this method will throw an exception.
   *
   *  @exception ClassException
   *       A failure when localizing this attribute  
   */
  @Override
  void localize(ConstantPool locals, ConstantPool normals)
       throws ClassException
  {
    super.localize(locals,normals);
    for(int i = 0; i < instructions.size(); i++) 
      ((Instruction) instructions.elementAt(i)).localize(locals,normals,code);

    for(int i = 0; i < exception_table.size(); i++)
      ((ExceptionTableEntry) exception_table.elementAt(i)).localize(locals,normals);

    if (attributes != null)
      for(int i = 0; i < attributes.size(); i++) 
	((Attribute) attributes.elementAt(i)).localize(locals,normals);

    if (trace)
      System.out.println("Completed localizing CodeAttribute");
  }

  @Override
  void emit(DataOutputStream out)
       throws IOException
  {
    if (trace)
      System.out.println("Emitting code attribute");
	  
    // If we do not have the code defined then
    // we have to calculate it from the instructions
    if (code == null ||  hasBeenLdcStripped) {
      ClassOutput cot = new ClassOutput(10000);
      DataOutputStream dout = cot.out;
      for (int i = 0; i < instructions.size(); i++) {
	((Instruction) instructions.elementAt(i)).emit(dout);
      }	
      code = new byte[cot.bytes.size()];
      code_length = code.length;

      System.arraycopy(cot.bytes.toByteArray(),0,code,0,cot.bytes.size());
      // Determine the Attribute length
      length = code_length + 12 + ((exception_table == null) ? 0 
				   : exception_table.size() * 8);

      if (attributes != null)
	for (int i =0 ; i < attributes.size(); i++)  {
	  length += ((Attribute) attributes.elementAt(i)).length;
	  length += 6;
	}             
    }
    super.emit(out);
    if (trace)
      toStdout("emitting>");
    out.writeShort(max_stack);
    out.writeShort(max_locals);
    out.writeInt(code_length);
    out.write(code,0,code.length);
    ExceptionTableEntry.emit(exception_table,out);
	 
    Attribute.emit(attributes,out);
       
  }

  @Override
  public void toStdout(String prefix) {
    super.toStdout(prefix);
    String newprefix = prefix + "    ";
    Instruction.toStdout(instructions,newprefix);
    System.out.println("");
    ExceptionTableEntry.toStdout(exception_table,newprefix);
    System.out.println("");
    Attribute.toStdout(attributes,newprefix);
    System.out.println("");
  }

  @Override
  public String toString() {
    return "<CodeAttribute, max_stack=" + max_stack +
      ", max_locals=" + max_locals +
      ", code_length=" + code_length +
      ", attributeinfo=" + super.toString() + ">";
  }

  static void setTrace(boolean traceOn) {
    trace = traceOn;
  }

  boolean isLdcStripped(){
    return hasBeenLdcStripped;
  }
}




