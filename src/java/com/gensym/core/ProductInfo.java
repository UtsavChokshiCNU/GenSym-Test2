
package com.gensym.core;

import java.io.Writer;
import java.io.IOException;

class ProductInfo {

  private String name;
  private int buildID;


  ProductInfo (String productDescription) throws MalformedProductInfoException {
    int spIndex = productDescription.indexOf (' ');
    if (spIndex < 0) {
      throw new MalformedProductInfoException("Could not parse product description : " + 
					      productDescription); 
    }
    name = productDescription.substring (0, spIndex);
    try {
      buildID = Integer.parseInt (productDescription.substring (spIndex + 1));
    } catch (NumberFormatException nfe) {
      throw new MalformedProductInfoException ("Error parsing version : " + nfe);
    }
  }

  ProductInfo (String name, int buildID) {
    this.name = name;
    this.buildID = buildID;
  }

  public String getName () {
    return name;
  }

  public int getVersion () {
    return buildID;
  }

  void format (Writer os) throws IOException {
    os.write (name);
    os.write (' ');
    os.write (Integer.toString (buildID));
  }

}
