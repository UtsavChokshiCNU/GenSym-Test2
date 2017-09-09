package com.gensym.gcg;

import java.awt.*;
import java.awt.event.*;
import java.util.StringTokenizer;
import java.util.Vector;
import java.util.Locale;
import java.util.Enumeration;

import com.gensym.util.Structure;
import com.gensym.util.Sequence ;
import com.gensym.util.Symbol;
import com.gensym.util.ItemEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;

import com.gensym.dlg.TabGroupPanel;
import com.gensym.classes.Item;
import com.gensym.classes.Block;
import com.gensym.classes.ClassDefinition;

import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.util.NoSuchAttributeException;

import com.gensym.controls.ItemProxy;
import com.gensym.controls.AttributeEditor;
import com.gensym.controls.SymbolVector;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.beansruntime.StringVector;
import com.gensym.gcg.AttributeDialogInfo;
import com.gensym.gcg.AttributeTextArea;

public abstract class GenericAttributesDialog extends Dialog
implements com.gensym.util.ItemListener
{
  private GridBagConstraints labelConstraints = new GridBagConstraints();
  private GridBagConstraints fieldConstraints = new GridBagConstraints();
  private GridBagConstraints complexFieldConstraints = new GridBagConstraints();
  private GridBagConstraints buttonConstraints = new GridBagConstraints();
  
  private Button okButton, applyButton, cancelButton;
  private Vector panels = new Vector();
  private Panel buttonPanel = null;
  private TabGroupPanel tabThing;

  private Item item;
  private Frame frame;
  private static final Symbol userMode = Symbol.intern("ADMINISTRATOR");
  private boolean isModal;
  private ItemProxy itemProxy;
  private TwAccess connection;
  private int accumulatedHeight = 0;
  private Locale locale;
  private AttributeDialogInfo[] attributeInfos;
  private Component[] editors;
  private Vector textAreas = new Vector();
  private Vector textAreaInfos = new Vector();
  private Dimension packedSize;

  private static int Y_INSET = 3;
  private static int X_INSET = 3;
  private static int MIN_EDITOR_HEIGHT = 25;

  private static final Symbol g2GetDenotedAttributeTexts_
     = Symbol.intern("G2-GET-DENOTED-ATTRIBUTE-TEXTS");

  private static final Symbol type_ = Symbol.intern("TYPE");
  private static final Symbol name_ = Symbol.intern("NAME");
  private static final Symbol attribute_ = Symbol.intern("ATTRIBUTE");
  private static final Symbol classQualifier_ = Symbol.intern("CLASS-QUALIFIER");
  private String[] attributeNames;
  private String[] attributeLabels;
  private boolean[] editables;

  public GenericAttributesDialog(Frame frame,
				 Item item,
				 TwAccess connection,
				 boolean isModal,
				 Locale locale)
  {
    super(frame,"", isModal);
    this.item = item;
    this.frame = frame;
    this.isModal = isModal;
    this.connection = connection;
    this.locale = locale;
    this.attributeNames = getAttributeNames();
    this.attributeLabels = getAttributeLabels();
    this.editables = getEditables();
    
    // Set up Top Level Tab Panel and buttons
    setLayout(new BorderLayout());
    tabThing = new TabGroupPanel( );
    tabThing.addComponentListener (new ComponentAdapter () {
      @Override
      public void componentResized (ComponentEvent e) {
	if (packedSize == null)
	  return;
	Dimension currentSize = tabThing.getSize ();
	if (currentSize.width < packedSize.width ||
	    currentSize.height < packedSize.height)
	  addPane ();
      }
    });
    add(tabThing, "Center");
    try {
      item.addItemListener(this);
    } catch (G2AccessException e) {
      e.printStackTrace();
    }

    labelConstraints.fill = GridBagConstraints.BOTH;
    labelConstraints.weightx = 1.0;
    labelConstraints.weighty = 1.0;
    labelConstraints.insets = new Insets(Y_INSET,X_INSET,Y_INSET,X_INSET);

    fieldConstraints.fill = GridBagConstraints.BOTH;
    fieldConstraints.gridwidth = GridBagConstraints.REMAINDER;
    fieldConstraints.weightx = 50.0;
    fieldConstraints.weighty = 1.0;
    fieldConstraints.insets = new Insets(Y_INSET,X_INSET,Y_INSET,X_INSET);

    complexFieldConstraints.fill = GridBagConstraints.BOTH;
    // complexFieldConstraints.gridwidth = GridBagConstraints.REMAINDER;
    complexFieldConstraints.weightx = 50.0;
    complexFieldConstraints.weighty = 1.0;
    complexFieldConstraints.insets = new Insets(Y_INSET,X_INSET,Y_INSET,0);

    buttonConstraints.fill = GridBagConstraints.BOTH;
    buttonConstraints.gridwidth = GridBagConstraints.REMAINDER;
    buttonConstraints.weightx = 1.0;
    buttonConstraints.weighty = 1.0;
    buttonConstraints.insets = new Insets(Y_INSET,0,Y_INSET,X_INSET);

    populatePanels();
    setUpItemProxy();//pbk ???
    
    pack ();
    packedSize = getSize ();
    boolean needPane =  ((packedSize.width > screenDisplaySize.width - 200) ||
			 (packedSize.height > screenDisplaySize.height - 200));
    packedSize = tabThing.getSize ();
    if (needPane) addPane ();
    addWindowListener(new AttributesDialogAdapter(this));
    connection.addG2ConnectionListener
      (new G2ConnectionAdapter ()
       {
	 @Override
	 public void g2ConnectionClosed(G2ConnectionEvent e)
	 {
	   GenericAttributesDialog.this.cleanup(false);
	 }
       } );
  }


  public abstract String[] getAttributeNames();

  public abstract String[] getAttributeLabels();

  public abstract boolean[] getEditables();
  
  @Override
  public void setSize (Dimension sz) {
    // Maybe put in a hook for inserting/removing ScrollPane -vkp, 9/21/98
    super.setSize (sz);
  }

  private static java.awt.Dimension screenDisplaySize = java.awt.Toolkit.getDefaultToolkit().getScreenSize ();

  private void addPane () {
    if (true) return;
    long t0 = System.currentTimeMillis ();
    Container mainPanelContainer = (Container) tabThing.getComponentAt (0); // We know this
    Panel mainPanel = (Panel) mainPanelContainer.getComponents()[0];
    ScrollPane pane = new ScrollPane(ScrollPane.SCROLLBARS_ALWAYS);
    Rectangle mpcBounds = mainPanelContainer.getBounds ();
    pane.setBounds (mpcBounds.x, mpcBounds.y,
		    mpcBounds.width + 20, screenDisplaySize.height - 200);
    pane.add (mainPanel);
    mainPanelContainer.add (pane);
    tabThing.validate ();
    packedSize = null; // has pane
  }

  private void populatePanels()
  {
    Container mainPanelContainer = new Container () {};//ColoredPanel (Color.lightGray);
    mainPanelContainer.setLayout(new BorderLayout());
    mainPanelContainer.setName ("MPC");
    Panel mainPanel = new Panel (); //new ColoredPanel(Color.lightGray);
    mainPanel.setLayout(new GridBagLayout());
    mainPanel.setName ("MP!!");
    tabThing.addTab("Attributes", mainPanelContainer);
    mainPanelContainer.add (mainPanel, BorderLayout.CENTER);
    int height;
    
    String[] visibleAttributeKeys = attributeNames;
    int attributeCount = visibleAttributeKeys.length;
    attributeInfos = new AttributeDialogInfo[attributeCount];
    editors = new Component[attributeCount];
    Object attributeValues[] = new Object[attributeCount];
    String attributeTexts[] = new String[attributeCount];
    fillInfosValuesAndTexts(visibleAttributeKeys,
			    attributeInfos,
			    attributeValues,
			    attributeTexts);

    for (int i = 0; i<attributeCount ; i++) {
      AttributeDialogInfo info = attributeInfos[i];
      //String nameText = info.attributeName.toString();
      String nameText = attributeLabels[i];
      boolean editable = editables[i];
      if (!editable) info.isTextWritable = false;
      if (!editable || ((!info.hasEditor ||
			 attributeValues[i] instanceof Item) && 
			info.isTextReadable))
	addDefaultRow(info,mainPanel,attributeTexts[i], attributeValues[i],nameText);
      else if (info.hasEditor) {
	Component editor = info.makeEditor();
	editors[i] = editor;
	addInlineEditorRow(info,mainPanel,editor, nameText);
      }
    }
  }

  private void fillInfosValuesAndTexts(String[] keys,
				       AttributeDialogInfo[] infos,
				       Object[] values,
				       String[] texts)
  {
    int i, len = keys.length, count = 0;
    Sequence request = new Sequence();
    Sequence valueRequest = new Sequence();
    Sequence result = null;
    int[] positions = new int [len];
    
    for (i=0 ; i<len ; i++)
      {
	AttributeDialogInfo info
	  = AttributeDialogInfo.getAttributeDialogInfo(connection,keys[i]);
	infos[i] = info;
	editors[i] = null; // unless overridden later 
	request.addElement(info.denotation);
	valueRequest.addElement(info.attributeName);
	positions[count++] = i;
      }

    result = getAttributeTexts(request);

    if (result != null)
      for (i=0 ; i<result.size(); i++)
	texts[positions[i]] = (String) result.elementAt(i);
    
    try {
      for (i=0; i<valueRequest.size() ; i++)
	  values[positions[i]] 
	    = item.getPropertyValue((Symbol)valueRequest.elementAt(i));
	  
      /*
      Structure valueStructure = item.getAttributeValues(valueRequest);
      System.out.println("values Structure "+valueStructure);
      Enumeration attrNames = valueStructure.getAttributeNames();
      Enumeration attrValues = valueStructure.getAttributeValues();
      while (attrNames.hasMoreElements())
	values[valueRequest.indexOf(attrNames.nextElement())] 
	  = attrValues.nextElement();
	  */
    } catch (G2AccessException gae)
      {
	gae.printStackTrace();
	// just do nothing - no value for attribute
      }
    catch (NoSuchAttributeException nsae)
      {
	nsae.printStackTrace();
	// just do nothing - no value for attribute
      }
  }

  private Sequence getAttributeTexts (Sequence request)
  {
    Sequence result = null;
    try {
      if (request.size() > 0)
	result 
	  = (Sequence) connection.callRPC(g2GetDenotedAttributeTexts_,
					  new Object[] { item , request });
    } catch (Exception e)
      {
	System.out.println("Failed to getAttributeTexts");
	e.printStackTrace();
      }
    return result;
  }

  private void addInlineEditorRow(AttributeDialogInfo info,
				  Panel panel,
				  Component editor,
				  String label)
  {
    int height = 1;
    addLabel(panel, label, height);

    GridBagLayout gridBag = (GridBagLayout) panel.getLayout();
    fieldConstraints.gridheight = height;
    fieldConstraints.weighty = 10.0 * ((double) height);
    gridBag.setConstraints(editor, fieldConstraints);
    panel.add(editor);
    
    Dimension size = editor.getPreferredSize();
    accumulatedHeight += Math.max(MIN_EDITOR_HEIGHT,size.height) +
			 (2 * Y_INSET);
  }

  private void addDefaultRow(AttributeDialogInfo info,
			     Panel panel, 
			     String text,
			     Object value,
			     String label)
  {
    if (text == null)
      text =  "<NO-TEXT-FOR-ATTRIBUTE>";
    int height = getTextHeight(text);
    addLabel(panel, label, height);
    Item subItem = (value instanceof Item) ? ((Item) value) : null;
    AttributeTextArea textArea 
      = addField(info, panel, text, height, false, subItem);
    
    if (info.isValueReadable) {
      textAreas.addElement(textArea);
      textAreaInfos.addElement(info);
    }
  }

  private int lookupTextAreaIndex(Symbol attributeName,
					   Symbol classQualifier)
  {
    int i,size = textAreaInfos.size();
    for (i=0; i<size; i++)
      {
	AttributeDialogInfo info 
	  = (AttributeDialogInfo)textAreaInfos.elementAt(i);
	if (info.attributeName.equals(attributeName))
	  {
	    return i;
	  }
      }
    return -1;
  }

  private void addLabel(Panel panel, String string, int height)
  {
    GridBagLayout gridBag = (GridBagLayout) panel.getLayout();
    StringBuffer buffer = 
      new StringBuffer(string.replace('-',' ').toLowerCase());
    buffer.append(':');
    buffer.setCharAt(0,Character.toUpperCase(buffer.charAt(0)));
    Label label = new Label(buffer.toString(), Label.RIGHT);
    labelConstraints.gridheight = height;
    labelConstraints.weighty = (double) height;
    gridBag.setConstraints(label, labelConstraints);
    panel.add(label);
  }

  private int getTextHeight(String text)
  {
    StringTokenizer tokenizer = new StringTokenizer(text,"\n");
    return 1 + tokenizer.countTokens();
  }

  private AttributeTextArea addField(AttributeDialogInfo info,
				     Panel panel, String text,
				     int height, boolean hasSubEditor,
				     Item subItem)
  {
    AttributeTextArea field = new AttributeTextArea(text,info,item,
						    userMode,connection,isModal,
						    subItem,locale);
    GridBagLayout gridBag = (GridBagLayout) panel.getLayout();

    if (hasSubEditor)
      {
	Button button = new Button("...");
	complexFieldConstraints.gridheight = height;
	complexFieldConstraints.weighty = (double) height;
	gridBag.setConstraints(field, complexFieldConstraints);
	buttonConstraints.gridheight = height;
	buttonConstraints.weighty = (double) height;
	gridBag.setConstraints(button, buttonConstraints);
	panel.add(field);
	panel.add(button);
      }
    else
      {
	fieldConstraints.gridheight = height;
	fieldConstraints.weighty = 10.0 * ((double) height);
	gridBag.setConstraints(field, fieldConstraints);
	panel.add(field);
      }
    // Call getPreferredSize after textArea has parent
    Dimension size = field.getPreferredSize();
    accumulatedHeight += (size.height + (2 * Y_INSET));
    return field;
  }

  private void setUpItemProxy()
  {
    itemProxy = new ItemProxy();
    itemProxy.setProxy(item);
    itemProxy.setAutoUpload(true);

    int i,size = editors.length;
    SymbolVector attributeNames = new SymbolVector();
    for (i=0; i<size; i++)
      if (editors[i] instanceof AttributeEditor)
	{
	  Component editor = editors[i];
	  Symbol attributeName = attributeInfos[i].attributeName;
	  attributeNames.addElement(attributeName);
	  AttributeEditor attributeEditor = (AttributeEditor)editor;
	  attributeEditor.setAttribute(attributeName);
	  if (editor instanceof ObjectUpdateListener)
	    itemProxy.addObjectUpdateListener((ObjectUpdateListener)editor);
	  if (attributeInfos[i].isValueWritable)
	    attributeEditor.addObjectChangeListener(itemProxy);
	}

    itemProxy.setAttributes(attributeNames);
    try { 
      itemProxy.download();
    } catch (Exception e)
      {
	System.out.println("Could not Download Attributes for Dialog");
	e.printStackTrace();
      }
  }

  @Override
  public void receivedInitialValues (ItemEvent e){}

  @Override
  public void itemModified (ItemEvent e)
  {
    Sequence denotation = e.getDenotation();
    if (denotation.size() > 0 &&
	denotation.elementAt(0) instanceof Structure)
      {
	Structure denotationElement = (Structure)denotation.elementAt(0);
	if (denotationElement.getAttributeValue(type_,null).equals(attribute_)) 
	  {
	    Symbol attributeName
	      = (Symbol)denotationElement.getAttributeValue(name_,null);
	    Symbol classQualifier
	      = (Symbol)denotationElement.getAttributeValue(classQualifier_,null);
	    String newText;
	    int textAreaIndex
	      = lookupTextAreaIndex(attributeName,classQualifier);
	    
	    if (textAreaIndex != -1) {
	      newText = getAttributeText((AttributeDialogInfo)textAreaInfos.
					 elementAt(textAreaIndex));
	      AttributeTextArea textArea
		= (AttributeTextArea) textAreas.elementAt(textAreaIndex);
	      textArea.setText(newText);
	    }
	    try {
	      itemProxy.fireAttributeUpdate(attributeName);
	    } catch (Exception exception) {
	      System.out.println("Could not Download Attributes for Dialog");
	      exception.printStackTrace();
	    }
	  }
      }
  }

  private String getAttributeText(AttributeDialogInfo info)
  {
    Sequence request = new Sequence();
    request.addElement(info.denotation);
    Sequence result = getAttributeTexts(request);
    if (result != null)
      return (String) result.elementAt(0);
    else
      return null;
  }

  @Override
  public void itemDeleted (ItemEvent e)
  {
    cleanup(false);
  }

  void cleanup(boolean commitChanges)
  {
    try {
      item.removeItemListener(this);
    } catch (G2AccessException e) {
      e.printStackTrace();
    }
    
    // Reset the ItemProxy and the item
    itemProxy.setProxy (null);
    
    // Try to be environment-friendly and help out the GarbageCollector.
    item = null;
    itemProxy = null;
    editors = null;
    attributeInfos = null;
    connection = null;

    setVisible(false);
    dispose();
  }

  //This is  workaround for bug HQ-2033348: T2 properties dialog text fields display
  // strange (first chars clipped); This is called from DialogManager.
  private static boolean textAreaIsBuggy = true;
  static {
    try {
      textAreaIsBuggy = (System.getProperty ("os.name").toLowerCase().indexOf ("windows") >= 0);
    } catch (Exception e) {
    }
  }
  public void doHackForAWTTextComponentBug(){
    if (textAreaIsBuggy) {
      for (int i=0; i<editors.length; i++){
	if (editors[i] instanceof java.awt.TextComponent)
	  ((java.awt.TextComponent)editors[i]).setCaretPosition(0);
      }
    }
  }

  class AttributesDialogAdapter extends WindowAdapter
  {
    GenericAttributesDialog dialog;
    
    AttributesDialogAdapter(GenericAttributesDialog dialog)
    {
      this.dialog = dialog;
    }
    
    @Override
    public void windowClosing(WindowEvent e)
    {
      dialog.cleanup(false);
    }
  }

}

