package com.gensym.g2script;

import antlr.CommonAST;
import com.gensym.classtools.*;
import java.util.Vector;
import java.util.Hashtable;
import java.lang.reflect.Method;
import java.beans.PropertyDescriptor;
import java.beans.IntrospectionException;
import java.beans.Introspector; 
import java.beans.BeanInfo; 

public class ValueNode extends TreeWalker implements G2ScriptTokenTypes, RuntimeConstants
{
  Type type;
  String operator;
  Expression expression;
  Vector subExpressions = new Vector();
  static Hashtable operatorNameTable = new Hashtable();
  private static boolean debug = false;

  static {
    operatorNameTable.put("+","add");
    operatorNameTable.put("-","subtract");
    operatorNameTable.put("*","multiply");
    operatorNameTable.put("/","divide");
    operatorNameTable.put(">","greater");
    operatorNameTable.put("<","less");
    operatorNameTable.put(">=","greaterOrEqual");
    operatorNameTable.put("<=","lessOrEqual");
    operatorNameTable.put("&&","and");
    operatorNameTable.put("||","or");
  }

  ValueNode (Type type, String operator)
  {
    this.type = type;
    this.operator = operator;
  }

  ValueNode (Type type, Expression expression, G2ScriptAST ast)
  {
    if (type == null)
      throw new IllegalArgumentException("type was null");
    this.type = type;
    this.expression = expression;
    if (ast != null)
      expression.setLineNumber(ast.getLineNumber());
  }

  static ValueNode compileExpression(CommonAST expressionAST, Compiler c)
       throws CompilerException
  {
    return compileExpression((G2ScriptAST)expressionAST,c);
  }
  
  static ValueNode compileExpression(G2ScriptAST expressionAST, Compiler c)
       throws CompilerException
  {
    G2ScriptAST argAST1 = child(expressionAST), argAST2, designationAST;
    ValueNode arg1, arg2;
    int tokenType = expressionAST.getType();
    switch (tokenType)
      {
      case WHOLE_STRING_LITERAL:
	String string = (String)expressionAST.getValue();
	return new ValueNode(c.stringType,
			     new Value(string),
			     expressionAST);
      case INTEGER_LITERAL:
	Integer iValue = (Integer) expressionAST.getValue();
	return new ValueNode(c.primIntType,
			     new Value(iValue.intValue()),
			     expressionAST);
      case FLOAT_LITERAL:
	Double dValue = (Double) expressionAST.getValue();
	return new ValueNode(c.primDoubleType,
			     new Value(dValue.doubleValue()),
			     expressionAST);
      case TRUTH_VALUE_LITERAL:
	Boolean bValue = (Boolean) expressionAST.getValue();
	return new ValueNode(c.primBooleanType,
			     new Value(bValue.booleanValue()),
			     expressionAST);
      case PLUS:
      case MINUS:
	argAST2 = sibling(argAST1);
	if (argAST2 == null) // unary operation case
	  {
	    arg2 = compileExpression(argAST1,c);
	    // arg2.setLineNumber(argAST1,c);
	    arg1 = new ValueNode(c.typeForName("int"),
				 new Value(0),
				 argAST1);
	    // arg1.setLineNumber(argAST1,c);
	  }
	else
	  {
	    arg1 = compileExpression(argAST1,c);
	    arg2 = compileExpression(argAST2,c);
	  }
	if (isG2Number(c,arg1.type) && isG2Number(c,arg2.type))
	  return makeBinaryOperation(c,expressionAST,arg1,arg2);
	else
	  throw new CompilerException("non numeric types for "+expressionAST);
      case EQUALS:
      case NOT_EQUAL:
	try
	  {
	    argAST2 = sibling(argAST1);
	    arg1 = compileExpression(argAST1,c);
	    arg2 = compileExpression(argAST2,c);
	    if (arg1.type.isPrimitive() &&
		arg2.type.isPrimitive() &&
		arg1.type.equals(arg2.type))
	      {
		return 
		  new ValueNode(c.primBooleanType,
				new OperatorCall((tokenType == EQUALS ?
						  "==" : "!="),
						 new Expression[] { arg1.expression,
								      arg2.expression}),
				expressionAST);
	      }
	    else
	      {
		Expression exp1, exp2;
	        exp1 = c.castForAssignment(argAST1,arg1,
					   c.objectType," equality argument");
		exp2 = c.castForAssignment(argAST2,arg2,
					   c.objectType," equality argument");
		return 
		  new ValueNode(c.primBooleanType,
				makeStaticCall("com.gensym.g2scriptruntime.Math",
					       (tokenType == EQUALS ?
						"equal" : "notEqual"),
					       "(Ljava/lang/Object;Ljava/lang/Object;)Z",
					       exp1,exp2),
				expressionAST);
	      }
	  } catch (ClassException e)
	    {
	      e.printStackTrace();
	      throw new RuntimeException("Internal Compiler Failure");
	    }
      case TIMES:
      case GREATER:
      case LESS:
      case GREATER_EQUAL:
      case LESS_EQUAL:
	argAST2 = sibling(argAST1);
	arg1 = compileExpression(argAST1,c);
	// arg1.setLineNumber(argAST1.getLineNumber());
	arg2 = compileExpression(argAST2,c);
	// arg2.setLineNumber(argAST2.getLineNumber());
	boolean isValidArg1 = isG2Number(c,arg1.type) || (tokenType != TIMES && arg1.type.equals(c.stringType));
	boolean isValidArg2 = isG2Number(c,arg2.type) || (tokenType != TIMES && arg2.type.equals(c.stringType));
	
	if (isValidArg1 && isValidArg2)
	  return makeBinaryOperation(c,expressionAST,arg1,arg2);
	else
	  throw new CompilerException("incompatible types for "+expressionAST);
      case SLASH: // a.k.a divide
	argAST2 = sibling(argAST1);
	arg1 = compileExpression(argAST1,c);
	arg2 = compileExpression(argAST2,c);
	if (isG2Number(c,arg1.type) && isG2Number(c,arg2.type))
	  try
	  {
	    Expression dividend, divisor;
	    if (arg1.type.equals(c.primDoubleType))
	      dividend = arg1.expression;
	    else if (arg1.type.equals(c.primIntType))
	      dividend = new Cast("D",arg1.expression);
	    else
	      dividend = makeStaticCall("com.gensym.g2scriptruntime.Math",
					"extractDoubleFromNumber",
					"(Ljava/lang/Object;)D",
					arg1.expression);
	    if (arg2.type.equals(c.primDoubleType))
	      divisor = arg2.expression;
	    else if (arg2.type.equals(c.primIntType))
	      divisor = new Cast("D",arg2.expression);
	    else
	      divisor = makeStaticCall("com.gensym.g2scriptruntime.Math",
				       "extractDoubleFromNumber",
				       "(Ljava/lang/Object;)D",
				       arg2.expression);
	    return
	      new ValueNode(c.primDoubleType,
			    new OperatorCall("/",
					     new Expression[] { dividend, 
								  divisor }),
			    expressionAST);
	  } catch (ClassException e)
	    {
	      e.printStackTrace();
	      throw new RuntimeException("Internal Compiler Failure");
	    }
	else
	  throw new CompilerException("non numeric types for "+expressionAST);
      case OR:
      case AND:
	argAST2 = sibling(argAST1);
	arg1 = compileExpression(argAST1,c);
	arg2 = compileExpression(argAST2,c);
	if (isG2Boolean(c,arg1.type) && isG2Boolean(c,arg2.type))
	  return makeBinaryLogicalOperation(c,expressionAST,arg1,arg2);
	else
	  throw new CompilerException("non truth-values for "+expressionAST);
      case NOT:
	try {
	  arg1 = compileExpression(argAST1,c);
	  Expression booleanExp = null;
	  if (arg1.type.equals(c.primBooleanType))
	    booleanExp = arg1.expression;
	  else if (arg1.type.equals(c.objectType) ||
		   arg1.type.equals(c.booleanType))
	    booleanExp = makeStaticCall("com.gensym.g2scriptruntime.Math",
					"extractBooleanFromObject",
					"(Ljava/lang/Object;)Z",
					arg1.expression);
	  else
	    throw new CompilerException(argAST1+" is not a truth-value");
	  return new ValueNode(c.primBooleanType,
			       new OperatorCall("!", new Expression []
						{ booleanExp }),
			       expressionAST);
	} catch (ClassException ce)
	  {
	    System.out.println("Internal error:"+ ce.getMessage());
	    ce.printStackTrace();
	    throw new RuntimeException("Internal Compiler Failure");
	  }
      case CALL:
	return compileCall(expressionAST,c);
      case OF:
	return compileFieldAccess(expressionAST,c);
      case SEQUENCE:
	return compileSequenceConstructor(expressionAST,c);
      case STRUCTURE:
	return compileStructureConstructor(expressionAST,c);
      case IS:
	return compileDesignationPredicate(expressionAST,false,c);
      case EXIST:
      case EXISTS:
	return compileDesignationPredicate(expressionAST,true,c);
      case CONNECTED:
	return compileConnectionExpression(expressionAST,c);
      case UPON:
	return compileUponExpression(expressionAST,c);
      case ANY:
	if (c.compilingRule)
	  return null; //compileAny()
	else
	  throw new CompilerException("Cannot use ANY in procedures and Methods");
      case TIME:
	return compileTimeExpression(expressionAST,c);
      case ELEMENTS:
	arg1 = compileExpression(argAST1,c);
	if (!c.objectType.isAssignableFrom(arg1.type))
	  throw new CompilerException("Can only get number of elements of sequence or list");
	return new ValueNode(c.primIntType,
			     makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					    "sequenceOrListLength",
					    "(Ljava/lang/Object;)I",
					    arg1.expression),
			     expressionAST);
      case RECEIVES:
	designationAST = child(expressionAST);
	ValueNode compiledDesignation = compileExpression(designationAST,c);
	try {
	  return new ValueNode(c.primBooleanType,
			       new OperatorCall("!=",
						new Expression[]
						{ c.castForAssignment(designationAST,
								      compiledDesignation,
								      c.objectType,
								      "receives-a-value event detection"),
						    new Value((Object)null)
						    }),
			       designationAST);
	} catch (ClassException e)
	  {
	    throw new RuntimeException("Internal Compiler Failure");
	  }
      case HAS:
	// The following form is guaranteed by the rule 
	// (HAS <local-reference> <event-name> <local-refernce>)
	designationAST = child(expressionAST); // must be a LOCAL_REFERENCE
	G2ScriptAST eventNameAST = sibling(designationAST);  // ignored at compile time
	G2ScriptAST eventBindingAST = sibling(eventNameAST); // must be a LOCAL_REFERENCE
	ValueNode compiledSourceBinding = compileExpression(designationAST,c);
	ValueNode compiledEventBinding = compileExpression(eventBindingAST,c);
	try {
	  ValueNode compiledEventSource 
	    = new ValueNode(c.objectType,
			    makeInstanceCall(false,
					     compiledEventBinding.expression,
					     "java.util.EventObject", 
					     "getSource", 
					     "()Ljava/lang/Object;"),
			    expressionAST);
	  Expression assignmentExression
	    = new OperatorCall("=",
			       new Expression[]
			       { compiledSourceBinding.expression, 
				  c.castForAssignment(designationAST,
						      compiledEventSource,
						      compiledSourceBinding.type,
						      "generic event detection") });
	  return new ValueNode(c.primBooleanType,
			       new OperatorCall("!=",
						new Expression[]
						{ assignmentExression,
						    new Value((Object)null) }),
			       expressionAST);
	} catch (ClassException e)
	  {
	    throw new RuntimeException("Internal Compiler Failure");
	  }

      case UNRESERVED:
	String head = expressionAST.toString();
	if (debug)
	  System.out.println("UNRESERVED symbol expression case "+expressionAST);
	if (head.equals("LOCAL_REFERENCE"))
	  {
	    String g2Name = child(expressionAST).toString();
	    LocalVariable local = c.getLocal(g2Name,false);
	    FieldRef binding;
	    try {
	      if (local == null)
		{
		  if (c.compilingRule &&
		      (binding = c.getBinding(g2Name)) != null)
		    return new ValueNode(Type.forDescriptor(c,binding.getDescriptor()),
					 binding,
					 expressionAST);
		  else if (c.compilingRule ||
			   c.allowGlobals())
		    {
		      if (debug)
			System.out.println("compiling global lookup on "+g2Name);
		      MethodCall lookupCall 
			= makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					 "lookupObject",
					 "(Ljava/lang/String;Ljava/lang/Object;)"+
					 "Ljava/lang/Object;",
					 new Value(g2Name),
					 c.makeThisVariable());
		      return new ValueNode(c.objectType,
					   lookupCall,
					   expressionAST);
		    }
		  else
		    throw new CompilerException("undefined local "+g2Name);
		}
	      else if (local.isThis)
		return new ValueNode(local.type,
				     new Variable(0,local.type.makeDescriptor()),
				     child(expressionAST));
	      else
		return new ValueNode(local.type,
				     new Variable(local.javaName,
						  local.type.makeDescriptor()),
				     child(expressionAST));
	    }
	    catch (ClassException e)
	      {
		e.printStackTrace();
		throw new RuntimeException("classtools nested failure "+e.getMessage());
	      }
	  }
	else if (head.equals("FORMAT_FORM"))
	  return compileStringConcatenation(expressionAST,c);
	else if (head.equals("SYMBOL_LITERAL"))
	  return compileSymbolLiteral(expressionAST,c);
	else if (head.equals("ARRAY_REFERENCE"))
	  return compileArrayReference(expressionAST,c);
	else if (head.equals("INTERVAL"))
	  return compileInterval(expressionAST,c);
	else if (head.equals("FUNCTION_CALL"))
	  return Functions.compileFunction(expressionAST,c);
	else 
	  throw new RuntimeException("unhandled expression "+expressionAST);
	default:
      }
    throw new RuntimeException("unhandled expression "+expressionAST);
  }

  static boolean isG2Number(Compiler c,Type type)
  {
    return (type.isNumeric() || c.numberType.isAssignableFrom(type) ||
	    type.equals(c.objectType));
  }

  static boolean isG2Boolean(Compiler c, Type type)
  {
    return (type.equals(c.booleanType) || type.equals(c.objectType) ||
	    type.equals(c.primBooleanType));
  }
       

  static ValueNode compileFieldAccess(G2ScriptAST fieldAST, Compiler c)
       throws CompilerException
  {
    G2ScriptAST fieldNameAST = child(fieldAST);
    G2ScriptAST objectOrClassAST = null, localNameAST = null;
    if (siblingCount(fieldNameAST) == 1)
       objectOrClassAST = sibling(fieldNameAST);
    else
      {
	if (!c.compilingRuleAntecedent)
	  throw new CompilerException("Name binding is not yet supported");
	localNameAST = sibling(fieldNameAST);
	objectOrClassAST = sibling(localNameAST);
      }
    String fieldName = c.makeJavaName(fieldNameAST.toString(),false);
    ValueNode compiledFieldAccess;
    if (objectOrClassAST.toString().equals("CLASS"))
      compiledFieldAccess 
	= compileStaticFieldAccess(fieldAST,fieldName,objectOrClassAST,c);
    else
      compiledFieldAccess 
	= compileInstanceFieldAccess(fieldAST,fieldName,objectOrClassAST,c);
    if (localNameAST == null)
      return compiledFieldAccess;
    else
      {
	try {
	  ValueNode compiledLocal = compileExpression(localNameAST,c);
	  Expression assignmentExpression
	    = new OperatorCall("=",
			       new Expression[]
			       { compiledLocal.expression,
				   c.castForAssignment(fieldAST,
						       compiledFieldAccess,
						       compiledLocal.type,
						       "attribute access binding to "+
						       child(localNameAST).toString())
				   }); // need cast
	  return new ValueNode(compiledLocal.type,
			       assignmentExpression,
			       fieldAST);
	}
	catch (ClassException e)
	  {
	    throw new RuntimeException("Internal Compiler Failure");
	  }
      }
  }

  static ValueNode compileStaticFieldAccess(G2ScriptAST fieldAST, String fieldName, 
					    G2ScriptAST classAST, Compiler c)
       throws CompilerException
  {
    Type type = c.compileTypeDeclaration(classAST);
    if (type == null)
      throw new CompilerException("unknown class for static field reference");
    Type fieldType = type.getFieldType(fieldName,false,true);
    if (type != null)
      try 
      {
	FieldRef fieldRef = new FieldRef(type.getName(),
					 fieldName,
					 fieldType.makeDescriptor(),
					 true);
	return new ValueNode(fieldType, fieldRef, fieldAST);
      } catch (ClassException e)
	{
	  throw new RuntimeException("Internal Compiler Failure");
	}
    else // compile into slow, painful run-time lookup
      return new ValueNode(c.objectType,
			   makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					  "getStaticField",
					  "(Ljava/lang/String;Ljava/lang/String;)"+
					  "Ljava/lang/Object;",
					  new Value(type.getName()),
					  new Value(fieldName)),
			   fieldAST);
  }

  static ValueNode compileInstanceFieldAccess(G2ScriptAST fieldAST, String fieldName,
					      G2ScriptAST objectAST, Compiler c)
       throws CompilerException
  {
    ValueNode compiledObject = compileExpression(objectAST,c);
    Type type = compiledObject.type.getFieldType(fieldName,false,false);
    ClassInfoFactory factory = c.classInfoFactory;
    PropertyDescriptor propertyDescriptor = null;
    if (type != null)
      try 
      {
	FieldRef fieldRef = new FieldRef(compiledObject.expression,
					 fieldName,
					 type.makeDescriptor());
	return new ValueNode(type, fieldRef, fieldAST);
      } catch (ClassException e)
	{
	  throw new RuntimeException("Internal Compiler Failure");
	}
    else if (factory != null &&
	     compiledObject.type.isInterface() &&
	     factory.interfaceHasImplicitProperties(compiledObject.type.getName()))
      return compileImplicitFieldAccess(compiledObject,fieldAST,fieldName,
					objectAST,c);
    else if ((propertyDescriptor 
	      = getPropertyDescriptor(compiledObject.type,fieldName))
	     != null)
      return compilePropertyAccess(compiledObject,fieldAST,propertyDescriptor,c);
    else // compile into slow, painful run-time lookup
      return new ValueNode(c.objectType,
			   makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					  "getInstanceField",
					  "(Ljava/lang/Object;Ljava/lang/String;)"+
					  "Ljava/lang/Object;",
					  compiledObject.expression,
					  new Value(fieldName)),
			   fieldAST);
  }

  static ValueNode compileImplicitFieldAccess(ValueNode compiledObject,
					      G2ScriptAST fieldAST, String fieldName,
					      G2ScriptAST objectAST, Compiler c)
       throws CompilerException
  {
    String g2AttributeName = child(fieldAST).toString();
    ClassInfoFactory factory = c.classInfoFactory;
    String propertyGetterName 
      = factory.getImplicitPropertyGetter(compiledObject.type.getName(),
					  g2AttributeName);
    Type returnType = compiledObject.type.getMethodReturnType(propertyGetterName,false);
    if (returnType != null)
      {
	return new ValueNode(returnType,
			     makeInstanceCall(true,
					      compiledObject.expression,
					      compiledObject.type.getName(),
					      propertyGetterName,
					      "()"+returnType.makeDescriptor()),
			     fieldAST);
      }
    else
      // eventually join runtime field lookup case
      throw new CompilerException("Attribute "+g2AttributeName+" not found in "+
				  compiledObject.type.getName());
    

  }

  static PropertyDescriptor getPropertyDescriptor(Type objectType,String fieldName)
  {
    try {
      Class c = Class.forName(objectType.getName());
      if (debug)
	System.out.println("##### Looking for bean prop for "+fieldName+
			   " for class "+c);
      BeanInfo info = Introspector.getBeanInfo(c);
      PropertyDescriptor[] descriptors = info.getPropertyDescriptors();
      int i,len = descriptors.length;
      for (i=0; i<len; i++)
	{
	  if (debug)
	    System.out.println("  ##### desc name = "+descriptors[i].getName());
	  if (descriptors[i].getName().equals(fieldName) &&
	      descriptors[i].getReadMethod() != null)
	    {
	      if (debug)
		System.out.println("  ##### Found bean prop for "+fieldName);
	      return descriptors[i];
	    }
	}
      return null;
    } catch (ClassNotFoundException cnfe)
      {
	return null;
      }
    catch (IntrospectionException ie)
      {
	return null;
      }
  }

  static ValueNode compilePropertyAccess(ValueNode compiledObject,
					 G2ScriptAST fieldAST,
					 PropertyDescriptor propertyDescriptor,
					 Compiler c)
       // compileImplicitFieldAccess(ValueNode compiledObject,
       //	     G2ScriptAST fieldAST, String fieldName,
       //	     G2ScriptAST objectAST, Compiler c)
       throws CompilerException
  {
    Method readMethod = propertyDescriptor.getReadMethod();
    Type returnType = c.typeForName(readMethod.getReturnType().getName());
    String g2AttributeName = child(fieldAST).toString();
    String propertyGetterName = readMethod.getName();
    if (returnType != null)
      {
	return new ValueNode(returnType,
			     makeInstanceCall(true,
					      compiledObject.expression,
					      compiledObject.type.getName(),
					      propertyGetterName,
					      "()"+returnType.makeDescriptor()),
			     fieldAST);
      }
    else
      // eventually join runtime field lookup case
      throw new CompilerException("Attribute "+g2AttributeName+" not found in "+
				  compiledObject.type.getName());
    

  }
  
  static ValueNode compileSequenceConstructor(G2ScriptAST expressionAST,
					      Compiler c)
       throws CompilerException
  {
    G2ScriptAST argAST = child(expressionAST);
    int i = 0, length = siblingCount(argAST) + 1;
    if (debug)
      System.out.println("building "+length+" arg sequence");
    Expression[] newArrayArgs = null;
    if (argAST != null) {
      newArrayArgs = new Expression[length];
      while (argAST != null)
	{
	  if (debug)
	    System.out.println("sequence arg loop "+i+" arg "+argAST.toString());
	  ValueNode elementNode
	    = wrapAsNumber(c,compileExpression(argAST,c),true);
	  newArrayArgs[i] = elementNode.expression;
	  i++;
	  argAST = sibling(argAST);
	}
    } 
    try {
      NewArray argArray = null;
      if (newArrayArgs == null)
	argArray = new NewArray("[Ljava.lang.Object;", new int[] {0});
      else
	argArray = new NewArray("[Ljava.lang.Object;",newArrayArgs);
      return 
	new ValueNode(c.sequenceType,
		      makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				     "makeSequence",
				     "([Ljava/lang/Object;)Lcom/gensym/util/Sequence;",
				     argArray),
		      expressionAST);
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  static ValueNode compileStructureConstructor(G2ScriptAST expressionAST,
					       Compiler c)
       throws CompilerException
  {
    G2ScriptAST nameAST = child(expressionAST);
    G2ScriptAST valueAST;
    int i = 0, count = siblingCount(nameAST) + 1;
    Expression[] nameExpressions = new Expression[count/2],
      valueExpressions = new Expression[count/2];
    while (nameAST != null)
      {
	nameExpressions[i] = c.getOrMakeSymbolConstant(nameAST.toString());
	valueAST = sibling(nameAST);
	ValueNode compiledValue 
	  = wrapAsNumber(c,compileExpression(valueAST,c),true);
	valueExpressions[i] = compiledValue.expression;
	nameAST = sibling(valueAST);
	i++;
      }
    try {
      NewArray nameArray = new NewArray("[Lcom/gensym/util/Symbol;",nameExpressions);
      NewArray valueArray = new NewArray("[Ljava.lang.Object;",valueExpressions);
      return 
	new ValueNode(c.structureType,
		      makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				     "makeStructure",
				     "([Lcom/gensym/util/Symbol;[Ljava/lang/Object;)"+
				     "Lcom/gensym/util/Structure;",
				     nameArray,
				     valueArray),
		      expressionAST);
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  static ValueNode compileInterval(G2ScriptAST intervalAST, Compiler c)
       throws CompilerException
  {
    G2ScriptAST quantityAST = child(intervalAST);
    G2ScriptAST unitAST;
    double interval = 0.0;
    while (quantityAST != null)
      {
	double unscaledValue = ((Number)quantityAST.getValue()).doubleValue();
	if (unscaledValue < 0.0)
	  throw new CompilerException("Intervals must be non-negative "+unscaledValue);
	unitAST = sibling(quantityAST);
	switch (unitAST.getType())
	  {
	  case WEEK:
	  case WEEKS:
	    interval += unscaledValue * 604800.0;
	    break;
	  case DAY:
	  case DAYS:
	    interval += unscaledValue * 86400.0;
	    break;
	  case HOUR:
	  case HOURS:
	    interval += unscaledValue * 3600.0;
	    break;
	  case MINUTE:
	  case MINUTES:
	    interval += unscaledValue * 60.0;
	    break;
	  case SECOND:
	  case SECONDS:
	    interval += unscaledValue;
	    break;
	  default:
	  }
	quantityAST = sibling(unitAST);
      }
    return new ValueNode(c.primDoubleType,new Value(interval),intervalAST);
  }

  static ValueNode compileArrayReference(G2ScriptAST arrayRefAST, Compiler c)
       throws CompilerException
  {
    G2ScriptAST designationAST = child(arrayRefAST);
    G2ScriptAST indexAST = sibling(designationAST);
    ValueNode compiledArray = compileExpression(designationAST,c);
    ValueNode compiledIndex = compileExpression(indexAST,c);
    if (compiledArray.type.equals(c.sequenceType))
      {
	if (c.canPerformNumericOrLogicalAssignment(c.primIntType, 
						   compiledIndex.type))
	  {
	    Expression indexExp = wrapAsIntExpression(c,compiledIndex);
	    MethodCall call
	      = makeInstanceCall(false,
				 compiledArray.expression,
				 "java.util.Vector",
				 "elementAt",
				 "(I)Ljava/lang/Object;",
				 compiledIndex.expression);
	    return new ValueNode(c.typeForName("java.lang.Object"),
				 call,
				 arrayRefAST);
	  }
	else
	  throw new CompilerException("Non-integral sequence/array index");
      }
    else if (compiledIndex.type.equals(c.primIntType))
      return new ValueNode(c.objectType,
			   makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					  "getArrayOrSequenceElement",
					  "(Ljava/lang/Object;I)Ljava/lang/Object;",
					  compiledArray.expression,
					  compiledIndex.expression),
			   arrayRefAST);
    else if (compiledIndex.type.equals(c.integerType) ||
	     compiledIndex.type.equals(c.numberType) ||
	     compiledIndex.type.equals(c.objectType))
      return new ValueNode(c.objectType,
			   makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					  "getArrayOrSequenceElement",
					  "(Ljava/lang/Object;Ljava/lang/Object;)"+
					  "Ljava/lang/Object;",
					  compiledArray.expression,
					  compiledIndex.expression),
			   arrayRefAST);
    else
      throw new CompilerException("Non-integral sequence/array index");
  }

  static ValueNode compileDesignationPredicate(G2ScriptAST expressionAST, 
					       boolean existsCase,
					       Compiler c)
       throws CompilerException
  {
    try {
      G2ScriptAST subjectAST = child(expressionAST);
     
      ValueNode subject = compileExpression(subjectAST,c);
      G2ScriptAST firstArgAST = sibling(subjectAST);
      Type compileTestType = null;
      boolean negate = false;
      if (firstArgAST != null && //only occurs for "if <d> exists then..."
	  firstArgAST.getType() == NOT)
	{
	  firstArgAST = sibling(firstArgAST);
	  negate = true;
	}
      Expression testNode = null;
      if (existsCase)
	{
	  negate = !negate;
	  testNode
	    = new OperatorCall("==",
			       new Expression[]
			       { subject.expression, new Value((Object)null) });
	}
      else
	switch (firstArgAST.getType())
	  {
	  case UNRESERVED:
	    String symbolName = firstArgAST.toString();
	    if (symbolName.equals("CLASS"))
	      {
		Type testType = c.compileTypeDeclaration(firstArgAST);
		ClassRef classRef = new ClassRef(testType.getName());
		testNode = new OperatorCall("instanceof",
					    new Expression[]
					    { subject.expression, classRef });
	      }
	    else
	      testNode
		= new OperatorCall("==",
				   new Expression[]
				   { subject.expression,
				       c.getOrMakeSymbolConstant(symbolName) });
	    break;
	  case TRUTH_VALUE_LITERAL:
	    if (((Boolean) firstArgAST.getValue()).booleanValue() == false)
	      negate = true;
	    if (subject.type.equals(c.primBooleanType))
	      testNode = subject.expression;
	    else if (subject.type.equals(c.objectType))
	      testNode = makeStaticCall("com.gensym.g2scriptruntime.Math",
					"extractBooleanFromObject",
					"(Ljava/lang/Object;)Z",
					subject.expression);
	    else
	      throw new CompilerException(expressionAST+" is not a truth-value");
	    break;
	  case OBJECT: // reference equality test
	    ValueNode otherObject = compileExpression(sibling(firstArgAST),c);
	    testNode = new OperatorCall("==",
					new Expression[]
					{ subject.expression,
					    otherObject.expression });
	    break;
	  case INTEGER:
	    if (subject.type.equals(c.primIntType) ||
		subject.type.equals(c.integerType))
	      testNode = new Value(true);
	    else if (subject.type.equals(c.objectType) ||
		     subject.type.equals(c.numberType))
	      testNode = new OperatorCall("instanceof",
					  new Expression[]
					  { subject.expression, 
					      new ClassRef("java.lang.Integer") });
	    else
	      throw new CompilerException(expressionAST+" could not be an integer");
	    break;
	  case FLOAT:
	    if (subject.type.equals(c.primDoubleType) ||
		subject.type.equals(c.integerType))
	      testNode = new Value(true);
	    else if (subject.type.equals(c.objectType) ||
		     subject.type.equals(c.numberType))
	      testNode = new OperatorCall("instanceof",
					  new Expression[]
					  { subject.expression, 
					      new ClassRef("java.lang.Double") });
	    else
	      throw new CompilerException(expressionAST+" could not be an float");
	    break;
	  case QUANTITY:
	    if (subject.type.equals(c.primIntType) ||
		subject.type.equals(c.primDoubleType) ||
		subject.type.equals(c.numberType))
	      testNode = new Value(true);
	    else if (subject.type.equals(c.objectType))
	      testNode = new OperatorCall("instanceof",
					  new Expression[]
					  { subject.expression, 
					      new ClassRef("java.lang.Number") });
	    else
	      throw new CompilerException(expressionAST+" could not be an quantity");
	    break;
	  case TRUTH_VALUE:
	    if (subject.type.equals(c.primBooleanType))
	      testNode = new Value(true);
	    else if (subject.type.equals(c.objectType))
	      testNode = new OperatorCall("instanceof",
					  new Expression[]
					  { subject.expression, 
					      new ClassRef("java.lang.Boolean") });
	    else
	      throw new CompilerException(expressionAST+" could not be a truth-value");
	    break;
	  case VALUE:
		boolean isNumberType = subject.type.equals(c.primIntType) || subject.type.equals(c.primDoubleType) 
								|| c.numberType.isAssignableFrom(subject.type);
	    
		if (isNumberType || subject.type.equals(c.primBooleanType) || subject.type.equals(c.stringType))
	      testNode = new Value(true);
	    else
	      {
		negate = !negate;
		testNode
		  = new OperatorCall("instanceof",
				     new Expression[]
				     { subject.expression, 
					 new ClassRef("com.gensym.classes.Item") });
	      }
	    break;
	  case ITEM_OR_VALUE:
	    testNode = new Value(true);
	    break;
	  case TEXT:
	  case SYMBOL:
	  case SEQUENCE:
	  case STRUCTURE:
	    compileTestType = c.compileTypeDeclaration(firstArgAST);
	    if (subject.type.equals(compileTestType))
	      testNode = new Value(true);
	    else if (subject.type.equals(c.objectType))
	      testNode = new OperatorCall("instanceof",
					  new Expression[]
					  { subject.expression, 
					      new ClassRef(compileTestType.getName()) });
	    else
	      throw new CompilerException(expressionAST+" could not be a "+
					  compileTestType);
	    break;
	  default:
	  }
      if (negate)
	return new ValueNode(c.primBooleanType,
			     new OperatorCall("!", new Expression [] {testNode}),
			     expressionAST);
      else
	return new ValueNode(c.primBooleanType,testNode,expressionAST);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }
  
  static ValueNode compileConnectionExpression(G2ScriptAST expressionAST,
					       Compiler c)
       throws CompilerException
  {
    G2ScriptAST classNameAST = child(expressionAST);
    G2ScriptAST localNameAST = null, connectionSpecAST;
    if (siblingCount(classNameAST) == 2)
      {
	localNameAST = sibling(classNameAST);
	connectionSpecAST = sibling(localNameAST);
      }
    else
      connectionSpecAST = sibling(classNameAST);
    
    Type connectedObjectType = c.compileClassName(classNameAST.toString());
    if (connectionSpecAST.toString().equals("TO"))
      throw new CompilerException("connected to <object> case NYI");
    else
      {
	G2ScriptAST portSpecAST = child(connectionSpecAST);
	G2ScriptAST objectAST = sibling(portSpecAST);
	ValueNode compiledObject = compileExpression(objectAST,c);
	MethodCall call
	  = makeStaticCall("com.gensym.g2scriptruntime.Kernel",
			   "getUniqueConnectedObject",
			   "(Ljava/lang/Object;Ljava/lang/String;"+
			   "Ljava/lang/String;)Ljava/lang/Object;",
			   compiledObject.expression,
			   new Value(connectedObjectType.getName()),
			   new Value(portSpecAST.toString()));
	return new ValueNode(c.objectType,call,expressionAST);
			 
      }
  }

  static ValueNode compileUponExpression(G2ScriptAST expressionAST,
					 Compiler c)
       throws CompilerException
  {
    G2ScriptAST classNameAST = child(expressionAST);
    G2ScriptAST localNameAST = null, workspaceDesignationAST;
    if (siblingCount(classNameAST) == 2)
      {
	localNameAST = sibling(classNameAST);
	workspaceDesignationAST = sibling(localNameAST);
      }
    else
      workspaceDesignationAST = sibling(classNameAST);
    
    Type subblockObjectType = c.compileClassName(classNameAST.toString());
    ValueNode compiledWorkspace = compileExpression(workspaceDesignationAST,c);
    MethodCall call
      = makeStaticCall("com.gensym.g2scriptruntime.Kernel",
		       "getUniqueObjectUponWorkspace",
		       "(Ljava/lang/Object;Ljava/lang/String;)Ljava/lang/Object;",
		       compiledWorkspace.expression,
		       new Value(subblockObjectType.getName()));
    return new ValueNode(c.objectType,call,expressionAST);
  }

  static ValueNode compileTimeExpression(G2ScriptAST expressionAST,Compiler c)
  {
    G2ScriptAST modifiers = child(expressionAST);
    if (siblingsContain(modifiers,REAL))
      {
	if (siblingsContain(modifiers,SUBSECOND))
	  return new ValueNode(c.primDoubleType,
			       makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					      "getCurrentSubsecondRealTime",
					      "()D"),
			       expressionAST);
	else
	  return new ValueNode(c.primIntType,
			       makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					      "getCurrentRealTime",
					      "()I"),
			       expressionAST);
      }
    else
      throw new RuntimeException("Internal Compiler Failure");
  }

  static ValueNode compileCall(G2ScriptAST callAST, Compiler c)
       throws CompilerException
  {
    G2ScriptAST methodAST = child(callAST);
    String methodName;
    Type staticMethodType = null;
    boolean isStatic = false, isConstructor = false;
    int i = 0 , argCount = siblingCount(methodAST);
    G2ScriptAST argAST = sibling(methodAST);
    ValueNode compiledTarget = null; // bound if virtual
    Type constructorType = null; // bound if constructor

    if (methodAST.getType() == NEW) // constructor invocation
      {
	methodName = "<init>";
	isConstructor = true;
	G2ScriptAST classNameAST = argAST;
	constructorType = c.compileTypeDeclaration(classNameAST);
	argAST = sibling(sibling(argAST));
	argCount -= 2;
      }
    else if (methodAST.getType() == UNRESERVED) // virtual invocation
      {
	methodName = c.makeJavaName(methodAST.toString(),false);
	if (argCount == 0)
	  throw new CompilerException("non static call must have at least one argument");
	else
	  argCount--; // target object is not officially an "arg"
	compiledTarget = compileExpression(argAST,c);
	argAST = sibling(argAST);
      }
    else
      {
	G2ScriptAST staticMethodNameAST = child(methodAST);
	G2ScriptAST staticMethodClassAST = sibling(staticMethodNameAST);
	methodName = c.makeJavaName(staticMethodNameAST.toString(),
					   false);
	staticMethodType = c.compileTypeDeclaration(staticMethodClassAST);
	isStatic = true;
      }
    
    if (debug)
      System.out.println((isStatic ? "static " : "virtual")+
			 "method "+methodName+" has "+argCount+" args");
    ValueNode[] compiledArgs = new ValueNode[argCount];
    Expression[] methodArgs = new Expression[argCount];
    StringBuffer descriptorBuffer = new StringBuffer("(");
    boolean allArgTypesAlreadyDefined = true;
    Type[] argTypes = new Type[argCount];

    while (argAST != null)
      {
	if (debug)
	  System.out.println("arg loop "+i+" arg "+argAST.toString());
	ValueNode compiledArg  = compileExpression(argAST,c);
	methodArgs[i] = compiledArg.expression;
	argTypes[i] = compiledArg.type;
	compiledArgs[i++] = compiledArg;
	if (!compiledArg.type.isCurrentlyDefined())
	  allArgTypesAlreadyDefined = false;
	descriptorBuffer.append(compiledArg.type.makeDescriptor());
	argAST = sibling(argAST);
      }
    descriptorBuffer.append(")");

    Type invocationType = (isStatic ? 
			   staticMethodType : 
			   (isConstructor ? constructorType : compiledTarget.type));
    Type returnType = null;
    Method method = null;
    String descriptor = "";

    if (isConstructor)
      {
	// this should do some checking to see that the method exists
	descriptorBuffer.append("V");
	descriptor = descriptorBuffer.toString();
	// Joe, I did not sort out the correct Constructor sigs here...TBD
	// We normaly only have no arg constructors anyway.
	returnType = constructorType;
      }
    else
      {
	method = invocationType.getMethod(methodName, isStatic, argTypes); 
	if (method == null)
	  throw new CompilerException("unknown "+
				  (isStatic ? "static " : "")+
				  "method "+methodName+" in "+invocationType.getName());
	descriptor = invocationType.getDescriptorForMethod(method);
	//returnType = invocationType.getMethodReturnType(methodName,isStatic);
	returnType = c.typeForName(method.getReturnType().getName());
	if (returnType == null)
	  throw new CompilerException("unknown "+
				      (isStatic ? "static " : "")+
				      "method "+methodName+" of "+invocationType.getName());
	//descriptorBuffer.append(returnType.makeDescriptor());
      }

    if (allArgTypesAlreadyDefined)
      {
	try 
	  {
	    String methodClassName = invocationType.getName();
	    if (debug)
	      System.out.println("making method ref of "+methodClassName+
				 "::"+methodName);
	    MethodRef methodRef
	      = new MethodRef(methodClassName,
			      methodName,
			      //descriptorBuffer.toString());
			      descriptor);
	    InterfaceMethodRef interfaceMethodRef
	      = new InterfaceMethodRef(methodClassName,
				       methodName,
				       //descriptorBuffer.toString());
				       descriptor);
	    methodRef.setLineNumber(methodAST.getLineNumber());
	    MethodCall targetCall;
	    if (isStatic)
	      targetCall = 
		new MethodCall(methodRef, methodArgs,RuntimeConstants.MTH_CALL_STATIC);
	    else if (isConstructor)
	      targetCall =
		new MethodCall(methodRef, methodArgs,RuntimeConstants.MTH_CALL_SPECIAL);
	    else if (compiledTarget.type.isInterface())
	      targetCall 
		= new MethodCall(compiledTarget.expression,
				 interfaceMethodRef, 
				 methodArgs, 
				 RuntimeConstants.MTH_CALL_INTERFACE);
	    else
	      targetCall 
		= new MethodCall(compiledTarget.expression,
				 methodRef, 
				 methodArgs, 
				 RuntimeConstants.MTH_CALL_VIRTUAL);
	    return new ValueNode(returnType, 
				 ( isConstructor ? 
				   (Expression) (new New(targetCall)) : 
				   (Expression) targetCall),
				 methodAST);
	  }
	catch (ClassException e)
	  {
	    throw new CompilerException(e.getMessage());
	  }
      }
    else
      {
	// compile call using com.gensym.util.Dispatcher
	return null;
      }
  }
  
  static ValueNode compileSymbolLiteral(G2ScriptAST wrapperAST, Compiler c)
  {
    G2ScriptAST symbolAST = child(wrapperAST);
    FieldRef fieldRef = c.getOrMakeSymbolConstant(symbolAST.toString());
    fieldRef.setLineNumber(symbolAST.getLineNumber());
    return new ValueNode(c.symbolType, fieldRef, symbolAST);
  }

  static ValueNode compileStringConcatenation(G2ScriptAST expressionAST,
					      Compiler c)
       throws CompilerException
  {
    G2ScriptAST stringAST = child(expressionAST);
    int count = siblingCount(stringAST) + 1, i = 0;
    Expression[] expressions = new Expression[count];
    try
      {
	while (stringAST != null)
	  {
	    int type = stringAST.getType();
	    if (type == LEFT_STRING_LITERAL ||
		type == MIDDLE_STRING_LITERAL ||
		type == RIGHT_STRING_LITERAL ||
		type == WHOLE_STRING_LITERAL)
	      {
		expressions[i] = new Value((String)stringAST.getValue());
	      }
	    else
	      {
		ValueNode compiledString = compileExpression(stringAST,c);
		expressions[i] = compiledString.expression;
		if (debug)
		  System.out.println("Non string format elt "+compiledString);
	      }
	    i++;
	    stringAST = sibling(stringAST);
	  }
	return new ValueNode(c.typeForName("java.lang.String"),
			     new OperatorCall("+",expressions),
			     expressionAST);
      }
    catch (ClassException e)
      {
	throw new CompilerException(e.getMessage());
      }
  }

  // should be called makeBinaryNumericOperation
  static ValueNode makeBinaryOperation(Compiler c,
				       G2ScriptAST expressionAST,
				       ValueNode arg1, ValueNode arg2)
       throws CompilerException
  {
    String opName = expressionAST.toString();
    try 
      {
	if (arg1.type.isPrimitive() && arg2.type.isPrimitive())
	  {
	    OperatorCall operatorCall 
	      = new OperatorCall(opName,
				 new Expression[] {arg1.expression,arg2.expression });
	    String descriptor = operatorCall.getExpressionType().getReturnTypeString();
	    if (debug)
	      System.out.println("operatorCall type "+descriptor);
	    return new ValueNode(Type.forDescriptor(c,descriptor),
				 operatorCall,
				 expressionAST);
	  }
	else
	  {
	    // simplify life by making all out-of-line math take Objects as
	    // arguments and perform type checking at run time.  I know this
	    // wastes some java.lang.Number wrappers needlessly, but why
	    // optimize this already extremely non-optimal case.  Folks that
	    // want efficient numerical code should use specific type.
	    ValueNode
	      objectArg1 = arg1.type.isPrimitive() ? wrapAsNumber(c,arg1,true) : arg1;
	    ValueNode
	      objectArg2 = arg2.type.isPrimitive() ? wrapAsNumber(c,arg2,true) : arg2;
	    Method method = getMethodForOperator(opName,c.objectType,c.objectType);
	    Type returnType = Type.forClass(c,method.getReturnType());
	    MethodCall call 
	      = makeStaticCall ("com.gensym.g2scriptruntime.Math",
				method.getName(),
				"(Ljava/lang/Object;Ljava/lang/Object;)"+
				returnType.makeDescriptor(),
				objectArg1.expression,
				objectArg2.expression);
	    return new ValueNode(returnType,call,expressionAST);
	  }
      }
    catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Error "+e.getMessage());
      }
  }

  static ValueNode makeBinaryLogicalOperation(Compiler c,
					      G2ScriptAST expressionAST,
					      ValueNode arg1, ValueNode arg2)
       throws CompilerException
  {
    String opName = (expressionAST.toString().equals("AND") ?
		     "&&" : "||");
    try 
      {
	if (arg1.type.isPrimitive() && arg2.type.isPrimitive())
	  {
	    OperatorCall operatorCall 
	      = new OperatorCall(opName,
				 new Expression[] {arg1.expression,arg2.expression });
	    String descriptor = operatorCall.getExpressionType().getReturnTypeString();
	    if (debug)
	      System.out.println("operatorCall type "+descriptor);
	    return new ValueNode(Type.forDescriptor(c,descriptor),
				 operatorCall,
				 expressionAST);
	  }
	else
	  {
	    ValueNode
	      objectArg1 = arg1.type.isPrimitive() ? wrapAsBoolean(c,arg1,true) : arg1;
	    ValueNode
	      objectArg2 = arg2.type.isPrimitive() ? wrapAsBoolean(c,arg2,true) : arg2;
	    Method method = getMethodForOperator(opName,c.objectType,c.objectType);
	    MethodCall call 
	      = makeStaticCall ("com.gensym.g2scriptruntime.Math",
				method.getName(),
				"(Ljava/lang/Object;Ljava/lang/Object;)"+
				"Z",
				objectArg1.expression,
				objectArg2.expression);
	    return new ValueNode(c.primBooleanType,call,expressionAST);
	  }
      }
    catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Error "+e.getMessage());
      }
  }
 
  static Expression wrapAsIntExpression(Compiler c, ValueNode node)
       throws CompilerException
  {
    if (node.type.equals(c.primIntType))
      return node.emit();
    else if (c.numberType.isAssignableFrom(node.type) ||
	     node.type.equals(c.objectType))
      return makeStaticCall("com.gensym.g2scriptruntime.Math",
			    "extractIntFromNumber",
			    "(Ljava/lang/Object;)I",
			    node.emit());
    else 
      throw new CompilerException("Value not coercible to integer "+node);
  }

  static ValueNode wrapAsNumber(Compiler c, ValueNode node, boolean ignoreNonNumbers)
       throws CompilerException
  {
    if (node.type.equals(c.primIntType) ||
	node.type.equals(c.primDoubleType))
      {
	try {
	  MethodRef methodRef = (node.type.equals(c.primIntType)) ?
	    new MethodRef("java.lang.Integer","<init>","(I)V")  :
	    new MethodRef("java.lang.Double","<init>","(D)V");
	  MethodCall methodCall = new MethodCall(methodRef,
						 new Expression []
						 { node.emit() },
						 RuntimeConstants.MTH_CALL_SPECIAL);
	  return new ValueNode((node.type.equals(c.primIntType) ? c.integerType : c.doubleType),
			       new New(methodCall),
			       null);
	} catch (ClassException e)
	  {
	    throw new RuntimeException("Internal Compiler Error");
	  }
      }
    else if (c.numberType.isAssignableFrom(node.type) || ignoreNonNumbers)
      return node;
    else
      throw new CompilerException("Value not coercible to Quantity");
  }

  static ValueNode wrapAsBoolean(Compiler c, ValueNode node, boolean ignoreNonBooleans)
       throws CompilerException
  {
    if (node.type.equals(c.primBooleanType))
      {
	try {
	  MethodRef methodRef = 
	    new MethodRef("java.lang.Double","<init>","(Z)V");
	  MethodCall methodCall = new MethodCall(methodRef,
						 new Expression []
						 { node.emit() },
						 RuntimeConstants.MTH_CALL_SPECIAL);
	  return new ValueNode(c.booleanType,new New(methodCall),null);
	} catch (ClassException e)
	  {
	    throw new RuntimeException("Internal Compiler Error");
	  }
      }
    else if (c.booleanType.isAssignableFrom(node.type) || ignoreNonBooleans)
      return node;
    else
      throw new CompilerException("Value not coercible to Boolean");
  }

  static MethodCall makeInstanceCall(boolean isInterface,
				     Expression object,
				     String className, String methodName, 
				     String descriptor)
  {
    try {
      if (isInterface)
	{
	  InterfaceMethodRef methodRef 
	    = new InterfaceMethodRef(className,methodName,descriptor);
	  return new MethodCall(object,
				methodRef,
				new Expression[0],
				RuntimeConstants.MTH_CALL_INTERFACE);
	}
      else
	{
	  MethodRef methodRef 
	    = new MethodRef(className,methodName,descriptor);
	  return new MethodCall(object,
				methodRef,
				new Expression[0],
				RuntimeConstants.MTH_CALL_VIRTUAL);
	}
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }

  static MethodCall makeInstanceCall(boolean isInterface,
				     Expression object,
				     String className, String methodName, 
				     String descriptor, Expression arg)
  {
    try {
      if (isInterface)
	{
	  InterfaceMethodRef methodRef 
	    = new InterfaceMethodRef(className,methodName,descriptor);
	  return new MethodCall(object,
				methodRef,
				new Expression [] { arg },
				RuntimeConstants.MTH_CALL_INTERFACE);
	}
      else
	{
	  MethodRef methodRef 
	    = new MethodRef(className,methodName,descriptor);
	  return new MethodCall(object,
				methodRef,
				new Expression [] { arg },
				RuntimeConstants.MTH_CALL_VIRTUAL);
	}
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }

  static MethodCall makeStaticCall(String className, String methodName, 
				   String descriptor)
  {
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      return new MethodCall(methodRef,
			    new Expression [] {},
			    RuntimeConstants.MTH_CALL_STATIC);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }


  static MethodCall makeStaticCall(String className, String methodName, 
				   String descriptor, Expression arg)
  {
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      return new MethodCall(methodRef,
			    new Expression [] { arg },
			    RuntimeConstants.MTH_CALL_STATIC);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }

  static MethodCall makeStaticCall(String className, String methodName, 
				   String descriptor, Expression arg1,
				   Expression arg2)
  {
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      return new MethodCall(methodRef,
			    new Expression [] { arg1, arg2 },
			    RuntimeConstants.MTH_CALL_STATIC);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }

  static MethodCall makeStaticCall(String className, String methodName, 
				   String descriptor, Expression arg1,
				   Expression arg2, Expression arg3)
  {
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      return new MethodCall(methodRef,
			    new Expression [] { arg1, arg2, arg3 },
			    RuntimeConstants.MTH_CALL_STATIC);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Error");
      }
  }

  /** Returns byte code that will cast this valueNode to the required type.
   *  @param requiredType the required type
   *  @return an expression to cast this node to the required type
  **/
  Expression castTo(Compiler c, Type requiredType) throws ClassException {
    if (requiredType.isAssignableFrom(type)) // no cast required
      return expression;
    if (debug)
      System.out.println("Casting " + type + " to " + requiredType.makeDescriptor()); // DEBUG
    if (type.equals(c.numberType)) {
      // If this is a Number type (i.e. a G2 quantity), we can't cast it.
      // We need to call the correct extraction method on it.
      String methodName = "";
      String descriptor = "";
      if (requiredType.equals(c.primIntType)) {
	methodName = "intValue";
	descriptor = "()I";
      }
      else if (requiredType.equals(c.primDoubleType)) {
	methodName = "doubleValue";
	descriptor = "()D";
      }
      MethodRef mRef = new MethodRef("java.lang.Number", methodName, descriptor);
      return new MethodCall(expression,
			    mRef,
			    null,
			    RuntimeConstants.MTH_CALL_VIRTUAL);
    }
    else if (type.equals(c.primIntType)) {
      if (requiredType.equals(c.objectType)) {
	MethodRef mRef = new MethodRef("java.lang.Integer", "<init>", "(I)V");
	return new New(new MethodCall(mRef,
				      new Expression[] {expression},
				      MTH_CALL_SPECIAL)
		       );
      }
    }
    else if (type.equals(c.primDoubleType)) {
      if (requiredType.equals(c.objectType)) {
	MethodRef mRef = new MethodRef("java.lang.Double", "<init>", "(D)V");
	return new New(new MethodCall(mRef,
				      new Expression[] {expression},
				      MTH_CALL_SPECIAL)
		       );
      }
    }
    else if (type.equals(c.primBooleanType)) {
      if (requiredType.equals(c.objectType)) {
	MethodRef mRef = new MethodRef("java.lang.Boolean", "<init>", "(Z)V");
	return new New(new MethodCall(mRef,
				      new Expression[] {expression},
				      MTH_CALL_SPECIAL)
		       );
      }
    }

    return new Cast(requiredType.makeDescriptor(), expression);
  }

  static Method getMethodForOperator(String operation, Type t1, Type t2)
  {
    String operatorMethodName = 
      (String) operatorNameTable.get(operation);
    Class c1 = t1.getCompiledClass(), 
      c2 = t2.getCompiledClass();
    if (operatorMethodName == null ||
	c1 == null ||
	c2 == null)
      throw new RuntimeException("Internal Compiler Error");
    else
      {
	try {
	  Class math = Class.forName("com.gensym.g2scriptruntime.Math");
	  Method m 
	    = math.getDeclaredMethod(operatorMethodName, new Class[] { c1, c2 });
	  if (m == null)
	    throw new RuntimeException("Internal Compiler Error");
	  else
	    return m;
	}
	catch (ClassNotFoundException cnfe)
	  {
	    throw new RuntimeException("Internal Compiler Error");
	  }
	catch (NoSuchMethodException nsme)
	  {
	    throw new RuntimeException("Internal Compiler Error");
	  }
      }
  }

  Expression emit()
  {
    return expression;
  }

  @Override
  public String toString()
  {
    return "<ValueNode type = "+type+" exp "+expression+" of "+expression.getClass()+">";
  }

}
