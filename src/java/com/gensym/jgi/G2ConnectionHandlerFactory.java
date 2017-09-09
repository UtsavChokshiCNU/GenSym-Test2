package com.gensym.jgi;

/**
 * This Interface defines a factory for handling incomming unsolicted
 * (initiated from G2) connections from G2. It is used by the 
 * G2Connection class to create a G2Connection for a specific
 * G2Connection.
 *
 * @see      com.gensym.jgi.G2Connection
 * @Author   M.D.Gribble
 * @version  1.0, 26-Feb-1997
 *
 */
public interface G2ConnectionHandlerFactory
{

  /**
   * This method must be implemented by a G2ConnectionHandlerFactory 
   * to return a G2Connection for a given unsolicated G2Connection
   * 
   * @param connection_data a string sent from the G2 to identify the
   *        connection (from the GSI-INTERFACE Remote-Process-Initialization-String 
   *        attribute)
   */
  public G2Connection createG2Connection(String connection_data);

}
