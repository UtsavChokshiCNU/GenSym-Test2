package com.gensym.wksp;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
import java.io.File;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.ScrollPaneConstants;

import com.gensym.classes.Block;
import com.gensym.classes.SystemClassDefinitionImpl;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.TwConnection;
import com.gensym.ntw.util.G2ObjectCreator;
import com.gensym.ntw.util.G2Palette;
import com.gensym.ui.ObjectCreator;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.menu.awt.CPopupMenu;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.symbol.G2ClassSymbols;

public class PalettePane extends JScrollPane implements G2ClassSymbols, ScrollPaneConstants, StandardDialogClient {
  private JTabbedPane jTabbedPane;
  private int iconSize = -1, buttonStyle = -1;
  private TwConnection cxn;
  private MouseAdapter mouseListener;
  private boolean isDialog;
  static final Resource i18n = Resource.getBundle ("com/gensym/wksp/UiLabels");
  static final int ADD = 1025;
  static final int REMOVE = 1026;
  private static final String ANY = "*", COMMA = ",";
  private static final int TEXT_AND_ICON = 2,
    ICON_ONLY = 0,
    TEXT_ONLY = 1;
  private static final RepresentationConstraints textAndIconConstraints =
        new RepresentationConstraints(RepresentationConstraints.TEXT_AND_ICON,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.TOP,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.BOTTOM);
  private static final RepresentationConstraints iconOnlyConstraints =
        new RepresentationConstraints(RepresentationConstraints.ICON_ONLY,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER);
  private static final RepresentationConstraints textOnlyConstraints =
        new RepresentationConstraints(RepresentationConstraints.TEXT_ONLY,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER,
				      RepresentationConstraints.CENTER);
  private static final int 
    CONNECTION_NAME = 0,
    EQUALS          = 1,
    CLASS           = 2,
    SEPARATOR       = 3;
  static Hashtable paletteClassHash;
  Vector objectCreators = new Vector();
  private static final Symbol TOP_LEVEL_MODULE_ = Symbol.intern("TOP-LEVEL-MODULE"),
    CLASS_ENTRIES_ = Symbol.intern("CLASS-ENTRIES"),
    PALETTE_TABS_ = Symbol.intern("PALETTE-TABS"),
    ICON_WIDTH_ = Symbol.intern ("ICON-WIDTH"),
    ICON_HEIGHT_ = Symbol.intern ("ICON-HEIGHT"),
    ICON_SIZE_ = Symbol.intern("ICON-SIZE"),
    BUTTON_STYLE_ = Symbol.intern("BUTTON-STYLE"),
    TAB_NAME_ = Symbol.intern ("TAB-NAME"),
    CLASS_NAME_ = Symbol.intern("CLASS-NAME"),
    CLASS_DEFINITION_ = Symbol.intern("CLASS-DEFINITION"),
    DEFINING_MODULE_ = Symbol.intern("DEFINING-MODULE"),
    G2_GET_MODULE_PALETTES_ = Symbol.intern("G2-GET-MODULE-PALETTES");
  static final int defaultIconWidth = 16, defaultIconHeight = 16;
  static final int defaultIconSize = ObjectCreator.SMALL_ICON;
  private Sequence currentPaletteTabs = null;
  private static Symbol[] rulesAndDefinitionClasses = new Symbol[]
  {
    RULE_, CLASS_DEFINITION_, PROCEDURE_, METHOD_DECLARATION_, METHOD_, USER_MENU_CHOICE_,
      RELATION_, FUNCTION_DEFINITION_, FOREIGN_FUNCTION_DECLARATION_, TOKENIZER_,
      IMAGE_DEFINITION_
  };
  private static Symbol[] buttonAndDisplayClasses = new Symbol[]
  {
    ACTION_BUTTON_, RADIO_BUTTON_, CHECK_BOX_, SLIDER_, TYPE_IN_BOX_,
      DIAL_, METER_, TREND_CHART_, CHART_, FREEFORM_TABLE_, READOUT_TABLE_, DIGITAL_CLOCK_
  };
  private static Symbol[] listAndArrayClasses = new Symbol[]
  {
    G2_LIST_, ITEM_LIST_, VALUE_LIST_, SYMBOL_LIST_, TEXT_LIST_, TRUTH_VALUE_LIST_,
      QUANTITY_LIST_, FLOAT_LIST_, INTEGER_LIST_,
    G2_ARRAY_, ITEM_ARRAY_, VALUE_ARRAY_, SYMBOL_ARRAY_, TEXT_ARRAY_, TRUTH_VALUE_ARRAY_,
      QUANTITY_ARRAY_, FLOAT_ARRAY_, INTEGER_ARRAY_,       
  };
  private static Symbol[] variableAndParameterClasses = new Symbol[]
  {
    LOGICAL_VARIABLE_, QUANTITATIVE_VARIABLE_, INTEGER_VARIABLE_, FLOAT_VARIABLE_,
      SYMBOLIC_VARIABLE_, TEXT_VARIABLE_,
    LOGICAL_PARAMETER_, QUANTITATIVE_PARAMETER_, INTEGER_PARAMETER_,
      FLOAT_PARAMETER_, SYMBOLIC_PARAMETER_, TEXT_PARAMETER_,       
  };
  private static Symbol[] miscClasses = new Symbol[]
  {CONNECTION_POST_, G2_WINDOW_, GSI_INTERFACE_};

  public PalettePane(TwConnection cxn, int iconSize, int buttonStyle) {
    super(new JTabbedPane());
    jTabbedPane = (JTabbedPane)getViewport().getView();
    this.cxn = cxn;
    this.iconSize = iconSize;
    this.buttonStyle = buttonStyle;
    initialize();
    isDialog = false;
  }
  
  public PalettePane (TwConnection cxn) {
    super(new JTabbedPane());
    jTabbedPane = (JTabbedPane)getViewport().getView();
    this.cxn = cxn;
    initialize();
    isDialog = true;
  }
  
  private void initialize() {
    int size, style;
    if (iconSize > -1)
      size = iconSize;
    else
      size = defaultIconSize;
    if (buttonStyle > -1)
      style = buttonStyle;
    else
      style = TEXT_AND_ICON;
    try {
      //get any saved palettetabs or default paletteTabs
      Sequence paletteTabs=determinePaletteTabsForConnection(cxn);
      // make tabs for each elt in the sequence
      if (!paletteTabs.isEmpty())
        for (int i=0; i < paletteTabs.size(); i++) {
          Structure paletteTab = (Structure) paletteTabs.elementAt(i);
          String tabName = (String) paletteTab.getAttributeValue(TAB_NAME_);
          Sequence classEntries = (Sequence)paletteTab.getAttributeValue(CLASS_ENTRIES_, new Sequence());
          Structure classEntry = (Structure)classEntries.elementAt(0);
          int newIconSize = ((Integer) classEntry.getAttributeValue(ICON_SIZE_, new Integer(size))).intValue();
	  int newButtonStyle = ((Integer) classEntry.getAttributeValue(BUTTON_STYLE_, new Integer(style))).intValue();
          makeNewPaletteTabPane (tabName, cxn, -1, paletteTab, newIconSize, newButtonStyle);
        }
    } catch (NoSuchAttributeException ex) {
      Trace.exception (ex);
    }
  }
  
  Vector getObjectCreators() {
    return objectCreators;
  }
  
  public Dimension getTabPreferredSize() {
    return jTabbedPane.getPreferredSize();
  }

  public JTabbedPane getTabbedPane() {
    return jTabbedPane;
  }

  public Sequence getCurrentPaletteTabs() {
    return currentPaletteTabs;
  }

  private static Sequence defaultPaletteTabs = new Sequence();
  static
  {
    defaultPaletteTabs.addElement(makePaletteTab(null, i18n.getString("rulesAndDefinitions"),
						 rulesAndDefinitionClasses,
						 defaultIconWidth,
						 defaultIconHeight,
						 defaultIconSize, TEXT_AND_ICON));
    defaultPaletteTabs.addElement(makePaletteTab(null, i18n.getString("buttonsAndDisplays"),
						 buttonAndDisplayClasses,
						 defaultIconWidth,
						 defaultIconHeight,
						 defaultIconSize, TEXT_AND_ICON));
    defaultPaletteTabs.addElement(makePaletteTab(null, i18n.getString("listsAndArrays"),
						 listAndArrayClasses,
						 defaultIconWidth,
						 defaultIconHeight,
						 defaultIconSize, TEXT_AND_ICON));
    defaultPaletteTabs.addElement(makePaletteTab(null, i18n.getString("variablesAndParameters"),
						 variableAndParameterClasses,
						 defaultIconWidth,
						 defaultIconHeight,
						 defaultIconSize, TEXT_AND_ICON));    
    defaultPaletteTabs.addElement(makePaletteTab(null, i18n.getString("misc"),
						 miscClasses,
						 defaultIconWidth,
						 defaultIconHeight,
						 defaultIconSize, TEXT_AND_ICON));
  }
  private void makePaletteTabsForModule(Sequence currentPaletteTabs) {
    if (cxn == null) return;

    try {
      Module[] modules = cxn.getKb().getModules();
      if (modules == null) return;
      for (int k=0; k < modules.length; k ++) {
        ModuleInformation topModuleInfo = modules[k].getModuleInformation();
        if (topModuleInfo == null) return;

        Sequence modPaletteSeq = (Sequence) cxn.callRPC(G2_GET_MODULE_PALETTES_, new Object[] {topModuleInfo});

        if (modPaletteSeq == null) return;

        for (int i=0; i < modPaletteSeq.size(); i++) {
          Structure tabStructure = (Structure) modPaletteSeq.get(i);
          String tabName = (String) tabStructure.getAttributeValue(TAB_NAME_);
          Sequence classEntries = (Sequence) tabStructure.getAttributeValue(CLASS_ENTRIES_);
          if (classEntries.size() == 0) return;

          //get class names and icon size of module palettes
          Symbol[] modClasses  = new Symbol[classEntries.size()];
          int classIconSize = 0;
	  int classButtonStyle = TEXT_AND_ICON;
          for (int j=0; j < classEntries.size(); j++) {
            Structure classEntry = (Structure) classEntries.get(j);
            if (classEntry.getAttributeValue(CLASS_NAME_) == null) return;
            modClasses[j] = (Symbol) classEntry.getAttributeValue(CLASS_NAME_);
            classIconSize = ((Integer) classEntry.getAttributeValue(ICON_SIZE_)).intValue();
	    classButtonStyle = ((Integer) classEntry.getAttributeValue(BUTTON_STYLE_)).intValue();
          }

	  if (iconSize > -1) classIconSize = iconSize;
	  if (buttonStyle > -1) classButtonStyle = buttonStyle;
          //make tabs for module palettes
          currentPaletteTabs.addElement(makePaletteTab(cxn, tabName,
						     modClasses,
						     defaultIconWidth,
						     defaultIconHeight,
						     classIconSize,
						       classButtonStyle));

        }
      }
    }
    catch (G2AccessException ex) {
      Trace.exception(ex);
    }
    catch (NoSuchAttributeException ex) {
      Trace.exception(ex);
    }

  }


  static Structure makePaletteTab(TwAccess cxn,
				  String tabName,
				  Symbol[] classNames,
				  int iconWidth,
				  int iconHeight,
                                  int newIconSize,
				  int newButtonStyle) {
    Structure tab = new Structure();
    tab.setAttributeValue(TAB_NAME_, tabName);
    Sequence classEntries = new Sequence();
    for (int i=0;i<classNames.length;i++) {
      Structure classEntry = new Structure();
      Symbol className = classNames[i];
      classEntry.setAttributeValue(CLASS_NAME_, className);
      Symbol definingModule = null;
      if (cxn != null) {
	try {
	  Object def = ((G2Gateway)cxn).getDefinition(className);
	  if (def != null && (!(def instanceof SystemClassDefinitionImpl))) {
	    definingModule = ((Block)def).getContainingModule();
	  }
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }
      classEntry.setAttributeValue(DEFINING_MODULE_, definingModule);
      classEntry.setAttributeValue(ICON_WIDTH_, new Integer(iconWidth));
      classEntry.setAttributeValue(ICON_HEIGHT_, new Integer(iconWidth));
      classEntry.setAttributeValue(ICON_SIZE_, new Integer(newIconSize));
      classEntry.setAttributeValue(BUTTON_STYLE_, new Integer(newButtonStyle));
      classEntries.addElement(classEntry);
    }
    tab.setAttributeValue(CLASS_ENTRIES_, classEntries);
    return tab;
  }

  public void cancelDrops() {
    int tabSize = jTabbedPane.getTabCount();
    for (int i=0;i<tabSize;i++) 
      ((G2Palette)jTabbedPane.getComponentAt(i)).dropCancelled();      
  }
  
  @Override
  public void dialogDismissed(StandardDialog dialog, int index) {
    if (dialog instanceof QuestionDialog) {
      switch (index) {
      case StandardDialog.CANCEL:
	return;
      case StandardDialog.NO:
	return;
      case StandardDialog.YES:
	saveCurrentPreferences(currentPaletteTabs);
      }
    }
  }
    
    void makeNewPaletteTabPane (String tabName, TwConnection cxn, int insertIndex, Structure paletteTab, int newIconSize, int constraintType) {
    try {
      Symbol[] classesForPalette = getTabClassesArray(paletteTab);
      G2ObjectCreator objectCreator = new G2ObjectCreator (cxn, classesForPalette);
      G2GridPalette palette = new G2GridPalette (cxn);
      if (iconSize > -1) newIconSize = iconSize;
      palette.setIconSize(newIconSize);
      palette.setButtonStyle(constraintType);
      if (buttonStyle > -1) constraintType = buttonStyle;
      switch (constraintType) {
      case TEXT_AND_ICON:
	palette.add (objectCreator, textAndIconConstraints);
	break;
      case TEXT_ONLY:
	palette.add (objectCreator, textOnlyConstraints);
	break;
      case ICON_ONLY:
	palette.add (objectCreator, iconOnlyConstraints);
	break;
      }
      palette.addMouseListener(new MouseAdapter(this));
      if (insertIndex == -1) {  //add comp to the jTabbedPane
        jTabbedPane.addTab(tabName, palette);
        objectCreators.addElement(objectCreator);
      } else {
        jTabbedPane.insertTab(tabName, null, palette, "", insertIndex);
        objectCreators.insertElementAt(objectCreator, insertIndex);
      }
    } catch (G2AccessException g2ae) {
        Trace.exception (g2ae);
    }
  }
  private Sequence determinePaletteTabsForConnection(TwConnection cxn) {
    String oldStyleCache = System.getProperty ("com.gensym.wksp.palette.classes");
    if (oldStyleCache == null) {
      try{
	Sequence prefs = establishPreferences();
	if (prefs != null) {
	  currentPaletteTabs = getSavedPaletteTabsForCurrentModule(prefs);
	  if (currentPaletteTabs != null) {
	    Vector droppedClasses = filterDeadClasses(currentPaletteTabs);
	    if (droppedClasses != null)
	      new QuestionDialog(null, i18n.getString("classesdropped"), true,
				 i18n.getString("dropmsg")+droppedClasses+i18n.getString("saveQuestion"),
				 this).setVisible(true);
	  }
	} 
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      } catch (G2AccessException gae){
	Trace.exception(gae);
      } catch (IOException ioe) {
	Trace.exception(ioe);
      }
      if (currentPaletteTabs == null) {
	//System.out.println("CASE 1");
	currentPaletteTabs = (Sequence)defaultPaletteTabs.clone();

        //make paletteTabs for modules
        //makePaletteTabsForModule(currentPaletteTabs);
      } else {
	//System.out.println("CASE 2 "+currentPaletteTabs);
      }
      return currentPaletteTabs;
    } else {//THIS IS OLD STYLE, ONE TAB, PALETTE CACHING IN THE .com.gensym.properties FILE
      if (paletteClassHash == null)
	initializePaletteClasses(oldStyleCache);
      String logicalName = ((G2Gateway)cxn).getG2ConnectionInfo().getLogicalName ();
      if (logicalName == null)
	logicalName = ANY;
      Symbol[] classes = (Symbol[])paletteClassHash.get (logicalName);
      Sequence paletteTabs = new Sequence();
      paletteTabs.addElement(makePaletteTab(cxn,"Tab One",classes,
					    defaultIconWidth, defaultIconHeight, defaultIconSize, TEXT_AND_ICON));
      return paletteTabs;
    }
  }

  private Symbol[] getTabClassesArray(Structure paletteTab) {
    Sequence classEntries = (Sequence)paletteTab.getAttributeValue(CLASS_ENTRIES_, new Sequence());
    int classCount = classEntries.size();
    Symbol[] classes = new Symbol[classCount];    
    for (int i=0;i<classCount;i++) {
      Structure classEntry = (Structure)classEntries.elementAt(i);
      classes[i]=(Symbol)classEntry.getAttributeValue(CLASS_NAME_, null);
    }
    return classes; 
  }


  private Sequence getSavedPaletteTabsForCurrentModule(Sequence prefs)
    throws G2AccessException
  {
    Symbol modName = cxn.getKb().getTopLevelModule().getName();
    if (modName == null) modName = NONE_;
    Sequence paletteTabs = null;
    Structure savedPalette=null;
    for (int i=0; i<prefs.size()&&paletteTabs==null; i++) {
      savedPalette = (Structure)prefs.elementAt(i);
      if (modName.equals(savedPalette.getAttributeValue(TOP_LEVEL_MODULE_, null))) {
	paletteTabs = (Sequence)savedPalette.getAttributeValue(PALETTE_TABS_, null);
	//System.out.println("FOUND IT "+savedPalette);
      } else {
	//System.out.println("NOT IT " + savedPalette + modName);
      }
    }
    return paletteTabs;
  }    

 /**
  * @return a sequence of dropped classes or null if none were dropped
  */
  private Vector filterDeadClasses(Sequence paletteTabs)
    throws NoSuchAttributeException
  {
    int tabCount = paletteTabs.size();
    Symbol className;
    Vector droppedClasses = null;
    for (int i=0; i<tabCount; i++) {
      Structure paletteTab = (Structure)paletteTabs.elementAt(i);
      Sequence paletteEntries = (Sequence)paletteTab.getAttributeValue(CLASS_ENTRIES_, new Sequence());
      for (int j=0;j<paletteEntries.size();j++) {
	Structure classEntry = (Structure)paletteEntries.elementAt(j);
	className = (Symbol)classEntry.getAttributeValue(CLASS_NAME_, null);
	try {
	  ((G2Gateway)cxn).getDefinition(className);//make sure it still exists
	} catch (G2AccessException gae) {
	  if (droppedClasses == null)
	    droppedClasses = new Sequence();
	  paletteEntries.removeElement(className);
	  droppedClasses.addElement(className);
	}
      }
    }
    return droppedClasses;   
  }
    String fileName;
  private void getFile() throws IOException {
    String defaultFileName;
    fileName = System.getProperty
      ("com.gensym.g2studio.preferences", null);
    if (fileName == null)
      defaultFileName = "g2studio.prefs";
    else defaultFileName = fileName;
    String homeDir = System.getProperty("user.home");
    if (fileName != null) {
      File prefFile = new File(fileName);
      prefFile.createNewFile();
    }
    if (homeDir != null) fileName = homeDir + File.separator + defaultFileName;
  }

  //returns the Sequence in the file specified by property or null.
  private Sequence establishPreferences() throws IOException {
    getFile();
    Sequence currentPreferences;
    FileInputStream fis = null;
    ObjectInputStream ois = null;
    try{
      fis= new FileInputStream(fileName);
      ois = new ObjectInputStream(fis);
      Object prefs = ois.readObject();
      if (prefs instanceof Sequence)
	currentPreferences = (Sequence)prefs;
      else currentPreferences = null;
    }
    catch(Exception ex){
      // ignore all errors and just create a new prefs object
      currentPreferences = null;
    } finally {
      if (ois != null) ois.close();
      if (fis != null) fis.close();
    }
    return currentPreferences;
  }

  private static final Symbol NONE_ = Symbol.intern ("NONE");
  private Sequence makeObjectToWriteToFile(Sequence cachableModulePreferences)
    throws G2AccessException, IOException
  {
    Sequence totalPrefs = establishPreferences(); //read from file
    Symbol modName = cxn.getKb().getTopLevelModule().getName();
    if (modName == null)
      modName = NONE_;
    
    Structure modulePreferences = null;
    if (totalPrefs == null)
      totalPrefs = new Sequence();
    else {
      for (int i=0; i<totalPrefs.size()&&modulePreferences==null; i++) {
	Structure currentModulePreferences = (Structure)totalPrefs.elementAt(i);
	Symbol currentModuleName = (Symbol)
	  currentModulePreferences.getAttributeValue(TOP_LEVEL_MODULE_, null);
	if (modName.equals(currentModuleName))
	  modulePreferences = currentModulePreferences;
      }
    }
    if (modulePreferences == null) {
      modulePreferences = new Structure();
      modulePreferences.setAttributeValue(TOP_LEVEL_MODULE_, modName);
      totalPrefs.addElement(modulePreferences);
    }

    modulePreferences.setAttributeValue(PALETTE_TABS_,cachableModulePreferences);
    return totalPrefs;
  }
  
  void saveCurrentPreferences(Sequence paletteTabs) {
    FileOutputStream fos = null;
    ObjectOutputStream oos = null;
    try{
      Sequence totalPrefs = makeObjectToWriteToFile(paletteTabs);
      fos = new FileOutputStream(fileName);
      oos = new ObjectOutputStream(fos);
      oos.writeObject(totalPrefs);
      oos.close();
      fos.close();
    } catch(Exception ex){
      com.gensym.message.Trace.exception(ex);
      //should the user be bothered if their preferences can't be saved?
    }
  }
  
  private void initializePaletteClasses (String propValue) {
    paletteClassHash = new Hashtable ();
    paletteClassHash.put (ANY, new Symbol[] {CLASS_DEFINITION_, PROCEDURE_});
    if (propValue == null)
      return;
    StringTokenizer tknzr = new StringTokenizer (propValue, "=,:", true);
    int tknzrState = CONNECTION_NAME;
    String connectionName = null;
    Vector classes = new Vector ();
    while (tknzr.hasMoreTokens ()) {
      String token = tknzr.nextToken ();
      switch (tknzrState)
	{
	case CONNECTION_NAME: connectionName = token; tknzrState = EQUALS; break;
	case EQUALS: tknzrState = CLASS; break;
	case CLASS: classes.addElement (Symbol.intern (token)); tknzrState = SEPARATOR; break;
	case SEPARATOR:
	  if (token.equals (COMMA)) {
	    tknzrState = CLASS;
	  } else {
	    saveClassesForConnection (connectionName, classes);
	    connectionName = null;
	    tknzrState = CONNECTION_NAME;
	  }
	}
    }
    if (connectionName != null)
      saveClassesForConnection (connectionName, classes);
  }
  
  private void saveClassesForConnection (String connectionName, Vector classes) {
    int numClasses = classes.size ();
    Symbol[] classArray = new Symbol [numClasses];
    classes.copyInto (classArray);
    classes.removeAllElements ();
    paletteClassHash.put (connectionName, classArray);
  }
  
  class G2GridPalette extends G2Palette{
    
    private int numberOfCols = 4;
    private int counter = 0;
    private GridBagLayout gridBag;
    private GridBagConstraints constraints;
    
    G2GridPalette(TwAccess connection){
      super(connection);
      gridBag = new GridBagLayout();
      setLayout(gridBag);
      constraints = new GridBagConstraints();
      constraints.insets = new Insets(0, 0, 0, 0);
      constraints.ipadx = 0;
      constraints.ipady = 0;
      constraints.anchor = GridBagConstraints.NORTHWEST;
    }
    
    @Override
    public Component add(Component c){
      counter++;
      constraints.fill = constraints.BOTH;
      if (counter % numberOfCols == 0) 
	constraints.gridwidth = constraints.REMAINDER;
      else 
	constraints.gridwidth = 1;
      gridBag.setConstraints(c, constraints);
      return super.add(c);
    }
    
    @Override
    public void remove(int i){
      counter--;
      super.remove(i);
    }
    
  }
  
  
  class MouseAdapter implements MouseListener {
    PalettePane palettePane;
    public MouseAdapter (PalettePane palettePane) {
      this.palettePane = palettePane;
    }
    @Override
    public void mousePressed(MouseEvent event){
      popupMenuIfNecessary(event);
    }
    @Override
    public void mouseReleased(MouseEvent event){
      popupMenuIfNecessary(event);
    }
    private void popupMenuIfNecessary(MouseEvent event){
      if (event.isPopupTrigger()){
	CPopupMenu popup = new CPopupMenu();
	if (isDialog)
	  popup.add(new PaletteCommands(cxn));
	else
	  popup.add(new PaletteCommands(cxn, palettePane));
	add (popup);
	popup.show((Component)event.getSource(), event.getX(), event.getY());
      }
    }
    @Override
    public void mouseClicked(MouseEvent event){}
    @Override
    public void mouseEntered(MouseEvent event){}
    @Override
    public void mouseExited(MouseEvent event){}
  }
}
