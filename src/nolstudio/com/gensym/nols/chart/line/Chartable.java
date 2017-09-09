package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;

public interface Chartable {
	public int getDragBehavior();
	public Rectangle getSelectionBoxConstraints();  // used when dragging creates selection box
	public int getSelectionBoxStyle();
	public int getSelectionBoxBehavior();
}
