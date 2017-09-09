package com.gensym.classtools;
import java.io.*;
import java.util.Vector;

/**
 *  The Info class embodies the behavior and data that MethodInfo
 * FieldInfo, Attribute and InterfaceInfo all share. This is an abstract
 * class because the only use of this class is in the subclasses that
 * share this functionality. 
 */
public abstract class Info {
  protected String name;
  public String getName()
  {
    return name;
  }
  
  protected int nameIndex;  
  public int getNameIndex()
  {
    return nameIndex;
  }
  
  ConstantPool localConstants;
  ConstantPool normalizedConstants;
  
  public ConstantPool getConstantPool() {
    if (normalized)
      return normalizedConstants;
    else
      return localConstants;
  }

  boolean normalized = false;
  
  private static final boolean trace = false;
  
  Info(DataInputStream in,ConstantPool constantPool) { }
  
  protected Info () {
  }
  
  protected Info(ConstantPool pool) {
    localConstants = pool;
  }
  
  Info(int nameIndex, ConstantPool pool) 
       throws ClassException
  {
    localConstants = pool;
    name = pool.getPool(nameIndex).getName();
    this.nameIndex = nameIndex;
  }
  
  
  void emit(DataOutputStream out)
       throws IOException
  {
    if (trace)
      System.out.println(">>>> emitting name " + nameIndex);
    out.writeShort(nameIndex);
  }
  
  int normalize(final ConstantPool locals, final ConstantPool normals, final int index) 
       throws ClassException
  {
	int localIndex = index;
    Constant namec = locals.getPool(nameIndex);
    localIndex = namec.normalize(locals,normals, localIndex);
    nameIndex = normals.member(normals,namec);
    name = normals.getPool(nameIndex).getName();
    normalized = true;
    return localIndex;
  }
  
  void localize(ConstantPool locals, ConstantPool normals)
       throws ClassException
  {
    if (localConstants == null)
      localConstants = locals;
    Constant namec = normals.getPool(nameIndex);
    nameIndex = locals.add(namec,false);
    name = namec.getName();
    normalized = false;
  }
  
  void localize(ConstantPool locals)
       throws ClassException
  {
  }
  
  @Override
  
  public String toString() {
    return "<Info, name=" + name + ">";
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
  
  static void emit(Vector infos,DataOutputStream out)
       throws IOException
  {		
    if(infos != null) {
      out.writeShort(infos.size());
      for (int i=0; i < infos.size();i++) {
	((Info) infos.elementAt(i)).emit(out);
      }
    }
    else {
      if (trace)
	System.out.println("Writing out an empty list");		 
      out.writeShort(0);
    }
  }
  
  @Override
  
  public boolean equals(Object obj) {
	if(obj == null || !Info.class.equals(obj.getClass())){
		return false;
	}
	  
	Info info = (Info) obj;
    return 
      (normalized ? 
       normalizedConstants.getPool(nameIndex) : 
       localConstants.getPool(nameIndex)).
      equals ((info.normalized ? 
	       info.normalizedConstants.getPool(nameIndex) :
	       info.localConstants.getPool(nameIndex)));
  }
  
  @Override
  
  public int hashCode() {
  	final int prime = 31;
  	int result = 1;
  	result = prime * result + ((this.normalizedConstants == null) ? 0 : this.normalizedConstants.hashCode());
  	result = prime * result + ((this.localConstants == null) ? 0 : this.localConstants.hashCode());
  	return result;

  }
  
}
