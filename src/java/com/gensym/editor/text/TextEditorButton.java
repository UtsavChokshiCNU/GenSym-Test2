/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TextEditorButton.java
 *
 */
package com.gensym.editor.text;

import java.awt.Button;
import java.util.Locale;
import com.gensym.message.Resource;


/** This is a simple subclasssing of the AWT button so that 
 * we can setup a resource by which to internationalize button labels.
 * @author David McDonald
 * @version 1.0
 * @undocumented -- final Text Editor API is still under review
 */

/* v0.1 just subclasses button.
 * v0.2 adds the resource. 
 */

class TextEditorButton extends Button { 

  static private Resource i18nLabels =
     Resource.getBundle("com.gensym.editor.text.ButtonLabels", Locale.getDefault() );
  
  public TextEditorButton( String label ) {
    super( i18nLabels.getString(label) );
  }
}
