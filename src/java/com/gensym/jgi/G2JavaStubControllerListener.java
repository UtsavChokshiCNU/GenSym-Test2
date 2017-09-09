package com.gensym.jgi;

/**
 * Listener interface for Event notifications from a G2JavaStubController.
 */
public interface G2JavaStubControllerListener {

  public void callMethod(G2JavaStubControllerEvent event);

  public void deleteInstance(G2JavaStubControllerEvent event);

}
    
