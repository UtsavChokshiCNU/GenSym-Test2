package com.gensym.editor.icon.g2;

import com.gensym.editor.icon.core.Evaluator;
import java.awt.Font;
import java.awt.Frame;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.shapes.IconElement;
import com.gensym.editor.icon.shapes.IconText;
import com.gensym.editor.icon.dlgs.TextDialog;
import java.awt.Image;
import java.net.URL;
import java.net.MalformedURLException;
import com.gensym.message.Trace;
import java.awt.Toolkit;
import com.gensym.util.Symbol;
import java.util.Hashtable;
import java.util.Enumeration;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.editor.icon.core.UnknownVariableException;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.VariableTableModel;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Component;
import javax.swing.JSlider;
import javax.swing.JComboBox;
import javax.swing.JTextField;
import java.util.Vector;
import javax.swing.DefaultComboBoxModel;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Structure;
import com.gensym.ntw.util.G2FontMap;
import com.gensym.editor.icon.g2.G2TextDialog;

public class G2ExpressionEvaluator implements Evaluator
{
  private Structure parameters = new Structure();
  
  public G2ExpressionEvaluator(Parameter[] params)
  {
    setParameters(params);
  }

  @Override
  public Evaluator copy() {
    Parameter[] paramsCopy = getParameters();
    G2ExpressionEvaluator copy = new G2ExpressionEvaluator(paramsCopy);
    return copy;
  }

  
  @Override
  public VariableTableModel getVariableTableModel() {
    return new G2ParameterTableModel(getParameters());
  }
  
  @Override
  public Parameter[] getParameters() {
    Enumeration e = parameters.getAttributeValues();
    int count = parameters.getAttributeCount();
    Parameter[] params = new Parameter[count];
    int i=count-1;
    while(e.hasMoreElements()) 
      params[i--]=(Parameter)e.nextElement();
    return params;
  }

  @Override
  public TextDialog getElementEditor(Frame frame, IconElement iconElement, IconEditorCanvas canvas) {
    if (iconElement instanceof IconText)
      return new G2TextDialog(frame, (IconText)iconElement, canvas);
    return null;
  }
  
  @Override
  public void setParameters(Parameter[] params) {
    parameters = new Structure();
    for (int i=0;i<params.length;i++) 
      addParameter(params[i]);
  }
  
  @Override
  public void addParameter(Parameter parameter) {
    Symbol name = Symbol.intern(parameter.getName().toUpperCase());
    if (parameters.getAttributeValue(name, null) == null)
      parameters.setAttributeValue(name, parameter);
  }

  @Override
  public boolean removeParameter(Parameter parameter) {
    Symbol name = Symbol.intern(parameter.getName().toUpperCase());
    if (parameters.getAttributeValue(name, null) == null)
      return false;
    else {
      parameters.deleteAttribute(name);
      return true;
    }
  }

  @Override
  public void compileExpression(Object expression)
       throws BadExpressionException
  {
    if (expression instanceof PointExpression) {
      try {
	((PointExpression)expression).compile();
      } catch (InvalidPointExpressionException ipee) {
	throw new BadExpressionException(ipee);
      }
    } else if (expression instanceof Number ||
	expression instanceof Boolean ||
	expression instanceof String ||
	expression instanceof Image)
      return;
    else if (expression instanceof Symbol) {
      if (parameters.getAttributeValue((Symbol)expression, null) == null)
	throw new UnknownVariableException(expression + " is not defined");
    } 
  }

  private Object getParameterValue(Symbol name) {
    try {
      return ((Parameter)parameters.getAttributeValue(name)).getDefaultValue();
    } catch (NoSuchAttributeException nsae) {
      //should really throw this
      Trace.exception(nsae);
      return null;
    }
  }

  @Override
  public int evaluateInteger(Object expression) {
    if (expression instanceof Symbol)
      return ((Integer)getParameterValue((Symbol)expression)).intValue();
    else if (expression instanceof PointExpression) {
      PointExpression exp = (PointExpression)expression;
      return exp.eval(parameters, null);
    }
    return ((Number)expression).intValue();    
  }
  
  @Override
  public boolean evaluateBoolean(Object expression) {
    if (expression instanceof Symbol)
      return ((Boolean)getParameterValue((Symbol)expression)).booleanValue();    
    else
      return ((Boolean)expression).booleanValue();
  }

  @Override
  public Font evaluateFont(Object expression) {
    if (expression instanceof Symbol && expression != Util.SMALL_ && expression != Util.LARGE_ && expression != Util.EXTRA_LARGE_) {
      Symbol font = (Symbol)getParameterValue((Symbol)expression);
      return (Font)G2FontMap.get(font);
    }
    if (expression instanceof Font)
      return (Font)expression;
    return null;
  }

  @Override
  public String evaluateText(Object expression){
    if (expression instanceof Symbol)
      return getParameterValue((Symbol)expression).toString();
    return expression.toString();
  }
  
  @Override
  public Image evaluateImage(Object expression) {
    //TBD    
    if (!(expression instanceof String))
      return null;
    String url =(String)expression;
    URL resolvedURL = null;
    if (url.startsWith("file")) {
      try {
	resolvedURL = new URL(url);
      } catch (MalformedURLException murle) {
	Trace.exception(murle);
      }
    } 
    Image image = null;
    if (resolvedURL != null)
      image = Toolkit.getDefaultToolkit().getImage(resolvedURL);
    return image;
  }
  
  @Override
  public Object addOffset(Object expression, int offset){
    if (offset < 0)
      return subtractOffset(expression, -offset);
    if (expression instanceof Number)
      return new Integer(((Number)expression).intValue() + offset);
    else if (expression instanceof PointExpression) {
      String exp = expression.toString();
      return new PointExpression(exp.substring(1,exp.length()-1)+" + "+offset);
    } else if (expression instanceof Symbol)
      return new PointExpression(expression+" + "+offset);
    else 
      return expression;
  }
  
  @Override
  public Object subtractOffset(Object expression, int offset) {
    if (expression instanceof Number)
      return new Integer(((Number)expression).intValue() - offset);
    else if (expression instanceof PointExpression) {
      String exp = expression.toString();
      return new PointExpression(exp.substring(1,exp.length()-1)+" - "+offset);      
    } else if (expression instanceof Symbol)
      return new PointExpression(expression+" - "+offset);      
    else
      return expression;    
  }

  @Override
  public String getPrintedVersion(Object expression) {
    return expression.toString();
  }
  
  @Override
  public Object getExpression(String printedVersion) {
    Object expression = null;
    try {
      expression = new Integer(printedVersion);
      return expression;
    } catch (NumberFormatException nfe) {
    }
    String lowercase = printedVersion.toLowerCase();
    if (lowercase.equals("true") || lowercase.equals("false"))
      return new Boolean(lowercase);

    try {
      expression = new URL(printedVersion);
      return printedVersion;
    } catch (MalformedURLException murle) {
      expression = null;
    }
    
    if (printedVersion.indexOf('+')>0 ||
	printedVersion.indexOf('-')>0 ||
	printedVersion.indexOf('(')>0 ||
	printedVersion.indexOf(')')>0)
      return new PointExpression(printedVersion);
       
    expression = Symbol.intern(printedVersion.toUpperCase());
    return expression;
  }

  class SliderParameterAdapter implements ChangeListener {
    private Parameter parameter;
    SliderParameterAdapter(Parameter parameter) {
      this.parameter = parameter;
    }

    @Override
    public void stateChanged(ChangeEvent ce) {
      JSlider slider = (JSlider)ce.getSource();
      int newValue = slider.getValue();
      parameter.setDefaultValue(new Integer(newValue));
    }
  }

  class ComboBoxParameterAdapter implements ActionListener {
    private Parameter parameter;
    ComboBoxParameterAdapter(Parameter parameter) {
      this.parameter = parameter;
    }

    @Override
    public void actionPerformed(ActionEvent ce) {
      JComboBox comboBox = (JComboBox)ce.getSource();
      Object newValue = comboBox.getSelectedItem();
      if (!(newValue instanceof Symbol))
	newValue = Symbol.intern(newValue.toString().toUpperCase());
      parameter.setDefaultValue(newValue);
    }    
  }

  class TextFieldParameterAdapter implements ActionListener {
    private Parameter parameter;
    TextFieldParameterAdapter(Parameter parameter) {
      this.parameter = parameter;
    }

    @Override
    public void actionPerformed(ActionEvent ce) {
      JTextField textField = (JTextField)ce.getSource();
      Object newValue = textField.getText();
      Class type = parameter.getType();
      if (type == com.gensym.util.Symbol.class)
	newValue = com.gensym.util.Symbol.intern(((String)newValue).toUpperCase());
      parameter.setDefaultValue(newValue);
    }    
  }

  private static final Symbol
  SMALL_ = Symbol.intern ("SMALL"),
    LARGE_ = Symbol.intern ("LARGE"),
    EXTRA_LARGE_ = Symbol.intern ("EXTRA-LARGE");
  private static Vector defaultSymbols = new Vector();
  static {
    defaultSymbols.addElement(SMALL_);
    defaultSymbols.addElement(LARGE_);
    defaultSymbols.addElement(EXTRA_LARGE_);
  }
  @Override
  public Component createEditComponent(Parameter parameter) {
    Component component = null;
    Class type = parameter.getType();
    if (type == Integer.class) {
      component = new JSlider(0, 100, ((Integer)parameter.getDefaultValue()).intValue());
      ((JSlider)component).setMajorTickSpacing(10);
      ((JSlider)component).setMinorTickSpacing(5);
      ((JSlider)component).setLabelTable(((JSlider)component).createStandardLabels(10,0));
      ((JSlider)component).setPaintTicks(true);
      ((JSlider)component).setPaintLabels(true);
      ((JSlider)component).addChangeListener(new SliderParameterAdapter(parameter));
    } else if (type == String.class) {
      component = new JTextField(parameter.getDefaultValue().toString());
      ((JTextField)component).addActionListener(new TextFieldParameterAdapter(parameter));
    } else if (type == com.gensym.util.Symbol.class) {
      Symbol sym = (Symbol)parameter.getDefaultValue();
      int choiceCount = defaultSymbols.size();
      boolean isDefault = defaultSymbols.contains(sym);
      if (!isDefault)
	choiceCount++;
      Object[] choices = new Object[choiceCount];
      defaultSymbols.copyInto(choices);
      if (!isDefault)
	choices[choiceCount-1] = sym;
      SymbolMutableComboBoxModel model = new SymbolMutableComboBoxModel(choices);
      model.setSelectedItem(sym);
      JComboBox cb = new JComboBox(model);
      cb.setEditable(true);
      cb.addActionListener(new ComboBoxParameterAdapter(parameter));
      component = cb;
    }
    return component;
  }

  class SymbolMutableComboBoxModel extends DefaultComboBoxModel {
    SymbolMutableComboBoxModel(Object[] defaultChoices) {
      for (int i=0;i<defaultChoices.length;i++) 
	addElement(defaultChoices[i]);
    }

    @Override
    public void insertElementAt(Object anObject, int index) {
      if (!(anObject instanceof com.gensym.util.Symbol))
	anObject = Symbol.intern(anObject.toString().toUpperCase());
      super.insertElementAt(anObject, index);
    }
  }
  
}
