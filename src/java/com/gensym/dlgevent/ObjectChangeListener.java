package com.gensym.dlgevent;

import java.util.EventListener;

/** The ObjectChangeListener interface indicates that an object
 *  can receive ObjectChange events.  Controls that implement
 *  aggregate data structures (G2Listbox, ItemProxy, StructureMUX)
 *  are ObjectChangeListeners.
 *  @see com.gensym.controls.G2Listbox
 *  @see com.gensym.controls.ItemProxy
 *  @see com.gensym.controls.StructureMUX
 */
public interface ObjectChangeListener extends EventListener
{
  void objectChanged(ObjectChangeEvent e);
}
