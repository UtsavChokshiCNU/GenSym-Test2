package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;

/**
 * This class provides scoping services for JavaNode's that provide
 * variable scopes.  At the time of writing this applied only to 
 * ScopedExpression and Block
 */
class VariableScope {
  private Hashtable localVariables = new Hashtable();
  private Vector indexedLocalVariables =  new Vector();
  int startVarID;
  VariableScope parentScope;

  public void add(VariableDeclaration vdec)
       throws ClassException
  {
    String name = vdec.getName();
    Type tpe = vdec.getVariableType(); 
    if (localVariables.containsKey(name)) 
      throw new ClassException("Attempt to define variable " + 
			       name + " twice in the same block");
    else {
      localVariables.put(name,tpe);
    }
  }

  void generateVariableIds(EmitState state) throws ClassException {
    VariableScope scope = state.scope; 
    int varID = state.varID;
    String[] argumentNamesIfAny =  state.argumentNames;
    Type classType =  state.classType;
    Type[] argumentTypes =  state.argumentTypes;

    if (scope == this) 
      throw new ClassException("Block cannot contain itself " + this);
    // top level scope in the method 
    if (scope == null) {
      indexedLocalVariables.addElement("this");
      if (argumentTypes != null) {
	for (int i = 0; i < argumentTypes.length;  i++) {
	  if (argumentNamesIfAny != null && argumentNamesIfAny.length >= i) {
	    String name = argumentNamesIfAny[i];
	    indexedLocalVariables.addElement(name);
	  }
	  Type argType = argumentTypes[i];
	  if (argType.isDoubleType() | argType.isLongType()) {
	    indexedLocalVariables.addElement(null);
	    varID +=2;
	  }
	  else varID++;
	}	
      }
      Enumeration enum =  localVariables.keys();
      Type tpe;
      while (enum.hasMoreElements()) {
	String name = (String) enum.nextElement();
	
	indexedLocalVariables.addElement(name);
	tpe = (Type) localVariables.get(name);
	if (tpe.isDoubleType() | tpe.isLongType()) {
	  indexedLocalVariables.addElement(null);
	  varID +=2;     
	}
	else varID++;      
      }
      // System.out.println("About to put this in scope; localVariables = " + localVariables + ", classType = " + classType);
      localVariables.put("this",classType);
      if (argumentNamesIfAny != null) {
	for (int i = 0; i < argumentNamesIfAny.length;  i++) {
	  String name = argumentNamesIfAny[i];
	  localVariables.put(name,argumentTypes[i]);
	}
      }
      state.varID = varID;
      //state.scope = this;
      //generateVariableIds0(state);

    }
    else {
      generateVariableIds0(state);
    }
  }
  
  void generateVariableIds0(EmitState state) throws ClassException {
    int nextVarID = state.varID;
    this.parentScope = state.scope;
    this.startVarID = nextVarID + 1; // don't re-use indices
    Enumeration enum =  localVariables.keys();
    Type tpe;
    while (enum.hasMoreElements()) {
      String name = (String) enum.nextElement();
      if (parentScope.isDefined(name))
	throw new ClassException("Attempt to redefine variable " + name);
      indexedLocalVariables.addElement(name);
      tpe = (Type) localVariables.get(name);
      if (tpe.isDoubleType() | tpe.isLongType()) {
	indexedLocalVariables.addElement(null);
	nextVarID +=2;
      }
      else nextVarID++;
    }
    state.varID =  nextVarID;
  }  

  

  // ******* Support for named variable scopes ****************

  public boolean isDefined(String st) {
    if (localVariables.containsKey(st))
      return true;
    else if (parentScope == null)
      return false;
    else return parentScope.isDefined(st);
  }
  
  public int getVariableId(String st, Type varType) {
    if (localVariables.containsKey(st)) {
      Type defined = (Type) localVariables.get(st);
      if (varType.potentialMethodArgumentConversion(defined)) 
	return indexedLocalVariables.indexOf(st) + startVarID;
      else return -1;
    }
    else if (parentScope == null)
      return -1;
    else return parentScope.getVariableId(st,varType);
  }

}
