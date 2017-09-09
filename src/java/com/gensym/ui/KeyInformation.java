package com.gensym.ui;

import javax.swing.KeyStroke;

public class KeyInformation{

  private String cmdKey;
  private boolean useDefaultMnemonic;
  private Character mnemonic;
  private boolean useDefaultShortcut;
  private KeyStroke shortcut;

  /**
   * Encapsulated key information for a single command.
   * @param cmdKey the command's key
   * @param useDefaultMnemonic true to use default mnemonic and ignore the mnemonic parameter, false to use the provided mnemonic
   * @param mnemonic mnemonic to be used for command instead of any default, null means no mnemonic
   * @param useDefaultShortcut true to use default shortcut and ignore the shortcut parameter, false to use the provided shortcut
   * @param shortcut shortcut to be used for command instead of any default, null means no shortcut
   */
  public KeyInformation(String cmdKey, boolean useDefaultMnemonic, Character mnemonic, 
			boolean useDefaultShortcut, KeyStroke shortcut){
    this.cmdKey = cmdKey;
    this.useDefaultMnemonic = useDefaultMnemonic;
    this.mnemonic = mnemonic;
    this.useDefaultShortcut = useDefaultShortcut;
    this.shortcut = shortcut;
  }

  public String getCommandKey(){
    return cmdKey;
  }

  public boolean getUseDefaultMnemonic(){
    return useDefaultMnemonic;
  }

  public Character getMnemonic(){
    return mnemonic;
  }

  public boolean getUseDefaultShortcut(){
    return useDefaultShortcut;
  }

  public KeyStroke getShortcut(){
    return shortcut;
  }
}
