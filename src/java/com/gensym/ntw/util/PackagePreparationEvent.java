package com.gensym.ntw.util;

import java.util.EventObject;
import com.gensym.util.Symbol;
import com.gensym.ntw.TwGateway;
import com.gensym.jgi.ConnectionResolver;

public class PackagePreparationEvent extends EventObject {

  static final long serialVersionUID = -742752407299824401L;//????
  private ConnectionResolver connectionResolver;
  
  public static final int PACKAGE_PREPARATION_MODE_CHANGED  = 400;
  public static final int SIMULATE_PROPRIETARY_MODE_CHANGED  = 401;  
  private int id;
  private boolean state;

  /**
   * Constructs a PackagePreparationEvent for the given gateway, event-id and
   * state.
   * @param source The TwGateway with which this event is associated
   * @param id an int specifying which type of event this is.
   * @param state a boolean specifying the current state of any nnparameter
   * associated with this event.n
   */
  public PackagePreparationEvent (TwGateway source, int id, boolean state) {
    super (source);
    connectionResolver = ConnectionResolver.getConnectionResolver(source);    
    this.id = id;
    this.state = state;
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
   * @return a int specifying which event type this is.
   */
  public int getId() {
    return id;
  }

  /**
   * @return a boolean describing the current state of any parameter associated with
   * an event with this event's id.
   */
  public boolean getState() {
    return state;
  }
  
}
