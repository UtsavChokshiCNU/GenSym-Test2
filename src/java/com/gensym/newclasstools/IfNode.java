package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Enumeration;

public class IfNode extends NetworkNode {

  public IfNode(Expression ifexp) throws ClassException {
    addJavaNode(ifexp);
  }

  public void setNextNodeIfTrue (NetworkNode iftrue) throws ClassException {
    if (parent.children.contains(iftrue)) {
      this.nextIfTrue = iftrue;
      if (iftrue != null) {
	this.finalIfTrue = true;
      }
    } else {
      throw new ClassException("Successor to a node must be part of the same NetworkStatement");
    }
  }

  public NetworkNode getNextNodeIfTrue() {
    return nextIfTrue;
  }

  public void setFinalIfTrue() {
    finalIfTrue = true;
    nextIfTrue = null;
  }

  public void getFinalIfTrue(boolean finalNode) {
    this.finalIfTrue = finalNode;
    if (finalNode = true) {
      nextIfTrue = null;
    }
  }

  public void setNextNodeIfFalse (NetworkNode iffalse) throws ClassException {
    if (parent.children.contains(iffalse)) {
      nextIfFalse = iffalse;
      if (iffalse != null) {
	this.finalIfFalse = true;
      }
    } else {
      throw new ClassException("Successor to a node must be part of the same NetworkStatement");
    }
  }

  public NetworkNode getNextNodeIfFalse() {
    return nextIfFalse;
  }

  public void setFinalIfFalse() {
    finalIfFalse = true;
    nextIfFalse = null;
  }

  public void getFinalIfFalse(boolean finalNode) {
    this.finalIfFalse = finalNode;
    if (finalNode = true) {
      nextIfFalse = null;
    }
  }

  @Override
  public Enumeration preferredFollowers() {
    Vector followers = new Vector(1);
    if (nextIfTrue != null) 
      followers.addElement(nextIfTrue);
    if (nextIfFalse != null) 
      followers.addElement(nextIfFalse);
    return followers.elements();
  }

  @Override
  public void emitNetworkNode(EmitState state,
			      NetworkNode followingNode,
			      Statement continuation) throws ClassException
  {
    NetworkNode branchNode, fallThroughNode;
    Instruction branch;
    boolean branchFinal, fallThroughFinal;

    super.emit(state, false, continuation);
    ((JavaNode) children.elementAt(0)).emit(state, true, continuation);
    if (followingNode == nextIfTrue) {
      branchNode = nextIfFalse;
      fallThroughNode = nextIfTrue;
      branch = Instruction.makeInstruction(opc_ifeq,0);
    } else {
      branchNode = nextIfTrue;
      fallThroughNode = nextIfFalse;
      branch = Instruction.makeInstruction(opc_ifne,0);
    }
    state.instructions.addElement(branch);
    
    if (branchNode == null) {
      branch.jumpDestination = parent.getEndLabel();
    } else {
      /*
      System.out.println("branchnode is " + branchNode);
      System.out.println("branchnode label is " + branchNode.label);
      */
      branch.jumpDestination = branchNode.label;
    }
    
    if (fallThroughNode == null) {
      // call getEndLabel even if no branch is needed to ensure continuation
      // gets generated if necessary
      Instruction endLabel = parent.getEndLabel();
      if (followingNode != null) {
	Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
	state.instructions.addElement(gotoInst);
	gotoInst.jumpDestination = endLabel;
      }
    } else {
      if (fallThroughNode != followingNode) {
	Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
	state.instructions.addElement(gotoInst);
	gotoInst.jumpDestination = fallThroughNode.label;
      }
    }
  }

  private NetworkNode nextIfTrue;
  private NetworkNode nextIfFalse;
  private boolean finalIfTrue = false;
  private boolean finalIfFalse = false;
  
}
