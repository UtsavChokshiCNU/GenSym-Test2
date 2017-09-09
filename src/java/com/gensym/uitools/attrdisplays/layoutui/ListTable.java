package com.gensym.uitools.attrdisplays.layoutui;

import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.JCheckBox;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.DefaultCellEditor;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableModel;
import java.awt.Dimension;
import java.util.Vector;
import java.awt.Component;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutTableModel;
import javax.swing.table.TableCellRenderer;

public class ListTable extends JTable {
  
  public ListTable(LayoutTableModel model)
  {
    super(model);
    setDefaultEditor(Boolean.class, new DefaultCellEditor(new JCheckBox()));
    setDefaultEditor(String.class, new DefaultCellEditor(new JTextField()));
    setColumnWidths();
    setAutoResizeMode(AUTO_RESIZE_ALL_COLUMNS);
  }

  @Override
  public void setModel(TableModel model) {
    super.setModel(model);
    setColumnWidths();
  }

  private void setColumnWidths() {
    getColumn("Name?").setMaxWidth(45);
    getColumn("Attribute").setWidth(200);
    setSize(new Dimension(196, 34));
  }

  public Object[] getSelectedRowValues(){
    int[] selectedIndicies = getSelectedRows();
    Vector returnValue = new Vector();
    for (int i=0; i<selectedIndicies.length; i++)
      returnValue.addElement(((LayoutTableModel)getModel()).getRowAt(selectedIndicies[i]));
    return returnValue.toArray();
  }

}
