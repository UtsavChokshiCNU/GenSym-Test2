/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Launcher.java
 *
 */
package com.gensym.editor.text;

import java.awt.Window;
import java.util.Vector;
import com.gensym.util.CorruptionException;
import com.gensym.classes.Item;
import com.gensym.ntw.TwGateway;
import com.gensym.util.Symbol;

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

  private final static boolean debug = false;


  /**
   * Initiates a full editing session.
   * <p>NOTE: This method will actually make the window visible before it
   * it returns.
   * </p>
   * @param item - The item whose attribute is to be edited.
   * @param attributeName - A symbol naming the attribute to be edited.
   * @param connection -- a TwGateway identifying the G2 where the item resides.
   * @returns The window that contains the UI for the editing session.
   * @throws IllegalArgumentException if null is passed in as the attribute or
   * if the attribute name is not valid for the item's class
   * @throws CorruptionException if for some reason the text of the attribute
   * cannot be accessed from G2.
   */
  public static Window launchG2TextEditor(Item item, Symbol attributeName, 
					  TwGateway connection) 
  throws IllegalArgumentException, CorruptionException {
    Session session = getEditor(connection.getEditorPool());
    session.setActive( true );
    session.initialize(item, attributeName, true);
    return session.getFrame();
  }


  /**
   * Initiates a full editing session.
   * <p>NOTE: This method will actually make the window visible before it
   * it returns.
   * </p>
   * @param item - The item whose attribute is to be edited.
   * @param attributeName - A symbol naming the attribute to be edited.
   * @returns The window that contains the UI for the editing session.
   * @throws IllegalArgumentException if null is passed in as the attribute or
   * if the attribute name is not valid for the item's class
   * @throws CorruptionException if for some reason the text of the attribute
   * cannot be accessed from G2.
   */

  public static Window launchG2TextEditor(Item item, Symbol attributeName) 
  throws IllegalArgumentException, CorruptionException {
    Session session = getEditor(Session.getEditorPool());
    session.setActive( true );
    session.initialize(item, attributeName, true);
    return session.getFrame();
  }


  private static Session getEditor (Vector editorPool) {
    Session session = null;
    if (editorPool.isEmpty()) { // optimization
      session = makeAnotherG2TextEditor(editorPool);
      if (debug)
	System.out.println("Making the very first session: " + session.toString());
      return session;
    }
    else {
      for(int i=0; i < editorPool.size(); i++) {
	session = (Session)editorPool.elementAt(i);
	if (!session.getActive()) {
	  if (debug)
	    System.out.println("Reusing " + session.toString());
	  return session;
	}
      }
      session = makeAnotherG2TextEditor(editorPool);
      if (debug)
	System.out.println("Making an additional Sesssion: " + session.toString());
      return session;
    }
  }


  private static int highestEditorIndex = -1;

  private static Session makeAnotherG2TextEditor(Vector editorPool) {
    Session session = new Session();
    session.setIndex(++highestEditorIndex);
    editorPool.addElement(session);
    return session;
  }
}
