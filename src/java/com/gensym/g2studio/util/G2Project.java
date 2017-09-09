/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Project.java
 *
 */
package com.gensym.g2studio.util;

import com.gensym.classes.Kb;

public class G2Project extends Object {

  private Kb projectKb;

  /** Value to display. */
  protected String projectName;

  /**
   * Constructs a new instance of SampleData with the passed in
   * arguments.
   */
  public G2Project(String projectName, Kb projectKb) {
    this.projectName = projectName;
    this.projectKb = projectKb;
  }

  public Kb getKb() {
    return projectKb;
  }

  /**
   * Sets the string to display for this object.
   */
  public void setString(String newString) {
    projectName = newString;
  }

  /**
   * Returns the string to display for this object.
   */
  public String string() {
    return projectName;
  }

  @Override
  public String toString() {
    return projectName;
  }
}
