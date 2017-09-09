package com.gensym.classtools;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.util.Vector;

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

  int jumpTagIfAny = -1;
  int jumpTagIfAny2 = -1;
  long tryStartIfAny = -1;
  int exceptionIfAny = -1;
  String labelNameIfAny = null;
  int lineNumberIfAny = -1;
   
  private int localstart;

  private static boolean trace = false;

  //********************* Constructors ***************************

  /** Create an instruction of the type given by the first byte in the array, 
   * using all the bytes in the array.  This constructor is the relatively
   * fast one because it assumes the opcode has been calculated
   * correctly and that the array is of the appropriate length. See the
   * bytes only constructor above for all sanity checking.
   */
  private Instruction(int opcde, int start, int length, byte[] btes) {
    bytes = new byte[length];
    opcode = opcde;
    name = opcNames[opcode];
    System.arraycopy(btes,start,bytes,0,length);
    localstart = start;
    if (trace) {
      System.out.println("Instuction found : " + name + 
			 " Length: " + length + " Bytes found " +
			 toDecimalString(bytes));
    }
  }

  protected Instruction(int opcode) {	
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

  public static Instruction makeInstruction(int opcode, long longBranch) {
    return makeNullInstruction();
  }

  public static Instruction makeInstruction(int[] args) {
    ByteArrayOutputStream baob = new ByteArrayOutputStream();
    int opcode = args[0];
    if ((opcode >= 0) && (opcode < opcLengths.length)) {
      int startIndex = opcStartMultiByteValue[opcode];
      baob.write(opcode);
      int i = 1;
      if (startIndex == WIDE_START_MARKER) {
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
					    static Vector readInstructions(byte[] bytes, int start, int length)
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
      if(i <  (start + length)) {		 
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
	  instructs.addElement(
			       new Instruction(nextop, i, nextlength, bytes));
	       
	  instructsfound++;
	}
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
  private static int determineInstructionLength (final int opCode, final int index, final byte[] bytes) throws ClassException {
    int indexLocal = index;
	if (isDefiniteLengthInstruction(opCode))
      return opcLengths[opCode];
     
    int startIndex = indexLocal;
    while ((++indexLocal)%4 != 0) {
      if ((bytes[indexLocal]&0xFF) != 0)
 	throw new ClassException ("Illegal padding in instruction " + opCode + " at index " + indexLocal);
    }
    int instrLength;
    if (opCode == 0xAA) { // tableswitch
      int defaultIndex = Attribute.readU4(bytes, indexLocal);
      indexLocal += 4;
      int lowIndex = Attribute.readU4(bytes, indexLocal);
      indexLocal += 4;
      int highIndex = Attribute.readU4(bytes, indexLocal);
      indexLocal +=4;
      instrLength =  (indexLocal - startIndex) + (highIndex - lowIndex + 1)*4;
    } else { // must be 0xAB = lookupswitch
      int defaultIndex = Attribute.readU4(bytes, indexLocal);
      indexLocal +=4;
      int numPairs = Attribute.readU4(bytes, indexLocal);
      indexLocal +=4;
      instrLength = (indexLocal - startIndex) + numPairs*2*4;
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
	",length=" + opcLengths[opcode] +
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

  public void set2ByteValue(int startIndex, int value) throws ClassException
  {
    if (opcStartMultiByteValue[opcode] != startIndex)
      throw new ClassException("Not a multibyte index - set2ByteValue failed");
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

  public void set4ByteValue(int startIndex, long value) throws ClassException
  {
    bytes[startIndex] = (byte) ((bytes[startIndex] >>> 24) & 0xFF);
    bytes[startIndex + 1] = (byte) ((bytes[startIndex + 1] >>> 16) & 0xFF);
    bytes[startIndex + 2] = (byte) ((bytes[startIndex + 2] >>> 8) & 0xFF);
    bytes[startIndex + 3] = (byte) (bytes[startIndex + 3] & 0xFF);
  }


  /* Normalize both this instance, and its original location inside the
   * bytes array passed as an argument
   **/
  int normalize(final ConstantPool locals, final ConstantPool normals, 
		  final int index, final byte[] btes) throws ClassException
  {
    int startindex;
    int localindex;
    Constant constt;
	int idx = index;	
    // Check to see if this is an Instruction which contains a constant
    // reference
		
    if (trace)
      {
	System.out.println("Considering normalizing an instruction:" + this);
	System.out.println(locals);  
      }
		
    if ((startindex = opcStartConstantPoolIndex[opcode]) > 0) {
      if ((startindex + 1) < bytes.length)
	localindex =  get2ByteValue(startindex);
      else localindex = (bytes[startindex] & 0xFF);
			
      constt = locals.getPool(localindex);	
      if (trace)
	System.out.println("Before Normalizing an instruction, index=" + 
			   localindex + " Constant = " +constt);
      idx= constt.normalize(locals,normals,idx);
      int newindex = normals.member(normals,constt);	
	
      
      if (trace)
	System.out.println("After Normalizing an instruction, index=" + 
			   newindex + " Constant = " + 
			   normals.getPool(newindex) );			
      if ((startindex + 1) < bytes.length) {
	set2ByteValue(startindex,newindex);

	if (btes != null) {
	  btes[startindex + localstart ] =  bytes[startindex];
	  btes[startindex +  localstart + 1] = bytes[startindex + 1];
	}
      }
      else {
	bytes[startindex] = (byte) newindex;
	if (btes != null)
	  btes[startindex + localstart] = (byte) bytes[startindex];
      }
    }
	
    return idx;
  }
	
  void localize(ConstantPool locals, ConstantPool normals, byte[] btes) 
       throws ClassException
  {
    int startindex;
    int normalindex;
    int localindex;
    Constant constt;
    boolean notthere =true;
		
    // Check to see if this is an Instruction which contains a constant
    // reference
    if ((startindex = opcStartConstantPoolIndex[opcode]) > 0) {
      if ((startindex + 1) < bytes.length) 
	normalindex = get2ByteValue(startindex);
      else normalindex = (bytes[startindex] & 0xFF);
	  
      constt = normals.getPool(normalindex);
      if (trace)
	System.out.println("Before Localizing an instruction:" + name +
			   " index=" + normalindex + " Constant = " +
			   constt);			
      localindex = constt.localize(locals,normals);
      if (trace)
	System.out.println("After Localizing an instruction:"  + 
			   name +", index=" + localindex + 
			   " Constant = " +locals.getPool(localindex));
      if ((startindex + 1) < bytes.length) {
	set2ByteValue(startindex,localindex);
	if (btes != null) {
	  btes[startindex + localstart ] =  (byte) bytes[startindex];
	  btes[startindex +  localstart + 1] 
	    = (byte) bytes[startindex + 1];
	}
      }
      else {
	bytes[startindex] = (byte) localindex;
	if (btes != null)
	  btes[startindex + localstart] =  (byte) localindex;
      }
    }
  }

  @Override
  void emit(DataOutputStream dout) throws IOException {
    dout.write(bytes);
  }

  public int size() {
    return bytes.length;
  }

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
    if (! (tpe.isLongType() || tpe.isDoubleType()))
      state.popStack();
    state.instructions.addElement(ins);
  }


  static final void emitArrayStoreInstruction(EmitState state, Type tpe) 
       throws ClassException
  {
    Instruction ins2;
    if (tpe.isReferenceType())
      ins2 = Instruction.makeInstruction(opc_aastore);
    else if (tpe.isBooleanType() || tpe.isByteType()) 
      ins2 = Instruction.makeInstruction(opc_bastore);
    else if (tpe.isCharType()) 
      ins2 = Instruction.makeInstruction(opc_castore);
    else if (tpe.isFloatType())
      ins2 = Instruction.makeInstruction(opc_fastore);
    else if (tpe.isDoubleType())
      ins2 = Instruction.makeInstruction(opc_dastore);
    else if (tpe.isShortType())
      ins2 = Instruction.makeInstruction(opc_sastore);
    else if (tpe.isLongType())
      ins2 = Instruction.makeInstruction(opc_lastore);
    else ins2 = Instruction.makeInstruction(opc_iastore);
    state.instructions.addElement(ins2);
    if (tpe.isLongType() || tpe.isDoubleType())
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
    Instruction ins = null;
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
      if (expressionType.isIntegerType())
	ins = Instruction.makeInstruction(opc_f2i);
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
      if (expressionType.isIntegerType()) {
	ins = Instruction.makeInstruction(opc_d2i);
	state.popStack();
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
    }
  }

  static final void emitElementStoreInstruction(EmitState state, 
						Type tpe, int argumentNumber)
       throws ClassException
  {			
    Instruction ins = null;			
    if(tpe.isClassType() || tpe.isArrayType()) {
      switch(argumentNumber) {
			case 0:
				ins = Instruction.makeInstruction(opc_astore_0);
				break;
			case 1:
				ins = Instruction.makeInstruction(opc_astore_1);
				break;
			case 2:
				ins = Instruction.makeInstruction(opc_astore_2);
				break;
			case 3:
				ins = Instruction.makeInstruction(opc_astore_3);
				break;
			default:
				ins = Instruction.makeInstruction(opc_astore, argumentNumber);
				break;
      }			
      state.popStack();
    }	
    else if(tpe.isIntegerType() || tpe.isShortType() || tpe.isByteType()
	    || tpe.isBooleanType()) {
      switch(argumentNumber) {
			case 0:
				ins = Instruction.makeInstruction(opc_istore_0);
				break;
			case 1:
				ins = Instruction.makeInstruction(opc_istore_1);
				break;
			case 2:
				ins = Instruction.makeInstruction(opc_istore_2);
				break;
			case 3:
				ins = Instruction.makeInstruction(opc_istore_3);
				break;
			default:
				ins = Instruction.makeInstruction(opc_istore, argumentNumber);
      }
      state.popStack();
    }
    else  {	
      if(tpe.isDoubleType())  {
	switch(argumentNumber) {
				case 0:
					ins = Instruction.makeInstruction(opc_dstore_0);
					break;
				case 1:
					ins = Instruction.makeInstruction(opc_dstore_1);
					break;
				case 2:
					ins = Instruction.makeInstruction(opc_dstore_2);
					break;
				case 3:
					ins = Instruction.makeInstruction(opc_dstore_3);
					break;
				default:
					ins = Instruction.makeInstruction(opc_dstore, argumentNumber);
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
    if (tpe.isLongType() || tpe.isDoubleType()) {
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
    if (tpe.isLongType() || tpe.isDoubleType()) {
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
    if (tpe.isLongType() || tpe.isDoubleType()) {
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
    if (argtype.isSmallIntegralType() && argtype.isNumericType()) {
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
    if (argtype.isSmallIntegralType() && argtype.isNumericType()) {
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

    static void setTrace(boolean traceOn) {
        trace = traceOn;
    }
}
