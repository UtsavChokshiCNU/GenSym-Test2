package com.gensym.editor.icon.shapes;

import java.awt.*;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Fillable;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconRectangle extends BasicDrawElement
implements IconElement,Fillable
{
  private boolean filled;
  private transient Layer layer;
  private Rectangle[] bounds;
  public final static int X = 0;
  public final static int Y = 1;
  public final static int WIDTH = 2;
  public final static int HEIGHT = 3;
  public final static int FILLED = 4;
  {
    expressions = new Object[5];
  }  
  
  public IconRectangle(int x, int y, int width, int height, boolean filled)
  {
    bounds = new Rectangle[1];    
    setBounds(x, y, width, height);
    this.filled = filled;
  }

  @Override
  public String getShapeName() {
    return "Rectangle";
  }
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"x","y","width","height","filled"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[] {X, Y, WIDTH, HEIGHT,FILLED};
  }
  
  @Override
  public void setBounds(int x, int y, int width, int height) {
    bounds[0] = new Rectangle(x,y,width,height);
    super.setBounds(x,y,width,height);    
  }

  @Override
  public Object getExpression(int argIndex) {
    Object expression = super.getExpression(argIndex);
    if (expression != null)
      return expression;
    Rectangle rect = bounds[0];    
    switch (argIndex) {
    case X:
      return new Integer(rect.x);
    case Y:
      return new Integer(rect.y);
    case WIDTH:
      return new Integer(rect.width);
    case HEIGHT:
      return new Integer(rect.height);
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
      setBounds(x, rect.y, rect.width, rect.height);
      break;
    case Y:
      int y = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, y, rect.width, rect.height);      
      break;
    case WIDTH:
      int width = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, rect.y, width, rect.height);            
      break;
    case HEIGHT:
      int height = evaluator.evaluateInteger(expressions[argIndex]);
      setBounds(rect.x, rect.y, rect.width, height);                  
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
    IconRectangle copy = new IconRectangle(bounds.x, bounds.y,
					   bounds.width, bounds.height,
					   filled);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
      copy.setExpression(WIDTH, getExpression(WIDTH));
      copy.setExpression(HEIGHT, getExpression(HEIGHT));
      copy.setExpression(FILLED, getExpression(FILLED));
    } catch (BadExpressionException bee) {
      Trace.exception(bee);
    }
    return copy;
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
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }
  
  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle bounds = getExactBounds()[0];
    g.setColor(layer.getColor());
    if (filled)
      g.fillRect(0,0,bounds.width, bounds.height);
    else
      g.drawRect(0,0,bounds.width-1, bounds.height-1);
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
