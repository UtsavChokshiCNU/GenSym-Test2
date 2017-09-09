/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *          com.gensym.com.ActiveXDefaultComponent.java
 *
 *   Author: Allan Scott
 */
package com.gensym.com;

import java.awt.Rectangle;
import java.awt.Dimension;

/** The interface <code>ActiveXDefaultComponent</code> describes 
 *  the interfaces that a default representation of an ActiveX component
 *  in Java may want to provide.  The <code>ActiveXDefaultComponent</code>
 *  interface mixes in the requirements of <code>ActiveXDisplayComponent</code>
 *  and <code>ActiveXDispatchable</code>.  This implies that classes that
 *  implement <code>ActiveXDefaultComponent</code> are providing a visual representation
 *  of an ActiveX component and also a generic automation interface.
 *  <p>
 *  An implementation of the <code>ActiveXDefaultComponent</code> interface
 *  is provided by the <code>ActiveXDefaultComponentImpl</code> class.
 * <p>
 *  @see ActiveXDisplayComponent
 *  @see ActiveXDispatchable
 *  @see ActiveXDefaultComponentImpl
 */  
public interface ActiveXDefaultComponent 
            extends ActiveXDisplayComponent,
			  ActiveXDispatchable
{
  
}
