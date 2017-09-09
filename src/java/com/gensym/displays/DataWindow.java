package com.gensym.displays;

import java.awt.*;
import java.util.*;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.*;

/** The window that draws the plot values
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class DataWindow extends Object
implements DynamicShape {
  /** 20 */
  public static final int DEFAULT_MINIMUM_HEIGHT = 20;
  /** 20 */
  public static final int DEFAULT_MINIMUM_WIDTH = 20;

  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays", DataWindow.class);

  private Dimension minimumSize;
  private Dimension size;
  private Point location = new Point();
  // from G2
  private boolean needsFormatting = true;
  // NOTE valid has to do with whether the visible drawing reflects
  // the current state of the object. invalidElement implies the state
  // itself is wrong or unknown (perhaps due to the source of data
  // having communication problems).
  private boolean valid = false;
  private boolean invalidElement = false;
  private Rectangle boundsRect = new Rectangle();

  // fix this: normal awt stuff should make this unnecessary, but
  // it doesn't seem to be right now
  private Vector chartPaths = new Vector();
  //  private TimeLabels timeLabels;
  TrendChart chart;
  private boolean configured = false;
  private Color backgroundColor;
  private Color borderColor;
  boolean borderVisible;

  /** NOTE: incomplete: the plots and axes will be included
  * @param minSize if this is null, the DataWindow class will choose. */
  public DataWindow(// TrendChart chart,
		    Dimension initialSize,
		    Dimension minSize) {
    size = initialSize;
    setBounds(0, 0, size.width, size.height);
    minimumSize = (minSize == null
		   ? new Dimension(DEFAULT_MINIMUM_WIDTH,
				   DEFAULT_MINIMUM_HEIGHT)
		   : minSize);
  }

  /** fix this: quick fix to get chart to initialize correctly.
   * should only be used in the constructor for DataAndLabelWindow.
   * It is not kept up-to-date.
   */
  Color getBackgroundColor() {
    return backgroundColor;
  }

  /** fix this: quick fix to get chart to initialize correctly.
   * should only be used in the constructor for DataAndLabelWindow.
   * It is not kept up-to-date.
   */
  Color getBorderColor() {
    return borderColor;
  }

  @Override
  public Dimension formatShape() throws UnableToFormatException{
    Trace.send(10, traceKey, i18nTrace, "dwFormatShape1",
	       new Boolean(needsFormatting));
    if (!needsFormatting)
      return size;
    else
      return formatShape(size, size, true);
  }

  @Override
  public Dimension formatShape(Dimension preferredSize,
			  Dimension maxSize, boolean growVerticallyFirst)
  throws UnableToFormatException {
    Trace.send(10, traceKey, i18nTrace, "dwFormatShape2",
	       new Boolean(needsFormatting),
	       preferredSize);
    // there may be other reasons to complain in the future.
    if(maxSize.width < minimumSize.width ||
       maxSize.height < minimumSize.height)
      throw new UnableToFormatException(i18n.format("dwMaxTooSmall", maxSize,
						    minimumSize));

    size = preferredSize;
    needsFormatting = false;
    //setSize(size);
    return size;
  }

  private Component parent;
  void setParent(Component parent) {
    this.parent = parent;
  }

  /** Mimics a Component */
  public void setBounds(int x, int y, int width, int height) {
    boundsRect.x = x;
    boundsRect.y = y;
    boundsRect.width = width;
    boundsRect.height = height;
    location.x = x;
    location.y = y;
    if (!configured) {
    Trace.send(20, traceKey, i18nTrace, "dwSetBounds0", boundsRect);
    //Trace.backTrace(20, traceKey);
    configured = true;
    return;
    }
    if (getBounds().height != height) {
      for(Enumeration en = chart.getValueAxes(); en.hasMoreElements();) {
	((ValueAxis)en.nextElement()).invalidateLabels();
      }
    }
    
    //super.setBounds(x, y, width, height);
    for(Enumeration en = chartPaths.elements(); en.hasMoreElements();)
      // non-component: make the ChartPaths 1 pixel bigger, to let them paint
      // values right on the y-axis.
      ((ChartPath)en.nextElement()).setBounds(0, 0, width, height + 1);
  }

  public Dimension getMinimumSize() {
    return minimumSize;
  }

  public Component add(Component component, int index) {
    Trace.send(5, traceKey, i18nTrace, "dwadd", this, component);
    chartPaths.addElement(component);
    Rectangle bounds = getBounds();
    // non-component: make the ChartPaths 1 pixel bigger, to let them paint
    // values right on the y-axis. don't modify the bounds rectangle.
    component.setBounds(bounds.x, bounds.y, bounds.width, bounds.height + 1);
    return ((Container)parent).add(component, index);
    // non-component: if DataWindow goes back into the awt hierarchy, switch
    // back to the following
    //return super.add(component);
  }

  public Component add(Component component) {
    return add(component, -1);
  }

  public void remove(Component component) {
    chartPaths.removeElement(component);
    ((Container)parent).remove(component);
  }

  /** Exposes internally stored data (doesn't create new data structure).
   */
  Rectangle getBounds() {
    //non-component: eliminate this method when a sub-class or Component
    return boundsRect;
  }

  /** Exposes internally stored data (doesn't create new data structure).
   */
  Point getLocation() {
    return location;
  }

  Dimension getSize() {
    return new Dimension(boundsRect.width, boundsRect.height);
  }

  public void invalidate() {
    //super.invalidate();
    valid = false;
  }

  public void invalidateFormat() {
    needsFormatting = true;
  }

  public void setChart(Chart chart) {
    this.chart = (TrendChart)chart;
  }

  TrendChart getTrendChart() {
    return chart;
  }

  public void draw(Graphics g) {
    Trace.send(10, traceKey, i18nTrace, "boundsClip",
 	       this, getBounds(), g.getClipBounds());

    TimeAxis timeAxis = chart.getTimeAxis();
    Rectangle bounds = getBounds();
    int width = bounds.width;

    if (!chart.getActive())
      return;

    timeAxis.draw(g);
    
    for(Enumeration valueAxes = chart.getValueAxes();
	valueAxes.hasMoreElements();) {
      ValueAxis axis = (ValueAxis)valueAxes.nextElement();
      if(axis.getGridLinesVisible() && axis.getValueAxisVisible()) {
	axis.draw(g, width);
      }
    }

    if (timeAxis.getBaselineVisible() && timeAxis.getAbsoluteLabelsVisible()) {
      g.setColor(timeAxis.getBaselineColor());
      g.drawLine(0, bounds.height, width, bounds.height);
    }
  }

  //public void setEventHandler(EventHandler eh) {
  //}
}
