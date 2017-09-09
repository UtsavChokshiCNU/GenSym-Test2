package com.gensym.beaneditor;

import java.awt.Frame;
import java.awt.BorderLayout;
import java.awt.Dimension;

import java.awt.Component;
import java.awt.Color;
import javax.swing.JTable;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.DefaultTableColumnModel;
import javax.swing.table.DefaultTableCellRenderer;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

public class MultiColumnSelectionDialog extends StandardDialog{

  /**
   * Constant to indicate that there be no initial
   * element selected in the dialog.
   */
  public static final int NO_SELECTION = -1;

  private boolean requireSelection;
  private MultiColumnPanel multiColumnPanel;

  //allowMultipleSelection, initialSelection, and requireSelection not yet
  //implemented

  public MultiColumnSelectionDialog(Frame frame, String title, boolean isModal,
				    String prompt, String[] columnLabels,
				    Object[] initialValues, 
				    boolean allowMultipleSelection,
				    int initialSelection,
				    boolean requireSelection,
				    StandardDialogClient client){
    super(frame, title, isModal, new String[] {OK_LABEL, CANCEL_LABEL},
          new int[] {OK, CANCEL}, 
	  new MultiColumnPanel(prompt, columnLabels, initialValues, allowMultipleSelection,
			       initialSelection), 
	  client);
    this.requireSelection = requireSelection;
    multiColumnPanel = (MultiColumnPanel)getDialogComponent();
    setSize(getPreferredSize().width, 300);
  }


  /**
   * Retrieves the result of a single selection dialog
   * @return the index of the selected item in the list, if
   *    one exists, -1 otherwise
   */
  public int getResult (){
    return multiColumnPanel.getResult();
  }

  /**
   * Retrieves the results of a multiple selection dialog
   * @return an integer array of length >= 0 containing
   *    the indices of the selected items in the list
   */
  public int[] getResults (){
    return multiColumnPanel.getResults();
  }
}

class MultiColumnPanel extends JPanel{

  JTable table;

  MultiColumnPanel(String prompt, String[] labels, Object[] initialValues, 
		   boolean allowMultipleSelection, 
		   int initialSelection){
    setLayout (new BorderLayout (0, 5));

    if (prompt != null)
      add (new JLabel (prompt, SwingConstants.LEFT), BorderLayout.NORTH);

    table = new JTable(new MultiColumnTableModel(labels, initialValues));
    table.setDefaultRenderer(Object.class, new NoFocusHighlightTableCellRenderer());
    JScrollPane scrollpane = new JScrollPane(table);
    add (scrollpane, BorderLayout.CENTER);
  }

  int getResult (){
    return table.getSelectedRow();
  }
  
  int[] getResults (){
    return table.getSelectedRows();
  }

  class MultiColumnTableModel extends AbstractTableModel{
    private Object[] data;
    private String[] labels;

    public MultiColumnTableModel(String[] labels, Object[] data){
      this.data = data;
      this.labels = labels;
    }
    
    @Override
    public int getColumnCount(){
      return data.length;
    }
    
    @Override
    public String getColumnName(int column){
      return labels[column];
    }
    
    @Override
    public Class getColumnClass(int column){
      return String.class;
    }
    
    @Override
    public boolean isCellEditable(int row, int col) {
      return false;
    }
    
    @Override
    public int getRowCount(){
      String[] column = (String[])data[0];
      return column.length;
    }
    
    @Override
    public Object getValueAt(int row, int column){
      String[] aColumn = (String[])data[column];
      return aColumn[row];
    }  
    
    @Override
    public void setValueAt(Object aValue, int row, int column){
      String[] aColumn = (String[])data[column];
      aColumn[row] = (String)aValue;
    }   
  }


  class NoFocusHighlightTableCellRenderer extends DefaultTableCellRenderer{
    
    private Color unselectedForeground; 
    private Color unselectedBackground; 
    
    @Override
    public void setForeground(Color c) {
      super.setForeground(c); 
      unselectedForeground = c; 
    }
    
    @Override
    public void setBackground(Color c) {
      super.setBackground(c); 
      unselectedBackground = c; 
    }
    
    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, boolean hasFocus, 
						   int row, int column) {
      
      if (isSelected) {
	super.setForeground(table.getSelectionForeground());
	super.setBackground(table.getSelectionBackground());
      }
      else {
	super.setForeground((unselectedForeground != null) ? unselectedForeground 
			    : table.getForeground());
	super.setBackground((unselectedBackground != null) ? unselectedBackground 
			    : table.getBackground());
      }
      
      setFont(table.getFont());
      setBorder(noFocusBorder);
      
      setValue(value); 
      
      return this;
    }
  }
  
}






