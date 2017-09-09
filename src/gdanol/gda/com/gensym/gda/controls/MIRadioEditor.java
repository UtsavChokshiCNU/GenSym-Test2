
package com.gensym.gda.controls;

import com.gensym.util.Symbol;
import com.gensym.controls.FieldType;
import com.gensym.beansruntime.StringVector;

/**
RadioBoxEditor which can contains only 
ignore, queue, and/or ok values
*/
public class MIRadioEditor extends RadioBoxEditor {


	/**This constructor create RadioBoxEditor 
	with values ignore, queue, and ok
	*/
	public MIRadioEditor() {
    	this(true, true);
  }
	
	/**This constructor create RadioBoxEditor 
	with values ignore, ok, and if withQueue then queue
        @param withQueue controls whether to create the "queue" choice
	*/
	public MIRadioEditor(boolean withQueue) {
		this(withQueue, true);
	}

	/**This constructor create RadioBoxEditor 
	with value ignore, and if withQueue then queue and if withOk then ok
        @param withQueue controls whether to create the "queue" choice
        @param withOk controls whether to create the "ok" choice
	*/	
	public MIRadioEditor(boolean withQueue, boolean withOk) {
		super.setFieldType(symbolFieldType);
		members = new StringVector(new String[]{Ignore});
		if (withQueue)
			members.add(Queue);
		if (withOk)
			members.add(Ok);
		setLabels(new StringVector());
		setMembers(members);
		setRowsAndColumns(1, members.size());
	}
	
	//must be statusFieldType only
    public void setFieldType(FieldType type) {}

	private static LowerCaseSymbolFieldType symbolFieldType= new LowerCaseSymbolFieldType();

	protected final static String Ignore="ignore";
	protected final static String Queue="queue";
	protected final static String Ok="ok";
	
	protected StringVector members;
}