package com.gensym.nols.data;

import java.awt.Color;
import java.io.Serializable;

 /**
 * Gensym NolLabel Class
 * @version     1.0 September 30, 1998
 * @author      Gang Chen
 **/

public class NolLabel implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	public String name;
	private String comment;		//Defaults are "".
	private Color labelColor;
	private int labelOrder;
	private transient Project project;

/** Default constructor.*/
	public NolLabel() {
		super();
		name = "";
		comment = "";
		labelColor = Color.red;
		labelOrder = -1;
	}

/** Constructor with name.*/
	public NolLabel(String name) {
		this();
		this.name = new String(name);
	}

/** Constructor with name.*/
	public NolLabel(String labelName, String comment, Color labelColor){
		this();
		this.name = labelName;
		this.comment = comment;
		this.labelColor = labelColor;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		NolLabel cloned = (NolLabel) super.clone();
		if(labelColor != null){
			float[] hsb = Color.RGBtoHSB(labelColor.getRed(), labelColor.getGreen(), labelColor.getBlue(), null);
			cloned.labelColor = Color.getHSBColor(hsb[0], hsb[1], hsb[2]);
		}
		
		cloned.project = project == null ? null : (Project) project.clone();
		return cloned;
	}
	
	public void setName(String n) {
		name = n;
		project.labelNameChanged(this);
	}
	
	public String getName() {
		return name;
	}

/** Return the comment of this label.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this label.*/
	public void setComment(String c){
		comment = c;
	}

/** Return the label color index of this label.*/
	public Color getLabelColor(){
		return labelColor;
	}

/** Set the label color index of this label.*/
	public void setLabelColor(Color c){
		labelColor = c;
		project.labelColorChanged(this);
	}

/** Return the label order index of this label.*/
	public int getLabelOrder(){
		return labelOrder;
	}

/** Set the label order index of this label.*/
	public void setLabelOrder(int i){
		labelOrder = i;
	}

/** Return the project of this label.*/
	public Project getProject(){
		return project;
	}

/** Set the project of this label.*/
	public void setProject(Project p){
		project = p;
	}

/** Returns a String object representing this column value.  */
	@Override
	public String toString(){
		return name;
	}

/** Initialize the transient attributes.*/
	public void initTransient(Project p){
		project = p;
	}

}