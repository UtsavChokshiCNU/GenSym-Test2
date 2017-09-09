package com.gensym.uilcontrols;

import java.awt.Component;
import java.io.Serializable;
import java.io.IOException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.beansruntime.Enum;
import com.gensym.controls.FieldType;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.UiClientItem;
import com.gensym.classes.modules.uilroot.UilText;

public class UilClientTextImpl extends UilClientGrmesImpl implements UilClientText, Serializable{

  static final long serialVersionUID = -8591197382321828407L;
  
  private Symbol uilLabelConstant;
  private Symbol uilTranslationConstraints;
  private String uilLabelId;
  private Symbol uilFormatSpecification;
  private String uilBorderId;
  private Symbol state;
  private String messageContents;
  private boolean uilUpdateValue;

  private UILFormatSpec fieldType;

  public UilClientTextImpl(UilText uilText, UILText component,
			   Class staticClass) throws G2AccessException{
    super(uilText, component, staticClass);
    uilLabelConstant = uilText.getUilLabelConstant();
    uilTranslationConstraints = uilText.getUilTranslationConstraints();
    uilLabelId = (String)uilText.getUilLabelId();
    uilFormatSpecification = (Symbol)uilText.getUilFormatSpecification();
    uilBorderId = (String)uilText.getUilBorderId();
    state = (Symbol)uilText.getState();
    messageContents = (String)uilText.getMessageContents();
    uilUpdateValue = ((Boolean)uilText.getUilUpdateValue()).booleanValue();

    G2Access connection = ((ImplAccess)uilText).getContext();//is this kosher?
    fieldType = UILFormatSpec.create(connection, uilFormatSpecification);
  }

  //UilClientText interface
  //properties
  @Override
  public Symbol getUilLabelConstant(){
    return uilLabelConstant;
  }

  @Override
  public Symbol getUilTranslationConstraints(){
    return uilTranslationConstraints;
  }

  @Override
  public String getUilLabelId(){
    return uilLabelId;
  }

  @Override
  public Symbol getUilFormatSpecification(){
    return uilFormatSpecification;
  }

  @Override
  public String getUilBorderId(){
    return uilBorderId;
  }

  @Override
  public Symbol getUilState(){
    return state;
  }

  @Override
  public String getMessageContents(){
    return messageContents;
  }

  protected void setMessageContents(String messageContents){
    this.messageContents = messageContents;
  }

  @Override
  public boolean getUilUpdateValue(){
    return uilUpdateValue;
  }

  //API
  @Override
  public void uilUpdateGrobj(UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, 
			     Object actionQueue) throws G2AccessException{
    if (uilUpdateValue)
      super.uilUpdateGrobj(win, dlg, buttonOrInitObj, actionQueue);
  }

  @Override
  public void uilUpdateText(Object value){
    String txt = fieldType.objectToString(value);
    messageContents = txt;
    clipText(txt);
  }

  //misc
  @Override
  public Object getValue(){
    return messageContents;
  }
}
