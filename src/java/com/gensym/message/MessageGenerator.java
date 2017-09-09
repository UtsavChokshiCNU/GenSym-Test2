package com.gensym.message;

/**
 * This interface can be used to mark a class that is capable of providing Trace messages.
 * Trace messages are pushed to MessageListeners who subscribe to a MessageGenerator object.
 */
public interface MessageGenerator
{

  /**
   * Subscribe a MessageListener to receive Trace messages from this Traceable object.
   * @param listener The non-null MessageListener.
   * @param key A non-null String detailing the trace topic the subscriber is interested in.
   * @param classKey A non-null Class detailing the Class of the trace message generators that
   *        the subscriber is interested in.
   * @param level An int detailing the level at which level of messages the subscriber wises to
   *        to receive messages.
   */
  public void addMessageListener(MessageListener listener,
				 String topic,
				 Class classKey,
				 int level);
  
  /**
   * Remove a MessageListener from subscribing to Trace messages.
   * @param listener The non-null MessageListener no-longer interested in messages.
   */
  public void removeMessageListener(MessageListener listener);

}
