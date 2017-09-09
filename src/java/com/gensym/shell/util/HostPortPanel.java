/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HostPortPanel.java
 *
 */
package com.gensym.shell.util;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.util.Vector;

import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * A Container that displays connection information (host and port) for an 
 * application. For single connection applications, the connection information
 * would typically be displayed as a piece of static text. For multiple 
 * connection applications, the connection information would typically be 
 * displayed as a drop down list for switching between the existing Telewindows2 
 * connections. 
 */
public class HostPortPanel extends Container {
  private static Resource i18ui  = Resource.getBundle ("com/gensym/shell/util/UiLabels");
  private static String noConnectionText = i18ui.getString ("NO_CONNECTION");
  private static String comboBoxToolTip = i18ui.getString("Host/Port");
  
  private ConnectionManager connectionMgr;
  private TwConnection connection;

  private JLabel connectionLabel;
  private JComboBox connectionComboBox;
 
  /**
   * Creates a HostPortPanel that uses a JLabel for displaying the
   * host and port information.
   * @param connnection The TwConnection for the single connection application
   */
  public HostPortPanel (TwConnection connection) throws G2AccessException {
    this (false);
    setConnection (connection);
  }

  /**
   * Creates a HostPortPanel that uses a JComboBox for displaying the
   * host and port information.
   * @param connectionMgr The ConnectionManager for the multiple connection
   * application
   */
  public HostPortPanel (ConnectionManager connectionMgr) throws G2AccessException {
    this (true);
    this.connectionMgr = connectionMgr;
    connectionList = new Vector ();
    //Check if there is any open connection. if yes, update connectionList and
    //connectionComboBox with the connection - FY 01/19/00
    if (connectionMgr.hasConnections()) {
        TwAccess[] connections = connectionMgr.getOpenConnections();
        for (int i=0; i < connections.length; i++) {
            TwConnection aTwConnection =  (TwConnection) connections[i];
            aTwConnection.addG2ConnectionListener (new ConnectionAdapter ());
            connectionList.addElement(aTwConnection);
            connectionComboBox.addItem (aTwConnection.toShortString());
        }
    }

    connectionMgr.addContextChangedListener (new ContextListener ());
    setConnection0 ((TwConnection)connectionMgr.getCurrentConnection ());

  }

  /**
   * Creates a HostPortPanel that uses a JLabel for display the host
   * and port information for the single connection application.
   */
  public HostPortPanel () {
    this (false);
  }

  @Override
  public void setMaximumSize(Dimension d) {
    connectionComboBox.setMaximumSize(d);
  }
  
  private HostPortPanel (boolean useComboChooser) {
    setLayout (new BoxLayout (this, BoxLayout.X_AXIS));
    add (Box.createRigidArea (new Dimension (5, 1)));
    if (!useComboChooser) {//System.out.println ("Created Connection Label!");
      add (connectionLabel = new JLabel ("             "));
    } else {//System.out.println ("Created Connection Combo Box");
      connectionComboBox = new JComboBox();
      connectionComboBox.setToolTipText(comboBoxToolTip);
      add (connectionComboBox);
      connectionComboBox.setLightWeightPopupEnabled(false);
      connectionComboBox.addItemListener (new HostPortItemListener ());
      connectionComboBox.addActionListener (new HostPortActionListener ());
    }
    add (Box.createRigidArea (new Dimension (5, 1)));
    try {
      setConnection (null);
    } catch (G2AccessException gae) {// Should never happen!
    }
  }

  /**
   * Sets the connection for the HostPortPanel
   */
  public void setConnection (TwConnection connection) throws G2AccessException {
    //System.out.println("running HostPortPanel.setConnection");
    if (connectionMgr != null)
      throw new RuntimeException ("Cannot call setConnection");
    setConnection0 (connection);
  }

  private void setConnection0 (TwConnection cxn) throws G2AccessException {
    //System.out.println("running HostPortPanel.setConnection0, cxn: "+cxn);
    if (connection != null && connection.equals (cxn))
      return;

    if (connectionMgr != null)
      connectionMgr.setCurrentConnection (cxn);

    updateHostPortDisplay (cxn);

    connection = cxn;
  }

  private void updateHostPortDisplay (TwConnection cxn) {
    //System.out.println("running HostPortPanel.updateHostPortDisplay " + cxn.toShortString ());
    if (cxn != null) {

      if (connectionLabel != null) {
	connectionLabel.setText (cxn.toShortString ());
    }
      else {
	connectionComboBox.setEnabled(true);
	int currentIndex = connectionList.indexOf (cxn);
	if (!(currentIndex == connectionComboBox.getSelectedIndex ())) // bug in 1.1.1 Beta 1 - Infinite Recursion
	    connectionComboBox.setSelectedIndex (currentIndex);
      }
    } else {
      if (connectionLabel != null)
	connectionLabel.setText (noConnectionText + "      ");
       else
	 connectionComboBox.setEnabled(false);
    }
  }
       
  class HostPortItemListener implements ItemListener {
    @Override
    public void itemStateChanged (ItemEvent e) {
      //System.out.println ("HostPortPanel.itemStateChanged : " + e);
    }
  }

  class HostPortActionListener implements ActionListener {
    @Override
    public void actionPerformed (ActionEvent e) {
      JComboBox cb = (JComboBox) e.getSource ();
      int selIndex = cb.getSelectedIndex ();
      if (selIndex < 0)		// We're removing items?
	return;
      TwConnection cxn = (TwConnection) connectionList.elementAt (selIndex);
      try {
	setConnection0 (cxn);
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
    }
  }

  class ContextListener implements ContextChangedListener {
    @Override
    public void currentConnectionChanged (ContextChangedEvent e) {
      //System.out.println("running ContextListener.currentConnectionChanged");
      TwConnection cxn = (TwConnection) connectionMgr.getCurrentConnection ();
      
      ensureConnectionInList (cxn);
      try {
	setConnection0 (cxn);
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      } catch (Exception ex) {
	Trace.exception (ex);
      }
    }
  }

  private Vector connectionList;
  private void ensureConnectionInList (TwConnection cxn) {
    if (cxn == null || connectionList.indexOf (cxn) >= 0)
      return;
    connectionList.addElement (cxn);
    G2ConnectionListener x;
    cxn.addG2ConnectionListener (x = new ConnectionAdapter ());

    // we need to check to see if this host:port combination is alreay in list.
    // if it is, then we should append something to the end of the text to make
    // it different
    String newInfo = cxn.toShortString();
    int newLen = newInfo.length();
    int count = 1;
    String cxnInfo = null;
    for (int i=0; i<connectionComboBox.getItemCount(); i++) {
      cxnInfo = (String)connectionComboBox.getItemAt(i);
      if (cxnInfo.length() >= newLen) {
	// the string is long enough, check to see if it contains the new string
	if (cxnInfo.regionMatches(0, newInfo, 0, newLen)) 
	  count = count + 1;
      }
    }

    if (count > 1)
      newInfo = newInfo + " <" + count + ">";

    connectionComboBox.addItem (newInfo);
  }

  private void removeConnectionFromList (TwConnection cxn) {
    connectionComboBox.removeItemAt (connectionList.indexOf (cxn));
    connectionList.removeElement (cxn);
  }

  class ConnectionAdapter extends G2ConnectionAdapter {
    @Override
    public void g2ConnectionClosed (G2ConnectionEvent event) {
      try {
      TwConnection cxn = (TwConnection) event.getSource ();
      removeConnectionFromList (cxn);
      cxn.removeG2ConnectionListener (this);
      } catch (Exception ex) {
	Trace.exception (ex);
      }
    }
  }

  /**
   * @undocumented
   */
  public static void main (String[] args) throws Exception {
    JFrame f = new JFrame ("Test");
    f.getContentPane().add (new HostPortPanel (), BorderLayout.CENTER);
    f.pack ();
    f.setVisible (true);
  }

}
