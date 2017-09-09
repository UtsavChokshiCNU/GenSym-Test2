/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Report.java
 *
 */

//package com.gensym.bundle;

import java.awt.Component;
import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;
import javax.swing.JFileChooser;

public class Report {

  static final boolean debug = true;

  String report;
  Component parent;

  public Report(Component parent, String report) {
    this.parent = parent;
    this.report = report;
  }

  void writeReportToFile() {
    try {
      File f = identifyFile();
      if (debug)
	System.out.println("Writing report to: " + f);
      if (f != null) {
	BufferedWriter b = new BufferedWriter( new FileWriter(f) );
	b.write(report, 0, report.length());
	b.close();
      }
    } catch (FileNotFoundException fnf) {
      if (debug)
	problem("File not found: " + fnf);
    } catch (IOException io) {
      if (debug)
	problem("IOException: " + io);
    }
  }


  static final String NOT_SPECIFIED = "The directory for log files was not specified";
  static final String NOT_THERE = "The user's launch directory property is missing.";

  /* Determine whether we're getting the directory from the designated
   * property or from the default.
   */
  private File identifyFile() {
    Properties props = System.getProperties();
    //props.list(System.out);
    String directory = props.getProperty("logs", NOT_SPECIFIED); // deliberate

    if (directory.equals(NOT_SPECIFIED)) {
      directory = props.getProperty("user.dir", NOT_THERE); // default
      if (directory.equals(NOT_THERE))
	problem("The default location for logs, the Java property user.dir is " +
		"missing. Use the 'logs' property instead.");
    }
    return constructFileFromData(directory);
  }


  /* Vet the pathname.
   */
  private File constructFileFromData(String directoryOrPathName) {
    File f = new File(directoryOrPathName);
    if ( !f.exists() ) {
      problem("The location " + directoryOrPathName + " does not exist");
      return null; // compiler doesn't know that we're throwing
    }
    else {
      if ( !f.canWrite() ) {
	problem("Can't write to " + directoryOrPathName);
	return null;
      }
      else {
	if ( f.isDirectory() )
	  return generateFilename(directoryOrPathName);
	else
	  return f;
      }
    }
  }

  /* If needed, generate a filename from today's date.
   */
  private File generateFilename(String directoryName) {
    Date now = new Date();
    SimpleDateFormat formatter = new SimpleDateFormat("yy-MMM-d hh-mm-ss");
    String time = formatter.format(now);
    if (directoryName.charAt(directoryName.length() - 1) != '\\') {
      directoryName += "\\";
    }
    String pathnamestring = directoryName + time + ".doc";
    if (debug)
      System.out.println("Pathnamestring: " + pathnamestring);
    return new File(pathnamestring);
  }


  // #+obsolete / unused
  /* If the locations where the log files are to be stored and the
   * file names to use were going to vary a lot, then this might
   * be a good way to go but as it stands (and given that there
   * appears to be a Java problem) I'm not using it.
   */
  private File lastFileOpened = null;
  // This pattern is supposed to take you to the same directory/file
  // as you used last time, but it's not working.

  private File getFileFromFileChooser() {
    JFileChooser chooser;
    if (lastFileOpened != null)
      chooser = new JFileChooser(lastFileOpened);
    else
      chooser = new JFileChooser();
    chooser.setApproveButtonText("log file to use");

    int returnValue = chooser.showOpenDialog(parent);
    if ( returnValue == JFileChooser.APPROVE_OPTION ) {
      File selection = chooser.getSelectedFile();
      if (selection != null) {
	lastFileOpened = selection;
	System.out.println("lastFileOpened = " + selection.toString());
      }
      return selection;
    }
    else if ( returnValue == JFileChooser.CANCEL_OPTION )
      return null;
    else
      return null;
  }


  //--------- An abstraction to report problems to the user --

  private void problem(String description) {
    if (debug)
      System.out.println("Problem: " + description);
    throw new BadReportLocation(description);
  }

  /**
   * @undocumented -- Gensym internal use only
   */
  public class BadReportLocation extends NullPointerException {
    public BadReportLocation(String description) {
      super(description);
    }
  }


}
