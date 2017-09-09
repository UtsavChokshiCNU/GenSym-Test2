/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      WorkspaceChartImpl.java
 *
 *
 */

package com.gensym.wksp;

import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.util.symbol.*;
import com.gensym.displays.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ItemDeletedException;
import com.gensym.draw.DrawElement;
import com.gensym.draw.PersistentCanvas;
import com.gensym.classes.Item;
import com.gensym.classes.Chart;
import java.util.*;
import java.awt.*;

/** Handles the translating of G2 messages into more java-like messages.
 * Implements the basic aspects of "being a workspace element".
 */
public class WorkspaceChartImpl extends Container
implements WorkspaceChart, DrawElement,
com.gensym.util.symbol.ChartSymbols{

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.wksp", WorkspaceChart.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.wksp.TraceMessages");

  private WorkspaceElementHelper helper;
  private WorkspaceView workspace;
  private PersistentCanvas canvas;
  private com.gensym.classes.Chart g2Chart;
  private SimpleChart chartView;

  //
  // For DrawElement
  //
  protected Rectangle[] bounds;
  
  public WorkspaceChartImpl(Item item, WorkspaceView parent)
  throws G2AccessException {
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     item,
					     parent);
    item.addItemListener(this);
    bounds = WorkspaceElementHelper.getExactBounds(item);
    Trace.send(10, traceKey, i18nTrace, "wcBounds", bounds[0]);
    canvas = parent;
    workspace = parent;
    g2Chart = (com.gensym.classes.Chart)item;
    initialize();
    setLayout(new BorderLayout());
    setBounds(bounds[0]);
    try {
      chartView = new SimpleChart(g2Chart);
    } catch (NoSuchAttributeException nsae) {
      Trace.exception(nsae);
      throw new UnexpectedException(nsae);
    }
    //chartView.setBounds(bounds[0]);
    chartView.setVisible(true);
    add(chartView, BorderLayout.CENTER);
    parent.add(this);
    validate();
    
    this.setVisible(true);
  }

  Sequence chartDataSeries;
  Structure annotations;
  Structure computedAxisDetails;

  /** This is the initialization of the "G2" properties */
  private void initialize() throws G2AccessException {
    chartDataSeries = g2Chart.getChartDataSeries();
    annotations = g2Chart.getAnnotations();
    
    Trace.send(10, traceKey, i18nTrace, "wcinitialize", annotations,
	       chartDataSeries, computedAxisDetails);
  }

  //
  // AWT overrides
  //

  /*WORKSPACE ELEMENT API*/

  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
  }

  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    Trace.send(10, traceKey, i18nTrace, "wchandleWsItemMoved", event);
    helper.shift(event);   
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    Trace.send(10, traceKey, i18nTrace, "wcresize0", event);
    helper.resize(event);
  }

  @Override
  public void setBounds(int x, int y, int width, int height) {
    Trace.send(10, traceKey, i18nTrace, "wcsetBounds",
	       new Rectangle(x, y, width, height));
    super.setBounds(x, y, width, height);
    bounds[0].x = x;
    bounds[0].y = y;
    bounds[0].width = width;
    bounds[0].height = height;
    validate();
  }

  @Override
  public void receivedInitialValues (ItemEvent e) {
    helper.receivedInitialValues(e);
  }

  // fix this: this utility method should be in a more general place,
  // and, in fact, should be unnecessary here. as the ItemImpl should
  // take care of all this

//   /** Returns null if the denotation is not a simple attribute denotation */
//   static Symbol getAttributeName(Sequence denotation) {
//     if (denotation.getLength() != 1)
//       return null;
//     Structure struct = (Structure)denotation.firstElement();
//     if (!G2TypeSymbols.ATTRIBUTE_.
// 	equals(struct.getAttributeValue(Denotation.TYPE_, null)))
//       return null;
//     return (Symbol)struct.getAttributeValue(Denotation.NAME_, null);
//   }
    

  @Override
  public void itemModified (ItemEvent e) {
    Trace.send(10, traceKey, i18nTrace, "wcprocessItemEvent", e);
    try {
      chartView.acknowledgeSlotChange(e);
    } catch (G2ItemDeletedException g2ide) {
      Trace.exception(g2ide); // itemModified is called during item deletion
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae);
    } catch (NoSuchAttributeException nsae) {
      throw new UnexpectedException(nsae);
    }
    helper.itemModified(e);
  }

  // fix this: temp hack for development
  //     Structure denotation = e.getDenotation();
  //     Symbol attrName = getAttributeName(denotation);
  //     if (attrName == null)
  //       return;
  //     Object newValue = e.getnewValue();
//     try {
//       dispatchSlotChange(attrName, newValue);
//     } catch (G2AccessException g2ae) {
//       throw new UnexpectedException(g2ae);
//     }
//   }

  @Override
  public void itemDeleted (ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }

  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return helper.getDraggingGhost(left,top,width,height);
  }

  @Override
  public DraggingGhost getDraggingGhost () {
    return helper.getDraggingGhost();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return helper.getDraggingGhost(markerLocn, currentX, currentY);
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  //
  // DrawElement
  //

  @Override
  public void setCanvas(PersistentCanvas canvas) {
    this.canvas = canvas;
  }
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
  }

  @Override
  public Object[] getLogicalColors()
  {
    return null;
  }

  @Override
  public Rectangle[] getExactBounds() {
    return bounds;
  }

  @Override
  public void shift (int deltaX, int deltaY)
  {
    helper.shift(deltaX,deltaY);
    bounds[0].translate(deltaX, deltaY);
    Point location = getLocation();
    setLocation(location.x + deltaX, location.y + deltaY);
  }

  @Override
  public void setSize(int width, int height) {
    bounds[0].width = width;
    bounds[0].height = height;
    invalidate();
    super.setSize(width,height);
    Trace.send(10, traceKey, i18nTrace, "wcsetSize2", getSize());
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  @Override
  public void paint (Graphics g) {
    super.paint (g);
    if (isCut ()) {
      Rectangle[] exbnds = getExactBounds ();
      Rectangle bnds = exbnds[0];
      helper.paintCutStatus (g, bnds.x, bnds.y, bnds.width, bnds.height);
    }
  }

  @Override
  public void dispose() throws G2AccessException{
    getItem().removeItemListener(this);
  }

}
