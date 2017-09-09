/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CustomPalettePanel.java
 *
 * THIS IS A WORK IN PROGRESS
 */
package com.gensym.ntw.util.uitools;

import java.awt.Component;
import java.awt.FlowLayout;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;

import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.shell.dialogs.CustomizePalettePanelDialog;
import com.gensym.util.Symbol;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JViewport;
import javax.swing.ScrollPaneConstants;

public class CustomPalettePanel extends JPanel implements BrowserSymbols {

  private static Resource i18n = Resource.getBundle("com/gensym/ntw/util/uitools/Messages");

  private TwAccess cxn;
  private G2Palette palette;
  private JLabel dummyPalette;
  private Symbol[] paletteClasses ;
  private Symbol[] defaultPaletteClasses = {CLASS_DEFINITION_, PROCEDURE_};

  private PaletteScrollPane scrollPane;
  private JButton customizeButton;

  private DialogClient client = new DialogClient();
 
  public CustomPalettePanel(TwAccess connection) {
    if (defaultPaletteClasses != null) {
      paletteClasses = new Symbol[defaultPaletteClasses.length];
      for (int i=0; i<defaultPaletteClasses.length; i++)
	paletteClasses[i] = defaultPaletteClasses[i];
    }
    initializeCustomPalettePanel(cxn);
  }

  private void initializeCustomPalettePanel(TwAccess cxn) {
    setLayout(new FlowLayout(FlowLayout.LEFT));
    add(scrollPane = new PaletteScrollPane());
    add(customizeButton = new JButton(i18n.getString("CustomizePaletteLabel")));
    customizeButton.addActionListener(new ActionListener() {
    @Override
    public void actionPerformed(ActionEvent e) {
      System.out.println("Customize Palette");
      //new CustomizePaletteDialog(scrollPane.getObjectCreator(), client).setVisible(true);
      new CustomizePalettePanelDialog(scrollPane.getObjectCreator()).setVisible(true);
    }
    });
    setConnection(cxn);
  }

  public void setConnection(TwAccess cxn) {
    System.out.println("\nCustomPalettePanel.setConnection: "+cxn);
    if (this.cxn != null) {
      if (!(this.cxn.equals(cxn)))
	this.cxn = cxn;
    } else {
      this.cxn = cxn;
    }

    if (cxn != null)
      scrollPane.createPaletteForContext(cxn);
    else {
      // insert dummy icon for placeholder
      scrollPane.createPaletteForNullContext();
    }
  }

  public Symbol[] getPaletteClasses() {
    return paletteClasses;
  }

  public void setPaletteClasses(Symbol[] classes) {
    paletteClasses = new Symbol[classes.length];
    for (int i=0; i<classes.length; i++)
      paletteClasses[i] = classes[i];
  }

  public Symbol[] getDefaultPaletteClasses() {
    return defaultPaletteClasses;
  }

  class PaletteScrollPane extends JScrollPane implements ScrollPaneConstants {
    private G2ObjectCreator objectCreator;

    public PaletteScrollPane () {
      setHorizontalScrollBarPolicy(HORIZONTAL_SCROLLBAR_AS_NEEDED);
      setVerticalScrollBarPolicy(VERTICAL_SCROLLBAR_NEVER);
      if (cxn != null)
	createPaletteForContext(cxn);
    }

    protected void createPaletteForContext(TwAccess cxn) {
      System.out.println("createPaletteForContext");
      JViewport viewport = getViewport();

      if (dummyPalette != null) {
	Component viewComponent= viewport.getView();

	if (viewComponent.equals(dummyPalette)) {
	  System.out.println("removing dummyPalette from toolbar");
	  viewport.remove(dummyPalette);
	}
      }

      if (palette == null) {
	palette = new G2Palette(cxn); 
	try {
	  //System.out.println("create objectCreator for: "+paletteClasses);
	  palette.add(objectCreator = new G2ObjectCreator(cxn, paletteClasses));
	  //System.out.println("objectCreator: "+objectCreator);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	  System.out.println(gae);
	}  
      }

      System.out.println("adding palette to toolbar");
      setViewportView(palette);
      viewport.paint(viewport.getGraphics());
      customizeButton.setEnabled(true);
    }

    protected void createPaletteForNullContext() {
      System.out.println("createPaletteForNullContext");
      JViewport viewport = getViewport();

      if (palette != null) {
	Component viewComponent = viewport.getView();
	if (viewComponent.equals(palette)) {
	  System.out.println("removing palette from toolbar");
	  viewport.remove(palette);
	}
      }

      if (dummyPalette == null) {
	Image dummyImage = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource("classdef.gif"));
	ImageIcon dummyIcon = new ImageIcon(dummyImage);
	dummyPalette = new JLabel(dummyIcon);
      }

      System.out.println("adding dummyPalette to toolbar");
      setViewportView(dummyPalette);
      viewport.paint(viewport.getGraphics());

      customizeButton.setEnabled(false);
    }

    protected G2ObjectCreator getObjectCreator() {
      return objectCreator;
    }
  }

  class DialogClient implements StandardDialogClient, CommandConstants {
    @Override
    public void dialogDismissed(StandardDialog dlg, int code) {
      if (dlg.wasCancelled()) return;
      System.out.println("CustomPalettePanel.dialogDismissed: "+dlg);
    }
  }
}
