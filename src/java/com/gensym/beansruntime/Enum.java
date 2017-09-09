package com.gensym.beansruntime;

import java.beans.*;

public class Enum implements java.io.Serializable
{

  static final long serialVersionUID = 5065772850568602151L;

  private String[] labels;
  private int[] values;
  public int value;

static 
  {
    Class editor = com.gensym.beansruntime.EnumEditor.class;
    PropertyEditorManager.registerEditor
      (com.gensym.beansruntime.Enum.class,editor);
  }

  public Enum(String[] labels, int[] values,
	      int value)
  {
    if (labels.length != values.length)
      throw new IllegalArgumentException("Unequal labels and values");
    boolean found = false;
    for (int i = 0; i<labels.length ; i++)
      {
	if (labels[i] == null)
	  throw new IllegalArgumentException("Null label found");
	if (values[i] == value)
	  found = true;
      }
    if (!found)
      throw new IllegalArgumentException("Initial value not in set of values");
    this.labels = labels;
    this.values = values;
    this.value = value;
  }
  
  public int getValueForLabel(String string)
       throws IllegalArgumentException
  {
    for (int i = 0; i<labels.length ; i++)
      if (labels[i].equals(string))
	return values[i];
    throw new IllegalArgumentException(string);
  }

  public String[] getLabels()
  {
    return labels;
  }

  public int[] getValues()
  {
    return values;
  }

  @Override
  public String toString()
  {
    for (int i = 0; i<values.length ; i++)
      if (values[i] == value)
	return labels[i];
    return null;
  }    
  
}

