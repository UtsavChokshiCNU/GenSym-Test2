package com.gensym.uitools.utils;

import java.awt.*;
import java.io.*;
import javax.swing.JPanel;

import com.gensym.core.GensymApplication;
import java.net.URL;
/*
 *  This class will display an animated Gensym Logo
 *
 */

public class GensymLogoAnimator extends JPanel implements Runnable
{
  private static final int NUM_IMAGES = 6;
  private static final int DELAY      = 100;
  Thread       gThread   = null;
  Image        images[]  = new Image[NUM_IMAGES];
  int          i         = 0;
  int          j;
  boolean      paused    = true;
  MediaTracker tracker   = new MediaTracker(this);


  public GensymLogoAnimator()
  {
    init();
    start();
  }
  
  public void init()
  {
    int i;

    setBackground (Color.lightGray);

    for (i = 0; i < images.length; i++)
    {
      URL imageLocation = this.getClass().getResource("logo-small-" + i + ".gif");
      if (imageLocation != null)
       {
	 MediaTracker tracker = new MediaTracker(this);
	 images [i] = Toolkit.getDefaultToolkit().getImage (imageLocation);
	 tracker.addImage (images[i], i);
	 
	 try
	   {
             tracker.waitForID(i);
	   }
	 catch (Exception e)
	   {
	   }
       }
      else
	images [i] = null;       
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

  @Override
  public Dimension minimumSize()
  {
    return new Dimension(23, 18);
  }

  @Override
  public Dimension preferredSize()
  {
    return minimumSize();
  }

  public void setBusy () {
    startAnimation ();
  }

  public void setIdle () {
    stopAnimation ();
    resetAnimation ();
  }

}
