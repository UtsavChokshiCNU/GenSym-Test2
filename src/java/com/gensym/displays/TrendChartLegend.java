package com.gensym.displays;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Label;
import java.awt.FontMetrics;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Color;

import com.gensym.util.*;
import com.gensym.util.Set;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.message.*;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;

/** Corresponds to the legends of a G2 trend chart. Each TrendChartPlot has
 * its own TrendChartLegend component to paint the legend string for that
 * plot. Knows how to generate the text of the legend based on the plot to
 * which it belongs.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
class TrendChartLegend extends ChartLabel
implements com.gensym.util.symbol.TrendChartSymbols {

  private static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");

  private static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  private static final MessageKey traceKey =
  Message.registerMessageKey("com.gensym.displays", TrendChartLegend.class);

  private static final Symbol MATCHING_PLOT_COLOR_ = Symbol.intern ("MATCHING-PLOT-COLOR");

  private static final int
  DEFAULT_TOP_MARGIN = 2,
    DEFAULT_BOTTOM_MARGIN = 4;

  static private final TextStyle DEFAULT_LEGEND_STYLE =
  new TextStyle(G2FontMap.HM14, 0, 0, 2);

  private TrendChartPlot trendChartPlot;
  private TrendChart trendChart;
  private String legendText;
  private TextCell textCell;

  public TrendChartLegend(TrendChartPlot plot,
		    TrendChart trendChart) {
    super(trendChart.getSize(),
	  trendChart.getSize(),
	  true,
	  "",
	  DEFAULT_LEGEND_STYLE,
	  TextCell.CENTER,
	  trendChart.getOuterBackgroundColor(),
	  Color.black,
	  0,
	  trendChart.getOuterBackgroundColor());
    trendChartPlot = plot;
    this.trendChart = trendChart;
  }

  // hack: fix this: hack for development
  int topMargin = DEFAULT_TOP_MARGIN;
  int bottomMargin = DEFAULT_BOTTOM_MARGIN;

  @Override
  public int getHeight() {
    return getSize().height;
  }

  private Symbol makeColorName() {
    Symbol colorName = trendChartPlot.getMostVisibleColorName();
    if (TRANSPARENT_.equals(colorName))
      return null;
    else
      return colorName;
  }
    
  private Symbol makeColorName(ConnectorFormat connectorFormat,
				 MarkerFormat markerFormat) {
    Symbol colorName = null;
    if (connectorFormat.getConnectorsVisible()) {
      colorName = connectorFormat.getConnectorLineColorName();
    } else if (markerFormat.getMarkersVisible()) {
      colorName = markerFormat.getMarkerColorName();
    }

    if (colorName == null ||
	TRANSPARENT_.equals(colorName))
      return null;
    else
      return colorName;
  }

  String makeLegend() {
    TrendChartPlot plot = trendChartPlot;
    if (!plot.getIncludeInLegend()) {
      Trace.send(10, traceKey, i18nTrace, "tclNotInLegend",
		 plot.getChartElementUid());
      return null;
    }

    Object expression = plot.getExpression();
    if (expression == null) {
      Trace.send(10, traceKey, i18nTrace, "tclNoPlotExpression",
		 plot.getChartElementUid());
      return null;
    }
    
    ConnectorFormat connectorFormat = plot.getConnectorFormat();
    MarkerFormat markerFormat = plot.getMarkerFormat();
    Object colorType = trendChart.getLegendColorType();
    boolean usePlotColor = MATCHING_PLOT_COLOR_.equals(colorType);

    Symbol colorName = null;
    if (!usePlotColor) {
      colorName = makeColorName();
      if (colorName == null) {
	Trace.send(10, traceKey, i18nTrace, "tclColorTransparent",
		   plot.getChartElementUid());
	return null;
      }
    }
    
    String name = plot.getName();
    name = (name == null ? expression.toString() : name);

    String markerString = markerFormat.makeMarkerString();

    //    StringBuffer buf = new StringBuffer(name);

    String legendString = name;

    if (usePlotColor) {
      if (markerString == null) {
	legendString = name;
      } else {
	legendString = i18n.format("tclLegendWithMarker",
				   new Object[] {name, markerString});
      }
    } else {
      String colorNameString = colorName.getPrintValue().toLowerCase();
      if (markerString == null) {
	legendString = i18n.format("tclLegendWithColor",
				   new Object[] {name, colorNameString});
      } else {
	legendString = i18n.format("tclLegendWithColorAndMarker",
				   new Object[] {name, colorNameString,
						   markerString});
      }
    }

    Trace.send(10, traceKey, i18nTrace, "tclLegendString", legendString);

    int width = getSize().width;
    Font font = getFont();
    if (font == null)
      return null;
    FontMetrics metrics = getFontMetrics(font);
    int labelWidth = metrics.stringWidth(legendString);

    Trace.send(10, traceKey, i18nTrace, "tclFontAndWidth", font,
	       new Integer(width), new Integer(labelWidth));
//     if (labelWidth > width) {
//       if (metrics.stringWidth(name) > width)
// 	return i18n.getString("tclLegendTooLong");
//       else
// 	return name;
//     } else {
//       return legendString;
//     }
    return legendString;
  }

  void setLegendText(String legendText) {
    this.legendText = legendText;
    setText(legendText);
  }

  String getLegendText() {
    return legendText;
  }

  void resetLegendText() {
    //System.out.println("Before makeLegend");
    setLegendText(makeLegend());
    //System.out.println("After makeLegend");
  }

  private Color getLegendColor() {
    Symbol colorType = trendChart.getLegendColorType();
    if(MATCHING_PLOT_COLOR_.equals(colorType))
      return trendChartPlot.getMostVisibleColor();
    else
      return trendChart.getLegendColor();
  }

  @Override
  public void paint(Graphics g) {
    setTextColor(getLegendColor());
    super.paint(g);
  }

}
