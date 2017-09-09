/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Button.java
 *
 */

/** A standard Swing button 
*/
package com.gensym.jcontrols;

import java.awt.*;
import javax.swing.JButton;
import com.gensym.message.Resource;
import java.util.MissingResourceException;
import java.util.Hashtable;
import com.gensym.message.Trace;

/** 
 *  The G2 Button is a subclass of of java.awt.Button that 
 *  adds a few capabilities, notably internationalization.
 *  It has no special differences in behavior regarding 
 *  mouse handling or event generation from java.awt.Button.
 */

public class G2Button extends JButton
{
  private String   resourceName = "";
  private String   labelKey     = "";
  private transient Resource bundle = null;
  private Hashtable table = new Hashtable();
 
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = -7541913793958375294L;

  /**
   * Creates the button
   */
  public G2Button () 
  {
    super();
    setLabel ("Action");
  }

  /** 
   * Sets the label key for this bean.  The labelKey is used to 
   * lookup a string in the resource bundle named by the resource
   * property.
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

  /** Returns the label key for this bean.
   */
  public String getLabelKey()  
  {
    return labelKey;  
  }

  public void put(Object key, Object value)
  {
    table.put(key,value);
  }

  public Object get(Object key)
  {
    return table.get(key);
  }

  public void putInt(Object key, int value)
  {
    table.put(key,new Integer(value));
  }

  public int getInt(Object key, int defaultValue)
  {
    Object val = table.get(key);
    if (val instanceof Integer)
      return ((Integer)val).intValue();
    else
      return defaultValue;
  }

  public void putString(Object key, String value)
  {
    table.put(key,value);
  }

  public String getString(Object key)
  {
    Object val = table.get(key);
    if (val instanceof String)
      return (String)val;
    else
      return null;
  }

  /** Sets the name of the resource for internationalization.
   *  The labelKey will be used in as an index into the resource
   *  to find a label for the Button.
   * @param  resourceName String
   * @see com.gensym.controls.G2Button#getLabelKey
   */
  public void setResourceName(String resourceName)
  {
    this.resourceName = resourceName;

    if (resourceName == null)
      return;
    
    try
    {
      bundle = Trace.getBundle(resourceName);
      if (bundle != null && labelKey != null && !"".equals(labelKey))
        setLabel(bundle.getString(labelKey));
    }
    catch (MissingResourceException ex)
    {
      Trace.exception (ex, null);
    }
  }

  /** Returns the name of the resource for Internationalization.
   *  The labelKey will be used in as an index into the resource
   *  to find a label for the Button.
   * @return the resource's name
   * @see com.gensym.controls.G2Button#getLabelKey
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
    setResourceName (resourceName); // refreshes bundle and label in possibly new locale
  } 

}
