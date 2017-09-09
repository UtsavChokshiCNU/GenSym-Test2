/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceData.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import com.gensym.classes.KbWorkspace;
import com.gensym.util.Symbol;

public class WorkspaceData extends Object {

  public static final int UNKNOWN = 0;
  public static final int KB_WORKSPACES = 1;
  public static final int G2_KB_WORKSPACE = 2;

  private int dataType = UNKNOWN;

  private KbWorkspace workspace;

  /** Value to display. */
  protected String string;

  public WorkspaceData(KbWorkspace workspace, Symbol name) {
    this.dataType = G2_KB_WORKSPACE;
    this.workspace = workspace;
    string = name.toString();
  }

  public WorkspaceData(int moduleInfo, String cxnTag) {
    this.dataType = KB_WORKSPACES;
    if (cxnTag.equals(""))
      string = "Named Workspaces";
    else
      string = "Named Workspaces ("+cxnTag+")";
  }

  public KbWorkspace getKbWorkspace() {
    return workspace;
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
