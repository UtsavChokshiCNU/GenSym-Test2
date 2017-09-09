package com.gensym.ntw.util;

public interface CollectionListener extends java.util.EventListener {

  /**
   * Invoked when the collection changes
   */
  public void collectionChanged(CollectionEvent collectioinEvent);

}
