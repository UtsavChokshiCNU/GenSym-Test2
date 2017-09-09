/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Launcher.java
 *
 */

package com.gensym.ntwx.editor.text;

import java.awt.Window;

import com.gensym.editor.text.Session;
import com.gensym.classes.Item;
import com.gensym.util.Symbol;
import com.gensym.util.CorruptionException;

/**
 * The Launcher class encapsulates all of the setup necessary to
 * initiate a session editing a given attribute on a given item in a
 * single static method.  The method instantiates all of the objects
 * that comprise an editing session. It populates the default editor
 * UI and makes it visible, showing the previous value of the
 * attribute and the prompts that are applicable at the initial
 * location of the cursor. The UI object is returned as a
 * java.awt.Window so that the user of the method can resize or
 * reposition it as they like. Multiple editing sessions can be active
 * simultaneously, including even multiple sessions editing the same
 * item and attribute; in this case the last session to apply its
 * results back to G2 establishes the attribute's value.
 */

public class Launcher {

  /**
   * Initiates a full editing session.
   * <p>NOTE: This method will actually make the window visible before it
   * it returns.
   * </p>
   * @param item - The item whose attribute is to be edited.
   * @param attribute - A symbol naming the attribute to be edited.
   * @returns The window that contains the UI for the editing session.
   * @throws IllegalArgumentException if null is passed in as the attribute or
   * if the attribute name is not valid for the item's class
   * @throws CorruptionException if for some reason the text of the attribute
   * cannot be accessed from G2.
   */

  public static Window launchG2TextEditor(Item item, Symbol attribute) 
  throws IllegalArgumentException, CorruptionException {
    Session session = new Session(item, attribute, null);
    return session.getFrame();
  }
}
