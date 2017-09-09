
package com.gensym.wksp;

import com.gensym.util.Symbol;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwConnection;

/**
 * An interface that is to be implemented by
 * classes that wish to handle G2 Item menu
 * choices locally. This allows the appearance
 * of the menu entry be determined in G2 (by
 * class and other applicable conditions) but
 * to be executed locally on the client.
 * @see com.gensym.wksp.UserMenuChoiceCommands#setLocalMenuChoiceHandler
 */
public interface MenuChoiceHandler {

  /**
   * Method that will be called whenever the menu choice needs to be invoked.
   * @param menuLabel the symbolic label of the menu entry. This is unique for
   *    any item. It will match the label of one of the menu choice which this
   *    handler was registered.
   * @param itm the Item for which to invoke the menu  choice
   * @param cxn the TwConnection over which this Item was received
   */
  public void executeMenuChoice (Symbol menuLabel, Item itm, TwConnection cxn) throws G2AccessException;

}
