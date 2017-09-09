package com.gensym.controls;

import java.util.EventObject;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.message.MessageEvent;

/** Contains either the resolved Item or an error message with exception that
 * was caught during the attempt to retrieve the item.
 *
 * @author rpenny
 * @version 1.3
 * @see com.gensym.controls.ItemRetriever */
public class ItemRetrievalEvent extends EventObject {

  /** The resolved item */
  public final Item item;
  /** The exception that was caught during the attempt to resolve the item */
  public final G2AccessException exception;
  /** Any message the ItemRetriever added to give any additional explanation
   * as to why the retrieval attempt failed */
  public final MessageEvent message;

  /** Creates an event indicating the successful retrieval of an Item. */
  public ItemRetrievalEvent(Object source, Item item) {
    super(source);
    this.item = item;
    exception = null;
    message = null;
  }

  /** Creates an event indicating that an attempt to resolve an item failed. */
  public ItemRetrievalEvent(Object source,
			    G2AccessException exception, MessageEvent message) {
    super(source);
    item = null;
    this.exception = exception;
    this.message = message;
  }

  /** Returns <code>true</code> if this ItemRetrievalEvent is communicating
   * the failure of an attempt to resolve an item */
  public boolean retrievalFailed() {
    return (message != null || exception != null || item == null);
  }

  /**
   * Returns the retrieved item.
   *
   * @returns the item whose retrieval generated this event. If it is
   * <code>null</code>, then there should be at least a message and
   * possibly an exception giving information as to why the retrieval
   * failed.
   */
  public Item getRetrievedItem () {
    return item;
  }

  /**
   * Returns the exception thrown if retrival failed.
   *
   * @returns the exception (if any) thrown when attempting
   * to retrieve an <code>Item</code> from G2.
   */
  public G2AccessException getException () {
    return exception;
  }

  /**
   * Gives more detail on any failure
   *
   * returns a message event that provides additional information
   * as to the nature of, or reasons for, the failure to retrieve
   * an <code>Item</code> from G2.
   */
  public MessageEvent getMessage () {
    return message;
  }
}
