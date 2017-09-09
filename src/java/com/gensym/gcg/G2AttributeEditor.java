package com.gensym.gcg;

import java.awt.Component;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.ItemProxy;
import com.gensym.util.Symbol;

/**
 * This class encapsulates information concerning an editor for an attribute of an item
 */
public class G2AttributeEditor{

  private String groupName;
  private Component label;
  private AttributeEditor editor;
  private ItemProxy itemProxy;
  private Symbol attribute;

  public G2AttributeEditor(String groupName, Component label, AttributeEditor editor, ItemProxy itemProxy,
			   Symbol attribute){
    this.groupName = groupName;
    this.label = label;
    this.editor = editor;
    this.itemProxy = itemProxy;
    this.attribute = attribute;
  }

  /**
   *  Returns the group to which this editor belongs
   */
  public String getGroupName(){
    return groupName;
  }

  /**
   *  Returns a Component to be used as the label for the editor
   */
  public Component getLabel(){
    return label;
  }

  /**
   *  Returns a Component to be used to edit the attribute
   */
  public AttributeEditor getEditor(){
    return editor;
  }

  public ItemProxy getItemProxy(){
    return itemProxy;
  }

  /**
   *  Returns the attribute for which this is an editor
   */
  public Symbol getAttribute(){
    return attribute;
  }

  @Override
  public String toString(){
    return getClass().getName() + "[" + paramString() + "]";
  }

  private String paramString(){
    return "itemProxy="+itemProxy+" attribute="+attribute+" group="+groupName+" label="+label+" editor="+editor;
  }
}
