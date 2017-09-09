package com.gensym.ntw.files;

import com.gensym.files.*;

public class UILDialogImportFileSystemView extends URLFileSystemView
{  
  public UILDialogImportFileSystemView(String startingPath)
  {
    super(new UILDialogImportDirectoryModel(startingPath));
  }
}
