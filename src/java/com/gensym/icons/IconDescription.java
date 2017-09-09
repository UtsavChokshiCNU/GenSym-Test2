package com.gensym.icons;

import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.ntw.util.*;
import java.awt.image.BufferedImage;


/**
 *
 *       <b>SYNOPSIS:<p></b>
 *         Stores G2 IconDescriptions.<p>
 *
 */

public class IconDescription {

  private static final Symbol REGION_NAME_   = Symbol.intern ("REGION-NAME");
  private static final Symbol COLOR_NAME_    = Symbol.intern ("COLOR-NAME");
  private static final Symbol VARIABLE_NAME_ = Symbol.intern ("VARIABLE-NAME");
  private static final Symbol INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");
  private static final Symbol WIDTH_         = Symbol.intern ("WIDTH");
  private static final Symbol HEIGHT_        = Symbol.intern ("HEIGHT");
  private static final Symbol REGIONS_       = Symbol.intern ("REGIONS");
  private static final Symbol VARIABLES_     = Symbol.intern ("VARIABLES");
  private static final Symbol LAYERS_        = Symbol.intern ("LAYERS");
  private static final Symbol ICON_BACKGROUND_LAYER_ = Symbol.intern ("ICON-BACKGROUND-LAYER");
  private static final Object COLOR_CAST     = new Object ();

  private static boolean we_can_render_transparent_layers = false;
  private static boolean makeAllLayersDynamic = true;
  private int width, height;
  private int extended_width; int extended_height;
  private Structure regions;
  private Structure variables;
  private IconBackgroundLayer icon_background_layer;
  private Object[] layers;

  
  
  /**
   *@param gsi_icondescription_object the GsiObject recieved from
   *   JGsi that represents a G2 icondescription.
   */
  //protected IconDescription(GsiObject gsi_icondescription_object) {}

  
  /**
   *@param <em>width</em> the width of the icon at normal scale
   *@param <em>height</em> the height of the icon at normal scale
   *@param <em>regions</em> a Structure whose AttributeNames are 
   *       region_names, and whose AttributeValues g2_colors.
   *@param <em>variables</em> a Structure whose AttributeNames 
   *      are variable_names and whose AttributeValues are variable_values.
   *      A variable_value can be a String, an Integer or a Symbol
   *@param <em>background_layer</em> an optional layer that is the background
   *      of the icon when rendered. May be of type "g2_color" or "image"
   *@param <em>layers</em> an array of Layers.
   *@see com.gensym.irm.IconRendering#setRenderingOverrides
   *@see Layer
   *@see G2ColorMap
   */
  protected IconDescription(int width, int height,
			    Sequence regions, Sequence variables,
			    IconBackgroundLayer background_layer,
			    Object[] layers) {
    this.width = width; 
    this.height = height;
    if (regions != null) 
      this.regions = flattenSpecList (regions,
				      REGION_NAME_,
				      COLOR_NAME_,
				      COLOR_CAST);
    if (variables != null) 
      this.variables = flattenSpecList (variables,
					VARIABLE_NAME_,
					INITIAL_VALUE_,
					null);
    //System.out.println("variables--> " + this.variables + variables);
    this.icon_background_layer = background_layer;
    this.layers = layers;
    setExtendedWidthandHeight();
  }

  private Structure flattenSpecList (Sequence speclist, Symbol namekey, Symbol valuekey,
				     Object classCastName) {
    if (speclist == null)
      return null;
    else {
      int specListSize = speclist.size ();
      Structure newStruct = new Structure (/*specListSize*/);
      Structure currentspec;
      Symbol name; 
      Object value;
      for (int i=0; i<specListSize; i++) {
	currentspec = (Structure) speclist.elementAt (i);
	name = (Symbol) currentspec.getAttributeValue (namekey, null);
	value = currentspec.getAttributeValue (valuekey, null);
	if (classCastName != null && classCastName.equals (COLOR_CAST))
	  value = (Color) G2ColorMap.get ((Symbol)value);
	if (name != null)
	  newStruct.setAttributeValue (name, value);
      }
      return newStruct;
    }
  }
  
  Layer[] castObjectArray (Sequence sequence, String classname) {
    Structure struct;
    Layer layer;
    int count = sequence.size();
    Layer[] newobjects =  new Layer[count];
    for (int i=0; i<count; i++) {
      struct = (Structure) sequence.elementAt (i);
      layer =  new Layer(struct, variables, regions);
      newobjects[i] = layer;
    }
    return newobjects;
  }
  
  public IconDescription(Structure data) {
    //System.out.println("IconDescription constructor recieved data from cdm" + data);
    Integer w = (Integer) data.getAttributeValue (WIDTH_, null);
    if (w != null)
      this.width = w.intValue();
    Integer h = (Integer) data.getAttributeValue (HEIGHT_, null);
    if (h != null)
      this.height = h.intValue();
    Sequence regionsdata = (Sequence) data.getAttributeValue (REGIONS_, null);
    this.regions = flattenSpecList (regionsdata,
				    REGION_NAME_,
				    COLOR_NAME_,
				    COLOR_CAST);
    Sequence variablesdata = (Sequence) data.getAttributeValue (VARIABLES_, null);
    this.variables = flattenSpecList (variablesdata,
				      VARIABLE_NAME_,
				      INITIAL_VALUE_,
				      null);
    //System.out.println("variables--> " + this.variables + variables);
    
    Object iconBgLayer = data.getAttributeValue(ICON_BACKGROUND_LAYER_, null);
    if (iconBgLayer instanceof Structure) {
      Structure iconbackgroundlayerstruct
	= (Structure) iconBgLayer;
      this.icon_background_layer = new IconBackgroundLayer(iconbackgroundlayerstruct);
    }
    Sequence layersequence = (Sequence) data.getAttributeValue (LAYERS_, null);
    Layer[] layersLocal = castObjectArray (layersequence, "Layer");
    this.layers = layersLocal;
    setExtendedWidthandHeight();
    /*System.out.println("end of constructor has" +
		       this.width + this.height + this.regions + this.variables +
		       this.icon_background_layer + this.layers);
		       */
  }
  
  private void setExtendedWidthandHeight() {
    int layer_count = layers.length;
    Layer layer;
    int[] extrema = new int[2];
    extrema[0] = width; 
    extrema[1] = height;
    for (int i = 0; i<layer_count; i++) {
      layer = (Layer) layers[i];
      layer.updateRightBottomExtrema(extrema,variables, null);
    }
    extended_width = extrema[0];  //may extend past the width
    extended_height = extrema[1]; //may extend past the height
  }

  private Vector DrawLayersOffScreen(int x_scale, int y_scale,
				     int rotationindegrees, Point pivotpoint,
				     boolean reflected) {
    Vector renderings = new Vector();
    int layer_count = layers.length;
    boolean need_new_image = true;
    int scale_constant = G2PrimitiveDraw.scale_constant;
    int image_width = extended_width*x_scale/scale_constant;
    int image_height = extended_height*y_scale/scale_constant;

    Layer layer;
    Graphics g = null;
    
    Image current_offscreenbitmap = null;

    if (icon_background_layer != null) {
      Image scaledImage = null, image = getBackgroundImage();
      if (makeAllLayersDynamic || we_can_render_transparent_layers) {
	IconBackgroundLayer ibl = icon_background_layer;
	if (image != null) {
	  ibl = new IconBackgroundLayer(icon_background_layer.type,
					null, null,
					icon_background_layer.getImageLocation());
	  ibl.setImage(image,
		       icon_background_layer.getImageWidth(),
		       icon_background_layer.getImageHeight());
	}
	renderings.addElement(ibl);
      } else {
	current_offscreenbitmap
	  = WindowUtil.createImage(image_width + 1,image_height + 1);
	if (current_offscreenbitmap != null) {
	  g = (Graphics) current_offscreenbitmap.getGraphics();
	  g.setColor(Color.white);
	  g.fillRect(0,0,image_width + 1, image_height + 1);
	  icon_background_layer.Draw(g,
				     image_width, image_height,
				     x_scale, y_scale,
				     rotationindegrees,
				     pivotpoint,
				     reflected);
	  renderings.addElement(current_offscreenbitmap);
	  need_new_image = false;
	}
	else
	  System.err.println("couldn't allocate offscreen bitmap");
      }
    }
    boolean hasDynamicColor;
    for (int i = 0; i < layer_count; i++) {
      layer = (Layer) layers[i];
      if (layer != null) {
	if (makeAllLayersDynamic || layer.isDynamic()) {
	  //System.err.println("layer " + i + " is dynamic. Adding as is");
	  //could do some computation here!!!!
	  renderings.addElement(layer);
	  need_new_image = true;
	} else {
	  hasDynamicColor = layer.hasDynamicColor();
	  //System.out.println("Has Dynamic Color = " + hasDynamicColor);
	  if (need_new_image||hasDynamicColor) {
	    if (g != null) {
	    	g.dispose();
	    }
	    current_offscreenbitmap
	      = WindowUtil.createImage(image_width + 1, image_height + 1);
	    if (current_offscreenbitmap != null) {
	      g = (Graphics) current_offscreenbitmap.getGraphics();
	      g.setColor(Color.white);
	      g.fillRect(0,0,image_width + 1, image_height + 1);
	    }
	    else System.err.println("offscreen image allocation" +
				    image_width + " " + image_height +
				    "returned null in DrawLayersOffScreen" );
	    renderings.addElement(current_offscreenbitmap);
	    need_new_image = hasDynamicColor;
	  }
	  if (g != null) {
	    //System.err.println("drawing Layer " + i + " into offscreenbitmap");
	    layer.Draw(g,
		       x_scale, y_scale,
		       rotationindegrees, pivotpoint,
		       reflected,
		       null, null);
	  }
	  else System.err.println("Graphic g == null in DrawLayersOffScreen");
	}
      }
    }
    if (g != null)
      g.dispose();
    return renderings;
  }

  /** Sets the layer defaultColors.
   * Made for the use of "icons as plot markers" in trend-charts.
   * @undocumented
   */
  public void setLayerColors(Color color, boolean monochromeOnly) {
    if (!monochromeOnly || isMonochrome()) {
      int layer_count = layers.length;
      for (int i = 0; i < layer_count; i++) {
	Layer layer = (Layer) layers[i];
	layer.defaultColor = color;
      }
    }
  }

  /** Returns true if all Layers have the same color.
   * Made for the use of "icons as plot markers" in trend-charts.
   * @undocumented
   */
  private boolean isMonochrome() {
    int layer_count = layers.length;
    if (layer_count == 0)
      return true;

    Color color = ((Layer)layers[0]).defaultColor;

    if (color == null) {
      for (int i = 0; i < layer_count; i++) {
	Layer layer = (Layer) layers[i];
	if (layer.defaultColor != null)
	  return false;
      }
    } else {
      for (int i = 0; i < layer_count; i++) {
	Layer layer = (Layer) layers[i];
	if (!color.equals(layer.defaultColor))
	  return false;
      }
    }

    return true;
  }

  /**
   *@return the width of the icon description.
   */
  public int getWidth() {
    return width;
  }
  
  /**
   *@return the height of the icon description.
   */
  public int getHeight() {
    return height;
  }

  /**
   *@return the regions, if any, of the icondescription in a Structure.
   */
  public Structure getRegions() {
    return regions;
  }
  
  /**
   *@return the default variables, if any, of the icondescription in a Structure.
   */
  public Structure getDefaultVariables() {
    return variables;
  }

  public Symbol getBackgroundImageName()
  {
    if (icon_background_layer != null)
      return icon_background_layer.getImageName();
    else
      return null;
  }

  public void setBackgroundImage(Image image,
				 int width,
				 int height)
  {
    if (icon_background_layer != null)
      icon_background_layer.setImage(image, width, height);
  }

  public int getBackgroundImageWidth()
  {
    if (icon_background_layer != null)
      return icon_background_layer.getImageWidth();
    else
      return 0;
  }

  public int getBackgroundImageHeight()
  {
    if (icon_background_layer != null)
      return icon_background_layer.getImageHeight();
    else
      return 0;
  }
  
  public Image getBackgroundImage()
  {
    if (icon_background_layer != null)
      return icon_background_layer.getImage();
    else
      return null;
  }
  
  @Override
  public String toString() {
    return "#<ICON-DESCRIPTION @" + Integer.toHexString(hashCode()) + ">";
  }

  /*public boolean equals(IconDescription otherID) {
    return (otherID.width == width &&
	    otherID.height == height &&
	    otherID.regions.equals(regions) &&
	    otherID.variables.equals(variables) &&
	    otherID.icon_background_layer.equals(icon_background_layer) &&
	    otherID.layers.equals(layers));
  }
  */
	    
  /**
   *@param <em> x_scale</em> the horizontal scaling factor at which draw this
   * description.
   *@param <em> y_scale</em> the vertical scaling factor at which draw this
   * description.
   *@param <em> rotationindegrees </em> an int representing a g2 icon rotation in degrees.
   *@param <em> pivotpoint </em> the point around which elements should be rotated/reflected,
   * typically the center.
   *@return a Vector of dynamic Layers an static Images(maybe change to Sequence when built)
   *@see Layer#Draw
   */
  public Vector DrawOffScreen(int x_scale, int y_scale,
			      int rotationindegrees, Point pivotpoint,
			      boolean reflected) {
    Vector renderings = null;
    renderings = DrawLayersOffScreen(x_scale, y_scale,
				     rotationindegrees, pivotpoint,
				     reflected);
    return renderings;
  }

  public Image createImage(int width, int height,
			   int rotationindegrees,
			   Point pivotpoint,
			   boolean reflected,
			   Structure regionOverrides,
			   Structure variableOverrides) {
    int scaleConstant = G2PrimitiveDraw.scale_constant;
    int xScale = scaleConstant*width/getWidth()-1;
    int yScale = scaleConstant*height/getHeight()-1;
    int layerCount = layers.length;
    
    Image image = new BufferedImage(width,height,BufferedImage.TYPE_INT_ARGB);
    //WindowUtil.createImage(width, height);
    Graphics g = image.getGraphics();

    if (icon_background_layer != null)
      icon_background_layer.Draw(g, width, height,
				 xScale, yScale,
				 rotationindegrees,
				 pivotpoint,
				 reflected);
    Layer layer;
    for (int i=0; i<layerCount; i++) {
      layer = (Layer)layers[i];
      layer.Draw(g,
		 xScale, yScale,
		 rotationindegrees, pivotpoint,
		 reflected,
		 regionOverrides,
		 variableOverrides);
    }
    g.dispose();
    return image;
  }
  
}




