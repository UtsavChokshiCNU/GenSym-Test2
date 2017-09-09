package com.gensym.uitools.utils;

import java.awt.Toolkit;
import java.awt.Graphics;
import java.awt.Insets;
import javax.swing.JButton;
import javax.swing.ImageIcon;

public class HideButton extends JButton {
  static ImageIcon hideIcon =
  new ImageIcon(Toolkit.getDefaultToolkit().getImage(HideButton.class.getResource("hide.gif")));
  
    public HideButton() {
      super(hideIcon);
      setRolloverEnabled(true);
      setMargin(new Insets(1,2,2,2));
      //setPreferredSize(new Dimension(16,16));
    }
    @Override
    protected void paintBorder(Graphics g) {
      if (getModel().isRollover() || getModel().isPressed())
	super.paintBorder(g);
    }
}
