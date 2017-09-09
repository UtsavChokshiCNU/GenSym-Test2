
package com.gensym.jgi;

/**
 * An empty implementation of G2ConnectionListener.
 * This class is provided as a convenience for easily
 * creating listeners by extending this class
 * and overriding only the methods of interest.
 *
 * @version     1.00  4/10/98
 * @author      vkp
 */
public class G2ConnectionAdapter implements G2ConnectionListener {

  @Override
  public void g2IsPaused (G2ConnectionEvent event) {}
  
  @Override
  public void g2IsResumed (G2ConnectionEvent event) {}

  @Override
  public void g2IsReset (G2ConnectionEvent event) {}

  @Override
  public void g2IsStarted (G2ConnectionEvent event) {}
  
  @Override
  public void g2ConnectionClosed (G2ConnectionEvent event) {}

  @Override
  public void g2ConnectionInitialized (G2ConnectionEvent event) {}
 
  @Override
  public void g2MessageReceived (G2ConnectionEvent event) {}

  @Override
  public void communicationError (G2CommunicationErrorEvent error_event) {}

  @Override
  public void readBlockage (G2ConnectionEvent event) {}

  @Override
  public void writeBlockage (G2ConnectionEvent event) {}

}

