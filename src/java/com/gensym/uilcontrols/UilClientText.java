package com.gensym.uilcontrols;

import com.gensym.util.Symbol;

public interface UilClientText extends UilClientGrmes{

  //properties
  public Symbol getUilLabelConstant();
  public Symbol getUilTranslationConstraints();
  public String getUilLabelId();
  public Symbol getUilFormatSpecification();
  public String getUilBorderId();
  public Symbol getUilState();
  public String getMessageContents();
  public boolean getUilUpdateValue();

}
