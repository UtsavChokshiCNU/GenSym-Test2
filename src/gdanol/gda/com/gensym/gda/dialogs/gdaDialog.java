package com.gensym.gda.dialogs;

import java.awt.BorderLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Dimension;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Iterator;

import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.border.EmptyBorder;
import javax.swing.JScrollPane;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.classes.Item;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;
import com.gensym.core.UiApplication;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.gda.controls.AbstractAttributeEditor;
import java.util.MissingResourceException;

/**
  Root class for all configure dialogs. Contains OK, Apply, Cancel buttons
  and mechanism for updating controls with the edited item attribute values 
  and sending changes in the controls to G2.
  */
public class gdaDialog extends JDialog implements ObjectChangeListener {

  /**
    Constructor without parameters. Use static method
    {@link com.gensym.core.UiApplication#getCurrentFrame()}
    to get java.awt.Frame instance.
    */
  public gdaDialog () {
    this(UiApplication.getCurrentFrame());
  }
  
  /**
    Main constructor. Creates button panel with 
    OK, Apply, Cancel buttons.
    */
  public gdaDialog(java.awt.Frame frame) {
    super(frame);
    attributes=new Hashtable();
    attributesStructure=new Structure();
    changedAttributes = new Hashtable();
    editors = new Vector();
    
    JComponent contentPane = (JComponent)getContentPane();
    ((BorderLayout)contentPane.getLayout()).setHgap(30);
    contentPane.setBorder(new EmptyBorder(10, 10, 10, 10));
    
    centerPane = null;
    
    buttonPane = new JPanel();
    buttonPane.setBorder(new EmptyBorder(5, 0, 0, 0));
    constraints = new GridBagConstraints();
    constraints.fill = GridBagConstraints.HORIZONTAL;
    constraints.insets = new Insets(2, 0, 2, 0);
    buttonsLayout = new GridBagLayout();
    contentPane.add(buttonPane, BorderLayout.SOUTH);
    
    ok = new JButton(gdaDialogMessages.getString("OKButton"));
    apply = new JButton(gdaDialogMessages.getString("ApplyButton"));
    cancel = new JButton(gdaDialogMessages.getString("CancelButton"));
    
    buttonPane.add(ok);	
    buttonPane.add(apply); 
    buttonPane.add(cancel);
    resizeButtons();
    
    getRootPane().setDefaultButton(ok);
    ok.addActionListener(new ActionListener() {
      public void actionPerformed (ActionEvent e) {
	if (applyDialog())
	  cancelDialog();
      }
    });
    apply.addActionListener(new ActionListener() {
      public void actionPerformed (ActionEvent e) {applyDialog();}
    });
    cancel.addActionListener(new ActionListener() {
      public void actionPerformed (ActionEvent e) {cancelDialog();}
    });
    
    //scroll pane to which add panels or tabbed panes.
    scrollPane = new JScrollPane();
    getContentPane().add(scrollPane, BorderLayout.CENTER);
  }
  
  /**
    Override this methods in subclasses to initialize editors with some additional data.
    */
  protected void initializeEditors() {
  }
  
  /**
    Sets the properties of the dialog and the attribute editor values.
    @param additionalData should contain the next attributes:<br>
    ITEM - the {@link #editedItem} of the dialog;<br>
    TITLE - the title of the dialog;<br>
    COMMON-NAME - (optional) the {@link #commonName} of the dialog;<br>
    IS-MODAL - (optional, by default - false) the modality of the dialog ;<br>
    ATTRIBUTES - the sequence of structures about attribute values.	
    */
  public void setAdditionalData(Structure additionalData) {
    Object item = additionalData.getAttributeValue(ITEM_, null);
    String title = (String) additionalData.getAttributeValue(TITLE_, "");
    String commonName= (String) additionalData.getAttributeValue(COMMON_NAME_, "");
    Boolean isModal = (Boolean) additionalData.getAttributeValue(IS_MODAL_, Boolean.FALSE);
    Sequence attributes = (Sequence) additionalData.getAttributeValue(ATTRIBUTES_, null);
    
    setEditedItem(item);
    setTitle(title);
    setCommonName(commonName);
    setModal(isModal.booleanValue());
    setAttributeValues(attributes);
    pack();
    setLocationRelativeTo(getOwner());
    
  }
  /**
    Update controls with values of item attributes in sequence <i>avalues</i>.
    @param avalues sequence of structures with the following attributes:<br>
    ATTRIBUTE-NAME - the name of the attribute;<br>
    ATTRIBUTE-VALUE - the value of the attribute;<br>
    ELEMENTS - (optional) the sequence of valid predefined values, for example the sequence of
    valid all variable-or-parameter names in the G2 application.<br>
    Sequence may contain any other attribute which can be used by control in the {@link #initializeEditors()} method.	
    */
  public void setAttributeValues(Sequence avalues) {
    if (avalues==null) return;
    
    Structure[] values = (Structure[]) 
      avalues.toArray(new Structure[avalues.size()]);
    Object attrValue;
    Object elements;
    for (int i=0; i<values.length;i++) {
      Symbol attrName = (Symbol) values[i].getAttributeValue(ATTRIBUTE_NAME_, "");
      String key=attrName.toString();
      attributes.put(key, values[i]);
      elements=values[i].getAttributeValue(ELEMENTS_, null);
      if (elements==null)
	attrValue=values[i].getAttributeValue(ATTRIBUTE_VALUE_, null);
      else
	attrValue=new Object[]{values[i].getAttributeValue(ATTRIBUTE_VALUE_, null),
				 elements};
      attributesStructure.setAttributeValue(attrName, attrValue);
      
    }
    Trace.send(Trace.ALL_LEVELS, traceKey, gdaDialogMessages, "SettingAttributes", attributesStructure);
    initializeEditors();
    fireObjectUpdate();
  }
  
  /**
    Sets the item edited by this dialog.
    */
  public void setEditedItem(Object item) {editedItem = item;}
  
  public Object getEditedItem() {return editedItem;}
  
  public void setConnection(TwAccess c) {connection=c;}
  
  public TwAccess getConnection() {return connection;}
  
  /**
    Sets the {@link #commonName} variable. iF the name of the editedItem is set to none, 
    then the title of this dialog will be set to the value of {@link #commonName}
    */
  public void setCommonName(String commonname) {commonName=commonname;}
  public String getCommonName() {return commonName;}
  
  public boolean editorsAreValid() {
    for (Iterator i=editors.iterator();i.hasNext();) {
      AbstractAttributeEditor editor = (AbstractAttributeEditor)i.next();
      if (!editor.isValid()) {
	Trace.send(Trace.ALL_LEVELS, traceKey, gdaDialogMessages, "InvalidValueForAttribute", editor.getAttribute());
	editor.setValid(true);
	return false;
      }
    }
    return true;
  }
  
  /**
    Sends all changes made in the dialog to G2 procedure gdl-configure.
    */
  
  public boolean applyDialog() {
    
    if (!editorsAreValid())
      return false;
    
    try {
      connection.callRPC(GDL_CONFIGURE_PROC_,
			 new Object[]{editedItem, getResultStructures(), connection.retrieveSession()}
			 );
    } catch (G2AccessException e) {
      Trace.exception(e);
      return false;
    }
    changedAttributes.clear();
    return true;
  }
  
  /**
    Closes dialog without applying changes.
    */
  public void cancelDialog() {
    try {
      connection.callRPC(GDL_BREAK_CONFIGURATION_LOCK_, new Object[]{editedItem, connection.retrieveSession()});
    } catch (G2AccessException e) {
      Trace.exception(e);
    }
    dispose();
  }
  
  public JPanel getDialogPanel() {return centerPane;}
  
  //puts AttributeStructure to updatedAttributes
  /**
    Collect information about changes made in editors.
    */
  public void objectChanged(ObjectChangeEvent e) {
    String key = e.getAttributeName();
    Structure s = (Structure) attributes.get(key);
    if (s!=null) {
      Structure change = (Structure) changedAttributes.get(key);
      if(change==null) {
	change = new Structure();
	change.setAttributeValue(ATTRIBUTE_NAME_, s.getAttributeValue(ATTRIBUTE_NAME_, null));
      }
      change.setAttributeValue(ATTRIBUTE_VALUE_, e.getChangedObject());
      changedAttributes.put(key, change);
      Trace.send(Trace.ALL_LEVELS, traceKey, gdaDialogMessages, "AttributeValueChanged", key, e.getChangedObject(), changedAttributes);
      
    }
  }
  
  public Sequence getResultStructures() {
    Sequence attributes = new Sequence(changedAttributes.size());
    attributes.addAll(changedAttributes.values());
    Trace.send(Trace.ALL_LEVELS, traceKey, gdaDialogMessages, "ReturnValuesToApply", attributes);
    
    return attributes;
  }
  
  
  
  public synchronized void addObjectUpdateListener(ObjectUpdateListener objectupdatelistener)
  {
    if(updateListeners == null)
      updateListeners = new Vector();
    updateListeners.addElement(objectupdatelistener);
  }
  
  public synchronized void removeObjectUpdateListener(ObjectUpdateListener objectupdatelistener) {
    if(updateListeners == null) {
      return;
    } else {
      updateListeners.removeElement(objectupdatelistener);
      return;
    }
  }
  
  void fireObjectUpdate() {
    Vector vector;
    synchronized(this) {
      if(updateListeners == null) {
	return;
      }
      vector = (Vector)updateListeners.clone();
    }
    
    ObjectUpdateEvent objectupdateevent = new ObjectUpdateEvent(this, attributesStructure);
    for(int i = 0; i < vector.size(); i++) {
      ObjectUpdateListener objectupdatelistener = (ObjectUpdateListener)vector.elementAt(i);
      objectupdatelistener.objectUpdated(objectupdateevent);
    }
  }
  
  private void resizeButtons() {
    
    Dimension okButtonSize = ok.getPreferredSize();
    Dimension applyButtonSize = apply.getPreferredSize();
    Dimension cancelButtonSize = cancel.getPreferredSize();
    
    int buttonHeight = Math.max(okButtonSize.height, applyButtonSize.height);
    buttonHeight = Math.max(buttonHeight, cancelButtonSize.height);
    
    int buttonWidth = Math.max(okButtonSize.width, applyButtonSize.width);
    buttonWidth = Math.max(buttonWidth, cancelButtonSize.width);
    
    Dimension buttonSize = new Dimension(buttonWidth, buttonHeight);
    
    ok.setPreferredSize(buttonSize);
    apply.setPreferredSize(buttonSize);
    cancel.setPreferredSize(buttonSize);
  }
  
  public Structure getAttributeDescription(Symbol attribute){
    return (Structure) attributes.get(attribute.toString());
  }
  
  public void addEditor(AbstractAttributeEditor editor) {
    editors.add(editor);
  }
  
  protected Object getChangedValue(Symbol attribute_) {
    Structure s = (Structure)changedAttributes.get(attribute_.toString());
    if (s==null)
      return null;
    
    return s.getAttributeValue(ATTRIBUTE_VALUE_, null);
  }
  
  protected Object getInitialValue(Symbol attribute_) {
    return ((Structure)attributes.get(attribute_.toString())).
      getAttributeValue(ATTRIBUTE_VALUE_, null);
  }
  
  /**Localizes lowercased Symbol from com.gensym.gda.dialogs.blocks.Messages
    resource file. If the key not found returns lowercased symbol string.
    */
  protected String localize(Symbol attribute) {
    if (attribute==null) return "";
    try {
      return i18n.getString(attribute.toString().toLowerCase());
    } catch (MissingResourceException e) {
      return attribute.toString().toLowerCase();
    }
  }
  
  /**Localizes text from com.gensym.gda.dialogs.blocks.Messages
    resource file. If the value for the key is not found then it returns key itself.
    */
  protected String localize(String text) {
    try {
      return i18n.getString(text);
    } catch (MissingResourceException e) {
      return text;
    }
  }
  
  
	
  Vector updateListeners;
  
  protected Structure attributesStructure;
  protected Hashtable attributes; //keys = attributeStrings, values - 
  //structure (attribute-name: symbol, 
  //			 attribute-value: Object)
  
  protected Hashtable changedAttributes; // see attributes. contains only 
  //changed attribute structures
  
  
  protected JPanel buttonPane;
  protected JPanel centerPane;
  protected GridBagConstraints constraints;
  protected GridBagConstraints labelConstraints;
  protected GridBagConstraints fieldConstraints;
  protected GridBagLayout dialogLayout;
  protected GridBagLayout buttonsLayout;
  
  protected JButton ok;
  protected JButton apply;
  protected JButton cancel;
  protected TwAccess connection;
  protected JScrollPane scrollPane;
  
  protected Object editedItem;
  /** The dialog title will be set to <code>commonName</code> if the name of editedItem is set to none, 
    else the name of editedItem*/
  protected String commonName;
  private Structure emptyStructure = new Structure();
  
  private final static Symbol GDL_CONFIGURE_PROC_ = 
  Symbol.intern("GDL-CONFIGURE");
  private final static Symbol GDL_BREAK_CONFIGURATION_LOCK_ = Symbol.intern("GDL-BREAK-CONFIGURATION-LOCK");
  private final static Symbol ATTRIBUTES_ = Symbol.intern("ATTRIBUTES");
  public final static Symbol ATTRIBUTE_NAME_ = Symbol.intern("ATTRIBUTE-NAME");
  public final static Symbol ATTRIBUTE_VALUE_ = Symbol.intern("ATTRIBUTE-VALUE");
  public final static Symbol ELEMENTS_ = Symbol.intern("ELEMENTS");
  private final static Symbol ITEM_ = Symbol.intern("ITEM");
  private final static Symbol TITLE_ = Symbol.intern("TITLE");
  private final static Symbol IS_MODAL_ = Symbol.intern("IS-MODAL");
  private final static Symbol COMMON_NAME_ = Symbol.intern("COMMON-NAME");
  
  protected Resource i18n;
  protected Resource gdaDialogMessages= Resource.getBundle("com/gensym/gda/dialogs/Messages");
  static MessageKey traceKey = Trace.registerMessageKey("com.gensym.gda", gdaDialog.class);
  
  private Vector editors;
  
}

