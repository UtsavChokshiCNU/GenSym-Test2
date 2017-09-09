package com.gensym.swing;

import com.sun.java.swing.plaf.motif.*;
import javax.swing.*;

public class GensymMotifLookAndFeel extends MotifLookAndFeel
{

  @Override
  protected void initClassDefaults(UIDefaults table)
  {
    super.initClassDefaults(table);
    table.put("FileChooserUI","com.gensym.swing.plaf.GensymMotifFileChooserUI");
  }
}
