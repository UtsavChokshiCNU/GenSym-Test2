package com.gensym.cbu.odieeventfilterlanguage;
 
import java.beans.PropertyChangeSupport;
import java.beans.PropertyChangeListener;
import java.io.Serializable;

abstract public class EventFilterBlock implements Serializable
{
  PropertyChangeSupport support;
  boolean properlyConfigured = false;

  public EventFilterBlock()
  {    
    support = new PropertyChangeSupport(this);
  }// end EventFilterSpecificationComponent Constructor

  public PropertyChangeSupport getSupport()
  {
    return support;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    this.support = support;
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    support.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }

  public boolean getProperlyConfigured()
  {
    return properlyConfigured;
  }

  abstract public String booleanExpression();

}









