package com.gensym.draw;

import java.util.Observer;
import java.util.Observable;
import java.lang.Integer;
import java.awt.*;
import java.awt.event.*;

public class ViewScrollbar extends LWScrollbar
       implements Observer, AdjustmentListener
{
  static final long serialVersionUID = 5394187949540868884L;
  private Scrollable controlledComponent;
  private static int offset_hack = 0;
  
  public ViewScrollbar (Scrollable parent,
			int orientation, int value, 
			int visible, int minimum, int maximum)
  {
    super(orientation,value+offset_hack,visible,
           minimum+offset_hack,maximum+offset_hack);
    addAdjustmentListener(this);
    controlledComponent = parent;
    resetScrollIncrements (visible);
  }

  public void setScrollable(Scrollable scrollable)
  {
    controlledComponent = scrollable;
  }

  public Scrollable getScrollable()
  {
    return controlledComponent;
  }

  @Override
  public void update(Observable observable, Object arg)
  {
    ViewScrollState state = (ViewScrollState) observable;
    if (false) {
      System.out.println("RCVD SCROLL UPDATE vmin="+state.view_min+
			 " vmax="+state.view_max+
			 " lmin="+state.logical_min+
			 " lmax="+state.logical_max);
      System.out.println ("Visible = " + getVisibleAmount ());
    }
    if (state.view_max - state.view_min != getVisibleAmount ())
      resetScrollIncrements (state.view_max - state.view_min);

    setValues(state.view_min + offset_hack,
              state.view_max - state.view_min,
              state.logical_min + offset_hack,
              state.logical_max + offset_hack /* die, die, die
              (state.view_max - state.view_min) */
              );
    /* } */
  }

  @Override
  public void adjustmentValueChanged(AdjustmentEvent event)
  {
      int type = event.getAdjustmentType();
      int scroll_value = 0;
      boolean is_horizontal 
         = (getOrientation() == Scrollbar.HORIZONTAL);

      /*
      UNIT_INCREMENT, UNIT_DECREMENT, BLOCK_INCREMENT, BLOCK_DECREMENT,
          TRACK 
      */
      int unitIncrement = getUnitIncrement();//20;
      int blockIncrement = getBlockIncrement();//100;
      
      switch (type) {    
      case AdjustmentEvent.TRACK:
	if (false) {
          System.out.println("abs scrollval="+scroll_value);
          System.out.println("getValue="+ event.getValue());
	}
	controlledComponent.scrollViewAbsolute
	  (event.getValue() - offset_hack,is_horizontal);
	break;
      case AdjustmentEvent.UNIT_DECREMENT:
	controlledComponent.scrollView
	  (-unitIncrement,is_horizontal);
	break;
      case AdjustmentEvent.UNIT_INCREMENT:
	controlledComponent.scrollView
	  (unitIncrement,is_horizontal);
	break;
      case AdjustmentEvent.BLOCK_DECREMENT:
	controlledComponent.scrollView
	  (-blockIncrement,is_horizontal);
	break;
      case AdjustmentEvent.BLOCK_INCREMENT:
	controlledComponent.scrollView
	  (blockIncrement,is_horizontal);
	break;
      default:
	break;
     }
  }

  private void resetScrollIncrements (int visibleAmount) {
    /* Totally arbitrary setting, but better than the default
     * of 1 and 20 pixels respectively
     */
    setUnitIncrement (visibleAmount/20);
    setBlockIncrement (visibleAmount*4/5);
  }
  
}
