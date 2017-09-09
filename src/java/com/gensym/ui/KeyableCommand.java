package com.gensym.ui;

import javax.swing.KeyStroke;

public interface KeyableCommand{

  public Character getMnemonic(String commandKey);

  public KeyStroke getShortcut(String commandKey);
}
