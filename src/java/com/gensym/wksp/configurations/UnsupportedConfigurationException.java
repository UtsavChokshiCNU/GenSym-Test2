package com.gensym.wksp.configurations;
import com.gensym.util.Structure;

public class UnsupportedConfigurationException extends Exception
{
  private Structure statement;
  public UnsupportedConfigurationException(String message) {
    super(message);
  }
  
  public UnsupportedConfigurationException(Structure statement,
					   String message) {
    super(message);
    this.statement = statement;
  }

  public Structure getConfigurationStatement()
  {
    return statement;
  }
  
}
