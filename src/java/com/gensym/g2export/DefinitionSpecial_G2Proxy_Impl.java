package com.gensym.g2export;

import com.gensym.fida.ClassReference;

public class DefinitionSpecial_G2Proxy_Impl extends G2__BaseImpl implements ClassReference
{

  private String exportedClassName = null;

  public void setExportedClassName(String exportedClassName)
  {
    this.exportedClassName = exportedClassName;
  }

  /**
   * Get the Class name for this class.
   * @return The non-null Class name for the refernced class.
   */
  public String getClassName()
  {
    return exportedClassName;
  }

  /**
   * The codebase to locate the class if necessary.
   * @return the possibly null codebase to locate the class.
   */
  public String getCodebase()
  {
    return null;
  }

}
