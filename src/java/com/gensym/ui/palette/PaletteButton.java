/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteButton.java
 *
 */

package com.gensym.ui.palette;

import java.awt.Container;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.MouseListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JToggleButton;
import javax.swing.ImageIcon;
import javax.swing.Icon;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.ObjectCreator2;
import com.gensym.ui.ObjectFactory;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.message.Resource;
import com.gensym.ui.LookAndFeel;
import java.awt.Font;


/**
 *  A PaletteButton represents a single object that can be created from a Palette.
 *  The PaletteButton's ObjectFactory creates the object.
 *  <p>
 *  A double-click on a PaletteButton sets the button in "sticky" mode. 
 * </p>
 */
public class PaletteButton extends JToggleButton {

  protected static int DOUBLE_CLICK_INTERVAL = 250;

  private static Resource i18n = Resource.getBundle("com/gensym/ui/palette/Errors");
  private static String defaultImageName = "default.gif";
  private static String defaultImageName32x32 = "default32x32.gif";
  private static Image defaultImage;
  private static Image defaultImage32x32;
  private static Image userImage;
  private static ImageIcon defaultImageIcon;
  private static ImageIcon defaultImageIcon32x32;
  private static Class thisClass = com.gensym.ui.palette.PaletteButton.class;

  private String key;
  private boolean stickyMode;
  private ObjectFactory objectFactory;
  private ObjectCreatorAdapter adapter;
  private MouseListener mouseAdapter = new DoubleClickAdapter();
  private transient long prevWhen;

  /** Creates a PaletteButton. */
  public PaletteButton(){
    init();
  }

  PaletteButton(ObjectCreator objectCreator, String key, ObjectCreatorAdapter adapter, int iconSize, RepresentationConstraints constraints) {
    int type = constraints.getRepresentationType();

    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON))
      setText(objectCreator.getDescription(key, ObjectCreator.SHORT_DESCRIPTION));
    if ((type == constraints.ICON_ONLY) || (type == constraints.TEXT_AND_ICON)) {
      Icon icon = null;
      Image iconImage;
      if (objectCreator instanceof ObjectCreator2)
	icon = ((ObjectCreator2)objectCreator).getIcon2(key, iconSize);
      else if ((iconImage = objectCreator.getIcon(key, iconSize)) != null)
	icon = new ImageIcon(iconImage);
      else
	icon = getDefaultImage(iconSize);
      if (LookAndFeel.getUseSnappyLookAndFeel())      
	setRolloverEnabled(true);      
      setIcon(icon);
    }

    setFont(new Font("sansserif", Font.PLAIN, 9));
    setHorizontalAlignment(constraints.getHorizontalAlignment());
    setVerticalAlignment(constraints.getVerticalAlignment());
    setHorizontalTextPosition(constraints.getHorizontalTextPosition());
    setVerticalTextPosition(constraints.getVerticalTextPosition());
    setMargin(new Insets(0, 0, 0, 0));
    this.key = key;
    this.objectFactory = objectCreator;
    this.adapter = adapter;
    adapter.add(this);

    setToolTipText(objectCreator.getDescription(key, ObjectCreator.LONG_DESCRIPTION));
    if (!objectCreator.isAvailable(key)) this.setEnabled(false);
    init();
  }

  private void init(){
    this.addMouseListener(mouseAdapter);
  }

  /** Sets the objectFactory of the PaletteButton.  The objectFactory
   *  creates the object that the PaletteButton represents.
   */
  public void setObjectFactory(ObjectFactory factory){
    objectFactory = factory;
  }

  /** Returns the objectFactory for this PaletteButton. */
  public ObjectFactory getObjectFactory(){
    return objectFactory;
  }

  /** 
   * Convenience method for creating the object represented by this PaletteButton.
   * @see com.gensym.ui.ObjectFactory
   */
  public Object createObject(){
    if (objectFactory == null)
      throw new IllegalStateException(i18n.getString("objectCreatorFactoryNull")); 
    return objectFactory.createObject(key);
  }
  
  static ImageIcon getDefaultImage(int iconSize){
    if (iconSize == ObjectCreator.SMALL_ICON){
      if (defaultImageIcon == null){
	if (userImage == null){
	  if (defaultImage == null)
	    defaultImage = Toolkit.getDefaultToolkit().getImage(thisClass.getResource(defaultImageName));
	  defaultImageIcon = new ImageIcon(defaultImage);
	}
	else defaultImageIcon = new ImageIcon(userImage);
      }
      return defaultImageIcon;
    }
    else {
      if (defaultImageIcon32x32 == null){
	if (userImage == null){
	  if (defaultImage32x32 == null)
	    defaultImage32x32 = Toolkit.getDefaultToolkit().getImage(thisClass.getResource(defaultImageName32x32));
	  defaultImageIcon32x32 = new ImageIcon(defaultImage32x32);
	}
	else defaultImageIcon32x32 = new ImageIcon(userImage);
      }
      return defaultImageIcon32x32;
    }
  }

  /* Returns the key associated with the PaletteButton. */
  public String getKey(){
   return key;
  }

  void setStickyMode(boolean mode){
    stickyMode = mode;
  }

  boolean isStickyMode(){
    return stickyMode;
  }

  /** If the parent of the PaletteButton is a Palette, then the parent Palette
   *  is returned; otherwise null is returned. */
  Palette getPalette(){
    Container parent = getParent();
    if (parent instanceof Palette)
      return (Palette)parent;
    else 
      return null;
  }

  @Override
  public void setSelected(boolean state){
    if ((!state) && (stickyMode))
      setStickyMode(false);
    super.setSelected(state);
  }

  @Override
  protected void paintBorder(java.awt.Graphics g) {
    if (!LookAndFeel.getUseSnappyLookAndFeel() ||
	getModel().isRollover() ||
	getModel().isPressed() ||
	isSelected())
      super.paintBorder(g);
  }
  
  static void setDefaultImage(Image image){
    defaultImage = image;
    defaultImageIcon = null;
  }

  class DoubleClickAdapter extends MouseAdapter{
    @Override
    public void mouseClicked(MouseEvent event){
      if (isEnabled()){
	if (event.getWhen() - prevWhen > DOUBLE_CLICK_INTERVAL){
	  prevWhen = event.getWhen();
	  if (isStickyMode()) 
	    setStickyMode(false);
	}
	else{
	  if (!isSelected()) 
	    setSelected(true);
	  setStickyMode(true);
	}
      }
    }
  }

}

