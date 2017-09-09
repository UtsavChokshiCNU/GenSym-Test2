/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Button.java
 *
 */

/** A standard AWT button 
*/
package com.gensym.controls;

import java.awt.*;
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

public class G2Button extends Button
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

  /** Returns the label key for this bean.  The labelKey is used to 
   * lookup a string in the resource bundle named by the resource
   * property.
   */
  public String getLabelKey()  
  {
    return labelKey;  
  }

  /** The put method allows one to store state information in G2Buttons.
   *  The key can and value can be any object.  This is provided as a convenience
   *  to UI developers who need to accumulated state information into dialogs,
   *  typically to be as arguments in method calls that the button may eventually
   *  trigger.
   */
  public void put(Object key, Object value)
  {
    table.put(key,value);
  }

  /*  The get method retrieves objects stored by put.  It returns null if
   *  no value is stored for the given key.
   */
  public Object get(Object key)
  {
    return table.get(key);
  }

  /* putInt is a convenience method for put(), that eliminates the
   * need to box an int in an Integer.
   */
  public void putInt(Object key, int value)
  {
    table.put(key,new Integer(value));
  }

  /* getInt is a convenience method for get(), that eliminates a
   * unboxing an int from an Integer object.
   */
  public int getInt(Object key, int defaultValue)
  {
    Object val = table.get(key);
    if (val instanceof Integer)
      return ((Integer)val).intValue();
    else
      return defaultValue;
  }
 
 /* putString is a convenience method for put() */
  public void putString(Object key, String value)
  {
    table.put(key,value);
  }

  /* getString is a convenience method for get() that eliminates a cast
   * to String.
   */
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
