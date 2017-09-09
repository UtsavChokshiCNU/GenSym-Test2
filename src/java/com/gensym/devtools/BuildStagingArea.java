package com.gensym.devtools;

import java.util.Vector;
import java.util.StringTokenizer;
import java.util.Enumeration;
import java.io.*;

import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.message.Trace;

/**
 * -rootJavaDirectory (required) the pathname from which package names
 *                    can be derived
 * -startingDirectory the directory to start looking for package.info files
 *                    (must be a subdirectory of -rootJavaDirectory).
 *                    If not specified, it defaults to -rootJavaDirectory.
 * -targetDirectory the root of the staging area.
 * -classesDirectory the directory to be placed in the CLASSPATH. Typically
                     this is a subdirectory of targetDirectory. If not supplied,
                     it defaults to targetDirectory/classes
 * -productName (required) the name of the product
 * -productDirectories a string of source directories
 *                     that are copied into the staging area,
 *                     each directory is separated by system path separator. 
 */
public class BuildStagingArea extends GensymApplication {

  ModuleInfoTool infoTool;
  Vector moduleInfos;
  String productName;
  String targetDirectoryPath;
  File targetDirectory;
  String classesDirectoryPath;
  File classesDirectory;
  File[] extraSourceDirectories;

  /**
   * @param fileNames a Vector of strings for the full
   * pathnames for the files.
   */
  static File[] getFiles(Vector fileNames) {
    int size = fileNames.size();
    File[] files = new File[size];
    for (int i = 0; i < size; i++) {
      files[i] = new File((String)fileNames.elementAt(i));
    }
    return files;
  }

  public BuildStagingArea(String[] args) {
    super(args);
    CmdLineArgHandler commandLineArguments =
      new CmdLineArgHandler (args);
    productName = commandLineArguments.getOptionValue("-productName");
    targetDirectoryPath = commandLineArguments.getOptionValue("-targetDirectory");
    this.targetDirectory = new File(targetDirectoryPath);
    classesDirectoryPath = commandLineArguments.getOptionValue("-classesDirectory");
    if (classesDirectoryPath == null)
      classesDirectoryPath = targetDirectoryPath + File.separator + "classes";
    classesDirectory = new File(classesDirectoryPath);
    String extraDirs = commandLineArguments.getOptionValue("-productDirectories");
    if (extraDirs != null)
      extraSourceDirectories = getFiles(BuildUtils.getList(extraDirs,
                               File.pathSeparator));
    String rootDir = commandLineArguments.getOptionValue ("-rootJavaDirectory");
    String startingPackage = commandLineArguments.getOptionValue ("-startingPackage");
    infoTool = new ModuleInfoTool(rootDir, startingPackage);
    ModuleInfo[] matchingModules =
      infoTool.getModules(new ModuleInfoTool.ProductNameFilter (new String[] {productName}));
    moduleInfos = new Vector();
    for (int i=0; i<matchingModules.length; i++)
      moduleInfos.addElement (matchingModules[i]);
  }

  public BuildStagingArea(ModuleInfoTool infoTool,
			  String productName,
			  String targetDirectoryPath,
			  String classesDirectoryPath,
			  String sourceDirectoriesString) {
    super(new String[] {});
    this.infoTool = infoTool;
    this.productName = productName;
    this.targetDirectoryPath = targetDirectoryPath;
    this.targetDirectory = new File(targetDirectoryPath);
    this.classesDirectoryPath = classesDirectoryPath;
    classesDirectory = new File(classesDirectoryPath);
    extraSourceDirectories =
      getFiles(BuildUtils.getList(sourceDirectoriesString));
    moduleInfos = infoTool.getModuleInfos(productName);
  }

  public BuildStagingArea(Vector moduleInfos,
			  String productName,
			  File targetDirectory,
			  File[] extraSourceDirectories) {
    super(new String[] {});
    this.moduleInfos = moduleInfos;
    this.productName = productName;
    this.targetDirectory = targetDirectory;
    this.extraSourceDirectories = extraSourceDirectories;
  }

  public static Vector getModulesToCopy(Vector moduleInfos) {
    Vector modulesToCopy = new Vector();
    int size = moduleInfos.size();
    for (int i = 0; i < size; i++) {
      ModuleInfo info = (ModuleInfo)moduleInfos.elementAt(i);
      if (info.isIncludedInStaging())
	modulesToCopy.addElement(info);
    }
    return modulesToCopy;
  }

  public void build() throws IOException {
    Vector modulesToCopy = getModulesToCopy(moduleInfos);
    copyModules(classesDirectory, modulesToCopy);
    copyExtraDirs(targetDirectory, extraSourceDirectories, BuildUtils.FILE_TYPES_TO_INCLUDE_WITH_DIRECTORIES);
  }

  /**
   * This will copy all the appropriate files from each module into
   * the classes directory, maintaining the sub-directory structure
   * for that module.
   */
  public static void copyModules(File classesDirectory, Vector modulesToCopy) throws IOException {
    int size = modulesToCopy.size();
    for (int i = 0; i < size; i++) {
      ModuleInfo info = (ModuleInfo)modulesToCopy.elementAt(i);
      String relativePath = info.getRelativePath();
      File newTargetDirectory = BuildUtils.ensureDirectory(classesDirectory,
							   relativePath);
      info.copyTo(newTargetDirectory);
    }
  }

  public static void copyExtraDirs(File targetDirectory,
				   File[] extraSourceDirectories,
				   FileFilter filter)
  throws IOException {
    if (extraSourceDirectories == null)
      return;
    int length = extraSourceDirectories.length;
    for (int i = 0; i < length; i++) {
      File extraDir = extraSourceDirectories[i];
      BuildUtils.copyDirectory(targetDirectory, extraDir, filter);
    }
  }

  public static void main(String[] args) {
    try {
      BuildStagingArea buildStagingArea =
	new BuildStagingArea(args);
      buildStagingArea.build();
    } catch (IOException ioe) {
      Trace.exception(ioe);
    }
  }
}
