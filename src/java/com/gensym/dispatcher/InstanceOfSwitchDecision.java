package com.gensym.dispatcher;

import java.lang.reflect.*;
import com.gensym.message.Trace;

public class InstanceOfSwitchDecision extends SwitchDecision {

  private static boolean debug = false;
  
  public InstanceOfSwitchDecision(Reference reference) {
    super(reference);
  }

  public static boolean instanceOfMethod(Object obj1, Class type) {
    return type.isInstance(obj1);
  }

  public static Method instanceOfMethod;
  static {
    try {
      instanceOfMethod
	= InstanceOfSwitchDecision.class.getMethod("instanceOfMethod",
						   new Class[]
						   {Object.class, Class.class});
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }
  
  private Condition newCase(Object type) {
    if (debug)
      System.out.println("NEW INSTANCE OF CASE");
    try {
      return new SimpleCondition(instanceOfMethod,
				 referenceSwitch,
				 new ConstantReference(type));
      
    } catch (NonStaticMethodException nstme) {
      if (debug)
	System.out.println("instanceOfMethod needs to be static" + nstme);
      Trace.exception(nstme);
      return null;
    }
  }

  @Override
  public void addCase(Object constCase, Node node){
    if (setDefault) return;
    if (setRoot) {
      Decision nextDecision = new Decision(newCase(constCase),node,new Noop());
      currentDecision.setFalseNode(nextDecision);
      if (debug)
	System.out.println("add instanceof case " + constCase + node + " to\n" + this);
      currentDecision = nextDecision;
    } else {
      setCondition(newCase(constCase));
      setTrueNode(node);
      setRoot = true;
    }
  }
  
  @Override
  public String toString() 
  {
    String str = "//switch (" + referenceSwitch + ") \n";
    str += "if (" + getCondition() + ")";
    Node trueNode = getTrueNode(),  falseNode = getFalseNode();
    if (trueNode instanceof SimpleAction && !(trueNode instanceof Noop))
      str+= "\n" + trueNode + "\n";
    else
      str+= "{\n" + trueNode + "\n}";
    if (falseNode instanceof SimpleAction && !(falseNode instanceof Noop))
      str+= " else \n   " + falseNode + "\n";
    else if (falseNode instanceof Decision)
      str+= " else " + falseNode;
    else if (!(falseNode instanceof Noop))
      str+= " else {\n   " + falseNode + "\n}";
    return str;
  }
      
}
  
