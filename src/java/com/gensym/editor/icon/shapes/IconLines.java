package com.gensym.editor.icon.shapes;

import java.awt.Color;
import java.awt.Rectangle;
import java.awt.Graphics;
import java.awt.Point;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconLines extends BasicDrawElement
implements IconElement
{
  private Layer layer;
  protected Rectangle[] bounds;
  protected int[] xPoints, yPoints;
  protected int pointCount;
  
  public IconLines(int numPoints, int[] xPts, int[] yPts)
  {
    expressions = new Object[numPoints*2];    
    init(numPoints, xPts, yPts);
  }

  @Override
  public String getShapeName() {
    return "Lines";
  }
  
  @Override
  public String[] getExpressionLabels() {
    String[] labels = new String[pointCount*2];
    for (int i=0;i<pointCount;i++) {
      labels[2*i]="x"+(i+1);
      labels[2*i+1]="y"+(i+1);
    }
    return labels;
  }
  
  @Override
  public int[] getExpressionIndices() {
    int[] indices = new int[pointCount*2];
    for (int i=0;i<pointCount*2;i++) 
      indices[i]=i;
    return indices;
  }
  
  @Override
  public void evaluateExpression(int coordinateIndex, Evaluator evaluator) {
    boolean isXCoordinate = (coordinateIndex%2 == 0);
    int newValue = evaluator.evaluateInteger(expressions[coordinateIndex]);
    if (isXCoordinate)
      xPoints[coordinateIndex/2] = newValue;
    else
      yPoints[coordinateIndex/2] = newValue;
    init(pointCount,xPoints, yPoints);
    ((ToolContainer)getParent()).invalidateElement(this);        
  }

  public int getPointCount() {
    return pointCount;
  }

  @Override
  public Object getExpression(int coordinateIndex) {
    Object expression = super.getExpression(coordinateIndex);
    if (expression != null)
      return expression;
    else {
      boolean isXCoordinate = (coordinateIndex%2 == 0);
      if (isXCoordinate)
	return new Integer(xPoints[coordinateIndex/2]);
      else
	return new Integer(yPoints[coordinateIndex/2]);
    }
  }
  
  private void init(int numPoints, int[] xPts, int[] yPts) {
    this.pointCount = numPoints;
    int xmin = 100000, ymin = 100000, xmax = -100000, ymax = -100000;
    bounds = new Rectangle[1];
    xPoints = new int[numPoints];
    yPoints = new int[numPoints];
    for (int i=0; i<numPoints; i++) {
      xPoints[i] = xPts[i];
      yPoints[i] = yPts[i];
      xmax = Math.max (xmax, xPts[i]); xmin = Math.min (xmin, xPts[i]);
      ymax = Math.max (ymax, yPts[i]); ymin = Math.min (ymin, yPts[i]);
    }
    bounds[0] = new Rectangle(xmin, ymin, xmax - xmin, ymax - ymin);
    setLocation(xmin,ymin);
    setSize( xmax - xmin+1, ymax - ymin+1);    
  }

  @Override
  public IconElement copy()
  {
    int numPoints = xPoints.length;
    int[] xPointsCopy = new int[numPoints];
    int[] yPointsCopy = new int[numPoints];
    for (int i=0;i<numPoints;i++) {
      xPointsCopy[i] = xPoints[i];
      yPointsCopy[i] = yPoints[i];
    }
    IconLines copy = new IconLines(numPoints, xPointsCopy, yPointsCopy);
    for (int i=0;i<numPoints*2;i++) {
      try {
	copy.setExpression(i, getExpression(i));
      } catch (BadExpressionException bee) {
	Trace.exception(bee);
      }
    }
    return copy;
  }

  @Override
  public void paint (Graphics g)
  {
    Rectangle theBounds = bounds[0];
    g.setColor(color);
    
    int linecount = (xPoints.length - 1);
    int x1,y1,x2,y2;
    for (int i = 0; i<linecount; i++) {
      x1 = xPoints[i]; y1 = yPoints[i];
      x2 = xPoints[i+1]; y2 = yPoints[i+1];
      g.drawLine(x1-theBounds.x,y1-theBounds.y,
		 x2-theBounds.x,y2-theBounds.y);
    }
  }
  
  @Override
  public void shift (int shiftX, int shiftY)
  {
    Evaluator evaluator = getEvaluator();
    for (int i=0; i<xPoints.length; i++) {
      xPoints[i] += shiftX;
      yPoints[i] += shiftY;
      if (evaluator != null) {
	try {
	  setExpression(i*2, evaluator.addOffset(getExpression(i*2), shiftX));
	  setExpression(i*2+1, evaluator.addOffset(getExpression(i*2+1), shiftY));
	} catch (BadExpressionException bee) {
	Trace.exception(bee);
	}
      } else {
	//TBD
      }
    }
    layer.repaint();
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }
  
  public int[] getXPoints()
  {
    return xPoints;
  }

  public int[] getYPoints()
  {
    return yPoints;
  }  
  
  @Override
  public Layer getLayer()
  {
    return layer;
  }
  
  @Override
  public void setLayer(Layer layer)
  {
    this.layer = layer;
  }

}
