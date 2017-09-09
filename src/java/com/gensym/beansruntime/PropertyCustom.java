package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.lang.reflect.Method;

public class PropertyCustom extends Dialog 
{
  private Component customizer;
  private Button    ok     = new Button("  OK   ");
  private Button    apply  = new Button(" Apply ");
  private Button    cancel = new Button("Cancel");
  
  public PropertyCustom(Frame frame, PropertyEditor pe, int x, int y, 
		 Method propertyRead, Object bean)
  {
    super(frame, "Custom", true);
    
    customizer = pe.getCustomEditor();
    
    try
      {
	Object value = propertyRead.invoke (bean, new Object[] {});
	pe.setValue(value);
      }
    catch (Exception e)
      {
      }
    
    add("Center", customizer);
    
    setLocation(x, y);

    pack ();
    //setResizable (false);
    addWindowListener
      (
       new WindowAdapter ()
       {
	 @Override
	 public void windowClosing(WindowEvent e)
	   {
	     e.getWindow().dispose();
	   }
       } ) ;
    show();
  }
  
 
}

