package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class CodeAttribute extends Attribute implements RuntimeConstants {
  
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
  
  
  private static final boolean trace = false;

  /** Create a CodeAttribute by completing the partial parse of the 
   *  attribute that was started by Attribute.readAttribute();
   *  
   *  @exception ClassException
   *       A failure when parsing the bytes  
   */

  CodeAttribute(UTF8Constant nameIndex,
		ConstantPool constantPool,byte[] bytes, int start) 
       throws ClassException

  {
    super(nameIndex);
    max_stack = Attribute.readU2(bytes,start);
    max_locals = Attribute.readU2(bytes,start+=2);
    code_length = Attribute.readU4(bytes,start+=2);

    if (trace) {
      System.out.println("Max stack: " + max_stack + " Max locals: " + 
			 max_locals);
      System.out.println("Code length: " + code_length);
    }

    code = new byte[code_length];
    if (trace) 
      System.out.println("Code starts at " + (start + 4));
    System.arraycopy(bytes,start+=4,code,0,code_length);
    instructions =  Instruction.readInstructions(code,0,code_length, constantPool);
		
    start+=code_length;
    exception_table_length = Attribute.readU2(bytes,start);
    exception_table = new Vector(exception_table_length);
		
    if (trace)
      System.out.println("Exception Table length: " + 
			 exception_table_length);
		
    // Need to read in ExceptionTable here - note that the ExceptionTable
    // does it's own parsing.
    start+=2;

    for(int i = 0; i < exception_table_length; i++) { 
      exception_table.addElement(new ExceptionTableEntry(constantPool,
							 bytes,code,start));
      start += 8;
    }

    attributes_count = Attribute.readU2(bytes,start);
    start+=2; 

    // Need to read in the Attributes of the Code Attribute here
    // Otherwise nothing will work - I expect.
    attributes = new Vector();

    for(int i = 0; i < attributes_count; i++) {
      attributes.addElement(Attribute.readAttribute(constantPool,
						    bytes,start));
      if (trace)
	System.out.println("Found subattribute " + 
			   attributes.elementAt(i));
      start += (((Attribute) attributes.elementAt(i)).length + 6);
    }
    if (trace)
      System.out.println("CodeAttribute completed with " + 
			 attributes_count + " Sub Attributes");

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
    super("Code");
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
    attributes.addElement(attr);
  }

  @Override
  synchronized void emit(DataOutputStream out, ConstantPool cp)
       throws IOException, ClassException
  {
    if (trace)
      System.out.println("Emitting code attribute");

    boolean emitFailed = false;

    int offset = 0;
    int i = 0;
    ClassOutput cot = null;
    DataOutputStream dout;
    do {
      try {
	for (i = 0; i < instructions.size(); i++) {
	  Instruction instruction = (Instruction) instructions.elementAt(i);
	  instruction.offset = offset;
	  offset += instruction.size(cp);
	}
	cot = new ClassOutput(10000);
	dout = cot.out;
	// Need to catch error in emit and adjust and retry.
	for (i = 0; i < instructions.size(); i++) {
	  ((Instruction) instructions.elementAt(i)).instructionEmit(dout, cp);
	}	
      } catch (LongBranchException exception) {
	emitFailed = true;
	Instruction branch = exception.branchInstruction;
	Instruction destination = exception.destination;
	Instruction branchOverLongBranch = Instruction.makeInstruction(opc_goto, 0);
	Instruction longBranchLabel = Instruction.makeInstruction(opc_label);
	Instruction longBranch = Instruction.makeInstruction(opc_goto_w, 0);
	Instruction branchOverDestination = Instruction.makeInstruction(opc_label);
	branch.jumpDestination = longBranchLabel;
	branchOverLongBranch.jumpDestination = branchOverDestination;
	longBranch.jumpDestination = destination;
	instructions.insertElementAt(branchOverLongBranch, i+1);
	instructions.insertElementAt(longBranchLabel, i+2);
	instructions.insertElementAt(longBranch, i+3);
	instructions.insertElementAt(branchOverDestination, i+4);
      }
    } while (emitFailed);
    code = new byte[cot.bytes.size()];
    code_length = code.length;
    
    System.arraycopy(cot.bytes.toByteArray(),0,code,0,cot.bytes.size());
    // Determine the Attribute length
    length = code_length + 12 + ((exception_table == null) ? 0 
				 : exception_table.size() * 8);
    
    if (attributes != null)
      for (i = 0 ; i < attributes.size(); i++)  {
	length += ((Attribute) attributes.elementAt(i)).length;
	length += 6;
      }             
    super.emit(out, cp);
    if (trace)
      toStdout("emitting>");
    out.writeShort(max_stack);
    out.writeShort(max_locals);
    out.writeInt(code_length);
    out.write(code,0,code.length);
    ExceptionTableEntry.emit(exception_table, out, cp);
	 
    Attribute.emit(attributes, out, cp);
       
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
}




