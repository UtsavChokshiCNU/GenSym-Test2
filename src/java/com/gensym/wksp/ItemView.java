package com.gensym.wksp;
import com.gensym.classes.Item;

/**
 * A common interface for all views of G2 Items,
 * including KbWorkspaces.
 */

public interface ItemView
{
  /**
   * Gets the item for this element.
   * All data access and data change requests should go through
   * the item returned by this method. 
   * @return the G2 item which this element is viewing. 
   */
  public Item getItem();
  
}
