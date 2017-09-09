package com.gensym.dlgruntime;

import java.net.URL;

public class GeneratedDialogResource extends DialogResource
{
  private DialogLauncher dialogLauncher;
  GeneratedDialogResource(URL url)
  {
    super(url);
  }

  /**
   * @undocumented
   */
  @Override
  public DialogLauncher getDialogLauncher() {
    if (dialogLauncher == null) {
      dialogLauncher = new DefaultGeneratedDialogLauncher();
    }
    return dialogLauncher;
  }
}
