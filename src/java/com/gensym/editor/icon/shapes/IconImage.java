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

public class IconImage extends BasicDrawElement
implements IconElement
{
  private Layer layer;
  private Rectangle[] bounds;
  private Object imageLocation;
  Image cachedImage;
  {
    expressions = new Object[5];
  }
  public final static int X = 0;
  public final static int Y = 1;
  public final static int WIDTH = 2;
  public final static int HEIGHT = 3;  
  public static final int IMAGE_LOCATION = 4;
  
  
  public IconImage(Object imageLocation, Image image, int x, int y, int width, int height)
  {
    this.imageLocation = imageLocation;
    setBounds(x,y,width,height);
    setImage(image);
  }

  @Override
  public String getShapeName() {
    return "Image";
  }
  
  @Override
  public String[] getExpressionLabels() {
    return new String[] {"x","y","width","height","location"};
  }
  
  @Override
  public int[] getExpressionIndices() {
    return new int[] {X, Y, WIDTH, HEIGHT,IMAGE_LOCATION};
  }
  
  private void setImage(Image image) {
    cachedImage = image;
  }
  
  @Override
  public void setBounds(int x, int y, int width, int height) {
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x,y,width,height);
    super.setBounds(x,y,width,height);    
  }

  @Override
  public Object getExpression(int argIndex) {
    Object expression = super.getExpression(argIndex);
    Rectangle rect = bounds[0];
    if (expression != null)
      return expression;
    switch (argIndex) {
    case X:
      return new Integer(rect.x);
    case Y:
      return new Integer(rect.y);
    case WIDTH:
      return new Integer(rect.width);
    case HEIGHT:
      return new Integer(rect.height);
    case IMAGE_LOCATION:
      return imageLocation;
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
    case IMAGE_LOCATION:
      setImage(evaluator.evaluateImage(expressions[argIndex]));
      break;
    }
    ((ToolContainer)getParent()).invalidateElement(this);    
  }

  public Object getImageLocation() {
    return imageLocation;
  }
  
  @Override
  public IconElement copy()
  {
    Rectangle bounds = getExactBounds()[0];
    IconImage copy = new IconImage(imageLocation,cachedImage,
				   bounds.x, bounds.y,
				   bounds.width, bounds.height);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
      copy.setExpression(WIDTH, getExpression(WIDTH));
      copy.setExpression(HEIGHT, getExpression(HEIGHT));
      copy.setExpression(IMAGE_LOCATION, getExpression(IMAGE_LOCATION));
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
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }
  
  @Override
  public synchronized void paint (Graphics g)
  {
    Rectangle bounds = getExactBounds()[0];
    if (cachedImage != null)
      g.drawImage(cachedImage,0,0,bounds.width, bounds.height, null);
    else {
      g.setColor(Color.red);
      g.fillRect(0,0,bounds.width,bounds.height);
    }
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
