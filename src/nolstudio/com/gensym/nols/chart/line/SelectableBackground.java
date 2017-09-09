package com.gensym.nols.chart.line;

import java.awt.*;
import java.util.*;
import java.lang.Object.*;

public class SelectableBackground extends ChartBackground {

	SelectableBackground() {
		super();
		setColor(Color.darkGray);
		setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
	}
}