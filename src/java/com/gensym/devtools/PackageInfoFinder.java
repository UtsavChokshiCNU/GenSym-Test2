package com.gensym.devtools;

import java.io.File;

/**
 * This file will find all Package.info files.
 */

public class PackageInfoFinder {
  static boolean FOUND = false;

  public static void main(String[] args) {
    if ((args.length == 0)) {
      System.out.println("Please specify a directory as an argument");
      System.exit(0);
    }
    FindPackageFiles(args[0]);
  }
  
  static void FindPackageFiles(String targetDirName) {
    FOUND = false;
    File targetDir = new File (targetDirName);
    String dirList[] = targetDir.list();
    if (dirList == null) return;
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDir.getAbsolutePath()+File.separator+filename;
      File sourceFile = new File(targetFilename);
      if (sourceFile.isDirectory() && (!filename.equals("CVS"))) {
        FindPackageFiles(targetFilename);
      }
      if (filename.equals("package.info")) {
        //System.out.println("Found Package.info in: " + targetDirName);
        FOUND = true;
        break;
      }
    }
    if (!FOUND)
      System.out.println("** No Package.info in: " + targetDirName);
  }
}
