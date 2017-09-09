
package com.gensym.util;

import com.gensym.classes.G2__RemoteStub;

public class StubInvalidationEvent extends java.util.EventObject {

  private G2__RemoteStub stub;

  public StubInvalidationEvent (G2__RemoteStub stub) {
    super (stub);
    this.stub = stub;
  }

  public G2__RemoteStub getStub () {
    return stub;
  }
}
