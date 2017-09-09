/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIEvent.java
 *
 */

package com.gensym.mdi;

import java.util.EventObject;

/**
 *  A MDIEvent is delivered whenever a document is added to a MDIManager.
 */
public class MDIEvent extends EventObject{

  private MDIDocument document;

  /**  Creates a MDIEvent with the specified source object and document. */
  public MDIEvent(MDIManager source, MDIDocument document){
    super(source);
    this.document = document;
  }

  /** Returns the document that was added. */
  public MDIDocument getDocument(){
    return document;
  }
}
