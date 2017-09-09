package com.gensym.editor.icon.core;

import java.awt.Color;

public interface IconFormat {
  public Object createFormattedIcon(IconEditorCanvas canvas);
  public void importFormattedIcon(Object formattedIcon,
				  IconEditorCanvas canvas);
  public String getFormatName();
  public String getFormatDescription();
  public Object getDescriptionOfColor(Color color);
}
