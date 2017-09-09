package com.gensym.g2scriptruntime;

/**
 * The G2Script runtime ClassManager is responsible for accessing external Classes required by the
 * Kernel.
 */
public interface ClassManager 
{
  
  public Class getVersionedImplementationClass(String interfaceName,
						String defaultImplementationName,
						Object callingObject)
       throws ClassNotFoundException;


}
