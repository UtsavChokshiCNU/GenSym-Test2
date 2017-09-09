
package com.gensym.ntw.util;
//import sun.awt.win32.*;
//import sun.awt.motif.*;
import java.awt.Component;
import java.awt.Frame;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.Window;
import java.awt.image.ImageObserver;
import java.util.Properties;

import com.gensym.message.Trace;

public final class WindowUtil {
  private static volatile Component imagesource;
  private static boolean hacksPossible = false;

  static {
    try {
      //System.loadLibrary ("winutils");
      //hacksPossible = true;
    }  catch (UnsatisfiedLinkError ule) {
      if (com.gensym.core.GensymApplication.getDevOption ())
	System.err.println ("Error while trying to load winutils." + ule);
    } catch (Exception e) {
      Trace.exception (e);
    }
    new WindowUtil ();
  }

  // When this is in a static block, java SEGS
  private WindowUtil () {
    try {
      synchronized (WindowUtil.class) {
        imagesource = new Frame();
        imagesource.addNotify();
      }
    } catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  /** Only needs to be called in the Applet situation, as the imagesource
   * is set during class initialization in an application. */
  public static void setImageSource(Component source) {
    imagesource = source;
  }

  static native void pRaise        (Object c);
  static native void psetSaveUnder (Object c);
  static native void pMove         (Object c, int newX, int newY);
  static native void pUpdateCoordinates (Component c, int newX, int newY);

  public static void setLocation (Component c, int newX, int newY) {
    if (hacksPossible) {
      pMove (c.getPeer (), newX, newY);
      pUpdateCoordinates (c, newX, newY);
    } else
      c.setLocation (newX, newY);
  }

  /** Creates and returns an image if the imagesource has a native peer.
   * It is best to call this from a point in the code where the
   * native peer has already been created. Usually paint() is a good
   * place to do this.
   * @return The image returned by calling createImage() on the imagesource,
   * which can be <code>null</code> if the imagesource has no native peer.
   */
  public static Image createImage (int width, int height) {
    //System.out.println ("WindowUtil::createImage (" + width + ", " + height + ") called"); System.out.flush ();
    return imagesource.createImage (width, height);
    //    return java.awt.Toolkit.getDefaultToolkit ().createImage (width, height);
  }

  public static boolean prepareImage (Image image, int width, int height) {
    if (image == null)
      return false;
    return imagesource.prepareImage (image, width, height, (ImageObserver)null);
  }

  public static void setSaveUnder (Component c) {
    if (hacksPossible) {
      psetSaveUnder (c.getPeer ());
    }
  }

  private static java.awt.Dimension screenDisplaySize = java.awt.Toolkit.getDefaultToolkit().getScreenSize ();
  private static final int dialogMargin = 25;
  
  public static void centerFrame (java.awt.Window parentWindow, java.awt.Window childWindow) {
    Rectangle frameBnds;
    if (parentWindow != null)
      frameBnds = parentWindow.getBounds ();
    else
      frameBnds = new Rectangle (0, 0, screenDisplaySize.width, screenDisplaySize.height);
    Rectangle dlgBounds = childWindow.getBounds ();
    int dlgWidth        = dlgBounds.width;
    int dlgHeight       = dlgBounds.height;
    int dlgX = frameBnds.x + (frameBnds.width - dlgWidth)/2;
    int dlgY = frameBnds.y + (frameBnds.height - dlgHeight)/2;
    if (dlgX + dlgWidth > screenDisplaySize.width)
      dlgX = screenDisplaySize.width - dialogMargin - dlgWidth;
    if (dlgY + dlgHeight > screenDisplaySize.height)
      dlgY = screenDisplaySize.height - dialogMargin -dlgHeight;
    if (dlgX < 0)
      dlgX = dialogMargin;
    if (dlgY < 0)
      dlgY = dialogMargin;
    childWindow.setBounds (dlgX, dlgY, dlgBounds.width, dlgBounds.height);
  }

  public static void centerFrame (java.awt.Window win) {
    Frame theFrame = com.gensym.core.UiApplication.getCurrentFrame ();
    centerFrame (theFrame, win);
  }

}

