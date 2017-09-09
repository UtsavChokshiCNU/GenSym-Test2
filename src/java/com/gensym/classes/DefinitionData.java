/**
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   DefinitionData.java 
 * 
 * 
 */ 

package com.gensym.classes;

import com.gensym.util.DefinitionListener;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;

/**
 * Stores data necessary for DefinitionSpecialImpl
 *
 * @version 	1.00, 9/25/98
 * @author      vkp
 */

public class DefinitionData extends ItemData {

  /**
   * The list of listners who are interested in
   * changes to this Definition
   */
  public volatile DefinitionListener defnListener;

  /**
   * Keep copy of attributes as known to us so that we can
   * do a diff when we get itemModified. This is because
   * G2 sends us an update for almost all attributes when
   * definitions in the hierarchy change.
   */
  public volatile Structure defnAttributesStructure;

  public Sequence systemClassInhPath;

}
