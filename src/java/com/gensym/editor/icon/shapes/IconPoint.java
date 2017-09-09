package com.gensym.editor.icon.shapes;

import java.awt.Color;
import java.awt.Rectangle;
import java.awt.Graphics;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconPoint extends BasicDrawElement
implements IconElement
{
  private Layer layer;
  protected int x, y;
  private Rectangle[] bounds;
  private static final int fuz=4;
  public final static int X = 0;
  public final static int Y = 1;
  {
    expressions = new Object[2];
  }
  
  public IconPoint(int x, int y)
  {
    bounds = new Rectangle[1];    
    init(x,y);
  }

  @Override
  public String getShapeName() {
    return "Point";
  }
  
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"x","y"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[] {X, Y};
  }
  
  @Override
  public Object getExpression(int argIndex) {
    Object expression = super.getExpression(argIndex);
    if (expression != null)
      return expression;
    switch (argIndex) {
    case X:
      return new Integer(x);
    case Y:
      return new Integer(y);
    }
    return null;
  }
  
  @Override
  public void evaluateExpression(int argIndex, Evaluator evaluator) {
    int newValue = evaluator.evaluateInteger(expressions[argIndex]);
    switch(argIndex) {
    case X:
      x = newValue;
      break;
    case Y:
      y = newValue;
      break;
    }
    init(x,y);    
    ((ToolContainer)getParent()).invalidateElement(this);    
  }
  
  private void init(int x, int y) {
    this.x = x; this.y = y;
    bounds[0] = new Rectangle(x-fuz,y-fuz,fuz*2,fuz*2);
    setLocation(x-fuz,y-fuz);
    setSize(fuz*2,fuz*2);    
  }

  @Override
  public IconElement copy()
  {
    IconPoint copy = new IconPoint(x,y);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
    } catch (BadExpressionException bee) {
      Trace.exception(bee);
    }      
    return copy;
  }
  
  @Override
  public void shift (int shiftX, int shiftY)
  {
    Evaluator evaluator = getEvaluator();              
    if (evaluator != null) {
      try {
	setExpression(X, evaluator.addOffset(getExpression(X), shiftX));
	setExpression(Y, evaluator.addOffset(getExpression(Y), shiftY));
      } catch (BadExpressionException bee) {
	Trace.exception(bee);
      }	
    } else {
      //TBD
    }    
    layer.repaint();
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    g.setColor(color);
    g.drawLine(fuz,fuz,fuz,fuz);
  }

  public int[] getCoordinates() {
    return new int[] {x,y};
  }

  @Override
  public String toString () {
    return ("IconPoint [" + color + ", (" + x + "," + y + ")");
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return bounds;
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
