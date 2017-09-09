
package com.gensym.demos.wksppanel;

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
import java.util.Vector;

public class ConnectionCommandImpl implements Command, PropertyChangeListener {

  private BrowserApplication application;

  private boolean connectionActive = false;

  private static Resource i18nShort = Resource.getBundle ("com.gensym.demos.wksppanel.ShortCommandLabels");

  private static Resource i18nLong  = Resource.getBundle ("com.gensym.demos.wksppanel.LongCommandLabels");

  private static Resource i18nUI  = Resource.getBundle ("com.gensym.demos.wksppanel.UiLabels");

  private Vector listeners = new Vector ();

  private static final String
    OPEN_CONNECTION  = "open",
    CLOSE_CONNECTION = "close";

  public ConnectionCommandImpl (BrowserApplication browserApp) {
    this.application = browserApp;
    connectionActive = (browserApp.getConnection () != null);
    browserApp.addPropertyChangeListener (this);
  }


  @Override
  public boolean isImmediate(String key){
    if (key.equals(OPEN_CONNECTION))
      return false;
    else
    return true;
  }


  @Override
  public void actionPerformed (ActionEvent e) {
    String cmdKey = e.getActionCommand ();
    checkKey (cmdKey);
    System.out.println ("Running Command -> " + cmdKey);
    if (cmdKey.equals (OPEN_CONNECTION))
      openConnection ();
    else
      closeConnection ();
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    return (connectionActive == (cmdKey.equals (CLOSE_CONNECTION)));
  }

  @Override
  public String[] getKeys () {
    return new String[] {OPEN_CONNECTION, CLOSE_CONNECTION};
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
    return "Connection Command";
  }

  @Override
  public void propertyChange (PropertyChangeEvent pce) {
    System.out.println ("ConnectionCommandImpl.propertyChange (" + pce + ")");
    if (pce.getPropertyName().equals(application.CONNECTION)){
      Object newValue = pce.getNewValue ();
      connectionActive = (newValue != null);
      fireAvailabilityChanges (connectionActive);
    }
  }

  private void checkKey (String cmdKey) {
    if (!(cmdKey.equals (OPEN_CONNECTION)) &&
	!(cmdKey.equals (CLOSE_CONNECTION)))
      throw new IllegalArgumentException ("Unknown Key - " + cmdKey);
  }

    /**
     * Opens a new connection to a G2
     */
  private void openConnection () {
    String[] labels = {i18nUI.getString ("hostPrompt"),
		       i18nUI.getString ("portPrompt")};
    String[] initialValues = {"localhost", "1111"};
    StandardDialogClient openHandler = new StandardDialogClient () {
      @Override
      public void dialogDismissed (StandardDialog d, int code) {
	try {
	  InputDialog id = (InputDialog)d;
	  if (id.wasCancelled ()) return;
	  String[] results = id.getResults ();
	  String host = results[0];
	  String port = results[1];
	  TwAccess connection = TwGateway.openConnection (host, port);
	  // The following call will fail if the G2 is secure.
	  connection.login();
	  application.setConnection (connection);
	} catch (Exception e) {
	  Trace.exception (e);
	  new ErrorDialog (null, "Error During Connect", true, e.toString (), null).setVisible (true);
	}
      }
    };	  
    new InputDialog (application.getCurrentFrame (), i18nUI.getString ("openConnectionTitle"),
			 true, labels, initialValues,
			 (StandardDialogClient) openHandler).setVisible (true);
  }
  
  /**
   * Closes the current connection
   */
  private void closeConnection () {
    application.setConnection (null);
  }

  private void fireAvailabilityChanges (boolean connectionActive) {
    notifyListenersOfAvailabilityChange (OPEN_CONNECTION);
    notifyListenersOfAvailabilityChange (CLOSE_CONNECTION);   
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
