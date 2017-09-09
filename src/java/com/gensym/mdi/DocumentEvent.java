package com.gensym.mdi;

import java.util.EventObject;

/**
 * @undocumented
 */
public class DocumentEvent extends EventObject{

  private MDIDocument activeDoc;

  public DocumentEvent(MDIManager source, MDIDocument activeDoc){
    super(source);
    this.activeDoc = activeDoc;
  }

  public MDIDocument getActiveDocument(){
    return activeDoc;
  }
}
