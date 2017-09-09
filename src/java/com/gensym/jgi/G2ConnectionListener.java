
package com.gensym.jgi;

import java.util.EventListener;

/**
 * A G2ConnectionListener is informed when any of the following events occur;
 *
 * <LI>The connected G2 has resumed.
 * <LI>The connected G2 has paused.
 * <LI>The connected G2 has send a message.
 * <LI>The connection to G2 has been closed.
 * <LI>A connection to G2 has just been established.
 * <LI>A communicationError has occured while the connection to a G2 is active.
 * <LI>A communication error has occured, but no connection is active.
 * <LI>The network cannot deliver data that Java is attempting to write to G2.
 * <LI>The network cannot deliver data that G2 is attempting to write to Java.
 *
 * @version     1.00 24-NOV-1997
 * @author      M.D.Gribble
 */
public interface G2ConnectionListener extends java.util.EventListener
{

 /**
   * Called whenever the connected G2 process pauses
   * its current knowledge base (KB).
   *
   * <P>g2isPaused() is useful for pausing any methods/threads 
   * that operate asynchronously to G2. You can use 
   * g2isPaused() to suspend these functions until G2 resumes operation.
   */
  public void g2IsPaused(G2ConnectionEvent event);
  
  /** 
  * Called when a connected G2 process resumes its current knowledge base (KB).
  *
  * <P><B>g2isResumed</B> is called when the connected G2 process resumes running
  * its current knowledge base(KB). If a listener has any asynchronous 
  * operations  that are suspended by a call to <B>g2isPaused()</B>, you can
  * include code in g2isResumed() to resume those operations.
  *
  */
  public void g2IsResumed(G2ConnectionEvent event);

   /**
   * Called whenever the connected G2 process resets
   * its current knowledge base (KB).
   *
   * <P>g2isReset() is useful for pausing any methods/threads 
   * that operate asynchronously to G2. You can use 
   * g2isReset() to suspend these functions until G2 resumes operation.
   */
  public void g2IsReset(G2ConnectionEvent event);

   /**
   * Called whenever the connected G2 process starts
   * its current knowledge base (KB).
   *
   * <P>g2isStarted() is useful for starting any methods/threads 
   * that operate asynchronously to G2.
   */
  public void g2IsStarted(G2ConnectionEvent event);
  

  /** 
  * Called when a connected G2 closes an active connection.
  *
  * <P><B>g2ConnectionClosed()</B>is called when:
  *<P>
  * <LI>The connected G2 process disables, deactivates, or deletes the GSI
  * Interface
  * <LI> The connected G2 process changes the text of the
  * GSI-CONNECTION-CONFIGURATION attribute of the G2 GSI-INTERFACE that
  * is connected to a G2Gateway.
  * <LI>When the connected G2 is reset.
  * <LI>When a network error or failure causes the connection to the G2 process
  * to be lost.
  *
  * <P>Do not try to send data to G2 or invoke any G2 procedures from this
  * method. By the time <B>G2ConnectionClosed()</B> is called, G2 has already
  * closed the network connection, or the connection has been lost due to
  * a network failure.
  */
  public void g2ConnectionClosed(G2ConnectionEvent event); 


  /**
   * Called when a G2 process has just initiated a connection.
   *
   * <P>G2 calls <B>g2ConnectionInitialized</B> each time you activate a G2
   * connection that specifies the machine name and port number on which 
   * a G2Connection instance is listening. It can also be called as a result 
   * of calling G2Gateway methods <B>initiateConnection</B> or <B>getOrMakeConnection</B>
   *
   * <P> You can use this callback to perform tasks such as:
   * <P>
   * <LI> Validating connections from G2, as for a login procedure.
   * <LI> Allocating and/or initializing global tables on a per connection
   * basis; that is, tables which are unique to this connection.
   * <LI> Declaring G2 procedures as remote procedures, so the G2Gateway can
   * access them. These remote procedure declarations are valid only for
   * the lifetime of the connection with G2.
   *
   *
   * The string entered in the remote-process-initialization-string attribute 
   * of the G2 GSI-INTERFACE object that caused the connection to occur can be accessed
   * by calling event.getMessage()
   *
   * @param event The G2ConnectionEvent created for this event.
   */
  public void g2ConnectionInitialized(G2ConnectionEvent event);
 
  /**
   * Called when G2 sends a message to the G2Connection.
   *
   * <P><B>g2MessageReceived()</B> is called when a G2Gateway receives a message from a 
   * connected G2. G2 can sent a message by executing an inform action on a 
   * GSI-INTERFACE that is configured as a GSI message server. 
   *
   * The Message sent from g2 is embedded with the G2ConnectionEvent and can be accessed
   * by calling event.getMessage().
   *
   * @param event The G2ConnectionEvent created for this event.
   */
  public void g2MessageReceived(G2ConnectionEvent event);

  /**
   * Called when an asynchronous error has occured in the G2 communications interface
   * for the G2Connection
   *
   *@param error_event An G2CommunicationErrorEvent describing the error that occured.
   */
  public void communicationError(G2CommunicationErrorEvent error_event);

  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   *
   * <P>event.getstate will return;
   *              true - The network cannot deliver data, 
   *              false - The network can now deliver data once again
   *
   * @param event The G2ConnectionEvent created for this event.
   */
  public void readBlockage(G2ConnectionEvent event);

  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   *
   * <P>event.getState will return 
   *              true  - The network cannot deilver data,
   *              false - The network can now deliver data once again
   *
   * @param event The G2ConnectionEvent created for this event.
   */
  public void writeBlockage(G2ConnectionEvent event);

}

