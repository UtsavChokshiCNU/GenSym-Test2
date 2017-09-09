
package com.gensym.core;

import java.io.ByteArrayOutputStream;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileOutputStream;
import java.io.Writer;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.File;
import java.util.Vector;
import java.lang.reflect.Method;
import java.nio.charset.Charset;

public class ProductManager {

  private static Product[] products;
  private static boolean buildTime = false;
  private static final String usage = "java com.gensym.core.ProductManger -list | -listInstalled | -verbose | -jarlist <prodcutName>*";

  /**
   * Prevent instantiation
   */
  private ProductManager () {
  }

  /**
   * Returns a list of all known products
   */
  public static Product[] getProducts () {
    return getProducts0 (false);
  }

  /**
   * Returns a list of all installed products
   * @see #getProducts
   * @see com.gensym.core.Product#isInstalled
   */
  public static Product[] getInstalledProducts () {
    return getProducts0 (true);
  }

  /**
   * Attempts to read product data
   */
  private static synchronized Product[] getProducts0 (boolean installedProductsOnly) {
    readProductData ();
    Product[] productsCopy;
    int numProducts = products.length;
    if (installedProductsOnly) {
      Vector productsList = new Vector ();
      for (int i=0; i<numProducts; i++) {
	if (products[i].isInstalled ())
	  productsList.addElement (products[i]);
      }
      productsCopy = new Product[productsList.size ()];
      productsList.copyInto (productsCopy);
    } else {
      productsCopy = new Product[numProducts];
      System.arraycopy (products, 0, productsCopy, 0, numProducts);
    }
    return productsCopy;
  }

  /**
   * Returns a specific product by name
   */
  public static synchronized Product getProduct (String productName) {
    readProductData ();
    return retrieveProductByName (productName);
  }


  /**
   * The heart of the matter
   */
  private static synchronized void readProductData () {
    if (products != null)
      return;
    String resourceName = "/com/gensym/build/products.dat";
//      String resourceName = "com.gensym.build.products.dat";
    InputStream is = com.gensym.core.ProductManager.class.getResourceAsStream (resourceName);
    //System.out.println ("InputStream for resource " + resourceName + " = " + is);
    try {
      String[] lines = new LineReader (is, new LineFilter () {
	@Override
	public boolean accept (String line) {
	  return !(line.trim().startsWith ("#"));
	}
      }).readLines ();
      int numProducts = lines.length;
      products = new Product [numProducts];
      for (int i=0; i<numProducts; i++) {
	//System.out.println("current line = " + lines[i]);
	int spIndex = lines[i].indexOf (' ');
	String productName = lines[i].substring (0, spIndex);
	String productPackage = lines[i].substring (spIndex + 1).trim ();
	products[i] = new Product (productName, productPackage, buildTime);
	//System.out.println ("#" + i + " <" + productName + "> = " + products[i]);
      }
    } catch (IOException ioe) {
      System.err.println (ioe);
    }
  }

  /**
   * Get from list of already read products
   * Can be called during the read of dependent
   * products to retrieve required products
   */
  private static synchronized Product retrieveProductByName (String productName) {
    int numProducts = products.length;
    if (false)
      System.out.println ("retrieveByName (" + productName + ") from " +
			com.gensym.core.DebugUtil.printArray(products));
    for (int i=0; i<numProducts; i++) {
      if (products[i] == null)
	break;
      if (products[i].getName ().equals (productName)) {
        //System.out.println("product found: " + products[i].getName());
	return products[i];
      }
    }
    throw new UnknownProductException (productName);
  }

  /**
   * Maybe make public?
 * @throws UnsupportedEncodingException 
   */
  private static String getDescriptions (boolean installedProductsOnly, boolean verbose) throws UnsupportedEncodingException {
    Product[] products = getProducts0 (installedProductsOnly);
    ByteArrayOutputStream bos = new ByteArrayOutputStream (400);
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(bos, Charset.defaultCharset()));
    for (int i=0; i<products.length; i++) {
      Product product = products[i];
      String productDescription;
      if (verbose)
	productDescription = product.describe();
      else
	productDescription = product.toString();
      pw.write (productDescription);
      if (i != products.length - 1)
	pw.println ();
    }
    pw.close ();
    return bos.toString (Charset.defaultCharset().name());
  }

  /**
   *
   *
   */
  public static void main (String[] args) throws Exception {
    GensymApplication.initialize ();
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    boolean verbose = cmdLine.getSwitchValue("-verbose");
    if (cmdLine.getSwitchValue ("-list"))
      System.out.println (getDescriptions (false, verbose));
    else if (cmdLine.getSwitchValue ("-listInstalled"))
      System.out.println (getDescriptions (true, verbose));
    else if (cmdLine.getSwitchValue ("-build") ||
             cmdLine.getSwitchValue ("-buildAllUnder")) {
      buildTime = true;
      String productNameToBuild = cmdLine.getOptionValue ("-product");
      //System.out.println("product name " + productNameToBuild);
      boolean fullBuild = cmdLine.getSwitchValue ("-buildAllUnder");
      String[] productArgs = cmdLine.getOptionValues ("-product");
      /*
	if (cmdLine.getOptionValue ("-nobuild") || cmdLine.getOptionValue ("-nobuildUnder"))
	  String[] productNamesToSkip = determineProductsToSkip (cmdLine.getSwitchValue))
      */
      String[] productNamesToBuild = determineProductsToBuild (productArgs, fullBuild /*productsToSkip*/);
      System.out.println ("Products to build:\n" +
			  com.gensym.core.DebugUtil.printArray(productNamesToBuild));
      
      String newVersion = null;
      if (cmdLine.getSwitchValue("-setVersion")) {
	newVersion = cmdLine.getOptionValue("-setVersion");
      }
      for (int i=0; i<productNamesToBuild.length; i++) {
	  updateProductForBuild (productNamesToBuild[i],newVersion);
	//appendEntryForBuildLog (productNamesToBuild[i]);
      }
    } else if (cmdLine.getSwitchValue("-jarlist")) {
      String[] productNames = cmdLine.getOptionValues ("-jarlist");
      System.out.println (getProductDependenciesDescription (productNames));
    } else
      System.out.println (usage);
  }

  /**
   *
   */
  private static String[] determineProductsToBuild (String[] productNames,
						    boolean fullBuild/*,
					            String[] productsToSkip*/) {
    if (!fullBuild)
      return productNames; // better be in dependency order
    Vector buildProductsList = new Vector ();
    for (int i=0; i<productNames.length; i++)
      buildProductsList.addElement (productNames[i]);
    int i=-1;
    while (++i<buildProductsList.size()) {
      String productName = (String)buildProductsList.elementAt (i);
      String[] requiredProductNames = determineCurrentDependencies (productName); // product.getRequired?
      for (int j=0; j<requiredProductNames.length; j++) {
	String requiredProductName = requiredProductNames[j];
	if (!buildProductsList.contains(requiredProductName))
	  buildProductsList.addElement(requiredProductName);
      }
      if (false)
      System.out.println ("Checking : " + productName + " -> Adding " +
			  com.gensym.core.DebugUtil.printArray (requiredProductNames));
    }
    Vector buildProductsOrderedList = new Vector ();
    Product[] allProducts = getProducts();
    for (i=0; i<allProducts.length; i++) {
      Product currentProduct = allProducts[i];
      String currentProductName = currentProduct.getName();
      if (buildProductsList.contains (currentProductName))
	buildProductsOrderedList.addElement (currentProductName);
    }
    return (String[])toArray (buildProductsOrderedList, new String[buildProductsOrderedList.size()]);
  }
  
  /**
 * @throws UnsupportedEncodingException 
   *
   */
  private static String getProductDependenciesDescription (String[] productNames) throws UnsupportedEncodingException {
    Product[] allProducts = getProductDependencies (productNames);
    ByteArrayOutputStream bos = new ByteArrayOutputStream (400);
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(bos, Charset.defaultCharset()));
    for (int i=0; i<allProducts.length; i++) {
      Product product = allProducts[i];
      pw.write (product.getName());
      pw.write (" [" + product.getStatus() + "]");
      if (i != allProducts.length - 1)
	pw.println ();
    }
    pw.close ();
    return bos.toString(Charset.defaultCharset().name());
  }

  /**
   *
   */
  private static Product[] getProductDependencies (String[] productNames) {
    int i=0;
    if (productNames.length == 0)
      throw new RuntimeException ("No products specified for dependency list");
    Vector dependencyList = new Vector ();
    for (i=0; i<productNames.length; i++) {
      Product prod = getProduct (productNames[i]);
      if (prod == null) // user entered bad name
	throw new RuntimeException ("Unknown product " + productNames[i] + " specified");
      if (dependencyList.contains (prod))
	throw new RuntimeException ("Duplicate product specified - " + productNames[i]);
      dependencyList.addElement (prod);
    }
    i = -1;
    while (++i<dependencyList.size()) {
      Product currentProduct = (Product)dependencyList.elementAt (i);
      ProductInfo[] requiredProductsInfo = currentProduct.getRequiredProducts ();
      if (requiredProductsInfo != null) {
	for (int j=0; j<requiredProductsInfo.length; j++) {
	  Product requiredProduct = getProduct (requiredProductsInfo[j].getName()); // non-null!
	  if (!dependencyList.contains (requiredProduct)) {
	    dependencyList.addElement (requiredProduct);
	  }
	}
      }
    }
    return (Product[])toArray (dependencyList, new Product[dependencyList.size()]);
  }

  private static void updateProductForBuild (String productName, String newVersion) throws IOException {
    readProductData ();
    Product product = retrieveProductByName (productName);
    String markerPackageName = product.getMarkerPackage ();
    System.out.println("markerPackageName " + markerPackageName);
    String buildRoot = System.getProperty ("com.gensym.build.root");
    System.out.println("buildRoot " + buildRoot);

    //    String versionFileLocn = buildRoot + File.separator + "java" + File.separator 
    //      + markerPackageName + File.separator + "version.dat";
    String versionFileLocn = buildRoot + File.separator + 
      markerPackageName + File.separator + "version.dat";

    //System.out.println("versionFileLocn " + versionFileLocn);
    File versionFile = new File (versionFileLocn);
    OutputStream os = new FileOutputStream (versionFile);
    Writer w = new OutputStreamWriter (os, Charset.defaultCharset());
    if (newVersion != null)
      product.updateForBuild (newVersion);
    else
      product.updateForBuild ();
    product.format (w);
    w.close ();
    String buildTempDir = System.getProperty ("com.gensym.build.tempdir");
    writeProductBuildCommitLog (product, buildTempDir + File.separator + "build-commit-log.txt");
  }

  private static void writeProductBuildCommitLog (Product productBuilt,
						  String commitLogFileName) throws IOException {
    String productName = productBuilt.getName ();
    File commitLog = new File (commitLogFileName);
    FileOutputStream fos = new FileOutputStream (commitLog);
    Writer w = new OutputStreamWriter (fos, Charset.defaultCharset());
    w.write ("---------------------------------------------------------------------------\n");
    w.write (" " + productName + " " + productBuilt.getDisplayVersion () + "\n");
    w.write ("    Started at " + new java.util.Date () + "\n");
    w.write ("            by " + System.getProperty ("user.name") + "\n");
    w.write ("            on " + java.net.InetAddress.getLocalHost().getHostName() + "\n");
    w.write ("---------------------------------------------------------------------------\n");
    w.close ();
  }

  static Object pda;
  static Method mthd;
  static synchronized String[] determineCurrentDependencies (String productName) {
    try {
      if (pda == null) {
        Class pdaClass = Class.forName ("com.gensym.devtools.ProductDependencyAnalyzer");
        pda = pdaClass.newInstance ();
        mthd = pdaClass.getDeclaredMethod ("getRequiredProducts", new Class[] {String.class});
      }
      String[] dependencies = (String[]) mthd.invoke (pda, new Object[] {productName});
      return dependencies;
    } catch (Exception e) {
      com.gensym.message.Trace.exception (e);
      throw new RuntimeException ("Unable to determine dependencies for build - " + e);
    }
  }

  // junk code for 1.1 support

  static Object[] toArray (Vector v, Object[] array) {
    for (int i=0; i<v.size(); i++)
      array[i] = v.elementAt (i);
    return array;
  }
}
