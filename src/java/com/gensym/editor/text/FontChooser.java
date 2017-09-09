/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FontChooser.java
 *
 */
package com.gensym.editor.text;

import javax.swing.JPanel;
import javax.swing.JComboBox;
import javax.swing.text.JTextComponent;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GraphicsEnvironment;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.util.Vector;



public class FontChooser extends Object implements ItemListener {

  private boolean debug = true;

  /* The component, if any, whose font we are controlling.
   * Set by initialize. */
  private JTextComponent component;
  public void setTextComponent(JTextComponent c) { component = c; }
  public JTextComponent getTextComponent() { return component; }

  private String[] allFontNames;
  public String[] getAllFontNames() { return allFontNames; }

  private Font font;
  public void setFont(Font f) { font = f; }
  public Font getFont() { return font; }

  private String nameOfFont;
  public void setNameOfFont(String n) { nameOfFont = n; }
  public String getNameOfFont() { return nameOfFont; }

  private int size;
  public void setSize(int s) { size = s; }
  public int getSize() { return size; }

  private int style = Font.PLAIN;
  public void setStyle(int s) { style = s; }
  public int getStyle() { return style; }

  private String[] availableSizes = new String[] { "8", "10", "12", "14", "18", "24" };
  public void setAvailableSizes(String[] s) { availableSizes = s; }
  public String[] getAvailableSizes() { return availableSizes; }



  /** Initializes the set of available Fonts. */
  public FontChooser () {
    GraphicsEnvironment e = GraphicsEnvironment.getLocalGraphicsEnvironment();
    allFontNames = e.getAvailableFontFamilyNames();
  }

  /** Associates the FontChooser with a particular JTextComponent. */
  public void initialize (JTextComponent c) {
    component = c;
    font = component.getFont();
    size = font.getSize();
  }



  //---- The visible interface -----------

  JComboBox fontOptions;
  JComboBox sizeOptions;

  private JPanel ui;
  public JPanel getUI() {
    if ( ui != null )
      return ui;
    else {
      Vector fontList = new Vector();
      for ( int i=1; i < allFontNames.length; i++) {
	fontList.addElement(allFontNames[i]);
      }
      fontOptions = new JComboBox( fontList );
      sizeOptions = new JComboBox( availableSizes );
      fontOptions.setMaximumRowCount( 10 );
      sizeOptions.setMaximumRowCount( 5 );
      fontOptions.addItemListener( this );
      sizeOptions.addItemListener( this );

      ui = new JPanel();
      ui.setLayout( new FlowLayout() );
      ui.add(fontOptions);
      ui.add(sizeOptions);

      return ui;
    }
  }

  /* implementation of ItemListener */
  @Override
  public void itemStateChanged(ItemEvent e) {
    if ( e.getStateChange() != ItemEvent.SELECTED )
      return;

    Object list = e.getSource();
    if (list.equals(fontOptions)) {
      nameOfFont = (String)fontOptions.getSelectedItem();
    }
    else if ( list.equals(sizeOptions)) {
      Integer newSize = Integer.valueOf( (String)sizeOptions.getSelectedItem() );
      size = newSize.intValue();
    }
    else {
      if (debug) {
    	  System.out.println("Selection did not match.");
      }
    }

    font = new Font(nameOfFont, size, style);

    if (component != null) {
      component.requestFocus();
      component.setFont(font);
      component.repaint();
      component.revalidate();
    }    
  }




  //---- Standalone testing

  public static void main (String[] args) {
    FontChooser fc = new FontChooser();
    System.out.println("The available fonts are: ");
    for (int i=0; i < fc.allFontNames.length; i++) {
      System.out.println( fc.allFontNames[i] );
    }
    System.exit(0);
  }

}
