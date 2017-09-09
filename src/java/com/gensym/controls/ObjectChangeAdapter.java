package com.gensym.controls;

import java.beans.*;
import java.awt.event.*;
import java.awt.TextComponent;
// import com.gensym.dlgevent.ObjectUpdateListener;
// import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

public class ObjectChangeAdapter implements 
     java.io.Serializable, TextListener
{
 /*
  * Allow deserialization
  */
  static final long serialVersionUID = -1352589925400063307L;

  private java.util.Vector listeners = null;
  private String attributeName = "";
  private String targetClass = "Object"; /* add support and editor for 
					    more types and a drop-down 
					    list of supported coersions */

  public ObjectChangeAdapter()
  {

  }

  public String getAttributeName()
  {
    return attributeName;
  }

  public void setAttributeName(String string)
  {
    attributeName = string;
  }

  private void readObject(java.io.ObjectInputStream s)
       throws java.lang.ClassNotFoundException,
	 java.io.IOException
  {
    s.defaultReadObject();
  }

  @Override
  public void textValueChanged(TextEvent event)
  {
    Object source = event.getSource();
    System.out.println("obj adapter text event="+event+" from "+source);
    
    if (source instanceof TextComponent)
      {
        TextComponent tc = (TextComponent) source;
        fireObjectChange(tc.getText());
      }
  }
    
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (listeners == null) {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (listeners == null) {
      return;
    }
    listeners.removeElement(listener);
  }

   
  public void fireObjectChange(Object newObject) 
  {
    java.util.Vector targets;
    synchronized (this) {
      if (listeners == null) {
	return;
      }
      targets = (java.util.Vector) listeners.clone();
    }
    
    ObjectChangeEvent evt;
    if (attributeName.equals(""))
       evt = new ObjectChangeEvent(this, newObject);
    else
       evt = new ObjectChangeEvent(this, newObject, attributeName);

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }
  
}
