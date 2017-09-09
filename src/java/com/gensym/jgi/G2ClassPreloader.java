/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ClassPreloader.java
 *
 *
 *   Modifications:
 *
 */
package com.gensym.jgi;

import com.gensym.jgi.download.StubClassLoader;
import com.gensym.util.Symbol;

/**
 * Helper class, to allow g2Classes to be preloaded 
 * in an independant thread
 */
class G2ClassPreloader extends Thread {

  StubClassLoader loader;
  Symbol[] g2ClassNames;

  public G2ClassPreloader(StubClassLoader loader, Symbol[] g2ClassNames) {
    this.loader = loader;
    this.g2ClassNames = g2ClassNames;
  }

  @Override
  public void run() {
    preloadG2Classes();
  }

  void preloadG2Classes() {
    for (int i = 0; i<g2ClassNames.length; i++) {
      loader.loadClass(g2ClassNames[i], true);
      loader.loadClass(g2ClassNames[i], false);
    }
  }
}
