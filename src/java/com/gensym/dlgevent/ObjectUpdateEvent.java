package com.gensym.dlgevent;

import java.util.EventObject;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;

/** ObjectUpdateEvents are one of the two main events classes that can
 *  be used to connect the G2-aware controls.  The G2-aware controls
 *  are a set of UI components derived from AWT that make it easy to
 *  present and edit complex, typed data structures from G2 to end users.
 *  ObjectUpdateEvents represent change notification from G2 or higher-level
 *  controls informing lower level controls to update their visual appearance.
 *  <p>
 *  The G2-aware controls can represent aggregate data structures.  Each level
 *  of aggregation is represented by a specific control.  For instance
 *  a G2 <b>Tank</b> class would be represented by an ItemProxy control.
 *  A level attribute of a tank could be represented by a G2TextField control.
 *  Typically these controls would be connected with an ObjectUpdateEvent
 *  flowing from the ItemProxy to the G2TextField and an ObjectChangeEvent
 *  flowing from the G2TextField to the ItemProxy.  For a more detailed 
 *  explanations please refer the Telewindows2 Technical Description.
 * 
 *  @see com.gensym.controls.G2TextField
 *  @see com.gensym.controls.ItemProxy
 *  @see com.gensym.controls.ObjectChangeEvent
 */
public class ObjectUpdateEvent extends EventObject
{
  /*
   * Allow deserialization
   */
   static final long serialVersionUID = 4845055393739481484L;

  private Object updatedObject = null;
  private String attributeName = null;

  public ObjectUpdateEvent(Object source, Object o)
  {
    super(source);
    updatedObject = o;
  }

  public ObjectUpdateEvent(Object source, Object o, String name)
  {
    super(source);
    updatedObject = o;
    attributeName = name;
  }

  /**
   *  The getUpdateObject method retrieves the object that has changed from 
   *  the event.  This object may need to be index by an attribute name 
   *  to get the value that is appropriate for the receiving control.
   *  @see com.gensym.controls.ObjectUpateEvent#getUpdatedValue
   */
  public Object getUpdatedObject()
  {
    return updatedObject;
  }

  /**
    *  This method allows ActiveX scripting environment users to distinguish
    *  objectUpdateEvents by attribute name, especially when generated
    *  from ItemProxy automatic updates.
    *  @deprecated
    *  @undocumented
   */
  public String getAttributeName()
  {
    return attributeName;
  }


  /** 
   *  This is the preferred method for getting an updatedValue from an
   *  this event.  This method handles attribute indexing and defaulting
   *  in a uniform manner and is used by all the scalar controls.
   */
  public Object getUpdatedValue(Symbol attributeNameOrNull, 
				Object defaultValue)
  {
    if (attributeNameOrNull == null)
      {
	if (updatedObject == null)
	  return defaultValue;
	else
	  return updatedObject;
      }
    else if ((updatedObject instanceof Structure) &&
	     (attributeNameOrNull != null))
      return ((Structure)updatedObject)
	     .getAttributeValue(attributeNameOrNull,defaultValue);
    else
      return defaultValue;
  }

  /** 
   *  This is the preferred method for getting an updatedValue from an
   *  this event.  This method handles attribute indexing and defaulting
   *  in a uniform manner and is used by all the scalar controls.
   *  It differs from the two-argument version in automatically inserting
   *  null as the default value.
   */
  public Object getUpdatedValue(Symbol attributeNameOrNull) 
  {
    return getUpdatedValue(attributeNameOrNull, null);
  }


  @Override
  public String toString () {
    return super.toString () + " {NAME = " + attributeName +
      ", VALUE = " + updatedObject;
  }
}
