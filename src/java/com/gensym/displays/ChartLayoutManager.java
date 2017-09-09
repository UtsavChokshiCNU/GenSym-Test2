package com.gensym.displays;

import com.gensym.util.*;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import com.gensym.irm.*;
import com.gensym.draw.*;
import java.util.*;
import java.awt.*;

/** Manages the layout of the essential visual elements of a chart:
 * Title
 * Legends
 * Axes and axes labels
 * Data window
 * Color of background and borders outside data window.
 * <p>
 * While this is called a LayoutManger, it doesn't implement
 * LayoutManager fully, as the components of the layout and their relative
 * behaviours are very specific to charts. This class should not throw
 * exceptions (except if made too small for a data window),
 * as it is responsible for finding some way to make the best of a bad job,
 * if necessary.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class ChartLayoutManager implements LayoutManager2 {
  public static boolean traceOn = false;

  public static final String ABOVE = "ABOVE";
  public static final String BELOW = "BELOW";

  static final int DATA_WINDOW_MARGIN = 10;

  private static final Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  private static final Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  private static final MessageKey messageKey =
  Message.registerMessageKey("com.gensym.displays", ChartLayoutManager.class);

  private static final MessageKey traceKey = messageKey;
  
  String legendPosition;
  String titlePosition;

  private TrendChart trendChart;
  protected ChartLabel title;
  /** A list of Chart Label elements whose contents is derived from
   * information in the plots */
  protected Vector legends;
  /** a list of Axis elements */
  protected Vector verticalAxes;
  /** a list of Axis elements */
  protected Vector horizontalAxes;
  protected DataAndLabelWindow dataAndLabelWindow;
  private TrendChartLegends trendChartLegends;

  private TimeAxis timeAxis;
  private RelativeTimeLabels relativeTimeLabels;
  

  /** true when the current layout is invalid */
  private boolean valid = false;

  /** NOTE: this constructor is incomplete */
  public ChartLayoutManager(TrendChart trendChart, // also parent
			    ChartLabel title,
			    String titlePosition,
			    DataAndLabelWindow dataAndLabelWindow,
			    TimeAxis timeAxis,
			    TrendChartLegends trendChartLegends,
			    RelativeTimeLabels relativeTimeLabels) {
    this.trendChartLegends = trendChartLegends;
    this.trendChart = trendChart;
    this.title = title;
    this.titlePosition = titlePosition;
    this.dataAndLabelWindow = dataAndLabelWindow;
    this.timeAxis = timeAxis;
    this.relativeTimeLabels = relativeTimeLabels;
  }

  @Override
  public Dimension maximumLayoutSize(Container target) {
    return target.getSize();
  }

  @Override
  public void addLayoutComponent(Component comp, Object constraints){
  }

  @Override
  public float getLayoutAlignmentX(Container target) {
    return 0.5f;
  }

  @Override
  public float getLayoutAlignmentY(Container target) {
    return 0.5f;
  }

  @Override
  public void invalidateLayout(Container target) {
    invalidate();
  }

  /** Does nothing */
  @Override
  public void addLayoutComponent(String name, Component comp){
  }

  /** Does nothing */
  @Override
  public void removeLayoutComponent(Component comp){
  }

  @Override
  public Dimension preferredLayoutSize(Container parent) {
    return parent.getSize();
  }

  @Override
  public Dimension minimumLayoutSize(Container parent){
    return parent.getSize();
  }

  void setTitlePosition(String position) {
    if (titlePosition == null || !titlePosition.equals(position)) {
      invalidate();
    }
    titlePosition = position;
  }

  public void invalidate () {
    valid = false;
    //dataAndLabelWindow.invalidateFormat();
    title.invalidateFormat();
  }

  @Override
  public void layoutContainer(Container parent) {
    Trace.send(20, traceKey, i18nTrace, "clmDoLayout", new Boolean(valid),
	       new Boolean(title.isVisible()), parent);
    Trace.send(20, traceKey, i18nTrace, "clmDoLayout2", parent.getSize(),
	       parent.getParent(), parent.getParent().getSize());
    
    if (valid)
      return;

    Dimension size = parent.getSize();

    // Order of priority as to who gets first choice on size is as
    // follows:
    // The title grows until the dataAndLabelWindow is shrunk to minimum size,
    // then each legend is allowed to grow until the dataAndLabelWindow is
    // shrunk to minimum size.
    // Note that the separation between elements is handled by the margins
    // within labels.
    if (timeAxis.getAbsoluteLabelsVisible()) {
      dataAndLabelWindow.setTimeLabelsVisible(true);
    } else {
      dataAndLabelWindow.setTimeLabelsVisible(false);
    }
    Dimension mindataAndLabelWindowSize = dataAndLabelWindow.getMinimumSize();
    int minDataWindowHeight = mindataAndLabelWindowSize.height;
    // fix this: throw an exception if this is bigger than the chart.
    int remainingHeight = size.height;
    int fullWidth = size.width;
    int remainingWidth = fullWidth;
    boolean needSpaceAtBottomOfDataWindow = true;

    // fix this: hack to emulate top margin
    int dwMargin = DATA_WINDOW_MARGIN/2;

    // top left of the data window is calculated as we go along
    int dwTop = 0;
    // The left will depend on the placement of value axes.
    int dwLeft = dwMargin;
    remainingWidth-= DATA_WINDOW_MARGIN;

    // first find out how much width is needed for all Axes on both
    // sides of the data window.

    // fix this: could optimize this by ensuring that the axes enumeration
    // gave the axes in reverse order (hence outside first in layout)
    int axesCount = trendChart.getValueAxesCount();
    int[] rightWidths = new int[axesCount],
      leftWidths = new int[axesCount];
    ValueAxis[] leftAxes = new ValueAxis[axesCount],
      rightAxes = new ValueAxis[axesCount];
    int rightIndex = 0, leftIndex = 0;
    for (Enumeration en = trendChart.getValueAxes(); en.hasMoreElements();) {
      ValueAxis valueAxis = (ValueAxis)en.nextElement();
      if(valueAxis.getLabelsVisible() && valueAxis.getValueAxisVisible()) {
	ValueLabels valueLabels = valueAxis.getValueLabels();
	Trace.send(10, traceKey, i18nTrace, "clmValueAxis", valueAxis);
	int width = valueLabels.computeMinimumWidth();
	Trace.send(10, traceKey, i18nTrace, "clmValueLabels",
		   valueLabels, new Integer(width));
	remainingWidth -= width;
	if (valueAxis.positionedOnRight()) {
	  rightWidths[rightIndex] = width;
	  rightAxes[rightIndex++] = valueAxis;
	} else {
	  leftWidths[leftIndex] = width;
	  leftAxes[leftIndex++] = valueAxis;
	  dwLeft += width;
	}
      }
    }

    // the title
    Trace.send(10, traceKey, i18nTrace, "clmdoLayoutTitle1", title);
    if (title.isVisible()) {
      try {
	Dimension preferredSize =
	  new Dimension(fullWidth, 0); // as little height as possible
	Dimension maximumSize =
	  new Dimension(fullWidth,
			remainingHeight - mindataAndLabelWindowSize.height);
	Dimension dim = title.formatShape(preferredSize,
					  maximumSize, true);
	remainingHeight = remainingHeight - dim.height;
	Trace.send(10, traceKey, i18nTrace, "clmdoLayoutTitle2",
		   dim, new Integer(remainingHeight));
      
      } catch (Exception ex) {
	Message.send(new MessageEvent (1, messageKey, i18n,
				       "clmTitleLayoutError",
				       new Object[] {ex.getMessage()}));
	ex.printStackTrace();
      }
      
      if(ABOVE.equals(titlePosition)) {
	title.setLocation(0, 0);
	//	dwTop = size.height - title.getSize().height
	dwTop = size.height - remainingHeight; // == title.getSize().height
      } else {
	title.setLocation(0, remainingHeight);
	needSpaceAtBottomOfDataWindow = false;
      }
    }

    
    // here is where the legends are layed out.
    if (trendChartLegends.isVisible()) {
      trendChartLegends.layoutLegends(remainingHeight - minDataWindowHeight);
      int legendHeight = trendChartLegends.getSize().height;
      remainingHeight -= legendHeight;
      if (ABOVE.equals(trendChart.getLegendPosition())) {
	trendChartLegends.setLocation(0, dwTop);
	dwTop+= legendHeight;
      } else {
	trendChartLegends.setLocation(0, dwTop + remainingHeight);
	needSpaceAtBottomOfDataWindow = false;
      }
    }

    // here is where the axes with their labels are layed out

    // first allot the height necessary for the relative labels
    int relativeLabelHeight = 0;
    boolean relativeLabelsVisible = timeAxis.getRelativeLabelsVisible();
    if (relativeLabelsVisible) {
      relativeLabelHeight = relativeTimeLabels.getPreferredHeight();
      if(remainingHeight - relativeLabelHeight >= minDataWindowHeight) {
	//OK, it will fit
	remainingHeight-= relativeLabelHeight;
      } else {
	relativeLabelsVisible = false; // not enough room
      }
    }
      
    // data window. We know that it has enough room, as its minimum
    // size was consulted all along.

    int dwTopAdjustment = trendChart.getDataWindowTopAdjustment();
    dwTop = dwTop + dwMargin + dwTopAdjustment;

    Dimension newDwSize = null;
    int spaceAtBottom = 
      needSpaceAtBottomOfDataWindow ? 2*dwTopAdjustment : 0;
    Dimension preferredSize =
      new Dimension(remainingWidth,
		    remainingHeight- (DATA_WINDOW_MARGIN + spaceAtBottom));
    try {
      newDwSize = dataAndLabelWindow.formatShape(preferredSize,
						 preferredSize, true);
    } catch (Exception ex) {
      Message.send(new MessageEvent (1, messageKey, i18n,
				     "clmdataAndLabelWindowLayoutError",
				     new Object[] {ex.getMessage()}));
      ex.printStackTrace();
    }
    if (newDwSize != null) {
      Trace.send(10, traceKey, i18nTrace, "clmSetDataAndLabelWindow",
		 new Rectangle (dwLeft, dwTop,
				newDwSize.width,
				newDwSize.height),
		 preferredSize);
      dataAndLabelWindow.setBounds(dwLeft, dwTop,
				   newDwSize.width,
				   newDwSize.height);
    }

    // Now we can position and size the relative labels

    if (relativeLabelsVisible) {
      relativeTimeLabels.setBounds(dwLeft,
			       dwTop + newDwSize.height,
			       newDwSize.width,
			       relativeLabelHeight);
      relativeTimeLabels.setVisible(true);
    } else {
      relativeTimeLabels.setVisible(false);
    }

    // now we have all the information we need to lay out the
    // value axes

    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "clmvalueAxesArrays",
		 DebugUtil.printArray(leftAxes),
		 DebugUtil.printArray(rightAxes));
    }

    int axisLeft = dwMargin;
    for (int i = leftIndex - 1; i >= 0; i--) {
      ValueAxis axis = leftAxes[i];
      int width = leftWidths[i];
      ValueLabels labels = axis.getValueLabels();
      int labelAscent = labels.getLabelAscent();
      // fix this: the top needs adjusting either here or on the data window
      // in order to show the entire number on the top and bottom labels, as
      // they are centered on the grid-line
      // the adjustment here is a hack.
      labels.setBounds(axisLeft, dwTop - labelAscent/2,
		       width, newDwSize.height + labelAscent);
      axis.computeAxisDescription();
      Trace.send(10, traceKey, i18nTrace, "clmSetLabelBoundsL",
		 labels, labels.getBounds());
      axisLeft += width;
    }

    axisLeft = dwLeft + newDwSize.width;
    for (int i = 0; i <= rightIndex - 1; i++) {
      ValueAxis axis = rightAxes[i];
      int width = rightWidths[i];
      ValueLabels labels = axis.getValueLabels();
      int labelAscent = labels.getLabelAscent();
      // fix this: the top needs adjusting either here or on the data window
      // in order to show the entire number on the top and bottom labels, as
      // they are centered on the grid-line
      labels.setBounds(axisLeft, dwTop - labelAscent/2,
		       width, newDwSize.height + labelAscent);
      axis.computeAxisDescription();
      Trace.send(10, traceKey, i18nTrace, "clmSetLabelBoundsR",
		 labels, labels.getBounds());
      axisLeft += width;
    }      

    Trace.send(10, traceKey, i18nTrace, "clmendLayoutContainer",
	       parent.getBounds(), title.getPreferredSize(),
	       dataAndLabelWindow.getBounds());

    valid = true;
  }
}

      
