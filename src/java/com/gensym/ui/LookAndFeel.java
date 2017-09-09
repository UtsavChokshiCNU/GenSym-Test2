package com.gensym.ui;

/**
 * @undocumented
 */
public class LookAndFeel {
  private static boolean snappyLookAndFeel;
  public static boolean getUseSnappyLookAndFeel() {
    return snappyLookAndFeel;
  }
  public static void setUseSnappyLookAndFeel(boolean snappyLookAndFeel) {
    LookAndFeel.snappyLookAndFeel = snappyLookAndFeel;
  }
}
