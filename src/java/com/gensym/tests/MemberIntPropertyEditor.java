
package com.gensym.tests;

import java.beans.*;
import java.util.*;

public abstract class MemberIntPropertyEditor implements PropertyEditor {

  private PropertyDescriptor propDescptor;
  private Vector listeners = new Vector ();
  private int currentValue;

  @Override
  public void setValue (Object value) {
    currentValue = ((Integer)value).intValue ();
  }

  @Override
  public Object getValue () {
    return new Integer (currentValue);
  }

  @Override
  public boolean isPaintable () {
    return false;
  }

  @Override
  public void paintValue (java.awt.Graphics gfx, java.awt.Rectangle box) {
    // do nothing
  }

  @Override
  public String getJavaInitializationString () {
    return Integer.toString (currentValue);
  }

  @Override
  public String getAsText () {
    return getNames()[currentValue];
  }

  @Override
  public void setAsText (String newValue) {
    String[] names = getNames ();
    for (int i=0; i<names.length; i++) {
      if (names[i].equals (newValue)) {
	int oldValue = currentValue;
	currentValue = getValues()[i];
	Vector listenersList = (Vector)listeners.clone ();
	PropertyChangeEvent propEvent = new PropertyChangeEvent (this, null, new Integer (oldValue), new Integer (currentValue));
	for (i=0; i<listenersList.size(); i++)
	  ((PropertyChangeListener)listeners.elementAt (i)).propertyChange (propEvent);
	return;
      }
    }
    //currentValue = Integer.parseInt (newValue);
    throw new IllegalArgumentException (newValue + " is a wrong value");
  }

  @Override
  public String[] getTags () {
    return (String[])getNames().clone();
  }

  protected abstract String[] getNames ();

  protected abstract int[] getValues ();

  @Override
  public java.awt.Component getCustomEditor () {
    return null;
  }

  @Override
  public boolean supportsCustomEditor () {
    return false;
  }

  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener) {
    System.out.println ("Adding listener: " + listener);
    listeners.addElement (listener);
  }

  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener) {
    System.out.println ("Removing listener: " + listener);
    listeners.removeElement (listener);
  }
}
