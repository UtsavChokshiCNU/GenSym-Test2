package com.gensym.beansruntime;

import java.beans.PropertyEditorSupport;
import java.net.URL;
import java.net.MalformedURLException;

public class URLEditor extends PropertyEditorSupport {
  
  @Override
  public String[] getTags() {
    return null;
  }
  
  @Override
  public void setValue(Object value) {
    if (value == null)
      super.setValue("");
    else if (value instanceof String)
      super.setValue((String)value);
    else if (value instanceof URL)
      super.setValue(((URL)value).toExternalForm());
  }

  @Override
  public Object getValue() {
    String string = (String) super.getValue();
    try {
      return new URL(string);
    } catch (MalformedURLException ex) {
      throw new RuntimeException(ex.getMessage());
    }
  }

  @Override
  public String getJavaInitializationString() {
    return ("new java.net.URL(\"" + super.getValue() + "\")");
  }
}
