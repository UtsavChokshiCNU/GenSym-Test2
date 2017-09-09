
package com.gensym.net.memcache;

import java.net.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.io.IOException;
import java.io.InputStream;
import java.io.ByteArrayInputStream;

/**
 * This class is a representation of an open connection to a G2
 * as a result of opening a URL. It can be used to resolve the URL
 * and download its contents. This might not suppport all the generic
 * methods that can be called. (Mostly throws exceptions for
 * getting the InputStream, bytes, or ContentHeaders). The latter
 * might actually be supported if we can actually determine the
 * type of the item that can be retreived as an RPC call.
 */

public class ResourceConnection extends URLConnection {

  private static final java.io.PrintStream o = System.out;
  private static final boolean urlXnDebug = false;
  private byte[] data;
  private String location;

  ResourceConnection (URL g2url) {
    super (g2url);
    location = g2url.getFile ().substring (1);
  }

  @Override
  public String getContentType () {
    if (urlXnDebug)
      o.println ("Returning g2/item-or-value from getContentType()");
    return "g2/data";
  }


  @Override
  public void connect () throws IOException {
    if (data == null)
      data = (byte[]) ResourceCache.retreiveResource (location);
    System.out.println ("ResourceConnection.connect : retreivedResource " + data);
  }


  @Override
  public long getLastModified () {
    return 0;
  }

  @Override
  public int getContentLength () {
    if (data == null)
      return -1;
    return data.length;
  }

  @Override
  public InputStream getInputStream () throws IOException {
    connect ();
    return new ByteArrayInputStream (data);
  }

}
