package com.gensym.uilcontrols;

import com.gensym.util.Sequence;

public interface UilClientCheckBox extends UilClientSelectionBox{

  //no properties

  //API
  public Sequence uilGetCheckBoxValues();
  public void uilSetCheckBoxValues(Sequence values);
}


