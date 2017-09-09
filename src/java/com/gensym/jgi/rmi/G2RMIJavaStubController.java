package com.gensym.jgi.rmi;

import java.rmi.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;
import com.gensym.util.*;

/**
 * This Interface declares the Rmote methods for a G2JavaStubController.
 */
public interface G2RMIJavaStubController extends Remote {

  void newInstance(Item g2proxy, String java_class_name, Sequence args)
       throws ClassNotFoundException, 
	 InstantiationException, 
	 IllegalAccessException,
	 com.gensym.util.MethodInvocationException,
	 NoSuchMethodException,
	 G2AccessException,
         RemoteException;

  Object callMethod(Item g2proxy, 
			  String method_name, 
			  Sequence args)
       throws NoSuchMethodException,
	 IllegalAccessException,
	 InstantiationException,
	 MethodInvocationException,
         G2AccessException,
         RemoteException;

  Object callStaticMethod(Item g2proxy, 
				String java_class_name, 
				String method_name, 
				Sequence args)
       throws ClassNotFoundException, 
	 NoSuchMethodException, 
	 IllegalAccessException,
	 InstantiationException,
	 com.gensym.util.MethodInvocationException,
         G2AccessException,
         RemoteException;

  void deleteInstance(Item g2proxy, boolean strictCheck)
       throws IllegalAccessException,
	 G2AccessException,
         RemoteException;

  /**
   * Add a Java object as a listener for events from a G2 Event Source.
   *
   *@param g2EventSource The G2 Item that the Java Object will be listening too
   *@param adderMethodName The G2 Method name on G2EventSource for adding this listener
   *@param javaProxyClass The name of the Java listener class of which we are interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   *@return The G2 ITEM Proxy that was used to listen for the G2 events
   * 
   */
   public Item addJavaListenerToG2EventSource(
					      Item  g2EventSource,
					      Symbol adderMethodName,
					      String javaProxyClass,
					      Symbol g2ParentClass,
					      Object javaListener)
       throws G2AccessException, RemoteException;

       
  /**
   * Remove a Java Object from listening for events from a G2 Event Source
   *
   *@param g2EventSource The G2 Item that the Java Object was listening too
   *@param removerMethodName The G2 Method name on G2EventSource for removing this listener
   *@param javaProxyClass The name of the Java listener class of which we where interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   *@param The G2 ITEM Proxy that was used to listen for the G2 events. If NULL, then there is 
   *        no proxy listener to remove from the G2 Event Source Listener list. This may occur
   *        when MultiCast Listeners are dispatching events from the G2 Event Source. 
   *        (in which case this method is responsible for  removing the Java Listener from 
   *        receiving events from the Event MultiCaster).
   *
   */
   public Item removeJavaListenerFromG2EventSource(
						   Item g2EventSource,
						   Symbol removerMethodName,
						   String javaProxyClass,
						   Symbol g2ParentClass,
						   Object javaListener)
       throws G2AccessException, RemoteException;

}
