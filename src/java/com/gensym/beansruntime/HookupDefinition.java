package com.gensym.beansruntime;

/**  This class is used to fold the definiton for a hookup
 *    (the name of the hookup and the bytes which define it)
 */
public class HookupDefinition implements java.io.Serializable
{
  static final long serialVersionUID = 1244668316192623450L;
  public String name = null;
  public byte[] bytes = null;
  
  public HookupDefinition (String name, byte[] bytes)
  {
    this.name = name;
    this.bytes = bytes;
  }
  
  @Override
  public String toString () {
    return super.toString () + "(" + name + " defined by " + bytes.length + " bytes)";
  }
}
