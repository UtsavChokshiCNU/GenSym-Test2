package com.gensym.uilcontrols;

import java.awt.Canvas;
import java.awt.Component;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Color;
import java.util.StringTokenizer;
import java.io.Serializable;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.widgets.TextWidget;
import com.gensym.beansruntime.Enum;
import com.gensym.controls.FieldType;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilText;
import com.gensym.classes.modules.uillib.UilFormatSpecificationClass;

public class UILText extends Canvas implements TextWidget, UilClientText, Serializable{

  static final long serialVersionUID = -8591197382321828407L;

  public static final int LEFT = 0;
  public static final int CENTER = 1;
  public static final int RIGHT = 2;
  private static final String[] alignmentChoices = new String[] {"Left", "Center", "Right"};
  private static final int[] alignmentCodes = new int[]{LEFT, CENTER, RIGHT};

  private static final int TEXT_XPAD = 12;
  private static final int TEXT_YPAD = 8;

  private static final Symbol LEFT_ = Symbol.intern("LEFT");
  private static final Symbol CENTER_ = Symbol.intern("CENTER");
  private static final Symbol RIGHT_ = Symbol.intern("RIGHT");

  private UilClientText uilHelper;

  private String text = "Label:";
  private Enum alignment;
  private boolean border;

  public UILText(UilText uilText, Class staticClass) throws G2AccessException{
    uilHelper = new UilClientTextImpl(uilText, this, staticClass);

    if (!uilHelper.getUilBorderId().equals(""))
      setBorder(true);

    Symbol alignment = uilText.getTextAlignment();
    if (alignment.equals(LEFT_))
      setAlignment(LEFT);
    else if (alignment.equals(CENTER_))
      setAlignment(CENTER);
    else if (alignment.equals(RIGHT_))
      setAlignment(RIGHT);

    setText(uilText.getText());
  }

  @Override
  public void setText(String txt){
    text = txt;
    repaint();
  }

  @Override
  public String getText(){
    return text;
  }

  private void setBorder(boolean border){
    if (this.border == border) return;
    this.border = border;
    repaint();
  }

  public void setAlignment(int alignment){
    setAlignment(new Enum(alignmentChoices, alignmentCodes, alignment)); 
  }

  public void setAlignment(Enum alignment){
    this.alignment = alignment;
    repaint();
  }

  public Enum getAlignment(){
    return alignment;
  }  

  @Override
  public Dimension getMinimumSize(){
    return getPreferredSize();
  }

  private Font defaultFont = new Font("Dialog", Font.PLAIN, 12);

  @Override
  public Dimension getPreferredSize(){
    Font font = getFont();
    if (font == null)
      font = defaultFont;
    FontMetrics fm = getFontMetrics(font);
    return new Dimension(fm.stringWidth(text) + TEXT_XPAD, 
			 fm.getMaxAscent() + fm.getMaxDescent() + TEXT_YPAD);
  }

  private static final int BORDER_WIDTH = 2;

  @Override
  public void paint(Graphics g){
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;

    g.setColor(getBackground());
    g.fillRect(0, 0, width - 1, height - 1);

    if (!isEnabled())
      g.setColor(Color.white);
    else
      g.setColor(getForeground());
    g.setFont(getFont());
       
    FontMetrics fm = g.getFontMetrics();
    int x = 1 + BORDER_WIDTH;
    if (alignment != null){
      int align = alignment.value;
      if (align == CENTER)
	x = (width - fm.stringWidth(text))/2;
      else if (align == RIGHT)
	x = width - fm.stringWidth(text) - BORDER_WIDTH - 1;
    }

    g.drawString(text, x, 
		 (height + fm.getMaxAscent() - fm.getMaxDescent()) / 2);

    if (!isEnabled()){
      g.setColor(Color.gray);
      g.drawString(text, x-1, 
		   ((height + fm.getMaxAscent() - fm.getMaxDescent()) / 2)-1);
      
    }
    
    if (border){
      g.setColor(Color.gray);
      g.drawLine(0, 0, width - 1, 0);
      g.drawLine(0, 1, width - 1, 1);
      g.drawLine(0, 0, 0, height - 1);
      g.drawLine(1, 0, 1, height - 1);
      g.setColor(Color.white);
      g.drawLine(0, height - 1, width - 1, height - 1);
      g.drawLine(0, height - 2, width - 1, height - 2);
      g.drawLine(width - 1, 0, width - 1, height - 1);
      g.drawLine(width - 2, 0, width - 2, height - 1);
    }
  }


  @Override
  public String toString(){
    return super.toString()+" id="+uilHelper.getId()+" messageContents="+uilHelper.getMessageContents();
  }

  //UilClientText interface: delegated to uilHelper
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
  public Symbol getUilLabelConstant(){
    return uilHelper.getUilLabelConstant();
  }
  @Override
  public Symbol getUilTranslationConstraints(){
    return uilHelper.getUilTranslationConstraints();
  }
  @Override
  public String getUilLabelId(){
    return uilHelper.getUilLabelId();
  }
  @Override
  public Symbol getUilFormatSpecification(){
    return uilHelper.getUilFormatSpecification();
  }
  @Override
  public String getUilBorderId(){
    return uilHelper.getUilBorderId();
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
  public boolean getUilUpdateValue(){
    return uilHelper.getUilUpdateValue();
  }

  //API
  @Override
  public void uilCallUpdateMethodForGrobj(UiClientItem win) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilCallUpdateMethodForGrobj(win);
  }
  @Override
  public void uilUpdateGrobjMethod(UiClientItem win, UilClientDialog dlg, Object button, 
				   Object actionQueue) throws G2AccessException, ClassNotFoundException, InvocationTargetException, NoSuchMethodException, IllegalAccessException{
    uilHelper.uilUpdateGrobj(win, dlg, button, actionQueue);
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
  }
  @Override
  public UilClientDialog getDialogProxy(){
    return uilHelper.getDialogProxy();
  }
  @Override
  public void uilUpdateText(Object value){
    uilHelper.uilUpdateText(value);
  }
}
