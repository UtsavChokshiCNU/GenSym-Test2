package com.gensym.dlgevent;

import java.util.EventListener;

/** The ObjectUpdateListener interface is used by controls
 *  that by represent values which may need to change from
 *  updates occurring in the outside world, i.e. G2 or higher
 *  level controls.  End-user editing controls (e.g. G2TextField)
 *  or intermediary controls (e.g StructureMUX).
 *
 *  @see com.gensym.controls.G2TextField
 *  @see com.gensym.controls.StructureMUX
 */
public interface ObjectUpdateListener extends EventListener
{
  void objectUpdated(ObjectUpdateEvent e);
}
