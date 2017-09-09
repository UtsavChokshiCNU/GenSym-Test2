 /*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbMessageTableView.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Component;
import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.Frame;
import java.awt.Window;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Vector;
import java.util.Enumeration;
import javax.swing.JTable;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableCellEditor;
import javax.swing.event.CellEditorListener;
import javax.swing.event.ChangeEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Trace;
import com.gensym.ui.toolbar.ToolBar;
import com.gensym.ui.menu.CPopupMenu;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;
import javax.swing.SwingConstants;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.uitools.utils.StatusBar;
import com.gensym.message.Resource;

public abstract class KbMessageTableView extends Container{

  private static final Resource i18n = Resource.getBundle("com.gensym.ntw.util.CommandShortResource");
  private static boolean useIndividualScrollBars;  
  private static final ColumnDefinition[] columns = new ColumnDefinition[]{
    new ColumnDefinition(null, String.class, useIndividualScrollBars)};

  protected static int NUMBER = 2, TIME = 3;
  protected TableView tableView;
  protected StatusBar statusBar;
  protected ToolBar toolBar;
  protected TwAccess connection;
  protected KbMessageListener kbMessageListener;
  private G2ConnectionListener connectionListener;
  private DeleteCommand deleteCommand;
  private JTextField rowHeightField;
  ViewMessageCommand viewMessageCommand;
  static RepresentationConstraints menuConstraints = 
  new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				SwingConstants.LEFT, 
				SwingConstants.CENTER, 
				SwingConstants.RIGHT, 
				SwingConstants.CENTER);      
  protected static CPopupMenu popup;
  private int initialRowHeight = 5*16;

  KbMessageTableView(TwAccess connection, 
			    KbMessageListener kbMessageListener) throws G2AccessException{
    tableView = new TableView(columns);
    statusBar = new StatusBar(4, true);
    tableView.setStatusBar(statusBar);
    JTable table = tableView.getTable();
    if (useIndividualScrollBars) {
      table.setDefaultRenderer(Object.class, new MultiLineTableViewCellRenderer4());
      table.setDefaultEditor(Object.class, new MultiLineTableViewCellRenderer4());
    } else {
      table.setDefaultRenderer(Object.class, new MultiLineTableViewCellRenderer2());
    }
    setRowHeight(initialRowHeight);
    setLayout(new BorderLayout());
    add(tableView, BorderLayout.CENTER);
    toolBar = new ToolBar();
    deleteCommand = new DeleteCommand(this);
    viewMessageCommand = new ViewMessageCommand(this);
    toolBar.add(deleteCommand);
    toolBar.add(viewMessageCommand);
    add(toolBar, BorderLayout.NORTH);

    setupStatusBar();
    this.connection = connection;
    this.kbMessageListener = kbMessageListener;
    connectionListener = new ConnectionAdapter();
    connection.addG2ConnectionListener(connectionListener);

    popup = new CPopupMenu();
    popup.add(deleteCommand,menuConstraints);
    popup.add(viewMessageCommand,menuConstraints);
  }

  void setupStatusBar() {
    JTextField rowLabel = statusBar.getTextField(0);
    GridBagConstraints gbc = new GridBagConstraints();
    gbc.anchor = GridBagConstraints.EAST;
    rowLabel.setBorder(null);
    rowLabel.setText(" "+i18n.getString("rowheight"));
    statusBar.setConstraints(0, gbc);
    rowHeightField = statusBar.getTextField(1);
    rowHeightField.setBackground(Color.white);
    rowHeightField.setEditable(true);
    rowHeightField.setText(""+initialRowHeight);
    rowHeightField.addActionListener(new FieldListener());
  }
  
  public void setRowHeight(int height) {
    tableView.getTable().setRowHeight(height);
  }
  
  public void dispose() throws G2AccessException{
    if (connection != null) { // dispose might get called multiple times
      connection.removeG2ConnectionListener(connectionListener);
      connection.getKb().removeKbMessageListener(kbMessageListener);
      connection = null; // help GC
    }
  }

  static void popupMenuIfNecessary(MouseEvent event, JTable table){
    if (event.isPopupTrigger()){
      int x = event.getX(), y = event.getY();
      Point point = new Point(x, y);
      int rowIndex = table.rowAtPoint(point);

      table.setRowSelectionInterval(rowIndex, rowIndex);
      popup.show((Component)event.getSource(), x, y);
    }
  }

  static String getMessageNumber(String message) {
    int timeStart = message.indexOf("  ");
    return (message.substring(0, timeStart));
  }

  static String getMessageTime(String message) {
    int timeStart = message.indexOf("  ");
    int timeEnd = message.indexOf("  ",timeStart+3);
    return (message.substring(timeStart, timeEnd));
  }
  /**
   * @undocumented Used by ViewCommands
   */
  public TwAccess getConnection () {
    return connection;
  }

  public void setPromptBeforeDelete(boolean prompt){
    deleteCommand.setPromptBeforeDelete(prompt);
  }

  TableView getTableView(){
    return tableView;
  }

  Window getParentWindow(){
    return getParentWindow(this);
  }

  Frame getParentFrame(Component c){
    if (c == null) return null;
    if (c instanceof Frame) return (Frame)c;
    Component parent = c.getParent();
    if (parent instanceof Frame) return (Frame)parent;
    else return getParentFrame(parent);
  }

  private Window getParentWindow(Component c){
    if (c == null) return null;
    if (c instanceof Window) return (Window)c;
    Component parent = c.getParent();
    if (parent instanceof Window) return (Window)parent;
    else return getParentWindow(parent);
  }

  class FieldListener implements ActionListener {
    @Override
    public void actionPerformed(ActionEvent e) {
      setRowHeight(new Integer(((JTextField)e.getSource()).getText()).intValue());
    }
  }
  
  class ConnectionAdapter extends G2ConnectionAdapter{
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent event){
      try {
	dispose ();
      } catch (G2AccessException g2ae) {
	Trace.exception (g2ae);
      }
    }
  }

  public class MultiLineTableViewCellRenderer extends Component implements TableCellRenderer{

    private TextCell textCell;

    public MultiLineTableViewCellRenderer() {
      //textCell's width, text, and colors get set in getTableCellRendererComponent
      textCell = new TextCell(20, "", 
			      new TextStyle(tableView.getTable().getFont(), 0, 0, 1, true), 
			      Color.white, Color.black, 0, null);
      textCell.setDrawBackground(true);
    }

    @Override
    public Dimension getPreferredSize(){
      return new Dimension(textCell.getWidth(), textCell.getHeight());
    }
    
    @Override
    public void paint (Graphics g){
      textCell.draw(g, 0, 0);
    } 
    
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, boolean hasFocus, 
						   int row, int column){
      textCell.setWidth(table.getColumnModel().getColumn(column).getWidth());
      setValue(value); 
      if (isSelected) {
	textCell.setTextColor(table.getSelectionForeground());
	textCell.setBackgroundColor(table.getSelectionBackground());
      }
      else {
	TableViewMessage msg = tableView.getTableViewMessage(row);
	if (msg != null){
	  textCell.setTextColor(msg.getForegroundColor());
	  textCell.setBackgroundColor(msg.getBackgroundColor());
	}
      }
      textCell.format(this);
      textCell.setHeight(table.getRowHeight());
      return this;
    }
    
    protected void setValue(Object value) {
      textCell.setText((value == null) ? "" : value.toString());
    }
  }

  public class MultiLineTableViewCellRenderer2 extends JTextArea implements TableCellRenderer{
    
    public MultiLineTableViewCellRenderer2() {
      super();
      setLineWrap(true);
      setWrapStyleWord(true);
      setFont(tableView.getTable().getFont());
    }
    
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, boolean hasFocus, 
						   int row, int column){
      setColumns(table.getColumnModel().getColumn(column).getWidth()/getColumnWidth());
      setValue(value); 
      if (isSelected) {
	setForeground(table.getSelectionForeground());
	setBackground(table.getSelectionBackground());
      }
      else {
	TableViewMessage msg = tableView.getTableViewMessage(row);
	if (msg != null){
	  setForeground(msg.getForegroundColor());
	  setBackground(msg.getBackgroundColor());
	}
      }
      
      return this;
    }
    
    protected void setValue(Object value) {
      setText((value == null) ? "" : value.toString());
    } 
  }

  public class MultiLineTableViewCellRenderer3 extends JScrollPane implements TableCellRenderer{
      
    private JTextArea textArea;

    public MultiLineTableViewCellRenderer3() {
      super();
      textArea = new JTextArea();
      textArea.setEditable(false);
      textArea.setLineWrap(true);
      textArea.setWrapStyleWord(true);
      textArea.setFont(tableView.getTable().getFont());
      setViewportView(textArea);
    }
    
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, boolean hasFocus, 
						   int row, int column){
      //textArea.setColumns(table.getColumnModel().getColumn(column).getWidth()/(textArea.getColumnWidth()));
      setValue(value); 
      if (isSelected) {
	textArea.setForeground(table.getSelectionForeground());
	textArea.setBackground(table.getSelectionBackground());
      }
      else {
	TableViewMessage msg = tableView.getTableViewMessage(row);
	if (msg != null){
	  textArea.setForeground(msg.getForegroundColor());
	  textArea.setBackground(msg.getBackgroundColor());
	}
      }

      return this;
    }
    
    protected void setValue(Object value) {
      textArea.setText((value == null) ? "" : value.toString());
    } 
  }

  public class MultiLineTableViewCellRenderer4 extends JScrollPane implements TableCellRenderer, 
    TableCellEditor{

    private JTextArea textArea;

    private Vector listeners = new Vector();
    
    public MultiLineTableViewCellRenderer4() {
      super();
      textArea = new JTextArea();
      textArea.setEditable(false);
      textArea.setLineWrap(true);
      textArea.setWrapStyleWord(true);
      textArea.setFont(tableView.getTable().getFont());
      setViewportView(textArea);
    }
    
    @Override
    public Component getTableCellEditorComponent(JTable table, Object value, boolean isSelected,
						 int row, int column){
      return getTableCellRendererComponent(table, value, isSelected, true, row, column);
    }

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, boolean hasFocus, 
						   int row, int column){
      setValue(value); 
      if (isSelected) {
	textArea.setForeground(table.getSelectionForeground());
	textArea.setBackground(table.getSelectionBackground());
      }
      else {
	TableViewMessage msg = tableView.getTableViewMessage(row);
	if (msg != null){
	  textArea.setForeground(msg.getForegroundColor());
	  textArea.setBackground(msg.getBackgroundColor());
	}
      }

      return this;
    }
    
    protected void setValue(Object value) {
      textArea.setText((value == null) ? "" : value.toString());
    } 
 
    @Override
    public void addCellEditorListener(CellEditorListener l){
      listeners.addElement(l);
    }

    @Override
    public void removeCellEditorListener(CellEditorListener l){
      listeners.removeElement(l);
    }

    @Override
    public Object getCellEditorValue(){
      return textArea.getText();
    }

    @Override
    public boolean isCellEditable(java.util.EventObject anEvent){
      return (anEvent instanceof MouseEvent  && ((MouseEvent)anEvent).getClickCount() >= 2);
    }

    @Override
    public boolean shouldSelectCell(java.util.EventObject anEvent){
      return isCellEditable(anEvent);
    }

    @Override
    public void cancelCellEditing(){
      dispatchCancelEvent();
    }

    private void dispatchCancelEvent(){
      ChangeEvent e = new ChangeEvent(this);
      Vector l = (Vector)listeners.clone();
      Enumeration dispatchList = l.elements();
      while (dispatchList.hasMoreElements()){
	CellEditorListener listener = ((CellEditorListener)dispatchList.nextElement());
	listener.editingCanceled(e);
      }
    }

    @Override
    public boolean stopCellEditing(){
      dispatchStopEvent();
      return true;
    }

    private void dispatchStopEvent(){
      ChangeEvent e = new ChangeEvent(this);
      Vector l = (Vector)listeners.clone();
      Enumeration dispatchList = l.elements();
      while (dispatchList.hasMoreElements()){
	CellEditorListener listener = ((CellEditorListener)dispatchList.nextElement());
	listener.editingStopped(e);
      }
    }
  }

}
