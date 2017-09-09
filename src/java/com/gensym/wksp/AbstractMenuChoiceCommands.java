
package com.gensym.wksp;

import com.gensym.ui.StructuredCommand;
import java.util.Vector;
import java.awt.Image;
import java.awt.PrintJob;
import java.awt.Frame;
import java.awt.Graphics;
import com.gensym.ui.Command;
import com.gensym.ui.CommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.StructuredCommandListener;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;
import com.gensym.message.Resource;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.Symbol;

/**
 * Package private abstract implementation of SelectionCommand
 * to be used by our subclasses. If we decide that this functionality
 * is useful, stable and reviewed, we can expose it in later releases.
 * - vkp, 5/7/98
 */
abstract class AbstractMenuChoiceCommands implements SelectionCommand {

  protected WorkspaceElement[] currentSelection;

  private Resource shortDescBundle, longDescBundle;
  protected WorkspaceView wkspView;
  private Vector cmdKeys;
  private SelectionAdapter cmdCurrentSelectionListener;

  AbstractMenuChoiceCommands (String[] keys) {
    int numKeys = keys.length;
    cmdKeys = new Vector (numKeys);
    for (int i=0; i<numKeys; i++)
      cmdKeys.addElement (keys[i]);
  }

  @Override
  public void setWorkspaceView (WorkspaceView view) {
    if (cmdCurrentSelectionListener != null) {
      if (wkspView != null)
	wkspView.removeSelectionListener (cmdCurrentSelectionListener);
      cmdCurrentSelectionListener = null;
    }
    reset ();
    wkspView = view;
    currentSelection = null;
    if (wkspView != null) {
      currentSelection = wkspView.getSelection ();
      wkspView.addSelectionListener (cmdCurrentSelectionListener);
    }
  }

  protected void reset () {
    currentSelection = null;
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
    return null;
  }


  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    return true;
  }

  @Override
  public boolean isImmediate (String cmdKey) {
    checkKey (cmdKey);
    return true;
  }

  /**
   * Returns the state for the command.
   */
  @Override
  public Boolean getState(String cmdKey) {
    return null;
  }

  @Override
  public abstract void actionPerformed (ActionEvent e);


  @Override
  public abstract Vector getStructuredKeys ();


  protected void checkKey (String cmdKey) {
    if (cmdKeys.indexOf (cmdKey) >= 0)
      return;
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
