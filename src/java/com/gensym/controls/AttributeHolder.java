package com.gensym.controls;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;

/**
 * The AttributeHolderClass implements the common mechanism
 *  of the ItemProxy and StructureMUX classes. 
 */
public abstract class AttributeHolder implements 
  java.io.Serializable, ObjectChangeListener
{

  // beta 4 and after:
  static final long serialVersionUID = -1123044281002118193L;

  // beta 3 and earlier:
  //  static final long serialVersionUID = -8813756914734761854L;
  /*
   * Allow deserialization
   */


  volatile Structure structure = new Structure();
  java.util.Vector updateListeners = null;
  java.util.Vector changeListeners = null;

  private void readObject(java.io.ObjectInputStream s)
       throws java.lang.ClassNotFoundException,
	 java.io.IOException
  {
    s.defaultReadObject();
  }

  @Override
  public void objectChanged(ObjectChangeEvent e)
  {
    String attrName =  e.getAttributeName();
    if (attrName != null)
      {
	Symbol nameSymbol = Symbol.intern(attrName);
        structure.setAttributeValue(nameSymbol, e.getChangedObject());
	fireObjectChange();
      }
  }
  
  public synchronized void addObjectUpdateListener (ObjectUpdateListener
						      listener)
  {
    if (updateListeners == null) {
      updateListeners = new java.util.Vector();
    }
    updateListeners.addElement(listener);
  }
  
  public synchronized void removeObjectUpdateListener(ObjectUpdateListener
							listener) 
  {
    if (updateListeners == null) {
      return;
    }
    updateListeners.removeElement(listener);
  }

  void fireObjectUpdate()
  {
    java.util.Vector targets;
    synchronized (this) {
      if (updateListeners == null) {
	return;
      }
      targets = (java.util.Vector) updateListeners.clone();
    }
    
    ObjectUpdateEvent evt;
    evt = new ObjectUpdateEvent(this, structure); /* don't clone updates */


    for (int i = 0; i < targets.size(); i++) {
      ObjectUpdateListener target = (ObjectUpdateListener)targets.elementAt(i);
      // System.out.println("before update "+target);
      target.objectUpdated(evt);
      // System.out.println("after update");
    }
  }

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
    evt = new ObjectChangeEvent(this, structure.clone()); /* clone changes */

    for (int i = 0; i < targets.size(); i++) {
      ObjectChangeListener target = (ObjectChangeListener)targets.elementAt(i);
      target.objectChanged(evt);
    }
  }

  
}
