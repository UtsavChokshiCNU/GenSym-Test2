package com.gensym.uitools.attrdisplays.layoutmodel;

import java.lang.IndexOutOfBoundsException;
import java.util.Vector;

/**
 * An AttributeDisplayLayout has two parts, its <b>attribute</b> section and 
 * its <b>global layout.</b>  A <i>LayoutStructure</i> is a data structure 
 * containing field-names and values in a 1 to 1 ratio.  The global layout is 
 * simply a LayoutStructure that holds information pertaining to the 
 * formatting of the entire AttributeDisplayLayout.
 * The attribute section contains <i>rows,</i> each of which is a
 * LayoutStructure, holding information for formatting of the row and the 
 * name, or key, of the attribute the row represents.
 */

public interface AttributeDisplayLayout
{
  /**
   * Sets how an attribute is shown in this attribute display.
   * @param rowLayout - a LayoutStructure containing row format information. 
   * In G2, this would be {(showName, boolean)}
   * @param rowKey - designates the key to access the attribute in this 
   * attribute display layout.  In other words, the attribute name.
   * @return boolean - whether or not operation was successful
   */
  public boolean setRowLayout(LayoutStructure rowLayout, Object rowKey);

  /**
   * @param rowLayout - a LayoutStructure containing row format information. 
   * In G2, this would be {(showName, boolean)}
   * @param index - an index numbering the attributes in the display.
   */
  public void setRowLayoutAt(LayoutStructure rowLayout, int index); 
    
  /**
   * @return the row layout at the specified index.
   */
  public LayoutStructure getRowLayoutAt(int index);

  /**
   * @return LayoutStructure[] of the row layouts that are currently chosen.
   */
  public LayoutStructure[] getRows();

  /**
   * @param rows - an array containing the row layouts to chose.
   */
  public void setRows(Vector rows);
  
  /**
   * Adds a row at the end of the list of selected attributes.
   */
  public void addAttributeRow(LayoutStructure row);
  
  /**
   * Adds a row at the specified index.
   */
  public void insertAttributeAt(LayoutStructure row, int index) throws IndexOutOfBoundsException;

  /**
   * Removes the first row layout encountered that has this key.
   */
  public boolean removeAttribute(Object rowKey);

  /**
   * Sets overall format for this attribute display.
   * @param globalLayout - a LayoutStructure containing information about the 
   * look of the attribute display. For G2, this would be {(color, 
   * G2color name), (position, Object coordinates)}
   */
  public void setGlobalLayout(LayoutStructure globalLayout);

  /**
   * @return LayoutStructure - contains the format of this 
   * AttributeDisplayLayout.
   */
  public LayoutStructure getGlobalLayout();

}
