/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Frame;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import javax.swing.JToggleButton;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.palette.PaletteButton;
import com.gensym.ui.palette.Palette;
import com.gensym.ui.palette.PaletteDropTarget;
import com.gensym.ui.palette.PaletteListener;
import com.gensym.ui.palette.PaletteEvent;

class PaletteCommands extends AbstractCommand implements 
PaletteDropTarget, PaletteListener{

  private static final String PALETTES = "ViewPalettes";

  private ComponentEditor application;
  private TabbedPalette tabbedPalette;
  private Vector paletteList;
  private boolean firstShow = true;
  private Palette currentPalette;

  PaletteCommands(ComponentEditor application){
    super(new CommandInformation[]{
      new CommandInformation(PALETTES, true, "CommandShortResource", 
			     "CommandLongResource", null,
			     null, Boolean.FALSE, true)});
    this.application = application;
    paletteList = new Vector();
    Palette.setDefaultImage(Toolkit.getDefaultToolkit().getImage(getClass().getResource("bean.gif")));
    Palette.addPaletteListener((PaletteListener)this);
    setAvailable(PALETTES, false);
  }

  @Override
  public void actionPerformed(ActionEvent event){
    if (tabbedPalette.isVisible())
      hidePalettes();
    else
      showPalettes();
  }

  private void showPalettes(){
    if (firstShow){
      firstShow = false;
      java.awt.Rectangle bounds = application.getCurrentFrame().getBounds();
      java.awt.Dimension size = tabbedPalette.getPreferredSize();
      int x = bounds.x + bounds.width - size.width - 30;
      int y = bounds.y + 30;
      java.awt.Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
      if (x > screenSize.width) x = screenSize.width - size.width;
      if (y > screenSize.height) y = screenSize.height - size.height;
      tabbedPalette.setLocation(x, y);
      tabbedPalette.setVisible(true);
      tabbedPalette.setSize(tabbedPalette.getPreferredSize());
    }
    setState(PALETTES, Boolean.TRUE);
    tabbedPalette.setVisible(true);
  }

  private void hidePalettes(){
    setState(PALETTES, Boolean.FALSE);
    tabbedPalette.setVisible(false);
    dropCancelled();
  }

  void addPalette(G2JarInfo g2JarInfo){
    if (g2JarInfo.getCount() < 1) return;
    setAvailable(PALETTES, true);
    if (tabbedPalette == null){
      tabbedPalette = new TabbedPalette(application.getCurrentFrame(), "Palette");
      WindowAdapter windowAdapter = new WindowAdapter(){
	@Override
	public void windowClosing(WindowEvent event){
	  hidePalettes();
	}
      };
      tabbedPalette.addWindowListener(windowAdapter);
    }
    String jarName = g2JarInfo.getShortJarName(); 
    int index = jarName.lastIndexOf('.');
    jarName = jarName.substring(0, index);
    int counter = 2;
    String name = jarName;
    while (paletteList.contains(name)){
      name = jarName+"<"+counter+">";
      counter++;
    }
    paletteList.addElement(name);
    tabbedPalette.addPalette(g2JarInfo, name);
    tabbedPalette.getTabbedPane().setSelectedIndex(paletteList.size() - 1);
    showPalettes();
  }

  @Override
  public void paletteCreated(PaletteEvent event){
    Object source = event.getSource();
    if (source instanceof BeanPalette){
      Palette palette = (Palette)source;
      palette.addPaletteDropTarget(this);
    }
  }

  @Override
  public void paletteButtonStateChanged(PaletteEvent event){
    PaletteButton button = event.getButton();
    String currentSelection = null;
    if (button.isSelected()){
      currentSelection = event.getKey();
      currentPalette = (Palette)event.getSource();
    }
    application.setBeanSelection(currentSelection, button);
  }

  void dropOccurred(){
    if (currentPalette != null)
      currentPalette.dropOccurred();
  }

  void dropCancelled(){
    if (currentPalette != null)
      currentPalette.dropCancelled();
  }
  
}
