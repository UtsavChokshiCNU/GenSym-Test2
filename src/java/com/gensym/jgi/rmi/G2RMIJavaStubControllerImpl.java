package com.gensym.jgi.rmi;

import java.rmi.*;
import com.gensym.jgi.*;
import com.gensym.classes.Item;
import com.gensym.classes.ItemImpl;
import com.gensym.util.Symbol;


/**
 * This subclass of G2JavaStubController overrides G2JavaStubController methods
 * which need to operate differently, depending whether the Items being passed
 * are created over a RMI context or a normal middle tier context.
 */
public class G2RMIJavaStubControllerImpl extends G2JavaStubController
        implements G2RMIJavaStubController {

  private static boolean isRMIExported = false;

  /** Use this method to access the G2RMIStubController for this VM
   */
  public static synchronized G2JavaStubController getG2JavaStubController() {
    if (controller == null) {
      synchronized (G2JavaStubController.class) {
        if (controller == null)
          controller = new G2RMIJavaStubControllerImpl();
      }
    }
    return controller;
  }

  /**
   * Export the VM's G2RMIJavaStubController if not already done so.
   */
  public static void exportObject() throws java.rmi.RemoteException {
    if (!isRMIExported) {
      java.rmi.server.UnicastRemoteObject.exportObject((G2RMIJavaStubController)getG2JavaStubController());
      isRMIExported = true;
    }
  }

 /**
   * Add Java object as a listener for events from a G2 Event Source.
   *
   *@param g2EventSource The G2 Item that the Java Object will be listening too
   *@param adderMethodName The G2 Method name on g2EventSource for adding this listener
   *@param javaProxyClass The name of the Java listener class of which we are interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   * 
   */
   @Override
   public Item addJavaListenerToG2EventSource(
					      Item  g2EventSource,
					      Symbol adderMethodName,
					      String javaProxyClass,
					      Symbol g2ParentClass,
					      Object javaListener)

       throws G2AccessException {
    try {
      Item itm = null;
      G2Connection context = (G2Connection)((ItemImpl)g2EventSource).getContext();

      // Special case for remote RemoteG2JavaStubControllerAccess
      if (context instanceof RemoteG2JavaStubControllerAccess) {
	G2RMIJavaStubController remoteController = 
	  ((RemoteG2JavaStubControllerAccess)context).getRemoteG2JavaStubController();

	// We pass our own context as the JavaListener
	// It will be used to create a G2JavaStubControllerListener that will update this VM
	// when events occur from g2EventSource
	itm =  remoteController.addJavaListenerToG2EventSource(
							       g2EventSource,
							       adderMethodName,
							       javaProxyClass,
							       g2ParentClass,
							       context);
	//System.out.println("Context " + context + "Got proxy " + itm  + "from  " + remoteController );
	// Locally , we will still need to resolve the G2 proxy created to receive the events
	// against the original Java Listener
	associate(context, itm, javaListener);
      } else
	itm = super.addJavaListenerToG2EventSource(
						   g2EventSource,
						   adderMethodName,
						   javaProxyClass,
						   g2ParentClass,
						   javaListener);
      return itm;
    } catch (RemoteException re) {
      throw new G2AccessException(re);
    }
  }


       
  /**
   * Remove a Java Object from listening for events from a G2 Event Source
   *
   *@param g2EventSource The G2 Item that the Java Object was listening too
   *@param removerMethodName The G2 Method name on G2EventSource for removing this listener
   *@param javaProxyClass The name of the Java listener class of which we where interested in
   *@param g2ParentClass The G2 class that the proxy class will inherit from in G2
   *@param javaListener The Java Listener object
   *
   */
   @Override
   public Item removeJavaListenerFromG2EventSource(
						   Item g2EventSource,
						   Symbol removerMethodName,
						   String javaProxyClass,
						   Symbol g2ParentClass,
						   Object javaObject)
       throws G2AccessException {
    try {
      Item itm = null;
      G2Connection context = (G2Connection)((ItemImpl)g2EventSource).getContext();

     // Special case for remote RemoteG2JavaStubControllerAccess
     if (context instanceof RemoteG2JavaStubControllerAccess) {
	G2RMIJavaStubController remoteController = 
	  ((RemoteG2JavaStubControllerAccess)context).getRemoteG2JavaStubController();

	// As we added our context when we added this client as a listener
	// we must remote it
	itm =  remoteController.removeJavaListenerFromG2EventSource(
							  g2EventSource,
							       removerMethodName,
							       javaProxyClass,
							       g2ParentClass,
							       context);
      } else
	itm =  super.removeJavaListenerFromG2EventSource(
							 g2EventSource,
							       removerMethodName,
							       javaProxyClass,
							       g2ParentClass,
							       javaObject);
      return itm;
    } catch (RemoteException re) {
      throw new G2AccessException(re);
    }
  }
}
