package com.gensym.gcg;

import java.awt.Component;
import java.awt.Container;
import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import com.gensym.classes.Item;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.dlgruntime.DialogCommandListener;
import com.gensym.dlgruntime.DialogCommandEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import java.awt.Color;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableCellEditor;
import javax.swing.JLabel;
import javax.swing.JComponent;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import com.gensym.uitools.utils.FontUtil;


public class GeneratedAttributeTable extends JTabbedPane implements ItemListener, DialogCommandListener, G2ConnectionListener{

  static final int DEFAULT_ROW_HEIGHT = 24;
  private static final int Y_INSET = 3;
  private static final int X_INSET = 3;
  private static final Color DEFAULT_NOTES_COLOR = java.awt.Color.red;  

  private TwAccess connection;
  private Item item;
  private DialogCommand dialogCommand;
  
  private boolean hasNotesPanel = false;
  private String notesTabTitle = null;
  private Component notesPanel = null;

  public GeneratedAttributeTable(TwAccess connection,
				 ItemProxy itemProxy,
				 DialogCommand dialogCommand,
				 G2AttributeGroup[] groups,
				 boolean live) throws G2AccessException
  {
    this.connection = connection;
    this.item = itemProxy.getProxy();
    this.dialogCommand = dialogCommand;
    dialogCommand.addDialogCommandListener(this);
    
    try{
      itemProxy.download();
    }
    catch(NoSuchAttributeException ex){
      Trace.exception(ex);
    }

    for (int i=0; i<groups.length; i++){
      G2AttributeGroup group = groups[i];
      String label = group.getName();
      Color labelColor = null;
      G2AttributeEditor[] editorList = group.getEditors();
      int numberOfEditors = editorList.length;      
      Component page=null;JAttributeTable table=null;

      boolean okToAddPanel = (numberOfEditors > 0);
      for (int j=0; j<numberOfEditors; j++){
	G2AttributeEditor g2AttributeEditor = editorList[j];
	Component editorLabel = g2AttributeEditor.getLabel();
	AttributeEditor editor = g2AttributeEditor.getEditor();
	if (editor instanceof Component){
	  if (page == null) {
	    if (numberOfEditors > 1) {
	      table = new JAttributeTable(numberOfEditors>1?2:1);
	      page = new JScrollPane(table);
	    } else {
	      page = createCompleteEditor((Component)editor);
	    }
	  }
	  if (table != null)
	    table.addRow(editorLabel, editor);	  
	  if (editor instanceof NotesTextArea){
	    NotesTextArea notesEditor = (NotesTextArea)editor;
	    notesEditor.setNotesDisplayer(new OptionalComponentDisplayer() {
	      @Override
	      public void hideComponent(){
		if (hasNotesPanel){
		  hasNotesPanel = false;
		  int index = indexOfComponent(notesPanel);
		  if (index >= 0)
		    removeTabAt(index);
		}
	      }
	      @Override
	      public void showComponent(){
		if (!hasNotesPanel){
		  hasNotesPanel = true;
		  addTab(notesTabTitle, notesPanel);
		  setForegroundAt(indexOfComponent(notesPanel),
				  DEFAULT_NOTES_COLOR);
		}
	      }
	    });
	    notesTabTitle = label;
	    notesPanel = page;
	    hasNotesPanel = notesEditor.isInteresting();;
	    okToAddPanel = hasNotesPanel;
	    labelColor = DEFAULT_NOTES_COLOR;
	  }
	}
      }
      if (okToAddPanel) {
	addTab(label, page);
	if (labelColor != null)
	  setForegroundAt(indexOfComponent(page), labelColor);
      }
    }
    
    if (live){
      try{
	item.addItemListener(this);
      } catch(G2AccessException e){
	Trace.exception(e);
      }
    }
  }

  static Component createCompleteEditor(Component editor) {
    editor.setFont(FontUtil.sanserifPlain11);
    Component completeEditor = editor;
    if (editor instanceof EditedBySubDialog) {
	JPanel panel = new JPanel();
	panel.setLayout(new BorderLayout());
	panel.add((Component)editor, BorderLayout.CENTER);
	panel.add(new RollOverSubDialogLauncher((EditedBySubDialog)editor), BorderLayout.EAST);
	completeEditor = panel;
    }
    return completeEditor;
  }
  
  class CellEditor extends AbstractCellEditor
  implements TableCellEditor {
    private JAttributeTableModel model;
    public CellEditor(JAttributeTableModel model) {
      this.model = model;
    }
    @Override
    public Component getTableCellEditorComponent(JTable table,
						 Object value,
						 boolean isSelected,
						 int row,
						 int column)
    {
      if (column == 0 && !model.labels.isEmpty())
	return null;
      else 
	return (Component)model.editors.elementAt(row);
    }
    @Override
    public Object getCellEditorValue() {
      return null;
    }    
  }
  
  class JAttributeTableModel extends AbstractTableModel
  implements TableCellRenderer
  {
    int columnCount = 2;
    Vector labels=new Vector();
    Vector editors=new Vector();
    JAttributeTableModel(int columnCount) {
      this.columnCount = columnCount;
    }
    @Override
    public int getRowCount() {
      return editors.size();
    }
    @Override
    public int getColumnCount() {
      return columnCount;
    }
    @Override
    public Object getValueAt(int row, int column) {
      return null;
    }    
    public void addRow(AttributeEditor editor) {
      editors.addElement(createCompleteEditor((Component)editor));
      fireTableDataChanged();            
    }
    public void addRow(Component label, AttributeEditor editor) {
      if (label != null)
	labels.addElement(label);
      addRow(editor);
    }

    @Override
    public boolean isCellEditable(int row, int col) {
      return col == 1 || columnCount == 1;
    }
    @Override
    public Component getTableCellRendererComponent(JTable table,
						   Object value,
						   boolean isSelected,
						   boolean hasFocus,
						   int row,
						   int column)
    {
      if (column == 0 && !labels.isEmpty())
	return (Component)labels.elementAt(row);
      else
	return (Component)editors.elementAt(row);
    }        
  }

  
  class JAttributeTable extends JTable {
    private JAttributeTableModel model;
    private int columnCount;
    JAttributeTable(int columnCount) {
      setPreferredScrollableViewportSize(new java.awt.Dimension(350,450));
      this.columnCount = columnCount;
      setTableHeader(null);
      setRowHeight(DEFAULT_ROW_HEIGHT);
      model = new JAttributeTableModel(columnCount);
      setModel(model);
      setDefaultRenderer(Object.class, model);
      setDefaultEditor(Object.class, new CellEditor(model));
    }

    public void addRow(Component label, AttributeEditor editor) {
      model.addRow(label, editor);
      //int lastRowIndex = model.getRowCount()-1;	      
      //setRowHeight(lastRowIndex, 55);//((Component)editor).getPreferredSize().height);
    }
  }
  
  @Override
  public void receivedInitialValues (ItemEvent e){}
  @Override
  public void itemModified(ItemEvent e){
    repaint();
  }
  @Override
  public void itemDeleted (ItemEvent e){
    disablePanel();
    cleanup();
  }

  private void disablePanel(){
    for (int i=0; i<getTabCount(); i++){
      Container c = (Container)getComponentAt(i);
      Component[] components = c.getComponents();
      for (int j=0; j<components.length; j++)
	components[j].setEnabled(false);
    }
  }
  
  private void cleanup(){
    if (item == null) return;
    try{
      item.removeItemListener(this);
    } catch(G2AccessException ex){
      Trace.exception(ex);
    }
    item = null;
    dialogCommand.removeDialogCommandListener(this);
    dialogCommand = null;
  }
  
  @Override
  public void dialogChangesFlushed (DialogCommandEvent event){}
  @Override
  public void dialogLaunched(DialogCommandEvent event){}
  @Override
  public void dialogShutdown(DialogCommandEvent event){
    cleanup();
  }

  @Override
  public void g2IsPaused(G2ConnectionEvent event){}
  @Override
  public void g2IsResumed(G2ConnectionEvent event){}
  @Override
  public void g2IsReset(G2ConnectionEvent event){}
  @Override
  public void g2IsStarted(G2ConnectionEvent event){}
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent event){}
  @Override
  public void g2MessageReceived(G2ConnectionEvent event){}
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event){}
  @Override
  public void readBlockage(G2ConnectionEvent event){}
  @Override
  public void writeBlockage(G2ConnectionEvent event){}
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent event){
    disablePanel();
    cleanup();
  }
}
  class RollOverSubDialogLauncher extends SubDialogLauncher {
    RollOverSubDialogLauncher(EditedBySubDialog editor) {
      super(editor);
      setRolloverEnabled(true);
    }
    @Override
    public void reshape(int x, int y, int w, int h) {
      super.reshape(x, y, w, GeneratedAttributeTable.DEFAULT_ROW_HEIGHT);
    }
    @Override
    protected void paintBorder(java.awt.Graphics g) {
      if (getModel().isRollover() || getModel().isPressed())
	super.paintBorder(g);
    }      
  }


//Replace w/ javax.swing.AbstractCellEditor when we move to jdk1.3 or greater
 abstract class AbstractCellEditor implements javax.swing.CellEditor, java.io.Serializable {
    protected javax.swing.event.EventListenerList listenerList = new javax.swing.event.EventListenerList();
    transient protected javax.swing.event.ChangeEvent changeEvent = null;
    @Override
    public boolean isCellEditable(java.util.EventObject e) { 
	return true; 
    } 
    @Override
    public boolean shouldSelectCell(java.util.EventObject anEvent) { 
	return true; 
    }
    @Override
    public boolean stopCellEditing() { 
	fireEditingStopped(); 
	return true;
    }
    @Override
    public void  cancelCellEditing() { 
	fireEditingCanceled(); 
    }
    @Override
    public void addCellEditorListener(javax.swing.event.CellEditorListener l) {
	listenerList.add(javax.swing.event.CellEditorListener.class, l);
    }
    @Override
    public void removeCellEditorListener(javax.swing.event.CellEditorListener l) {
	listenerList.remove(javax.swing.event.CellEditorListener.class, l);
    }
    protected void fireEditingStopped() {
	Object[] listeners = listenerList.getListenerList();
	for (int i = listeners.length-2; i>=0; i-=2) {
	    if (listeners[i]==javax.swing.event.CellEditorListener.class) {
		if (changeEvent == null)
		    changeEvent = new javax.swing.event.ChangeEvent(this);
		((javax.swing.event.CellEditorListener)listeners[i+1]).editingStopped(changeEvent);
	    }	       
	}
    }
    protected void fireEditingCanceled() {
	Object[] listeners = listenerList.getListenerList();
	for (int i = listeners.length-2; i>=0; i-=2) {
	    if (listeners[i]==javax.swing.event.CellEditorListener.class) {
		if (changeEvent == null)
		    changeEvent = new javax.swing.event.ChangeEvent(this);
		((javax.swing.event.CellEditorListener)listeners[i+1]).editingCanceled(changeEvent);
	    }	       
	}
    }
}
