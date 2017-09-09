package com.gensym.newclasstools;

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
  private Instruction breakTarget;
  private Instruction continueTarget;

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

  // Used to pop stack when a false leaveOnStack argument to emit
  // indicates that it should be popped.
  void maybePopStack(boolean leaveOnStack, Type expressionType) throws ClassException {
    if (leaveOnStack) return;
    if (expressionType.isLongType() || expressionType.isDoubleType()) {
      instructions.addElement(Instruction.makeInstruction(opc_pop2));
      popStack(2);
    } else {
      instructions.addElement(Instruction.makeInstruction(opc_pop));
      popStack(1);
    }
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
    return ins;
  }

  Instruction getLineNumberInstruction(int lineNumber) 
  {
    Instruction ins = Instruction.makeInstruction(opc_label);
    ins.lineNumberIfAny = lineNumber;
    lineNumberId++;
    return ins;
  }

  Instruction getTryInstruction(Instruction jumpTag1, 
                                Instruction jumpTag2,
                                int exceptionWhere)
  {
    Instruction  ins=  Instruction.makeInstruction(opc_try);
    ins.jumpDestination = jumpTag1;
    ins.jumpDestination2 = jumpTag2;
    ins.exceptionIfAny = exceptionWhere;
    tryId++;
    return ins;
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

	    key = new Integer(start_pc);
	    ins = getLineNumberInstruction(lineNumber);

	    add_label_entry(labels, key, ins);
	  } 
	lineNumberTable.setSize(0);
      }
  }


  /*

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
          
		key = new Integer(branchTarget);
          
		add_label_entry(labels, key, ins);
	      }
	  }

	// should handle variable length instrs. See Instruction.determineInstructionLength
	byteref += opcLengths[opcode];
      }
  }

  */

  /*

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

	    add_label_entry(labels, new Integer(start_pc), tryInst);
	    add_label_entry(labels, new Integer(end_pc), afterTry);
	    add_label_entry(labels, new Integer(handler_pc), catchTarget);                               
	  }
	exceptionTable.setSize(0);   
      }
  }

  */

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
    continueTarget = continueInst;
    if (breakInst != null)
      breakTarget = breakInst;
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
    breakTarget = breakInst;
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
      gotoInst.jumpDestination = breakTarget;
      instructions.addElement(gotoInst);
    }
  }

  void emitJumpToContinue() {
    Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
    gotoInst.jumpDestination = continueTarget;
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
	if (instructions.size() > 0)
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

  int getIndex(Constant constant) {
    return pool.getIndex(constant);
  }

}

