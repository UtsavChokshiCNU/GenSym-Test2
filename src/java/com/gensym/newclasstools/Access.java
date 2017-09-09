package com.gensym.newclasstools;

import java.io.*;

public class Access implements RuntimeConstants
{ 	
  protected int accessFlags;
  
  public Access(int flags) {
    accessFlags = flags;
  }
  
  void emit(DataOutputStream out) 
    throws IOException {
      out.writeShort(accessFlags);
  }
  
  public boolean isPublic() {
   return ((accessFlags & ACC_PUBLIC) != 0);
 }
  
  public boolean isPrivate() {
   return ((accessFlags & ACC_PRIVATE) != 0);
 }
  
  public boolean isProtected() {
    return ((accessFlags & ACC_PROTECTED) != 0);
  }
  
  public boolean isStatic() {
    return ((accessFlags & ACC_STATIC) != 0);
  }
  
  public boolean isFinal() {
    return ((accessFlags & ACC_FINAL) != 0);
  }
  
  public boolean isSynchronized() {
   return ((accessFlags & ACC_SYNCHRONIZED) != 0);
  }
  
 public boolean isVolatile() {
   return ((accessFlags & ACC_VOLATILE) != 0);
 }
  
  public boolean isTransient() {
   return ((accessFlags & ACC_TRANSIENT) != 0);
 }
  
  public boolean isNative() {
   return ((accessFlags & ACC_NATIVE) != 0);
 }
  
  public boolean isInterface() {
  return ((accessFlags & ACC_INTERFACE) != 0);
 }
  
  public boolean isAbstract() {
    return ((accessFlags & ACC_ABSTRACT) != 0);
  }
  
  public boolean isSuper() {
    return ((accessFlags & ACC_SUPER) != 0);
  }

  public void toStdout() {
    System.out.println("Access Restrictions: " + toString());
  }  

  public int getModifiers()
  {
    return accessFlags;
  }

  @Override
  public String toString() {
	 StringBuffer buf = new StringBuffer();
    
    if (isPublic())	   stringHelper(buf,"public");
    else if(isPrivate())   stringHelper(buf,"private");
    else if(isProtected()) stringHelper(buf,"protected");
    
    if (isStatic())	   stringHelper(buf,"static");
    if (isFinal())	   stringHelper(buf,"final");
    if(isSynchronized()) {
      if(this instanceof ClassAccess)
	stringHelper(buf,"super");						
      else
	stringHelper(buf,"synchronized");
    }
    if (isVolatile())	   stringHelper(buf,"volatile");
    if (isTransient())	   stringHelper(buf,"transient");
    if (isNative())	   stringHelper(buf,"native");
    if (isAbstract())	   stringHelper(buf,"abstract");
    if (isInterface())	   stringHelper(buf,"interface");
    
    return buf.toString();
  }

  private void stringHelper(StringBuffer buf,String str) {
    if(buf.length() > 0)
      buf.append(" " + str);
    else buf.append(str);
  }
}
