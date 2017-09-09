package com.gensym.wksp;

import com.gensym.wksp.WorkspaceView;
import com.gensym.draw.ViewScrollbar;
import com.gensym.draw.Scrollable;

/**
 * An Observer class that provides scrolling capability for a
 * WorkspaceView.
 * @see com.gensym.wksp.WorkspaceView
 */
public class WorkspaceViewScrollbar extends ViewScrollbar {

  // This signature provided as a place to put explainable
  // documentation
  /**
   * @param parent The WorkspaceView that this scrollbar will
   * be controlling
   * @param orientation one of Scrollbar.HORIZONTAL or
   * Scrollbar.VERTICAL
   * @param value initial scroll value (or position)
   * @param visible
   * @param minimum
   * @param maximum
   */
  public WorkspaceViewScrollbar (WorkspaceView parent,
				 int orientation, int value, 
				 int visible, int minimum, int maximum)
  {
    super(parent, orientation, value, visible, minimum, maximum);
  }

  // This signature provided for full compatibility with the
  // superclass.
  /**
   * @undocumented
   */
  public WorkspaceViewScrollbar (Scrollable parent,
				 int orientation, int value, 
				 int visible, int minimum, int maximum)
  {
    super(parent, orientation, value, visible, minimum, maximum);
  }
}
