package com.gensym.irm;

import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.util.Vector;

import com.gensym.icons.IconBackgroundLayer;
import com.gensym.icons.IconDescription;
import com.gensym.icons.Layer;
import com.gensym.ntw.util.G2PrimitiveDraw;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/**
 * <b>SYNOPSIS:<p></b>
 * 1. Stores a "rendered" version of an IconDescription at 
 *       a particuliar width, height and orientation. <p>
 * 2. public void Draw(Graphics g, int left, int top) <p>
 *       Draws the IconRendering into the Graphics g at the point (left,top). <p>
 * 3. public void setRenderingOverrides(Structure variable_overrides,
 *    Structure region_overrrides) <p>
 *       Overrides the values of variables in the IconRendering's
 *       IconDescription.<p>
 * 
 **/


public class IconRendering implements IconOrientationConstants {

  private static final Symbol WIDTH_ = Symbol.intern ("WIDTH");
  private static final Symbol HEIGHT_ = Symbol.intern ("HEIGHT");

  private IconRenderingParameters renderingParameters;
  private IconRendering originalIconRendering;
  private int referenceCount;
  private int description_width, description_height;  
  private Vector renderings;
  private Structure variable_overrides;
  private Structure region_overrides;
  //private Image doublebuffer; -> Why make these if dubbuf = false?
  //  private Graphics dbg;
  private static final int scale_constant = G2PrimitiveDraw.scale_constant;
  private static final boolean dubbuf = false;
  private static final boolean updateDebugp = false;
  private static final boolean drawingDebugp = false;


  IconRendering() {
    renderingParameters = new IconRenderingParameters ();
  }

  private IconRendering (IconRenderingParameters renderingParameters) {
    this.renderingParameters = renderingParameters;
  }

  /**
   *@param IconDescription The drawing description for this rendering.
   *@see IconDescription
   *@param width The width of the desired rendering.
   *@param height The height of the desired rendering.
   *@param orientation The orientation, with respect to the upright,
   * non-reflected icondescription.
   *@param irm can be null if the maker of the IconRendering wishes
   * to manage the rendering itself.
   **/
  protected IconRendering(IconDescription id, int width, int height,
			  int orientation, IconRenderingManager irm) {
    referenceCount = 0;
    int rotationindegrees = orientationToDegrees (orientation);
    boolean reflected = orientationIsReflected (orientation);
    renderingParameters = new IconRenderingParameters (irm, width, height, orientation, rotationindegrees,
						       reflected, null, id);
    update();
  }

  private void update()
  {
    if (renderingParameters.drawingdescription != null) {
      this.description_width = renderingParameters.drawingdescription.getWidth();
      this.description_height = renderingParameters.drawingdescription.getHeight();
      if (variable_overrides != null) {
	description_width  
	  = ((Integer) variable_overrides.getAttributeValue(WIDTH_, description_width)).intValue();
	description_height
	  = ((Integer) variable_overrides.getAttributeValue(HEIGHT_, description_height)).intValue();
      }
      renderingParameters.pivotpoint = new Point((int) description_width/2,(int) description_height/2);
      updateOffScreenBitmaps();
    }
  }

  private void updateOffScreenBitmaps()
  {
    int scale_constantLocal = G2PrimitiveDraw.scale_constant;
    int x_scale = scale_constantLocal*(renderingParameters.width)/description_width;
    int y_scale = scale_constantLocal*(renderingParameters.height)/description_height;
    this.renderings
      = renderingParameters.drawingdescription.DrawOffScreen(x_scale, y_scale,
					 renderingParameters.rotationindegrees, renderingParameters.pivotpoint,
					 renderingParameters.reflected);
  }
    
  IconDescription getIconDescription() {
    return renderingParameters.drawingdescription;
  }
  
  private int orientationToDegrees (int code) {
    int remainder = (code > CLOCKWISE_270 ? code % 4 : 4 - code);
    int degrees = remainder*90;
    if (degrees == 360)
      degrees = 0;
    return degrees;
  }

  private boolean orientationIsReflected (int code) {
    return (code > CLOCKWISE_270);
  }


  /**
   * Public orientation constants
   */
  public static final int NORMAL        = 0;
  public static final int CLOCKWISE_90  = 1;
  public static final int CLOCKWISE_180 = 2;
  public static final int CLOCKWISE_270 = 3;
  public static final int REFLECTED     = 4;
  public static final int REFLECTED_CLOCKWISE_90  = 5;
  public static final int REFLECTED_CLOCKWISE_180 = 6;
  public static final int REFLECTED_CLOCKWISE_270 = 7;

  /**
   * Used to set the scratch_rendering of the IconRenderingManager
   */
  void set (IconDescription id,
	    int width, int height,
	    int orientation) {
    renderingParameters.drawingdescription = id;
    renderingParameters.width = width;
    renderingParameters.height = height;
    renderingParameters.orientation = orientation;
  }
  
  /**
   * @return true iff the icondescription is valid
   */
  public boolean isValid() {
    return (renderingParameters.drawingdescription != null);
  }

  @Override
  public String toString() {
    return "#<ICON-RENDERING " +
      renderingParameters.drawingdescription.toString() +
      " " + renderingParameters.width + "x" + renderingParameters.height + " " +
      renderingParameters.orientation +
      " @" + Integer.toHexString(super.hashCode()) + ">";
  }
      
      
  /**
   *@returns a copy of this IconRendering. The copy includes pointers to
   * all static Images. All overrides are initialized to null. A user
   * may call setRenderingOverrides and Draw on this copy as they see fit.
   */
  
  protected IconRendering Copy() {
    // if this is not the original then return an error
    referenceCount+=1;
    IconRendering copy = new IconRendering(renderingParameters);
    copy.originalIconRendering = this;
    copy.description_width = description_width;
    copy.description_height = description_height;
    copy.renderings = renderings;    
    copy.variable_overrides = null;
    copy.region_overrides = null;
    if (dubbuf) {
      //copy.doublebuffer = WindowUtil.createImage(width+1, height+1);
      //copy.dbg = copy.doublebuffer.getGraphics();
    }
    return copy;
  }

  /**
   * Decrements the count of the number of copies of this original
   * rendering.  If the reference count drops to zero, this method
   * will signal the IconRenderingManager to decache this rendering.
   */
  protected void decrementReferenceCount() {
    referenceCount -= 1;
    if (referenceCount == 0 && renderingParameters.irm != null)
      renderingParameters.irm.removeIconRendering(this);
  }

  protected void incrementReferenceCount() {
    referenceCount += 1;
  }

  /**
   * Decrements the reference count for the original IconRendering
   * from which this was copied.
   */
  @Override
  protected void finalize () {
    if (originalIconRendering != null)
      originalIconRendering.decrementReferenceCount();
  }
  
  @Override
  public boolean equals(Object other) {
    if (other == null ||!getClass().equals(other.getClass())){
      return false;
    }
    IconRendering otherIR = (IconRendering)other;
    return renderingParameters.equals (otherIR.renderingParameters);
  }

  @Override
  public int hashCode() {
    return renderingParameters.hashCode ();
  }

  private void resetWidthandHeight(Integer new_width, Integer new_height) {
    int oldWidth = description_width;
    int oldHeight = description_height;
    if (new_width != null) 
      description_width = new_width.intValue();
    if (new_height != null) 
      description_height = new_height.intValue();
    if (oldWidth != description_width ||
	oldHeight != description_height)
      updateOffScreenBitmaps();
  }
    
  /**
   * Overrides the values of variables in the IconRendering's DrawingDescription.
   * @param overrides  Structure whose AttributeNames are variable_names
   * and whose AttributeValues are variable values.
   *A variable value can be a Symbol, an Integer or a Symbol.
   */
  
  public void setRenderingOverrides (Structure variable_overrides,
				     Structure region_overrides) {
    this.variable_overrides = variable_overrides;
    this.region_overrides = region_overrides;
    Integer new_width = null; 
    Integer new_height = null;
    
    if (variable_overrides != null) {
      new_width
	= (Integer) variable_overrides.getAttributeValue (WIDTH_, null);
      new_height
	= (Integer) variable_overrides.getAttributeValue (HEIGHT_, null);
    }
    resetWidthandHeight(new_width, new_height);
  }

  public Structure getVariableOverrides() {
    //we should probably return a copy
    return variable_overrides;
  }

  public Structure getRegionOverrides() {
    //we should probably return a copy
    return region_overrides;
  }

 /**
  *
  *Draws the IconRendering into the Graphics g at the point (left,top) 
  *clipped by the current width and height.
  *@param g Graphics to which to draw.
  *@param left - leftmost point of icon within g.
  *@param top  -  topmost point of icon within g.
  *
  **/
  
  public void Draw(Graphics g, int left, int top) {

    if (renderings != null) {
      int x_scale = scale_constant*(renderingParameters.width)/description_width;
      int y_scale = scale_constant*(renderingParameters.height)/description_height;
      int xOffset = 0, yOffset = 0;
      int rotation = renderingParameters.rotationindegrees; 
      if (rotation == 90 || rotation == 270) {
	x_scale = scale_constant*(renderingParameters.width)/description_height;
	y_scale = scale_constant*(renderingParameters.height)/description_width;
	int offset = (description_width-description_height)/2;
	xOffset -=x_scale*offset/scale_constant;
	yOffset +=y_scale*offset/scale_constant;
      }

      Graphics subg;
      if (dubbuf)
	//DUBBUF CODE HAS NOT BEEN UPDATED, SO BEWARE IF YOU TURN IT ON
	subg = null; //dbg;
      else {
	subg = g.create();
	subg.clipRect(left, top, renderingParameters.width + 1, renderingParameters.height + 1);
	subg.translate(left+xOffset,top+yOffset);
      }
      
      int count = renderings.size();
      int i = 0;
      Object rendering = renderings.elementAt(i);
      if (rendering instanceof IconBackgroundLayer) {
	if (drawingDebugp)
	  System.err.println("drawing-background-layer");
	((IconBackgroundLayer) rendering).Draw(subg,
					       renderingParameters.width, renderingParameters.height,
					       x_scale, y_scale,
					       renderingParameters.rotationindegrees,
					       renderingParameters.pivotpoint,
					       renderingParameters.reflected);
	//renderingParameters.orientation);
	i++;
      }
      while (i < count) {
	rendering = renderings.elementAt(i);
	if (rendering instanceof Image) {
	  if (drawingDebugp)
	    System.err.println("drawing-static-layer");
	  subg.drawImage((Image) rendering,0,0, null);
	}
	else {
	  if (drawingDebugp)
	    System.err.println("drawing-dynamic-layer");
	  ((Layer) rendering).Draw(subg,
				   x_scale, y_scale,
				   renderingParameters.rotationindegrees, renderingParameters.pivotpoint,
				   renderingParameters.reflected,
				   region_overrides,
				   variable_overrides);
	}
	i++;
      }
      if (dubbuf) {
	//g.drawImage(doublebuffer, left, top, null, null);
	//doublebuffer.flush();
      }
      else subg.dispose();
    }
  }
}


class IconRenderingParameters {

  IconRenderingManager irm;
  int width, height, orientation, rotationindegrees;
  boolean reflected;
  Point pivotpoint;
  IconDescription drawingdescription;

  IconRenderingParameters () {
  }

  IconRenderingParameters (IconRenderingManager irm,
			   int width,
			   int height,
			   int orientation,
			   int rotationindegrees,
			   boolean reflected,
			   Point pivotpoint,
			   IconDescription drawingdescription) {
    this.irm = irm;
    this.width = width;
    this.height = height;
    this.orientation = orientation;
    this.rotationindegrees = rotationindegrees;
    this.reflected = reflected;
    this.pivotpoint = pivotpoint;
    this.drawingdescription = drawingdescription;
  }

  @Override
  public boolean equals(Object other) {
	if (other == null ||!IconRenderingParameters.class.equals(other.getClass())){
		return false;
    }
    IconRenderingParameters ir_other = (IconRenderingParameters) other;
    return (drawingdescription.equals(ir_other.drawingdescription) &&
	    orientation == ir_other.orientation && 
	    width == ir_other.width &&
	    height == ir_other.height);
  }

  @Override
  public int hashCode() {
    int drawingDescriptionCode = drawingdescription.hashCode();
    int hashcode
      = (int) (drawingDescriptionCode|(orientation<<9)|(width<<12)|(height<<22));
    return hashcode;
  }

}
