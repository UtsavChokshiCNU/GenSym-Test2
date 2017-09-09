package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;

import com.gensym.gda.controls.*;

public class gdiRemoteProcess extends gdiPathConnectionPost {
	
	public gdiRemoteProcess() {}

	public gdiRemoteProcess(java.awt.Frame frame) {
		super(frame);

		name.getLabel().setText(localize("name-required"));		

        hostName = new TextOrNoneEditor();
        dpanel.placeAttributeEditor(hostName, 
            HOST_NAME_, new HostnameFieldType(), 1);
        
        portNumber = new SpinOrNoneEditor(0, MAXIMUM_G2_INT, 1);
        dpanel.placeAttributeEditor(portNumber, 
            PORT_NUMBER_, dpanel.integerFieldType, 2);


		displaySize = new ComboBoxEditor();
		displaySize.getComboBox().setChoices(new StringVector(
			new String[]{"small", "large", "extra-large"}));
		dpanel.placeAttributeEditor(displaySize, 
			DISPLAY_SIZE_, dpanel.symbolFieldType, 3);

		displayLocation = new RadioBoxEditor();
		displayLocation.setLabels(new StringVector());
		displayLocation.setMembers(new StringVector(
			new String[]{"rhs", "lhs"}));
		displayLocation.setRowsAndColumns(1, 2);
		dpanel.placeAttributeEditor(displayLocation, 
			DISPLAY_LOCATION_, dpanel.symbolFieldType, 4);
		
		
		displayFormat= new ComboBoxEditor();
		displayFormat.getComboBox().setChoices(new StringVector(
			new String[]{"minimal", "full", "summary", "normal"}));
		dpanel.placeAttributeEditor(displayFormat, 
			DISPLAY_FORMAT_, dpanel.symbolFieldType, 5);
		
	}

    private static final int MAXIMUM_G2_INT = 0x1FFFFFFF;

    protected TextOrNoneEditor hostName;
    protected SpinOrNoneEditor portNumber;
	protected ComboBoxEditor displaySize;
	protected RadioBoxEditor displayLocation;
	protected ComboBoxEditor displayFormat;

    protected final static Symbol HOST_NAME_ = Symbol.intern("HOST");
    protected final static Symbol PORT_NUMBER_ = Symbol.intern("PORT-NUMBER");

	protected final static Symbol DISPLAY_SIZE_ = Symbol.intern("DISPLAY-SIZE");
	protected final static Symbol DISPLAY_LOCATION_ = Symbol.intern("DISPLAY-LOCATION");
	protected final static Symbol DISPLAY_FORMAT_ = Symbol.intern("DISPLAY-FORMAT");

}