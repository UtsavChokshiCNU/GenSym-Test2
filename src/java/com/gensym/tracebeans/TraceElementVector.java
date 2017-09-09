package com.gensym.tracebeans;

import java.util.Vector;
import java.io.Serializable;

import java.beans.PropertyEditorManager;

public class TraceElementVector extends Vector implements java.io.Serializable {
  
  static final long serialVersionUID = 1660592314272617907L;
  public TraceElementVector() {
        try {
             Class editor = Class.forName("com.gensym.tracebeans.TraceElementVectorEditor");

             PropertyEditorManager.registerEditor
                (this.getClass(),
                editor);
        }
        catch (ClassNotFoundException e) {

        }
    }
}
