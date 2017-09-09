
package com.gensym.clscupgr.gfr;

import com.gensym.util.Symbol;
import com.gensym.jgi.*;
import com.gensym.ntw.*;
import com.gensym.classes.modules.gfr.GfrPaletteWindow;
import com.gensym.classes.Item;

public abstract class GFRAPI {

  private static final Symbol
  GFR_CREATE_INSTANCE_USING_PALETTE_METHOD_ 
  = Symbol.intern ("GFR-CREATE-INSTANCE-USING-PALETTE-METHOD"),
    GFR_GET_PALETTE_ITEM_ 
  = Symbol.intern ("GFR-GET-PALETTE-ITEM"),
    GFR_CREATE_PALETTE_CLONE_ =
  Symbol.intern ("GFR-CREATE-PALETTE-CLONE");

  public static Item getPaletteItem (TwAccess cxn, GfrPaletteWindow paletteWin) throws G2AccessException {
    return (Item) cxn.callRPC (GFR_GET_PALETTE_ITEM_, new java.lang.Object[] {paletteWin});
  }

  public static Item createInstanceUsingPaletteMethod (TwAccess cxn, Symbol className_) throws G2AccessException {
    return (Item) cxn.callRPC (GFR_CREATE_INSTANCE_USING_PALETTE_METHOD_,
				 new java.lang.Object [] { className_, cxn.retrieveSession () });
  }

  private static boolean createPaletteCloneAPIExists = true;
  public static Item createPaletteClone(TwAccess cxn,
					Item item)
       throws G2AccessException
  {
    if (createPaletteCloneAPIExists) {
      try {
	return (Item) cxn.callRPC (GFR_CREATE_PALETTE_CLONE_,
				   new java.lang.Object [] {item, cxn.retrieveSession()});
      } catch (G2AccessException g2ae) {
	createPaletteCloneAPIExists = false;
      }
    }
    return createInstanceUsingPaletteMethod(cxn, item.getG2ClassName());
    
  }  
}
