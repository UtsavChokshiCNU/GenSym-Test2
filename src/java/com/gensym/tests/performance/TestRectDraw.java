
package com.gensym.tests.performance;

import java.awt.*;
import java.awt.event.*;

public class TestRectDraw {

  static final Color[] colors = new Color[] {Color.white,
					       Color.lightGray,
					       Color.black,
					       Color.darkGray,
					       Color.black,
					       Color.red,
					       Color.pink,
					       Color.orange,
					       Color.yellow,
					       Color.green,
					       Color.magenta,
					       Color.cyan,
					       Color.blue};

  public static void main (String args[]) {
    TestFrame f = new TestFrame (args);
    f.setVisible (true);
  }

}

class TestFrame extends Frame {

  private boolean doubleBuffered, cloneGraphics;
  private static final int NUM_RECTS = 1000;
  private Image dImg;
  private Graphics dbg;

  TestFrame (String[] args) {
    super ("Drawing to : " + 
	   (args[0].equals ("true") ? "Image" : "Screen"));
    setSize (800, 800);
    doubleBuffered = new Boolean (args[0]).booleanValue();
    cloneGraphics = new Boolean (args[0]).booleanValue();
    addWindowListener (new WindowAdapter () {
      @Override
      public void windowClosing (WindowEvent wEvt) {
	System.exit (0);
      }
    });
  }

  @Override
  public void paint (Graphics g) {
    Graphics drawGraphics;
    Dimension dim = getSize ();
    if (doubleBuffered) {
      if (dbg == null) {
	dImg = createImage (dim.width, dim.height);
	dbg = dImg.getGraphics ();
      }
      drawGraphics = dbg;
    } else
      drawGraphics = g;
    if (cloneGraphics)
      drawGraphics = drawGraphics.create ();
    long t0 = System.currentTimeMillis ();
    for (int i=0; i<NUM_RECTS; i++) {
      int n = (int) (Math.random ()*13);
      drawGraphics.setColor (TestRectDraw.colors[n]);
      int x = (int) (Math.random ()*800);
      int y = (int) (Math.random ()*800);
      int width = (int) (Math.random ()*400);
      int height = (int) (Math.random ()*400);
      drawGraphics.fillRect (x, y, width, height);
    }
    long t1 = System.currentTimeMillis ();
    System.out.println ("Paint took : " + (t1 - t0) + "ms");
      
    if (doubleBuffered)
      g.drawImage (dImg, 0, 0, null);
  }
}
