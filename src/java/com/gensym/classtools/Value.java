package com.gensym.classtools;

import java.util.Vector;

public class Value extends Atom {
  ValueConstant constant;
  private String stringValueIfAny;
  private int intValueIfAny;
  private double doubleValueIfAny;
  private float floatValueIfAny;
  private long longValueIfAny;
  private int cachedType = -1;
  private boolean nullP = false;

  public Value(int value) {
    intValueIfAny = value;
    cachedType = T_INT;
    try {
      expressionType = new Type(T_INT);
    }  catch(Exception e) {}
  }

  public Value(short value) {
    intValueIfAny = value;
    cachedType = T_SHORT;
    try {
      expressionType = new Type(T_SHORT);
    }  catch(Exception e) {}
  }


  public Value(char value) {
    intValueIfAny = value;
    cachedType = T_CHAR;
    try {
      expressionType = new Type(T_CHAR);
    }  catch(Exception e) {}
  }

  public Value(byte value) {
    intValueIfAny = value;
    cachedType = T_BYTE;
    try {
      expressionType = new Type(T_BYTE);
    }  catch(Exception e) {}
  }

  public Value(float value) {
    floatValueIfAny = value;
    cachedType = T_FLOAT;
    try{
      expressionType = new Type(T_FLOAT);
    } catch(Exception e) {}

  }

  public Value(double value) {
    doubleValueIfAny = value;
    cachedType = T_DOUBLE;
    try {
      expressionType = new Type(T_DOUBLE);
    } catch(Exception e) {}
  }

  public Value(long value) {
    longValueIfAny = value;
    cachedType = T_LONG;
    try {
      expressionType = new Type(T_LONG);
    } catch(Exception e) {}
  }

  public Value(boolean value) {
    if (value) 
      intValueIfAny = 1;
    else intValueIfAny = 0;
    cachedType = T_BOOLEAN;
    try {
      expressionType = new Type(T_BOOLEAN);
    } catch(Exception e) {}
  }

  public Value(String st) {
    try {
      if (st == null) {
        nullP = true;
        expressionType = Type.parseType(OBJECT_DESC);
      }
      else {
        stringValueIfAny = st;
      
        expressionType = Type.parseType(STRING_DESC);
        }
     } catch(Exception e) {}
  }

  public Value(Object o) throws ClassException {
    if (o != null)
      throw new ClassException("Constant object reference can only be string or null");     
    try {
      expressionType = Type.parseType(OBJECT_DESC);
     } catch(Exception e) {}
     nullP = true;
  }
	
  boolean canFitInSingleByte() {
    if (stringValueIfAny != null)
      return true;
    if (expressionType.isSmallIntegralType())
      return (intValueIfAny < 256);
    return false;
  }
	

  boolean canFitInSingleSignedByte() {
    if (stringValueIfAny != null)
      return true;
    if (expressionType.isSmallIntegralType())
      return ((intValueIfAny < 128) && (intValueIfAny > -129));
    return false;
  }

  boolean isZero() {
    Type tpe = expressionType;
    if (! tpe.isNumericType()) 
      return false;
    if (tpe.isLongType()) 
      return (longValueIfAny == 0);
    else if (tpe.isSmallIntegralType()) 
      return (intValueIfAny == 0);
    else if (tpe.isFloatType()) 
      return (Float.compare(floatValueIfAny, 0.0f) == 0 );
    else if (tpe.isDoubleType()) 
      return (Double.compare(doubleValueIfAny, 0.0) == 0 );
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
    if (expressionType.isSmallIntegralType())
      return intValueIfAny;
    else throw new ClassException("Integer Value not defined for this type");
  }

  public long getLongValueIfAny() throws ClassException {
    if (expressionType.isLongType())
      return longValueIfAny;
    else throw new ClassException("Long Value not defined for this type");
  }

  public float getFloatValueIfAny() throws ClassException {
    if (expressionType.isFloatType())
      return floatValueIfAny;
    else throw new ClassException("Float Value not defined for this type");
  }

  public double getDoubleValueIfAny() throws ClassException {
    if (expressionType.isDoubleType())
      return doubleValueIfAny;
    else throw new ClassException("Double Value not defined for this type");
  }

  public boolean getBooleanValue() throws ClassException {
    if (expressionType.isBooleanType())
      return (intValueIfAny == 0 ? false : true);
    else throw new ClassException("Attempt to get Boolean Value of non boolean value");
  }


  public String getStringValueIfAny() throws ClassException {
    return stringValueIfAny;
  }

  @Override
  void generateConstants(ConstantPool cp) throws ClassException {
    if (cachedType > 0) 
      switch (cachedType) {
      case T_FLOAT: 
	if (!(Float.compare(floatValueIfAny, 0.0f) == 0 || Float.compare(floatValueIfAny, 1.0f) == 0 ||
			Float.compare(floatValueIfAny, 2.0f) == 0 )){
	  constant = new ValueConstant(cp,floatValueIfAny); 
	  constant = (ValueConstant) cp.getPool(cp.member(constant));
	}
	break;
      case T_DOUBLE: 
	if (!(Double.compare(doubleValueIfAny, 0.0) == 0 || Double.compare(doubleValueIfAny, 1.0) == 0 )) {
	  constant = new ValueConstant(cp,doubleValueIfAny);
	  constant = (ValueConstant) cp.getPool(cp.member(constant));
	}
	break;
      case T_LONG:	 
	if ((longValueIfAny > 1) || (longValueIfAny < 0)) {
	  constant = new ValueConstant(cp,longValueIfAny);
	  constant = (ValueConstant) cp.getPool(cp.member(constant));
	}	
	break;
      default:
	if ((intValueIfAny > 32767) || (intValueIfAny < -32768)) {
	  constant = new ValueConstant(cp,intValueIfAny);
	  constant = (ValueConstant) cp.getPool(cp.member(constant));
	}
      }
    else {
      if (! nullP) {
        constant =  new ValueConstant(cp,stringValueIfAny);
        constant = (ValueConstant) cp.getPool(cp.member(constant));
      }
    }
  }


  @Override
  void emit(EmitState state, boolean leaveOnStack, 
            Statement continuation) 
      throws ClassException {
    Vector instructions =  state.instructions;
    super.emit(state,leaveOnStack,continuation);
    Instruction ins;
    if (cachedType > 0)
      switch (cachedType) {
      case T_FLOAT: { 	 
	if (Float.compare(floatValueIfAny, 0.0f) == 0 )	
	  ins = Instruction.makeInstruction(opc_fconst_0);
	else if (Float.compare(floatValueIfAny, 1.0f) == 0 )
	  ins = Instruction.makeInstruction(opc_fconst_1);
	else if (Float.compare(floatValueIfAny, 2.0f) == 0 )
	  ins = Instruction.makeInstruction(opc_fconst_2);
	else ins = chooseConstantPoolLoadInstruction(constant.getWhere());
	state.pushStack();
	break;
      }
      case T_DOUBLE: {	 
	if (Double.compare(doubleValueIfAny,0.0) == 0 )	
	  ins = Instruction.makeInstruction(opc_dconst_0);
	else if (Double.compare(doubleValueIfAny, 1.0) == 0 )
	  ins = Instruction.makeInstruction(opc_dconst_1);
	else 
	  ins = Instruction.makeInstruction(opc_ldc2_w,constant.getWhere());
	state.pushStack(2);
	break;
      }		
      case T_LONG:	 {
	if (longValueIfAny == 0)	
	  ins = Instruction.makeInstruction(opc_lconst_0);
	else if (longValueIfAny == 1)
	  ins = Instruction.makeInstruction(opc_lconst_1);
	else ins = Instruction.makeInstruction(opc_ldc2_w,constant.getWhere());
	state.pushStack(2);
	break;
      }
      default: {
	switch(intValueIfAny) {
	case -1:   
		ins = Instruction.makeInstruction(opc_iconst_m1); 
		break;
	case 0:   
		ins = Instruction.makeInstruction(opc_iconst_0); 
		break;
	case 1:   
		ins = Instruction.makeInstruction(opc_iconst_1);
		break;
	case 2:  
		ins = Instruction.makeInstruction(opc_iconst_2); 
		break;
	case 3:  
		ins = Instruction.makeInstruction(opc_iconst_3); 
		break;
	case 4:  
		ins = Instruction.makeInstruction(opc_iconst_4); 
		break;
	case 5:  
		ins = Instruction.makeInstruction(opc_iconst_5); 
		break;
	default:  
	  if ((-129 < intValueIfAny) && (intValueIfAny < 128))
	    ins = Instruction.makeInstruction(opc_bipush,intValueIfAny);
	  else
	    if ((-32769 < intValueIfAny) && (intValueIfAny < 32768))
	      ins = Instruction.makeInstruction(opc_sipush,intValueIfAny);
	    else  
	      ins = chooseConstantPoolLoadInstruction(constant.getWhere());
	}				
	state.pushStack(); 
      }
      }
    else
      {
      if (nullP) {
        ins = Instruction.makeInstruction(opc_aconst_null);
        state.pushStack();
      }
      else {
        ins = chooseConstantPoolLoadInstruction(constant.getWhere());
        state.pushStack();
        }
      }
    instructions.addElement(ins);
  }

  private static final Instruction chooseConstantPoolLoadInstruction(int where)
 {
    // Later stages in the emit cannot handle the need for
    // opc_ldc's migrating to opc_ldc_w's.  This is an optimization
    // that it is a shame to miss
    //if (where > 254)
      return Instruction.makeInstruction(opc_ldc_w,where);
    //else return Instruction.makeInstruction(opc_ldc,where);
  }

  public String getPrintedRepresentation()
  {
    if (cachedType > 0)
      {
	switch (cachedType) {
	case T_FLOAT:  return floatValueIfAny + "";
	case T_DOUBLE: return doubleValueIfAny + "";
	case T_LONG:   return longValueIfAny  + "";
	case T_BOOLEAN: return (intValueIfAny == 0 ? "false" : "true");
	default: return intValueIfAny  + "";
	}
      }
    else
      return (stringValueIfAny == null) ? "null" : stringValueIfAny;
  }

  @Override
  public String toString() {
    if (cachedType > 0) {
      switch (cachedType) {
      case T_FLOAT: { return "<Value, type = " + expressionType + 
			", value = " + floatValueIfAny + ">"; }
      case T_DOUBLE: { return "<Value, type = " + expressionType + 
			 ", value = " + doubleValueIfAny + ">";}
      case T_LONG: { return "<Value, type = " + expressionType + 
		       ", value = " + longValueIfAny  + ">"; }
      default: { return "<Value, type = " + expressionType + 
		   ", value = " + intValueIfAny  + ">"; }
      }}
    else {
      return "<Value, type = " + expressionType + ", value = " + 
	stringValueIfAny  + ">"; 
    }
  }
}

