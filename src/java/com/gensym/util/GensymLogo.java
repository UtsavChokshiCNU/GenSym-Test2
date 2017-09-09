package com.gensym.util;

import java.applet.*;
import java.awt.*;

import com.gensym.core.GensymApplication;
/*
 *  This class will display an animated Gensym Logo
 *
 */

public class GensymLogo extends Applet implements Runnable, ActivityDisplay
{
  private static final int NUM_IMAGES = 6;
  private static final int DELAY      = 100;
  Thread       gThread   = null;
  Image        images[]  = new Image[NUM_IMAGES];
  int          i         = 0;
  int          j;
  boolean      paused    = true;
  MediaTracker tracker   = new MediaTracker(this);


  @Override
  public void init()
  {
    int counter;

    setBackground (Color.lightGray);

    for (counter = 0; counter < images.length; counter++)
    {
	    String imageLocation = GensymApplication.locateImageFile ("logo-small-" + counter + ".gif");
	    if (imageLocation != null)
       {
          MediaTracker mediaTracker = new MediaTracker(this);
	       images [counter] = Toolkit.getDefaultToolkit().getImage (imageLocation);
                 mediaTracker.addImage (images[counter], counter);

          try
          {
             mediaTracker.waitForID(counter);
          }
          catch (Exception e)
          {
          }
       }
	    else
	       images [counter] = null;       
    }
  }

  @Override
  public void start()
  {
    init();

    if (gThread == null)
    {
	    gThread = new Thread(this);
	    gThread.start();
    }
  }

  @Override
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
      notifyAll();
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

  @Override
  public void setBusy () {
    startAnimation ();
  }

  @Override
  public void setIdle () {
    stopAnimation ();
    resetAnimation ();
  }

}
