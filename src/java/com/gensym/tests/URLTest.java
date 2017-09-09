
package com.gensym.tests;

import java.net.*;

public class URLTest {

  public static void main (String[] args) throws Exception {
    URL url = new URL ("FILE:///tmp/buttons.ser");
    URLConnection cxn = url.openConnection ();
    int numBytes = cxn.getContentLength ();
    System.out.println ("# bytes = " + numBytes);
    String type = cxn.getContentType ();
    System.out.println ("Type = " + type);
    String encoding = cxn.getContentEncoding ();
    System.out.println ("Encoding = " + encoding);
    Object val = cxn.getContent ();
    System.out.println ("Object = " + val);
  }

}
