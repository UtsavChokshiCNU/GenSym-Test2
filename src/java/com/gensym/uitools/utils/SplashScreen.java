package com.gensym.uitools.utils;

import java.awt.Window;
import java.awt.Image;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.awt.Graphics;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.Color;
import javax.swing.border.Border;

public class SplashScreen extends Window implements MouseListener{
  private Image splashImage;
  private boolean imgDone = false;
  private Border border;

  public SplashScreen(Image splashImage,
		      int imageWidth, int imageHeight) {
    super (new Frame());
    addMouseListener(this);
    setBackground (Color.black);
    setSize(imageWidth, imageHeight);
    this.splashImage = splashImage;
    prepareImage (splashImage, this);
    try {
      Thread.sleep(500);
    } catch (InterruptedException ie) {}
    imgDone = true;
  }

  @Override
  public Insets getInsets() {
    if (border != null)
      return border.getBorderInsets(this);
    else
      return super.getInsets();
  }
  
  public void setBorder(Border border) {
    this.border = border;
  }
  
  @Override
  public void mouseClicked(MouseEvent me) {
    setVisible(false);
  }
  public void mouse(MouseEvent me) {}
  @Override
  public void mouseEntered(MouseEvent me) {}
  @Override
  public void mouseExited(MouseEvent me) {}
  @Override
  public void mousePressed(MouseEvent me) {}
  @Override
  public void mouseReleased(MouseEvent me) {}        
  @Override
  public void paint (Graphics g) {
    if (!imgDone)
      return;
    g.drawImage (splashImage, 0, 0, null);
    super.paint(g);
    if (border != null) {
      border.paintBorder(this, g, 0, 0, getWidth(), getHeight());
    }
  }
}

