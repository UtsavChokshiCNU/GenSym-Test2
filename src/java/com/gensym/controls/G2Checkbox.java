/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Checkbox.java
 *
 */

package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import java.util.MissingResourceException;
import com.gensym.message.Trace;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;


/** A Checkbox bean which is capable of storing a G2 item attribute
*/
public class G2Checkbox extends Checkbox
           implements ObjectUpdateListener, ItemListener,
                      AttributeEditor, MouseListener
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 4307355168931381931L;

  private java.util.Vector listeners = null;
  private String  attributeName      = "";
  private Symbol  attributeSymbol    = null;
  private Boolean defaultContents    = new Boolean ("false");
  private boolean nextTextChangeIsProbablyFromUI = false;
  private String   resourceName = "";
  private String   labelKey     = "";
  private transient Resource bundle = null;

  /** Creates the bean
  */
  public G2Checkbox()
  {
     setLabel ("Check");
     addItemListener(this);
     addMouseListener(this);
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */
  @Override
  public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  @Override
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /** Gets the default contents of the bean
  */
  public Boolean getDefaultContents()
  {
     return defaultContents;
  }

  /** Sets the default contents of the bean
  */
  public void setDefaultContents (Boolean value)
  {
     defaultContents = value;
  }

  /** This method responds to an ItemEvent (from this bean) by firing an ObjectChange event
  * to this bean's listeners.
  * @undocumented
  */
  @Override
  public void itemStateChanged(ItemEvent event)
  {
    Object source = event.getSource();
    if (source == this)
      {
	if (nextTextChangeIsProbablyFromUI)
	  {
	    Object object = (Object)(new Boolean(getState()));
	    fireObjectChange(object);
	    nextTextChangeIsProbablyFromUI = false;
	  }
      } 
  }

  /** listener method - do not call
   * @undocumented
   */
  @Override
  public void mouseEntered(MouseEvent e)
  {}

  /** listener method - do not call
   * @undocumented
   */
  @Override
  public void mouseExited(MouseEvent e)
  {}

  /** listener method - do not call
   * @undocumented
   */
  @Override
  public void mousePressed(MouseEvent e)
  {}

  /** listener method - do not call
   * @undocumented
   */
  @Override
  public void mouseClicked(MouseEvent e)
  {}

  /** listener method - do not call
   * @undocumented
   */
  @Override
  public void mouseReleased(MouseEvent e)
  {
    // Exception ex = new Exception();
    // ex.printStackTrace();
    nextTextChangeIsProbablyFromUI = true;
  }

  /**
   * The setState method sets whether the checkbox is checked.
   */
  @Override
  public void setState(boolean state)
  {
    // nextTextChangeIsProbablyFromUI = false;
    if (state != getState())
      {
	super.setState(state);
      }
  }

  /**  
   * This method responds to objectUpdateEvents by setting the text
   * of the bean and updating the G2 item attribute it is storing
   */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object fieldValue = e.getUpdatedValue(attributeSymbol, defaultContents);
    
    setState((new Boolean (fieldValue.toString())).booleanValue());
  } 
  
  /** Adds a listener to this bean for ObjectChangeEvents
   */
  @Override
  public synchronized void addObjectChangeListener (ObjectChangeListener
						    listener)
  {
    if (listeners == null) {
      listeners = new java.util.Vector();
    }
    listeners.addElement(listener);
  }
  
  /** Removes a listener from this bean for ObjectChangeEvents
   */
  @Override
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (listeners == null) {
      return;
    }
    listeners.removeElement(listener);
  }

  /** Invokes the ObjectChanged method on each of this beans ObjectChange
  * listeners
  */  
  public void fireObjectChange(Object newObject)
  {
    java.util.Vector targets;
    
    synchronized (this)
      {
	if (listeners == null)
	  {
	    return;
	  }
	targets = (java.util.Vector) listeners.clone();
      }
    
    ObjectChangeEvent evt;
    
    if (attributeName.equals(""))
      evt = new ObjectChangeEvent(this, newObject);
    else
      evt = new ObjectChangeEvent(this, newObject, attributeName);
    
    for (int i = 0; i < targets.size(); i++)
      { 
	ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
	target.objectChanged(evt);
      }
    
  }

  /** Sets the label key for this bean
   */
  public void setLabelKey(String labelKey)  
  {
    this.labelKey = labelKey;

    if (bundle != null)
    {
      try
      {
        setLabel(bundle.getString(labelKey));
      }
      catch (MissingResourceException ex)
      {
        Trace.exception (ex, null);
      }
    }
  }

  /** Returns the label key for this bean
   */
  public String getLabelKey()  
  {
    return labelKey;  
  }

  /** Sets the name of the resource which will be used
   *  to look up the label key for this bean
   */
  public void setResourceName(String resourceName)
  {
    this.resourceName = resourceName;
    
    try
    {
      bundle = ResourceUtil.getBundle(resourceName);
      if (bundle != null)
        setLabel(bundle.getString(labelKey));
    }
    catch (MissingResourceException ex)
    {
      Trace.exception (ex, null);
    }
  }

  /** Returns the name of the resource which will be used
   *  to look up the label key for this bean
   */
  public String getResourceName()
  {
    return resourceName; 
  }  

  private void readObject(java.io.ObjectInputStream stream) throws
                   java.lang.ClassNotFoundException, java.io.IOException,
                   java.io.NotActiveException
  {
    stream.defaultReadObject();
    setResourceName(resourceName); // refreshes bundle and label in possibly new locale
  } 

}
