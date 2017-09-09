package com.gensym.editor.icon.core;

import javax.swing.table.AbstractTableModel;
import java.util.Vector;
import java.awt.Color;
import com.gensym.dlg.ErrorDialog;

public class VariableSimulationTableModel extends AbstractTableModel {
  Vector parameters = new Vector();
  Vector expressionKeys = new Vector();
  
  public VariableSimulationTableModel(Parameter[] parameters) {
    int count = parameters.length;
    for (int i=0;i<count;i++) {
      Parameter param = parameters[i];
      expressionKeys.addElement(param.getSimulationPreferenceKey());
      this.parameters.addElement(param);
    }
  }

  public void addRow(Parameter parameter, int index) {
    parameters.insertElementAt(parameter, index);
    expressionKeys.addElement(parameter.getSimulationPreferenceKey());
    fireTableDataChanged();
  }
  
  public boolean removeRow(Parameter parameter) {
    boolean changed = parameters.removeElement(parameter);
    if (changed) {
      int index = parameters.indexOf(parameter);    
      if (index > -1) expressionKeys.removeElementAt(index);
      fireTableDataChanged();
    }
    return changed;
  }
  
  @Override
  public String getColumnName(int column) {
    switch (column) {
    case 0:
      return "Parameter";
    case 1:
      return "Simulation Expression";
    }
    return "";
  }
  
  @Override
  public int getColumnCount() { return 2;}
  
  @Override
  public int getRowCount() { return parameters.size();}
  
  @Override
  public Object getValueAt(int row, int col) {
    switch (col) {
    case 0:
      return parameters.elementAt(row);
    case 1:
      return expressionKeys.elementAt(row);
    }
    return "none";
  }
  
  @Override
  public Class getColumnClass(int col)
  {
    switch (col) {
    case 0:
      return Parameter.class;
    case 1:
      return String.class;      
    }
    return super.getColumnClass(col);
  }
  
  @Override
  public boolean isCellEditable(int row, int col)
  {
    return col == 1;
  }

  @Override
  public void setValueAt(Object aValue, int row, int column) {
    if (column == 1) {
      expressionKeys.setElementAt((String)aValue,row);
    }
  }


  public Parameter[] getParameters() {
    Parameter[] params = new Parameter[parameters.size()];
    parameters.copyInto(params);
    return params;
  }
  
  public String[] getExpressionKeys() {
    String[] exps = new String[expressionKeys.size()];
    expressionKeys.copyInto(exps);
    return exps;    
  }
}
