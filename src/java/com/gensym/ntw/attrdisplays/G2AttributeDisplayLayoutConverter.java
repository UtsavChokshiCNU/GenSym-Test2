package com.gensym.ntw.attrdisplays;


import java.util.Vector;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.util.PrettySymbol;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayout;
import com.gensym.uitools.attrdisplays.layoutmodel.AttributeDisplayLayoutImpl;
import com.gensym.uitools.attrdisplays.layoutmodel.VectorsNotSameLengthException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

public class G2AttributeDisplayLayoutConverter {

  private static final Symbol ATTRIBUTE_ = Symbol.intern("ATTRIBUTE");
  private static final Symbol TEXT_COLOR_ = Symbol.intern("TEXT-COLOR");
  private static final Symbol POSITION_ = Symbol.intern("POSITION");
  private static final Symbol DISPLAY_WITH_NAME_ = Symbol.intern("DISPLAY-WITH-NAME");
  private static final Symbol ATTRIBUTE_LIST_ = Symbol.intern("ATTRIBUTE-LIST");
  static final String TEXT_COLOR = "TEXT-COLOR";
  static final String POSITION = "POSITION";
  static final Symbol FOREGROUND_ = Symbol.intern("FOREGROUND");
  static final Symbol AT_STANDARD_POSITION_ = Symbol.intern("AT-STANDARD-POSITION");
  private static Vector keys;
  private static Vector globalKeys;

  public G2AttributeDisplayLayoutConverter() {
    initialize();
  }

  public static void initialize() {
    keys = new Vector();
    keys.add(G2LayoutTableModel.ROW_KEY);
    keys.add(G2LayoutTableModel.ROW_LAYOUT);
    globalKeys = new Vector();
    globalKeys.addElement(TEXT_COLOR);
    globalKeys.addElement(POSITION);
  }

  public AttributeDisplayLayout[] convertFromApplication
  (Object initialLayouts){
    Sequence attributes;
    LayoutStructure globalLayout;
    AttributeDisplayLayout tempLayout;

    Structure loopStructure = new Structure();
    
    if (initialLayouts == null) return null;
    if (!(initialLayouts instanceof Sequence)) return null;
    Sequence initSequence = (Sequence)initialLayouts;
    AttributeDisplayLayout[] convertedLayouts = 
      new AttributeDisplayLayout[initSequence.size()];
    try {
      
      for (int i = 0; i<initSequence.size(); i++) {
	attributes = (Sequence)((Structure)initSequence.elementAt(i)).
	  getAttributeValue(ATTRIBUTE_LIST_, null);
	for (int j = 0; j<attributes.size(); j++){
	  Vector values = new Vector();
	  loopStructure = (Structure)attributes.elementAt(j);
	  Object attributeName = loopStructure.getAttributeValue(ATTRIBUTE_);
	  if (attributeName instanceof Symbol)
	    attributeName = new PrettySymbol((Symbol)attributeName);
	  values.add(attributeName);
	  values.add(loopStructure.getAttributeValue(DISPLAY_WITH_NAME_));
	  LayoutStructure temp = new LayoutStructure(attributeName,
						     keys,
						     (Vector)values.clone());
	  attributes.setElementAt(temp, j);
	}
	Vector globalValues = new Vector();
	loopStructure = (Structure)initSequence.elementAt(i);
	globalValues.add(loopStructure.getAttributeValue(TEXT_COLOR_));
	globalValues.add(loopStructure.getAttributeValue(POSITION_));
	globalLayout = new LayoutStructure(null, globalKeys, globalValues);
	tempLayout = new AttributeDisplayLayoutImpl(attributes, globalLayout);
	convertedLayouts[i] = tempLayout;
      }
    } catch (NoSuchAttributeException nsae) {
      //This should never happen as long as G2 keeps the sequence of structures
      //with the same attribute Symbols.
    } catch (VectorsNotSameLengthException vnsle) {
      //Since I know the vectors used to construct LayoutStructure will always
      //be of length two in this method, this should never happen.
    }
    return convertedLayouts;
  }
  
  public Sequence convertForApplication
  (AttributeDisplayLayout[] currentAttributeDisplays) {
    Sequence convertedLayouts = new Sequence();
    Object color;
    Object position;
    if (currentAttributeDisplays == null) 
      return null;
    for (int i = currentAttributeDisplays.length - 1; i > -1; i--) {
      Structure tempLayout = new Structure();
      Sequence attributes = new Sequence();
      AttributeDisplayLayout attributeDisplayLayout = 
	(AttributeDisplayLayout)currentAttributeDisplays[i];
      Object[] rows = attributeDisplayLayout.getRows();
      attributes = convertAttributes(rows);
      tempLayout.setAttributeValue(ATTRIBUTE_LIST_, attributes);
      LayoutStructure lstru = attributeDisplayLayout.getGlobalLayout();
      if (lstru != null) {
	color = lstru.getAttributeValue(TEXT_COLOR, null);
	tempLayout.setAttributeValue(TEXT_COLOR_, 
				     convertColor(color));
	tempLayout = finishConversion(tempLayout, attributeDisplayLayout.
				      getGlobalLayout().getAttributeValue
				      (POSITION, null));
      } else {
	tempLayout.setAttributeValue(TEXT_COLOR_, FOREGROUND_);
	tempLayout.setAttributeValue(POSITION_, AT_STANDARD_POSITION_);
      }
      if (attributes.size() > 0) 
	convertedLayouts.add(tempLayout);
      
    }
    if (convertedLayouts.size() == 0) return null;
    return convertedLayouts;
  }
  
  private Sequence convertAttributes(Object[] attributes) {
    Sequence convertedAttrs = new Sequence();
    LayoutStructure layout;
    Object attrVal;
    Object attr;

    for (int i = 0; i < attributes.length; i++) {
    Structure structure = new Structure();

      LayoutStructure thisAttr = null;
      layout = (LayoutStructure)attributes[i];
      attrVal = layout.getAttributeValue(G2LayoutTableModel.ROW_KEY, null);
      if (attrVal != null) {
	structure.setAttributeValue(ATTRIBUTE_, ((PrettySymbol)attrVal).getSymbol());
	attr = layout.getAttributeValue(G2LayoutTableModel.ROW_LAYOUT, null);
	if (attr != null)
	  structure.setAttributeValue(DISPLAY_WITH_NAME_, attr);
	else
	  structure.setAttributeValue(DISPLAY_WITH_NAME_, 
				     new Boolean(false));
	convertedAttrs.add(structure);
      } 
    }
    return convertedAttrs;
  }
  
  private Symbol convertColor(Object rawColor) {
    Symbol convertedColor = FOREGROUND_;
    if (rawColor == null)
      convertedColor = FOREGROUND_;
    else
      convertedColor = Symbol.intern(rawColor.toString().toUpperCase().
				     replace(' ', '-'));
    return convertedColor;
  }
  
  private Structure finishConversion(Structure layout, Object position) {
    if (position == null)
      layout.setAttributeValue(POSITION_, 
			       AT_STANDARD_POSITION_);
    else
      layout.setAttributeValue(POSITION_, position);
    return layout;
  }
}
