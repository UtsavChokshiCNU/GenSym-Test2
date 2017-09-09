
package com.gensym.tests;

import java.awt.*;

public class FontSizeTest {

  public static void main (String[] args) {
    Toolkit tkt = Toolkit.getDefaultToolkit ();
    Font f = new Font ("sansserif", Font.PLAIN, 14);
    FontMetrics metrics = tkt.getFontMetrics (f);
    System.out.println ("'A' is " + metrics.charWidth ('A') + " pixels wide");
  }

}
