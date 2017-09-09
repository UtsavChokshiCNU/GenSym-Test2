package com.gensym.editor.icon.shapes;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconLine extends BasicDrawElement
implements IconElement
{
  private Layer layer;
  private Rectangle[] bounds;
  public final static int X1 = 0;
  public final static int Y1 = 1;
  public final static int X2 = 2;
  public final static int Y2 = 3;
  {
    expressions = new Object[4];
  }
  
  public IconLine(int x1, int y1, int x2, int y2)
  {
    init(x1,y1,x2,y2);
  }

  @Override
  public String getShapeName() {
    return "Line";
  }
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"x1","y1","x2","y2"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[] {X1, Y1, X2, Y2};
  }
  
  private int[] args = new int[4];
  private void init(int x1, int y1, int x2, int y2) {
    args[0]=x1;args[1]=y1;args[2]=x2;args[3]=y2;
    int low_x = x1, high_x = x2;
    int low_y = y1, high_y = y2; 

    if (x1 > x2) 
      {
	low_x = x2;
	high_x = x1;
      }
    if (y1 > y2)
      {
	low_y = y2;
	high_y = y1;
      }
    bounds = new Rectangle[1];
    int xExtra = (high_x == low_x ? 1 : 0);
    int yExtra = (high_y == low_y ? 1 : 0);
    bounds[0] = new Rectangle(low_x, low_y,
			      high_x - low_x + xExtra, high_y - low_y + yExtra);
    setLocation(low_x,low_y);
    setSize(high_x - low_x + xExtra, high_y - low_y + yExtra);
  }

  @Override
  public Object getExpression(int argIndex) {
    Object expression = super.getExpression(argIndex);
    if (expression != null)
      return expression;
    else
      return new Integer(args[argIndex]);
  }
  
  @Override
  public void evaluateExpression(int argIndex, Evaluator evaluator) {
    args[argIndex] = evaluator.evaluateInteger(expressions[argIndex]);
    init(args[0],args[1],args[2],args[3]);
    ((ToolContainer)getParent()).invalidateElement(this);    
  }
  
  @Override
  public IconElement copy()
  {
    IconLine copy = new IconLine(args[0],args[1],args[2],args[3]);
    try {
      copy.setExpression(X1, getExpression(X1));
      copy.setExpression(Y1, getExpression(Y1));
      copy.setExpression(X2, getExpression(X2));
      copy.setExpression(Y2, getExpression(Y2));
    } catch (BadExpressionException bee) {
      Trace.exception(bee);
    }
    return copy;    
  }

  public int[] getCoordinates() {
    return new int[] {args[0],args[1],args[2],args[3]};
  }
  
  @Override
  public void shift (int shiftX, int shiftY)
  {
    Evaluator evaluator = getEvaluator();              
    if (evaluator != null) {
      try {
	setExpression(X1, evaluator.addOffset(getExpression(X1), shiftX));
	setExpression(Y1, evaluator.addOffset(getExpression(Y1), shiftY));
	setExpression(X2, evaluator.addOffset(getExpression(X2), shiftX));
	setExpression(Y2, evaluator.addOffset(getExpression(Y2), shiftY));
      } catch (BadExpressionException bee) {
	Trace.exception(bee);
      }
    } else {
      //TBD
    }    
    layer.repaint();
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

  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle rect = bounds[0];
    g.setColor(color);
    g.drawLine(args[0] - rect.x ,args[1] - rect.y,
	       args[2] - rect.x ,args[3] - rect.y);
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    return bounds;
  }
  
}
