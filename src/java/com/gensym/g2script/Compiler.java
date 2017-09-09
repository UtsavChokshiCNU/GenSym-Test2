package com.gensym.g2script;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.util.BitSet;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;

import com.gensym.classtools.Access;
import com.gensym.classtools.Block;
import com.gensym.classtools.Break;
import com.gensym.classtools.Cast;
import com.gensym.classtools.ClassException;
import com.gensym.classtools.ClassInfo;
import com.gensym.classtools.ClassRef;
import com.gensym.classtools.Expression;
import com.gensym.classtools.ExpressionStatement;
import com.gensym.classtools.FieldInfo;
import com.gensym.classtools.FieldRef;
import com.gensym.classtools.If;
import com.gensym.classtools.MethodCall;
import com.gensym.classtools.MethodInfo;
import com.gensym.classtools.MethodRef;
import com.gensym.classtools.New;
import com.gensym.classtools.NewArray;
import com.gensym.classtools.OperatorCall;
import com.gensym.classtools.Return;
import com.gensym.classtools.RuntimeConstants;
import com.gensym.classtools.Statement;
import com.gensym.classtools.Try;
import com.gensym.classtools.Value;
import com.gensym.classtools.Variable;
import com.gensym.classtools.VariableDeclaration;
import com.gensym.classtools.While;
import com.gensym.message.Trace;
import com.gensym.rules.Condition;
import com.gensym.rules.PropertyChangeCondition;
import com.gensym.rules.Rule;
import com.gensym.rules.RuleInstance;
import com.gensym.rules.ScannedCondition;
import com.gensym.types.G2TokenReader;

import antlr.CommonAST;
import antlr.ParserException;
import antlr.collections.AST;

public class Compiler implements G2ScriptTokenTypes
{
  static boolean debug = false;
  private Vector visibleClasses = new Vector();
  private Vector locals = new Vector();  // all locals (args and otherwise)
  private Vector ruleBindings = new Vector();
  private Vector wheneverConditions = null;
  private Vector filterConditions = null;
  private Vector ruleConditions = null;
  private String methodName;
  private Vector argumentNames = new Vector();
  private StringBuffer descriptorBuffer = new StringBuffer("(");
  private ClassInfo currentClassInfo;
  private int argCount = 0;
  private int gensymCount = 0;
  private int loopAndCaseDepth = 0;
  private Type returnType;
  private Type currentType;
  boolean compilingRule = false;
  boolean compilingRuleAntecedent = false;
  Hashtable knownTypes = new Hashtable();
  Vector functionSpecs = new Vector();
  ClassInfoFactory classInfoFactory = null;
  Type booleanType;
  Type numberType;
  Type doubleType;
  Type integerType;
  Type stringType;
  Type sequenceType;
  Type structureType;
  Type symbolType;
  Type objectType;
  Type primBooleanType;
  Type primDoubleType;
  Type primIntType;
  Type enumerationType;
  Type eventObjectType;

  static String eventVariableName = "_event_object";
  static int bindingVariableCounter = 1;

  static final int MAY_RETURN = 1;
  static final int WILL_RETURN = 2;
  static final int MAY_THROW = 3;
  static final int WILL_THROW = 4;
  static final int FLAGS_SIZE = 16;
  
  public Compiler()
  {
    super();
    initializeTypeTable();
    Functions.initializeFunctionSpecs(this);
  }

  public Compiler(ClassInfoFactory classInfoFactory)
  {
    super();
    initializeTypeTable();
    Functions.initializeFunctionSpecs(this);
    this.classInfoFactory = classInfoFactory;
  }

  private void initializeTypeTable()
  {
    knownTypes.put("int",new Type(this,java.lang.Integer.TYPE));
    knownTypes.put("long",new Type(this,java.lang.Long.TYPE));
    knownTypes.put("float",new Type(this,java.lang.Float.TYPE));
    knownTypes.put("double",new Type(this,java.lang.Double.TYPE));
    knownTypes.put("boolean",new Type(this,java.lang.Boolean.TYPE));
    knownTypes.put("char",new Type(this,java.lang.Character.TYPE));
    knownTypes.put("short",new Type(this,java.lang.Short.TYPE));
    knownTypes.put("byte",new Type(this,java.lang.Byte.TYPE));
    knownTypes.put("void",new Type(this,java.lang.Void.TYPE));
    booleanType = typeForName("java.lang.Boolean");
    numberType = typeForName("java.lang.Number");
    doubleType = typeForName("java.lang.Double");
    integerType = typeForName("java.lang.Integer");
    stringType = typeForName("java.lang.String");
    objectType = typeForName("java.lang.Object");
    sequenceType = typeForName("com.gensym.util.Sequence");
    structureType = typeForName("com.gensym.util.Structure");
    symbolType = typeForName("com.gensym.util.Symbol");
    primBooleanType = typeForName("boolean");
    primDoubleType = typeForName("double");
    primIntType = typeForName("int");
    enumerationType = typeForName("java.util.Enumeration");
    eventObjectType = typeForName("java.util.EventObject");
  }

  Type typeForName(String className)
  {
    return Type.forName(this,className);
  }

  public String testCompileMethod(String methodText, ClassInfo uncompiledClass)
  {
    String compileError = "";
    try {
      compileMethod(methodText,uncompiledClass);
    } catch (CompilerException e)
      {
	compileError = e.getMessage();
      }
    return compileError;
  }

  public MethodInfo compileMethod(String methodText,
				  ClassInfo uncompiledClass,
				  Block methodBody)
       throws CompilerException
  {
    return compileMethod(new StringReader(methodText),uncompiledClass,methodBody,false);
  }
  
  public MethodInfo compileMethod(String methodText,
				  ClassInfo uncompiledClass)
       throws CompilerException
  {
    return compileMethod(new StringReader(methodText),uncompiledClass,false);
  }

  public MethodInfo compileMethod(Reader reader,
				  ClassInfo uncompiledClass,
				  boolean verbose)
       throws CompilerException
  {
    return compileMethod(reader,uncompiledClass,null,verbose);
  }

  public MethodInfo compileMethod(Reader reader,
				  ClassInfo uncompiledClass,
				  Block methodBody,
				  boolean verbose)
       throws CompilerException
  {
    currentClassInfo = uncompiledClass;
    AntlrTokenizer lexer = 
      new AntlrTokenizer(new G2TokenReader(new BufferedReader(reader)));
    G2ScriptParser parser = new G2ScriptParser(lexer);
    parser.setASTFactory(new G2ScriptASTFactory());

    currentType = Type.ensureUncompiledClassIsType(this,uncompiledClass);
    
    boolean wasDebugging = debug;
    try {
      if (verbose) debug = true;
      try {
	parser.compilationUnit();
      } catch (IOException ioe)
	{
	  throw new RuntimeException("IO exception while parsing "+ioe);
	}
      G2ScriptAST t = (G2ScriptAST)parser.getAST();
      // Print the resulting tree out in LISP notation
      if (verbose) 
	printSiblings(t);
      MethodInfo methodInfo
	= makeMethodInfo(t,uncompiledClass.getClassName(),methodBody,false);
      return methodInfo;
    } catch (ParserException e)
      {
	Trace.exception(e);
	if (debug)
	  e.printStackTrace();
	throw new CompilerException("Syntax Error: "+e.getMessage());
      }
    finally
      {
	debug = wasDebugging;
      }
  }
  
  public Rule compileRule(Reader reader,
			  ClassInfo uncompiledClass,
			  boolean verbose)
       throws CompilerException
  {
    currentClassInfo = uncompiledClass;
    AntlrTokenizer lexer = 
      new AntlrTokenizer(new G2TokenReader(new BufferedReader(reader)));
    G2ScriptParser parser = new G2ScriptParser(lexer);
    parser.setASTFactory(new G2ScriptASTFactory());

    currentType = Type.ensureUncompiledClassIsType(this,uncompiledClass);
    
    boolean wasDebugging = debug;
    try {
      if (verbose) debug = true;
      try {
	parser.rule();
      } catch (IOException ioe)
	{
	  throw new RuntimeException("IO exception while parsing "+ioe);
	}
      G2ScriptAST t = (G2ScriptAST)parser.getAST();
      // Print the resulting tree out in LISP notation
      if (verbose) 
	printSiblings(t);
      Rule rule	= compileRule2(t);
      return rule;
    } catch (ParserException e)
      {
	Trace.exception(e);
	if (debug)
	  e.printStackTrace();
	throw new CompilerException("Syntax Error: "+e.getMessage());
      }
    finally
      {
	debug = wasDebugging;
      }
  }
  
  private MethodInfo makeMethodInfo(G2ScriptAST parseResult, 
				    String className,
				    Block methodBody,
				    boolean isStatic)
       throws CompilerException
  {
    this.locals = new Vector();
    argumentNames = new Vector();
    argCount = 0;
    loopAndCaseDepth = 0;
    descriptorBuffer = new StringBuffer("(");
    compilingRule = false;
    G2ScriptAST prototype = parseResult;
    compilePrototype(prototype,isStatic);
    G2ScriptAST localsOrReturnType = sibling(prototype);
    G2ScriptAST localsOrBlock;
    
    try
      {
	if (localsOrReturnType.getType() == EQUALS)
	  {
	    if (child(localsOrReturnType) == null) // if ret spec is "= ()"
	      returnType = typeForName("void");
	    else
	      returnType = compileTypeDeclaration(child(localsOrReturnType));
	    localsOrBlock = sibling(localsOrReturnType);
	  }
	else
	  {
	    returnType = typeForName("void");
	    localsOrBlock = localsOrReturnType;
	  }
	if (debug)
	  System.out.println("returnType = "+returnType);
	descriptorBuffer.append(")"+returnType.makeDescriptor());
	Block topBlock = (methodBody == null ? new Block() : methodBody);
	//Block topBlock= new Block();
	G2ScriptAST beginAST;
	if (localsOrBlock.toString().equals("LOCALS"))
	  {
	    compileLocals(localsOrBlock,topBlock);
	    beginAST = sibling(localsOrBlock);
	  }
	else
	  beginAST = localsOrBlock;
	
	topBlock.setLineNumber(getLineNumber(beginAST));
	compileCompoundStatement(beginAST,topBlock);
	if (!getFlag(topBlock,WILL_RETURN))
	  {
	    if (returnType.equals(typeForName("void")))
	      {
		if (debug)
		  System.out.println("adding return for void method");
		topBlock.add(new Return());
	      }
	    else
	      throw new CompilerException("Method is missing return");
	  }
	
	MethodRef methodRef 
	  = new MethodRef (className, 
			   makeJavaName(methodName,false),
			   descriptorBuffer.toString());
	String[] argNameArray = new String[argCount];
	argumentNames.copyInto(argNameArray);
	//topBlock.toStdout();
	return new MethodInfo(new Access(RuntimeConstants.ACC_PUBLIC),
			      methodRef,
			      topBlock,
			      argNameArray,
			      new ClassRef[0]);
      } catch (ClassException e)
	{
	  Trace.exception(e);
	  e.printStackTrace();
	  throw new RuntimeException("Unexpected compile failure: "+e.getMessage());
	}
  }
  
  void compilePrototype(G2ScriptAST prototype, boolean isStatic)
       throws CompilerException
  {
    AST methodNameAST = prototype.getFirstChild();
    methodName = methodNameAST.toString();
    if (debug)
      System.out.println("methodName "+methodName);
    G2ScriptAST argAST = (G2ScriptAST) methodNameAST.getNextSibling();
    int i = 0;
    while (argAST != null)
      {
	G2ScriptAST argNameAST = (G2ScriptAST)argAST.getFirstChild();
	G2ScriptAST argTypeAST = (G2ScriptAST)argNameAST.getNextSibling();
	if (debug)
	  {
	    System.out.println("argname "+argNameAST);
	    System.out.println("argtype "+argTypeAST);
	  }
	Type type = compileTypeDeclaration(argTypeAST);
	LocalVariable arg = addLocal(argNameAST.toString(),type);
	
	if (i > 0 || isStatic)
	  {
	    descriptorBuffer.append(type.makeDescriptor());
	    argumentNames.addElement(arg.javaName);
	    argCount++;
	  }
	else if (i == 0 || !isStatic)
	  arg.isThis = true;
	// Should probably guarantee that arg0 of virtual methods
	// match the class being compiled
	if (debug)
	  System.out.println("compiledType "+type);
	argAST = (G2ScriptAST)argAST.getNextSibling();
	i++;
      }
  }

  Type compileTypeDeclaration(G2ScriptAST typeDeclaration)
       throws CompilerException
  {
    int tokenType = typeDeclaration.getType();
    if (tokenType == INTEGER)
      return typeForName("int");
    else if (tokenType == FLOAT)
      return typeForName("double");
    else if (tokenType == QUANTITY)
      return typeForName("java.lang.Number");
    else if (tokenType == TRUTH_VALUE)
      return typeForName("boolean");
    else if (tokenType == SYMBOL)
      return typeForName("com.gensym.util.Symbol");
    else if (tokenType == SEQUENCE)
      return typeForName("com.gensym.util.Sequence");
    else if (tokenType == STRUCTURE)
      return typeForName("com.gensym.util.Structure");
    else if (tokenType == TEXT)
      return typeForName("java.lang.String");
    else if (tokenType == VALUE || tokenType == ITEM_OR_VALUE)
      return typeForName("java.lang.Object");
    else if ((tokenType == CLASS)  ||
	     typeDeclaration.toString().equals("CLASS"))
      {
	G2ScriptAST classNameAST = child(typeDeclaration);
	String g2Name = classNameAST.toString();
	String javaName = makeJavaName(g2Name,true);
	Type result = typeForName(javaName);
	if (result == null)
	  throw new CompilerException("unknown class "+g2Name);
	else
	  return result;
      }
    else
      throw new RuntimeException("unexpected type "+typeDeclaration);
      
  }

  Type compileClassName(String g2Name)
       throws CompilerException
  {
    String javaName = makeJavaName(g2Name,true);
    Type result = typeForName(javaName);
    if (result == null)
      throw new CompilerException("unknown class "+g2Name);
    else
      return result;
  }


  void compileLocals(G2ScriptAST locals, Block block)
       throws CompilerException, ClassException
  {
    G2ScriptAST localDeclarationAST = child(locals);
    while (localDeclarationAST != null)
      {
	String head = localDeclarationAST.toString();
	G2ScriptAST typeDeclarationAST = child(localDeclarationAST);
	Type type = compileTypeDeclaration(typeDeclarationAST);
	VariableDeclaration variableDeclaration = null;
	LocalVariable local = null;
	if (head.equals("SINGLE_LOCAL"))
	  {
	    G2ScriptAST localNameAST = sibling(typeDeclarationAST);
	    G2ScriptAST expressionAST = sibling(localNameAST);
	    local = addLocal(localNameAST.toString(),type);
	    if (expressionAST != null)
	      {
		ValueNode compiledExpression
		  = ValueNode.compileExpression(expressionAST,this);
		Expression expressionOfProperType
		  = castForAssignment(expressionAST,
				      compiledExpression, 
				      local.type,
				      "local variable "+local.g2Name+" initialization");
		variableDeclaration 
		  = new VariableDeclaration(local.javaName,
					    type.makeDescriptor(),
					    expressionOfProperType);
	      }
	    else
	      variableDeclaration = 
		new VariableDeclaration(local.javaName,
					type.makeDescriptor(),
					makeDefaultValueForType(type));
	    variableDeclaration.setLineNumber(getLineNumber(localNameAST));
	    block.add(variableDeclaration);
	  }
	else if (head.equals("MULTIPLE_LOCAL"))
	  {
	    G2ScriptAST localNameAST = sibling(typeDeclarationAST);
	    while (localNameAST != null)
	      {
		local = addLocal(localNameAST.toString(),type);
		variableDeclaration 
		  = new VariableDeclaration(local.javaName,
					    type.makeDescriptor(),
					    makeDefaultValueForType(type));
		variableDeclaration.setLineNumber(getLineNumber(localNameAST));
		block.add(variableDeclaration);
		localNameAST = sibling(localNameAST);
	      }
	  }
	else
	  throw new RuntimeException("unexpected local declaration "+
				      localDeclarationAST);
	localDeclarationAST = sibling(localDeclarationAST);
      }
  }

  Expression makeDefaultValueForType(Type type)
  {
    if (type.isPrimitive())
      {
	Class clazz = type.getPrimitive();
	if (clazz == Integer.TYPE)
	  return new Value(0);
	else if (clazz == Long.TYPE)
	  return new Value((long)0);
	else if (clazz == Byte.TYPE)
	  return new Value((byte)0);
	else if (clazz == Character.TYPE)
	  return new Value((char)0);
	else if (clazz == Short.TYPE)
	  return new Value((short)0);
	else if (clazz == Float.TYPE)
	  return new Value((float)0.0);
	else if (clazz == Double.TYPE)
	  return new Value(0.0);
	else if (clazz == Boolean.TYPE)
	  return new Value(false);
	else if (clazz == Void.TYPE)
	  throw new RuntimeException("void is not a recommended default value");
	else
	  throw new RuntimeException("bad type for default value");
      }
    else if (type.equals(numberType))
      {
	try {
	  MethodRef methodRef = new MethodRef("java.lang.Integer","<init>",
					      "(I)V"); 
	  MethodCall methodCall = new MethodCall(methodRef,
						 new Expression []
						 { new Value(0) },
						 RuntimeConstants.MTH_CALL_SPECIAL);
	  return new New(methodCall);
	} catch (ClassException e)
	  {
	    // This exception is not affected by User input and has
	    // no recovery, but is almost guaranteed not to happen.
	    System.out.println("Internal G2Script Error");
	    e.printStackTrace();
	    throw new RuntimeException("Internal Compiler Failure");
	  }
      }
    else
      try {
	return new Value((Object)null);
      } catch (ClassException e)
	{
	  // this can't happen, or if it does it's a severe enough 
	  // bug in classtools that the consequences are immaterial
	  throw new RuntimeException("bad type for default value");
	}
    
  }

  void compileCompoundStatement(G2ScriptAST beginAST, Block block)
       throws CompilerException
  {
    G2ScriptAST mainBlockAST = child(beginAST);
    G2ScriptAST mainBlockFirstStatementAST = child(mainBlockAST);
    if (sibling(mainBlockAST) == null) // no on error
      compileCompoundTail(mainBlockFirstStatementAST,block);
    else
      try 
      {
	Block protectedBlock
	  = (Block) compileStatement(mainBlockAST);
	G2ScriptAST errorSymbolVarAST = sibling(mainBlockAST);
	G2ScriptAST errorTextVarAST = sibling(errorSymbolVarAST);
	G2ScriptAST handlerBlockAST = sibling(errorTextVarAST);
	LocalVariable errorSymbolVar = getLocal(child(errorSymbolVarAST).toString());
	LocalVariable errorTextVar = getLocal(child(errorTextVarAST).toString());
	
	if (!(isLocalVariableTypeEquals(errorSymbolVar, symbolType) ||
			isLocalVariableTypeEquals(errorSymbolVar, objectType)))
	  throw new CompilerException("Variable "+child(errorSymbolVarAST)+ " cannot hold a symbol");
	
	if (!(isLocalVariableTypeEquals(errorTextVar, stringType) ||
			isLocalVariableTypeEquals(errorTextVar, objectType)))
	  throw new CompilerException("Variable "+child(errorSymbolVarAST)+ " cannot hold a text");
	
	Block handlerBlock = new Block();
	handlerBlock.setLineNumber(handlerBlockAST.getLineNumber());
	// add variable assignments here
	LocalVariable exceptionLocal = addLocal("GENERATED-LOCAL-"+gensymCount++,
						typeForName("java.lang.Exception"));
	VariableDeclaration exceptionVariableDeclaration
	  = new VariableDeclaration(exceptionLocal.javaName,"Ljava/lang/Exception;");
	Variable exceptionVariable 
	  = new Variable(exceptionLocal.javaName,"Ljava/lang/Exception;");
	Variable errorSymbol = new Variable(errorSymbolVar.javaName,
					    "Lcom/gensym/util/Symbol;");
	Variable errorText = new Variable(errorTextVar.javaName,
					  "Ljava/lang/String;");
	MethodCall exceptionSymbolCall 
	  = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				     "getExceptionSymbol",
				     "(Ljava/lang/Exception;)Lcom/gensym/util/Symbol;",
				     exceptionVariable);
	Expression symbolAssign
	  = new OperatorCall("=", new Expression[] {errorSymbol, 
						      exceptionSymbolCall });
	symbolAssign.setLineNumber(getLineNumber(errorSymbolVarAST));
	MethodCall exceptionTextCall 
	  = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				     "getExceptionText",
				     "(Ljava/lang/Exception;)Ljava/lang/String;",
				     exceptionVariable);
	Expression textAssign 
	  = new OperatorCall("=", new Expression[] { errorText,
						       exceptionTextCall});
	textAssign.setLineNumber(getLineNumber(errorTextVarAST));
	handlerBlock.add(new ExpressionStatement(symbolAssign));
	handlerBlock.add(new ExpressionStatement(textAssign));
	compileCompoundTail(child(handlerBlockAST),handlerBlock);
	Try tryy 
	  = new Try(protectedBlock,
		    new VariableDeclaration[] { exceptionVariableDeclaration },
		    new Block [] { handlerBlock });
	if (debug)
	  {
	    System.out.println("protected flags "+pprintFlags(protectedBlock));
	    System.out.println("handler flags "+pprintFlags(handlerBlock));
	  }
	setFlags(tryy,combineAlternative(protectedBlock,handlerBlock));
	if (debug)
	  System.out.println("tryy flags "+pprintFlags(tryy));
	setFlags(block,combineSequential(tryy,block));
	if (debug)
	  System.out.println("outer block flags "+pprintFlags(block));
	block.add(tryy);
      } catch (ClassException e)
	{
	  throw new RuntimeException("Internal Compiler Failure");
	}
  }
  
  private boolean isLocalVariableTypeEquals(LocalVariable localVariable, Type type) {
	  boolean isErrorSymbolTypeNull = localVariable == null || localVariable.type == null;
	  return (isErrorSymbolTypeNull  && type == null) || (!isErrorSymbolTypeNull && localVariable.type.equals(type));
  }

  void compileCompoundTail(G2ScriptAST firstStatement, Block block)
       throws CompilerException
  {
    try {
      G2ScriptAST statementAST = firstStatement;
      BitSet flags = makeDefaultFlags();
      while (statementAST != null)
	{
	  Statement statement = compileStatement(statementAST);
	  block.add(statement);
	  flags = combineSequential(statement,flags);
	  // don't compile invisible code
	  if (flags.get(WILL_RETURN) || flags.get(WILL_THROW))
	    break;
	  else
	    statementAST = sibling(statementAST);
	}
      setFlags(block,flags);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  Statement compileStatement(G2ScriptAST statementAST)
       throws CompilerException, ClassException
  {
    String head = statementAST.toString();
    // possibilities CALL, EQUALS, IF, BLOCK
    if (head.equals("="))
      {
	G2ScriptAST localAST = child(statementAST);
	G2ScriptAST expressionAST = sibling(localAST);
	ValueNode node = ValueNode.compileExpression(expressionAST,this);
	LocalVariable local = getLocal(localAST.toString());
	Variable variable = new Variable(local.javaName,
					 local.type.makeDescriptor());
	variable.setLineNumber(getLineNumber(localAST));
	Expression valueExpression
	  = castForAssignment(expressionAST,node,local.type,local.g2Name);
	Expression assignment 
	  = new OperatorCall("=", new Expression[] {variable, 
						      valueExpression });
	assignment.setLineNumber(getLineNumber(statementAST));
	return new ExpressionStatement(assignment);
      }
    else if (head.equals("CALL"))
      {
	ValueNode node = ValueNode.compileExpression(statementAST,this);
	ExpressionStatement se = new ExpressionStatement(node.emit());
	se.setLineNumber(getLineNumber(statementAST));
	return se;
      }
    else if (head.equals("IF"))
      {
	G2ScriptAST conditionAST = child(statementAST);
	ValueNode node = ValueNode.compileExpression(conditionAST,this);
	if (canPerformNumericOrLogicalAssignment(primBooleanType,node.type))
	  {
	    Expression booleanExpression 
	      = castForAssignment(conditionAST,node,primBooleanType,
				  "if statement test expression");
	    G2ScriptAST thenAST = sibling(conditionAST);
	    G2ScriptAST elseAST = sibling(thenAST);
	    If theIf;
	    if (elseAST != null)
	      {
		Statement thenStatement = compileStatement(thenAST);
		Statement elseStatement = compileStatement(elseAST);
		theIf = new If(booleanExpression,thenStatement,elseStatement);
		setFlags(theIf,combineAlternative(thenStatement,elseStatement));
	      }
	    else
	      {
		Statement thenStatement = compileStatement(thenAST);
		theIf = new If(booleanExpression,thenStatement);
		setFlags(theIf,combineAlternative(thenStatement,makeDefaultFlags()));
	      }
	    theIf.setLineNumber(getLineNumber(statementAST));
	    return theIf;
	  }
	else 
	  throw new CompilerException("if statment condition must produce a truth-value");
      }
    else if (head.equals("RETURN"))
      {
	G2ScriptAST expressionAST = child(statementAST);
	if (expressionAST == null && returnType.isVoid())
	  {
	    Return theReturn = new Return();
	    theReturn.setLineNumber(getLineNumber(statementAST));
	    setFlag(theReturn,WILL_RETURN);
	    return theReturn;
	  }
	else if (expressionAST == null)
	  throw new CompilerException("return must be of type "+returnType.g2Name());
	else
	  {
	    ValueNode compiledExpression
	      = ValueNode.compileExpression(expressionAST,this);
	    Expression returnExpression
	      = castForAssignment(expressionAST,compiledExpression,
				  returnType,"method return value");
	    Return theReturn = new Return(returnExpression);
	    theReturn.setLineNumber(getLineNumber(statementAST));
	    setFlag(theReturn,WILL_RETURN);
	    return theReturn;
	  }
      }
    else if (head.equals("BEGIN"))
      {
	Block subBlock = new Block();
	subBlock.setLineNumber(getLineNumber(statementAST));
	compileCompoundStatement(statementAST, subBlock);
	return subBlock;
      }
    else if (head.equals("BLOCK"))
      {
	Block subBlock = new Block();
	subBlock.setLineNumber(getLineNumber(statementAST));
	G2ScriptAST firstStatement = child(statementAST);
	if (firstStatement != null)
	  compileCompoundTail(firstStatement, subBlock);
	return subBlock;
      }
    else if (head.equals("CREATE"))
      // only handle zero-arg constructors now
      {
	G2ScriptAST typeSpecAST = child(statementAST);
	Type newObjectType = compileTypeDeclaration(typeSpecAST);
	G2ScriptAST localAST = sibling(typeSpecAST);
	LocalVariable local = getLocal(localAST.toString(),!compilingRule);
	// support auto-declaration of variables for rule
	if (local == null && compilingRule)
	  local = addLocal(localAST.toString(),objectType);
	if (debug)
	  System.out.println("in CREATE local = "+local+" localType "+
			     local.type+" new Obj Type "+newObjectType);
	Variable variable = new Variable(local.javaName,
					 local.type.makeDescriptor());
	variable.setLineNumber(getLineNumber(localAST));
	String classNameToCreate = newObjectType.getName();
	String defaultImplementationClassName = null;
	Expression newExpression;
	ValueNode newExpressionNode;
	if (classInfoFactory != null &&
	    ((defaultImplementationClassName 
	      = classInfoFactory.getImplementationClassName(classNameToCreate))
	     != null))
	  {
	    newExpression
	      = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					 "newVersionedImplementionClass",
					 "(Ljava/lang/String;Ljava/lang/String;"+
					 "Ljava/lang/Object;)Ljava/lang/Object;",
					 // need extra arg for the owner of 
					 // the method making this call
					 // need for lookupObject as well
					 new Value((String)classNameToCreate),
					 new Value((String)defaultImplementationClassName),
					 makeThisVariable());
	    newExpressionNode = new ValueNode(objectType,newExpression,typeSpecAST);
	  }
	else
	  {
	    newExpression = new New(newObjectType.getName());
	    newExpressionNode = new ValueNode(newObjectType,newExpression,typeSpecAST);
	  }
	newExpression.setLineNumber(getLineNumber(statementAST));
	Expression castNewExpression
	  = castForAssignment(typeSpecAST,
			      newExpressionNode,
			      local.type,
			      "newly created object");
	Expression assignment 
	  = new OperatorCall("=", new Expression[] {variable, castNewExpression });
	assignment.setLineNumber(getLineNumber(statementAST));
	ExpressionStatement se = new ExpressionStatement(assignment);
	se.setLineNumber(getLineNumber(statementAST));
	return se;
      }
    else if (head.equals("INFORM"))
      {
	G2ScriptAST stringExpressionAST = child(statementAST);
	int lineNumber = getLineNumber(statementAST);
	FieldRef systemOut = new FieldRef("java.lang.System",
					  "out",
					  "Ljava/io/PrintStream;",
					  true);
	systemOut.setLineNumber(lineNumber);
	ValueNode compiledExpression
	      = ValueNode.compileExpression(stringExpressionAST,this);
	MethodRef printlnMethodRef 
	  = new MethodRef("java.io.PrintStream",
			  "println",
			  "(Ljava/lang/String;)V");
	MethodCall call 
	  = new MethodCall(systemOut,
			   printlnMethodRef,
			   new Expression[] {compiledExpression.emit() },
			   RuntimeConstants.MTH_CALL_VIRTUAL);
	call.setLineNumber(lineNumber);
	ExpressionStatement se = new ExpressionStatement(call);
	se.setLineNumber(lineNumber);
	return se;
      }
    else if (head.equals("REPEAT"))
      {
	loopAndCaseDepth++;
	While whileStatement = 
	  new While(new Value(true),
		    compileStatement(child(statementAST)));
	whileStatement.setLineNumber(getLineNumber(statementAST));
	loopAndCaseDepth--;
	return whileStatement;
      }
    else if (head.equals("EXIT"))
      {
	if (loopAndCaseDepth == 0)
	  throw new CompilerException("no loop or case from which to exit");
	ValueNode condition = ValueNode.compileExpression(child(statementAST),this);
	if (!condition.type.equals(typeForName("boolean")))
	  throw new CompilerException("exit if must use a truth-value expression");
	Statement exitIfStatement 
	  = new If(condition.emit(),new Break());
	exitIfStatement.setLineNumber(getLineNumber(statementAST));
	return exitIfStatement;
      }
    else if (head.equals("FOR"))
      return compileForStatement(statementAST);
    else if (head.equals("START"))
      return compileStartAction(statementAST);
    else if (head.equals("ALLOW"))
      return new ExpressionStatement(); // a no-op
    else if (head.equals("SIGNAL"))
      return compileSignal(statementAST);
    else if (head.equals("DELETE"))
      return compileDeleteAction(statementAST);
    else if (head.equals("CONCLUDE"))
      return compileConcludeAction(statementAST);
    else if (head.equals("WAIT"))
      return compileWaitStatement(statementAST);
    else if (head.equals("CHANGE"))
      return compileChangeColorStatement(statementAST);
    else 
      throw new RuntimeException("expected statement type "+head);
  }

  boolean canPerformNumericOrLogicalAssignment(Type placeType,
					       Type expressionType)
  {
	boolean isPrimeBoolExpType =   expressionType.equals(primBooleanType) || expressionType.equals(objectType);
	
	boolean isIntExpressionType = expressionType.equals(primIntType) || expressionType.equals(numberType) 
							|| expressionType.equals(integerType) || expressionType.equals(objectType);
	boolean isPrimeIntType = isIntExpressionType && placeType.equals(primIntType);
	
	boolean isPrimeDoubleType = placeType.equals(primDoubleType) && (expressionType.equals(primDoubleType) 
							|| numberType.isAssignableFrom(expressionType) || expressionType.equals(objectType));
	
	boolean isNumberPlaceType = placeType.equals(numberType) || placeType.equals(objectType);
	boolean isMixExpressionType = expressionType.equals(primIntType) || expressionType.equals(primDoubleType) 
								|| isPrimeBoolExpType || numberType.isAssignableFrom(expressionType);
	
	isNumberPlaceType = isNumberPlaceType && isMixExpressionType;
	
	boolean isBooleanType = placeType.equals(primBooleanType) && (isPrimeBoolExpType || expressionType.equals(booleanType));

    return isPrimeIntType || isPrimeDoubleType || isNumberPlaceType || isBooleanType;
  }

  // trivial assignments are already handled
  //   (i.e. class from subclass, subclass from class with explicit cast)
  // i.e double <- double
  // i.e int <- int
  // input must have passed canPerformNumericOrLogicalAssignment()
  private Expression buildNumericAssignment(G2ScriptAST expressionAST,
					    ValueNode node,
					    Type placeType)
  {
    try 
      {
	if (placeType.equals(primIntType))
	  {
	    MethodRef extractMethodRef 
	      = new MethodRef("com.gensym.g2scriptruntime.Math",
			      "extractIntFromNumber",
			      "(Ljava/lang/Object;)I");
	    return new MethodCall(extractMethodRef,
				  new Expression [] { node.emit() },
				  RuntimeConstants.MTH_CALL_STATIC);
	  }
	else if (placeType.equals(primDoubleType))
	  {
	    MethodRef extractMethodRef 
	      = new MethodRef("com.gensym.g2scriptruntime.Math",
			      "extractDoubleFromNumber",
			      "(Ljava/lang/Object;)D");
	    return new MethodCall(extractMethodRef,
				  new Expression [] { node.emit() },
				  RuntimeConstants.MTH_CALL_STATIC);
	  }
	else if (placeType.equals(primBooleanType))
	  {
	    MethodRef extractMethodRef 
	      = new MethodRef("com.gensym.g2scriptruntime.Math",
			      "extractBooleanFromObject",
			      "(Ljava/lang/Object;)B");
	    return new MethodCall(extractMethodRef,
				  new Expression [] { node.emit() },
				  RuntimeConstants.MTH_CALL_STATIC);
	  }
	else if ((placeType.equals(numberType) && !node.type.equals(primBooleanType)) || 
		 placeType.equals(objectType))
	  {
	    MethodRef methodRef 
	      = (node.type.equals(primBooleanType) ?
		 new MethodRef("java.lang.Boolean","<init>","(Z)V") :
		 (node.type.equals(primIntType)) ?
		 new MethodRef("java.lang.Integer","<init>","(I)V")  :
		 new MethodRef("java.lang.Double","<init>","(D)V"));
	    MethodCall methodCall = new MethodCall(methodRef,
						   new Expression []
						   { node.emit() },
						   RuntimeConstants.MTH_CALL_SPECIAL);
	    return new New(methodCall);
	  }
        else 
	  throw new RuntimeException("Internal Error: bad G2 Script numerical conversion");
      }
    catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Exception");
      }
  }
 
  private Statement compileForStatement(G2ScriptAST statementAST)
       throws CompilerException
  {
    // FOR var lower direction upper increment? block
    loopAndCaseDepth++;
    G2ScriptAST localAST = child(statementAST);
    G2ScriptAST iterationSpecAST = sibling(localAST);
    G2ScriptAST blockAST = sibling(iterationSpecAST);
    if (iterationSpecAST.toString().equals("="))
      return compileIntegerForStatement(statementAST,localAST,
					iterationSpecAST,blockAST);
    else
      return compileEnumerationForStatement(statementAST,localAST,
					    iterationSpecAST,blockAST);
  }

  private Statement compileIntegerForStatement(G2ScriptAST statementAST,
					       G2ScriptAST localAST,
					       G2ScriptAST iterationSpecAST,
					       G2ScriptAST blockAST)
       throws CompilerException
  {
    G2ScriptAST lowerLimitAST = child(iterationSpecAST);
    G2ScriptAST directionAST =  sibling(lowerLimitAST);
    G2ScriptAST upperLimitAST = sibling(directionAST);
    G2ScriptAST incrementAST = sibling(upperLimitAST); // may be NULL


    // G2 binds the upper limit and increment values upon entry 
    // to FOR statement, unlike java
    boolean isIncreasing = directionAST.toString().equals("TO");
    LocalVariable counter = getLocal(child(localAST).toString());
    if (!counter.type.equals(primIntType))
      throw new CompilerException("Loop Counter "+child(localAST).toString()+
				  " must be an integer");
    
    
    try {
      ValueNode compiledLowerLimit = ValueNode.compileExpression(lowerLimitAST,this);
      if (!compiledLowerLimit.type.equals(primIntType))
	throw new CompilerException("Loop initial value of "+child(localAST).toString()+
				    " must be an integer");
      ValueNode compiledUpperLimit = ValueNode.compileExpression(upperLimitAST,this);
      if (!compiledUpperLimit.type.equals(primIntType))
	throw new CompilerException("Loop limit of "+child(localAST).toString()+
				    " must be an integer");
      Expression incrementExpression;
      if (incrementAST == null)
	incrementExpression = new Value(isIncreasing ? 1 : -1);
      else
	{
	  ValueNode compiledIncrement = ValueNode.compileExpression(incrementAST,this);
	  if (!compiledIncrement.type.equals(primIntType)) 
	    throw new CompilerException("Loop increment of "+child(localAST).toString()+
					" must be an integer");
	  incrementExpression = compiledIncrement.emit();
	}
      LocalVariable upperLimit = addLocal("GENERATED-LOCAL-"+gensymCount++,
					  primIntType);
      LocalVariable increment = addLocal("GENERATED-LOCAL-"+gensymCount++,
					 primIntType);
      Variable counterVariable = new Variable(counter.javaName,"I");
      Block result = new Block();
      result.add(new VariableDeclaration(upperLimit.javaName,"I",
					 compiledUpperLimit.emit()));
      result.add(new VariableDeclaration(increment.javaName,"I",
					 incrementExpression));
      Variable limitVariable = new Variable(upperLimit.javaName,"I");
      Variable incrementVariable = new Variable(increment.javaName,"I");
      /*
      result.add(new ExpressionStatement
		 (new OperatorCall("=",
				   new Expression[] {limitVariable,
						       compiledUpperLimit.emit() })));
      result.add(new ExpressionStatement
		 (new OperatorCall("=",
				   new Expression[] {incrementVariable,
						       incrementExpression })));
						       */
      Expression assignment 
	= new OperatorCall("=", new Expression[] {counterVariable, 
						    compiledLowerLimit.emit()});
      assignment.setLineNumber(getLineNumber(statementAST));
      ExpressionStatement assignmentStatement =  new ExpressionStatement(assignment);
      
      Expression update
	= new OperatorCall("+=", new Expression[] { counterVariable,
						      incrementVariable});
      ExpressionStatement updateStatement = new ExpressionStatement(update);
      Statement compiledBlock = compileStatement(blockAST);
      result.add(assignmentStatement);
      Block loopBody = new Block();
      loopBody.add(compiledBlock);
      loopBody.add(updateStatement);
      While theLoop 
	= new While(new OperatorCall (isIncreasing ? "<=" : ">=",
				      new Expression[] { counterVariable,
							   limitVariable }),
		    loopBody);
      result.add(theLoop);
      loopAndCaseDepth--;
      return result;
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure "+e.getMessage());
      }
  }

  private Statement compileEnumerationForStatement(G2ScriptAST statementAST,
						   G2ScriptAST localAST,
						   G2ScriptAST iterationSpecAST,
						   G2ScriptAST blockAST)
       throws CompilerException
  {
    try {
      G2ScriptAST typeSpecAST = child(iterationSpecAST);
      G2ScriptAST operationAST = sibling(typeSpecAST);
      LocalVariable elementLocal = getLocal(child(localAST).toString());
      Variable elementVariable = new Variable(elementLocal.javaName,
					      elementLocal.type.makeDescriptor());
      Type elementType = compileTypeDeclaration(typeSpecAST);
      Expression enumerationExpression = null;
      if (operationAST == null) // iteration of all class members
	{
	  if (elementType.isPrimitive() ||
	      elementType.equals(stringType) ||
	      numberType.isAssignableFrom(elementType))
	    throw new CompilerException("cannot iterate all elements of "+elementType);
	  enumerationExpression 
	    = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				       "getClassEnumeration",
				       "(Ljava/lang/String;)Ljava/util/Enumeration;",
				       new Value((String)elementType.getName()));
	}
      else if (operationAST.toString().equals("IN"))
	{
	  ValueNode compiledAggregate 
	    = ValueNode.compileExpression(sibling(operationAST), this);
	  enumerationExpression 
	    = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				       "getAggregateEnumeration",
				       "(Ljava/lang/Object;)Ljava/util/Enumeration;",
				       compiledAggregate.emit());
	}
      LocalVariable enumeration = addLocal("GENERATED-LOCAL-"+gensymCount++,
					   enumerationType);
      LocalVariable unfilteredElement = addLocal("GENERATED-LOCAL-"+gensymCount++,
						 objectType);
      Block result = new Block();
      result.add(new VariableDeclaration(enumeration.javaName,
					 enumerationType.makeDescriptor(),
					 enumerationExpression));
      result.add(new VariableDeclaration(unfilteredElement.javaName,
					 "Ljava/lang/Object;"));
      Variable enumerationVariable = new Variable(enumeration.javaName,
						  enumerationType.makeDescriptor());  
      Variable unfilteredElementVariable = new Variable(unfilteredElement.javaName,
							"Ljava/lang/Object;");
      Statement compiledBlock = compileStatement(blockAST);
      MethodCall nextElementCall 
	= ValueNode.makeInstanceCall(true,enumerationVariable,
				     "java.util.Enumeration",
				     "nextElement",
				     "()Ljava/lang/Object;");
      ExpressionStatement unfilteredAssignmentStatement
	= new ExpressionStatement(new OperatorCall("=",
						   new Expression[]
						   { unfilteredElementVariable,
						       nextElementCall }));
      ValueNode nextValueNode 
	= new ValueNode(objectType,
			unfilteredElementVariable,
			iterationSpecAST);
      ExpressionStatement assignmentStatement = 
	new ExpressionStatement
	(new OperatorCall("=",
			  new Expression[]
			  { elementVariable,
			      castForAssignment(iterationSpecAST,
						nextValueNode,
						elementType,
						"for-each enumerated value") }));
      Block filteredBody = new Block();
      filteredBody.add(assignmentStatement);
      filteredBody.add(compiledBlock);
      Block loopBody = new Block();
      loopBody.add(unfilteredAssignmentStatement);
      loopBody.add(new If(new OperatorCall("instanceof",
					   new Expression[]
					   { unfilteredElementVariable,
					       new ClassRef(elementType.getName()) }),
			  filteredBody));
      While theLoop 
	= new While(ValueNode.makeInstanceCall(true,
					       enumerationVariable,
					       "java.util.Enumeration",
					       "hasMoreElements",
					       "()Z"),
		    loopBody);
      result.add(theLoop);
      loopAndCaseDepth--;
      return result;
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure "+e.getMessage());
      }
  }
  
  private Statement compileStartAction(G2ScriptAST statementAST)
       throws CompilerException
  {
    G2ScriptAST methodAST = child(statementAST);
    String methodNameLocal = null;
    String className = null;
    boolean isStatic = false;
    int i = 0 ;
    int argCountLocal = 0;

    if (methodAST.getType() == UNRESERVED) // virtual invocation
      methodNameLocal = makeJavaName(methodAST.toString(),false);
    else
      {
	G2ScriptAST staticMethodNameAST = child(methodAST);
	G2ScriptAST staticMethodClassAST = sibling(staticMethodNameAST);
	className = makeJavaName(staticMethodClassAST.toString(),true);
	methodNameLocal = makeJavaName(staticMethodNameAST.toString(),false);
	isStatic = true;
      }
    
    Vector compiledArgVector = new Vector();
    G2ScriptAST argAST = sibling(methodAST);
    ValueNode compiledTarget = null;
    Expression priority = null, delay = null;

    if (!isStatic)
      {
	compiledTarget = ValueNode.compileExpression(argAST,this);
	argAST = sibling(argAST);
      }
    while (argAST != null)
      {
	if (debug)
	  System.out.println("arg loop "+i+" arg "+argAST.toString());
	String head = argAST.toString();
	if (head.equals("PRIORITY"))
	  {
	    ValueNode priorityNode = ValueNode.compileExpression(child(argAST),this);
	    priority = ValueNode.wrapAsIntExpression(this,priorityNode);
	  }
	else if (head.equals("AFTER"))
	  {
	    ValueNode delayNode = ValueNode.compileExpression(child(argAST),this);
	    ValueNode castedDelayNode = ValueNode.wrapAsNumber(this,delayNode,false);
	    delay = castedDelayNode.emit();
	  }
	else
	  {
	    ValueNode compiledArg  = ValueNode.compileExpression(argAST,this);
	    compiledArgVector.addElement(ValueNode.wrapAsNumber(this,compiledArg,true));
	    argCountLocal++;
	  }
	argAST = sibling(argAST);
      }
    if (argCountLocal == 0 && !isStatic)
      throw new CompilerException("non static call must have at least one argument");
    Expression[] newArrayArgs = new Expression[argCountLocal];
    for (i=0; i<argCountLocal ; i++)
      newArrayArgs[i] = ((ValueNode)compiledArgVector.elementAt(i)).expression;
    if (debug)
      System.out.println((isStatic ? "static " : "virtual")+
			 "method "+methodNameLocal+" has "+argCountLocal+" args");
    try {
      NewArray argArray = new NewArray("[Ljava.lang.Object;",newArrayArgs);
      if (delay == null)
	delay = makeDefaultValueForType(numberType);
      if (priority == null)
	priority = new Value(-2);
      MethodRef methodRef 
	= new MethodRef ("com.gensym.g2scriptruntime.Kernel", 
			 isStatic ? "startStatic" : "startVirtual",
			 (isStatic ? "(Ljava/lang/String;" : "(Ljava/lang/Object;") + 
			 "Ljava/lang/String;[Ljava/lang/Object;Ljava/lang/Number;I)V");
      
      MethodCall call = new MethodCall(methodRef,
				       new Expression[] 
				       {  (isStatic ? new Value(className) :
					   compiledTarget.emit()),
					  new Value(methodNameLocal),
					  argArray,
					  delay,
					  priority },
				       RuntimeConstants.MTH_CALL_STATIC);
      call.setLineNumber(getLineNumber(statementAST));
      return new ExpressionStatement(call);
    }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  private Statement compileDeleteAction(G2ScriptAST statementAST)
       throws CompilerException
  {
    G2ScriptAST designationAST = child(statementAST);
    Designation designation 
      = Designation.compileDesignation(designationAST,this,false);
    return compileConcludeAction2(designation,null,designationAST);
  }

  private Statement compileConcludeAction(G2ScriptAST statementAST)
       throws CompilerException
  {
    G2ScriptAST designationAST = child(statementAST);
    Designation designation 
      = Designation.compileDesignation(designationAST,this,false);
    G2ScriptAST assignmentAST = sibling(designationAST);
    ValueNode expression = null;
    if (assignmentAST.getType() == EQUALS)
      {
	expression = ValueNode.compileExpression(sibling(assignmentAST),this);
      }

    if (designation.code == Designation.VARIABLE_REFERENCE)
      throw new CompilerException("Global variables not yet supported"+
				  designationAST);

    return compileConcludeAction2(designation,expression,designationAST);
  }

  private Statement compileConcludeAction2(Designation designation,
					   ValueNode node,
					   G2ScriptAST designationAST)
       throws CompilerException
  {
    Type placeType = designation.placeType;
    ValueNode root = designation.rootNode;
    Expression expression;
    // first case: setting null into a reference is always okay
    try {
      if (node == null)
	{
	  if (placeType != null && placeType.isPrimitive())
	    throw new CompilerException("Cannot delete/conclude no-value into "+
					placeType);
	  else
	    expression = new Value(null);
	}
      else
	expression =  castForAssignment(designationAST,node,placeType,
					designation.toString());

      switch (designation.code)
	{
	case Designation.VARIABLE_REFERENCE:
	  Variable variable = new Variable(designation.localName,
					   placeType.makeDescriptor());
	  Expression assignment 
	    = new OperatorCall("=", new Expression[] {variable, expression });
	  assignment.setLineNumber(getLineNumber(designationAST));
	  return new ExpressionStatement(assignment);
	case Designation.ARRAY_REFERENCE:
	  ValueNode index = designation.indexExpression;
	  Expression assignmentCall;
	  if (index.type.equals(primIntType))
	    {
	      assignmentCall = 
		ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					 "setArrayOrSequenceElement",
					 "(Ljava/lang/Object;ILjava/lang/Object;)V",
					 root.emit(),
					 index.emit(),
					 expression);
	      assignmentCall.setLineNumber(getLineNumber(designationAST));
	      return new ExpressionStatement(assignmentCall);
	    }
	  else if (index.type.equals(integerType) || index.type.equals(numberType) || index.type.equals(objectType))
	    {
	      assignmentCall = 
		ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					 "setArrayOrSequenceElement",
					 "(Ljava/lang/Object;Ljava/lang/Object;"+
					 "Ljava/lang/Object;)V",
					 root.emit(),
					 index.emit(),
					 expression);
	      assignmentCall.setLineNumber(getLineNumber(designationAST));
	      return new ExpressionStatement(assignmentCall);
	    }
	  else
	    throw new CompilerException("index expression is not an integer");
	case Designation.FIELD_REFERENCE:
	  if (designation.fieldFoundAtCompileTime)
	    try 
	    {
	      Expression fieldAssign;
	      if (designation.isImplicitProperty &&
		  designation.propertySetterName != null)
		fieldAssign 
		  = ValueNode.makeInstanceCall(true,
					       root.emit(),
					       root.type.getName(),
					       designation.propertySetterName,
					       "("+placeType.makeDescriptor()+")V",
					       expression);
	      else if (designation.isImplicitProperty)
		throw new CompilerException("attempting to conclude to "+
					    designation.g2AttributeName+
					    ", which is read-only");
	      else
		{
		  FieldRef fieldRef = new FieldRef(root.emit(),
						   designation.fieldName,
						   placeType.makeDescriptor());
		  fieldAssign
		    = new OperatorCall("=", new Expression[] { fieldRef, expression });
		}
	      fieldAssign.setLineNumber(designationAST.getLineNumber());
	      return new ExpressionStatement(fieldAssign);
	    } catch (ClassException e)
	      {
		throw new RuntimeException("Internal Compiler Failure");
	      }
	  else // compile into slow, painful run-time lookup
	    {
	      MethodCall call 
		= ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					   "setInstanceField",
					   "(Ljava/lang/Object;Ljava/lang/String;"+
					   "Ljava/lang/Object;)V",
					   designation.rootNode.emit(),
					   new Value(designation.fieldName),
					   expression);
	      call.setLineNumber(designationAST.getLineNumber());
	      return new ExpressionStatement(call);
	    }
	case Designation.STATIC_FIELD_REFERENCE:
	  Type classType = designation.staticClass;
	  if (designation.fieldFoundAtCompileTime)
	    try 
	    {
	      FieldRef fieldRef = new FieldRef(classType.getName(),
					       designation.fieldName,
					       placeType.makeDescriptor(),
					       true);
	      Expression fieldAssign
		= new OperatorCall("=", new Expression[] { fieldRef, expression });
	      fieldAssign.setLineNumber(designationAST.getLineNumber());
	      return new ExpressionStatement(fieldAssign);
	    } catch (ClassException e)
	      {
		throw new RuntimeException("Internal Compiler Failure");
	      }
	  else
	    {
	      MethodCall call 
		= ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					   "setStaticField",
					   "(Ljava/lang/String;Ljava/lang/String;"+
					   "Ljava/lang/Object;)V",
					   new Value(classType.getName()),
					   new Value(designation.fieldName),
					   expression);
	      call.setLineNumber(designationAST.getLineNumber());
	      return new ExpressionStatement(call);
	    }
	default:
	  throw new RuntimeException("Internal Compiler Failure");
	}
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  private Statement compileSignal(G2ScriptAST signalAST)
       throws CompilerException
  {
    G2ScriptAST arg1AST, errorSymbolAST, errorTextAST;
    arg1AST = child(signalAST);
    if (sibling(arg1AST) == null)
      throw new CompilerException("1-arg signal statement not yet supported");
    else
      {
	errorSymbolAST = arg1AST;
	errorTextAST = sibling(arg1AST);
	ValueNode errorSymbol = ValueNode.compileExpression(errorSymbolAST,this);
	ValueNode errorText = ValueNode.compileExpression(errorTextAST,this);
	if (!(errorSymbol.type.equals(symbolType) || errorSymbol.type.equals(objectType)))
	  throw new CompilerException("error name is not a symbol "+errorSymbolAST);
	else if (!(errorText.type.equals(stringType) || errorText.type.equals(objectType)))
	  throw new CompilerException("error text is not a text "+errorTextAST);
	else
	  {
	    try 
	      {
		MethodCall call 
		  = ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
					     "signal",
					     "(Ljava/lang/Object;Ljava/lang/Object;)V",
					     errorSymbol.emit(), errorText.emit());
		call.setLineNumber(signalAST.getLineNumber());
		ExpressionStatement signal = new ExpressionStatement(call);
		setFlag(signal,WILL_THROW);
		return signal;
	      }
	    catch (ClassException e)
	      {
		throw new RuntimeException("Internal Compiler Failure");
	      }
	  }
      }
  }

  private Statement compileChangeColorStatement(G2ScriptAST statementAST)
       throws CompilerException
  {
    try {
      G2ScriptAST regionNameAST = child(statementAST);
      G2ScriptAST objectAST = sibling(regionNameAST);
      G2ScriptAST colorAST = sibling(objectAST);
      
      FieldRef regionSymbol = getOrMakeSymbolConstant(regionNameAST.toString());
      ValueNode compiledObject = ValueNode.compileExpression(objectAST,this);
      FieldRef colorSymbol = getOrMakeSymbolConstant(colorAST.toString());
      
      MethodCall call
	= ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				   "setIconRegionColor",
				   "(Ljava/lang/Object;Lcom/gensym/util/Symbol;"+
				   "Lcom/gensym/util/Symbol;)V",
				   compiledObject.expression,
				   regionSymbol,
				   colorSymbol);
      call.setLineNumber(statementAST.getLineNumber());
      ExpressionStatement wait = new ExpressionStatement(call);
      return wait;
    } catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  private Statement compileWaitStatement(G2ScriptAST statementAST)
       throws CompilerException
  {
    try {
      ValueNode delayNode = ValueNode.compileExpression(child(statementAST),this);
      ValueNode castedDelayNode = ValueNode.wrapAsNumber(this,delayNode,false);
      MethodCall call 
	= ValueNode.makeStaticCall("com.gensym.g2scriptruntime.Kernel",
				   "waitForInterval",
				   "(Ljava/lang/Number;)V",
				   castedDelayNode.emit());
      call.setLineNumber(statementAST.getLineNumber());
      ExpressionStatement wait = new ExpressionStatement(call);
      return wait;
    } catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Failure");
      }
  }
    
  // Rule Compilations

 private Rule compileRule2(G2ScriptAST parseResult)
       throws CompilerException
  {
    locals = new Vector();
    ruleBindings = new Vector();
    argumentNames = new Vector();
    argCount = 0;
    loopAndCaseDepth = 0;
    descriptorBuffer = new StringBuffer("(");
    compilingRule = true;

    try
      {
	// generate pack and unpack method from ruleBindings vector
	// handle different rule syntax cases (if, when, whenever and when)
	//    allowing filter code to be generated
	// make filter
	// add scan interval to Rule 
	// build rmi test harness for rule installation and testing
	//   - factoring out moving ruleinstance code
	// Worry about Rule.install()
	// Worry about Rule.invokeRuleEngine
	//   - the two previous worries are mostly worries about unique keying from
        //   - conditions to Rules and their associated RuleInstances
	// worry about rules with scan intervals that want to sweep over their domains
	// 
	// step one categorize rules and their means of activation
	//  whenever rules only trigger on conditions
	//  unconditionally and when rules only trigger on scan intervals
	//  if rules trigger on conditions of ...
	//
	// ASSERTION 1:
	// when and if rules are the same aside from default chaining options
	//  i.e. "(not)? invocable by forward chaining"
	// ASSERTION 2:
	// unconditionally rules are marked as invocable by forward chaining by default,
	// but this is a mystery as they effectively have no antecedent.
	
	// here: verify iterative vs chained behavior of generate-rule-context-vectors

	// Rule antecedents must execute receiving bindings either from scanning
	// or chaining equally.  The invocatio and scheduling harness is responsible
	// for taking java events and turning them into chaining focii, or iterating
	// over instances using the naming service.  Only the fundamental domain
	// instantiation is outside the methods of the antecedent.  All further filtering
	// and connection and relation chasing must occur in the code.

	// Experiment 1:  look at compilation of rules with "connected to" (and the like)
	//       to see if the byte-code-bodies implement these as boolean expressions
	//       or is it factored outside for generate-rule-context-vectors
	// Answer:  the compilate of roles/designations is outside the byte-code body
	
	// Experiment 2: look at the parse trees of various rules in java and see if
	//       there is a simple way of replacing any's and globals with locals
	//       and an accumulation of nested quantifiers.  The quantifiers may
	//       be also seen as chaining-links/conditions as single matches can
	//       instantiate the local the replaced the quantifier

	// chaining links can be based on an attribute of class, receipt of 
	// generic event, or reference to a global

	// Re-write to do
	// 1 compileAntecedent
	//     factor out any's
	//     ensure expression is boolean
	//     search for top level attr refs (and globals if we ever implement them)
	// 2 fix compileWhenever conditions
	//     dont build establishBindings block
	//      - or - can it be modified to be used for all chaining-based activation
	//     on second thought whenever conditions are more like "if" antecedents 
	//       and need the same scan for substitutions and chaining links
	//     maybe extend condition to know about substitution names
	//     maybe change demand binding to type rule instance variables/fields strongly
	// 3 pack/unpack
	// 4 runtime re-wiring
	//    installing
	//    scanning thread
	//    scanning domain iteration driver
	//    chaining binding substitution mechanism
	//    chaining will supply a subset of the necessary domain substitutions for
	//     running and antecedent, the rest will be instantiated through iteration
	G2ScriptAST conditionsAST, antecedentAST, actionsAST = null;
	filterConditions = new Vector();
	Condition[][] wheneverConditionsLocal = null;
	// The antecedent block will return a boolean
	Block antecedentBlock = new Block();
	
	int ruleType = -1;
	// Step One Sort out the disparate syntaxes of the four rule types

	try {
	  compilingRuleAntecedent = true;

	  switch (parseResult.getType())
	    {
	    case WHENEVER:
	      // HERE, what does the whenever test method look like
	      //  how does it handle the "OR" of conditions
	      //    n.b. there are no AND's in the event-disjuncts (yesss!)
	      //  how does it handle uninstantiated substitution variables
	      // IDEA
	      /// 1. make an array of condition arrays for each disjunct
	      //     the chaining condition can find which set is active at runtime
	      //     the active set can be combined with the filter conditions for 
	      //     a single condition array for runAntecedents
	      //  2. Indexing the code associated with a condition set
	      //     at compile time the count of disjuncts is well known
	      //     at runtime 
	      ruleType = Rule.WHENEVER;
	      conditionsAST = child(parseResult);
	      antecedentAST = sibling(conditionsAST);
	      if (antecedentAST.toString().equals("ACTIONS"))
		{
		  actionsAST = antecedentAST;
		  antecedentAST = null;
		}
	      else
		{
		  actionsAST = sibling(antecedentAST);
		  antecedentAST = child(antecedentAST);
		}
	      wheneverConditionsLocal = compileWheneverConditions(conditionsAST);
	      if (antecedentAST != null)
		compileAntecedent(antecedentAST,antecedentBlock,false);
	      break;
	    case IF:
	    case WHEN:
	      ruleType = (parseResult.getType() == IF ? Rule.IF : Rule.WHEN);
	      antecedentAST = child(parseResult);
	      actionsAST = sibling(antecedentAST);
	      if (debug)
		System.out.println("about to compile antecedent in IF/WHEN case");
	      printSiblings(antecedentAST);
	      compileAntecedent(antecedentAST,antecedentBlock,true);
	      break;
	    case UNCONDITIONALLY:
	      ruleType = Rule.UNCONDITIONALLY;
	      antecedentBlock.add(new ExpressionStatement(new Value(true)));
	      actionsAST = child(parseResult);
	      break;
	    default:
	    }
	}
	finally 
	  {
	    compilingRuleAntecedent = false;
	  }
	compileConsequent(actionsAST);
	if (false)
	  throw new ClassException("asdfa");
	Condition[] filterConditionArray = new Condition[filterConditions.size()];
	filterConditions.copyInto(filterConditionArray);
	return new Rule(ruleType,wheneverConditionsLocal,
			filterConditionArray,currentClassInfo.getClassName());
      } catch (ClassException e)
	{
	  Trace.exception(e);
	  e.printStackTrace();
	  throw new RuntimeException("Internal Compiler Failure: "+e.getMessage());
	}
  }

  private void compileAntecedent(G2ScriptAST antecedentAST,
				 Block antecedentBlock,
				 boolean findChainingLinks)
       throws CompilerException
  {
    ruleConditions = filterConditions;
    scanForChainingLinks(antecedentAST,findChainingLinks,-1);
    if (debug)
      {
	System.out.println("After link scan...");
	printSiblings(antecedentAST);
	System.out.println("conditions found ...");
	for (int i = 0; i<filterConditions.size(); i++)
	  System.out.println("  "+filterConditions.elementAt(i));
      }
    ValueNode antecedent = ValueNode.compileExpression(antecedentAST,this);
    if (!ValueNode.isG2Boolean(this,antecedent.type))
      throw new CompilerException("antecedent is not a logical expression");
    try {
      antecedentBlock.add(new Return(castForAssignment(antecedentAST,
						       antecedent,
						       primBooleanType,
						       "rule antecedent logical value")));
      MethodRef methodRef
	= new MethodRef(currentClassInfo.getClassName(),
			"filter","()Z");
      MethodInfo methodInfo
	= new MethodInfo(new Access(RuntimeConstants.ACC_PUBLIC),
			 methodRef,
			 antecedentBlock, 
			 new String[] {},
			 new ClassRef[0]);
      currentClassInfo.add(methodInfo);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  private static final int FORMAT_FORM = 10001;
  private static final int ARRAY_REFERENCE = 10002;
  private static final int FUNCTION_CALL = 10003;

  private void scanForChainingLinks(G2ScriptAST expressionAST,
				    boolean findLinks,
				    int context)
				    
       throws CompilerException
  {
    G2ScriptAST argAST1 = child(expressionAST), argAST2;
    int tokenType = expressionAST.getType();
    switch (tokenType)
      {
      case WHOLE_STRING_LITERAL:
      case INTEGER_LITERAL:
      case FLOAT_LITERAL:
      case TRUTH_VALUE_LITERAL:
      case TIME:
	return;
      case PLUS:
      case MINUS:
      case EQUALS:
      case NOT_EQUAL:
      case TIMES:
      case GREATER:
      case LESS:
      case GREATER_EQUAL:
      case LESS_EQUAL:
      case SLASH:
      case OR:
      case AND:
	argAST2 = sibling(argAST1);
	if (argAST2 == null) // unary operation case (PLUS, MINUS only)
	  scanForChainingLinks(argAST1,findLinks,tokenType);
	else
	  {
	    scanForChainingLinks(argAST1,findLinks,tokenType);
	    scanForChainingLinks(argAST2,findLinks,tokenType);
	  }
	return;
      case NOT:
	scanForChainingLinks(argAST1,findLinks,tokenType);
	throw new CompilerException("Call cannot occur in rule antecedents");
      case CALL:
	throw new CompilerException("Call cannot occur in rule antecedents");
      case OF:
	// HERE worry about chaining link
	// need attr name, class of PropChangeCondition
	// Wednesday.
	// 1. Use souped-up demandBinding earlier, along with Conditions
	// 2. Do deep analysis of compiledDesignation in OF if (findingLinks)
	//     A of <any> make link (and binding for nested any)
	//        replace any with proper local reference
	//     B of global make link (eventually)
	//        can compileDesignation analyze global/local, sure, check callers for
	//        compatibility
	//     C (default) cannot link, nor will sub expressions.
	// 3.  Add case for RECEIVES A VALUE/ HAS EVENT in analyzer and compileExpression
	// 4.  look at a bunch of compilations and environments
	// 5.  test scanned and chained rules locally and remotely using r5.rule
	//      requires writing interpretation of REI's
	scanAttributeReferenceForChainingLinks(expressionAST,findLinks,tokenType);
	return;
      case SEQUENCE:
	// is this too generous??
	scanChildrenForChainingLinks(expressionAST,findLinks,tokenType);
	return;
      case STRUCTURE:
	// is this too generous??
	scanStructureConstructorForChainingLinks(expressionAST,findLinks,tokenType);
	return;
      case EXISTS:
      case EXIST:
      case IS:
	G2ScriptAST subjectAST = child(expressionAST);
	G2ScriptAST firstArgAST = sibling(subjectAST);
	if (firstArgAST != null && //only occurs for "if <d> exists then..."
	    firstArgAST.getType() == NOT)
	  firstArgAST = sibling(firstArgAST);
	scanForChainingLinks(argAST1,true,tokenType);
	if (firstArgAST == null &&
	    firstArgAST.getType() != OBJECT)
	  return;
	else
	  {
	    // scan the "same object as" other object
	    scanForChainingLinks(sibling(firstArgAST),findLinks,tokenType);
	    return;
	  }
      case ANY:
	Designation designation 
	  = Designation.compileDesignation(expressionAST,this,true);
	String bindingName 
	      = (designation.g2BindingName != null ?
		 designation.g2BindingName : 
		 generateBindingName(designation.placeType));
	ruleConditions.addElement(new ScannedCondition(makeJavaName(bindingName,false),
							 designation.placeType.getName()));
	demandBinding(bindingName,designation.placeType);
	replaceAnyWithBinding(expressionAST,bindingName);
	return;
      case ELEMENTS:
      case RECEIVES:
	scanForChainingLinks(argAST1,findLinks,tokenType);
	return;
      case HAS:
	scanGenericEventForChainingLinks(expressionAST,findLinks,tokenType);
	return;
      case UNRESERVED:
	String head = expressionAST.toString();
	if (head.equals("LOCAL_REFERENCE"))
	  {
	    String g2Name = child(expressionAST).toString();
	    LocalVariable local = getLocal(g2Name,false);
	    FieldRef binding;
	    if (local == null)
	      {
		if (compilingRule &&
		    (binding = getBinding(g2Name)) != null)
		  return;
		else if (compilingRule ||
			 allowGlobals())
		  {
		    if (debug)
		      System.out.println("worry about chaining link on global "+g2Name);
		    return;
		  }
		else
		  throw new CompilerException("undefined local "+g2Name);
	      }
	    else
	      return;
	  }
	else if (head.equals("FORMAT_FORM"))
	  {
	    scanChildrenForChainingLinks(expressionAST,false,FORMAT_FORM);
	    return;
	  }
	else if ("SYMBOL_LITERAL".equals(head) || "INTERVAL".equals(head))
	  return;
	else if (head.equals("ARRAY_REFERENCE"))
	  // be strict (or annoying) like G2 and make array ref's invisible to chaining
	  {
	    G2ScriptAST arrayAST = child(expressionAST);
	    G2ScriptAST indexAST = sibling(arrayAST);
	    scanForChainingLinks(arrayAST,false,ARRAY_REFERENCE);
	    scanForChainingLinks(indexAST,false,ARRAY_REFERENCE);
	    return;
	  }
	else if (head.equals("FUNCTION_CALL"))
	  {
	    // is G2 this powerful, or does it ignore sub-expr's of funcalls
	    scanChildrenForChainingLinks(expressionAST,false,FUNCTION_CALL);
	    return;
	  }
	else 
		throw new CompilerException("unhandled expression "+expressionAST);
    default:  
      }
    throw new CompilerException("unhandled expression "+expressionAST);
  }

  private void scanChildrenForChainingLinks(G2ScriptAST expressionAST,
					    boolean findLinks,
					    int context)
       throws CompilerException
  {
    G2ScriptAST argAST = child(expressionAST);
    while (argAST != null)
      {
	scanForChainingLinks(argAST,findLinks,context);
	argAST = sibling(argAST);
      }
  }

  private void scanStructureConstructorForChainingLinks(G2ScriptAST expressionAST,
							boolean findLinks,
							int context)
       throws CompilerException
  {
    G2ScriptAST argAST = child(expressionAST);
    while (argAST != null)
      {
	argAST = sibling(argAST); // skip the structure attr names
	scanForChainingLinks(argAST,findLinks,context);
	argAST = sibling(argAST);
      }
  }

  private void scanAttributeReferenceForChainingLinks(G2ScriptAST designationAST,
						      boolean findLinks,
						      int context)
       throws CompilerException
  {
    G2ScriptAST fieldNameAST = child(designationAST);
    G2ScriptAST objectOrClassAST = null;
    if (siblingCount(fieldNameAST) == 1)
      objectOrClassAST = sibling(fieldNameAST);
    else
      objectOrClassAST = sibling(sibling(fieldNameAST));
    Designation designation 
      = Designation.compileDesignation(designationAST,this,true);
    if (designation.code != Designation.FIELD_REFERENCE)
      throw new RuntimeException("Internal Compiler Failure");
    if (debug)
      System.out.println("Of binding name "+designation.g2BindingName);
    if (designation.g2BindingName != null)
      {
	demandBinding(designation.g2BindingName);
      }
    if (findLinks)
      {
	Designation root = designation.rootDesignation;
	if (root == null)
	  throw new RuntimeException("Internal Compiler Failure");   
	if (root.code == Designation.ANY_INSTANCE) 
	  {
	    String bindingName 
	      = (root.g2BindingName != null ?
		 root.g2BindingName : 
		 generateBindingName(root.placeType));
	    PropertyChangeCondition condition 
	      = ((designation.g2BindingName != null)?
		 new PropertyChangeCondition(makeJavaName(bindingName,false),
					     root.placeType.getName(),
					     designation.fieldName,
					     makeJavaName(designation.g2BindingName,false)):
		 new PropertyChangeCondition(makeJavaName(bindingName,false),
					     root.placeType.getName(),
					     designation.fieldName));
	    ruleConditions.addElement(condition);
	    demandBinding(bindingName,root.placeType);
	    replaceAnyWithBinding(objectOrClassAST,bindingName);
	  }
	// HERE allow globals soon
	else  if (debug)
	  System.out.println("No chaining link found under OF "+designation.fieldName);
      }
    scanForChainingLinks(objectOrClassAST,false,OF);
  }

  private void scanGenericEventForChainingLinks(G2ScriptAST genericEventAST,
						boolean findLinks,
						int context)
       throws CompilerException
  {
    G2ScriptAST designationAST = child(genericEventAST);
    G2ScriptAST eventNameAST = sibling(designationAST);
    G2ScriptAST eventBindingAST = sibling(eventNameAST); // may be null
    Designation designation 
      = Designation.compileDesignation(designationAST,this,true);
    if (findLinks)  // I think findLinks will always be true, but I will follow the form...
      {
	// Should
	// scanForChainingLinks(designationAST,false,OF);
	//  but, there are no interesting sub-designations yet
	if (designation.code == Designation.ANY_INSTANCE) 
	  {
	    // event firing binds event to event variable
	    // (HAS <local-reference> <event-name> <local-refernce>)
	    String eventBindingName;
	    if (eventBindingAST != null)
	      eventBindingName = child(eventBindingAST).toString();
	    else
	      {
		eventBindingName = generateBindingName(eventNameAST.toString());
		setSiblingToLocalReference(eventNameAST,eventBindingName);
	      }
	    String eventName = makeJavaName(eventNameAST.toString(),false);
	    ruleConditions.addElement(new Condition(makeJavaName(eventBindingName,false),
						    designation.placeType.getName(),
						    eventName));
	    demandBinding(eventBindingName,eventObjectType);
	    String anyBindingName 
	      = (designation.g2BindingName != null ?
		 designation.g2BindingName : 
		 generateBindingName(designation.placeType));
	    demandBinding(anyBindingName,designation.placeType);
	    replaceAnyWithBinding(designationAST,anyBindingName);
	  }
	// HERE allow globals soon
	else  if (debug)
	  System.out.println("No chaining link found under HAS AN EVENT "+designation.fieldName);
      }
  }

  private void compileWheneverConditionsOld(G2ScriptAST conditionsAST,
					    Block bindingsBlock)
       throws CompilerException, ClassException
  {
    String eventName = null;
    G2ScriptAST conditionAST = child(conditionsAST);
    Variable eventVariable = new Variable(eventVariableName,
					  "Ljava/util/EventObject;");
    MethodRef getSourceMethodRef = new MethodRef("java.util.EventObject",
						 "getSource",
						 "()Ljava/lang/Object;");
    while (conditionAST != null)
      {
	if (debug)
	  System.out.println("condition "+ conditionAST);
	G2ScriptAST designationAST = child(conditionAST);
	Designation designation 
	  = Designation.compileDesignation(designationAST,this,true);
	G2ScriptAST firstArgAST = sibling(designationAST);
	switch (conditionAST.getType())
	  {
	  case RECEIVES:
	    if (designation.code != Designation.FIELD_REFERENCE)
	      throw new CompilerException("receives a value rules can only be defined"+
					  "on attributes, not "+designation);
	    Designation root = designation.rootDesignation;
	    if (root == null)
	      throw new RuntimeException("Internal Compiler Failure");
	    if (root.code != Designation.ANY_INSTANCE)
	      throw new CompilerException("must be any <class> designation, not "+
					  designation);
	    wheneverConditions.addElement(new PropertyChangeCondition(null,
								  root.placeType.getName(),
								  designation.fieldName));
	    if (debug)
	      System.out.println("Of binding name "+designation.g2BindingName);
	    if (designation.g2BindingName != null)
	      {
		FieldRef attributeField = demandBinding(designation.g2BindingName);
		Cast propertyChangeEvent
		  = new Cast("Ljava/beans/PropertyChangeEvent;",eventVariable);
		MethodRef methodRef = new MethodRef("java.beans.PropertyChangeEvent",
						    "getNewValue",
						    "()Ljava/lang/Object;");
		MethodCall propertyValue = new MethodCall(propertyChangeEvent,
						 methodRef,
						 new Expression[0],
						 RuntimeConstants.MTH_CALL_VIRTUAL);
		OperatorCall assignment 
		  = new OperatorCall("=",
				     new Expression[]
				     { attributeField, propertyValue });
		bindingsBlock.add(new ExpressionStatement(assignment));
	      }
	    if (root.g2BindingName != null)
	      {
		FieldRef sourceField = demandBinding(root.g2BindingName);
		
		MethodCall source = new MethodCall(eventVariable,
						   getSourceMethodRef,
						   new Expression[0],
						   RuntimeConstants.MTH_CALL_VIRTUAL);
		OperatorCall assignment 
		  = new OperatorCall("=",new Expression[] { sourceField, source });
		bindingsBlock.add(new ExpressionStatement(assignment));
	      }
	    break;
	  case HAS:
	    if (designation.code != Designation.ANY_INSTANCE)
	      throw new CompilerException("Generic rules must be defined on a class, "+
					  designation+" was supplied.");
	    eventName = makeJavaName(firstArgAST.toString(),false);
	    G2ScriptAST bindingAST = sibling(firstArgAST);
	    wheneverConditions.addElement(new Condition(null,
							designation.placeType.getName(),
							eventName));
	    if (bindingAST != null)
	      {
		FieldRef bindingField = demandBinding(child(bindingAST).toString());
		OperatorCall assignment
		  = new OperatorCall("=",
				     new Expression[] 
				     { bindingField, eventVariable });
		bindingsBlock.add(new ExpressionStatement(assignment));
	      }
	    if (designation.g2BindingName != null)
	      {
		FieldRef sourceField = demandBinding(designation.g2BindingName);
		
		MethodCall source = new MethodCall(eventVariable,
						   getSourceMethodRef,
						   new Expression[0],
						   RuntimeConstants.MTH_CALL_VIRTUAL);
		OperatorCall assignment 
		  = new OperatorCall("=",new Expression[] { sourceField, source });
		bindingsBlock.add(new ExpressionStatement(assignment));
	      }
	    break;
	  default:
	  }
	conditionAST = sibling(conditionAST);
      }
  }

  private Condition[][] compileWheneverConditions(G2ScriptAST conditionsAST)
       throws CompilerException, ClassException
  {
    G2ScriptAST conditionAST = child(conditionsAST);
    int conditionCount = 0;
    Vector conditionArrays = new Vector();
    while (conditionAST != null)
      {
	if (debug)
	  System.out.println("Compiling condition "+ conditionAST);
	if (conditionCount > RuleInstance.MAX_WHENEVER_CONDITIONS)
	  throw new CompilerException("Too many whenever conditions");
	conditionArrays.addElement(compileWheneverCondition(conditionAST,conditionCount));
	conditionAST = sibling(conditionAST);
	conditionCount++;
      }
    Condition[][] result = new Condition[conditionArrays.size()][];
    conditionArrays.copyInto(result);
    return result;
  }

  private Condition[] compileWheneverCondition(G2ScriptAST conditionAST, int index)
       throws CompilerException
  {
    // HERE Sunday
    // add expression compilation and scanForChLinks support for RECEVIES and HAS
    ruleConditions = new Vector();
    scanForChainingLinks(conditionAST,true,-1);
    if (debug)
      {
	System.out.println("After whenever condition link scan...");
	printSiblings(conditionAST);
	System.out.println("conditions found ...");
	for (int i = 0; i<ruleConditions.size(); i++)
	  System.out.println("  "+ruleConditions.elementAt(i));
      }
    try {
      Block block = new Block();
      ValueNode compiledCondition = ValueNode.compileExpression(conditionAST,this);
      // I think the following test could never find an error because syntax prevents
      // this.
      if (!ValueNode.isG2Boolean(this,compiledCondition.type))
	throw new CompilerException("condition is not a logical expression"); 
      block.add(new Return(castForAssignment(conditionAST,
					     compiledCondition,
					     primBooleanType,
					     "rule condition logical value")));
      MethodRef methodRef
	= new MethodRef(currentClassInfo.getClassName(),
			RuleInstance.nameWheneverTestMethod(index),"()Z");
      MethodInfo methodInfo
	= new MethodInfo(new Access(RuntimeConstants.ACC_PUBLIC),
			 methodRef,
			 block, 
			 new String[] {},
			 new ClassRef[0]);
      currentClassInfo.add(methodInfo);
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
    Condition[] result = new Condition[ruleConditions.size()];
    ruleConditions.copyInto(result);
    return result;
  }

  String generateBindingName(Type type)
  {
    return generateBindingName(type.getName());
  }

  String generateBindingName(final String rootName)
  {
    String capitalRootName = rootName.toUpperCase();
    int index = capitalRootName.lastIndexOf('.');
    if (index == -1)
      return capitalRootName+"-BINDING-"+(bindingVariableCounter++);
    else 
      return capitalRootName.substring(index+1)+"-BINDING-"+(bindingVariableCounter++);
  }

  static void replaceAnyWithBinding(G2ScriptAST anyAST, 
				    String bindingName)
  {
    anyAST.setText("LOCAL_REFERENCE");
    anyAST.setType(UNRESERVED);
    G2ScriptAST nameAST = new G2ScriptAST();
    nameAST.setText(bindingName);
    nameAST.setType(UNRESERVED);
    nameAST.setLineNumber(anyAST.getLineNumber());
    anyAST.setFirstChild(nameAST);
  }

  static void setSiblingToLocalReference(G2ScriptAST ast, String bindingName)
  {
    G2ScriptAST outerAST = new G2ScriptAST();
    outerAST.setText("LOCAL_REFERENCE");
    outerAST.setType(UNRESERVED);
    G2ScriptAST innerAST = new G2ScriptAST();
    innerAST.setText(bindingName);
    innerAST.setType(UNRESERVED);
    outerAST.setFirstChild(innerAST);
    ast.setNextSibling(outerAST);
  }

  FieldRef getBinding(String g2Name)
  {
    try {
      String fieldName = makeJavaName(g2Name,false);
      FieldInfo fieldInfo = currentClassInfo.getField(fieldName);
      if (fieldInfo == null)
	return null;
      else
	{
	  return new FieldRef(currentClassInfo.getClassName(),
			      fieldName,
			      fieldInfo.getDescriptor());
	}
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  private FieldRef demandBinding(String g2Name)
  {
    return demandBinding(g2Name, objectType);
  }

  private FieldRef demandBinding(String g2Name, Type type)
  {
    try {
      String fieldName = makeJavaName(g2Name,false);
      FieldRef fieldRef 
	= new FieldRef(currentClassInfo.getClassName(),
		       fieldName,
		       type.makeDescriptor());
      if (currentClassInfo.getField(fieldName) == null)
	{
	  FieldInfo fieldInfo
	    = new FieldInfo(new Access(RuntimeConstants.ACC_PUBLIC),
			    fieldRef);
	  currentClassInfo.add(fieldInfo);
	  ruleBindings.addElement(fieldName);
	}
      return fieldRef;
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }    

  private void compileConsequent(G2ScriptAST actionsAST)
       throws CompilerException, ClassException
  {
    Block block = new Block();
    G2ScriptAST actionAST = child(actionsAST);
    // Don't worry about sequential/parallel consequents yet
    if (actionAST.getType() == ORDER)
      actionAST = sibling(actionAST);
    while (actionAST != null)
      {
	block.add(compileStatement(actionAST));
	actionAST = sibling(actionAST);
      }
    block.add(new Return());
    MethodRef methodRef
      = new MethodRef(currentClassInfo.getClassName(),"doConsequent","()V");
    MethodInfo methodInfo
      = new MethodInfo(new Access(RuntimeConstants.ACC_PUBLIC),
		       methodRef,
		       block,
		       new String[0],
		       new ClassRef[0]);
    currentClassInfo.add(methodInfo);
  }



  // Utilities

  Expression castForAssignment(G2ScriptAST expressionAST, ValueNode node, 
			       Type placeType, String placeString)
       throws CompilerException
  {
    try 
      {
	Expression valueExpression;
	if (placeType.isAssignableFrom(node.type))
	  valueExpression = node.emit();
	else if (!placeType.isPrimitive() &&
		 node.type.isAssignableFrom(placeType))
	  {
	    valueExpression
	      = new Cast(placeType.makeDescriptor(),node.emit());
	    valueExpression.setLineNumber(getLineNumber(expressionAST));
	  }
	else if (canPerformNumericOrLogicalAssignment(placeType,node.type))
	  valueExpression = buildNumericAssignment(expressionAST,node,placeType);
	else
	  throw new CompilerException("incompatible type "+node.type+
				      " for "+placeString);
	return valueExpression;
      }
    catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  FieldRef getOrMakeSymbolConstant(String symbolName)
  {
    // this isn't perfect
    try {
      String fieldName = "SYMCONST_"+symbolName.replace('-','_')+"_";
      FieldRef fieldRef 
	= new FieldRef(currentClassInfo.getClassName(),
		       fieldName,
		       "Lcom/gensym/util/Symbol;",
		       true);
      if (currentClassInfo.getField(fieldName) == null)
	{
	  FieldInfo fieldInfo
	    = new FieldInfo(new Access(RuntimeConstants.ACC_PUBLIC |
				       RuntimeConstants.ACC_STATIC),
			    fieldRef,
			    ValueNode.makeStaticCall("com.gensym.util.Symbol",
						     "intern",
						     "(Ljava/lang/String;)"+
						     "Lcom/gensym/util/Symbol;",
						     new Value(symbolName)));
	  currentClassInfo.add(fieldInfo);
	}
      return fieldRef;
    } catch (ClassException e)
      {
	e.printStackTrace();
	throw new RuntimeException("Internal Compiler Failure");
      }
  }


  private LocalVariable addLocal(String g2Name, Type type)
       throws CompilerException
  {
    int i,size = locals.size();
    for (i=0; i<size; i++)
      {
	LocalVariable local = (LocalVariable)locals.elementAt(i);
	if (local.g2Name.equals(g2Name))
	  throw new CompilerException("duplicate local name "+g2Name);
      }
    String javaName = makeJavaName(g2Name,false);
    // System.out.println("Makeing local w/ "+g2Name+" j "+javaName+
    // " type "+type);
    LocalVariable localVariable = new LocalVariable(g2Name,javaName,type);
    locals.addElement(localVariable);
    return localVariable;
  }

  Type getTypeForLocal(String g2Name)
       throws CompilerException
  {
    int i,size = locals.size();
    for (i=0; i<size; i++)
      {
	LocalVariable local = (LocalVariable)locals.elementAt(i);
	if (local.g2Name.equals(g2Name))
	  return ((LocalVariable)locals.elementAt(i)).type;
      }
    throw new CompilerException("undefined local "+g2Name);
  }

  LocalVariable getLocal(String g2Name)
       throws CompilerException
  {
    return getLocal(g2Name,true);
  }

  LocalVariable getLocal(String g2Name, boolean throwErrorIfNotFound)
       throws CompilerException
  {
    int i,size = locals.size();
    for (i=0; i<size; i++)
      {
	LocalVariable local = (LocalVariable)locals.elementAt(i);
	if (local.g2Name.equals(g2Name))
	  return local;
      }
    if (throwErrorIfNotFound)
      throw new CompilerException("undefined local "+g2Name);
    else
      return null;
  }
  
  String makeJavaName(String g2Name, boolean forClass)
  {
    // System.out.println("calling makeJavaName "+g2Name);
    if (classInfoFactory != null && forClass)
      {
	return classInfoFactory.getJavaNameForG2ClassName(g2Name);
      }
    else
      {
	StringBuffer buffer = new StringBuffer();
	String nameWithoutPackage = null;
	int lastIndex = g2Name.lastIndexOf('.');
	if (lastIndex != -1)
	  {
	    buffer.append(g2Name.substring(0,lastIndex+1).toLowerCase());
	    nameWithoutPackage = g2Name.substring(lastIndex+1);
	  }
	else
	  nameWithoutPackage = g2Name;
	StringTokenizer tokenizer
	  = new StringTokenizer(nameWithoutPackage.toLowerCase(),"-");
	boolean first = true;
	while (tokenizer.hasMoreTokens())
	  {
	    String token = tokenizer.nextToken();
	    char[] chars = token.toCharArray();
	    if (!first || forClass)
	      chars[0] = Character.toUpperCase(chars[0]);
	    buffer.append(new String(chars));
	    first = false;
	  }
	String result = buffer.toString();
	// System.out.println("  yielding "+result);
	return result;
      }
  }

  boolean allowGlobals()
  {
    return (classInfoFactory != null &&
	    classInfoFactory.allowGlobalNameReferences());
  }

  Variable makeThisVariable()
  {
    // should check to see if current method compilation is static
    // and throw an error if so.
    try
      {
	return new Variable(0,currentType.makeDescriptor());
      }
    catch (ClassException e)
      {
	throw new RuntimeException("Internal Compiler Failure");
      }
  }

  // Statement flag maintenance

  private void setFlags(Statement statement, BitSet flags)
  {
    statement.setExtension(flags);
  }

  private BitSet makeDefaultFlags()
  {
    return new BitSet(FLAGS_SIZE);
  }

  private boolean getFlag(Statement statement,int index)
  {
    BitSet bits = (BitSet) statement.getExtension();
    if (bits == null)
      return false;
    else
      return bits.get(index);
  }

  private BitSet demandFlags(Statement statement)
  {
    BitSet bits = (BitSet) statement.getExtension();
    if (bits == null)
      {
	bits = new BitSet(FLAGS_SIZE);
	statement.setExtension(bits);
      }
    return bits;
  }

  private void setFlag(Statement statement,int index)
  {
    BitSet bits = demandFlags(statement);
    bits.set(index);
  }
 
  private void clearFlag(Statement statement,int index)
  {
    BitSet bits = demandFlags(statement);
    bits.clear(index);
  }

  private BitSet combineSequential (Statement s1, Statement s2)
  {
    return combineSequential(demandFlags(s1),demandFlags(s2));
  }

  private BitSet combineSequential(Statement statement, BitSet bs2)
  {
    return combineSequential(demandFlags(statement),bs2);
  }
 
  private BitSet combineSequential(BitSet bs1, BitSet bs2)
  {
    BitSet result = new BitSet(FLAGS_SIZE);
    if (bs1.get(WILL_RETURN) || bs2.get(WILL_RETURN))
      result.set(WILL_RETURN);
    else if (bs1.get(MAY_RETURN) || bs2.get(MAY_RETURN))
      result.set(MAY_RETURN);
   
    if (false)
      {
	System.out.println("bs1 "+pprintFlags(bs1)+"bs2 "+pprintFlags(bs2));
	System.out.println("will bool "+(bs1.get(WILL_THROW) || bs2.get(WILL_THROW)));
	System.out.println("may bool "+(bs1.get(MAY_THROW) || bs2.get(MAY_THROW)));
      }

    if (bs1.get(WILL_THROW) || bs2.get(WILL_THROW))
      result.set(WILL_THROW);
    else if (bs1.get(MAY_THROW) || bs2.get(MAY_THROW))
      result.set(MAY_THROW);
    
    return result;
  }
  private BitSet combineAlternative (Statement s1, Statement s2)
  {
    return combineAlternative(demandFlags(s1),demandFlags(s2));
  }

  private BitSet combineAlternative(Statement statement, BitSet bs2)
  {
    return combineAlternative(demandFlags(statement),bs2);
  }
 
  private BitSet combineAlternative(BitSet bs1, BitSet bs2)
  {
    BitSet result = new BitSet(FLAGS_SIZE);

    if (bs1.get(WILL_RETURN) && bs2.get(WILL_RETURN))
      result.set(WILL_RETURN);
    else if (bs1.get(WILL_RETURN) || bs2.get(WILL_RETURN) || 
	     bs1.get(MAY_RETURN) || bs2.get(MAY_RETURN))
      result.set(MAY_RETURN);
   
    if (bs1.get(WILL_THROW) && bs2.get(WILL_THROW))
      result.set(WILL_THROW);
    else if (bs1.get(WILL_THROW) || bs2.get(WILL_THROW) ||
	     bs1.get(MAY_THROW) || bs2.get(MAY_THROW))
      result.set(MAY_THROW);
    
    return result;
  }

  private String pprintFlags(Statement s)
  {
    return pprintFlags(demandFlags(s));
  }

  private String pprintFlags(BitSet bs)
  {
	String willReturn = bs.get(WILL_RETURN) ? "WILL_RETURN " : "";
	String mayReturn = bs.get(MAY_RETURN)  ? "MAY_RETURN " : "";
	String willThrow = bs.get(WILL_THROW)  ? "WILL_THROW " : "";
	String mayThrow = bs.get(MAY_THROW)   ? "MAY_THROW " : "";
    
	return "<Flags: " + willReturn + mayReturn + willThrow + mayThrow + ">";
  }
  
  // Convenience methods

  private static int getLineNumber(G2ScriptAST ast)
  {
    return ((G2ScriptAST)ast).getLineNumber();
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
	G2ScriptAST tree = ast;
    int count = 0;
    while (tree.getNextSibling() != null)
      {
    	tree = sibling(tree);
    	count++;
      }
    return count;
  }

  // AST pretty printer (well, kinda pretty)

  static void printSiblings(final CommonAST ast)
  {
	CommonAST tree = ast;
    while (tree != null)
      {
	System.out.println();
	System.out.println("__________________________");
	pprint(ast,0,0);
	tree = (CommonAST) tree.getNextSibling();
      }

  }

  static void pprint(CommonAST ast, int level, int childCount)
  {
    AST t = ast;
   
    String head = ast.toString();

    if ( t.getFirstChild()==null )
      {
	if (childCount >= 1)
	  indent(level);
	System.out.println(" "+head);
      }
    else
      {
	t = t.getFirstChild();
	
	indent(level);
	System.out.print("("+head);
	int newLevel = level + head.length() + 1;
	int subChildCount = 0;
	while ( t!=null ) 
	  {
	    pprint((CommonAST)t, newLevel, subChildCount);
	    t = t.getNextSibling();
	    subChildCount++;
	  }
	System.out.print(")");
      }
  }

  private static void indent(int n)
  {
    System.out.println("");
    for (int i = 0; i<n ; i++) System.out.print(" ");
  }

}
