/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbData.java
 *
 */
package com.gensym.g2studio.util;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemTable;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;

public class KbData extends Object {

  public static final int UNKNOWN = 0;
  public static final int G2_PROJECT = 1;
  public static final int G2_MODULE = 2;
  public static final int G2_KB_WORKSPACE = 3;
  public static final int G2_CLASS_DEFINITION = 4;
  public static final int G2_SYSTEM_TABLE = 5;

  public static final int MODULE_CLASSES = 20;
  public static final int MODULE_WORKSPACES = 21;
  public static final int MODULE_MODULES = 22;
  public static final int MODULE_SYSTEM_TABLES = 23;

  public static final int THE_INVISIBLE_ROOT = 99;

  private int dataType = UNKNOWN;

  private Module module;
  private KbWorkspace workspace;
  private ClassDefinition classDefinition;
  private SystemTable systemTable;

  /** Value to display. */
  protected String string;

  public KbData(Module module) {
    //System.out.println("KbData (module)");
    this.dataType = G2_MODULE;
    this.module = module;
    string = module.getName().toString();
  }

  public KbData(KbWorkspace workspace, Symbol name) {
    //System.out.println("KbData (workspace)");
    this.dataType = G2_KB_WORKSPACE;
    this.workspace = workspace;
    string = name.toString();
  }

  public KbData(ClassDefinition classDefinition) {
    //System.out.println("KbData (classDefinition)");
    this.dataType = G2_CLASS_DEFINITION;
    this.classDefinition = classDefinition;
    try {
      string = classDefinition.getClassName().toString();
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  public KbData(SystemTable systemTable) {
    //System.out.println("KbData (systemTable)");
    this.dataType = G2_SYSTEM_TABLE;
    this.systemTable = systemTable;
    try {
      string = systemTable.getG2ClassName().toString();
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  public KbData(int moduleInfo) {
    //System.out.println ("KbData (moduleInfo)");
    this.dataType = moduleInfo;
    if (moduleInfo == MODULE_CLASSES)
      string = "Classes";
    else if (moduleInfo == MODULE_WORKSPACES)
      string = "Workspaces";
    else if (moduleInfo == MODULE_MODULES)
      string = "Modules";
    else if (moduleInfo == MODULE_SYSTEM_TABLES)
      string = "System Tables";
    else if (moduleInfo == G2_PROJECT) 
      string = "Project";
    else if (moduleInfo == THE_INVISIBLE_ROOT)
      string = "ROOT";
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
