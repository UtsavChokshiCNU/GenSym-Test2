
package com.gensym.gda.dialogs.blocks;


import javax.swing.border.TitledBorder;
import javax.swing.border.LineBorder;
import java.util.Hashtable;

import com.gensym.dlgevent.ObjectChangeEvent;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.dlgevent.ObjectChangeListener;
import com.gensym.dlgevent.ObjectUpdateListener;
import com.gensym.controls.FieldType;
import com.gensym.util.Structure;
import com.gensym.dlg.WarningDialog;

import com.gensym.gda.controls.*;

/**
BoundPanel contains two controls with quantity FieldType, where
one of the controls represent minimum value and the other - maximum value.
To create BoundPanel:<br>
1. Create BoundPanel instance.<br>
2. Create minimum and maximum controls.<br>
3. Add controls to BoundPanel.<br>
4. Register editors in BoundPanel using setEditors or setMinEditor and setMaxEditor methods.<br>
5. Set the Border Title of the BoundPanel if needed using setBorderTitle method.<br>
6. Add BoundPanel to the appropriate dialog.
*/
public class BoundPanel extends BlocksPanel 
	implements ObjectChangeListener, ObjectUpdateListener {


	public BoundPanel(BlocksDialog d) {
    	super(d);
    	values = new Hashtable();
    	minEditor = null;
    	maxEditor = null;
		border = new TitledBorder(LineBorder.createBlackLineBorder(),"");
		dialog.addObjectUpdateListener(this);
		setBorder(border);
	}

	public void setEditors(AbstractAttributeEditor max,
							AbstractAttributeEditor min) {
		maxEditor = max;
		minEditor = min;
	}

	public void setMinEditor(AbstractAttributeEditor min) {minEditor = min;}
	public void setMaxEditor(AbstractAttributeEditor max) {maxEditor = max;}

	public AbstractAttributeEditor getMinEditor() {return minEditor ;}
	public AbstractAttributeEditor getMaxEditor() {return maxEditor ;}

	public void setBorderTitle(String title) {border.setTitle(title);}
	public String getBorderTitle() {return border.getTitle();}
	
	
	/**Override superior method. BoundPanel is listening for change events from editors
	and perform additional validation.
	*/
	public void registerEditor(AbstractAttributeEditor editor) {
	    dialog.addEditor(editor);
	   	editor.addObjectChangeListener(this);
    	dialog.addObjectUpdateListener(editor);		
	}
	
	public void objectChanged(ObjectChangeEvent e) {
		AbstractAttributeEditor editor = (AbstractAttributeEditor) e.getSource();
		Object value = e.getChangedObject();
		boolean isvalid = checkNewValue(editor, value);
		if (isvalid) {
			dialog.objectChanged(e);
			values.put(editor, value);
		} else 
			returnToPrevious(editor);
	}

	public void objectUpdated(ObjectUpdateEvent e) {
		if (minEditor == null || maxEditor == null)
			return;// *** throw exception? !!!
		values.put(minEditor, e.getUpdatedValue(minEditor.getAttribute()));
		values.put(maxEditor, e.getUpdatedValue(maxEditor.getAttribute()));
        checkNewValue();
	}

	protected boolean checkNewValue(AbstractAttributeEditor editor, Object value) {
		Object oldvalue = values.get(editor);
		values.put(editor, value);
		boolean result = checkNewValue();
	    values.put(editor, oldvalue);
	    return result;
			
	}
	
	protected boolean checkNewValue() {
	    double bandwidth = ((Number) values.get(maxEditor)).doubleValue() - 
			((Number) values.get(minEditor)).doubleValue();
			
		if (bandwidth <0) {
			warningDialog(localize("MinLargerThenMax"));
			return false;
		}
			
  		((Boundary)minEditor).setMaxValue(getCurrentValue(maxEditor, minEditor.getFieldType()));
		((Boundary)maxEditor).setMinValue(getCurrentValue(minEditor, maxEditor.getFieldType()));	    
	    return true;
		    
	}
	
	protected void returnToPrevious(AbstractAttributeEditor editor) {
		Structure s= new Structure();
		s.setAttributeValue(editor.getAttribute(),values.get(editor));
		editor.objectUpdated(new ObjectUpdateEvent(this, s)); 
	}	
	
    protected void warningDialog(String s){
		WarningDialog warningdialog = new WarningDialog(null, "", true, s, null);
		warningdialog.pack();
		warningdialog.setVisible(true);
    }

	protected double getCurrentValue(AbstractAttributeEditor editor, FieldType fieldtype) {
		Number value= (Number) values.get(editor);
		if (fieldtype.getTypeName().equals("Integer"))
			return value.intValue();
		else
			return value.doubleValue();
	}
	
	private TitledBorder border;
	
	protected AbstractAttributeEditor minEditor;
	protected AbstractAttributeEditor maxEditor;
	protected Hashtable values;
		
}