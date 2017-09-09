/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.BeanXporterEvent.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.awt.Event;

/** The class <code>BeanXporterEvent</code> is used for the communication
* of a successful or failed export from an instance of a <code>BeanXporter</code>
* to an object the implements <code>BeanXporterListener</code>
* @see BeanXporter
* @see BeanXporterListener
*/  
public class BeanXporterEvent extends Event
{

  /** Construct a BeanXporterEvent.  For now the type is not used, and
  * the argument will be a String indicating the path to the exported 
  * jar in the case of a successful export.
  */
  public BeanXporterEvent(BeanXporter source, int type, Object argument)
  {
    super(source, type, argument);
  }

}
