
package com.gensym.util;

import java.beans.*;
import java.io.StringReader;
import java.io.StringWriter;
import java.io.IOException;
import com.gensym.util.Symbol;
import com.gensym.types.ValueType;
import com.gensym.types.SymbolType;
import com.gensym.types.G2Token;

public class SymbolEditor
		extends PropertyEditorSupport
{
  private static Symbol BAD_SYNTAX_ = Symbol.intern("BAD-SYNTAX");

  public SymbolEditor ()
  {
  }
		  
  @Override
  public String[] getTags() {
    return null;
  }
  
  @Override
  public void setValue(Object value) 
  {
    if (value == null)
      super.setValue("");
    else if (value instanceof String)
      super.setValue((String)value);
    else
      super.setValue(G2Token.makeParseableSymbolName(value.toString()));
  }

  @Override
  public Object getValue()
  {
    String string = (String) super.getValue();
    try {
      StringReader reader = new StringReader(string);
      Object value = ValueType.parseValue(reader);
      if (value instanceof Symbol)
	return value;
      else
	return BAD_SYNTAX_;
    } catch (Exception e)
      {
	com.gensym.message.Trace.exception (e);
	return BAD_SYNTAX_;
      }
  }

  @Override
  public String getJavaInitializationString()
  {
    return "com.gensym.util.Symbol.intern(\""+super.getValue()+"\")";
  }
}


