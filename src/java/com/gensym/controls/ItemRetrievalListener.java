package com.gensym.controls;

import java.util.EventListener;

/** Beans that wish to request the "retrieval" of an item can asynchronously
 * receive notification of that "retrieval" through this interface.
 *
 * @author rpenny
 * @version 1.1
 * @see com.gensym.controls.ItemRetriever */
public interface ItemRetrievalListener extends EventListener {

  /** Notification that the requested G2 item has been sucessfully resolved */
  public void itemRetrieved(ItemRetrievalEvent event);

  /** Notification that the request to resolve a G2 Item has failed */
  public void itemRetrievalFailed(ItemRetrievalEvent event);
  
}
