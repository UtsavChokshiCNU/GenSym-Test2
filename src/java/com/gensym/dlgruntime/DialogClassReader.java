
package com.gensym.dlgruntime;

import java.awt.Component;

import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;
import com.gensym.message.Resource;

public class DialogClassReader implements DialogReader{

  private static Resource i18n =
  Resource.getBundle("com.gensym.dlgruntime.Messages");

  static volatile ClassLoader defaultClassLoader;

  private ClassLoader loader = defaultClassLoader;

  public static void setDefaultClassLoader(ClassLoader loader) {
    defaultClassLoader = loader;
  }

  public DialogClassReader() {
    this(defaultClassLoader);
  }

  public DialogClassReader(ClassLoader loader) {
    this.loader = loader;
  }

  /**
   * Read the contents of the resource into a byte array
   * @throws IllegalArgumentException if resourceDescription is
   * not a String.
   */
  @Override
  public Object readResource (Object resourceDescription) {
    if (!(resourceDescription instanceof String))
      throw new IllegalArgumentException(i18n.format("resourceDescriptionNotString",
						     resourceDescription));
    try {
      String className = (String)resourceDescription;
      if (loader == null)
	return Class.forName(className);
      else
	return loader.loadClass(className);
    } catch (ClassNotFoundException cfne) {
      throw new RuntimeException(i18n.format("drClassNotFound",
						  resourceDescription,
						  loader));
    }
  }


  /**
   * Create an actual resource object from the data
   * @throws IllegalArgumentException of the resourceData is not an instance
   * of java.lang.Class
   */
  @Override
  public Object makeResource (Object resourceData) throws ResourceInstantiationException{
    if (!(resourceData instanceof Class))
      throw new IllegalArgumentException(i18n.format("resourceDataNotClass",
						     resourceData));
    try {
      return ((Class)resourceData).newInstance();
    } catch (InstantiationException ie) {
      throw new ResourceInstantiationException(i18n.format("drClassNotInstantiable",
							   resourceData),
					       ie);
    } catch (IllegalAccessException iae) {
      throw new ResourceInstantiationException(i18n.format("drAccessException",
							   resourceData),
					       iae);
    }
  }

  /** 
   * Assumes that the resource is a component and simply returns it.
   * @throws ClassCastException if resource is not a Component.
   */
  @Override
  public Component getComponent (Object resource){
    return (Component)resource;
  }
  
  /**
   * Get an array of item proxies contained in this resource
   */
  @Override
  public ItemProxy[] getItemProxies (Object resource) {
    if (resource instanceof SingleItemEditor)
      return new ItemProxy[] {((SingleItemEditor)resource).getProxy()};
    else if (resource instanceof MultipleItemEditor)
      return ((MultipleItemEditor)resource).getProxies();
    else
      return null;
  }

  /**
   * Not useful in this implementation
   * @returns null
   */
  @Override
  public Object[] getObjectsOfClass(Object resource, Class clazz) {
    return null;
  }

  /**
   * Get the dialog closer contained in this resource, if any
   */
  @Override
  public DialogCommand getDialogCommand (Object resource) {
    if (resource instanceof Commandable)
      return ((Commandable)resource).getDialogCommand();
    else
      return null;
  }

}
