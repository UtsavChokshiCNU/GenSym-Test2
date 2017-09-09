package com.gensym.ui;

import java.awt.Component;
import java.awt.Frame;
import java.awt.Window;
import javax.swing.SwingUtilities;

public class UIUtilities {

  /**
   * @returns a <code>Frame</code> if the window ancestor of
   * <code>component</code> is a <code>Frame</code>, <code>null</code>
   * otherwise.
   * @see javax.swing.SwingUtilities#getWindowAncestor(Component).
   */
  public static Frame getFrameIfAny(Component component) {
    Window window = SwingUtilities.getWindowAncestor(component);

    if (window instanceof Frame)
      return (Frame)window;
    else
      return null;
  }
}
