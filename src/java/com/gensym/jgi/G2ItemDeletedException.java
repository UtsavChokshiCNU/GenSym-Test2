
package com.gensym.jgi;

import com.gensym.classes.Item;

/**
 * An exception that is thrown whenever a deleted item
 * is passed to G2 as an argument of an RPC call.
 *
 * @version 1.0 7/21/98
 * @author  vkp
 */
public class G2ItemDeletedException extends G2AccessException {

  private Item deletedItem;

  public G2ItemDeletedException () {
  }

  public G2ItemDeletedException (String details) {
    super (details);
  }

  /**
   * @undocumented
   */
  public G2ItemDeletedException (String details, Item deletedItem) {
    super (details);
    this.deletedItem = deletedItem;
  }

}
