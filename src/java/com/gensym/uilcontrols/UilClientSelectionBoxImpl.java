package com.gensym.uilcontrols;

import java.awt.Component;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilSelectionBox;

class UilClientSelectionBoxImpl extends UilClientGrobjImpl implements UilClientSelectionBox{

  static final long serialVersionUID = -90470503195906522L;

  private Symbol uilButtonOrientation;
  private Symbol uilState;
  private String label;
  private boolean uilUpdateValue;
  private int uilBorderXOffset;
  private int uilBorderYOffset;
  private int uilLabelXOffset;
  private int uilLabelYOffset;

  UilClientSelectionBoxImpl(UilSelectionBox uilSelectionBox, UILSelectionBox box,
			    Class staticClass) throws G2AccessException{
    super(uilSelectionBox, box, staticClass);
    uilButtonOrientation = uilSelectionBox.getUilButtonOrientation();
    uilState = (Symbol)uilSelectionBox.getState();
    label = (String)uilSelectionBox.getLabel();
    uilUpdateValue = ((Boolean)uilSelectionBox.getUilUpdateValue()).booleanValue();
    uilBorderXOffset = ((Integer)uilSelectionBox.getUilBorderXOffset()).intValue();
    uilBorderYOffset = ((Integer)uilSelectionBox.getUilBorderYOffset()).intValue();
    uilLabelXOffset = ((Integer)uilSelectionBox.getUilLabelXOffset()).intValue();
    uilLabelXOffset = ((Integer)uilSelectionBox.getUilLabelXOffset()).intValue();
  }

  //properties
  @Override
  public Symbol getUilButtonOrientation(){
    return uilButtonOrientation;
  }

  @Override
  public Symbol getUilState(){
    return uilState;
  }

  @Override
  public String getLabel(){
    return label;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  @Override
  public int getUilBorderXOffset(){
    return uilBorderXOffset;
  }

  @Override
  public int getUilBorderYOffset(){
    return uilBorderYOffset;
  }

  @Override
  public int getUilLabelXOffset(){
    return uilLabelXOffset;
  }

  @Override
  public int getUilLabelYOffset(){
    return uilLabelYOffset;
  }

  //API
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
			       //System.out.println("UilClientSelectionBoxImpl.uilUpdateGrobj");
    if (uilUpdateValue){
      UilClientStateButton[] buttons = ((UILSelectionBox)getComponent()).getMembers();
      for (int i=0; i<buttons.length; i++){
	//System.out.println("("+i+") "+buttons[i].getClass());
	buttons[i].uilUpdateGrobj(win, dlg, buttonOrInitObj, actionQueue);
      }
    }
  }

  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			       Object actionQueue) throws G2AccessException{
    UilClientStateButton[] buttons = ((UILSelectionBox)getComponent()).getMembers();
    for (int i=0; i<buttons.length; i++)
      buttons[i].uilConcludeGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  @Override
  public UilClientStateButton[] getMembers(){
    return ((UILSelectionBox)getComponent()).getMembers();
  }
}

