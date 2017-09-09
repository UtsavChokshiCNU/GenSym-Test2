/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Bundle.java
 *
 * @author David McDonald
 * @version 0.1 initiated 6/30/00
 */

//package com.gensym.bundle;

import java.util.Vector;


public class Bundle {

  private String version;
  public void setVersion(String v) { version = v; }
  public String getVersion() { return version; }
  
  private String name;
  public void setName(String n) { name = n; }
  public String getName() { return name; }
  
  private int id;
  public void setID(int i) { id = i; }
  public int getID() { return id; }
  
  private Vector platforms = new Vector();
  public Vector getPlatforms() { return platforms; }
  public void setPlatforms(Vector p) { platforms = p; }
  public void addPlatform(Platform p) {
    platforms.addElement(p);
  }
  
  private Vector components;
  public Vector getComponents() { return components; }
  public void addComponent(Component c) {
    components.addElement(c);
  }
  
  private Vector optionalComponents;
  public Vector getOptionalComponents() {
    if ( optionalComponents == null ) {
      optionalComponents = new Vector();
      for (int i=0; i < components.size(); i++) {
	if ( ((Component)components.elementAt(i)).isOptional() )
	  optionalComponents.addElement( components.elementAt(i) );
      }
    }
    return optionalComponents;
  }
  public boolean hasComponents() {
    if ( optionalComponents == null )
      getOptionalComponents();
    return ( optionalComponents.size() > 0 );
  }
  
  
  public Bundle (String name) {
    this.name = name;
    components = new Vector(15);
  }
}
