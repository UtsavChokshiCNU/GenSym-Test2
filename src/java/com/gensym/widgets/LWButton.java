/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   LWButton.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.AWTEventMulticaster;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;

import com.gensym.uiutil.UIHeartBeat;
import com.gensym.uiutil.UIHeartBeatRecipient;

/**
 * A lightweight button class that can repeat if held down.
 */
public class LWButton extends Container 
implements MouseListener, UIHeartBeatRecipient {

  static final long serialVersionUID = 1370727509995435694L;

  public static int REPEAT_WAIT = 1000;
  public static int REPEAT_INTERVAL = 250;

  private int repeatWait = REPEAT_WAIT;

  public int getRepeatWait(){
      return repeatWait;
  }

  public void setRepeatWait(int repeatWait){
    this.repeatWait = repeatWait;
  }

  private int repeatInterval = REPEAT_INTERVAL;

  public int getRepeatInterval(){
      return repeatInterval;
  }

  public void setRepeatInterval(int repeatInterval){
    this.repeatInterval = repeatInterval;
  }

  public LWButton() {
    addMouseListener(this);
  }

  private ActionListener actionListener;

  public void addActionListener(ActionListener l) {
    actionListener = AWTEventMulticaster.add(actionListener, l);
  }

  public void removeActionListener(ActionListener l) {
    actionListener = AWTEventMulticaster.remove(actionListener, l);
  }

  private void dispatchActionEvent() {
    if (actionListener != null)
      actionListener.actionPerformed(new ActionEvent(this,
						     ActionEvent.ACTION_PERFORMED,
						     "Action"));
  }

  @Override
  public void dub() {
    dispatchActionEvent();
  }

  private boolean armed;

  public boolean isArmed(){
      return armed;
  }

  private boolean pressed;

  public boolean isPressed(){
      return pressed;
  }

  @Override
  public void mouseClicked(MouseEvent e) {
//     dispatchActionEvent();
  }

  @Override
  public void mousePressed(MouseEvent e) {
    if (isEnabled()) {
      armed = pressed = true;
      UIHeartBeat.registerForUIHeartBeat(this, repeatWait, repeatInterval);
      repaint();
    }
  }
  
  @Override
  public void mouseReleased(MouseEvent e){
    boolean wasArmed = armed;
    boolean wasPressed = pressed;
    armed = false;
    pressed = false;
    if(wasPressed) {
      UIHeartBeat.unregisterForUIHeartBeat(this);
      repaint();
      dispatchActionEvent();
    }
  }

  @Override
  public void mouseEntered(MouseEvent e){
    if(armed) {
      pressed = true;
      UIHeartBeat.registerForUIHeartBeat(this, repeatWait, repeatInterval);
      repaint();
    }
  }

  @Override
  public void mouseExited(MouseEvent e){
    pressed = false;
    if (armed) {
      UIHeartBeat.unregisterForUIHeartBeat(this);
      repaint();
    }
  }

  @Override
  public void update(Graphics g) {
    paint(g);
  }

  // private final Object colorLock;

  // A stub paint method
  @Override
  public void paint(Graphics g) {
    super.paint(g);

    Dimension size = getSize();
    int width = size.width;
    int height = size.height;

    Color topLeftOuter = pressed ? Color.black : Color.white;
    Color topLeftInner = pressed ? Color.gray : Color.lightGray;
    Color bottomRightInner = pressed ? Color.lightGray : Color.gray;
    Color bottomRightOuter = pressed ? Color.white : Color.black;

    g.setColor(topLeftOuter);
    g.drawLine(0, 0, 0, height - 1);
    g.drawLine(0, 0, width - 1, 0);

    g.setColor(topLeftInner);
    g.drawLine(1, 1, 1, height - 2);
    g.drawLine(1, 1, width - 2, 1);

    int y = height - 2;
    int x = width - 2;
    g.setColor(bottomRightInner);
    g.drawLine(x, 1, x, y);
    g.drawLine(1, y, x, y);

    y = height - 1;
    x = width - 1;
    g.setColor(bottomRightOuter);
    g.drawLine(x, 0, x, y);
    g.drawLine(0, y, x, y);

  }    
}
