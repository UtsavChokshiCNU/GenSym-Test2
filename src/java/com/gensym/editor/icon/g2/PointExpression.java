package com.gensym.editor.icon.g2;

import java.io.StringReader;
import java.util.Vector;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Cons;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.message.Trace;

public class PointExpression extends Object {
  private int staticvalue = 0;
  private Symbol expression;
  private int constant = 0;
  private Symbol[] variableNames;
  private boolean[] isPositive;
  private String pointExpression;

  protected PointExpression(int staticvalue) {
    this.staticvalue = staticvalue;
  }
  
  private static final Symbol PLUS_ = Symbol.intern("+");
  private static final Symbol MINUS_ = Symbol.intern("-");
  
  private String getCompiledExpression() {
    int length = variableNames.length;
    String expr="(";
    for (int i=0;i<length;i++){
      boolean positive = isPositive[i];
      if (!(i==0&&positive))
	expr+=(positive?" + ":" - ");
      expr+=variableNames[i];
    }
    if (constant != 0) {
      boolean negate = constant < 0;
      if (negate)
	constant=-constant;
      expr+=(negate?" - ":" + ");
      expr+=constant;
    }

    expr+=")";
    return expr;
  }
  
  protected PointExpression(Object expression)
  {
    if (expression instanceof Integer)
      this.staticvalue = ((Integer) expression).intValue();
    else if (expression instanceof Symbol)
      this.expression = (Symbol) expression;
    else if (expression instanceof String) {
      if (!(((String)expression).startsWith("(")) ||
	  !(((String)expression).endsWith("(")))
	expression = "("+expression+")";      
      this.pointExpression = (String)expression;
    }
    try {
      compile();
    } catch (InvalidPointExpressionException ipee) {
      Trace.exception(ipee);
    }
  }

  @Override
  public String toString() {
    if (pointExpression != null)
      return pointExpression;
    else if (expression != null)
      return expression.toString();
    else
      return staticvalue+"";
  }

  private static void addWithFiltering(Vector stuff,
				       Symbol lastSign,
				       Symbol symbol) {
    int index = stuff.indexOf(symbol);
    boolean offset=false;
    if (index >= 0) {
      Object offsetSign = PLUS_;
      if (index>0)
	offsetSign = stuff.elementAt(index-1);
      if (!offsetSign.equals(lastSign)) {
	offset = true;
	stuff.removeElementAt(index);
	if (index>0)
	  stuff.removeElementAt(index-1);
      }
    }
    if (!offset) {
      stuff.addElement(lastSign);
      stuff.addElement(symbol);
    }
  }
  
  private static Object[] compile(Cons list) {
    int len = list.properListLength();
    Vector stuff = new Vector();
    Cons tail = list;
    Symbol lastSign = PLUS_;
    
    int compiledConstant=0;    
    Symbol[] vNames;
    boolean[] positives;
    for (int i=0;i<len;i++){
      if (tail.car instanceof Symbol) {
	Symbol symbol = (Symbol)tail.car;
	if (symbol.equals(PLUS_))
	  lastSign = PLUS_;
	else if (symbol.equals(MINUS_))
	  lastSign = MINUS_;
	else {
	  addWithFiltering(stuff, lastSign, symbol);
	}
      } else if (tail.car instanceof Integer) {
	int lastConstant = ((Integer)tail.car).intValue();
	if (lastSign.equals(MINUS_))
	  lastConstant = -lastConstant;
	compiledConstant+= lastConstant;
      } else if (tail.car instanceof Cons){
	Object[] vals = compile((Cons)tail.car);
	boolean[] subPositives = (boolean[])vals[0];      
	Symbol[] subVariableNames = (Symbol[])vals[1];
	int subConstant = ((Integer)vals[2]).intValue();
	boolean negate = lastSign.equals(MINUS_);
	for (int j=0;j<subVariableNames.length;j++) {
	  boolean positive = subPositives[j];
	  if (negate)
	    positive = !positive;
	  addWithFiltering(stuff, positive?PLUS_:MINUS_,subVariableNames[j]);
	}
	if (negate)
	  subConstant = -subConstant;
	compiledConstant+=subConstant;
      } 
      tail = tail.tail();
    }
    int size = stuff.size() / 2;
    vNames = new Symbol[size];
    positives = new boolean[size];
    for (int i=0; i<size ; i++) {
      positives[i]
	= ((stuff.elementAt(2*i)).equals(PLUS_)) ? true : false;
      vNames[i] = (Symbol)(stuff.elementAt((2*i)+1));
    }
    return new Object[] {positives, vNames, new Integer(compiledConstant)};
  }

  public void compile() 
    throws InvalidPointExpressionException
  {
    if (pointExpression == null)
      return;
    StringReader reader = new StringReader(pointExpression);
    Object o = null;
    try {
      o = Cons.read(reader);
    } catch (Exception e) 
      { e.printStackTrace(); }
    reader.close();
    if (o instanceof Cons && ((Cons)o).isProperList()) {
      Cons list = (Cons)o;
      Object[] vals = compile(list);
      isPositive = (boolean[])vals[0];      
      variableNames = (Symbol[])vals[1];
      constant= ((Integer)vals[2]).intValue();
      int variableCount = variableNames.length;
      if (variableCount==1 && constant == 0 && isPositive[0]) {
	this.pointExpression = null;
	this.expression = variableNames[0];	
	variableNames = null;
	isPositive = null;
      } else if (variableCount==0) {
	this.pointExpression = null;
	this.expression = null;	
	variableNames = null;
	isPositive = null;
	this.staticvalue = constant;
      } else
	this.pointExpression = getCompiledExpression();
    } else {
      throw new InvalidPointExpressionException("Improper list " + pointExpression);
    }
  }

  protected int eval(Structure variables, Structure overrides) {
    if (variableNames != null) {
      int i,length = variableNames.length, total = constant;
      for (i = 0; i<length ; i++){
	int value = evalSymbol(variables,overrides,variableNames[i]);
	if (isPositive[i]) 
	  total += value;
	else 
	  total -= value;
      }
      return total;
    } else if (expression != null)
      return evalSymbol(variables,overrides,expression);
    else
      return staticvalue;
  }

  private int evalSymbol(Structure variables, Structure overrides,
			 Symbol name)
  {
    Object value = null;
    if (overrides != null) {
      value = overrides.getAttributeValue(name, null);
      if (value != null)
	return ((Integer) value).intValue();
    }
    if (variables != null) {
      value = variables.getAttributeValue(name, null);
      if (value != null) {
	value = ((Parameter)value).getDefaultValue();
	if (value != null)
	  return ((Integer) value).intValue();
      }
    }
    return staticvalue;
  }
}
