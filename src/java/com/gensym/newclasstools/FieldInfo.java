package com.gensym.newclasstools;

import java.io.*;
import java.util.Vector;

public class FieldInfo extends Info implements RuntimeConstants
{
  //*************** Properties ************
  private Access access;
  
  public Access getAccess()
  {
    return access;
  } 

  Vector attributes; // package public only until parsing of attributes is moved
  // into this class
  public Attribute[] getAttributes()
  {
    if (attributes == null)
      return new Attribute[] { };
    Attribute[] attributeArray = new Attribute[attributes.size()];
    attributes.copyInto(attributeArray);
    return attributeArray;       
  }

  private Type type;
  public Type getType() 
  {
    return type;
  }

  private Expression initialValue;
  public Expression getInitialValue()
  {
    return initialValue;
  }

  Statement getFieldInitializer(ClassInfo containingClass) throws ClassException
{
  if (initialValue == null)
    return null;
  else
    return new ExpressionStatement(new OperatorCall("=", new Expression[]{new FieldRef(containingClass.getClassType(), getName(), type, isStatic()),
						    initialValue}));
  }

  public boolean isStatic() {
    return access.isStatic();
  }

  private static final boolean trace = false;

  public FieldInfo(Access accessFlags, String fieldName, Type fieldType, Expression initialValue) 
       throws ClassException
  {
    super(fieldName);
    if (initialValue != null) {
      if (!fieldType.potentialAssignmentConversion(initialValue))
	throw new ClassException("Invalid Expression Type for field initialization, Field Type = " +
				 fieldType + 
				 " ExpressionType = "+ 
				 initialValue.getExpressionType());
      // Need to check if the expression contains any potential Exception throwing
      // in which case it will not be valid for field initialization		
      initialValue = new Cast(fieldType, initialValue, false);
      // NB. Cast is a no-op when unnecessary
      this.initialValue = initialValue;
    }
    this.type = fieldType;
    this.access = accessFlags;
  }

  public FieldInfo(Access accessFlags, String fieldName, Type fieldType, Expression initialValue, boolean staticp) 
       throws ClassException
  {
    this(new Access(accessFlags.getModifiers() | (staticp? ACC_STATIC : 0)),
	 fieldName, fieldType, initialValue);
  }

  public FieldInfo(Access accessFlags, String fieldName, Type fieldType, boolean staticp) 
       throws ClassException
  {
    this(new Access(accessFlags.getModifiers() | (staticp? ACC_STATIC : 0)),
	 fieldName, fieldType, null);
  }

  public FieldInfo(Access accessFlags, String fieldName, Type fieldType) 
       throws ClassException
  {
    this(accessFlags, fieldName, fieldType, null);
  }

  public void setInitialValue(Expression initialValue) throws ClassException {
    if (!type.potentialAssignmentConversion(initialValue))
      throw new ClassException("Invalid Expression Type for field initialization, Field Type = " +
			       type + 
			       " ExpressionType = "+ 
			       initialValue.getExpressionType());
    this.initialValue = initialValue;
  }

  public void setAccess(Access access) {
    this.access = access;
      }

  public void setType(Type type) throws ClassException {
    if (initialValue != null && !type.potentialAssignmentConversion(initialValue))
      throw new ClassException("Invalid Expression Type for field initialization, Field Type = " +
			       type + 
			       " ExpressionType = "+ 
			       initialValue.getExpressionType());
    this.type = type;
  }

  public void setStaticp(boolean staticp) {
    this.access = new Access(access.getModifiers() | (staticp? ACC_STATIC : 0));
  }

  @Override
  void emit(DataOutputStream out, ConstantPool cp) 
       throws IOException, ClassException
  {
    access.emit(out);	
    out.writeShort(cp.getIndex(nameConstant));
    out.writeShort(cp.getIndex(new UTF8Constant(type.descriptor())));
    Attribute.emit(attributes, out, cp);
  }

  @Override
  public String toString() {
    return       "<FieldInfo, name=" +  getName() +
      ", type=" + type +
      ", access=" + access.toString() + ">";
  }
						
  static void emit(Vector fields,DataOutputStream out, ConstantPool cp) 
       throws IOException, ClassException
  {
    if(fields != null) {
      Info.emit(fields, out, cp);
    }
    else {
      out.writeShort(0);
    }
  }
  
  public static void toStdout(Vector fields) {
    System.out.println("Fields");
    System.out.println("------");
    Info.toStdout(fields,"");
  }

  
}
