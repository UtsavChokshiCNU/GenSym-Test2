/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDislpayComponent.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.awt.Rectangle;
import java.awt.Dimension;

/**
 * The interface <code>ActiveXDisplayComponent</code> describes the 
 * requirements of a Java Class that provides a visual 
 * representation of an ActiveX component.
 * <p>
 * <code>ActiveXDisplayComponent</code> is one of a system of 
 * interfaces that
 * can be used to describe the classes that are created by 
 * <code>BeanXporter</code>.
 * Other important interfaces are:  <code>ActiveXComponent</code> which  
 * describes the requirements of a Java Class that represents an
 * ActiveX component and <code>ActiveXDispatchable</code> which  
 * provides a general automation interface.
 *<p>
 * Currently there are two ways by which an ActiveX component can be displayed
 * in Java:
 *<ul>
 *<li> In place Activated -  this means that the component manages all of it's
 * own display and only the dimension aspects of the ActiveXDisplayComponent
 * interface are relevant;
 *<li> Out of place Activated - this means that the component when activated
 * will create its own separate window.  The display of the component in
 * Java is mediated through the IViewObject C interface.  In this case
 * the frozen property and repaint methods of ActiveXDisplayComponent become
 * important.
 *</ul>
 *
 * The decision on whether to make an object in place activated or out of
 * place activated is currently controlled by <code>ActiveXProxy</code>.
 * Currently, in place activation is used wherever possible.
 *<p>
 * @see ActiveXProxy
 * @see ActiveXDispatchable
 * @see ActiveXComponent
 */
public interface ActiveXDisplayComponent 
            extends ActiveXComponent
{
  
  /** Get the Bounds of the component.
  */
  public Rectangle getBounds();
  
  /** Get the dimensions of the component
  */
  public Dimension getSize();

  /** Repaint the component.  The normal implementation of this
  * will call the repaint method on ActiveXProxy.  Note that 
  * it is not necessary to propagate the repaint method to ActiveXProxy
  * if the component was in place activated
  */
  public void repaint();

  /** For components that have been out of place activated the frozen
  * property provides the equivalent of the freeze() and unfreeze() methods
  * that are defined by IViewObject.  The normal way to use this property
  * in an implementation of ActiveXDisplayComponent is to decline to forward calls
  * to repaint() to ActiveXProxy while frozen is true and when frozen is set
  * to false to then forward a call to repaint.  This provides the effect that
  * a number of changes can be made to the component and the repainting can
  * be batched.
  */
  public void setFrozen(boolean freeze);

  /** For components that have been out of place activated the frozen
  * property provides the equivalent of the freeze() and unfreeze() methods
  * that are defined by IViewObject.  The normal way to use this property
  * in an implementation of ActiveXDisplayComponent is to decline to forward calls
  * to repaint() to ActiveXProxy while frozen is true and when frozen is set
  * to false to then forward a call to repaint.  This provides the effect that
  * a number of changes can be made to the component and the repainting can
  * be batched.
  */
  public boolean getFrozen();

}
