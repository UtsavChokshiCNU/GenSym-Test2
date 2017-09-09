package com.gensym.nols.dlg;

import javax.swing.*;
import java.util.*;


public class NolList extends JList {

	public NolList(DefaultListModel model) {
		super((ListModel) model);
	}

	/** One additional method used for pre-sizing entries in list. */
	public void presize(Vector vars) {
		if(vars.isEmpty()) 
			return;
		DefaultListModel model = (DefaultListModel) getModel();
		// if the list already has elements, find the biggest one
		int maxLength = 0;
		for(int i=0;i<model.getSize();i++) {
			if(model.elementAt(i).toString().length() > maxLength) {
				maxLength = model.elementAt(i).toString().length();
			}
		}
		// now see if any of the new elements is longer
		int index = -1;
		for(int z = 0; z < vars.size(); z++) {
			if(vars.elementAt(z).toString().length() > maxLength) {
				maxLength = vars.elementAt(z).toString().length();
				index = z;
			}
		}
		if (index>=0){
			setPrototypeCellValue(vars.elementAt(index));
		}
	}

	/** A convenience method for rapidly adding a vector of strings, to list.
	This method applies the toString() method to the objects in the Vector. */
	public void addElements(Vector vars) {
		if(vars.isEmpty()) 
			return;
		presize(vars);  // much, much faster for long lists!
		DefaultListModel model = (DefaultListModel) getModel();
		for(int z = 0; z < vars.size(); z++) {
			model.addElement(vars.elementAt(z).toString());
		}
	}

	/** A convenience method for rapidly adding a vector of objects, to list.
	This method DOES NOT apply the toString() method to the objects in the Vector. */
	public void addObjects(Vector vars) {
		if(vars.isEmpty()) 
			return;
		presize(vars);  // much, much faster for long lists!
		DefaultListModel model = (DefaultListModel) getModel();
		for(int z = 0; z < vars.size(); z++) {
			model.addElement(vars.elementAt(z));
		}
	}
}
