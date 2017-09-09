
package com.gensym.gda.controls;

import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
//for Rose Engineering
import java.lang.String;

public class SampleComboBoxEditor extends ComboBoxEditor {

    public SampleComboBoxEditor() {
    	this(FIXED);
	}
	
	public SampleComboBoxEditor(int type) {
		super.setFieldType(symbolFieldType);
		setType(type);
	}
	
	public void setType (int i) {
		sampleType = i;
		switch (i) {
			case FIXED: combobox.setChoices(fixed);break;
			case NO_FIXED: 
			default: combobox.setChoices(nofixed);
		}
	}	
	
	public int getType() {return sampleType;}
	
	//must be statusFieldType only
    public void setFieldType(FieldType type) {}

	
	private static FieldType symbolFieldType= new LowerCaseSymbolFieldType();

	protected final static String Points="points";
	protected final static String Time="time";
	protected final static String Fixed="fixed";
	
	/** contains true, none, false, unknwown choices
	*/
	public final static int FIXED = 0;
	/** contains points, time, fixed choices
	*/
	public final static int NO_FIXED = 1;
	/** contains points, time choices
	*/
	
	protected final static StringVector fixed = new StringVector(
		new String[] {Points, Time, Fixed});
	protected final static StringVector nofixed = new StringVector(
		new String[] {Points, Time});
	
	
	private int sampleType;
}