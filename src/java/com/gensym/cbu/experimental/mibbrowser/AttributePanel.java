package com.gensym.cbu.experimental.mibbrowser;

import java.awt.Component;
import java.awt.Color;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Insets;
import java.awt.Dimension;
import java.util.*;
import java.text.BreakIterator;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.JComponent;
import javax.swing.border.*;

import com.adventnet.snmp.mibs.*;

public class AttributePanel extends Box {
  private final static Dimension minYSize50 = new Dimension(100,50);
  private final static Dimension minYSize120 = new Dimension(100,120);
  private final static Dimension minYSize140 = new Dimension(100,140);

  private JTextField symbolicName = new JTextField("Symbolic Name Data");
  private JTextField numericName = new JTextField("Numeric Name Data");
  private JTextArea fullSymbolicName = new JTextArea("Full Symbolic Name Data");
  private JTextField fullNumericName = new JTextField("Full Numeric Name Data");
  //private JTextField parentSymbolicName = new JTextField("Parent Symbolic Name Data");
  private JTextArea description = new JTextArea("Description Data");
  private JTextArea tag = new JTextArea("Tag Data");
  private SubObjectPanel subObjects = new SubObjectPanel();

  public AttributePanel() {
    super(BoxLayout.Y_AXIS);
    add(createAttributeFields());
    //add(Box.createVerticalGlue());
    //add(createDescriptionField());
    add(createSubObjectsPanel());
//    add(createTagField());
    clearAttributes();
  }


  private JPanel createSubObjectsPanel() {
    subObjects.setBorder(new CompoundBorder(new EmptyBorder(1,1,1,1),
      new SoftBevelBorder(SoftBevelBorder.RAISED)));
    return subObjects;
  }

  private JPanel createTagField() {
    JPanel panel = new JPanel(new BorderLayout());
    panel.setBorder(new CompoundBorder(new EmptyBorder(1,1,2,1),
      new SoftBevelBorder(BevelBorder.RAISED)));
    JLabel tagLabel = new JLabel("Tag:");
    tagLabel.setLabelFor(description);
    tagLabel.setHorizontalAlignment(SwingConstants.LEFT);
    tagLabel.setHorizontalTextPosition(SwingConstants.LEFT);
    panel.add(tagLabel,BorderLayout.NORTH);

    tag.setLineWrap(true);
    tag.setWrapStyleWord(true);
    tag.setEditable(false);
    tag.setRows(4);
    JScrollPane pane = new JScrollPane(tag);
    panel.add(pane,BorderLayout.CENTER);
    return panel;
  }

  private String removeWhiteSpaces(String str) {
    String retv = new String();
    BreakIterator bit = BreakIterator.getWordInstance();
    bit.setText(str);
    int start = bit.first();
    int end  = bit.next();
    while (start != bit.DONE && end != bit.DONE) {
      retv += str.substring(start,end) + " ";
      start = bit.next();
      if (start != bit.DONE)
        end = bit.following(start);
      if (end == bit.DONE)
        retv += str.substring(start);
    }
    return retv;
  }

  private JPanel createDescriptionField() {
    JPanel panel = new JPanel(new BorderLayout());
    panel.setBorder(new CompoundBorder(new EmptyBorder(1,1,1,1),
      new SoftBevelBorder(SoftBevelBorder.RAISED)));
    JLabel descriptionLabel = new JLabel("Description:");
    descriptionLabel.setLabelFor(description);
    descriptionLabel.setHorizontalAlignment(SwingConstants.LEFT);
    descriptionLabel.setHorizontalTextPosition(SwingConstants.LEFT);
    panel.add(descriptionLabel,BorderLayout.NORTH);

    description.setLineWrap(true);
    description.setWrapStyleWord(true);
    description.setTabSize(1);
    description.setRows(4);
    JScrollPane pane = new JScrollPane(description);
    pane.setMinimumSize(minYSize50);
    panel.add(pane,BorderLayout.CENTER);
    return panel;
  }

  private void addField(JPanel p,JLabel l, JComponent f) {
    GridBagConstraints c = new GridBagConstraints();

    l.setLabelFor(f);
    c.fill = GridBagConstraints.BOTH;
    c.weightx = 2.0;
    c.insets = new Insets(0,1,0,5);
    p.add(l,c);

    f.setForeground(Color.black);
    c.gridwidth = GridBagConstraints.REMAINDER;
    c.weightx = 1.0;
    c.insets = new Insets(0,0,0,1);
    p.add(f,c);
  }

  private JComponent createAttributeFields() {
    JLabel symbolicNameLabel = new JLabel("Symbolic Name:");
    JLabel numericNameLabel = new JLabel("Numeric Name:");
    JLabel fullSymbolicNameLabel = new JLabel("Full Symbolic Name:");
    JLabel fullNumericNameLabel = new JLabel("Full Numeric Name:");
    //JLabel parentSymbolicNameLabel = new JLabel("Parent Symbolic Name:");

//    JPanel p = new JPanel(new GridBagLayout());
    JPanel p = new JPanel();
    p.setLayout(new BoxLayout(p,BoxLayout.Y_AXIS));
    p.setBorder(new CompoundBorder(new EmptyBorder(2,1,1,1),
      new SoftBevelBorder(SoftBevelBorder.RAISED)));
    TitledBorder title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED), "SymbolicName");
    title.setTitleColor(Color.black);
    symbolicName.setBorder(title);
    p.add(symbolicName);

    title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED), "NumericName");
    title.setTitleColor(Color.black);
    numericName.setBorder(title);
    p.add(numericName);
    
    title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED), "FullSymbolicName");
    title.setTitleColor(Color.black);
    fullSymbolicName.setBorder(title);
    fullSymbolicName.setLineWrap(true);
    //fullSymbolicName.setRows(2);
    p.add(fullSymbolicName);
    
    title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED), "FullNumericName");
    title.setTitleColor(Color.black);
    fullNumericName.setBorder( title);
    p.add(fullNumericName);
    
    title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED), "Description");
    title.setTitleColor(Color.black);
    JScrollPane sp = new JScrollPane(description);
    sp.setBorder( title);
    description.setLineWrap(true);
    description.setWrapStyleWord(true);
    description.setRows(3);
    p.add(sp);
    
    //addField(p,symbolicNameLabel,symbolicName);
    //addField(p,numericNameLabel,numericName);
    //fullSymbolicName.setLineWrap(true);
    //addField(p,fullSymbolicNameLabel,new JScrollPane(fullSymbolicName));
    //addField(p,fullNumericNameLabel,fullNumericName);
    //addField(p,parentSymbolicNameLabel,parentSymbolicName);

    //JScrollPane pane = new JScrollPane(p);
    //pane.setMinimumSize(minYSize140);
    //pane.setPreferredSize(minYSize140);
    return p;
  }

  public void showAttributes(MibOperations mibOprs, Object o) {
    if (o instanceof MibTrap) {
      showAttributes(mibOprs,(MibTrap)o);
    }
    else if (o instanceof MibNode) {
      showAttributes(mibOprs,(MibNode)o);
    }
    else {
      clearAttributes();
    }
    repaint();
  }

  private void showAttributes(MibOperations mibOprs, MibTrap trap) {
    MibModule mibModule = mibOprs.getMibModule(trap.getModuleName());
    symbolicName.setText(trap.getName());
    numericName.setText(Integer.toString(trap.getValue()));
    String fullNumName = trap.getEnterprise().toString() + "." +
      Integer.toString(trap.getValue());
    fullNumericName.setText(fullNumName);
    fullSymbolicName.setText(mibModule.translateToNames(fullNumName));
    description.setText(unformatString(trap.getDescription()));
    description.setCaretPosition(0);
    tag.setText(trap.toTagString());
    tag.setCaretPosition(0);
    Vector vars = trap.getVariables();
    if (vars != null) {
      String varStr = new String();
      Iterator it = vars.iterator();
      while (it.hasNext()) {
        varStr += (String)it.next();
        if (it.hasNext())
          varStr += ",";
      }
      Vector objects = mibOprs.getNodesFromString(varStr);
      subObjects.setLabel("Variables:");
      subObjects.setSubObjects(objects);
    }
    else {
      subObjects.clearSubObjects();
    }
  }

  private void showAttributes(MibOperations mibOprs, MibNode node) {
    symbolicName.setText(node.getLabel());
    int[] oid = node.getOID();
    numericName.setText(Integer.toString(oid[oid.length - 1]));
    fullNumericName.setText(node.getNumberedOIDString());
    fullSymbolicName.setText(node.getOIDString());
    description.setText(unformatString(node.getDescription()));
    description.setCaretPosition(0);
    tag.setText(node.toTagString());
    tag.setCaretPosition(0);
    String objectNames = node.getObjectNames();
    Vector objects = mibOprs.getNodesFromString(objectNames);
    System.out.println("ObjectNames: " + objectNames);
    System.out.println("Objects: " + objects);
    subObjects.setLabel("Objects:");
    subObjects.setSubObjects(objects);
  }


  private void clearAttributes() {
    symbolicName.setText("");
    numericName.setText("");
    fullSymbolicName.setText("");
    fullNumericName.setText("");
    //parentSymbolicName.setText("");
    description.setText("");
    tag.setText("");
    subObjects.clearSubObjects();
    subObjects.setLabel("Sub Objects:");
  }

  private String unformatString(String s)
    {
      if (s != null) {
        StringBuffer results = new StringBuffer();
        StringTokenizer st = new StringTokenizer(s);
        while(st.hasMoreTokens()){
        	results.append(st.nextToken() + " ");
        }
        return results.toString();
      }
      return null;
    }
}
