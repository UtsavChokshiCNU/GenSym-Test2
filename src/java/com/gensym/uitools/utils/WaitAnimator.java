package com.gensym.uitools.utils;

import java.awt.*;
import java.io.*;
import javax.swing.JPanel;

import com.gensym.core.GensymApplication;
/*
 *  This class will display an animated Gensym Logo
 *
 */

public class WaitAnimator extends JPanel implements Runnable
{
  private static final int NUM_IMAGES = 10;
  private static final int DELAY      = 100;
  Thread       gThread   = null;
  Image        images[]  = new Image[NUM_IMAGES];
  int          i         = 0;
  int          j;
  boolean      paused    = true;
  MediaTracker tracker   = new MediaTracker(this);


  public WaitAnimator()
  {
    init();
    start();
    setPreferredSize(new Dimension(87, 19));
    setMinimumSize(new Dimension(87, 19));
    setMaximumSize(new Dimension(87, 19));    
  }
  
  public void init()
  {
    int i;

    setBackground (Color.lightGray);

    for (i = 0; i < images.length; i++)
    {
      MediaTracker tracker = new MediaTracker(this);
      images[i] = Toolkit.getDefaultToolkit().getImage
	(this.getClass().getResource("wait" + (i+1) + ".gif"));
	tracker.addImage (images[i], i);
      try {
	tracker.waitForID(i);
      } catch (Exception e) { }
    }
  }
  
  public void start()
  {
    init();

    if (gThread == null)
    {
      gThread = new Thread(this);
      gThread.start();
    }
  }

  public void stop()
  {
    if (gThread != null)
      {
	gThread.stop();
	gThread = null;
      }
  }

  @Override
  public void run()
  {
    while (true)
    {
	   try
      {
	     repaint ();
	     if (paused)
        {
	        synchronized (this)
           {
		        wait ();
	        }
	     }
	     Thread.sleep(DELAY);
      }
	   catch (InterruptedException e)
      {
	      stop();
      }

    }
  }

  public void stopAnimation ()
  {
    paused = true;
  }

  public void startAnimation ()
  {
    paused = false;
    synchronized (this) {
      notify ();
    }
  }

  public void resetAnimation ()
  {
    i = 0;
  }

  @Override
  public boolean mouseUp (Event evt, int x, int y)
  {
    if (paused)
      startAnimation ();
    else
      stopAnimation ();
    return true;
  }

  @Override
  public void update(Graphics g)
  {
     paint(g);
  }

  @Override
  public void paint(Graphics g)
  {
    super.paint(g);
    Image image;

    if (i < NUM_IMAGES)
      j = i;
    else
      j = (2*NUM_IMAGES -1) - i;

    image = images[j];
    if (image != null)
      g.drawImage(image, 0, 0, null);
		
    if (!paused)
      i++;

    if (i > (2*NUM_IMAGES - 1))
      i = 0;
  }

  public void setBusy () {
    startAnimation ();
  }

  public void setIdle () {
    stopAnimation ();
    resetAnimation ();
  }

}
