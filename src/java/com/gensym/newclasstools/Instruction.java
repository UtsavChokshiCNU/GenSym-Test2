package com.gensym.newclasstools;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.util.Vector;
import java.util.Hashtable;

public class Instruction extends Info implements RuntimeConstants 
{
  private int opcode;
  public int getOpcode()
  {
    return opcode;
  }

  private String name;
  @Override
  public String getName()
  {
    return name;
  }

  private byte[] bytes;
  /** Returns a copy of the byte array contained
   * in this instruction
   */
  public byte[] getBytes()
  {
    if (bytes == null)
      return new byte[] { };
    int length = bytes.length;
    byte[] copy = new byte[length];
    for (int i =0; i < length; i++)
      copy[i] = bytes[i];
    return copy;
  }

  Instruction jumpDestination = null;
  Instruction jumpDestination2 = null;
  int jumpTagIfAny2 = -1;
  long tryStartIfAny = -1;
  int exceptionIfAny = -1;
  String labelNameIfAny = null;
  int lineNumberIfAny = -1;
  Constant constant;

  private static final boolean trace = false;

  //********************* Constructors ***************************

  /** Create an instruction of the type given by the first byte in the array, 
   * using all the bytes in the array.  This constructor is the relatively
   * fast one because it assumes the opcode has been calculated
   * correctly and that the array is of the appropriate length.
   */
  private Instruction(int opcde, int start, int length, byte[] btes) {
    bytes = new byte[length];
    opcode = opcde;
    name = opcNames[opcode];
    System.arraycopy(btes,start,bytes,0,length);
    if (trace) {
      System.out.println("Instuction found : " + name + 
			 " Length: " + length + " Bytes found " +
			 toDecimalString(bytes));
    }
  }

  private Instruction(int opcode) {	
    this.opcode = opcode;
  }

  /** 
   * Static method for creating a new instruction.  Decided to do this rather
   * than have 255 subclasses of Instruction which would be messy.  This is
   * messy in it's own way - all users of this facility will have to implement 
   * RunTimeConstants. The reason I have defined five versions of this method 
   * is that I do not want users of this facility to have to create byte
   * arrays for arguments.  The reason that integer is the type of the
   * arguments is that the indexes into the constant pool are specified as
   * one argument under this scheme rather than two. This method will
   * automatically covert those indexes into the  constant pools into the
   * appropriate two bytes. Note that if the user of this  facility specifies
   * an instruction type or arguments that are invalid this method will always
   * return the null instruction.  This is to relieve the informed user
   * from needing to write try{}catch() {} forms around all uses of this
   *  method.
   */
  public static Instruction makeInstruction(int opcode) {
    if ((opcode < 0) || (opcode < opcLengths.length)) {
      Instruction ins = new Instruction(opcode);
      ins.bytes = new byte[1];
      ins.bytes[0] = (byte) opcode;
      return ins;
    }
    else {
      return makeNullInstruction();
    } 
  }

  public static Instruction makeInstruction(int opcode, long longBranch)
    throws ClassException
  {
    throw new ClassException("branches longer than 32K are not yet supported");
  }

  public static Instruction makeInstruction(int[] args) {
    ByteArrayOutputStream baob = new ByteArrayOutputStream();
    int opcode = args[0];
    int startIndex = opcStartMultiByteValue[opcode];
    if ((opcode >= 0) & (opcode < opcLengths.length)) {
      baob.write(opcode);
      int i = 1;
      if (opcNames[opcode].equals("wide")) {
	if (args.length == 3) {				
	  baob.write((byte) args[i]);
	  i++;
	  baob.write((byte) ((args[i] >>> 8) & 0xFF));
	  baob.write((byte) (args[i] & 0xFF));
	}
	else if (args.length == 4) {
	  baob.write((byte) args[i]);
	  i++;
	  baob.write((byte) ((args[i] >>> 8) & 0xFF));
	  baob.write((byte) (args[i] & 0xFF));		
	  i++;
	  baob.write((byte) ((args[i] >>> 8) & 0xFF));
	  baob.write((byte) (args[i] & 0xFF));		
	}
	else return makeNullInstruction();
      }
      else 
	for (; i < args.length; i++) {
	  if (startIndex == i) {
	    baob.write((byte) ((args[i] >>> 8) & 0xFF));
	    baob.write((byte) (args[i] & 0xFF));
	  }
	  else {
	    baob.write((byte) args[i]);
	  }
	}
      Instruction ins  = new Instruction(opcode);
      ins.bytes = baob.toByteArray();
      return ins;
    }
    else {
      return makeNullInstruction();
    }
  }


  public static Instruction makeInstruction(int opcode, int arg1) {
    if (opcode < 0) {
      Instruction ins  = new Instruction(opcode);
      ins.bytes = new byte[2];
      ins.bytes[0] = (byte) opcode;
      ins.bytes[1] = (byte) arg1;
      return ins;
    }
    else if (opcode < opcLengths.length) {
      Instruction ins  = new Instruction(opcode);
      int startIndex = opcStartMultiByteValue[opcode];
      if (startIndex == 1) {
	ins.bytes = new byte[3];
	ins.bytes[0] = (byte) opcode;
	ins.bytes[1] =  (byte) ((arg1 >>> 8) & 0xFF);
	ins.bytes[2] = (byte) (arg1 & 0xFF);
      }
      else {
	ins.bytes = new byte[2];
	ins.bytes[0] = (byte) opcode;
	ins.bytes[1] = (byte) arg1;
      }	
      return ins;
    }
    else {
      return makeNullInstruction();
    }
  }

  public static Instruction makeInstruction(int opcode, int arg1, int arg2) {
    int[] args = {opcode, arg1, arg2};
    return makeInstruction(args);
  }

  public static Instruction makeInstruction(int opcode, int arg1,
					    int arg2, int arg3) {
    int[] args = {opcode, arg1, arg2, arg3};
    return makeInstruction(args);
  }

  public static Instruction makeInstruction(int opcode, int arg1, 
					    int arg2, int arg3, int arg4) {
    int[] args = {opcode, arg1, arg2, arg3, arg4};
    return makeInstruction(args);
  }

  public static Instruction makeInstruction(int opcode, Constant constant) {
    Instruction result;
    if (opcStartConstantPoolIndex[opcode] == 1) {
      // bytes for constant reference get filled in later.
      result = makeInstruction(new int[] {opcode, 0});
      result.constant = constant;
      return result;
    } else {
      return makeNullInstruction();
    }
  }

  public static Instruction makeInstruction(int opcode, Constant constant, int arg1) {
    Instruction result;
    if (opcStartConstantPoolIndex[opcode] == 1) {
      // bytes for constant reference get filled in later.
      result = makeInstruction(new int[] {opcode, 0, arg1});
      result.constant = constant;
      return result;
    } else {
      return makeNullInstruction();
    }
  }

  public static Instruction makeInstruction(int opcode, Constant constant, int arg1, int arg2) {
    Instruction result;
    if (opcStartConstantPoolIndex[opcode] == 1) {
      // bytes for constant reference get filled in later.
      result = makeInstruction(new int[] {opcode, 0, arg1, arg2});
      result.constant = constant;
      return result;
    } else {
      return makeNullInstruction();
    }
  }



  private static Instruction makeNullInstruction() {
    Instruction ins = new Instruction(0);
    ins.bytes = new byte[1];
    ins.bytes[0] = 0;
    return ins;
  }

  
  //********************* Static fields and Operations **************

  /**
   * Return an array of instructions atfer having parsed the bytes
   * array that is passed as the first argument starting at the start index
   * for length bytes.  If the bytes are corrupt then this will throw an
   *  exception
   */ 
					    static Vector readInstructions(byte[] bytes, int start, int length, ConstantPool constantpool)
					  throws ClassException
  {
    int nextop = 0;
    int nextlength=0;
    int nextstep;
    int instructsfound=0;
    byte bytecopies[];
    // Maximim amount of space required cannot exceed length because 
    // instructions  must take at least one byte each
    Vector instructs = new Vector(length); 
		
    if (trace) {
      for (int i = start; i <(start + length); i++) {
	System.out.println("Bytes[" + i +"] = " 
			   + (int) (bytes[i] & 0xFF));
      }
      System.out.println("Start Parsing operators : " + start);
    }
		
    for (int i = start; i < (start + length);i+=nextlength) {	 
      nextop = (bytes[i] & 0xFF);
	if(nextop < opcLengths.length) {
	  if (trace)
	    System.out.println("Opcode found: " +
			       nextop + " Index: " + i);
	  nextlength = determineInstructionLength (nextop, i, bytes);
	  if (trace)
	    System.out.println("Opcode length found: " +  nextlength);
	  // handle the odd case of the wide operator
	  if (nextlength == WIDE_MARKER_LENGTH) {
	    int subop = (bytes[i + 1] & 0xFF);
	    if (subop == opc_iinc)
	      nextlength = WIDE_IINC_LENGTH; 
	    else {
	      if (subop >= opcLengths.length)
		throw new ClassException("Undefined Operator found in wide instruction " + subop); 
	      switch (subop) {
	      case opc_aload:
	      case opc_iload:
	      case opc_fload:
	      case opc_dload:
	      case opc_lload:
	      case opc_astore:
	      case opc_istore:
	      case opc_fstore:
	      case opc_dstore:
	      case opc_lstore: {
		nextlength = WIDE_OTHER_LENGTH;
		break;		
	      }
 	      default: throw new ClassException("Invalid Operator found in wide instruction : #" + 
 						Integer.toHexString(subop) + " = " + opcNames[subop]);

	      }
	    }
	  }
	  Instruction newInstruction =
	    new Instruction(nextop, i, nextlength, bytes);
	  int constantstart = opcStartConstantPoolIndex[nextop];
	  if (constantstart > 0) {
	    if (opcStartMultiByteValue[nextop] == constantstart) {
	      newInstruction.constant =
		constantpool.getConstant(newInstruction.get2ByteValue(constantstart));
	    } else {
	      newInstruction.constant =
		constantpool.getConstant((bytes[i + constantstart] & 0xFF));
	    }
	  }
	  instructs.addElement(
			       new Instruction(nextop, i, nextlength, bytes));
	       
	  instructsfound++;
	}
    }
		
    // Resize the Instructions Array that has been created
    // if it is larger than the number of instructions that were added
	
    /*
      if( instructsfound < instructs.size()) {
      Instruction[] shorterinstructs = new Instruction[instructsfound];
      System.arraycopy(instructs,0,shorterinstructs,0,instructsfound);
      instructs = shorterinstructs;
      }
      */
        
    return instructs;
  }

  private static boolean isDefiniteLengthInstruction (int nextop) {
    return opcLengths[nextop] >= 0;
  }
 
  /**
   * Returns the number of bytes occupied by an instruction.
   * Written specially for handling variable length instructions
   * lookupswitch and tableswitch.
   */
  private static int determineInstructionLength (int opCode, int index, byte[] bytes) throws ClassException {
    if (isDefiniteLengthInstruction(opCode))
      return opcLengths[opCode];
     
    int startIndex = index;
    while ((++index)%4 != 0) {
      if ((bytes[index]&0xFF) != 0)
 	throw new ClassException ("Illegal padding in instruction " + opCode + " at index " + index);
    }
    int instrLength;
    if (opCode == 0xAA) { // tableswitch
      int defaultIndex = Attribute.readU4(bytes, index);
      index += 4;
      int lowIndex = Attribute.readU4(bytes, index);
      index += 4;
      int highIndex = Attribute.readU4(bytes, index);
      index +=4;
      instrLength =  (index - startIndex) + (highIndex - lowIndex + 1)*4;
    } else { // must be 0xAB = lookupswitch
      int defaultIndex = Attribute.readU4(bytes, index);
      index +=4;
      int numPairs = Attribute.readU4(bytes, index);
      index +=4;
      instrLength = (index - startIndex) + numPairs*2*4;
    }
    return instrLength;
  }
 

  // ******************** Predicates ************************

  public boolean isIfInstruction() {
    switch (opcode)  {
    case opc_ifeq:
    case opc_ifne:
    case opc_iflt:
    case opc_ifge:
    case opc_ifgt:
    case opc_ifle:
    case opc_if_icmpeq:
    case opc_if_icmpne:
    case opc_if_acmpeq:
    case opc_if_acmpne:
    case opc_ifnonnull:
    case opc_ifnull:  
      return true;
    default: return false;
    }
  }

  /** True if the instruction represents either a return or
   * an exception being thrown
   */
  public boolean isReturnOrThrowInstruction() {
    switch (opcode)  {
    case opc_ret:
    case opc_return:
    case opc_ireturn:
    case opc_freturn:
    case opc_lreturn:
    case opc_dreturn:
    case opc_areturn:
    case opc_athrow:
      return true;
    default: return false; 
    }
  }
	

  //******************* Output Operations ******************************
	
  @Override
  public String toString() {
    if (opcode > 0)
      return "<Instruction, name=" + opcNames[opcode] +
	",opcode=" + opcode + 
	",length=" + bytes.length +
	",rawBytes=" + toDecimalString(bytes) + 
	">";
    else {
      switch (opcode) {
      case opc_label:
	return "<Instruction, name=label, opcode = -1, length = 0>";    
      default: return "<Instruction, opcode=" + opcode +", rawBytes=" +
		 toDecimalString(bytes) + ">";                                                
      }
    }
  }
	
  private String toDecimalString(byte[] bts) {
    if (bts == null) 
      return null;
    StringBuffer newints = new StringBuffer();
    newints.append("" + (bts[0] & 0xFF));
    for (int i =1; i < bts.length; i++)
      newints.append(" " + (bts[i] & 0xFF));
    return newints.toString();
  }
	
  private String toHexString(byte[] bts) {
    return "";
  }

  public static void toStdout(Instruction[] instructs,String prefix) {
    System.out.println(prefix + "Instructions");
    System.out.println(prefix + "------------");
    Info.toStdout(instructs,prefix);
  }

  //******************* Operations using an instance *******************


  public int get2ByteValue(int startIndex) throws ClassException
  {
    if (opcStartMultiByteValue[opcode] != startIndex)
      throw new ClassException("Not a multibyte index - get2ByteValue failed");
    return ((bytes[startIndex] << 8) | (bytes[startIndex + 1] & 0xFF));		
  }

  public void set2ByteValue(int startIndex, int value) 
  {
    if (opcStartMultiByteValue[opcode] != startIndex)
      throw new Error("Not a multibyte index - set2ByteValue failed");
    bytes[startIndex] = (byte)((value >>> 8) & 0xFF);
    bytes[startIndex + 1] = (byte) (value & 0xFF);
  } 

  public long get4ByteValue(int startIndex) throws ClassException
  {
    return ((bytes[startIndex] << 24) |
	    (bytes[startIndex+1] << 16) |
	    (bytes[startIndex+2] << 8) |
	    (bytes[startIndex+3] & 0xFF));		
  }

  public void set4ByteValue(int startIndex, int value)
  {
    bytes[startIndex] = (byte) ((bytes[startIndex] >>> 24) & 0xFF);
    bytes[startIndex + 1] = (byte) ((bytes[startIndex + 1] >>> 16) & 0xFF);
    bytes[startIndex + 2] = (byte) ((bytes[startIndex + 2] >>> 8) & 0xFF);
    bytes[startIndex + 3] = (byte) (bytes[startIndex + 3] & 0xFF);
  }

  // Different name, since it can throw more exceptions than other emit methods.
  void instructionEmit(DataOutputStream dout, ConstantPool constantpool) throws IOException, LongBranchException {

    boolean substituteInstructionEmitted = false;

    // Need to encode jumpDestination into bytes, and throw an error if
    // it doesn't fit.
    if (opcode < 0) return;
    int constantstart = opcStartConstantPoolIndex[opcode];
    if (constantstart > 0) {
      if (trace) {
	if (constant == null) {
	  System.out.println("Null constant in instruction #" + opcode + ": " + opcNames[opcode]);
	}
      }
      if (constantstart == opcStartMultiByteValue[opcode]) {
	set2ByteValue(constantstart, constantpool.getIndex(constant));
      } else {
	int index = constantpool.getIndex(constant);
	if (index < 256) {
	  bytes[constantstart] = (byte)index;
	} else {
	  if (opcode == opc_ldc) {
	    Instruction longLoad =  makeInstruction(opc_ldc_w, constant);
	    longLoad.instructionEmit(dout, constantpool);
	    substituteInstructionEmitted = true;
	  } else {
	    throw new Error("Instruction with unfixable long constant: " + this);
	  }
	}
      }
    }
    if (opcode == opc_tableswitch || opcode == opc_lookupswitch) {
      throw new Error("switch instructions not yet supported");
    }
    if (opcBranchStart[opcode] > 0) {
      int branchDistance = jumpDestination.offset - offset;
      if (-32768 < branchDistance && branchDistance < 32768) {
	set2ByteValue(opcBranchStart[opcode], branchDistance);
      } else {
	if (opcode == opc_goto_w || opcode == opc_jsr_w) {
	  set4ByteValue(opcBranchStart[opcode], branchDistance);
	} else {
	  throw new LongBranchException(this, this.jumpDestination);
	}
      }
    }
    if(opcode >= 0 && (!substituteInstructionEmitted))
      dout.write(bytes); 
  }

  public int size(ConstantPool cp) {
    if (opcode == opc_ldc && cp.getIndex(constant) > 255)
      return bytes.length + 1;
    if (opcode < 0)
      return 0;
    return bytes.length;
  }

  int offset;

  //*************  Static Methods for emitting from a group of instructions ***

  static final void emitArrayLoadInstruction(EmitState state, Type tpe) 
       throws ClassException
  {
    Instruction ins;
    if (tpe.isShortType()) 
      ins = Instruction.makeInstruction(opc_saload);
    else if (tpe.isByteType()) 
      ins = Instruction.makeInstruction(opc_baload);	
    else if (tpe.isCharType()) 
      ins = Instruction.makeInstruction(opc_caload);
    else if (tpe.isLongType()) 
      ins = Instruction.makeInstruction(opc_laload);
    else if (tpe.isFloatType()) 
      ins = Instruction.makeInstruction(opc_faload);
    else if (tpe.isDoubleType()) 
      ins = Instruction.makeInstruction(opc_daload); 
    else if (tpe.isReferenceType())
      ins = Instruction.makeInstruction(opc_aaload);
    else ins = Instruction.makeInstruction(opc_iaload);
    if (! (tpe.isLongType() | tpe.isDoubleType()))
      state.popStack();
    state.instructions.addElement(ins);
  }


  static final void emitArrayStoreInstruction(EmitState state, Type tpe) 
       throws ClassException
  {
    Instruction ins2;
    if (tpe.isReferenceType())
      ins2 = Instruction.makeInstruction(opc_aastore);
    else if (tpe.isBooleanType()) 
      ins2 = Instruction.makeInstruction(opc_bastore);
    else if (tpe.isCharType()) 
      ins2 = Instruction.makeInstruction(opc_castore);
    else if (tpe.isFloatType())
      ins2 = Instruction.makeInstruction(opc_fastore);
    else if (tpe.isDoubleType())
      ins2 = Instruction.makeInstruction(opc_dastore);
    else if (tpe.isByteType())
      ins2 = Instruction.makeInstruction(opc_bastore);
    else if (tpe.isShortType())
      ins2 = Instruction.makeInstruction(opc_sastore);
    else if (tpe.isLongType())
      ins2 = Instruction.makeInstruction(opc_lastore);
    else ins2 = Instruction.makeInstruction(opc_iastore);
    state.instructions.addElement(ins2);
    if (tpe.isLongType() | tpe.isDoubleType())
      state.popStack(4);
    else state.popStack(3);
  }

  static final void emitPlusInstruction(EmitState state, Type expressionType) 
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_iadd);
      state.popStack();
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_fadd);
      state.popStack();
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dadd);
      state.popStack(2);
    }
    else {
      ins = Instruction.makeInstruction(opc_ladd);
      state.popStack(2);
    }
		
    state.instructions.addElement(ins);
  }

  static final void emitMinusInstruction(EmitState state, Type expressionType) 
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_isub);
      state.popStack();
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_fsub);
      state.popStack();
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dsub);
      state.popStack(2);
    }
    else  {
      ins = Instruction.makeInstruction(opc_lsub);
      state.popStack(2);
    }
    state.instructions.addElement(ins);		
  }

  static final void emitMultiplyInstruction(EmitState state, 
					    Type expressionType) 
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_imul);
      state.popStack();
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_fmul);
      state.popStack();
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dmul);
      state.popStack(2);
    }
    else  {
      ins = Instruction.makeInstruction(opc_lmul);
      state.popStack(2);
    }
    state.instructions.addElement(ins);		
  }


  static final void emitDivideInstruction(EmitState state, 
					  Type expressionType) 
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_idiv);
      state.popStack();
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_fdiv);
      state.popStack();
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_ddiv);
      state.popStack(2);
    }
    else  {
      ins = Instruction.makeInstruction(opc_ldiv);
      state.popStack(2);
    }
    state.instructions.addElement(ins);		
  }


  static final void emitNegateInstruction(EmitState state, 
					  Type expressionType)
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_ineg);
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_fneg);
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dneg);
    }
    else  {
      ins = Instruction.makeInstruction(opc_lneg);
    }
    state.instructions.addElement(ins);		
  }

  static final void emitRemainderInstruction(EmitState state, 
					     Type expressionType)
       throws ClassException
  {
    Instruction ins;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_irem);
      state.popStack();
    }
    else if (expressionType.isFloatType()) {
      ins = Instruction.makeInstruction(opc_frem);
      state.popStack();
    }
    else if (expressionType.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_drem);
      state.popStack(2);
    }
    else  {
      ins = Instruction.makeInstruction(opc_lrem);
      state.popStack(2);
    }
    state.instructions.addElement(ins);		
  }

  static final void emitCastInstruction(EmitState state, 
					Type expressionType, Type tpe)
       throws ClassException
  
  {
    if (trace) {
      System.out.println("in EmitCastInstruction, casting from " + tpe + ", to " + expressionType);
    }
    Instruction ins = null;
    // Casts from floating point to types smaller than int require two separate
    // casting instructions.
    boolean secondCastRequired = false;
    // Casts from integral types
    if (tpe.isSmallIntegralType()) {
      if (expressionType.isLongType()) {
	ins = Instruction.makeInstruction(opc_i2l);
	state.pushStack();	
      }
      else if (expressionType.isFloatType())
	ins = Instruction.makeInstruction(opc_i2f);
      else if (expressionType.isDoubleType()) {
	ins = Instruction.makeInstruction(opc_i2d);
	state.pushStack();	
      }
      else if (tpe.isIntegerType()) {
	if(expressionType.isCharType())
	  ins = Instruction.makeInstruction(opc_i2c);
	else if (expressionType.isByteType())
	  ins = Instruction.makeInstruction(opc_i2b);
	else if (expressionType.isShortType())
	  ins = Instruction.makeInstruction(opc_i2s);
      }
    }
    else if (tpe.isFloatType()) {  // Casts from floats
      if (expressionType.isSmallIntegralType()) {
	ins = Instruction.makeInstruction(opc_f2i);
	if (!expressionType.isIntegerType()) {
	  secondCastRequired = true;
	}
      }
      else if (expressionType.isLongType()) {
	ins = Instruction.makeInstruction(opc_f2l);
	state.pushStack();	
      }
      else if (expressionType.isDoubleType()) {
	ins = Instruction.makeInstruction(opc_f2d);
	state.pushStack();	
      }
    }
    else if (tpe.isDoubleType()) { // Casts from doubles
      if (expressionType.isSmallIntegralType()) {
	ins = Instruction.makeInstruction(opc_d2i);
	if (!expressionType.isIntegerType()) {
	  secondCastRequired = true;
	}
      }
      else if (expressionType.isLongType())
	ins = Instruction.makeInstruction(opc_d2l);
      else if (expressionType.isFloatType()) {
	ins = Instruction.makeInstruction(opc_d2f);
	state.popStack();
      }
    }
    else if (tpe.isLongType()) { // Casts from longs
      if (expressionType.isIntegerType()) {
	ins = Instruction.makeInstruction(opc_l2i);
	state.popStack();
      }
      else if (expressionType.isDoubleType())
	ins = Instruction.makeInstruction(opc_l2d);
      else if (expressionType.isFloatType()) {
	ins = Instruction.makeInstruction(opc_l2f);
	state.popStack();	
      }
    }
    if (ins !=  null) {
      if (trace)
	System.out.println("Casting instruction emitted " + ins);
      state.instructions.addElement(ins);
      if (secondCastRequired)
	emitCastInstruction(state, expressionType, Type.INT_TYPE);
    }
  }

  static final void emitElementStoreInstruction(EmitState state, 
						Type tpe, int argumentNumber)
       throws ClassException
  {			
    Instruction ins = null;			
    if(tpe.isClassType() || tpe.isArrayType()) {
      switch(argumentNumber) {
      case 0:   ins = Instruction.makeInstruction(opc_astore_0); break;
      case 1:   ins = Instruction.makeInstruction(opc_astore_1); break;
      case 2:   ins = Instruction.makeInstruction(opc_astore_2); break;
      case 3:   ins = Instruction.makeInstruction(opc_astore_3); break;
      default:  ins = Instruction.makeInstruction(opc_astore,
						  argumentNumber); break;
      }			
      state.popStack();
    }	
    else if(tpe.isIntegerType() || tpe.isShortType() || tpe.isByteType()
	    || tpe.isBooleanType()) {
      switch(argumentNumber) {
      case 0:   ins = Instruction.makeInstruction(opc_istore_0); break;
      case 1:   ins = Instruction.makeInstruction(opc_istore_1); break;
      case 2:   ins = Instruction.makeInstruction(opc_istore_2); break;
      case 3:   ins = Instruction.makeInstruction(opc_istore_3); break;
      default:  ins = Instruction.makeInstruction(opc_istore,
						  argumentNumber);
      }
      state.popStack();
    }
    else  {	
      if(tpe.isDoubleType())  {
	switch(argumentNumber) {
	case 0:   ins = Instruction.makeInstruction(opc_dstore_0); break;
	case 1:   ins = Instruction.makeInstruction(opc_dstore_1); break;
	case 2:   ins = Instruction.makeInstruction(opc_dstore_2); break;
	case 3:   ins = Instruction.makeInstruction(opc_dstore_3); break;
	default:  ins = Instruction.makeInstruction(opc_dstore,
						    argumentNumber);
	}
	state.popStack(2);
      }
      else
	if(tpe.isLongType())  {
	  switch(argumentNumber) {
	  case 0:   ins = Instruction.makeInstruction(opc_lstore_0); 
	    break;
	  case 1:   ins = Instruction.makeInstruction(opc_lstore_1); 
	    break;
	  case 2:   ins = Instruction.makeInstruction(opc_lstore_2); 
	    break;
	  case 3:   ins = Instruction.makeInstruction(opc_lstore_3); 
	    break;
	  default:  ins = Instruction.makeInstruction(opc_lstore,
						      argumentNumber);
	  }
	  state.popStack(2);
	}
	else 
	  if(tpe.isFloatType()) {
	    switch(argumentNumber) {
	    case 0:   ins = Instruction.makeInstruction(opc_fstore_0);
	      break;
	    case 1:   ins = Instruction.makeInstruction(opc_fstore_1);
	      break;
	    case 2:   ins = Instruction.makeInstruction(opc_fstore_2);
	      break;
	    case 3:   ins = Instruction.makeInstruction(opc_fstore_3);
	      break;
	    default:  ins = Instruction.makeInstruction(opc_fstore,
							argumentNumber);
	    }
	    state.popStack();
	  }
	  else
	    throw new ClassException("Invalid variable type discovered during emitting " + tpe);			
    }					
    state.instructions.addElement(ins);	
  }

  static void emitDupInstruction(EmitState state, Type tpe) {
    Instruction ins;
    if (tpe.isLongType() | tpe.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dup2);
      state.pushStack(2);
    }
    else {
      ins = Instruction.makeInstruction(opc_dup);
      state.pushStack();
    }
    state.instructions.addElement(ins);
  }

  static void emitDup2Instruction(EmitState state) {
    Instruction ins;
    ins = Instruction.makeInstruction(opc_dup2);
    state.pushStack(2);
    state.instructions.addElement(ins);
  }


  static void emitDupX1Instruction(EmitState state, Type tpe) {
    Instruction ins;
    if (tpe.isLongType() | tpe.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dup2_x1);
      state.pushStack(2);
    }
    else {
      ins = Instruction.makeInstruction(opc_dup_x1);
      state.pushStack();
    }
    state.instructions.addElement(ins);
  }

  static void emitDupX2Instruction(EmitState state, Type tpe) {
    Instruction ins;
    if (tpe.isLongType() | tpe.isDoubleType()) {
      ins = Instruction.makeInstruction(opc_dup2_x2);
      state.pushStack(2);
    }
    else {
      ins = Instruction.makeInstruction(opc_dup_x2);
      state.pushStack();
    }
    state.instructions.addElement(ins);
  }


  static final void emitBitwiseOrInstruction(EmitState state, 
					     Type expressionType) 
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_ior);
      state.popStack();
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_lor);
      state.popStack(2);
    }
    else throw new ClassException("Invalid type for bitwise or instruction: " +
				  expressionType);
    state.instructions.addElement(ins);		
  }

  static final void emitBitwiseAndInstruction(EmitState state, 
					      Type expressionType)
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_iand);
      state.popStack();
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_land);
      state.popStack(2);
    }
    else throw new ClassException("Invalid type for bitwise and instruction: "+
				  expressionType);
    state.instructions.addElement(ins);		
  }

  static final void emitBitwiseXorInstruction(EmitState state, 
					      Type expressionType) 
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_ixor);
      state.popStack();
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_lxor);
      state.popStack(2);
    }
    else throw new ClassException("Invalid type for bitwise xor instruction: "+
				  expressionType);
    state.instructions.addElement(ins);		
  }

  static final void emitLeftShiftInstruction(EmitState state, 
					     Type expressionType)
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_ishl);
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_lshl);
    }
    else throw new ClassException("Invalid type for left shift instruction: "+
				  expressionType);
    state.popStack();
    state.instructions.addElement(ins);		
  }

  static final void emitRightShiftInstruction(EmitState state, 
					      Type expressionType)
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_ishr);
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_lshr);
    }
    else throw new ClassException("Invalid type for left shift instruction: "+
				  expressionType);
    state.popStack();
    state.instructions.addElement(ins);		
  }

  static final void emitUnsignedRightShiftInstruction(EmitState state, 
						      Type expressionType)
       throws ClassException
  {
    Instruction ins = null;
    if (expressionType.isSmallIntegralType()) {
      ins = Instruction.makeInstruction(opc_iushr);
    }
    else if (expressionType.isLongType()) {
      ins = Instruction.makeInstruction(opc_lushr);
    }
    else throw new ClassException("Invalid type for left shift instruction: "+
				  expressionType);
    state.popStack();
    state.instructions.addElement(ins);		
  }

  static final void emitLtInstructions(EmitState state, Type expressionType)
       throws ClassException
  {
    if (expressionType.isSmallIntegralType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmpge,
								0));	
      state.popStack(2);
    }
    else if (expressionType.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifge,0));  
      state.popStack(4);
    }
    else if (expressionType.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpg));  
      state.instructions.addElement(Instruction.makeInstruction(opc_ifge,0));
      state.popStack(2);
    }
    else if (expressionType.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifge,0));
      state.popStack(4);
    }
  }

  static final void emitGtInstructions(EmitState state, Type expressionType)
       throws ClassException
  {
    if (expressionType.isSmallIntegralType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmple,
								0));
      state.popStack(2);
    }
    else if (expressionType.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifle,0));
      state.popStack(4);
    }
    else if (expressionType.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpl));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifle,0));
      state.popStack(2);
    }
    else if (expressionType.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpl));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifle,0));
      state.popStack(4);
    }
  }

  static final void emitGeqInstructions(EmitState state, Type expressionType) 
       throws ClassException
  {
    if (expressionType.isSmallIntegralType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmplt,
								0));
      state.popStack(2);
    }
    else if (expressionType.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_iflt,0));
      state.popStack(4);
    }
    else if (expressionType.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpl));
      state.instructions.addElement(Instruction.makeInstruction(opc_iflt,0));
      state.popStack(2);
    }
    else if (expressionType.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpl));
      state.instructions.addElement(Instruction.makeInstruction(opc_iflt,0)); 
      state.popStack(4);
    }
  }

  static final void emitLeqInstructions(EmitState state, Type expressionType)
       throws ClassException
  {
    if (expressionType.isSmallIntegralType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmpgt,
								0));
      state.popStack(2);
    }
    else if (expressionType.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifgt,0)); 
      state.popStack(4);
    }
    else if (expressionType.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifgt,0));
      state.popStack(2);
    }
    else if (expressionType.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifgt,0));
      state.popStack(4);
    }
  }

  static final void emitEqInstructions(EmitState state, Type argtype,
				       Expression arg0, Expression arg1)
       throws ClassException 
  {
    if (argtype.isSmallIntegralType() & argtype.isNumericType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmpeq,
								0));
      state.popStack(2);
    }
    else if (argtype.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifeq,0));
      state.popStack(4);
    }
    else if (argtype.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifeq,0));
      state.popStack(2);
    }
    else if (argtype.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifeq,0));
      state.popStack(4);
    }
    else if (argtype.isBooleanType()) {
      boolean actualvalue = false;
      boolean secondactualvalue = false;
      boolean bothconstant = false;
      boolean oneconstant = false;
      if (arg0 instanceof Value) {
	actualvalue = ((Value) arg0).getBooleanValue();
	oneconstant = true;
	if (arg1 instanceof Value) {
	  bothconstant = true;
	  secondactualvalue = ((Value) arg1).getBooleanValue();
	}
      }
      else if (arg1 instanceof Value) {
	actualvalue = ((Value) arg1).getBooleanValue();
	oneconstant = true;
      }
      // Constant expressions should have been compiled away by this point
      if (bothconstant)
	throw new ClassException("Internal error constant expression caught too late");
      else if (oneconstant) {
	if (actualvalue) {
	  state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
	}
	else {
	  state.instructions.addElement(
					Instruction.makeInstruction(opc_ifeq,0));
	}
      }
      // Case where neither are constant - use if_icmp
      else 
	state.instructions.addElement(
				      Instruction.makeInstruction(opc_if_icmpeq,0));		
    }
    // Does not deal with null case - see callers
    else if (argtype.isClassType() || argtype.isArrayType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_acmpeq,
								0));
    }
  }

  static final void emitNeqInstructions(EmitState state, Type argtype,
					Expression arg0, Expression arg1)
       throws ClassException
  {
    if (argtype.isSmallIntegralType() & argtype.isNumericType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_icmpne,
								0));
      state.popStack(2);
    }
    else if (argtype.isLongType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_lcmp));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
      state.popStack(4);
    }
    else if (argtype.isFloatType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_fcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
      state.popStack(2);
    }
    else if (argtype.isDoubleType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_dcmpg));
      state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
      state.popStack(4);
    }
    else if (argtype.isBooleanType()) {
      boolean actualvalue = false;
      boolean secondactualvalue = false;
      boolean bothconstant = false;
      boolean oneconstant = false;
      if (arg0 instanceof Value) {
	actualvalue = ((Value) arg0).getBooleanValue();
	oneconstant = true;
	if (arg1 instanceof Value) {
	  bothconstant = true;
	  secondactualvalue = ((Value) arg1).getBooleanValue();
	}
      }
      else if (arg1 instanceof Value) {
	actualvalue = ((Value) arg1).getBooleanValue();
	oneconstant = true;
      }
      // Constant expressions should have been compiled away by this point
      if (bothconstant)
	throw new ClassException("Internal error constant expression caught too late");
      else if (oneconstant) 
	{
	  if (actualvalue)
	    state.instructions.addElement(Instruction.makeInstruction(opc_ifeq,0));
	  else
	    state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
	}
      else // neither constant case
	state.instructions.addElement(Instruction.makeInstruction(opc_if_icmpne,0));	
    }
    // Does not deal with null case - see callers.
    else if (argtype.isClassType() || argtype.isArrayType()) {
      state.instructions.addElement(Instruction.makeInstruction(opc_if_acmpne,
								0));	
    }
  }

  static final void emitIfeqInstruction(EmitState state) 
       throws ClassException
  {
    state.instructions.addElement(Instruction.makeInstruction(opc_ifeq,0));
  }

  static final void emitIfneInstruction(EmitState state) 
       throws ClassException
  {
    state.instructions.addElement(Instruction.makeInstruction(opc_ifne,0));
  }


  public static void main (String[] args) {
    for (int i = 0; i < opcLengths.length; i++) {
      System.out.println("Operator : " + opcNames[i] + " Code : " + i 
			 + " Length : " + opcLengths[i]
			 + " Indexbytes Start :" +
			 opcStartConstantPoolIndex[i] +
			 " Branch start " + opcBranchStart[i]);
    }
  }
}
