package com.gensym.gcg;

import java.awt.Component;

import com.gensym.types.*;
import com.gensym.jcontrols.G2Checkbox;
import com.gensym.controls.FieldType;

public class CheckboxEditorBuilder extends EditorBuilder 
{
  G2Type type;

  public CheckboxEditorBuilder()
  {
  }

  @Override
  public Component buildEditor()
  {
    G2Checkbox checkbox = new G2Checkbox();
    checkbox.setLabel("");
    return checkbox;
  }
}
