package com.gensym.uitools.inspect.trees;

import java.util.Enumeration;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Dimension;
import java.awt.Insets;
import javax.swing.JTree;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.ToolTipManager;
import javax.swing.tree.TreePath;
import javax.swing.JPopupMenu;
import javax.swing.tree.TreePath;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.classes.Item;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.BasicTreeCellRenderer;
import com.gensym.ntw.util.InstanceData;
import com.gensym.ntw.util.DefaultObjectInstancePopupMenuFactory;
import com.gensym.ntw.util.InstancePopupMenuFactory;
import com.gensym.ntw.util.BasicTreeNode;
import com.gensym.uitools.utils.JTreePlus;
import com.gensym.uitools.utils.FontUtil;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.Component;
import java.awt.Color;
import com.gensym.classes.Item;
import com.gensym.classes.Block;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

public class InspectTreeView extends JTreePlus
{
  private static final Symbol
  ITEM_OR_NAME_ = Symbol.intern ("ITEM-OR-NAME"),
    CHILDREN_ = Symbol.intern ("CHILDREN");
  private static final String NO_DATA_AVAILABLE = "NO DATA AVAILABLE";
  private static final String KNOWLEDGE_BASE = InspectNodeInstanceData.KNOWLEDGE_BASE;
  private static final String KNOWLEDGE_BASE_FROM_G2 = "KNOWLEDGE-BASE";  
  private static final String NO_NAME = "NO NAME";
  private static final Symbol OK_ = Symbol.intern("OK");    
  private InstancePopupMenuFactory menuFactory;
  private TwAccess cxn;
  private int autoExpandDepth;
  private boolean autoExpand;
 
  public InspectTreeView(TwAccess cxn,
			 Structure inspectRootNodeData) {
    this(cxn, false, inspectRootNodeData);
  }

  public InspectTreeView(TwAccess cxn,
			 boolean autoExpand,
			 Structure inspectRootNodeData)       
  {
    super();
    this.autoExpand = autoExpand;
    this.cxn = cxn;    
    setRootNodeData(inspectRootNodeData);
    menuFactory = createInstancePopupMenuFactory();
    //ToolTipManager.sharedInstance().registerComponent(this);
    setCellRenderer(new SpecializedTreeCellRenderer());
    setRowHeight(19);
    setEditable(false);
    addMouseListener(new MouseEventListener());
    setSize(new Dimension(250,400));
  }

  class SpecializedTreeCellRenderer extends BasicTreeCellRenderer {
    @Override
    public Component getTreeCellRendererComponent(JTree tree, Object value,
						  boolean selected, boolean expanded,
						  boolean leaf, int row, boolean hasFocus) {
      super.getTreeCellRendererComponent(tree,value,selected,expanded,leaf, row, hasFocus);      
      InstanceData userObject
	= (InstanceData)((DefaultMutableTreeNode)value).getUserObject();
      Item item = userObject.getItem();
      if (item instanceof Block) {
	Block b = (Block)item;
	boolean interesting = false;
	try {
	  interesting = (!b.getItemStatus().equals(OK_) || b.getItemNotes() != null);//NOTE attributes not cached!
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
	if (interesting)
	  setForeground(Color.red);
      }
      return this;
    }
  }

  public boolean getAutoExpand(){
    return autoExpand;
  }

  public void setAutoExpand(boolean autoExpand){
    this.autoExpand = autoExpand;
  }

  public void setAutoExpandDepth(int autoExpandDepth) {
    this.autoExpandDepth = autoExpandDepth;
  }
  
  public void setConnection(TwAccess cxn) {
    this.cxn = cxn;
  }

  private static final Structure KNOWLEDGE_BASE_ROOT_STRUCTURE = new Structure();
  static {
    KNOWLEDGE_BASE_ROOT_STRUCTURE.setAttributeValue(ITEM_OR_NAME_, KNOWLEDGE_BASE);
  }
  public void setRootNodeData(Structure inspectRootNodeData) {
   
   if (inspectRootNodeData != null &&
       (KNOWLEDGE_BASE_FROM_G2.equals(inspectRootNodeData.getAttributeValue(ITEM_OR_NAME_, null)))) {
     inspectRootNodeData.setAttributeValue(ITEM_OR_NAME_, KNOWLEDGE_BASE);
   } else {
     Structure data = inspectRootNodeData;
     inspectRootNodeData = (Structure)KNOWLEDGE_BASE_ROOT_STRUCTURE.clone();
     if (data != null) {
       Sequence children = new Sequence();
       children.addElement(data);
       inspectRootNodeData.setAttributeValue(CHILDREN_, children);
     }
   } 
   ((DefaultTreeModel)getModel()).setRoot(createNode(cxn, inspectRootNodeData));
   if (autoExpand) {
     for (int i=0;i<getRowCount();i++) {
       TreePath path = getPathForRow(i);
       if (path.getPathCount() <= autoExpandDepth)
	 expandRow(i);
     }
   }
  }

  public void setInstancePopupMenuFactory(InstancePopupMenuFactory factory) {
    menuFactory = factory;
  }
  
  protected InstancePopupMenuFactory createInstancePopupMenuFactory()
  {
    return new DefaultObjectInstancePopupMenuFactory();
  }

  protected static InspectNodeInstanceData createInstanceData(Object userObject) {
    return new InspectNodeInstanceData(userObject);
  }
  
  private static BasicTreeNode createNode(TwAccess cxn,
					  Object userObject,
					  boolean allowsChildren)
  {
    BasicTreeNode node=new BasicTreeNode(cxn,
					 createInstanceData(userObject),
					 !allowsChildren);
    return node;
  }
  
  private static BasicTreeNode createNode(TwAccess cxn,
					  Structure nodeDataStructure)
  {       
    Object itemOrName = nodeDataStructure.getAttributeValue(ITEM_OR_NAME_,NO_NAME);
    Sequence children = (Sequence)nodeDataStructure.getAttributeValue(CHILDREN_, null);
    boolean hasChildren = (children!=null) && (children.size()>0);
    BasicTreeNode node = createNode(cxn, itemOrName, hasChildren);
    if (hasChildren) {
      Enumeration e = children.elements();
      int i = 0;
      while(e.hasMoreElements()) 
	node.insert(createNode(cxn, (Structure)e.nextElement()), i++);
    }
    return node;
  }

  class MouseEventListener extends MouseAdapter {
    @Override
    public void mouseReleased(MouseEvent e) {
      if (e.isPopupTrigger()) //intelNT
	doPopup(e);
    }

    @Override
    public void mousePressed(MouseEvent e) {
      if (e.isPopupTrigger())//Solaris
	doPopup(e);
    }
    
    private void doPopup(MouseEvent e) {
      JTree tree = (JTree)e.getSource();
      int x = e.getX();
      int y = e.getY();
      TreePath path = tree.getPathForLocation(x, y);     
      if (path != null) {
	tree.setSelectionPath(path);
	BasicTreeNode node = (BasicTreeNode)path.getLastPathComponent();
	InspectNodeInstanceData data = (InspectNodeInstanceData)node.getUserObject();
	Item item = data.getItem();
	if (item != null) {
	  JPopupMenu menu =
	    ((InstancePopupMenuFactory)menuFactory).createInstancePopupMenu(cxn,
									    data.getDataType(),
									    tree);
	  FontUtil.initMenuElement(menu, menuInsets, FontUtil.sanserifPlain11);
	  if (menu != null)
	    menu.show(tree, x+1, y+1);
	}
      } 
    }
  }
  private static Insets menuInsets = new Insets(2,0,2,0);
  
}
