package com.gensym.message;

import java.util.MissingResourceException;
import java.util.EventObject;
import java.io.*;

/// possible optimizations:
/// 1. could store the final formatted message and only regenerate if
///    the locale changes.

/**
 * Normally MessageEvents are normally created by the class Message or the
 * class Trace.
 * Encapsulates message information that can work in a distributed
 * environment. The translation occurs at the time <code>getMessage</code>
 * is called, using a Resource resolved in the local Java VM.
 *
 * @see com.gensym.message.Resource
 */
public class MessageEvent extends EventObject {

  static final long serialVersionUID = 1L;

  /**
   * @undocumented
   */
  public static final boolean traceOn = false;

  static class NullSource {
      @Override
      public boolean equals(Object source) {
          return true;
      }
      
      @Override
      public int hashCode() {
    	  int prime = 31;
          return prime * NullSource.class.hashCode();
      }
  }

  public static final NullSource NULL_SOURCE = new NullSource();

  //
  // class variables
  //

  //
  // instance variables
  //

  private String key;

  private String messageLookup;

  private int level;

  private String classKeyName;

  private transient Class classKey;

  transient Object[] messageArgs;

  // in case it is not possible to find the Resource when translation
  // is requested.
  private String backupMessage;

  private Resource requestedResource;

  /** Create a new MessageEvent. This signature does not use a registered
   * key, so this is not the preferred constructor.
   * Normally MessageEvents are created by the <code>Message</code> or the
   * <code>Trace</code>.
   * @param level the "verbosity". Higher is more verbose (less likely to be
   * "listened" for).
   * @param key an arbitrary String key for grouping MessageEvents
   * @param classKey a Class to be associated with this MessageEvent. Allows
   * for a hierarchical grouping of messages. Should normally be the class
   * of the object creating the message.
   * @param resource the Resource used to "translate" the full message text.
   * @param messageLookup the key used to look up the full text in
   * <code>resource</code>
   * @param args the arguments used in a call to MessageFormat.format. Any
   * <code>null</code> element is replaced by the string "<NULL>" before
   * the call to <code>format</code>.
   *
   * @see #MessageEvent(int, MessageKey, Resource, String, Object[]).
   */
  public MessageEvent(int level, String key, Class classKey,
		      Resource resource, String messageLookup,
		      Object[] args) {
    this(NULL_SOURCE,level,key,classKey,resource,messageLookup,args);
  }

  /** Creates a <code>MessageEvent</code> with a <code>source</code>.
   * @param level the "verbosity". Higher is more verbose (less likely to be
   * "listened" for).
   * @param key an arbitrary String key for grouping MessageEvents
   * @param classKey a Class to be associated with this MessageEvent. Allows
   * for a hierarchical grouping of messages. Should normally be the class
   * of the object creating the message.
   * @param resource the Resource used to "translate" the full message text.
   * @param messageLookup the key used to look up the full text in
   * <code>resource</code>
   * @param args the arguments used in a call to MessageFormat.format.
   * @see #MessageEvent(Object, int, MessageKey, Resource, String, Object[]).
   */
  public MessageEvent(Object source, int level, String key, Class classKey,
		      Resource resource, String messageLookup,
		      Object[] args) {
    super(source);
    this.level = level;
    this.key = key;
    if(classKey != null) {
      this.classKey = classKey;
      classKeyName = classKey.getName();
    } else {
      this.classKey = Object.class;
      classKeyName = this.classKey.getName();
    }
    this.messageLookup = messageLookup;
    messageArgs = args;
    requestedResource = resource;
  }

  /**
   * Can be used when receiving <code>MessageEvents</code>
   * from the Trace or Message and relaying them on to other
   * listeners. Makes an identical event with a different
   * source.
   * @undocumented
   */
  public MessageEvent makeRelayEvent(Object source, boolean force) {
    if (getSource() == null || force)
      return new MessageEvent(source,level,key,
        classKey,requestedResource,messageLookup,messageArgs);
    else return this;
  }

  /** The constructor typically used when
   * using <code>Message.send</code>
   * @param msgKey: a pre-registered MessageKey. */
  public MessageEvent(int level, MessageKey msgKey, Resource res,
		      String messageLookup, Object[] args) {
    this(level, msgKey.msgKey, msgKey.getMessageClass(),
	 res, messageLookup, args);
  }

  /**
   * The preferred constructor if not sending via the Message class.
   * Normally MessageEvents are created by the class Message or the
   * class Trace.
   * @param msgKey: a pre-registered MessageKey. */
  public MessageEvent(Object source, int level, MessageKey msgKey,
		      Resource res,
		      String messageLookup, Object[] args) {
    this(source, level, msgKey.msgKey, msgKey.getMessageClass(),
	 res, messageLookup, args);
  }

  @Override
  public String toString() {
    return "<" + this.getClass().getName() + ", " + messageLookup + ", " +
      classKey + ", " + requestedResource + ">";
  }

  /** The backup message only needs to be initialized if the
   * MessageEvent is being serialized and there exists the possibility
   * that the target VM may not be able to locate the resource. Given
   * that the target VM may have the resource and the source VM may not,
   * inability to locate the resource during writeObject is not an error.
   * <p>
   * NOTE: if the object is being re-serialized, it is presumed that the
   * current VM is more likely to provide the correct translation than
   * the preceding VM, so the backup message is overwritten if the resource
   * is available.
   */
  private void writeObject(ObjectOutputStream stream) throws IOException{
    String candidateMessage = null;
    try {
      candidateMessage = requestedResource.getString(key);
    } catch (Exception e) {}
    try {
    stream.defaultWriteObject();
    } catch (NotActiveException nae) {
    }
    stream.writeObject(candidateMessage);
    writeMessageArgs(stream);

  }

  private void readObject(ObjectInputStream in)
       throws IOException, ClassNotFoundException
  {
    in.defaultReadObject();

    classKey = Class.forName(classKeyName);
    backupMessage = (String)in.readObject();
    readMessageArgs(in);
  }

  private void convertArgsToStrings() {
    if (messageArgs == null)
      return;
    for (int i = 0 ; i<messageArgs.length; i++) {
      Object arg = messageArgs[i];
      if (arg == null)
	messageArgs[i] = "<NULL>";
      else
	messageArgs[i] = arg.toString();
    }
  }
    

  private void writeMessageArgs(ObjectOutputStream stream)
  throws IOException {
    convertArgsToStrings();
    stream.writeObject(messageArgs);
  }
    
  private void readMessageArgs(ObjectInputStream in)
  throws IOException, ClassNotFoundException {
    try {
      messageArgs = (Object[])in.readObject();
    } catch (OptionalDataException ode) {
      if (traceOn)
	ode.printStackTrace();
    }
  }

  /** Returns the localized, formatted message string for presentation
   * to the final consumer of the MessageEvent (typically the end user).
   * The elements of the Object array will be converted to strings using
   * the toString() method.
   * Any <code>null</code> element in <code>args</code>is replaced by the string
   * "<NULL>" before the call to <code>MessageFormat.format</code>.
   */
  public String getMessage() throws MissingResourceException {

    String localMessage = backupMessage;

    try {
      localMessage = requestedResource.getString(messageLookup);
    } catch (Exception ex) {
      ex.printStackTrace();
      ex.fillInStackTrace();
      throw new MissingResourceException("Can't translate message",
					 requestedResource.getResourceName(),
					 key);
    }

    convertArgsToStrings();
    if (localMessage == null)
      return null;
    if (messageArgs != null) {
      return java.text.MessageFormat.format(localMessage, messageArgs);
    } else
      return localMessage;
  }

  /** The key that groups various MessageEvents */
  public String getMessageKey() {
    return key;
  }

  /** The verbosity level of this MessageEvent. Higher is more verbose, and
   * therefore less likely to be listened for */
  public int getMessageLevel() {
    return level;
  }

  /** Returns the string that is used to look for the translated message
   * in the Resource */
  public String getMessageLookup() {
    return messageLookup;
  }

  /** The Resource used to find the full text of the message */
  public Resource getResource() {
    return requestedResource;
  }

  /** the java Class associated with this MessageEvent */
  public Class getMessageClassKey() throws ClassNotFoundException {
    if (classKey == null)
      classKey = Class.forName(classKeyName);
    return classKey;
  }

}
    
