/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionSpecialImpl.java
 *
 *   Description: Overides for generated Interface files. 
 *
 *        Author: Paul B. Konigberg
 *
 *       Version: 5.0 Rev. 1
 *
 *          Date: Thu Apr 16 10:44:44 EDT 1998
 *
 */


package com.gensym.classes;

import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class ConnectionSpecialImpl extends ItemImpl {
  private static final Symbol
    G2_MAKE_CONNECTION_FOR_USER_         = Symbol.intern ("G2-MAKE-CONNECTION-FOR-USER"),
    G2_GET_CONNECTION_INPUT_AND_OUTPUT_  = Symbol.intern ("G2-GET-CONNECTION-INPUT-AND-OUTPUT");
  
  /**
   * @return a Sequence of the {InputObject or False, OutputObject or False}
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                              
  public Sequence getConnectionInputAndOutput () throws G2AccessException {
    java.lang.Object[] args
      = new java.lang.Object[] {this};
    return (Sequence) callRPC (G2_GET_CONNECTION_INPUT_AND_OUTPUT_, args);
  }

  /**
   * @param otherItemOrStub either the loose end Connection or Entity to
   * which this Connection should be connected.
   * @param makeConnectionMode either MOVING_LOOSE_END_, JOINING_LOOSE_ENDS_,
   * or MAKING_NEW_JUNCTION_BLOCK_;
   * @param connectionPositionSequence a flattend Sequence of the vertices
   * to be set for this connection.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */                              
  public void setVerticesAndJoin(Item otherItemOrStub,
				 Symbol makeConnectionMode,
				 Sequence connectionPositionSequence) throws G2AccessException {
    java.lang.Object otherItemOrFalse = otherItemOrStub;
    if (otherItemOrStub == null)
      otherItemOrFalse = Boolean.FALSE;
    java.lang.Object[] args = new java.lang.Object[5];
    args[0] = this;
    args[1] = otherItemOrFalse;
    args[2] = makeConnectionMode;
    args[3] = connectionPositionSequence;
    args[4] = Boolean.FALSE;
    callRPC (G2_MAKE_CONNECTION_FOR_USER_, args);
  }

  /**
   * @undocumented Used to update the CONNECTION-POSITION-SEQUENCE
   * attribute from a WorkspaceEvent
   */
  @Override
  public void setBoundsFromWorkspaceEvent (Structure eventInfo) {
    Structure attributes = getActualAttributes();
    Sequence cxnPosnSeq = (Sequence)
	  eventInfo.getAttributeValue (TW_WORKSPACE_ITEM_POSITION_, null);
    attributes.setAttributeValue (CONNECTION_POSITION_SEQUENCE_, cxnPosnSeq);
  }

}
