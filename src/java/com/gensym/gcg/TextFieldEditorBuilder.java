package com.gensym.gcg;

import java.awt.Component;

import com.gensym.types.*;
import com.gensym.jcontrols.G2TextField;
import com.gensym.controls.FieldType;


public class TextFieldEditorBuilder extends EditorBuilder 
{
  G2Type type;
  boolean emptyFieldImpliesNoItem;

  public TextFieldEditorBuilder(G2Type type)
  {
    this.type = type;
  }

  public TextFieldEditorBuilder(G2Type type, Boolean emptyFieldImpliesNoItem)
  {
    this.type = type;
    this.emptyFieldImpliesNoItem = emptyFieldImpliesNoItem.booleanValue();
  }

  @Override
  public Component buildEditor()
  {
    G2TextField textField = new G2TextField();
    textField.setFieldType(new FieldType(type));
    textField.setEmptyFieldImpliesNull(emptyFieldImpliesNoItem);
    return textField;
  }
}
