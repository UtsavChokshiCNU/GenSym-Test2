package com.gensym.newclasstools;
import java.util.Vector;

public class Variable extends Expression {
  int argumentNumber = -1;
  private String variableName;
	
  /** Create a variable for an argument number.  The number
   * will only mean something once this Variable is part of a 
   * MethodInfo object. The number refers to the position of the 
   * Variable in the local variable vector.  By convention the
   * 0th element = this
   * If there are N arguments to the method and N > 0 then 1 - N
   * are by convention the arguments to the method.
   * The compilation of the method is free to do what it wants with
   * any other entries in the local variable vector.
   */
  public Variable(int argumentNumber, Type type) throws ClassException
  {
    // Allow 0 - need to review whether we want "this" to be specified in this way
    expressionType = type;
    this.argumentNumber = argumentNumber;
  }

  public Variable(String variableName, Type type) throws ClassException {
    expressionType = type;
    this.variableName = variableName;
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
	    Statement continuation) throws ClassException
  {
    super.emit(state,leaveOnStack, continuation);
    Vector instructions = state.instructions; 
    Instruction ins;
    Type tpe = expressionType;
    if (argumentNumber == 0) 
      {
	ins = Instruction.makeInstruction(opc_aload_0);
	state.pushStack();
      }
    else {
      if(tpe.isReferenceType()) {
	switch(argumentNumber) {
	case 1:   ins = Instruction.makeInstruction(opc_aload_1); break;
	case 2:   ins = Instruction.makeInstruction(opc_aload_2); break;
	case 3:   ins = Instruction.makeInstruction(opc_aload_3); break;
	default:  ins = Instruction.makeInstruction(opc_aload,argumentNumber); break;
	}
	state.pushStack();
      }
      else 
	if(tpe.isIntegerType() || tpe.isShortType() || tpe.isByteType() ||
	   tpe.isBooleanType()) {
	  switch(argumentNumber) {
	  case 1:   ins = Instruction.makeInstruction(opc_iload_1); break;
	  case 2:   ins = Instruction.makeInstruction(opc_iload_2); break;
	  case 3:   ins = Instruction.makeInstruction(opc_iload_3); break;
	  default:  ins = Instruction.makeInstruction(opc_iload,argumentNumber); break;
	  }
	  state.pushStack();
	}						 
	else  {	
	  if(tpe.isDoubleType())  {
	    switch(argumentNumber) {
	    case 1:   ins = Instruction.makeInstruction(opc_dload_1); break;
	    case 2:   ins = Instruction.makeInstruction(opc_dload_2); break;
	    case 3:   ins = Instruction.makeInstruction(opc_dload_3); break;
	    default:  ins = Instruction.makeInstruction(opc_dload,argumentNumber); break;
	    }
	    state.pushStack(2);
	  }
	  else 
	    if(tpe.isLongType())  {
	      switch(argumentNumber) {
	      case 1:   ins = Instruction.makeInstruction(opc_lload_1); break;
	      case 2:   ins = Instruction.makeInstruction(opc_lload_2); break;
	      case 3:   ins = Instruction.makeInstruction(opc_lload_3); break;
	      default:  ins = Instruction.makeInstruction(opc_lload,argumentNumber); break;
	      }
	      state.pushStack(2);
	    }
            else 
	      if(tpe.isFloatType()) {
		switch(argumentNumber) {
		case 1:   ins = Instruction.makeInstruction(opc_fload_1); break;
		case 2:   ins = Instruction.makeInstruction(opc_fload_2); break;
		case 3:   ins = Instruction.makeInstruction(opc_fload_3); break;
		default:  ins = Instruction.makeInstruction(opc_fload,argumentNumber);
		  break;
		} 
		state.pushStack();
	      }
	      else
		throw new ClassException("Invalid variable type discovered during emitting " + tpe);			
	}
    }		
    instructions.addElement(ins);	
  }


  @Override
  public boolean isConstantExpression() {
    return false;
  }

  @Override
  void generateVariableIds(EmitState state) throws ClassException {
    VariableScope parentScope = state.scope;
    if (variableName != null) 
      argumentNumber = parentScope.getVariableId(variableName,expressionType);
    if (argumentNumber == -1) 
      throw new ClassException("Cannot find variable " + variableName + " of type " + expressionType); 
  }


  @Override
  public String toString() {
    return "<Variable, name = " + variableName + ", type = " + expressionType + ">";
  }

  public String getVariableName() {
    return variableName;
  }
}

