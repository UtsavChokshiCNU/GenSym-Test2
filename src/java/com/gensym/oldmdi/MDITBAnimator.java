
package com.gensym.oldmdi;

import java.awt.*;
import java.io.*;
import com.gensym.ntw.util.WindowUtil;

class MDITBAnimator extends Panel implements Runnable {

  private int xOld, yOld, wOld, xNew, yNew, wNew, numSplits = 6;
  private int xBegin = 20, yBegin = 20, wBegin = 500, xEnd, yEnd, wEnd;
  private String title;
  private static Color TBColor = new Color (0, 0, 128); // From preferences
  private static Color TBTextColor = Color.white;
  private static Font tbFont = new Font ("sansserif", Font.BOLD, 12);
  private MDIClient client;

  MDITBAnimator (MDIClient client) {
    this.client = client;
    new Thread (this).start ();
  }

  void setParameters (String title, int xBegin, int yBegin, int wBegin, int xEnd, int yEnd, int wEnd) {
    this.title = "Icon" + title;
    this.xBegin  = xBegin;
    this.yBegin  = yBegin;
    this.wBegin  = wBegin;
    this.xEnd  = xEnd;
    this.yEnd  = yEnd;
    this.wEnd  = wEnd;
  }

  synchronized void animate () {
    notify ();
    try {
      wait (1000);
    } catch (InterruptedException ie) {}
  }

  @Override
  public synchronized void run () {
    try {
      while (true) {
	wait ();
	client.add (this);
	WindowUtil.setSaveUnder (this);
	// WindowUtil.raise (this);
	xOld = xBegin; yOld = yBegin; wOld = wBegin;
	for (int i=1; i<numSplits; i++) {
	  xNew= xBegin + (xEnd - xBegin)*i/(numSplits - 1);
	  yNew= yBegin + (yEnd - yBegin)*i/(numSplits - 1);
	  wNew= wBegin + (wEnd - wBegin)*i/(numSplits - 1);
	  reshape (xNew, yNew, wNew, 20);
	  Thread.currentThread().sleep (40);
	  xOld = xNew; yOld = yNew; wOld = wNew;
	}
	xBegin = xEnd; yBegin = yEnd; wBegin = wEnd;
	client.remove (this);
	validate ();
	notify ();
      }
    } catch (InterruptedException ie) {}
  }

  @Override
  public void update (Graphics g) {
    paint (g);
  }

  @Override
  public void paint (Graphics g) {
    g.setColor (TBColor);
    g.fillRect (0, 0, wNew, 20);
    g.setColor (TBTextColor);
    g.setFont (tbFont);
    g.drawString (title, 20, 14);
  }
}
