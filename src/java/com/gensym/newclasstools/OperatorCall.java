package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Enumeration;

public class OperatorCall extends Call implements OperatorConstants, MacroNode{
  private int operator = -1;

  // Fields that relate only to assignment operators
  private int secondaryOperator = -1;
  private int setType;

  private Type intType = Type.INT_TYPE;
  private Type booleanType = Type.BOOLEAN_TYPE;
  private static Type stringType  = Type.STRING_TYPE;
  private static Noop noop = new Noop(Type.STRING_TYPE);
  private boolean requiresExpansion = false;
  private boolean trace = false;

  // ******** Constructors  ***********
		
  public OperatorCall(String operator, Expression[] arguments) 
      throws ClassException
  {
    int op = -1;
    int secondary = -1;
    for (int i = 0 ; i < operators.length ; i ++) 
      if (operator.equals(operators[i]))
	op = i;
    if (op == -1) {
      secondary = checkForSecondaryOperator(operator);
      if (secondary == -1)
	throw new ClassException("Operator undefined " + operator);
      op = ASSIGN;
    }
    if (isIncrOrDecrOp(op)) {
      secondary = op;
      op = ASSIGN;
      Expression[] oldarguments = arguments;
      arguments = new Expression[2];
      arguments[0] = oldarguments[0];
      arguments[1] = new Value(1);
    }
    if (arguments.length == 1)
      expressionType = Type.computeResultType(operator, arguments[0].getExpressionType());
    if (arguments.length >= 2)
      if (op == CONDITIONAL) {
	if (trace) {
	  System.out.println("Creating a Conditional");
	  System.out.println("Type of arg 0 is " + arguments[0].getExpressionType());
	  System.out.println("Type of arg 1 is " + arguments[1].getExpressionType());
	  System.out.println("Type of arg 2 is " + arguments[2].getExpressionType());
	}
	if (arguments[0].getExpressionType() == Type.BOOLEAN_TYPE)
	  expressionType = Type.computeResultType("?", arguments[1].getExpressionType(), arguments[2].getExpressionType());
	else
	  throw new ClassException("First argument to conditional operator must be of type boolean");
      } else {
	expressionType = Type.computeResultType(operator, arguments[0].getExpressionType(), arguments[1].getExpressionType());
      }
    if (expressionType == null) {
      throw new ClassException ("bad argument types for operator " + operator);
    }
    init(op,secondary,arguments);
  }

  private void init(int operator, int secondary, Expression[] arguments)
      throws ClassException
  {
    if (operator > operators.length) 
      throw new ClassException("Invalid operator constant " +
			       operators[operator]);
    int count = operandCount[operator];
    if ((arguments.length !=  count) && (count > 0))
      throw new ClassException("Invalid number of arguments to operator " +
                               operators[operator] + 
			       ". Expected " + operandCount[operator] + 
			       " Received " + arguments.length);
    this.operator = operator;
    this.secondaryOperator = secondary;
					      
    // Check any special case types for primary operator
    switch (operator) {
    case ASSIGN:
      checkAssignArguments(arguments);
      break;
    case PLUS:  {
      if (plusIsNumeric(arguments)) {
	checkPlusOrMinusArguments(arguments);
      }
      break;
    }
    case MINUS: {
      checkPlusOrMinusArguments(arguments);
      break;	}
    case ONES_COMPLEMENT: {
      checkNumericArguments(arguments);
      requiresExpansion = true;
      break; }
    case MULTIPLY: {
      checkNumericArguments(arguments);
      break; }
    case DIVIDE:
    case REMAINDER: {
      checkDivisionArguments(arguments);
      break; }
    case AND:
    case OR: 
    case XOR: {
      checkBitwiseArguments(arguments);
      break;}
    case LEFT_SHIFT: 
    case RIGHT_SHIFT: 
    case UNSIGNED_RIGHT_SHIFT: {
      checkShiftArguments(arguments);
      break;}
    case GREATER_THAN_OR_EQUAL: 
    case LESS_THAN_OR_EQUAL: 
    case GREATER_THAN: 
    case LESS_THAN: {
      checkNumericArguments(arguments);
      requiresExpansion = true;
      break;}
    case BOOLEAN_AND:
    case BOOLEAN_OR:
    case NOT: {
      requiresExpansion = true;
      break;}
    case EQUALITY:
    case NOT_EQUAL: {
      checkEqualityArguments(arguments);
      requiresExpansion = true;
      break; }
    case CONDITIONAL: {
      checkConditionalArguments(arguments);
      break;
    }
    case INSTANCEOF: {
      checkInstanceofArguments(arguments);
      break;
    }
    }

    // Check any special case types for secondary operator
    switch (secondaryOperator) {
    case PLUS: {
      if (plusIsNumeric(arguments)) 
	checkPlusOrMinusArguments(arguments);
      break; }
    case MINUS:
    case POST_PLUS_PLUS:
    case POST_MINUS_MINUS:
    case PRE_PLUS_PLUS:
    case PRE_MINUS_MINUS:
      {
      checkPlusOrMinusArguments(arguments);
      break; }
    case MULTIPLY:
    case DIVIDE:
    case REMAINDER: {
      checkNumericArguments(arguments);
      break; }
    case LEFT_SHIFT: 
    case RIGHT_SHIFT: 
    case UNSIGNED_RIGHT_SHIFT: {
      checkShiftArguments(arguments);
      break;
    }
    case AND:
    case OR: 
    case XOR: {	
      checkBitwiseArguments(arguments);	
      break;
    }
    }

    for (int i = 0; i < arguments.length ; i ++)
      addJavaNode(arguments[i]);
  }

  static boolean isIncrOrDecrOp(int operator) {
    return
      (operator == PRE_PLUS_PLUS) || (operator == POST_PLUS_PLUS) || 
      (operator == PRE_MINUS_MINUS) || (operator == POST_MINUS_MINUS);
  } 

  private int checkForSecondaryOperator(String operator) {
    int secondary = -1;
    if ((operator.length() > 1) && operator.charAt(1) == ASSIGNC)  {
      String second = operator.substring(0,1);
      for (int i = 0 ; i < operators.length ; i ++) 
	if (second.equals(operators[i])) {
	  if (assignableOperators.indexOf(second) != -1) {
	    secondary = i;
	  }
	}
    }
    else if (operator.length() > 2 && operator.charAt(2) == ASSIGNC) {
      String second = operator.substring(0,2);
      for (int i = 0 ; i < operators.length ; i ++) 
	if (second.equals(operators[i])) {
	  if (assignableOperators.indexOf(second) != -1) {
	    secondary = i;
	  }
	}
    } else if (operator.length() > 2 && operator.charAt(3) == ASSIGNC) {
      String second = operator.substring(0,3);
      for (int i = 0 ; i < operators.length ; i ++) 
	if (second.equals(operators[i])) {
	  if (assignableOperators.indexOf(second) != -1) {
	    secondary = i;
	  }
	}
    }
    return secondary;
  }
		

  // ************ Operator specific constructor code *****************
		
  private void checkEqualityArguments(Expression [] args) 
      throws ClassException
  {
    Expression arg0 = args[0];
    Expression arg1 = args[1];
    Type tpe0 = arg0.getExpressionType();
    Type tpe1 = arg1.getExpressionType();

    if (tpe0.isNumericType()){
      if (! tpe1.isNumericType())
	throw new ClassException("Incompatable type for ==. Can't convert non-numeric to numeric type");
      else checkNumericArguments(args);
    }
    else 
      if (tpe1.isNumericType())
	throw new ClassException("Incompatable type for ==. Can't convert non-numeric to numeric type");
      else  {
	if (tpe0.isBooleanType())
	  if (!tpe1.isBooleanType())
	    throw new ClassException("Incompatable type for ==. Can't convert non-boolean to boolean type");
      }
  }	 

  private void checkConditionalArguments(Expression [] args) 
      throws ClassException
  {
    Expression arg0 = args[0];
    Expression arg1 = args[1];
    Expression arg2 = args[2];
    Type tpe0 = arg0.getExpressionType();
    Type tpe1 = arg1.getExpressionType();
    Type tpe2 = arg2.getExpressionType();
    if (!(tpe0.isBooleanType()))
      throw new ClassException("Invalid condition type: " + tpe0);
    if (tpe1.potentialAssignmentConversion(arg2))
      args[2] = new Cast(tpe1,args[2],false);
    else if (tpe2.potentialAssignmentConversion(arg1))
      args[1] = new Cast(tpe2,args[1],false); 
    // else exception
    else throw new ClassException("Inconsistent conditional return types: " 
+ tpe1 + ", and " + tpe2);
  }	 


  private void checkAssignArguments(Expression [] args) throws ClassException {
    Expression arg0 = args[0];
    Expression arg1 = args[1];
    if (! ((arg0 instanceof FieldRef) || (arg0 instanceof Variable) 
	   || (arg0 instanceof ArrayRef))) 
      throw 
	new ClassException("Assignment operator only applicable to local variables, fields or array elements");
    Type tpe = arg1.getExpressionType();
    if (!expressionType.potentialAssignmentConversion(arg1)) 
      throw new ClassException("Invalid type for assignment, type = " +
			       expressionType + ", expression type = " + tpe);
    if (arg0 instanceof FieldRef) {
      FieldRef fieldRef = (FieldRef) arg0;
      if (fieldRef.isStaticRef())
	setType = SET_STATIC_FIELD;
      else setType = SET_FIELD;
    }
    else {
      if (arg0 instanceof Variable) {
	Variable var = (Variable) arg0;
	setType = SET_VARIABLE;
      }
      else {
	setType = SET_ARRAY;
      }
    }
    // If there is no need for a conversion cast becomes a No-op
    args[1] = new Cast(expressionType,args[1], false);
  }

  private void checkInstanceofArguments(Expression[] args) 
      throws ClassException
  {
    Expression arg0 = args[0];
    Expression arg1 = args[1];
    if (! (arg1 instanceof ClassRef))
      throw 
	new ClassException("Invalid class reference for instanceof operator");
  }

  // ***** Arithmetic operators constructor code *****************

  private void checkPlusOrMinusArguments(Expression[] args) 
      throws ClassException
  {
    checkOneOrTwoArgs(args);
    checkNumericArguments(args);
  }

  private boolean plusIsNumeric(Expression[] args) 
      throws ClassException
  {
    boolean good = true;
    for (int i = 0; i < args.length; i ++) {
      Expression arg = args[i];
      if (!arg.getExpressionType().isNumericType())
	good = false;
    }
    if (good) 
      return true;
    for (int i = 0; i < args.length ; i ++) {
      Expression arg = args[i];
      if (stringType.equals (arg.getExpressionType())) 
	good = true;
      if (arg instanceof OperatorCall && 
	  (((OperatorCall) arg).getPrimaryOperator() == PLUS)) 
	requiresExpansion = true;
    }
    if (good) 
      return false;
    else
      throw new ClassException("Invalid operand type to: " +
			       operators[operator]);
  }

  private void checkOneOrTwoArgs(Expression[] args) throws ClassException {
    if (args.length > 2)
      throw new ClassException("Invalid number of arguments to operator " +
                               operators[operator] + 
			       ". Expected 1 or 2 Received " + args.length);
  }

  private void checkNumericArguments(Expression[] args) throws ClassException {
    Type type0 = args[0].getExpressionType();
    // Binary numeric promotion pp 19-20
    if (args.length == 2) {
      Type type1 = args[1].getExpressionType();
      boolean t0is = type0.isDoubleType();
      boolean t1is = type1.isDoubleType();
      if (t0is | t1is) {
	if (! t0is)
	  args[0] = new Cast(type1,args[0], false);
	if (! t1is) 
	  args[1] = new Cast(type0,args[1], false);
      }
      else {
	t0is = type0.isFloatType();
	t1is = type1.isFloatType();			
	if (t0is | t1is) {
	  if (! t0is)
	    args[0] = new Cast(type1,args[0], false);
	  if (! t1is) 
	    args[1] = new Cast(type0,args[1], false);
	}
	else {
	  t0is = type0.isLongType();
	  t1is = type1.isLongType();
	  if (t0is | t1is) {
	    if (! t0is)
	      args[0] = new Cast(type1,args[0], false);
	    if (! t1is) 
	      args[1] = new Cast(type0,args[1], false);
	  }
	  else {
	    t0is = type0.isIntegerType();
	    t1is = type1.isIntegerType();
	    if (! t0is)
	      args[0] = new Cast(intType,args[0], false);
	    if (! t1is) 
	      args[1] = new Cast(intType,args[1], false);
	  }
	}
      }
    }
    else {     // Unary Numeric promotion
      if (type0.isShortType() || type0.isByteType() || type0.isCharType())
	args[0] = new Cast(intType, args[0], false);
    }
  }

  public void checkDivisionArguments(Expression[] args) throws ClassException {
    // Division by zero check at compile time
    Expression arg0 = args[0];
    if ((arg0 instanceof Value) && ((Value) arg0).isZero())
      throw new ClassException("Arithmetic Exception");
    else checkNumericArguments(args);
  }

  public void checkShiftArguments(Expression[] args) throws ClassException {
    args[1] = new Cast(intType,args[1], false);			
  }

  public void checkBitwiseArguments(Expression[] args) throws ClassException {
    //pg 365 "The Java Language Specification"
    if (!(args[0].getExpressionType().isBooleanType() &
	  args[0].getExpressionType().isBooleanType()))
      checkNumericArguments(args);
  }


  // *********** Predicates ******************

  /**
   * @deprecated Please use isExpressionStatement instead
   */
  public boolean isStatementExpression() {
    return isExpressionStatement();
  }

  public boolean isExpressionStatement() {
    return (isAssignmentOperator());
  }
			
  public boolean isAssignmentOperator() {
    return (operator == ASSIGN); 
  }

  public boolean isConditionalOperator() {
    return (operator == CONDITIONAL); 
  }

  public boolean isSimpleBranch() {
    switch (operator)	{	
    case GREATER_THAN_OR_EQUAL: 
    case LESS_THAN_OR_EQUAL: 
    case GREATER_THAN: 
    case LESS_THAN:
    case NOT:
    case EQUALITY:
    case NOT_EQUAL:
      return true;
    default: return false;
    }
  }

  public boolean isLogicalBranch() {
    switch (operator)	{	
    case BOOLEAN_AND:
    case BOOLEAN_OR:
      return true;
    default: return false;
    }
  }


  // ************ Get methods **************


  public int getPrimaryOperator() {
    return operator;
  }

  public int getSecondaryOperator() {
    return secondaryOperator;
  }




  //********* Emitting ***********

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation) 
      throws ClassException
  {
    // System.out.println("Emitting Operator Call " + this + "; operator is " + operator);
    // ************  Assignment Operators *******
    if (operator == ASSIGN) 
      emitAssign(state,leaveOnStack,continuation);	
    else {
      generateLineNumberInfo(state);
      Expression arg0 = null;
      Expression arg1 = null;
      Expression arg2 = null;
      int numberOfSubExpressions = children.size();
      if (numberOfSubExpressions == 1) 
	arg0 =  (Expression) children.elementAt(0);
      else if (numberOfSubExpressions == 2) {
	arg0 =  (Expression) children.elementAt(0);
	arg1 =  (Expression) children.elementAt(1);
      }
      else  {
	arg0 =  (Expression) children.elementAt(0);
	arg1 =  (Expression) children.elementAt(1);
	arg2 =  (Expression) children.elementAt(2);
      }
      switch (operator) {
		
	// ***********  Conditional Operators *******
						
      case CONDITIONAL: {
	emitConditional(state,leaveOnStack,arg0,arg1,arg2,continuation);
	break;
      }
      //*************** Equality Operators **************

      case EQUALITY: {
	emitEqual(state,arg0,arg1,continuation);
	break;
      }
      case NOT_EQUAL: {
	emitNotEqual(state,arg0,arg1,continuation);
	break;
      }

      //******** Arithmetic Operators ************
					
      case PLUS: {
	// System.out.println("Emitting +; arguments are " + children + "expressionType is " + expressionType);
	if (expressionType.equals(stringType))
	  emitStringPlus(state,null,children,continuation);
	else {
	  if (numberOfSubExpressions == 2) 
	    emitPlus(state,expressionType,arg0,arg1,continuation);
	  else emitUnaryPlus(state,expressionType,arg0,continuation);
	}
	break;
      } 
      case MINUS: {
	if (numberOfSubExpressions == 2) 
	  emitMinus(state,expressionType,arg0,arg1,continuation);
	else emitUnaryMinus(state,expressionType,arg0,continuation); 
	break;
      } 
      case MULTIPLY: {
	emitMultiply(state,expressionType,arg0,arg1,continuation);
	break;
      } 
      case DIVIDE: {
	emitDivide(state,expressionType,arg0,arg1,continuation);
	break;
      } 
      case REMAINDER: {
	emitRemainder(state,expressionType,arg0,arg1,continuation);
	break;
      }
      case GREATER_THAN_OR_EQUAL: {
	emitGeq(state,arg0,arg1,continuation);
	break;
      } 
      case LESS_THAN_OR_EQUAL: {
	emitLeq(state,arg0,arg1,continuation);
	break;
      }	
      case GREATER_THAN: {
	emitGt(state,arg0,arg1,continuation);
	break;
      }
      case LESS_THAN: {
	emitLt(state,arg0,arg1,continuation);
	break;	
      }
					
      //********************  Bitwize Operators *********************

      case AND: {
	emitBitwiseAnd(state,expressionType,arg0,arg1,continuation);
	break;
      } 
      case OR: {
	emitBitwiseOr(state,expressionType,arg0,arg1,continuation);
	break;
      }
      case XOR: {
	emitBitwiseXor(state,expressionType,arg0,arg1,continuation);
	break;
      } 
      case LEFT_SHIFT: {
	emitLeftShift(state,expressionType,arg0,arg1,continuation);
	break;
      } 
      case RIGHT_SHIFT: {
	emitRightShift(state,expressionType,arg0,arg1,continuation);
	break;
      }
      case UNSIGNED_RIGHT_SHIFT: {
	emitUnsignedRightShift(state,expressionType,arg0,arg1,continuation);
	break;
      }
					
      //************ Boolean Operators *********
					
      case BOOLEAN_AND: {
	emitBooleanAnd(state,arg0,arg1,continuation);
	break;
      }		
      case BOOLEAN_OR: {
	emitBooleanOr(state,arg0,arg1,continuation);
	break;
      }
      case NOT: {
	emitBooleanNot(state,arg0,continuation);
	break;
      }
						
      //****************  Instanceof Operator **********
      case INSTANCEOF: {
	emitInstanceof(state,arg0,arg1,continuation);
	break;
      }
      }
    }	
  }

  //**********  Emit code for individual Operators *******************


  // **********  Assignment Operators ********************************

  void emitAssign(EmitState state, boolean leaveOnStack,
		  Statement continuation) 
      throws ClassException
  {
    if (trace) {
      System.out.println("emitAssign called: setType is " + setType + ", stack size is " + state.stackSize);
      System.out.println("leaveOnStack is " + leaveOnStack);
    }
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;  
    Expression nextElement = (Expression) children.elementAt(0);	
		
    int ref = 1;
    switch (setType) {
    case SET_VARIABLE: {
      Instruction ins;	
      // push value onto stack
      Variable var = (Variable) nextElement;
      var.generateVariableIds(state);
      Expression val = (Expression) children.elementAt(1);
      boolean iinc_used = false;
      
      // Secondary Operator
      if (secondaryOperator != -1) 
        iinc_used = emitSecondaryOperator(state,true,continuation);
      else val.emit(state,true,continuation);       
      
      // Leaving result on the stack
      if (leaveOnStack) {
        if (iinc_used) 
          var.emit(state,true,continuation);	
        else Instruction.emitDupInstruction(state,val.getExpressionType());	
      }
      
      // use appropriate local variable set instruction to set the value
      // into the local var vector
      if (! iinc_used) {
        Type tpe = var.getExpressionType();
        int argumentNumber = var.argumentNumber;
        Instruction.emitElementStoreInstruction(state,tpe,argumentNumber);
      }
      break;}
    case SET_FIELD: {
      int stackRef = state.stackSize;
      FieldRef fieldRef = (FieldRef) nextElement;
      nextElement = (Expression) children.elementAt(1);
      
      // Either put the object being referred to or "this" on the stack	
      if (fieldRef.hasChildren()) { 
        Enumeration e = fieldRef.getChildren();
        JavaNode j =(JavaNode) e.nextElement();
        j.emit(state,true,continuation);
      }
      else {
        Instruction ins = Instruction.makeInstruction(opc_aload_0);
        state.pushStack();
        instructions.addElement(ins);
      }
      // Secondary operator
      if (secondaryOperator != -1) {			
	emitSecondaryOperator(state,true, continuation);			
      }
      else nextElement.emit(state,true, continuation);
	
      state.popStack(state.stackSize - stackRef);
      // Leaving result on the stack
      if (leaveOnStack)
	Instruction.emitDupX1Instruction(state,nextElement.getExpressionType());
      Instruction ins = Instruction.makeInstruction(opc_putfield,fieldRef.constant);
      instructions.addElement(ins);
      break;
    }
    case SET_STATIC_FIELD: {
      int stackRef =  state.stackSize;
      FieldRef fieldRef = (FieldRef) nextElement;
      nextElement = (Expression) children.elementAt(1);
									
      // Secondary operator
      if (secondaryOperator != -1) 			
        emitSecondaryOperator(state,true,continuation);			
      else nextElement.emit(state,true,continuation);

      state.popStack(state.stackSize - stackRef);
      
      // Leaving result on the stack
      if (leaveOnStack)
        Instruction.emitDupInstruction(state,nextElement.getExpressionType());
							
      Instruction ins = Instruction.makeInstruction(opc_putstatic,fieldRef.constant);
      instructions.addElement(ins);
      if (trace)	
	System.out.println("Instruction for field set" + ins);
      break; }
    case SET_ARRAY:   {
      Enumeration e = ((ArrayRef) nextElement).getChildren();
      Expression exp = (Expression) e.nextElement();
      exp.emit(state,true,continuation);
      ((Expression) e.nextElement()).emit(state,true,continuation);
      nextElement = (Expression) children.elementAt(1);
      
      // Secondary operator
      if (secondaryOperator != -1) 			
	emitSecondaryOperator(state,true,continuation);			
      else nextElement.emit(state,true,continuation);
	
      // Leaving result on the stack
      if (leaveOnStack)
        Instruction.emitDupX2Instruction(state,
					 nextElement.getExpressionType());
     
      Instruction.emitArrayStoreInstruction(state,expressionType);
      break;
    }
    default:
      throw new ClassException("Cannot emit - invalid set type " + setType); 
    }
    if (leaveOnStack && (secondaryOperator == POST_PLUS_PLUS)) {
      Cast cast = new Cast(expressionType, new Value(1), false);
      cast.emit(state, true, continuation);
      Instruction.emitMinusInstruction(state, expressionType);
    }
    if (leaveOnStack && (secondaryOperator == POST_MINUS_MINUS)) {
      Cast cast = new Cast(expressionType, new Value(1), false);
      cast.emit(state, true, continuation);
      Instruction.emitPlusInstruction(state, expressionType);
    }
    if (trace) {
      System.out.println("emitAssign returns: stack size is " + state.stackSize);
    }

  }

	
  private boolean emitSecondaryOperator(EmitState state, 
                                        boolean leaveOnStack,
                                        Statement continuation) 
      throws ClassException
  {
    if ((secondaryOperator == PLUS) &&
	(expressionType.equals(stringType) ||
	 ((Expression)children.elementAt(1)).getExpressionType().equals(stringType)))
      return emitSecondaryStringPlus(state,continuation);
    switch (setType) {
    case SET_VARIABLE: {
      Variable arg0 = (Variable) children.elementAt(0);
      Expression arg1 = (Expression) children.elementAt(1);		
      switch (secondaryOperator) {
      case PLUS:
      case MINUS:
      case POST_PLUS_PLUS:
      case POST_MINUS_MINUS:
      case PRE_PLUS_PLUS:
      case PRE_MINUS_MINUS:
	{
	  arg0.generateVariableIds(state);
	  if ((arg1 instanceof Value) &&
	      (arg0.getExpressionType().isSmallIntegralType()) &&
	      (arg1.getExpressionType().isSmallIntegralType())) {
	    Value val = (Value) arg1;
	    Instruction ins;
	    if (val.canFitInSingleSignedByte()) 
	      ins = Instruction.makeInstruction(opc_iinc,arg0.argumentNumber,((Value) arg1).getIntegerValueIfAny());
	    else { 
	      int val2 = ((Value) arg1).getIntegerValueIfAny();
	      if (secondaryOperator == MINUS)
		ins = Instruction.makeInstruction(opc_wide,opc_iinc,arg0.argumentNumber,-val2);
	      else ins = Instruction.makeInstruction(opc_wide,opc_iinc,arg0.argumentNumber,val2);
	    }	
	    state.instructions.addElement(ins);
	    return true;
	  }
	}
      default:  {
	emit2Args(state, arg0, arg1, continuation);	
	emitSecondaryOperatorInstruction(state,expressionType,secondaryOperator);
      }
      }
      break;
    }
    case SET_STATIC_FIELD: {						
      ((Expression) children.elementAt(0)).emit(state,true,continuation);
      ((Expression) children.elementAt(1)).emit(state,true,continuation);
      emitSecondaryOperatorInstruction(state,expressionType,secondaryOperator);		
      break;				
    }
    case SET_FIELD: {
      // Optimization involving copying reference on the stack
      // to the instance with the field. Reference is either "this" or result
      // of some other expression
      state.instructions.addElement(Instruction.makeInstruction(opc_dup));
      FieldRef fieldRef = (FieldRef) children.elementAt(0);
      Type frtp = fieldRef.getExpressionType();
      Instruction ins;
      ins = Instruction.makeInstruction(opc_getfield,fieldRef.constant);
      state.instructions.addElement(ins);
      if (frtp.isDoubleType() | frtp.isLongType())
	state.pushStack(2);
      else state.pushStack();
      ((Expression) children.elementAt(1)).emit(state,leaveOnStack,continuation);
      emitSecondaryOperatorInstruction(state,expressionType,secondaryOperator);	
      break;
    }
    case SET_ARRAY: {
      // duplicate the array which is already on the stack
      state.instructions.addElement(Instruction.makeInstruction(opc_dup2)); 
      state.pushStack(2);
      Instruction.emitArrayLoadInstruction(state,expressionType);
      ((Expression) children.elementAt(1)).emit(state,true,continuation);
      emitSecondaryOperatorInstruction(state,expressionType,secondaryOperator);
      break;
    }
    }
    return false;
  }

  private boolean emitSecondaryStringPlus(EmitState state, Statement continuation) 
      throws ClassException
  {
    switch (setType) {
    case SET_VARIABLE: {
      Variable arg0 = (Variable) children.elementAt(0);
      arg0.generateVariableIds(state);
      emitStringPlus(state,null,children,continuation);		
      break;
    }
    case SET_STATIC_FIELD: {						
	
      emitStringPlus(state,null,children,continuation);		
      break;				
    }
    case SET_FIELD: {
      // Optimization involving copying reference on the stack
      // to the instance with the field. Reference is either "this" or result
      // of some other expression
      state.instructions.addElement(Instruction.makeInstruction(opc_dup));
	
      // Put field on the stack
      FieldRef fieldRef = (FieldRef) children.elementAt(0);
      Type frtp = fieldRef.getExpressionType();
      Instruction ins;
      ins = Instruction.makeInstruction(opc_getfield,fieldRef.constant);
      state.instructions.addElement(ins);

      // Create a new Node, assuming first string is already on the stack 
      New buffer = new New(Type.STRING_BUFFER_TYPE,
			   new Type[]{Type.STRING_TYPE},
			   new Expression[] { noop });
      // Already have StringBuffer and String on the stack so: 
      Vector v = new Vector();
      v.addElement(children.elementAt(1));
      emitStringPlus(state,buffer,v,continuation);
      break;
    }
    case SET_ARRAY: {
      // duplicate the array which is already on the stack
      state.instructions.addElement(Instruction.makeInstruction(opc_dup2)); 
      state.pushStack(2);
      Instruction.emitArrayLoadInstruction(state,expressionType);
      // Create a new Node, assuming first string is already on the stack 
      New buffer = new New(Type.STRING_BUFFER_TYPE,
			   new Type[]{Type.STRING_TYPE},
			   new Expression[] { noop });
      // Already have StringBuffer and String on the stack so: 
      Vector v = new Vector();
      v.addElement(children.elementAt(1));
      emitStringPlus(state,buffer,v,continuation);
      break;
    }
    }
    return false;
  }

  //******************* Conditional Operator **********************************

  static final void emitConditional(EmitState state, 
                                    boolean leaveOnStack,
                                    JavaNode arg0, 
                                    JavaNode arg1, JavaNode arg2,
                                    Statement continuation)
      throws ClassException
  {      
    Vector instructions = state.instructions; 
    OperatorCall operatorCall = null;
    boolean orBranch = false;
    boolean logicalBranch = false;
    // Support for use when emitting If
    boolean forkBranch = (arg2 != null);
    int defaultBranch = opc_ifeq;
      
    arg0.emit(state,true,continuation);
    if (arg0 instanceof OperatorCall) {
      operatorCall = (OperatorCall) arg0;
     
      if (operatorCall.isOrBranch())
	orBranch = true;
      
      if (operatorCall.isLogicalBranch()) {
	logicalBranch = true;
      }
      else if (!operatorCall.isSimpleBranch())
	instructions.addElement(Instruction.makeInstruction(defaultBranch,0));
    }
    else instructions.addElement(Instruction.makeInstruction(defaultBranch,0));
      
    Instruction ifi2 = null;

    if (logicalBranch) {
      // Need to get the one before last if instruction from the 
      // instructions  vector, it must also not have a jump target
      // yet, and not have a label 
      for (int i = (instructions.size() - 2); i > -1; i --) {
	ifi2 = ((Instruction) instructions.elementAt(i));
	if (ifi2.isIfInstruction() && 
	    (ifi2.jumpDestination == null) &&
	    (ifi2.labelNameIfAny == null)) {
	  //System.out.println("Logical Branch Inst: " + ifi2);
	  break;
	}
	else ifi2 = null;
      }
      if (ifi2 == null)  
	throw new ClassException("Compiler bug - failure to emit components");
    }

    Instruction ifi = (Instruction) instructions.lastElement();

    int stackRef = state.stackSize;
       
    Instruction jump1 = null;
    if (orBranch) {
      jump1 = state.getJumpTargetInstruction();
      instructions.addElement(jump1);
    }

    // System.out.println("Emitting then branch of Conditional, " + arg1);
    // System.out.println("This is of type, " + arg1.getClass());
    arg1.emit(state,leaveOnStack,continuation);
	 
    // because they won't both be on the stack at the same time
    state.popStack(state.stackSize - stackRef);

    Instruction gotoInst = null;
    if (forkBranch) {
      if ((continuation == null) && (! leaveOnStack)) 
	{
	  state.doContinuation(continuation);
	}
      else {
	gotoInst = Instruction.makeInstruction(opc_goto,0);
	instructions.addElement(gotoInst);
      }
    }
    Instruction jump2 = state.getJumpTargetInstruction();
    Instruction jump3 = null;
    instructions.addElement(jump2);

    if (forkBranch) { 
      jump3 = state.getJumpTargetInstruction();
      arg2.emit(state,leaveOnStack,continuation);
      instructions.addElement(jump3);
    }
    if (orBranch) {
      ifi2.jumpDestination = jump1;
    }
    else if (logicalBranch) {
      ifi2.jumpDestination = jump2;
    }
 
    ifi.jumpDestination = jump2;

    if (forkBranch && (gotoInst != null)) 
      gotoInst.jumpDestination = jump3;

    if (! leaveOnStack) 
      state.doContinuation(continuation);
  }

  //******************* Equality Operators ************************************
	
  static final void emitEqual(EmitState state, Expression arg0, 
			      Expression arg1,
			      Statement continuation) 
      throws ClassException
  {
    // Dealing with null cases.  
    // Note the null == null case should be dealt with before emitting:
    if (arg0 instanceof Value && ((Value) arg0).isNull()) {
      arg1.emit(state,true,continuation);
      state.instructions.addElement(Instruction.makeInstruction(opc_ifnonnull,0));
    }
    else if (arg1 instanceof Value && ((Value) arg1).isNull()) {
      arg0.emit(state,true,continuation);
      state.instructions.addElement(Instruction.makeInstruction(opc_ifnonnull,0));
    }
    else {
      Type tpe = arg0.getExpressionType();
      if (tpe.isBooleanType()) {
	if (arg0 instanceof Value) 
	  arg1.emit(state,true,continuation);
	else if (arg1 instanceof Value) 
	  arg0.emit(state,true,continuation);			
	else emit2Args(state, arg0, arg1,continuation);				
	Instruction.emitNeqInstructions(state,arg0.getExpressionType(),
					arg0,arg1);
      }
      else {
	emit2Args(state, arg0, arg1,continuation);
	Instruction.emitNeqInstructions(state,arg0.getExpressionType(),
					arg0,arg1);
      }
    }
  }

  static final void emitNotEqual(EmitState state, Expression arg0, 
				 Expression arg1,
				 Statement continuation) 
      throws ClassException
  {
    // Dealing with null cases.  
    // Note the null != null case should be dealt with before emitting:
    if (arg0 instanceof Value && ((Value) arg0).isNull()) {
      arg1.emit(state,true,continuation);
      state.instructions.addElement(Instruction.makeInstruction(opc_ifnull,0));
    }
    else if (arg1 instanceof Value && ((Value) arg1).isNull()) {
      arg0.emit(state,true,continuation);
      state.instructions.addElement(Instruction.makeInstruction(opc_ifnull,0));
    }
    else {
      Type tpe = arg0.getExpressionType();
      if (tpe.isBooleanType()) {
	if (arg0 instanceof Value) 
	  arg1.emit(state,true,continuation);
	else if (arg1 instanceof Value) 
	  arg0.emit(state,true,continuation);			
	else emit2Args(state, arg0, arg1, continuation);				
	Instruction.emitEqInstructions(state,arg0.getExpressionType(),
				       arg0,arg1);
      }
      else {
	emit2Args(state, arg0, arg1,continuation);
	Instruction.emitEqInstructions(state,arg0.getExpressionType(),
				       arg0,arg1);
      }			
    }
  }

  //******************* Arithmetic Operators *********************************

  // Using static final methods to inline everything when compiled with -O

  static final void emit2Args(EmitState state, Expression arg0, 
			      Expression arg1,
			      Statement continuation) 
      throws ClassException
  {
    arg0.emit(state,true,continuation);
    arg1.emit(state,true,continuation);
  }

  static final void  emitPlus(EmitState state, Type tpe, Expression arg0, 
			      Expression arg1,
			      Statement continuation) 
      throws ClassException
  {
    emit2Args(state, arg0, arg1,continuation);
    Instruction.emitPlusInstruction(state,tpe);
  }

  static final void  emitUnaryPlus(EmitState state, Type tpe, 
				   Expression arg0, Statement continuation) 
      throws ClassException
  {
    // Because Unary promotion is all there is to Unary plus in Java, 
    // see p348 "Java Language Spec"
    arg0.emit(state,true,continuation);
  }

  static final void emitMinus(EmitState state, Type tpe, Expression arg0, 
			      Expression arg1,
			      Statement continuation) 
      throws ClassException
  {	
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitMinusInstruction(state,tpe);
  }

  static final void  emitUnaryMinus(EmitState state, Type tpe, 
				    Expression arg0,
				    Statement continuation) throws ClassException
  {
    arg0.emit(state,true,continuation);
    Instruction.emitNegateInstruction(state,tpe);
  }

  static final void emitMultiply(EmitState state, Type tpe, Expression arg0,
				 Expression arg1, Statement continuation)
      throws ClassException
  {     
    emit2Args(state, arg0, arg1,continuation);
    Instruction.emitMultiplyInstruction(state,tpe);
  }

  static final void emitDivide(EmitState state, Type tpe, Expression arg0, 
			       Expression arg1, Statement continuation)
      throws ClassException
  {	
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitDivideInstruction(state,tpe);
  }

  static final void emitRemainder(EmitState state, Type tpe, Expression arg0, 
				  Expression arg1, Statement continuation) 
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitRemainderInstruction(state,tpe);
  }

  static final void emitGeq(EmitState state, Expression arg0, 
			    Expression arg1, Statement continuation)
      throws ClassException
  {			
    emit2Args(state,arg0,arg1,continuation);
    Instruction.emitGeqInstructions(state,arg0.getExpressionType());
  }

  static final void emitLeq(EmitState state, Expression arg0, 
                            Expression arg1, Statement continuation)
      throws ClassException
  {		
    emit2Args(state,arg0,arg1,continuation);
    Instruction.emitLeqInstructions(state,arg0.getExpressionType());
  }

  static final void emitLt(EmitState state, Expression arg0, Expression arg1,
                           Statement continuation)
      throws ClassException
  {					
    emit2Args(state,arg0,arg1,continuation);
    Instruction.emitLtInstructions(state,arg0.getExpressionType());
  }

  static final void emitGt(EmitState state, Expression arg0, 
                           Expression arg1, 
                           Statement continuation)
      throws ClassException
  {			
    emit2Args(state,arg0,arg1,continuation);
    Instruction.emitGtInstructions(state,arg0.getExpressionType());
  }


  static final void emitSecondaryOperatorInstruction(EmitState state, 
						     Type tpe, 
						     int secondaryOperator) 
      throws ClassException
  {	
    switch (secondaryOperator) {
    case PLUS: 
    case PRE_PLUS_PLUS:
    case POST_PLUS_PLUS:
      Instruction.emitPlusInstruction(state,tpe);
      break;
    case MINUS: 	
    case PRE_MINUS_MINUS:
    case POST_MINUS_MINUS:
      Instruction.emitMinusInstruction(state,tpe);
      break;
    case MULTIPLY:
      Instruction.emitMultiplyInstruction(state,tpe);
      break;
    case DIVIDE:
      Instruction.emitDivideInstruction(state,tpe);
      break;
    case REMAINDER:
      Instruction.emitRemainderInstruction(state,tpe);
      break;
    case AND:
      Instruction.emitBitwiseAndInstruction(state,tpe);
      break; 
    case OR:
      Instruction.emitBitwiseOrInstruction(state,tpe);
      break;
    case XOR: 
      Instruction.emitBitwiseXorInstruction(state,tpe);
      break;
    case LEFT_SHIFT:
      Instruction.emitLeftShiftInstruction(state,tpe);
      break;
    case RIGHT_SHIFT:
      Instruction.emitRightShiftInstruction(state,tpe);
      break;			
    case UNSIGNED_RIGHT_SHIFT:
      Instruction.emitUnsignedRightShiftInstruction(state,tpe);
      break;			
    }
  }

  //******************************  Bitwise Operators *************/

  static final void  emitBitwiseOr(EmitState state, Type tpe, 
				   Expression arg0, Expression arg1,
				   Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitBitwiseOrInstruction(state,tpe);
  }

  static final void  emitBitwiseAnd(EmitState state, Type tpe, 
				    Expression arg0, Expression arg1,
				    Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitBitwiseAndInstruction(state,tpe);
  }

  static final void  emitBitwiseXor(EmitState state, Type tpe, 
				    Expression arg0, Expression arg1,
				    Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitBitwiseXorInstruction(state,tpe);
  }

  static final void  emitLeftShift(EmitState state, Type tpe, 
				   Expression arg0, Expression arg1,
				   Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitLeftShiftInstruction(state,tpe);
  }

  static final void  emitRightShift(EmitState state, Type tpe, 
				    Expression arg0, Expression arg1,
				    Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitRightShiftInstruction(state,tpe);
  }

  static final void  emitUnsignedRightShift(EmitState state, Type tpe,
					    Expression arg0, Expression arg1,
					    Statement continuation)
      throws ClassException
  {
    emit2Args(state, arg0, arg1, continuation);
    Instruction.emitUnsignedRightShiftInstruction(state,tpe);
  }


  //*******************************  Instanceof Operator *********************

  static final void emitInstanceof(EmitState state, Expression arg0, 
				   Expression arg1,
				   Statement continuation)
      throws ClassException
  {
    arg0.emit(state,true,continuation);
    state.instructions.addElement(Instruction.makeInstruction(opc_instanceof,
							      ((ClassRef)arg1).constant));
  }


  //******************************* Operators that return boolean values *****
	
  static final void emitBooleanAnd(EmitState state, Expression arg0,
				   Expression arg1,
				   Statement continuation)
      throws ClassException
  {
    arg0.emit(state,true, continuation);
    Instruction.emitIfeqInstruction(state);
    arg1.emit(state,true, continuation);
    Instruction.emitIfeqInstruction(state);
  }	

  static final void emitBooleanOr(EmitState state, Expression arg0,
				  Expression arg1,
				  Statement continuation) 
      throws ClassException
  {
    arg0.emit(state,true, continuation);
    Instruction.emitIfneInstruction(state);
    arg1.emit(state,true, continuation);
    Instruction.emitIfeqInstruction(state);
  }

  static final void emitBooleanNot(EmitState state, Expression arg0,
                                   Statement continuation)
      throws ClassException
  {
    arg0.emit(state,true, continuation);
    Instruction.emitIfneInstruction(state);
  }

  //******************************* String Addition ***************/
		
  static final void emitStringPlus(EmitState state,Expression buffer,
				   Vector arguments,
				   Statement continuation)
      throws ClassException
  {
    // System.out.println("emitStringPlus called on arguments " + arguments + "; buffer is " + buffer);

    if (buffer == null) {
      Expression e 
	= getStringValueExpression((Expression) arguments.elementAt(0));
      buffer = 
	new New(Type.STRING_BUFFER_TYPE,
		new Type[]{Type.STRING_TYPE},
		new Expression[] {e});
    }	
    int size = arguments.size();
    // Create nested calls to append()
    for (int i = 1; i < size; i++) {
      Expression e 
	= (Expression)arguments.elementAt(i);
      Type argType =
	e.getExpressionType().isReferenceType() ?
	Type.OBJECT_TYPE : e.getExpressionType();
      buffer = new MethodCall("append",
			      Type.STRING_BUFFER_TYPE,
			      new Type[]{argType},
			      Type.STRING_BUFFER_TYPE,
			      buffer,
			      new Expression[] {e},
			      MTH_CALL_VIRTUAL);
    }
    // Finally invoke the toString method for the String Buffer, 
    new MethodCall("toString",
		   Type.OBJECT_TYPE,
		   Type.STRING_TYPE,
		   buffer,
		   MTH_CALL_VIRTUAL).emit(state,true,continuation);
  }

  static final Expression getStringValueExpression(Expression exp) 
      throws ClassException
  {
    // System.out.println("getStringValueExpression called on " + exp);
    Type tpe = exp.getExpressionType();
    // Constant strings, no need to change
    if (exp instanceof Value && tpe.equals(stringType))
      return exp;
    Type argType =
      tpe.isReferenceType() ?
      Type.OBJECT_TYPE : tpe;
    Type methodArgType;
    if (argType.isSmallIntegralType() && (!(argType == Type.CHAR_TYPE)))
      methodArgType = Type.INT_TYPE;
    else
      methodArgType = argType;
    MethodCall methodCall 
      = new MethodCall("valueOf",
		       Type.STRING_TYPE,
		       new Type[]{methodArgType},
		       Type.STRING_TYPE,
		       null,
		       new Expression[] {exp},
		       MTH_CALL_STATIC);
    // Need to call ValueOf twice in reference type case; first call might
    // return null, while second call is on a string, so it will always
    // return a non-null (possibly "null") string. Kludgey, but that's the
    // way javac handles it.
    if (tpe.isReferenceType()) {
      methodCall 
	= new MethodCall("valueOf",
			 Type.STRING_TYPE,
			 new Type[]{Type.OBJECT_TYPE},
			 Type.STRING_TYPE,
			 null,
			 new Expression[] {methodCall},
			 MTH_CALL_STATIC);
    }
    return methodCall;
  }
	
  //*******************************  Macro Expansion *************/

  @Override
  public boolean expansionRequired() {
    return requiresExpansion;
  }

  @Override
  public void expandInto(JavaNode j) throws ClassException {

    // System.out.println("Expanding node " + this);
    switch (operator) {
      // For String +, any String + operators that are arguments to this are 
      // collapsed, because the StringBuffer optimization works better this
      // way, and then the nested method calls that represent String + are
      // generated
    case PLUS: {
      Expression exp;
      Enumeration e;
      // Canoninize this
      for (int i = 0; i < children.size(); i++) {
	exp =  (Expression) children.elementAt(i);
	if (exp instanceof OperatorCall &&
	    (((OperatorCall) exp).getPrimaryOperator() == PLUS) &&
	    (exp.getExpressionType() == stringType)) {
	  e = exp.getChildren();
	  if (e.hasMoreElements()) {
	    children.setElementAt((Expression) e.nextElement(),i);
	  }
	  while (e.hasMoreElements()) {
	    i++;
	    children.insertElementAt((Expression) e.nextElement(),i);
	  }		
	}
      }
      requiresExpansion = false;
      j.addJavaNode(this);
      break;
    }
    case ONES_COMPLEMENT: {
      Expression e = (Expression) children.elementAt(0);
      Type tpe = e.getExpressionType();
      Value val = null;
      if (tpe.isLongType()) 
	val = new Value((long) -1);
      else val = new Value(-1);
      j.addJavaNode(new OperatorCall("^",
				     new Expression[] {e,val}));
      break;
    }
    case GREATER_THAN_OR_EQUAL: 
    case LESS_THAN_OR_EQUAL: 
    case GREATER_THAN: 
    case LESS_THAN: 
    case BOOLEAN_AND:
    case BOOLEAN_OR:
    case NOT:
    case EQUALITY:
    case NOT_EQUAL: {
      requiresExpansion = false;

      if (j instanceof If | j instanceof While 
	  | j instanceof For | j instanceof Do | 
	  (j instanceof OperatorCall 
	   && (((OperatorCall) j).isConditionalOperator()))) 
	j.addJavaNode(this);
      else {  
	j.addJavaNode(new OperatorCall("?:",
				       new Expression[] {this, 
							   new Value(true),
							   new Value(false)}));
      }
      break;
    }
    default: {
      requiresExpansion = false;
      j.addJavaNode(this);
      break;
    }
    }
  }

  boolean isOrBranch()  {
    switch (operator) {
    case BOOLEAN_OR:
      return true;
    default:
      return false;
    }
  }

  //*******************************  Constant Expression Evaluation **********

  @Override
  public Expression evaluateConstantExpression() throws ClassException {
    // if it really isn't a constant expression, let user off the hook and
    // simply return this
    if (! isConstantExpression())
      return this;
    // First evaluate arguments to get their constant values 	
    super.evaluateConstantExpression();
    Expression arg0 = (Expression) children.elementAt(0);
    Expression arg1 = null;
    Expression arg2 = null;
    Type argtype0 = arg0.getExpressionType();
    Type argtype1 = null;
    Type argtype2 = null;
    boolean result = false;
    int count = children.size();
    if (count > 1) {
      arg1 = (Expression) children.elementAt(1);
      argtype1 = arg1.getExpressionType();
    }
    if (count > 2) {
      arg2 = (Expression) children.elementAt(2);
      argtype2 = arg2.getExpressionType();
    }
    int int0 = 0;
    boolean bool0 = false;
    float float0 = (float) 0.0;
    long long0 = 0;
    double double0 = 0.0;
    int int1 = 0;
    boolean bool1 = false;;
    float float1 = (float) 0.0;
    long long1 = 0;
    double double1 = 0.0;
    if (argtype0.isBooleanType())
      bool0 = ((Value) arg0).getBooleanValue(); 
    else if (argtype0.isSmallIntegralType())
      int0 = ((Value) arg0).getIntegerValueIfAny();
    else if (argtype0.isFloatType())
      float0 = ((Value) arg0).getFloatValueIfAny();
    else if (argtype0.isDoubleType())
      double0 = ((Value) arg0).getDoubleValueIfAny();
    else if (argtype0.isLongType())
      long0 = ((Value) arg0).getLongValueIfAny();
    if (argtype1 != null) {
      if (argtype1.isBooleanType())
	bool1 = ((Value) arg1).getBooleanValue(); 
      else if (argtype1.isSmallIntegralType())
	int1 = ((Value) arg1).getIntegerValueIfAny();
      else if (argtype1.isFloatType())
	float1 = ((Value) arg1).getFloatValueIfAny();
      else if (argtype1.isDoubleType())
	double1 = ((Value) arg1).getDoubleValueIfAny();
      else if (argtype1.isLongType())
	long1 = ((Value) arg1).getLongValueIfAny();
    }
    // Are now guarunteed to have all constant expressions that are
    // children replaced with Value's.
    switch (operator) {
    case CONDITIONAL: {
      if (bool0)
	return arg1;
      else return arg2;
    }
    //*************** Equality Operators **************					
    case EQUALITY: {
      // No special knowledge of reference equality at compile time
      // can be improved on, especially for arrays
      if (argtype0.isReferenceType())
	return this;						
      if (argtype0.isLongType())
	result = (long0 == long1);
      else if (argtype0.isBooleanType())
	result = (bool0 == bool1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 == int1);
      else if (argtype0.isFloatType())
	result = (float0 == float1);
      else if (argtype0.isDoubleType())
	result = (double0 == double1);
      else throw new ClassException();
      return new Value(result); 
    }
    case NOT_EQUAL: {
      // No special knowledge of reference equality at compile time
      // can be improved on, especially for arrays
      if (argtype0.isReferenceType())
	return this;						
      if (argtype0.isLongType())
	result = (long0 != long1);
      else if (argtype0.isBooleanType())
	result = (bool0 != bool1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 != int1);
      else if (argtype0.isFloatType())
	result = (float0 != float1);
      else if (argtype0.isDoubleType())
	result = (double0 != double1);
      else throw new ClassException();
      return new Value(result); 
    }
    //******** Arithmetic Operators ************
    case PLUS: {
      if (expressionType.equals(stringType)) {
	StringBuffer buf = new StringBuffer("");
	for (int i = 0; i < count; i++)
	  buf.append(((Value) children.elementAt(i)).getPrintedRepresentation());
	return new Value(buf.toString());
      }
      if (argtype0.isLongType())
	return new Value(long0 + long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 + int1);
      else if (argtype0.isFloatType())
	return new Value(float0 + float1);
      else if (argtype0.isDoubleType())
	return new Value(double0 + double1);
      else throw new ClassException();
    } 
    case MINUS: {
      if (argtype0.isLongType())
	return new Value(long0 - long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 - int1);
      else if (argtype0.isFloatType())
	return new Value(float0 - float1);
      else if (argtype0.isDoubleType())
	return new Value(double0 - double1);
      else throw new ClassException();
    } 
    case MULTIPLY: {
						
      if (argtype0.isLongType())
	return new Value(long0 * long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 * int1);
      else if (argtype0.isFloatType())
	return new Value(float0 * float1);
      else if (argtype0.isDoubleType())
	return new Value(double0 * double1);
      else throw new ClassException();
    } 
    case DIVIDE: {
      if (((Value) arg1).isZero())
	throw new ClassException("Arithmetic Exception");
      if (argtype0.isLongType()) 
	return new Value(long0 / long1); 
      else if (argtype0.isSmallIntegralType()) 
	return new Value(int0 / int1); 
      else if (argtype0.isFloatType()) 
	return new Value(float0 / float1);
      else if (argtype0.isDoubleType()) 
	return new Value(double0 / double1); 
      else throw new ClassException();
    } 
    case REMAINDER: {
      if (((Value) arg1).isZero())
	throw new ClassException("Arithmetic Exception");
      if (argtype0.isLongType()) 
	return new Value(long0 % long1); 
      else if (argtype0.isSmallIntegralType()) 
	return new Value(int0 % int1); 
      else if (argtype0.isFloatType()) 
	return new Value(float0 % float1);
      else if (argtype0.isDoubleType()) 
	return new Value(double0 % double1); 
      else throw new ClassException();
    }
    case GREATER_THAN_OR_EQUAL: {
      if (argtype0.isLongType())
	result = (long0 >= long1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 >= int1);
      else if (argtype0.isFloatType())
	result = (float0 >= float1);
      else if (argtype0.isDoubleType())
	result = (double0 >= double1);
      else throw new ClassException();
      return new Value(result); 
    } 
    case LESS_THAN_OR_EQUAL: {
      if (argtype0.isLongType())
	result = (long0 <= long1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 <= int1);
      else if (argtype0.isFloatType())
	result = (float0 <= float1);
      else if (argtype0.isDoubleType())
	result = (double0 <= double1);
      else throw new ClassException();
      return new Value(result); 
    }	
    case GREATER_THAN: {
      if (argtype0.isLongType())
	result = (long0 > long1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 > int1);
      else if (argtype0.isFloatType())
	result = (float0 > float1);
      else if (argtype0.isDoubleType())
	result = (double0 > double1);
      else throw new ClassException();
      return new Value(result); 
    }
    case LESS_THAN: {
      if (argtype0.isLongType())
	result = (long0 < long1);
      else if (argtype0.isSmallIntegralType())
	result = (int0 < int1);
      else if (argtype0.isFloatType())
	result = (float0 < float1);
      else if (argtype0.isDoubleType())
	result = (double0 < double1);
      else throw new ClassException();
      return new Value(result); 
    }
					
    //********************  Bitwize Operators *********************
    case AND: {
      if (argtype0.isBooleanType())
	return new Value(bool0 & bool1);
      if (argtype0.isLongType())
	return new Value(long0 & long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 & int1);
      else throw new ClassException();
    } 
    case OR: {
      if (argtype0.isBooleanType())
	return new Value(bool0 | bool1);
      if (argtype0.isLongType())
	return new Value(long0 | long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 | int1);
      else throw new ClassException();
    }
    case XOR: {
      if (argtype0.isBooleanType())
	return new Value(bool0 ^ bool1);
      if (argtype0.isLongType())
	return new Value(long0 ^ long1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 ^ int1);	
      else throw new ClassException();
    } 
    case LEFT_SHIFT: {
      if (argtype0.isLongType())
	return new Value(long0 << int1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 << int1);	
      else throw new ClassException();					
    } 
    case RIGHT_SHIFT: {
      if (argtype0.isLongType())
	return new Value(long0 >> int1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 << int1);	
      else throw new ClassException();										
    }
    case UNSIGNED_RIGHT_SHIFT: {
      if (argtype0.isLongType())
	return new Value(long0 >>> int1);
      else if (argtype0.isSmallIntegralType())
	return new Value(int0 >>> int1);						
      else throw new ClassException();										
    }
    //************ Boolean Operators *********					
    case BOOLEAN_AND:
      return new Value(bool0 & bool1);
    case BOOLEAN_OR: 
      return new Value(bool0 | bool1);
    case NOT: 
      return new Value(! bool0);
      //****************  Instanceof Operator **********
    case INSTANCEOF: // For now return this
    }
    return this;
  }

  //******************************  Miscellaneous ****************************

  @Override
  public String toString() {
    if (operator == -1)
      return "<OperatorCall, <incomplete>>";
    if (secondaryOperator == -1)
      return "<OperatorCall, operator = " + operators[operator] + 
	", type = " + expressionType +">";
    return "<OperatorCall, operator = " + operators[secondaryOperator] + 
      operators[operator] 
      + ", type = " + expressionType + ">"; 
  }
}
