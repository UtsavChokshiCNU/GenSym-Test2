package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;
import com.gensym.nols.dlg.*;

public class NolLabelWKSP  extends NolInternalFrame{
    protected static final String LABELWKSP_NAME = "NameLabel";
    protected static final String LABELWKSP_COMMENT = "CommentLabel";
    protected static final String LABELWKSP_COLOR = "ColorLabel";
    protected static final String LABELWKSP_CHANGECOLOR = "LabelWKSP_ChangeColor";
    protected static final String LABELWKSP_APPLYLABEL = "LabelWKSP_ApplyLabel";
    protected static final String DELETE = "DeleteLabel";

	private NolMainFrame frame;
	private JTextField labelName;
	private NolLabel nolLabel;
	private JTextArea descriptArea;
	private Action actionListener;
	private ColoredSquare colorBlock;

	public NolLabelWKSP (NolMainFrame frame, NolLabel nolLabel){
		super(frame.getProject().getRawDataSource());
		this.frame = frame;
		this.nolLabel = nolLabel;
		String title = "Label:["+nolLabel.getName()+"]";
		setTitle(title);
		actionListener = new ControlAction();
		initLayout();
		initDisplay();
	}

	private void initLayout(){
		JPanel workPane = new JPanel(new BorderLayout());
													    
		JPanel infoPane = new JPanel(new BorderLayout());
		JPanel namePane = new JPanel(new GridLayout(2,2,10,10));
		namePane.setBorder(new EmptyBorder(10,10,10,10));
		namePane.add(new JLabel(frame.getNolResourceString(LABELWKSP_NAME)+":"));
		labelName = new JTextField();
		labelName.addActionListener(actionListener);
		namePane.add(labelName);
//		namePane.add(new JLabel("Color:"));
		namePane.add(new JLabel(frame.getNolResourceString(LABELWKSP_COLOR)+":"));
		colorBlock = new ColoredSquare(Color.red, true);
		namePane.add(colorBlock);

		JPanel descriptPane = new JPanel(new GridLayout());
		descriptPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(LABELWKSP_COMMENT)+":", TitledBorder.LEFT , TitledBorder.TOP));
		descriptArea = new JTextArea();
		descriptArea.getDocument().addDocumentListener((DocumentListener)actionListener);
		JScrollPane listScrollPane = new JScrollPane(descriptArea);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listScrollPane.setPreferredSize(NolMainFrame.vpad50); 
		descriptPane.add(listScrollPane);

		infoPane.add("North",namePane);
		infoPane.add("Center",descriptPane);

		workPane.add("Center",infoPane);
		workPane.add("East",getControlPanel());
		setContentPane(workPane);

	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(5,1,5,5));
		JButton but = new JButton(frame.getNolResourceString(LABELWKSP_CHANGECOLOR));
		but.setActionCommand("Change Color...");
		but.addActionListener(actionListener);
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(LABELWKSP_APPLYLABEL));
		but.setActionCommand("Apply Label...");
		but.addActionListener(actionListener);
		but.setEnabled(false); //Temp gchen 9/9/98
  		pane0.add(but);
		but = new JButton(frame.getNolResourceString(DELETE));
		but.setActionCommand("Delete");
		but.addActionListener(actionListener);
  		pane0.add(but);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad500));
		control.add(Box.createVerticalGlue());
		return control;
	}


	private void initDisplay(){
		labelName.setText(nolLabel.getName());
		descriptArea.setText(nolLabel.getComment());
		colorBlock.setShowColor(nolLabel.getLabelColor());

	}


	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+1,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+1,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

	public NolLabel getLabel(){
		return nolLabel;
	}

	private void labelChanged(){
		colorBlock.setShowColor(nolLabel.getLabelColor());
		colorBlock.validate();
		colorBlock.repaint(0l);
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction implements DocumentListener, Runnable {
		String command;
		Object source;
		ControlAction() {super("controlAction");}
		@Override
		public void actionPerformed(ActionEvent e) {
			command = e.getActionCommand();
			source = e.getSource();
			new Thread (this).start();
		}
        @Override
		public void run() {
			if(command.equals("Change Color...")){
				Project project = frame.getProject();
				NolColorChooser colorChooser = new NolColorChooser((JFrame)frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				colorChooser.dispose();
				if(!colorChooser.getResult()) {
					return;
				}
				setWaitCursor(true);
				nolLabel.setLabelColor(color);
				labelChanged();
				refreshDisplay();
				setWaitCursor(false);
			}else if(command.equals("Apply Label...")){

			}else if(command.equals("Delete")){
				setWaitCursor(true);
				frame.removeLabel(nolLabel);
				setWaitCursor(false);
			}else if(source.equals(labelName)){
				setWaitCursor(true);
				String n = labelName.getText();
				if(!n.equals("")) {
					nolLabel.setName(n);
				}else{
					labelName.setText(nolLabel.getName());
				}
				setWaitCursor(false);
			}
		}
		@Override
		public void changedUpdate(DocumentEvent e){}
		@Override
		public void insertUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			nolLabel.setComment(com);
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			String com = descriptArea.getText();
			nolLabel.setComment(com);
		}
    }	
}

