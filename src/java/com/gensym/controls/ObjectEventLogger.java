package com.gensym.controls;

import java.beans.*;
import java.awt.event.*;
import java.awt.*;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

public class ObjectEventLogger extends TextArea implements 
     ObjectChangeListener, ObjectUpdateListener
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -4053504765677129000L;

  public ObjectEventLogger ()
  {
    setEditable(false);
  }


  @Override
  public void objectChanged(ObjectChangeEvent e)
  {
    String attrName =  e.getAttributeName();
    Object newValue = e.getChangedObject();
   
    append("Change Source = "+e.getSource()+"\n");
    append("  attribute-name = "+attrName+"\n");
    append("  new-value = "+newValue+"\n");
  }
  
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    String attrName =  e.getAttributeName();
    Object newValue = e.getUpdatedObject();
   
    append("Update Source = "+e.getSource()+"\n");
    append("attribute-name = "+attrName+"\n");
    append("new-value = "+newValue+"\n");
  }
  
  public void clear ()
  {
    setText("");
  }
}
