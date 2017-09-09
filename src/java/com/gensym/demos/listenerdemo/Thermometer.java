package com.gensym.demos.listenerdemo;

import java.awt.*;

public class Thermometer extends Component{
  private static int borderWidth = 4;
  private int min = 0;
  private int max = 100;
  private int increment = 5;
  private double temperature = 0.0;
  private String label = "";

  public Thermometer(){
  }

  public Thermometer(int min, int max, int increment, double temperature){
    this.min = min;
    this.max = max;
    this.increment = increment;
    this.temperature = temperature;
  }

  public int getMin(){
    return min;
  }

  public void setMin(int min){
    this.min = min;
  }

  public int getMax(){
    return max;
  }

  public void setMax(int max){
    this.max = max;
  }

  public int getIncrement(){
    return increment;
  }

  public void setIncrement(int increment){
    this.increment = increment;
  }

  public double getTemperature(){
    return temperature;
  }

  public void setTemperature(double temp){
    temperature = temp;
    repaint();
  }

  public String getLabel(){
    return label;
  }

  public void setLabel(String label){
    this.label = label;
  }

  @Override
  public Dimension getPreferredSize() {
    return new Dimension(100, 180);
  }
  

  @Override
  public Dimension getMinimumSize() {
    return getPreferredSize();
  }

  @Override
  public void paint(Graphics g){
    int width = getSize().width;
    int height = getSize().height;
    //background panel
    g.setColor(Color.white);
    g.fillPolygon(new Polygon(new int[]{0, width, width - borderWidth, borderWidth, borderWidth, 0}, new int[]{0, 0, borderWidth, borderWidth, height - borderWidth, height}, 6));
    g.setColor(Color.gray);
    g.fillPolygon(new Polygon(new int[]{0, borderWidth, width - borderWidth, width - borderWidth, width, width}, new int[]{height, height - borderWidth, height - borderWidth, borderWidth, 0, height}, 6));
    g.setColor(Color.black);
    g.drawRect(0, 0, width, height);
    g.setColor(Color.lightGray);    
    g.fillRect(borderWidth, borderWidth, width - 2 * borderWidth, height - 2 * borderWidth);


    int thermWidth = 10;  //could be calculated
    int thermHeight = 100;  //could be calculated
    int thermX = (int)(0.4 * width);
    int thermY = 20;

    //mercury
    g.setColor(Color.white);
    g.fillRoundRect(thermX, thermY, thermWidth, thermHeight, 4, 4);
    g.setColor(Color.red);
    g.fillOval(thermX - 5, thermY + thermHeight - 2, 2 * thermWidth, 2 * thermWidth);
    if (temperature >= max) {
      g.fillRoundRect(thermX, thermY, thermWidth, thermHeight, 4, 4);
      g.setColor(Color.white);
      g.drawLine(thermX + 2, thermY, thermX + 2, thermY + thermHeight - 4);
      g.drawArc(thermX - 3, thermY + thermHeight, 2 * thermWidth - 4, 2 * thermWidth - 2, -280, 85); 
    }
    else {
      int h = (int)((thermHeight * temperature)/max);
      g.fillRect(thermX, thermY + thermHeight - h, thermWidth, h);
      g.setColor(Color.white);
      if (temperature > 1.0) g.drawLine(thermX + 2, thermY + thermHeight - h, thermX + 2, thermY + thermHeight - 4);
      g.drawArc(thermX - 3, thermY + thermHeight, 2 * thermWidth - 4, 2 * thermWidth - 2, -280, 85); 
    }  

    //labels and ticks
    g.setColor(Color.black);
    int label = max;
    int y = thermY;
    int x = thermX + thermWidth + 3;
    int i = 0;
    int yIncrement = thermHeight/((max - min)/increment);
    while (label >= min) {
      if ((i % 2) == 0){
	g.drawLine(x, y, x + 4, y);
	if ((i % 4) == 0) {
	  g.drawString(Integer.toString(label), x + 6, y + 5);
	  label = label - 4 * increment;
	}
      }
      else g.drawLine(x, y, x + 2, y);
      y = y + yIncrement;
      i++;
    }

    int labelLength = g.getFontMetrics().stringWidth(this.label);
    g.drawString(this.label, thermX + (thermWidth/2)-(labelLength/2), height - borderWidth - 10);
  }

  @Override
  public void update(Graphics g){
    paint(g);
  }

}
