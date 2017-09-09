package com.gensym.dispatcher;

/**
 * Decision
 */

public class Decision extends Node

{
  Node trueNode, falseNode;
  Condition condition;

  public Decision(Condition condition,
		  Node trueNode,
		  Node falseNode)
  {
    this.condition = condition;
    this.trueNode = trueNode;
    this.falseNode = falseNode;
  }
  
  public void setCondition(Condition condition)
  {
    this.condition = condition;
  }
  
  public void setTrueNode(Node trueNode)
  {
    this.trueNode = trueNode;
  }

  public void setFalseNode(Node falseNode)
  {
    this.falseNode = falseNode;
  }

  public Condition getCondition()
  {
    return condition;
  }
  
  public Node getTrueNode()
  {
    return trueNode;
  }

  public Node getFalseNode()
  {
    return falseNode;
  }

  Node getNode(boolean trueOrFalse)
  {
    if (trueOrFalse)
      return trueNode;
    else
      return falseNode;
  }

  @Override
  public String toString() 
  {
    String str = "if (" + condition + ")";
    if (trueNode instanceof SimpleAction && !(trueNode instanceof Noop))
      str+= "\n" + trueNode + "\n";
    else
      str+= "{\n" + trueNode + "\n}";
    if (falseNode instanceof SimpleAction && !(falseNode instanceof Noop))
      str+= " else \n   " + falseNode + "\n";
    else if (falseNode instanceof Decision)
      str+= " else " + falseNode ;
    else if (!(falseNode instanceof Noop))
      str+= " else {\n   " + falseNode + "\n}";
    return str;
  }

}
