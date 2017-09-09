package com.gensym.uitools.attrdisplays.layoutmodel;

import java.util.Vector;

public class LayoutStructure {
  private Vector keys;
  private Vector values;
  private Object rowKey;

  public LayoutStructure() throws VectorsNotSameLengthException {
    this(null);
  }
  
  public LayoutStructure(Object rowKey) throws VectorsNotSameLengthException {
      this(rowKey, null, null);
  }

  public LayoutStructure (Object rowKey,
			 Vector keys,
			 Vector values) throws VectorsNotSameLengthException
  {
    this.rowKey = rowKey;
    if (keys == null && values == null) {
      this.keys = new Vector();
      this.values = new Vector();
    } else if (keys.size() != values.size())
      throw (new VectorsNotSameLengthException
	     ("Unequal data pairs in LayoutStructure constructor"));
    else {
      this.keys = (Vector)keys.clone();
      this.values = (Vector)values.clone();
    }
  }

  public Object getRowKey() {
    return rowKey;
  }

  public void setRowKey(Object rowKey) {
    this.rowKey = rowKey;
  }
  
  /** 
   * @param key - key for which to return value
   * @param defaultValue - what to return if key not found
   */
  public Object getAttributeValue(Object key, Object defaultValue) {
    if (key == null) return defaultValue;
    int i = keys.indexOf(key);
    if (i >= 0) return (values.elementAt(i));
    else
      return defaultValue;
  }

  public void setAttributeValue(Object key, Object value) {
    int i = keys.indexOf(key);

    if (i >= 0) 
      values.setElementAt(value, i);
    else {
      keys.addElement(key);
      values.addElement(value);
    }

  }

  public Object[] getValues() {
    return values.toArray();
  }

  public Object[] getKeys() {
    return keys.toArray();
  }

}
