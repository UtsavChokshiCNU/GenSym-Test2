package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Container;
import java.awt.GridLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Insets;
import java.util.Enumeration;
import java.util.Vector;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.G2List;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.modules.uilroot.UilSelectionBox;
import com.gensym.classes.modules.uilroot.UilRadioBox;
import com.gensym.classes.modules.uilroot.UilSelectionButton;
import com.gensym.classes.modules.uillib.UilRadioButton;
import com.gensym.classes.modules.uillib.UilCheckButton;
import com.gensym.classes.modules.uillib.UilRadioButtonConfigurationClass;
import com.gensym.classes.modules.uillib.UilCheckButtonConfigurationClass;

public abstract class UILSelectionBox extends Container implements UilClientSelectionBox{

  static final long serialVersionUID = 6201916345839181736L;

  private static final Symbol UIL_GET_RELATED_ITEMS_ = Symbol.intern ("UIL-GET-RELATED-ITEMS");
  private static final Symbol GROUPED_BY_ = Symbol.intern ("GROUPED-BY");
  private static final Symbol UIL_RADIO_BUTTON_CONFIGURATION_CLASS_ = Symbol.intern("UIL-RADIO-BUTTON-CONFIGURATION-CLASS");
  private static final Symbol TRANSPARENT_ = Symbol.intern("TRANSPARENT");

  protected Vector members = new Vector();
  protected boolean border = true;
  protected Insets insets;
  protected transient Class staticClass;

  protected UilClientSelectionBox uilHelper;

  protected UILSelectionBox(UilSelectionBox uilSelectionBox, Class staticClass) throws G2AccessException{
    uilHelper = new UilClientSelectionBoxImpl(uilSelectionBox, this, staticClass);
    this.staticClass = staticClass;
    GridLayout gridLayout;
    if (getUilButtonOrientation().equals(HORIZONTAL_))
      gridLayout = new GridLayout(1, 0);
    else
      gridLayout = new GridLayout(0, 1);
    setLayout(gridLayout);

    G2Access connection = ((ImplAccess)uilSelectionBox).getContext();
    Object btns = connection.callRPC(UIL_GET_RELATED_ITEMS_, 
				     new java.lang.Object[] {GROUPED_BY_, uilSelectionBox});
    if (btns instanceof G2List){
      Enumeration buttons = ((G2List)btns).getG2ListSequence().elements();
      while (buttons.hasMoreElements()){
	UilSelectionButton uilSelectionButton = (UilSelectionButton)buttons.nextElement();
	UILSelectionButton selectionButton = createSelectionButton(uilSelectionButton);
	members.addElement(selectionButton);
	add(selectionButton);
      }
    }

    try{
      Object config = 
	connection.getUniqueNamedItem(UIL_RADIO_BUTTON_CONFIGURATION_CLASS_, getConfiguration());
      if (config instanceof UilRadioButtonConfigurationClass)
	border = !(TRANSPARENT_.equals(((UilRadioButtonConfigurationClass)config).getUilBoxBorderColor()));
      else if (config instanceof UilCheckButtonConfigurationClass)
	border = !(TRANSPARENT_.equals(((UilCheckButtonConfigurationClass)config).getUilBoxBorderColor()));
    }
    catch(G2AccessException ex){
      //if no config, then assume border=false;
      border = false;
    }

    int x = getUilBorderYOffset();
    int y = getUilBorderXOffset();
    insets = new Insets(y, x, y, x);
  }

  protected abstract UILSelectionButton createSelectionButton(UilSelectionButton button) throws G2AccessException;

  protected void setUilHelper(UilClientSelectionBox helper){
    uilHelper = helper;
  }

  @Override
  public Insets getInsets(){
    return insets;
  }

  public boolean getBorder(){
    return border;
  }

  @Override
  public void paint(Graphics g){
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;
    g.setColor(getBackground());
    g.fillRect(0, 0, width, height);
    super.paint(g);
    if (border){
      g.setColor(Color.gray);
      g.drawLine(0, 0, width - 2, 0);
      g.drawLine(width - 2, 0, width - 2, height - 2);
      g.drawLine(0, height - 2, width - 2, height - 2);
      g.drawLine(0, 0, 0, height -2);
      g.setColor(Color.white);
      g.drawLine(1, 1, width - 3, 1);
      g.drawLine(width - 1, 0, width - 1, height - 1);
      g.drawLine(0, height - 1, width - 1, height - 1);
      g.drawLine(1, 1, 1, height - 3);
    }
  }

  @Override
  public UilClientStateButton[] getMembers(){
    UilClientStateButton[] buttons = new UilClientStateButton[members.size()];
    members.copyInto(buttons);
    return buttons;
  }

  //UilClientSelectionBox interface
  //properties
  @Override
  public String getId(){
    return uilHelper.getId();
  }
  @Override
  public Object getUserData(){
    return uilHelper.getUserData();
  }
  @Override
  public void setUserData(Object data){
    uilHelper.setUserData(data);
  }
  @Override
  public Object getUilEventSourceObject(){
    return uilHelper.getUilEventSourceObject();
  }
  @Override
  public Symbol getUilEventSourceAttribute(){
    return uilHelper.getUilEventSourceAttribute();
  }
  @Override
  public Object getUilEventTargetObject(){
    return uilHelper.getUilEventTargetObject();
  }
  @Override
  public Symbol getUilEventTargetAttribute(){
    return uilHelper.getUilEventTargetAttribute();
  }
  @Override
  public Symbol getConfiguration(){
    return uilHelper.getConfiguration();
  }
  @Override
  public Symbol getUilSize(){
    return uilHelper.getUilSize();
  }
  @Override
  public boolean getUilConcludeValueImmediately(){
    return uilHelper.getUilConcludeValueImmediately();
  }
  @Override
  public Symbol getUilInitializationMethod(){
    return uilHelper.getUilInitializationMethod();
  }
  @Override
  public Symbol getUilEnableMethod(){
    return uilHelper.getUilEnableMethod();
  }
  @Override
  public Symbol getUilDisableMethod(){
    return uilHelper.getUilDisableMethod();
  }
  @Override
  public Symbol getUilSizeOfMethod(){
    return uilHelper.getUilSizeOfMethod();
  }
  @Override
  public Symbol getUilConfigurationMethod(){
    return uilHelper.getUilConfigurationMethod();
  }
  @Override
  public Symbol getUilCloneMethod(){
    return uilHelper.getUilCloneMethod();
  }
  @Override
  public Symbol getUilManageMethod(){
    return uilHelper.getUilManageMethod();
  }
  @Override
  public Symbol getUilUpdateMethod(){
    return uilHelper.getUilUpdateMethod();
  }
  @Override
  public Symbol getUilDeleteMethod(){
    return uilHelper.getUilDeleteMethod();
  }
  @Override
  public UilCallback getUpdateCallback(){
    return uilHelper.getUpdateCallback();
  }
  @Override
  public void setUpdateCallback(UilCallback callback){
    uilHelper.setUpdateCallback(callback);
  }
  @Override
  public UilCallback getEnableCallback(){
    return uilHelper.getEnableCallback();
  }
  @Override
  public void setEnableCallback(UilCallback callback){
    uilHelper.setEnableCallback(callback);
  }
  @Override
  public UilCallback getDisableCallback(){
    return uilHelper.getDisableCallback();
  }
  @Override
  public void setDisableCallback(UilCallback callback){
    uilHelper.setDisableCallback(callback);
  }
  @Override
  public Symbol getUilValidationMethod(){
    return uilHelper.getUilValidationMethod();
  }
  @Override
  public UilCallback getValidationCallback(){
    return uilHelper.getValidationCallback();
  }
  @Override
  public void setValidationCallback(UilCallback callback){
    uilHelper.setValidationCallback(callback);
  }
  @Override
  public Symbol getUilConcludeMethod(){
    return uilHelper.getUilConcludeMethod();
  }
  @Override
  public UilCallback getConcludeCallback(){
    return uilHelper.getConcludeCallback();
  }
  @Override
  public void setConcludeCallback(UilCallback callback){
    uilHelper.setConcludeCallback(callback);
  }
  @Override
  public Symbol getUilButtonOrientation(){
    return uilHelper.getUilButtonOrientation();
  }
  @Override
  public Symbol getUilState(){
    return uilHelper.getUilState();
  }
  @Override
  public String getLabel(){
    return uilHelper.getLabel();
  }
  @Override
  public boolean getUilUpdateValue(){
    return uilHelper.getUilUpdateValue();
  }
  @Override
  public int getUilBorderXOffset(){
    return uilHelper.getUilBorderXOffset();
  }
  @Override
  public int getUilBorderYOffset(){
    return uilHelper.getUilBorderYOffset();
  }
  @Override
  public int getUilLabelXOffset(){
    return uilHelper.getUilLabelXOffset();
  }
  @Override
  public int getUilLabelYOffset(){
    return uilHelper.getUilLabelYOffset();
  } 
  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallUpdateMethodForGrobj(win);
  }
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilUpdateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			     Object actionQueue) throws G2AccessException{
    uilHelper.uilUpdateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilDisableGrobjMethod();
  }
  @Override
  public void uilDisableGrobj(){
    uilHelper.uilDisableGrobj();
  }
  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEnableGrobjMethod();
  }
  @Override
  public void uilEnableGrobj(){
    uilHelper.uilEnableGrobj();
  }
  @Override
  public void setDialogProxy(UilClientDialog dlg){
    uilHelper.setDialogProxy(dlg);
    for (int i=0; i<members.size(); i++)
      ((UILSelectionButton)members.elementAt(i)).setDialogProxy(dlg);
  }
  @Override
  public UilClientDialog getDialogProxy(){
    return uilHelper.getDialogProxy();
  }
  @Override
  public String uilCallValidateMethodForGrobj(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilCallValidateMethodForGrobj(win);
  }
  @Override
  public String uilValidateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
					 Object actionQueue) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    return uilHelper.uilValidateGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
				 Object actionQueue){
    return uilHelper.uilValidateGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public void uilCallConcludeMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallConcludeMethodForGrobj(win);
  }
  @Override
  public void uilConcludeGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				     Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilConcludeGrobjMethod(win, dlg, button, actionQueue);
  }
  @Override
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, 
			       Object actionQueue) throws G2AccessException{
    uilHelper.uilConcludeGrobj(win, dlg, button, actionQueue);
  }
}
