package com.gensym.controls;

import java.beans.*;

public class FieldTypeEditor
		extends PropertyEditorSupport {

  public FieldTypeEditor ()
  {
  }
		  
  @Override
  public String[] getTags() {
    String result[] = {
      "Text",
      "Symbol",
      "Integer",
      "Float",
      "Quantity",
      "BooleanTruthValue",
      "Sequence",
      "Structure",
      "Value"};
    return result;
  }

  @Override
  public void setValue(Object value) 
  {
    if (value instanceof FieldType) 
      super.setValue(((FieldType)value).getTypeName());
    else
      super.setValue(value);
  }

  @Override
  public Object getValue()
  {
    String string = (String) super.getValue();
    return new FieldType(string);
  }

  @Override
  public String getJavaInitializationString()
  {
    return "new com.gensym.controls.FieldType(\""+super.getValue()+"\")";
  }
}

