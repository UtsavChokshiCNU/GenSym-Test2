package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.TextField;
import java.awt.Dimension;
import java.io.Serializable;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilGrmes;

abstract class UilClientGrmesImpl extends UilClientItemImpl implements UilClientGrmes, Serializable{

  static final long serialVersionUID = 3607286566638283114L;

  private Object uilMaximumCharactersToDisplay;
  private int uilBoxWidth;

  public UilClientGrmesImpl(UilGrmes grmes, Component component, Class staticClass) 
       throws G2AccessException{
    super(grmes, component, staticClass);
    uilMaximumCharactersToDisplay = grmes.getUilMaximumCharactersToDisplay();
    uilBoxWidth = ((Integer)grmes.getUilBoxWidth()).intValue();
  }

  protected UilClientGrmesImpl(){
  }

  //properties
  @Override
  public Object getUilMaximumCharactersToDisplay(){
    return uilMaximumCharactersToDisplay;
  }

  @Override
  public int getUilBoxWidth(){
    return uilBoxWidth;
  }

  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
				      Object actionQueue) throws G2AccessException{
    Item sourceObject = getSourceObject();
    if (sourceObject == null) return;
    Object value = null;
    Symbol sourceAttributeName = getUilEventSourceAttribute();
    try{
      if (sourceAttributeName != null && !sourceAttributeName.equals( UilClientConstants.UNSPECIFIED_))
	value = sourceObject.getPropertyValue(sourceAttributeName);
      else
	value = sourceObject;
    }
    catch(NoSuchAttributeException ex){
      value = sourceObject;
    }
    finally{
      Object extractedValue = uppExtractValue(value);
      if (extractedValue != null)
	uilUpdateText(extractedValue);
    }
  }

  protected void clipText(String txt){
    if (uilMaximumCharactersToDisplay instanceof Integer){
      int max = ((Integer)uilMaximumCharactersToDisplay).intValue();
      if (max < txt.length())
	txt = txt.substring(0, max)+"...";
    }
    Component text = getComponent();
    if (text instanceof UILText)
      ((UILText)text).setText(txt);
    else if (text instanceof TextField)
      ((TextField)text).setText(txt);
    Dimension size = text.getSize();
    Dimension preferredSize = text.getPreferredSize();
    if (preferredSize.width > size.width)
      text.setSize(new Dimension(preferredSize.width, size.height));
    if (preferredSize.height > size.height)
      text.setSize(new Dimension(size.width, preferredSize.height));
  }

  @Override
  public abstract void uilUpdateText(Object value);
}
