package com.gensym.nols.chart.line;

import java.awt.*;

public class MarkerFormat {
	
	public static final int SQUARE = 0;
	public static final int DIAMOND = 1;
	public static final int CIRCLE = 2;
	public static final int TRIANGLE = 3;
	public static final int X = 4;
	public static final int CROSS = 5;
	public static final int STAR = 6;
	
	public int markerType;
	private Color foregroundColor;		 // refers to ColorMap colors
	private Color backgroundColor;
	private int foregroundSize;
	private int backgroundSize;
	private int halfFS;
	private int halfBS;
	private int xcorners[];
	private int ycorners[];

	public MarkerFormat() {
		super();
		xcorners = new int[4];
		ycorners = new int[4];
		markerType = MarkerFormat.SQUARE;
		foregroundColor = Color.green;
		backgroundColor = null;
		foregroundSize = 6;
		backgroundSize = 10;
		halfFS = 3;
		halfBS = 5;
	}

	public MarkerFormat(int markerType, Color foregroundColor, Color backgroundColor, int foregroundSize, int backgroundSize) {
		this();
		this.markerType = markerType;
		this.foregroundColor = foregroundColor;
		this.backgroundColor = backgroundColor;
		this.foregroundSize = foregroundSize;
		this.backgroundSize = backgroundSize;
		halfFS = foregroundSize/2;
		halfBS = backgroundSize/2;
	}

	public void setForegroundSize(int s) {
		if (s < 0) {
			foregroundSize = 0;  // don't let negative size slip by
		} else {
			foregroundSize = s;
		}
		halfFS = foregroundSize/2;
	}

	public int getForegroundSize() {
		return foregroundSize;
	}

	public void setBackgroundSize(int s) {
 		if (s < 0) {
 			backgroundSize = 0;  // don't let negative size slip by
 		}else {
 			backgroundSize = s;
 		}
		halfBS = backgroundSize/2;
	}

	public int getBackgroundSize() {
		return backgroundSize;
	}

	public void setForegroundColor(Color color) {
		foregroundColor = color;
	}

	public Color getForegroundColor() {
		return foregroundColor;
	}

	public void setBackgroundColor(Color color) {
		backgroundColor = color;
	}

	public Color getBackgroundColor() {
		return backgroundColor;
	}
/*	private void calculateSelectSize() {
		// this is based on "what looks good" in my judgment
		if (markerSize <= 1) selectSize = 3;
		else if (markerSize == 2) selectSize = 4;
		else if (markerSize == 3) selectSize = 6;
		else selectSize = markerSize + 4;
	}	 */

	public int getMarkerSize() {
		return Math.max(foregroundSize, backgroundSize);
	}

	public Color drawMarker(Graphics g, int x, int y, Color currentColor) {
		Color color = currentColor;
		if (backgroundSize > 0 && backgroundColor != null) {
			if (!backgroundColor.equals(color)) {
				g.setColor(backgroundColor);
				color = backgroundColor;
			}
			g.drawRect(x-halfBS, y-halfBS, backgroundSize, backgroundSize);
		}
		if (foregroundSize > 0 && foregroundColor != null) {
			int d = foregroundSize;
			int r = halfFS;
			if (!foregroundColor.equals(color)) {
				g.setColor(foregroundColor);
				color = foregroundColor;
			}
			switch(markerType) {
			case 0:  // square
				g.fillRect(x-r, y-r, d, d);
				break;
			case 1:  // diamond
				xcorners[0] = x-r;
				xcorners[1] = x;
				xcorners[2] = x+r;
				xcorners[3] = x;
				ycorners[0] = y;
				ycorners[1] = y-r;
				ycorners[2] = y;
				ycorners[3] = y+r;
				g.fillPolygon(xcorners, ycorners, 4);
				break;
			case 2: // circle
				g.fillOval(x-r, y-r, d, d);
				break;
			case 3:  // triangle
				xcorners[0] = x-r;
				xcorners[1] = x;
				xcorners[2] = x+r;
				ycorners[0] = y+r;
				ycorners[1] = y-r;
				ycorners[2] = ycorners[0];
				g.fillPolygon(xcorners, ycorners, 3);
				break; 
			case 4: // X
				g.drawLine(x-r, y+r, x+r, y-r);
				g.drawLine(x-r, y-r, x+r, y+r);
				break;
			case 5: // cross
				g.drawLine(x-r, y, x+r, y);
				g.drawLine(x, y-r, x, y+r);
				break;
			default: // star
				g.drawLine(x-r, y+r, x+r, y-r);
				g.drawLine(x-r, y-r, x+r, y+r);
				g.drawLine(x, y-r, x, y+r);
				break;
			}
		}
		return color;
	}

/* not used
	public void drawMarkers(Graphics g, int[] x, int[] y, int n) {
		if (backgroundSize > 0 && backgroundColor != -1) {
			int d = backgroundSize;
			int r = halfBS;
			g.setColor(ColorMap.colors[backgroundColor]);
			for (int i=0; i < n; ++i) {
				g.drawRect(x[i]-r, y[i]-r, d, d);
			}
		}
		if (foregroundSize > 0 && foregroundColor != -1) {
			int d = foregroundSize;
			int r = halfFS;
			g.setColor(ColorMap.colors[foregroundColor]);	
			switch(markerType) {
			case 0:  // square
				for (int i=0; i < n; ++i) g.fillRect(x[i]-r, y[i]-r, d, d);
				break;
			case 1:  // diamond
				for (int i=0; i < n; ++i) {
					xcorners[0] = x[i]-r;
					xcorners[1] = x[i];
					xcorners[2] = x[i]+r;
					xcorners[3] = x[i];
					ycorners[0] = y[i];
					ycorners[1] = y[i]-r;
					ycorners[2] = y[i];
					ycorners[3] = y[i]+r;
					g.fillPolygon(xcorners, ycorners, 4);
				}
				break;
			case 2: // circle
				for (int i=0; i < n; ++i) g.fillOval(x[i]-r, y[i]-r, d, d);
				break;
			case 3:  // triangle
				for (int i=0; i < n; ++i) {
					xcorners[0] = x[i]-r;
					xcorners[1] = x[i];
					xcorners[2] = x[i]+r;
					ycorners[0] = y[i]+r;
					ycorners[1] = y[i]-r;
					ycorners[2] = ycorners[0];
					g.fillPolygon(xcorners, ycorners, 3);
				}
				break; 
			case 4: // X
				for (int i=0; i < n; ++i) {
					g.drawLine(x[i]-r, y[i]+r, x[i]+r, y[i]-r);
					g.drawLine(x[i]-r, y[i]-r, x[i]+r, y[i]+r);
				}
				break;
			case 5: // cross
				for (int i=0; i < n; ++i) {
					g.drawLine(x[i]-r, y[i], x[i]+r, y[i]);
					g.drawLine(x[i], y[i]-r, x[i], y[i]+r);
				}
				break;
			default: // star
				for (int i=0; i < n; ++i) {
					g.drawLine(x[i]-r, y[i]+r, x[i]+r, y[i]-r);
					g.drawLine(x[i]-r, y[i]-r, x[i]+r, y[i]+r);
					g.drawLine(x[i], y[i]-r, x[i], y[i]+r);
				}
				break;
			}
		}
	} */
}
