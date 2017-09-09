package com.gensym.ntw.attrdisplays;

import java.util.Vector;
import com.gensym.ntw.util.PrettySymbol;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.VectorsNotSameLengthException;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutTableModel;
import com.gensym.uitools.attrdisplays.layoutui.ListTable;

public class G2LayoutTableModel extends LayoutTableModel {

  public static final Object ROW_KEY = "ROW-KEY";
  public static final Object ROW_LAYOUT = "ROW-LAYOUT";
  
  public G2LayoutTableModel() {
    super();
  }

  public G2LayoutTableModel(Vector layoutStructures) {
    super(layoutStructures);
  }

  public G2LayoutTableModel (LayoutStructure[] layoutArray) {
    super(layoutArray);
  }

  @Override
  public int getColumnCount() { return 2;}
  
  @Override
  public Object getValueAt(int row, int column){
    switch (column) {
    case 0: return ((LayoutStructure)layoutStructures.elementAt(row)).getRowKey();
	      // getAttributeValue(ROW_KEY, null);
    case 1: return ((LayoutStructure)layoutStructures.elementAt(row)).
	 getAttributeValue(ROW_LAYOUT, null);
    }
    return null;
  }
 
  @Override
  public void setValueAt(Object bool, int row, int column) {
    ((LayoutStructure)layoutStructures.elementAt(row)).
      setAttributeValue(ROW_LAYOUT, bool);
  }

  //DO NOT CALL THIS FOR NOW
  //BECAUSE WE HAVENT RESOLVED REMOVING THE FOLLOWING
  //else
  //    layoutStructures.addElement(createLayoutStructure(row));
  public void addRow(Object row) {
    if (row instanceof LayoutStructure)
      layoutStructures.addElement(row);
    fireTableDataChanged();
  }

  @Override
  public String getColumnName(int column) {
    switch (column) {
    case 0: return "Attribute";
    case 1: return "Name?";
    }
    return "";
  }
  @Override
  public Class getColumnClass(int column) {
    switch (column) {
    case 0: return PrettySymbol.class;
    case 1: return Boolean.class;
    }
    return super.getColumnClass(column);
  }

  @Override
  public boolean isCellEditable(int row, int col)
  {
    return (col == 1);
  }

}
