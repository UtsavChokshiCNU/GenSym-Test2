package com.gensym.nols.main;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;



/**
 *
 * @version	1.0 Sep 30 2004
 * @author G.Chen
**/
//public class IndependentDataManager extends PrintWriter {  // cannot do this, since System.setErr() requires a printStream
public class IndependentDataManager extends Object {

	private Vector lineCharts; 
	private Vector projectionCharts; 
	private Vector xyCharts; 

	public IndependentDataManager() {
		lineCharts = new Vector();
		projectionCharts = new Vector();
		xyCharts = new Vector();
	}


}