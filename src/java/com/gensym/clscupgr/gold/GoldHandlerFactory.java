
package com.gensym.clscupgr.gold;

import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.clscupgr.ModuleHandler;
import com.gensym.clscupgr.ModuleHandlerFactory;

public class GoldHandlerFactory implements ModuleHandlerFactory {

  @Override
  public ModuleHandler makeModuleHandler(TwAccess connection, Symbol moduleName) {
    return new GoldHandler();
  }
}
