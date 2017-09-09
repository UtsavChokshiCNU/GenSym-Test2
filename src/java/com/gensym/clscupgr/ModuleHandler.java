
package com.gensym.clscupgr;

import com.gensym.util.Symbol;
import com.gensym.ntw.TwAccess;

public interface ModuleHandler {

  public void moduleLoaded (TwAccess cxn, Symbol moduleName_);

  public void moduleUnloaded (TwAccess cxn, Symbol moduleName_);

}
