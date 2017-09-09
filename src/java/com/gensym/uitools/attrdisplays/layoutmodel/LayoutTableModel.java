package com.gensym.uitools.attrdisplays.layoutmodel;

import java.util.Vector;
import javax.swing.table.AbstractTableModel;

public abstract class LayoutTableModel extends AbstractTableModel {
  protected Vector layoutStructures;

  public LayoutTableModel() {
    layoutStructures = new Vector();
  } 

  public LayoutTableModel(Vector layoutStructures) {
    this.layoutStructures = (Vector)layoutStructures.clone();
  }

  public LayoutTableModel(Object[] layoutStructureArray) {
    layoutStructures = new Vector();
    for (int i=0;i<layoutStructureArray.length;i++)
      layoutStructures.addElement(layoutStructureArray[i]);
  }

  @Override
  public abstract int getColumnCount() ;
  
  @Override
  public int getRowCount() { return layoutStructures.size();}

  @Override
  public abstract Object getValueAt(int row, int column);
 
  public Vector getLayouts() {
    return (Vector)layoutStructures.clone();
  }

  public void removeRow(Object row) {
    layoutStructures.removeElement(row);
  }

  public Object getRowAt(int index) {
    return layoutStructures.elementAt(index);
  }

}
