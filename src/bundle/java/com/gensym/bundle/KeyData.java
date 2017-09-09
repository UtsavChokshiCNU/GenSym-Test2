/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KeyData.java
 *
 */

//package com.gensym.bundle;

import java.util.Vector;


public class KeyData {

    private boolean debug = true;

    private int syntaxVersion;
    private int family_id;
    private int bundle_id;
    private int operatingSystemID;
    private byte[] componentArray = new  byte[68];

    static {
	System.loadLibrary("keyGenerator");
    }

    // The final arg, typicalinstall, if true, means to take all the 
    // required components and the selected optional components.  If false,
    // it means take just the optional components.  In the later case, it
    // is expected that the "required" components will be the optional 
    // components list.
    public KeyData (Family f, Bundle b, 
		    Platform p, Vector optionalComponentsSelected,
		    Component clientsComponentSelected,
		    Component option_2, Component option_3, Component option_4,
		    Component option_5, Component option_6,
		    boolean typicalInstall) {

	this.syntaxVersion = f.getVersion();
	operatingSystemID = p.getId();
	family_id = f.getIndex();
	bundle_id = b.getID();

	if (debug)
	    System.out.println
		("Sending to License Server: " +
		 "\n  Installer version: "  + syntaxVersion +
		 "\n  Family: " + f.getName() + "  id: " + family_id +
		 "\n  Bundle: " + b.getName() + "  id: " + bundle_id +
		 "\n  O/S: " + p.getName() + "  id: " + operatingSystemID );

	/* Fill the components array. it's mostly empty, so we start 
	 * by zero'ing everything. Then we fill it with 1's where there 
	 * are components. */
	for (int i=0; i < componentArray.length; i++) {
	    componentArray[i] = 0;
	}

	/* We always include the standard components of the bundle, unless
	   typicalInstall is false, in which case they can be customized. */
	Vector allTheComponents = b.getComponents();
	if (debug)
	    System.out.println("  Setting bits for required components:");
	for (int i=0; i < allTheComponents.size(); i++) {
	  Component c = (Component)allTheComponents.elementAt(i);
	  boolean optional = c.isOptional();
	  boolean licensing = c.isLicensingComponent();
	  boolean selected
	    = (typicalInstall || optionalComponentsSelected.contains(c));

	  int group = c.getButtonGroup();
	    
	  if (selected && !optional && !licensing)
	    {
	      if (debug)
		System.out.println("   Bit# " + c.getIndex() + "  " + c.getName());
	      componentArray[ c.getIndex() ] = 1;
	    }
	}

	if (debug)
	    System.out.println("  Setting bits for options:");
	Vector all_option_components = b.getOptionalComponents();
	for (int i=0; i < optionalComponentsSelected.size(); i++) {
	    Component c = (Component)optionalComponentsSelected.elementAt(i); 
	    int index = c.getIndex();
	    if (all_option_components.contains(c)) // be sure it's a true "option" component
	      {
		if (debug)
		  System.out.println("   Bit# " + index + "  " + c.getName());
		componentArray[index] = 1;
	      }
	}

	if (debug)
	    System.out.println("  Setting bit for client pack.");
	if (clientsComponentSelected != null) {
	    int index = clientsComponentSelected.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   clientsComponentSelected.getName());
	} else {
	    if (debug)
		System.out.println("     No client pack.");
	}
	if (option_2 != null) {
	    int index = option_2.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   option_2.getName());
	} else {
	    if (debug)
		System.out.println("     No option 2.");
	}
	if (option_3 != null) {
	    int index = option_3.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   option_3.getName());
	} else {
	    if (debug)
		System.out.println("     No option 3.");
	}
	if (option_4 != null) {
	    int index = option_4.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   option_4.getName());
	} else {
	    if (debug)
		System.out.println("     No option 4.");
	}
	if (option_5 != null) {
	    int index = option_5.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   option_5.getName());
	} else {
	    if (debug)
		System.out.println("     No option 5.");
	}
	if (option_6 != null) {
	    int index = option_6.getIndex();
	    componentArray[index] = 1;
	    if (debug)
		System.out.println("    #" + index + " - " +
				   option_6.getName());
	} else {
	    if (debug)
		System.out.println("     No option 6.");
	}

	// Use this if the bit alignment gets off -- iterate up to the highest component
	//	if (debug)
	//	    for (int i=0; i<20; i++) {
	//		System.out.println("Bit: " + i + " value: " +
	//				   componentArray[i] );
	//	    }


    }

    public String getKey() {
	return getKey1(syntaxVersion, family_id, bundle_id,
		       operatingSystemID, componentArray);
    }

    public native String getKey1 (int syntaxVersion, int family_id, 
				  int bundle_id, int operatingSystemID, 
				  byte[] componentArray);

}
