package com.gensym.newclasstools;

import java.util.Vector;

public class MethodCall extends Call implements RuntimeConstants {
  private static final boolean trace = false;
  protected int callType = -1;
  String name;
  Type classType;
  Type returnType;
  Type[] argumentTypes;

  public String getName() {
    return name;
  }
		
  /**
   * Create a call to a method. If target is null, call is implicitly on "this"
   * - the current instance),
   * or on the class given by classType if this is a static call.
   */
  public MethodCall(String name,
		    Type classType,
		    Type[] argumentTypes,
		    Type returnType,
		    Expression target,
		    Expression[] arguments,
		    int callType)
       throws ClassException
  {
    checkMethodArgumentTypes(argumentTypes, arguments);
    this.argumentTypes = (argumentTypes == null)? new Type[0]: argumentTypes;
    this.name = name;
    this.classType = classType;
    this.returnType = returnType;
    addJavaNode(target); 
    if (arguments != null) {
      for(int i = 0; i < arguments.length; i++) 
	addJavaNode(arguments[i]);
    }
    this.callType = callType;	 
    if (trace) {
      /*
      System.out.println("Just created a method call to " + name + " with " + (children.size() - 1) +  " arguments.");
      for(int i = 0; i < this.argumentTypes.length; i++) {
	System.out.println("Argument #" + i + " has type " + argumentTypes[i]);
      }
      */
    }
  }


  /**
   * Create a call to a method (implicitly on "this" - the current instance
   * if target is null),
   * or on the class that defines the Method if this is a static call. This is
   * the constructor for a call that involves zero arguments.
   */
  public MethodCall(String name, Type classType, Type returnType,
		    Expression target, int callType)
       throws ClassException
  {
    this(name, classType, new Type[]{}, returnType, target, new Expression[]{},
    callType);
  }


  private void checkMethodArgumentTypes(Type[] argumentSpec,
					Expression[] arguments)
       throws ClassException 
  {
    if (arguments == null)  {
      if (argumentSpec != null && argumentSpec.length != 0)
	throw new 
	  ClassException("Incorrect number of arguments passed to method: " +
			 name + " Expected: " + argumentSpec.length +
			 " Received: " + 0);
    }
    else {
      if (arguments.length != argumentSpec.length)
	throw 
	  new ClassException("Incorrect number of arguments passed to method: " +
			     name + " Expected: " + argumentSpec.length + " Received: " +
			     arguments.length);
      for (int i = 0; i < arguments.length; i++) 
	{
	  /*
	  if (trace) {
	    System.out.println("arg " + i + ": " + argumentSpec[i] + " == " + arguments[i]);
	  }
	  */

	  // Cast here is only for numeric arguments, to cast int to long
	  // as appropriate.
	  if (argumentSpec[i].potentialMethodArgumentConversion(arguments[i]))
	    arguments[i] = new Cast(argumentSpec[i], arguments[i], false);
	  // NB. Cast is a no-op when unneeded during emit
	  else 
	    throw 
	      new ClassException("Wrong type for argument to method. Method: "+ 
				 name + " Argument number: " +
				 i + " Expected: " + argumentSpec[i] +
				 " Received: " + 
				 arguments[i].getExpressionType());
	}
    }
  }			

  @Override
  public Type getExpressionType() {
    return returnType;
  }

  public Type getClassType() {
    return classType;
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
    if (trace) {
      System.out.println("Emitting MethodCall " + this);
      System.out.println("Initial stack value is " + state.stackSize);
      System.out.println("operandAlreadyOnTheStack = " + state.operandAlreadyOnTheStack);
      System.out.println("LeaveOnStack is " + leaveOnStack);
    }
    Constant constant;
    if (callType == MTH_CALL_INTERFACE) {
      constant = new InterfaceMethodRefConstant(classType, name, returnType,
						argumentTypes);
    } else {
      constant = new MethodRefConstant(classType, name, returnType,
						argumentTypes);
    }
    Vector instructions =  state.instructions;
    super.emit(state,leaveOnStack,continuation);
    // For each expression that is an argument to this method call
    // emit all instructions
      switch (callType) {
    case MTH_CALL_STATIC:  {
      int stackRef =  state.stackSize;
      // A static call can actually have a target expression, which
      // is evaluated and then thrown away.
      Expression fakeTarget = (Expression) children.elementAt(0);
      if (fakeTarget != null) {
	fakeTarget.emit(state, false, continuation);
      }
      for (int i = 1; i < children.size(); i ++) {
	Expression nextElement = (Expression) children.elementAt(i);
	state.pushStack();
	nextElement.emit(state, true, continuation);
      }

      state.popStack(state.stackSize - stackRef);
      Instruction ins = 
	Instruction.makeInstruction
	(opc_invokestatic, constant);
      instructions.addElement(ins);
      break;
    }
    case MTH_CALL_VIRTUAL:
    case MTH_CALL_INTERFACE:
    case MTH_CALL_SPECIAL:  {
      Expression target = (Expression) children.elementAt(0);
      int stackref = state.stackSize;
      if (trace && (name.equals("intValue")))
	System.out.println("Emitting intvalue target " + target);
      if (state.operandAlreadyOnTheStack) {
	stackref--;
	state.operandAlreadyOnTheStack = false;
      } else {
	if (target == null) {
	  // push "this" onto the stack
	  Instruction ins = Instruction.makeInstruction(opc_aload_0);
	  instructions.addElement(ins);
	  state.pushStack();
	} else {
	  // Case where instance is specified.
	  target.emit(state,true, continuation);
	}
      }
      int reflength = instructions.size();
      int doubleCount = 0;
      for (int i = 1; i < children.size(); i ++) {
	Expression nextElement = (Expression) children.elementAt(i);
	// System.out.println("Emitting expression " + i + ": " + nextElement + "as argument to method call");
	if ((nextElement.getExpressionType().isDoubleType() || 
	     nextElement.getExpressionType().isLongType()))
	  doubleCount++;
	nextElement.emit(state,true, continuation);
      }
      state.popStack(state.stackSize - stackref);   

      int nargs = 0;
      if (callType == MTH_CALL_INTERFACE) {
	nargs = children.size() + doubleCount;
      }
      switch (callType) {
      case MTH_CALL_VIRTUAL:
	{
	  Instruction ins = Instruction.makeInstruction(opc_invokevirtual,
							constant);
	  if (trace)	
	    System.out.println("Instruction for virtual call" + ins);
	  instructions.addElement(ins);
	  break;
	}
      case MTH_CALL_SPECIAL:
	{
	  Instruction ins = Instruction.makeInstruction(opc_invokespecial,
							constant);
	  if (trace)	
	    System.out.println("Instruction for special call" + ins);
	  instructions.addElement(ins);
	  break;
	}
      case MTH_CALL_INTERFACE:
	{

	  Instruction ins = Instruction.makeInstruction(opc_invokeinterface,
							constant, nargs, 0);
	  if (trace) 
	    System.out.println("Instruction for interface call " + ins);
	  instructions.addElement(ins);
	  break;
	}
      }
      break;					 
    }			 

    default: 
      throw new ClassException("Undefined call type: " + callType);
    }

    // Push for return value if any
    boolean twobyte;
    if (returnType.isVoidType()) {
      if (trace) {
	System.out.println("Finished emitting void MethodCall " + this);
	System.out.println("Final stack value is " + state.stackSize);
	System.out.println("operandAlreadyOnTheStack = " + state.operandAlreadyOnTheStack);
      }
      return;
    }
    if (twobyte = (returnType.isDoubleType() | returnType.isLongType())) 
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
    if (trace) {
      System.out.println("Finished emitting MethodCall " + this);
      System.out.println("Final stack value is " + state.stackSize);
      System.out.println("operandAlreadyOnTheStack = " + state.operandAlreadyOnTheStack);
    }
  }


  @Override
  public String toString() {
    return "<MethodCall, class = " + getClassType() + ", method = " + name 
      +  ", argument types = " + argumentTypes + ", return type = " + returnType + ">";
  }
}
