package com.gensym.ui.palette;


import java.awt.Image;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import javax.swing.ImageIcon;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.StructuredObjectCreator;
import com.gensym.ui.StructuredObjectCreatorListener;
import com.gensym.ui.ObjectCreatorEvent;
import com.gensym.ui.RepresentationConstraints;

class ObjectCreatorAdapter implements StructuredObjectCreatorListener{
  private ObjectCreator objectCreator;
  private RepresentationConstraints constraints;
  private Palette palette;
  private boolean entireCreatorAdded;
  private Hashtable buttons;
  private Vector buttonList;

  ObjectCreatorAdapter(ObjectCreator objectCreator, RepresentationConstraints constraints, Palette palette, boolean entireCreatorAdded){
    this.objectCreator = objectCreator;
    this.constraints = constraints;
    this.palette = palette;
    this.entireCreatorAdded = entireCreatorAdded;
    buttons = new Hashtable();
    buttonList = new Vector();
    if (objectCreator instanceof StructuredObjectCreator)
      ((StructuredObjectCreator)objectCreator).addStructuredObjectCreatorListener(this);
    else
      objectCreator.addObjectCreatorListener(this);
  }
  
  void add(PaletteButton button){
    buttons.put(button.getKey(), button);
    buttonList.addElement(button);
  }
  
  @Override
  public void availabilityChanged(ObjectCreatorEvent event){
    ObjectCreator objectCreator = (ObjectCreator)event.getSource();
    String key = event.getKey();
    PaletteButton btn = (PaletteButton)buttons.get(key);
    btn.setEnabled(objectCreator.isAvailable(key));
  }

  @Override
  public void descriptionChanged(ObjectCreatorEvent event){
    ObjectCreator objectCreator = (ObjectCreator)event.getSource();
    String key = event.getKey();
    PaletteButton btn = (PaletteButton)buttons.get(key);
    btn.setToolTipText(objectCreator.getDescription(key, ObjectCreator.LONG_DESCRIPTION));
    int type = constraints.getRepresentationType();
    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON)){
      btn.setText(objectCreator.getDescription(key, ObjectCreator.SHORT_DESCRIPTION));
    }  
  }

  @Override
  public void iconChanged(ObjectCreatorEvent event){
    ObjectCreator objectCreator = (ObjectCreator)event.getSource();
    String key = event.getKey();
    PaletteButton btn = (PaletteButton)buttons.get(key);
    int type = constraints.getRepresentationType();
    if ((type == constraints.ICON_ONLY) || (type == constraints.TEXT_AND_ICON)){
      Image icon = objectCreator.getIcon(key, palette.getIconSize());
      if (icon != null){
	ImageIcon img = new ImageIcon(icon);
	btn.setIcon(img);
      }
      else{
	btn.setIcon(PaletteButton.getDefaultImage(palette.getIconSize()));
      }
    }  
  }

  @Override
  public void structureChanged(ObjectCreatorEvent event){
    if (!entireCreatorAdded) return;
    ObjectCreator objectCreator = (ObjectCreator)event.getSource();
    //pop
    Vector poppedList = new Vector();
    int count = palette.getComponentCount();
    boolean foundFirstButton = false;
    boolean previousItemWasSeparator = false;
    for (int i=count-1; i>=0; i--){
      java.awt.Component c = palette.getComponent(i);
      palette.remove(i);
      if (c instanceof com.gensym.ui.palette.Palette.Separator){
	previousItemWasSeparator = true;
	if (!foundFirstButton) poppedList.addElement(c);
      }
      else{
	previousItemWasSeparator = false;
	boolean contained = buttonList.contains(c);
	if ((!contained)&&(!foundFirstButton)) poppedList.addElement(c);
	else if ((!foundFirstButton)&&(contained)){
	  foundFirstButton = true;
	  buttons.remove(c);
	  //remove itemlistener from button
	}
	else if ((foundFirstButton)&&(!contained)){
	  palette.add(c);
	  if (previousItemWasSeparator) palette.addSeparator();
	  break;
	}
	else{
	  buttons.remove(c);
	  //remove il from btn
	}
      }
    }	 
    //re-build
    palette.add(objectCreator, this, constraints);
    //push
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--){
      palette.add((java.awt.Component)poppedList.elementAt(i));
    }
    palette.validate();
  }
}


