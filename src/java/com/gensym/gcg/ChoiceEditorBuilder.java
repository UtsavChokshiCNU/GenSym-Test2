package com.gensym.gcg;

import java.awt.Component;
import java.io.IOException;

import com.gensym.types.*;
import com.gensym.jcontrols.G2ComboBox;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
import com.gensym.util.UnexpectedException;


public class ChoiceEditorBuilder extends EditorBuilder 
{
  MemberType type;
  G2Type elementType;

  public ChoiceEditorBuilder(G2Type type, G2Type elementType)
  {
    this.type = (MemberType) type;
    this.elementType = elementType;
  }

  @Override
  public Component buildEditor()
  {
    G2ComboBox choice = new G2ComboBox();
    //G2DropDownChoice choice = new G2DropDownChoice();
    FieldType fieldType = new FieldType(elementType);
    choice.setFieldType(fieldType);
    Object[] members = type.getMembers();
    int i,length = members.length;
    StringVector choices = new StringVector();
    try {
      for (i=0; i<length ; i++)
	choices.addElement(fieldType.objectToString(members[i]));
    } catch (IOException e)
      {
	throw new UnexpectedException(e);
      }
    choice.setChoices(choices);
    return choice;
  }
}
