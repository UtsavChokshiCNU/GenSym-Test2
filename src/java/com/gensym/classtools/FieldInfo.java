package com.gensym.classtools;

import java.io.*;
import java.util.Vector;

public class FieldInfo extends Info 
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

  private String declaringClassName;
  public String getClassName() 
  {
    return declaringClassName;
  }
  
  private String typeName;
  public String getDescriptor() 
  {
    return typeName;
  }

  private int typeIndex;
  public int getTypeIndex()
  {
    return typeIndex;
  }
     
  private FieldRefConstant fieldRefConstant;

  
  private Expression initialValue;
  public Expression getInitialValue()
  {
    return initialValue;
  }

  private static final boolean trace = false;

  public FieldInfo(final Access accessFlags, final FieldRef fieldRef, final Expression initialValue) 
       throws ClassException
  {
	Expression initValue = initialValue;  
    if ( (fieldRef.isStaticRef()) &&
	 (! accessFlags.isStatic()))
      throw new ClassException("ACC_STATIC is required to create static fieldInfo");
    if (! fieldRef.getExpressionType().potentialAssignmentConversion(initValue))
      throw new ClassException("Invalid Expression Type for field initialization, Field Type = " +
			       fieldRef.getExpressionType() + 
			       " ExpressionType = "+ 
			       initValue.getExpressionType());
    // Need to check if the expression contains any potential Exception throwing
    // in which case it will not be valid for field initialization		
    initA(accessFlags,fieldRef);
    initValue = new Cast(fieldRef.getExpressionType(),initValue, false);
    // NB. Cast is a no-op when unnecessary
    initValue.generateConstants(normalizedConstants);
    this.initialValue = new OperatorCall("=",new Expression[] {fieldRef, initValue});
    //new Set(fieldRef,initialValue);	  
  }


  public FieldInfo(Access accessFlags,FieldRef fieldRef) 
       throws ClassException
  {
    initA(accessFlags,fieldRef);
  }
  

  private void initA(Access accessFlags, FieldRef fieldRef) 
       throws ClassException
  {
    access = accessFlags;
    // Consider only doing this when added to a class
    fieldRef.generateConstants(normalizedConstants = new ConstantPool());
    fieldRefConstant = fieldRef.constant;
    typeName = fieldRef.getExpressionType().getReturnTypeString();
    name = fieldRef.getFieldName();
    normalized = true;
  }


  protected FieldInfo(int accessFlags, ConstantPool constantPool,
		      int nameIndex, int typeIndex)
       throws ClassException
  {
    super(nameIndex,constantPool);
    access = new Access(accessFlags);    
    Constant typeConstant = constantPool.getPool(typeIndex);
    typeName = typeConstant.getUTF8String();
    this.typeIndex = typeIndex;
    if (trace)
      System.out.println("  just made field name="+name+" type="+typeName);
  }

  @Override
  void emit(DataOutputStream out) 
       throws IOException
  {
    access.emit(out);	
    if (fieldRefConstant == null) {
      super.emit(out);
      out.writeShort(typeIndex);
    }
    else {
      if (trace)
	System.out.println("Emitting field info from constant" + fieldRefConstant);
      fieldRefConstant.emitAsFieldInfo(out);
    }

    Attribute.emit(attributes,out);
  }

  /** The normalize() method changes all references to constants 
   * to references to constants in the
   * normalizedConstantpool. The normalizeConstantpool will have all the
   * constants necessary for this fieldInfo.
   * 
   * @exception ClassException
   *     Failure in normalization of this FieldInfo
   */	
  void normalize()
       throws ClassException
  {
	
    // Because normalize(3) will fill at the current index and then increment
    int index = 1;
	
    // The normalizedConstants must be smaller than the local ones,
    // so allocate  the maximum amount of space that could be needed
    normalizedConstants = new ConstantPool(localConstants.getLength());

    if (fieldRefConstant == null)
      {	
	// Normalize the name index by calling the super method
	index = normalize(localConstants, normalizedConstants, index);

	// Normalize the descriptor index
	normalizedConstants.add(localConstants.getPool(typeIndex),false);

	typeIndex = index;
	index++;
      }
    else 
      {
	fieldRefConstant = (FieldRefConstant) 
	  normalizedConstants.getPool(fieldRefConstant.normalize(fieldRefConstant.constantPool,
								 normalizedConstants, index));
      }

    // Iterate over each attribute, calling normalize(ConstantPool,
    // ConstantPool,index)
    // each attribute will then complete building up the normalizedConstants
    // array

    for (int i =0; i < attributes.size(); i++) {
      if (trace) {
	System.out.println("Starting normalizing: " + 
			   ((Attribute) attributes.elementAt(i)).name);
	System.out.flush();
      }
      index = ((Attribute) attributes.elementAt(i)).normalize(localConstants,
							      normalizedConstants,index);
    }
	
    // Set state of fieldInfo
    normalized = true;
  }

  @Override
  void localize(ConstantPool pool) throws ClassException{
    if (fieldRefConstant == null) {
      super.localize(pool, normalizedConstants);
		
      Constant typeref = normalizedConstants.getPool(typeIndex);
			
      int localindex = pool.member(typeref);
      if(localindex == -1) 
	throw new ClassMergeException();
      typeIndex = localindex;
    }
    else {
      localConstants = pool;
      fieldRefConstant = (FieldRefConstant) 
	pool.getPool(fieldRefConstant.localize(fieldRefConstant.constantPool,
					       pool));
      normalized = false;

    }
  }

  @Override
  public String toString() {
    return       "<FieldInfo, name=" +  name +
      ", declaring class=" + declaringClassName +
      ", type=" + typeName +
      ", access=" + access.toString() + ">";
  }
						
  static void emit(Vector fields,DataOutputStream out) 
       throws IOException
  {
    if(fields != null) {
      Info.emit(fields,out);
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
