package com.gensym.editor.icon.shapes;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Fillable;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconOval extends BasicDrawElement
implements IconElement,Fillable
{
  private Layer layer;
  private Rectangle[] bounds;
  protected boolean filled = false;
  public final static int X = 0;
  public final static int Y = 1;
  public final static int RADIUS_X = 2;
  public final static int RADIUS_Y = 3;
  public final static int FILLED = 4;
  {
    expressions = new Object[5];
  }
  
  public IconOval(int x, int y, int xRadius, int yRadius, boolean filled)
  {
    bounds = new Rectangle[1];
    setBounds(x-xRadius,y-yRadius,xRadius*2, yRadius*2);
    this.filled = filled;    
  }

  @Override
  public void setBounds(int x, int y, int width, int height) {
    bounds[0] = new Rectangle(x,y,width,height);
    super.setBounds(x,y,width,height);    
  }
  
  @Override
  public String getShapeName() {
    return "Oval";
  }
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"center X","center Y","radius X","radius Y","filled"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[] {X, Y, RADIUS_X, RADIUS_Y,FILLED};
  }
  
  @Override
  public Object getExpression(int argIndex) {
    Object expression = super.getExpression(argIndex);
    Rectangle rect = bounds[0];
    if (expression != null)
      return expression;
    switch (argIndex) {
    case X:
      return new Integer(rect.x+rect.width/2);
    case Y:
      return new Integer(rect.y+rect.height/2);
    case RADIUS_X:
      return new Integer(rect.width/2);
    case RADIUS_Y:
      return new Integer(rect.height/2);
    case FILLED:
      return filled?Boolean.TRUE:Boolean.FALSE;
    }
    return null;
  }
  
  @Override
  public void evaluateExpression(int argIndex, Evaluator evaluator) {
    Rectangle rect = bounds[0];
    switch (argIndex) {
    case X:
      int x = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(x-rect.width/2, rect.y, rect.width, rect.height);
      break;
    case Y:
      int y = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, y-rect.height/2, rect.width, rect.height);      
      break;
    case RADIUS_X:
      int xRadius = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, rect.y, xRadius*2, rect.height);            
      break;
    case RADIUS_Y:
      int yRadius = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, rect.y, rect.width, yRadius*2);                  
      break;
    case FILLED:
      setFilled(evaluator.evaluateBoolean(expressions[argIndex]));
      break;
    }
    ((ToolContainer)getParent()).invalidateElement(this);    
  }
  
  @Override
  public void setFilled(boolean filled)
  {
    this.filled = filled;
    ((ToolContainer)getParent()).invalidateElement(this);
  }

  @Override
  public boolean isFilled()
  {
    return filled;
  }
  
  @Override
  public IconElement copy()
  {
    Rectangle bounds = getExactBounds()[0];
    IconOval copy = new IconOval(bounds.x+bounds.width/2,
				 bounds.y+bounds.height/2,
				 bounds.width/2, bounds.height/2,
				 filled);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
      copy.setExpression(RADIUS_X, getExpression(RADIUS_X));
      copy.setExpression(RADIUS_Y, getExpression(RADIUS_Y));
      copy.setExpression(FILLED, getExpression(FILLED));
    } catch (BadExpressionException bee) {
      Trace.exception(bee);
    }
    return copy;    
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle bounds = getExactBounds()[0];
    g.setColor(layer.getColor());
    if (filled)
      g.fillOval(0,0, bounds.width, bounds.height);
    else
      g.drawOval(0,0, bounds.width-1, bounds.height-1);
  }

  @Override
  public void shift (int shiftX, int shiftY)
  {
    Rectangle rect = bounds[0];
    rect.translate(shiftX,shiftY);
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
    setLocation(rect.x, rect.y);
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
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }
  
}
