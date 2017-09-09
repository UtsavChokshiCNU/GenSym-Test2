package com.gensym.gda.dialogs.blocks;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.StringVector;
import com.gensym.ntw.TwAccess;
import com.gensym.gda.controls.*;

public class gdiSoundBite extends BlocksDialog {
	
	public gdiSoundBite() {}

	public gdiSoundBite(java.awt.Frame frame) {
		super(frame);

		soundFileAndDirectory = new FileEditor();
		dpanel.placeAttributeEditor(soundFileAndDirectory, SOUND_FILE_, 0);
		soundFileAndDirectory.setFileDialogTitle(localize("soundFileAndDirectoryTitle"));
		
		soundDriver = new FileEditor();
		dpanel.placeAttributeEditor(soundDriver, SOUND_DRIVER_, 1);
		soundDriver.setFileDialogTitle(localize("soundDriverTitle"));
		
		soundDuration = new IntervalOrNoneEditor();
		dpanel.placeAttributeEditor(soundDuration, SOUND_DURATION_, 2);
		
		volume = new SpinEditor();
		dpanel.placeAttributeEditor(volume, VOLUME_, 3);
		
		loop = new SpinEditor();
		dpanel.placeAttributeEditor(loop, LOOP_, dpanel.integerFieldType, 4);
		
		priority = new ComboBoxEditor();
		priority.getComboBox().setChoices(new StringVector(new String[]
			{"high", "urgent", "low", "normal"}));
		dpanel.placeAttributeEditor(priority, PRIORITY_,dpanel.symbolFieldType, 5);
		
	}
	
	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		soundFileAndDirectory.setConnection(connection);
		soundDriver.setConnection(connection);
	}
		
	protected FileEditor soundFileAndDirectory;
	protected FileEditor soundDriver;
	protected IntervalOrNoneEditor soundDuration;
	protected SpinEditor volume;
	protected SpinEditor loop;
	protected ComboBoxEditor priority;
	
	protected final static Symbol SOUND_FILE_ = Symbol.intern("SOUND-FILE");
	protected final static Symbol SOUND_DRIVER_ = Symbol.intern("SOUND-DRIVER");
	protected final static Symbol SOUND_DURATION_ = Symbol.intern("SOUND-DURATION");
	protected final static Symbol VOLUME_ = Symbol.intern("VOLUME");
	protected final static Symbol LOOP_ = Symbol.intern("LOOP");
	protected final static Symbol PRIORITY_ = Symbol.intern("PRIORITY");

}