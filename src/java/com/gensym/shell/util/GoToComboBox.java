 /*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 GoToComboBox.java
 *
 */
package com.gensym.shell.util;

import java.awt.Font;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JComboBox;
import javax.swing.ComboBoxEditor;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.dlg.ErrorDialog;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import java.util.Enumeration;

public class GoToComboBox extends JComboBox 
{
  private static final int WKSP = 0;
  private static final int ITEM = 1;
  private static final Symbol ITEM_ = Symbol.intern("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern("GO-TO-ITEM");
  private TwAccess connection;
  private ContextChangedAdapter contextChangedListener;

  /**
   * Creates a combo box which uses its current text as the name of
   * an item to go to in the current connection.
   */
  public GoToComboBox() {
    this((TwAccess)null);
  }

  /**
   * Creates a combo box which uses its current text as the name of
   * an item to go to in the current connection.
   * @param connection the connection to set as the current connection.
   */  
  public GoToComboBox(TwAccess connection) {
    setConnection(connection);
    setToolTipText("Go To");
    setFont(new Font("Arial", Font.PLAIN, 12));
    setPreferredSize(new Dimension(140, 20));
    setEditable(true);
    setEnabled(false);
    addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
        GoToComboBox gtcb = (GoToComboBox)e.getSource();
	gtcb.goToItem();
      } 
    });     
  }

  /**
   * Creates a combo box which uses its current text as the name of
   * an item to go to in the current connection.
   * @param connectionManager a connectionManager from which to 
   * determine the current connection.
   */
  public GoToComboBox(ConnectionManager connectionManager) {
    this(connectionManager.getCurrentConnection());    
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);    
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }

  /**
   * Sets the current connection to be used when going to an item.
   * @param connection the <code>TwAccess</code> to use as the 
   * current connection.
   */
  public void setConnection(TwAccess connection){
    this.connection = connection;
    setEnabled(connection != null);
  }

  private void goToItem() {
    String arg = (String)getSelectedItem();
    arg = arg.trim();
    if (arg.equals("")) return;
    Symbol name = Symbol.intern(arg.toUpperCase());
    try {
      Item item = connection.getUniqueNamedItem(ITEM_, name);
      Item [] items = getWorkspaceAndItemOnWksp(item);
      if (items != null) {
	goToItem(items[ITEM], (KbWorkspace)items[WKSP]);
	removeItem(arg);
	insertItemAt(arg, 0);
	ComboBoxEditor cbe = (ComboBoxEditor)getEditor();      
	cbe.setItem(arg);
      } else
	new ErrorDialog(null,"Can not go to item", false,
			name+" exists, but is not on a workspace.",
			null).setVisible(true);
    } catch (G2AccessException g2ae) {
      new ErrorDialog(null,"Error", false, g2ae.getMessage(), null).setVisible(true);
    }
  }

  private static void goToItem(Item item, KbWorkspace wksp)
       throws G2AccessException
  {
    if (wksp != null){
      Structure particulars = new Structure();
      if (!(item instanceof com.gensym.classes.Connection)) {
	//show doesn't work well with connections(6/12/99)
	particulars.setAttributeValue(ITEM_, item);	
	particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
      }
      wksp.show(particulars);
    }   
  }

  private static Item[] getWorkspaceAndItemOnWksp(Item item)
       throws G2AccessException
  {
    Sequence containment = item.getContainmentHierarchy();
    containment.insertElementAt(item, 0);
    Enumeration items = containment.elements();
    Item itemOnWksp = item;
    while (items.hasMoreElements()){
      Item itm = (Item)items.nextElement();
      if (itm instanceof KbWorkspace){
	Item[] itms = new Item[2];
	itms[WKSP] = itm;
	itms[ITEM] = itemOnWksp;
	return itms;
      }
      else itemOnWksp = itm;
    }
    return null;
  }

  /**
   * @undocumented
   */
  @Override
  public void setEnabled(boolean enabled) {
    super.setEnabled(enabled);
    if (!enabled) {
      ComboBoxEditor cbe = (ComboBoxEditor)getEditor();      
      cbe.setItem("  ");
    } 
  }
  
}


