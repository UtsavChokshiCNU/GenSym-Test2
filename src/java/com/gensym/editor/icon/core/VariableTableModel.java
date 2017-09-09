package com.gensym.editor.icon.core;

import javax.swing.table.AbstractTableModel;
import com.gensym.editor.icon.core.Parameter;
import java.util.Vector;
import java.awt.Color;
import com.gensym.dlg.ErrorDialog;

public abstract class VariableTableModel extends AbstractTableModel {
  Parameter[] parameters;
  private Vector params = new Vector();
  
  public VariableTableModel(Parameter[] parameters) {
    for (int i=0;i<parameters.length;i++) {
      Parameter param = parameters[i];
      params.addElement(param);
    }
  }

  @Override
  public String getColumnName(int column) {
    switch (column) {
    case 0:
      return "Name";
    case 1:
      return "Type";
    case 2:
      return "Value";
    }
    return "";
  }
  
  @Override
  public int getColumnCount() { return 3;}
  
  @Override
  public int getRowCount() { return params.size();}
  
  @Override
  public Object getValueAt(int row, int col) {
    Parameter param = (Parameter)params.elementAt(row);
    switch (col) {
    case 0:
      return param.getName();
    case 1:
      return param.getType();
    case 2:
      return param.getDefaultValue();
    }
    return "none";
  }

  public void addRow(Parameter parameter, int index) {
    params.insertElementAt(parameter, index);
    fireTableDataChanged();
  }
  
  public boolean removeRow(Parameter parameter) {
    boolean changed = params.removeElement(parameter);
    if (changed)
      fireTableDataChanged();
    return changed;
  }

  public Parameter getRow(int rowIndex) {
    return (Parameter)params.elementAt(rowIndex);
  }

  public Parameter[] getParameters() {
    Parameter[] parameters = new Parameter[params.size()];
    params.copyInto(parameters);
    return parameters;
  }
  
  @Override
  public Class getColumnClass(int col)
  {
    switch (col) {
    case 0:
      return String.class;
    case 1:
      return Class.class;
    case 2:
      return String.class;
    }
    return super.getColumnClass(col);
  }
  
  @Override
  public boolean isCellEditable(int row, int col)
  {
    return true;
  }

  public abstract Class[] getDefaultParameterTypes();
  
  public abstract Object castValue(Object value, Class type)
       throws BadValueForTypeException;
  
  @Override
  public void setValueAt(Object aValue, int row, int column) {
    Parameter parameter = (Parameter)params.elementAt(row);
    if (column == 1) {
      if (aValue instanceof Class)
	parameter.setType((Class)aValue);
      else if (aValue instanceof String) {
	try {
	  Class clazz = Class.forName((String)aValue);
	  parameter.setType(clazz);
	} catch (java.lang.ClassNotFoundException cnfe) {
	  System.out.println(cnfe);
	}
      }
      setValueAt(parameter.getDefaultValue().toString(), row, 2);//recast
    } else {
      try {
	aValue = castValue(aValue, parameter.getType());
	parameter.setDefaultValue(aValue);
      } catch(BadValueForTypeException bfte) {
	(new ErrorDialog(null, "Bad value for type", true,
			 bfte.getMessage(), null)).setVisible(true);
      }
    }
  }
}
