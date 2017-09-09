
package com.gensym.ntw.util;

import com.gensym.jgi.G2AccessException;
import com.gensym.draw.ColorTable;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;





/**
 * 
 * CrossSectionPattern
 *
 */
public class CrossSectionPattern extends Object {

  private Object[] regions;
  private int[] widths;
  private Object[] logicalColors;
  private Color[] colors;
  private Sequence crossSectionRegionsData;
  private static final Symbol CROSS_SECTION_STRIPES_
  = Symbol.intern ("CROSS-SECTION-STRIPES");
  private static final Symbol CROSS_SECTION_REGIONS_
  = Symbol.intern ("CROSS-SECTION-REGIONS");
  private static final Symbol REGION_NAME_
  = Symbol.intern ("REGION-NAME");
  private static final Symbol REGION_SIZE_
  = Symbol.intern ("REGION-SIZE");
  private static final Symbol REGION_COLOR_
  = Symbol.intern ("REGION-COLOR");


  public CrossSectionPattern(Structure data) {
    Sequence crossSectionStripes
      = (Sequence) data.getAttributeValue(CROSS_SECTION_STRIPES_, null);
    if (crossSectionStripes != null) {
      Object[] crossSectionStripesArray = crossSectionStripes.getContents();
      int length = crossSectionStripesArray.length;
      Symbol regionName;
      Integer regionSize;
      Structure crossSectionStripe;
      widths = new int[length];
      regions = new Object[length];
      for (int i=0; i<length; i++) {
	crossSectionStripe = (Structure) crossSectionStripesArray[i];
	regionName = (Symbol) crossSectionStripe.getAttributeValue
	  (REGION_NAME_, null);
	regionSize = (Integer) crossSectionStripe.getAttributeValue
	  (REGION_SIZE_, null);
	regions[i] = regionName;
	widths[i] = regionSize.intValue();
      }
    }
    crossSectionRegionsData
      = (Sequence) data.getAttributeValue(CROSS_SECTION_REGIONS_, null);
    if (crossSectionRegionsData == null) {
      /* This is the case where the colors are specified directly
       * without logical region-names. We hack up a cross-sections-data
       * where the logical region-name is the same as the color.
       */
      int numRegions = regions.length;
      crossSectionRegionsData = new Sequence (numRegions);
      for (int i=0; i<numRegions; i++) {
	Symbol regionName = (Symbol) regions[i];
	Structure str = new Structure ();
	str.setAttributeValue (REGION_NAME_,  regionName);
	str.setAttributeValue (REGION_COLOR_, regionName);
	crossSectionRegionsData.addElement (str);
      }
    }
    logicalColors = extractRegions (crossSectionRegionsData, REGION_NAME_);
    colors = extractColors (crossSectionRegionsData, REGION_COLOR_, null);
  }

  public Object[] getRegions() {
    return regions;
  }
  
  public int[] getWidths() {
    return widths;
  }
  
  public Object[] getLogicalColors() {
    return logicalColors;
  }

  public Color[] getColors() {
    return colors;
  }

  public Color[] getColors(Structure regionOverrides, ColorTable colorMap) {
    return extractColors(crossSectionRegionsData, REGION_COLOR_, colorMap);
  }

  private Object[] extractRegions(Sequence speclist, Symbol key) {
    if (speclist == null)
      return null;
    else {
      Object[] regions = new Object[speclist.size()];
      Structure currentspec;
      Object value;
      int i = 0;
      for (Enumeration specs = speclist.elements(); specs.hasMoreElements();) {
	currentspec = (Structure) specs.nextElement();
	value = currentspec.getAttributeValue(key, null);
	regions[i] = value;
	i++;
      }
      return regions;
    }
  }

  private Color[] extractColors(Sequence speclist, Symbol key,
				ColorTable colorTable)
  {
    if (speclist == null)
      return null;
    else {
      Color[] colors = new Color[speclist.size()];
      Structure currentspec;
      Object value;
      int i = 0;
      for (Enumeration specs = speclist.elements(); specs.hasMoreElements();) {
	currentspec = (Structure) specs.nextElement();
	value = currentspec.getAttributeValue(key, null);
	if (colorTable != null)
	  colors[i] = colorTable.lookup((Symbol)value);
	else
	  colors[i] = G2ColorMap.get((Symbol)value);
	i++;
      }
      return colors;
    }
  }

  public Structure getColorMap() {
    return flattenSpecList(crossSectionRegionsData, REGION_NAME_, REGION_COLOR_);
  }
  
  public static Structure flattenSpecList(Sequence speclist, Symbol namekey, Symbol valuekey) {
    if (speclist == null)
      return null;
    else {
      Structure newStruct = new Structure();
      Structure currentspec;
      Symbol name; Object value;
      for (Enumeration specs = speclist.elements(); specs.hasMoreElements();) {
	currentspec = (Structure) specs.nextElement();
	name = (Symbol) currentspec.getAttributeValue(namekey, null);
	value = currentspec.getAttributeValue(valuekey, null);
	if (name != null) newStruct.setAttributeValue(name, value);
      }
      return newStruct;
    }
  }

}
