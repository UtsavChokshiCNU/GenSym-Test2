package com.gensym.classes;

import com.gensym.jgi.G2Access;
import com.gensym.util.Structure;

/**
 * This class is specifically designed for cases where loading a class
 * definition (call it A) requires the load of an instance of one the
 * subclasses of A. The motivating example of this was the fact
 * that PROTOOLS-ITEM is related to an instance of
 * PROTOOLS-DOCUMENTATION, which is a subclass of PROTOOLS-ITEM.
 * In these situations, an instance of this class is returned
 * if none of the stubs in the class inheritance path have already
 * been loaded.
 */
public class Interim__StubImpl extends ItemImpl {

  public Interim__StubImpl() {
  }

  public Interim__StubImpl(G2Access context, int handle, Structure attributes) {
    super(context, handle, attributes);
  }

  public Interim__StubImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super(context, handle, handleVersion, wrap, attributes);
  }

}
