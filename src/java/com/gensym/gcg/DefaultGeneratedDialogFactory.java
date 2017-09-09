/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultGeneratedDialogFactory.java
 *
 */
//make jtable easy
//editing sequences/structures
//dynamic label
//edit names in place
//dynamic pages

package com.gensym.gcg;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Toolkit;
import java.util.Hashtable;
import java.util.Locale;
import java.util.Vector;
import javax.swing.JDialog;
import com.gensym.classes.Item;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.DialogCommand;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.SymbolVector;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.types.G2Type;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;

public class DefaultGeneratedDialogFactory implements GeneratedDialogFactory, AttributePanelFactory{

  private static final Resource i18n = Resource.getBundle("com.gensym.gcg.UiLabels");

  public static final String ATTRIBUTES_GROUP = "Attributes";
  public static final String CONFIGURATION_GROUP = "Configuration";
  public static final String NOTES_GROUP = "Notes";
  public static final String TEXT_GROUP = "Text";
  public static final String[] DEFAULT_GROUPS = new String[]{i18n.getString(TEXT_GROUP),
							     i18n.getString("Attributes"), 
				  			     i18n.getString("Configuration"), 
							     i18n.getString("Notes")};

  private static boolean showWaitDialog = true;
  private static Dimension screenDisplaySize = Toolkit.getDefaultToolkit().getScreenSize ();

  /**
   * Generates a properties dialog for editing an item.  The contents of the dialog are determined by 
   * generateAttributePanel() and generatedCommandButtonPanel().  A command button panel is created
   * when the itemProxy's autoUpload property is false.
   * @see #generateAttributePanel
   * @see #generatedCommandButtonPanel
   */
  @Override
  public Component generateDialog(Frame frame, TwAccess connection, ItemProxy itemProxy,
				  DialogCommand dialogCommand, Locale locale) throws G2AccessException{
    WaitDialog w = null;
    long ts = System.currentTimeMillis ();
    if (showWaitDialog) {
      w = new WaitDialog (frame);
      w.setVisible (true);
    }
    itemProxy.setAttributes(new SymbolVector());//clear out names attribute
    boolean live = itemProxy.getAutoUpload();
    Container panel = generateAttributePanel(connection, itemProxy, dialogCommand, locale);
    JDialog dialog = new GeneratedDialog(frame, connection, itemProxy, dialogCommand, panel, live, locale);
    if (!live)
      dialog.getContentPane().add(generateCommandButtonPanel(connection, itemProxy, dialogCommand), BorderLayout.SOUTH);
    dialog.pack();
    Dimension size = dialog.getSize();
    if (size.width > screenDisplaySize.width)
      dialog.setSize(screenDisplaySize.width - 200, size.height);
    if (size.height > screenDisplaySize.height)
      dialog.setSize(size.width, screenDisplaySize.height - 200);
    long te = System.currentTimeMillis ();
    if ((te - ts) < 1000)
      showWaitDialog = false;
    if (w != null)
      w.setVisible (false);
    
    return dialog;
  }

  @Override
  public Container generatePanel(TwAccess connection, ItemProxy itemProxy,
				 DialogCommand dialogCommand,
				 Locale locale) throws G2AccessException
  {
    return generateAttributePanel(connection, itemProxy, dialogCommand, locale);
  }
  
  /**
   * Creates a container for editing an item.  The container consists of tab pages.  Each tab page 
   * contains editors for one or more attributes. The order and titles of the tab pages, and 
   * the editors for each attribute are determined by getAttributeEditors(). If an editor is specified
   * for the NOTES attribute of an item and it is specified to be on its own tab page, then
   * the NOTES tab page will only be present when the item has notes.
   * @see getAttributeEditors
   */
  protected Container generateAttributePanel(TwAccess connection, ItemProxy itemProxy, DialogCommand dialogCommand, Locale locale) throws G2AccessException{
    G2AttributeGroup[] groups = getAttributeEditors(connection, itemProxy, dialogCommand, locale);
    return new GeneratedAttributePanel(connection, itemProxy, dialogCommand, groups, 
				       itemProxy.getAutoUpload());
  }

  /**
   * Creates a container for closing and/or cancelling an item editing dialog.
   * @see com.gensym.gcg.GeneratedCommandPanel
   */
  protected Container generateCommandButtonPanel(TwAccess connection, ItemProxy itemProxy,
						 DialogCommand dialogCommand){
    return new GeneratedCommandPanel(dialogCommand);
  }

  /**
   * Returns a list of the names of each group of attributes
   */
  public String[] getGroupNames(TwAccess connection, ItemProxy itemProxy, Locale locale){
    return DEFAULT_GROUPS;
  }

  /**
   *  Returns a list of G2AttributeGroups.  getGroupNames determines the ordering and names of the groups.
   *  The attributes considered are obtained via getAttributes.
   *  Each G2AttributeEditor is obtained via getG2AttributeEditor 
   *  @see getAttributes
   *  @see getG2AttributeEditor
   */
  protected G2AttributeGroup[] getAttributeEditors(TwAccess connection, ItemProxy itemProxy, 
						   DialogCommand dlgCommand,
						   Locale locale) throws G2AccessException{
    String[] groupNames = getGroupNames(connection, itemProxy, locale);
    int len = groupNames.length;
    Hashtable groupTable = new Hashtable(len);
    G2AttributeGroup[] groups = new G2AttributeGroup[len];
    for (int i=0; i<groupNames.length; i++){
      G2AttributeGroup group = new G2AttributeGroup(groupNames[i]);
      groupTable.put(groupNames[i], group);
      groups[i] = group;
    }

    AttributeInfo[] attributes = getAttributeInfos(connection, itemProxy, locale);
    for (int i=0; i<attributes.length; i++){
      G2AttributeEditor g2Editor = getG2AttributeEditor(connection, itemProxy, dlgCommand,
							attributes[i], locale);
      if (g2Editor != null){
	AttributeEditor editor = g2Editor.getEditor();
	if (editor != null){
	  G2AttributeGroup group = (G2AttributeGroup)groupTable.get(g2Editor.getGroupName());
	  if (group != null){
	    group.addEditor(g2Editor);
	  }
	}
      }
    }

    return groups;
  }

  /**
   * Returns a list of AttributeInfos for all non-virtual readable attributes of the item for the 
   * connection's current user mode.
   * @see com.gensym.gcg.AttributeInfo#getTableAttributesForMode
   * @see com.gensym.gcg.AttributeInfo#getAttributeInfos
   */
  protected AttributeInfo[] getAttributeInfos(TwAccess connection, ItemProxy itemProxy, Locale locale) throws G2AccessException{
    Symbol[] attributes = AttributeInfo.getTableAttributesForMode(connection, itemProxy.getProxy(), connection.getUserMode());
    return AttributeInfo.getAttributeInfos(connection, itemProxy.getProxy(), attributes);
  }

  /**
   * Returns a G2AttributeEditor for editing the attribute of the item.
   * @see getAttributeLabel
   * @see getAttributeEditor
   * @see getAttributeGroupName
   */
  protected G2AttributeEditor getG2AttributeEditor(TwAccess connection, ItemProxy itemProxy, DialogCommand dlgCommand, AttributeInfo info, Locale locale) throws G2AccessException{
    AttributeEditor editor = getAttributeEditor(connection, itemProxy, dlgCommand, info, locale);
    if (editor != null){
      String groupName = getAttributeGroupName(connection, itemProxy, info, locale);
      Component label = getAttributeLabel(connection, itemProxy, dlgCommand, info, locale);
      return new G2AttributeEditor(groupName, label, editor, itemProxy, info.attributeName);
    }
    return null;
  }

  /**
   * Returns a component to be used as the label for editing the attribute of the item.
   * By default, a AttributeLabel is returned.
   * @see AttributeLabel
   */
  protected Component getAttributeLabel(TwAccess connection, ItemProxy itemProxy, DialogCommand dlgCommand, AttributeInfo info, Locale locale) throws G2AccessException{
    AttributeLabel label = null;
    if (!info.attributeName.equals(SystemAttributeSymbols.NOTES_) &&
	!info.attributeName.equals(SystemAttributeSymbols.TEXT_) &&
	!info.attributeName.equals(SystemAttributeSymbols.ITEM_CONFIGURATION_))
      label = new AttributeLabel(connection, itemProxy.getProxy(), info.attributeName, 
				 itemProxy.getAutoUpload());
    return label;
  }

  /**
   * Returns a component to be used for editing the attribute of the item.  The component is wired to
   * the ItemProxy, if appropriate, via hookupEditor
   */
  protected AttributeEditor getAttributeEditor(TwAccess connection, ItemProxy itemProxy, DialogCommand dlgCommand, AttributeInfo info, Locale locale) throws G2AccessException{
    Item item = itemProxy.getProxy();
    Component editor = null;
    if (info.attributeName.equals(SystemAttributeSymbols.NOTES_))
      editor = new NotesTextArea(connection, item, dlgCommand);
    else{
      Object value = null;
      try{
	value = item.getPropertyValue(info.attributeName);
      }
      catch(NoSuchAttributeException ex){
	Trace.exception(ex);
      }
      info.initializeEditorInformation();
      if ((!info.hasEditor || value instanceof Item) && info.isTextReadable){
	if (!info.isTextWritable)
	  editor = new G2ReadOnlyTextArea(connection, item, info.attributeName, info.denotation);
	else{
	  if (value instanceof Item)
	    editor = new G2TextArea(connection, item, (Item)value, info.attributeName, info.denotation,  
				    connection.getUserMode(), locale);
	  else
	    editor = new G2TextArea(connection, item, info.denotation, 
				    info.definingClass, info.simpleAttributeName);
	}
      }
      else if (info.hasEditor)
	editor = info.makeEditor();
    }

    if (editor != null)
      hookUpEditor((AttributeEditor)editor, itemProxy, info.attributeName, info.isValueWritable);

    return (AttributeEditor)editor;
  }

  /**
   * Returns the group assigment for the editor of the attribute of the item.  This may be used to
   * arrange the editing components in a container
   * By default, the notes attribute, text attribute and item-configuration attribute are each assigned to there 
   * own group, NOTES_GROUP, TEXT_GROUP and CONFIGURATION_GROUP, respectively; all other attributes are assigned 
   * to ATTRIBUTES_GROUP
   */
  protected String getAttributeGroupName(TwAccess connection, ItemProxy itemProxy, AttributeInfo info, Locale locale) throws G2AccessException{
    if (info.attributeName.equals(SystemAttributeSymbols.NOTES_))
      return NOTES_GROUP;
    else if (info.attributeName.equals(SystemAttributeSymbols.ITEM_CONFIGURATION_))
      return CONFIGURATION_GROUP;
    else if (info.attributeName.equals(SystemAttributeSymbols.TEXT_))
      return TEXT_GROUP;
    else
      return ATTRIBUTES_GROUP;
  }

  /**
   * Wires together the editor's ObjectChangedEvents and the ItemProxy's ObjectUpdatedEvents
   */
  protected void hookUpEditor(AttributeEditor editor, ItemProxy itemProxy, Symbol attributeName, 
			      boolean writableAttribute){
    itemProxy.addAttribute(attributeName);
    editor.setAttribute(attributeName);
    if (writableAttribute)
      editor.addObjectChangeListener(itemProxy);
    itemProxy.addObjectUpdateListener((ObjectUpdateListener)editor);
  }
}
