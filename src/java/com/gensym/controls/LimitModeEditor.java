package com.gensym.controls;

import java.beans.*;

public class LimitModeEditor
		extends PropertyEditorSupport {

  public LimitModeEditor ()
  {
  }
		  
  @Override
  public String[] getTags() {
    String result[] = {
      "None",
      "Inclusive",
      "Exclusive"};
    return result;
  }

  @Override
  public void setValue(Object value) 
  {
    if (value instanceof LimitMode)
      super.setValue(((LimitMode)value).toString());
    else
      super.setValue(value);
  }

  @Override
  public Object getValue()
  {
    String string = (String) super.getValue();
    return new LimitMode(string);
  }

  @Override
  public String getJavaInitializationString()
  {
    return "new LimitMode(\""+super.getValue()+"\")";
  }
}


