/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ScalableScrollState.java
 *
 */

package com.gensym.wksp;

import java.awt.Component;
import java.awt.Point;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.util.Observer;
import com.gensym.draw.ViewScrollState;
import com.gensym.message.Trace;

/* 
   This class is used by ScalableWorkspaceView to help support scaling. The logical_min, logical_max,
   view_min and view_max properties which are inherited from ViewScrollState are NOT transformed.

   The txScrollState property encapsulates the transformed logical min/max & view min/max. 

   The txScrollState is used as the Observable and it notifies Observers of state change.  Therefore,
   the scroll bars will be interpreting transformed coordinates (which is what we want).

   Note:  The scroll state contains coordinates in the Workspace coordinate system.  These coordinates
   need to be translated to the AWT coordinate system before they are transformed and then translated
   back after the transform has been performed.
*/

class ScalableScrollState extends ViewScrollState{

  private ScalableWorkspaceView wkspView;
  private ChangeableScrollState txScrollState; //holds the transformed coords

  ScalableScrollState (boolean isHorizontal, ScalableWorkspaceView wkspView) {
    super(isHorizontal);
    this.wkspView = wkspView;
    txScrollState = new ChangeableScrollState(isHorizontal);
  }

  //assumes transform is only scaling
  private void resetAndTransformState(AffineTransform previousTransform, boolean updateView){
    int logicalMin = getLogicalMin();
    int newLogicalMax; 
    int newLogicalWidth;
    boolean horizontal = isHorizontal();
    AffineTransform tx = wkspView.getTransform();

    //calculate logical min/max
    if (tx != null){
      int logicalWidth = getLogicalMax() - logicalMin;
      Point p = horizontal ? new Point(logicalWidth, 0) : new Point(0, logicalWidth);
      tx.transform(p, p);
      newLogicalWidth = horizontal ? p.x : p.y;
      newLogicalMax = newLogicalWidth + logicalMin;
    }
    else{
      newLogicalMax = getLogicalMax();
      newLogicalWidth = newLogicalMax - logicalMin;
    }

    if (updateView){
      //determine view min/max
      int awtWidth = horizontal ? wkspView.getBounds().width : wkspView.getBounds().height;
      if (awtWidth >= newLogicalWidth)
	txScrollState.setScrollState(logicalMin, newLogicalMax, logicalMin, newLogicalMax);
      else{
	//calculate current view center
	int viewMin = txScrollState.getViewMin();
	int viewMax = txScrollState.getViewMax();
	int viewCenter = (viewMin + viewMax)/2;
	//calculate tx'd view center
	Point p = horizontal ? new Point(viewCenter - logicalMin, 0) : new Point(0, viewCenter - logicalMin);
	if (previousTransform != null){
	  try{
	    previousTransform.inverseTransform(p, p);
	  }
	  catch(NoninvertibleTransformException ex){
	  }
	}
	if (tx != null)
	  tx.transform(p, p);
	int newViewCenter = (horizontal ? p.x : p.y) + logicalMin;
	//calculate viewMin & viewMax based on tx'd view center
	int newViewMin = newViewCenter - ((viewMax - viewMin)/2);
	
	txScrollState.setScrollState(logicalMin, newLogicalMax, 
				     newViewMin, Math.min(newViewMin + awtWidth, 
							  newViewMin + newLogicalWidth));
      }
      super.setView(getInverseTxViewMin(), getInverseTxViewMax());
    }
    else
      txScrollState.setScrollState(logicalMin, newLogicalMax, 
				   txScrollState.getViewMin(), txScrollState.getViewMax());
    setChanged();
    notifyObservers();
  }

  //delegate all Observer API to txScrollState so that the Scrollbars will get transformed coordinates
  @Override
  public void addObserver(Observer o){
    txScrollState.addObserver(o);
  }

  @Override
  public int countObservers(){
    return txScrollState.countObservers();
  }

  @Override
  public void deleteObserver(Observer o){
    txScrollState.deleteObserver(o);
  }

  @Override
  public void deleteObservers(){
    txScrollState.deleteObservers();
  }

  @Override
  public boolean hasChanged(){
    return txScrollState.hasChanged();
  }

  @Override
  public void notifyObservers(){
    txScrollState.notifyObservers();
  }

  @Override
  public void notifyObservers(Object o){
    txScrollState.notifyObservers(o);
  }

  @Override
  protected void clearChanged(){
    txScrollState.clearChanged();
  }

  @Override
  protected void setChanged(){
    txScrollState.setChanged();
  }
  
  //override ViewScrollState API to keep txScrollState in sync with this scroll state
  @Override
  public void setScrollState(int lmin, int lmax, int vmin, int vmax){
    super.setScrollState(lmin, lmax, vmin, vmax);
    resetAndTransformState(null, true);
  }

  @Override
  public void shift (int size){
    txScrollState.shift(size);
    super.setView(getInverseTxViewMin(), getInverseTxViewMax());
  }

  private int getInverseTxViewMin(){
    boolean horizontal = isHorizontal();
    //translate to AWT coords
    Point p = horizontal ? new Point(txScrollState.getViewMin() - logical_min, 0) 
      : new Point(0, txScrollState.getViewMin() - logical_min);
    AffineTransform tx = wkspView.getTransform();
    //inverse transform
    if (tx != null){
      try{
	tx.inverseTransform(p, p);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
    //translate back to wksp coords
    return (horizontal ? p.x : p.y) + logical_min;
  }

  private int getInverseTxViewMax(){
    boolean horizontal = isHorizontal();
    //translate to AWT coords
    Point p = horizontal ? new Point(txScrollState.getViewMax() - logical_min, 0) 
      : new Point(0, txScrollState.getViewMax() - logical_min);
    AffineTransform tx = wkspView.getTransform();
    //inverse transform
    if (tx != null){
      try{
	tx.inverseTransform(p, p);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
    //translate back to wksp coords
    return (horizontal ? p.x : p.y) + logical_min;
  }

  @Override
  public void setView(int viewMin, int viewMax){
    txScrollState.setView(viewMin, viewMax);
    super.setView(getInverseTxViewMin(), getInverseTxViewMax());
  }

  @Override
  public void adjustView(int size){
    txScrollState.adjustView(size);
    super.setView(getInverseTxViewMin(), getInverseTxViewMax());
  }

  @Override
  public void grow(int size, boolean setMinimum, int newViewMax){
    super.grow(size, setMinimum, newViewMax);
    resetAndTransformState(null, false);
  }

  //hooks for ScalableWorkspaceView
  void updateViewBounds(){
    super.setView(getInverseTxViewMin(), getInverseTxViewMax());
  }

  ViewScrollState getTransformedScrollState(){
    return txScrollState;
  }
  
  void transformChanged(AffineTransform previousTransform){
    resetAndTransformState(previousTransform, true);
  }

  String toString0(){
    return toString()+"\n TxState:"+txScrollState;
  }
}

class ChangeableScrollState extends ViewScrollState{
  
  ChangeableScrollState(boolean horizontal){
    super(horizontal);
  }
  
  @Override
  protected void setChanged(){
    super.setChanged();
  }
  
  @Override
  protected void clearChanged(){
    super.clearChanged();
  }
  
}
