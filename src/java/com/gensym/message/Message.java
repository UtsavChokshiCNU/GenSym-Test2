/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Message.java
 *
 *  Description:
 *              A static class for sending translatable and
 *              serializable messages, with a flexible way of
 *              categorizing the messages and registering interest
 *              in various categories of messages.
 *
 *	 Author:
 *		Robert Penny		Jul/97
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.message;
import java.util.*;

/** Provides the base methods for issuing messages to listeners.
 * <p>
 * Messages are always associated with a particular key, and there
 * is an open-ended idea of "levels of verboseness" associated with each
 * message that can vary from key to key, thought the first
 * few "levels of verbosity" are well-defined. Facilities are provided
 * for runtime control of which messages are sent to where.
 * <p>
 * The <code>classKey</code> arguments are provided to allows for flexible
 * categorizations of messages. Interfaces are allowable and work as expected
 * because <code>isAssignableFrom</code> is the test used to compare classes.
 * <p>
 * Because <code>send</code> does not and should not have functional
 * implications on the applications using it, the <code>send</code> calls
 * are not 
 * <code>synchronized</code>. As a result, if a listener or key is being added
 * or removed when a call to <code>send</code> is being made, it is
 * unpredicatable as to which listeners will receive the messages.
 * <p>
 * It cannot be instantiated. 
 * @see Resource
 */

public class Message {

  /** To allow open-ended (positive) integer levels, a special value
   * for <code>level</code> can be specified when adding listeners
   * @see Message#addMessageListener
   */
  public static final int ALL_LEVELS = -1;

  /** The table for "listener" information about keys: what listeners
   * have registered interest in this key, and the details of their interest.
   */
  private static Hashtable messageSubscriptions = new Hashtable();

  // contains information about the message keys. Information such
  // which classes use a given key, and any "documentation" that is associated
  // with the key.
  private static Hashtable keyInfoTable = new Hashtable();

  // When doing class-based subscriptions, one needs to know what
  // keys and subscribers are associated with which classes.
  private static Hashtable classTable = new Hashtable();

  private static Resource i18n =
  Resource.getBundle("com.gensym.message.Messages");

  /** prevent instantiation, but not subclassing */
  protected Message() {
  }

  static Enumeration getSubscriptions(String key) {
    Vector listeners = (Vector)messageSubscriptions.get(key);

    if (listeners != null)
      return listeners.elements();
    else
      return null;
  }

  /** Sends the <code>MessageEvent</code> to any listeners that have
  * registered interest in this kind of event.
  * @see addMessageListener */
  public static boolean send(MessageEvent message) {
    Enumeration listeners =
      getSubscriptions(message.getMessageKey());

    if (listeners != null)
      return send(message, listeners);
    else
      return false;
  }

  // If this method is made available to subclasses outside this package,
  // One would have to make MessageSubscription public, in which case
  // interestedInMessage should be at least protected. getSubscriptions()
  // could also be made at least protected at the same time.
  /** A subclass can decide for itself what its list of listeners is.
   * @param listeners the Enumeration must contain only
   * MessageSubscription objects.
   * @undocumented
   */
  static boolean send(MessageEvent message, Enumeration listeners) {
    boolean anySent = false;
    int level = message.getMessageLevel();
    Class classKey = Object.class;
    try {
      classKey = message.getMessageClassKey();
    } catch (ClassNotFoundException cnfe) {
      // uses Object if the class is not available.
    } 
    for(; listeners.hasMoreElements();) {
      MessageSubscription sub = (MessageSubscription)listeners.nextElement();
      if (sub.interestedInMessage(classKey, level)){
	anySent = true;
	try {
	  sub.listener.processMessageEvent(message);
	} catch (Exception ex) {
	  ex.printStackTrace();
	  //try {
	    //System.err.println(i18n.getString(ex.toString()));
	  //} catch (Exception ex2) {
	  //  ex2.printStackTrace();
	  //}
	  System.err.println(message.getMessageLookup());
	}
      }
    }
    // fix this: is this interesting? Is the number of messages sent
    // more interesting? Is any of this interesting? should it return
    // void?
    return anySent;
    
  }

  /** Register the combination of a key and a class as being a possible
   * combination of interest for a MessageListener. */
  public static MessageKey registerMessageKey(String key, Class classKey) {
    return _registerMessageKey(key, classKey, null, null, null);
  }

  /** Provide documentation regarding what kind of messages
   * are associated with this particular key. Registration of
   * keys allows other classes to be able to discover what kinds
   * of keys are available for listening to.
   */
  public static MessageKey registerMessageKey(String key, Class classKey,
					      Resource resource,
					      String shortDescriptionKey,
					      String longDescriptionKey)
  {
	 if (shortDescriptionKey == null)
	   throw new NullPointerException(i18n.getString("Message_noShortDescription"));

	 KeyInfo keyInfo = (KeyInfo)keyInfoTable.get(key);

	 return _registerMessageKey(key, classKey, shortDescriptionKey,
				    longDescriptionKey, resource);
  }

  private static MessageKey _registerMessageKey(String messageKey,
					     Class classKey, 
					     String shortDescriptionKey,
					     String longDescriptionKey,
					     Resource resource) {
    KeyInfo keyInfo = (KeyInfo)keyInfoTable.get(messageKey);
    
    if (keyInfo == null) {
      keyInfo = new KeyInfo(messageKey, classKey,
			    shortDescriptionKey,
			    longDescriptionKey,
			    resource);
      keyInfoTable.put(messageKey, keyInfo);
    } else {
      keyInfo.addClass(classKey);
    }
      
    _registerMessageClass(classKey, messageKey);
    
    return new MessageKey(messageKey, classKey);
  }

  private static void _registerMessageClass(Class classKey, String messageKey)
  {
    Vector keyVector = (Vector)classTable.get(classKey);

    if (keyVector == null)
      keyVector = new Vector();
    
    if(!keyVector.contains(messageKey))
      keyVector.addElement(messageKey);

    classTable.put(classKey, keyVector);
  }

  /** Adds the MessageListener to the list of listeners interested in
   * notifications associated with a given key and class. Also indicates
   * the level of verbosity of the MessageEvent's that the listener would
   * like to receive.
   * @param level all message calls whose <code>level</code> is less than or
   * equal to this <code>level</code> will be sent to this listener. If
   * <code>level</code> is less than 0, then all MessageEvents will be sent
   * to <code>listener</code>
   * @see Message.ALL_LEVELS */
  public static synchronized void addMessageListener(MessageListener listener,
						     String key,
						     Class classKey,
						     int level) {
    Vector listeners = (Vector)messageSubscriptions.get(key);
    //System.out.println ("Adding Listener " + listener + " for Key: " + key +
    //" ClassKey = " + classKey + ", Level = " + level);

    if (listeners == null) {
      listeners = new Vector();
      messageSubscriptions.put(key, listeners);
    }

    // fix this: need to decide what to do if already registered in some way
    //    for(Enumeration en = listeners.elements(); en.hasMoreElements;) {
    //  MessageSubscription sub = (MessageSubscription)en.nextElement();
    //  if (sub.listener == listener) {

    listeners.addElement(new MessageSubscription(listener, classKey, level));
	
  }

  /** Add a listener for all classes associated with <code>key</code>.
   * NOTE: UNIMPLEMENTED
   * @see addMessageListener(MessageListener, String, Class, int)
   * @see registerMessageKey
   */
  //  public static synchronized void addMessageListener(MessageListener listener,
  //				String key, int level) {
  //}

  /** Add a listener for all keys associated with <code>classKey</code>
   * NOTE: UNIMPLEMENTED
   * @see addMessageListener(MessageListener, String, Class, int)
   * @see registerMessageKey
   */
  //public static synchronized void addMessageListener(MessageListener listener,
  //				Class classKey, int level) {
  //}

  /** Removes a message listener from the list of those interested in
   * messages with this <code>key</code> and <code>class</code> */
  public static synchronized void removeMessageListener(MessageListener
							listener,
							String key,
							Class classKey) {
    Vector listeners = (Vector)messageSubscriptions.get(key);

    if (listeners != null) {
      for (Enumeration en = listeners.elements(); en.hasMoreElements();) {
	MessageSubscription info = (MessageSubscription)en.nextElement();
	if (info.listener.equals(listener) &&
	    classKey.isAssignableFrom(info.classKey))
	  listeners.removeElement(info);
      }

      if (listeners.isEmpty())
	messageSubscriptions.remove(key);
    }
  }
	  
  //public static synchronized void removeMessageListener(MessageListener
  //						listener,
  //						Class classKey) {
    // fix this: stub
  //}

  /** Ends any subscription to this key for this listener */
  public static synchronized void removeMessageListener(MessageListener
							listener,
							String key) {
    // performance: the isAssignableFrom test is obviously unnecessary,
    // so this call results in an unnecessary test
    removeMessageListener(listener, key, Object.class);
  }

  /** Ends any subscription to any key for this listener.
   */
  public static synchronized void removeMessageListener(MessageListener
						       listener) {
    for (Enumeration en = messageSubscriptions.keys();
	 en.hasMoreElements();) {
      removeMessageListener(listener, (String)en.nextElement());
    }
  }
}

class MessageSubscription {
  final MessageListener listener;
  final Class classKey;
  final int level;

  MessageSubscription(MessageListener listener, Class classKey, int level) {
    this.listener = listener;
    if (classKey == null)
      throw new NullPointerException("MustSpecifyClass");
    this.classKey = classKey;
    this.level = level;
  }

  boolean interestedInMessage(Class classKeyIn, int messageLevel) {
    // fix this: debugging
    return (((messageLevel <= level) || level < 0) &&
	    classKey.isAssignableFrom(classKeyIn));
  }
}
