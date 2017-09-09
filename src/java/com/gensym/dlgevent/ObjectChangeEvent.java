package com.gensym.dlgevent;

import java.util.EventObject;

/** ObjectChangeEvents are one of the two main events classes that can
 *  be used to connect the G2-aware controls.  The G2-aware controls
 *  are a set of UI components derived from AWT that make it easy to
 *  present and edit complex, typed data structures from G2 to end users.
 *  ObjectChangeEvents flow up from fundamental editing controls like text fields
 *  and check boxes, through higher level components such as ListBoxes and
 *  eventually through ItemProxies to the G2 server.
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
 *  @see com.gensym.controls.ObjectUpdateEvent
 */
public class ObjectChangeEvent extends EventObject implements java.io.Serializable
{
  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 178911556576203034L;

  private Object changedObject = null;
  private String attributeName = null;
  private static int foo = 10;

  public ObjectChangeEvent()
  {
    super(42);
  }

  public ObjectChangeEvent(Object source, Object o)
  {
    super(source);
    changedObject = o;
  }

  public ObjectChangeEvent(Object source, Object o, String name)
  {
    super(source);
    changedObject = o;
    attributeName = name;
  }

  /**
   * The getChangedObject method retrieves the newly edited data
   * contained in the event.  It is used by ObjectChangeListeners.
   * @see com.gensym.controls.ObjectChangeListener
   */
  public Object getChangedObject()
  {
    return changedObject;
  }

  /** The attribute name of an update event contains the
   * the name of the attribute of the control editing
   * the piece of data.  This is used when ObjectChangeEvents
   * are received by ItemProxy's or StructureMUX's
   * @see com.gensym.controls.ItemProxy
   * @see com.gensym.controls.StructureMUX
   */
  public String getAttributeName()
  {
    return attributeName;
  }
}
