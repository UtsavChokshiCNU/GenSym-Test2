/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 LicenseKey.java
 *
 * @author David McDonald
 * work initiated 6/29/00
 *
 *   v1.0 July...September 2000
 *
 *   v1.1 October 17, 2000  -- Fixes bugs in the definition of the key, 
 *      i.e. keys made with 1.0 were not working on Solaris boxes.
 *      and initially weren't working at all because of an incorrect
 *      constant burned in for the syntax version.
 *         Also provided reasonable scrolling and the capacity to
 *      make 'custom' serial numbers where the set of 'standard' 
 *      bundle components was exposed as a screen of checkboxes
 *      and could be individually selected.
 *
 *   v1.2 October 27, 2000 -- Fixes disconnects in the paths taken when 
 *      'backing up'. Allows you to get through the 'number of clients'
 *      choice without picking on if it's a custom install. Fixes hang
 *      at the 'pick two options' screen when the bundle has no options.
 *
 *   v1.3 December 29, 2000 -- Adds a property to the call to java in the
 *      script that lets you predefine the location where you want the
 *      log to be written. Makes the select button the default for faster
 *      navigation. Turned off the 'go back' button because of a bug.
 *
 *   v1.4 ??? -- Fixes the 'go back' bugs.
 */


/* 2do:
 *  - fix bugs in backup: why is the mode occasionally 'unknown' and
 *      add more cases where choices should be forgotten, e.g. when
 *      making a whole new serial#.
 *  - Add an initial screen where they get typein boxes
 *      to specify the name of the log file and to optionally add
 *      additional information to it.
 *  - Rework the interaction with the native code so we can do this
 *      via package-relative calls like we really should
 */

//package com.gensym.bundle;

import javax.swing.JFrame;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

public class LicenseKey {

    static final boolean debug = true;

    static JFrame frame;
    static Families theFamilies;
    static Platforms thePlatforms;


    /* Establish the set of options by having the family
     * description files read in, then set the ball rolling
     * by bringing up the frame. From here on out everything
     * is event driven by the user. */
    public static void main(String[] args) 
    throws FileNotFoundException, IOException {
	initializePlatforms();
	initializeFamilyFiles( args[0] );
	frame = new UI(theFamilies);
    }


    /* loop through all of the files in the directory
     * that have a particular suffix indicating that they
     * are renderings of the data in a family descriptor file.
     * On each one, get it parsed and added in.
     */
    private static void initializeFamilyFiles (String directory) 
    throws FileNotFoundException, IOException {
	theFamilies = new Families();

	File dir = new File(directory);
	/* package these checks into FilenameFilter somehow ? */
	if ( ! dir.exists() )
	    throw new FileNotFoundException(directory + " does not exist.");
	if ( ! dir.isDirectory() )
	    throw new IOException(directory + " is not a directory.");

	String[] files = dir.list(); // add filter for an extension ?
	for ( int i = 0; i < files.length; i++ ) {
	    String filename = files[i];
	    String namestring = dir.getPath() + File.separator + filename;
	    if (debug)
		System.out.println("Reading " + namestring);
	    ReadFamilyFileData.readFamily(namestring, theFamilies);
	}
    }

    private static void initializePlatforms() {
	thePlatforms = new Platforms();
	/* N.b. These spellings come from the spec. in parse-family-file
	 * and the numbers come from codes.h -- if they don't match we're
	 * in trouble. */
	thePlatforms.addPlatform( new Platform("intelnt", 0));
	thePlatforms.addPlatform( new Platform("sparcsol", 1));
	thePlatforms.addPlatform( new Platform("aix", 2));
	thePlatforms.addPlatform( new Platform("hpux", 3));
	thePlatforms.addPlatform( new Platform("linux", 4));
	thePlatforms.addPlatform( new Platform("alphaosf", 5));
	thePlatforms.addPlatform( new Platform("hpia64", 6));
    }

    public static Platform platformNamed(String name) {
	return thePlatforms.platformNamed(name);
    }

}
