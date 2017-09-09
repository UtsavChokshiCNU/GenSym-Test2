package com.gensym.draw;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.icons.*;
import com.gensym.util.*;
import com.gensym.message.*;

/**
 *
 * IconELement
 *
 */
public class IconElement extends BasicDrawElement
{
  private boolean paintMode = true;
  private IconRenderingManager irm;
  protected Rectangle[] bounds;
  protected IconRendering iconRendering;
  protected IconDescription iconDescription;
  protected int orientation;

  
  public IconElement(IconDescription iconDescription,
		     Structure variableOverrides,
		     Structure regionOverrides,
		     int orientation,
		     int x, int y, int width, int height,
		     IconRenderingManager irm)
  {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y, width,height);
    this.irm = irm;
    this.iconDescription = iconDescription;
    this.orientation = orientation;
    updateIconRendering(true, false);  //Do preserve overrides, don't update images
    if (iconRendering != null)
      iconRendering.setRenderingOverrides(variableOverrides, regionOverrides);
    setSize(width,height);
    setLocation(x,y);
  }

  protected void updateIconRendering(boolean preserveOverrides, boolean updateImages)
  {
    if (iconDescription == null)
      return;
    /* Note: it is important to first get a new rendering, and
       and then to drop the pointer to the old rendering.  This
       will ensure a non-empty sequence of renderings for this
       drawingdescription after the rendering is decached, thereby
       not allowing the decaching mechanism to decache the empty
       sequence itself. */
    Rectangle[] bounds=getExactBounds();
    /* yduJ 5/02: Need to actually tell this to update, or it'll just 
       get the cached one.  Pass null as first arg -- it's ignored. */
    if (updateImages)
      irm.update(null,iconDescription);
    IconRendering updatedIconRendering
      = irm.GetIconRendering (iconDescription,
			      bounds[0].width - 1,
			      bounds[0].height - 1,
			      orientation);
    if (preserveOverrides &&
	updatedIconRendering != null &&
	iconRendering != null)
      updatedIconRendering.setRenderingOverrides (iconRendering.getVariableOverrides(),
						  iconRendering.getRegionOverrides());
    if (updatedIconRendering == null) 
      Trace.exception(new Exception("No Icon Rendering available for iconDescription of " +
				    iconDescription));
    this.iconRendering = updatedIconRendering;
  }

  @Override
  public void shift (int shift_x, int shift_y)
  {
    bounds[0].translate(shift_x, shift_y);
    Point location = getLocation();
    setLocation(location.x + shift_x, location.y + shift_y);
  }

  @Override
  public void setSize(int width, int height) {
    bounds[0].width = width;
    bounds[0].height = height;
    super.setSize(width,height);
  }

  @Override
  public boolean contains(int logical_x, int logical_y)
  {
    Rectangle boundsRect = bounds[0];
    return bounds[0].contains(logical_x + boundsRect.x,
			      logical_y + boundsRect.y);
  }

  /**
   * @return the IconRendering that is used to paint
   * this element.
   */
  public IconRendering getIconRendering() {
    return iconRendering;
  }

  public void setPaintMode(boolean paintMode) {
    this.paintMode = paintMode;
  }
  
  /**
   * Paint the IconRendering if it is valid, otherwise,
   * paints a blue rectangle encompassing the bounds of this
   * element.
   */
  @Override
  public void paint (Graphics g)
  {
    if (!paintMode)
      g.setXORMode(((PersistentCanvas)getParent()).getBackgroundColor());
    if ((iconRendering != null)&& iconRendering.isValid())
      iconRendering.Draw(g,0,0);
    else {
      Rectangle tb = getExactBounds()[0];
      g.setColor(Color.blue);
      Rectangle[] bounds=getExactBounds();
      g.fillRect(0,0, bounds[0].width, bounds[0].height);
    }
    super.paint(g);
  }

  @Override
  public void changeColor(Object logicalColor, Color color)
  {
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
  }

  @Override
  public Object[] getLogicalColors()
  {
    return null;
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return bounds;
  }

}

