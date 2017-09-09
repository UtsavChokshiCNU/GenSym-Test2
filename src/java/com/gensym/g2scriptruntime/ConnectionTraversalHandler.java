package com.gensym.g2scriptruntime;

public interface ConnectionTraversalHandler
{
  public Object getUniqueConnectedObject(Object root,
					 String className,
					 String portName);

  public Object getUniqueObjectUponWorkspace(Object workspace,
					     String subObjectClassName);
}
