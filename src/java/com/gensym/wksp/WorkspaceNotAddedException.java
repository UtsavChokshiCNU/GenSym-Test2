package com.gensym.wksp;

import com.gensym.classes.KbWorkspace;

public class WorkspaceNotAddedException extends RuntimeException
{
  private KbWorkspace wksp;
  public WorkspaceNotAddedException(KbWorkspace wksp)
  {
    this.wksp = wksp;
  }

  public KbWorkspace getWorkspace()
  {
    return wksp;
  }
  
}
