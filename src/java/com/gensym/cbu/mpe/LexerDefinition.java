package com.gensym.cbu.mpe;

import java.beans.*;
import java.rmi.RemoteException;
import com.gensym.denali.model.ServerImpl;
import com.gensym.denali.model.GraphElement;
import com.gensym.denali.model.Node;

public class LexerDefinition implements java.io.Serializable
{
  private PropertyChangeSupport support;
  // 703 266 5600
  // wmorris 218
  // gms     220
  // th      232
  // KB cell phone 703 626 1325
  // th cell 214 676 2837
  // Houston office 713 623 8000
  public LexerDefinition()
  {
    support = new PropertyChangeSupport(this);
  }

  public PropertyChangeSupport getSupport()
  {
    return support;
  }

  public void setSupport(PropertyChangeSupport support)
  {
    this.support = support;
  }

  public void addPropertyChangeListener(PropertyChangeListener listener)
  {
    support.addPropertyChangeListener(listener);
  }

  public void removePropertyChangeListener(PropertyChangeListener listener)
  {
    support.removePropertyChangeListener(listener);
  }

  public DFADefinition getDefinition()
       throws RemoteException
  {
    GraphElement[] nodes = ServerImpl.getGraphElementsContaining(this);
    if (nodes.length == 1 &&
	nodes[0] instanceof Node)
      {
	Node node = (Node)nodes[0];
	DefinitionSchematicImpl definitionSchematic 
	  = (DefinitionSchematicImpl)node.getSubContainer("details");
	return definitionSchematic.definition;
      }
    else
      throw new IllegalStateException("lexer definition should be in one and only one node");
  }
  
}

