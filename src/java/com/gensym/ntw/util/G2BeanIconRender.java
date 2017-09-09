package com.gensym.ntw.util;

import java.awt.*;
import java.util.Enumeration;
import com.gensym.irm.*;
import com.gensym.draw.*;
import com.gensym.classes.Entity;
import com.gensym.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;

/**
 * This is a Icon Render helper class for beans created from the BeanBuilder.
 */
public class G2BeanIconRender extends Component implements WorkspaceListener {

  private boolean showIconUpdates = false;
  private transient Item item = null;
  private transient IconRendering iconRendering = null;
  private transient KbWorkspace currentWorkspace = null;
  private transient Structure logicalColorMap = new Structure();
  private boolean scaleImageToFit = true;
  private transient boolean workspaceListener = false;
  private Component parent = null;

  private static final Symbol 
              COLOR_PATTERN_CHANGES_ = Symbol.intern ("COLOR-PATTERN-CHANGES"),
              WIDTH_ = Symbol.intern ("WIDTH"), 
              HEIGHT_ = Symbol.intern ("HEIGHT");

  /**
   * This constructor will create a G2BeanIconRender, where all drawing is 
   * controlled by a parent icon. Any Icon update events are reported to 
   * the parent via repaint();
   */
  public G2BeanIconRender(Component parent) {
    this.parent = parent;
  }

  /** Default Constructor */
  public G2BeanIconRender() {
    super();
  }


  /**
   * This method allows the item for this renderer to be set.
   * @param Item to be wrapped
   */
  public void setItem(Item item) {
    // Clean up any workspace listening for the last item
    if (this.item != null) {
      boolean currentShowIconUpdates = showIconUpdates;
      setShowIconUpdates(false);
      boolean showIconUpdates = currentShowIconUpdates;
    }
    this.item = item;
    if (item != null) {
      getIconDescription();
      if (showIconUpdates)
	setShowIconUpdates(showIconUpdates);
    }
  }



 /**
  * This method returns the item for which the rendere will generate an image
  *@param Item
  */
  public Item getItem() {
    return item;
  }



  /**
   * This method enables the setting of the showIconUpdates attribute.
   *
   * @param boolean flag to set this Java object to show icon color and
   *        variable changes in the icon of the G2 item it represents
   */
  public void setScaleImageToFit(boolean newScaleImageToFit) {
    scaleImageToFit = newScaleImageToFit;
    getIconDescription();
    if (parent != null)
      parent.repaint();
    else
      repaint(); //standalone
  }


  /**
   * This method allows the setting of the scaleImageToFit attribute; which
   * indicates if the image for this bean is to be scaled so as to fit
   * within the bounds of the bean or not.
   * @return boolean flag representing this property
   */
   public boolean isScaleImageToFit() {
    return scaleImageToFit;
  }

  /**
   * This method allows the boolean value of the showIconUpdates attribute to
   * be obtained.
   * @return boolean flag if true this Java object shows icon color and
   *        variable changes in the icon of the G2 item it represents
   */
  public boolean isShowIconUpdates() {
    return showIconUpdates;
  }




  /**
   * This method enables the setting of the showIconUpdates attribute.
   * @param boolean flag to set this Java object to show icon color and
   *        variable changes in the icon of the G2 item it represents
   */
  public void setShowIconUpdates(boolean newShowIconUpdates) {
    showIconUpdates = newShowIconUpdates;
    if (item != null) {
      KbWorkspace parentWorkspace = getContainmentWorkspace(item);
      if(parentWorkspace != null)
	try {
	  if(showIconUpdates && !workspaceListener) {
	    parentWorkspace.addWorkspaceListener(this);
	    workspaceListener = true;
	    getIconDescription();
	  } else if (!showIconUpdates && workspaceListener) {
	    workspaceListener = false;
	    parentWorkspace.removeWorkspaceListener(this);
	  }
        } catch(Exception g2ae) {
	  System.err.println(g2ae);
	  g2ae.printStackTrace();
	}
      else
	showIconUpdates = false;
    }

    if (parent == null) //standalone
      repaint();
  }

  /**
   * This method return the workspace upon which the wrapped item is located
   * used when hooking the bean to listen for icon event changes.
   * @param  Item a G2 Item
   * @return KbWorkspace  which the G2 Item is on or null
   */
  private KbWorkspace getContainmentWorkspace(Item g2Item)  {
    if(g2Item != null) {

      KbWorkspace parentWorkspace = null;
      Sequence seq = null;
      try {
	seq = g2Item.getContainmentHierarchy();
	if(seq != null && seq.capacity() > 0)
	  try {
	  parentWorkspace = (KbWorkspace)seq.firstElement();
	  if(getCurrentWorkspace() == null)
	    setCurrentWorkspace(parentWorkspace);
	  else
	    if(!getCurrentWorkspace().equals(parentWorkspace))
	      setCurrentWorkspace(parentWorkspace);
	}
	catch(Exception ex2) {
	  System.err.println(ex2);
	  ex2.printStackTrace();
	}
      }
      catch(Exception ex1) {
	  System.err.println(ex1);
	  ex1.printStackTrace();
	}
      return getCurrentWorkspace();
    }
    else
      return null; // cos the g2Item was null
  }

  /**
   * This method enabled the KbWorkspace currently associated with the item
   * to be stored in the currentWorkspace property.
   *
   * @param newCurrentWorkspace
   */
  private void setCurrentWorkspace(KbWorkspace newCurrentWorkspace) {
    currentWorkspace = newCurrentWorkspace;
  }

  /**
   * This method returns the workspace currently associated with the item
   * @return  the workspace upon which the wrapped item currently resides.
   */
  public KbWorkspace getCurrentWorkspace() {
    return currentWorkspace;
  }





  /**
   * Invoked when the listener is added
   * (within the context of the addWorkspaceListener method).
   *@param the WorkspaceEvent
   */
  @Override
  public void receivedInitialDownload (WorkspaceEvent event){}


  /**
   * Invoked when an item is transferred onto the Workspace
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemAdded(WorkspaceEvent event) {
  }

  /**
   *
   *Invoked when an item is removed from a workspace.
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemRemoved(WorkspaceEvent event) {

    KbWorkspace target = (KbWorkspace)event.getSource();
    try {
	target.removeWorkspaceListener(this);
    }
    catch(Exception exception) {}

    // check to see if the item has been placed on onother workspace
    setShowIconUpdates(isShowIconUpdates());
  }

  /**
   * Invoked when the Workspace bounds changes
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceResized (WorkspaceEvent event){

  }

  /**
   * Invoked when an item on the workspace is moved
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemMoved (WorkspaceEvent event){

  }

  /**
   * Invoked when an item on the workspace is resized
   *@param the WorkspaceEvent
   */

  @Override
  public void workspaceItemResized (WorkspaceEvent event){

  }

  /**
   * Invoked when an item on the workspace is rotated
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemRotated (WorkspaceEvent event){

  }

  /**
   * Invoked when an item on the workspace changes colors
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemColorsChanged (WorkspaceEvent event) {

    Item changedItem = event.getItem();
    if(changedItem != null && changedItem.equals(item)){
      handleWorkspaceItemColorsChanged(event);
    }
  }

  /**
   * Invoked when the icon-variables of an item on the workspace changes
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemIconVariablesChanged (WorkspaceEvent event) {

      Item changedItem = event.getItem();
      if(changedItem != null && changedItem.equals(item)) {
	      handleWorkspaceItemIconVariablesChanged(event);
      }
  }

  /**
   * Invoked when one of the interesting virtual attributes of an
   * item changes.
   *@param the WorkspaceEvent
   */
  @Override
  public void workspaceItemAttributesChanged (WorkspaceEvent event){}


  /**
   * Method for receiving overrides to the variables of the IconRendering.
   *@param the WorkspaceEvent
   */
  public void handleWorkspaceItemIconVariablesChanged(WorkspaceEvent event) {
    //System.out.println("in helper handleWorkspaceItemIconVariablesChanged");
      Structure variableOverrides = event.getInfo();
      iconRendering.setRenderingOverrides(variableOverrides,
					  iconRendering.getRegionOverrides());

      if (parent != null)
	parent.repaint();
      else
	repaint(); //standalone;
  }


  /**
   * Method for receiving overrides to the colors of an icon's regions.
   *@param the WorkspaceEvent
   */
  private void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    //System.out.println("in helper handleWorkspaceItemColorsChanged");
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
      = (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);

    updateColorPattern(colorPatternChanges);

    if (parent != null)
      parent.repaint();
    else
      repaint(); //standalone;

  }



  /**
   * Method for receiving overrides to the colors of an icon's regions.
   * @param colorPatternChange A Structure of region-name:
   * color-name attributes.
   */
   private void updateColorPattern(Structure colorPatternChange){

     //System.out.println("in helper updateColorPattern "+
     //	       colorPatternChange.toString());

    if (colorPatternChange != null) {
      Enumeration newColorNames = colorPatternChange.getAttributeNames();

      Symbol nextColor;
      Symbol nextColorValue;
      while (newColorNames.hasMoreElements()) {
	nextColor = (Symbol) newColorNames.nextElement();

	nextColorValue =
	  (Symbol)colorPatternChange.getAttributeValue(nextColor, null);

	logicalColorMap.setAttributeValue(nextColor,nextColorValue);

      }//end while
    }// end if

    if(logicalColorMap.getAttributeCount() != 0){
    iconRendering.setRenderingOverrides(iconRendering.getVariableOverrides(),
					transformColorValues(logicalColorMap));
    }
   }


  /**
   * Method for remapping icon color changes
   * @regionOverrides  Structure holding the icon region names and color
   * changes that this object has undergone.
   *
   */
  private static Structure transformColorValues(Structure regionOverrides) {

    if (regionOverrides == null)
      return regionOverrides;
    else {
      regionOverrides = (Structure) regionOverrides.clone();
      Symbol regionName; Symbol color;
      for (Enumeration regionNames
	     = regionOverrides.getAttributeNames();
	   regionNames.hasMoreElements();)
	{
	  regionName = (Symbol) regionNames.nextElement();
	  color =(Symbol) regionOverrides.getAttributeValue(regionName, null);


	  if (color instanceof Symbol)
	    regionOverrides.setAttributeValue(regionName,
					      (Color)G2ColorMap.get(color));
	}
    }
    return regionOverrides;
  }

  /**
   * Method override of the setSize method,
   *
   * If the G2 item that this bean represents has been fetched, then
   * set size also change the size of the icon
   *
   * @param d  - the Dimension describing the new size for the icon
   */
  @Override
  public void setSize( Dimension d)
  {
    getIconDescription(d);
    if (parent == null)
      super.setSize(d);
    else
      parent.repaint();
  }


   /**
 * Method to get the current icon description for the wrapped items class
 */
  private void getIconDescription ()  {
    Dimension d = null;
    if (parent != null)
      d = parent.getSize();
    else
      d = getSize();
    getIconDescription(d);
  }

 /**
 * Method to get the current icon description for the wrapped items class
 */
  private void getIconDescription (Dimension d)  {

  if(item == null) return;
    // If we do not have access to an Iconrenderinf manager
    // then forget this
    IconRenderingManager irm =
           ((TwAccess)((com.gensym.classes.ImplAccess)item).getContext()).getIconManager();

    try {
      Entity entity = (Entity)item;
      Structure iconDescription = entity.getIconDescriptionForClass ();
      Structure iconVariables   = entity.getIconVariables ();
      Structure iconRegions     = entity.getItemColorPattern ();

      int width = 32;
      int height = 32;

      if(isScaleImageToFit()) {
	width = d.width -1;
	height = d.height -1;
      }
      else {
	width  =((Integer)
		 iconVariables.getAttributeValue(WIDTH_, null)).intValue ();
	height =((Integer)
		 iconVariables.getAttributeValue(HEIGHT_, null)).intValue ();
      }


      com.gensym.icons.IconDescription icd =
	new  com.gensym.icons.IconDescription (iconDescription);

      iconRendering = irm.GetIconRendering( icd ,
					     width , height , 0);
      // Make sure we have the default icon
      iconRendering.setRenderingOverrides(iconVariables, iconRegions);
      updateColorPattern(iconRegions);


    } catch (G2AccessException gae) {
      gae.printStackTrace ();
    }
  }

  private int lastwidth = 0;
  private int lastheight = 0;

  /**
  * Override Paint method
  */
  @Override
  public void paint(Graphics g) {
    if (scaleImageToFit) {
      Dimension d = (parent == null ? getSize() : parent.getSize());
      if (lastwidth != d.width ||
	  lastheight != d.height)
	getIconDescription(d);
        lastwidth = d.width;
	lastheight = d.height;
    }
    iconRendering.Draw(g,0,0) ;
  }

}









