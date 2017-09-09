
package com.gensym.shell.util;

import com.gensym.ntw.*;
import com.gensym.ntw.util.DefaultWorkspaceShowingAdapter;
import com.gensym.jgi.*;
import java.util.Vector;
import com.gensym.message.Trace;

class ContextChangedAdapterForShowingAdapter implements ContextChangedListener{

  private Vector connections = new Vector ();
  private WorkspaceShowingListener showingAdapter;
  private G2ConnectionListener cxnCleanupAdapter = new ConnectionCleanupAdapter ();

  ContextChangedAdapterForShowingAdapter (ConnectionManager cxnMgr,
					  WorkspaceShowingListener showingListener)
  throws G2AccessException {
    showingAdapter = showingListener;
    TwAccess[] openConnections = cxnMgr.getOpenConnections();
    for (int i=0; i<openConnections.length; i++){
      openConnections[i].addG2ConnectionListener (cxnCleanupAdapter);
      if (openConnections[i].isLoggedIn ())
	openConnections[i].addWorkspaceShowingListener (showingAdapter);
      connections.addElement(openConnections[i]);
    }
  }

  @Override
  public void currentConnectionChanged(ContextChangedEvent event){
    TwAccess currentConnection = event.getConnection();
    if (currentConnection == null) return;
    if (!connections.contains(currentConnection)){
      try{
	connections.addElement(currentConnection);
	currentConnection.addG2ConnectionListener (cxnCleanupAdapter);
	currentConnection.addWorkspaceShowingListener (showingAdapter);
      }
      catch(com.gensym.jgi.G2AccessException ex){
	Trace.exception(ex);
      }
    }
  }

  class ConnectionCleanupAdapter extends TwConnectionAdapter {
    @Override
    public void g2ConnectionClosed (G2ConnectionEvent cxnEvent) {
      G2Access cxn = (G2Access) cxnEvent.getSource ();
      connections.removeElement (cxn);	// Drop it so it can be garbage collected
      DefaultWorkspaceShowingAdapter adapter =
	(DefaultWorkspaceShowingAdapter) showingAdapter;
      adapter.cleanupConnection(cxn);
      /* No need to remove xn and showing listeners. Pointers to us */
    }
  }
}
