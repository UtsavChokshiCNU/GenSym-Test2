package com.gensym.icons;

import java.util.*;
import java.awt.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.io.StringReader;

public class PowerPoint extends PointOrArcPoint {

  private static final Symbol X_   = Symbol.intern("X");
  private static final Symbol Y_   = Symbol.intern("Y");
  private static final Symbol ARC_ = Symbol.intern("ARC");
  protected boolean isdynamic = false;
  private PointExpression varx;
  private PointExpression vary;

  public PowerPoint(int x, int y) {
    super(x,y);
    isdynamic = false;
    this.varx = new PointExpression(x);
    this.vary = new PointExpression(y);
  }
  public PowerPoint(int x, Symbol y) {
    super(x,0);
    this.isdynamic = true;
    this.varx = new PointExpression(x);
    this.vary = new PointExpression(y);

  }

  public PowerPoint(Symbol x, int y) {
    super(0,y);
    this.isdynamic = true;
    this.varx = new PointExpression(x);
    this.vary = new PointExpression(y);
  }
  
  public PowerPoint(Symbol x, Symbol y) {
    super(0,0);
    this.isdynamic = true;
    this.varx = new PointExpression(x);
    this.vary = new PointExpression(y);
  }

  public PowerPoint(Structure data) {
    super(0,0);
    arcPoint = ((Boolean)data.getAttributeValue(ARC_, Boolean.FALSE)).booleanValue();

    Object xval = data.getAttributeValue(X_, null);
    if (xval instanceof Integer) 
      this.x = ((Integer) xval).intValue();
    else {
      isdynamic = true;
      this.varx = new PointExpression(xval);
    }
    Object yval = data.getAttributeValue(Y_, null);
    if (yval instanceof Integer)
      this.y = ((Integer) yval).intValue();
    else {
      isdynamic = true;
      this.vary = new PointExpression(yval);
    }
  }
    
  public void eval(Structure variables, Structure overrides) {
    if (varx != null)
      this.x = varx.eval(variables, overrides);
    if (vary != null)
      this.y = vary.eval(variables, overrides);
  }

}

class PointExpression extends Object {

  private int staticvalue = 0;
  private Symbol expression;
  private int constant = 0;
  private Symbol[] variableNames;
  private boolean[] isPositive;

  protected PointExpression(int staticvalue) {
    this.staticvalue = staticvalue;
  }
  
  private static final Symbol PLUS_ = Symbol.intern("+");
  private static final Symbol MINUS_ = Symbol.intern("-");
  

  protected PointExpression(Object expression) {
    if (expression instanceof Integer)
      this.staticvalue = ((Integer) expression).intValue();
    else if (expression instanceof Symbol)
      this.expression = (Symbol) expression;
    else 
      parsePointExpression(expression);
  }

  private void parsePointExpression(Object expression)
  {
    StringReader reader = new StringReader((String)expression);
    Object o = null;
    try {
      o = Cons.read(reader);
    } catch (Exception e) 
      { e.printStackTrace(); }
    reader.close();
    if (o instanceof Cons &&
	((Cons)o).isProperList())
      {
	Cons list = (Cons)o;
	int i , len = list.properListLength(), varCount = 0;
	Vector stuff = new Vector();
	Cons tail = list;
	Symbol lastSign = PLUS_;
	for (i=0; i<len ; i++)
	  {
	    if (tail.car instanceof Symbol)
	      {
		Symbol symbol = (Symbol)tail.car;
		if (symbol.equals(PLUS_))
		  lastSign = PLUS_;
		else if (symbol.equals(MINUS_))
		  lastSign = MINUS_;
		else
		  {
		    stuff.addElement(lastSign);
		    stuff.addElement(symbol);
		  }
	      }
	    else if (tail.car instanceof Integer) {
	      constant = ((Integer)tail.car).intValue();
	      if (lastSign.equals(MINUS_))
 		constant = -constant;
	    }
	    tail = tail.tail();
	  }
	int size = stuff.size() / 2;
	variableNames = new Symbol[size];
	isPositive = new boolean[size];
	for (i=0; i<size ; i++)
	  {
	    isPositive[i]
	      = ((stuff.elementAt(2*i)).equals(PLUS_)) ? true : false;
	    variableNames[i] = (Symbol)(stuff.elementAt((2*i)+1));
	  }
      }
    else
      throw new RuntimeException("Bad PowerPoint Export "+expression);
  }

  protected int eval(Structure variables, Structure overrides)
  {
    if (variableNames != null)
      {
	int i,length = variableNames.length, total = constant;
	for (i = 0; i<length ; i++)
	  {
	    int value = evalSymbol(variables,overrides,variableNames[i]);
	    if (isPositive[i])
	      total += value;
	    else
	      total -= value;
	  }
	return total;
      }
    else if (expression != null)
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
      if (value != null)
	return ((Integer) value).intValue();
    }
    return staticvalue;
  }
}
       
    
