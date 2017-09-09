
package com.gensym.wksp;

import com.gensym.ui.StructuredCommand;
import com.gensym.ui.StructuredCommandListener;
import java.util.Vector;
import java.awt.Image;
import com.gensym.ui.CommandListener;
import java.awt.event.ActionEvent;
import com.gensym.ui.Command;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.message.Resource;

public class StandardItemCommands implements SelectionCommand {

  private WorkspaceElement[] currentSelection;

  public static final String CUT = "cut",
                             COPY = "copy",
                             PASTE = "paste",
                             PRINT = "print";

  private Resource shortDescBundle, longDescBundle;
  private WorkspaceView wkspView;
  private SelectionAdapter cmdSelnListener;

  /**
   * 
   */
  public StandardItemCommands () {
  }

  @Override
  public void setWorkspaceView (WorkspaceView view) {
    if (cmdSelnListener != null) {
      wkspView.removeSelectionListener (cmdSelnListener);
      cmdSelnListener = null;
    }
    reset ();
    wkspView = view;
    wkspView.addSelectionListener (cmdSelnListener);
  }

  private void reset () {
    currentSelection = null;
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    if (currentSelection != null)
      System.out.println ("# Selected Items = " + currentSelection.length);
    else
      System.out.println ("Current Selection = null");
    return (currentSelection != null && currentSelection.length > 0 && (cmdKey.equals (CUT) || cmdKey.equals (COPY)));
  }

  /**
   * Add a CommandListener.
   */
  @Override
  public void addCommandListener (CommandListener listener) {
  }

  /**
   * Remove a CommandAvailabilityListener.
   */
  @Override
  public void removeCommandListener(CommandListener listener) {
  }

  /**
   * Add a CommandListener.
   */
  @Override
  public void addStructuredCommandListener (StructuredCommandListener listener) {
  }

  /**
   * Remove a CommandAvailabilityListener.
   */
  @Override
  public void removeStructuredCommandListener (StructuredCommandListener listener) {
  }

  /**
   * Returns an array of command keys.
   */
  @Override
  public String[] getKeys() {
    return null;
  }

  /**
   * Returns a textual description for command.
   * The key should be either SHORT_DESCRIPTION or
   * LONG_DESCRIPTION.
   */
  @Override
  public String getDescription (String cmdKey, String key) {
    checkKey (cmdKey);
    if (Command.SHORT_DESCRIPTION.equals (key)) {
      if (shortDescBundle == null)
	shortDescBundle = Resource.getBundle ("com/gensym/wksp/ShortCommandDescriptions");
      System.out.println ("Lookup up key " + cmdKey + " in " + shortDescBundle);
      return shortDescBundle.getString (cmdKey);
    } else {
      if (longDescBundle == null)
	longDescBundle = Resource.getBundle ("com/gensym/wksp/LongCommandDescriptions");
      return longDescBundle.getString (cmdKey);
    }
  }

  /**
   * Returns an image of the size indicated by key.
   * Key should be either SMALL_ICON or LARGE_ICON.
   */
  @Override
  public Image getIcon (String cmdKey, String key) {
    checkKey (cmdKey);
    return null;
  }


  @Override
  public boolean isImmediate (String cmdKey) {
    checkKey (cmdKey);
    return (cmdKey.equals (PRINT));
  }

  /**
   * Returns the state for the command.
   */
  @Override
  public Boolean getState(String cmdKey) {
    checkKey (cmdKey);
    return null;
  }

  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
  }

  @Override
  public Vector getStructuredKeys () {
    Vector keys = new Vector (4);
    Vector subKeys = new Vector (3);
    subKeys.addElement (CUT);
    subKeys.addElement (COPY);
    subKeys.addElement (PASTE);
    keys.addElement (subKeys);
    return keys;
  }

  private void checkKey (String cmdKey) {
    if (cmdKey.equals (CUT) ||
	cmdKey.equals (COPY) ||
	cmdKey.equals (PASTE)) return;
    throw new IllegalArgumentException ("Unknown Key - <" + cmdKey + ">");
  }

  class SelectionAdapter implements SelectionListener {
    @Override
    public void selectionChanged (SelectionEvent evt) {
      reset ();
      currentSelection = wkspView.getSelection ();
    }
  }

}
