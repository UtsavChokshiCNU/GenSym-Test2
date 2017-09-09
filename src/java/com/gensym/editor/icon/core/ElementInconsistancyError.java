package com.gensym.editor.icon.core;

/**
 * @author Paul B. Konigsberg
 */

public class ElementInconsistancyError extends Exception
{
  public static final String twoLayerError
  = "Element can not be added to two different layers";
  public static final String sameLayerError
  = "Element can not be added twice to the same layer";
  public static final String nonExistantElementError
  = "Element does not exist";
  public ElementInconsistancyError(String message)
  {
    super(message);
  }
  
}
