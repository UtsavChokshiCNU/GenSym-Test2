
package com.gensym.classes;

import com.gensym.classes.Item;

public class InvalidItemException extends RuntimeException {

  private Item item;

  public InvalidItemException (Item itm) {
    super ();
    item = itm;
  }

  public InvalidItemException (Item itm, String details) {
    super (details);
    item = itm;
  }

  public Item getItem () {
    return item;
  }

}
