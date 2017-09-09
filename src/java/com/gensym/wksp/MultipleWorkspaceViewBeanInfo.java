package com.gensym.wksp;

import java.beans.*;
import com.gensym.util.ModifiableBeanInfo;
import java.awt.Image;
import java.awt.Toolkit;

public class MultipleWorkspaceViewBeanInfo extends ModifiableBeanInfo {
  private Image icon32x32 = Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("multipleworkspaceview.gif"));

  @Override
  public Image getIcon(int iconKind) {
    if (iconKind == ICON_COLOR_32x32) return icon32x32;
    return null;
  }

  @Override
  protected Class getBeanClass()
  {
    return MultipleWorkspaceView.class;
  }

  @Override
  protected void modifyEventSetDescriptor(EventSetDescriptor eventSetDescriptor)
  {
    String eventName = eventSetDescriptor.getName();
    if (eventName.equals("selection"))
      eventSetDescriptor.setExpert(false);
    else
      eventSetDescriptor.setExpert(true);
  }

  @Override
  protected PropertyDescriptor modifyPropertyDescriptor(PropertyDescriptor propertyDescriptor)
  {
    String propertyName = propertyDescriptor.getName();
    if (propertyName.equals("foregroundColor") ||
	propertyName.equals("backgroundColor") ||
	propertyName.equals("blockIncrement") ||
	propertyName.equals("unitIncrement"))
      propertyDescriptor.setExpert(false);
    else 
      //useG2Configurations, currentWorkspace, item, elements, selection
      // currentView
      propertyDescriptor.setExpert(true);
    return propertyDescriptor;
  }

  @Override
  protected void modifyMethodDescriptor(MethodDescriptor methodDescriptor)
  {
    String methodName = methodDescriptor.getName();
    if (methodName.equals("nextWorkspace") ||
	methodName.equals("previousWorkspace") ||
	methodName.equals("selectAll") ||
	methodName.equals("clearSelection") ||
	methodName.equals("deleteSelection") ||
	methodName.equals("scrollUnitUp") ||
	methodName.equals("scrollUnitDown") ||
	methodName.equals("scrollUnitLeft") ||
	methodName.equals("scrollUnitRight") ||
	methodName.equals("scrollBlockUp") ||
	methodName.equals("scrollBlockDown") ||
	methodName.equals("scrollBlockLeft") ||
	methodName.equals("scrollBlockRight")) {
      methodDescriptor.setExpert(false);
    }
    else 
      /*contains, addWorkspace, removeWorkspace, getCurrentView,
	getWorkspaces, addScrollbar, removeScrollbar,
	addScrollObserver, removeScrollObserver,
	getScrollState, setScroll, growLogical, scrollView,
	scrollViewAbsolute, getSelection
	dispose, finalize, renderWorkspace,
	addElement(WorkspaceElement),addElement(WorkspaceElement,int)
	removeElement(WorkspaceElement),findElement(Item)
	handleColorsChanged(WorkspaceEvent)
	createElement(Item)
	selectElements(WorkspaceElement[])
	addElementsToSelection(WorkspaceElement[])
	addElementToSelection(WorkspaceElement)
	removeElementsFromSelection(WorkspaceElement[])
	removeElementFromSelection(WorkspaceElement)
	moveSelection(int,int,boolean)
	resizeSelection(int,int,int,int)*/
      {
	methodDescriptor.setExpert(true);
      }
  }
}

