/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 UI.java
 *
 */

//package com.gensym.bundle;

import javax.swing.JFrame;
import javax.swing.JRadioButton;
import javax.swing.JCheckBox;
import javax.swing.JButton;
import javax.swing.ButtonGroup;
import javax.swing.AbstractButton;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.BoxLayout;

import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Vector;


/** The UI class is view/model/controller all rolled together.
 * The presentation to the user is organized as a sequence of
 * successive choices, one screen (JPanel) each. The state machine
 * that goes forward through the choices is implemented in the 
 * SelectionListener for the 'select' button. Backwards moves
 * are done by the SelectionListener for the 'go back' button.
 *
 * Architecture: We go into a state, setup and populate its
 * screen, especially the label of the select button, and then wait
 * for the user to make a choice and hit the button. The selection
 * listeners know what state we're in from the value of currentMode.
 *   Each mode has a 'setup<mode>' method, which organizes the screen
 * and calls a 'populate<mode>' method to get it's content.
 */
 
public class UI extends JFrame {

  private final static boolean debug = true;
  private final static boolean traceTheKey = true;

  /* The version should be incremented by a tenth every time
   * a new jar is issued. If we makeover its overall L&F then
   * we should bump the major number. */
  private final static String version = "v1.8";

  ButtonGroup familyButtons;
  ButtonGroup bundleButtons;
  ButtonGroup platformButtons;
  ButtonGroup clientButtons;
  ButtonGroup typicalVsCustomButtons;
  myToggleListener toggleListener;
  myJPanel familyPanel;
  myJPanel bundlePanel;
  myJPanel platformPanel;
  myJPanel standardVsCustomPanel;
  myJPanel selectFromAllPanel;
  myJPanel optionsPanel;
  myJPanel clientsPanel;
  myJPanel resultsPanel;
  JPanel finalPanel;
  JScrollPane familyScroller;
  JScrollPane bundleScroller;
  JScrollPane platformScroller;
  JScrollPane standardVsCustomScroller;
  JScrollPane selectFromAllScroller;
  JScrollPane optionsScroller;
  JScrollPane clientOptionsScroller;
  JScrollPane otherOptions_2Scroller;
  JScrollPane otherOptions_3Scroller;
  JScrollPane otherOptions_4Scroller;
  JScrollPane otherOptions_5Scroller;
  JScrollPane otherOptions_6Scroller;
  JScrollPane resultsScroller;
  JLabel results;
  myJTextField whatTheKeyIs;
  JButton selectButton;
  JButton backButton;
  JButton reportButton;
  JPanel buttonPanel;
  
  Families theFamilies;
  Vector allTheFamilies;
  Vector allTheBundles;
  Vector allTheComponents;
  Vector clientComponents;
  Vector otherComponents_2;
  Vector otherComponents_3;
  Vector otherComponents_4;
  Vector otherComponents_5;
  Vector otherComponents_6;

  int versionOfInstaller;
  Family familySelected;
  Bundle bundleSelected;
  Platform platformSelected;
  boolean isInstallTypeKnown = false;
  boolean typicalInstall;
  Vector optionalComponentsSelected;
  Component clientsComponentSelected;
  Component otherComponent_2;
  Component otherComponent_3;
  Component otherComponent_4;
  Component otherComponent_5;
  Component otherComponent_6;
  String theKey;
  
  String description;

  private final static int SELECT_FAMILY = 1;
  private final static int SELECT_BUNDLE = 2;
  private final static int SELECT_PLATFORM = 3;
  private final static int SELECT_STANDARD_VS_CUSTOM = 4;
  private final static int SELECT_FROM_AMONG_ALL_COMPONENTS = 5;
  private final static int SELECT_OPTIONS = 6;
  private final static int SELECT_CLIENT_PACK = 7;
  private final static int SELECT_OTHER_OPTIONS_2 = 8;
  private final static int SELECT_OTHER_OPTIONS_3 = 9;
  private final static int SELECT_OTHER_OPTIONS_4 = 10;
  private final static int SELECT_OTHER_OPTIONS_5 = 11;
  private final static int SELECT_OTHER_OPTIONS_6 = 12;
  private final static int REVIEW = 13;
  private final static int LICENSE_CODE = 14;
  int mode = SELECT_FAMILY;

  private String currentMode() {
    switch (mode) {
    case SELECT_FAMILY:
      return "SELECT_FAMILY";
    case SELECT_BUNDLE:
      return "SELECT_BUNDLE";
    case SELECT_STANDARD_VS_CUSTOM:
      return "SELECT_STANDARD_VS_CUSTOM";
    case SELECT_FROM_AMONG_ALL_COMPONENTS:
      return "SELECT_FROM_AMONG_ALL_COMPONENTS";
    case SELECT_OPTIONS:
      return "SELECT_OPTIONS";
    case REVIEW:
      return "REVIEW";
    case LICENSE_CODE:
      return "LICENSE_CODE";
    default:
      return "unknown!";
    }
  }


  public UI (Families theFamilies) {
    this.theFamilies = theFamilies;
    setTitle("Gensym License Key Generator -- FOR INTERNAL USE ONLY -- " + version);
    addWindowListener( new WindowAdapter() {
      public void windowClosing(WindowEvent we) {
	System.exit(0);
      }
    });
    toggleListener = new myToggleListener();

    Insets border = new Insets(2, 4, 2, 4);
    selectButton = new JButton("  an artificially large text  ");
    selectButton.setMargin(border);
    selectButton.addActionListener( new SelectionListener() );
    getRootPane().setDefaultButton(selectButton);
    backButton = new JButton("go back");
    backButton.setMargin(border);
    backButton.addActionListener( new GoBackListener() );
    backButton.setEnabled( false );
    reportButton = new JButton("issue report");
    reportButton.setMargin(border);
    reportButton.addActionListener( new IssueReportListener() );
    reportButton.setEnabled( false );
    buttonPanel = new JPanel();
    //buttonPanel.setLayout( new GridLayout(0, 3) );
    buttonPanel.setLayout( new FlowLayout( FlowLayout.LEFT ) );
    buttonPanel.add(selectButton);
    buttonPanel.add(reportButton);
    buttonPanel.add(backButton);
    /* The default size of this JFrame is such that the third button
     * displays off the edge and you have to manually expand the
     * window to see it. Since in actual use so far, report generation
     * is something that is always done while backup is unusual,
     * this seems to be the right default. */

    BorderLayout layout = new BorderLayout();
    getContentPane().setLayout( layout );
    getContentPane().add(buttonPanel, BorderLayout.SOUTH);

    //getContentPane().setSize( new Dimension(150, 800));  // width x height
    // See discussion in myJPanel

    setupFamilyOptions();

    pack();
    show();

  }


  //---- Setup routines for moving from one state to another.

  private void setupFamilyOptions() {
    mode = SELECT_FAMILY;
    familyPanel = new myJPanel();
    populateFamilyPanel(familyPanel);
    selectButton.setText("Pick a family"); //i18n.getString("select"));
    //backButton.setEnabled( false );
    familyScroller = new JScrollPane(familyPanel);
    getContentPane().add(familyScroller, BorderLayout.CENTER);
    validate();
  }

  private void setupBundleOptions(Family family) {
    mode = SELECT_BUNDLE;
    bundlePanel = new myJPanel();
    populateBundlePanel(bundlePanel, family);
    selectButton.setText("Pick a bundle");
    bundleScroller = new JScrollPane(bundlePanel);
    getContentPane().add(bundleScroller, BorderLayout.CENTER);
    validate();
  }

  private void setupPlatformOptions(Bundle bundle) {
    mode = SELECT_PLATFORM;
    platformPanel = new myJPanel();
    populatePlatformPanel(platformPanel, bundle);
    selectButton.setText("Pick a platform");
    platformScroller = new JScrollPane(platformPanel);;
    getContentPane().add(platformScroller, BorderLayout.CENTER);
    validate();
  }

  private void setupStandardVsCustom () {
    mode = SELECT_STANDARD_VS_CUSTOM;
    standardVsCustomPanel = new myJPanel();
    populateStandardVsCustomPanel(standardVsCustomPanel);
    selectButton.setText("Pick one");
    standardVsCustomScroller = new JScrollPane(standardVsCustomPanel);
    getContentPane().add(standardVsCustomScroller, BorderLayout.CENTER);
    validate();
  }

  private void setupSelectFromAll (Bundle bundle) {
    mode = SELECT_FROM_AMONG_ALL_COMPONENTS;
    if (optionalComponentsSelected == null)
      optionalComponentsSelected = new Vector();
    selectFromAllPanel = new myJPanel();
    populateSelectFromAllPanel(selectFromAllPanel, bundle);
    selectButton.setText("Select individual components");
    selectFromAllScroller = new JScrollPane(selectFromAllPanel);
    getContentPane().add(selectFromAllScroller, BorderLayout.CENTER);
    validate();
  }

  private void setupOptionOptions(Bundle bundle) {

    // Initialize optionalComponentsSelected if it's null. It
    // will not be null in the case where the user did a
    // customization of the "required" components.
    if (optionalComponentsSelected == null)	
      optionalComponentsSelected = new Vector();

    if (bundle.hasComponents()) {
      mode = SELECT_OPTIONS;
      optionsPanel = new myJPanel();
      populateOptionsPanel(optionsPanel, bundle);
      selectButton.setText("Select options");
      optionsScroller = new JScrollPane(optionsPanel);
      getContentPane().add(optionsScroller, BorderLayout.CENTER);
      validate();
    } 
    else
      setupClientPack(bundle);
  }

  private void setupClientPack(Bundle bundle) {      
    clientComponents = scanComponentsForBundleGroup(bundle, 1);
    int count = clientComponents.size();
    if ( count != 0 ) {
      mode = SELECT_CLIENT_PACK;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, clientComponents, 1);
      clientOptionsScroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select license");
      getContentPane().add(clientOptionsScroller, BorderLayout.CENTER);
      validate();
    } else setupOtherOptions_2(bundle);
  }

  private void setupOtherOptions_2(Bundle bundle) {
    otherComponents_2 = scanComponentsForBundleGroup(bundle, 2);
    int count = otherComponents_2.size();
    if ( count != 0 ) {
      mode = SELECT_OTHER_OPTIONS_2;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, otherComponents_2, 2);
      otherOptions_2Scroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select option");
      getContentPane().add(otherOptions_2Scroller, BorderLayout.CENTER);
      validate();
    } else setupOtherOptions_3(bundle);
  }
  private void setupOtherOptions_3(Bundle bundle) {
    otherComponents_3 = scanComponentsForBundleGroup(bundle, 3);
    int count = otherComponents_3.size();
    if ( count != 0 ) {
      mode = SELECT_OTHER_OPTIONS_3;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, otherComponents_3, 3);
      otherOptions_3Scroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select option");
      getContentPane().add(otherOptions_3Scroller, BorderLayout.CENTER);
      validate();
    } else setupOtherOptions_4(bundle);
  }
  private void setupOtherOptions_4(Bundle bundle) {
    otherComponents_4 = scanComponentsForBundleGroup(bundle, 4);
    int count = otherComponents_4.size();
    if ( count != 0 ) {
      mode = SELECT_OTHER_OPTIONS_4;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, otherComponents_4, 4);
      otherOptions_4Scroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select option");
      getContentPane().add(otherOptions_4Scroller, BorderLayout.CENTER);
      validate();
    } else setupOtherOptions_5(bundle);
  }
  private void setupOtherOptions_5(Bundle bundle) {
    otherComponents_5 = scanComponentsForBundleGroup(bundle, 5);
    int count = otherComponents_5.size();
    if ( count != 0 ) {
      mode = SELECT_OTHER_OPTIONS_5;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, otherComponents_5, 5);
      otherOptions_5Scroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select option");
      getContentPane().add(otherOptions_5Scroller, BorderLayout.CENTER);
      validate();
    } else setupOtherOptions_6(bundle);
  }
        
  private void setupOtherOptions_6(Bundle bundle) {
    otherComponents_6 = scanComponentsForBundleGroup(bundle, 6);
    int count = otherComponents_6.size();
    if ( count != 0 ) {
      mode = SELECT_OTHER_OPTIONS_6;
      clientsPanel = new myJPanel();
      populateClientsPanel(clientsPanel, otherComponents_6, 6);
      otherOptions_6Scroller = new JScrollPane(clientsPanel); 
      selectButton.setText("Select option");
      getContentPane().add(otherOptions_6Scroller, BorderLayout.CENTER);
      validate();
    } else setupReview();
  }
        
  private void setupReview() {
    mode = REVIEW;
    //String s = "<html>";
    String s = constructReport( true, false );
    //s += "</html>";
    results = new JLabel(s);
    resultsPanel = new myJPanel();
    resultsPanel.add(results);
    selectButton.setText("Make License Key");
    resultsScroller = new JScrollPane(resultsPanel);
    getContentPane().add(resultsScroller, BorderLayout.CENTER);
    validate();
  }
  


    private void getAndDisplayLicenseKey() {
	mode = LICENSE_CODE;
	/* Get the key via JNI. */
	KeyData k = new KeyData(familySelected, bundleSelected,
				platformSelected, optionalComponentsSelected,
				clientsComponentSelected,
				otherComponent_2, otherComponent_3,
				otherComponent_4, otherComponent_5,
				otherComponent_6, typicalInstall);
	if (debug)
	    System.out.println("Calling native method");
	theKey = k.getKey();
	if (traceTheKey)
	    System.out.println("\n\nThe license key is \"" + theKey + "\"");

	/* Layout what we show them. */
	whatTheKeyIs = new myJTextField();
	whatTheKeyIs.setText('\t' + theKey);
	finalPanel = new JPanel();
	finalPanel.setLayout( new BoxLayout(finalPanel, BoxLayout.Y_AXIS));
	finalPanel.add(whatTheKeyIs);
	finalPanel.add(results);
	
	reportButton.setEnabled( true );
	selectButton.setText("Make another license key");
	selectButton.setEnabled( false );
	getContentPane().add(finalPanel, BorderLayout.CENTER);
	validate();
    }
	


    //---- Populate the various panels

    private void populateFamilyPanel(myJPanel p) {
	familyButtons = new ButtonGroup();
	Vector families = theFamilies.getAllTheFamilies();
	for (int i=0; i < families.size(); i++) {
	    Family f = (Family)families.elementAt(i);


	    String version = "(unknown version)";
             // Set the version (replace unknown) in the heuristic way 
             // we've been using until we restructure: get the first bundle's
	     // version, assume there's 1 or more, and they're all 
             // the same. (Later, the version will be on the family!)
             // (MHD 4/15/01)
            Vector bundles = f.getBundles();
	    if (bundles.size() > 0) {
	      Bundle bundle = (Bundle)bundles.elementAt(0);
	      version = bundle.getVersion();
            }
	    

	    String name = f.getName();
	    myRadioButton button = new myRadioButton(name + "  -  " + version);
	    button.addItemListener(toggleListener);
	    button.setType(FAMILY_BUTTON);
	    button.setItem(f);
	    familyButtons.add(button);
	    p.add(button);
	    if (families.size() == 1)
	      button.setSelected( true );
	    else if ((familySelected != null)
		     && (f.equals(familySelected)))
	      button.setSelected( true );
	}
    }

    private void populateBundlePanel(myJPanel p, Family family) {
      bundleButtons = new ButtonGroup();
      Vector bundles = family.getBundles();
      for (int i=0; i < bundles.size(); i++) {
	Bundle bundle = (Bundle)bundles.elementAt(i);
	String name = bundle.getName();
	myRadioButton button = new myRadioButton(name);
	button.addItemListener(toggleListener);
	button.setType(BUNDLE_BUTTON);
	button.setItem(bundle);
	bundleButtons.add(button);
	p.add(button);
	if (bundles.size() == 1)
	  button.setSelected( true );
	else if ((bundleSelected != null)
		 && (bundle.equals(bundleSelected)))
	  button.setSelected( true );
      }
    }

    private void populatePlatformPanel(myJPanel p, Bundle bundle) {
	platformButtons = new ButtonGroup();
	Vector platforms = bundle.getPlatforms();
	for (int i=0; i < platforms.size(); i++) {
	    Platform platform = (Platform)platforms.elementAt(i);
	    String name = platform.getName();
	    myRadioButton button = new myRadioButton(name);
	    button.addItemListener(toggleListener);
	    button.setType(PLATFORM_BUTTON);
	    button.setItem(platform);
	    platformButtons.add(button);
	    p.add(button);
	    if (platforms.size() == 1)
	      button.setSelected( true );
	    else if ((platformSelected != null)
		     && (platform.equals(platformSelected)))
	      button.setSelected( true );
	}
    }

  private void populateStandardVsCustomPanel(myJPanel p) {
    typicalVsCustomButtons = new ButtonGroup();
    myRadioButton typical = new myRadioButton("Use the standard components");
    typical.addItemListener(toggleListener);
    typical.setType(STANDARD_VS_CUSTOM_BUTTON);
    typical.setItem(BUTTON_FOR_TYPICAL_INSTALL);
    typicalVsCustomButtons.add(typical);
    p.add(typical);
    myRadioButton custom = new myRadioButton("Select individual components");
    custom.addItemListener(toggleListener);
    custom.setType(STANDARD_VS_CUSTOM_BUTTON);
    custom.setItem(BUTTON_FOR_CUSTOM_INSTALL);
    typicalVsCustomButtons.add(custom);
    p.add(custom);
    if (isInstallTypeKnown) {
      if (typicalInstall)
	typical.setSelected( true );
      else
	custom.setSelected( true );
    } else
      typical.setSelected( true );
    isInstallTypeKnown = true;
  }

  private void populateSelectFromAllPanel(myJPanel p, Bundle b) {
    Vector components = b.getComponents();
    for (int i=0; i < components.size(); i++) {
      Component component = (Component)components.elementAt(i);
      if (!component.isLicensingComponent()
	  && !component.isOptional())
	setupComponentButton(component, p);
    }
  }

  private void populateOptionsPanel(myJPanel p, Bundle bundle) {
    Vector components = bundle.getOptionalComponents();
    for (int i=0; i < components.size(); i++) {
      Component component = (Component)components.elementAt(i);
      if ( component.validOnSelectedPlatform(platformSelected) ) {
	setupComponentButton((Component)components.elementAt(i), p);
      }
    }
  }


  private void clearComponentSelectionsIfNecessary() {
    System.out.println("Called clearComponentSelections...");
    if (optionalComponentsSelected != null) {
      optionalComponentsSelected.removeAllElements();
    }
  }


  private void setupComponentButton(Component component, myJPanel p) {
    String name = component.getName();
    myCheckBox button = new myCheckBox(name);
    button.addItemListener(toggleListener);
    button.setType(COMPONENT_BUTTON);
    button.setItem(component);
    p.add(button);
    if ((optionalComponentsSelected != null)
	&& (optionalComponentsSelected.contains(component)))
      button.setSelected( true );
  }


    
    private void populateClientsPanel(myJPanel p, Vector clientComponents, int group) {
	clientButtons = new ButtonGroup();
	for (int i=0; i < clientComponents.size(); i++) {
	    Component component = (Component)clientComponents.elementAt(i);
	    String name = component.getName();
	    myRadioButton button = new myRadioButton(name);
	    button.group = group;
	    button.addItemListener(toggleListener);
	    button.setType(CLIENT_BUTTON);
	    button.setItem(component);
	    clientButtons.add(button);
	    p.add(button);
	    switch (group) {
	    case 1:	    
		if ((clientsComponentSelected != null)
		    && (component.equals(clientsComponentSelected)))
		    button.setSelected( true );
		break;
	    case 2:
		if ((otherComponent_2 != null)
		    && (component.equals(otherComponent_2)))
		    button.setSelected( true );
		break;
	    case 3:
		if ((otherComponent_3 != null)
		    && (component.equals(otherComponent_3)))
		    button.setSelected( true );
		break;
	    case 4:
		if ((otherComponent_4 != null)
		    && (component.equals(otherComponent_4)))
		    button.setSelected( true );
		break;
	    case 5:
		if ((otherComponent_5 != null)
		    && (component.equals(otherComponent_5)))
		    button.setSelected( true );
		break;
	    case 6:
		if ((otherComponent_6 != null)
		    && (component.equals(otherComponent_6)))
		    button.setSelected( true );
		break;
	    }
	}
    }

    private Vector scanComponentsForBundleGroup(Bundle b, int radio_button_group_index) {
	Vector componentsWithBundleGroups = new Vector();
	Vector allTheComponents = b.getComponents();
	for (int i=0; i < allTheComponents.size(); i++) {
	    Component c = (Component)allTheComponents.elementAt(i);
	    if ( c.isLicensingComponent() && (c.getButtonGroup() == radio_button_group_index) )
	      componentsWithBundleGroups.addElement(c);
	}
	return componentsWithBundleGroups;
    }


  //---------------------- Widgets ------------------------------

    //---- A panel of specific size

    class myJPanel extends JPanel {
      //public Dimension getMinimumSize() {
      //return new Dimension(100, 130);  // width x height
      //}
      //public Dimension getPreferredSize() {
      //return new Dimension(150, 130);
      //}
      /* Vast hassles in trying to get this thing to scroll. With the
       * preferredSize set, adding these panels to a JScrollPane had
       * almost no effect, i.e. it was confused about the extent of the
       * underlying panel and though the range available for scrolling
       * was just a smidgen more than the height that was visible without
       * a scroller. Removing the setting shrank the height of the JFrame
       * overall, but now it scrolls correctly. */
      myJPanel() {
	setLayout( new BoxLayout(this, BoxLayout.Y_AXIS ));
      }
    }


    //---- A text field of a specific size

    class myJTextField extends JTextField {
	myJTextField() {
	    setEditable( false );
	    setColumns( 50 );
	}
    }


    //---- Ditto for a text area

    class myJTextArea extends JTextArea {
	myJTextArea() {
	    super(10, 50);  // lines by columns
	    setEditable( false );
	}
    }


    //---- Buttons and RadioBoxes

  /* These specializations of radio buttons and checkboxes provide a local
   * for recording what bundling element goes with them and what type they
   * are. The type is used in the dispatch within the Listener and the record
   * of the element (e.g. a component) lets us operate on that object
   * anonymously via its class. */

    class myRadioButton extends JRadioButton {
	private int group = -1;  /* default group = -1 */
	private int type;
	int getType() { return type; }
	void setType(int t) { type = t; }
	
	private Object item; /* Define a super class for our bundle elements? */
	Object getItem() { return item; }
	void setItem(Object i) { item = i; }

	myRadioButton(String name) { super(name);}
    }

    class myCheckBox extends JCheckBox {
	private int type;
	int getType() { return type; }
	void setType(int t) { type = t; }

	private Object item;
	Object getItem() { return item; }
	void setItem(Object i) { item = i; }

	myCheckBox(String name) { super(name);}
    }

    class myToggleListener implements ItemListener {
	public void itemStateChanged(ItemEvent e) {
	    Object button = e.getItemSelectable();
	    if (button instanceof myRadioButton)
		dispatchRadioButton( (myRadioButton)button, e);
	    else if (button instanceof myCheckBox)
		handleCheckBox( (myCheckBox)button, e);
	    else {
		System.out.println("wrong king of object");
		Thread.dumpStack();
	    }
	}
    }


  static final int FAMILY_BUTTON    = 1;
  static final int BUNDLE_BUTTON    = 2;
  static final int COMPONENT_BUTTON = 3;
  static final int PLATFORM_BUTTON  = 4;
  static final int CLIENT_BUTTON    = 5;
  static final int STANDARD_VS_CUSTOM_BUTTON = 6;

  void dispatchRadioButton(myRadioButton b, ItemEvent e) {
    int effect = e.getStateChange();
    Object item = b.getItem();
    if ( effect == ItemEvent.SELECTED ) {
      switch ( b.getType() ) {
      case FAMILY_BUTTON:
	familySelected = (Family)item;
	break;
      case PLATFORM_BUTTON:
	platformSelected = (Platform)item;
	break;
      case BUNDLE_BUTTON:
	bundleSelected = (Bundle)item;
	break;
      case CLIENT_BUTTON:
	  switch (b.group) {
	  case 1:	    
	      clientsComponentSelected = (Component)item;
	      break;
	  case 2:    
	      otherComponent_2 = (Component)item;
	      break;
	  case 3:    
	      otherComponent_3 = (Component)item;
	      break;
	  case 4:    
	      otherComponent_4 = (Component)item;
	      break;
	  case 5:    
	      otherComponent_5 = (Component)item;
	      break;
	  case 6:    
	      otherComponent_6 = (Component)item;
	      break;
	  }
	  break;
      case STANDARD_VS_CUSTOM_BUTTON:
	decodeStandardVsCustomButton(b, true);
	break;
      default:
	throw new RuntimeException("Unknown type of radio button selected.");
      }
    }
    else if ( effect == ItemEvent.DESELECTED ) {
      switch ( b.getType() ) {
      case FAMILY_BUTTON:
	familySelected = null;
	break;
      case PLATFORM_BUTTON:
	platformSelected = null;
	break;
      case BUNDLE_BUTTON:
	bundleSelected = null;
	break;
      case CLIENT_BUTTON:
	  switch (b.group) {
	  case 1:	    
	      clientsComponentSelected = null;
	      break;
	  case 2:    
	      otherComponent_2 = null;
	      break;
	  case 3:    
	      otherComponent_3 = null;
	      break;
	  case 4:    
	      otherComponent_4 = null;
	      break;
	  case 5:    
	      otherComponent_5 = null;
	      break;
	  case 6:    
	      otherComponent_6 = null;
	      break;
	  }
	  break;
      case STANDARD_VS_CUSTOM_BUTTON:
	decodeStandardVsCustomButton(b, false);
	break;
      default:
	throw new RuntimeException("Unknown type of radio button selected.");
      }
    }
  }

  void handleCheckBox(myCheckBox b, ItemEvent e) {
    int effect = e.getStateChange();
    Component component = (Component)b.getItem();
    if ( effect == ItemEvent.SELECTED ) {
      if ( !optionalComponentsSelected.contains(component) )
	optionalComponentsSelected.addElement(component);
    }
    else if ( effect == ItemEvent.DESELECTED ) {
      optionalComponentsSelected.removeElement(component);
    }
  }

  
  static final Integer BUTTON_FOR_TYPICAL_INSTALL = new Integer(1);
  static final Integer BUTTON_FOR_CUSTOM_INSTALL  = new Integer(2);

  void decodeStandardVsCustomButton(myRadioButton b, boolean wasSelected) {
    Integer item = (Integer)b.getItem();
    if ( item.equals(BUTTON_FOR_TYPICAL_INSTALL) ) {
      if (wasSelected)
	typicalInstall = true;
      else
	typicalInstall = false;
    } else { 
      // custom button
      if (wasSelected)
	typicalInstall = false;
      else
	typicalInstall = true;
    }
  }



  //---- Code for reacting to the 'select' button and move to the
  //     next state.

  /* For the 'do it' button that the user hits when they've make
   * a selection from a given screen. */
  class SelectionListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      switch (mode) {
      case SELECT_FAMILY:
	if (familySelected != null) {
	  if (debug)
	    System.out.println("Selected the family " + familySelected.getName());
	  //backButton.setEnabled( true );
	  getContentPane().remove(familyScroller);
	  setupBundleOptions(familySelected);
	}
	break;
      case SELECT_BUNDLE:
	if (bundleSelected != null) {
	  if (debug)
            // See the comment above on the fact that the version is 
            // attached to the bundle and not to the family. (JPG 7/12/06)
	    System.out.println("Selected the bundle " + bundleSelected.getName()
                                              + " - " + bundleSelected.getVersion());
	  getContentPane().remove(bundleScroller);
	  setupPlatformOptions(bundleSelected);
	}
	break;
      case SELECT_PLATFORM:
	if (platformSelected != null) {
	  if (debug)
	    System.out.println("Selected the platform " + platformSelected.getName());
	  getContentPane().remove(platformScroller);
	  setupStandardVsCustom();
	}
	break;
      case SELECT_STANDARD_VS_CUSTOM:
	/* No check since this option starts with a default of 'typical'. */
	getContentPane().remove(standardVsCustomScroller);
	if (typicalInstall) {
	  if (debug) 
	    System.out.println("Making a typical installation.");
	  setupOptionOptions(bundleSelected);  
	} else {
	  if (debug)
	    System.out.println("Making a custom installation with individual components");
	  setupSelectFromAll(bundleSelected);
	}
	break;
      case SELECT_FROM_AMONG_ALL_COMPONENTS:
	if (optionalComponentsSelected != null) {
	  if (debug)
	    System.out.println("Selected some component(s)");
	  getContentPane().remove(selectFromAllScroller);
	  setupOptionOptions(bundleSelected);
	}
	break;
      case SELECT_OPTIONS:
	/* No check since these are optional. */
	getContentPane().remove(optionsScroller);
	setupClientPack(bundleSelected);
	break;
      case SELECT_CLIENT_PACK:
	if ((clientsComponentSelected != null) || (!typicalInstall)) {
	  getContentPane().remove(clientOptionsScroller);
	  setupOtherOptions_2(bundleSelected);
	}
	break;
      case SELECT_OTHER_OPTIONS_2:
	if ((otherComponent_2 != null) || (!typicalInstall)) {
	  getContentPane().remove(otherOptions_2Scroller);
	  setupOtherOptions_3(bundleSelected);
	}	
	break;
      case SELECT_OTHER_OPTIONS_3:
	if ((otherComponent_3 != null) || (!typicalInstall)) {
	  getContentPane().remove(otherOptions_3Scroller);
	  setupOtherOptions_4(bundleSelected);
	}	
	break;
      case SELECT_OTHER_OPTIONS_4:
	if ((otherComponent_4 != null) || (!typicalInstall)) {
	  getContentPane().remove(otherOptions_4Scroller);
	  setupOtherOptions_5(bundleSelected);
	}	
	break;
      case SELECT_OTHER_OPTIONS_5:
	if ((otherComponent_5 != null) || (!typicalInstall)) {
	  getContentPane().remove(otherOptions_5Scroller);
	  setupOtherOptions_6(bundleSelected);
	}	
	break;
      case SELECT_OTHER_OPTIONS_6:
	if ((otherComponent_6 != null) || (!typicalInstall)) {
	  getContentPane().remove(otherOptions_5Scroller);
	  setupReview();
	}	
	break;
      case REVIEW:
	getContentPane().remove(resultsScroller);
	getAndDisplayLicenseKey();
	break;
      case LICENSE_CODE:
	getContentPane().remove(finalPanel);
	setupFamilyOptions();
	break;
      default:
	if (debug)
	  System.out.println("!! Select Button: unknown mode");
      }
    }
  }


  /* Redo what we just did. */
  class GoBackListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      goBackAction(e);
    }
    private void goBackAction(ActionEvent e) {
      if (debug)
	System.out.println("Going back: mode is " + currentMode());
      switch (mode) {
      case SELECT_FAMILY:
	//getContentPane().remove(familyScroller);
	break;
      case SELECT_BUNDLE:
	getContentPane().remove(bundleScroller);
	setupFamilyOptions();
	break;
      case SELECT_PLATFORM:
	getContentPane().remove(platformScroller);
	clearComponentSelectionsIfNecessary();
	setupBundleOptions(familySelected);		
	break;
      case SELECT_STANDARD_VS_CUSTOM:
	getContentPane().remove(standardVsCustomScroller);
	clearComponentSelectionsIfNecessary();
	setupPlatformOptions(bundleSelected);
	break;
      case SELECT_FROM_AMONG_ALL_COMPONENTS:
	getContentPane().remove(selectFromAllScroller);
	setupStandardVsCustom();
	break;
      case SELECT_OPTIONS:
	getContentPane().remove(optionsScroller);
	if (typicalInstall)
	  setupPlatformOptions(bundleSelected);
	else
	  setupSelectFromAll(bundleSelected);
	break;
      case SELECT_CLIENT_PACK:
      case SELECT_OTHER_OPTIONS_2:
      case SELECT_OTHER_OPTIONS_3:
      case SELECT_OTHER_OPTIONS_4:
      case SELECT_OTHER_OPTIONS_5:
      case SELECT_OTHER_OPTIONS_6:
	getContentPane().remove(clientOptionsScroller);
	getContentPane().remove(otherOptions_2Scroller);
	getContentPane().remove(otherOptions_3Scroller);
	getContentPane().remove(otherOptions_4Scroller);
	getContentPane().remove(otherOptions_5Scroller);
	getContentPane().remove(otherOptions_6Scroller);
	// mimic logic in setupOptionOptions
	if ( bundleSelected.hasComponents() )
	  setupOptionOptions(bundleSelected);
	else {
	  mode = SELECT_OPTIONS;
	  goBackAction(e);
	}
	break;
      case REVIEW:
	getContentPane().remove(resultsScroller);
	// mimic logic in setupClientPack, which is implemented there
	// only for the forward direction. If we don't do this we loop.
	if ((clientComponents != null)
	    && (clientComponents.size() != 0)) 
	  setupClientPack(bundleSelected);
	else
	  setupOptionOptions(bundleSelected);
	break;
      case LICENSE_CODE:
	getContentPane().remove(finalPanel);
	setupReview();
	break;
      default:
	if (debug)
	  System.out.println("!! Back Button: unknown mode");
      }
      if (debug)
	System.out.println("  the mode now is " + currentMode());
    }
  }



  //--------------- The report writer -----------------------

  private String constructReport(boolean useHTML, boolean keyCreated) {
    String report = "";
    if (useHTML)
      report += "<html>";
        // See the comment above on the fact that the version is 
        // attached to the bundle and not to the family. (JPG 7/12/06)
    report += "Family: " + familySelected.getName() 
                         + " - " + bundleSelected.getVersion();
    report += (useHTML ? "<br>" : "\n");
    report += "Bundle: " + bundleSelected.getName();
    report += (useHTML ? "<br>" : "\n");
    report += "Platform: " + platformSelected.getName();
    report += (useHTML ? "<br>" : "\n");
    if ((optionalComponentsSelected != null)
	&& (optionalComponentsSelected.size() > 0)) {
      if (typicalInstall)
	report += "Options: ";
      else
	report += "Components: ";
      if (useHTML)
	report += "<ul>";
      for (int i=0; i < optionalComponentsSelected.size(); i++) {
	if (useHTML)
	  report += "<li>";
	report += ((Component)optionalComponentsSelected.
		   elementAt(i)).getName();
	report += " ";
      }
      if (useHTML)
	report += "</ul>";
    }
    report += (useHTML ? "<br>" : "\n");
    if (clientsComponentSelected != null) {
      report += "License: ";
      report += clientsComponentSelected.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (otherComponent_2 != null) {
      report += "Option: ";
      report += otherComponent_2.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (otherComponent_3 != null) {
      report += "Option: ";
      report += otherComponent_3.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (otherComponent_4 != null) {
      report += "Option: ";
      report += otherComponent_4.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (otherComponent_5 != null) {
      report += "Option: ";
      report += otherComponent_5.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (otherComponent_6 != null) {
      report += "Option: ";
      report += otherComponent_6.getName();
      report += (useHTML? "<br>" : "\n");
    }
    if (keyCreated)
      report += "License Key: " + theKey;
    if (useHTML)
      report += "</html>";
    else
      report += "\n";
    return report;
  }

  class IssueReportListener implements ActionListener {
    public void actionPerformed(ActionEvent e) {
      String report = constructReport( false, true );
      Report r = new Report(UI.this, report);
      r.writeReportToFile();
    }
  }


} 
