
package com.gensym.demos.singlecxnsdiapp;

import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Vector;

import com.gensym.classes.KbWorkspace;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.Command;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.CommandListener;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.G2ClassSymbols;
import com.gensym.wksp.MultipleWorkspacePanel;

public class NavigationCommandImpl implements Command, PropertyChangeListener {

  private BrowserApplication application;

  private static Resource i18nShort = Resource.getBundle ("com/gensym/demos/singlecxnsdiapp/ShortCommandLabels");

  private static Resource i18nLong  = Resource.getBundle ("com/gensym/demos/singlecxnsdiapp/LongCommandLabels");

  private Vector listeners = new Vector ();

  private static final String GO_BACK = "goback";
  private static final String GO_FORWARD = "goforward";

  public NavigationCommandImpl (BrowserApplication browserApp) {
    this.application = browserApp;
    browserApp.addPropertyChangeListener (this);
  }


  @Override
  public boolean isImmediate(String key){
    return true;
  }

  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
    //System.out.println ("Running Command -> " + cmdKey);
    if (cmdKey.equals (GO_FORWARD))
      application.setNext ();
    else
      application.setPrevious ();
  }

  private boolean determineAvailability(){
    boolean available = false;
    //fill in availability determination here
    /*
     * If no connection => false
     * If no downloaded workspaces => false
     */
    TwAccess cxn = application.getConnection();

    if (cxn !=  null) {
      int wkspCount = application.getWorkspaceCount();
      if (wkspCount > 0)
	available = true;
    }
    
    return available;
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    boolean available = determineAvailability();
    return available;
  }

  @Override
  public String[] getKeys () {
    return new String[] {GO_BACK, GO_FORWARD};
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
  public void propertyChange (PropertyChangeEvent pce) {
    //System.out.println ("NavigationCommandImpl.propertyChange (" + pce + ")");
    if (pce.getPropertyName().equals(application.WORKSPACE_COUNT) ||
	pce.getPropertyName().equals(application.WORKSPACE_INDEX)) {
      fireAvailabilityChanges (determineAvailability());
    }
  }

  @Override
  public String toString () {
    return "Navigate Workspaces Command";
  }

  private void checkKey (String cmdKey) {
    if (!(cmdKey.equals (GO_BACK) || cmdKey.equals (GO_FORWARD)))
      throw new IllegalArgumentException ("Unknown Key - " + cmdKey);
  }

  private void fireAvailabilityChanges (boolean connectionActive) {
    notifyListenersOfAvailabilityChange (GO_BACK);
    notifyListenersOfAvailabilityChange (GO_FORWARD);
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

}
