package com.gensym.g2script;

import com.gensym.classtools.*;
import java.util.Vector;
import java.util.Hashtable;
import java.lang.reflect.*;

public class Functions implements G2ScriptTokenTypes, RuntimeConstants, com.gensym.util.ClassConstants
{
  static boolean debug = false;

  static Hashtable nonEvaluatingFunctions = new Hashtable();
  static
  {
    nonEvaluatingFunctions.put("CHANGE-ATTRIBUTE",new boolean[] { false, true, false });
    nonEvaluatingFunctions.put("REMOVE-ATTRIBUTE",new boolean[] { false, true});
  }

  static ValueNode compileFunction(G2ScriptAST call, Compiler c)
       throws CompilerException
  {
    G2ScriptAST functionNameAST = child(call);
    G2ScriptAST argAST = sibling(functionNameAST);
    String functionName = functionNameAST.toString();
    int i,argCount = siblingCount(functionNameAST);
    ValueNode[] argNodes 
      = new ValueNode[argCount];
    boolean[] nonEvaluatingInfo = (boolean[])nonEvaluatingFunctions.get(functionName);
    if (nonEvaluatingInfo == null)
      for (i=0; i<argCount; i++)
	{
	  argNodes[i] = ValueNode.compileExpression(argAST,c);
	  argAST = sibling(argAST);
	}
    else
      {
	if (argCount != nonEvaluatingInfo.length)
	  throw new CompilerException("wrong number of args to "+functionName);
	for (i=0; i<argCount; i++)
	  {
	    if (nonEvaluatingInfo[i])
	      {
		if (argAST.getType() == UNRESERVED &&
		    argAST.toString().equals("LOCAL_REFERENCE"))
		  {
		    FieldRef symbolFieldRef 
		      = c.getOrMakeSymbolConstant(child(argAST).toString());
		    argNodes[i] = new ValueNode(c.symbolType, symbolFieldRef, argAST);
		  }
		else
		  throw new CompilerException("expected symbol constant for argument "+
					      i+" of "+functionName);
	      }
	    else
	      argNodes[i] = ValueNode.compileExpression(argAST,c);
	    argAST = sibling(argAST);
	  }
      }
    FunctionSpec spec = findFunctionSpec(functionName, argNodes, c);
    return makeFunctionExpression(call,spec,argNodes, c);
  }

  /** Declare G2 function definitions.
  **/
  static void initializeFunctionSpecs(Compiler c)
  {
    String[] oneObject = new String[] {OBJECT_DESC};
    String[] twoObjects = new String[] {OBJECT_DESC, OBJECT_DESC};
    String[] threeObjects = new String[] {OBJECT_DESC, OBJECT_DESC, OBJECT_DESC};
    String[] fourObjects = new String[] {OBJECT_DESC, OBJECT_DESC, OBJECT_DESC, OBJECT_DESC};
    // Must be added from most specific type for function name to least specifi    // BEGIN Arithmetic Functions
    add("ABS", 1, 1, -1, new String[] {"I"}, c); // abs(quantity-expression)
    add("ABS", 1, 1, -1, new String[] {"D"}, c); // abs(quantity-expression)
    add("ABS", 1, 1, -1, oneObject, c); // abs(quantity-expression)
    add("ARCTAN", 1, 1, -1, new String[] {"D"}, c);
    add("ARCTAN", 2, 2, -1, new String[] {"D", "D"}, c);
    add("ARCTAN", 1, 1, -1, oneObject, c);
    add("ARCTAN", 2, 2, -1, twoObjects, c);
    // ^ arctan(quantity-expression [, quantity-expression])
    add("AVERAGE", 2, -1, 2, new String[] {"D", "D", "D"}, c);
    add("AVERAGE", 2, -1, 2, threeObjects, c);
    // ^ average(quantity-expression, quantity-expression [, quantity-expression...])
    add("CEILING", 1, 1, -1, new String[] {"D"}, c); // ceiling(quantity-expression)
    add("CEILING", 1, 1, -1, oneObject, c);
    add("COS", 1, 1, -1, new String[] {"D"}, c); // cos(quantity-expression)
    add("COS", 1, 1, -1, oneObject, c);
    add("EXP", 1, 1, -1, new String[] {"D"}, c); // exp(quantity-expression)
    add("EXP", 1, 1, -1, oneObject, c);
    add("EXPT", 2, 2, -1, new String[] {"D", "D"}, c);
    add("EXPT", 2, 2, -1, twoObjects, c);
    // ^ expt(quantity-expression, quantity-expression)
    add("FLOOR", 1, 1, -1, new String[] {"D"}, c); // floor(quantity-expression)
    add("FLOOR", 1, 1, -1, oneObject, c);
    add("LN", 1, 1, -1, new String[] {"D"}, c); // ln(quantity-expression) (base e)
    add("LN", 1, 1, -1, oneObject, c);
    add("LOG", 1, 1, -1, new String[] {"D"}, c); // log(quantity-expression) (base 10)
    add("LOG", 1, 1, -1, oneObject, c);
    add("MAX", 2, -1, 2, new String[] {"D", "D", "D"}, c);
    // ^ max(quantity-expression, quantity-expression [,...])
    add("MAX", 2, -1, 2, threeObjects, c);
    add("MIN", 2, -1, 2, new String[] {"D", "D", "D"}, c);
    // ^ min(quantity-expression, quantity-expression [,...])
    add("MIN", 2, -1, 2, threeObjects, c);
    add("QUOTIENT", 2, 2, -1, new String[] {"D", "D"}, c);
    // ^ quotient(quantity-expression, quantity-expression)
    add("QUOTIENT", 2, 2, -1, twoObjects, c);
    add("RANDOM", 2, 2, -1, new String[] {"D", "D"}, c);
    add("RANDOM", 2, 2, -1, twoObjects, c);
    add("RANDOM", 1, 1, -1, new String[] {"D"}, c);
    add("RANDOM", 1, 1, -1, oneObject, c);
    // ^ random(quantity-expression [, quantity-expression])
    add("REMAINDER", 2, 2, -1, new String[] {"D", "D"}, c);
    add("REMAINDER", 2, 2, -1, twoObjects, c);
    // ^ remainder(quantity-expression, quantity-expression)
    add("ROUND", 1, 1, -1, new String[] {"D"}, c); // round(quantity-expression)
    add("ROUND", 1, 1, -1, oneObject, c);
    add("SIN", 1, 1, -1, new String[] {"D"}, c); // sin(quantity-expression)
    add("SIN", 1, 1, -1, oneObject, c);
    add("SQRT", 1, 1, -1, new String[] {"D"}, c); // sqrt(quantity-expression)
    add("SQRT", 1, 1, -1, oneObject, c);
    add("TAN", 1, 1, -1, new String[] {"D"}, c); // tan(quantity-expression)
    add("TAN", 1, 1, -1, oneObject, c);
    add("TRUNCATE", 1, 1, -1, new String[] {"D"}, c); // truncate(quantity-expression)
    add("TRUNCATE", 1, 1, -1, oneObject, c);
    // NO MAPPING: add("TRUTH-VALUE", 1, 1, -1, new String[] {"D"}); 
    // truth-value(quantity-expression)
    // END Arithmetic Functions

    // BEGIN Bitwise Functions
    // Where arguments are primitive types, then use operator calls.  Otherwise, use method calls
    // In Java, the bitwise operators can act only on numeric or boolean types.
    // If we encounter any other types here, throw a Runtime exception
    // bitwise-or(value-expression, value-expression)
    add("BITWISE-OR", 2, 2, -1, new String[] {"I", "I"}, c);
    add("BITWISE-OR", 2, 2, -1, new String[] {"D", "D"}, c);
    add("BITWISE-OR", 2, 2, -1, new String[] {"Z", "Z"}, c);
    // END Bitwise Functions

    // Call Function
    // Character Support Functions
    // Connection Evaluator Functions

    // BEGIN Quantity Function
    add("QUANTITY", 1, 1, -1, new String[] {"Z"}, c);
    add("QUANTITY", 1, 1, -1, new String[] {STRING_DESC}, c);
    add("QUANTITY", 1, 1, -1, oneObject, c);
    // END Quantity Function

    // Regular Expression Functions

    // BEGIN Sequence Functions
    add("CHANGE-ELEMENT", 3, 3, -1, new String[] {SEQUENCE_DESC, "I", OBJECT_DESC}, c);
    add("CHANGE-ELEMENT", 3, 3, -1, threeObjects, c);
    // ^ change-element(sequence, integer, item-or-value)
    add("CONCATENATE", 2, -1, 2, new String[] {SEQUENCE_DESC, SEQUENCE_DESC, SEQUENCE_DESC}, c);
    add("CONCATENATE", 2, -1, 2, threeObjects, c);
    // ^ concatenate(Sequence, Sequence [,...])
    add("INSERT-AT-BEGINNING", 2, 2, -1, new String[] {SEQUENCE_DESC, OBJECT_DESC}, c);
    add("INSERT-AT-BEGINNING", 2, 2, -1, twoObjects, c);
    // ^ insert-at-beginning(sequence, item-or-value)
    add("INSERT-AT-END", 2, 2, -1, new String[] {SEQUENCE_DESC, OBJECT_DESC}, c);
    add("INSERT-AT-END", 2, 2, -1, twoObjects, c);
    // ^ insert-at-end(sequence, item-or-value)
    add("INSERT-AFTER", 3, 3, -1, new String[] {SEQUENCE_DESC, OBJECT_DESC, OBJECT_DESC}, c);
    add("INSERT-AFTER", 3, 3, -1, threeObjects, c);
    // ^ insertAfter(sequence, item-or-value, item-or-value)
    // insert-before-element(sequence, integer, item-or-value)
    add("INSERT-BEFORE-ELEMENT", 3, 3, -1, new String[] {SEQUENCE_DESC, "I", OBJECT_DESC}, c);
    add("INSERT-BEFORE-ELEMENT", 3, 3, -1, threeObjects, c);
    // insert-after-element(sequence, integer, item-or-value)
    add("INSERT-AFTER-ELEMENT", 3, 3, -1, new String[] {SEQUENCE_DESC, "I", OBJECT_DESC}, c);
    add("INSERT-AFTER-ELEMENT", 3, 3, -1, threeObjects, c);
    // remove(Sequence, integer)
    add("REMOVE", 2, 2, -1, new String[] {SEQUENCE_DESC, "I"}, c);
    add("REMOVE", 2, 2, -1, twoObjects, c);
    // portion(Sequence, integer, integer)
    add("PORTION", 3, 3, -1, new String[] {SEQUENCE_DESC, "I", "I"}, c);
    add("PORTION", 3, 3, -1, threeObjects, c);
    // sequence(item-or-value [, ...])
    add("SEQUENCE", 1, -1, 2, new String[] {OBJECT_DESC, OBJECT_DESC}, c);
    // END Sequence Functions

    // BEGIN Symbol Function
    add("SYMBOL", 1, 1, -1, new String[] {STRING_DESC}, c);
    add("SYMBOL", 1, 1, -1, oneObject, c);
    // END Symbol Function

    // BEGIN Structure Functions
    // change-attribute(structure, attribute-name, item-or-value)
    add("CHANGE-ATTRIBUTE", 3, 3, -1, new String[] {STRUCTURE_DESC, SYMBOL_CLASS_DESC, OBJECT_DESC}, c);
    add("CHANGE-ATTRIBUTE", 3, 3, -1, threeObjects, c);
    // change-evaluated-attribute(structure, symbol-expression, item-or-value)
    add("CHANGE-EVALUATED-ATTRIBUTE", 3, 3, -1, new String[] {STRUCTURE_DESC, SYMBOL_CLASS_DESC, OBJECT_DESC}, c);
    add("CHANGE-EVALUATED-ATTRIBUTE", 3, 3, -1, threeObjects, c);
    // evaluated-structure(symbol-expression, item-or-value [,...])
    add("EVALUATED-STRUCTURE", 2, -1, 2, twoObjects, c);
    // remove-attribute(structure, attribute-name)
    add("REMOVE-ATTRIBUTE", 2, 2, -1, new String[] {STRUCTURE_DESC, SYMBOL_CLASS_DESC}, c);
    add("REMOVE-ATTRIBUTE", 2, 2, -1, twoObjects, c);
    // remove-evaluated-attribute(structure, symbol-expression)
    add("REMOVE-EVALUATED-ATTRIBUTE", 2, 2, -1, new String[] {STRUCTURE_DESC, SYMBOL_CLASS_DESC}, c);
    add("REMOVE-EVALUATED-ATTRIBUTE", 2, 2, -1, twoObjects, c);
    // structure(attribute-name: item-or-value [,...]) - special case, dealt with in Compiler.java
    // END Structure Functions

    // BEGIN Text Functions
    add("CAPITALIZE-WORDS", 1, 1, -1, new String[] {"String"}, c);
    add("CAPITALIZE-WORDS", 1, 1, -1, oneObject, c);
    // ^ capitalize-words(text-expression)
    add("GET-FROM-TEXT", 3, 3, -1, new String[] {"String", "I", "I"}, c);
    add("GET-FROM-TEXT", 3, 3, -1, threeObjects, c);
    // ^ get-from-text(text-expression, integer, integer)
    add("INSERT-IN-TEXT", 3, 3, -1, new String[] {"String", "String", "I"}, c);
    add("INSERT-IN-TEXT", 3, 3, -1, threeObjects, c);
    // ^ insert-in-text(text-expression, text-expression, integer)
    add("IS-CONTAINED-IN-TEXT", 2, 2, -1, new String[] {"String", "String"}, c);
    add("IS-CONTAINED-IN-TEXT", 2, 2, -1, twoObjects, c);
    // ^ is-contained-in-text(text-expression, text-expression)
    add("LENGTH-OF-TEXT", 1, 1, -1, new String[] {"String"}, c);
    add("LENGTH-OF-TEXT", 1, 1, -1, oneObject, c);
    // ^ length-of-text(text-expression)
    add("LOWER-CASE-TEXT", 1, 1, -1, new String[] {"String"}, c); 
    add("LOWER-CASE-TEXT", 1, 1, -1, oneObject, c);
    // ^ lower-case-text(text-expression)
    add("OMIT-FROM-TEXT", 3, 3, -1, new String[] {"String", "I", "I"}, c); 
    add("OMIT-FROM-TEXT", 3, 3, -1, threeObjects, c);
    // ^ omit-from-text(text-expression, integer, integer)
    add("POSITION-OF-TEXT", 2, 2, -1, new String[] {"String", "String"}, c); 
    add("POSITION-OF-TEXT", 2, 2, -1, twoObjects, c);
    // ^ position-of-text(text-expression, text-expression)
    add("REPLACE-IN-TEXT", 4, 4, -1, new String[] {"String", "String", "I", "I"}, c); 
    add("REPLACE-IN-TEXT", 4, 4, -1, fourObjects, c);
    // ^ replace-in-text(text-expression, text-expression, int, int)
    // text-begins-with-quantity
    add("TEXT-BEGINS-WITH-QUANTITY", 1, 1, -1, new String[] {"String"}, c);
    add("TEXT-BEGINS-WITH-QUANTITY", 1, 1, -1, oneObject, c);
    add("UPPER-CASE-TEXT", 1, 1, -1, new String[] {"String"}, c); 
    add("UPPER-CASE-TEXT", 1, 1, -1, oneObject, c);
    // ^ upper-case-text(text-expression)
    // END Text Functions
    
    // Text Tokenizing Function

    // BEGIN Time Functions
    add("YEAR", 1, 1, -1, new String[] {"I"}, c); // year(time-expression) = (integer)
    add("MONTH", 1, 1, -1, new String[] {"I"}, c); // month(time-expression) = (integer)
    add("DAY-OF-THE-MONTH", 1, 1, -1, new String[] {"I"}, c); // day-of-the-month(time-expression) = (integer)
    add("DAY-OF-THE-WEEK", 1, 1, -1, new String[] {"I"}, c); // day-of-the-week(time-expression) = (symbol)
    add("MINUTE", 1, 1, -1, new String[] {"I"}, c); // minute(time-expression) = (integer)
    add("HOUR", 1, 1, -1, new String[] {"I"}, c); // hour(time-expression) = (integer)
    add("SECOND", 1, 1, -1, new String[] {"I"}, c); // second(time-expression) = (integer)
    add("TIME", 6, 6, -1, new String[] {"I", "I", "I", "I", "I", "I"}, c);
    // time(integer, integer, integer, integer, integer) = (integer)
    // END Time Functions
  }

  /** Locate a function that can take the correct number and type of arguments.
   *  @returns the FunctionSpec of the located argument (on success)
   *  @throws CompilerException if function cannot be located
  **/
  private static FunctionSpec findFunctionSpec(String name, ValueNode[] compiledArgs, Compiler c)
       throws CompilerException
  {
    Vector specs = c.functionSpecs;
    int i,j,size = specs.size(), argCount = compiledArgs.length;
    boolean anyNamesMatched = false;
    int specArgCount = 0;
    
    if (debug) {
      System.out.print("Searching for match for method: " + name + "("); // DEBUG
      for (j = 0; j < argCount; j++) { // DEBUG
	System.out.print(compiledArgs[j].type); // DEBUG
	if (j < (argCount - 1)) 
	  System.out.print(", "); // DEBUG
      }
      System.out.println(")"); // DEBUG
    }

    // first, check for an exact match
    for (i = 0; i < size; i++) {
      FunctionSpec testSpec = (FunctionSpec) specs.elementAt(i);
      specArgCount = testSpec.types.length;
      if (testSpec.name.equals(name)) {
	anyNamesMatched = true;
	if (testSpec.isArgCountOk(argCount)) {
	  if (debug) {
	    System.out.print("Checking for perfect match with : " + name + "("); // DEBUG
	    for (j = 0; j < specArgCount; j++) { // DEBUG
	      System.out.print(testSpec.types[j]); // DEBUG
	      if (j < (argCount - 1))
		System.out.print(", ");
	    }
	    System.out.println(")"); // DEBUG
	  }
	  boolean perfect = true;
	  for (j = 0; j < argCount; j++) {
	    if (!testSpec.perfectArgument(compiledArgs[j], j, c)) {
	      perfect = false;
	      break;
	    }
	  }
	  if (perfect) {
	    if (debug) System.out.println("Perfect");
	    return testSpec;
	  }
	}
      }
    }

    // if no perfect match found, check for an acceptable match
    for (i=0; i<size; i++) {
      FunctionSpec testSpec = (FunctionSpec) specs.elementAt(i);
      specArgCount = testSpec.types.length;
      if (testSpec.name.equals(name)) {
	anyNamesMatched = true;
	if (testSpec.isArgCountOk(argCount)) {
	  if (debug) {
	    System.out.print("Checking for acceptable match with : " + name + "("); // DEBUG
	    for (j = 0; j < specArgCount; j++) { // DEBUG
	      System.out.print(testSpec.types[j]); // DEBUG
	      if (j < (argCount - 1))
		System.out.print(", ");
	    }
	    System.out.println(")"); // DEBUG
	  }
	  boolean ok = true;
	  for (j=0; j<argCount; j++)
	    if (!testSpec.acceptArgument(compiledArgs[j],j, c)) {
	      ok = false;
	      break;
	    }
	  if (ok) {
	    if (debug) System.out.println("Acceptable");
	    return testSpec;
	  }
	}
      }
    }
    if (anyNamesMatched)
      throw new CompilerException("bad arguments for function "+name);
    else
      throw new CompilerException("unknown function name "+name);
  }

  /** Creates (and returns) byte code (in a ValueNode) for the java equivalent
   *  of the given G2 function.
   *  @returns a ValueNode containing the byte code for the java 
   *  equivalent of the given G2 function.
   *  @throws CompilerException if no mapping exists for the function (most likely)
  **/
  private static ValueNode makeFunctionExpression(G2ScriptAST uncompiledCall,
						  FunctionSpec spec, 
						  ValueNode[] compiledArgs,
						  Compiler c)
       throws CompilerException
  {
    Type sequenceType = Type.forDescriptor(c, SEQUENCE_DESC);
    Type structureType = Type.forDescriptor(c, STRUCTURE_DESC);
    Type symbolType = Type.forDescriptor(c, SYMBOL_CLASS_DESC);
    String g2FunctionsClass = "com.gensym.g2scriptruntime.G2Functions";
    String argDesc = spec.types[0].makeDescriptor();

    // BEGIN Arithmetic Functions
    if (spec.name.equals("ABS")) { // map to Math.abs(double) or Math.abs(int)
      //      System.out.println("Found ABS function; returnType = " + spec.types[0] + "; descriptor = " + argDesc);
      String className = null;
      if (spec.types[0].g2Name().equals("float") || spec.types[0].g2Name().equals("integer"))
	className = "java.lang.Math";
      else
	className = g2FunctionsClass;
      return makeStaticCall(uncompiledCall,
			    spec,
			    className,
			    "abs",
			    "(" + argDesc + ")" + argDesc,
			    spec.types[0],
			    compiledArgs,
			    c);
    }
    if (spec.name.equals("ARCTAN")) {
      //      System.out.println("Found arctan function; return = " + spec.types[0].g2Name() + "; desc = " + argDesc);
      if (compiledArgs.length > 1) {
	if (spec.types[0].g2Name().equals("float") && spec.types[1].g2Name().equals("float")) {
	  //  System.out.println("ARCTAN>> Invoking Math.atan2(DD)");
	  // map to Math.atan2(double, double)
	  return makeStaticCall(uncompiledCall,
				spec,
				"java.lang.Math",
				"atan2",
				"(DD)D",
				c.primDoubleType,
				compiledArgs,
				c);
	}
	else {
	  //System.out.println("ARCTAN>> Invoking G2Functions.arctan(" + argDesc + argDesc + ")");
	  // map to G2Functions.tan(Object, Object)
	  return makeStaticCall(uncompiledCall,
				spec,
				g2FunctionsClass,
				"arctan",
				"(" + argDesc + argDesc + ")" + argDesc,
				spec.types[0],
				compiledArgs,
				c);
	}
      }
      else {
	if (spec.types[0].g2Name().equals("float")) {
	  //System.out.println("ARCTAN>> Invoking G2Functions.arctan(D)");
	  // map to Math.atan(double)
	  return makeStaticCall(uncompiledCall,
				spec,
				"java.lang.Math",
				"atan",
				"(D)D",
				c.primDoubleType,
				compiledArgs,
				c);
	}
	else {
	  //System.out.println("ARCTAN>> Invoking Math.arctan(" + argDesc + ")");
	  // map to G2Functions.tan(Object)
	  return makeStaticCall(uncompiledCall,
				spec,
				g2FunctionsClass,
				"arctan",
				"(" + argDesc + ")" + argDesc,
				spec.types[0],
				compiledArgs,
				c);
	}
      }
    }
    if (spec.name.equals("AVERAGE")) { // map to G2Functions.average(double[])
      // 3 cases - all ints, all floats, mixture
      boolean gotAnObject = false;
      for (int i = 0; ((i < compiledArgs.length) && (!gotAnObject)); i++)
	if (spec.types[i].g2Name().indexOf('-') > -1) // anything containing a '-' is a class 
	  gotAnObject = true;
      Type returnType = null;
      if (!gotAnObject) { // can use primitives
	argDesc = "D";
	returnType = c.primDoubleType;
      }
      else {
	argDesc = OBJECT_DESC;
	returnType = c.objectType;
      }
      return makeStaticCall(uncompiledCall,
			    spec,
			    g2FunctionsClass,
			    "average",
			    "([" + argDesc + ")" + argDesc,
			    returnType,
			    compiledArgs,
			    c);
    }
    if (spec.name.equals("CEILING")) {
      if (spec.types[0].g2Name().equals("float")) {
	// map to java.lang.Math.ceil(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "ceil",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
      // map to G2Functions.ceil(Object)
      return makeStaticCall(uncompiledCall,
			    spec,
			    g2FunctionsClass,
			    "ceil",
			    "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			    c.objectType,
			    compiledArgs,
			    c);
    }
    if (spec.name.equals("COS")) {
      if (spec.types[0].g2Name().equals("float")) // map to java.lang.Math.cos(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "cos",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Fucntions.cos(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "cos",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
	
    }
    if (spec.name.equals("EXP")) {
      if (spec.types[0].g2Name().equals("float")) // map to java.lang.Math.exp(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "exp",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.exp(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "exp",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("EXPT")) { // map to java.lang.Math.pow(double, double)
      String descriptor = "";
      Type returnType = null;
      if ((spec.types[0].g2Name().equals("integer")) && (spec.types[1].g2Name().equals("integer"))) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "pow",
			      "(II)I",
			      c.primIntType,
			      compiledArgs,
			      c);
      }
      else if (spec.types[0].g2Name().indexOf('-') > -1) // class
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "expt",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
      else {
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "pow",
			      "(DD)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
    }
    if (spec.name.equals("FLOOR")) {
      if (spec.types[0].g2Name().equals("float")) // map to java.lang.Math.floor(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "floor",
			      "(D)I",
			      c.primIntType,
			      compiledArgs,
			      c);
      else // map to G2Functions(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "floor",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("LN")) {
      if (spec.types[0].g2Name().equals("float")) // map to java.lang.Math.log(double) (which is base e)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "log",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.log(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "ln",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("LOG")) { 
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to G2Functions.log(double) (which is base 10)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "log",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "log",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("MAX")) { // map to G2Functions.max(double[])
      // 3 cases - all ints, all floats, mixture
      boolean allPrims = true;
      for (int i = 0; ((i < compiledArgs.length) && allPrims); i++)
	if (spec.types[i].g2Name().indexOf("-") > -1) 
	  allPrims = false;
      if (allPrims) { // return float
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "max",
			      "([D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
      else { // return Object
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "max",
			      "([" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
      }
    }
    if (spec.name.equals("MIN")) { // map to G2Functions.min(double[])
      // 3 cases - all ints, all floats, mixture
      boolean allPrims = true;
      for (int i = 0; ((i < compiledArgs.length) && allPrims); i++)
	if (spec.types[i].g2Name().indexOf("-") > -1) allPrims = false;
      if (allPrims) { // return float
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "min",
			      "([D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
      else { // return Object
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "min",
			      "([" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
      }
    }
    if (spec.name.equals("QUOTIENT")) {
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to G2Functions.quotient(double, double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "quotient",
			      "(DD)J",
			      c.primIntType,
			      compiledArgs,
			      c);
      else // map to G2Functions.quotient(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "quotient",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("RANDOM")) { // mappings vary depending on param types
      /* There are four potential mappings here:
	 A.  One argument - must be positive
	   A1.  Integral arg: int random(int x) // 0 <= ret < x
	   A2.  Floating point arg: double random(double x) // 0 <= ret < x
	 B. Two Arguments - can be anything as long as 2nd arg is greater than 1st arg
	   B1.  Integral args: int random(int x, int y) // x <= ret <= y
	   B2.  Floating point args: double random(double x, double y) // x <= ret < y
	 The only method we have in Java is a double random() method which returns
	 a floating point value between 0.0 and 1.0
	 */
      String descriptor = "";
      Type returnType = new Type();
      if (compiledArgs.length > 1) { // two args
	String firstArgG2Type = spec.types[0].g2Name();
	String secondArgG2Type = spec.types[1].g2Name();
	if ((firstArgG2Type.equals("integer")) && (secondArgG2Type.equals("integer"))) { // integral types
	  descriptor = "(II)I";
	  returnType = c.primIntType;
	}
	else if (firstArgG2Type.equals("float")) { // floating point types
	  descriptor = "(DD)D";
	  returnType = c.primDoubleType;
	}
	else { // object types
	  descriptor = "(" + OBJECT_DESC + OBJECT_DESC + ")" + OBJECT_DESC;
	  returnType = c.objectType;
	}
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "random",
			      descriptor,
			      returnType,
			      compiledArgs,
			      c);
      }
      else { // one arg
	String argDescriptor = spec.types[0].g2Name(); // type of arg
	if (argDescriptor.equals("integer")) { // integral type
	  descriptor = "(I)I";
	  returnType = c.primIntType;
	}
	else if (argDescriptor.equals("float")) { // floating point type
	  descriptor = "(D)D";
	  returnType = c.primDoubleType;
	}
	else { // object type
	  descriptor = "(" + OBJECT_DESC + ")" + OBJECT_DESC;
	  returnType = c.objectType;
	}
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "random",
			      descriptor,
			      returnType,
			      compiledArgs,
			      c);
      }
    }
    if (spec.name.equals("REMAINDER")) {
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to java.lang.Math.IEEEremainder(double, double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "IEEEremainder",
			      "(DD)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.remainder(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "remainder",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("ROUND")) {
      if (spec.types[0].g2Name().indexOf('-') == -1) // map to java.lang.Math.round(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "round",
			      "(D)J",
			      c.primIntType,
			      compiledArgs,
			      c);
      else // map to G2Functions.round(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "round",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("SIN")) {
      if (spec.types[0].g2Name().indexOf("-") == -1)// map to java.lang.Math.sin(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "sin",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.sin(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "sin",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("SQRT")) {
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to java.lang.Math.sqrt(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "sqrt",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.sqrt(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "sqrt",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("TAN")) {
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to java.lang.Math.tan(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "java.lang.Math",
			      "tan",
			      "(D)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      else // map to G2Functions.tan(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "tan",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("TRUNCATE")) {
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to G2Functions.truncate(double)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "truncate",
			      "(D)I",
			      c.primIntType,
			      compiledArgs,
			      c);
      else // map to g2Functions.truncate(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "truncate",
			      "(" + OBJECT_DESC + ")" + OBJECT_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    // TRUTH-VALUE can have no reasonable mapping in the Java world 
    // (until we implement certainty factors in Java)
    // END Arithmetic Functions

    // BEGIN Bitwise Functions
    if (spec.name.equals("BITWISE-OR")) {
      // Options:  1.  Both args primitive and either int, float, or boolean - use | operator
      // 2.  Either arg is a non-primitive - cast them to Boolean or Number, and extract primitive value
      if (spec.types[0].isAcceptableForBitwiseOp() && spec.types[1].isAcceptableForBitwiseOp()) {
	// primitive args - use | operator on primitives
	return makeInfixOperatorCall(uncompiledCall,
				     spec,
				     "|",
				     spec.types[0], // whatever the args type is, the return type will be
				     compiledArgs[0],
				     compiledArgs[1],
				     c);
      }
      else {
	throw new RuntimeException("Invalid arguments for bitwise OR operator: " + 
				   compiledArgs[0].type + ", " + compiledArgs[1].type);
      }
    }
    // END Bitwise Functions

    // BEGIN Quantity Function
    if (spec.name.equals("QUANTITY")) {
      if (spec.types[0].g2Name().equals("truth-value")) { // map to G2Functions.quantity(boolean)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "quantity",
			      "(Z)D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
      else if (spec.types[0].g2Name().equals("java-lang-string")) { // map to G2Functions.quantity(String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "quantity",
			      "(" + STRING_DESC  + ")D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
      else { // map to G2Functions.quantity(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "quantity",
			      "(" + OBJECT_DESC  + ")D",
			      c.primDoubleType,
			      compiledArgs,
			      c);
      }
    }
    // END Quantity Function

    // BEGIN Sequence Functions
    if (spec.name.equals("CHANGE-ELEMENT")) { 
      if (!spec.types[0].g2Name().equals("java-lang-object")) // map this to G2Functions.changeElement(Sequence, int, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "changeElement",
			      "(" + SEQUENCE_DESC + "I" + 
			      OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.changeElement(Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "changeElement",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("CONCATENATE"))
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map to G2Functions.concatenate(sequence, sequence[])
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "concatenate",
			      "(" + SEQUENCE_ARRAY_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "concatenate",
			      "(" + OBJECT_DESC + OBJECT_ARRAY_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    if (spec.name.equals("INSERT-AT-BEGINNING")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map to G2Functions.insertAtBeginning()
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAtBeginning",
			      "(" + SEQUENCE_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.insertAtBeginning(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAtBeginning",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("INSERT-AT-END")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map to G2Functions.insertAtEnd(Sequence, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAtEnd",
			      "(" + SEQUENCE_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.insertAtEnd(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAtEnd",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("INSERT-AFTER")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map to G2Functions.insertAfter(seq, obj, obj)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAfter",
			      "(" + SEQUENCE_DESC + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to g2Functions.insertAfter(obj, obj, obj)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAfter",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);	
    }
    if (spec.name.equals("INSERT-BEFORE-ELEMENT")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-Sequence")) // map this to G2Functions.insertBeforeElement()
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertBeforeElement",
			      "(" + SEQUENCE_DESC + "I" + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map toG2Functions.insertBeforeElement(obj, obj, obj)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertBeforeElement",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("INSERT-AFTER-ELEMENT")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map to G2Functions.insertAfterElement(seq, int, obj)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAfterElement",
			      "(" + SEQUENCE_DESC + "I" + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.insertAfterElement(obj, obj, obj)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertAfterElement",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("REMOVE")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map this to G2Functions.remove(Sequence, int)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "remove",
			      "(" + SEQUENCE_DESC + "I" + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.remove(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "remove",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("PORTION")) { 
      if (spec.types[0].g2Name().equals("com-gensym-util-sequence")) // map this to G2Functions.portion(Sequence, int, int)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "portion",
			      "(" + SEQUENCE_DESC + "II" + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
      else // map to G2Functions.portion(Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "portion",
			      "(" + OBJECT_DESC + OBJECT_DESC  + OBJECT_DESC  + ")" + SEQUENCE_DESC,
			      sequenceType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("SEQUENCE")) { // map this to G2Functions.sequence(Object[])
      return makeStaticCall(uncompiledCall,
			    spec,
			    g2FunctionsClass,
			    "sequence",
			    "([" + OBJECT_DESC  + ")" + SEQUENCE_DESC,
			    sequenceType,
 			    compiledArgs,
			    c);
    }
    // END Sequence Functions

    // BEGIN Structure Functions
    if (spec.name.equals("EVALUATED-STRUCTURE")) {
      if (((compiledArgs.length % 2) != 0) || (compiledArgs.length == 0)) { // must have an even no. of args
	throw new RuntimeException("internal g2script error : Wrong number of arguments passed to EVALUATED-STRUCTURE function.");
      }
      return makeEvaluatedStructureCall(uncompiledCall, structureType, compiledArgs, c);
    }
    if ((spec.name.equals("CHANGE-ATTRIBUTE")) || (spec.name.equals("CHANGE-EVALUATED-ATTRIBUTE"))) {
      if (spec.types[0].g2Name().equals("java-lang-object")) // map to changeAttribute(Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "changeAttribute",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + STRUCTURE_DESC,
			      structureType,
			      compiledArgs,
			      c);
      else // map to changeAttribute(Structure, Symbol, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "changeAttribute",
			      "(" + STRUCTURE_DESC + SYMBOL_CLASS_DESC + OBJECT_DESC + ")" + STRUCTURE_DESC,
			      structureType,
			      compiledArgs,
			      c);
    }
    if ((spec.name.equals("REMOVE-ATTRIBUTE")) || (spec.name.equals("REMOVE-EVALUATED-ATTRIBUTE"))) {
      if (spec.types[0].g2Name().equals("java-lang-object")) // map to removeAttribute(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "removeAttribute",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")" + STRUCTURE_DESC,
			      structureType,
			      compiledArgs,
			      c);
      else // map to removeAttribute(Structure, Symbol)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "removeAttribute",
			      "(" + STRUCTURE_DESC + SYMBOL_CLASS_DESC + ")" + STRUCTURE_DESC,
			      structureType,
			      compiledArgs,
			      c);
    }
    // END Structure Functions

    // BEGIN Symbol Function
    if (spec.name.equals("SYMBOL")) { 
      if (spec.types[0].g2Name().equals("java-lang-string")) { // map to Symbol.intern(String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      "com.gensym.util.Symbol",
			      "intern",
			      "(" + STRING_DESC + ")" + SYMBOL_CLASS_DESC,
			      symbolType,
			      compiledArgs,
			      c);
      }
      else { // object
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "symbol",
			      "(" + OBJECT_DESC + ")" + SYMBOL_CLASS_DESC,
			      symbolType,
			      compiledArgs,
			      c);
      }
    }
    // END Symbol Function

    // BEGIN Text Functions
    if (spec.name.equals("CAPITALIZE-WORDS")) 
      if (spec.types[0].g2Name().equals("java-lang-string")) // map to G2Functions.capitalizeWords(String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "capitalizeWords",
			      "(" + STRING_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
      else // map to G2Functions.capitalizeWords(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "capitalizeWords",
			      "(" + OBJECT_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    if (spec.name.equals("GET-FROM-TEXT")) { 
      if (spec.types[1].g2Name().indexOf("-") == -1) // map to String.substring(int, int)
	return makeVirtualCall(uncompiledCall,
			       compiledArgs[0],
			       "java.lang.String",
			       "substring",
			       "(II)" + STRING_DESC,
			       c.stringType,
			       compiledArgs[1], // start index
			       compiledArgs[2]); // end index
      else // map to G2Functions.getFromText(String, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "getFromText",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC  + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("INSERT-IN-TEXT")) { 
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to G2Functions.insertInText(String, String, int)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertInText",
			      "(" + STRING_DESC + 
			      STRING_DESC + "I)" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
      else // map to G2Functions.insertInText(Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "insertInText",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + STRING_DESC,
			      c.objectType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("IS-CONTAINED-IN-TEXT")) { 
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to G2Functions.isContainedInString(String, String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "isContainedInText",
			      "(" + STRING_DESC + STRING_DESC + ")Z",
			      c.primBooleanType,
			      compiledArgs,
			      c);
      else // map to G2Functions.isContainedInString(Objetc, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "isContainedInText",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")Z",
			      c.primBooleanType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("LENGTH-OF-TEXT")) 
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to String.length()
	return makeVirtualCall(uncompiledCall,
			       compiledArgs[0],
			       "java.lang.String",
			       "length",
			       "()I",
			       c.primIntType);
      else // map to G2Functions.length(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "lengthOfText",
			      "(" + OBJECT_DESC + ")I",
			      c.primIntType,
			      compiledArgs,
			      c);
    if (spec.name.equals("LOWER-CASE-TEXT")) 
      if (spec.types[0].g2Name().indexOf("-") == -1) // map to String.toLowerCase()
	return makeVirtualCall(uncompiledCall,
			       compiledArgs[0],
			       "java.lang.String",
			       "toLowerCase",
			       "()" + STRING_DESC,
			       c.stringType);
      else // map to G2Functions.lowerCaseText(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "lowerCaseText",
			      "(" + OBJECT_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    if (spec.name.equals("OMIT-FROM-TEXT")) 
      if (spec.types[1].g2Name().indexOf("-") == -1) // map to G2Functions.omitFromText(String, int, int)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "omitFromText",
			      "(" + STRING_DESC + "II)" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
      else // map to G2Functions.omitFromText(Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "omitFromText",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    if (spec.name.equals("POSITION-OF-TEXT")) 
      if (spec.types[0].g2Name().equals("java-lang-string")) // map to G2Functions.positionOfText(String, String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "positionOfText",
			      "(" + STRING_DESC + STRING_DESC + ")I",
			      c.primIntType,
			      compiledArgs,
			      c); // string to search in
      else // map to G2Functions.positionOfText(Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "positionOfText",
			      "(" + OBJECT_DESC + OBJECT_DESC + ")I",
			      c.primIntType,
			      compiledArgs,
			      c);
    if (spec.name.equals("REPLACE-IN-TEXT"))
      if (spec.types[0].g2Name().equals("java-lang-string")) // map to G2Functions.replaceInText(String, String, int, int)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "replaceInText",
			      "(" + STRING_DESC + STRING_DESC + "II)" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c); // end index
      else // map to G2Functions.replaceInText(Object, Object, Object, Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "replaceInText",
			      "(" + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + OBJECT_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    if (spec.name.equals("TEXT-BEGINS-WITH-QUANTITY")) 
      if (spec.types[0].g2Name().equals("java-lang-string")) // map to G2Functions.textBeginsWithQuantity(String)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "textBeginsWithQuantity",
			      "(" + STRING_DESC + ")Z",
			      c.primBooleanType,
			      compiledArgs,
			      c); // string to test
      else // map to G2Functions.textBeginsWithQuantity(Object)
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "textBeginsWithQuantity",
			      "(" + OBJECT_DESC + ")Z",
			      c.primBooleanType,
			      compiledArgs,
			      c);
    if (spec.name.equals("UPPER-CASE-TEXT"))
      if (spec.types[0].g2Name().equals("java-lang-string")) // map to String.toUpperCase()
	return makeVirtualCall(uncompiledCall,
			       compiledArgs[0],
			       "java.lang.String",
			       "toUpperCase",
			       "()" + STRING_DESC,
			       c.stringType);
      else
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "upperCaseText",
			      "(" + OBJECT_DESC + ")" + STRING_DESC,
			      c.stringType,
			      compiledArgs,
			      c);
    // END Text Functions

    // BEGIN Time Functions
    if (spec.name.equals("YEAR")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "year",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("MONTH")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "month",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("DAY-OF-THE-MONTH")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "dayOfTheMonth",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("DAY-OF-THE-WEEK")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "dayOfTheWeek",
			      "(I)" + SYMBOL_CLASS_DESC,
			      symbolType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("MINUTE")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "minute",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("HOUR")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "hour",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("SECOND")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "second",
			      "(I)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    if (spec.name.equals("TIME")) {
	return makeStaticCall(uncompiledCall,
			      spec,
			      g2FunctionsClass,
			      "time",
			      "(IIIIII)I",
			      c.primIntType,
			      compiledArgs,
			      c);
    }
    // END Time Functions
    return null;
  }

  private static ValueNode makeEvaluatedStructureCall(G2ScriptAST uncompiledCall, 
						      Type returnType, 
						      ValueNode[] args,
						      Compiler c) {
    int attCount = args.length / 2; // we must have the right no. of args here - makeFunctionExpression guarantees this
    ValueNode[] attributeNames = new ValueNode[attCount];
    ValueNode[] attributeValues = new ValueNode[attCount];
    if (debug) System.out.println("Building structure from " + args.length + " arguments");
    // now we need to work out how many arguments we have
    int argIndex = 0;
    for (int n = 0; n < attCount; n++) {
      if (debug)
	System.out.println("Attribute " + n);
      attributeNames[n] = args[argIndex];
      attributeValues[n] = args[argIndex + 1];
      argIndex += 2; // move on to next attribute pair
    }
    try {
      Expression[] attNames = new Expression[attCount];
      Expression[] attValues = new Expression[attCount];
      for (int i = 0; i < attCount; i++) {
	attNames[i] = attributeNames[i].castTo(c, Type.forDescriptor(c, SYMBOL_CLASS_DESC));
	attValues[i] = attributeValues[i].castTo(c, c.objectType);
	if (debug) System.out.println("att " + i);
      }
      if (debug) {
	System.out.println("Generating method ref");
	System.out.println("Desc = " + "(" + SYMBOL_ARRAY_CLASS_DESC + OBJECT_ARRAY_DESC + ")V");
      }
      MethodRef consRef = new MethodRef("com.gensym.util.Structure",
					"<init>",
					"(" + SYMBOL_ARRAY_CLASS_DESC + OBJECT_ARRAY_DESC + ")V");
      if (debug) System.out.println("Generating method call");
      MethodCall constructorCall = new MethodCall(consRef,
						  new Expression[] {new NewArray(SYMBOL_ARRAY_CLASS_DESC, attNames), 
								      new NewArray(OBJECT_ARRAY_DESC, attValues)},
						  MTH_CALL_SPECIAL);
      if (debug) System.out.println("Generating new structure");
      New newStructure = new New(constructorCall);
      if (debug) System.out.println("Returning new value node");
      return new ValueNode(returnType, newStructure, uncompiledCall);
    }
    catch (ClassException ce) {
      ce.printStackTrace(System.err);
    }
    return null;
  }

  /** Returns a ValueNode containing an infix operator call on the given arguments.
   *  <arg1> <operator> <arg2>
  **/
  private static ValueNode makeInfixOperatorCall(G2ScriptAST uncompiledCall,
						 FunctionSpec spec,
						 String operator,
						 Type returnType,
						 ValueNode arg1,
						 ValueNode arg2,
						 Compiler c) {
    try {
      OperatorCall opCall = new OperatorCall(operator, new Expression[] {arg1.castTo(c, spec.types[0]), 
									   arg2.castTo(c, spec.types[1])});
      return new ValueNode(returnType, opCall, uncompiledCall);
    }
    catch (ClassException e) {
      e.printStackTrace();
      throw new RuntimeException("internal g2script error " + e.getMessage());
    }
  }
  
  /** Returns a ValueNode containing a virtual call on the specified instance (target). 
  **/
  // 0 Arg Virtual Call Utility
  private static ValueNode makeVirtualCall(G2ScriptAST uncompiledCall,
					   ValueNode target,
					   String className,
					   String methodName,
					   String descriptor,
					   Type returnType)
  {
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      MethodCall call 
	= new MethodCall(target.emit(),
			 methodRef,
			 new Expression[0],
			 MTH_CALL_VIRTUAL);
      return new ValueNode(returnType ,call,uncompiledCall);
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("internal g2script error "+e.getMessage());
      }
  }
  
  /** Returns a ValueNode containing a virtual call on the specified instance (target). 
  **/
  // 1 Arg Virtual Call Utility
  private static ValueNode makeVirtualCall(G2ScriptAST uncompiledCall,
					   ValueNode target,
					   String className, 
					   String methodName,
					   String descriptor,
					   Type returnType,
					   ValueNode arg1)
  {
    Expression[] args = null;
    if ((className.equals("java.lang.String")) && (arg1.type.g2Name().equals("integer"))) {
      // this function applies to a string, and the argument is integral, so
      // we need to decrement the argument value
      try {
	args = new Expression[] {new OperatorCall("--", new Expression[] {arg1.emit()} ) };
      } catch (ClassException ce) {
	ce.printStackTrace(System.err);
      }
    }
    else {
      args = new Expression[] {arg1.emit()};
    }
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      MethodCall call 
	= new MethodCall(target.emit(),
			 methodRef,
			 args,
			 MTH_CALL_VIRTUAL);
      return new ValueNode(returnType, call, uncompiledCall);
    }
    catch (ClassException e)
      {
	throw new RuntimeException("internal g2script error "+e.getMessage());
      }
  }

  /** Returns a ValueNode containing a virtual call on the specified instance (target). 
  **/
  // 2 Arg Virtual Call Utility
  private static ValueNode makeVirtualCall(G2ScriptAST uncompiledCall,
					   ValueNode target,
					   String className, 
					   String methodName,
					   String descriptor,
					   Type returnType,
					   ValueNode arg1,
					   ValueNode arg2)
  {
    Expression[] args = null;
    if (className.equals("java.lang.String")) {
      // this function applies to a string, if any of the arguments 
      // is integral, we need to decrement the argument value(s)
      try {
	args = new Expression[]
	  {
	    (arg1.type.g2Name().equals("integer") 
	     ? new OperatorCall("--", new Expression[] {arg1.emit()}) 
	     : arg1.emit()
	    ),
	    (arg2.type.g2Name().equals("integer") 
	     ? new OperatorCall("--", new Expression[] {arg2.emit()}) 
	     : arg2.emit()
	    )
	  };
      } catch (ClassException ce) {
	ce.printStackTrace(System.err);
      }
    }
    else {
      args = new Expression[] {arg1.emit(), arg2.emit()};
    }
    try {
      MethodRef methodRef 
	= new MethodRef(className,methodName,descriptor);
      MethodCall call 
	= new MethodCall(target.emit(),
			 methodRef,
			 args,
			 MTH_CALL_VIRTUAL);
      return new ValueNode(returnType, call, uncompiledCall);
    }
    catch (ClassException e) {
      throw new RuntimeException("internal g2script error "+e.getMessage());
    }
  }

  /** Variable optional args (as an array) with variable non-optional args
   *  Static Call Utility - returns a ValueNode containing
   *  a static call passed the given arguments
   *  @param uncompiledCall the uncompiled (G2) function call
   *  @param className the name of the class to call the static method on
   *  @param methodName the name of the method to call
   *  @param descriptor the method descriptor
   *  @param returnType the return type of the method
   *  @param args the array containing the arguments for the method
   *  @returns a ValueNode containing the method call
  **/
  private static ValueNode makeStaticCall(G2ScriptAST uncompiledCall,
					  FunctionSpec spec,
					  String className,
					  String methodName,
					  String descriptor,
					  Type returnType,
					  ValueNode[] args,
					  Compiler c)
  {
    try {
      MethodRef methodRef = new MethodRef(className, methodName, descriptor);
      int optionalCount, nonOptionalCount, mappedArgCount;
      if ((spec.minArgs == spec.optionalStart) && (spec.maxArgs == -1)) {
	// then all optional args should go in an array
	nonOptionalCount = 0; // no non-optional args
	optionalCount = args.length; // all args are optional - put them in an array
	mappedArgCount = 1; // only one argument for mapped method
      }
      else {
	if (spec.optionalStart == -1) { // no optional args at all
	  nonOptionalCount = args.length; // all args are non-optional
	  optionalCount = 0; // no optional args
	  mappedArgCount = args.length; // one-to-one mapping
	}
	else { //  mixture of optional & non-optional args
	  nonOptionalCount = spec.optionalStart - 1; // anything before the optionals begin
	  optionalCount = args.length - nonOptionalCount; // all the rest
	  mappedArgCount = optionalCount + 1; // all non-optionals + one array to hold all optionals
	}
      }

      if (debug)
	System.out.println(optionalCount + " optional args; " + nonOptionalCount + " non optional args.");

      Expression[] mappedArgs = new Expression[mappedArgCount]; // the arguments to pass to the mapped (java) method
      Expression[] optionalExpressions = null; // the un-mapped optional arguments
      Expression optionalArg = null; // will be an array which will hold the mapped optional args

      if (optionalCount > 0) { // include optional args in call
	Type optionalType = spec.types[spec.optionalStart]; // the type of the optional args
	optionalExpressions = new Expression[optionalCount]; // to hold all optionals
	for (int i = 0; i < optionalCount; i++) // put all optionals into an array
	  optionalExpressions[i] = args[nonOptionalCount + i].castTo(c, optionalType);
	// create an array to hold the variable-length list of optional args
	optionalArg = new NewArray("[" + optionalType.makeDescriptor(), optionalExpressions);
	mappedArgs[nonOptionalCount] = optionalArg; // include array at end of argument list
      }
      for (int i = 0; i < nonOptionalCount; i++) { // emit all non-optional args
	mappedArgs[i] = args[i].castTo(c, spec.types[i]);
	if (debug) {
	  System.out.println("type[" + i + "] = " + spec.types[i] + "; argType = " + args[i].type + "; desc = " + descriptor);
	}
      }
      MethodCall call = new MethodCall(methodRef,
				       mappedArgs,
				       MTH_CALL_STATIC);
      return new ValueNode(returnType, call, uncompiledCall);
    }
    catch (ClassException e){
      e.printStackTrace();
      throw new RuntimeException("internal g2script error " + e.getMessage());
    }
  }

  private static void add(String name, int minArgs, int maxArgs,
			  int optionalStart, String[] descriptors, Compiler c)
       // String targetClass, String targetMethod)
  {
    c.functionSpecs.addElement
      (new FunctionSpec(name,minArgs,maxArgs,optionalStart,descriptors, c));
      // targetClass,targetMethod));
  }
			  
  private static G2ScriptAST child(G2ScriptAST ast)
  {
    return (G2ScriptAST)ast.getFirstChild();
  }
  
  private static G2ScriptAST sibling(G2ScriptAST ast)
  {
    return (G2ScriptAST)ast.getNextSibling();
  }

  private static int siblingCount(final G2ScriptAST ast)
  {
	G2ScriptAST tree =ast;  
    int count = 0;
    while (tree.getNextSibling() != null)
      {
    	tree = sibling(tree);
    	count++;
      }
    return count;
  }
  

}

class FunctionSpec 
{
  String name;
  int minArgs;
  int maxArgs;
  int optionalStart;
  Type[] types;
  Class targetClass;
  Method targetMethod;
  static boolean debug = false;
    
  FunctionSpec(String name, int minArgs, int maxArgs,
	       int optionalStart, String[] descriptors, Compiler c)
       // String targetClass, String targetMethod)
  {
    this.name = name;
    this.minArgs = minArgs;
    this.maxArgs = maxArgs;
    this.optionalStart = optionalStart;
    int i,length = descriptors.length;
    types = new Type[length];
    try {
      for (i=0; i<length; i++)
	{
	  String descriptor = descriptors[i];
	  if (descriptor.equals("I"))
	    types[i] = c.primIntType;
	  else if (descriptor.equals("D"))
	    types[i] = c.primDoubleType;
	  else if (descriptor.equals("Z"))
	    types[i] = c.primBooleanType;
	  else if (descriptor.equals("Boolean"))
	    types[i] = c.booleanType;
	  else if (descriptor.equals("Double"))
	    types[i] = c.doubleType;
	  else if (descriptor.equals("Integer"))
	    types[i] = c.integerType;
	  else if (descriptor.equals("Number"))
	    types[i] = c.numberType;
	  else if (descriptor.equals("String"))
	    types[i] = c.stringType;
	  else
	    types[i] = Type.forDescriptor(c, descriptor);
	  //this.targetClass = Class.forName(targetClass);
	  //this.targetMethod = getDeclaredMethod( );
	}
    }
    catch (Exception e)
      {
	System.out.println("Couldn't initialize G2Script "+e.getMessage());
    	e.printStackTrace();
	System.exit(0);
      }
      
  }

  boolean isArgCountOk(int count)
  {
    return (count >= minArgs &&
	    ((maxArgs == -1) || (count <= maxArgs)));
  }
    
  boolean acceptArgument(ValueNode compiledArg, int index, Compiler c)
  {
    Type requiredType;
    Type valueType = compiledArg.type;
    if (index < types.length)
      requiredType = types[index];
    else
      requiredType = types[types.length - 1];
    if (debug) { 
      System.out.println("req = " + requiredType + "; val = " + valueType);
      System.out.println("req hash "+requiredType.hashCode()+" val hash "+valueType.hashCode());
    }
    
    boolean isNumberType = requiredType.equals(c.numberType) || requiredType.equals(c.doubleType) || requiredType.equals(c.primDoubleType);
    boolean isNumberValueType = valueType.equals(c.numberType) || valueType.equals(c.doubleType) || valueType.equals(c.integerType);
    isNumberValueType = isNumberValueType || valueType.equals(c.primDoubleType) || valueType.equals(c.primIntType);
    
    boolean isIntegerType = requiredType.equals(c.integerType) || requiredType.equals(c.primIntType);
    boolean isIntegerValueType = valueType.equals(c.integerType) || valueType.equals(c.primIntType);
    
    boolean isValidType = (isNumberType && isNumberValueType) || (isIntegerType && isIntegerValueType);
    
    return isValidType || requiredType.isAssignableFrom(valueType);
  }

  boolean perfectArgument(ValueNode compiledArg, int index, Compiler c)
  {
    Type requiredType;
    Type valueType = compiledArg.type;
    if (index < types.length)
      requiredType = types[index];
    else
      requiredType = types[types.length - 1];
    if (debug) { 
      System.out.println("req = " + requiredType + "; val = " + valueType);
      System.out.println("req hash "+requiredType.hashCode()+" val hash "+valueType.hashCode());
    }
    return requiredType.equals(valueType);
  }

}
