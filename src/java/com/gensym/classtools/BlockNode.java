package com.gensym.classtools;

import java.util.Vector;
import java.util.Enumeration;

public class BlockNode extends NetworkNode {

  public BlockNode(Block block) throws ClassException {
    addJavaNode(block);
  }

  public void setNextNode(NetworkNode next) throws ClassException {
    if (!parent.children.contains(next))
      throw new ClassException("Successor to a node must be part of the same NetworkStatement");
    this.next = next;
    if (next == null) {
      this.finalNode = true;
	} else {
      this.finalNode = false;
    }
  }

  public NetworkNode getNextNode() {
    return this.next;
  }

  public void setFinal() {
    finalNode = true;
    next = null;
  }

  public boolean getFinal() {
    return(finalNode);
  }

  @Override

  public Enumeration preferredFollowers() {
    Vector followers = new Vector(1);
    if (next != null) 
      followers.addElement(next);
    return followers.elements();
  }


  @Override


  public void emitNetworkNode(EmitState state,
			      NetworkNode followingNode,
			      Statement continuation) throws ClassException
  {
    super.emit(state,false,continuation);

    /*
    System.out.println("Emitting Block Node " + this);
    System.out.println("FollowingNode is  " + followingNode);
    System.out.println("next is " + next);
    System.out.println("finalNode is " + finalNode);
    */

    ((JavaNode)children.elementAt(0)).emit(state, false, 
					   (finalNode ? continuation :
					    //continuation isn't really parent,
					    // but we need a non-null
					    // statement.
					    (Statement)parent));
    if (finalNode) {
      if (followingNode != null && continuation != null) {
	Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
	state.instructions.addElement(gotoInst);
	gotoInst.jumpTagIfAny = ((NetworkStatement)parent).getEndLabel().jumpTagIfAny;
      }
    } else {
      if ((followingNode != null && !followingNode.equals(next)) || next != null) {
	Instruction gotoInst = Instruction.makeInstruction(opc_goto,0);
	state.instructions.addElement(gotoInst);
	gotoInst.jumpTagIfAny = next.label.jumpTagIfAny;
      }
    }
  }

  private NetworkNode next;
  private boolean finalNode = false;
  
}
