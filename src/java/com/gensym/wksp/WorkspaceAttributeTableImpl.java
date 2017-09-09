package com.gensym.wksp;

import com.gensym.classes.Table;
import com.gensym.jgi.G2AccessException;
/**
 *
 * WorkspaceAttributeTable <p>
 * A WorkspaceElement that appears as an attribute-table
 * Text of the rows and the table borders and dividers
 * will draw by default.
 *
 */
public class WorkspaceAttributeTableImpl extends WorkspaceTableImpl
{
  public WorkspaceAttributeTableImpl(Table table, WorkspaceView parent)
       throws G2AccessException
  {
    super(table, parent);
  }

}
