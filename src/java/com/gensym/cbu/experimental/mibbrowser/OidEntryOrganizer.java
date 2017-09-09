package com.gensym.cbu.experimental.mibbrowser;

import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

class OidEntryOrganizer
{
  Vector placedOids = new Vector();
  Vector toBePlacedOids = new Vector();
  Hashtable oidToNode = new Hashtable();
  JTree tree;
  DefaultTreeModel defaultTreeModel;
  DefaultMutableTreeNode treeRoot;

  public OidEntryOrganizer()
    {
      treeRoot = new DefaultMutableTreeNode (new String("OIDHierarchy"));

      defaultTreeModel = new DefaultTreeModel(treeRoot);
	
      tree = new JTree(defaultTreeModel) {
	  @Override
	  public String convertValueToText(Object value,
					   boolean selected,
					   boolean expanded,
					   boolean leaf,
					   int row,
					   boolean hasFocus) {
	    return value.toString();
	  }
	};

       tree.getSelectionModel().setSelectionMode
	 (TreeSelectionModel.SINGLE_TREE_SELECTION);

       addOidEntry(new OidEntry("iso", "1", "RFC1155-SMI", null, null));
       addOidEntry(new OidEntry("org", "3", "RFC1155-SMI", "iso", "RFC1155-SMI"));
       addOidEntry(new OidEntry("dod", "6", "RFC1155-SMI", "org", "RFC1155-SMI"));
       addOidEntry(new OidEntry("internet", "1", "RFC1155-SMI", "dod", "RFC1155-SMI"));
       addOidEntry(new OidEntry("directory", "1", "RFC1155-SMI", "internet", "RFC1155-SMI"));
       addOidEntry(new OidEntry("mgmt", "2", "RFC1155-SMI", "internet", "RFC1155-SMI"));
       addOidEntry(new OidEntry("experimental", "3", "RFC1155-SMI", "internet", "RFC1155-SMI"));
       addOidEntry(new OidEntry("private", "4", "RFC1155-SMI", "internet", "RFC1155-SMI"));
       addOidEntry(new OidEntry("enterprises", "1", "RFC1155-SMI", "private", "RFC1155-SMI"));
    }

  public void addOidEntry(OidEntry oe)
    {
      DefaultMutableTreeNode node = new DefaultMutableTreeNode(oe);
      oidToNode.put(oe, node);
      
      if (oe.parentShortName == null)
	{
	  defaultTreeModel.insertNodeInto(node,
					  treeRoot,
					  treeRoot.getChildCount());
	  placedOids.add(oe);
	}
      else {
	OidEntry parentObject = null;
	OidEntry currentOid;
	Enumeration e = placedOids.elements();
	while (e.hasMoreElements() && parentObject == null)
	  {
	    currentOid = (OidEntry)e.nextElement();
	    if (currentOid.shortName.equals(oe.parentShortName) &&
	      currentOid.definingFile.equals(oe.parentDefiningFile))
	      parentObject = currentOid;
	  }
	if (parentObject != null) {
	  DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode)oidToNode.get(parentObject);
	  defaultTreeModel.insertNodeInto(node,
					  parentNode,
					  parentNode.getChildCount());
	  placedOids.add(oe);
	}
	else {
	  defaultTreeModel.insertNodeInto(node,
					  treeRoot,
					  treeRoot.getChildCount());
	  placedOids.add(oe);
	}
      }
    }

  public JTree getTree()
    {
      return tree;
    }
}

  
