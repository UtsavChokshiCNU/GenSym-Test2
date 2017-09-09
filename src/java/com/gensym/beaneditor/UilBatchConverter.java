package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.Button;
import java.awt.Frame;
import java.awt.Color;
import java.awt.Font;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.OutputStream;
import java.io.IOException;
import java.io.FileNotFoundException;
import java.lang.reflect.Method;
import java.util.Enumeration;
import java.util.Vector;
import javax.swing.UIManager;
import javax.swing.BoundedRangeModel;
import javax.swing.JLabel;
import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.controls.*;
import com.gensym.uilcontrols.*;
import com.gensym.beansruntime.StringVector;
import com.gensym.files.URLFile;
import com.gensym.ntw.files.*;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Sorter;
import com.gensym.util.UnexpectedException;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.classes.SymbolArray;
import com.gensym.classes.G2List;
import com.gensym.classes.G2Array;
import com.gensym.classes.Procedure;
import com.gensym.classes.modules.uilroot.*;
import com.gensym.classes.modules.uillib.*;
import com.gensym.classes.modules.uildefs.*;
import com.gensym.classes.modules.uilsa.*;
import com.gensym.classes.modules.uilcombo.*;
import com.gensym.classes.modules.uilslide.*;

public class UilBatchConverter extends GensymApplication{

  private static final Symbol DIMENSION_ = Symbol.intern("DIMENSION");
  private static final Symbol CENTER_X_ = Symbol.intern("CENTER-X");
  private static final Symbol CENTER_Y_ = Symbol.intern("CENTER-Y");
  private static final Symbol WIDTH_ = Symbol.intern("WIDTH");
  private static final Symbol HEIGHT_ = Symbol.intern("HEIGHT");
  private static final Symbol COMPONENTS_ = Symbol.intern("COMPONENTS");
  private static final Symbol TITLE_HEIGHT_ = Symbol.intern("TITLE-HEIGHT");
  private static final Symbol TITLE_ = Symbol.intern("TITLE");

  private static final Integer ZERO = new Integer(0);

  private static final Symbol UIL_GET_LABEL_TEXT_ = Symbol.intern ("UIL-GET-LABEL-TEXT");
  private static final Symbol UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_ = Symbol.intern ("UPP-GET-IDEAL-SELECTION-BOX-BOUNDS");
  private static final Symbol UPP_GET_RELATED_BOX_CONNECTOR_ = Symbol.intern ("UPP-GET-RELATED-BOX-CONNECTOR")
;
  private static final Symbol UPP_GET_RELATED_LINE_SEPARATOR_ = Symbol.intern ("UPP-GET-RELATED-LINE-SEPARATOR");
  private static final Symbol LEFT_TO_RIGHT_ = Symbol.intern("LEFT-TO-RIGHT");

  private static final int DEFAULT_INDICATOR_WIDTH = 10;
  private static final int DEFAULT_INDICATOR_HEIGHT = 10;

  private static final Symbol[] UNSUPPORTED_SYSTEM_ATTRIBUTES = new Symbol[]{
      Symbol.intern("ITEM-X-POSITION"),
      Symbol.intern("ITEM-Y-POSITION"),
      Symbol.intern("ITEM-WIDTH"),
      Symbol.intern("ITEM-HEIGHT"),
      Symbol.intern("LAST-RECORDED-VALUE"),
      Symbol.intern("ARRAY-LENGTH"),
      Symbol.intern("NAMES")};

  private static final boolean debug = false;

  private G2Access connection;
  private BufferedReader inFile;
  private String outputReposName;
  private Class staticClass;
  private BeanCanvas canvas;

  private Vector dialogIDs;
  private Vector actionArrayNames;

  private UILDialogProxy dlgProxy;  private int originX, originY;
  private int verticalOffset;
  private Vector conversionInfo = new Vector();
  //private int counter = 0;

  private UilBatchConverter(String[] commandLineArgs){
    super(commandLineArgs);
  }

  private static final Symbol UIL_GET_MASTER_DIALOG_ = Symbol.intern("UIL-GET-MASTER-DIALOG");
  private static final Symbol UIL_ACTION_DESCRIPTION_ARRAY_ = Symbol.intern("UIL-ACTION-DESCRIPTION-ARRAY");

  private void doConversion(String host, String port, 
			    String inputFileName, String outputReposName, 
			    String callbackClassName) throws G2AccessException, FileNotFoundException,
                                                             IOException, ClassNotFoundException{
    connection = G2Gateway.getOrMakeConnection(host, port);
    FileReader fileIn = new FileReader(inputFileName);
    inFile = new BufferedReader(fileIn);
    if (outputReposName == null)
      this.outputReposName = System.getProperty ("com.gensym.beaneditor.uilconversionrepository", null);
    else
      this.outputReposName = outputReposName;
    staticClass = Class.forName(callbackClassName);
    dialogIDs = new Vector();
    actionArrayNames = new Vector();

    Frame f = new Frame();
    ProgressFrame progressDlg = new ProgressFrame(f, "Setting up conversion...");
    progressDlg.addWindowListener(new WindowAdapter(){
      @Override
      public void windowClosed (WindowEvent we) {
    	  System.exit(0);
      }
      
      @Override
      public void windowClosing (WindowEvent we) {
    	  System.exit(0);
      }
    });
    progressDlg.setTitle("UIL Dialog Batch Conversion");
    progressDlg.setSize(400, 200);
    progressDlg.setVisible(true);
    JLabel label = progressDlg.getLabel();
    BoundedRangeModel model = progressDlg.getProgressBar().getModel();
    model.setMinimum(0);
    readDataFile();
    model.setMaximum(dialogIDs.size());
    for (int i=0; i<dialogIDs.size(); i++){
      String id = (String)dialogIDs.elementAt(i);
      label.setText("Converting \""+id+"\"...");
      Object result = connection.callRPC(UIL_GET_MASTER_DIALOG_, new Object[] {id});
      if (result instanceof UilTailoredDialog){
	UilTailoredDialog dlg = (UilTailoredDialog)result;
	String actionArrayName = (String)actionArrayNames.elementAt(i);
	UilActionDescriptionArray array = null;
	if (actionArrayName != null && !actionArrayName.equals(""))
	  array = (UilActionDescriptionArray)connection.getUniqueNamedItem(UIL_ACTION_DESCRIPTION_ARRAY_, Symbol.intern(actionArrayName.toUpperCase()));
	convertDialog(dlg, array);
	saveResource(id);
      }
      else{
	conversionInfo.addElement("------------------------------------------------------------------------");
	conversionInfo.addElement("Dialog id: \""+id+"\"");
	conversionInfo.addElement("Unable to find dialog with id="+id);
      }
      model.setValue(i+1);
    }
    conversionInfo.addElement("------------------------------------------------------------------------");
    conversionInfo.addElement("Conversion completed with "+callbacks.size()+" translations required.");
    label.setText("Writing log information...");
    writeLog();
    label.setText("Conversion is complete.");
  }

  private void readDataFile() throws IOException{
    String line;
    while ((line = inFile.readLine()) != null){
      dialogIDs.addElement(line);
      line = inFile.readLine();
      if (line == null) break;
      actionArrayNames.addElement(line);
    }
    if (actionArrayNames.size() < dialogIDs.size())
      actionArrayNames.addElement(null);
    inFile.close();
  }

  private void saveResource(String id) throws IOException{
    addBeansToCanvas();
    T2URLDirectoryModel directoryModel 
      = new T2URLDirectoryModel(true,false,true,null,null);
    URLFile urlFile = directoryModel.makeFileFromPath(outputReposName+"/"+id+".ser");
    OutputStream os = urlFile.getOutputStream();
    canvas.save(os);
    os.close();
  }

  private void writeLog(){
    for (int i=0; i<conversionInfo.size(); i++){
      Object element = conversionInfo.elementAt(i);
      if (element instanceof String)
	System.out.println(element);
      else{
	Vector info = (Vector)element;
	for (int j=0; j<info.size(); j++)
	  System.out.println(info.elementAt(j));
      }  
    }

    for (int i=0; i<callbacks.size(); i++)
      System.out.println(callbacks.elementAt(i));
  }

  private void convertDialog(UilTailoredDialog dialog, 
			     UilActionDescriptionArray launchArray) throws G2AccessException{
    canvas = new BeanCanvas();
    components.removeAllElements();
    commandButtons.removeAllElements();
    otherComponents.removeAllElements();
    Structure layout = dialog.uppGetDialogLayout();
    Structure dimension = (Structure)layout.getAttributeValue(DIMENSION_, null);
    if (dimension != null){
      Integer centerX = (Integer)dimension.getAttributeValue(CENTER_X_, ZERO);
      Integer centerY = (Integer)dimension.getAttributeValue(CENTER_Y_, ZERO);
      Integer width = (Integer)dimension.getAttributeValue(WIDTH_, ZERO);
      Integer height = (Integer)dimension.getAttributeValue(HEIGHT_, ZERO);
      Sequence components = (Sequence)layout.getAttributeValue(COMPONENTS_, null);
      if (components != null){
	originX = centerX.intValue() - (width.intValue() / 2);
	originY = centerY.intValue() + (height.intValue() / 2);
	verticalOffset = -((Integer)layout.getAttributeValue(TITLE_HEIGHT_, ZERO)).intValue();

	conversionInfo.addElement("------------------------------------------------------------------------");
	conversionInfo.addElement("Dialog id: \""+dialog.getId()+"\"");
	conversionInfo.addElement("Action array: "+(launchArray == null ? "<none>" : launchArray.getNames().toString()));
	conversionInfo.addElement("Static classs: "+(staticClass == null ? "<none>" : staticClass.getName()));
	conversionInfo.addElement("\n");

	ItemProxy proxy = new ItemProxy();
	proxy.setAutoUpload(false);
	proxy.setAutoDownload(false);
	proxy.setAttributes(new SymbolVector());
	addBean(proxy, width.intValue()+70, height.intValue()+10, 50, 50);//maybe add after resize?

	dlgProxy = new UILDialogProxy(dialog, launchArray, staticClass);
	//dlgProxy.setTitle((String)layout.getAttributeValue(TITLE_, null));
	dlgProxy.setProxy(proxy);
	checkDialog(dlgProxy);
	addBean(dlgProxy, width.intValue()+10, height.intValue()+10, 50, 50);

	int canvasWidth = width.intValue();
	int canvasHeight = height.intValue() + verticalOffset;
	canvas.setContainerSize(canvasWidth, canvasHeight);
	Rectangle logicalBounds = canvas.getLogicalBounds();
	if (canvasWidth > logicalBounds.width)
	  canvas.growLogical(canvasWidth - logicalBounds.width + 10, true, false);
	if (canvasHeight > logicalBounds.height)
	  canvas.growLogical(canvasHeight - logicalBounds.height + 10, false, false);

	Enumeration controls = components.elements();
	while (controls.hasMoreElements()){
	  Item item = (Item)controls.nextElement();
	  convertControl(item);
	}
      }
    }
  }

  private static final String ACTION_SIGNATURE = "(UilClientDialog dlg, Object dlgLauncher, UiClientItem win, Object origDlgLauncher, Object actionQueue)";

  private void checkDialog(UILDialogProxy dlg){
    Vector info = new Vector();
    checkSourceAndTargetObject(dlg, info);
    checkPseudoMethods(dlg, info);
    if (dlg.customLaunchActions()){
      UilCallback[] actions = dlg.getLaunchActions();
      for (int i=0; i<actions.length; i++)
	if (!actions[i].isDefaultCallback())
	  generateMessageIfNecessary("the uil-action-specifics of "+dlg.getLaunchArrayName().toString(), 
				     actions[i].getName(), UilClientConstants.ACTION_ARG_TYPES,
				     ACTION_SIGNATURE, info);
    }
    if (info.size() > 0)
      addInfoForControl(dlg, info);
  }

  private void addInfoForControl(Object control, Vector info){
    info.insertElementAt("Control: "+control.toString(), 0);
    conversionInfo.addElement(info);
    //counter = counter + (info.size() - 1);
  }

  private void convertControl(Item item) throws G2AccessException{
    Component component = null;
    if (item instanceof UilRadioBox){
      UilRadioBox radioBox = (UilRadioBox)item;
      component = convertToUILRadiobox(radioBox);
      convertLabel(radioBox, false);
    }
    else if (item instanceof UilCheckBox){
      UilCheckBox checkbox = (UilCheckBox)item;
      component = convertToUILCheckbox(checkbox);
      convertLabel(checkbox, false);
    }
    else if (item instanceof UilIconToggleButton)
      component = convertToUILToggleButton((UilIconToggleButton)item);
    else if (item instanceof UilTextToggleButton)
      component = convertToUILToggleButton((UilTextToggleButton)item);
    else if (item instanceof UilIconPushbutton)
      component = convertToUILPushbutton((UilIconPushbutton)item);
    else if (item instanceof UilTextPushbutton)
      component = convertToUILPushbutton((UilTextPushbutton)item);
    else if (item instanceof UilScrollArea)
      component = convertToUILScrollArea((UilScrollArea)item);
    else if (item instanceof UilBoxBorderLeft)
      component = convertToUILBorder((UilBoxBorder)item);
    else if (item instanceof UilLineSeparatorLeft)
      component = convertToUILSeparator((UilLineSeparator)item);
    else if (item instanceof UilSlider){
      component = null;
      conversionInfo.addElement("Converting uil-sliders is not supported.\n");
    }
    else if (item instanceof UilDialogTitle){
      component = null;
      UILDialogTitle title = new UILDialogTitle((UilDialogTitle)item, staticClass);
      dlgProxy.addControl(title);
      dlgProxy.setTitle(title.getMessageContents());
    }
    else if (item instanceof UilText)
      component = convertToUILText((UilText)item);
    else if (item instanceof UilComboBox){
      component = null;
      conversionInfo.addElement("Converting uil-combo-boxes is not supported.\n");
    }
    else if (item instanceof UilSpinControlEntryBox){
      component = convertToUILSpinControl((UilSpinControlEntryBox)item);
      Component label = convertLabel((UilSpinControlEntryBox)item, true);
      if (label != null && component instanceof UILSpinControl && 
	  label instanceof com.gensym.widgets.TextWidget)
	((UILSpinControl)component).setLabelComponent((com.gensym.widgets.TextWidget)label);
    }
    else if (item instanceof UilEditBox){
      UilEditBox editBox = (UilEditBox)item;
      component = convertToUILEditBox(editBox);
      Component label = convertLabel(editBox, true);
      if (label != null && component instanceof UILEditBox && label instanceof com.gensym.widgets.TextWidget)
	((UILEditBox)component).setLabelComponent((com.gensym.widgets.TextWidget)label);
    }
    
    if (component != null){
      if (component instanceof UilClientItem)
	dlgProxy.addControl((UilClientItem)component);
      Rectangle bounds = computeBounds(item, component);
      addBean(component, bounds.x, bounds.y + verticalOffset, 
			   bounds.width, bounds.height);
    }
  }

  private static final Symbol UIL_MORE_ICON_PUSHBUTTON_ = Symbol.intern("UIL-MORE-ICON-PUSHBUTTON");

  private Rectangle computeBounds(Item item, Component component) throws G2AccessException{
    int x, y, width, height;
    if (item instanceof UilSelectionBox){
      Structure selectionBoxBounds = (Structure)connection.callRPC(UPP_GET_IDEAL_SELECTION_BOX_BOUNDS_,
								new Object[] {(UilSelectionBox)item});
      x = ((Integer)selectionBoxBounds.getAttributeValue(CENTER_X_, ZERO)).intValue();
      y = ((Integer)selectionBoxBounds.getAttributeValue(CENTER_Y_, ZERO)).intValue();
      width = ((Integer)selectionBoxBounds.getAttributeValue(WIDTH_, ZERO)).intValue();
      height = ((Integer)selectionBoxBounds.getAttributeValue(HEIGHT_, ZERO)).intValue();
      x = x - (width / 2);
      y = y + (height / 2);
    }
    else if (item instanceof UilIconPushbutton || item instanceof UilTextPushbutton){
      boolean moreButton = false;
      if (item.isInstanceOfG2Class(UIL_MORE_ICON_PUSHBUTTON_)){
	moreButton = true;
	if (component instanceof Button){
	  Button button = (Button)component;
	  button.setLabel("...");
	  button.setFont(new Font("Monospaced", Font.BOLD, 12));
	}
      }
      x = item.getItemXPosition();
      y = item.getItemYPosition();
      width =  item.getItemWidth() - (moreButton ? 0 : DEFAULT_INDICATOR_WIDTH);
      height = item.getItemHeight() - (moreButton ? 0 : DEFAULT_INDICATOR_HEIGHT);
      x = x - (width / 2);
      y = y + (height / 2);
    }
    else if (item instanceof UilBoxBorder){
      UilBoxBorder right = 
	(UilBoxBorder)connection.callRPC(UPP_GET_RELATED_BOX_CONNECTOR_, new Object[]{item});
      x = item.getItemXPosition();
      y = right.getItemYPosition();
      int itemWidth = item.getItemWidth();
      int itemHeight = right.getItemHeight();
      x = x - (itemWidth / 2);
      y = y - (itemHeight /2);
      width = right.getItemXPosition() - x;
      height = y - item.getItemYPosition();
    }
    else if (item instanceof UilLineSeparator){
      UilLineSeparator right = (UilLineSeparator)connection.callRPC(UPP_GET_RELATED_LINE_SEPARATOR_, new Object[]{item});
      x = item.getItemXPosition();
      y = item.getItemYPosition();
      int itemWidth = item.getItemWidth();
      int itemHeight = item.getItemHeight();
      x = x - (itemWidth / 2);
      y = y - (itemHeight /2);
      //if left-to-right:
      if (LEFT_TO_RIGHT_.equals(((UilLineSeparator)item).getOrientation())){
	width = right.getItemXPosition() - x;
	height = 2;
      }
      else{
	width = 2;
	height = y - right.getItemYPosition();
      }
    }
    else{
      x = item.getItemXPosition();
      y = item.getItemYPosition();
      width =  item.getItemWidth();
      height = item.getItemHeight();
      x = x - (width / 2);
      y = y + (height / 2);
    }

    x = x - originX;
    y = -(y - originY);
    return new Rectangle(x, y, width, height);
  }

  private Vector components = new Vector();
  private Vector commandButtons = new Vector();
  private Vector otherComponents = new Vector();

  private void addBean(Object bean, int x, int y, int width, int height){
    if (bean instanceof Component){
      Component c = (Component)bean;
      c.setLocation(x, y);
      c.setSize(width, height);
      if (c.getBackground() == null){
	Preferences prefs = Preferences.currentPreferences;
	c.setBackground(prefs.getContainerBackgroundColor());
      }
      if (bean instanceof UilClientLineSeparator || bean instanceof UilClientBorder)
	otherComponents.addElement(bean);
      else if (bean instanceof UilClientPushbutton){
	UilClientPushbutton button = (UilClientPushbutton)bean;
	if (button.getUilDefaultedButton() || button.getUilCancelButton() || button.getUilUpdateButton())
	  commandButtons.addElement(button);
	else
	  components.addElement(button);
      }
      else
	components.addElement(bean);
    }
    else
      addBeanToCanvas(bean, x, y, width, height);
  }

  private void addBeansToCanvas(){
    try{      
      Component[] buttons = new Component[commandButtons.size()];
      commandButtons.copyInto(buttons);
      Class componentSorterClass = com.gensym.beaneditor.ComponentSorterSupport.class;
      Class[] args = new Class[]{ Component.class, Component.class};
      Method compareMethod = componentSorterClass.getMethod("compareHorizontallyFirst", args);
      Sorter.sort(buttons, Sorter.DESCENDING, compareMethod);
      for (int i=0; i<buttons.length; i++)
	addBeanToCanvas(buttons[i]);

      Component[] widgets = new Component[components.size()];
      components.copyInto(widgets);
      compareMethod = componentSorterClass.getMethod("compareVerticallyFirst", args);
      Sorter.sort(widgets, Sorter.DESCENDING, compareMethod);
      for (int i=0; i<widgets.length; i++)
	addBeanToCanvas(widgets[i]);
      
      Component[] other = new Component[otherComponents.size()];
      otherComponents.copyInto(other);
      for (int i=0; i<other.length; i++)
	addBeanToCanvas(other[i]);
    }
    catch(NoSuchMethodException ex){
      throw new UnexpectedException(ex);
    }
  }

  private void addBeanToCanvas(Component bean){
    Rectangle bounds = bean.getBounds();
    addBeanToCanvas(bean, bounds.x, bounds.y, bounds.width, bounds.height);
  }
  
  private void addBeanToCanvas(Object bean, int x, int y, int width, int height){
    Wrapper wrapper = new Wrapper(Color.gray, bean.getClass(), x, y, width, height); 
    canvas.addElement(wrapper);
    wrapper.bean = bean;
    if (bean instanceof Component)
      canvas.addElement((Component)bean);
    Dimension unconstrainedSize = wrapper.getSize();
    wrapper.setSize(unconstrainedSize.width, unconstrainedSize.height);
    wrapper.ensureBeanBounds();
  }

  /*
  private void addComponentToCanvas(Object bean, int x, int y, int width, int height){
    Wrapper wrapper = new Wrapper(Color.gray, bean.getClass(), x, y, width, height); 
    canvas.addElement(wrapper);
    wrapper.bean = bean;
    if (bean instanceof Component){
      Component c = (Component)bean;
      c.setLocation(x, y);
      if (c.getBackground() == null){
	Preferences prefs = Preferences.currentPreferences;
	c.setBackground(prefs.getContainerBackgroundColor());
      }
      canvas.addElement(c);
    }
    Dimension unconstrainedSize = wrapper.getSize();
    wrapper.setSize(unconstrainedSize.width, unconstrainedSize.height);
    wrapper.ensureBeanBounds();
  }
  */

  private Component convertToUILRadiobox(UilRadioBox uilRadioBox) throws G2AccessException{
    UILRadioBox radioBox = new UILRadioBox(uilRadioBox, staticClass);
    checkSelectionBox(radioBox);
    return radioBox;
  }

  private Component convertToUILCheckbox(UilCheckBox uilCheckBox) throws G2AccessException{
    UILCheckBox checkBox = new UILCheckBox(uilCheckBox, staticClass);
    checkSelectionBox(checkBox);
    return checkBox;
  }

  private void checkSelectionBox(UILSelectionBox selectionBox){
    Vector info = new Vector();
    checkSourceAndTargetObject(selectionBox, info);
    checkPseudoMethods(selectionBox, info);
    if (info.size() > 0)
      addInfoForControl(selectionBox, info);

    UilClientStateButton[] buttons = selectionBox.getMembers();
    for (int i=0; i<buttons.length; i++)
      checkStateButton((UILStateButton)buttons[i]);
  }

  private Component convertToUILToggleButton(UilIconToggleButton uilToggleButton) throws G2AccessException{
    UILToggleButton toggleButton = new UILToggleButton(uilToggleButton, staticClass);
    checkStateButton(toggleButton);
    return toggleButton;
  }

  private Component convertToUILToggleButton(UilTextToggleButton uilToggleButton) throws G2AccessException{
    UILToggleButton toggleButton = new UILToggleButton(uilToggleButton, staticClass);
    checkStateButton(toggleButton);
    return toggleButton;
  }

  private static final String CALLBACK_SIGNATURE = "(UilClientButton button, UiClientItem win, UilClientDialog dlg)";

  private void checkStateButton(UILStateButton button){
    Vector info = new Vector();
    checkSourceAndTargetObject(button, info);
    checkPseudoMethods(button, info);
    if (!(UilClientConstants.UIL_HANDLE_BUTTON_METHOD_.equals(button.getUilHandlerMethod())))
	generateMessageIfNecessary("uil-handler-method", button.getUilHandlerMethod(), "Overriding the uil-handler-method is not supported.", info);
    Symbol callback = button.getCallback();
    if (!UilClientConstants.UIL_DO_NOTHING_.equals(callback))
	generateMessageIfNecessary("callback", callback, UilClientConstants.CALLBACK_ARG_TYPES,
				   CALLBACK_SIGNATURE, info); 
    if (info.size() > 0)
      addInfoForControl(button, info);
  }

  private Component convertToUILPushbutton(UilIconPushbutton pushbutton) throws G2AccessException{
    UILPushbutton button = new UILPushbutton(pushbutton, staticClass);
    checkPushbutton(button);
    return button;
  }

  private Component convertToUILPushbutton(UilTextPushbutton pushbutton) throws G2AccessException{
    UILPushbutton button = new UILPushbutton(pushbutton, staticClass);
    checkPushbutton(button);
    return button;
  }

  private void checkPushbutton(UILPushbutton button){
    Vector info = new Vector();
    checkSourceAndTargetObject(button, info);
    checkPseudoMethods(button, info);
    if (!(UilClientConstants.UIL_HANDLE_BUTTON_METHOD_.equals(button.getUilHandlerMethod())))
      generateMessageIfNecessary("uil-handler-method", button.getUilHandlerMethod(), "Overriding the uil-handler-method is not supported.", info);
    Symbol callback = button.getCallback();
    if (!UilClientConstants.UIL_CONTROL_DIALOG_CALLBACK_.equals(callback) && 
	!UilClientConstants.UIL_DO_NOTHING_.equals(callback))
      generateMessageIfNecessary("callback", callback,  UilClientConstants.CALLBACK_ARG_TYPES, 
				 CALLBACK_SIGNATURE, info); 
    UilCallback[] actions = button.getActions();
    if (actions != null){
      for (int i=0; i<actions.length; i++){
	if (!actions[i].isDefaultCallback())
	  generateMessageIfNecessary("uil-action-description", actions[i].getName(), 
				     UilClientConstants.ACTION_ARG_TYPES, ACTION_SIGNATURE, info); 
      }
    }
    if (info.size() > 0)
      addInfoForControl(button, info);
  }

  private Component convertToUILScrollArea(UilScrollArea uilScrollArea) throws G2AccessException{
    UILScrollArea scroll = new UILScrollArea(uilScrollArea, staticClass);
    checkScrollArea(scroll);
    return scroll;
  }

  private static final String MESSAGE_SELECTION_METHOD_SIGNATURE = "(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, UiClientItem win)";
  private static final String MESSAGE_UNSELECTION_METHOD_SIGNATURE = "(UilClientMessageObject msgObject, UilClientScrollArea scrollArea, UiClientItem win)";

  private void checkScrollArea(UILScrollArea scroll){
    Vector info = new Vector();
    checkSourceAndTargetObject(scroll, info);
    checkPseudoMethods(scroll, info);
    if (!UilClientConstants.UIL_MESSAGE_SELECTION_METHOD_.equals(scroll.getUilMessageSelectionMethod()))
      generateMessageIfNecessary("uil-message-selection-method", scroll.getUilMessageSelectionMethod(),
				 UilClientConstants.SELECTION_ARG_TYPES, MESSAGE_SELECTION_METHOD_SIGNATURE,
				 info);
    if (!UilClientConstants.UIL_MESSAGE_UNSELECTION_METHOD_.equals(scroll.getUilMessageUnselectionMethod()))
      generateMessageIfNecessary("uil-message-unselection-method", scroll.getUilMessageUnselectionMethod(), 
				 UilClientConstants.SELECTION_ARG_TYPES, //selection & unselection are the same
				 MESSAGE_UNSELECTION_METHOD_SIGNATURE, info);
    if (info.size() > 0)
      addInfoForControl(scroll, info);
    
  }

  private static final Symbol QUANTITY_ = Symbol.intern("QUANTITY");
  private static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");

  private Component convertToUILSeparator(UilLineSeparator item) throws G2AccessException{
    UILSeparator separator = new UILSeparator(item, staticClass);
    Vector info = new Vector();
    checkPseudoMethods(separator, info);
    if (info.size() > 0)
      addInfoForControl(separator, info);
    return separator;
  }

  private Component convertToUILBorder(UilBoxBorder item) throws G2AccessException{
    UILBorder border = new UILBorder(item, staticClass);
    Vector info = new Vector();
    checkPseudoMethods(border, info);
    if (info.size() > 0)
      addInfoForControl(border, info);
    return border;
  }

  private Component convertToUILText(UilText text) throws G2AccessException{
    UILText txt = new UILText(text, staticClass);
    checkText(txt);
    return txt;
  }

  private void checkText(UILText label){
    Vector info = new Vector();
    checkSourceAndTargetObject(label, info);
    checkPseudoMethods(label, info);
    if (!label.getUilFormatSpecification().equals(UilClientConstants.UNSPECIFIED_)){
      try{
	UilFormatSpecificationClass formatSpec = (UilFormatSpecificationClass)connection.getUniqueNamedItem(UilClientConstants.UIL_FORMAT_SPECIFICATION_CLASS_, label.getUilFormatSpecification());
	Symbol type = (Symbol)formatSpec.getUilFormatType();
	if (type.equals(QUANTITY_)){
	  Symbol format = (Symbol)formatSpec.getUilFloatFormatOutputFormat();
	  if (!format.equals(DEFAULT_))
	    generateMessageIfNecessary("uil-float-format-output-format of "+label.getUilFormatSpecification(), type, "Non-default quantity format options are not supported", info);
	}
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
	//ignore
      }
    }
    if (info.size() > 0)
      addInfoForControl(label, info);
  }
  
  private Component convertToUILEditBox(UilEditBox uilEditBox) throws G2AccessException{
    UILEditBox editBox = new UILEditBox(uilEditBox, staticClass);
    checkEditBox(editBox);
    return editBox;
  }

  private static final String EDIT_BOX_SELECTION_METHOD_SIGNATURE ="(UilClientEditBox editBox, UilClientDialog dlg, UiClientItem win)";
  private static final String EDIT_BOX_UNSELECTION_METHOD_SIGNATURE ="(UilClientEditBox editBox, UilClientDialog dlg, UiClientItem win, Boolean committed)";


  private void checkEditBox(UILEditBox editBox){
    Vector info = new Vector();
    checkSourceAndTargetObject(editBox, info);
    checkPseudoMethods(editBox, info);

    if (!UilClientConstants.UIL_EDIT_BOX_SELECTION_METHOD_.equals(editBox.getUilMessageSelectionMethod()))
	generateMessageIfNecessary("uil-message-selection-method", 
				   editBox.getUilMessageSelectionMethod(),
				   UilClientConstants.EDIT_BOX_SELECTION_ARG_TYPES,
				   EDIT_BOX_SELECTION_METHOD_SIGNATURE, info);
    if (!UilClientConstants.UIL_EDIT_BOX_UNSELECTION_METHOD_.equals(editBox.getUilMessageUnselectionMethod()))
	generateMessageIfNecessary("uil-message-unselection-method", 
				   editBox.getUilMessageUnselectionMethod(),
				   UilClientConstants.EDIT_BOX_UNSELECTION_ARG_TYPES,
				   EDIT_BOX_UNSELECTION_METHOD_SIGNATURE, info);

    if (!editBox.getUilFormatSpecification().equals(UilClientConstants.UNSPECIFIED_)){
      try{
	UilFormatSpecificationClass formatSpec = (UilFormatSpecificationClass)connection.getUniqueNamedItem(UilClientConstants.UIL_FORMAT_SPECIFICATION_CLASS_, editBox.getUilFormatSpecification());
	Symbol type = (Symbol)formatSpec.getUilFormatType();
	if (type.equals(QUANTITY_)){
	  Symbol format = (Symbol)formatSpec.getUilFloatFormatOutputFormat();
	  if (!format.equals(DEFAULT_))
	    generateMessageIfNecessary("uil-float-format-output-format of "+editBox.getUilFormatSpecification(), format, "Non-default quantity format options are not supported", info);
	}
	Symbol formatType = (Symbol)formatSpec.getUilFormatType();
	if (formatType.equals(UilClientConstants.DATE_) || formatType.equals(UilClientConstants.TIME_) || formatType.equals(UilClientConstants.PROCEDURE_CALL_) ||
	    formatType.equals(UilClientConstants.FUNCTION_CALL_))
	  generateMessageIfNecessary("uil-format-type of "+editBox.getUilFormatSpecification(), formatType, "Date, time, procedure-call and function-call format types are not supported.", info);
	if (!UilClientConstants.UNSPECIFIED_.equals(formatSpec.getUilValidationFailureMethod()))
	  generateMessageIfNecessary("uil-validation-failure-method of "+editBox.getUilFormatSpecification(), formatSpec.getUilValidationFailureMethod(), "Validation failure method is not supported.", info);
	G2Array array;
	array = (G2Array)formatSpec.getUilArrayOfLegalSymbolicValues();
	if (array.getG2ArraySequence().size() > 0)
	  generateMessageIfNecessary("uil-array-of-legal-symbolic-values of "+formatSpec.getUilValidationFailureMethod(), "<contains values>", "Symbolic legal values are not supported.", info);
	array = (G2Array)formatSpec.getUilArrayOfLegalTextValues();
	if (array.getG2ArraySequence().size() > 0)
	  generateMessageIfNecessary("uil-array-of-legal-text-values of "+formatSpec.getUilValidationFailureMethod(), "<contains values>", "Text legal values are not supported.", info);
	array = (G2Array)formatSpec.getUilArrayOfLegalIntegerValues();
	if (array.getG2ArraySequence().size() > 0)
	  generateMessageIfNecessary("uil-array-of-legal-integer-values of "+formatSpec.getUilValidationFailureMethod(), "<contains values>", "Integer legal values are not supported.", info);
	array = (G2Array)formatSpec.getUilArrayOfLegalQuantityValues();
	if (array.getG2ArraySequence().size() > 0)
	  generateMessageIfNecessary("uil-array-of-legal-quantity-values of "+formatSpec.getUilValidationFailureMethod(), "<contains values>", "Quantity legal values are not supported.", info);
	
      }
      catch(G2AccessException ex){
	Trace.exception(ex);
	//ignore
      }
    }
    if (info.size() > 0)
      addInfoForControl(editBox, info);
  }

  private Component convertToUILSpinControl(UilSpinControlEntryBox uilSpinControl) throws G2AccessException{
    UILSpinControl spinControl = new UILSpinControl(uilSpinControl, staticClass);
    checkSpinControl(spinControl);
    return spinControl;
  }

  private void checkSpinControl(UILSpinControl spinControl){
    Vector info = new Vector();
    checkSourceAndTargetObject(spinControl, info);
    checkPseudoMethods(spinControl, info);

    if (!UilClientConstants.UIL_EDIT_BOX_SELECTION_METHOD_.equals(spinControl.getUilMessageSelectionMethod()))
	generateMessageIfNecessary("uil-message-selection-method", 
				   spinControl.getUilMessageSelectionMethod(),
				   UilClientConstants.EDIT_BOX_SELECTION_ARG_TYPES,
				   EDIT_BOX_SELECTION_METHOD_SIGNATURE, info);
    if (!UilClientConstants.UIL_EDIT_BOX_UNSELECTION_METHOD_.equals(spinControl.getUilMessageUnselectionMethod()))
	generateMessageIfNecessary("uil-message-unselection-method", 
				   spinControl.getUilMessageUnselectionMethod(),
				   UilClientConstants.EDIT_BOX_UNSELECTION_ARG_TYPES,
				   EDIT_BOX_UNSELECTION_METHOD_SIGNATURE, info);
    if (info.size() > 0)
      addInfoForControl(spinControl, info);
  }

  private Component convertLabel(Item item, boolean attached) throws G2AccessException{    
    Object result = connection.callRPC(UIL_GET_LABEL_TEXT_, new java.lang.Object[] {item});
    if (result instanceof UilText){
      UilText label = (UilText)result;
      UILText g2label = (UILText) convertToUILText(label);
      if (attached)
	g2label.setAlignment(g2label.RIGHT);
      Rectangle bounds = computeBounds(label, g2label);
      int width, height;
      if (attached){
	width = bounds.width;
	height = bounds.height;
      }
      else{
	Dimension size = g2label.getPreferredSize();
	width = size.width;
	height = size.height;
      }
      addBean(g2label, bounds.x, bounds.y + verticalOffset, width, height);
      return g2label;
    }
    return null;
  }

  private void checkSourceAndTargetObject(UilClientItem grobj, Vector info){
    Object sourceObject = grobj.getUilEventSourceObject();
    if (!UilClientConstants.INITIATING_OBJECT_.equals(sourceObject) && 
	!UilClientConstants.UNSPECIFIED_.equals(sourceObject))
      generateMessageIfNecessary("uil-event-source-object", sourceObject, "Only initiating-object is supported for uil-event-source-object.", info);
    if (grobj instanceof UilClientText) return;
    Object targetObject = grobj.getUilEventTargetObject();
    if (!UilClientConstants.INITIATING_OBJECT_.equals(targetObject) &&
	!UilClientConstants.UNSPECIFIED_.equals(targetObject))
      generateMessageIfNecessary("uil-event-target-object", targetObject, "Only initiating-object is supported for uil-event-target-object.", info);
  }

  private void checkSourceAndTargetObject(UilClientPushbutton grobj, Vector info){
  }

  private static final String ENABLE_METHOD_SIGNATURE= "(UilClientItem grobjOrGmres)";
  private static final String DISABLE_METHOD_SIGNATURE= "(UilClientItem grobjOrGrmes)";
  private static final String UPDATE_METHOD_SIGNATURE= "(UilClientItem grobjOrGrmes, UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, Object actionQueue)";
  private static final String CONCLUDE_METHOD_SIGNATURE= "(UilClientItem grobjOrGrmes, UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, Object actionQueue)";
  private static final String VALIDATE_METHOD_SIGNATURE= "(UilClientItem grobjOrGrmes, UiClientItem win, UilClientDialog dlg, Object buttonOrInitObj, Object actionQueue)";


  private void checkPseudoMethods(UilClientItem grobj, Vector info){
    Symbol callbackName = grobj.getUilEnableMethod();
    if (!UilClientConstants.UIL_ENABLE_GROBJ_METHOD_.equals(callbackName))
	generateMessageIfNecessary("uil-enable-method", callbackName,
				   UilClientConstants.ENABLE_ARG_TYPES, ENABLE_METHOD_SIGNATURE, info);
    callbackName = grobj.getUilDisableMethod();
    if (!UilClientConstants.UIL_DISABLE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-disable-method", callbackName, 
				 UilClientConstants.DISABLE_ARG_TYPES, DISABLE_METHOD_SIGNATURE, info);
    callbackName = grobj.getUilUpdateMethod();
    if (!UilClientConstants.UIL_UPDATE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-update-method", callbackName,  
				 UilClientConstants.UPDATE_ARG_TYPES, UPDATE_METHOD_SIGNATURE, info);
    callbackName = grobj.getUilInitializationMethod();
    if (!UilClientConstants.UIL_INITIALIZE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-initialize-method", callbackName, "Overriding uil-initialization-method is not supported.", info);
    callbackName = grobj.getUilDeleteMethod();
    if (!UilClientConstants.UIL_DELETE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-delete-method", callbackName, "Overriding uil-delete-method is not supported.", info);
    callbackName = grobj.getUilCloneMethod();
    if (!UilClientConstants.UIL_CLONE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-clone-method", callbackName, "Overriding uil-clone-method is not supported.", info);
    callbackName = grobj.getUilManageMethod();
    if (!UilClientConstants.UIL_MANAGE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-manage-method", callbackName, "Overriding uil-manage-method is not supported.", info);
    callbackName = grobj.getUilConfigurationMethod();
    if (!UilClientConstants.UIL_CONFIGURE_GROBJ_METHOD_.equals(callbackName))
      generateMessageIfNecessary("uil-configure-method", callbackName, "Overriding uil-configure-method is not supported.", info);
    
    if (grobj instanceof UilClientGrobj){
      UilClientGrobj clientGrobj = (UilClientGrobj)grobj;
      callbackName = clientGrobj.getUilConcludeMethod();
      if (!UilClientConstants.UIL_CONCLUDE_GROBJ_METHOD_.equals(callbackName)  && !(grobj instanceof UilClientPushbutton))
	generateMessageIfNecessary("uil-conclude-method", callbackName, 
				   UilClientConstants.CONCLUDE_ARG_TYPES,
				   CONCLUDE_METHOD_SIGNATURE, info);
      callbackName = clientGrobj.getUilValidationMethod();
      if (!UilClientConstants.UIL_VALIDATE_GROBJ_METHOD_.equals(callbackName))
	generateMessageIfNecessary("uil-validate-grobj", callbackName,  
				   UilClientConstants.VALIDATION_ARG_TYPES,
				   VALIDATE_METHOD_SIGNATURE, info);
    }
    if (grobj instanceof UilClientEditBox){
      UilClientEditBox clientEB = (UilClientEditBox)grobj;
      callbackName = clientEB.getUilConcludeMethod();
      if (!UilClientConstants.UIL_CONCLUDE_GROBJ_METHOD_.equals(callbackName))
	generateMessageIfNecessary("uil-conclude-method", callbackName, 
				   UilClientConstants.CONCLUDE_ARG_TYPES,
				   CONCLUDE_METHOD_SIGNATURE, info);
      callbackName = clientEB.getUilValidationMethod();
      if (!UilClientConstants.UIL_VALIDATE_GROBJ_METHOD_.equals(callbackName))
	generateMessageIfNecessary("uil-validate-grobj", callbackName,  
				   UilClientConstants.VALIDATION_ARG_TYPES,
				   VALIDATE_METHOD_SIGNATURE, info);
    }
  }

  private void generateMessageIfNecessary(String attributeName, Symbol callbackName, Class[] args,
					    String argumentSignature, Vector info){
    try{
      staticClass.getMethod(UilCallback.convertCallbackNameToMethodName(callbackName), args);
    }
    catch(NoSuchMethodException ex){
      info.addElement(generateMessage(attributeName, callbackName, argumentSignature));
    }
    catch(SecurityException ex){
      info.addElement(generateMessage(attributeName, callbackName, argumentSignature));
    }
  }

  private static final Symbol PROCEDURE_ = Symbol.intern("PROCEDURE");

  private Vector callbacks = new Vector();

  private String generateMessage(String attributeName, Symbol callbackName, String argumentSignature){
    if (!callbacks.contains(callbackName))
      callbacks.addElement(callbackName);
    String procedureText = "PROCEDURE NOT FOUND";
    try{
      Procedure proc = (Procedure)connection.getUniqueNamedItem(PROCEDURE_, callbackName);
      procedureText = proc.getText();
    }
    catch(G2AccessException ex){
    }
    if (attributeName.equals("uil-validate-grobj"))
      return "Attribute: "+attributeName+"\nProcedure name: "+callbackName.toString()+"\nJava method signature: "+"public static String "+UilCallback.convertCallbackNameToMethodName(callbackName)+argumentSignature+"\nProcedure text: \n"+procedureText+"\n";
    else
      return "Attribute: "+attributeName+"\nProcedure name: "+callbackName.toString()+"\nJava method signature: "+"public static void "+UilCallback.convertCallbackNameToMethodName(callbackName)+argumentSignature+"\nProcedure text: \n"+procedureText+"\n";
  }

  private void generateMessageIfNecessary(String attributeName, Object value, String message, Vector info){
    info.addElement(generateMessage(attributeName, value, message));
  }
  
  private String generateMessage(String attributeName, Object value, String message){
    return "Attribute: "+attributeName+"\n  Attribute value: "+value+"\n "+message+"\n";
  }
  
  public static void main(String[] args){
    if (args == null || args.length < 2){
      System.err.println ("Usage: java com.gensym.beaneditor.UilBatchConverter [-host host] [-port port] -input <filename> [-outputRepos <URL>] -callbackClass <classname>");
      System.exit (2);
    }

    try{
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    }
    catch (Exception ex) {
      throw new com.gensym.util.UnexpectedException(ex);
    }

    UilBatchConverter application = new UilBatchConverter(args);
    Preferences.establishPreferences();
    CmdLineArgHandler cmdLineHandler = application.commandLineArguments;
    String host = cmdLineHandler.getOptionValue ("-host");
    if (host == null) host = "localhost";
    String port = cmdLineHandler.getOptionValue ("-port");
    if (port == null) port = "1111";
    String input = cmdLineHandler.getOptionValue ("-input");
    String output = cmdLineHandler.getOptionValue ("-outputRepos");
    String callbackClass = cmdLineHandler.getOptionValue ("-callbackClass");

    try{
      application.doConversion(host, port, input, output, callbackClass);
    }
    catch(Exception ex){
      application.writeLog();
      ex.printStackTrace();
      System.exit(-1);
    }
    System.out.println("exiting");
    System.exit(0);
  }
}
