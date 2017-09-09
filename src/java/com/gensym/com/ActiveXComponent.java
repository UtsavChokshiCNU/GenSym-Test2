/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXComponent.java
 *
 *  Author: Allan Scott
 */
package com.gensym.com;

import java.beans.PropertyVetoException;

/**
 * The interface <code>ActiveXComponent</code> 
 * describes the requirements of a Java Class that is used to represent
 * an ActiveX component.  A Java Class must implement <code>ActiveXComponent
 * </code> if it is to be managed by the <code>ActiveXProxy</code> class.
 *<p>
 * When <code>BeanXporter</code> exports the contents of a type library it 
 * will emit a Java Class which implements <code>ActiveXComponent</code> for
 * each CO_CLASS type in the type library.
 *<p>
 * <code>ActiveXComponent</code> is one of a system of interfaces that
 * can be used to describe the classes that are created by <code>BeanXporter</code>.
 * Other important interfaces are:  <code>ActiveXDispatchable</code> which  
 * provides a general automation interface and <code>ActiveXDisplayComponent</code>
 * which provides an interface for a visual <code>ActiveXComponent</code>.
 * Interfaces are used to specify these behaviors so that it is possible
 * for the BeanXporter facility to be specified without reference to
 * implementation issues, and to allow alternative implementations.
 * <p>
 * @see Guid
 * @see BeanXporter
 */
 public interface ActiveXComponent {

  /** Get the classID which identifies the ActiveX conponent that this represents.
  */
  public Guid getClassID ();

  /** Change the classID which this ActiveX component represents.  This
  * is a vetoable property because some implementations may not want to allow
  * this change.  Other implementations such as <code>ActiveXGenericComponent</code>
  * can use allow this to be changed to that one Java Class can be used to 
  * represent many ActiveX components.
  * @see Guid
  */
  public void setClassID (Guid classID) throws PropertyVetoException;

  /** The activateOnLoad property indicates whether an ActiveXComponent
  * that has been deserialized from a Java Object Stream will be activated
  * automatically or not.  For many simple ActiveX controls 
  * automatic activation is a good idea.  For components, such as OLE documents
  * the inactive state is useful.
  */
  public boolean getActivateOnLoad();

  /** The activateOnLoad property indicates whether an <code>ActiveXComponent</code>
  * that has been deserialized from a Java Object Stream will be activated
  * automatically or not.  For many simple ActiveX controls 
  * automatic activation is a good idea.  For components, such as OLE documents
  * the inactive state is useful.
  */
  public void setActivateOnLoad(boolean activateOnLoad);

  /** The <code>activate<code> method causes the underlying ActiveX component
  * to be activated.  Normally this method will be implemented by calling the
  * activate() method on the ActiveXProxy that manages this ActiveXComponent.
  * @see ActiveXProxy
  */
  public void activate () throws ActiveXException;

  /** The <code>delete</code> method causes the underlying ActiveX component
  * to be deleted.  This means that the resources associated with that 
  * component will be removed from memory.  Normally this method will be
  * implemented by calling the delete() method in the ActiveXProxy that
  * manages this ActiveXComponent
  * @see ActiveXProxy
  */
  public void delete () throws ActiveXException;

  /** The <code>proxyActivated</code> method is used to give notication to
  * the ActiveXComponent that the underlying <code>ActiveXProxy</code> on
  * which it is dependent has been activated.
  */
  public void proxyActivated();

}

