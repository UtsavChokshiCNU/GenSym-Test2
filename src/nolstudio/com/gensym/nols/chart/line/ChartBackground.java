package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;
import java.lang.Math.*;

public class ChartBackground extends ChartComponent {
	private Color itsColor;

	ChartBackground() {
		super();
		itsColor = Color.lightGray;
	}

	@Override
	public boolean contains(int px, int py) {
		return true;
	}

	@Override
	public void paint(Graphics g){
		if (g instanceof PrintGraphics) {
			g.setColor(Color.white);
			Dimension bounds = getSize();
			g.fillRect(0,0, bounds.width, bounds.height);
			return;
		}
		super.paint(g);
	}
	@Override
	public void paintComponent(Graphics g) {	
		//System.out.println("painting "+getClass().getName()+", color = "+itsColor.toString());
		g.setColor(itsColor);
		Rectangle bounds = g.getClipBounds();
		g.fillRect(bounds.x, bounds.y, bounds.width, bounds.height);
	}

	public void setColor(Color color) {
		itsColor = color;
	}

	public Color getColor() {
		return itsColor;
	}
}