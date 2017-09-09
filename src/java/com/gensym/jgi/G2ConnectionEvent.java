
package com.gensym.jgi;

import java.util.EventObject;

/**
 * A event object that encapsulates information fired during a G2Connection event.
 *
 * @version     1.00 24-Nov-1997
 * @author      M.D.Gribble
 */
public class G2ConnectionEvent extends EventObject
{
  static final long serialVersionUID = -842752407299824401L;
  private ConnectionResolver connectionResolver;
  private String message;
  private boolean state = false;
  private int id;
  public static final int 
      G2_IS_PAUSED              = 0,
      G2_IS_RESUMED             = 1,
      G2_IS_RESET               = 2,
      G2_IS_STARTED             = 3,

      G2_CONNECTION_CLOSED      = 10,
      G2_CONNECTION_INITIALIZED = 11,
      G2_CONNECTION_ABORTED     = 12,

      G2_MESSAGE_RECEIVED       = 20,
      G2_COMMUNICATION_ERROR    = 21,
      G2_NOCONNECTION_COMMUNICATION_ERROR = 22,

      G2_READ_BLOCKAGE          = 30,
      G2_WRITE_BLOCKAGE         = 31;

  /**
   * Construct a G2ConnectionEvent, with message and state information
   */
  public G2ConnectionEvent(Object source, int id, String message, boolean state)
  {
    super(source);
    this.message = message;
    this.state = state;
    this.id = id;
    if (source instanceof G2Gateway)
      connectionResolver = ConnectionResolver.getConnectionResolver((G2Gateway)source);
  }

  /**
   * Construct a G2ConnectionEvent, source only
   */
  public G2ConnectionEvent(Object source, int id)
  {
    this(source, id, null, false);
  }

  /**
   * Get any embedded message.
   */
  public String getMessage()
  {
    return message;
  }

  /**
   * Get any embedded state information.
   */
  public boolean getState()
  {
    return state;
  }

  /**
   * Get Id
   */
  public int getId()
  {
    return id;
  }

  /**
   * Returns the parameter string representing the information
   * in this event.
   * @return the paramter string of this Event.
   */
  public String paramString () {
    String idString = "";
    switch (id) 
      {
      case G2_IS_PAUSED:
	idString = "PAUSED"; 
	break;
      case G2_IS_RESUMED:
	idString = "RESUMED"; 
	break;
      case G2_IS_RESET:
	idString = "RESET"; 
	break;
      case G2_IS_STARTED:
	idString = "STARTED"; 
	break;
      case G2_CONNECTION_CLOSED:
	idString = "CONNECTION CLOSED"; 
	break;
      case G2_CONNECTION_INITIALIZED:
	idString = "CONNECTION INITIALIZED"; 
	break;
      case G2_MESSAGE_RECEIVED:
	idString = "MESSAGE RECEIVED"; 
	break;
      case G2_COMMUNICATION_ERROR:
	idString = "COMMUNICATION ERROR"; 
	break;
      case G2_NOCONNECTION_COMMUNICATION_ERROR:
	idString = "NOCONNECTION COMMUNICATION ERRORPAUSED"; 
	break;
      case G2_READ_BLOCKAGE:
	idString = "READ BLOCKAGE"; 
	break;
      case G2_WRITE_BLOCKAGE:
	idString = "WRITE BLOCKAGE"; 
	break;
	  default:
      }
    return idString;
  }

  private void readObject(java.io.ObjectInputStream stream)
  throws java.io.IOException, ClassNotFoundException{
    try {
      stream.defaultReadObject();
    } catch (java.io.NotActiveException ex) {
      com.gensym.message.Trace.exception(ex);
    }
    
    source =
      connectionResolver == null ? null : connectionResolver.getContext();
  }

  /**
   * Returns a string representation of this event and its state.
   * @return    a string representation of this event.
   */
  @Override
  public String toString () {
    return
      new StringBuffer (super.toString ()).append("(").append(paramString()).append(")").toString ();
  }
}
