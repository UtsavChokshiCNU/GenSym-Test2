package com.gensym.jgi.rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;

/** Interface to tag a Class that will provide access to a remote
 * G2JavaStubController
 */
public interface RemoteG2JavaStubControllerAccess extends Remote {

  /** Return the Remote G2RMIJavaStubController
   */
  public G2RMIJavaStubController getRemoteG2JavaStubController()
  throws RemoteException;

}
