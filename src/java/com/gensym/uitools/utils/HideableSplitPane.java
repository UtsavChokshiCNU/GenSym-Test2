package com.gensym.uitools.utils;

import java.awt.Component;
import javax.swing.JSplitPane;

public class HideableSplitPane extends JSplitPane {

  private ComponentVisibilityAdapter compVisListener;

  /**
   * @param firstComponent component to left or top of split.  MUST BE INSTANCE
   * OF java.awt.Component
   * @param secondComponent component to right or bottom of split.  MUST BE
   * INSTANCE OF java.awt.Component
   */
  public HideableSplitPane (int orientation,
			    ComponentVisibilityEventSource firstComponent,
			    ComponentVisibilityEventSource secondComponent){
    super(orientation, (Component)firstComponent, (Component)secondComponent);
    if (!getLeftComponent().isVisible() && !getRightComponent().isVisible())
      setVisible(false);
    compVisListener = new ComponentVisibilityAdapter();
    firstComponent.addComponentVisibilityListener(compVisListener);
    secondComponent.addComponentVisibilityListener(compVisListener);
  }

  class ComponentVisibilityAdapter implements ComponentVisibilityListener {
    @Override
    public void visibilityChanged(ComponentVisibilityEvent e) {
      if (!getLeftComponent().isVisible() && !getRightComponent().isVisible())
	setVisible(false);
      else
	setVisible(true);
      Component parent = getParent();
      if (parent instanceof JSplitPane) 
	((JSplitPane)parent).resetToPreferredSizes();
    }
  }
}
