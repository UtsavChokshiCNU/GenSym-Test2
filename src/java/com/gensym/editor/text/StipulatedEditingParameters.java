/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StipulatedEditingParameters.java
 *
 */
package com.gensym.editor.text;

import com.gensym.util.Symbol;


/** The purpose of this class is to simulate the information that
 * an editing session would need to get from an item/attribute
 * that it was told to edit.  It will go away as soon as its
 * functionality can be replaced with the real thing.
 *
 * The only user of this class is EditorApp.
 *
 * @author David McDonald
 * @version 1.0
 */

public class StipulatedEditingParameters {

  private String classNameString = "PROCEDURE";
  private String attributeNameString = "PROCEDURE-DEFINITION";



  private Symbol className, attributeName;

  public Symbol getClassName() {
    return className;
  }
  public Symbol getAttributeName() {
    return attributeName;
  }

  public StipulatedEditingParameters() {
    className = Symbol.intern(classNameString);
    attributeName = Symbol.intern(attributeNameString);
  }
}
