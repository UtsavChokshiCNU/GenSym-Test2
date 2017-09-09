package com.gensym.newclasstools;
import java.io.*;
import java.util.Vector;

/**
 *  The Info class embodies the behavior and data that MethodInfo
 * FieldInfo, Attribute and InterfaceInfo all share. This is an abstract
 * class because the only use of this class is in the subclasses that
 * share this functionality. 
 */
public abstract class Info {
  protected UTF8Constant nameConstant;

  UTF8Constant getConstant() {
    return nameConstant;
  }

  public String getName()
  {
    return nameConstant.getString();
  }

  public void setName(String name)
  {
    nameConstant = new UTF8Constant(name);
  }
  
  private static final boolean trace = false;
  
  protected Info () {
  }
  
  Info(String name) 
  {
    nameConstant = new UTF8Constant(name);
  }

  Info(UTF8Constant nameConstant) 
  {
    this.nameConstant = nameConstant;
  }
  
  
  void emit(DataOutputStream out, ConstantPool cp)
       throws IOException, ClassException
  {
    if (trace)
      System.out.println(">>>> emitting name " + getName());
    out.writeShort(cp.getIndex(nameConstant));
  }
  
  @Override
  public String toString() {
    return "<Info, name=" + getName() + ">";
  }
  
  public static void toStdout(Vector infos, String prefix) {
    if (infos != null) 
      for (int i = 0; i < infos.size(); i++)  {
	if (infos.elementAt(i) != null) 
	  ((Info) infos.elementAt(i)).toStdout(prefix);
      }
  }
  
  public static void toStdout(Info[] infos, String prefix) {
    Info inf;
    if (infos != null) 
      for (int i = 0; i < infos.length; i++)  {
	inf = infos[i];
	if (inf != null) 
	  inf.toStdout(prefix);
      }
  }
  
  public static void toStdout(Vector infos) {
    Info.toStdout(infos,"");
  }
  
  public void toStdout(String prefix) {
    System.out.println(prefix + toString());
  }
  
  static void emit(Vector infos, DataOutputStream out, ConstantPool cp)
       throws IOException, ClassException
  {		
    if(infos != null) {
      out.writeShort(infos.size());
      for (int i=0; i < infos.size();i++) {
	if (trace)
	  System.out.println("Emitting Info #" + i + ": " + infos.elementAt(i));
	((Info) infos.elementAt(i)).emit(out, cp);
      }
    }
    else {
      if (trace)
	System.out.println("Writing out an empty list");		 
      out.writeShort(0);
    }
  }
  
  public boolean equals(Info info) {
    return nameConstant.equals(info.nameConstant);
  }
  
}
