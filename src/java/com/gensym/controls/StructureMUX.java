package com.gensym.controls;

import java.beans.*;
import java.awt.event.*;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

/** The StructureMUX is an invisible component used to route events
 * that comprise the editing of the various fields of a structure.
 * The StructureMUX both sends and receives ObjectChangeEvents and 
 * ObjectUpdateEvents.
 *
 * @see com.gensym.util.Structure
 */ 

public class StructureMUX extends AttributeHolder
  implements ObjectUpdateListener
{
  /*
  * Allow deserialization
  */
  private String attributeName = "";
  private Symbol attributeSymbol = null;
  private String defaultContents = "";
  static final long serialVersionUID = 3189649626433027240L;

  public StructureMUX ()
  {
    super();
  }

  /** Gets the name of the G2 Item attribute which this bean is
   * storing as a Symbol.
   * @see com.gensym.util.Symbol
   */ 
  public Symbol getAttribute()
  {
    return attributeSymbol;
  }

  /** Sets the name of the G2 Item attribute which this bean is
   * storing from a Symbol.
   * @see com.gensym.util.Symbol
   */
  public void setAttribute(Symbol symbol)
  {
    attributeSymbol = symbol;
    attributeName = symbol.toString();
  }

  /* The objectUpdated method implements the objectUpdated interface.
   * when it is called it will update the contained Structure of this
   * component and propagate ObjectUpdateEvents to all downstream
   * components.
   */
  @Override
  public void objectUpdated(ObjectUpdateEvent e)
  {
    Object updateObject
      = e.getUpdatedValue(attributeSymbol,null);
    if (updateObject instanceof Structure)
      {
	structure = (Structure) updateObject;
	fireObjectUpdate();
      }
  }   

  /** Subscribe to ObjectChangeEvents from a given StructureMUX
   */
  public synchronized void addObjectChangeListener (ObjectChangeListener
						      listener)
  {
    if (changeListeners == null) {
      changeListeners = new java.util.Vector();
    }
    changeListeners.addElement(listener);
  }
  
  /** Cancel subscription to ObjectChangeEvents from a given StructureMUX.
   *
   */
  public synchronized void removeObjectChangeListener(ObjectChangeListener
							listener) 
  {
    if (changeListeners == null) {
      return;
    }
    changeListeners.removeElement(listener);
  }

  @Override
  void fireObjectChange()
  {
    java.util.Vector targets;
    synchronized (this) {
      if (changeListeners == null) {
	return;
      }
      targets = (java.util.Vector) changeListeners.clone();
    }
    
    ObjectChangeEvent evt;
    evt = new ObjectChangeEvent(this, structure.clone(), attributeName); /* clone changes */

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }
    
}
