package com.gensym.editor.icon.shapes;

import java.awt.*;
import com.gensym.editor.icon.core.ToolContainer;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.message.Trace;

/**
 * @author Paul B. Konigsberg
 */

public class IconText extends BasicDrawElement
implements IconElement
{
  private Layer layer;
  private Rectangle[] bounds;
  private String text;
  private Font font;
  int height = 20, width = 50;
  public final static int X = 0;
  public final static int Y = 1;
  public final static int TEXT = 2;
  public final static int FONT = 3;
  {
      expressions = new Object[4];
  }
  public IconText(String text,
		  Font font,
		  int x, int y)
  {
    this.text = text;
    this.font = font;
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,width,height);
    setLocation(x,y-height);
    setSize(width,height);
  }
  
  public void setText(String text) {
    this.text = text;
  }

  public String getText() {
    return text;
  }

  @Override
  public void setFont(Font font) {
    this.font = font;
  }

  @Override
  public Font getFont() {
    return font;
  }

  @Override
  public String getShapeName() {
    return "Text";
  }
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"x", "y", "text", "font"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[]{X, Y, TEXT, FONT};
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
    case TEXT:
      return text;
    case FONT:
      return font;
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
    case TEXT:
      setText(evaluator.evaluateText(expressions[argIndex]));
      break;
    case FONT:
      setFont(evaluator.evaluateFont(expressions[argIndex]));
      break;
    }
    ((ToolContainer)getParent()).invalidateElement(this);      
  }
  
  @Override
  public IconElement copy()
  {
    Rectangle bounds = getExactBounds()[0];
    IconText copy = new IconText(text,
			font,
			bounds.x, bounds.y);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
      copy.setExpression(FONT, getExpression(FONT));
      copy.setExpression(TEXT, getExpression(TEXT));
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
    g.setColor(layer.getColor());
    if (font != null) 
      g.setFont(font);
    if (text != null)
      g.drawString(text, 0, 0+height);

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
