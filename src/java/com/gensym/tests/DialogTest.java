
package com.gensym.tests;

import java.awt.*;

public class DialogTest {

  public static void main (String[] args) {
    Frame f = new Frame ("hello");
    f.setSize (300, 200);
    f.setVisible (true);
    Dialog d = new Dialog (f, "Dialog!", true);
    d.setSize (200, 200);
    d.setResizable (false);
    d.setVisible (true);
  }

}
