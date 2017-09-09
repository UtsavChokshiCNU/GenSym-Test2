package com.gensym.editor.icon.g2;

import javax.swing.table.AbstractTableModel;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.VariableTableModel;
import com.gensym.editor.icon.core.BadValueForTypeException;
import java.util.Vector;
import java.awt.Color;
import com.gensym.util.Symbol;

public class G2ParameterTableModel extends VariableTableModel {
  private static Class[] types = {Integer.class, String.class, Symbol.class};

  @Override
  public Class[] getDefaultParameterTypes() {
    return types;
  }
  
  public G2ParameterTableModel(Parameter[] parameters) {
    super(parameters);
  }

  @Override
  public Object castValue(Object value, Class type)
       throws BadValueForTypeException
  {
    try {
      if (type == Integer.class)
	value = new Integer((String)value);
      else if (type == Symbol.class)
	value = Symbol.intern(((String)value).toUpperCase());
      //else it's a string
    } catch (NumberFormatException nfe) {
      throw new BadValueForTypeException(nfe.getMessage());
    }  
    return value;    
  }
  
}
