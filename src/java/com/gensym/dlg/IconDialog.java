
package com.gensym.dlg;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.*;
import java.awt.image.ImageObserver;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

/**
 * Don't want to make this public?
 */
abstract class IconDialog extends StandardDialog {

  private boolean      inUse;
  private MessagePanel mp;
  private static final Toolkit tk = Toolkit.getDefaultToolkit ();

  protected IconDialog (Frame frame, String title, boolean isModal,
			String[] btnLabels, int[] btnCodes,
			String message,
			Image img,
			boolean multiLine,
			StandardDialogClient client) {
    this (frame, title, 
	  isModal,
	  btnLabels,
	  btnCodes,
	  message, img, multiLine,
	  client,
	  ensureImageIsLoaded (img));
  }

  private IconDialog (Frame frame, String title, boolean isModal,
		      String[] btnLabels, int[] btnCodes,
		      String message,
		      Image img,
		      boolean multiLine,
		      StandardDialogClient client,
		      boolean zz) {
    super(frame, title, 
	  isModal,
	  btnLabels,
	  btnCodes,
	  new MessagePanel (img == null ? null : new ImageComponent (img), multiLine, message),
	  client);
    mp = (MessagePanel) getDialogComponent ();
    setDefaultButton (OK);
    mp.setKeyHandler (getStandardKeyInterpreter ());
    //setMessage (message);
    //pack();
  }

  /**
   * Called from StandardDialog to lay out buttons
   */
  @Override
  protected int getButtonAlignment () {
    return CENTER;
  }

  public void setImage (Image img) {
    Component icon = mp.icon;
    mp.remove (icon);
    icon = null;
    if (img != null)
      icon = new ImageComponent (img);
    mp.add ("West", icon);
    icon.invalidate ();
    pack ();
  }

  /*
  public void setVisible (boolean showQ) {
    if (showQ)
      okButton.requestFocus();
    super.setVisible (showQ);
  }
  */

  public void setMessage(String message) {
    mp.setText (message);
  }

  @Override
  public void dispose () {
    inUse = false;
    super.dispose ();
  }

  protected static final boolean ensureImageIsLoaded (Image img) {
    int imgState = tk.checkImage (img, -1, -1, null);
    if ((imgState & ImageObserver.ALLBITS) != 0)
      return false;
    waitForImage (img);
    return true;
  }

  private static final ImageLoader imgLoader = new ImageLoader ();
  private static final synchronized  void waitForImage (Image img) {
    imgLoader.loadImage (img);
  }
}

class ImageLoader implements ImageObserver {

  private static final Toolkit tk = Toolkit.getDefaultToolkit ();
  private Image imgToLoad;
  private boolean imageDone;
  
  synchronized void loadImage (Image img) {
    if (imgToLoad != null)
      throw new IllegalStateException ("Cannot load multiple images concurrently");
    imgToLoad = img;
    int imgFlags = tk.checkImage (img, -1, -1, null);
    if ((imgFlags & ImageObserver.ALLBITS) != 0) {
      imgToLoad = null;
      return;
    }
    tk.prepareImage (img, -1, -1, this);
    imgFlags = tk.checkImage (img, -1, -1, null);
    if ((imgFlags & ImageObserver.ALLBITS) != 0) {
      imgToLoad = null;
      return;
    }
    try {
      while (!imageDone) {
		wait();
      }
    } catch (InterruptedException ie) {
      // Don't care?
    }
  }

  @Override
  public boolean imageUpdate (Image img, int flags, int x, int y, int height, int width) {
    imageDone = (flags & ImageObserver.ALLBITS) != 0;
    if (imageDone) {
      synchronized (this) {
    	  imgToLoad = null;
    	  notifyAll();
      }
    }
    return !imageDone;
  }

}

class MessagePanel extends JPanel {

  private final int DEFAULT_COLUMNS = 60;
  private final int DEFAULT_ROWS = 6;
  JLabel lbl;
  JTextArea mlbl;
  Component icon;

  public MessagePanel (Component icon, boolean multiLine, String message) {
    this.icon = icon;
    setLayout (new BorderLayout ());
    if (icon != null)
      add ("West", icon);
    JScrollPane scrollPane = null;
    if  (multiLine) {
      mlbl = new JTextArea (message);
      mlbl.setEditable (false);
      mlbl.setLineWrap(true);
      mlbl.setWrapStyleWord(true);
      mlbl.setColumns(DEFAULT_COLUMNS);
      mlbl.setRows(DEFAULT_ROWS);
      scrollPane = new JScrollPane(mlbl);
    } else
      lbl = new JLabel (message, JLabel.CENTER);
    add ("Center", lbl == null ? (Component)scrollPane : (Component)lbl);
    if (mlbl != null)
      mlbl.setBackground(mlbl.getParent().getBackground());
  }

  @Override
  public Insets getInsets () {
    return new Insets(10,10,10,10);
  }

  public void setText (String msg) {
    if (lbl != null)
      lbl.setText (msg);
    else
      mlbl.setText (msg);
  }

  void setKeyHandler (KeyListener keyHandler) {
    if (mlbl != null)
      mlbl.addKeyListener (keyHandler);
  }
}

class ImageComponent extends Component implements ImageObserver {

  private Image img;
  private int wd = -1, ht = -1;
  private static final Dimension ZERO_DIMENSIONS = new Dimension (0, 0);

  ImageComponent (Image img) {
    this.img = img;
  }


  @Override
  public Dimension getPreferredSize () {
    if (wd == -1)
      wd = img.getWidth (this);
    if (ht == -1)
      ht = img.getHeight (this);
    if (wd == -1)
      return ZERO_DIMENSIONS;
    else {
      Dimension x = new Dimension (wd, ht);
      return x;
    }
  }

  public boolean imageUpdate (Image img, int flags, int x, int height, int width) {
    invalidate ();
    return ((flags & ImageObserver.WIDTH) == 0 || (flags & ImageObserver.HEIGHT) == 0);
  }

  @Override
  public void paint (Graphics g) {
    Dimension size = getSize ();
    g.drawImage (img, (size.width - wd)/2, (size.height - ht)/2, null);
  }

}
