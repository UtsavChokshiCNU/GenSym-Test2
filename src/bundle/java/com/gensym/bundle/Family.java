/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Family.java
 *
 * @author David McDonald
 * @version 0.1 initiated 6/29/00
 */

//package com.gensym.bundle;

import java.util.Vector;


public class Family {

    private int version = 10; /* default to 10, the original version. */
    public void setVersion(int v) { version = v; }
    public int getVersion() { return version; }

    private String name;
    public void setName(String n) { name = n; }
    public String getName() { return name; }

    private int index;
    public void setIndex(int i) { index = i; }
    public int getIndex() { return index; }

    private Vector bundles;
    public Vector getBundles() { return bundles; }
    public void addBundle(Bundle b) {
	bundles.addElement(b);
    }

    public Family(String idNumber) {
	bundles = new Vector(10);
	this.index = (Float.valueOf(idNumber)).intValue();
    }

}

    
