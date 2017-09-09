/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ArraySpecialImpl.java
 *
 *      Author: Gensym Corp.
 *
 */


package com.gensym.g2export;

import com.gensym.util.Structure;
import com.gensym.util.CheckedSequence;
import com.gensym.util.Symbol;
import com.gensym.g2scriptruntime.G2ListAccess;

public class G2ListSpecialImpl extends G2__BaseImpl 
     implements com.gensym.g2scriptruntime.G2ListAccess {
  
  protected CheckedSequence internalList;
  public boolean allowDuplicateElements;

  /**
   * Returns the Sequence used internally to store the G2List data.
   */
  @Override
  public com.gensym.util.CheckedSequence getList() {
    if (internalList == null) {
      internalList = new CheckedSequence();
      internalList.setAllowDuplicateElements(allowDuplicateElements);
    }
    return internalList;
  }

  /**
   * Set the Sequence used internally to store the G2List data.
   * The original Sequence will no longer be referenced by the G2List.
   */
  @Override
  public void setList(com.gensym.util.CheckedSequence list) {
    internalList = list;
  }
    

  @Override
  public boolean getAllowDuplicateElements() {
    return allowDuplicateElements;
  }

  @Override
  public void setAllowDuplicateElements(boolean state) {
    CheckedSequence list = getList();
    list.setAllowDuplicateElements(state);
    allowDuplicateElements = state;
  }
}
