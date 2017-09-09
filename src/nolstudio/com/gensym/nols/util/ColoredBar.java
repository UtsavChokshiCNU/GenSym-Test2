package com.gensym.nols.util;

import java.awt.*;
import java.io.*;

import javax.swing.*;

public class ColoredBar extends JComponent implements Icon, Cloneable, Serializable {

	Color color;
	double value;
	int flag; // 0:two sides; 1:positive side; -1:nagtive size.
	boolean isComponent;
	
	public ColoredBar(Color c, boolean com, double value, int flag) {	
		this.color = c;
		this.value = value;
		this.flag = flag;
		isComponent = com;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		ColoredBar cloned = (ColoredBar) super.clone();
		if(color != null){
			float[] hsb = Color.RGBtoHSB(color.getRed(), color.getGreen(), color.getBlue(), null);
			cloned.color = color == null ? null : Color.getHSBColor(hsb[0], hsb[1], hsb[2]);
		}
		
		return cloned;
	}

	public void setShowColor(Color c) {
		this.color = c;
	}
	
	public void setValue(double value) {
		this.value = value;
	}

	public double getValue() {
		return value;
	}
	
	public void setFlag(int flag) {
		this.flag = flag;
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Dimension dim = getSize();
		if(isComponent){			
			Color oldColor = g.getColor();
			g.setColor(color);
			if(flag == -1){
				double start = dim.width*(1+value);
				double length = -dim.width*value; 
				g.fillRect((int)start,0,(int)length, dim.height);
			}else if(flag == 1){
				double end = dim.width*value;
				g.fillRect(0,0,(int)end, dim.height);
			}else{
				g.drawLine(dim.width/2,0,dim.width/2, dim.height);
				if(value >= 0){
					double length = dim.width*value/2.0; 
					g.fillRect(dim.width/2,0,(int)length, dim.height);
				}else{
					double start = dim.width*(1+value)/2.0;
					double length = -dim.width*value/2.0; 
					g.fillRect((int)start,0,(int)length, dim.height);
				}
			}
			g.setColor(oldColor);
		}
	}

	@Override
	public void paintIcon(Component c, Graphics g, int x, int y) {
		Dimension dim = getSize();
//		g.setColor(Color.white);
//		g.fillRect(0,0,dim.width, dim.height);
		if(isComponent){			
			Color oldColor = g.getColor();
			g.setColor(color);
			if(flag == -1){
				double start = dim.width*(1+value);
				double length = -dim.width*value; 
				g.fillRect((int)start,0,(int)length, dim.height);
			}else if(flag == 1){
				double end = dim.width*value;
				g.fillRect(0,0,(int)end, dim.height);
			}else{
				if(value >= 0){
					double length = dim.width*value/2.0; 
					g.fillRect(dim.width/2,0,(int)length, dim.height);
//					System.out.println("paintComponent dim.width = "+dim.width);
//					System.out.println("paintComponent value = "+value);
//					System.out.println("paintComponent length = "+length);
				}else{
					double start = dim.width*(1+value)/2.0;
					double length = -dim.width*value/2.0; 
					g.fillRect((int)start,0,(int)length, dim.height);
//					System.out.println("paintComponent dim.width = "+dim.width);
//					System.out.println("paintComponent value = "+value);
//					System.out.println("paintComponent start = "+start);
//					System.out.println("paintComponent length = "+length);
				}
			}
			g.setColor(oldColor);
		}
	}

	@Override
	public int getIconWidth() { return 12; }
	@Override
	public int getIconHeight() { return 12; }

}
