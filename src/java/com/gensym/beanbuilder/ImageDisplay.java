package com.gensym.beanbuilder;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.MediaTracker;
import java.net.URL;
import java.net.MalformedURLException;
import java.beans.PropertyVetoException;
import java.beans.PropertyChangeListener;
import java.io.ObjectInputStream;
import java.io.IOException;


public class ImageDisplay extends Component implements java.io.Serializable
{

  private static String imageDir;

  /**
   * Create default image viewer.
   */
  public ImageDisplay() {
  }

  /**
   * Crate image viewer with filename.  The specified filename is used as
   * the image source.
   *
   * @param str name of file containing the image source
   * @exception MalformedURLException Thrown if URL cannot be generated from filename
   *
   */
  public ImageDisplay(String str) throws MalformedURLException
  {
    this();

    try
      {
	setFileName(str);
      }
    catch(PropertyVetoException e){}
  }

  /**
   * Create image viewer with URL.  The specified URL is used as
   * the image source.
   *
   * @param url the URL of the image to be displayed
   */
  public ImageDisplay(URL url)
  {
    this();

    //try
    //{
    setURL(url);
    //}
    //catch ( PropertyVetoException e ) { }
  }

  /**
   * Create image viewer with image.  The specified image is used as
   * the image source
   *
   * @param img the image to be displayed
   */
  public ImageDisplay(Image img)
  {
    this();

    // try
    //{
    setImage(img);
    //}
    //catch ( PropertyVetoException e ) { }
  }

  /**
   * Specify or change the image filename.
   *
   * @param str name of file containing image source
   *
   * @exception PropertyVetoException
   * if the specified property value is unacceptable
   */
  public void setFileName(String str) throws PropertyVetoException
  {
    String oldValue = fileName;
    //System.out.println("image file :"+str+"\n");
    //try
    {
      //vetos.fireVetoableChange("FileName", oldValue, str );

      fileName = str;
      if(fileName != null && !"".equals(fileName)) 
    	  setURL(this.getClass().getResource("images/"+str));
      //setURL(new java.net.URL("file:///"+imageDir+str));
    }
    //catch(MalformedURLException e)
    //{
    //System.out.println("malformed URL");
    //fileName = oldValue;
    //}
    repaint();
    changes.firePropertyChange("FileName", oldValue, str );
  }

  /**
   * Obtain the filename associated with the current image.
   *
   * @return the name of the file, if any, associated with this image.  If
   * no file is associated with this image, returns null
   */
  public String getFileName()
  {
    return fileName;
  }

  /**
   * Specify or change the image URL.
   *
   * @param aUrl the URL of the image to be displayed
   *
   * @exception PropertyVetoException
   * if the specified property value is unacceptable
   */
  protected void setURL(URL aUrl) //throws PropertyVetoException
  {
    URL oldValue = url;
    //	vetos.fireVetoableChange("URL", oldValue, aUrl );

    url = aUrl;
    // fileName = null;
    Image loadedImage = null;
    if(url != null){
      loadedImage = getToolkit().getImage(url);
		}
    setImage(loadedImage);
    repaint();
    //	changes.firePropertyChange("URL", oldValue, aUrl );
  }



  /**
   * Specify or change the image filename.
   *
   * @param dir name of directory containing image sourc
   * @param str name of file containing image source
   *
   * @exception PropertyVetoException
   * if the specified property value is unacceptable
   */
  public void setAbsoluteFileName(String dir , String str) throws PropertyVetoException
  {
    String oldValue = fileName;
    try
      {
	//vetos.fireVetoableChange("FileName", oldValue, str );

		fileName = str;
		if(fileName != null && !"".equals(fileName))
		  setURL(new java.net.URL("file:///"+dir+str));
/*	       else
	       setURL(null);
	       */
      }
    catch(MalformedURLException e)
      {
	System.out.println("malformed URL");
	fileName = oldValue;
      }
    repaint();

    changes.firePropertyChange("FileName", oldValue, str );
  }


  /**
   * Obtain the URL associated with the current image.  If the image
   * was specified by file name, or URL, it will have a URL which
   * indicates its source.  Images created using the constructor
   * with an Image parameter will have no associated URL.
   *
   * @return the name of the URL, if any, associated with this image.  If
   no URL is associated with this image, returns null
   */
  protected URL getURL()
  {
    return url;
  }


  /**
   * Sets the new panel image style.
   * @param newStyle the new panel image style, one of
   * IMAGE_TILED, IMAGE_CENTERED, or IMAGE_SCALED_TO_FIT
   * @exception PropertyVetoException
   * if the specified property value is unacceptable
   * @see #getStyle
   */
  public void setStyle(int newStyle)// throws PropertyVetoException
  {
    if (newStyle != imageStyle)
	    {
	      Integer oldValue = imageStyle;
			Integer newValue = newStyle;

			//			vetos.fireVetoableChange("Style", oldValue, newValue);

			imageStyle = newStyle;
	        repaint();
		
	        changes.firePropertyChange("Style", oldValue, newValue);
		}
  }

  /**
   * Gets the current panel image style.
   * @return the current panel image style, one of
   * IMAGE_TILED, IMAGE_CENTERED, or IMAGE_SCALED_TO_FIT
   * @see #setStyle
   * @see #IMAGE_TILED
   * @see #IMAGE_CENTERED
   * @see #IMAGE_SCALED_TO_FIT
   */
  public int getStyle()
  {
    return imageStyle;
  }

  /**
   * Set or change the current image.  Call this method if you want to
   * specify directly the image to display.
   *
   * @param img the image to be displayed
   *
   * @exception PropertyVetoException
   * if the specified property value is unacceptable
   */
  public void setImage(Image img) //throws PropertyVetoException
  {
    //fileName = null;
    Image oldValue = image;
    //    vetos.fireVetoableChange( "Image", oldValue, img );
    image    = img;

    if (img != null)
      {
	MediaTracker tracker;

	try
	  {
	    tracker = new MediaTracker(this);
	    tracker.addImage(image, 0);
	    tracker.waitForID(0);
	  }
	catch(InterruptedException e) { }
      }
    else
      repaint();

    changes.firePropertyChange( "Image", oldValue, img );
  }


    public void substituteImage(Image img){
      image = img;
    }
  /**
   * Obtain the image currently being displayed.
   *
   * @return the image currently displayed or null if no image
   */
  public Image getImage()
  {
    return image;
  }

  /**
   * Paints this component using the given graphics context.
   * This is a standard Java AWT method which typically gets called
   * by the AWT to handle painting this component. It paints this component
   * using the given graphics context. The graphics context clipping region
   * is set to the bounding rectangle of this component and its [0,0]
   * coordinate is this component's top-left corner.
   *
   * @param g the graphics context used for painting
   * @see java.awt.Component#repaint
   * @see java.awt.Component#update
   */
  @Override
  public void paint(Graphics g)
  {
    super.paint(g);
    if (image != null){
      g.drawImage(image, 0, 0, this);

    }

  }

  /**
   * Returns the recommended dimensions to properly display this component.
   * This is a standard Java AWT method which gets called to determine
   * the recommended size of this component.
   *
   * @return  If no image has been loaded, a dimension of 10 by 10 is returned.
   *          If an image has been loaded, the height and width of the image
   *          is returned.
   *
   * @see #minimumSize
   */
  @Override
  public Dimension preferredSize()
  {
    if (image != null)
      return (new Dimension(image.getWidth(this), image.getHeight(this)));
    else
      return new Dimension(10, 10);
  }


  /**
   * Returns the minimum dimensions to properly display this component.
   * This is a standard Java AWT method which gets called to determine
   * the minimum size of this component.
   *
   * @return  If no image has been loaded, a dimension of 10 by 10 is returned.
   *          If an image has been loaded, the height and width of the image
   *          is returned.
   * @see #preferredSize
   */
  @Override
  public Dimension minimumSize()
  {
    return preferredSize();
  }

  /**
   * Adds a listener for all event changes.
   * @param PropertyChangeListener listener the listener to add.
   * @see #removePropertyChangeListener
   */
  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    changes.addPropertyChangeListener(listener);
  }

  /**
   * Removes a listener for all event changes.
   * @param PropertyChangeListener listener the listener to remove.
   * @see #addPropertyChangeListener
   */
  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    changes.removePropertyChangeListener(listener);
  }



  private void readObject(ObjectInputStream stream) throws IOException, ClassNotFoundException {
    stream.defaultReadObject();

    if (url != null) {
      image = getToolkit().getImage(url);

      MediaTracker tracker = new MediaTracker(this);
      tracker.addImage(image, 0);
      try {
	tracker.waitForAll();
      }
      catch(InterruptedException e) {
	throw new IOException("Unable to load image for URL " + url);
      }
    }
  }

  /**
   * Image that this viewer is displaying.
   */
  protected transient Image image;
  
  /**
   * Name of file, if any, associated with this image.
   */
  protected String fileName;

  /**
   * URL of the image being displayed.
   */
  protected transient URL url;

  /**
   * Determines how to draw the image.
   */
  protected int imageStyle;

  private com.gensym.beanbuilder.PropertyChangeSupport changes = new com.gensym.beanbuilder.PropertyChangeSupport(this);

}
