
package com.gensym.ntw.util;

public class WorkspaceDisplayStyle {

  private boolean isFloating, isTitleDisplayed, isScrollbarsVisible, allowMultipleViews;
      

  WorkspaceDisplayStyle (boolean isFloating, boolean isTitleDisplayed,
			 boolean isScrollbarsVisible, boolean allowMultipleViews) {
    this.isFloating = isFloating;
    this.isTitleDisplayed = isTitleDisplayed;
    this.isScrollbarsVisible = isScrollbarsVisible;
    this.allowMultipleViews = allowMultipleViews;
  }

  public boolean isFloating () {
    return isFloating;
  }

  public boolean isTitleDisplayed () {
    return isTitleDisplayed;
  }

  public boolean isScrollbarsVisible () {
    return isScrollbarsVisible;
  }

  public boolean allowMultipleViews () {
    return allowMultipleViews;
  }
}
