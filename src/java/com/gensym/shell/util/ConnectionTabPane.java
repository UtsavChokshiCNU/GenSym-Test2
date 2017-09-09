package com.gensym.shell.util;

import java.awt.Frame;
import javax.swing.JTabbedPane;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;

import java.util.Vector;
import java.util.Hashtable;

import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.TW2Document;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIDocument;
import com.gensym.ntw.TwAccess;
import javax.swing.JLabel;
import com.gensym.message.Trace;
import javax.swing.JComponent;
import com.gensym.dlg.TabGroupPanel;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2CommunicationErrorEvent;
import java.awt.Dimension;
import java.awt.Insets;


public class ConnectionTabPane extends TabGroupPanel {

  private Frame frame;
  private ConnectionManager connectionManager;
  private ContextChangedAdapter contextChangedListener;
  private G2ConnectionListener connectionListener = new ConnectionListenerAdapter();
  private TabChangedAdapter tabChangedListener;
  private Vector tabSelectionConnectionTable;
  private EmptyComponent emptyComponent = new EmptyComponent();
  private boolean isALLTab = true;

  
  public ConnectionTabPane(Frame frame, ConnectionManager connectionManager) {
    this.frame = frame;
    this.connectionManager = connectionManager;
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    tabChangedListener = new TabChangedAdapter();
    addChangeListener(tabChangedListener);
    setInsets(new Insets(5,6,0,5));
  }

  @Override
  public Dimension getPreferredSize() {
    if (tabSelectionConnectionTable != null &&
	tabSelectionConnectionTable.size() > 0)
      return super.getPreferredSize();
    else
      return new Dimension(0,0);
  }
  
  private void insertNewTab(TwAccess cxn) {
    if (cxn == null) return;
    // for the first connection , make two tabs - ALL and the first connection
    if (tabSelectionConnectionTable == null) {
      tabSelectionConnectionTable = new Vector();

    }

    try {
      addTab(cxn.g2GetHostName()+":"+cxn.g2GetPortNumberOrName(), (EmptyComponent)emptyComponent.clone());
      // store connections in the selectionconnectiontable for tab selection later. vector index is tab page index
      tabSelectionConnectionTable.addElement(cxn);
      if (tabSelectionConnectionTable.size() == 2) {
        insertTab("ALL", (EmptyComponent)emptyComponent.clone(), 0);
        // the first connection tab starts at index 1, 0 is for ALL
        tabSelectionConnectionTable.insertElementAt(null, 0);
      }
      // add connection listener
      cxn.addG2ConnectionListener(connectionListener);

    }
    catch (com.gensym.jgi.G2AccessException ex) {
      Trace.exception(ex);
    }
  }


  private void removeTab(TwAccess cxn) {
    if (tabSelectionConnectionTable == null) return;
    int index = 0;
    if ((index =tabSelectionConnectionTable.indexOf(cxn)) != -1) {
      tabSelectionConnectionTable.removeElementAt(index);
      removeTabAt(index);
    }
    // this is for ALL tab
    if (tabSelectionConnectionTable.size() == 2) {
      removeTabAt(0);
      tabSelectionConnectionTable.removeElementAt(0);
    }

    // remove connectionListener
    if (connectionListener != null)
      cxn.removeG2ConnectionListener(connectionListener);


  }

  public void filterMDIDocuments(TwAccess cxn) {
    if (frame instanceof MDIFrame) {
        MDIDocument[] docs = ((MDIFrame) frame).getManager().getDocuments();
        if (!isALLTab) {
          for (int i=0; i < docs.length; i++) {
	    MDIDocument doc = docs[i];
            if (doc instanceof TW2Document) {
	      if ((((TW2Document)doc).getConnection()).equals(cxn)) {
		doc.setVisible(true);
		try {
		  doc.setSelected(true);
		} catch (java.beans.PropertyVetoException ex) {
		  Trace.exception(ex);
		}
	      } else
		doc.setVisible(false);
	    }
          }
        } else {
          for (int i=0; i < docs.length; i++)
            docs[i].setVisible(true);
        }
      }
      frame.repaint();
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      TwAccess cxn = e.getConnection();
      if (e.isConnectionNew()) {
        insertNewTab(cxn);
      }

      // filter wkspacedocument which do not belong to the connection for non-ALL tabs
      filterMDIDocuments(cxn);

      // select corresponding tab
      if (!isALLTab) {
        int index = tabSelectionConnectionTable.indexOf(cxn);
        if (index == getSelectedIndex()) return;
        if (index != -1)
          addAccessibleSelection(index);
      }
    }

  }

  class TabChangedAdapter implements ChangeListener {
    @Override
    public void stateChanged(ChangeEvent e) {
      if (tabSelectionConnectionTable == null || tabSelectionConnectionTable.size() == 0) return;
      // find the index of selected tab
      int index = getSelectedIndex();
      if (index == -1) return;

      // get its corresponding connection
      TwAccess  cxn = (TwAccess) tabSelectionConnectionTable.elementAt(index);
      if (cxn != null) {
          isALLTab = false;
          // if cxn is current connection, force filtering MDIDoc because cxnMgr will not fire up contextEvent
          if (cxn.equals(connectionManager.getCurrentConnection()))
            filterMDIDocuments(cxn);
          else
            // reset current connection
            connectionManager.setCurrentConnection(cxn);

      } else {
          isALLTab = true;
          MDIDocument[] docs = ((MDIFrame) frame).getManager().getDocuments();
          for (int i=0; i < docs.length; i++)
            docs[i].setVisible(true);

      }

    }
  }

  class ConnectionListenerAdapter implements G2ConnectionListener {
    @Override
    public void g2IsPaused(G2ConnectionEvent event) {}
    @Override
    public void g2IsResumed(G2ConnectionEvent event) {}
    @Override
    public void g2IsReset(G2ConnectionEvent event) {}
    @Override
    public void g2IsStarted(G2ConnectionEvent event) {}
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event) {
     removeTab((TwAccess) event.getSource());
    }
    @Override
    public void g2ConnectionInitialized(G2ConnectionEvent event){}
    @Override
    public void g2MessageReceived(G2ConnectionEvent event){}
    @Override
    public void communicationError(G2CommunicationErrorEvent error_event){}
    public void userModeChanged (TwConnectionEvent evt) {}
    @Override
    public void readBlockage(G2ConnectionEvent event) {}
    @Override
    public void writeBlockage(G2ConnectionEvent event) {}
  }


  class EmptyComponent extends JComponent {
    EmptyComponent() {
      super();
      setSize(new Dimension(0,0));
      setPreferredSize(new Dimension(0,0));
    }
    @Override
    protected Object clone() {
      return new EmptyComponent();
    }
  }

}
