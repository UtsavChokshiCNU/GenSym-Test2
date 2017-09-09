package com.gensym.gda.dialogs.preferences;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;

import com.gensym.beansruntime.StringVector;
import com.gensym.util.Symbol;
import com.gensym.gda.controls.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

public class gdiTabularViewTemplatePanel extends PreferencesPanel implements ActionListener{
	
	public gdiTabularViewTemplatePanel(PreferencesDialog dialog) {
		super(dialog);

		linesPerRow = new SpinEditor(1, Integer.MAX_VALUE, 1);
		placeAttributeEditor(linesPerRow, LINES_PER_ROW_, integerFieldType, 0);
		
		fontSize=new ComboBoxEditor();
		fontSize.setChoices(new StringVector(new String[]{
			"extra-large", "large", "small"}));
		placeAttributeEditor(fontSize, FONT_SIZE_, symbolFieldType, 1);		
		
		initialColymnKeyToSort=new ComboBoxEditor();
		placeAttributeEditor(initialColymnKeyToSort, 
			INITIAL_COLUMN_KEY_TO_SORT_, symbolFieldType, 2);
		
		initialSortingOrder = new ComboBoxEditor();
		initialSortingOrder.setChoices(new StringVector(new String[]{
			"ascending", "descending"}));
		placeAttributeEditor(initialSortingOrder, 
			INITIAL_SORTING_ORDER_, symbolFieldType, 3);
		
		reSortNewEntries = new CheckBoxEditor();
		placeAttributeEditor(reSortNewEntries, 
			RESORT_NEW_ENTRIES_, symbolFieldType, 4);

		JPanel panel = new JPanel();
		layoutButton =new JButton(localize("LayoutButtonLabel"));
		layoutButton.addActionListener(this);
		panel.add(layoutButton);
		addPanel(panel, null, 5);

	}

	public void actionPerformed(ActionEvent e) {
		if (e.getSource()==layoutButton) {
			try {
				dialog.getConnection().callRPC(GQSV_LAUNCH_CONFIGURATION_,
					new Object[]{dialog.getEditedItem(), dialog.getConnection().retrieveSession()});
			} catch (G2AccessException error) {Trace.exception(error);}
			
		}

	}
	
	protected SpinEditor linesPerRow;
	protected ComboBoxEditor fontSize;
	protected ComboBoxEditor initialColymnKeyToSort;
	protected ComboBoxEditor initialSortingOrder;
	protected CheckBoxEditor reSortNewEntries;
	protected JButton layoutButton;

	
	protected final static Symbol LINES_PER_ROW_= Symbol.intern("GQMV-LINES-PER-ROW");
	protected final static Symbol FONT_SIZE_= Symbol.intern("GQMV-FONT-SIZE");
	protected final static Symbol INITIAL_COLUMN_KEY_TO_SORT_= Symbol.intern("_GQMV-INITIAL-COLUMN-KEY-TO-SORT");
	protected final static Symbol INITIAL_SORTING_ORDER_= Symbol.intern("_GQMV-INITIAL-SORTING-ORDER");
	protected final static Symbol RESORT_NEW_ENTRIES_= Symbol.intern("_GQMV-RESORT-NEW-ITEMS");
	protected final static Symbol GQSV_LAUNCH_CONFIGURATION_= Symbol.intern("GQSV-LAUNCH-CONFIGURATION");
	
}