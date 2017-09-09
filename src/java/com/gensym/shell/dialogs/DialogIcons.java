/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DialogIcons.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Image;
import java.awt.Toolkit;

import javax.swing.ImageIcon;

public class DialogIcons {

  public static Image newImage = Toolkit.getDefaultToolkit().getImage(DialogIcons.class.getResource("new.gif"));
  public static ImageIcon newIcon = new ImageIcon(newImage);

  public static Image openImage = Toolkit.getDefaultToolkit().getImage(DialogIcons.class.getResource("open.gif"));
  public static ImageIcon openIcon = new ImageIcon(openImage);

  public static Image saveImage = Toolkit.getDefaultToolkit().getImage(DialogIcons.class.getResource("save.gif"));
  public static ImageIcon saveIcon = new ImageIcon(saveImage);
}
