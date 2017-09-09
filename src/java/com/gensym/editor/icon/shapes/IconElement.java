package com.gensym.editor.icon.shapes;

import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.DrawElement;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.BadExpressionException;

/**
 * @author Paul B. Konigsberg
 */

public interface IconElement extends DrawElement 
{
  public Layer getLayer();
  public void setLayer(Layer layer);
  public IconElement copy();
  public void evaluateExpression(int argIndex, Evaluator evaluator);
  public void evaluateExpressions();
  public void setExpression(int argIndex, Object expression)
       throws BadExpressionException;
  public Object getExpression(int argIndex);
  public Object[] getExpressions();
  public Evaluator getEvaluator();
  public String getShapeName();
  public String[] getExpressionLabels();
  public int[] getExpressionIndices();

}
