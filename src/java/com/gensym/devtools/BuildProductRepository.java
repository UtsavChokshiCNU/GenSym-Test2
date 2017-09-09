package com.gensym.devtools;

import java.util.Vector;
import java.util.StringTokenizer;
import java.util.Enumeration;
import java.io.*;
import java.nio.charset.Charset;
import java.util.zip.*;
import com.gensym.jartools.JarFile;
import com.gensym.core.CmdLineArgHandler;

/**
 * This java file, will build a Java product, utilising module-info
 * found in each com.gensym.* package. It also assumes that there is
 * a product directory, that contains the product dir structure and
 * at least contains classes, bin and docs directories.
 * This files, does not belong to any package, and does not
 * utilize any com.gensym. files as, the classpath is assumed to 
 * set pointing to the new location, so that copied java files can
 * be compiled without refering to the repository files.
 */
public class BuildProductRepository {

  private String productName = "";
  String targetDir = "";
  private String sourceDir = "";
  private String sourceJavaDir = "";
  private String sourceProductDir = "";
  private String targetClassesDir = "";
  private String targetDocsDir = "";
  private String targetBinDir = "";
  private Vector modulesToCopy = new Vector();
  private static Vector fileTypesToInclude = new Vector();
  {
    fileTypesToInclude.addElement(".java");
    fileTypesToInclude.addElement(".ser");
    fileTypesToInclude.addElement(".ovr");
    fileTypesToInclude.addElement(".gif");
    fileTypesToInclude.addElement(".jpg");
    fileTypesToInclude.addElement(".htm");
    fileTypesToInclude.addElement(".html");
    fileTypesToInclude.addElement(".class");
    fileTypesToInclude.addElement(".cls"); // encrypted class files
    fileTypesToInclude.addElement(".properties");
    fileTypesToInclude.addElement(".kbs");
    fileTypesToInclude.addElement(".txt");
    fileTypesToInclude.addElement(".bat");
    fileTypesToInclude.addElement(".sh");
    fileTypesToInclude.addElement(".lisp");
    fileTypesToInclude.addElement(".dat");
    fileTypesToInclude.addElement(".jar");
    fileTypesToInclude.addElement(".xml");
  }

  private static Vector dirNamesToAlwaysExclude = new Vector();
  {
    dirNamesToAlwaysExclude.addElement("Cvs");
    dirNamesToAlwaysExclude.addElement("CVS");
  }

  private static String MODULE_INFO_FILE_NAME = "package.info";
  private static String INCLUDE_IN_MODULE_TAG = "include-in-module:";
  private static String EXCLUDE_FROM_COMPILE_TAG = "exclude-from-compile:";
  private static String EXCLUDE_FROM_JAVADOC_TAG = "exclude-from-javadoc:";
  private static String DONT_JAR_PACKAGE_TAG = "dont-jar-package:";
  private static String DONT_DELETE_JAVA_TAG = "dont-delete-java:";
  private static String JAR_AS_BEAN_TAG = "jar-as-bean:";
  private static String PACKAGE_IS_PRIVATE_TAG = "package-is-private";

  private static String platformOS = System.getProperty ("os.name");
  private static String platformAR = System.getProperty ("os.arch");
  private static String externalJavaDocClassesPath = "";

  public static void main(String args[]) {

    // Need
    // 1. Product Name
    // 2. Source directory of repository
    // 3. Output directory root
    // 4. Classes path for external classes (like jdk) do not include repository


    if (args.length >= 4) {

      System.out.println("This build for " + platformOS);
      
      // Support for old parameters list
      String productName = args[0];
      String sourceDir = args[1];
      String targetDir = args[2];
      String javadocClassPath = args[3];
      String productTreeDir = null;
      boolean createJavadoc = true;

      // New parameters list
      CmdLineArgHandler cmdline = new CmdLineArgHandler(args);
      productName = cmdline.getOptionValue("-productName");
      sourceDir = cmdline.getOptionValue("-sourceDir");
      targetDir = cmdline.getOptionValue("-targetDir");
      productTreeDir = cmdline.getOptionValue("-productTreeDir");
      javadocClassPath = cmdline.getOptionValue("-javadocClassPath");
      createJavadoc = !cmdline.getSwitchValue("-dontCreateJavadoc");

      if (productTreeDir == null) // default for old style parameters;
	productTreeDir = sourceDir+File.separator+"java"; 

      // Dont allow any utilities to do a System.exit like JavaDoc
      System.setSecurityManager(new BuilderSecurityManager());

      //Test
      //System.out.println("" + wildcardCompare("*Impl.java", "fredImpl.java"));
      //System.out.println("" + wildcardCompare("*Impl.java", "fredImpldfd.java"));
      // System.out.println("" + wildcardCompare("Testing*Impl.java", "fredImpl.java"));
      //System.out.println("" + wildcardCompare("Testing*Impl.java", "TestingfredImpl.java"));
      //System.out.println("" + wildcardCompare("*Impldfss.*", "fredImpl.fred"));
      //System.out.println("" + wildcardCompare("*Impl.*", "fredImpl.class"));

      BuildProductRepository builder = new BuildProductRepository(productName, sourceDir, 
								  targetDir, productTreeDir);

      System.out.println("Copying Product files from product directory");
      builder.copyProductDirectory();
      System.out.println("Copying Product Files from repository");
      builder.copyProductJavaFiles();

      if (createJavadoc) {
	try {
	  System.out.println("Stripping undocumented methods before javadoc");
	  StripUndocumentedMembers.main(new String[] {targetDir});
	}
	catch(IOException e)
	  {
	    System.out.println("Stripping undocumented methods failed");
	    e.printStackTrace();
	  }

	builder.createJavaDoc(javadocClassPath); 
	System.out.println("Completed Generating Java Doc");
      }

      System.out.println("Copying Java files excluded from java Doc");
      builder.copyExcludedJavaDocFiles();
      //System.out.println("Compiling Source");
      //builder.compileProductJavaFiles();
      //System.out.println("Completed compiling Java ");
      System.out.println("Deleting Java Files");
      builder.deleteProductJavaFiles();
      builder.jarClassesDir();
      builder.deleteGensymPackages();

      System.out.println("Finished...Product dir created at " + builder.targetDir); 

    } else {
      System.out.println("usage: java com.gensym.devtools.BuildProductRepository productname reposdir outputdir javadocclasspath");
      System.out.println("e.g. java mkfiles.BuildProductRepository javalink c:\\bt\\mg c:\\bt\\mg\\javalink\\intelnt-staging-directory c:\\jdk1.1\bin\\classes.zip");
      System.out.println("or");
      System.out.println("usage: java com.gensym.devtools -productName <productName> [-sourceDir <sourceDir> -productTreeDir <productTreeDir> -targetDir <targetDir> [-dontCreateJavadoc] [-javadocClassPath <javadocClassPath> ]");
    }

  }

  public BuildProductRepository(String productName, 
				String sourceDir, 
				String outputDir,
				String productTreeDir) {

    this.productName = productName.toLowerCase();
    this.sourceDir = sourceDir;
    this.targetDir = outputDir;
    this.sourceJavaDir = productTreeDir;
    this.sourceProductDir = sourceJavaDir+File.separator+"products"+File.separator+productName;
    this.targetClassesDir = targetDir+File.separator+"classes";
    this.targetDocsDir = targetDir+File.separator+"docs"+File.separator+"api";
    this.targetBinDir = targetDir+File.separator+"bin";

    System.out.println(productName + "  "  + targetClassesDir + " " + sourceJavaDir + " ");

    loadModuleInfo(new File(sourceJavaDir));

  }

  private String getPlatformName() {
    if ((platformOS.indexOf("Windows") > -1))
      if ((platformAR.indexOf("alpha") > -1))
        return "alphant";
      else 
        return "intelnt";
    else if ((platformOS.indexOf("HP-UX") > -1))
      return "hp9000s700";
    else if ((platformOS.indexOf("AIX") > -1))
      return "rs6000";
    else if ((platformAR.indexOf("sparc") > -1))
      return "sparcsol";
    else if (platformOS.indexOf("Linux") > -1)
      return "linux";
    // Following is needed to identify Solaris Intel for porting work; it can
    // be removed when a Sparc box is available and if Solaris Intel isn't to be
    // supported.
    else if (platformOS.indexOf("SunOS") > -1)
      if (platformAR.indexOf("x86") > -1)
        return "sparcsol";
    else {
      System.out.println("Platform not supported " + platformAR + " ...bye bye");
      System.exit(0);
    }
    return "";
  }

  public void copyProductDirectory() {

    copyDir(targetDir, 
	    new File(sourceProductDir+File.separator+"common"),
	    null, 
	    null,
	    null,
	    false,
	    null);

    File sourcePlatformDir = null;
    sourcePlatformDir = new File(sourceProductDir+File.separator+getPlatformName());

    copyDir(targetDir, 
	    sourcePlatformDir, 
	    null,
	    null,
	    null,
	    false,
	    null);
  }

  public void createJavaDoc(String externalJavaDocClassesPath) {
    String pathSeparator = System.getProperty ("path.separator");
    Vector packages = new Vector();
    packages.addElement("-d");
    packages.addElement(targetDocsDir);
    packages.addElement("-sourcepath");
    packages.addElement(targetClassesDir+ pathSeparator + externalJavaDocClassesPath);
    int i = 4;
    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements(); i++) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      if (! moduleInfo.packageIsPrivate)
        packages.addElement(moduleInfo.packageName);  
    }

    System.out.println("javadoc");
    for (int y=0; y<packages.size(); y++) {
      System.out.println(packages.elementAt(y));
    }
    String[] packagesArray = new String[packages.size()];
    packages.copyInto(packagesArray);

    javaRunJavaDoc(packagesArray);

  }

  public void copyProductJavaFiles() {
    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      String moduleSourceDir = moduleInfo.sourceDirFile.getAbsolutePath();
      String relativePath = moduleSourceDir.substring(sourceJavaDir.length());
      String moduleTargetDir = targetClassesDir + relativePath;
      moduleInfo.targetDirFile = new File(moduleTargetDir);
      moduleInfo.excludedFromJavaDocFiles = new Vector();

      System.out.println("Copying package to " + moduleTargetDir);

      copyDir(moduleTargetDir, 
            moduleInfo.sourceDirFile, 
            moduleInfo.excludeFromCompileList, 
	    moduleInfo.excludeFromJavaDocList,
            fileTypesToInclude,
            true,
	    moduleInfo.excludedFromJavaDocFiles  );

    }
  }



  public void copyExcludedJavaDocFiles() {
    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {

      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();

      if (moduleInfo.excludedFromJavaDocFiles != null)
	for (Enumeration m = moduleInfo.excludedFromJavaDocFiles.elements(); m.hasMoreElements();) {

	  FileCopyRequest filereq = (FileCopyRequest)m.nextElement();
	  //System.out.println("Copying Excluded java Doc file to " + filereq.targetFile.toString() );
	  javaCopyFile(filereq.sourceFile, filereq.targetFile);
	  filereq.sourceFile = null;
	  filereq.targetFile = null;
	}

    }
  }

  public void deleteProductJavaFiles() {
    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      String moduleSourceDir = moduleInfo.sourceDirFile.getAbsolutePath();
      String relativePath = moduleSourceDir.substring(sourceJavaDir.length());
      String moduleTargetDir = targetClassesDir + relativePath;

      if (!moduleInfo.dontDeleteJava) 
	 deleteFilesFromDir(new File(moduleTargetDir), "*.java");

    }
  }

  public void compileProductJavaFiles() {

    // Special for G2Connection, which will fail if complied by recusrion but not be its self !
    
    String G2ConnectionFilename = targetClassesDir+File.separator+"com"+
			 File.separator+"gensym"+File.separator+"jgi"+File.separator+"G2Connection.java";
    System.out.println("Compiling  " + G2ConnectionFilename);
    if (!javaCompileJava(G2ConnectionFilename)) {
	  System.out.println("Could Not compile " + G2ConnectionFilename);
	  //System.exit(0);
    }

    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      String filetocompile = moduleInfo.targetDirFile.getAbsolutePath()+File.separator+"*.java";
     
      System.out.println("Compiling..." + filetocompile);

      compileDir(moduleInfo.targetDirFile);
    }
  }

  // The current directory must be set to the targetClassesDir to find com and 
  // for the jar file to include the correct relative paths from com.
  public void osjarClassesDir() {
    osRunJar("cvf " + targetClassesDir + File.separator + productName + ".jar com");
  }

  public void jarClassesDir() {
    try {
      JarFile jf = new JarFile();
      for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      String moduleSourceDir = moduleInfo.sourceDirFile.getAbsolutePath();
      String relativePath = moduleSourceDir.substring(sourceJavaDir.length()+1);
      String moduleTargetDir = targetClassesDir + relativePath;

      if (!moduleInfo.dontJarPackage) {
	System.out.println("Putting " + relativePath + " into classes jar file");
	jarDir(jf, moduleInfo.targetDirFile, relativePath, moduleInfo.jarAsBeansList);
      }

      }
      // make a call to save the contents of the jar file
      System.out.println("Saving Jar to " + targetClassesDir + " " + productName);
      jf.saveAs( targetClassesDir + File.separator + productName + ".jar" );
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString()); 
      System.exit(0);}
  }


  public void deleteGensymPackages() {
    for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
      
      ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
      if (!moduleInfo.dontJarPackage && !moduleInfo.dontDeleteJava) {
	// Jar class files and delete source
	System.out.println("Deleting Gensym dir package  " + moduleInfo.targetDirFile);
	deleteFilesFromDir(moduleInfo.targetDirFile, "*");
	moduleInfo.targetDirFile.delete();
      } else if (!moduleInfo.dontJarPackage && moduleInfo.dontDeleteJava) {
	// Jar class files , but keep source in dir
	System.out.println("Deleting Gensym dir package class files " + moduleInfo.targetDirFile);
	deleteFilesFromDir(moduleInfo.targetDirFile, "*.class");
      }
    }
  }


  void compileDir(File targetDir) {

    String dirList[] = targetDir.list();
    if (dirList == null) {
    	return;
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDir.getAbsolutePath()+File.separator+filename;

      if (targetFilename.lastIndexOf(".java") > 1) {
	//System.out.println("Compling file " + targetFilename);
	if (!javaCompileJava(targetFilename)) {
	  System.out.println("******************* Could Not compile " + targetFilename);
	  //System.exit(0);
	}

      }
    }
  }

  void deleteFilesFromDir(File targetDir, String filetype) {

    String dirList[] = targetDir.list();
    if (dirList == null) {
    	return;
    }

    System.out.println ("deleteFilesFromDir (" + targetDir + ", " + filetype + ")");
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String targetFilename = targetDir.getAbsolutePath()+File.separator+filename;
      //System.out.println("  del ->?  " + targetFilename + filetype );
      if (wildcardCompare(filetype, targetFilename)) {

	      //System.out.println("deleteing file " + targetFilename);
	      File targetFile = new File(targetFilename);
	      if (targetFile.isDirectory()) {
	        // check that this is not a package directory that we want to keep
	        boolean deleteDir = true;
	        for (Enumeration e = modulesToCopy.elements(); e.hasMoreElements();) {
	          ModuleInfo moduleInfo = (ModuleInfo)e.nextElement();
	          if (moduleInfo.targetDirFile.getAbsolutePath().equals(targetFile.getAbsolutePath())) {
	            if (moduleInfo.dontJarPackage || moduleInfo.dontDeleteJava) 
		            deleteDir = false;
	            break;
	          }
	        }
	        if (deleteDir) {
	        	deleteFilesFromDir(targetFile, filetype);
	        }
	      }
	      targetFile.delete();
      }
    }
  }



  void copyDir(String targetDirName, 
	       File sourceDirFile, 
	       Vector filesToExclude, 
	       Vector filesToDefer,
	       Vector fileTypes,
	       boolean ignoreDirs,
	       Vector deferredCopyRequests) {

    if (wildcardCompare(dirNamesToAlwaysExclude, sourceDirFile.getName() )) 
      return;

    File targetDirFile = new File(targetDirName);
    if (!targetDirFile.exists()) 
      targetDirFile.mkdirs();
    String dirList[] = sourceDirFile.list();
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String sourceFilename = sourceDirFile.getAbsolutePath()+File.separator+filename;
      String targetFilename = targetDirName+File.separator+filename;
      File sourceFile = new File(sourceFilename);

      if (!ignoreDirs && sourceFile.isDirectory()) {
	      copyDir(targetFilename,
		      sourceFile,
		      filesToExclude,
		      filesToDefer,
		      fileTypes,
		      ignoreDirs,
		      deferredCopyRequests);

      } else if (!sourceFile.isDirectory()) {
		
	      int prefixPos = filename.lastIndexOf(".");
	      String fileType = prefixPos > -1 ? filename.substring(prefixPos) : "";
	      if (wildcardCompare(filesToExclude, sourceFilename)) {
	      } else if (wildcardCompare(filesToDefer, sourceFilename)) {
	        if (deferredCopyRequests != null) 
	          deferredCopyRequests.addElement(new FileCopyRequest(sourceFile, 
								      new File(targetFilename)));
	      } else if ( (fileTypes == null || (fileTypes != null && fileTypes.contains(fileType)))) {
	        javaCopyFile(sourceFile, new File(targetFilename));
	        //System.out.println("Copying file --->" + targetFilename + " \n   from --->" + sourceFilename);
	      }
      }
    }   
  }

  boolean jarDir(JarFile jf, File dir, String relativePath, Vector beanFiles) {   

    String dirList[] = dir.list();
    if (dirList == null) {
    	return false;
    }
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String sourceFilename = dir.getAbsolutePath()+File.separator+filename;
      if (!new File(sourceFilename).isDirectory()) {
	try {
	  //System.out.println ("  JD: " + sourceFilename);
	  if (wildcardCompare(beanFiles, sourceFilename))
	    jf.putFile(sourceFilename, relativePath +"/" + filename, true);
	  else
	    jf.putFile(sourceFilename, relativePath +"/" + filename);
	} catch (java.io.IOException e) {
	  e.printStackTrace();
	  System.out.println("Cant put " + filename + "in jar because of " + e.toString());}
      }
    }

    return true;
  }

  // Does a System.out.exit !, but trapped by our SecurityException
  boolean javaRunJavaDoc(String[] parameters) {
    try {
      Class jdocclass = null;
      try {
	// Try JDK1.2
	jdocclass = Class.forName("com.sun.tools.javadoc.Main");
      } catch (ClassNotFoundException e) {
	try {
	  // Try JDK1.1
	  jdocclass = Class.forName("sun.tools.javadoc.Main");
	} catch (ClassNotFoundException ne) {
	  throw new Error("****** Cant find Java Doc class from JDK1.2 or JDK1.1 *****");
	}
      }
      try {
	String[] dummy = new String[0];
	java.lang.reflect.Method main = jdocclass.getMethod("main", new Class[] {dummy.getClass()});
	main.invoke(null, new Object[] {parameters});
      } catch (Exception e) {
        e.printStackTrace();
      }
    } catch (SecurityException e) {
      e.printStackTrace();
      System.out.println("JavaDoc tried to System.exit"); }
    return true;
  }

  boolean osRunJavaDoc(String[] parameters) {
    String parStr = "";
    for (int i=0; i<parameters.length; i++)
      parStr = parStr + " " + parameters[i];
    return osCallJavaProc("javadoc ", parStr);
  }

  boolean osRunJar(String parameters) {
    return osCallJavaProc("jar ", parameters);
  }
  

  boolean javaCompileJava(String parameters) {
    ByteArrayOutputStream byteStream = new ByteArrayOutputStream (5); 
    sun.tools.javac.Main compiler = new sun.tools.javac.Main (byteStream, "javac");
    boolean success = compiler.compile (new String[] {parameters});
    byte[] compilerOutputBytes = byteStream.toByteArray ();
    StringBuffer compilerOutput = new StringBuffer (new String (compilerOutputBytes, Charset.defaultCharset()));
    String compilerOutputStr = compilerOutput.toString();
    if (!compilerOutputStr.equals("")) {
    	System.out.println(compilerOutputStr);
    }
    return success;
  }

  boolean osCompileJava (String parameters)
  {
    return osCallJavaProc("javac -J-Djavac.pipe.output=true", parameters);
  }


  boolean osCallJavaProc(String process, String parameters)
  {

    try {
      System.out.println ("Running:\n>>>");
      System.out.println (process + " " + " " + parameters);
      System.out.println (">>>");
      StringBuffer compilerOutput = new StringBuffer("");
      long start_time = System.currentTimeMillis();

      Process  compilerProcess = Runtime.getRuntime().exec (process + " " + parameters);	
		
      try { 
    	  Thread.sleep(1000); 
      } catch (Exception E) {}
		
      InputStream istream = compilerProcess.getInputStream();
	
	// Process.waitFor() does not work on NT ! with JDK1.1
	
	int buffer_size = 1;
	byte[] opt = new byte[buffer_size];
	int read_size = istream.read(opt);
	
	
	while (read_size == buffer_size) {
	  compilerOutput.append((char)opt[0]);
	  read_size = istream.read(opt);
	  // Check we have not been operating too long
	  if (System.currentTimeMillis() - start_time > 60000*60 ) //an hour !
	    {
	      compilerProcess.destroy();  // ensure that the compiler process is dead
	      break;
	    }
	}
	System.out.println(compilerOutput.toString());
	if (compilerOutput.toString().toLowerCase().indexOf("error") > -1)
	  return false;
	else
	  return true;
	
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());
      return false;
    }
  }

  void osCopyFile(File sourceFile, File targetFile) {
    //We are assuming that we have the cygnus unix command set on NT
      try {
	System.out.println((platformOS + " " + sourceFile.getAbsolutePath() + " " +
				  targetFile.getAbsolutePath()));
	Runtime.getRuntime().exec("cp " + 
			  sourceFile.getAbsolutePath() + " " +
				  targetFile.getAbsolutePath());
	
	System.out.println("copied");
      } catch (Exception e) {
	e.printStackTrace();
	System.out.println(e.toString());
	System.exit(0);
      }

  }
  
  void javaCopyFile(File sourceFile, File targetFile) {

    try {
      FileInputStream inf = new FileInputStream(sourceFile);
      FileOutputStream outf = new FileOutputStream(targetFile);

      byte[] ba = new byte[4096];
      int bytes_read;
      while ((bytes_read = inf.read(ba)) != -1) {
	outf.write(ba, 0, bytes_read);
      }
      inf.close();
      outf.close();
    } catch (Exception e) {
      e.printStackTrace();
      System.out.println(e.toString());
    }
  }
	 

  void loadModuleInfo(File sourceDirFile) {
    String dirList[] = sourceDirFile.list();
    for (int i=0; i<dirList.length; i++) {
      String filename = dirList[i];
      String fullfilename = sourceDirFile.getAbsolutePath()+File.separator+filename;
      // System.out.println(fullfilename);
      File dirFile = new File(fullfilename);

      if (filename.equals(MODULE_INFO_FILE_NAME)) {
	lookupModuleInfo(dirFile, sourceDirFile);
      } else if (dirFile.isDirectory()) 
	  loadModuleInfo(dirFile);
    }
  }
 

  void lookupModuleInfo(File moduleInfoFile, File sourceDirFile) {
    //System.out.println("Found module info at " + moduleInfoFile);
	FileInputStream inStream = null;
    Reader fileIn = null;
	BufferedReader in = null;
    try {
      inStream = new FileInputStream(moduleInfoFile);	
      fileIn = new InputStreamReader(inStream, Charset.defaultCharset());
      in = new BufferedReader(fileIn);
      String line;
      boolean include = false;
      Vector excludeFromCompileFiles = new Vector();
      Vector excludeFromJavaDocFiles = new Vector();
      Vector jarAsBeansFiles = new Vector();
      boolean dontJarPackage = false;
      boolean dontDeleteJava = false;
      boolean packageIsPrivate = false;

      while ((line = in.readLine()) != null) {
	if (line.startsWith(INCLUDE_IN_MODULE_TAG) &&
	    line.indexOf(productName) > -1) {
	  // only include, if productName word is found
	  int startPos = line.indexOf(productName);
	  int endPos = startPos + productName.length();
	  if (line.length() > endPos && Character.isLetterOrDigit(line.charAt(endPos)))    
	    include = false;
	  else
	    include = true;
	  //System.out.println("Line was line " + line + " included = " + include);
	}

	if (line.startsWith(EXCLUDE_FROM_COMPILE_TAG)) {
	  excludeFromCompileFiles = getList(line.substring(EXCLUDE_FROM_COMPILE_TAG.length()));
	}

	if (line.startsWith(EXCLUDE_FROM_JAVADOC_TAG)) {
	  excludeFromJavaDocFiles = getList(line.substring(EXCLUDE_FROM_JAVADOC_TAG.length()));
	}

	if (line.startsWith(JAR_AS_BEAN_TAG)) {
	  jarAsBeansFiles = getList(line.substring(JAR_AS_BEAN_TAG.length()));
	}
	
	if (line.startsWith(DONT_JAR_PACKAGE_TAG)) {
	   dontJarPackage = true;
	}

	if (line.startsWith(DONT_DELETE_JAVA_TAG)) {
	  dontDeleteJava = true;
	}
	if (line.startsWith(PACKAGE_IS_PRIVATE_TAG)) {
	  packageIsPrivate = true;
	}
      }

      if (include) {
	String packagename = sourceDirFile.getAbsolutePath().substring(sourceJavaDir.length());
	packagename = packagename.replace(File.separatorChar, '.');
	if (packagename.startsWith("."))
	  packagename = packagename.substring(1, packagename.length());
	modulesToCopy.addElement(new ModuleInfo(sourceDirFile,
						packagename,
						excludeFromCompileFiles, 
						excludeFromJavaDocFiles,
						jarAsBeansFiles,
						dontJarPackage,
						dontDeleteJava,
            packageIsPrivate));
	System.out.println("Found module info for " + productName + " at " + moduleInfoFile);
	//System.out.println("Found " + productName + " Details");
      }
	
    } catch (IOException e) {
      e.printStackTrace();
      System.out.println(e.toString());
    } finally {
    	closeSilently(in);
    	closeSilently(fileIn);
    	closeSilently(inStream);
    }
  }
  
  private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println(e.toString());
      } 
  }

  Vector getList(String line) {
    Vector list = new Vector();
    StringTokenizer st = new StringTokenizer(line);
    while (st.hasMoreElements()) {
      String item = st.nextToken();
      //System.out.println("Token " + item);
      list.addElement(item);
    }   
    return list;
  }

  static boolean wildcardCompare(Vector names, String name) {
    if (names == null){
    	return false;
    }
    for (Enumeration e = names.elements(); e.hasMoreElements();) {
      String compareStr = (String)e.nextElement();
      if (wildcardCompare(compareStr, name))
	      return true;
    }
    return false;
  }

  static boolean wildcardCompare(final String source, final String toCompareString) {
    //System.out.println(source + "  " +  toCompareString);
	String compareString = toCompareString;
    if (source.equals(compareString))
      return true;

    StringTokenizer st = new StringTokenizer(source, "*");
    int numTokens = st.countTokens();
    String tokens[] = new String[numTokens];
    int i = 0;
    while (st.hasMoreTokens()) {
      tokens[i] = st.nextToken();
      //System.out.println("Wtoken " + i + tokens[i]);
      i++;
    }

    for (i = 0; i<numTokens; i++) {
      if (i==0) {
	      if (compareString.indexOf(tokens[i]) == -1)
	        return false;
	      else
	       compareString = compareString.substring(compareString.indexOf(tokens[i]) + 
						           tokens[i].length()); 
      } else {
	      if (!compareString.startsWith(tokens[i])) 
	        return false;
	      else
	        compareString = compareString.substring(tokens[i].length());
      }

      if (i<numTokens-1) {
	      int nextTokenPos = compareString.indexOf(tokens[i+1]);
	      if (nextTokenPos > 0)
	        compareString = compareString.substring(nextTokenPos);
	      else if (nextTokenPos == -1)
	        return false;
      }
    }

    return true;
  }

  class FileCopyRequest {
    FileCopyRequest(File sourceFile,
		    File targetFile) {
      this.sourceFile = sourceFile;
      this.targetFile = targetFile;
    }
    
    File sourceFile;
    File targetFile;

  }
    


}

    

    
