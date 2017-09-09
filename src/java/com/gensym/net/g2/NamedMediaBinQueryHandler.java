
package com.gensym.net.g2;

public final class NamedMediaBinQueryHandler extends Interpreter {

  public static final String MAGIC_MARKER = "namedBin?";

  static {
    G2ProtocolRegistry.registerInterpreter (MAGIC_MARKER, new NamedMediaBinQueryHandler ());
  }

  private NamedMediaBinQueryHandler () {
  }

  @Override
  java.net.URLConnection createConnection (java.net.URL url) {
    return new G2MediaQueryConnection (url);
  }
    
}

