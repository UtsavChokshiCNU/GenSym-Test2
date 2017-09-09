package com.gensym.classtools;

import java.util.Vector;

public class InterfaceInfo extends Info
{ 
  public InterfaceInfo(int nameIndex, ConstantPool pool) 
       throws ClassException 
  {		
    super(nameIndex,pool);
  }
  
  public InterfaceInfo(String interfaceName) throws ClassException {
    normalizedConstants = new ConstantPool();
    nameIndex 
      = normalizedConstants.add(new ClassConstant(normalizedConstants,interfaceName),
				true);
    normalized = true;
  }
  
  
  /**
   * @exception ClassException
   *        Failure during normalization of this Attribute
   */
  void normalize() 
       throws ClassException 
  {
    int index = 0;
    normalizedConstants = new ConstantPool(localConstants.getLength());
    super.normalize(localConstants, normalizedConstants,index);
  }
  
  /**
   * @exception ClassException
   *        Failure during localization of this Attribute
   */
  @Override
  void localize(ConstantPool pool) 
       throws ClassException 
  {
    super.localize(pool, normalizedConstants);
  }
  
  @Override
  public String toString() {
    return "<InterfaceInfo, name=" + name + ">";
  }
  
  public static void toStdout(Vector interfaces) {
    System.out.println("Interfaces");
    System.out.println("----------");
		Info.toStdout(interfaces);
  }
  
}

