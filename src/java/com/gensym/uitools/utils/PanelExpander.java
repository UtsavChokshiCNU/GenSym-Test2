package com.gensym.uitools.utils;

import java.awt.Dimension;
import java.awt.Cursor;
import java.awt.Point;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import javax.swing.JComponent;
import javax.swing.JPanel;

public class PanelExpander extends JComponent
  implements MouseListener, MouseMotionListener{
  private boolean dragging = false;
  private JPanel panel;
  private int lastPosition;
  private boolean vertical;
  
  public PanelExpander(JPanel panel, boolean vertical) {
    this.panel = panel;
    this.vertical = vertical;
    if (vertical)
      setPreferredSize(new Dimension(2,200));
    else setPreferredSize(new Dimension(200, 2));
    addMouseListener(this);
    addMouseMotionListener(this);
  }
  @Override
  public void mouseDragged(MouseEvent e) {
    int newPosition = 0;
    int oldY = (int)panel.getLocation().getY();
    if (vertical) {
      panel.setCursor(Cursor.getPredefinedCursor(Cursor.E_RESIZE_CURSOR));
      newPosition = e.getX();
    } else {
      panel.setCursor(Cursor.getPredefinedCursor(Cursor.N_RESIZE_CURSOR));
      newPosition = e.getY();
    }
    int delta = newPosition - lastPosition;
    Dimension size = panel.getSize();
    if (vertical)
      size.width+=delta;
    else {
      size.height-=delta;
      panel.setLocation(new Point(0, oldY+delta));
    }
    panel.setSize(size);
    panel.repaint();
    lastPosition = newPosition;      
  }
  @Override
  public void mouseMoved(MouseEvent e) {
  }
  @Override
  public void mouseClicked(MouseEvent e) {
  }
  @Override
  public void mouseEntered(MouseEvent e) {
    if (vertical)
      panel.setCursor(Cursor.getPredefinedCursor(Cursor.E_RESIZE_CURSOR));
    else panel.setCursor(Cursor.getPredefinedCursor(Cursor.N_RESIZE_CURSOR));
  }
  @Override
  public void mouseExited(MouseEvent e) {
    panel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));      
  }
  @Override
  public void mousePressed(MouseEvent e) {
    dragging = true;
    if (vertical)
      lastPosition = e.getX();
    else lastPosition = e.getY();
  }
  @Override
  public void mouseReleased(MouseEvent e) {
    dragging = false;
    panel.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    panel.setPreferredSize(panel.getSize());
    panel.getParent().validate();
  }
}
