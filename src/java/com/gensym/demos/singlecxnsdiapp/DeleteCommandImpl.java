
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
import com.gensym.wksp.WorkspaceView;
import com.gensym.ntw.util.SelectionListener;
import com.gensym.ntw.util.SelectionEvent;

public class DeleteCommandImpl implements Command, PropertyChangeListener, SelectionListener {

  private BrowserApplication application;
  
  private WorkspaceView currentView;

  private static Resource i18nShort = Resource.getBundle ("com/gensym/demos/wksppanel/ShortCommandLabels");

  private static Resource i18nLong  = Resource.getBundle ("com/gensym/demos/wksppanel/LongCommandLabels");

  static Resource i18nui  = Resource.getBundle ("com/gensym/demos/wksppanel/UiLabels");

  private Vector listeners = new Vector ();

  private static final String DELETE = "delete";

  public DeleteCommandImpl (BrowserApplication browserApp) {
    this.application = browserApp;
    browserApp.addPropertyChangeListener (this);
  }

  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
    System.out.println ("Running Command -> " + cmdKey);
    //fill action in here
  }

  private boolean determineAvailability(){
    boolean available = false;
    //fill availability determination here
    return available;
  }


  @Override
  public boolean isImmediate(String key){
    return true;
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    return determineAvailability();
  }

  @Override
  public String[] getKeys () {
    return new String[] {DELETE};
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
    return "Delete Command";
  }

  @Override
  public void propertyChange (PropertyChangeEvent pce) {
    System.out.println ("DeleteCommandImpl..propertyChange (" + pce + ")");
    if (pce.getPropertyName().equals(application.WORKSPACE_COUNT)){
      //fill in add/remove selection listener
      fireAvailabilityChanges (determineAvailability());
    }
  }

  @Override
  public void selectionChanged(SelectionEvent event){
    fireAvailabilityChanges (determineAvailability());
  }


  private void checkKey (String cmdKey) {
    if (!(cmdKey.equals (DELETE)))
      throw new IllegalArgumentException ("Unknown Key - " + cmdKey);
  }

  private void fireAvailabilityChanges (boolean connectionActive) {
    notifyListenersOfAvailabilityChange (DELETE);
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
