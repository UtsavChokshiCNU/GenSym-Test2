package com.gensym.uitools.attrdisplays.layoutmodel;

import java.lang.IndexOutOfBoundsException;
import java.util.Vector;

/**
 * An AttributeDisplayLayout has two parts, its <b>attribute</b> section and 
 * its <b>global layout.</b>  A LayoutStructure is a data structure containing 
 * field-names and values in a 1 to 1 ratio.  The global layout is 
 * simply a LayoutStructure that holds information pertaining to the formatting 
 * of the entire AttributeDisplayLayout.
 * The attribute section contains <i>rows,</i> each of which is a
 * LayoutStructure, holding information for formatting of the row and the name, 
 * or key, of the attribute the row represents.
 */

public class AttributeDisplayLayoutImpl implements AttributeDisplayLayout {
  protected Vector attributeLayouts;
  protected LayoutStructure globalLayout;

  public AttributeDisplayLayoutImpl() {
    this(null);
  }
  
  public AttributeDisplayLayoutImpl(Vector attributeLayouts) {
    this(attributeLayouts, null);
  }
  
  public AttributeDisplayLayoutImpl(Vector attributeLayouts, 
				    LayoutStructure globalLayout) {
    if (attributeLayouts == null)
      attributeLayouts = new Vector();
    this.attributeLayouts = attributeLayouts;
    if (globalLayout == null) {
      try {
	globalLayout = new LayoutStructure(null);
      } catch (VectorsNotSameLengthException vnsle) {
	//couldn't happen
      }
    }
    this.globalLayout = globalLayout;
  }

  /**
   * Sets how an attribute is shown in this attribute display.
   * @param rowLayout - a LayoutStructure containing row format information. 
   * In G2, this would be {(showName, boolean)}
   * @param rowKey - designates the key to access the attribute in this 
   * attribute display layout.  In other words, the attribute name.
   * @return boolean - whether or not operation was successful
   */
  @Override
  public boolean setRowLayout(LayoutStructure rowLayout, Object rowKey) {
    boolean success = false;
    int i = getIndexOf(rowKey);
    if (-1 < i) {
      setRowLayoutAt(rowLayout, i);
      success = true;
    }
    return success;
  }

  /**
   * @param rowLayout - a LayoutStructure containing row format information. In
   * G2, this would be {(showName, boolean)}
   * @param index - an index numbering the attributes in the display.
   * @return Layout the previous layout at index.
   */
  @Override
  public void setRowLayoutAt(LayoutStructure rowLayout, int index) {
    attributeLayouts.setElementAt(rowLayout, index);
  }

  /**
   * @return the row layout at the specified index.
   */
  @Override
  public LayoutStructure getRowLayoutAt(int index) {
    return (LayoutStructure)attributeLayouts.elementAt(index);
  }

  /**
   * @return LayoutStructure[] of the row layouts that are currently chosen.
   */
  @Override
  public LayoutStructure[] getRows() {
    int length = attributeLayouts.size();

    LayoutStructure[] layoutArray = new LayoutStructure[length];
    for (int i=0; i<length; i++)
      layoutArray[i] = (LayoutStructure)attributeLayouts.elementAt(i);
    return layoutArray;
  }

  /**
   * @param rows - an array containing the row layouts to chose.
   */
  @Override
  public void setRows(Vector rows) {
    if (rows != null)
      attributeLayouts = rows;
    else rows.clear();
  }
 
  /**
   * Adds a row at the end of the list of selected attributes.
   */ 
  @Override
  public void addAttributeRow(LayoutStructure row) {
    if (row != null)
      attributeLayouts.addElement(row);
    else {
      try {
	attributeLayouts.addElement(new LayoutStructure(null));
      } catch (VectorsNotSameLengthException vnsle) {
	//won't happen, since LayoutStructure constructor not being called
	//with vectors.
      }
    }
  }
  
  /**
   * Adds a row at the specified index.
   */
  @Override
  public void insertAttributeAt(LayoutStructure row, int index) throws IndexOutOfBoundsException {
    if (row != null)
      attributeLayouts.insertElementAt(row, index);
    else {
      try {
	attributeLayouts.insertElementAt(new LayoutStructure(null), index);
      } catch (VectorsNotSameLengthException vnsle) {
	//won't happen, since LayoutStructure constructor not being called
	//with vectors.
      }
    }
  }

  /**
   * Removes the first row layout encountered that has this key.
   */
  @Override
  public boolean removeAttribute(Object rowKey) {
    boolean flag = false;
    int i = getIndexOf(rowKey);
    if (i>=0) {
      attributeLayouts.removeElementAt(i);
      flag = true;
    }
    return flag;
  }

  /**
   * @return the index of the first row encountered for an attribute with 
   * this key.
   */
  private int getIndexOf(Object rowKey) {
    int j = -1;
    for (int i=0; i<attributeLayouts.size(); i++) {
      if (((LayoutStructure)attributeLayouts.elementAt(i)).getRowKey() == rowKey)
	j = i;
    }
    return j;
  }

  /**
   * Sets overall format for this attribute display.
   * @param globalLayout - a LayoutStructure containing information about the look 
   * of the attribute display. For G2, this would be {(color, G2color name), 
   * (position, Object coordinates)}
   */ 
  @Override
  public void setGlobalLayout(LayoutStructure globalLayout) {
    if (globalLayout != null)
      this.globalLayout = globalLayout;
  }

  /**
   * @return LayoutStructure - contains the format of this 
   * AttributeDisplayLayout.
   */
  @Override
  public LayoutStructure getGlobalLayout() {
    return globalLayout;
  }


}
