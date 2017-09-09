package com.gensym.g2script;

import com.gensym.classtools.*;

/** 
  This file is support for compiling actions such as
  conclude and delete, both of which modify their args. Could
  also have been called l-value or place-reference.
 */

public class Designation extends TreeWalker
{
  ValueNode rootNode;
  Designation rootDesignation; // filled only for rule antecedents
  static final int FIELD_REFERENCE = 1;
  static final int STATIC_FIELD_REFERENCE = 2;
  static final int ARRAY_REFERENCE = 3;
  static final int VARIABLE_REFERENCE = 4;
  static final int ANY_INSTANCE = 5;
  int code;
  
  /** for fields, if null, implies name not known at comp time.
   *  Will compile to runtime lookup usually.
   */
  Type placeType; 
  ValueNode indexExpression; // if ARRAY_REFERENCE
  String fieldName; 
  String localName;
  boolean fieldFoundAtCompileTime = true;
  Type staticClass;
  String g2AttributeName;
  String propertyGetterName;
  String propertySetterName;
  boolean isImplicitProperty;
  String g2BindingName = null;
  boolean isGlobal = false;  // iff cannot proven to be local and globals allowed
  
  Designation(ValueNode rootNode, int designationCode,
	      Type placeType)
  {
    this.rootNode = rootNode;
    this.code = designationCode;
    this.placeType = placeType;
  }

  // convenience constructor for fields
  Designation(ValueNode rootNode, int designationCode,
	      Type placeType, String fieldName, 
	      String g2AttributeName,
	      boolean fieldFoundAtCompileTime)
  {
    this.rootNode = rootNode;
    this.code = designationCode;
    this.placeType = placeType;
    this.fieldName = fieldName;
    this.g2AttributeName = g2AttributeName;
    this.fieldFoundAtCompileTime = fieldFoundAtCompileTime;
  }

  static Designation compileDesignation(G2ScriptAST designationAST,
					Compiler c,
					boolean isRuleAntecedent)
       throws CompilerException
  {
    String head = designationAST.toString();
    if (head.equals("LOCAL_REFERENCE"))
      {
	ValueNode node = ValueNode.compileExpression(designationAST,c);
	Designation result = new Designation(node,VARIABLE_REFERENCE,node.type);
	String g2Name = child(designationAST).toString();
	LocalVariable local = c.getLocal(g2Name,false);
	FieldRef binding;
	if (local == null)
	  {
	    if (c.compilingRule && (binding = c.getBinding(g2Name)) != null){
	   
	    } else if (c.compilingRule || c.allowGlobals())
	      result.isGlobal = true;
	    else
	      throw new CompilerException("Globals not supported "+g2Name);
	  }
	result.localName = g2Name;
	return result;
      }
    else if (head.equals("ARRAY_REFERENCE"))
      {
	G2ScriptAST arrayAST = child(designationAST);
	G2ScriptAST indexAST = sibling(arrayAST);
	ValueNode node = ValueNode.compileExpression(arrayAST,c);
	// place type is unknown because either its a sequence or any 
	// array without any specific compile-time type.
	Designation result = new Designation(node,ARRAY_REFERENCE,
					     c.objectType); 
	result.indexExpression = ValueNode.compileExpression(indexAST,c);
	return result;
      }
    else if (head.equals("OF"))
      {
	ClassInfoFactory factory = c.classInfoFactory;
	boolean fieldFoundAtCompileTime = true;
	G2ScriptAST fieldNameAST = child(designationAST);
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
	String g2AttributeName = fieldNameAST.toString();
	String fieldName = c.makeJavaName(g2AttributeName,false);
	if (objectOrClassAST.toString().equals("CLASS"))
	  {
	    Type classType = c.compileTypeDeclaration(objectOrClassAST);
	    Type fieldType = classType.getFieldType(fieldName,false,true);
	    if (fieldType == null)
	      { 
		fieldType = c.objectType;
		fieldFoundAtCompileTime = false;
	      }
	    Designation result = new Designation(null,STATIC_FIELD_REFERENCE,
						 fieldType);
	    result.fieldName = fieldName;
	    result.fieldFoundAtCompileTime = fieldFoundAtCompileTime;
	    result.staticClass = classType;
	    return result;
	  }
	else
	  {
	    ValueNode node = null;
	    Designation rootDesignation = null;
	    Type rootType = null;
	    if (isRuleAntecedent)
	      {
		rootDesignation = compileDesignation(objectOrClassAST,c,true);
		rootType = rootDesignation.placeType;
	      }
	    else
	      {
		node = ValueNode.compileExpression(objectOrClassAST,c);
		rootType = node.type;
	      }
	    Type fieldType = rootType.getFieldType(fieldName,false,false);
	    if (Compiler.debug)
	      System.out.println("*** fieldName "+fieldName+
				 " class "+rootType+
				 " type "+fieldType);
	    Designation result;

	    if (fieldType == null)
	      { 
		if (factory != null &&
		    rootType.isInterface() &&
		    factory.interfaceHasImplicitProperties(rootType.getName()))
		  {
		    String propertyGetterName 
		      = factory.getImplicitPropertyGetter(rootType.getName(),
							  g2AttributeName);
		    String propertySetterName 
		      = factory.getImplicitPropertySetter(rootType.getName(),
							  g2AttributeName);
		    Type propertyType
		      = rootType.getMethodReturnType(propertyGetterName,false);
		    if (propertyType == null)
		      result = new Designation(node,FIELD_REFERENCE,c.objectType,
					       fieldName,g2AttributeName,false);
		    {
		      result
			= new Designation(node,FIELD_REFERENCE,propertyType,
					  fieldName,g2AttributeName,true);
		      result.isImplicitProperty = true;
		      result.propertyGetterName = propertyGetterName;
		      result.propertySetterName = propertySetterName;
		      return result;
		    }
		  }
		else
		  result = new Designation(node,FIELD_REFERENCE,c.objectType,
					   fieldName,g2AttributeName,false);
	      }
	    else
	      result = new Designation(node,FIELD_REFERENCE,fieldType,
				     fieldName,g2AttributeName,true);
	    result.rootDesignation = rootDesignation;
	    if (localNameAST != null)
	      result.g2BindingName = child(localNameAST).toString();
	    return result;
	  }
      }
    else if (head.equals("ANY"))
      {
	if (!isRuleAntecedent)
	  throw new CompilerException("ANY is illegal in this context");
	G2ScriptAST typeAST = child(designationAST);
	Type type = c.compileTypeDeclaration(typeAST);
	Designation result = new Designation(null,ANY_INSTANCE,type);
	if (sibling(typeAST) != null)
	  result.g2BindingName = child(sibling(typeAST)).toString();
	return result;
      }
    else if (head.equals("CONNECTED"))
      throw new CompilerException("CONNECTED Designations are not yet implemented");
    else if (head.equals("UPON"))
      throw new CompilerException("UPON Designations are not yet implemented");
    else 
      return null; // won't happen, except if internal error
  }

  @Override
  public String toString()
  {
    switch (code)
      {
      case FIELD_REFERENCE:
	return "the "+g2AttributeName+" of "+rootNode.type;
      case STATIC_FIELD_REFERENCE:
	return "the "+g2AttributeName+" of the class-fields of "+rootNode.type;
      case ARRAY_REFERENCE:
	return "an element of "+rootNode.type;
      case VARIABLE_REFERENCE:
	return localName;
      default:
	return "<unknown place>";
      }
  }
}
