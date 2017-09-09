package com.gensym.uitools.utils;

import java.util.Hashtable;
import com.gensym.ui.toolbar.ToolBar;
import javax.swing.border.BevelBorder;
import java.awt.Dimension;
import java.awt.Toolkit;
import javax.swing.ImageIcon;
import java.awt.Insets;
import javax.swing.JButton;
import javax.swing.Icon;
import java.awt.Image;
import java.awt.Component;
import java.awt.event.ActionListener;

public class IconicStatusBar extends ToolBar {
    private Hashtable components = new Hashtable();
    public IconicStatusBar() {
      setBorder(new BevelBorder(BevelBorder.LOWERED));
      setBorderPainted(true);
      setPreferredSize(new Dimension(60, 19));
      setMargin(new Insets(0,0,0,0));
    }

    public void addIcon(String name, Image image, ActionListener listener) {
      IconButton component = new IconButton(name, new ImageIcon(image));
      if (listener != null)
	component.addActionListener(listener);
      super.add(component);
      components.put(name, component);
    }
    public Component getComponent(Object name) {
      return (Component)components.get(name);
    }
}

  class IconButton extends JButton {
    private String name;
    IconButton(String name,Icon image) {
      super(image);
      setRolloverEnabled(true);
      this.name = name;
      setMargin(new Insets(0, 0, 0, 0));
      setToolTipText(name);
    }
    @Override
    public String getName() {
      return this.name;
    }
    @Override
    protected void paintBorder(java.awt.Graphics g) {
      if (getModel().isRollover() || getModel().isPressed())
	super.paintBorder(g);
    }
  }
