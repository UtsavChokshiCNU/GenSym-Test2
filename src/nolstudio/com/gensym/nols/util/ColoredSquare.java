package com.gensym.nols.util;

import java.awt.*;
import java.io.*;

import javax.swing.*;

public class ColoredSquare extends JComponent implements Icon, Cloneable, Serializable {

	Color color;
	boolean isComponent;
	
	public ColoredSquare(Color c) {
		this.color = c;
		isComponent = false;
	}

	public ColoredSquare(Color c, boolean com) {	
		this.color = c;
		isComponent = com;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		ColoredSquare cloned = (ColoredSquare) super.clone();
		if(color != null){
			float[] hsb = Color.RGBtoHSB(color.getRed(), color.getGreen(), color.getBlue(), null);
			cloned.color = color == null ? null : Color.getHSBColor(hsb[0], hsb[1], hsb[2]);
		}
		
		return cloned;
	}
	
	public void setShowColor(Color c) {
		this.color = c;
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		if(isComponent){
			Color oldColor = g.getColor();
			g.setColor(color);
			g.fill3DRect(0,0,getSize().width, getSize().height, true);
			g.setColor(oldColor);
		}
	}

	@Override
	public void paintIcon(Component c, Graphics g, int x, int y) {
		if(!isComponent){
			Color oldColor = g.getColor();
			g.setColor(color);
			g.fill3DRect(x,y,getIconWidth(), getIconHeight(), true);
			g.setColor(oldColor);
		}
	}
	@Override
	public int getIconWidth() { return 12; }
	@Override
	public int getIconHeight() { return 12; }
}
