
package com.gensym.gda.controls;

import java.awt.BorderLayout;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.border.LineBorder;
import javax.swing.JTextField;
import javax.swing.JPanel;
import javax.swing.JButton;

import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.NoSuchAttributeException;

import com.gensym.controls.FieldType;
import com.gensym.dlgevent.ObjectUpdateEvent;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.editor.color.*;
import com.gensym.dlg.*;

/**
*/
public class ColorEditor extends AbstractAttributeEditor {

    public ColorEditor() {
		colorfield = new JTextField();
		JPanel panel = new JPanel(new BorderLayout());
		panel.setBorder(colorfield.getBorder());
		colorfield.setBorder(new LineBorder(colorfield.getBackground(), borderWidth));
		colorfield.setEnabled(false);
		colorfield.setHorizontalAlignment(JTextField.CENTER);
		colorfield.setText("");
		setLayout(layout = new GridBagLayout());
		c=new GridBagConstraints();
		c.fill=GridBagConstraints.HORIZONTAL;
		c.weightx=1.0;
		layout.setConstraints(panel, c);
		add(panel);		
		panel.add(colorfield, BorderLayout.CENTER);

		button = new JButton("...");
		panel.add(button, BorderLayout.EAST);
		
		button.addActionListener(new ShowColorDialogListener());
		int x;
		button.setPreferredSize(
			new java.awt.Dimension(x=colorfield.getPreferredSize().height, x));
		
		colorDialog = new G2ColorsDialog(null, "choose a color", true, new ColorDialogClient());

	}

	public void setFieldType(FieldType type) {}

	public FieldType getFieldType() { return null;}

	public void setEnabled(boolean enabled) {
		super.setEnabled(enabled);
		button.setEnabled(enabled);
	}

	public void objectUpdated(ObjectUpdateEvent event) {		
		Structure values = (Structure) event.getUpdatedObject();
		try {
			Symbol color = (Symbol) values.getAttributeValue(getAttribute());
			if(getDisableIfNotUpdated()) setEnabled(true);
			colorfield.setBackground(G2ColorMap.get(color));
			colorfield.setBorder(new LineBorder(colorfield.getBackground(), borderWidth));
//			colorfield.setText(color.toString().toLowerCase());
			((G2ColorsDialog)colorDialog).setSelectedColor(
				g2colors.getColorStringForColorSymbol(color));
		} catch (NoSuchAttributeException e) {
			if(getDisableIfNotUpdated()) setEnabled(false);
		}
	}

	protected void fireChangeDialogColors() {
		Symbol color = ((G2ColorsDialog)colorDialog).getSelectedColorSymbol();
		colorfield.setBackground(((G2ColorsDialog)colorDialog).getSelectedColor());
		colorfield.setBorder(new LineBorder(colorfield.getBackground(), borderWidth));
//		colorfield.setText(color.toString().toLowerCase());
		((G2ColorsDialog)colorDialog).setSelectedColor(
			g2colors.getColorStringForColorSymbol(color));
		fireObjectChange(color);
	}
	
	class ShowColorDialogListener implements ActionListener {	
		public ShowColorDialogListener() {}		
		public void actionPerformed(ActionEvent e) {colorDialog.show();}
	}
	
	
	class ColorDialogClient implements StandardDialogClient {
		public ColorDialogClient () {}

		public void dialogDismissed(StandardDialog standarddialog, int i) {
			if (colorDialog!=standarddialog)
				return;
				
			if (i!=2) {
				fireChangeDialogColors();
			}
		}
	}
	
	protected JTextField colorfield;
	protected JButton button;
	final G2Colors g2colors = new G2Colors();

	protected StandardDialog colorDialog;
	protected int borderWidth=3;
	protected GridBagLayout layout;
	protected GridBagConstraints c;
}