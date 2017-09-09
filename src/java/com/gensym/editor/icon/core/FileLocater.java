package com.gensym.editor.icon.core;

import java.net.URL;
import javax.swing.filechooser.FileFilter;

public interface FileLocater {
  public URL getFile(FileFilter filter);
}
