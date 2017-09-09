package com.gensym.dispatcher;

import java.awt.*;
import java.util.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;



/**
 * DispatchTable
 */

public class DispatchTable 
{
  private Decision defaultRoot;
  private Hashtable roots = new Hashtable();
  private static boolean debug = false;
  
  transient Object target;
  transient Container container;
  transient EventObject event;
  transient Vector variables;

  private String pprintVariables() {
    String str = "";
    if (variables == null)
      return str;
    for (int i=0; i<variables.size(); i++) {
      Variable var = (Variable)variables.elementAt (i);
      String type = var.getType().getName();
      String name = var.getName();
      Object val = var.getValue();
      str+=type + " " + name;
      if (val != null)
	str+= " = " + val + ";\n";
      else
	str+= ";\n";
    }
    return str;
  }

  private String getType(Class cls) {
    if (!cls.isPrimitive())
      return cls.getName();
    if (cls == Integer.TYPE)
      return "Integer";
    else if (cls == Boolean.TYPE)
      return "Boolean";
    else if (cls == Float.TYPE)
      return "Float";
    else if (cls == Short.TYPE)
      return "Short";
    else if (cls == Long.TYPE)
      return "Long";
    else if (cls == Double.TYPE)
      return "Double";
    else if (cls == Character.TYPE)
      return "Character";
    else if (cls == Byte.TYPE)
      return "Byte";
    return "Object";
  }
  
  private String pprintSetVariable() {
    if (variables == null)
      return "";
    String str = "public void setVariable(String name, Object value) {\n";
    str+= "if (false){}\n";
    for (int i=0; i<variables.size(); i++) {
      Variable var = (Variable)variables.elementAt (i);
      String type = var.getType().getName();
      String name = var.getName();
      str+= " else if (name.equals(\""+name+"\"))\n"+
	name + " = (("+ getType(var.getType()) + ")value)";
      if (var.getType().isPrimitive())
	str+= "."+type+"Value();\n";
      else
	str+= ";\n";
    }
    return str + "}";
  }

  private String pprintGetVariable() {
    if (variables == null)
      return "";
    String str = "public Variable getVariable(String name) {\n";
    str+= "if (false){}\n";
    for (int i=0; i<variables.size(); i++) {
      Variable var = (Variable)variables.elementAt (i);
      Class classType = var.getType();
      String type = classType.getName();
      String name = var.getName();
      str+= " else if (name.equals(\""+name+"\"))\n"+
	"return new Variable(\"" + name + "\",";
      if (classType.isPrimitive())
	str+= "new " + getType(classType) + "(" + name + "), " +
	  getType(classType) + ".TYPE, true);\n";
      else
	str+= name + ", " + type + ".class, true);\n";
    }
    return str + "return null;\n}";
  }
  
  @Override
  public String toString() {
    return
      "transient Object theTarget;\n" +
      "transient Container theContainer;\n" +
      "transient EventObject theEvent;\n" +
      "//transient Vector variables;\n" +
      pprintVariables() + "\n\n" +
      pprintSetVariable() + "\n\n" +
      pprintGetVariable() + "\n\n" +
      "void dispatch() {\n" +
      defaultRoot +
      roots + 
      //other roots??
      "}";
  }
  
  protected Variable getVariable(String name)
       throws NoSuchVariableException
  {
    for (int i=0; i<variables.size(); i++) {
      Variable var = (Variable)variables.elementAt (i);
      if (var.equals(name)) {
	if (debug)
	  System.out.println("FOUND VAR " + name + " in " + variables);
	return var;
      }
    }
    if (debug)
      System.out.println("COULDNT FIND VAR " + name + " in " + variables);
    throw new NoSuchVariableException(name);
  }

  public void setVariable(String name, Object value)
       throws NoSuchVariableException
  {
    Variable var = getVariable(name);
    if (var != null && var.isSetable()) {
      if (debug)
	System.out.println("SETTING VALUE OF " + var + " to " + value);
      var.setValue(value);
    } else
      throw new NoSuchVariableException(name);
  }
  
  public void addVariable(Variable variable)
  {
    if (variables == null)
      variables = new Vector();
    variables.addElement(variable);
  }
  
  public Action lookupAction(Decision decision)
       throws IllegalAccessException
  {
    if (decision == null)
      return null;
    Node nextNode = decision.condition.isSatisfied(this)?
      decision.trueNode : decision.falseNode;
    if (nextNode instanceof Action || nextNode == null)
      return (Action)nextNode;
    else
      return lookupAction((Decision)nextNode);
  }

  public void setEvent(EventObject event)
  {
    this.event = event;
  }

  public void setContainer(Container container)
  {
    this.container = container;
  }

  public void setTarget(Object target)
  {
    this.target = target;
  }
  
  void setRoot(Decision root)
  {
    this.defaultRoot = root;
  }
  
  Decision getRoot()
  {
    return defaultRoot;
  }

  public Decision getRoot(Object obj) 
  {
    if (obj == null)
      return getRoot();
    else
      return (Decision)roots.get(obj);
  }

  public void clear()
  {
    roots.clear();
    setRoot(null);
    //variables = null;
  }

  public void clearVariables(){
	variables = null;	
  }

  public Vector getVariables(){
	return variables;	
  }

  public void setVariables(Vector var){
		variables = var;
  }
  
  public void setRoot(Object obj, Decision root)
  {
    if (obj == null){
      setRoot(root);
      return;
    }
    if (root == null)
      roots.remove(obj);
    else
      roots.put(obj, root);
  }

}
