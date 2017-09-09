package com.gensym.draw;

import java.awt.*;

public interface Scrollable {

  public void addScrollbar(ViewScrollbar scrollbar, boolean isHorizontal);
  public void removeScrollbar(ViewScrollbar scrollbar, boolean isHorizontal);
  public void addScrollObserver (java.util.Observer o, boolean isHorizontal);
  public ViewScrollState getScrollState(boolean isHorizontal);
  public void setScroll();
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom);
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom,
                        int viewLeft, int viewTop,
                        int viewRight, int viewBottom);
  public void growLogical(int size, boolean isHorizontal, 
                          boolean setMinimum);
  public void scrollView(int distance, boolean is_horizontal);
  public void scrollViewAbsolute(int new_view_min, boolean is_horizontal);
}
