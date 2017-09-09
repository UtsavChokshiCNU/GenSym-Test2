
package com.gensym.demos.multiplecxnmdiapp;

import com.gensym.ui.*;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;

public class ConnectionCommandImpl extends com.gensym.ui.AbstractCommand {

  private ConnectionManager cxnMgr;
  private boolean hasActiveConnection;
  public static final String TW_DISCONNECT = "TwDisconnect";

  public ConnectionCommandImpl (ConnectionManager connectionManager) {
    super (new CommandInformation[] {new CommandInformation (TW_DISCONNECT,
							     false, // initially available
							     "CommandShortResource",
							     "CommandLongResource",
							     "disconnect.gif", // small icon
							     null, // large icon
							     null, //state
							     true)});
    cxnMgr = connectionManager;
    cxnMgr.addContextChangedListener (new ContextChangedListener () {
      @Override
      public void currentConnectionChanged (ContextChangedEvent e) {
	hasActiveConnection = (cxnMgr.getCurrentConnection () != null);
	setAvailable0 (TW_DISCONNECT, hasActiveConnection);
      }
    });
  }

  private void setAvailable0 (String cmdKey, boolean isAvailable) {
    setAvailable (cmdKey, isAvailable);
  }

  @Override
  public boolean isAvailable (String cmdKey) {
    checkKey (cmdKey);
    return hasActiveConnection;
  }

  @Override
  public void actionPerformed (java.awt.event.ActionEvent e) {
    String actionCommand = e.getActionCommand ();
    checkKey (actionCommand);
    cxnMgr.getCurrentConnection().closeConnection();
  }

}
