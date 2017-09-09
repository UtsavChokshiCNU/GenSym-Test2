package com.gensym.uitools.inspect.trees;

import com.gensym.util.Symbol;

public class ColumnSpecification {

  Symbol[] columnNames;
  boolean[] columnViewAsTexts;
  int[] preferredColumnWidths;
  
  public ColumnSpecification(Symbol[] columnNames,
			     boolean[] columnViewAsTexts,
			     int[] preferredColumnWidths)
  {
    this.columnNames = columnNames;
    this.columnViewAsTexts = columnViewAsTexts;
    this.preferredColumnWidths = preferredColumnWidths;    
  }
    
}
