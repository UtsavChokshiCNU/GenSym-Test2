package com.gensym.cbu.experimental.mibbrowser;

import java.util.*;
import javax.swing.*;
import javax.swing.tree.*;

import com.adventnet.snmp.mibs.*;

class MibFileOrganizer
{
  JTree tree;
  DefaultTreeModel defaultTreeModel;
  DefaultMutableTreeNode treeRoot;
  Hashtable fileToNode = new Hashtable();

  public MibFileOrganizer()
    {
      treeRoot = new DefaultMutableTreeNode (new String("MibFiles"));

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
    }

  public void add(MibModule mibModule) {
    Enumeration children = treeRoot.children();
    String moduleName = mibModule.getName();
    DefaultMutableTreeNode child;
    String childModuleName;
    boolean childFound = false;
    //System.out.println("adding module " +  moduleName);
    while (children.hasMoreElements () && (childFound == false))
    {
      child = (DefaultMutableTreeNode) children.nextElement();
      childModuleName = ((MibModule)child.getUserObject()).toString();
      //System.out.println("existing module " +  childModuleName);
      if (moduleName.equals(childModuleName))
      {
        child.setUserObject(mibModule);
        childFound = true;
      }
    }
    //System.out.println(moduleName + " is being added");
    if ( childFound == false) {
      DefaultMutableTreeNode node = new DefaultMutableTreeNode(mibModule);
      defaultTreeModel.insertNodeInto(node,treeRoot,treeRoot.getChildCount());
      addChildNodes(node);
    }
  }

  private void addChildNodes(DefaultMutableTreeNode node) {
    if (node.getUserObject() instanceof MibModule) {
      MibModule mibModule = (MibModule)node.getUserObject();
      Enumeration traps = mibModule.getDefinedTraps();

      if (traps.hasMoreElements()) {
        DefaultMutableTreeNode trapsNode = new DefaultMutableTreeNode("Traps");
        defaultTreeModel.insertNodeInto(trapsNode, node, node.getChildCount());
        while (traps.hasMoreElements()) {
          MibTrap trap = (MibTrap)traps.nextElement();
          DefaultMutableTreeNode trapNode = new DefaultMutableTreeNode(trap);
          defaultTreeModel.insertNodeInto(trapNode, trapsNode, trapsNode.getChildCount());
        }
      }

      Enumeration notifications = mibModule.getDefinedNotifications();
      if(notifications.hasMoreElements()) {
        DefaultMutableTreeNode notifsNode = new DefaultMutableTreeNode("Notifications");
        defaultTreeModel.insertNodeInto(notifsNode, node, node.getChildCount());
        while (notifications.hasMoreElements()) {
          MibNode notif = (MibNode)notifications.nextElement();
          DefaultMutableTreeNode notifNode = new DefaultMutableTreeNode(notif);
          defaultTreeModel.insertNodeInto(notifNode, notifsNode, notifsNode.getChildCount());
        }
      }
    }
  }

  private void addOIDChildren(DefaultMutableTreeNode node) {
    MibNode mibNode = (MibNode)node.getUserObject();

    Iterator it = mibNode.getChildList().iterator();
    while (it.hasNext()) {
      Object userObject = it.next();
      if (userObject instanceof MibNode) {
        MibNode child = (MibNode)it.next();
        DefaultMutableTreeNode treeNode = new DefaultMutableTreeNode(child);
        defaultTreeModel.insertNodeInto(treeNode,node,node.getChildCount());
        addOIDChildren(treeNode);
      }
    }
  }

  public void add(MibFile mibFile)
    {
      DefaultMutableTreeNode node = new DefaultMutableTreeNode(mibFile);
      fileToNode.put(mibFile, node);

      DefaultMutableTreeNode mibFileNode = new DefaultMutableTreeNode(mibFile);
      defaultTreeModel.insertNodeInto(mibFileNode,
				      treeRoot,
				      treeRoot.getChildCount());

      DefaultMutableTreeNode objectTypeRootNode
	= new DefaultMutableTreeNode(new String("Object-Types"));
      defaultTreeModel.insertNodeInto(objectTypeRootNode,
				     mibFileNode,
				     mibFileNode.getChildCount());
      
      DefaultMutableTreeNode objectTypeNode;
      for (Enumeration e = mibFile.objectTypes.elements(); e.hasMoreElements(); )
	{
	  objectTypeNode = new DefaultMutableTreeNode(e.nextElement());
	  defaultTreeModel.insertNodeInto(objectTypeNode,
					  objectTypeRootNode,
					  objectTypeRootNode.getChildCount());
	}
      
      DefaultMutableTreeNode objectIdentifierRootNode
	= new DefaultMutableTreeNode(new String("Object Identifiers"));
      defaultTreeModel.insertNodeInto(objectIdentifierRootNode,
				     mibFileNode,
				     mibFileNode.getChildCount());
      
      DefaultMutableTreeNode objectIdentifierNode;
      for (Enumeration e = mibFile.objectIdentifiers.elements(); e.hasMoreElements(); )
	{
	  objectIdentifierNode = new DefaultMutableTreeNode(e.nextElement());
	  defaultTreeModel.insertNodeInto(objectIdentifierNode,
					  objectIdentifierRootNode,
					  objectIdentifierRootNode.getChildCount());
	}
      
      DefaultMutableTreeNode trapTypeRootNode
	= new DefaultMutableTreeNode(new String("Trap-Types"));
      defaultTreeModel.insertNodeInto(trapTypeRootNode,
				     mibFileNode,
				     mibFileNode.getChildCount());
      
      DefaultMutableTreeNode trapTypeNode;
      for (Enumeration e = mibFile.trapTypes.elements(); e.hasMoreElements(); )
	{
	  trapTypeNode = new DefaultMutableTreeNode(e.nextElement());
	  defaultTreeModel.insertNodeInto(trapTypeNode,
					  trapTypeRootNode,
					  trapTypeRootNode.getChildCount());
	}
      
      DefaultMutableTreeNode mibDataTypeRootNode
	= new DefaultMutableTreeNode(new String("DataTypes"));
      defaultTreeModel.insertNodeInto(mibDataTypeRootNode,
				     mibFileNode,
				     mibFileNode.getChildCount());
      
      DefaultMutableTreeNode mibDataTypeNode;
      for (Enumeration e = mibFile.mibDataTypes.elements(); e.hasMoreElements(); )
	{
	  mibDataTypeNode = new DefaultMutableTreeNode(e.nextElement());
	  defaultTreeModel.insertNodeInto(mibDataTypeNode,
					  mibDataTypeRootNode,
					  mibDataTypeRootNode.getChildCount());
	}

      DefaultMutableTreeNode mibNotificationTypeRootNode
	= new DefaultMutableTreeNode(new String("Notification Types"));
      defaultTreeModel.insertNodeInto(mibNotificationTypeRootNode,
				     mibFileNode,
				     mibFileNode.getChildCount());
      
      DefaultMutableTreeNode mibNotificationTypeNode;
      for (Enumeration e = mibFile.notificationTypes.elements(); e.hasMoreElements(); )
	{
	  mibNotificationTypeNode = new DefaultMutableTreeNode(e.nextElement());
	  defaultTreeModel.insertNodeInto(mibNotificationTypeNode,
					  mibNotificationTypeRootNode,
					  mibNotificationTypeRootNode.getChildCount());
	}

    }

  public JTree getTree()
    {
      return tree;
    }
}
