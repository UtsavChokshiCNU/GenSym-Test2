package com.gensym.cbu.mpe;

import java.beans.*;
import com.gensym.beansruntime.Enum;
import com.gensym.beansruntime.EnumEditor;

public class TransitionSpecification implements TestTypes
{
  public static final char UNBOUND_CHAR = 0xFFFF;
  int type = EQUAL;
  String stringToMatch = "";
  char charArg = UNBOUND_CHAR;
  private PropertyChangeSupport support;
  NDFAState next;

  public TransitionSpecification()
  {
    support = new PropertyChangeSupport(this);
  }

  TransitionSpecification(TransitionSpecification transition)
  {
    type = transition.type;
  }

  TransitionSpecification(int type, char charArg, NDFAState next)
  {
    this.type = type;
    this.charArg = charArg;
    this.next = next;
  }

  boolean isNonConsuming()
  {
    return ((type == TRUE) ||
	    ((type == EQUAL) && (charArg == UNBOUND_CHAR) && (stringToMatch.equals(""))));
  }

  boolean simpleEquals(TransitionSpecification other)
  {
    return ((type == other.type) && (charArg == other.charArg));
  }

  // non-proper subsets (equivalents) return true!!
  public boolean includes(TransitionSpecification other)
  {
    switch (type)
      {
      case EQUAL:
	switch (other.type)
	  {
	  case EQUAL:
	    return (charArg == other.charArg);
	  case TRUE:
	    return false;
	  default:
	    throw new RuntimeException("NYI");
	  }
      case TRUE:
	return false;
      default:
	throw new RuntimeException("NYI");
      }
  }
  
  public String getStringToMatch()
  {
    return stringToMatch;
  }

  public void setStringToMatch(String stringToMatch)
  {
    String oldMatch = this.stringToMatch;
    this.stringToMatch = stringToMatch;
    if (support != null)
      support.firePropertyChange("stringToMatch",oldMatch,stringToMatch);
  }

  public int getTestType()
  {
    return type;
  }

  public void setTestType(int type)
  {
    Integer oldType = new Integer(type);
    this.type = type;
    if (support != null)
      support.firePropertyChange("testType",oldType,new Integer(type));
  }

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
  
  @Override
  public String toString()
  {
    return "<TransitionSpec type="+type+" arg="+charArg+" next="+next+">";
  }
}
