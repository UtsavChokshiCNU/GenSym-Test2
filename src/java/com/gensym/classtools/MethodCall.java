package com.gensym.classtools;

import java.util.Vector;

public class MethodCall extends Call implements RuntimeConstants {
  private static final boolean trace = false;
  protected int callType = -1;
		
  /**
   * Create a call to a method (implicitly on "this" - the current instance),
   * or on the class that defines the Method if this is a static call.
   */
  public MethodCall(MethodRef methodRef,
		    Expression[] arguments,
		    int callType)
       throws ClassException
  {
    checkMethodArgumentTypes(methodRef,arguments);
    // Check the type of argument expressions here
    checkInterfaceType(methodRef,callType);
    name = methodRef.getMethodName();
    addJavaNode(methodRef); 
    if (arguments != null) {
      for(int i = 0; i < arguments.length; i++) 
	addJavaNode(arguments[i]);
    }
    this.callType = callType;	 
  }


  /**
   * Create a call to a method (implicitly on "this" - the current instance),
   * or on the class that defines the Method if this is a static call. This is
   * the constructor for a call that involves zero arguments.
   */
  public MethodCall(MethodRef methodRef, int callType)
       throws ClassException
  {
    checkMethodArgumentTypes(methodRef);
    checkInterfaceType(methodRef,callType);
    addJavaNode(methodRef); 
    this.callType = callType;	 
  }


  /** 
   * Create a call to a method of a specified instance. Cannot specify 
   * static calls in this case.
   */
  public MethodCall(Expression expression,
		    MethodRef methodRef,
		    Expression[] arguments,
		    int callType)
       throws ClassException
  {
    checkMethodArgumentTypes(methodRef,arguments);
    checkInterfaceType(methodRef,callType); 
    if (callType == MTH_CALL_STATIC) 
      throw new ClassException("Cannot make a static call on an instance.");
    if (callType == MTH_CALL_SPECIAL) 
      throw new ClassException("Cannot make a special call on an instance.");
    Type tpe = expression.getExpressionType();
    if (! tpe.isClassType()) 
      throw new ClassException("Attempt to construct a MethodCall on a non-object type: " +
			       tpe);
    // Check the type of argument expressions here	
    // Add Java nodes
    addJavaNode(expression);
    addJavaNode(methodRef);
    if (arguments != null)
      for(int i = 0; i < arguments.length; i++) {
	// System.out.println("Adding argument " + arguments[i] + " to a methodCall");
	addJavaNode(arguments[i]);
      }
    this.callType = callType;	 
  }
		
  private void checkInterfaceType(MethodRef methodRef,int callType)
       throws ClassException
  {
    if ((callType == MTH_CALL_INTERFACE) 
	&& (!(methodRef instanceof InterfaceMethodRef)))
      throw new ClassException("Interface calls must be specified with a InterfaceMethodRef class");
  }

  private void checkMethodArgumentTypes(MethodRef methodRef, 
					Expression[] arguments)
       throws ClassException 
  {
    Type tpe = methodRef.getExpressionType();
    Type[] argumentSpec = tpe.getArgumentTypes();
    if (arguments == null)  {
      if (argumentSpec.length != 0)
	throw new 
	  ClassException("Incorrect number of arguments passed to method: " +
			 methodRef.getMethodName() + " Expected: " + argumentSpec.length +
			 " Received: " + 0);
    }
    else {
      if (arguments.length != argumentSpec.length)
	throw 
	  new ClassException("Incorrect number of arguments passed to method: " +
			     methodRef.getMethodName() + " Expected: " + argumentSpec.length + " Received: " +
			     arguments.length);
      for (int i = 0; i < arguments.length; i++) 
	{
	  if (trace) {
	    System.out.println("arg " + i + ": " + argumentSpec[i] + " == " + arguments[i]);
	  }
	  if (argumentSpec[i].potentialMethodArgumentConversion(arguments[i]))
	    arguments[i] = new Cast(argumentSpec[i], arguments[i], false);
	  // NB. Cast is a no-op when unneeded during emit
	  else 
	    throw 
	      new ClassException("Wrong type for argument to method. Method: "+ 
				 methodRef.getMethodName() + " Argument number: " +
				 i + " Expected: " + argumentSpec[i] +
				 " Received: " + 
				 arguments[i].getExpressionType());
	}
    }
  }			

  private void checkMethodArgumentTypes(MethodRef methodRef) throws ClassException {
    Type tpe = methodRef.getExpressionType();
    Type [] argumentSpec = tpe.getArgumentTypes();
    if ((argumentSpec != null) && (argumentSpec.length != 0))
      throw new ClassException("Attempt to pass zero arguments to method: " +
			       methodRef.getMethodName() + " Expected: " +
			       argumentSpec.length);
  }


  @Override
  public Type getExpressionType() {
			
    for (int i = 0; i < children.size(); i++) {
      Expression nextElement = (Expression) children.elementAt(i);
      if (nextElement instanceof MethodRef)
	return nextElement.getExpressionType();
    }
    // Consider throwing an Exception.  This case should
    // never happen
    return new Type(T_VOID); 
  }

  public int getClassWhere () throws ClassException {
    for (int i = 0; i < children.size(); i++) {
      Expression nextElement = (Expression) children.elementAt(i);
      if (nextElement instanceof MethodRef)
	return ((MethodRef) nextElement).getWhere();
    }
    return -1;
  }

  public String getClassName() {
    for (int i = 0; i < children.size(); i++) {
      Expression nextElement = (Expression) children.elementAt(i);
      if (nextElement instanceof MethodRef)
	return ((MethodRef) nextElement).getClassName();
    }
    return null;
  }

  @Override
  public void generateConstants(ConstantPool pool) throws ClassException {
    for (int i = 0; i < children.size(); i++) {
      Expression nextElement = (Expression) children.elementAt(i);
      if (nextElement instanceof MethodRef)
	((MethodRef) nextElement).generateConstants(pool);
    }
  }

  @Override
  public boolean isConstantExpression() {
    // Should be conditional on whether method is final or not.
    return false;
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
       throws ClassException
  {
    Vector instructions =  state.instructions;
    MethodRef methodRef;
    super.emit(state,leaveOnStack,continuation);
    // For each expression that is an argument to this method call
    // emit all instructions
    Expression nextElement =  (Expression) children.elementAt(0);
    if (trace) 
      System.out.println(nextElement.toString());
    switch (callType) {
    case MTH_CALL_STATIC:  {
      methodRef = (MethodRef) nextElement;
      methodRef.generateConstants(state.pool);
      int stackRef =  state.stackSize;
      for (int i = 1; i < children.size(); i ++) {
	nextElement = (Expression) children.elementAt(i);
	state.pushStack();
	nextElement.emit(state, true, continuation);
      }

      state.popStack(state.stackSize - stackRef);
     
      int index = methodRef.getWhere();
      Instruction ins = Instruction.makeInstruction(opc_invokestatic,index);
      instructions.addElement(ins);
      break;
    }
    case MTH_CALL_VIRTUAL:
    case MTH_CALL_INTERFACE: {
      int ref = 0;
      boolean addedThis =false;

      // Case where instance is a reference to this
      if (nextElement instanceof MethodRef) {
	methodRef = (MethodRef) nextElement;
	methodRef.generateConstants(state.pool);
						
	// push "this" onto the stack
	Instruction ins = Instruction.makeInstruction(opc_aload_0);
	instructions.addElement(ins);
	state.pushStack();
	addedThis = true;
      }
      // Case where instance is specified.
      else {
	nextElement.emit(state,true, continuation);
	methodRef = (MethodRef) children.elementAt(++ref);
	methodRef.generateConstants(state.pool);			
			
      }
      int reflength = instructions.size();
      
      int stackref = state.stackSize;
      int doubleCount = 0;
      for (int i = ref; i < children.size(); i ++) {
	nextElement = (Expression) children.elementAt(i);
	// System.out.println("Emitting expression " + i + ": " + nextElement + "as argument to method call");
	if ((nextElement.getExpressionType().isDoubleType() || 
	     nextElement.getExpressionType().isLongType()) &&
	    i != ref)
	  doubleCount++;
	nextElement.emit(state,true, continuation);
      }
      state.popStack(state.stackSize - stackref);   
      if (addedThis) {
    	  state.popStack(1);
      }

      int nargs = 0;
      if (callType == MTH_CALL_INTERFACE) {
	nargs = children.size() - 1 + doubleCount;
      }
      int index = methodRef.getWhere();					
      switch (callType) {
      case MTH_CALL_VIRTUAL:
	{
	  Instruction ins = Instruction.makeInstruction(opc_invokevirtual,
							index);
	  if (trace)	
	    System.out.println("Instruction for virtual call" + ins);
	  instructions.addElement(ins);
	  break;
	}
      case MTH_CALL_INTERFACE:
	{

	  Instruction ins = Instruction.makeInstruction(opc_invokeinterface,
							index,nargs,0);
	  if (trace) 
	    System.out.println("Instruction for interface call " + ins);
	  instructions.addElement(ins);
	  break;
	}
	  default:
      }
      break;					 
    }			 
    case MTH_CALL_SPECIAL: 
      {
	methodRef = (MethodRef) nextElement;	
					
	methodRef.generateConstants(state.pool);
	Instruction ins = Instruction.makeInstruction(opc_invokespecial,
						      methodRef.getWhere());	
	int stackref = state.stackSize;
	if (state.operandAlreadyOnTheStack) 
	  stackref--;
	else {
	  instructions.addElement(Instruction.makeInstruction(opc_aload_0));
	  state.pushStack();
	}
	for (int i = 1; i < children.size(); i ++) {
	  nextElement = (Expression) children.elementAt(i);
	  nextElement.emit(state,true,continuation);
	}

	state.popStack(state.stackSize - stackref);
   
	instructions.addElement(ins);
	break;
      }
    default: 
      throw new ClassException("Undefined call type: " + callType);
    }

    // Push for return value if any
    Type methodType = methodRef.getExpressionType();
    boolean twobyte;
    if (methodType.isVoidType())
      return;
    if (twobyte = (methodType.isDoubleType() || methodType.isLongType())) 
      state.pushStack(2);
    else state.pushStack();
    
    // Pop for return value if this is a non-returning context
    if (! leaveOnStack)
      {
	if (twobyte) {
	  instructions.addElement(Instruction.makeInstruction(opc_pop2));
	  state.popStack(2);  
	}
	else {
	  instructions.addElement(Instruction.makeInstruction(opc_pop));
	  state.popStack();  
	}
      }
  }


  @Override
  public String toString() {
    return "<MethodCall, class = " + getClassName() + ", method = " + name 
      +  ", descriptor = " + getExpressionType() + ">";
  }
}
