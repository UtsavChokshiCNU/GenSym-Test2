/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RelativeTimeLabels.java
 *
 *  Description:
 *               The "fixed" labels that show the relative time values.
 *
 *	 Author:
 *		Robert Penny		Feb/98
 *
 *
 */

package com.gensym.displays;

import java.awt.*;
import java.util.Date;
import java.text.DateFormat;
import com.gensym.message.Resource;

public class RelativeTimeLabels extends Component {

  private static final int
  DEFAULT_TOP_MARGIN = 0,
    DEFAULT_BOTTOM_MARGIN = 2;

  TrendChart trendChart;
  DataAndLabelWindow dataWindow;
  TimeAxis timeAxis;
  private boolean labelFrequencyValid = false;
  private int topMargin = DEFAULT_TOP_MARGIN;
  private int bottomMargin = DEFAULT_BOTTOM_MARGIN;
  private DateFormat dateFormat;

  public RelativeTimeLabels(TrendChart trendChart,
			    DataAndLabelWindow dataWindow) {
    this.trendChart = trendChart;
    this.dataWindow = dataWindow;
    timeAxis = trendChart.getTimeAxis();
  }

  int mWidth;
  static final String mString = "m";
  static final Date sampleDate = new Date(TimeUtils.midnight() +
					  86400000/2); //noon

  int preferredHeight = -1;

  int getPreferredHeight() {
    if (preferredHeight == -1)
      preferredHeight =
	getFontMetrics(getFont()).getHeight() + topMargin + bottomMargin;

    return preferredHeight;
  }

  int getMaxLabelWidth() {
    FontMetrics metric = getFontMetrics(getFont());
    if (mWidth == 0) {
      mWidth = metric.stringWidth(mString);
    }
    String sampleLabel = timeAxis.getRelativeDateFormat().format(sampleDate);

    return metric.stringWidth(sampleLabel) + mWidth; // allow an extra character
  }

  private Date dateHelper = new Date();

  // NOTE: the dateFormat object is what is putting in the
  // minus signs
  String generateRelativeTimeLabel(long timeOffset, long midnight) {
    synchronized (dateHelper) {
      dateHelper.setTime(midnight + timeOffset);
      return dateFormat.format(dateHelper);
    }
  }

  @Override
  public void paint(Graphics g) {
    dateFormat = timeAxis.getRelativeDateFormat();

    long labelFrequency = timeAxis.getRealLabelFrequency();
    super.paint(g);
    if (labelFrequency == 0) {
      return;
    }

    int width = getSize().width;

    long timeSpan = timeAxis.getVisibleTimeSpan();

    int alignmentIndicator = timeAxis.getAlignmentIndicator();

    // timestamps are painted from right to left
    long firstTimeOffset =
      alignmentIndicator == timeAxis.RIGHT ?
      0 : labelFrequency;

    long midnight = TimeUtils.midnight();
    FontMetrics metric = getFontMetrics(getFont());
    int verticalOffset = metric.getHeight() + topMargin;
    double scale = timeAxis.getScale();

    g.setColor(timeAxis.getLabelColor());
    g.setFont(getFont());

    for (long timeOffset = firstTimeOffset;
	 timeOffset < timeSpan;
	 timeOffset += labelFrequency) {
      String label = generateRelativeTimeLabel(timeOffset, midnight);
      int stringWidth = metric.stringWidth(label);
      int deviceOffset = (int)(timeOffset * scale);
      int labelLeft;
      
      switch (alignmentIndicator) {
      case TimeAxis.RIGHT:
	labelLeft = width - (deviceOffset + stringWidth);
	break;
      case TimeAxis.CENTER:
	labelLeft = width - (deviceOffset + stringWidth/2);
	break;
      default:
	labelLeft = width - deviceOffset;
      }

      if (labelLeft < 0)
	break;

      g.drawString(label, labelLeft, verticalOffset);
    }
  }      
}
