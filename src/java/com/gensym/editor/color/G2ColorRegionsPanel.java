/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorRegionsPanel.java
 *
 */
package com.gensym.editor.color;

import java.awt.Color;
import java.awt.GridBagConstraints;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Panel;
import java.awt.List;
import java.util.Enumeration;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;

/**
 * G2ColorRegionsPanel
 */
class G2ColorRegionsPanel extends StandardGridBagPanel
implements ItemListener
{
  private static Resource i18n = 
		Resource.getBundle("com.gensym.editor.color.ColorEditorResources");
  
  private Label regionsLabel = null;
  private List regionsList = null;
  private G2ColorsPanel colorsPanel = null;
  private Structure regionsStructure = null;
  
  G2ColorRegionsPanel()
  {
    initialize();
  }

  private void initialize() {
    regionsStructure = new Structure();
    createRegionsPanel();
    regionsList.addItemListener(this);
  }

  private void createRegionsPanel()
  {
    GridBagConstraints gridC = new GridBagConstraints ();
    setLayout (gridBagLayout);
    setBackground(Color.lightGray);

    gridC.gridheight = GridBagConstraints.RELATIVE;
    gridC.gridwidth = GridBagConstraints.RELATIVE;
    gridC.gridx = 0;
    gridC.gridy = 0;
    gridC.insets = new Insets(5, 5, 0, 0);
    addComponent(regionsLabel = new Label(i18n.getString("Regions")), gridC);
    
    gridC.gridheight = GridBagConstraints.REMAINDER;
    gridC.gridwidth = GridBagConstraints.RELATIVE;
    gridC.gridy = GridBagConstraints.RELATIVE;
    gridC.weighty = 1.0;
    gridC.weightx = 1.0;
    gridC.fill = GridBagConstraints.BOTH;
    gridC.insets = new Insets(10, 5, 0, 0);
    regionsList = new List();
    addComponent(regionsList, gridC);

    gridC.gridwidth = GridBagConstraints.REMAINDER;
    gridC.gridheight = GridBagConstraints.REMAINDER;
    gridC.gridy=GridBagConstraints.NONE;
    gridC.gridx=GridBagConstraints.RELATIVE;
    gridC.anchor = GridBagConstraints.EAST;
    gridC.insets = new Insets(0, 0, 5, 5);
    addComponent(colorsPanel =
		 new G2ColorsPanel(7, G2ColorsCanvas.INCLUDE_TRANSPARENT +
				   G2ColorsCanvas.INCLUDE_FOREGROUND),
		 gridC);
  }

  String getSelectedColorString()
  {
    return colorsPanel.getSelectedColorString();
  }

  void clearRegions()
  {
    regionsList.clear();
    regionsStructure = new Structure();
  }
  
  void setRegions(Structure regions)
  {
    clearRegions();
    addRegions(regions);
  }
  
  void addRegions(Structure regions)
  {
    Enumeration e = regions.getAttributeNames();
    while(e.hasMoreElements()) {
      Symbol regionName = (Symbol)e.nextElement();
      Symbol currentColorName = (Symbol)regions.getAttributeValue(regionName, null);
      addRegion(regionName, currentColorName);
    }
  }

  Structure getRegions()
  {
    return regionsStructure;
  }
  
  void addRegion(Symbol regionName,
			Symbol currentColorName)
  {
    regionsList.add(regionName.getPrintValue());
    regionsStructure.setAttributeValue(regionName, currentColorName);
  }

  Symbol getColorNameForRegion(Symbol regionName)
  {
    return (Symbol)regionsStructure.getAttributeValue(regionName, null);
  }

  void setSelectedColor(String colorString)
  {
    Symbol colorSymbol;
    if (colorString.equals("transparent"))
      colorSymbol = TRANSPARENT_;
    else
      colorSymbol = colorsPanel.getG2ColorsCanvas().g2Colors.getColorSymbolForColorString(colorString);
    setSelectedColor(colorSymbol, true);
  }

  private static final Symbol TRANSPARENT_ = Symbol.intern ("TRANSPARENT");
  private void setSelectedColor(Symbol colorSymbol, boolean updateData)
  {
    String colorString;
    if (colorSymbol.equals(TRANSPARENT_))
      colorString = "transparent";
    else 
      colorString = colorsPanel.getG2ColorsCanvas().g2Colors.getColorStringForColorSymbol(colorSymbol);
    colorsPanel.setSelectedColor(colorString);
    if (updateData) {
      String selectedRegion =regionsList.getSelectedItem();
      if (selectedRegion != null) {
	Symbol regionName = Symbol.intern(selectedRegion);
	regionsStructure.setAttributeValue(regionName, colorSymbol);
      }
    }
  }
  
  @Override
  public void itemStateChanged(ItemEvent ie)
  {
    Symbol regionName = Symbol.intern(regionsList.getSelectedItem());
    Symbol colorNameForRegion = getColorNameForRegion(regionName);
    setSelectedColor(colorNameForRegion, false);
  }

}
