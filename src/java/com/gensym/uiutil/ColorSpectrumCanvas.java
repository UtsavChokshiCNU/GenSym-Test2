package com.gensym.uiutil;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.TextField;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class ColorSpectrumCanvas extends Canvas implements MouseListener {
  private float hue;
  private float sat;
  private int brightness;
  private int width;
  private TextField bTextField;

  public ColorSpectrumCanvas(int w) {
    this.addMouseListener(this);
    width = w;
  }

  public void init() {
  }

  public void setColor(float h, float s) {
    hue = h;
    sat = s;
    repaint();
  }

  public int getBrightness() {
    return brightness;
  }

  public void setBrightness(int br) {
    brightness = br;
  }

  public void addEventSource(TextField tx) {
    bTextField = tx;
  }

  @Override
  public void paint(Graphics gr) {
    int xPos = 0;
    int yPos = 0;
    Color c;

    for (int i=0; i<256; i++) {
      c = Color.getHSBColor(hue,sat,((float)i)/255f);
      gr.setColor(c);
      gr.drawRect(xPos,yPos,width, 1);
      gr.fillRect(xPos,yPos,width, 1);
      yPos++;
    }
  }

  @Override
  public void update (Graphics g) {
    paint(g);
  }

  @Override
  public void mouseClicked(MouseEvent e) {
    brightness = e.getY();
    bTextField.setText("" + brightness);
  }

  @Override
  public void mousePressed(MouseEvent e) {}
  @Override
  public void mouseEntered(MouseEvent e) {}
  @Override
  public void mouseExited(MouseEvent e) {}
  @Override
  public void mouseReleased(MouseEvent e) {}
}
