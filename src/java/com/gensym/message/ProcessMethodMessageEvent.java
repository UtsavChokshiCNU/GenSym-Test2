package com.gensym.message;

/**
 * A ProcessMethodMessageEvent contains information about a message generated from
 * a process method usually via a <code>ProcessTrace</code>.
 * Encapsulates message information that can work in a distributed
 * environment. 
 * 
 * @see com.gensym.message.Resource
 * @see com.gensym.ProcessTrace;
 */
public class ProcessMethodMessageEvent extends ProcessMessageEvent
{

  static final long serialVersionUID = 1L;

  /** A constant to signal that this message came from inside a method
   */
  public static final int METHOD_INNER = 0;

  /** A constant to signal that this message was generated on entry to a method
   */
  public static final int METHOD_ENTRY = 1;

  /** A constant to signal that this message was generated just before exit from a method
   */
  public static final int METHOD_EXIT = 2;

  /** A constant to signal that this message was generated after an exception from this method
   */
  public static final int METHOD_EXCEPTION = 3;

  private String methodName;
  private int messageType;
  private String returnObjectStr;

   /** Creates a <code>ProcessMethodMessageEvent</code>.
    *@param source the non-null source of this object.
   * @param level the "verbosity". Higher is more verbose (less likely to be
   * "listened" for).
   * @param processID a non-null String identifing the process.
   * @param key an arbitrary String key for grouping MessageEvents
   * @param classKey a Class to be associated with this MessageEvent. Allows
   * for a hierarchical grouping of messages. Should normally be the class
   * of the object creating the message.
   * @param methodName The name of the Method.
   * @param resource the Resource used to "translate" the full message text.
   * @param messageLookup the key used to look up the full text in
   * <code>resource</code>
   * @param args the arguments used in a call to MessageFormat.format.
   * @param returnVal the possible-null return value when messageType = METHOD_EXIT
   */
  public ProcessMethodMessageEvent(Object source,
				   String processID,
				   int level,
				   MessageKey key,
				   int messageType,
				   String methodName,
				   Resource resource,
				   String messageLookup,
				   Object[] args,
				   Object returnVal)
  {
    super(source, processID, level, key,  resource, messageLookup, args);
    this.methodName = methodName;
    this.returnObjectStr = (returnVal == null ? null : returnVal.toString());
    this.messageType = messageType;
  }

  /**
   * Get the method name associated with this event.
   */
  public String getMethodName()
  {
    return methodName;
  }

  /**
   * Get the value returned as a string (if message type is METHOD_EXIT).
   */
  public String getReturnAsString()
  {
    return returnObjectStr;
  }

  /**
   * Get the message type of this event.
   */
  public int getMessageType()
  {
    return messageType;
  }

  /** 
   * Get the message type of this event as a string.
   */
  public String getMessageTypeAsString()
  {
    switch (messageType) {
    case METHOD_INNER: return "inner";
    case METHOD_ENTRY: return "entering";
    case METHOD_EXIT: return "exiting";
    default:
    }
    return "";
  }

  /**
   * Get the arguments associated with this method.
   */
  public Object[] getMessageArgs()
  {
    return messageArgs;
  }

}
