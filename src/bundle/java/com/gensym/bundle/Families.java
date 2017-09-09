/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Families.java
 *
 * @author David McDonald
 * @version 0.1 initiated 6/29/00
 */

//package com.gensym.bundle;

import java.util.Vector;

public class Families {

    private Vector v;
    public Vector getAllTheFamilies() { return v; }

    public Families() {
	v = new Vector(10);
    }


    public void addFamily(Family f) {
	v.addElement(f);
    }	

    public void removeFamily(Family f) {
	v.removeElement(f);
    }

}
