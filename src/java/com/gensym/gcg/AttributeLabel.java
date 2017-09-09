package com.gensym.gcg;

import javax.swing.JLabel;
import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.ClassManager;
import com.gensym.util.DefinitionEvent;
import com.gensym.util.DefinitionListener;
import com.gensym.util.Symbol;

/**
 * AttributeLabel is the component representation of an attribute name.
 * By default, the label is the attribute name with '-' replaced with space and a ':' appended to the end.
 */
public class AttributeLabel extends JLabel {

  private Symbol attribute;
  private G2Definition definition;

  public AttributeLabel(TwAccess connection, Item item, Symbol attribute, boolean live) throws G2AccessException{
    this.attribute = attribute;
    setText(translateAttributeName(attribute).toString());
  }

  protected StringBuffer translateAttributeName(Symbol attribute){
    StringBuffer buffer = 
      new StringBuffer(attribute.toString().replace('-',' ').toLowerCase());
    buffer.setCharAt(0,Character.toUpperCase(buffer.charAt(0)));
    buffer.append(':');
    return buffer;
  }

}
