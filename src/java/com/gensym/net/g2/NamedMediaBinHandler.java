
package com.gensym.net.g2;

public final class NamedMediaBinHandler extends Interpreter {

  public static final String MAGIC_MARKER = "namedBin";

  static {
    G2ProtocolRegistry.registerInterpreter (MAGIC_MARKER, new NamedMediaBinHandler ());
  }

  private NamedMediaBinHandler () {
  }

  @Override
  java.net.URLConnection createConnection (java.net.URL url) {
    return new G2MediaConnection (url);
  }
    
}

