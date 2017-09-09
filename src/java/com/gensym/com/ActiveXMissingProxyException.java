/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXMissingProxyException.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

/** The class <code>ActiveXMissingProxyException</code> is thrown
* when an attempt is made to make an automation call through the 
* <code>ActiveXDispatchable</code> interface and the associated
* ActiveXProxy does not exists or is not activated.
* @see ActiveXDispatchable  
*/
public class ActiveXMissingProxyException extends ActiveXException {
  
  /** @undocumented */
  public ActiveXMissingProxyException(ActiveXComponent axComponent) 
  {
    super("ActiveX Component does not have a Proxy" + axComponent);
  }

  protected ActiveXMissingProxyException(String message)
  {
    super(message);
  }
}
