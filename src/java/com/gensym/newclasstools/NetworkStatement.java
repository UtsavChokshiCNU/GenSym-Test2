package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Enumeration;

public class NetworkStatement extends Statement {

  private Instruction endLabel;
  private boolean endLabelIsUsed;

  public NetworkStatement (NetworkNode initialNode) throws ClassException {
    addJavaNode(initialNode);
  }

  public void add(NetworkNode newnode) throws ClassException {
    if (newnode.inNetworkStatement)
      throw new ClassException("Node " + newnode + " is already contained in a NetworkStatement");
    addJavaNode (newnode);
    newnode.parent = this;
    newnode.index = children.indexOf(newnode);
  }

  @Override
  void emit(EmitState state, boolean leaveOnStack, Statement continuation)  throws ClassException {
    NetworkNode node;
    Enumeration e = getChildren();
    while(e.hasMoreElements()) {
      node = (NetworkNode)e.nextElement();
      // System.out.println("Labelling " + node);
      node.label = state.getJumpTargetInstruction();
      node.emitted = false;
    }
    endLabel = state.getJumpTargetInstruction();
    endLabelIsUsed = false;

    NetworkNode nodeToEmit = (NetworkNode)children.elementAt(0);
    NetworkNode followingNode = null;
    boolean followingNodeFound = false;

    while (nodeToEmit != null) {
      nodeToEmit.emitted = true;
      followingNodeFound = false;
      e = nodeToEmit.preferredFollowers();
      // by emitting the nodes in an appropriate order, we cut down on goto's.
      while(e.hasMoreElements()) {
	followingNode = (NetworkNode)e.nextElement();
	if (!followingNode.emitted) {
	  followingNodeFound = true;
	  break;
	}
      }
      if (!followingNodeFound) {
	e = getChildren();
	while(e.hasMoreElements()) {
	  followingNode = (NetworkNode)e.nextElement();
	  if (!followingNode.emitted) {
	    followingNodeFound = true;
	    break;
	  }
	}
      }
      if (!followingNodeFound) {
	followingNode = null;
      }
      state.instructions.addElement(nodeToEmit.label);
      nodeToEmit.emitNetworkNode(state, followingNode, continuation);
      nodeToEmit = followingNode;
    }
    if (endLabelIsUsed) {
      state.instructions.addElement(endLabel);
      // if there is a continuation here, blocks will never branch here
      // (because they will do their own docontinuation instead)
      state.doContinuation(continuation);
    }
  }

  Instruction getEndLabel() {
    endLabelIsUsed = true;
    return (endLabel);
  }
}
