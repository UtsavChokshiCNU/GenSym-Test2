package com.gensym.demos.docs.custompopups;

import com.gensym.wksp.MenuChoiceHandler;
import com.gensym.dlg.MessageDialog;
import com.gensym.util.Symbol;
import com.gensym.classes.Item;
import com.gensym.ntw.TwConnection;
import com.gensym.jgi.G2AccessException;

public class LocalMenuChoiceHandler implements MenuChoiceHandler {

  @Override
  public void executeMenuChoice(Symbol menuLabel, Item itm, TwConnection cxn) throws G2AccessException {
    new MessageDialog (null, "Message", true, "Handling user menu choice locally", null).setVisible (true);
  }
}
