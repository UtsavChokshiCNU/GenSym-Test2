// jh, 5/21/97.

// Here's how I tag a tree of Java directories from scratch on my PC.
// I believe the following are all the tags you need for NTW and
// JavaLink.

// jh, 8/8/97.  Pardon the double backslashes.  Apparently JDK 1.3
// tokenizes comments.

// cd \\bt\\jhnt\\util
// Edit the initialization of oneEtagsFilePath in this file 
//   to point to the util directory in your sandbox (could be cleaner)
// javac EtagsGenerator.java
// java EtagsGenerator c:\\bt\\jhnt\\java
// cd \\bt\\jhnt\\java
// tag-all-java-subdirs.bat

// Then in emacs 19.34 on my PC, I do 
//   meta-X visit-tags-table      to specify one of these tags tables
//   meta-dot                     to look for a Java class, interface or method
//   control-U meta-dot           to look for the next one
//   meta-X tags-reset-tags-files to start fresh if things stop working

// Note that our UNIX version of etags seems to lack the --regexp switch and
// doesn't grok Java automatically, so we have to build tagfiles on Windows/NT.

// So we're committed to the Windows/PC command lanugage. But .BAT files don't
// seem to be able to recurse through the directory tree on their own.  So this
// Java program will generate a .BAT file that does.

// The class EtagsGenerator takes a single command-line argument, the full
// pathname of the topmost directory in a tree containing .java files to be
// tagged.  It generates a file named tag-all-java-subdirs.bat in that topmost
// directory.  A full pathname is necessary so that the tags can work from
// multiple directories.

// tag-all-java-utils.bat has to be run to do the actual tagging.  This batch
// file takes no arguments, but is designed to be run in the topmost directory
// where it has been placed. [Maybe there is some way to run a command from a
// non-Applet java code? - jh, 8/8/97.  Indeed there is, under System or Runtime
// in java.lang.]

// tag-all-java-subdirs.bat visits each child directory and runs etags there,
// using helper .BAT file named by oneEtagsFilePath, currently
// util\\tag-a-java-dir.bat.  tag-all-java-subdirs.bat then deposits a forwarding
// TAGS file in the child directory that does nothing except point to the TAGS
// file at the topmost directory.

import java.io.*;

class EtagsGenerator {
  static String batFileName = "tag-all-java-subdirs.bat";
  static String oneEtagsFilePath 
    = "c:\\bt\\jhnt\\util\\tag-a-java-dir.bat";
  
  public static void main(String[] args) {
    File thisDirectory;

    // Check the command-line argument.
    if (args.length < 1) {
      System.out.println("usage: EtagsGenerator <directory>");
      return;
    }

    // Do some checking on the directory we're supposed to put the
    // batch file.
    try {
      thisDirectory = new File(args[0]);
    } catch (NullPointerException e) {
      System.out.println("Starting with empty string: " + e);
      return;
    }
    if (!thisDirectory.isDirectory()) {
      System.out.println(args[1] + " is not a directory");
      return;
    }

    // Open an output printing stream to the batch file.
    File batFile = new File(thisDirectory, batFileName);
    FileWriter batFileWriter;
    try {
      batFileWriter = new FileWriter(batFile);
    } catch (IOException e) {
      System.out.println
	("Can't open output to " + batFile.getAbsolutePath());
      return;
    }
    PrintWriter batFileStream 
      = new PrintWriter(new BufferedWriter(batFileWriter));

    // At this point, we are writing a valid batch file.

    // Prevent the interpreter from echoing the batch file commands.
    batFileStream.println("@echo off");
    batFileStream.println("");

    // Add comment to forestall manual editing.
    batFileStream.println
      ("rem automatically generated by EtagsGenerator.java");
    batFileStream.println ("rem   DO NOT EDIT");
    batFileStream.println("");

    // Define a name for the command that runs the etags executable.
    batFileStream.println("setlocal");
    batFileStream.println
      ("set ETAGS= \\emacs-19.34\\bin\\etags.exe --language=none ");
    batFileStream.println("");

    // Define a name for the helper batch that tags a single directory.
    batFileStream.println("set TAGONE= " + oneEtagsFilePath);
    batFileStream.println("");

    // Emit commands to delete the old TAGS file, since we will be
    // appending to it.
    File tagsFile = new File(thisDirectory, "TAGS");
    String tagsFileName = tagsFile.getAbsolutePath();
    batFileStream.println
      ("if exist " + tagsFileName + " del " + tagsFileName);

    // Store the current directory, since we'll be cd'ing all over the
    // place.
    batFileStream.println("pushd .");
    batFileStream.println("");

    // Start walking the directory tree.
    emitOneEtags(0, thisDirectory, batFileStream, tagsFileName);

    // Clean up.
    batFileStream.println("endlocal");
    batFileStream.println("popd");

    // Erratic things happen (e.g., blank output files) unless this is
    // done here rather than implicilty in some finalize() method.
    batFileStream.close();
  }

  private static void emitOneEtags
    (int level, 
     File thisDirectory, 
     PrintWriter batFileStream, 
     String tagsFileName)
  {
    String thisDirname = thisDirectory.getAbsolutePath();

    // Go to the directory being tagged.
    batFileStream.println("cd " + thisDirname);

    // Emit command to append tags for this directory to the topmost
    // TAGS file.
    batFileStream.println
      ("call %TAGONE% " + tagsFileName + " " + thisDirname);

    // Emit command that deposits a TAGS file that forwards to the
    // topmost TAGS file.
    if (level > 0) {
      String tagDir = "";
      for (int i = 0; i < level; i++) {
	tagDir = tagDir + "..\\";
      }
      batFileStream.println("%ETAGS% --include=" + tagDir + "TAGS");
    }
    batFileStream.println("");

    // Get subdirectory names and recurse.
    String[] subdirNames = thisDirectory.list();
    if (subdirNames != null) {
      for (int i = 0; i < subdirNames.length; i++) {
	// we know some directories won't contain Java code.
	if (!(subdirNames[i].equals("CVS") ||
	      subdirNames[i].equals("doc")))
	  {
	   File subDirectory = new File(thisDirectory, subdirNames[i]);
	   if (subDirectory.isDirectory()) {
	     emitOneEtags
               (level + 1, subDirectory, batFileStream, tagsFileName);
	   }
	  }
      }
    }
  }
}
