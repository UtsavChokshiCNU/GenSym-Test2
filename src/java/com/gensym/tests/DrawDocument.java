
package com.gensym.tests;

import java.awt.*;

public class DrawDocument extends Component implements Runnable {

  private boolean useImage;
  private Image dImg;
  private Graphics dbg;
  private int WIDTH = 200, HEIGHT = 200;
  private int numPaints, numRepaints, numDraws;
  private int paintIntervalMillis;
  private long t0;


  public DrawDocument (boolean useImage, int paintIntervalMillis) {
    this.useImage = useImage;
    this.paintIntervalMillis = paintIntervalMillis;
    new Thread (this).start ();
  }

  @Override
  public void paint (Graphics g) {
    if (!useImage) {
      paint0 (g);
    } else {
      if (dImg == null) {
	dImg = createImage (WIDTH, HEIGHT);
	System.out.println ("Double Buffer Image = " + dImg);
	dbg = dImg.getGraphics ();
	System.out.println ("Double Buffer Graphics = " + dbg);
	paint0 (dbg);
      }
      g.drawImage (dImg, 0, 0, null);
    }
    numPaints++;
  }


  private final void paint0 (Graphics g) {
    g.setColor (Color.red);
    g.fillRect (10, 10, 180, 180);
    g.setColor (Color.blue);
    g.fillOval (0, 0, 100, 100);
    g.setColor (Color.yellow);
    g.fillOval (100, 100, 100, 100);
    g.setColor (Color.cyan);
    g.drawPolyline (new int[] {10, 10, 100}, new int[] {10, 190, 190}, 3);
    g.setColor (Color.pink);
    g.drawString ("Hello", 50, 50);
    numDraws++;
  }

  @Override
  public Dimension getPreferredSize () {
    return new Dimension (WIDTH, HEIGHT);
  }

  @Override
  public void run () {
    Thread currentThread = Thread.currentThread ();
    try {
      t0 = System.currentTimeMillis ();
      while (true) {
	repaint ();
	numRepaints++;
	currentThread.sleep (paintIntervalMillis);
	if (numRepaints%200 == 0) {
	  long t1 = System.currentTimeMillis () - t0;
	  System.out.println ("Repaint " + numPaints + " / Paint " + numRepaints + " / Draw " + numDraws +
			       " in " + t1 + "ms");
	  System.out.flush ();
	  t0 += t1;
	  numDraws = numRepaints = numPaints = 0;
	}
      }
    } catch (InterruptedException ie) {
      ie.printStackTrace (System.err);
    }
  }
}
