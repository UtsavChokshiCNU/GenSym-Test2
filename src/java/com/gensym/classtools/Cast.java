package com.gensym.classtools;

import java.util.Vector;

public class Cast extends Expression implements MacroNode
{
  private boolean trace = false;
  private boolean requiresExpansion = false;
  private boolean strict = true;
  
  public Cast(String type, Expression exp) throws ClassException {
    expressionType = Type.parseType(type);
    init(exp);
  }
  
  public Cast(Type tpe, Expression exp) throws ClassException {
    expressionType = tpe;
    init(exp);
  }

  Cast(Type tpe, Expression exp, boolean strict) throws ClassException {
    this.strict = strict;
    expressionType = tpe;
    init(exp);
  }

  
  @Override
  public boolean expansionRequired() {
    return requiresExpansion;
  }
  
  @Override
  
  public void expandInto(JavaNode j) throws ClassException {
    j.addJavaNode((JavaNode) children.elementAt(0));
  }
  
  private void init(Expression exp) throws ClassException {
    Type tpe = exp.getExpressionType();
    if (expressionType.equals(tpe)) {
      requiresExpansion = true;
      if (trace)
	System.out.println("No cast required, from " + tpe + ", to " + expressionType);
      addJavaNode(exp);
    }
    else if (expressionType.isNumericType()) {
      if (! tpe.isNumericType()) {
	throw new ClassException("Cannot cast a non-numeric type to a numeric type, type = " +
				 expressionType + ", non-numeric type = " + tpe);
	
      }
      if (tpe.isSmallIntegralType() && expressionType.isSmallIntegralType() &&
	  (! expressionType.requiresNarrowingPrimitiveConversion(tpe))) {
	if (trace)
	  System.out.println("No cast required, from " + tpe + ", to " + expressionType);
	requiresExpansion = true;
      }
      addJavaNode(exp);
    }
    else {
      if (strict || 
          (!expressionType.equals(exp.getExpressionType()))) { 
        String typeString = expressionType.getReturnTypeString();
	addJavaNode(new ClassRef(Type.className(typeString)));
	addJavaNode(exp);
        }
      else {
        if (trace)
          System.out.println("No cast required, from " + tpe + ", to " + expressionType);
        requiresExpansion = true;
        addJavaNode(exp);
      }
    }
  }
  
  @Override
  void emit(EmitState state, boolean leaveOnStack, 
            Statement continuation) 
      throws ClassException {
    generateLineNumberInfo(state);
    Vector instructs = state.instructions;		
    Expression exp;
    if (! requiresExpansion) {
      if (expressionType.isNumericType()) {
	exp = (Expression) children.elementAt(0);
	exp.emit(state,leaveOnStack,continuation);				
	Type tpe = exp.getExpressionType();
	Instruction.emitCastInstruction(state,expressionType,tpe);
      }
      else {
	ClassRef classRef =  (ClassRef) children.elementAt(0);
	classRef.generateConstants(state.pool);
	exp = (Expression) children.elementAt(1);
	exp.emit(state, leaveOnStack, continuation);
	Instruction ins = Instruction.makeInstruction(opc_checkcast,classRef.getWhere());	
	instructs.addElement(ins);
      }
    }
    else {
      exp = (Expression) children.elementAt(0);
      if (trace)
	System.out.println("Cast emitted no instruction");
      exp.emit(state,leaveOnStack, continuation);
    }
  }
  
  
  //**************************** Constant Expression Evaluation ***********/
  
  @Override
  public Expression evaluateConstantExpression() throws ClassException {
    if (((Expression)children.elementAt(0)).isConstantExpression()) {
      super.evaluateConstantExpression();
      Value val = (Value) children.elementAt(0);
      Type tpe = val.getExpressionType();
      if (tpe.isSmallIntegralType()) {
	int intVal = val.getIntegerValueIfAny();
	if (expressionType.isLongType()) 
	  return new Value((long) intVal);	
	else if (expressionType.isFloatType())
	  return new Value((float) intVal);	
	else if (expressionType.isDoubleType()) 
	  return new Value((double) intVal);
	else if (tpe.isIntegerType()) {
	  if(expressionType.isCharType())
	    return new Value((char) intVal);	
	  else if (expressionType.isByteType())
	    return new Value((byte) intVal);	
	  else if (expressionType.isShortType())
	    return new Value((short) intVal);	
	}
      }
      else if (tpe.isFloatType()) {  // Casts from floats
	float floatVal = val.getFloatValueIfAny();
	if (expressionType.isIntegerType())
	  return new Value((int) floatVal);	
	else if (expressionType.isLongType()) 
	  return new Value((long) floatVal);	
	else if (expressionType.isDoubleType()) 
	  return new Value((double) floatVal);	
      }
      else if (tpe.isDoubleType()) { // Casts from doubles
	double doubleVal = val.getDoubleValueIfAny();		
	if (expressionType.isIntegerType()) 
	  return new Value((int) doubleVal);	
	else if (expressionType.isLongType())
	  return new Value((long) doubleVal);	
	else if (expressionType.isFloatType()) 
	  return new Value((float) doubleVal); 	
      }
      else if (tpe.isLongType()) { // Casts from longs
	double longVal = val.getLongValueIfAny();		
	if (expressionType.isIntegerType())
	  return new Value((int) longVal); 	
	else if (expressionType.isDoubleType())
	  return new Value((double) longVal);	
	else if (expressionType.isFloatType()) 
	  return new Value((float) longVal);	
      }
      return this;
    }
    else return this;
  }
  
  @Override
  public String toString() {
    return "<Cast, type = " + expressionType+">";
  }

  void setTrace(boolean traceOn) {
      trace = traceOn;
  }
}
