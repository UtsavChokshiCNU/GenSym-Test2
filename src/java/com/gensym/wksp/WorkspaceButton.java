package com.gensym.wksp;

import com.gensym.util.Symbol;
/**
 * A <code>WorkspaceIcon</code> intended for use with entities of class <code>Button</code>.
 * All buttons have an attribute named <code>LABEL_</code>.
 */
public interface WorkspaceButton extends WorkspaceIcon {

  /**
   * An attribute name received in the <code>itemModified</code> method for this class.
   */
  public static final Symbol LABEL_ = Symbol.intern("LABEL");

  public void setArmed(boolean state);
}



