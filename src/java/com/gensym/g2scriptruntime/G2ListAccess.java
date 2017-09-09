package com.gensym.g2scriptruntime;

/**

This interface is for the G2List types. We simply want access to
Vector/Sequence methods here, but we must take into account the
Allow-Duplicate-Entries slot. 

*/


public interface G2ListAccess {

  /**
   * Returns the Sequence used internally to store the G2List data.
   */
  public com.gensym.util.CheckedSequence getList();

  /**
   * Set the Sequence used internally to store the G2List data.
   * The original Sequence will no longer be referenced by the G2List.
   */
  public void setList(com.gensym.util.CheckedSequence list);

  public boolean getAllowDuplicateElements();

  public void setAllowDuplicateElements(boolean state);
} 

