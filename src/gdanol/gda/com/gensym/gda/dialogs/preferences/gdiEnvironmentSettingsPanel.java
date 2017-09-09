package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;

public class gdiEnvironmentSettingsPanel extends PreferencesPanel {
	
	public gdiEnvironmentSettingsPanel(PreferencesDialog dialog) {
		super(dialog);

		settingClass=GDL_ENVIRONMENT_SETTINGS_;

		propagateExpirationEvents = CheckBoxEditor.createYesNoCheckBox();
		placeAttributeEditor(propagateExpirationEvents, PROPAGATE_EXPIRATION_EVENTS_, 0);
		
		sweepInterval=new IntervalEditor();
		placeAttributeEditor(sweepInterval, SWEEP_INTERVAL_, 1);
		
		animationDelay = new SpinEditor();
		animationDelay.setIncrement(0.01);
		placeAttributeEditor(animationDelay, ANIMATION_DELAY_, 2);
		
		snapGridResolution = new SpinEditor();
		placeAttributeEditor(snapGridResolution, SNAP_GRID_RESOLUTION_, 3);
		
		blocksBetweenAllowOtherProcessing = new SpinEditor();
		placeAttributeEditor(blocksBetweenAllowOtherProcessing, 
			BLOCKS_BETWEEN_ALLOW_OTHER_PROCESSING_, 4);

		maximumDataSeekingTimeout = new SpinEditor();
		placeAttributeEditor(maximumDataSeekingTimeout, MAXIMUM_DATA_SEEKING_TIMEOUT_, 5);
	}

	
	protected CheckBoxEditor propagateExpirationEvents;
	protected IntervalEditor sweepInterval;
	protected SpinEditor animationDelay;
	protected SpinEditor snapGridResolution;
	protected SpinEditor blocksBetweenAllowOtherProcessing;	
	protected SpinEditor maximumDataSeekingTimeout;	

	protected final static Symbol PROPAGATE_EXPIRATION_EVENTS_ = Symbol.intern("PROPAGATE-EXPIRATION-EVENTS");	
	protected final static Symbol SWEEP_INTERVAL_ = Symbol.intern("SWEEP-INTERVAL");	
	protected final static Symbol ANIMATION_DELAY_ = Symbol.intern("ANIMATION-DELAY");	
	protected final static Symbol SNAP_GRID_RESOLUTION_ = Symbol.intern("SNAP-GRID-RESOLUTION");	
	protected final static Symbol BLOCKS_BETWEEN_ALLOW_OTHER_PROCESSING_=
		Symbol.intern("BLOCKS-BETWEEN-ALLOW-OTHER-PROCESSING");
	protected final static Symbol MAXIMUM_DATA_SEEKING_TIMEOUT_ = Symbol.intern("MAXIMUM-DATA-SEEKING-TIMEOUT");	
	protected final static Symbol GDL_ENVIRONMENT_SETTINGS_ = Symbol.intern("GDL-ENVIRONMENT-SETTINGS");	
}