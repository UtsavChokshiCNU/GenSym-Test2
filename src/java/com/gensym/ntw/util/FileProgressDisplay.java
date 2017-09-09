package com.gensym.ntw.util;

import com.gensym.uitools.utils.StatusBar;
import javax.swing.JDialog;
import javax.swing.JPanel;
import java.awt.Frame;
import com.gensym.util.Symbol;
import java.awt.BorderLayout;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.JScrollPane;
import java.util.Vector;
import javax.swing.table.TableColumnModel;
import java.awt.Window;
import java.awt.Rectangle;
import javax.swing.table.TableCellRenderer;
import java.awt.Font;
import java.awt.Color;
import java.awt.Component;
import javax.swing.JLabel;
import java.awt.FlowLayout;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Cursor;

public class FileProgressDisplay extends JDialog
implements FileProgressListener
{
  private StatusBar statusBar;
  private String prefix = "";
  private JTable table;
  private FileProgressTableModel tableModel;
  private static final String DISMISS = "Dismiss";
  //private JButton dismissButton;
  private static final Symbol NO_MODULE_ = Symbol.intern ("NO-MODULE");
  private Vector modules = new Vector();  
  
  public FileProgressDisplay(Frame frame) {
    super(frame);
    JPanel mainPanel = new JPanel();
    mainPanel.setLayout(new BorderLayout());
    statusBar = new StatusBar(1);
    mainPanel.add(statusBar, "South");
    tableModel = new FileProgressTableModel();
    table = new JTable(tableModel);
    table.setCellSelectionEnabled(false);
    table.setRowSelectionAllowed(false);
    table.setBackground(java.awt.Color.lightGray);
    java.awt.Font font = com.gensym.uitools.utils.FontUtil.sanserifPlain11;
    table.setFont(font);
    setFont(font);
    table.getTableHeader().setFont(font);
    table.setDefaultRenderer(Object.class, new FileProgressTableCellRenderer());
    initColumnWidths(new int[] {80,180,140,80});
    mainPanel.add(new JScrollPane(table), "Center");
    JPanel buttonPanel = new JPanel();
    buttonPanel.setLayout(new FlowLayout());
    //dismissButton = new JButton(DISMISS);
    //dismissButton.setEnabled(false);
    /*dismissButton.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent ae) {
	setVisible(false);
      }
    });*/
    //dismissButton.setFont(font);
    //buttonPanel.add(dismissButton);
    //JPanel outerPanel = new JPanel();
    //outerPanel.setLayout(new BorderLayout());
    //outerPanel.add(buttonPanel, "South");
    //outerPanel.add(mainPanel, "Center");
    //getContentPane().add(outerPanel);
    getContentPane().add(mainPanel);
    centerWindowInWindow(this, frame, 500, 210);
    //setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
  }
  
  private static void centerWindowInWindow(Window child,
					   Window parent,
					   int childWidth,
					   int childHeight) {
    Rectangle bnds = parent.getBounds();
    int x = bnds.x+bnds.width/2;
    int y = bnds.y+bnds.height/2;
    child.setBounds(x-childWidth/2,y-childHeight/2,
		    childWidth, childHeight);
  }
  
  private void initColumnWidths(int[] preferredColumnWidths) {
    TableColumnModel columnModel = table.getColumnModel();
    for (int i=0;i<preferredColumnWidths.length;i++)  
      columnModel.getColumn(i).setPreferredWidth(preferredColumnWidths[i]);
  }
  
  public void clear() {
    //dismissButton.setEnabled(false);
    tableModel.removeAll();
    tableModel.update();
  }
  
  public void displaySingleMessage(String message) {
    statusBar.setStatus(message, 0);
    setVisible(true);
  }

  public void setPrefix(String prefix) {
    this.prefix = prefix;
  }

  @Override
  public void setVisible(boolean visible) {
    super.setVisible(visible);
    if (visible)
      requestFocus();
  }

  @Override
  public void addFile(FileProgressEvent event) {
    statusBar.setStatus("Working...", 0);
    Symbol moduleName = event.getModuleName();
    if (moduleName == null)
      moduleName = NO_MODULE_;
    String fileName = event.getFileName();
    String status = event.getStatus().toString();
    int progress = event.getProgress();
    Symbol units = event.getUnitsForProgressThroughFile();
    String progressStatus = ""+progress;
    if (units != null)
      progressStatus+=" "+units.toString().toLowerCase();
    int percentDone = event.getPercentageDone();
    if (percentDone != 0)
      progressStatus += " ("+percentDone+"% done)";

    String[] newData = new String[] {moduleName.toString(),fileName,progressStatus,status};
    tableModel.setRowData(moduleName, newData);
    tableModel.update();    
    table.scrollRectToVisible(table.getCellRect(tableModel.getRowIndex(moduleName), 0, true));
    setVisible(true);    
  }

  @Override
  public void removeFile(FileProgressEvent event) {
    //dismissButton.setEnabled(true);
    statusBar.setStatus("Done", 0);
    setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
  }
  
}

class FileProgressTableModel extends AbstractTableModel
{
  private Vector columns, data;

  public FileProgressTableModel()
  {
    data = new Vector();
    columns = new Vector();
    columns.addElement("Module");
    columns.addElement("File Name");
    columns.addElement("Progress through file");    
    columns.addElement("Status");

  }

  private Vector keys = new Vector();

  public void setRowData(Symbol key, String[] newData)
  {
    int index = keys.indexOf(key);
    if (index == -1) {
      keys.addElement(key);
      data.addElement(newData);
    } else
      data.setElementAt(newData, index);
  }
  
  public int getRowIndex(Symbol key) {
    return keys.indexOf(key);
  }
  
  public boolean removeRow(int index)
  {
   data.removeElementAt(index);
   return true;
  }

  public void removeAll()
  {
    keys.removeAllElements();
    data.removeAllElements();
  }

  @Override
  public int getColumnCount()
  {
    return columns.size();
  }
  
  @Override
  public int getRowCount()
  {
    return data.size();
  }

  @Override
  public String getColumnName(int column) {
    return (String)columns.elementAt(column);
  }

  public void update() {
    fireTableDataChanged();
  }

  @Override
  public Object getValueAt(int row, int col) {
    String[] rowData = (String[])data.elementAt(row);
    return rowData[col];
  }

}

class FileProgressTableCellRenderer extends JLabel
implements TableCellRenderer
{
  public FileProgressTableCellRenderer() {
    super();
    setFont(com.gensym.uitools.utils.FontUtil.sanserifPlain11);
    setOpaque(true);
  }
  private static final String UNOPENED = "unopened";
  private static final String WRITING = "writing";  
  private static final String CLOSED = "closed";
  private static final String OPEN = "open";
  private final int STATUS_INDEX = 3;  
  @Override
  public Component getTableCellRendererComponent(JTable table,
						 Object value,
						 boolean isSelected,
						 boolean hasFocus,
						 int row,
						 int column){
    Color bgColor = table.getBackground();//color.lightGray;
    String status = (String)table.getModel().getValueAt(row,STATUS_INDEX);
    if (UNOPENED.equals(status))
      bgColor = Color.yellow;
    else if (WRITING.equals(status)||OPEN.equals(status))
      bgColor = Color.green;
    setBackground(bgColor);
    setForeground(table.getForeground());		
    if (value == null)
      value = "";
    setText(value.toString());
    return this;
  }
  
}


