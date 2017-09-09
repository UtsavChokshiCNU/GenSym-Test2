/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 UserModePanel.java
 *
 */
package com.gensym.shell.util;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Hashtable;
import java.util.Vector;

import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.ntw.TwGateway;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;


import javax.swing.AbstractListModel;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.MutableComboBoxModel;
/**
 * A Container that consists of a JComboBox for displaying and changing 
 * the user mode for the current client. In single connection applications,
 * the application is responible for updating this command with
 * the current connection via setConnection.  In multiple connection 
 * applications, the ConnectionManager is used to obtain the currentConnection. 
 */
public class UserModePanel extends Container {
  private static Resource i18ui  = Resource.getBundle ("com/gensym/shell/util/UiLabels");
  private static String comboBoxToolTip = i18ui.getString("UserMode" );

  private ConnectionManager connectionMgr;
  private TwConnection connection;
 
  private JComboBox userModeComboBox;

  // Hashtable for storing information about connection(s) & mode(s)
  private int maxConnections = 5;
  private Hashtable modesForConnection = new Hashtable(maxConnections);

  private ModeListener modeListener = new ModeListener();
 
  /**
   * @param connection The TwConnection for which to display user mode information
   * @param allowUserModeAddition A boolean that specifies whether or not the JComboBox
   * created for displaying user mode information should be editable.
   */
  public UserModePanel (TwConnection connection, boolean allowUserModeAddition) throws G2AccessException {
    this (allowUserModeAddition);
    setConnection (connection);
  }

  /**
   * @param connectionManager The ConnectionManager from which to get the current
   * connection via getCurrentConnection().
   * @param allowUserModeAddition A boolean that specifies whether or not the JComboBox
   * created for displaying user mode information should be editable.
   */
  public UserModePanel (ConnectionManager connectionManager, 
			boolean allowUserModeAddition) throws G2AccessException {
    this (allowUserModeAddition);
    connectionMgr = connectionManager;
    connectionMgr.addContextChangedListener (new ContextListener ());
    setConnection0 ((TwConnection)connectionMgr.getCurrentConnection ());
  }

  /**
   * Assume a single connection application, and does not allow edits to the JComboBox
   * created for displaying user mode information.
   */
  public UserModePanel () {
    this (false);
  }

  @Override
  public void setMaximumSize(Dimension d) {
    userModeComboBox.setMaximumSize(d);
  }
  
  private UserModePanel (boolean allowUserModeAddition) {
    setLayout (new BoxLayout (this, BoxLayout.X_AXIS));
    add (Box.createRigidArea (new Dimension (10, 1)));
    userModeComboBox = new JComboBox(new ComboBoxModel());
    userModeComboBox.setToolTipText(comboBoxToolTip);    
    add (userModeComboBox);
    userModeComboBox.setLightWeightPopupEnabled (false);
    add (Box.createRigidArea (new Dimension (5, 1)));
    userModeComboBox.setLightWeightPopupEnabled(false);
    userModeComboBox.addActionListener (new UserModeActionListener ());
    userModeComboBox.setEditable (allowUserModeAddition);

    try {
      setConnection (null);
    } catch (G2AccessException gae) {// Should never happen!
    }
  }

  /**
   * Sets the current connection.  This component acts upon the current
   * connection.  Single connection application should use this method to
   * inform this component about changes in the current connection.
   */
  public void setConnection (TwConnection cxn) throws G2AccessException {
    //System.out.println("UserModePanel.setConnection(cxn): "+cxn);
    if (connectionMgr != null)
      throw new RuntimeException ("Cannot call setConnection");
    setConnection0 (cxn);
  }

  private void setConnection0 (TwConnection cxn) throws G2AccessException {
    //System.out.println ("UserModePanel.setConnection0 (" + cxn + ")");

    if (connection != null && connection.equals (cxn))
      return;

    clearUserModes(); 

    if (connection != null)
      connection.removeTwConnectionListener (modeListener);

    if (cxn != null) 
      cxn.addTwConnectionListener (modeListener);

    connection = cxn;

    // see if we already know about this connection, if not 
    // add it to Hashtable
    if (cxn != null) {
      //System.out.println("modesForConnection empty? "+modesForConnection.isEmpty());
      //System.out.println("cxn in modesForConnection? "+modesForConnection.containsKey(cxn));
      userModeComboBox.setEnabled(true);
      if (modesForConnection.isEmpty() || (!(modesForConnection.containsKey(cxn)))) {
	//System.out.println("adding cxn to ModesForConnection");
	addConnectionToModesForConnection(cxn);
      }
      updateUserMode (cxn);
      if (cxn.isLoggedIn()) {
	Symbol currentMode = cxn.getUserMode();
	updateUserMode (cxn, currentMode);
	//System.out.println("calling updateUserMode(cxn, mode)");
      }
    } else {
      //System.out.println("cxn is null => disable");
      userModeComboBox.setEnabled(false);
    }
  }

  private void addConnectionToModesForConnection(TwConnection cxn) {
    //System.out.println("addConnectionToModesForConnection: "+cxn);
    
    // get the known modes for this connection
    Symbol[] modes = getModesForConnection(cxn);
    //System.out.println("after call to getModesForConnection, modes: "+modes);
    if (modes != null) {
      //System.out.println("modes[0]: "+modes[0]);
      modesForConnection.put(cxn, modes);
    }
  }

  private boolean isNewMode(TwConnection cxn, Symbol mode) {
    //System.out.println("running isNewMode: "+mode);
    boolean isNew = true;
    Symbol[] modes = (Symbol[])modesForConnection.get(cxn);
    if (modes != null) {
      for (int i=0; (i<modes.length) && isNew; i++) {
	if (mode.equals(modes[i])) 
	  isNew = false;
      }
    }
    return isNew;
  }

  private void addModeForConnection (TwConnection cxn, Symbol newMode) {
    //System.out.println("addModeForConnection: "+newMode);
    Symbol[] newModes = null;
    Symbol[] modes = (Symbol[])modesForConnection.get(cxn);
    if (modes == null) {
      newModes = new Symbol[1];
      newModes[0] = newMode;
    }
    else {
      newModes = new Symbol[modes.length + 1];
      System.arraycopy (modes, 0, newModes, 0, modes.length);
      newModes[modes.length] = newMode;
      //sort
      //Sorter.sort(newModes, Sorter.ASCENDING);
    }
    
    modesForConnection.put(cxn, newModes);
  }

  private static final Symbol G2_GET_KNOWN_USER_MODES_ = Symbol.intern ("G2-GET-KNOWN-USER-MODES");

  /**
   * @undocumented
   */
  protected Symbol[] getModesForConnection(TwConnection cxn) {
    //System.out.println("getModesForConnection: "+cxn);
    Symbol[] modes = null;
    try {
      Sequence knownModes = 
	(Sequence)cxn.callRPC (G2_GET_KNOWN_USER_MODES_, new Object[] {});
      int numModes = knownModes.size();
      modes = new Symbol[numModes];
      knownModes.copyInto (modes);
    } catch (G2AccessException ex) {
      Trace.exception(ex);
    }
    
    // sort the list alphabetically when we get it
    return modes;
  }

  private void updateUserMode (TwConnection cxn) {
    //System.out.println("updateUserMode(cxn)");

    clearUserModes();
   
    Symbol[] modes = (Symbol[])modesForConnection.get(cxn);
    //System.out.println("modesForConnection returned: "+ com.gensym.core.DebugUtil.printArray (modes));
    if (modes != null) {
      //System.out.println("number of modes: "+modes.length);
      //System.out.println("modes= " + com.gensym.core.DebugUtil.printArray (modes);
      for (int i=0; i<modes.length; i++) {
	try {
	  userModeComboBox.addItem (convertModeToDisplay (modes[i]));
	} catch (IllegalArgumentException iae) {
	  // catching JComboBox bug where you cant type in new mode if
	  // ComboBoxList is down. It tries to call setSelectedIndex
	  // with -1
	  Trace.exception(iae);
	}
      }
    }
  }

  private void updateUserMode (TwConnection connection, Symbol newMode) {
    //System.out.println("updateUserMode(connection, newMode): "+connection+"  "+newMode);

    // at this point, newMode is in the hashtable but might not
    // be in the comboBoxList.
    if (isNewMode(connection, newMode)) {
      addModeForConnection(connection, newMode);
      userModeComboBox.addItem (convertModeToDisplay (newMode));
    }
    int selectedIndex = getIndexForMode(newMode);

    int currentIndex = userModeComboBox.getSelectedIndex ();
    if (!(currentIndex == selectedIndex)) // hack for bug in 1.1.1 Beta 1 - Infinite Recursion otherwise
      userModeComboBox.setSelectedIndex(selectedIndex);
  }

  private void clearUserModes () {
    try {
      userModeComboBox.removeAllItems ();
    } catch (IndexOutOfBoundsException iobe) {
      //Trace.exception (iobe);
    }
    userModeComboBox.setSelectedItem (null);
  }  

  private int getIndexForMode(Symbol mode) {
    //System.out.println("getIndexForMode: "+mode);
    Symbol[] modes = (Symbol[])modesForConnection.get (connection);
    for (int i=0; i<modes.length; i++) {
      if (mode.equals (modes[i])) {
	return i;
      }
    }
    return -2;
  }

  private String convertModeToDisplay (Symbol userMode) {
    return userMode.getPrintValue().toLowerCase ();
  }

  private Symbol convertInputToMode (String modeInput) {
    return Symbol.intern (modeInput.toUpperCase ());
  }
 
  class UserModeActionListener implements ActionListener {
    @Override
    public void actionPerformed (ActionEvent e) {
      /*
       * User did one of two things. He/she either typed in a new mode, or
       * selected one from the list. First check to see if this is a known
       * mode for this connection and do the appropriate thing:
       * i) If not, add it to the Symbol array for the connection in the
       * hashtable.
       * ii) If it is, then just change the mode & update the display
       */
      //System.out.println("UserModeActionListener.actionPerformed : "+ e);

      String action = e.getActionCommand();
      if (action.equals("comboBoxChanged")) {
	JComboBox cb = (JComboBox) e.getSource();
	cb.hidePopup ();
	Object selObj = cb.getSelectedItem();

	if (selObj != null) {
	  Symbol selMode = convertInputToMode (selObj.toString().trim());

	  TwConnection cxn = null;
	  if (connectionMgr != null)
	    cxn = (TwConnection)connectionMgr.getCurrentConnection();
	  else
	    cxn = connection;

	  if (cxn != null) {
	    //System.out.println("cxn is: "+cxn);

	    if (isNewMode(cxn, selMode)) {
	      addModeForConnection(cxn, selMode);
	      if (cb.getSelectedIndex () < 0)
		cb.addItem (convertModeToDisplay (selMode));
	    }
	    updateUserMode(cxn, selMode);

	    if (cxn.isLoggedIn ()) {
	      try {
		Symbol currentMode = cxn.getUserMode();
		if (!(currentMode.equals(selMode)))
		  cxn.setUserMode(selMode);
	      } catch (G2AccessException ex) {
		Trace.exception(ex);
	      }
	    }
	  }
	}
      }
    }
  }

  class ModeListener extends TwConnectionAdapter {
    @Override
    public void loggedIn (TwConnectionEvent e) {
      //System.out.println("loggedIn <<"+e.getUserMode());
     
      /*
       * First check to see if the mode the user logged int with is 
       * a known mode for this connection. If not, add it to the 
       * Symbol array for the connection in the hashtable.
       */
      TwConnection cxn = (TwConnection)e.getSource();
      Symbol loginMode = e.getUserMode();
      updateUserMode(cxn, loginMode);
    }

    @Override
    public void userModeChanged (TwConnectionEvent e) {
      //System.out.println("userModeChanged <<"+e.getUserMode());
      TwConnection cxn = (TwConnection)e.getSource();
      Symbol newMode = e.getUserMode();
      updateUserMode(cxn, newMode);
    }

    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      modesForConnection.remove(e.getSource());
    }

  }


  class ContextListener implements ContextChangedListener {
    @Override
    public void currentConnectionChanged (ContextChangedEvent e) {
      // The ConnectionManager is responsible for generating ContextChangedEvents
      //System.out.println("currentConnectionChanged, calling setConnection0");
      //System.out.println("***** Source: "+e.getSource()+" *****");
      TwConnection cxn = (TwConnection) connectionMgr.getCurrentConnection ();
      
      try {
	setConnection0 (cxn);
      } catch (G2AccessException gae) {
	Trace.exception (gae);
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
    f.getContentPane().add (new UserModePanel (), BorderLayout.CENTER);
    f.pack ();
    f.setVisible (true);
  }
}

//this model will not select an item implicity, e.g., the first item added is not selected by default
class ComboBoxModel extends AbstractListModel implements MutableComboBoxModel{
  Vector objects;
  Object selectedObject;

  ComboBoxModel() {
    objects = new Vector();
  }

  @Override
  public void setSelectedItem(Object anObject) {
    selectedObject = anObject;
    fireContentsChanged(this, -1, -1);
  }

  @Override
  public Object getSelectedItem() {
    return selectedObject;
  }

  @Override
  public int getSize() {
    return objects.size();
  }

  @Override
  public Object getElementAt(int index) {
    if ( index >= 0 && index < objects.size() )
      return objects.elementAt(index);
    else
      return null;
  }

  @Override
  public void addElement(Object anObject) {
    objects.addElement(anObject);
    fireIntervalAdded(this,objects.size()-1, objects.size()-1);
  }

  @Override
  public void insertElementAt(Object anObject,int index) {
    objects.insertElementAt(anObject,index);
    fireIntervalAdded(this, index, index);
  }

  @Override
  public void removeElementAt(int index) {
    objects.removeElementAt(index);
    fireIntervalRemoved(this, index, index);
  }

  @Override
  public void removeElement(Object anObject) {
    int index = objects.indexOf(anObject);
    if ( index != -1 ) {
      removeElementAt(index);
    }
  }

}
