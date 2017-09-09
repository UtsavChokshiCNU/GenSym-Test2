/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ModuleHandlerFactory.java 
 * 
 * 
 */ 

package com.gensym.clscupgr;

import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

/**
 * A ModuleHandlerFactory, once registered with the ModuleManager class,
 * will have its makeModuleHandler method called every time any module
 * for which it is registered is loaded (for every connection).
 * @see ModuleManager#registerModuleHandlerFactory
 * @see ModuleManager#moduleLoaded
 * @author
 */
public interface ModuleHandlerFactory {
  public ModuleHandler makeModuleHandler(TwAccess connection, Symbol moduleName);
}
