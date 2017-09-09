package com.gensym.g2export;

import com.gensym.util.Sequence;
import com.gensym.fida.support.g2scriptsupport.VisualEntity;
import com.gensym.denali.model.AbstractNode;

public class EntitySpecialImpl extends G2__BaseImpl implements VisualEntity
{
  /** Workspace and Connection support TBD

  Sequence inputConnections;
  Sequence outputConnections;

  public Sequence getInputConnections()
  {
    if (inputConnections == null) 
      inputConnections = new Sequence();
    return (Sequence)inputConnections.clone();
  }

  public Sequence getOutputConnections()
  {
    if (outputConnections == null)
      outputConnections = new Sequence();
    return (Sequence)outputConnections.clone();
  }

  public void addInputConnection(Connection connection)
  {
    if (inputConnections == null) 
      inputConnections = new Sequence();
    inputConnections.addElement(connection);
  }

  public void addOutputConnection(Connection connection) 
  {
    if (outputConnections == null)
      outputConnections = new Sequence();
    outputConnections.addElement(connection);
  }

  **/

  KbWorkspace subWorkspace;
  Item parent = null;
  transient java.lang.Object absNode;

  public void _setAbstractNode(java.lang.Object node)
  {
    absNode = node;
  }

  public java.lang.Object _getAbstractNode()
  {
    return absNode;
  }

  public AbstractNode getAbstractNode()
  {
    return (AbstractNode)absNode;
  }

  public KbWorkspace getSubworkspace() 
  {
    return subWorkspace;
  }
  
  public void setSubworkspace(KbWorkspace workspace)
  {
    subWorkspace = workspace;
  }

  public Item getParent()
  {
    return parent;
  }
 
  public void setParent(Item parent)
  {
    this.parent = parent;
  }
}
