/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Access.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.jgi;

/* Imports */
import java.lang.reflect.Method;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;


/**
 * This interface class provides the outbound methods
 * required for accessing a connection to G2
 *
 * 
 * @version 	1.2, 22 May 1997
 *
 * @author M.D.Gribble
 */
public interface G2Access
{

  //Public functions



  // **** Public outboud access to G2 connection library ****

  /**
   * Add a G2ConnectionListener, who will be informed of any G2Connection events for
   * a G2 connection.
   */
  public void addG2ConnectionListener(G2ConnectionListener listener); 


  /**
   * Remove a G2ConnectionListener, who was previously listening for G2Connection
   * events.
   */
  public void removeG2ConnectionListener(G2ConnectionListener listener);

  /**
   * Return a message to the connected G2.
   * 
   * <P> The message text is sent to the MESSAGE-BOARD item in the current KB 
   * of the connected G2.
   *
   * @param message the message to send to G2's message board
   */
  public void returnMessage(String message);


  /**
   * Report an Error Message to the Log book of the connected G2.
   * @param errorSymbol A Symbol to identify the error
   * @param errorMessage A String detailing the error
   *
   */
  public  void reportLogBookErrorMessage(Symbol error_symbol, String error_message);

  /** 
   * Close an active connection with a G2.
   * The connection is not alive after this point.
   * Any attempts to call RPCs through this Gateway will
   * fail.
   */
  public void closeConnection();


  /**
   * Determines if this Gateway can be used for RPC calls
   * to G2 or not. It will return true once it has initialized
   * properly and until it is closed (either by a method call
   * or from the server).
   * @return boolean true if it is OK to call RPCs through
   *   this Gateway, false otherwise
   * @see #closeConnection
   */
  public boolean isAlive ();


  /**
   * Register a method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI connection to Javalink then JavaLink will attempt to call 
   * [target].[method_name](params_from_G2_call...).
   * JavaLink will call method_name with the number and type of parameters sent from
   * G2 during the G2 RPC call. If target does not have the corresponding method_name with 
   * the correct parameter signature then JavaLink will raise a java.lang.NoSuchMethodException.
   *
   * Note: For the most optimal performance, it is recommended that Methods are registered
   * with the second variant of this method, where a java.lang.reflect.Method is registered 
   * instead of a method String this saves significant time, as JavaLink does not need to 
   * lookup the registered method each time. However, by registering a method with a string
   * allows JavaLink to dynamically dispatch a method call based on the method name and 
   * the parameters sent from G2.
   *
   * @param target      The object on which the method is to be called.
   * @param method_name The method to made visible.
   * @param g2_RPD_name The G2 REMOTE-PROCEDURE-DECLARATION name to be associated with method_name for target.
   * @exception DuplicateLocalRPCException When g2_RPD_name has already been declared as a G2 RPC.
   */
  public void registerJavaMethod(Object target, 
				 String method_name, 
				 Symbol g2_RPD_name );
   /**
   * Register a prelooked up Method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI-INTERFACE(connected to JAVALINK) then JavaLink will attempt to call
   * [target].[java_method](params...) registered for the RPD name using <B>registerJavaMethod</B>
   * Note, JavaLink will call java_method with the number and type of parameters sent from
   * G2 during the G2 RPC call. If java_method does not have 
   * the correct parameter signature then JavaLink will raise a java.lang.NoSuchMethodException.
   *
   *
   * @param target      The object on which the method is to be called.
   * @param java_method The method to made visible.
   * @param g2_RPD_name The G2 REMOTE-PROCEDURE-DECLARATION name to be associated with method_name for target.
   * @param call_in_new_thread Set true to create a new thread for the execution of the method
   *                           otherwise a G2 RPC call to Java will be queued with all other
   *                           method calls for this G2Connection.
   * @exception DuplicateLocalRPCException When g2_RPD_name has already been declared as a G2 RPC.
   */
  public void registerJavaMethod(Object target, 
				 Method java_method,
				 Symbol g2_RPD_name, 
				 boolean call_in_new_thread );

  /**
   * Call a predeclared G2 procedure/method synchronously (wait until the call returned or a timeout)
   * The current thread will wait until the remote G2 has executed.
   * <P>To call a G2 method the first argument in args must be a G2 Item of the 
   * appropriate class.</P>
   * 
   * @param g2_procedure_name  The predeclared G2 procedure/method to call.
   * @param args   The Object array to pass to the G2 procedure/method as its arguments.
   * @param timeout Time in milliseconds to wait for the return, 0 for indefinite.
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @exception TimeoutException if the the RPC takes longer than the timeout period.
   * @Exception ConnectionNotAliveException when the G2Connection is not currently connected to a G2.
   * @return The result of the G2 procedure/method.
   */
  public Object callRPC (Symbol g2_procedure_name, 
			 Object args[], 
			 int timeout)
       throws G2AccessException;


  /**
   * Call a predeclared G2 procedure/method synchronously (wait until then call returned or 
   * a timeout).
   * The current thread will wait until the remote G2 has executed.
   * <P>To call a G2 method the first argument in args must be a G2 Item of the 
   * appropriate class.</P>
   *
   * @param g2_procedure_name  The predeclared G2 procedure to call.
   * @param args   The Object array to pass to the G2 procedure/method as its arguments.
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @exception TimeoutException if the the RPC takes longer than the default timeout period.
   * @Exception ConnectionNotAliveException when the G2Connection is not currently connected to a G2.
   * @return The result of the G2 procedure/method.
   */
  public Object callRPC (Symbol g2_procedure_name, 
				    Object args[])
       throws G2AccessException;

  /**
   * Start a predeclared remote G2 procedure, ignore any return values.
   * The method returns Immediately. The G2 procedure must have been
   * previously declared using method <B>declareRemoteRPC</B>
   *
   * @param g2_procedure_name  The G2 procedure to call
   * @param items  The array of objects to pass as arguments
   */
  public void startRPC(Symbol g2_procedure_name, 
		       Object items[]);

  /**
   * Indicates whether this thread can successfully call an RPC synchronously
   * If this call returns false, then a call to <code>callRPC</code> will throw
   * an Exception.
   * @return true if synchronous RPC calls are allowed in the current Thread,
   *   false otherwise.
   */
  public boolean canCallRPC ();

  /**
   * Set the value type of the return type of a object parameter from a remote RPC call
   * @param return_value_type either PASS_BY_COPY or PASS_BY_HANDLE
   */
  public void setRemoteRPCReturnKind (Symbol g2_procedure_name,
						    int return_value_type);

  /**
   *
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object.
   *
   *@param javaProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param g2ParentClass the G2 class created that will inherit from this G2 Class
   *@param javaObject the Java Object to create a proxy for.
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  public Item getG2ProxyForJavaObject(String javaProxyClass,
				      Symbol g2ParentClass,
				      Object javaObject)
       throws G2AccessException;



  // Introspection Access
       
  /**
   * Retrieves a specific named Item from a G2. Use this
   * method to get a "root" item after making a connection to G2.
   * @param itmClass a Symbol naming the class of the Item
   * @param itmName the name of the Item
   * @return the requested Item
   * @exception G2AccesException if any error occurs during communication or if
   *   no such Item exists
   */
  public Item getUniqueNamedItem (Symbol itmClass,
				    Symbol itmName) 
       throws G2AccessException ;


  /**
   * Retrieves a specific Item with the specified uuid from a G2. Use this
   * method to get a "root" item after making a connection to G2.
   * Requires G2 version 6.0 or greater
   * @param uuid a String specifying the uuid of the Item;
   * @return the requested Item
   * @exception G2AccessException if any error occurs during communication or if
   *   no such Item exists
   */         
  public Item getItemWithUUID(String uuid) throws G2AccessException;
       
  /**
   * @undocumented
   */
  public String getAttributeAsText (Item itm,
				    Symbol slotName,
				    Symbol specificClassIfAny) 
       throws G2AccessException ;

  /**
   * Returns the ClassManager used to manage classes for this connection.
   *
   */
  public ClassManager getClassManager();

  /**
   * Returns the java <code>Class</code> for the interface
   * corresponding to the G2 class named by the argument.<p>
   * <bold>Note:</bold> This method must only be called on
   * an active connection.
   * @param className_ the name of a G2 class
   * @return the Class for the corresponding interface
   */
  public Class getInterfaceForG2Class (Symbol className_);
       
  /**
   * @undocumented For Gensym use only. Used by the stub loader to initialize class info
   */
  public Object getClassAttributeValue (Symbol className,
					Symbol attrName)
       throws G2AccessException ;

  /**
   * @undocumented For Gensym use only. Used by the stub loader to initialize class info
   */
  public Structure getClassAttributeValues (Symbol className,
					 Sequence attrNames)
       throws G2AccessException ;

  /**
   * Returns a Sequence of structures describing each attribute of the class
   * (See Attribute Export for details of the format of this information)
   * @param className a Symbol naming the G2 class
   * @param attributeNames a Sequence of symbols naming attributes of <code>
   *          className</code> for which to retreive attribute descriptions.
   *          A zero length Sequence may be passed in to retreive the
   *          descriptions of <bold>all</all> attributes.
   * @return A Sequence containing structures, each of which is a description
   *           of an attribute of the class.
   */
  public Sequence getAttributeDescriptions (Symbol className, Sequence attributeNames) 
       throws G2AccessException;

  /**
   * @param itm The item for which updates are being requested.
   * @param denotation a sequence specifying the path from itm to the place being observed
   * @param userData any user-defined data included in the callback
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   *
   * @undocumented
   */
  public Structure subscribeToItem (Item itm,
				    Sequence denotation,
				    Object userData) throws G2AccessException;

  /**
   * Removes a subscription.
   * @param subscrpnHandle the Integer obtained from subscribeToItem
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   *
   * @undocumented
   */
  public boolean unsubscribeToItem (int subscrpnHandle) throws G2AccessException;
       
 /**
   * @param itm The item for which updates are being requested.
   * @param denotations a sequence specifying the path from itm to the place being observed
   * @param userData any user-defined data included in the callback
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   *
   * @undocumented
   * @author fy 02/22/00
   */
  public Sequence subscribeToItemMultiple (Item itm, Sequence denotation_sequences, java.lang.Object userData) throws G2AccessException;

  /**
   * Removes a set of subscriptions.
   * @param subscrpnHandles the array of Integers obtained from subscribeToItem
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   *
   * @undocumented
   * @author fy 02/22/00
   */
  public boolean unsubscribeToItemMultiple (Sequence subscrpnHandles) throws G2AccessException;

  /**
   * Returns the current system time in the connected G2
   * @return The current unix system time (elapsed since Jan 1, 1970) at the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */

  public double g2UnixTime() throws G2AccessException;

  /**
   * Returns the time when G2 was started most recently.
   * @return The double value of the time when G2 was most recently started.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public double g2UnixTimeAtStart() throws G2AccessException;

  /**
   * Gets the host name of the machince on which the connected G2 is running on.
   * @return The machine's host name of the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetHostName() throws G2AccessException;

  /**
   * Gets the TCP/IP port number or name on which the connected G2 is listening for network connections.
   * @return The connected G2's listener TCP/IP port number or port name as a String.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetPortNumberOrName() throws G2AccessException;

  /**
   * Returns the current port number or name based on a network type index.
   * @param index An integer of 1 or 2.
   * @return A Text string of the current port number or name.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetPortNumberOrNameGivenIndex(int index) throws G2AccessException;

  /**
   * Gets the current version of the G2 Software.
   * @return A String value of the system and software version of the connected G2 process.
   * @exception G2AccessException When there is a problem communicating with G2.
   */
  public String g2GetSoftwareVersion() throws G2AccessException;


  /**
   * @undocumented
   */
  public G2Version getG2Version ();

  public boolean getSecureContext ();

  /** 
   * Returns the current run state of G2.
   * @return a symbol that is one of RUNNING, PAUSED, or RESET
   * @exception G2AccesException if any error occurs during communication
   *   with G2
   * @see G2Gateway#getG2State
   * @see G2Gateway#RUNNING_
   * @see G2Gateway#PAUSED_
   * @see G2Gateway#RESET_
   */
  public Symbol getG2State() throws G2AccessException;

  /**
   * Sets the run state of G2. In order to restart G2, first change to
   * RESET then change to RUNNING.
   * @param the desired new state of G2. This should be one of the following
   *   Symbols - RUNNING, PAUSED, or RESET
   * @exception G2AccesException if any error occurs during communication
   *   with G2
   * @see G2Gateway#getG2State
   * @see G2Gateway#RUNNING_
   * @see G2Gateway#PAUSED_
   * @see G2Gateway#RESET_
   */
  public Symbol setG2State(Symbol newState) throws G2AccessException;


  /**
   * Retreives all strict instances of a given class. In other words,
   * given a class A and its subclass B, assuming instances of both A
   * and B exist in the KB, <code>getStrictInstancesOfClass (A)</code>
   * will not include instances of B. In order to gather all instances of
   * a class including subclasses, use <code>getDirectSubClasses</code>
   * and call <code>getStrictInstances</code> recursively.
   * <code>getStrictInstancesOfClass</code> returns stubs (by-handle) not objects
   * (by-copy) so there will be no attribute downloading.
   * @param g2ClassName_ a Symbol naming a class
   * @return a Sequence of 0 or more Items of the class g2ClassName_
   * @see #getDirectSubClasses
   * @exception G2AccessException if there any errors during communication or within the call
   */
  public Sequence getStrictInstancesOfClass (Symbol g2ClassName_) throws G2AccessException;


 /**
   * Retreives the names of all direct subclasses of a given class.
   * Use this method recursively to gather all subclasses of a given class.
   * @param g2ClassName_ a Symbol naming a class
   * @return a Sequence of Symbols naming the direct subclasses
   * @exception G2AccessException if there any errors during communication or within the call
   */
  public Sequence getDirectSubclasses (Symbol g2ClassName_) throws G2AccessException;

  /**
   * Returns a string that refers to this particular G2
   * @return a String describing this connection suitable for use in a URL
   * @undocumented For Gensym use only. Used to create G2 URLs
   */
  public String toURLString ();

  /**
   * Returns a short description of this connection
   * @return a String that contains the host and port info for this connection
   * @undocumented For Gensym use only. Used to display current connection in TW tool-bar.
   */
  public String toShortString ();

  /** Sets the debugging state of the underlying g2 interface class. Should
   * avoid using this in three-tier situations, as others may be using
   * the middle tier that is slowed down by turning on debug. */
  public void setInterfaceDebugOptions(boolean on);


  /** Sets the debugging level of the underlying g2 interface class.*/
  public void setInterfaceDebugOptions(int level);


  /**
   * Creates a new Item in G2 and returns it
   * @param className a Symbol naming the class of the item to create
   * @exception G2AccessException if any error occurs while communicating
   *   with G2
   */
  public Item createItem (Symbol className) throws G2AccessException;


  /**
   * Returns the item-or-value that is obtained by travesing the denotation from
   * the item as root.
   * @itm the root item
   * @denotation the denotation to traverse
   * @exception G2AccessException if any error occurs during communication or
   *   within the call
   * @undocumented For Gensym use only. Others should use com.gensym.classes.Item#getPropertyValue
   *   or other public methods.
   */
  public Object getValue (Item itm,
			  Denotation denotation)
       throws G2AccessException ;


  /**
   * Concludes the value at the place pointed to by the denotation
   * @itm the root item
   * @denotation the denotation to traverse
   * @value the new value for the place
   * @exception G2AccessException if any error occurs during communication or
   *   within the call
   * @undocumented For Gensym use only. Others should use com.gensym.classes.Item#setPropertyValue
   *   or other public methods.
   */
  public boolean setValue (Item itm,
			   Denotation denotation,
			   Object value) 
       throws G2AccessException ;

  /**
   * Returns the definition Item for any G2 class
   * @exception G2AccessException when a problem occurs as a result
   *   of communicating with G2.
   */
  public G2Definition getDefinition (Symbol g2ClassName)  throws G2AccessException;

  /**
   * This method allows groups of "by-handle" items to have their attributes updated "in-place".
   * JavaLink will update the items as a group using one remote call to G2. 
   * Note, all Items updated by this call must have been downloaded from this
   * connection.
   * @param items The "by-handle" items referring to items in the G2 across this connection
   * @param attributesArray Structure containing values of named attributes to be overwritten. 
            Set null for no attributes changes.
   * @param values If the items are Gsi-Variables, this array contains the new values for the 
   *               each variable. Set to null if the items are not Gsi-Variables.
   * @param statusValues If the items are Gsi-Variables, this arrat contains the new status for
   *               each variable, Set to null if the items are not Gsi-Variables.
   * @undocumented For gensym internal use only
   */
  public void returnValues(Item[] items, 
			  Structure[] attributesArray, 
			  Object[] values, 
			  int[] statusValues);
}
