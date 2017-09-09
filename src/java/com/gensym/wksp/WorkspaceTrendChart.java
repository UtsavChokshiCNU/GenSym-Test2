package com.gensym.wksp;

import com.gensym.ntw.util.TrendChartEvent;
/**
 * A <code>WorkspaceElement</code> intended for use with items of class <code>TrendChart</code>.
 */
public interface WorkspaceTrendChart extends WorkspaceElement {

  /**
   * Translates and dispatches the event to the appropriate
   * trend chart method using the event's id.
   */
  public void processTrendChartEvent(TrendChartEvent event);
  
}


