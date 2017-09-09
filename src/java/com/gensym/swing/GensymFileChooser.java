/*
 * @(#)JFileChooser.java	1.65 00/03/14
 *
 * Copyright 1997-2000 Sun Microsystems, Inc. All Rights Reserved.
 * 
 * This software is the proprietary information of Sun Microsystems, Inc.  
 * Use is subject to license terms.
 * 
 */

package com.gensym.swing;

import com.gensym.core.util.SystemUtilities;
import com.gensym.swing.plaf.GensymMotifFileChooserUI;

import java.io.File;
import javax.swing.JFileChooser;
import javax.swing.UIManager;
import javax.swing.filechooser.FileView;
import javax.swing.filechooser.FileSystemView;
import javax.swing.plaf.FileChooserUI;

public class GensymFileChooser extends JFileChooser {
  
  private FileView uiFileView = null;

  public GensymFileChooser() {
    super();
  }
  
  public GensymFileChooser(String currentDirectoryPath) {
    super(currentDirectoryPath);
  }

  public GensymFileChooser(File currentDirectory) {
    super(currentDirectory);
  }

  public GensymFileChooser(FileSystemView fsv) {
    super(fsv);
  }

  public GensymFileChooser(File currentDirectory, FileSystemView fsv) {
    super(currentDirectory, fsv);
  }

  public GensymFileChooser(String currentDirectoryPath, FileSystemView fsv) {
    super(currentDirectoryPath, fsv);
  }
  
    @Override
    public String getName(File file) {
	return file.getName();
    }

  @Override
  public void updateUI() {
    FileChooserUI ui;
    if (SystemUtilities.isWindowsPlatform())
      ui = ((FileChooserUI)UIManager.getUI(this));
    else
      ui = new GensymMotifFileChooserUI(this);
    setUI(ui);
    
    uiFileView = getUI().getFileView(this);
    if(isAcceptAllFileFilterUsed()) {
      addChoosableFileFilter(getAcceptAllFileFilter());
    }
  }  
}

