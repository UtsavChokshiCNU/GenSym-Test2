package com.gensym.util;

import java.util.Locale;
import com.gensym.message.Resource;
import com.gensym.message.MessageEvent;

/**
 * Provides easy facilities for making translatable exceptions. Is a
 * wrapper around MessageEvent. The MessageEvent is created with its
 * <code>classKey</code> set to the class of the exception, and a
 * <code>messageKey</code> of "exception".
 * @see com.gensym.util.MessageEvent
 */

public abstract class TranslatableException extends Exception {

  private static final String MESSAGE_KEY = "Exception";
  private static final Class CLASS_KEY = Exception.class;
  private MessageEvent messageEvent;
  private Throwable nestedException;

  public TranslatableException() {
    super();
  }

  /**
   * Embeds a MessageEvent with the given Resource and Key.
   * @param res The Resource object that will perform the lookup
   * @param key The key that will be looked up in the Resource
   */
  public TranslatableException(Resource res, String key) {
    messageEvent = new MessageEvent(0, MESSAGE_KEY, this.getClass(),
				    res, key, null);
  }

  /**
   * Embeds a MessageEvent with the given Resource, key, and args.
   * @param res The Resource object that will perform the lookup
   * @param key The key that will be looked up in the Resource
   * @param args The object array that will be "formatted" into the
   * template found by <code>key</code>
   */
  public TranslatableException(Resource res, String key, Object[] args) {
    messageEvent = new MessageEvent(0, MESSAGE_KEY, this.getClass(),
				    res, key, args);
  }

  /**
   * Embeds the MessageEvent
   */
  public TranslatableException(MessageEvent event) {
    messageEvent = event;
  }

  public MessageEvent getMessageEvent() {
    return messageEvent;
  }

  @Override
  public String getMessage() {
    if (messageEvent == null)
      return null;
    else
      return messageEvent.getMessage();
  }

  @Override
  public String toString() {
    return super.toString() + ":[" + messageEvent + "]";
  }
}
