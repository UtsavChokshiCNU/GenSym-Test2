package com.gensym.beaneditor;

import java.awt.*;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.JDialog;
import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;

class TabbedPalette extends JDialog{
  private JTabbedPane tabbedPane;

  TabbedPalette(Frame editorFrame, String title){
    super(editorFrame, title);
    tabbedPane = new JTabbedPane(SwingConstants.RIGHT);
    getContentPane().add(tabbedPane, BorderLayout.CENTER);
  }
  
  void addPalette(G2JarInfo g2JarInfo, String jarName){
    Hashtable groups = new Hashtable();
    Vector groupNames = new Vector();
    for (int i=0; i<g2JarInfo.getCount(); i++){
      String groupName = g2JarInfo.getGroup(i);
      if (groupName == null)
	groupName = jarName;
      Vector beans = (Vector)groups.get(groupName);
      if (beans == null){
	beans = new Vector();
	groups.put(groupName, beans);
	groupNames.addElement(groupName);
      }
      beans.addElement(g2JarInfo.getName(i));
    }
    Enumeration beanGroups = groupNames.elements();
    while (beanGroups.hasMoreElements()){
      String name = (String)beanGroups.nextElement();
      // apologies for the quickie hack
      // the jcontrols beans must be excluded until Swing components
      // can be serialized for persistence, or until we use
      // a different save format
      if ("jcontrols".equals(name))
 	continue;

      Vector beans = (Vector)groups.get(name);
      String[] beanArray = new String[beans.size()];
      beans.copyInto(beanArray);
      BeanPalette beanPalette = new BeanPalette(name, 3);
      BeanCreator creator = new BeanCreator(beanArray, g2JarInfo.getClassLoader());
      beanPalette.add(creator);
      tabbedPane.addTab(name, beanPalette);
      Dimension size = tabbedPane.getPreferredSize();
      Insets insets = getInsets();
      Dimension newSize = new Dimension(size.width + insets.left + insets.right, size.height + insets.top + insets.bottom);
      setSize(newSize);
    }
  }
  
  JTabbedPane getTabbedPane(){
    return tabbedPane;
  }
}


