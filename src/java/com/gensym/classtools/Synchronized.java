package com.gensym.classtools;

import java.util.Vector;

public class Synchronized extends Statement {

  private VariableScope variableScope = new VariableScope();
  
  public Synchronized (Expression exp, Block block) 
    throws ClassException
  {
    VariableDeclaration vdecl = 
      VariableDeclaration.generateUniqueVariableDeclaration(
      OBJECT_DESC);

    variableScope.add(vdecl);

    Variable var = vdecl.getVariable();

    OperatorCall opCall = 
      new OperatorCall("=", new Expression[] { var, exp});
    EnterMonitor enter = new EnterMonitor(var);
    Block startBlock = new Block();
    startBlock.add(opCall);
    startBlock.add(enter);
    
    ExitMonitor normalExit = new ExitMonitor(var);
    
    Block catchBlock = new Block();
    ExitMonitor exit = new ExitMonitor(var);
    catchBlock.add(exit);
        
    VariableDeclaration vdecl2 = 
      VariableDeclaration.generateUniqueVariableDeclaration(
          "Ljava/lang/Throwable;");
    
    catchBlock.add(new Throw(new Noop(vdecl2.getVariableType())));

    addJavaNode(startBlock);
    
    addJavaNode(block);
    
    addJavaNode(normalExit);

    addJavaNode(catchBlock);
  }

  @Override
  void generateVariableIds(EmitState state) throws ClassException {
      variableScope.generateVariableIds(state);
  } 

  @Override
  void emit(EmitState state, boolean leaveOnStack, 
        Statement continuation) 
        throws ClassException 
  {
    Vector instructions = state.instructions;
    VariableScope scope = state.scope;
    super.emit(state,false,continuation);
    state.scope = variableScope;
    Block startBlock = (Block) children.elementAt(0);
    Block theMeat = (Block) children.elementAt(1);
    ExitMonitor theExit = (ExitMonitor) children.elementAt(2);
    Block catchBlock = (Block) children.elementAt(3);
    startBlock.emit(state, leaveOnStack, theMeat);
    
    Instruction afterTry = state.getJumpTargetInstruction();
    Instruction catchTarget =  state.getJumpTargetInstruction();
    Instruction tryInstruct = state.getTryInstruction(afterTry,
            catchTarget,
            0);   // Any Throwable
    instructions.addElement(tryInstruct);

    theMeat.emit(state,leaveOnStack,theExit);

    instructions.addElement(afterTry);

    theExit.emit(state,leaveOnStack,continuation);
    state.doContinuation(continuation);

    instructions.addElement(catchTarget);
    state.pushStack();
    catchBlock.emit(state, leaveOnStack, continuation);
    
    state.scope = scope;
  }
}
