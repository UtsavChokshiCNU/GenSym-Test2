package com.gensym.newclasstools;

import java.util.Vector;

public class For extends Statement {
  // Consider Providing a constructor to cover the cases when part is not specified.

  private static final boolean trace = false;

  private VariableScope variableScope = new VariableScope();
  
  public For (VariableDeclaration varDec, Expression condition, ExpressionStatement[] updates, Statement body) throws ClassException {	
    this((Statement)varDec, condition, updates, body);
    variableScope.add(varDec);
  }
  
  public For (ExpressionStatement[] inits, Expression condition,
	      ExpressionStatement[] updates, Statement body) throws ClassException {	
    this(combineInits(inits), condition, updates, body);
  }

  private static Statement combineInits(ExpressionStatement[] inits) throws ClassException {
    Block initBlock = new Block();
    for(int i = 0; i < inits.length; i++) {
      initBlock.add(inits[i]);
    }
    return initBlock;
  }

  private For (Statement init, Expression condition, ExpressionStatement[] updates, Statement body) throws ClassException {	
    Type tpe = condition.getExpressionType();
    if (! tpe.isBooleanType())
      throw new ClassException("Condition in while statement must be boolean, received" + tpe);
    addJavaNode(init);
    addJavaNode(new OperatorCall("!", new Expression[]{condition}));
    Block updateBlock = new Block();
    for(int i = 0; i < updates.length; i++) {
      updateBlock.add(updates[i]);
    }
    addJavaNode(updateBlock);
    addJavaNode(body);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)
        throws ClassException
  {

    Vector instructions = state.instructions;
    Statement init =  (Statement) children.elementAt(0);
    Expression condition =  (Expression) children.elementAt(1);
    Statement update =  (Statement) children.elementAt(2);
    Statement body =  (Statement) children.elementAt(3);

    VariableScope savedScope = state.scope;
    super.emit(state,false,continuation);
    state.scope = variableScope;

    init.emit(state, false, this);

    // Create jump tag instructions
    Instruction continueLabel = state.getJumpTargetInstruction();
    Instruction breakLabel = state.getJumpTargetInstruction();
    Instruction startLabel = state.getJumpTargetInstruction();
    Instruction entryLabel = state.getJumpTargetInstruction();

    
    // Start with a branch to the bottom. That way the loop only contains
    // one branch (the conditional branch to start) which makes it faster.

    Instruction ins = Instruction.makeInstruction(opc_goto,0);
    ins.jumpDestination = entryLabel;
    instructions.addElement(ins);

    ContinuableAndBreakableContext saved =
      state.getContinuableAndBreakableContext();
    state.setContinuableAndBreakableContext(continueLabel, breakLabel);

    instructions.addElement(startLabel);

    body.emit(state, false, this);

    instructions.addElement(continueLabel);

    update.emit(state, false, this);

    instructions.addElement(entryLabel);

    condition.emit(state, true, this);

    Instruction branchInst;

    if (!(condition instanceof OperatorCall))  {
      if (trace) {
	System.out.println("Getting Branch instruction from OperatorCall");
      }
      branchInst = Instruction.makeInstruction(opc_ifeq,0);
      instructions.addElement(branchInst);		
    }
    else {
      if (trace) {
	System.out.println("Getting Branch instruction from OperatorCall");
      }
      branchInst = (Instruction) instructions.lastElement();
    }
    branchInst.jumpDestination = startLabel;

    state.restoreContinuableAndBreakableContext(saved);

    state.scope = savedScope;

    instructions.addElement(breakLabel);
    state.doContinuation(continuation);
  }

  @Override
  void generateVariableIds(EmitState state) throws ClassException {
      variableScope.generateVariableIds(state);
  }

}

