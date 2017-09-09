package com.gensym.irm;

import java.util.*;
import java.lang.*;
import java.awt.*;
import java.applet.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.icons.IconDescription;
import com.gensym.jgi.G2AccessException;




/**
 *     <b>SYNOPSIS:<p></b>
 *     1. Creates and stores renderings of a particuliar IconDescription,
 *        orientation, width and height. <p>
 *     2. Returns a copy(snapshot) of the stored rendering through the
 *        public interface GetIconRendering.  All static layers
 *        are already rendered and cached as Images.
 *        This rendering will NOT stay in synch with the
 *        ClassDefinitionManager.  Users of the IconRenderingManager must
 *        subscribe to the ClassDefinitionManager and invalidate their
 *        IconRendering copies on their own.<p>
 *     3. Calling the IconRendering's Draw(Graphics g, int left, int top)
 *        method will paint the rendering's layers to g at (left,top) 
 *        clipping by the current width and height. The rendering's current 
 *        overrides are substituted into dynamic layers as they are drawn 
 *        (directly) to the screen. <p>
 *     4. A user who has retrieved an IconRendering through this interface
 *        may set the rendering's overrides through the method
 *        setRenderingOverrides(Structure variables_overrides,Structure region_overrides).<p>
 *
 */

public class IconRenderingManager extends Object implements Observer {
  
  private Hashtable table = new Hashtable();
  private IconRendering scratch_rendering = new IconRendering();
  private boolean updateDebugp = false;
  private boolean irmdebugp = false;

  
  public IconRenderingManager() {}

  private Sequence getRenderingsForIconDescription(IconDescription id) {
    Sequence renderingsForIconDescription = (Sequence) table.get(id);
    if (renderingsForIconDescription == null) {
      if (irmdebugp)
	System.out.println("Initializing renderings for id = " + id);
      renderingsForIconDescription = new Sequence();
      table.put(id, renderingsForIconDescription);
    }
    return renderingsForIconDescription;
  }
      
  private IconRendering MakeIconRendering (IconDescription id,
					   int width, int height,
					   int orientation)
  {
    IconRendering icon_rendering
      = new IconRendering(id, width, height, orientation, this);
    
    if (icon_rendering.isValid()) {
      Sequence renderingsForIconDescription = getRenderingsForIconDescription(id);
      renderingsForIconDescription.addElement(icon_rendering);
      return icon_rendering;
    } else if (irmdebugp)
      System.out.println("MAKEICONRENDERING got an inValid rendering\n");
    
      return null;
  }

  private synchronized void set_scratch_rendering (IconDescription id,
						   int width, int height,
						   int orientation) {
    scratch_rendering.set(id, width, height, orientation);
  }

  private void removeIconRenderings(IconDescription id) {
    table.remove(id);
  }

  private void removeIconRendering(IconDescription id, IconRendering ir) {
    Sequence renderingsForIconDescription = (Sequence) table.get(id);
    if (irmdebugp)
      System.out.println("About to remove " + ir +
			 " from " + renderingsForIconDescription);
    renderingsForIconDescription.removeElement(ir);
    if (renderingsForIconDescription.isEmpty()) {
      if (irmdebugp)
	System.out.println("About to remove empty renderings list " +
			   renderingsForIconDescription);
      table.remove(id);
    }
  }
  
  void removeIconRendering(IconRendering ir) {
    if (irmdebugp)
      System.out.println("The IconRendering " + ir + " is no longer being used");
    IconDescription id = ir.getIconDescription();
    removeIconRendering(id, ir);
  }

  /**
   *@param <em>id</em> The IconDescription that is desired.
   *@param <em>width</em> The width of the actual rendering.  The scale of the
   * rendering is determined by width/IconDescription.width
   *@param <em>height</em> The heightof the actual rendering.  The scale of the
   * rendering is determined by height/IconDescription.height
   *@param orientation An integer representing the orientation of the rendering.
   *@return true iff the IconDescription is already drawn and cached.
   */
  
  public boolean isCached (IconDescription id,
			   int width, int height,
			   int orientation) {
    set_scratch_rendering(id, width, height, orientation);
    Sequence renderingsForIconDescription = getRenderingsForIconDescription(id);
    return renderingsForIconDescription.contains(scratch_rendering);
  }
      
  /**
   *@param <em>id</em> The IconDescription that is desired.
   *@param <em>width</em> The width of the actual rendering.  The scale of the
   * rendering is determined by width/IconDescription.width
   *@param <em>height</em> The heightof the actual rendering.  The scale of the
   * rendering is determined by height/IconDescription.height
   *@param orientation An integer representing the orientation of the rendering.
   *@return A copy of the stored IconRendering having the above properties.  All
   * static layers are already drawn, and are shared among all other copies of this
   * rendering. The user may use this copy as they like, calling setRenderingOverrides
   * and Draw at their will.  
   *@see IconRendering
   *@see IconDescription
   *@see IconBackgroundLayer
   *@see Layer
   *@see DrawingElement
   */
  public synchronized IconRendering GetIconRendering (IconDescription id,
						      int width, int height, 
						      int orientation)
  {
    IconRendering icon_rendering = null;
    if (id != null) {
      set_scratch_rendering(id, width, height, orientation);
      Sequence renderingsForIconDescription = getRenderingsForIconDescription(id);
      if (irmdebugp)
	System.out.println("RENDERINGS FOR ID " + renderingsForIconDescription.toString());
      int index = renderingsForIconDescription.indexOf(scratch_rendering);

      if (index != -1)
	icon_rendering  = (IconRendering) renderingsForIconDescription.elementAt(index);
      if (icon_rendering == null) {
	if (irmdebugp)
	  System.out.println("Couldnt Find a Rendering\n");
	icon_rendering = MakeIconRendering(id, width, height, orientation);
      }
      else if (!icon_rendering.isValid()) {
	icon_rendering = null;
      }
    }
    if (icon_rendering == null)
      return null;
    else 
      return icon_rendering.Copy(); 
  }


  /**
   *The update method through which the user can inform the irm of
   * changes to a particuliar IconDescription.  The IconRenderingManager
   * will invalidate all IconRenderings for that IconDescription, if it
   * is determined that the icon-description has changed. 
   *@param <em>slot</em> The IconDescription Slot that is begin observed.
   *@param <em>id</em> The IconDescription that has changed.
   */
    
  @Override
  public void update(Observable slot, Object id)
  {
    if (updateDebugp) {
      System.out.println("ICONRENDERINGMANAGER is receiving an UPDATE FROM "
			 + slot + "\n");
      System.out.println("arg-->" + id + "\n");
      System.out.println(toString());
    }
    if (id instanceof IconDescription)
      removeIconRenderings((IconDescription) id);
  }      

  
  /**
   *@return A String containing the contents of this IconRenderingManager
   *
   */
  
  @Override
  public String toString()
  {
    return "#<ICON-RENDERING-MANAGER @" + Integer.toHexString(super.hashCode()) +
      ">\n  " + table.toString() + "\n";
  }
}


