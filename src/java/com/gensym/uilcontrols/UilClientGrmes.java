package com.gensym.uilcontrols;

public interface UilClientGrmes extends UilClientItem{

  //properties
  public Object getUilMaximumCharactersToDisplay();
  public int getUilBoxWidth();

  //API
  public void uilUpdateText(Object value);
 
}
