package com.gensym.dlgevent;

import java.util.EventObject;
import com.gensym.classes.Item;

public class ItemDeletionEvent extends EventObject {
  
  static final long serialVersionUID = 2L;

  public ItemDeletionEvent(Object source, Item deletedItem) {
    super(source);
    this.deletedItem = deletedItem;
  }

  private Item deletedItem;

  public Item getDeletedItem(){
      return deletedItem;
  }
}
