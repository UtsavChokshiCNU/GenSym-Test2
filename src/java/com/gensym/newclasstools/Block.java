package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;

public class Block extends Statement {
  private VariableScope variableScope = new VariableScope();

  /** Create an empty block
   */
  public Block() {
    super();	
  }

  /** Add a statement to a block.
   */
  public void add(Statement se) throws ClassException {
    if (se == null) return;
    addJavaNode(se); 
    if (se instanceof VariableDeclaration) {
      VariableDeclaration vdec = (VariableDeclaration) se;
      variableScope.add(vdec);
    }
  }

  /**
   * Shortcut for adding an ExpressionStatement to a block
   * This will check that the expression being added can be passed to the
   * constructor of  ExpressionStatement. This saves the user the effort of
   * always having to create ExpressionStatement objects
   */
  public void add(Expression exp) throws ClassException {
    if (exp == null) return;
    ExpressionStatement es = new ExpressionStatement(exp);
    addJavaNode(es);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)  throws ClassException {
    // System.out.println("***Emitting a new block; " + this + "***");
    Statement currentContinuation;
    JavaNode node1, node2;
    long childrenLength, lastButOneLength;
    if (leaveOnStack)
      throw new ClassException("leaveOnStack cannot be true for Block");
    VariableScope scope = state.scope;
    super.emit(state,false,continuation);
    state.scope = variableScope;
    childrenLength = children.size();
    lastButOneLength = childrenLength - 1;
    
    for (int i = 0; i < childrenLength; i++) {	
      node1 = (JavaNode) children.elementAt(i);
      if (i < lastButOneLength)
      {
        node2 = (JavaNode) children.elementAt(i + 1);
	// System.out.println("***Emitting statement " + node1 + " in block");
        node1.emit(state, false, (Statement) node2);
      }
      else {
	// System.out.println("***Emitting final statement " + node1 + " in block");
	node1.emit(state, false, continuation);
      }
    }
    state.scope = scope;
    state.doContinuation(continuation);
  }

  @Override
  void generateVariableIds(EmitState state) throws ClassException {
      variableScope.generateVariableIds(state);
  }

  public boolean isEmpty() {
    return (children.size() == 0 ?  true : false);
  } 
}
