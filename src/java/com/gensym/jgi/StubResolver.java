package com.gensym.jgi;


import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.jgi.download.G2StubFactory;
import java.util.Enumeration;
import com.gensym.classes.DeferredStub;
import com.gensym.classes.Item;


/**
 * This class provides the mechanism to resolve a DeferredStub or a DeferredStub
 * embedded inside complex items (Sequence, Structures, Object[]).
 * normal behaviour will be to use a G2StubFactory to return a G2 stub 
 * corresponding to a DeferredStub.
 */
class StubResolver {

  private G2StubFactory g2StubFactory;

  StubResolver (G2StubFactory fac) {
    this.g2StubFactory = fac;
  }
  
  /**
   * resolveDeferredStubs is the preferred way to ensure that
   * the object handed to the client has the right stubs.
   * This code is cognizant of the data-structures sent back
   * from G2 and recursively walks the return value to
   * resolve all embedded stubs.
   */

  /* 
   * An alternative implementation to calling the method on
   * all objects would be to call it only on those classes
   * that we know methods exist for. i.e., 
   * if (clazz == Structure.class || clazz == Sequence.class
   *        || clazz == DeferredStub.class)
   * I don't know if it is more efficient to check the
   * class before dispatch or just let the method for
   * Object be the catch.
   */

  Object resolveDeferredStubs (Object stubObject) {
    return dispatchResolution (stubObject);
  }

  /**
   * If any of you are wondering why we dont just override resolveDeferredStubs for
   * each class we need to resolve...well there seems to be a VM feature/error in JDK1.1.
   * where once the object has been cast for a method parameter (in the call to dispatchResolution
   * it is cast to Object), the VM will then dispatch on the cast class, not the actual class !!!
   */
  private Object dispatchResolution (Object o) {

    if (o == null)
      return o;

    if (o instanceof DeferredStub)
      return resolveDeferredStub ((DeferredStub)o);
    else if (o instanceof Sequence)
      return resolveDeferredStubsInSequence ((Sequence)o);
    else if (o instanceof Structure)
      return resolveDeferredStubsInStructure ((Structure)o);
    else if (o instanceof Object[])
      return resolveDeferredStubsInObjectArray ((Object[])o);
    else
      return o;
  }

  /*
   * These can be made package public if necessary.
   * They return an instance of the appropriate type.
   */
  private Item resolveDeferredStub (DeferredStub ds) {

    // There may be embedded attributes in 
    Structure dsAtts = ds.getAttributes();
    if (dsAtts != null)
      resolveDeferredStubsInStructure (dsAtts);
    return ds.resolve (g2StubFactory);
  }

  private Sequence resolveDeferredStubsInSequence (Sequence s) {
    if (s.isEmpty())
      return s;
    int i, numElts = s.size ();
    Sequence retnSeq = new Sequence (numElts);
    for (i=0; i<numElts; i++) {
      Object o = s.elementAt (i);
      retnSeq.addElement (dispatchResolution (o));
    }
    return retnSeq;
  }

  private Structure resolveDeferredStubsInStructure (Structure s) {
    Enumeration keys = s.getAttributeNames ();
    Enumeration vals = s.getAttributeValues ();
    while (keys.hasMoreElements ()) {
      Symbol key = (Symbol) keys.nextElement ();
      Object val = dispatchResolution (vals.nextElement ());
      s.setAttributeValue (key, val);
    }
    return s;
  }

  private Object[] resolveDeferredStubsInObjectArray (Object[] oarray) {
    for (int i = 0; i<oarray.length; i++) {
      oarray[i] = dispatchResolution(oarray[i]);
    }
    return oarray;
  }

}

