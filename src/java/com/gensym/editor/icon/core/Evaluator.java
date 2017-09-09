package com.gensym.editor.icon.core;

import java.awt.Font;
import java.awt.Image;
import java.awt.Component;
import java.awt.Frame;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.dlgs.TextDialog;

public interface Evaluator {
  public int evaluateInteger(Object expression);
  public boolean evaluateBoolean(Object expression);
  public Font evaluateFont(Object expression);
  public String evaluateText(Object expression);
  public Image evaluateImage(Object expression);
  public Object addOffset(Object expression, int offset);
  public Object subtractOffset(Object expression, int offset);
  public String getPrintedVersion(Object expression);
  public Object getExpression(String printedVersion);
  public void compileExpression(Object expression) throws BadExpressionException;
  public void addParameter(Parameter parameter);
  public boolean removeParameter(Parameter parameter);
  public Parameter[] getParameters();
  public void setParameters(Parameter[] parameters);
  public VariableTableModel getVariableTableModel();
  public Evaluator copy();
  public Component createEditComponent(Parameter parameter);
  public TextDialog getElementEditor(Frame frame, IconElement iconElement, IconEditorCanvas canvas);
}
