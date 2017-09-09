
package com.gensym.gda.controls;

import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;


/**
ComboBoxEditor which can contain the following choices:
"true", "none", "false", "unknown", "always", "all-changes"
(all of type Symbols, and true is the symbol .TRUE, false is the symbol .FALSE).
*/
public class StatusComboBoxEditor extends ComboBoxEditor {

    public StatusComboBoxEditor() {
    	this(UNKNOWN);
	}
	
	public StatusComboBoxEditor(int type) {
		super.setFieldType(statusFieldType);
		setType(type);
	}
	
	public void setType (int i) {
		statusType = i;
		switch (i) {
			case ALWAYS: combobox.setChoices(always);break;
			case ALL_CHANGES: combobox.setChoices(allchanges);break;
			case SMALL_UNKNOWN: combobox.setChoices(smallunknown);break;
            case ALWAYS_UNKNOWN: combobox.setChoices(alwaysunknown);break;
			case UNKNOWN: 
			default: combobox.setChoices(unknown);
		}
	}	
	
	public int getType() {return statusType;}
	
	//must be statusFieldType only
    public void setFieldType(FieldType type) {}

	
	private static StatusFieldType statusFieldType= new StatusFieldType();

	protected final static String True="true";
	protected final static String AllChanges="all-changes";
	protected final static String None="none";
	protected final static String False="false";
	protected final static String Unknown="unknown";
	protected final static String Always="always";
	
	/** contains true, none, false, unknwown choices
	*/
	public final static int UNKNOWN = 0;
	/** contains true, none, false, always choices
	*/
	public final static int ALWAYS = 1;
	/** contains true, all-changes, false, unknown choices
	*/
	public final static int ALL_CHANGES = 2;
	/** contains true, false, unknwown choices
	*/
	public final static int SMALL_UNKNOWN = 3;
	
    /** contains true, always, false, unknwown choices
    */
    public final static int ALWAYS_UNKNOWN = 4;

	protected final static StringVector unknown = new StringVector(
		new String[] {True, None, False, Unknown});
	protected final static StringVector smallunknown = new StringVector(
		new String[] {True, False, Unknown});
    protected final static StringVector alwaysunknown = new StringVector(
        new String[] {True, Always, False, Unknown});
    protected final static StringVector always =  new StringVector(
		new String[] {True, None, False, Always});
	protected final static StringVector allchanges=  new StringVector(
		new String[] {True, AllChanges, False, Unknown});
	
	
	private int statusType;
}