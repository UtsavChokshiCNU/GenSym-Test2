/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.BeanXporterEventListener.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

/** The interface <code>BeanXporterListener</code> should be implemented
* by classes that intend to receive notification of either the success or
* failure of an export by a <code>BeanXporter</code> instance.
* @see BeanXporter
* @see BeanXporterEvent
*/
public interface BeanXporterListener
{
  /** A successfull export by a BeanXporter will cause the <code>
  * exportSuccess</code> method to be called on all registered
  * BeanXporter listeners.  Conventionally the path to the exported
  * jar will be container within the arg field of the <code>
  * BeanXporterEvent</code>
  */
  public void exportSuccess(BeanXporterEvent e);

  /** Notification that a BeanXporter export has failed
  */
  public void exportFailure(BeanXporterEvent e);

}
