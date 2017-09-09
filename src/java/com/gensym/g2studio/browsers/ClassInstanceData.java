/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceData.java
 *
 */
package com.gensym.uitools.browsers;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemTable;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;

public class ClassInstanceData extends Object implements BrowserSymbols {

  private int dataType = UNKNOWN;

  private Module module;
  private KbWorkspace workspace;
  private ClassDefinition classDefinition;
  private G2Definition g2Definition;
  private SystemTable systemTable;

  private Symbol baseClass;
  private Symbol moduleScope;

  /** Value to display  */
  protected String string;

  public ClassInstanceData(Symbol hierarchyType, Symbol baseClass, Symbol moduleScope) {
    System.out.println("ClassInstanceData (hierachy): "+hierarchyType);
    if (hierarchyType.equals(MODULE_HIERARCHY_))
      dataType = MODULE_HIERARCHY;
    else if (hierarchyType.equals(WORKSPACE_HIERARCHY_))
      dataType = WORKSPACE_HIERARCHY;
    else if (hierarchyType.equals(CLASS_HIERARCHY_))
      dataType = CLASS_HIERARCHY;
    else if (hierarchyType.equals(KNOWLEDGE_BASE_))
      dataType = KNOWLEDGE_BASE;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
   
    string = hierarchyType.toString();
  }

  public ClassInstanceData(Module module, Symbol baseClass, Symbol moduleScope) {
    System.out.println("ClassInstanceData (module)");
    this.dataType = G2_MODULE;
    this.module = module;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    string = module.getName().toString();
  }

  public ClassInstanceData(KbWorkspace workspace, Symbol baseClass, Symbol moduleScope) {
    //System.out.println("ClassInstanceData (workspace)");
    this.dataType = G2_KB_WORKSPACE;
    this.workspace = workspace;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    try {
      Symbol name = (Symbol)workspace.getNames();
      if (name == null) name = DEFAULT_WORKSPACE_NAME_;
      string = name.toString();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      System.out.println(gae);
    }
  }

  public ClassInstanceData(ClassDefinition classDefinition, Symbol baseClass, Symbol moduleScope) {
    System.out.println("ClassInstanceData (classDefinition)");
    this.dataType = G2_CLASS_DEFINITION;
    this.classDefinition = classDefinition;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    try {
      string = classDefinition.getClassName().toString();
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  public ClassInstanceData(G2Definition g2Definition, Symbol baseClass, Symbol moduleScope) {
    //System.out.println("ClassInstanceData (g2Definition)");
    this.dataType = G2_DEFINITION;
    this.g2Definition = g2Definition;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    try {
      string = g2Definition.getClassName().toString();
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  public ClassInstanceData(SystemTable systemTable, Symbol baseClass, Symbol moduleScope) {
    System.out.println("ClassInstanceData (systemTable)");
    this.dataType = G2_SYSTEM_TABLE;
    this.systemTable = systemTable;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    try {
    string = systemTable.getG2ClassName().toString();
    } catch (G2AccessException gae) {
    System.out.println(gae);
    }
  }

  public Symbol getModuleScope() {
    return moduleScope;
  }

  public Symbol getBaseClass() {
    return baseClass;
  }

  public Module getModule() {
    return module;
  }

  public KbWorkspace getKbWorkspace() {
    return workspace;
  }

  public ClassDefinition getClassDefinition() {
    return classDefinition;
  }

  public G2Definition getG2Definition() {
    return g2Definition;
  }

  public SystemTable getSystemTable() {
    return systemTable;
  }

  /**
   * Returns the object's data type
   */
  public int getDataType() {
    return dataType;
  }

  /**
   * Sets the string to display for this object.
   */
  public void setString(String newString) {
    string = newString;
  }

  /**
   * Returns the string to display for this object.
   */
  public String string() {
    return string;
  }

  @Override
  public String toString() {
    return string;
  }
}
