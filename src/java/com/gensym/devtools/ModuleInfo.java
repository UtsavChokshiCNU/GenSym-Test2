package com.gensym.devtools;

import java.util.Vector;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Enumeration;
import java.io.*;
import java.nio.charset.Charset;

public class ModuleInfo {

  public static final String MODULE_INFO_FILE_NAME = "package.info";
  public static final String INCLUDE_IN_MODULE_TAG = "include-in-module:";
  public static final String EXCLUDE_FROM_COMPILE_TAG = "exclude-from-compile:";
  public static final String EXCLUDE_FROM_JAVADOC_TAG = "exclude-from-javadoc:";
  public static final String DONT_JAR_PACKAGE_TAG = "dont-jar-package:";
  public static final String DONT_DELETE_JAVA_TAG = "dont-delete-java:";
  public static final String JAR_AS_BEAN_TAG = "jar-as-bean:";
  public static final String BEAN_GROUP_TAG = "bean-group:";
  public static final String PACKAGE_IS_PRIVATE_TAG = "package-is-private:";
  public static final String AUTHOR_TAG = "author:";

  /**
   * Two Obsolete fields here only to support old version of ModuleInfo
   * from BuildProductRepository
   */
  File sourceDirFile;
  File targetDirFile;

  File directoryFile;
  String packageName;
  Vector excludeFromCompileList;
  Vector excludeFromJavaDocList;
  Vector excludedFromJavaDocFiles;
  Vector jarAsBeansList;
  boolean dontJarPackage;
  boolean dontDeleteJava;
  boolean packageIsPrivate; // = false by default
  boolean include;
  Hashtable manifestData = new Hashtable();
  String[] productNames;
  String rootJavaDirName;
  String relativePath;
  private boolean hasInfo;
  private String author;
  private String[] javaFiles;
  private String[] classFiles;
  private boolean strictOwnership;
  private Hashtable dependencyTable = new Hashtable(); // keyed by class-name
  private String[] requiredPackages; // union

  /**
   * Obsolete constructor here only to support old version of ModuleInfo
   * from BuildProductRepository
   */
  ModuleInfo (File sourceDirFile,
	      String packagename,
	      Vector excludeFromCompileList,
	      Vector excludeFromJavaDocList,
	      Vector jarAsBeansList,
	      boolean dontJarPackage,
	      boolean dontDeleteJava,
	      boolean packageIsPrivate) {
    this.sourceDirFile = sourceDirFile;
    this.packageName = packagename;
    this.excludeFromCompileList = excludeFromCompileList;
    this.excludeFromJavaDocList = excludeFromJavaDocList;
    this.jarAsBeansList = jarAsBeansList;
    this.dontJarPackage = dontJarPackage;
    this.dontDeleteJava = dontDeleteJava;
    this.packageIsPrivate = packageIsPrivate;
  }

  public ModuleInfo (File moduleInfoFile,
		     String rootJavaDirName,
		     boolean strictOwnership) throws IOException {
    //System.out.println ("File = " + moduleInfoFile + ", Root = " + rootJavaDirName + ", DirFile = " + directoryFile);
    this.rootJavaDirName = new File(rootJavaDirName).getAbsolutePath();
    this.directoryFile = moduleInfoFile.getParentFile();
    this.strictOwnership = strictOwnership;
    if (moduleInfoFile.exists ())
      processFile(moduleInfoFile);
    getPackageName();
  }

  static Vector getList(String line) {
    Vector list = new Vector();
    StringTokenizer st = new StringTokenizer(line);
    while (st.hasMoreElements()) {
      String item = st.nextToken();
      //System.out.println("Token " + item);
      list.addElement(item);
    }   
    return list;
  }

  public String[] getProductNames() {
    return productNames;
  }

  public boolean isAssigned () {
    //System.out.println (this + ".isAssigned = " + (productNames != null));
    return productNames != null && productNames.length > 0;
  }

  /**
   * Whether or not the package.info was found
   */
  public boolean hasInfo () {
    return hasInfo;
  }

  /**
   * Returns the names of Java source files in directory
   */
  public String[] getJavaSources () {
    if (javaFiles == null)
      javaFiles = getFiles (".java");
    return javaFiles;
  }

  /**
   * Returns the names of Java class files in directory
   */
  public String[] getJavaClasses () {
    if (classFiles == null)
      classFiles = getFiles (".class");
    return classFiles;
  }

  /**
   * Whether or not the directory contains any Java source code
   */
  public boolean hasJavaSources () {
    return getJavaSources().length > 0;
  }

  /**
   * Whether or not the directory contains any Java classes
   */
  public boolean hasJavaClasses () {
    return getJavaClasses().length > 0;
  }

  /**
   * Whether or not we can find Java code in this directory
   */
  public boolean hasJava () {
    return hasJavaSources() || hasJavaClasses();
  }

  /**
   * WHether or not this package is included in the named product
   */
  public boolean isForProduct(String productName) {
    if (productNames == null)
      return false;
    int length = productNames.length;
    for (int i = 0; i< length; i++) {
      if (productName.equalsIgnoreCase(productNames[i]))
	return true;
    }
    return false;
  }

  /**
   * Only for friends
   */
  void setJavaClasses (String[] classFiles) {
    this.classFiles = classFiles;
  }

  /**
   * Only for friends
   */
  void setJavaSources (String[] javaFiles) {
    this.javaFiles = javaFiles;
  }

  /**
   * Returns the valid qualified package name of all classes
   */
  public String getPackageName() {
    if (packageName == null) {
      packageName = getRelativePath().replace(File.separatorChar, '.');
    }
    return packageName;
  }

  /**
   * Ships as source?
   */
  public boolean isSourceIncluded() {
    return dontDeleteJava;
  }

  /**
   * Whether the package is public (documented) or not
   */
  public boolean isPublic () {
    return !packageIsPrivate;
  }

  public String getAuthor () {
    return author;
  }

  public boolean hasAuthor () {
    return author != null;
  }

  public String getRelativePath() {
    if (relativePath == null) {
      String directoryFilePath = directoryFile.getAbsolutePath();
      if (directoryFilePath.equals(rootJavaDirName))
	relativePath = "";
      else
	relativePath = directoryFilePath.substring(rootJavaDirName.length() + 1);
    }
    return relativePath;
  }

  public File getSourceDirectory() {
    return directoryFile;
  }

  private void processFile(File moduleInfoFile) throws IOException {
	FileInputStream inStream = null;
	Reader fileIn = null;
	BufferedReader in = null;
    try {
      inStream = new FileInputStream(moduleInfoFile);	
      fileIn = new InputStreamReader(inStream, Charset.defaultCharset());
      in = new BufferedReader(fileIn);
      String line;
      while ((line = in.readLine()) != null) {
    	  processLine(line);
      }
    } finally {
  	  closeSilently(in);
 	  closeSilently(fileIn);
 	  closeSilently(inStream);
    }
    hasInfo = true;
  }
  
  private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println(e.toString());
      } 
  }

  private static final String BEAN_GROUP = "Bean-Group";

  // the first entry in the line is the name of the bean group
  private void dealWithBeanGroup(String line) {
    Vector list = getList(line);
    Enumeration en = list.elements();
    String beanGroupName = (String)en.nextElement();

    while (en.hasMoreElements()) {
      String filename = (String) en.nextElement();
      addManifestEntry(filename, BEAN_GROUP, beanGroupName);
    }
  }

  Vector getManifestData(String filename) {
    return (Vector)manifestData.get(filename);
  }

  private void storeProductNames(String line) {
    Vector productList = getList(line);
    int size = productList.size();
    if (size > 1 &&
	strictOwnership) // Pick primary product for package
      size = 1;
    productNames = new String[size];
    for(int i = 0; i < size; i++) {
      productNames[i] = (String)productList.elementAt(i);
    }
  }

  private void storeAuthor (final String line) {
    String trimmedLine = line.trim();
    int spaceIndex = trimmedLine.indexOf(' ');
    if (spaceIndex < 0)
      author = trimmedLine;
    else {
      if (trimmedLine.charAt(spaceIndex+1) == '*')
	author = trimmedLine.substring (0, spaceIndex);
    }
  }

  private void processLine(String line) {
    if (line.startsWith(INCLUDE_IN_MODULE_TAG)) {
      storeProductNames(line.substring(INCLUDE_IN_MODULE_TAG.length()));
    } else if (line.startsWith(EXCLUDE_FROM_COMPILE_TAG)) {
      excludeFromCompileList = getList(line.substring(EXCLUDE_FROM_COMPILE_TAG.length()));
    } else if (line.startsWith(EXCLUDE_FROM_JAVADOC_TAG)) {
      excludeFromJavaDocList = getList(line.substring(EXCLUDE_FROM_JAVADOC_TAG.length()));
    } else if (line.startsWith(JAR_AS_BEAN_TAG)) {
      jarAsBeansList = getList(line.substring(JAR_AS_BEAN_TAG.length()));
    } else if (line.startsWith(DONT_JAR_PACKAGE_TAG)) {
      dontJarPackage = true;
    } else if (line.startsWith(DONT_DELETE_JAVA_TAG)) {
      dontDeleteJava = true;
    } else if (line.startsWith(PACKAGE_IS_PRIVATE_TAG)) {
      packageIsPrivate = true;
    } else if (line.startsWith(BEAN_GROUP_TAG)) {
      dealWithBeanGroup(line.substring(BEAN_GROUP_TAG.length()));
    } else if (line.startsWith(AUTHOR_TAG))
      storeAuthor (line.substring(AUTHOR_TAG.length()));
  }

  private void addManifestEntry(String filename, String name, String value) {
//     System.out.println("adding to manifest. filename=" + filename +
// 		       ";name=" + name + ";value=" + value);
    Vector entryPairs = (Vector)manifestData.get(filename);

    if (entryPairs == null) {
      entryPairs = new Vector();
      manifestData.put(filename, entryPairs);
    }

    entryPairs.addElement(new Pair(name, value));
  }

  private String[] getFiles (String suffix) {
    String[] allFilesInDirectory = directoryFile.list ();
    Vector matchedFileNames = new Vector ();
    for (int i=0; i<allFilesInDirectory.length; i++) {
      String fileName = allFilesInDirectory[i];
      if (fileName.endsWith (suffix))
	matchedFileNames.addElement (fileName);
    }
    return (String[])matchedFileNames.toArray (new String[matchedFileNames.size()]);
  }

  void analyzeRequirements () {
    try {
      String pkgName = getPackageName();
      String[] classNames = getJavaClasses();
      File rootFile = new File (rootJavaDirName);
      Vector requiredPackagesList = new Vector();
      for (int i=0; i<classNames.length; i++) {
	//System.out.println ("Checking class : " + classNames[i]);
	String[] dependencies =
	  new ClassDependencyAnalyzer (rootFile, pkgName, classNames[i]).getRequiredClassNames();
	if (false)
	System.out.println ("Class " + pkgName + "." + classNames[i] + " requires -> " +
			    com.gensym.core.DebugUtil.printArray (dependencies));
	dependencyTable.put(classNames[i], dependencies);
	for (int j=0; j<dependencies.length; j++) {
	  String requiredClass = dependencies[j];
	  //System.out.println ("RC: <" + requiredClass + ">");
	  String pkgOfRequiredClass = determinePackageOfClass(requiredClass);
	  if (!requiredPackagesList.contains(pkgOfRequiredClass))
	    requiredPackagesList.addElement(pkgOfRequiredClass);
	}
      }
      requiredPackages = (String[])requiredPackagesList.toArray(new String[requiredPackagesList.size()]);
      if (false)
      System.out.println ("Package : " + getPackageName() + " -> requires -> " +
			  requiredPackagesList);
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private String determinePackageOfClass (String className) {
    return className.substring(0,className.lastIndexOf('.'));
  }

  ClassDependency[] getDependenciesOnPackage (String pkgName) {
    Enumeration keys = dependencyTable.keys();
    Vector matchingDependencies = new Vector();
    Vector matchingClasses = null;
    while (keys.hasMoreElements()) {
      if (matchingClasses == null)
	matchingClasses = new Vector();
      String className = (String)keys.nextElement();
      String[] requiredClasses = (String[])dependencyTable.get (className);
      for (int i=0; i<requiredClasses.length; i++) {
	String requiredClass = requiredClasses[i];
	String pkgOfRequiredClass = determinePackageOfClass(requiredClass);
	if (pkgName.equals(pkgOfRequiredClass))
	  matchingClasses.addElement(requiredClass);
      }
      if (!matchingClasses.isEmpty()) {
	String[] matchedClasses = (String[])matchingClasses.toArray(new String[matchingClasses.size()]);
	matchingDependencies.addElement (new ClassDependency (className,
							      matchedClasses));
	matchingClasses = null;
      }
    }
    return (ClassDependency[])matchingDependencies.toArray(new ClassDependency[matchingDependencies.size()]);
  }

  public String[] getRequiredPackages () {
    return requiredPackages; // clone!
  }

  public Vector getExcludeFromJavaDoc() {
    return excludeFromJavaDocList;
  }

  public boolean excludeFromJavaDoc(String fileName) {
	  boolean excludeCheck = !isPublic() || dontJarPackage() || dontDeleteJava();
    return excludeCheck ||
      BuildUtils.wildcardCompare(excludeFromJavaDocList, fileName) ||
      BuildUtils.wildcardCompare(excludeFromCompileList, fileName);
  }

  public boolean dontJarPackage() {
    return dontJarPackage;
  }

  public boolean dontDeleteJava() {
    return dontDeleteJava;
  }

  /**
   * Means is included in the staging area *instead* of in the jar.
   */
  public boolean isIncludedInStaging() {
    return dontJarPackage || dontDeleteJava;
  }

  public void copyTo(File target) throws IOException {
    FileFilter filter;
    if (dontDeleteJava()) {
      filter = BuildUtils.FILE_TYPES_TO_INCLUDE;
    } else if (dontJarPackage()) {
      filter = BuildUtils.FILE_TYPES_TO_INCLUDE_WITHOUT_JAVA;
    } else {
      return;
    }
    BuildUtils.copyDirectory(target, getSourceDirectory(), filter);
  }
  

  @Override
  public String toString() {
    return "ModuleInfo [package=" + getPackageName() +
      ";beans=" + jarAsBeansList + ";manifest-data=" + manifestData + "]";
  }

}
