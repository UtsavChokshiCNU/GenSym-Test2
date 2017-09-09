package com.gensym.beansruntime;

import java.beans.*;

public class EnumEditor
extends PropertyEditorSupport implements java.io.Serializable
{

  static final long serialVersionUID = -8042784720904665406L;

  public EnumEditor ()
  {
    super();
  }

  public EnumEditor(Object source)
  {
    super(source);
  }
		  
  @Override
  public String[] getTags() 
  {
    return ((Enum)getValue()).getLabels();
  }

  @Override
  public String getAsText()
  {
    return getValue().toString();
  }

  @Override
  public void setAsText(String textValue)
  {
    Enum value = (Enum)getValue();
    setValue(new Enum(value.getLabels(), value.getValues(), 
		      value.getValueForLabel(textValue)));
  }

  @Override
  public String getJavaInitializationString()
  {
    int i;
    Enum enumeration = (Enum)getValue();
    StringBuffer buffer = new StringBuffer("new Enum(");
    buffer.append("new String[] {");
    String[] labels = enumeration.getLabels();
    for (i=0; i<labels.length; i++)
      buffer.append(((i>0)?", \"":"\"")+labels[i]+"\"");
    buffer.append("}, new int[] {");
    int[] values = enumeration.getValues();
    for (i=0; i<values.length; i++)
      buffer.append(((i>0)?", ":"")+values[i]);
    buffer.append("}, "+enumeration.value+")");
    return buffer.toString();
  }
}
