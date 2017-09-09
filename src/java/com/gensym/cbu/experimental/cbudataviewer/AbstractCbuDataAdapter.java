package com.gensym.cbu.experimental.cbudataviewer;

import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;

abstract public class AbstractCbuDataAdapter
{
  Hashtable originalToCbuDataMapping = new Hashtable();
  Vector listeners = new Vector();

  public void addCbuDataAdapterListener(CbuDataAdapterListener listener)
  {
    listeners.addElement(listener);
  }

  public void removeCbuDataAdapterListener(CbuDataAdapterListener listener)
  {
    listeners.removeElement(listener);
  }

  void addDataElement(Object originalDataReference, CbuData correspondingCbuData)
  {
    originalToCbuDataMapping.put(originalDataReference, correspondingCbuData);
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
      {
	((CbuDataAdapterListener)e.nextElement()).addCbuData(correspondingCbuData);
      }
  }

  void removeDataElement(Object originalDataReference)
  {
    CbuData cbuData = (CbuData)originalToCbuDataMapping.get(originalDataReference);
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
      {
	((CbuDataAdapterListener)e.nextElement()).removeCbuData(cbuData);
      }
    originalToCbuDataMapping.remove(originalDataReference);
  }

  void dataElementChanged(Object originalDataReference, String changedPropertyName, Object newPropertyValue)
  {
    CbuData cbuData = (CbuData)originalToCbuDataMapping.get(originalDataReference);
    for (Enumeration e = listeners.elements(); e.hasMoreElements(); )
      {
	((CbuDataAdapterListener)e.nextElement()).cbuDataChanged(cbuData, changedPropertyName, newPropertyValue);
      }
  }
}
  
