package com.gensym.uilcontrols;

import java.awt.Component;
import java.awt.Dimension;
import java.lang.reflect.InvocationTargetException;
import com.gensym.widgets.Spin;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.widgets.TextWidget;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uillib.UilSpinControlEntryBox;

public class UILSpinControl extends Spin implements UilClientSpinControl{

  static final long serialVersionUID = -6891176474513220622L;

  private UilClientSpinControl uilHelper;
  private UILSpinBox editBox;

  public UILSpinControl(UilSpinControlEntryBox uilSpinControl, Class staticClass) throws G2AccessException{
    super(new UILSpinBox(uilSpinControl, staticClass));
    editBox = (UILSpinBox)getTextWidget();
    editBox.setSpinControl(this);
    uilHelper = new UilClientSpinControlImpl(uilSpinControl, this, staticClass);
  }

  UILEditBox getEditBox(){
    return editBox;
  }

  //UilClientSpinControl interface: delegated to uilHelper
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
  public Object getUilMaximumCharactersToDisplay(){
    return uilHelper.getUilMaximumCharactersToDisplay();
  }
  @Override
  public int getUilBoxWidth(){
    return uilHelper.getUilBoxWidth();
  }
  @Override
  public Symbol getUilEditStyle(){
    return uilHelper.getUilEditStyle();
  }
  @Override
  public boolean getUilAllowFieldEditOfThisMessage(){
    return uilHelper.getUilAllowFieldEditOfThisMessage();
  }
  @Override
  public Symbol getUilFormatSpecification(){
    return uilHelper.getUilFormatSpecification();
  }
  @Override
  public boolean getUilClearTextBeforeEdit(){
    return uilHelper.getUilClearTextBeforeEdit();
  }
  @Override
  public Symbol getUilConcludeMethod(){
    return uilHelper.getUilConcludeMethod();
  }
  @Override
  public boolean getUilValidateValueImmediately(){
    return uilHelper.getUilValidateValueImmediately();
  }
  @Override
  public Symbol getUilValidationMethod(){
    return uilHelper.getUilValidationMethod();
  }
  @Override
  public Symbol getUilMessageSelectionMethod(){
    return uilHelper.getUilMessageSelectionMethod();
  }
  @Override
  public Symbol getUilMessageUnselectionMethod(){
    return uilHelper.getUilMessageUnselectionMethod();
  }
  @Override
  public String getLabel(){
    return uilHelper.getLabel();
  }
  @Override
  public void setLabel(String label){
    uilHelper.setLabel(label);
  }
  @Override
  public Symbol getUilState(){
    return uilHelper.getUilState();
  }
  @Override
  public String getMessageContents(){
    return uilHelper.getMessageContents();
  }
  @Override
  public void setMessageContents(String txt){
    uilHelper.setMessageContents(txt);
  }
  @Override
  public boolean getUilUpdateValue(){
    return uilHelper.getUilUpdateValue();
  }
  @Override
  public Boolean getUilUseGrammarPerTargetSpecifications(){
    return uilHelper.getUilUseGrammarPerTargetSpecifications();
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
  public UilCallback getValidationCallback(){
    return uilHelper.getValidationCallback();
  }
  @Override
  public void setValidationCallback(UilCallback callback){
    uilHelper.setValidationCallback(callback);
  }
  @Override
  public UilCallback getMessageSelectionCallback(){
    return uilHelper.getMessageSelectionCallback();
  }
  @Override
  public void setMessageSelectionCallback(UilCallback callback){
    uilHelper.setMessageSelectionCallback(callback);
  }
  @Override
  public UilCallback getMessageUnselectionCallback(){
    return uilHelper.getMessageUnselectionCallback();
  }
  @Override
  public void setMessageUnselectionCallback(UilCallback callback){
    uilHelper.setMessageUnselectionCallback(callback);
  }
  @Override
  public double getUilSpinControlLowValue(){
    return uilHelper.getUilSpinControlLowValue();
  }
  @Override
  public double getUilSpinControlHiValue(){
    return uilHelper.getUilSpinControlHiValue();
  }
  @Override
  public double getUilSpinControlIncrement(){
    return uilHelper.getUilSpinControlIncrement();
  }
  @Override
  public boolean getUilSpinControlPermitWrapping(){
    return uilHelper.getUilSpinControlPermitWrapping();
  }
  @Override
  public void setUilSpinControlLowValue(double lowValue){
    uilHelper.setUilSpinControlLowValue(lowValue);
  }
  @Override
  public void setUilSpinControlHiValue(double highValue){
    uilHelper.setUilSpinControlHiValue(highValue);
  }
  @Override
  public void setUilSpinControlIncrement(double increment){
    uilHelper.setUilSpinControlIncrement(increment);
  }
  @Override
  public void setUilSpinControlPermitWrapping(boolean permitWrapping){
    uilHelper.setUilSpinControlPermitWrapping(permitWrapping);
  }

  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallUpdateMethodForGrobj(win);
  }
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilUpdateGrobjMethod(win, dlg, buttonOrInitObj, actionQueue);
  }
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
    uilHelper.uilUpdateGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }
  @Override
  public void uilDisableGrobj(){
    uilHelper.uilDisableGrobj();
  }
  @Override
  public void uilDisableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilDisableGrobjMethod();
  }
  @Override
  public void uilEnableGrobj(){
    uilHelper.uilEnableGrobj();
  }
  @Override
  public void uilEnableGrobjMethod() throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEnableGrobjMethod();
  }
  @Override
  public void setDialogProxy(UilClientDialog dlg){
    uilHelper.setDialogProxy(dlg);
  }
  @Override
  public UilClientDialog getDialogProxy(){
    return uilHelper.getDialogProxy();
  }
  @Override
  public void uilUpdateText(Object value){
    uilHelper.uilUpdateText(value);
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
  public String uilValidateGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue){
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
  public void uilConcludeGrobj(UiClientItem win, UilClientDialog dlg, Object button, Object actionQueue) 
       throws G2AccessException{
    uilHelper.uilConcludeGrobj(win, dlg, button, actionQueue);
  }
  @Override
  public Object uilGetEditBoxValue(){
    return uilHelper.uilGetEditBoxValue();
  }
  @Override
  public void uilUpdateEditBoxLabel(){
    uilHelper.uilUpdateEditBoxLabel();
  }
  @Override
  public void uilEditBoxSelection(UilClientDialog dlg, UiClientItem win){
    uilHelper.uilEditBoxSelection(dlg, win);
  }
  @Override
  public void uilEditBoxSelectionMethod(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEditBoxSelectionMethod(dlg, win);
  }
  @Override
  public void uilEditBoxUnselection(UilClientDialog dlg, UiClientItem win, Boolean committed)throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEditBoxUnselection(dlg, win, committed);
  }
  @Override
  public void uilEditBoxUnselectionMethod(UilClientDialog dlg, UiClientItem win, Boolean committed) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilEditBoxUnselectionMethod(dlg, win, committed);
  }
  @Override
  public void uilSelectEditBox(UilClientDialog dlg, UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilSelectEditBox(dlg, win);
  }
  @Override
  public void uilSelectEditBoxOnDialog(UiClientItem win) throws ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilSelectEditBoxOnDialog(win);
  }
  @Override
  public TextWidget getLabelComponent(){
    return uilHelper.getLabelComponent();
  }
  @Override
  public void setLabelComponent(TextWidget text){
    uilHelper.setLabelComponent(text);
  }
}

class UILSpinBox extends UILEditBox{
  
  static final long serialVersionUID = 8109553165201697045L;

  private UILSpinControl spin;

  UILSpinBox(UilSpinControlEntryBox uilSpinControl, Class staticClass) throws G2AccessException{
    super(uilSpinControl, staticClass);
  }

  void setSpinControl(UILSpinControl spin){
    this.spin = spin;
  }
  
  @Override
  public void setText(String txt){
    super.setText(txt);
    if (spin != null)
      spin.setMessageContents(txt);
  }

  @Override
  public void setSize(int width, int height){
    Dimension size = getSize();
    int widthDiff = width - size.width;
    int heightDiff = height - size.height;
    super.setSize(width, height);
    java.awt.Container parent = getParent();
    if (parent != null){
      size = parent.getSize();
      parent.setSize(size.width+widthDiff, size.height+heightDiff);
      parent.validate();
    } 
  }

}

