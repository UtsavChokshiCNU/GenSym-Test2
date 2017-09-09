package com.gensym.types;

/** See Documentation for G2Type 
 *
 */
public abstract class CompoundType extends G2Type
{
  /*
   * Allow deserialization
   */
  /* not required for abstract class? */
  static final long serialVersionUID = 7184300658841769386L;

  @Override
  public boolean includes(Object o)
  {
    return false;
  }
}
