package com.gensym.util;

import com.gensym.core.BaseModifiableBeanInfo;

/** ModifiableBeanInfo is a really useful hack that allows one to
 *  override the default behavior of Introspector.getBeanInfo().  It
 *  is not obvious to the author why Javasoft did not make the
 *  Introspector a little more open.  The implementation of this class
 *  seems to be a little bit hackish, but is hoped that it is at least
 *  has good hygiene.  
 *  <p> 
 *  It provides four protected methods to be
 *  overridden by subclasses.  getBeanClass() informs the parent class
 *  of what bean is being introspected.  The other three are methods
 *  that allow the subclasses to inspect and modify FeatureDescriptors
 *  that are created by the default Introspector getBeanInfo. 
 *  <p>
 *  @see com.gensym.core.BaseModifiableBeanInfo
 */

public abstract class ModifiableBeanInfo extends BaseModifiableBeanInfo
{
}
