package com.gensym.icons;

import java.util.*;
import java.lang.*;
import java.awt.*;
import java.awt.image.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.*;

/**
 *<b>SYNOPSIS</b><p>
 * well, duh!
 */
  
public class IconBackgroundLayer {
  private static final Symbol TYPE_       = Symbol.intern ("TYPE");
  private static final Symbol IMAGE_NAME_ = Symbol.intern ("IMAGE-NAME");
  private static final Symbol IMAGE_      = Symbol.intern ("IMAGE");
  private static final Symbol COLOR_      = Symbol.intern ("COLOR");
  private static final Symbol POINT_      = Symbol.intern ("POINT");

  Symbol type;
  private Symbol image_name;
  private ImageLoader il;
  private Image image;
  int imageWidth = 0, imageHeight = 0;
  Image currentScaledImage;
  private int currentXScale = G2PrimitiveDraw.scale_constant,
    currentYScale = G2PrimitiveDraw.scale_constant;
  private Point point;
  private Symbol g2_color;
  
  /**
   *@param <em>type</em> the Symbol color or the Symbol image.
   *@param <em>image_name</em> A Symbol representing the name of the image to
   *   be used when the <em>type</em> is image.
   *@param <em>g2_color</em> a Symbol representing any g2 color, used when the
   *   <em>type</em> is color.
   *@param <em>point</em> the Point at which to draw the left/top of the image,
   *  when the <em>type</em> is image.
   *@see G2ColorMap 
   */
  protected IconBackgroundLayer(Symbol type,Symbol image_name,
				Symbol g2_color,Point point) {
    this.type = type;
    this.image_name = image_name;
    this.g2_color = g2_color;
    this.point = point;
    if (IMAGE_.equals(type))
      this.il = new ImageLoader();
  }

  protected IconBackgroundLayer(Structure data) {
    if (data != null) {
      this.type = (Symbol) data.getAttributeValue (TYPE_, null);
      if (IMAGE_.equals(type)) {
	this.image_name = (Symbol) data.getAttributeValue (IMAGE_NAME_, null);
	Structure pointData = (Structure)data.getAttributeValue (POINT_, null);
	if (pointData != null)
	  point = new PowerPoint(pointData);
	else
	  point = new PowerPoint(0,0);
	this.il = new ImageLoader();
      } else 
	this.g2_color = (Symbol) data.getAttributeValue (COLOR_, null);
    } else {
      this.type = null;
      this.image_name = null;
      this.g2_color = null;
      this.point = null;
    }
  }

  void setImage(Image image, int width, int height)
  {
    this.image = image;
    imageWidth = width;
    imageHeight = height;
  }

  Symbol getImageName()
  {
     return image_name;
  }
  
  Point getImageLocation()
  {
    return point;
  }
  
  Image getImage()
  {
    return image;
  }
  
  int getImageWidth()
  {
    return imageWidth;
  }
  
  int getImageHeight()
  {
    return imageHeight;
  }

  /**
   *Draws a background layer with the specified width and height.
   * Images can specify a point at which to draw the upper left corner of the
   * image. Colors start drawing at (0,0) and extends to (width,height).
   *@param <em>g</em> the Graphics to which the background layer should be drawn.
   *@param <em>width</em> the width of the background.
   *@param <em>height</em> the height of the background.
   *@param <em>rotationindegrees</em> an int that can be 0, 90, 180 or 270.
   */
  public void Draw(Graphics g,
		   int iconWidth, int iconHeight,
		   int xScale, int yScale,
		   int rotationindegrees,
		   Point pivotPoint,
		   boolean isReflected) {
    if (type != null) {
      if (type.equals(IMAGE_)) {
	if (image == null) {
		return;//error????
	}
	//need to handle rotation/reflection soon	
	if (xScale != currentXScale || yScale != currentYScale) {
	  currentXScale = xScale;
	  currentYScale = yScale;	 	  
	  currentScaledImage =
	    il.loadAndPaintImage(image, true, g,
				 new Point(point.x*xScale/G2PrimitiveDraw.scale_constant,
					   point.y*yScale/G2PrimitiveDraw.scale_constant),
				 imageWidth*xScale/G2PrimitiveDraw.scale_constant,
				 imageHeight*yScale/G2PrimitiveDraw.scale_constant);
	} else {
	  if (currentScaledImage == null) {
	    currentXScale = xScale;
	    currentYScale = yScale;
	    currentScaledImage
	      = il.loadAndPaintImage(image, true, g,
				     new Point(point.x*xScale/G2PrimitiveDraw.scale_constant,
					       point.y*yScale/G2PrimitiveDraw.scale_constant));
	  } else {
	    if (il.isLoaded())
	      g.drawImage(currentScaledImage,
			  point.x*xScale/G2PrimitiveDraw.scale_constant,
			  point.y*yScale/G2PrimitiveDraw.scale_constant,
			  null);
	  }
	}
      } else { 
	Color color = (Color) G2ColorMap.get(g2_color);
	if (color == null){
		color = Color.black;
	}
	g.setColor(color);
	g.fillRect(0,0, iconWidth, iconHeight);
      }
    }
  }
}

class ImageLoader extends Component implements Runnable{
  Image image;
  MediaTracker mt;
  Graphics g;
  Point point;
  int width, height;
  public ImageLoader()
  {
    mt = new MediaTracker(this);
  }

  Image loadAndPaintImage(Image image, 
			  boolean synchronously,
			  Graphics g,
			  Point point,
			  int width, int height)
  {
    Image scaledImage =
      image.getScaledInstance(width, height, Image.SCALE_FAST);//SMOOTH);
    return loadAndPaintImage(scaledImage, synchronously, g, point);
  }
		      
  Image loadAndPaintImage(Image image, 
			  boolean synchronously,
			  Graphics g,
			  Point point) {
    this.point = point;
    this.g = g;
    this.image = image;
    mt.addImage(image, 0);
    if (synchronously) {
      //System.out.println("WAITING FOR SCALED VERSION OF " + image);
      run();
      //System.out.println("GOT SCALED VERSION OF " + image);
    } else {
      Thread thread = new Thread(this);
      thread.start();
    }
    return image;
  }

  public boolean isLoaded()
  {
    return mt.statusID(0, false) == MediaTracker.COMPLETE;
  }
      
  @Override
  public void run() {
    try {
      mt.waitForID(0);
      g.drawImage(image, point.x, point.y, null);
    } catch (InterruptedException ie) {
      Trace.exception(ie);
      return;
    }
  }
  
}
