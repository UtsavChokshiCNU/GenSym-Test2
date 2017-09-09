  /*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwGateway.java
 *
 */
package com.gensym.ntw;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.AttributeDenotation;

class SessionListener implements com.gensym.util.ItemListener {
  TwGateway context;
  SessionListener(TwGateway context) {
    this.context = context;
  }

  @Override
  public void receivedInitialValues (com.gensym.util.ItemEvent e) {}
  @Override
  public void itemModified (com.gensym.util.ItemEvent e) {//System.out.println (e);
    Sequence s = e.getDenotation ();
    if (!AttributeDenotation.isAttributeDenotation (s))
      return;
      Symbol attrName = AttributeDenotation.getAttributeName (s);
      if (!(attrName.equals (com.gensym.util.symbol.SystemAttributeSymbols.UI_CLIENT_SESSION_USER_MODE_)))
	return;
      Symbol newUserMode = (Symbol) e.getNewValue ();
      context.dispatchTwConnectionEvent (new TwConnectionEvent (context, TwConnectionEvent.USER_MODE_CHANGED, newUserMode));
    }
    @Override
    public void itemDeleted (com.gensym.util.ItemEvent e) {
      context.uiClientSession = null;
      context.dispatchTwConnectionEvent (new TwConnectionEvent (context, TwConnectionEvent.CONNECTION_LOGGED_OUT));
    }
  }
