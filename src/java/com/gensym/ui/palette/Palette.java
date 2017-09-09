/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Palette.java
 *
 */


package com.gensym.ui.palette;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.lang.reflect.Array;
import javax.swing.JComponent;
import javax.swing.ImageIcon;
import javax.swing.BoxLayout;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.lang.reflect.Array;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.StructuredObjectCreator;
import com.gensym.ui.ObjectCreatorListener;
import com.gensym.ui.ObjectCreatorEvent;
import com.gensym.ui.RepresentationConstraints;

/**
 *  A Palette is used to create objects and place them in a container.
 *  The buttons on the Palette may becreated by adding an ObjectCreator to the 
 *  Palette.
 *  Each key in the ObjectCreator generates a PaletteButton.  Palettes respond
 *  appropriately to changes in a ObjectCreator through the ObjectCreatorListener
 *  interface.
 *
 *  Each group in a StructuredObjectCreator is separated with a separator.
 *
 *  Clients can be notified of the creation of new Palettes by registering as
 *  a PaletteListener.  
 *  A client may then register as a PaletteDropTarget 
 *  for particular palettes to receive notification of toggle button 
 *  selection/unselection.
 *
 *  PaletteDropTargets need to notify the Palette of the completion or cancellation
 *  of a drop through dropOcurred() and dropCancelled().
 *
 *  @see com.gensym.uu.palette.PaletteButton
 *  @see com.gensym.ui.ObjectCreator
 *  @see com.gensum.ui.palette.PaletteDropTarget
 *  @see com.gensym.ui.palette.PaletteListener
 */

public class Palette extends JComponent{

  public static final int HORIZONTAL = 0;
  public static final int VERTICAL = 1;

  private static final RepresentationConstraints defaultConstraints =
        new RepresentationConstraints(RepresentationConstraints.ICON_ONLY,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.CENTER);
  private final static Insets stdInsets = new Insets(5, 5, 5, 5);

  private static PaletteButton selectedButton;
  private static Vector allPalettes = new Vector();
  private static Vector paletteListeners = new Vector();
  private static boolean stickyMode;

  private int iconSize = ObjectCreator.LARGE_ICON;
  private Vector targets;
  private String name;
  private int orientation;

  private ItemListener itemListener;

  private int count = 1;

  /** Creates a Palette with a default name. */
  public Palette(){
    this(null);
  }

  /** Creates a Palette with the specified name. */
  public Palette(String name){
    if (name == null)
      this.name = "Palette"+count++;
    else
      this.name = name;
    init();
  }    

  private void init(){
    setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
    stickyMode = false;
    targets = new Vector();
    allPalettes.addElement(this);
    itemListener = new ItemAdapter();    
    notifyPaletteCreated(new PaletteEvent(this));
  }
  
  @Override
  public Insets getInsets (){
    return stdInsets;
  }

  /**
   * Returns the orientation of the Palette.  
   */
  public int getOrientation(){
    return orientation;
  }

  /**
   *  Sets the orientation of the Palette.  orientation is either HORIZONTAL or
   *  VERTICAL.
   */
  public void setOrientation(int orientation){
    if (orientation != this.orientation){
      this.orientation = orientation;
      if (orientation == HORIZONTAL)
	setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
      else
	setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
    }
  }

  protected void notifyPaletteCreated(PaletteEvent event){
    Vector l;
    synchronized(this) {l = (Vector)paletteListeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      ((PaletteListener)dispatchList.nextElement()).paletteCreated(event);
    }
  }

  /**
   *  Adds a fixed space between buttons.
   */
  public void addSeparator(){    
    add(new Separator());
  }

  /** Adds a PaletteListener */
  public static void addPaletteListener(PaletteListener listener){
    if (!paletteListeners.contains(listener))
      paletteListeners.addElement(listener);
  }

  /** Removes a PaletteListener */
  public static void removePaletteListener(PaletteListener listener){
    if (paletteListeners.contains(listener))
      paletteListeners.removeElement(listener);
  }

  /** Returns an array of all the palettes that currently exists.*/
  public static Palette[] getPalettes(){
    Palette[] palettes = new Palette[allPalettes.size()];
    allPalettes.copyInto(palettes);
    return palettes;
  }

  /** Turns on/off "sticky" mode for all palettes.   
   *  Setting the mode to true turns "sticky" mode on, i.e, a toggle button 
   *  remains pressed until explicitly toggled.  Setting the mode to false turns 
   *  off "sticky" mode, i.e., after an item has been dropped, the toggle button 
   *  is released. The default value is false.*/
  public static void setStickyMode(boolean mode){
      stickyMode = mode;
  }

  /** Returns true if "sticky" mode is on; otherwise returns false. */
  public static boolean isStickyMode(){
    return stickyMode;
  }

  /** Sets the name of the palette. */
  @Override
  public void setName(String name){
    this.name = name;
  }

  /** Returns the name of the palette. */
  @Override
  public String getName(){
    return name;
  }

  /** Sets the size of the icon to be used for the toggle buttons.  iconSize should be
   *  either ObjectCreator.SMALL_ICON or ObjectCreator.LARGE_ICON.  The default size
   *  is LARGE_ICON.
   **/
  public void setIconSize(int iconSize){
    this.iconSize = iconSize;
  }

  /** Returns the size of the icon used for the toggle buttons.  The vaule is 
   *  either ObjectCreator.SMALL_ICON or ObjectCreator.LARGE_ICON.  The default size
   *  is LARGE_ICON.
   **/
  public int getIconSize(){
    return iconSize;
  }

  /** 
   *  Creates and adds a toggle button for each key in objectCreator. 
   *  The icon of the ObjectCreator is used for the icon
   *  of the toggle button.  The size is determined by the iconSize property
   *  of this Palette.
   *
   *  @see com.gensym.ui.palette.Palette#getIconSize
   *  @see com.gensym.ui.ObjectCreator#getIcon
   */
  public void add(ObjectCreator objectCreator){
    ObjectCreatorAdapter adapter = 
      new ObjectCreatorAdapter(objectCreator, defaultConstraints, this, true);
    add(objectCreator, adapter, defaultConstraints);
  }

  /**
   * Creates and adds a toggle button for each key in objectCreator according to
   * the specified RepresentationConstraints.  If specified in the constraints,
   * the label and/or icon of the button is obtained from the objectCreator.
   *
   * @see com.gensym.ui.ObjectCreator#getIcon
   * @see com.gensym.ui.ObjectCreator#getDescription
   */
  public void add(ObjectCreator objectCreator, RepresentationConstraints constraints){
    ObjectCreatorAdapter adapter = 
      new ObjectCreatorAdapter(objectCreator, constraints, this, true);
    add(objectCreator, adapter, constraints);
  }

  void add(ObjectCreator objectCreator, ObjectCreatorAdapter adapter, RepresentationConstraints constraints){
    if (objectCreator instanceof StructuredObjectCreator){
      Object[] structuredKeys = ((StructuredObjectCreator)objectCreator).getStructuredKeys();
      createGroups(structuredKeys, objectCreator, adapter, false, constraints);
    }
    else{
      String[] keys = objectCreator.getKeys();
      for (int i=0; i<keys.length; i++){
	PaletteButton button = new PaletteButton(objectCreator, (String)keys[i], adapter, iconSize, constraints);
        add(button);
	//addSeparator();
      }
    }
  }

  private void createGroups(Object structure, ObjectCreator objectCreator, ObjectCreatorAdapter adapter, boolean addSeparator, RepresentationConstraints constraints){
    if (structure == null) return;
    if (addSeparator) addSeparator();
    for (int i=0; i<Array.getLength(structure); i++){
      Object element = Array.get(structure, i);
      if (element instanceof String)
	add(objectCreator, (String)element, adapter, constraints);
      else if (element.getClass().isArray()){
        if ((!addSeparator)&&(i == 0))
          createGroups(element, objectCreator, adapter, false, constraints);
        else createGroups(element, objectCreator, adapter, true, constraints);
      }
    }
  }

  /** 
   *  Creates and adds a toggle button for the specified key.
   *  The icon of the ObjectCreator is used for the icon
   *  of the toggle button.  The size is determined by the iconSize property
   *  of this Palette.
   *
   *  @see com.gensym.ui.Palette#getIconSize
   *  @see com.gensym.ui.ObjectCreator#getIcon
   */
  public void add(ObjectCreator objectCreator, String key){
    ObjectCreatorAdapter adapter = 
      new ObjectCreatorAdapter(objectCreator, defaultConstraints, this, false);
    add(objectCreator, key, adapter, defaultConstraints);
  }    

  /**
   *  Creates and adds a single toggle button for the specified key and applies the
   *  specified contraints.
   */
  public void add(ObjectCreator objectCreator, String key, RepresentationConstraints constraints){
    ObjectCreatorAdapter adapter = 
      new ObjectCreatorAdapter(objectCreator, constraints, this, false);
    add(objectCreator, key, adapter, constraints);
  }

  private void add(ObjectCreator objectCreator, String key, ObjectCreatorAdapter adapter, RepresentationConstraints constraints){
    PaletteButton button = new PaletteButton(objectCreator, (String)key, adapter, iconSize, constraints);
    add(button);
  }

  @Override
  public Component add(Component c){
    if (c instanceof PaletteButton)
      ((PaletteButton)c).addItemListener(itemListener);
    return super.add(c);
  }

  private void remove(PaletteButton button){
    if (button.equals(selectedButton)){
      selectedButton.setSelected(false);
      selectedButton = null;
    }
    button.removeItemListener(itemListener);
    super.remove(button);
  }

  /** Sets the default image used for toggle buttons when getIcon in ObjectCreator
   *  returns null. */
  public static void setDefaultImage(Image image){
    PaletteButton.setDefaultImage(image);
  }

  /** Adds a PaletteDropTarget */
  public void addPaletteDropTarget(PaletteDropTarget target){
    targets.addElement(target);
  }
  
  /** Removes a PaletteDropTarget */
  public void removePaletteDropTarget(PaletteDropTarget target){
    targets.removeElement(target);
  }

  /** Resets the palette after a drop has ocurred. */
  public void dropOccurred(){
    if (selectedButton == null) return;
    if (!stickyMode){
      if (!selectedButton.isStickyMode())
	selectedButton.setSelected(false);
    }
  }
  
  /** Cancels the pending drop. */
  public void dropCancelled(){
    if (selectedButton == null) return;
    selectedButton.setSelected(false);
  }

  private void notifyPaletteButtonStateChanged(PaletteEvent event){
    Vector l;
    synchronized(this) {l = (Vector)targets.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      ((PaletteDropTarget)dispatchList.nextElement()).paletteButtonStateChanged(event);
    }
  }

  class ItemAdapter implements ItemListener{
    @Override
    public void itemStateChanged(ItemEvent event){
      Object source = event.getSource();
      if (source instanceof PaletteButton){
	PaletteButton btn = (PaletteButton)source;
	if (event.getStateChange() == ItemEvent.SELECTED){
	  if ((selectedButton != null)){
	    if (!selectedButton.equals(btn)){
	      selectedButton.setSelected(false);
	      selectedButton = btn;
	    }
	  }
	  else{
	    selectedButton = btn;
	  }
	}
	else{
	  selectedButton = null;
	}
	PaletteEvent e = new PaletteEvent(btn.getPalette(), btn, btn.getKey());
	notifyPaletteButtonStateChanged(e);
      }
    }
  }

  final class Separator extends Component {
    
    @Override
    public Dimension getMinimumSize() {
      return new Dimension(5,5);
    }
    
    @Override
    public Dimension getMaximumSize() {
      return new Dimension(5,5);
    }
    
    @Override
    public Dimension getPreferredSize() {
      return new Dimension(5,5);
    }
  }

}
