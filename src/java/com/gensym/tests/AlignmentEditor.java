
package com.gensym.tests;

public class AlignmentEditor extends MemberIntPropertyEditor {

  @Override
  public String[] getNames () {
    return new String[] {"Left", "Center", "Right"};
  }

  @Override
  public int[] getValues () {
    return new int[] {0, 1, 2};
  }
}
