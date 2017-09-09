
package com.gensym.devtools;

import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Properties;
import java.util.StringTokenizer;
import java.io.InputStream;
import java.io.IOException;

public class ProductDependencyAnalyzer {

  private Hashtable productTable;
  private Hashtable resolvedRequirementsTable;

  /* Used in core.Product */
  public ProductDependencyAnalyzer () {
  }

  public String[] getProducts() {
    readDependencyData();
    Vector productList = new Vector();
    Enumeration e = productTable.keys();
    while (e.hasMoreElements())
      productList.addElement(e.nextElement());
    return (String[])productList.toArray(new String[productList.size()]);
  }

  public String[] getRequiredProducts (String productName) {
    String[] reqdProducts = null;
    readDependencyData();
    Vector reqdProductsList = (Vector)productTable.get(productName);
    if (reqdProductsList != null)
      reqdProducts = (String[])reqdProductsList.toArray(new String[reqdProductsList.size()]);
    return reqdProducts;
  }

  private void readDependencyData () {
    if (productTable != null)
      return;
    ClassLoader cl = getClass().getClassLoader();
    InputStream is = 
      cl.getSystemResourceAsStream("com/gensym/build/product-dependencies.dat");
    Properties props;                                 
    try {
      props = new Properties ();
      props.load (is);
      is.close ();
    } catch (IOException ioe) {
      ioe.printStackTrace();
      return;
    }
    Enumeration products = props.keys();
    while (products.hasMoreElements()) {
      String currentProduct = (String)products.nextElement();
      Vector reqProducts =
	determineRequiredProducts (props.getProperty (currentProduct));
      props.put (currentProduct,
		 reqProducts);
    }
    productTable = props;
  }

  public String[] getProductsUnder (String productName) {
    if (resolvedRequirementsTable == null)
      resolvedRequirementsTable = new Hashtable ();
    String[] allrequiredProducts =
      (String[])resolvedRequirementsTable.get (productName);
    if (allrequiredProducts == null) {
      Vector collectedProducts = new Vector();
      collectedProducts.addElement (productName);
      int i=0;
      while (i<collectedProducts.size()) {
	String currentProduct = (String) collectedProducts.elementAt (i);
	String[] reqdProducts = getRequiredProducts (currentProduct);
	if (false)
	System.out.println ("Required Products of <" + currentProduct + "> = " +
			    com.gensym.core.DebugUtil.printArray (reqdProducts));
	if (reqdProducts  == null)
	  System.out.println ("XXX " + currentProduct + " has no dependency listing");
	else {
	  for (int j=0; j<reqdProducts.length; j++)
	    if (!collectedProducts.contains(reqdProducts[j]))
	      collectedProducts.addElement(reqdProducts[j]);
	}
	i++;
      }
      allrequiredProducts =
	(String[])collectedProducts.toArray(new String[collectedProducts.size()]);
      resolvedRequirementsTable.put (productName, allrequiredProducts);
    }
    return allrequiredProducts;
  }

  Vector determineRequiredProducts (String reqProductsString) {
    Vector products = new Vector ();
    if (reqProductsString != null) {
      StringTokenizer stknzr = new StringTokenizer (reqProductsString);
      while (stknzr.hasMoreElements())
	products.addElement (stknzr.nextElement ());
    }
    return products;
  }

  private static void main (String[] args) {
    ProductDependencyAnalyzer pda = new ProductDependencyAnalyzer ();
    String[] products = pda.getProducts();
    System.out.println ("Known Products = " + com.gensym.core.DebugUtil.printArray (products));
    for (int i=0; i<products.length; i++)
      System.out.println (products[i] + " -> requires -> " +
			  com.gensym.core.DebugUtil.printArray (pda.getRequiredProducts(products[i])));
  }
  
}
