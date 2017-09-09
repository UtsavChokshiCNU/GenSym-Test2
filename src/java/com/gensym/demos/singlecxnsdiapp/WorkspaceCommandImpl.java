
package com.gensym.demos.singlecxnsdiapp;

import com.gensym.ui.Command;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.CommandListener;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.Toolkit;
import com.gensym.message.Resource;
import java.beans.*;
import com.gensym.dlg.*;
import com.gensym.ntw.*;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.classes.KbWorkspace;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.jgi.G2AccessException;
import java.util.Vector;

public class WorkspaceCommandImpl implements Command, PropertyChangeListener {

  private BrowserApplication application;

  private boolean connectionActive = false;

  private static Resource i18nShort = Resource.getBundle ("com.gensym.demos.singlecxnsdiapp.ShortCommandLabels");

  private static Resource i18nLong  = Resource.getBundle ("com.gensym.demos.singlecxnsdiapp.LongCommandLabels");

  static Resource i18nUI  = Resource.getBundle ("com.gensym.demos.singlecxnsdiapp.UiLabels");

  private Vector listeners = new Vector ();

  private static final String
    GET_WORKSPACE = "getwksp";

  public WorkspaceCommandImpl (BrowserApplication browserApp) {
    this.application = browserApp;
    connectionActive = (browserApp.getConnection () != null);
    browserApp.addPropertyChangeListener (this);
  }

  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
    System.out.println ("Running Command -> " + cmdKey);
    getWorkspace ();
  }


  @Override
  public boolean isImmediate(String key){
    return false;
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    return (connectionActive);
  }

  @Override
  public String[] getKeys () {
    return new String[] {GET_WORKSPACE};
  }

  @Override
  public String getDescription (String cmdKey, String key) {
    checkKey (cmdKey);
    if (key.equals (Command.SHORT_DESCRIPTION))
      return i18nShort.getString (cmdKey);
    else
      return i18nLong.getString (cmdKey);
  }    

  @Override
  public Image getIcon (String cmdKey, String key) {
    checkKey (cmdKey);
    if (key.equals (Command.SMALL_ICON))
      return Toolkit.getDefaultToolkit().getImage(getClass().getResource (cmdKey + "_small.gif"));
    else
      return Toolkit.getDefaultToolkit().getImage(getClass().getResource (cmdKey + "_large.gif"));
  }

  @Override
  public Boolean getState (String cmdKey) {
    return null;
  }

  @Override
  public void addCommandListener (CommandListener listener) {
    listeners.addElement (listener);
  }

  @Override
  public void removeCommandListener (CommandListener listener) {
    listeners.removeElement (listener);
  }

  @Override
  public String toString () {
    return "Get Workspace Command";
  }

  @Override
  public void propertyChange (PropertyChangeEvent pce) {
    System.out.println ("WorkspaceCommandImpl..propertyChange (" + pce + ")");
    if (pce.getPropertyName().equals(application.CONNECTION)){
      Object newValue = pce.getNewValue ();
      connectionActive = (newValue != null);
      fireAvailabilityChanges (connectionActive);
    }
  }

  private void checkKey (String cmdKey) {
    if (!(cmdKey.equals (GET_WORKSPACE)))
      throw new IllegalArgumentException ("Unknown Key - " + cmdKey);
  }

  private void fireAvailabilityChanges (boolean connectionActive) {
    notifyListenersOfAvailabilityChange (GET_WORKSPACE);
  }

  private void notifyListenersOfAvailabilityChange (String cmdKey) {
    CommandEvent cmdEvent = new CommandEvent (this, CommandEvent.AVAILABILITY_CHANGED, cmdKey);
    Vector l;
    synchronized(this) {
      l = (Vector)listeners.clone();
    }
    for (int i=0; i<l.size(); i++) {
      CommandListener cl = (CommandListener) l.elementAt (i);
      cl.commandAvailabilityChanged (cmdEvent);
    }
  }


  /**
   * Get a Workspace in the current connection
   */
  private void getWorkspace () {
    try {
      final Sequence wkspNames = application.getConnection().getNamedWorkspaces ();
      int numWksps = wkspNames.size ();
      String[] names = new String [numWksps];
      for (int i=0; i<numWksps; i++)
	names[i] = ((Symbol)wkspNames.elementAt(i)).getPrintValue();
      StandardDialogClient getHandler = new StandardDialogClient () {
	@Override
	public void dialogDismissed (StandardDialog d, int code) {
	  if (d.wasCancelled ()) return;
	  SelectionDialog sd = (SelectionDialog)d;
	  int chosenIndex = sd.getResult ();
	  Symbol wkspName_ = (Symbol) wkspNames.elementAt (chosenIndex);
	  new WorkspaceDownloaderThread (application, wkspName_).start ();
	}
      };
      new SelectionDialog (application.getCurrentFrame(), i18nUI.getString ("getWkspTitle"),
			   false, 
			   i18nUI.getString ("getWkspPrompt"),
			   names, false, SelectionDialog.NO_SELECTION, true, getHandler).setVisible (true);
    } catch (Exception e) {
      new WarningDialog (null, i18nUI.getString ("getWkspError"), true, e.toString (), null).setVisible (true);
    }
  }

}


/**
 * Private Thread class to fetch the workspace and display it.
 */
class WorkspaceDownloaderThread extends Thread {
  
  /**
   * Private variables to store arguments passed to
   * the constructor.
   */
  private BrowserApplication application;
  private Symbol wkspName_;

  /**
   * Save Data
   */
  WorkspaceDownloaderThread (BrowserApplication application,
			   Symbol wkspName_) {
    this.application = application;
    this.wkspName_ = wkspName_;
  }

  /**
   * Do the task
   */
  @Override
  public void run () {
    try {
      KbWorkspace wksp = (KbWorkspace) application.getConnection().getUniqueNamedItem (G2ClassSymbols.KB_WORKSPACE_, wkspName_);
      application.addWorkspace (wksp);
    } catch (G2AccessException gae) {
      new WarningDialog (null, WorkspaceCommandImpl.i18nUI.getString ("getWkspError"), true, gae.toString (), null).setVisible (true);
    }
  }
}
