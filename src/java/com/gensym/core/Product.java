
package com.gensym.core;

import java.io.InputStream;
import java.io.IOException;
import java.io.Writer;
import java.util.Hashtable;
import java.util.StringTokenizer;
import java.util.Vector;

/**
 * Allows introspection of loaded product information.
 * @see com.gensym.core.ProductManager#getProduct
 */
public class Product {

  private String name;
  private String markerPackage;
  private String displayName;
  private String description;
  private boolean buildTime;

  private Version version;

  private boolean isUsable;
  private ProductInfo[] requiredProducts;

  private String status = "not installed";

  private static final int MAX_TOKENS                       = 5;
  private static final int NAME_INDEX                       = 0;
  private static final int VERSION_INDEX                    = 1;
  private static final int DISPLAY_VERSION_INDEX            = 2;
  private static final int DISPLAY_NAME_INDEX               = 3;
  private static final int DESCRIPTION_INDEX                = 4;

  private static final Hashtable productTable = new Hashtable (11);

  /**
   * Allow instantiation by package classes only!
   */
  Product (String name, String markerPackage, boolean buildTime) {
    if (productTable.get (name) != null)
      throw new RuntimeException ("Cannot create duplicate products");
    this.name = name;
    this.markerPackage = markerPackage.replace ('.', '/');
    this.buildTime = buildTime;
    readProductInfo ();
    productTable.put (name, this);
  }

  /**
   * Returns the internal name of the product
   */
  public String getName () {
    return name;
  }

  /**
   * Returns the pretty name of the product
   */
  public String getDisplayName () {
    return displayName;
  }

  /**
   * Returns the build ID of the version of the product
   */
  public int getVersion () {
    return version.getBuildID ();
  }

  /**
   * Returns the Version object of the product
   */
  public Version getVersionObject () {
    return version;
  }

  /**
   * Returns a string with the pretty name of the version of the product.
   * For example, "1.2 Rev. 1 (Build 1025)"
   */
  // Localize?
  public String getDisplayVersion () {
    return version.toString ();
  }


  /**
   * @undocumented
   */
  public boolean getState () {
    return isUsable;
  }

  /**
   * @undocumented
   */
  public String getStatus () {
    return status;
  }

  /**
   * @undocumented
   */
  public ProductInfo[] getRequiredProducts () {
    return requiredProducts;
  }

  /**
   * @undocumented
   */
  public boolean isInstalled () {
    return (displayName != null);
  }

  String getMarkerPackage () {
    return markerPackage;
  }

  private void readProductInfo () {
    String resourceName = "/" + markerPackage + "/version.dat";
    InputStream is = getClass ().getResourceAsStream (resourceName);
    //System.out.println ("Product Resource : " + resourceName + " -> " + is);
    if (is == null) {
      if (buildTime) {
	if(markerPackage.startsWith("com/gensym")) 
	   throw new RuntimeException ("No version.dat for " + name);
      }
      return;
    }
    try {
      String[] lines = new LineReader (is, new LineFilter () {
	@Override
	public boolean accept (String line) {
	  String trimmed = line.trim();
	  boolean comment = trimmed.startsWith ("#");
	  boolean empty = trimmed.length() == 0;
	  return !(comment || empty);
	}
      }).readLines ();
      is.close ();
      String header = lines[0];
      String[] dependencies = new String[lines.length - 1];
      fillInProductInfo (header);
      if (buildTime) {
	//System.out.println("name="+ name);
	String[] currentRequiredProducts = ProductManager.determineCurrentDependencies (name);
	if (currentRequiredProducts == null)
	  throw new RuntimeException("Product dependencies not defined for " +
				     name +
				     ". Even empty dependencies must be filled in in product-dependencies.dat");
	updateDependencies (currentRequiredProducts);
      } else {
	System.arraycopy (lines, 1, dependencies, 0, lines.length - 1);
	fillInDependencies (dependencies);
      }
      checkStatus ();
    } catch (IOException ioe) {
      System.err.println (ioe);
    } catch (MalformedProductInfoException mpio) {
      // fixme: by bbush, commented out to prevent whacked out inacurate errors
      //System.err.println (mpio);
    }
  }

  private void fillInProductInfo (String header) throws MalformedProductInfoException {
    StringTokenizer tknzr = new StringTokenizer (header, ":");
    String[] tokens = new String[MAX_TOKENS];
    int i = 0;
    while (tknzr.hasMoreTokens ()) {
      if (i == MAX_TOKENS)
	throw new MalformedProductInfoException ("Too many tokens in Header for " + name);
      tokens[i++] = tknzr.nextToken ();
    }
    if (!(tokens[NAME_INDEX].equals (name)))
      throw new MalformedProductInfoException ("Product Info for " + tokens[NAME_INDEX] +
					       " does not match expected " + name);
    version = new Version (tokens[VERSION_INDEX], tokens[DISPLAY_VERSION_INDEX]);
    displayName = tokens [DISPLAY_NAME_INDEX];
    description = tokens [DESCRIPTION_INDEX];
  }

  private void fillInDependencies (String[] dependencies) throws MalformedProductInfoException {
    int numdependencies = dependencies.length;
    requiredProducts = new ProductInfo [numdependencies];
    for (int i=0; i<numdependencies; i++) {
      requiredProducts[i] = new ProductInfo (dependencies[i]);
    }
  }

  private void updateDependencies (String[] requiredProductNames) {

    Vector productInfoList = new Vector ();
    for (int i=0; i<requiredProductNames.length; i++) {
      String requiredProductName = requiredProductNames[i];
      if (!requiredProductName.equals (name)) {
	try {
	  Product requiredProduct = ProductManager.getProduct (requiredProductName);
	  int requiredProductVersion = requiredProduct.getVersion ();
	  productInfoList.addElement (new ProductInfo (requiredProductName, requiredProductVersion));
	} catch (UnknownProductException upe) {
	  throw new RuntimeException ("Error updating " + name + " : " +
				      "Required Product <" + requiredProductName + "> not defined yet");

	}
      }
    }
    requiredProducts = (ProductInfo[]) ProductManager.toArray (productInfoList, new ProductInfo [productInfoList.size()]);
  }

  private void checkStatus () {
    for (int i=0; i<requiredProducts.length; i++) {
      ProductInfo reqdProductInfo = requiredProducts[i];
      String reqdProdInfoName = reqdProductInfo.getName ();
       Product reqdProduct = ProductManager.getProduct (reqdProdInfoName);
      if (!(reqdProduct.isInstalled () &&
	    reqdProduct.satisfies (reqdProductInfo))) {
	status = "not ok";
	return;
      }
    }
    status = "ok";
    isUsable = true;
  }

  @Override
  public String toString () {
    if (isInstalled ())
    return displayName + " (" + description + 
      ")\n  Installed Version = " + version.toString () + "\n  Status = " + status;
    else
      return name + " : Not Installed";
  }

  /**
   * @undocumented
   */
  public String describe () {
    String baseDescription = toString ();
    if (requiredProducts != null && requiredProducts.length > 0) {
      baseDescription += "\n  Requires : \n";
      for (int i=0; i<requiredProducts.length; i++) {
	String productName = requiredProducts[i].getName();
	Product reqProduct = ProductManager.getProduct (productName);
	boolean installed = false;
	if (reqProduct != null) {
	  String prodDisplayName = reqProduct.getDisplayName();
	  productName = prodDisplayName == null ? productName : prodDisplayName;
	  installed = reqProduct.isInstalled();
	}
	baseDescription += "    " + productName + " (Build " + requiredProducts[i].getVersion() + ")" +
	  (installed ? "" : " (not installed)") + (i == (requiredProducts.length - 1) ? "" : "\n");
      }
    }
    return baseDescription;
  }

  /**
   * @undocumented
   */
  @Override
  public boolean equals (Object other) {
    return (other != null && getClass().equals(other.getClass()) &&
	    ((Product)other).name.equals (name));
  }
  
  @Override
  public int hashCode() {
	final int prime = 31;
	int result = 1;
	return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
  }

  /**
   * @undocumented
   */
  public boolean satisfies (ProductInfo requiredProduct) {
    return (name.equals (requiredProduct.getName ()) &&
	    (getVersion () >= requiredProduct.getVersion ()));
  }

  /**
   * @undocumented
   */
  public static void main (String[] args) { 
    System.out.println (new Product (args[0], args[1], new Boolean (args[2]).booleanValue ()));
  }

  void updateForBuild (String newVersionString) {
    try {
      int prevBuildID = version.getBuildID ();
      int currentBuildID = prevBuildID + 1;
      version = new Version (Integer.toString (currentBuildID), newVersionString);
    } catch (MalformedProductInfoException mfe) {
      System.err.println (mfe);
    }
  }

  void updateForBuild () {
    version.incrementBuildID ();
  }

  void format (Writer os) throws IOException {
    os.write ("# Product Info\n");
    os.write (name);
    writeSeparator (os);
    os.write (Integer.toString (version.getBuildID ()));
    writeSeparator (os);
    os.write (version.getMajorVersion () + " " +
	      version.getMinorVersion () + " " +
	      version.getReleaseDescription () + " " +
	      version.getRevision ());
    writeSeparator (os);
    os.write (displayName);
    writeSeparator (os);
    os.write (description);
    os.write ('\n');
    os.write ("# Required Products\n");
    for (int i=0; i<requiredProducts.length; i++) {
      String reqProdName = requiredProducts[i].getName ();
      int currentReqProdVersion = ProductManager.getProduct (reqProdName).getVersion ();
      requiredProducts[i] = new ProductInfo (reqProdName, currentReqProdVersion);
      os.write (reqProdName);
      os.write (' ');
      os.write (Integer.toString (currentReqProdVersion));
      os.write ('\n');
    }
  }

  private void writeSeparator (Writer os) throws IOException {
    os.write (':');
  }

}
