/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      BufferedContainer.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.ntw.util;

import java.util.*;
import java.awt.*;

import com.gensym.message.Trace;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;

/** Paints to an image buffer. Most calls to <code>paint</code> should
 * simply be calls to
 * paint the image buffer to the screen. If a fresh view of the image
 * is needed, call repaintSlice(x1, x2). Resizing will always
 * result in a fresh image, and hence a fresh paint. Instead of overriding
 * the paint method, extenders of this class should override the localPaint()
 * method. To call the paint() method of Container class,
 * call containerPaint().
 * <p>
 * In a typical implementation, <code>localPaint</code> may simply contain
 * a call to <code>containerPaint</code>.
 * <p>
 * This class is only useful in cases where the container is aware of all
 * events that may cause appearance changes to the container itself or
 * to the components within the container. It is more useful when the
 * container also has an expensive paint method. It is most useful when,
 * in addition, the appearance changes infrequently.
 * @author Robert Penny
 * @version 1.0 12/5/97
 */
public abstract class BufferedContainer extends Container {

  static private final Resource i18n =
  Resource.getBundle("com.gensym.ntw.util.Messages");

  private static MessageKey messageKey =
  Trace.registerMessageKey("com.gensym.ntw.util",
			   BufferedContainer.class);

  public static boolean traceOn = false;
  static Resource i18nTrace =
  Resource.getBundle("com.gensym.ntw.util.TraceMessages");
  static MessageKey traceKey = messageKey;

  private boolean use_buffered_paint = true;
  private Image doublebuffer;
  private Graphics dbg;
  private boolean validSize = false;

  /** Calls the paint() method of class java.awt.Container */
  protected final void containerPaint(Graphics g) {
    super.paint(g);
  }

  /** Put what would normally the contents of the <code>paint</code> method
   * here. This method is called by <code>paint</code> after an
   * an <code>invalidatedPaint<code> or size change.
   * To give subclassers control over when the normal <code>paint</code> of
   * java.awt.Container is called, <code>BufferedContainer</code> does not
   * call it automatically, but leaves it up to the subclasser. It is strongly
   * recommended that it be called exactly once within the
   <code>localPaint</code> method of immediate subclasses of
   * <code>BufferedContainer</code>, so that subsequent subclasses can call
   <code>super.localPaint</code> and have the normal <code>paint</code>
   * of java.awt.Container called. */
  protected abstract void localPaint(Graphics g);

  /** Call this whenever something in the container changes that would render
   * the current image invalid */
  public void repaintAll() {
    Dimension size = getSize();
    repaintWholeSlice(size);
    Trace.send(20, traceKey, i18nTrace, "bcrepaintAll", size);
  }

  /** This method is overriden so that any changes to the size of the
   * container will result in a new image being generated the next
   * time <code>paint</code> is called. */
  @Override
  public void setBounds(int x, int y, int width, int height) {
    Dimension size = getSize();
    if (size.width != width || size.height != height) {
      validSize = false;
    }

    super.setBounds(x, y, width, height);
  }

  /** Indicate whether or not to use buffered painting or direct painting. */
  public void setBufferedPaint(boolean on) {
    if (use_buffered_paint != on) {
      use_buffered_paint = on;
//       invalidatePaint();
    }
  }

  /** Returns the current buffering state of the Container */
  public boolean getBufferedPaint() {
    return use_buffered_paint;
  }

  /** resets what dbg points to.
   */
  private void newImage(Dimension size) {
    doublebuffer = WindowUtil.createImage (size.width, size.height);
    if (dbg != null)
      dbg.dispose();
    dbg = (Graphics) doublebuffer.getGraphics();
    repaintWholeSlice(size);
    validSize = true;
  }
    
  // begin Trend-chart specific code

  // Not really a coordinate, actually the left point and
  // right values of the slice
  Point invalidSlice;

  /** specifies that a vertical slice of the container
   * needs to be repainted.
   * @undocumented
   */
  public void repaintSlice(int x1, int x2) {
    if (invalidSlice == null)
      invalidSlice = new Point (x1, x2);
    else {
      invalidSlice.x = Math.max(0, Math.min(x1, invalidSlice.x));
      invalidSlice.y = Math.max(x2, invalidSlice.y);
    }
    super.repaint();
  }

  private void adjustClipToSlice(Graphics g, Dimension size) {
    //Dimension size = getSize();
    int x = invalidSlice.x;
    int width = invalidSlice.y - x;
    g.setClip(x, 0, width, size.height);
    invalidSlice = null;
  }

  private void repaintWholeSlice(Dimension size) {
    //Dimension size = getSize()
    repaintSlice(0, size.width);
  }

  // end Trend-chart specific code

  /** It is recommended that sublcassers of <code>BufferedContainer</code>
   * not override this method, but instead put all their normal
   * <code>paint</code> into <code>localPaint</code> */
  @Override
  public void paint(Graphics finalg) {
    if (finalg instanceof java.awt.PrintGraphics ||
	!use_buffered_paint) {
      localPaint(finalg);
      return;
    }
    Dimension size = getSize();
    Trace.send(20, traceKey, i18nTrace, "bcpaint1", finalg, size);
    Graphics g = finalg;
    boolean somethingNewToDraw = false;
    try {
      if (!validSize) {
	// resets what dbg points to.
	newImage(size);
	somethingNewToDraw = true;
      } else {
	somethingNewToDraw = (invalidSlice != null);
      }
      if (!somethingNewToDraw) {
	Trace.send(20, traceKey, i18nTrace, "bcBlit");
	finalg.drawImage(doublebuffer, 0, 0, null);
	return;
      }
      g = dbg;
      Trace.send(20, traceKey, i18nTrace, "bcsliceBefore",
		 invalidSlice, size);
      adjustClipToSlice(g, size);
      Trace.send(20, traceKey, i18nTrace, "bcsliceAfter",
		 invalidSlice, g.getClipBounds());
    } catch (Exception ex) {
      use_buffered_paint = false;
      MessageEvent me =
	new MessageEvent(2, messageKey, i18n, "doubleBufferingFailure",
			 new Object[]
			 {ex.getMessage(), this.getClass().getName()});
      Message.send(me);
      Trace.exception(ex);
    }

    localPaint(g);

    if (use_buffered_paint) {
      finalg.drawImage(doublebuffer, 0, 0, null);
    }
  }
}
