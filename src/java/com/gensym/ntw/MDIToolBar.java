package com.gensym.ntw;

import java.awt.BorderLayout;
import java.awt.Choice;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Label;
import java.awt.Panel;
import java.awt.Toolkit;

import com.gensym.core.GensymApplication;
import com.gensym.util.GensymLogo;

import gjt.ImageButton;

public class MDIToolBar extends Panel {
  public Choice liveXns = new Choice ();
  public Choice userModes = new Choice ();
  public GensymLogo logo = new GensymLogo ();
  // public ToolBarPanel tbMain = new ToolBarPanel();
  public Panel tbMain = new Panel();

  private static Insets stdTBInsets = new Insets (3, 5, 0, 10);
  // static LayoutManager stdLayoutMgr = new RowLayout (Orientation.RIGHT, Orientation.CENTER, 4);
  private Panel eastPanel = new Panel();

  @Override
  public Insets insets () {
    return stdTBInsets;
  }

  @Override
  public void paint (Graphics g) {
    int width = getSize ().width;
    g.setColor (Color.gray);
    g.drawLine (0, 0, width, 0);
    g.setColor (Color.white);
    g.drawLine (0, 1, width, 1);
  }

  private void addImageToToolbar(Toolkit toolkit, String imageName,
				 String label) {
    Image image;
    ImageButton imageButton;
    String imageLocation;

    if (imageName == null)
      imageButton = new ImageButton();
    else {
      imageLocation = GensymApplication.locateImageFile(imageName);
      if (imageLocation != null)
	image = toolkit.getImage(imageLocation);
      else
	image = toolkit.getImage(imageName);
      imageButton = new ImageButton(image);
    }
    tbMain.add(imageButton);
  }



  public MDIToolBar () {
    String imageLocation;
    setBackground (Color.lightGray);
    setLayout (new BorderLayout());
    eastPanel.setLayout (new FlowLayout());
    add (eastPanel, "East");

    Toolkit tk = Toolkit.getDefaultToolkit();
    tbMain.setLayout (new FlowLayout());
    addImageToToolbar(tk, "tb_main_open.gif",  "Open KB");
    addImageToToolbar(tk, "tb_main_save.gif",  "Save KB");
    addImageToToolbar(tk, "tb_main_undo.gif",  "Undo");
    addImageToToolbar(tk, "tb_main_cut.gif",   "Cut");
    addImageToToolbar(tk, "tb_main_copy.gif",  "Copy");
    addImageToToolbar(tk, "tb_main_paste.gif", "Paste");
    addImageToToolbar(tk, "tb_main_help.gif",  "Help");
    add (tbMain, "West");

    liveXns.addItem ("machine port Xn#");
    liveXns.select (0);
    eastPanel.add (liveXns);

    eastPanel.add (new Label ("   "));

    userModes.addItem ("administrator");
    userModes.addItem ("developer");
    userModes.addItem ("user");
    userModes.addItem ("browser");
    userModes.select (0);
    eastPanel.add (userModes);

    eastPanel.add (new Label (""));
    logo.start();
    eastPanel.add (logo);
    // Hack
    com.gensym.ntw.Telewindows.registerActivityDisplay ((com.gensym.util.ActivityDisplay)logo);
  }

}