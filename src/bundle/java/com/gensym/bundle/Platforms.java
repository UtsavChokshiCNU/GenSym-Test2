/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Platforms.java
 *
 * @author David McDonald
 * @version 0.1 initiated 8/25/00
 */

import java.util.Vector;

public class Platforms {

    private Vector thePlatforms = new Vector();

    public void addPlatform(Platform p) {
	thePlatforms.addElement(p);
    }

    public Platform platformNamed(String name) {
	for (int i=0; i < thePlatforms.size(); i++) {
	    Platform p = (Platform)thePlatforms.elementAt(i);
	    if ( p.getName().equals(name) )
		return p;
	}
	throw new RuntimeException("Unknown platform: " + name);
    }
}
