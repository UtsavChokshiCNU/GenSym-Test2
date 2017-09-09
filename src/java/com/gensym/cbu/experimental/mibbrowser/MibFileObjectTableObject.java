package com.gensym.cbu.experimental.mibbrowser;

import javax.swing.*;
import javax.swing.table.*;

public interface MibFileObjectTableObject
{
  public int getRowCount();
  public String getAttribute(int row);
  public String getValue(int row);
}
