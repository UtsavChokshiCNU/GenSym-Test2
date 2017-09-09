package com.gensym.message;

/**
 * A ProcessMessageEvent contains information about a message generated from
 * a process usually via a <code>ProcessTrace</code>.
 * Encapsulates message information that can work in a distributed
 * environment. 
 * 
 * @see com.gensym.message.Resource
 * @see com.gensym.ProcessTrace;
 */
public class ProcessMessageEvent extends MessageEvent
{

  static final long serialVersionUID = 1L;

  private String processID;

   /** Creates a <code>ProcessMessageEvent</code> with a <code>source</code>.
   * @param level the "verbosity". Higher is more verbose (less likely to be
   * "listened" for).
   * @param processID a non-null String identifing the process.
   * @param key an arbitrary String key for grouping MessageEvents
   * @param classKey a Class to be associated with this MessageEvent. Allows
   * for a hierarchical grouping of messages. Should normally be the class
   * of the object creating the message.
   * @param resource the Resource used to "translate" the full message text.
   * @param messageLookup the key used to look up the full text in
   * <code>resource</code>
   * @param args the arguments used in a call to MessageFormat.format.
   */
  public ProcessMessageEvent(Object source,
			     String processID,
			     int level,
			     String key,
			     Class classKey,
			     Resource resource,
			     String messageLookup,
			     Object[] args)
  {
    super(source, level, key, classKey, resource, messageLookup, args);
    this.processID = processID;
  }

  /** Creates a <code>ProcessMessageEvent</code> with a <code>source</code>.
   * @param level the "verbosity". Higher is more verbose (less likely to be
   * "listened" for).
   * @param processID a non-null String identifing the process.
   * @param messageKey an arbitrary  key for grouping MessageEvents with
   *                    a Class to be associated with this MessageEvent. Allows
   *                    for a hierarchical grouping of messages. Should normally be the class
   *                    of the object creating the message.
   * @param resource the Resource used to "translate" the full message text.
   * @param messageLookup the key used to look up the full text in
   * <code>resource</code>
   * @param args the arguments used in a call to MessageFormat.format.
   */
  public ProcessMessageEvent(Object source,
			     String processID,
			     int level,
			     MessageKey messageKey,
			     Resource resource,
			     String messageLookup,
			     Object[] args)
  {
    super(source, level, messageKey, resource, messageLookup, args);
    this.processID = processID;
  }

  /**
   * Return the processID for this ProcessMessageEvent.
   * @return The non-null processID of this ProcessMessageEvent.
   */
  public String getProcessID()
  {
    return processID;
  }

}

