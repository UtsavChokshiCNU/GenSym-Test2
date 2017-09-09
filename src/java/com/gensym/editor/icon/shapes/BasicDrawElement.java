package com.gensym.editor.icon.shapes;

import java.awt.Component;
import java.awt.Container;
import java.awt.Color;
import java.awt.Point;
import java.awt.Rectangle;
import com.gensym.editor.icon.core.DrawElement;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.BadExpressionException;

public abstract class BasicDrawElement extends Component
implements DrawElement
{
  protected transient ToolContainer canvas = null;
  protected Color color = Color.black;
  protected static int argCount;
  protected Object[] expressions;

  @Override
  public boolean contains(int x, int y) {
    if (isVisible())
      return super.contains(x,y);
    else
      return false;
  }

  public Evaluator getEvaluator() {
    if (canvas instanceof IconEditorCanvas)
      return ((IconEditorCanvas) canvas).getEvaluator();
    else
      return null;
  }  

  public void evaluateExpressions() {
    Evaluator evaluator = getEvaluator();
    if (evaluator != null && expressions != null) {
      for (int i=0;i<expressions.length;i++) {
	if (expressions[i] != null)
	  evaluateExpression(i, evaluator);
      }
    }
  }
  
  public abstract void evaluateExpression(int argIndex, Evaluator evaluator);
  
  public void setExpression(int argIndex, Object expression)
       throws BadExpressionException {
    Evaluator evaluator = getEvaluator();
    if (evaluator != null) {
      evaluator.compileExpression(expression);
      Object oldValue = expressions[argIndex];
      try {
	expressions[argIndex] = expression;
	if (expression != null)
	  evaluateExpression(argIndex, evaluator);
      } catch (ClassCastException cce) {
	expressions[argIndex]=oldValue;
	throw new BadExpressionException("Expression should not evaluate to a(n) " + cce.getMessage());
      }
    } else {
      //when we clone we may not have a canvas yet
      expressions[argIndex] = expression;
    }
  }

  public Object[] getExpressions() {
    int exprCount = expressions.length;
    Object[] expr = new Object[exprCount];
    for (int i=0;i<exprCount;i++)
      expr[i]=getExpression(i);
    return expr;
  }
  
  public Object getExpression(int argIndex) {
    return expressions[argIndex];
  }

  @Override
  public void shift(int dx, int dy) {
    Point location = getLocation();
    setLocation(location.x+dx,location.y+dy);
  }
  
  @Override
  public void setCanvas(ToolContainer canvas)
  {
    this.canvas = canvas;
  }

  @Override
  public Rectangle[] getExactBounds ()
  {
    Rectangle[] res = new Rectangle[1];
    res[0] = new Rectangle(0 , 0, 100, 100);

    return res;
  }
  @Override
  public void changeColor(Color color) {
    this.color = color;
    if (canvas != null)
      canvas.repaint();
  }    

  @Override
  public Container getParent () {
    return canvas;
  }

}


