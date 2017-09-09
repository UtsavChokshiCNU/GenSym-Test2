
package com.gensym.dlgruntime;

import java.net.URL;
import java.awt.Component;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.DialogCommand;

public interface DialogReader {

  /**
   * Read the contents of the resource into a byte array
   */
  public Object readResource (Object resourceDescription) throws java.io.IOException;

  /**
   * Create an actual resource object from the data
   */
  public Object makeResource (Object resourceData) throws ResourceInstantiationException;

  /** 
   * Get a top level component for this resource (a panel
   * if the resource is a PageLayout or a tabbed panel if 
   * the resource is a PageGroup)
   */
  public Component getComponent (Object resource);
  
  /**
   * Get an array of item proxies contained in this resource
   */
  public ItemProxy[] getItemProxies (Object resource);

  /** Get an array of objects of a given class from a resource 
   *
   */
  public Object[] getObjectsOfClass(Object resource, Class clazz);

  /**
   * Get the dialog closer contained in this resource, if any
   */
  public DialogCommand getDialogCommand (Object resource);

}
