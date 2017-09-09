package com.gensym.draw;

import java.lang.Object;
import java.awt.*;
import java.awt.event.*;

/*
 *
 * DumbDrawTool
 *
 */
public abstract class EventHandler implements MouseListener,
  MouseMotionListener, KeyListener, ComponentListener,
  ContainerListener, FocusListener {

  protected static final int MOUSELISTENER       = 1,
                             MOUSEMOTIONLISTENER = 2,
			     KEYLISTENER         = 4,
			     FOCUSLISTENER       = 8,
			     COMPONENTLISTENER   = 16,
			     CONTAINERLISTENER   = 32;

  protected int listenerTypes = 0;
  private static final java.io.PrintStream o = System.out;

  public void registerListeners (PersistentCanvas c) {
    if ((listenerTypes & MOUSELISTENER) != 0)
      c.addMouseListener (this);
    if ((listenerTypes & MOUSEMOTIONLISTENER) != 0)
      c.addMouseMotionListener (this);
    if ((listenerTypes & KEYLISTENER) != 0)
      c.addKeyListener (this);
    if ((listenerTypes & FOCUSLISTENER) != 0)
      c.addFocusListener (this);
    if ((listenerTypes & COMPONENTLISTENER) != 0)
      c.addComponentListener (this);
    if ((listenerTypes & CONTAINERLISTENER) != 0)
      c.addContainerListener (this);
    /*
    if ((listenerTypes & MOUSELISTENER) != 0)
      o.println ("Registered Canvas as MouseListener");
    if ((listenerTypes & MOUSEMOTIONLISTENER) != 0)
      o.println ("Registered Canvas as MouseMotionListener");
    if ((listenerTypes & KEYLISTENER) != 0)
      o.println ("Registered Canvas as KeyListener");
    if ((listenerTypes & FOCUSLISTENER) != 0)
      o.println ("Registered Canvas as FocusListener");
    if ((listenerTypes & COMPONENTLISTENER) != 0)
      o.println ("Registered Canvas as ComponentListener");
      */
  }

  public void deregisterListeners (PersistentCanvas c) {
    if ((listenerTypes & MOUSELISTENER) != 0)
      c.removeMouseListener (this);
    if ((listenerTypes & MOUSEMOTIONLISTENER) != 0)
      c.removeMouseMotionListener (this);
    if ((listenerTypes & KEYLISTENER) != 0)
      c.removeKeyListener (this);
    if ((listenerTypes & FOCUSLISTENER) != 0)
      c.removeFocusListener (this);
    if ((listenerTypes & COMPONENTLISTENER) != 0)
      c.removeComponentListener (this);
    if ((listenerTypes & CONTAINERLISTENER) != 0)
      c.removeContainerListener (this);
  }

  public void Draw (Graphics g) {}

  @Override
  public void componentAdded(ContainerEvent e) {}
  @Override
  public void componentRemoved(ContainerEvent e) {}
  @Override
  public void componentMoved(ComponentEvent e) {}
  @Override
  public void componentShown(ComponentEvent e) {}
  @Override
  public void componentResized(ComponentEvent e) {}
  @Override
  public void componentHidden(ComponentEvent e) {}
  @Override
  public void focusGained(FocusEvent e) {}
  @Override
  public void focusLost(FocusEvent e) {}
  @Override
  public void mouseClicked(MouseEvent e) {}
  @Override
  public void mousePressed(MouseEvent e) {}
  @Override
  public void mouseReleased(MouseEvent e) {}
  @Override
  public void mouseEntered(MouseEvent e) {}
  @Override
  public void mouseExited(MouseEvent e) {}
  @Override
  public void mouseDragged(MouseEvent e) {}
  @Override
  public void mouseMoved (MouseEvent e) {}
  @Override
  public void keyTyped(KeyEvent e) {}
  @Override
  public void keyPressed(KeyEvent e) {}
  @Override
  public void keyReleased(KeyEvent e) {}
  public void actionPerformed(ActionEvent e) {}

}
