package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.*;

public class LineFormat {
	public Color lineColor;
	public int lineWidth;  // currently not implemented

	public LineFormat () {
		super ();
		lineColor = null;
		lineWidth = 1;
	}

	public LineFormat (Color color, int width) {
		super();
		lineColor = color;
		lineWidth = width;
	}

	public void setColor (Color color) {
		lineColor = color;
	}  	 //Gchen add 2/23/99


	public static void drawDottedLine(Graphics g, int x1, int y1, int x2, int y2, int spacing) {
		double dist = Math.sqrt(((double)(x2 - x1))*(x2 - x1) + (y1 - y2)*(y1 - y2));
		double nDots = dist/(spacing + 1);
		for(int i=0; i<(int) Math.floor(nDots); ++i) {
			g.fillRect((int) Math.rint(x1 + i*(x2 - x1)/nDots), (int) Math.rint(x2 + i*(y2 - y1)/nDots), 1, 1);
		}
	}

}