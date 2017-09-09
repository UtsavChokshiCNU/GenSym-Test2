package com.gensym.editor.icon.dlgs;

import com.gensym.dlg.InputDialog;
import com.gensym.dlg.MessageDialog;
import java.awt.Frame;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.editor.icon.core.UnknownVariableException;
import com.gensym.editor.icon.shapes.IconElement;

public class ExpressionEditDialog extends InputDialog {

  private static String editString = "Edit";
  private Evaluator evaluator;
  private int[] expressionIndices;
  private String[] initialValues;
  private IconElement element;
  private String[] labels;
  
  public ExpressionEditDialog(IconElement element,
			      String[] labels,
			      int[] expressionIndices,
			      Evaluator evaluator,
			      Frame frame)
  {
    this(element,
	 labels,
	 getInitialValues(element, evaluator, expressionIndices),
	 expressionIndices,
	 evaluator,
	 frame);
  }

  private ExpressionEditDialog(IconElement element,
			       String[] labels,
			       String[] initialValues,
			       int[] expressionIndices,
			       Evaluator evaluator,
			       Frame frame)
  {
    super(frame,editString+" "+element.getShapeName(),
	  false, labels, initialValues, null);
    this.element = element;    
    this.evaluator = evaluator;
    this.labels = labels;
    this.initialValues = initialValues;
    this.expressionIndices = expressionIndices;
  }
  
  private static String[] getInitialValues(IconElement element,
					   Evaluator evaluator,
					   int[] indices) {
    String[] initialValues = new String[indices.length];
    for (int i=0;i<indices.length;i++) 
      initialValues[i]=evaluator.getPrintedVersion(element.getExpression(indices[i]));
    return initialValues;
  }

  private boolean handleResults() {
    String[] results = getResults();
    boolean ok = true;
    for (int i=0;i<expressionIndices.length && ok;i++) 
      ok = handleResult(results[i], initialValues[i], evaluator,expressionIndices[i], element);
    return ok;
  }

  @Override
  protected void dispatchCallback (int code) {
    String[] results = getResults();
    if (!(code == CANCEL)) {
      if (handleResults()) 
	dispose();
      else
	setVisible(true);
    } else
      dispose();
  }
  
  private boolean handleResult(String newValue,
			       String oldValue,
			       Evaluator evaluator,
			       int expressionIndex,
			       IconElement element) {
    if (!oldValue.equals(newValue)) {
      try {
	element.setExpression(expressionIndex, evaluator.getExpression(newValue));
      } catch (UnknownVariableException uve) {
	MessageDialog md =
	  new MessageDialog((Frame)getParent(),
			    "Unknown variable within field ' " + labels[expressionIndex] + "'",
			    true, uve.getMessage() + "\n Would you like to define it now?",
			    null);
	md.setVisible(true);
	if (!md.wasCancelled()) {
	  //CanvasPropertiesDialog ved = new CanvasPropertiesDialog(frame,doc.getCanvas());
	  //ved.setTitle(doc.getTitle() + " properties");
	  //ved.setVisible(true);
	}
	return false;	
      } catch (BadExpressionException bee) {
	MessageDialog md =
	  new MessageDialog((Frame)getParent(),
			    "Bad Expression for field' " + labels[expressionIndex] + "'",
			    true, bee.getMessage(), null);
	md.setVisible(true);
	return false;	
      }
    }
    return true;
  }
  
}
