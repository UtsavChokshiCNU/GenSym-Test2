package com.gensym.newclasstools;

import java.util.Vector;

public class Value extends Atom {
  Constant constant;
  private boolean nullP = false;

  public Value(int value) {
    expressionType = Type.INT_TYPE;
    constant = new IntegerConstant(value);
  }

  public Value(short value) {
    expressionType = Type.SHORT_TYPE;
    constant = new IntegerConstant(value);
  }

  public Value(char value) {
    expressionType = Type.CHAR_TYPE;
    constant = new IntegerConstant(value);
  }

  public Value(byte value) {
    expressionType = Type.BYTE_TYPE;
    constant = new IntegerConstant(value);
  }

  public Value(float value) {
    expressionType = Type.FLOAT_TYPE;
    constant = new FloatConstant(value);
  }

  public Value(double value) {
    expressionType =  Type.DOUBLE_TYPE;
    constant = new DoubleConstant(value);
  }

  public Value(long value) {
    expressionType =  Type.LONG_TYPE;
    constant = new LongConstant(value);
  }

  public Value(boolean value) {
    expressionType = Type.BOOLEAN_TYPE;
    constant = new IntegerConstant(value ? 1 : 0);
  }

  public Value(String st) {
    if (st == null) {
      nullP = true;
      expressionType = Type.NULL_TYPE;
    } else {
      expressionType = Type.STRING_TYPE;
      constant = new StringConstant(st);
    }
  }

  public Value(Object o) throws ClassException {
    if (o != null)
      throw new ClassException("Constant object reference can only be string or null");     
    expressionType = Type.NULL_TYPE;
    nullP = true;
  }
	
  boolean canFitInSingleByte() {
    if (expressionType == Type.STRING_TYPE)
      return true;
    if (expressionType.isSmallIntegralType())
      return ((IntegerConstant)constant).getValue() < 256;
    return false;
  }
	

  boolean canFitInSingleSignedByte() {
    if (expressionType == Type.STRING_TYPE)
      return true;
    if (expressionType.isSmallIntegralType()) {
      int value = ((IntegerConstant)constant).getValue();
      return ((value < 128) && (value > -129));
    }
    return false;
  }

  boolean isZero() {
    Type tpe = expressionType;
    if (! tpe.isNumericType()) 
      return false;
    if (tpe.isLongType()) 
      return ((LongConstant)constant).getValue() == 0;
    else if (tpe.isSmallIntegralType()) 
      return ((IntegerConstant)constant).getValue() == 0;
    else if (tpe.isFloatType()) 
      return ((FloatConstant)constant).getValue() == 0.0;
    else if (tpe.isDoubleType()) 
      return ((DoubleConstant)constant).getValue() == 0.0;
    return false;
  }

  boolean isNull() {
    return nullP;
  }

  @Override
  public boolean isConstantExpression() {
    return true;
  }

  public int getIntegerValueIfAny() throws ClassException {
    if (expressionType.isSmallIntegralType() || expressionType == Type.BOOLEAN_TYPE)
      return ((IntegerConstant)constant).getValue();
    else throw new ClassException("Integer Value not defined for this type");
  }

  public long getLongValueIfAny() throws ClassException {
    if (expressionType.isLongType())
      return ((LongConstant)constant).getValue();
    else throw new ClassException("Long Value not defined for this type");
  }

  public float getFloatValueIfAny() throws ClassException {
    if (expressionType.isFloatType())
      return ((FloatConstant)constant).getValue();
    else throw new ClassException("Float Value not defined for this type");
  }

  public double getDoubleValueIfAny() throws ClassException {
    if (expressionType.isDoubleType())
      return ((DoubleConstant)constant).getValue();
    else throw new ClassException("Double Value not defined for this type");
  }

  public boolean getBooleanValue() throws ClassException {
    if (expressionType.isBooleanType())
      return ((IntegerConstant)constant).getValue() == 0 ? false : true;
    else throw new ClassException("Attempt to get Boolean Value of non boolean value");
  }


  public String getStringValueIfAny() throws ClassException {
    return ((StringConstant)constant).getString();
  }

  // Always generate an opc_ldc; it's the job of the CodeAttribute to 
  // transform this into an opc_ldc_w when necessary.
  @Override
  void emit(EmitState state, boolean leaveOnStack, 
            Statement continuation) 
      throws ClassException {
    Vector instructions =  state.instructions;
    // super.emit(state,leaveOnStack,continuation);
    Instruction ins;
    switch (expressionType.getTypeCode()) {
    case P_FLOAT: { 	 
	if (getFloatValueIfAny() == 0.0)	
	  ins = Instruction.makeInstruction(opc_fconst_0);
	else if (getFloatValueIfAny() == 1.0)
	  ins = Instruction.makeInstruction(opc_fconst_1);
	else if (getFloatValueIfAny() == 2.0)
	  ins = Instruction.makeInstruction(opc_fconst_2);
	else ins = Instruction.makeInstruction(opc_ldc, constant);
	state.pushStack();
	break;
      }
      case P_DOUBLE: {	 
	if (getDoubleValueIfAny() == 0.0)	
	  ins = Instruction.makeInstruction(opc_dconst_0);
	else if (getDoubleValueIfAny() == 1.0)
	  ins = Instruction.makeInstruction(opc_dconst_1);
	else 
	  ins = Instruction.makeInstruction(opc_ldc2_w,constant);
	state.pushStack(2);
	break;
      }		
      case P_LONG:	 {
	if (getLongValueIfAny() == 0)	
	  ins = Instruction.makeInstruction(opc_lconst_0);
	else if (getLongValueIfAny() == 1)
	  ins = Instruction.makeInstruction(opc_lconst_1);
	else ins = Instruction.makeInstruction(opc_ldc2_w, constant);
	state.pushStack(2);
	break;
      }
    case P_BOOLEAN:
    case P_CHAR:
    case P_BYTE:
    case P_SHORT:
    case P_INT:
      {
	switch(getIntegerValueIfAny()) {
	case -1:   ins = Instruction.makeInstruction(opc_iconst_m1); break;
	case 0:   ins = Instruction.makeInstruction(opc_iconst_0); break;
	case 1:   ins = Instruction.makeInstruction(opc_iconst_1); break;
	case 2:   ins = Instruction.makeInstruction(opc_iconst_2); break;
	case 3:   ins = Instruction.makeInstruction(opc_iconst_3); break;
	case 4:   ins = Instruction.makeInstruction(opc_iconst_4); break;
	case 5:   ins = Instruction.makeInstruction(opc_iconst_5); break;
	default:  
	  if ((-129 < getIntegerValueIfAny()) & (getIntegerValueIfAny() < 128))
	    ins = Instruction.makeInstruction(opc_bipush,getIntegerValueIfAny());
	  else
	    if ((-32769 < getIntegerValueIfAny()) & (getIntegerValueIfAny() < 32768))
	      ins = Instruction.makeInstruction(opc_sipush,getIntegerValueIfAny());
	    else  
	      ins = Instruction.makeInstruction(opc_ldc, constant);
	}				
	state.pushStack(); 
	break;
      }
    case P_NULL:
      {
        ins = Instruction.makeInstruction(opc_aconst_null);
        state.pushStack();
	break;
      }
    case P_STRING: 
      {
	ins = Instruction.makeInstruction(opc_ldc, constant);
        state.pushStack();
	break;
      }
    default:
      throw new ClassException("bad type code " + expressionType.getTypeCode()
			       + "in Value statement");
    }
    instructions.addElement(ins);
  }


  public String getPrintedRepresentation()
  {
    // System.out.println("getPrintedRepresentation called on " + this);
    // System.out.println("Expression type is " + expressionType);
    // System.out.println("Constant type is " + constant.getClass());
    if (expressionType.isNumericType())
      {
	if (expressionType == Type.FLOAT_TYPE)
	  return ((FloatConstant)constant).getValue() + "";
	if (expressionType == Type.DOUBLE_TYPE)
	  return ((DoubleConstant)constant).getValue() + "";
	if (expressionType == Type.LONG_TYPE)
	  return ((LongConstant)constant).getValue() + "";
	if (expressionType == Type.CHAR_TYPE)
	  return ((char)((IntegerConstant)constant).getValue()) + "";
	// Small integer type.
	return ((IntegerConstant)constant).getValue() + "";
      } else {
	if (expressionType == Type.BOOLEAN_TYPE)
	  return ((IntegerConstant)constant).getValue() == 0 ? "false" : "true";
	// Must be string or null.
	String string = ((StringConstant)constant).getString();
	return (string == null) ? "null" : string;
      }
  }

  @Override
  public String toString() {
    try {
      switch (expressionType.getTypeCode()) {
      case P_FLOAT: { return "<Value, type = " + expressionType + 
			", value = " + getFloatValueIfAny() + ">"; }
      case P_DOUBLE: { return "<Value, type = " + expressionType + 
			 ", value = " + getDoubleValueIfAny() + ">";}
      case P_LONG: { return "<Value, type = " + expressionType + 
		       ", value = " + getLongValueIfAny()  + ">"; }
      case P_BOOLEAN: { return "<Value, type = " + expressionType + 
		       ", value = " + getBooleanValue()  + ">"; }

    case P_NULL:
      return "<Value, null constant>";
    case P_STRING:
      return "<Value, type = " + expressionType + ", value = " + 
	getStringValueIfAny()  + ">"; 
    default: { return "<Value, type = " + expressionType + 
		 ", value = " + getIntegerValueIfAny()  + ">"; }
      }
    } catch (ClassException exp) {
	return "Bad Value object of type " + expressionType;
    }
  }

}

