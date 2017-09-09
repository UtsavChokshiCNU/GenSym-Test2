package com.gensym.classtools;

import java.util.Hashtable;
import java.util.Vector;

class EmitState implements RuntimeConstants {
  ConstantPool pool;
  VariableScope scope;
  int varID = 0;
  Vector instructions = new Vector();
  Vector exceptionTable = new Vector();
  Vector lineNumberTable;
  String[] argumentNames;
  Type[] argumentTypes;
  Type returnType;
  Type classType;
  boolean generateDebugInfo;
  int jumpId = 0;
  int tryId = 0;
  int lineNumberId = 0;
  int stackSize = 0;
  int maxStackSize = 0;
  boolean operandAlreadyOnTheStack = false;
  private boolean breakableContext = false;
  private boolean continuableContext = false;
  private int breakTarget;
  private int continueTarget;

  private static final boolean trace = false;

  /** 
   * Used for emitting
   */
  EmitState(ConstantPool pool, 
	    String[] argumentNames,
	    Type[] argumentTypes,
	    Type returnType,
	    Type classType,
	    boolean generateDebugInfo)
      throws ClassException
  {
    this.pool = pool;
    this.generateDebugInfo = generateDebugInfo;
    this.argumentNames = argumentNames;
    this.argumentTypes = argumentTypes;
    this.returnType = returnType;
    this.classType = classType;
  }

  /** 
   * Used for dissassembling to an intermediate form
   */
  EmitState(ConstantPool pool,
            Vector instructions,
            Vector exceptionTable,
            Vector lineNumberTable)
  {
    this.pool = pool;
    this.instructions = instructions;
    this.exceptionTable = exceptionTable;
    this.lineNumberTable = lineNumberTable;
  }


  // *****************Emulating the Stack Size  ********
  void popStack() throws ClassException {
    if (stackSize > 0) 
      stackSize--;
    else throw new ClassException("Invalid pop of stack: " + stackSize);
  }

  void popStack(int number) throws ClassException {
    if (stackSize >= number) 
      stackSize -= number;
    else throw new ClassException("Invalid pop of stack, stacksize= " + 
				  stackSize + " pop=" + number);
  }

  void pushStack() {
    stackSize++;
    if (stackSize > maxStackSize)
      maxStackSize = stackSize;
  }

  void pushStack(int number) {
    stackSize += number;
    if (stackSize > maxStackSize)
      maxStackSize = stackSize;
  }



  // **************** Jump targets *****************************
  Instruction getJumpTargetInstruction() 
  {
    Instruction ins = Instruction.makeInstruction(opc_label);
    ins.jumpTagIfAny = jumpId;
    jumpId++;
    return ins;
  }

  Instruction getLineNumberInstruction(int lineNumber) 
  {
    Instruction ins = Instruction.makeInstruction(opc_label);
    ins.jumpTagIfAny = jumpId;
    jumpId++;
    ins.lineNumberIfAny = lineNumber;
    lineNumberId++;
    return ins;
  }

  Instruction getTryInstruction(Instruction jumpTag1, 
                                Instruction jumpTag2,
                                int exceptionWhere)
  {
    Instruction  ins=  Instruction.makeInstruction(opc_try);
    ins.jumpTagIfAny = jumpTag1.jumpTagIfAny;
    ins.jumpTagIfAny2 = jumpTag2.jumpTagIfAny;
    ins.exceptionIfAny = exceptionWhere;
    tryId++;
    return ins;
  } 

  /**
   * Iterate over the array of instructions, removing each opc_label instruction
   * creating an array of the byte positions of each opc_label.  Then
   *	iterate over every instruction, and for every instruction that refers to a
   * target then substitute the appropriate byte offset to the target. 
   */
  void resolveAllLabels() throws ClassException {
    Instruction inst;
    Instruction[] tryInstructions = new Instruction[tryId];
    Instruction[] lineNumberInstructions = new Instruction[lineNumberId];
    int size = instructions.size();
    long[] positions = new long[jumpId];
    long bytes = 0;
    Hashtable namedTags = new Hashtable();
    int tryCount = 0;
    int lineNumberCount = 0;

    // Step 1 - remove all opc_label and opc_try instructions
    for (int i = 0; i < size; i ++) {
      inst = (Instruction) instructions.elementAt(i);
      int opcode = inst.getOpcode();
      if (opcode == opc_try) {
	inst.tryStartIfAny = bytes;
	tryInstructions[tryCount++] = inst; 
	instructions.removeElementAt(i);
	size --;
	i--;  
      }
      else { 
	if (opcode == opc_label) {              
	  if (trace)
	    System.out.println("Found a jump target instruction " + inst +
			       "bytes = " + bytes);
	  String labelName = inst.labelNameIfAny;
	  if (labelName != null) {
	    if (! namedTags.containsKey(labelName)){
	      if (trace) {
		System.out.println("Label name " + inst.labelNameIfAny);
		System.out.println("Jump tag " + inst.jumpTagIfAny);
		System.out.println("bytes " + bytes);
	      }
	      namedTags.put(labelName, inst.jumpTagIfAny);
	    }
	  }
	  positions[inst.jumpTagIfAny] = bytes;
	  int lineNumber = inst.lineNumberIfAny;
	  if (lineNumber != -1) {
	    lineNumberInstructions[lineNumberCount++] = inst;
	  }
	  instructions.removeElementAt(i);
	  size --;
	  i--;
	}
	else bytes += inst.size();
      }
    } 

    // Step 2 - generate the exception table
    for (int i = 0; i < tryId; i++) {
      Instruction tryInst = tryInstructions[i];
      long start_pc = tryInst.tryStartIfAny;
      long end_pc = positions[tryInst.jumpTagIfAny];
      end_pc = ((end_pc > 0) ? (end_pc) : 0);
      long handler_pc = positions[tryInst.jumpTagIfAny2];
      int catch_type = tryInst.exceptionIfAny;
      exceptionTable.addElement(new ExceptionTableEntry(pool,
							(int)start_pc,
							(int)end_pc,
							(int)handler_pc,
							catch_type));
    }
        
    // Step 3 - generate the line number table
        
    long last_pc = -1;
    int last_line = -1;
    if (lineNumberId > 0) {
      if (lineNumberTable == null)
	lineNumberTable = new Vector();
      for (int i = 0; i < lineNumberId; i++) {
	Instruction lineNumberInst = lineNumberInstructions[i];
	// This reflects a bug.
	if (lineNumberInst == null)
	  continue;
	int lineNumber = lineNumberInst.lineNumberIfAny;
	long start_pc = positions[lineNumberInst.jumpTagIfAny];
	if ((last_pc != start_pc) ||
	    (last_line != lineNumber)) {
	  lineNumberTable.addElement(
				     new LineNumberTableEntry((int) start_pc,lineNumber));
	  last_pc = start_pc;
	  last_line = lineNumber;
	}
      }
    }
        


    // Step 4 - sub branch pcs into branching instructions
    size = instructions.size();
    bytes = 0;
    int start, opcode;
    long diff;
    for (int i= 0; i < size; i ++) {
      inst = (Instruction) instructions.elementAt(i);
      opcode = inst.getOpcode();
      start = opcBranchStart[opcode];
      if (start > 0) {
	if (inst.labelNameIfAny != null) {
	  Integer value = (Integer) namedTags.get(inst.labelNameIfAny);
	  diff = positions[value.intValue()] - bytes;
	}  
	else diff = positions[(int) inst.jumpTagIfAny] - bytes;
	if ((-32769 < diff ) && (diff < 32768)) {
	  inst.set2ByteValue(start,(int) diff); // typical case
	  // ***WARNING: else clause here can invalidate steps 2 and 3, which rely
	  // upon the byte positions stored in the positions array. Possible
	  // solution will be to move this stage and make changes to
	  // the positions array, then calculate exception and line number
	  // tables.
	  // ***
	}
	else {
	  // Case when opc_goto_w is necessary.
	  // If goto replace with goto_w.
	  if (opcode == opc_goto)
	    instructions.setElementAt(Instruction.makeInstruction(opc_goto_w,diff),i);
	  else  if (opcode == opc_goto_w) { // if it is opc_goto_w then that is OK
	    inst.set4ByteValue(start,diff);
	  }
	  // Case when opc_jsr_w is necessary.
	  if (opcode == opc_jsr)
	    instructions.setElementAt(Instruction.makeInstruction(opc_jsr_w,diff),i);
	  else  if (opcode == opc_jsr_w) { 
	    inst.set4ByteValue(start,diff);
	  }
	  else 	{
	    // otherwize must do what?
	  }						
	}
      }
      inst.jumpTagIfAny = -1;
      bytes += inst.size();
    } 
  } 
  

  /*
   * Replace all opc_ldc's with opc_ldc_w's if replaceOpcLdcs
   * flag is true.
   *
   * Replace all return instructions to be jumps to the end (or if
   * they are at the end drop the return instruction) if the replaceReturns
   * option is true)
   *
   * Change all branching instructions to refer to labels
   * rather than direct byte references.
   *
   * Add labels for line number entries, branch targets and
   * try catch.
   * 
   * Note this is an expensive operation.  Only to be undertaken
   * if you are a dissassembler or if it is necessary because of 
   * widening constant pool indexes when merging a method into a 
   * class
   */
  int addAllLabels(boolean replaceOpcLdcs,  boolean replaceReturns) throws ClassException
  {
    Hashtable labels = new Hashtable();
     
    // Collect the location of all the line number instructions
    
    collectLineNumberTableLabels(labels);

    // Collect the location of all the opc_try and opc_labels to
    // add for the exception table

    collectExceptionLabels(labels);

    // Collect the location of all opc_labels which are jump targets
    collectBranchTargetLabels(labels);
    
    return addLabels(labels, replaceOpcLdcs, replaceReturns);
  }


  /* 
   * Performs a subset of the activities of addAllLabels().  It will only
   *  add labels for the try-catch exception handlers. Shares some implementation
   *  with addAllLabels().
   *
   *  Replace all opc_ldc's with opc_ldc_w's if replaceOpcLdcs flag is true.
   */
  int addExceptionLabels(boolean replaceOpcLdcs, boolean replaceReturns)
  {
    Hashtable labels = new Hashtable();

    collectExceptionLabels(labels);

    return addLabels(labels, replaceOpcLdcs, replaceReturns);
  }

  private int addLabels(Hashtable labels, 
                        boolean replaceOpcLdcs,
                        boolean replaceReturns)
  {
    int byteref = 0;
    int opcode, i, size;
    Integer key;
    Vector entries;
    Instruction ins, element, newElement;
    int increaseInSize = 0;
    boolean lastInstruction = false;
    Instruction lastTag = null;

    if (replaceReturns)
      lastTag = getJumpTargetInstruction();

    for (i = 0; (i < (size = instructions.size())) &&
	   ! lastInstruction; i++)
      {
	if (i == (size - 1))
	  lastInstruction = true;

	element = (Instruction) instructions.elementAt(i);
	opcode = element.getOpcode();
     
	key = byteref;
        
	if (labels.containsKey(key))
	  {
	    entries = (Vector)  labels.get(key);
        
	    for (int j =0; j < entries.size(); j++)
	      {
		ins = (Instruction) entries.elementAt(j);
		instructions.insertElementAt(ins, i++);
	      }
	  }
      
	if (replaceOpcLdcs && (opcode == opc_ldc))
	  {
	    newElement = 
	      Instruction.makeInstruction(opc_ldc_w, element.getBytes()[1]);
        
	    increaseInSize++;
     
	    // Do the replace here
	    instructions.setElementAt(newElement, i);
	  }
                
	if (replaceReturns) {
	  if ((opcode >= opc_ireturn) &&
	      (opcode <= opc_return))
	    {
	      if (lastInstruction)
		instructions.removeElementAt(i);
	      else {
		newElement = Instruction.makeInstruction(opc_goto, 0);
		newElement.jumpTagIfAny = lastTag.jumpTagIfAny;
		instructions.setElementAt(newElement, i);
	      }
	    }
	  if (lastInstruction)
	    {
	      // Add the jump tag for the end of the block
	      instructions.addElement(lastTag);
	    }
	}

	// should handle variable length instrs. See Instruction.determineInstructionLength        
	if (opcode >= 0)
	  byteref += opcLengths[opcode];

      }

    return increaseInSize;
  }
  
  private void collectLineNumberTableLabels(Hashtable labels)
  {
    Integer key;
    Instruction ins;
    int i, size;

    if (lineNumberTable != null)
      {
	int lineNumber, start_pc;
      
	size = lineNumberTable.size();

	for (i = 0; i < size; i++)
	  {
	    LineNumberTableEntry entry =
	      (LineNumberTableEntry) lineNumberTable.elementAt(i);

	    lineNumber =  entry.getLineNumber();
	    start_pc = entry.getStartPc();

	    key = start_pc;
	    ins = getLineNumberInstruction(lineNumber);

	    add_label_entry(labels, key, ins);
	  } 
	lineNumberTable.setSize(0);
      }
  }


  private void collectBranchTargetLabels(Hashtable labels)
      throws ClassException
  {
    int i, size, opcode, byteref, branchTarget;
    Instruction element, ins;
    Integer key;

    byteref = 0;
    size = instructions.size();

    // Collect the location of all the branch targets to add
    for (i = 0; i < size; i++)
      {
	element = (Instruction) instructions.elementAt(i);
	opcode = element.getOpcode();
	// Does have a branch
	if (opcBranchStart[opcode] > 0)
	  {
	    // Does not already have a tag
	    if (element.jumpTagIfAny == -1)
	      {
		// All branches are multi-byte values,
		// starting at element 1, so get 'em
          
		branchTarget = element.get2ByteValue(1) + byteref; 
		ins = getJumpTargetInstruction(); 
		element.jumpTagIfAny = ins.jumpTagIfAny;
          
		key = branchTarget;
          
		add_label_entry(labels, key, ins);
	      }
	  }

	// should handle variable length instrs. See Instruction.determineInstructionLength
	byteref += opcLengths[opcode];
      }
  }

  private void collectExceptionLabels(Hashtable labels)
  {
    if (exceptionTable != null)
      {
	int start_pc, end_pc, handler_pc, catch_type, size, i;
	Instruction tryInst, afterTry, catchTarget;
      
	size = exceptionTable.size();
	for (i = 0; i < size; i++)
	  { 
	    ExceptionTableEntry entry =
	      (ExceptionTableEntry) exceptionTable.elementAt(i);

	    start_pc = entry.getStartPc();
	    end_pc = entry.getEndPc();
	    handler_pc = entry.getHandlerPc();
	    catch_type = entry.getCatchType();
        
	    afterTry = getJumpTargetInstruction();
	    catchTarget = getJumpTargetInstruction();  
	    tryInst = getTryInstruction(afterTry,
					catchTarget,
					catch_type);

	    // Now must add these at the appropriate keys
	    // start_pc   == tryInst
	    // end_pc     == afterTry
	    // handler_pc == catchTarget

	    add_label_entry(labels, start_pc, tryInst);
	    add_label_entry(labels, end_pc, afterTry);
	    add_label_entry(labels, handler_pc, catchTarget);                               
	  }
	exceptionTable.setSize(0);   
      }
  }

  private static void add_label_entry(Hashtable labels, Integer key, Instruction ins)
  {
    Vector entries;
    if (labels.containsKey(key))
      {
	entries = (Vector) labels.get(key);
	entries.addElement(ins);   
      }
    else 
      {
	entries = new Vector();
	entries.addElement(ins);
	labels.put(key, entries);
      }
  }

  



  // **************** Continuable and Breakable Contexts ******
  
  void setContinuableAndBreakableContext(Instruction continueInst, Instruction breakInst) {
    continuableContext = true;
    breakableContext = true;
    continueTarget = continueInst.jumpTagIfAny;
    if (breakInst != null)
      breakTarget = breakInst.jumpTagIfAny;
  }

  ContinuableAndBreakableContext getContinuableAndBreakableContext()
  {
    return
      new ContinuableAndBreakableContext(continuableContext, breakableContext, continueTarget, breakTarget);
  }

  void restoreContinuableAndBreakableContext(ContinuableAndBreakableContext context) {
    continuableContext = context.continuableContext;
    breakableContext = context.breakableContext;
    if (continuableContext)
      continueTarget = context.continueTarget;
    if (breakableContext)
      breakTarget = context.breakTarget;
  }

  void unsetContinuableAndBreakableContext() {
    continuableContext = false;
    breakableContext = false;
  }

  void setBreakableContext(Instruction breakInst) {
    breakableContext = true;
    breakTarget = breakInst.jumpTagIfAny;
  }

  void unsetBreakableContext() {
    breakableContext = false;
  }

  boolean isBreakableContext() {
    return breakableContext;
  }

  boolean isContinuableContext() {
    return continuableContext;
  }

  void emitJumpToBreak(Statement continuation) 
      throws ClassException
  {
    if (continuation == null)
      {
        doContinuation(continuation);
      }
    else {
      Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
      gotoInst.jumpTagIfAny = breakTarget;
      instructions.addElement(gotoInst);
    }
  }

  void emitJumpToContinue() {
    Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
    gotoInst.jumpTagIfAny = continueTarget;
    // System.out.println("Emitting branch to " + continueTarget);
    instructions.addElement(gotoInst);
  }

  //************** Dealing with Return contexts  ********************

  /**
   * Call this at a point in the emit when you expect a return or
   * a throw.  This will check the instructions to see if a throw
   * or a return exists/ whether the throw or return is of the 
   * correct type.  It will also add opc_return in cases where
   * that was not added by the user of classtools and it is the
   * valid thing to do
   */
  void doContinuation(Statement continuation) throws ClassException
  {
    if (continuation == null)
      {
	Instruction lastInstruction = null;
	if (!instructions.isEmpty())
	  lastInstruction = (Instruction) instructions.lastElement();
     
	if ((lastInstruction == null) || 
	    (! (lastInstruction.isReturnOrThrowInstruction())))
	  {
	    // Now check that the method needs an opc_return
	    // If it does not then throw an exception
       
	    if (returnType.isVoidType())
	      {
		Instruction ins = Instruction.makeInstruction(opc_return);
		instructions.addElement(ins);
	      }
	    else throw new ClassException("Missing return from method");
	  } 
	else {
	  // Could do some type checking of returns here,
	  // But I prefer to do the work in Throw and Return
	  // so that the problem can be caught earlier inside
	  // the appropriate JavaNode.
	}   
      }
  }
}

