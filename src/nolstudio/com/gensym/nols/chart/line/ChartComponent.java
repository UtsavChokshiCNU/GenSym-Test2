package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;
import javax.swing.*;

public class ChartComponent extends JComponent implements Chartable {
	public Chart itsChart;
	private int dragBehavior;
	private int selectionBoxStyle;
	private int selectionBoxBehavior;

	ChartComponent() {
		super();
		itsChart = null;
		setVisible(true);
		dragBehavior = Chart.DRAG_DOES_NOTHING;  // default
		selectionBoxStyle = Chart.OUTLINE_STYLE;  // default
		selectionBoxBehavior = Chart.BOX_BEHAVIOR;  //default
	}

	@Override
	public int getDragBehavior() {
		return dragBehavior;
	}

	public void setDragBehavior(int drag) {
		dragBehavior = drag;
	}

	@Override
	public Rectangle getSelectionBoxConstraints() {
		return itsChart.getVisiblePortion(this);  // reasonable default 
	}

	public void setSelectionBoxStyle(int style) {
		selectionBoxStyle = style;
	}

	@Override
	public int getSelectionBoxStyle() {
		return selectionBoxStyle;
	}

	public void setSelectionBoxBehavior(int behavior) {
		selectionBoxBehavior = behavior;
	}

	@Override
	public int getSelectionBoxBehavior() {
		return selectionBoxBehavior;
	}

	@Override
	public boolean contains(Point p) {
		// included so ChartComponents only have to implement the contains(x,y) method
		// to effectively override both methods
		return contains(p.x, p.y);
	}

//	public void update(Graphics g) {	}
}
