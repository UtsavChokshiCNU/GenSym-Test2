package com.gensym.jgi.rmi;

import java.rmi.dgc.VMID;

/** In firewall cases (not yet properly supported), this RMIClientID is used
 * to uniquely identify a third-tier G2Gateway subclass client.
 * @deprecated
 */
public class RMIClientID implements java.io.Serializable {
  private VMID clientVMID;
  private int clientID;

  public RMIClientID() {
  }

  public RMIClientID(int clientID) {
    clientVMID = new VMID();
    this.clientID = clientID;
  }

  @Override
  public int hashCode() {
    return clientVMID.hashCode() | clientID;
  }

  @Override
  public boolean equals(Object obj) {
    if (obj == null || !getClass().equals(obj.getClass())){
      return false;
    }
    
    RMIClientID otherID = (RMIClientID)obj;

    return (clientID == otherID.clientID && clientVMID.equals(otherID.clientVMID));
  }
}
    
