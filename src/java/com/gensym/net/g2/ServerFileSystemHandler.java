
package com.gensym.net.g2;

public final class ServerFileSystemHandler extends Interpreter {

  public static final String MAGIC_MARKER = "serverFileSystem";

  static {
    G2ProtocolRegistry.registerInterpreter (MAGIC_MARKER, new ServerFileSystemHandler ());
  }

  private ServerFileSystemHandler () {
  }

  @Override
  java.net.URLConnection createConnection (java.net.URL url) {
    return new SFSConnection (url);
  }
    
}

