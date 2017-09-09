/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BeanCreator.java
 *
 */


package com.gensym.beaneditor;

import java.awt.Image;
import java.util.Vector;
import java.util.Enumeration;
import java.beans.Beans;
import java.beans.BeanInfo;
import java.beans.Introspector;
import java.beans.IntrospectionException;
import java.lang.ClassNotFoundException;
import com.gensym.util.UnexpectedException;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.ObjectCreatorListener;
import com.gensym.ui.ObjectCreatorEvent;
import com.gensym.message.Trace;
import javax.swing.Icon;
import javax.swing.ImageIcon;

/** An implementation of the ObjectCreator interface for creating Java Beans off
 *  of Palettes.  Keys (the fully qualified names of the Java Beans class)
 *  can be added and removed dynamically.  The icon of the Bean is obtained
 *  via the bean's BeanInfo object.  The short description is the class name
 *  and the long description is the fully qualified class name.*/
public class BeanCreator implements ObjectCreator{
  private ClassLoader classLoader;
  private Vector keys;
  private Vector icons16x16, icons32x32;
  private Vector listeners;

  /** Creates a BeanCreator for classes in keys. */
  public BeanCreator(String[] keys){
    this(keys, null);
  }

  public BeanCreator(String keys[], ClassLoader classLoader){
    this.classLoader = classLoader;
    this.keys = new Vector();
    this.icons16x16 = new Vector();
    this.icons32x32 = new Vector();
    if (keys != null)
      for (int i=0; i<keys.length; i++){
	this.keys.addElement(keys[i]);
	this.icons16x16.addElement(null);
	this.icons32x32.addElement(null);
      }
    listeners = new Vector();
  }

  private int getIndexForKey(String key){
    int index = -1;
    for (int i =0; i<keys.size(); i++){
      if (keys.elementAt(i).equals(key)){
	index = i;
	break;
      }
    }
    return index;
  }

  /** Returns all keys as one group. */
  @Override
  public String[] getKeys(){
    String[] group = new String[keys.size()];
    keys.copyInto(group);
    return group;
  }

  @Override
  public boolean isAvailable(String key){
    return true;
  }

  /** Returns the class name for the SHORT_DESCRIPTION and the full class name for 
   *  the LONG_DESCRIPTION. */
  @Override
  public String getDescription (String key, int type){
    int index = key.lastIndexOf(".");
    if (index == -1) return key;
    return key.substring(index+1, key.length());
  }

  private Image createImage(String key, int size) throws IntrospectionException, ClassNotFoundException{
    BeanInfo beanInfo = null;
    if (classLoader == null){
      beanInfo = Introspector.getBeanInfo(Class.forName(key));
    }
    else{    
      int index = key.lastIndexOf('.');
      if ((index == -1) || (!(key.substring(index+1).equals("class"))))
	beanInfo = Introspector.getBeanInfo(createObject(key).getClass());
      else
	beanInfo = Introspector.getBeanInfo(classLoader.loadClass(key));
    }

    if (beanInfo == null) return null;

    if (size == SMALL_ICON)
      return beanInfo.getIcon(BeanInfo.ICON_COLOR_16x16);
    else
      return beanInfo.getIcon(BeanInfo.ICON_COLOR_32x32);
  }

  /** Returns the image of the specified size from the bean. A
   *  com.gensym.util.UnexpectedException is
   *  thrown if the Bean class can not be found or if there is an 
   *  IntrospectionException. */
  @Override
  public Image getIcon (String key, int size){
    //System.out.println(key);
    try{
      int index = getIndexForKey(key);
      if (index >= 0){
	Image icon;
	if (size == SMALL_ICON){
	  icon = (Image)icons16x16.elementAt(index);
	  if (icon == null){
	    icon = createImage(key, SMALL_ICON);
	    icons16x16.setElementAt(icon, index);
	    return icon;
	  }
	  else return icon;
	}
	else{
	  icon = (Image)icons32x32.elementAt(index);
	  if (icon == null){
	    icon = createImage(key, LARGE_ICON);
	    icons32x32.setElementAt(icon, index);	
	    return icon;
	  }
	  else return icon;
	}
      } 
    }
    catch(Exception ex){
      throw new UnexpectedException(ex);
    }
    return null;
  }

  /** Returns the bean created for key.  An com.gensym.util.UnexpectedException is
   *  return if the class is not found or there is an IO exception. */
  @Override
  public Object createObject(String key){
    try{
      if (classLoader == null){
	Class clazz = Class.forName(key);
	return Beans.instantiate(clazz.getClassLoader(), key);
      }
      else{
	return Beans.instantiate(classLoader, key);
      }
    }
    catch(Exception ex){
      throw new UnexpectedException(ex);
    }
  }

  /** Adds a ObjectCreatorListener. */
  @Override
  public void addObjectCreatorListener(ObjectCreatorListener listener){
    listeners.addElement(listener);
  }

  /** Removes a ObjectCreatorListener. */
  @Override
  public void removeObjectCreatorListener(ObjectCreatorListener listener){
    listeners.removeElement(listener);
  }

}










