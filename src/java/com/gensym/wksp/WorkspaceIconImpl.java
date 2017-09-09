package com.gensym.wksp;

import java.util.*;
import java.awt.*;
import java.util.Observer;
import java.util.Observable;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.icons.IconDescription;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.classes.ImageDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Definition;
import com.gensym.classes.KbWorkspace;
import com.gensym.draw.BasicDrawElement;
import com.gensym.draw.IconElement;
import com.gensym.draw.PersistentCanvas;



/**
 *
 * WorkspaceIcon <p>
 * A WorkspaceElement that appears as an IconRendering
 * using the classname, bounds and orientation obtained from
 * the Item. The rendering is obtained from the IconRenderingManager.
 *
 */
public class WorkspaceIconImpl extends IconElement implements WorkspaceIcon {
  static boolean updateDebugp = false; 
  //Structure regionOverrides;
  WorkspaceElementHelper helper;
  private Structure logicalColorMap;

  private static final Symbol NORMAL_ = Symbol.intern ("NORMAL");
  private static final Symbol CLOCKWISE_90_ = Symbol.intern ("CLOCKWISE-90");
  private static final Symbol CLOCKWISE_180_ = Symbol.intern ("CLOCKWISE-180");
  private static final Symbol CLOCKWISE_270_ = Symbol.intern ("CLOCKWISE-270");
  private static final Symbol REFLECTED_ = Symbol.intern ("REFLECTED");
  private static final Symbol REFLECTED_CLOCKWISE_90_ = Symbol.intern ("REFLECTED-CLOCKWISE-90");
  private static final Symbol REFLECTED_CLOCKWISE_180_ = Symbol.intern ("REFLECTED-CLOCKWISE-180");
  private static final Symbol REFLECTED_CLOCKWISE_270_ = Symbol.intern ("REFLECTED-CLOCKWISE-270");

  /**
   * @param entity The g2 Entity which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceIcon.
   */  
  public WorkspaceIconImpl(Entity entity, WorkspaceView parent)
       throws G2AccessException
  {
    this(entity,
	 parent,
	 WorkspaceElementHelper.getExactBounds((Item)entity));
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     (Item)entity,
					     parent);
    // PBK notes that we need some sort of subscription to
    // the iconDescription. (And here it is -- yduJ 5/02)
    ImageDefinition def = getImageDefinition(entity, getIconDescription(entity));
    if (def != null) {
      this.imageDefinition = def;
      addImageDescriptionListener(this, def);
    }
  }
  
  private WorkspaceIconImpl(Entity entity,
			    WorkspaceView parent,
			    Rectangle[] bounds) throws G2AccessException
  {
    this (getIconDescription(entity),
	  entity.getIconVariables(),
	  (Structure)entity.getItemColorPattern(),
	  (PersistentCanvas) parent,
	  getOrientation(entity),
	  bounds[0].x,bounds[0].y, bounds[0].width + 1, bounds[0].height + 1 ,
	  getIconManager((Item)entity));
    addIconDescriptionListener(this, (Item)entity);
  }

  void handleIconDescriptionChange(boolean updateImage)
       throws G2AccessException
  {
    Rectangle[] currentBounds = getExactBounds();
    int length = currentBounds.length;
    Rectangle[] oldBounds = new Rectangle[length];
    for (int i = 0; i < length; i++) 
      oldBounds[i] = new Rectangle(currentBounds[i]);
    this.iconDescription = getIconDescription((Entity)getItem());
    updateIconRendering(false,updateImage); //Don't preserve overrides, updateImage as per our parameter
    canvas.invalidate(oldBounds);
    canvas.invalidateElement(this);
  }
  
  private static IconRenderingManager getIconManager(Item item)
  {
    return ((TwAccess)((com.gensym.classes.ImplAccess)item).getContext()).getIconManager();
  }

  private WorkspaceIconImpl(IconDescription iconDescription,
			    Structure variableOverrides,
			    Structure untransformedRegionOverrides,
			    PersistentCanvas canvas,
			    int orientation,
			    int x, int y, int width, int height,
			    IconRenderingManager irm)throws G2AccessException {
    super(iconDescription,
	  variableOverrides,
	  transformColorValues(untransformedRegionOverrides,canvas),
	  orientation,
	  x, y, width, height, irm);
    this.logicalColorMap = untransformedRegionOverrides;
  }

  private static int getOrientation (Entity entity) throws G2AccessException {
    int heading = entity.getIconHeading();
    if (entity.getIconReflection()==null) {
      switch (heading)
	{
	case 0: return IconRendering.NORMAL;
	case 90: return IconRendering.CLOCKWISE_90;
	case 180: return IconRendering.CLOCKWISE_180;
	case 270: return IconRendering.CLOCKWISE_270;
	}
    } else {
      switch (heading)
	{
	case 0: return IconRendering.REFLECTED;
	case 90: return IconRendering.REFLECTED_CLOCKWISE_90;
	case 180: return IconRendering.REFLECTED_CLOCKWISE_180;
	case 270: return IconRendering.REFLECTED_CLOCKWISE_270;
	}
    }
    return IconRendering.NORMAL;
  }
  
  private void updateColorPattern(Structure colorPatternChange, boolean isOnThisItem) {
    if (isOnThisItem) {
      if (colorPatternChange != null) {
	Enumeration newColorNames = colorPatternChange.getAttributeNames();
	Symbol nextColor;
	Object nextColorValue;
	while (newColorNames.hasMoreElements()) {
	  nextColor = (Symbol) newColorNames.nextElement();
	  nextColorValue = colorPatternChange.getAttributeValue(nextColor, null);
	  logicalColorMap.setAttributeValue(nextColor,nextColorValue);
	}
      }
    }
    iconRendering.setRenderingOverrides(iconRendering.getVariableOverrides(),
					transformColorValues(logicalColorMap,canvas));
  }

  private static final Symbol IMAGE_DEFINITION_ = Symbol.intern ("IMAGE-DEFINITION");
  private ImageDefinition imageDefinition = null;
  //iconDescriptions has two possibilities as keys: image definitions and
  //G2Definition's for the icon itself.  The value is always a IconDescription.
  private static Hashtable iconDescriptions = new Hashtable (101);
  private static Hashtable listeners = new Hashtable (101);
  private static void notifyListeners(Entity def)
  {
    boolean haveListeners = false;
    Vector list = null;
    synchronized(listeners) {
      Vector defListeners = (Vector)listeners.get(def);
      if (defListeners != null) {
	haveListeners = true;
	list = (Vector)defListeners.clone();
      }
    }
    if (haveListeners) {
      Enumeration e = list.elements();
      while (e.hasMoreElements()) {
	WorkspaceIconImpl listener = (WorkspaceIconImpl)e.nextElement();
	try {
	  listener.handleIconDescriptionChange(def instanceof ImageDefinition);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }
    }
  }

  private static final Symbol ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");
  private static DefinitionListener theClassListener =
  new DefinitionListener() {
    private void resetIcon(DefinitionEvent e) {
      Definition definitionSource = (Definition)e.getSource();
      iconDescriptions.remove(definitionSource);
      notifyListeners(definitionSource);
    }
    
    @Override
    public void staticAttributeChanged (DefinitionEvent e) 
      {
	Symbol attributeName = e.getAttributeName();
	if (ICON_DESCRIPTION_.equals(attributeName)) {
	  resetIcon(e);
	}
      }
    @Override
    public void classNameChanged (DefinitionEvent e){}
    @Override
    public void directSuperiorClassesChanged (DefinitionEvent e){}
    @Override
    public void deleted (DefinitionEvent e){
      Definition definitionSource = (Definition)e.getSource();
      iconDescriptions.remove(definitionSource);
    }
    @Override
    public void classInheritancePathChanged (DefinitionEvent e){
      resetIcon(e);
    }
    @Override
    public void classSpecificAttributesChanged (DefinitionEvent e) {}
  };
  
  private static void addIconDescriptionListener(WorkspaceIconImpl listener,
						 Item item)
       throws G2AccessException
  {
    G2Definition def = item.getDefinition();
    if (def instanceof Definition) {
      Vector defListeners = (Vector)listeners.get(def);
      if (defListeners == null) {
	((Definition)def).addDefinitionListener(theClassListener);
	defListeners = new Vector();
	listeners.put(def, defListeners);
      }
      defListeners.addElement(listener);
    }
  }


  private static void addImageDescriptionListener(WorkspaceIconImpl listener,
						  ImageDefinition item)
       throws G2AccessException
  {
    Vector defListeners = (Vector)listeners.get(item);
    if (defListeners == null) {
      item.addItemListener (imageListener);
      defListeners = new Vector();
      listeners.put(item, defListeners);
    }
    defListeners.addElement(listener);
  }


  private static void removeIconDescriptionListener(WorkspaceIconImpl listener,
						    Item item)
       throws G2AccessException
  {
    G2Definition def = item.getDefinition();
    if (def instanceof Definition) {
      Vector defListeners = (Vector)listeners.get(def);
      if (defListeners != null) 
	defListeners.removeElement(listener);
      if (defListeners.isEmpty()) {
	((Definition)def).removeDefinitionListener(theClassListener);
	listeners.remove(def);
	iconDescriptions.remove(def);
      }
    }
  }

  private static void removeImageDescriptionListener(WorkspaceIconImpl listener,
						    ImageDefinition item)
       throws G2AccessException
  {
    Vector defListeners = (Vector)listeners.get(item);
    if (defListeners != null) 
      defListeners.removeElement(listener);
    if (defListeners.isEmpty()) {
      ((Definition)item).removeItemListener(imageListener);
      listeners.remove(item);
      iconDescriptions.remove(item);
    }
  }
  
  private static IconDescription getIconDescription (Entity entity)
       throws G2AccessException
  {
    G2Definition def = ((com.gensym.classes.Item)entity).getDefinition();
    IconDescription iconDescription = (IconDescription)iconDescriptions.get(def);
    if (iconDescription == null) {
      Structure id = entity.getIconDescriptionForClass();
      if (id != null) {
	iconDescription = new IconDescription(id);
	Symbol imageName = iconDescription.getBackgroundImageName();
	if (imageName != null) {
	  com.gensym.jgi.G2Access context =
	    ((com.gensym.classes.ItemImpl)entity).getContext();
	  ImageDefinition imageDef =
	    (ImageDefinition)context.getUniqueNamedItem (IMAGE_DEFINITION_, imageName);
	  if (imageDef.getWidthOfImage () != null) {
	    Image image = imageDef.getImage();
	    iconDescription.setBackgroundImage(image,
					       imageDef.getWidthOfImage().intValue(),
					       imageDef.getHeightOfImage().intValue());
	  }
	  //yduJ: it's a little flaky that I'm overloading the existing hash table.
	  //perhaps I should have made a separate one for image definitions.
	  iconDescriptions.put(imageDef, iconDescription);
	}
	iconDescriptions.put(def, iconDescription);
      }
    }
    return iconDescription;
  }

  private static ImageDefinition getImageDefinition(Entity entity, IconDescription icon) {
    if (icon == null)
	return null;
    Symbol imageName = icon.getBackgroundImageName();
    if (imageName != null) {
      try {
	com.gensym.jgi.G2Access context =
	  ((com.gensym.classes.ItemImpl)entity).getContext();
	ImageDefinition imageDef =
	  (ImageDefinition)context.getUniqueNamedItem (IMAGE_DEFINITION_, imageName);
	return imageDef;
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	return null;
      }
    } else return null;
  }

  private static ItemListener imageListener =
    new ItemListener() {//implements com.gensym.util.ItemListener
    @Override
    public void receivedInitialValues(com.gensym.util.ItemEvent e){}
    @Override
    public void itemModified (com.gensym.util.ItemEvent e){
      Sequence denotation = e.getDenotation();
      if (AttributeDenotation.isAttributeDenotation(denotation)){
	Symbol attributeName_ = AttributeDenotation.getAttributeName(denotation);
	if (attributeName_.equals(com.gensym.util.symbol.SystemAttributeSymbols.FILE_NAME_OF_IMAGE_)){
	  try{
	    ImageDefinition imageDef = (ImageDefinition)(e.getItem ());
	    
	    if (imageDef.getWidthOfImage () != null) {
	      Image image = imageDef.getImage();
	      IconDescription iconDescription = (IconDescription)iconDescriptions.get(imageDef);
	      iconDescription.setBackgroundImage(image,
						 imageDef.getWidthOfImage().intValue(),
						 imageDef.getHeightOfImage().intValue());
	    notifyListeners(imageDef);
	    }
	  } catch (Exception ex) {Trace.exception (ex);}
	}  
      }
    }
    @Override
    public void itemDeleted(com.gensym.util.ItemEvent e) {}
      };



  private static Structure transformColorValues(Structure regionOverrides,
						PersistentCanvas canvas) {
    if (regionOverrides == null)
      return regionOverrides;
    else {
      regionOverrides = (Structure) regionOverrides.clone();
      Symbol regionName; Object color;
      for (Enumeration regionNames
	     = regionOverrides.getAttributeNames(); regionNames.hasMoreElements();) {
	regionName = (Symbol) regionNames.nextElement();
	color = regionOverrides.getAttributeValue(regionName, null);
	if (color instanceof Symbol)
	  regionOverrides.setAttributeValue(regionName,
					    canvas.getColorTable().lookup(color));
      }
    }
    return regionOverrides;
  }

  @Override
  public void shift (int deltaX, int deltaY)
  {
    helper.shift(deltaX,deltaY);
    super.shift(deltaX, deltaY);
  }

  @Override
  public boolean inside(int logical_x, int logical_y)
  {
    return contains(logical_x, logical_y);
  }

  @Override
  public boolean contains(int x, int y)
  {
    return helper.contains(x,y);
  }


  /**
   * Method for receiving updates to the orientation for this workspace element.
   */
  @Override
  public void handleWorkspaceItemRotated(WorkspaceEvent event) {
    Structure extraInfo = event.getInfo();
    Rectangle[] currentBounds = getExactBounds();
    int length = currentBounds.length;
    Rectangle[] oldBounds = new Rectangle[length];
    for (int i = 0; i < length; i++) 
      oldBounds[i] = new Rectangle(currentBounds[i]);
    Symbol newRotation = (Symbol) extraInfo.getAttributeValue(NEW_ROTATION_, null);
    this.orientation = rotationStateToOrientation (newRotation);
    updateIconRendering(true,false); //Do preserve overrides, don't update images
    canvas.invalidate(oldBounds);
    canvas.invalidateElement(this);
  }

  private int rotationStateToOrientation (Symbol rotnState) {
    if (rotnState.equals (NORMAL_))
      return IconRendering.NORMAL;
    else if (rotnState.equals (CLOCKWISE_90_))
      return IconRendering.CLOCKWISE_90;
    else if (rotnState.equals (CLOCKWISE_180_))
      return IconRendering.CLOCKWISE_180;
    else if (rotnState.equals (CLOCKWISE_270_))
      return IconRendering.CLOCKWISE_270;
    else if (rotnState.equals (REFLECTED_))
      return IconRendering.REFLECTED;
    else if (rotnState.equals (REFLECTED_CLOCKWISE_90_))
      return IconRendering.REFLECTED_CLOCKWISE_90;
    else if (rotnState.equals (REFLECTED_CLOCKWISE_180_))
      return IconRendering.REFLECTED_CLOCKWISE_180;
    else if (rotnState.equals (REFLECTED_CLOCKWISE_270_))
      return IconRendering.REFLECTED_CLOCKWISE_270;
    else
      return IconRendering.NORMAL;
  }

  /**
   * Method for receiving overrides to the variables of the IconRendering.
   * @param variableOverrides A Structure of variable-name: variable-value attributes.
   */
  @Override
  public void handleWorkspaceItemIconVariablesChanged(WorkspaceEvent event)
  {
    Structure variableOverrides = event.getInfo();
    iconRendering.setRenderingOverrides(variableOverrides,
					iconRendering.getRegionOverrides());
    canvas.invalidateElement(this);
  }

  /**
   * Method for receiving overrides to the colors of an icon's regions.
   * @param colorPatternChange A Structure of region-name: color-name attributes.
   */
  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    Structure colorPatternChanges
	= (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    updateColorPattern(colorPatternChanges, event.getItem().equals(getItem()));
    canvas.invalidateElement(this);
  }

  /*WORKSPACE ELEMENT API*/

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
    updateIconRendering(true,false); //Do preserve overrides, don't update images
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

  /*public void paint (Graphics g)
  {
    super.paint(g);
    if (isSelected()) {
      Color color = canvas.getBackgroundColor();
      g.setXORMode(color);
      g.setColor(Color.blue);
      Rectangle[] bounds=getExactBounds();
      g.fillRect(0,0, bounds[0].width, bounds[0].height);
    }
  }*/
  
  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    if (true)//outlineDrag
      return helper.getDraggingGhost(left,top,width,height);
    else {
      DraggingGhost ghost = new DraggingGhost ();
      ghost.elements = new Component[1];
      ghost.boundsArray[0] = new Rectangle (left, top, width+2, height+2);
      IconElement iconElement
	= new IconElement(iconDescription,
			  iconRendering.getVariableOverrides(),
			  iconRendering.getRegionOverrides(),
			  orientation,
			  left,top,width,height,
			  getIconManager(getItem()));
      iconElement.setPaintMode(false);
      ghost.elements[0] = iconElement;
      return ghost;
    }
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    Rectangle bounds = getExactBounds()[0];
    return getDraggingGhost(bounds.x, bounds.y, bounds.width, bounds.height);
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    Rectangle eltBounds = (getExactBounds())[0];
    int left = eltBounds.x, top = eltBounds.y,
      width = currentX - left, height = currentY - top;
    left -=1; top -=1; width +=1; height +=1;
    return getDraggingGhost (left, top, width, height);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  @Override
  public String toString()
  {
    String theString = "default";
    try {
      theString = super.toString() + "#<" + helper.getG2ClassName().toString() +
      " @" + Integer.toHexString(super.hashCode()) + ">" + isVisible();
    } catch (G2AccessException e) {}

    return theString;
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
  }

  @Override
  public void paint (Graphics g) {
    super.paint (g);
    helper.paintDecorations(g);
  }

  @Override
  public void dispose() throws G2AccessException{
    try {
      removeIconDescriptionListener(this, getItem());
      if (imageDefinition != null) {
	removeImageDescriptionListener(this, imageDefinition);
	imageDefinition = null;
      }
    } catch (Exception g2ae) {
      Trace.exception(g2ae);
    }
  }

}
