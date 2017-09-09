package com.gensym.uitools.inspect;

public class InspectSessionException extends Exception {
  private Exception nestedException;
  private InspectSession session;
  
  public InspectSessionException(InspectSession session,
				 Exception nestedException)
  {
    this.session = session;
    this.nestedException = nestedException;
  }

  public InspectSession getSource() {
    return session;
  }

  @Override
  public String getMessage() {
    if (nestedException != null)
      return nestedException.getMessage();
    else
      return super.getMessage();
  }
    
}
