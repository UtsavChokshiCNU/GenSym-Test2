package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.ntw.util.G2FontMap;


/**
 * DefaultWorkspaceElement
 */

public class DefaultWorkspaceElement extends BasicDrawElement
implements WorkspaceElement {

  private static boolean defaultWorkspaceElementDebugP = false;
  private static final Font defFont = G2FontMap.get(14);
  private WorkspaceElementHelper helper;
  
  /**
   * @param item The g2 item which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   */
  public DefaultWorkspaceElement(Item item, WorkspaceView parent)
  throws G2AccessException {
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     item,
					     parent);
    //System.out.println ("Making new DefaultWorkspaceElement!" + this);
    bounds = helper.getExactBounds (item);
    setBounds (bounds[0].x, bounds[0].y, bounds[0].width, bounds[0].height);
  }

  private Rectangle[] bounds;
  @Override
  public Rectangle[] getExactBounds () {
    return bounds;
  }

  /**
   * Paints a Gray 3D rectangle with the text of the representation 
   * type of this element in the center.
   */
  @Override
  public void paint(Graphics g) {
    int shiftedX = 0;//bounds[0].x + x;
    int shiftedY = 0;//bounds[0].y + y;
    Rectangle[] bounds = getExactBounds();
    int width =  bounds[0].width;
    int height =  bounds[0].height;
    g.setColor(Color.lightGray);
    g.fill3DRect(shiftedX, shiftedY, width, height, true);
    
    /*g.fillRect(shiftedX, shiftedY, width, height);
      g.setColor(Color.black);
      g.drawRect(shiftedX, shiftedY, width -1 ,height - 1);*/
    
    Graphics subg = g.create();
    subg.clipRect(shiftedX + 1, shiftedY + 1,width - 2, height - 2);
    subg.setColor(Color.black);
    String label;
    try {
      label = getItem().getRepresentationType().toString();
    } catch (G2AccessException g2ae) {
      System.out.println(g2ae);
      label = "default-rep-type";
    }
    int fontSize = 14;
    subg.setFont(defFont);
    int length = label.length();
    subg.drawString(label,
		    shiftedX - (length*fontSize)/3 + width/2,
		    shiftedY + height/2);
    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (subg, bnds.x, bnds.y, bnds.width, bnds.height);
    }
    subg.dispose();
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

  /*WORKSPACE ELEMENT API*/

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
	= (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    canvas.invalidateElement(this);
  }

  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    helper.shift(event);   
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    helper.resize(event);
  }

  @Override
  public void receivedInitialValues (ItemEvent e) {
    helper.receivedInitialValues(e);
  }

  @Override
  public void itemModified (ItemEvent e) {
    helper.itemModified(e);
  }

  @Override
  public void itemDeleted (ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return helper.getDraggingGhost(left,top,width,height);
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    return helper.getDraggingGhost();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return helper.getDraggingGhost(markerLocn, currentX, currentY);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }
  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  @Override
  public void dispose() throws G2AccessException{
  }
}

