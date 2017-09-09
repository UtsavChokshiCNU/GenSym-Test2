package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.Vector;

public class SyntaxTypeEditor extends Panel implements PropertyEditor{

  private SyntaxType syntax = new SyntaxType();
  
  //PropertyEditor methods
  @Override
  public void setValue(Object value){
    syntax = (SyntaxType)value;
  } 

  @Override
  public Object getValue(){
    return syntax;
  } 

  @Override
  public String getAsText(){
    if (syntax.getType() == HookupFactory.JAVA)
      return "JAVA";
    else 
      return "G2SCRIPT";
  } 

  @Override
  public void setAsText(String text) throws IllegalArgumentException{
    if (text.equals("JAVA"))
      syntax.setType(HookupFactory.JAVA);
    else if (text.equals("G2SCRIPT"))
      syntax.setType(HookupFactory.G2SCRIPT);
    else throw new IllegalArgumentException("text should be JAVA or G2SCRIPT");
  } 

  @Override
  public String[] getTags(){
    return new String[] {"JAVA", "G2SCRIPT"};
  } 

  @Override
  public boolean isPaintable(){
    return false;
  } 

  @Override
  public void paintValue(Graphics g , Rectangle bounds){}

  @Override
  public String getJavaInitializationString(){
    if (syntax.getType() == HookupFactory.JAVA)
      return "SyntaxType.JAVA";
    else 
      return "SyntaxType.G2SCRIPT";
  }

  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener){} 
  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener){} 

  @Override
  public boolean supportsCustomEditor(){
    return false;
  } 

  @Override
  public Component getCustomEditor(){
    return null;
  } 
}
