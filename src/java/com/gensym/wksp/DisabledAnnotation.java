package com.gensym.wksp;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import javax.swing.JLabel;
import javax.swing.ImageIcon;

/**
 * @undocumented
 */

class DisabledAnnotation extends JLabel {

  static ImageIcon image = new ImageIcon(Toolkit.getDefaultToolkit().getImage(DisabledAnnotation.class.getResource("disabled.gif")));

  DisabledAnnotation () {
    super(image);
    setVisible(true);
  }
//  public Dimension getPreferredSize(

  @Override
  public void paint(Graphics g) {
    image.paintIcon(this, g, 0, 0);
  }
  
}
  
  
