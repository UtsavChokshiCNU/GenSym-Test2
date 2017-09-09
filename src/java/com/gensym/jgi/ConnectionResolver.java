package com.gensym.jgi;

import java.util.Hashtable;
import java.io.*;
import java.rmi.Remote;
import com.gensym.util.*;
import com.gensym.message.*;

public class ConnectionResolver implements Serializable {
  static final long serialVersionUID = -6370391132714785094L;
  private static final Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi", ConnectionResolver.class);
  
  private static Hashtable stubToWrapperMapper = new Hashtable();
  private static Hashtable resolverTable = new Hashtable();

  public static void mapStubToWrapper(Object stub, G2Gateway wrapper) {
    Trace.send(10, traceKey, i18nTrace, "mapStubToWrapper2", stub, wrapper);
    if (stubToWrapperMapper.get(stub) != null)
      throw new RuntimeException();

    stubToWrapperMapper.put(stub, wrapper);
    Trace.send(5, traceKey, i18nTrace, "mapStubToWrapper",
	       stubToWrapperMapper);
  }

  /**
   * @undocumented
   */
  public static void clearWrapper(Object wrapper) {
    Object stub = resolverTable.remove(wrapper);
    if (stub != null)
      stubToWrapperMapper.remove(stub);
  }

  /** Clears a stub from the mapping. Should only be done when
   * closing a connection.
   * @undocumented
   */
  public static void clearStub(Object stub){
    G2Gateway wrapper = (G2Gateway)stubToWrapperMapper.remove(stub);
    if (wrapper != null)
      resolverTable.remove(wrapper);
    else
      Trace.send(0, traceKey, i18nTrace, "crUnableToClearResolverTable", stub);
  }

  private static G2Gateway getWrapper(Object stub) {
    return (G2Gateway)stubToWrapperMapper.get(stub);
  }

  private Object stub;
  private transient G2Gateway wrapper;

  public static ConnectionResolver getConnectionResolver(G2Gateway connection) {
    ConnectionResolver resolver;
    synchronized (resolverTable) {
      resolver = (ConnectionResolver)resolverTable.get(connection);
      if(resolver == null) {
	resolver = new ConnectionResolver(connection);
	resolverTable.put(connection, resolver);
      }
    }

    return resolver;
  }

  protected ConnectionResolver(G2Gateway connection) {
    //    if (connection instanceof Remote)
    //  stub = (Remote)connection;
    if (connection instanceof java.io.Serializable ||
	connection instanceof java.rmi.Remote) {
      stub = connection;
    }

    wrapper = connection;
  }

  private void readObject(ObjectInputStream stream)
  throws IOException {
    try {
    stream.defaultReadObject();
    } catch (ClassNotFoundException ex1) {
    } catch (NotActiveException ex1) {
    }

    if (stub != null)
      wrapper = getWrapper(stub);
    Trace.send(30, traceKey, i18nTrace, "crreadObject",
	       stubToWrapperMapper, wrapper, stub);
    stub = wrapper;
  }

  public G2Gateway getContext() {
    return wrapper;
  }
}
			    
