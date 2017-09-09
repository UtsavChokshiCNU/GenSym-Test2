package com.gensym.cbu.experimental.mibbrowser;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.util.Vector;
import java.util.Iterator;
import java.util.StringTokenizer;

import javax.swing.JComponent;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.table.DefaultTableModel;
import javax.swing.BoxLayout;
import javax.swing.border.*;
import javax.swing.SwingConstants;

import com.adventnet.snmp.mibs.*;

public class SubObjectPanel extends JPanel {
  private JLabel label = new JLabel("Sub Objects:");
  private JPanel subObjects = new JPanel();

  public SubObjectPanel() {
    setLayout( new BorderLayout());
    add(label,BorderLayout.NORTH);
    subObjects.setLayout(new BoxLayout(subObjects, BoxLayout.Y_AXIS));
    label.setHorizontalAlignment(SwingConstants.LEFT);
    label.setHorizontalTextPosition(SwingConstants.LEFT);
    JScrollPane pane = new JScrollPane(subObjects);
    pane.getVerticalScrollBar().setUnitIncrement(5);
    pane.getVerticalScrollBar().setBlockIncrement(20);
    add(pane);
  }

  private JComponent createSubObject(MibNode node) {
    JPanel p = new JPanel(new BorderLayout());
    TitledBorder title = new TitledBorder(
      new EtchedBorder(EtchedBorder.RAISED),node.getLabel());
    title.setTitleColor(Color.black);
    p.setBorder(new CompoundBorder(new EmptyBorder(1,1,1,1), title));
    JTextArea name = new JTextArea(node.getOIDString());
    name.setBorder(new CompoundBorder(new EmptyBorder(1,0,1,0),
      new BevelBorder(BevelBorder.RAISED)));
    name.setBackground(p.getBackground());
    name.setLineWrap(true);
    name.setSelectionColor(Color.darkGray);    
    p.add(name, BorderLayout.NORTH);
    JTextArea desc = new JTextArea(unformatString(node.getDescription()));
    desc.setBorder(new CompoundBorder(new EmptyBorder(1,0,1,0),
      new BevelBorder(BevelBorder.RAISED)));
    desc.setSelectionColor(Color.darkGray);
    desc.setBackground(p.getBackground());
    //desc.setRows(4);
    desc.setLineWrap(true);
    desc.setWrapStyleWord(true);
    p.add(desc, BorderLayout.CENTER);
    return p;
  }

  public void setLabel(String title) {
    label.setText(title);
  }

  public void clearSubObjects() {
    subObjects.removeAll();
  }

  public void setSubObjects(Vector mibNodes) {
    clearSubObjects();
    if (mibNodes != null) {
      Iterator it = mibNodes.iterator();
      while (it.hasNext()) {
        subObjects.add(createSubObject((MibNode)it.next()));
      }
    }
    subObjects.revalidate();
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
