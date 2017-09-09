
package com.gensym.net.memcache;

import java.net.*;

/**
 * The class <code>com.gensym.net.memache.Handler</code> is a protocol
 * handler that knows how to resolve <code>memcache</code> URLs. In order to
 * use this class, the application must either have the System property
 * java.protocol.handler.pkgs set to include com.gensym.net (in which
 * case, an instance of this class will be created the first time a
 * URL with the g2 protocol is created), or else
 * install a URLStreamHandlerFactory that returns an instance of this
 * class.<p>
 *
 * A typical example of a g2 URL is
 * memcache:///resource-name
 *
 * @author vkp
 * @version 1.0 12/25/97
 */

public class Handler extends URLStreamHandler {

  /**
   * Zero arg constructor called by StreamHandlerFactory
   */
  public Handler () {}

  @Override
  public URLConnection openConnection (URL url) throws java.io.IOException {
    System.out.println ("In memcache/Handler -> openConnection ()");
    URLConnection urlCnxn = new ResourceConnection (url);
    return urlCnxn;
  }
}
