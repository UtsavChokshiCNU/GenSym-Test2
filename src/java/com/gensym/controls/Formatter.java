package com.gensym.controls;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.beans.*;

/** The formatter class is a helper for the G2Listbox and can 
 * be safely ignored.  It may go away in future releases.
 */
public class Formatter extends Object implements java.io.Serializable
{
  static final long serialVersionUID = 3084899408139595266L;
  private String style = "toString";
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private Integer defaultValue = new Integer(123);

  public Formatter ()
  { 
    Class editor = com.gensym.controls.FormatterEditor.class;
    PropertyEditorManager.registerEditor
      (com.gensym.controls.Formatter.class,editor);
  }    

  public Formatter (String style, String attributeName)
  {
    this.style = style;
    this.attributeName = attributeName;
    attributeSymbol = Symbol.intern(attributeName);
  }

  public String getStyle ()
  { return style; }
  public void setStyle (String newStyle)
  { style = newStyle; }

  public String getAttributeName()
  { return attributeName; }
  public void setAttributeName(String newName)
  { 
    attributeName = newName; 
    attributeSymbol = Symbol.intern(newName);
  }
    
  public String format(Object object)
  {
    if (style.equals("Attribute"))
      {
        Object attributeValue = null;
	
        if ((object instanceof Structure) &&
            (attributeSymbol != null) &&
	    ((attributeValue =
	      ((Structure)object).getAttributeValue(attributeSymbol,defaultValue))
	     != defaultValue))
          {
	    if (attributeValue == null)
              return "<No Value>";
	    else
	      return attributeValue.toString();
          }
	else
	  return "<Couldn't format>";
      }
    else
      return object.toString();
  }

  @Override
  public String toString()
  {
    if (style.equals("Attribute"))
      return "attr = "+attributeName;
    else
      return style;
  }
  
}
