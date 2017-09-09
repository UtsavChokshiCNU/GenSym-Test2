package com.gensym.classtools;
import java.util.Vector;

public class Return extends Statement {
  private final boolean trace = false; 
  
  public Return(Expression e) throws ClassException {
    addJavaNode(e);
  }
  
  /**
   * Constructor for a VOID return
   */
  public Return() {
  }


  @Override
  void emit(EmitState state, boolean leaveOnStack, 
            Statement continuation) 
       throws ClassException
  {
    super.emit(state,leaveOnStack,continuation);
    Vector instructions = state.instructions;  
    int ref = 0;
    Instruction ins;		 
    if (!children.isEmpty()) {
      Expression nextElement = (Expression) children.elementAt(ref);
      if (trace)
        System.out.println("Emmitting sub expression" + nextElement); 
      nextElement.emit(state,true,continuation);
      
      Type tpe = nextElement.getExpressionType();	
      
      if(tpe.isIntegerType() || tpe.isShortType() || tpe.isByteType() ||
	 tpe.isBooleanType()) {
        ins = Instruction.makeInstruction(opc_ireturn);
      }
      else if(tpe.isDoubleType())
        ins = Instruction.makeInstruction(opc_dreturn);
      else
        if(tpe.isFloatType())
	  ins = Instruction.makeInstruction(opc_freturn);
	else
	  if(tpe.isLongType())
	    ins = Instruction.makeInstruction(opc_lreturn);
	  else 
	    if(tpe.isClassType() || tpe.isArrayType())
	      ins = Instruction.makeInstruction(opc_areturn);
      // Consider using this case versus the zero argument version of
      // return.
	    else ins = Instruction.makeInstruction(opc_return);
    }
    else {
      if (trace)
        System.out.println("Emitting zero argument return");
      ins = Instruction.makeInstruction(opc_return);		
    }
    if (trace)
      System.out.println("Adding instruction" + ins);
    instructions.addElement(ins);
  }
}
