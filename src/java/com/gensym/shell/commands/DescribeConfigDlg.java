package com.gensym.shell.commands;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.BevelBorder;
import com.gensym.classes.G2Definition;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.Item;
import com.gensym.core.GensymApplication;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.TW2MDIApplication;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;

public class DescribeConfigDlg extends StandardDialog {
  private static final Symbol ITEM_CONFIGURATION_ =
  Symbol.intern("ITEM-CONFIGURATION"),
    INSTANCE_CONFIGURATION_ = Symbol.intern ("INSTANCE-CONFIGURATION"),
    KB_CONFIGURATION_ =  Symbol.intern("KB-CONFIGURATION"),
    NOTES_ = Symbol.intern("NOTES");
  private static final String ITEM_CONFIG_ON = "Item configuration on ",
    INSTANCE_CONFIG_ON = "Instance configuration on ";
  private static Sequence instanceConfigurationAttrSeq = new Sequence();
  private static Sequence itemConfigurationAttrSeq = new Sequence();  
  private static GridBagConstraints gbc = new GridBagConstraints();
  private DialogCloser closer;

  static {
    itemConfigurationAttrSeq.addElement(ITEM_CONFIGURATION_);
    instanceConfigurationAttrSeq.addElement(INSTANCE_CONFIGURATION_);
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.anchor = GridBagConstraints.WEST;
    gbc.fill = GridBagConstraints.HORIZONTAL;
  }

  public DescribeConfigDlg (JFrame parent, Item item, G2Access cxn,
			    StandardDialogClient client)
       throws G2AccessException, NoSuchAttributeException
  {
    this(parent, item, cxn, new JPanel(new GridBagLayout()), client);
  }
  
  private DescribeConfigDlg (JFrame parent, Item item,
			     G2Access cxn, JPanel panel,
			    StandardDialogClient client)
       throws G2AccessException, NoSuchAttributeException {
    super(parent, "", false, 
	  new String[]{DISMISS_LABEL}, new int[]{DISMISS}, 
	  new JScrollPane(panel), client);
    String itemName = getName(item);
    setTitle("Item Configuration for " +itemName);
    populateDialog(item, panel);
    closer = new DialogCloser(cxn); 
    this.pack();
  }

  private void populateDialog(Item item, JPanel panel)
       throws G2AccessException, NoSuchAttributeException {

    Sequence containment = item.getContainmentHierarchy();
    Sequence inheritance = item.getDefinition().getClassInheritancePath();
    TwAccess context = 
      (TwAccess)((com.gensym.classes.ImplAccess)item).getContext();
    Item kbConfiguration = 
      context.getUniqueNamedItem(KB_CONFIGURATION_, KB_CONFIGURATION_);
    String currentPrefix;
    Item loopItem;
    
    addConfigurationDescriptionToPanel
      (item, ITEM_CONFIG_ON + getName(item) +": ", panel, true);
    for (int z = 0; z<containment.size(); z++) {
      loopItem = (Item)containment.elementAt(z);
      addConfigurationDescriptionToPanel 
	(loopItem, ITEM_CONFIG_ON + getName(loopItem)+": ", panel, true);
    }
    addConfigurationDescriptionToPanel
      (kbConfiguration, ITEM_CONFIG_ON +"the KB:\n", panel, true);
    for (int zz=0; zz<inheritance.size(); zz++) {
      G2Definition classDef
	= context.getClassManager().getDefinition((Symbol)inheritance.
						  elementAt(zz));
      if (classDef instanceof ClassDefinition) {
	loopItem = (Item)classDef;
	addConfigurationDescriptionToPanel
	  (loopItem, INSTANCE_CONFIG_ON + getName(loopItem)+": ",
		   panel, false);
      }
    }
  }

  private void addConfigurationDescriptionToPanel(Item item, String prefix,
			  JPanel panel, boolean useItemConfiguration)
       throws G2AccessException, NoSuchAttributeException
  {
    String configuration = useItemConfiguration?
      getItemConfiguration(item):
      getInstanceConfiguration((ClassDefinition)item);
    JTextArea textField = makeTextField(prefix+configuration);
    ((GridBagLayout)panel.getLayout()).setConstraints(textField, gbc);
    panel.add(textField);
  }

  private String getItemConfiguration(Item item)
       throws G2AccessException, NoSuchAttributeException
  {    
    //THERE IS A BUG IN getAttributeText (nov 15, 1999)
    return (String)((ImplAccess)item).getAttributeTexts
      (itemConfigurationAttrSeq).getAttributeValue(ITEM_CONFIGURATION_);
  }
  
  private String getInstanceConfiguration(ClassDefinition definition)
       throws G2AccessException, NoSuchAttributeException
  {    
    //THERE IS A BUG IN getAttributeText (nov 15, 1999)
    return (String)((ImplAccess)definition).getAttributeTexts
      (instanceConfigurationAttrSeq).
      getAttributeValue(INSTANCE_CONFIGURATION_);
  }
   
  private String getName(Item item) throws G2AccessException, 
    NoSuchAttributeException {
    String itemName, temp;

    itemName = item.getTableHeader();
    int comma = itemName.indexOf(",");//has a name
    if (comma > -1) itemName = itemName.substring(0, comma);	
    else {
      //will reference it by its class
      Sequence notes = new Sequence();
      notes.addElement(NOTES_);
      temp = ((ImplAccess)item).getAttributeTexts(notes).
	getAttributeValue(NOTES_).toString();
      if (temp.indexOf("-XXX-") > -1) {
	//has a -xxx-# name in notes
	comma = temp.indexOf(":");
	itemName = temp.substring(0, comma);
      }
    }
    return itemName;
  }

  private static final int DEFAULT_TEXT_AREA_WIDTH = 525;
  private static BevelBorder border
  = new BevelBorder(BevelBorder.LOWERED, Color.gray, Color.darkGray);
  
  private JTextArea makeTextField(String configString) {
    int width = DEFAULT_TEXT_AREA_WIDTH,
      height = Math.max(1, (configString.length()/52)) * 23;
    if (configString.indexOf("\n") > -1) height = height +23;
    JTextArea textField = new JTextArea();
    textField.setBorder(border);
    textField.append(configString);
    textField.setBackground(Color.lightGray);
    textField.setEditable(false);
    textField.setLineWrap(true);
    textField.setWrapStyleWord(true);
    textField.setPreferredSize(new Dimension(width, height));
    return textField;
  }

  private class DialogCloser extends G2ConnectionAdapter {
    G2Access cxn;
    public DialogCloser(G2Access cxn) {
      this.cxn = cxn;
      cxn.addG2ConnectionListener(this);
    }

    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e) {
      cxn.removeG2ConnectionListener(this);
      setVisible(false);
    }
  }
    
}
