package com.gensym.gcg;

import java.util.Vector;

/**
 * G2AttributeGroup designates logical groupings of editors.  A container can use these
 * groupings in laying out the editors.  For example, each group may be placed on a
 * separate tab page
 */
public class G2AttributeGroup{

  private String name;
  private Vector editors = new Vector();

  public G2AttributeGroup(String name){
    this.name = name;
  }
  
  /**
   *  Add an editor to this group
   */
  public void addEditor(G2AttributeEditor editor){
    editors.addElement(editor);
  }
  
  /**
   * Returns the name of this group
   */
  public String getName(){
    return name;
  }

  /**
   *  Returns a list of all of the editors in this group
   */
  public G2AttributeEditor[] getEditors(){
    G2AttributeEditor[] editorList = new G2AttributeEditor[editors.size()];
    editors.copyInto(editorList);
    return editorList;
  }

}
