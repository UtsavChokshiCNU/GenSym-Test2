package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Enumeration;

public abstract class NetworkNode extends JavaNode {

  boolean emitted = false;
  boolean inNetworkStatement = false;
  int index = -1;
  Instruction label;
  NetworkStatement parent;

  public abstract Enumeration preferredFollowers();

  public abstract void emitNetworkNode(EmitState state,
				       NetworkNode followingNode,
				       Statement continuation)
                                      throws ClassException;

}
