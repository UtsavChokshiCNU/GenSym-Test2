package com.gensym.devtools;

import java.util.Vector;
import java.util.StringTokenizer;
import java.util.Arrays;
import java.io.*;

import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.core.DebugUtil;

/**
 * This class is primarily intended to be a command-line tool to get information
 * about our java modules. If programmatic access is required (for other tools),
 * more public entry-points need to be added.
 * <p>
 * The class collects a list of modules (based on the starting package)
 * by traversing a hierarchy of directories. It must always be provided
 * a root directory (can be extended to multiple directories and jars
 * with some effort). The -norecurse option limits the traversal to a
 * single module. The command-line options are as follows:
 * <ul>
 * <li> <code>-root &lt;root-directory&gt; </code> Specifies the directory
 *      that forms the base of all the modules.
 * <li> <code>-startPackage &lt;package-name&gt;</code> Limit the
 *      traversal to the named package, and possibly its sub-packages.
 * <li> <code>-norecure</code> Do not traverse sub-packages.
 * </ul>
 * <p>
 * A number of predicates are provided to narrow down the output
 * based on information gathered about the collected modules.
 * These predicates are applied with an AND operator so that
 * <code>predicate1 predicate2</code> implies <code>predicate1 &&
 * predicate2</code>. <em>See -exclude for exception.</em>. The 
 * predicates by default are specified by using -option syntax.
 * They can be negated by using +option. The
 * currently known predicates available as options are:
 * <ul>
 * <li> <code>-+inProduct &lt;productName&gt; {, &lt;productName&gt;}*</code>
 *      whether the module is included in one of the named products (p1 OR p2 OR p3 ...).
 *      Negation?
 * <li> <code>-+underProduct &lt;productName&gt; {, &lt;productName&gt;}*</code>
 *      whether the module is required by one of the named products
 *      Negation?
 * <li> <code>-+author &lt;author-name&gt;</code> whether the module is authored by the
 *      specified person.
 *      Negation?
 * <li> <code>-+hasInfo</code> whether or not there is a package.info for the module.
 * <li> <code>-+assigned</code> whether or not the module is assigned to any product.
 * <li> <code>-+isPublic</code> whether or not the module is public.
 * <li> <code>-+assignedMultiple</code> whether or not the product is assigned to multiple products.
 * <li> <code>-+shipsSource</code> whether or not the module is shipped as source code.
 * <li> <code>-+hasJavaSources</code> whether or not there is any Java source code in the module.
 * <li> <code>-+hasJavaClasses</code> whether or not there are any Java class files in the module.
 * <li> <code>-+hasJava</code> -hasJavaSources || -hasJavaClasses
 * </ul>
 * The <code>-exclude</code> option is used to negate the predicate list. i.e. it
 * returns every module that does <em>not</em> match the given conditions. The
 * combination of <code>-exclude</code> and <code>+&lt;option&gt;</code> enables predicates
 * that can be combined in conjunction. For example, <code> +predicate1 +predicate2 -exclude</code>
 * is equivalent to <code> predicate1 || predicate2</code>.
 * <p>
 * After filtering the modules through the predicates, the class performs one of
 * a number of actions listed below.
 * <ul>
 * <li> <code>-detail {auto | &lt;detail-format-spec&gt;0 | 1 | 2 | ...}</code> Prints out information about
 *      the modules with differing levels of detail.
 * <li> <code>-check</code> Checks the modules for dependence consistency.
 * <li> <code>-exec &lt;command&gt;</code> Runs the command on the matched modules.
 *      Magic arguments are: <ul>
 *                           <li> <code>%m</code> = Module name.
 *                           <li> <code>%p</code> = product names.
 *                           <li> <code>%P</code> = primary product name.
 *                           <li> <code>%a</code> = author.
 *                           <li> <code>%d</code> = directory.
 *                           </ul>
 * </ul>
 * <p>
 * There is also a <code>-checkProducts</code> option that checks for unknown
 * products.
 *
 * Example that lists java packages required by pinpoint:
 *
 *   java com.gensym.devtools.ModuleInfoTool
 *     -root d:\bt\paf\nm
 *     -startPackage com.gensym
 *     -underProduct pinpoint
 *     -isPublic
 *     -hasJavaSources
 *     +shipsSource
 *     -detail packageNames
 * <p>
 */
/*
 * -root the pathname from which package names can be derived (required)
 * -startPackage the package to start looking in (optional)
 * -norecurse false by default
 * -+inProduct x1 x2 ... (x1 | x2 | ...)
 * -+underProduct x1 x2 ... (x1 | x2 | ...)
 * -+author a1 a2 ... (a1 | a2 | ...)
 * -+hasInfo
 * -+assigned
 * -+isPublic
 * -+assignedMultiple
 * -+hasAuthor
 * -+shipsSource
 * -+hasJavaSources
 * -+hasJavaClasses
 * -+hasJava (-hasJava = -hasJavaSources || -hasJavaClasses)
 * -exclude
 * -detail [0] {auto | 0 | 1 | 2 | .. }
 * -exec cmd (command script: magic args %p=product, %m=module, %d=directory %a=author)
 */

  
public class ModuleInfoTool extends GensymApplication {

  private String rootJavaDirPath;
  private String startingPackage;
  private boolean strictPackageOwnership;
  private Vector collectedModules,
                 secondaryModules; // Not under the startPackage hierarchy
  private ProductDependencyAnalyzer pda = new ProductDependencyAnalyzer ();

  private static final String
    CLASS_SUFFIX = ".class",
    JAVA_SUFFIX  = ".java";

  public ModuleInfoTool (String rootJavaDirPath,
			 String startingPackage,
			 boolean strictPackageOwnership) {
    super(new String[] {});
    if (rootJavaDirPath == null)
      throw new NullPointerException ("root path for Java cannot be null");
    this.rootJavaDirPath = rootJavaDirPath;
    this.startingPackage = startingPackage;
    this.strictPackageOwnership = strictPackageOwnership;
  }

  public ModuleInfoTool (String rootJavaDirPath,
			 String startingPackage) {
    this (rootJavaDirPath, startingPackage, false); // this may become "true" at some point
  }

  private ModuleInfoTool (String args[]) {
    super(args);
  }

  public void list (ModuleInfoFilter filter, String detailSpec) {
    loadModules ();
    Vector infos = getModuleInfos();
    ModuleInfo info = null;
    int j = 0;
    for (int i=0; i<infos.size(); i++) {
      if (filter.include (info = (ModuleInfo)infos.elementAt(i)))
	listModule (j++, info, detailSpec);
    }
  }

  private void listModule (int count, ModuleInfo info, String detailSpec) {
    if (detailSpec.equals ("0")) // equiv to "%4# %m\n"
      System.out.println (pad (Integer.toString (count), '0', 4) + " " + info.getPackageName());
    else if (detailSpec.equals ("1")) // equiv to "%4# %m in %p by %a\n"
      System.out.println (pad (Integer.toString (count), '0', 4) + " " + info.getPackageName() + " in " +
			  DebugUtil.printArray (info.getProductNames()) +
			  " by " + info.getAuthor());
    else if (detailSpec.equals ("2")) // equiv to "%4# %m in %p by %a with %#s Java files and %#c classes\n"
      System.out.println (pad (Integer.toString (count), '0', 4) + " " + info.getPackageName() + " in " +
			  DebugUtil.printArray (info.getProductNames()) + " by " +
			  info.getAuthor() + " with " +
			  info.getJavaSources().length + " Java files and " + info.getJavaClasses().length + " classes");
    else if (detailSpec.equals("packageNames")) {
      System.out.println(info.getPackageName());
    } else { // custom
      notifyUnimplementedFeatureAndExit ("-detail auto");
    }	  
  }

  private String pad (String printString, char padChar, int fieldWidth) {// pad left
    int printStringWidth = printString.length();
    StringBuffer sb = new StringBuffer (fieldWidth);
    for (int i=fieldWidth; i>printStringWidth; i--)
      sb.append (padChar);
    return sb.append (printString).toString();
  }

  public void exec (ModuleInfoFilter filter, String execSpec) {
    loadModules ();
    Vector infos = getModuleInfos();
    ModuleInfo info = null;
    for (int i=0; i<infos.size(); i++) {
      if (filter.include (info = (ModuleInfo)infos.elementAt(i)))
	execCommand (info, execSpec);
    }
  }

  private void execCommand (ModuleInfo info, String execSpec) {
    // fill in code here :)
    notifyUnimplementedFeatureAndExit ("-exec <command>");
  }

  public ModuleInfo[] getModules (ModuleInfoFilter filter) {
    loadModules();
    Vector infos = getModuleInfos();
    Vector filteredModules = new Vector (infos.size());
    ModuleInfo info = null;
    int j = 0;
    for (int i=0; i<infos.size(); i++) {
      if (filter.include (info = (ModuleInfo)infos.elementAt(i)))
	filteredModules.addElement (info);
    }
    return (ModuleInfo[]) filteredModules.toArray (new ModuleInfo[filteredModules.size()]);
  }

  public Vector getModuleInfos() {
    return collectedModules;
  }

  public Vector getModuleInfos(String productName) {
    loadModules();
    Vector modulesForProduct = new Vector();
    for (int i = 0; i < collectedModules.size(); i++) {
      ModuleInfo info = (ModuleInfo)collectedModules.elementAt(i);
      if (productName == null || info.isForProduct(productName))
	modulesForProduct.addElement(info);
    }
    return modulesForProduct;
  }

  private void loadModules() {
    if (collectedModules == null) {
      String startingDirectoryPath = rootJavaDirPath;
      if (startingPackage != null)
	startingDirectoryPath = rootJavaDirPath + File.separator +
	  startingPackage.replace ('.', File.separatorChar);
      collectedModules = new Vector();
      File currentDirFile = new File(startingDirectoryPath);
      loadModuleInfo(currentDirFile, true);
    }
  }

  // guaranteed to get us an info for any package - even if not in hierarchy
  ModuleInfo findModuleInfoForPackage (String pkgName) {
    ModuleInfo module;
    for (int i=0; i<collectedModules.size(); i++)
      if ((module = (ModuleInfo)collectedModules.elementAt(i)).getPackageName().equals(pkgName))
	return module;
    if (secondaryModules != null) {
      for (int i=0; i<secondaryModules.size(); i++)
	if ((module = (ModuleInfo)secondaryModules.elementAt(i)).getPackageName().equals(pkgName))
	  return module;
    }
    secondaryModules = new Vector();
    String searchDirectoryPath = rootJavaDirPath + File.separator +
      pkgName.replace('.', File.separatorChar);
    File searchDirectory = new File (searchDirectoryPath);
    module = loadModuleInfo (searchDirectory, false); // force load, but not subpackages
    if (module != null) {
      collectedModules.removeElement (module);
      secondaryModules.addElement (module);
    }
    return module;
  }

  private ModuleInfo loadModuleInfo(File currentDirectory, boolean recurseSubModules) {
    if (!currentDirectory.isDirectory()) // can happen with malformed class references
      return null; //throw new RuntimeException ("No directory : " + currentDirectory);
    String[] dirContents = currentDirectory.list();
    ModuleInfo currentPackageModuleInfo = null;
    Vector classFiles = new Vector (), javaFiles = new Vector ();
    for (int i=0; i<dirContents.length; i++) {
      //File currentFile = dirList[i]; //new File(fullfilename);
      String fileName = dirContents[i];
      if (fileName.equals(ModuleInfo.MODULE_INFO_FILE_NAME)) {
	currentPackageModuleInfo = lookupModuleInfo(new File (currentDirectory, fileName));
      } else if (fileName.endsWith (CLASS_SUFFIX)) {
	classFiles.addElement (fileName.substring(0, fileName.length() - 6));
      } else if (fileName.endsWith (JAVA_SUFFIX)) {
	javaFiles.addElement (fileName.substring(0, fileName.length() - 5));
      } else {
	File currentFile = new File (currentDirectory, fileName);
	if (currentFile.isDirectory() &&
	    !excludeDirectory (fileName)) {
	//System.out.println ("Checking " + fileName);
	  if (recurseSubModules)
	    loadModuleInfo(currentFile, true);
	}
      }
    }
    if (currentPackageModuleInfo == null)
      currentPackageModuleInfo = lookupModuleInfo (new File(currentDirectory, ModuleInfo.MODULE_INFO_FILE_NAME));
    currentPackageModuleInfo.setJavaClasses ((String[])classFiles.toArray (new String[classFiles.size()]));
    currentPackageModuleInfo.setJavaSources ((String[])javaFiles.toArray (new String[javaFiles.size()]));
    return currentPackageModuleInfo;
  }

  private void checkPackages (ModuleInfoFilter filter) {
    loadModules ();
    Vector modulesList = getModuleInfos();
    for (int i=0; i<modulesList.size(); i++) {
      ModuleInfo module = (ModuleInfo)modulesList.elementAt(i);
      module .analyzeRequirements();
      if (filter.include (module)) {
	String[] productsOwningModule = module.getProductNames(); // only one when -strictOwnership - guaranteed non-null
	String[] reqdPackages = module.getRequiredPackages();
	System.out.println ("Required Packages of " + module.getPackageName() + " = " +
			    DebugUtil.printArray(reqdPackages));
	for (int j=0; j<reqdPackages.length; j++) {
	  String requiredPackage = reqdPackages[j];
	  if (ownershipCanBeDetermined(requiredPackage)) {
	    System.out.println ("Checking dependency on : " + requiredPackage);
	    ModuleInfo reqdPkgModule =
	      findModuleInfoForPackage(requiredPackage);
	    if (reqdPkgModule == null) {
	      System.out.println("Unloadable package " + requiredPackage +
				 " skipping ");
	      break;
	    }
	    String[] productsOwningReqdPackage =
	      reqdPkgModule.getProductNames();  // again only one when -strictOwnership
	    if (productsOwningReqdPackage == null)
	      System.out.println ("XXX[1] Module " + module.getPackageName() + " in products " +
				  DebugUtil.printArray(productsOwningModule) + " by " + 
				  module.getAuthor() + " requires package " +
				  requiredPackage + " which is not assigned to any product");
	    else {
	      if (productsOwningModule == null)
		System.out.println ("XXX[2] Module " + module.getPackageName() + " has no owners. Skipping dependencyChecks");
	      else {
		for (int k=0; k<productsOwningModule.length; k++) { // all of these should be consistent
		  String productToCheck = productsOwningModule[k];
		  String[] reqdProducts = pda.getProductsUnder (productToCheck);
		  Object common = arraysHaveCommonElement (reqdProducts, productsOwningReqdPackage);
		  if (common != null)
		    System.out.println ("Dependency OK -> " + common);
		  else {
		    System.out.println ("XXX[3] Module " + module.getPackageName() + " in product " +
					productToCheck + " by " +
					module.getAuthor () +
					" requires package " +
					requiredPackage + " belonging to " +
					DebugUtil.printArray (productsOwningReqdPackage) + " which is not in the required list " +
					DebugUtil.printArray (reqdProducts));
		    ClassDependency[] dependencies = module.getDependenciesOnPackage (requiredPackage);
		    for (int l=0; l<dependencies.length; l++) {
		      System.out.println ("XXX[4]   " + dependencies[l].dependentClassName + " requires " +
					  DebugUtil.printArray(dependencies[l].dependencies));
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }

  private void notifyUnimplementedFeatureAndExit (String feature) {
    System.err.println ("Feature '" + feature + "' not implemented yet. Exiting");
    System.exit (1);
  }

  private void checkProducts () {
    loadModules();
    String[] knownProducts = pda.getProducts();
    Arrays.sort (knownProducts);
    Vector modulesList = getModuleInfos();
    for (int i=0; i<modulesList.size(); i++) {
      ModuleInfo module = (ModuleInfo)modulesList.elementAt (i);
      String[] productsOwningModule = module.getProductNames(); // only one when -strictOwnership
      //System.out.println ("Module = " + module + ", Owners = " + DebugUtil.printArray(productsOwningModule));
      if (productsOwningModule != null) { // belongs to at least one product
	for (int j=0; j<productsOwningModule.length; j++) {
	  String productName = productsOwningModule[j];
	  if (Arrays.binarySearch(knownProducts, productName)<0)
	    System.out.println (module.getPackageName() + " belongs to unknown product " + productName);
	}
      }
    }
  }

  private Object arraysHaveCommonElement (Object[] array0, Object[] array1) {
    for (int i=0; i<array0.length; i++) {
      Object o = array0[i];
      for (int j=0; j<array1.length; j++) {
	if (o.equals(array1[j])) {
	  if (false)
	  System.out.println ("Comparing arrays : \n 1. " + DebugUtil.printArray(array0) + "\n2. " +
			      DebugUtil.printArray(array1) + "\n  CommonElement = " + o);
	  return o;
	}
      }
    }
    return null;
  }

  private boolean ownershipCanBeDetermined (String pkgName) {
	boolean isJavaPackage = pkgName.startsWith("java.") || pkgName.startsWith("javax.");
    
	if (isJavaPackage || pkgName.startsWith("com.sun.") ||
			pkgName.startsWith("sun.") || pkgName.startsWith("antlr")) {
      return false;
	}
	
    if (!pkgName.startsWith("com.gensym.")) {
      System.out.println ("Unknown package = " + pkgName);
      return false;
    } 
     
    return true;
  }


  private boolean excludeDirectory (String dirName) {
    return directoryNamesToExclude.contains (dirName);
  }

  private ModuleInfo lookupModuleInfo (File moduleInfoFile) {
    //System.out.println("Found module info at " + moduleInfoFile);
    try {
      ModuleInfo info = new ModuleInfo (moduleInfoFile, rootJavaDirPath, strictPackageOwnership);
      //System.out.println("info=" + info);
      collectedModules.addElement(info);
      return info;
    } catch (IOException e) {
      System.out.println(e.toString());
      e.printStackTrace();
      return null;
    }
  }

  public static void main(String[] args) {
    CmdLineArgHandler commandLineArguments = new CmdLineArgHandler (args);
    String rootJavaDirPath = commandLineArguments.getOptionValue("-root");
    String startingPackage = commandLineArguments.getOptionValue("-startPackage");
    boolean strictQ = commandLineArguments.getSwitchValue("-strict");
    ModuleInfoTool tool = new ModuleInfoTool(rootJavaDirPath, startingPackage, strictQ);

    ProductFilter productFilter = determineProductsForFilter (commandLineArguments);

    Boolean hasInfo             = determineHasInfoForFilter (commandLineArguments);

    Boolean assigned            = determineAssignedForFilter (commandLineArguments);

    Boolean hasClasses          = determineHasClassesForFilter (commandLineArguments);

    Boolean shipsSource         = determineShipsSourceForFilter (commandLineArguments);

    Boolean hasJavaSources      = determineHasJavaSourcesForFilter (commandLineArguments);

    Boolean isPublic            = determineIsPublicForFilter (commandLineArguments);

    Boolean isMultiplyAssigned  = determineIsMultiplyAssignedForFilter (commandLineArguments);

    AuthorFilter authorFilter   = determineAuthorsForFilter (commandLineArguments);

    Boolean hasAuthor           = determineHasAuthorForFilter (commandLineArguments);

    ModuleInfoFilter filter = new ModuleInfoFilter (productFilter.productNames,
						    productFilter.include,
						    authorFilter.authors,
						    authorFilter.include,
						    hasInfo,
						    assigned,
						    isMultiplyAssigned,
						    hasAuthor,
						    shipsSource,
						    hasJavaSources,
						    hasClasses,
						    isPublic,
						    !commandLineArguments.getSwitchValue ("-exclude"));

    String detailSpec = commandLineArguments.getOptionValue ("-detail");
    if (detailSpec != null)
      tool.list (filter, detailSpec);

    String execSpec = commandLineArguments.getOptionValue ("-exec");
    if (execSpec != null)
      tool.exec (filter, execSpec);

    boolean checkProductOption = commandLineArguments.getSwitchValue ("-checkProducts");
    if (checkProductOption)
      tool.checkProducts();

    boolean consistencyCheckOption = commandLineArguments.getSwitchValue ("-check");
    if (consistencyCheckOption)
      tool.checkPackages(filter);
    
    //System.out.println("mit modules=" + tool.getModuleInfos());
    //System.out.println("mit modules2=" + tool.getModuleInfos("core"));
  }

  private static ProductFilter determineProductsForFilter (CmdLineArgHandler cmdLine) {
    ProductFilter productFilter = new ProductFilter ();
    productFilter.include = true;

    String[] inProducts = cmdLine.getOptionValues ("-inProduct");
    if (inProducts == null)
      inProducts = cmdLine.getOptionValues ("-inProducts");
    String[] underProducts = cmdLine.getOptionValues ("-underProduct");
    if (underProducts == null)
      underProducts = cmdLine.getOptionValues ("-underProducts");
    
    if (inProducts != null &&
	underProducts != null)
      throw new RuntimeException ("Can't use both -inProduct and -underProduct");

    if (inProducts == null &&
	underProducts == null) {
      productFilter.include = false;
      inProducts = cmdLine.getOptionValues ("+inProduct");
      if (inProducts == null)
	inProducts = cmdLine.getOptionValues ("+inProducts");
      underProducts = cmdLine.getOptionValues ("+underProduct");
      if (underProducts == null)
	underProducts = cmdLine.getOptionValues ("+underProducts");
      
      if (inProducts != null &&
	  underProducts != null)
	throw new RuntimeException ("Can't use both +inProduct and +underProduct");
    }
    if (underProducts != null)
      inProducts = getRequiredProducts (underProducts);
    // check for valid product names
    if (inProducts != null)
      productFilter.productNames = inProducts;
    return productFilter;
  }

  private static AuthorFilter determineAuthorsForFilter (CmdLineArgHandler cmdLine) {
    AuthorFilter authorFilter = new AuthorFilter ();
    authorFilter.include = true;

    String[] authors = cmdLine.getOptionValues ("-author");
    if (authors == null)
      authors = cmdLine.getOptionValues ("-authors");
    if (authors == null) {
      authorFilter.include = false;
      authors = cmdLine.getOptionValues ("+author");
      if (authors == null)
	authors = cmdLine.getOptionValues ("+authors");
    }
    if (authors != null)
      authorFilter.authors = authors;
    return authorFilter;
  }

  private static String[] getRequiredProducts (String[] underProducts) {
    Vector products = new Vector ();
    addUniqueElements (underProducts, products);
    int i=-1;
    ProductDependencyAnalyzer pda = new ProductDependencyAnalyzer();
    while (++i<products.size()) {
      String product = (String)products.elementAt (i);
      String[] allRequiredProducts = pda.getProductsUnder (product);
      addUniqueElements (allRequiredProducts, products);
    }
    return (String[]) products.toArray (new String[products.size()]);
  }

  private static void addUniqueElements (String[] array, Vector v) {
    for (int i=0; i<array.length; i++)
      if (!v.contains(array[i]))
	v.addElement(array[i]);
  }

  private static Boolean determineHasInfoForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-hasInfo") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+hasInfo") ? Boolean.FALSE : null);
  }

  private static Boolean determineAssignedForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-assigned") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+assigned") ? Boolean.FALSE : null);
  }

  private static Boolean determineHasClassesForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-hasClasses") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+hasClasses") ? Boolean.FALSE : null);
  }

  private static Boolean determineHasAuthorForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-hasAuthor") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+hasAuthor") ? Boolean.FALSE : null);
  }

  private static Boolean determineShipsSourceForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-shipsSource") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+shipsSource") ? Boolean.FALSE : null);
  }

  private static Boolean determineHasJavaSourcesForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-hasJavaSources") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+hasJavaSources") ? Boolean.FALSE : null);
  }

  private static Boolean determineIsPublicForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-isPublic") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+isPublic") ? Boolean.FALSE : null);
  }

  private static Boolean determineIsMultiplyAssignedForFilter (CmdLineArgHandler cmdLine) {
    return cmdLine.getSwitchValue ("-assignedMultiple") ?
      Boolean.TRUE : (cmdLine.getSwitchValue ("+assignedMultiple") ? Boolean.FALSE : null);
  }

  private static Vector directoryNamesToExclude = new Vector ();
  static {
    String excludedDirectories = System.getProperty ("com.gensym.devtools.moduleInfo.excludedDirectories");
    if (excludedDirectories == null)
      excludedDirectories = "";
    excludedDirectories = "CVS|" + excludedDirectories;
    StringTokenizer tknzr = new StringTokenizer (excludedDirectories, "|", false);
    while (tknzr.hasMoreTokens())
      directoryNamesToExclude.addElement (tknzr.nextToken());
  }

  /**
   * A convenient generally useful subclass of ModuleInfoFilter
   */
  public static class ProductNameFilter extends ModuleInfoFilter {
    public ProductNameFilter (String[] productNames) {
      super (productNames, true,
	     null, true,
	     null, null, null, null, null, null, null, null, true);
    }
  }


  /**
   * Filter for determining matching modules for further operations
   */
  public static class ModuleInfoFilter {

    private String[] productNames, authors;
    private boolean includeByProduct, includeByAuthor, matching;
    private Boolean hasInfo, assigned, multiplyAssigned, hasAuthor, shipsSource, hasJavaSources, hasClasses, isPublic;

    public ModuleInfoFilter () {
      this (null, true, null, true, null, null, null, null, null, null, null, null, true);
    }

    public ModuleInfoFilter (String[] productNames,
			     boolean includeByProduct,
			     String[] authors,
			     boolean includeByAuthor,
			     Boolean hasInfo,
			     Boolean assigned,
			     Boolean multiplyAssigned,
			     Boolean hasAuthor,
			     Boolean shipsSource,
			     Boolean hasJavaSources,
			     Boolean hasClasses,
			     Boolean isPublic,
			     boolean matching) {
      this.productNames     = productNames;
      this.includeByProduct = includeByProduct;
      this.authors          = authors;
      this.includeByAuthor  = includeByAuthor;
      this.hasInfo          = hasInfo;
      this.assigned         = assigned;
      this.multiplyAssigned = multiplyAssigned;
      this.hasAuthor        = hasAuthor;
      this.shipsSource      = shipsSource;
      this.hasJavaSources   = hasJavaSources;
      this.hasClasses       = hasClasses;
      this.isPublic         = isPublic;
      this.matching         = matching;
    }

    @Override
    public String toString () {
      return "ModuleInfoFilter [productNames=" + DebugUtil.printArray (productNames) +
	"," + (includeByProduct ? "includeNamed" : "excludeNamed") + 
	",assigned=" + assigned +
	",shipsSource=" + shipsSource +
	",hasClasses=" + hasClasses +
	",isPublic=" + isPublic +
	",MATCHING=" + matching + "]";
    }

    boolean include (ModuleInfo module) {
      boolean inc = include0 (module);
      //System.out.println ("include (" + module + ") through " + this + " = " + inc);
      return inc;
    }

    private boolean include0 (ModuleInfo module) {
      if (productNames != null) {
	boolean productMatch = (filterByProduct (module) == includeByProduct);
	if (!productMatch)
	  return !matching;
      }
      if (authors != null) {
	boolean authorMatch = (filterByAuthor (module) == includeByAuthor);
	if (!authorMatch)
	  return !matching;
      }
      if (hasInfo != null) {
	boolean infoMatch = module.hasInfo () == hasInfo.booleanValue ();
	if (!infoMatch)
	  return !matching;
      }
      if (assigned != null) {
	boolean assignedMatch = module.isAssigned () == assigned.booleanValue ();
	if (!assignedMatch)
	  return !matching;
      }
      if (multiplyAssigned != null) {
	String[] assignedProducts = module.getProductNames();
	boolean multiplyAssignedMatch =
	  ((assignedProducts != null) && (assignedProducts.length > 1)) == multiplyAssigned.booleanValue();
	if (!multiplyAssignedMatch)
	  return !matching;
      }
      if (hasAuthor != null) {
	boolean ownerMatch = module.hasAuthor() == hasAuthor.booleanValue();
	if (!ownerMatch)
	  return !matching;
      }
      if (shipsSource != null) {
	boolean shipsSourceMatch = module.isSourceIncluded () == shipsSource.booleanValue ();
	if (!shipsSourceMatch)
	  return !matching;
      }
      if (hasJavaSources != null) {
	boolean hasJavaSourcesMatch = module.hasJavaSources () == hasJavaSources.booleanValue ();
	if (!hasJavaSourcesMatch)
	  return !matching;
      }
      if (hasClasses != null) {
	boolean hasClassesMatch = module.hasJava () == hasClasses.booleanValue ();
	if (hasClassesMatch != matching)
	  return false;
      }
      if (isPublic != null) {
	boolean isPublicMatch = module.isPublic () == isPublic.booleanValue ();
	if (isPublicMatch != matching)
	  return false;
      }
      return matching;
    }

    private boolean filterByProduct (ModuleInfo module) {
      String[] moduleProducts = module.getProductNames();
      if (moduleProducts != null) {
	for (int i=0; i<productNames.length; i++) {
	  String productName = productNames[i];
	  for (int j=0; j<moduleProducts.length; j++) {
	    if (moduleProducts[j].equals (productName))
	      return true;
	  }
	}
      }
      return false;
    }

    private boolean filterByAuthor (ModuleInfo module) {
      String moduleAuthor = module.getAuthor();
      if (moduleAuthor != null) {
	for (int i=0; i<authors.length; i++) {
	  String author = authors[i];
	  if (moduleAuthor.equals(author))
	    return true;
	}
      }
      return false;
    }

  }
}


class ProductFilter {

  boolean include;
  String[] productNames;

}


class AuthorFilter {

  boolean include;
  String[] authors;

}
