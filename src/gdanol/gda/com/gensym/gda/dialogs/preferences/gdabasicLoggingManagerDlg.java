package com.gensym.gda.dialogs.preferences;

import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.ntw.TwAccess;

public class gdabasicLoggingManagerDlg extends PreferencesDialog {
	
	public gdabasicLoggingManagerDlg() {}

	public gdabasicLoggingManagerDlg(java.awt.Frame frame) {
		super(frame);
		centerPane=dpanel=new PreferencesPanel(this);
		scrollPane.setViewportView(dpanel);

		glfLoggingEnabled = new CheckBoxEditor();
		dpanel.placeAttributeEditor(glfLoggingEnabled, GLF_LOGGING_ENABLED_, 0);

		glfLogDirectory = new FileEditor();
		glfLogDirectory.setFileSelectionMode(javax.swing.JFileChooser.DIRECTORIES_ONLY);
		glfLogDirectory.setFileDialogTitle(localize("LogDirectoryFileDialogTitle"));
		dpanel.placeAttributeEditor(glfLogDirectory, GLF_LOG_DIRECTORY_, 1);

		glfLogFileNameTemplate = new TextFieldEditor();
		dpanel.placeAttributeEditor(glfLogFileNameTemplate, 
			GLF_LOG_FILE_NAME_TEMPLATE_, 2);
	
		glfTimeIntervalToOpenNewLogFile = new IntervalEditor();
		dpanel.placeAttributeEditor(glfTimeIntervalToOpenNewLogFile, 
			GLF_TIME_INTERVAL_TO_OPEN_NEW_LOG_FILE_, 3);

		glfMaximumFileSizeInBytes = new SpinEditor(0, Integer.MAX_VALUE, 1);
		dpanel.placeAttributeEditor(glfMaximumFileSizeInBytes, 
			GLF_MAXIMUM_FILE_SIZE_IN_BYTES_, dpanel.integerFieldType, 4);

		gqmLogComments = new CheckBoxEditor();
		dpanel.placeAttributeEditor(gqmLogComments, GQM_LOG_COMMENTS_, 6);

		glfAutomaticallyDeleteEmptyLogFiles = new CheckBoxEditor();
		dpanel.placeAttributeEditor(glfAutomaticallyDeleteEmptyLogFiles, 
			GLF_AUTOMATICALLY_DELETE_EMPTY_LOG_FILES_, 9);

		gqmTimeFormat = new ComboBoxEditor();
		gqmTimeFormat.setChoices(new com.gensym.beansruntime.StringVector(
			new String[]{"datetime", "date","filetime","time"}));
		dpanel.placeAttributeEditor(gqmTimeFormat, 
			GQM_TIME_FORMAT_, dpanel.symbolFieldType, 10);
	
	}

	public void setConnection(TwAccess connection) {
		super.setConnection(connection);
		glfLogDirectory.setConnection(connection);
	}

	protected CheckBoxEditor glfLoggingEnabled;
	protected FileEditor glfLogDirectory;
	protected TextFieldEditor glfLogFileNameTemplate;
	protected IntervalEditor glfTimeIntervalToOpenNewLogFile;
	protected SpinEditor glfMaximumFileSizeInBytes;
	protected CheckBoxEditor gdaLogEventsIncrementally;
	protected CheckBoxEditor gqmLogComments;
	protected CheckBoxEditor glfAutomaticallyDeleteEmptyLogFiles;
	protected ComboBoxEditor gqmTimeFormat;
	
	protected final static Symbol GLF_LOGGING_ENABLED_=
		Symbol.intern("GLF-LOGGING-ENABLED");
	protected final static Symbol GLF_LOG_DIRECTORY_=
		Symbol.intern("GLF-LOG-DIRECTORY");
	protected final static Symbol GLF_LOG_FILE_NAME_TEMPLATE_=
		Symbol.intern("GLF-LOG-FILE-NAME-TEMPLATE");
	protected final static Symbol GLF_TIME_INTERVAL_TO_OPEN_NEW_LOG_FILE_=
		Symbol.intern("GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE");
	protected final static Symbol GLF_MAXIMUM_FILE_SIZE_IN_BYTES_=
		Symbol.intern("GLF-MAXIMUM-FILE-SIZE-IN-BYTES");
	protected final static Symbol GQM_LOG_COMMENTS_=
		Symbol.intern("GQM-LOG-COMMENTS");
	protected final static Symbol GLF_AUTOMATICALLY_DELETE_EMPTY_LOG_FILES_=
		Symbol.intern("GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES");
	protected final static Symbol GQM_TIME_FORMAT_=
		Symbol.intern("GQM-TIME-FORMAT");

}