

package com.gensym.oldmdi;
import java.awt.*;
import java.net.*;
import gjt.RowLayout;
import gjt.Orientation;
import gjt.ImageButtonEx;
import com.gensym.ntw.util.WindowUtil;
import com.gensym.core.GensymApplication;

class MDIDocTB extends Panel {

  private static Color tbFocusBgColor = new Color (0, 0, 128);
  private static Color tbFocusFgColor = Color.white;
  private static Color tbUnFocusBgColor = Color.gray;
  private static Color tbUnFocusFgColor = Color.lightGray;
  // I dont' understand why the width affects the layout
  // The preferred width of a component in the "North" compartment
  // of a BorderLayout should be rightfully ignored.
  private static Dimension tbSize = new Dimension (52, 17);
  String title;
  private static Font tbFont = new Font ("sansserif", Font.BOLD, 12);
  private static Insets stdMDITBInsets = new Insets (2, 0, 1, 2);
  private static LayoutManager stdTBLayoutMgr = new RowLayout (Orientation.RIGHT,
							       Orientation.BOTTOM, 0);
  ImageButtonEx minimizeButton, maximizeButton, destroyButton;
  private static Image minImage, minInsetImage,
                       maxImage, maxInsetImage,
                       desImage, desInsetImage;

  private static Image getImageFromGensymApplication (Toolkit toolkit,
						      String imageName) {
    String imageFileName;

    imageFileName = GensymApplication.locateImageFile(imageName);
    if (imageFileName == null)
      return null;
    else
      return toolkit.getImage(imageFileName);
  }

  static void init () {
    Toolkit defToolkit = Toolkit.getDefaultToolkit ();
    // Images are not in CVS yet...
    String imageFileName;
    minImage      = getImageFromGensymApplication(defToolkit,
						  "minimize_raised.gif");
    minInsetImage = getImageFromGensymApplication(defToolkit,
						  "minimize_inset.gif");

    maxImage      = getImageFromGensymApplication(defToolkit,
						  "maximize_raised.gif");
    maxInsetImage = getImageFromGensymApplication(defToolkit,
						  "maximize_inset.gif");

    desImage      = getImageFromGensymApplication(defToolkit,
						  "destroy_raised.gif");
    desInsetImage = getImageFromGensymApplication(defToolkit,
						  "destroy_inset.gif");

    Image[] buttonImages = {minImage, minInsetImage, maxImage, maxInsetImage, desImage, desInsetImage};
    new TBImageLoader (buttonImages).start ();
  }

  @Override
  public Dimension preferredSize () {
    return tbSize;
  }

  @Override
  public Insets insets () {
    return stdMDITBInsets;
  }

  MDIDocTB (String title) {
    this.title = title;
    //System.out.println ("In MDIDocTB Constructor"); System.out.flush ();
    initButtons ();
    //System.out.println ("Initialized Buttons"); System.out.flush ();
    setLayout (stdTBLayoutMgr);
    //System.out.println ("About to add buttons"); System.out.flush ();
    if (minimizeButton != null)
      add (minimizeButton);
    if (maximizeButton != null)
      add (maximizeButton);
    if (destroyButton != null)
      add (destroyButton);
    //System.out.println ("Added buttons"); System.out.flush ();
  }

  MDIDocTB () {
    this ("Untitled Document");
  }

  private void initButtons () {
    if ((minImage != null) && (minInsetImage != null))
      minimizeButton = new ImageButtonEx(minImage, minInsetImage);
    if ((maxImage != null) && (maxInsetImage != null))
      maximizeButton = new ImageButtonEx(maxImage, maxInsetImage);
    if ((desImage != null) && (desInsetImage != null))
      destroyButton  = new ImageButtonEx(desImage, desInsetImage);
  }

  void setTitle (String newTitle) {
    this.title = title;
    repaint ();
  }

  @Override
  public void paint (Graphics g) {
    Dimension size = size ();
    int width  = size.width;
    int height = size.height;
    boolean hasFocus = ((MDIDocNC)getParent()).hasFocus();

    g.setColor (hasFocus ? tbFocusBgColor : tbUnFocusBgColor);
    g.fillRect (0, 0, size.width, 17);
    g.setColor (hasFocus ? tbFocusFgColor : tbUnFocusFgColor);
    g.setFont  (tbFont);
    g.drawString (title == null ? "Untitled" : title, 20, 13);
  }

  @Override
  public boolean handleEvent (Event evt) {
    //System.out.println ("MDIDocTB: ->" + evt);
    if (evt.id == Event.MOUSE_UP) {
      MDIDocNC doc = (MDIDocNC) getParent ();
      Container c = doc.getParent ();
      if (!(c instanceof MDIClient))
	c = c.getParent ();
      MDIClient client = (MDIClient)c;
      client.setMDIFocus (doc);
    }
    return super.handleEvent (evt);
  }
}


class TBImageLoader extends Thread {
  private Image[] imagesToLoad;

  TBImageLoader (Image[] imagesToLoad) {
    super ();
    this.imagesToLoad = imagesToLoad;
  }

  @Override
  public void run () {
    for (int i=0; i<imagesToLoad.length; i++) {
      WindowUtil.prepareImage (imagesToLoad[i], -1, -1);
    }
  }
}
