
package com.gensym.gda.controls;

import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;
//for Rose Engineering
import java.lang.String;

public class UpdateRadioBoxEditor extends RadioBoxEditor {

    public UpdateRadioBoxEditor() {
    	this(FIXED);
	}
	
	public UpdateRadioBoxEditor(int type) {
		super.setFieldType(symbolFieldType);
		radiobox.setLabels(new StringVector());
		setType(type);
	}
	
	public void setType (int i) {
		sampleType = i;
		switch (i) {
			case FIXED: 
				radiobox.setMembers(fixed);
				setRowsAndColumns(1, 3);
				break;
			case NO_FIXED: 
			default: radiobox.setMembers(nofixed);
				setRowsAndColumns(1, 2);
		}
	}	
	
	public int getType() {return sampleType;}
	
	//must be symbolFieldType only
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