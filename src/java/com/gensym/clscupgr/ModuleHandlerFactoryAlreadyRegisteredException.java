/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ModuleHandlerFactoryAlreadyRegisteredException.java 
 * 
 * 
 */ 

package com.gensym.clscupgr;

import com.gensym.util.Symbol;

public class ModuleHandlerFactoryAlreadyRegisteredException extends Exception {

  private Symbol moduleName;

  public Symbol getModuleName(){
      return moduleName;
  }

  private ModuleHandlerFactory moduleHandlerFactory;

  public ModuleHandlerFactory getModuleHandlerFactory(){
      return moduleHandlerFactory;
  }

  public ModuleHandlerFactoryAlreadyRegisteredException(Symbol moduleName,
							ModuleHandlerFactory factory) {
    this.moduleHandlerFactory = moduleHandlerFactory;
    this.moduleName = moduleName;
  }
}
    
