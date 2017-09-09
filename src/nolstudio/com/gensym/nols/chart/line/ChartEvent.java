package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;

public class ChartEvent extends MouseEvent {
	private Component subcomponentSource;
	private Rectangle selectionRectangle;
	
	ChartEvent(Chart source, MouseEvent event) {
		super(source, event.getID(), event.getWhen(), event.getModifiers(), event.getX(), event.getY(), event.getClickCount(), event.isPopupTrigger());
		subcomponentSource = (Component) event.getSource();
	}

	public Component getSubcomponentSource() {
		return subcomponentSource;
	}

	public Rectangle getSelectionRectangle() {
		return selectionRectangle;
	}

	public void setSelectionRectangle(Rectangle r) {
		selectionRectangle = r;
	}
}