package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.net.URL;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.nols.util.*;

import com.gensym.DEBUG	;

public class NolNewLabelWizard  extends NolWizardDialog {
	protected static final String TITLE_LABEL = "NewLabelWizard_Title";
	protected static final String STEP1_TITLE_LABEL = "NewLabelWizard_STEP1";
	protected static final String STEP2_TITLE_LABEL = "NewLabelWizard_STEP2";
	protected static final String COMMENT_LABEL = "CommentLabel";
	protected static final String WHAI_IS_LABEL = "NewLabelWizard_WhatIsLabel";
	protected static final String NAME_FOR_LABEL = "NewLabelWizard_NameForLabel";
	protected static final String COLOR_LABEL = "NewLabelWizard_LabelColorLabel";
	protected static final String MORE_LABEL = "NewLabelWizard_MoreLabel";
	protected static final String EXISTING_LABELS = "NewLabelWizard_ExistingLabel";
	protected static final String AVAILABLE_LABEL = "ColorChooser_availableLabel";
	protected static final String SELECT_COLOR = "NewLabelWizard_SelectColors";
 
	 
	private JTextField labelName;
	private JTextArea labelDescript;
	private JList labelList;
	private DefaultListModel labelListModel;
	private LabelListCellRenderer labelListCellRenderer;
	private Project project;
	private boolean noFire;
	private ControlAction actListener;
	private ColoredSquare colorBlock;
	private ColorComponent[] colorBlocks;
	private Color labelColor;
	
	private NolMainFrame frame;

	public NolNewLabelWizard (JFrame dw, String title) {
		super(dw, title, true, 2);
		this.frame = (NolMainFrame)dw;
		this.project = frame.getProject();
		actListener = new ControlAction(); 
		noFire = false;
		int labelColorIndex = project.getNumberOfLabels();
		labelColor = ColorMap.colors[ColorMap.defaultLabelColors[labelColorIndex]];
		initializeLayout();
		nextButton.setEnabled(false);
		finishButton.setEnabled(false);
	}

	public void setProject(Project p){
		project = p;
	}

	private void initializeLayout(){
		stepPanes.setElementAt(getGeneralPanel(),0);
		stepPanes.setElementAt(getColorPanel(),1);
	}

	private JPanel getGeneralPanel(){
		JPanel genPane = new JPanel(new BorderLayout());
		URL url = this.getClass().getResource("largeLabel.gif");
		ImageIcon importIcon = new ImageIcon(url);

		JPanel infoPane = new JPanel(new BorderLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));

		//String s = "Labels are used to indicate \nregions of special interest  \nin the raw data. Examples of \nlabel categories are outlier,\ntransition, product-grade-1, \nand cut.";
		
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(WHAI_IS_LABEL));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add("Center",infoLabel);
		infoPane.add("West",new JLabel(importIcon));

		genPane.add("North",infoPane);

		JPanel cenPane = new JPanel(new BorderLayout());

		JPanel namePane = new JPanel(new GridLayout(2,1,10,5));
 		namePane.setBorder(new EmptyBorder(10,10,10,10));

		namePane.add(new JLabel(frame.getNolResourceString(NAME_FOR_LABEL) + ":"));
		labelName = new JTextField();
//		labelName.addActionListener(actListener);
		labelName.getDocument().addDocumentListener((DocumentListener)actListener);
		namePane.add(labelName);

		cenPane.add("North",namePane);

		JPanel descripPane = new JPanel(new GridLayout());
		descripPane.setBorder(new TitledBorder(new EmptyBorder(10, 5, 25, 5),               
			frame.getNolResourceString(COMMENT_LABEL) + ":", TitledBorder.LEFT , TitledBorder.TOP));
		labelDescript = new JTextArea();
		JScrollPane listScrollPane = new JScrollPane(labelDescript);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		descripPane.add(listScrollPane);

		cenPane.add("Center",descripPane);
 		genPane.add("Center",cenPane);
		return genPane;
	}

	private JPanel getColorPanel(){
		JPanel colorPane = new JPanel(new BorderLayout());
		JPanel infoPane = new JPanel(new GridLayout());
 		infoPane.setBorder(new EmptyBorder(10,10,10,10));
	//	String s = "Label color is used to clearly mark the \nlabeled regions in spreadsheets and charts.";
		JTextArea infoLabel = new JTextArea(frame.getNolResourceString(COLOR_LABEL));
		infoLabel.setEditable(false);
		infoLabel.setLineWrap(true);
		infoLabel.setWrapStyleWord(true);
		infoLabel.setBackground(infoPane.getBackground());
		infoPane.add(infoLabel);
		colorPane.add("North",infoPane);

		JPanel colorselPane = new JPanel(new GridLayout(1,2,20,20));

		JPanel pane0 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		pane0.add(new JLabel(frame.getNolResourceString(SELECT_COLOR) + ":"));
		if(DEBUG.debugFlag){
			System.out.println("labelColor="+labelColor);
		}
		colorBlock = new ColoredSquare(labelColor, true);
		colorBlock.setPreferredSize(NolMainFrame.pad3020); 
		pane0.add(colorBlock);

		JPanel colorChoicePane = new JPanel(new BorderLayout());
		colorChoicePane.setBorder(new TitledBorder(frame.getNolResourceString(AVAILABLE_LABEL) + ":"));
		JPanel paletePane = new JPanel(new GridLayout(4,4,2,5));
		colorBlocks = new ColorComponent[16];
		for(int i=0;i<16;i++){
			Color c = ColorMap.colors[ColorMap.defaultLabelColors[i]];
			colorBlocks[i] = new ColorComponent(c);
			paletePane.add(colorBlocks[i]);
		}
		JButton more = new JButton(frame.getNolResourceString(MORE_LABEL) + "...");
		more.setActionCommand("More...");
		more.addActionListener(actListener);
		colorChoicePane.add("Center",paletePane);
		colorChoicePane.add("South",more);
		colorselPane.add(pane0);
		colorselPane.add(colorChoicePane);

		JPanel listPane = new JPanel(new GridLayout());
		listPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(EXISTING_LABELS) + ":", TitledBorder.LEFT , TitledBorder.TOP));
  		labelList = new JList(getLabelListModel());
		labelList.setCellRenderer(getLabelListCellRenderer());
		labelList.setBackground(Color.white);
		JScrollPane listScrollPane = new JScrollPane(labelList);
		listScrollPane.setBorder(BorderFactory.createLoweredBevelBorder());
		listPane.add(listScrollPane);

		JPanel cenPane = new JPanel(new BorderLayout());
 		cenPane.setBorder(new EmptyBorder(10,10,10,10));
		cenPane.add("North",colorselPane);
		cenPane.add("Center",listPane);



		colorPane.add("Center",cenPane);
		return colorPane;
	}

	private DefaultListModel getLabelListModel() {
		if (labelListModel == null) {
			labelListModel = new DefaultListModel();
		}	
		return labelListModel;
	}	

	private LabelListCellRenderer getLabelListCellRenderer() {
		if (labelListCellRenderer == null) {
			labelListCellRenderer = new LabelListCellRenderer(labelList);
		}	
		return labelListCellRenderer;
	}	

		
	class LabelListCellRenderer extends JLabel implements ListCellRenderer{		
		JList   listBox;

		LabelListCellRenderer(JList listBox) {
			setOpaque(true);
			this.listBox = listBox;
		}
		
		@Override
		public Component getListCellRendererComponent(
			JList list, 
			Object value, 
			int index, 
			boolean isSelected,
			boolean cellHasFocus){			
			String n = ((NolLabel)value).getName();
			Color c = ((NolLabel)value).getLabelColor();
			setIcon(new ColoredSquare(c)); //temp
			setBackground(Color.white);
			setForeground(Color.black);
			setText(n);
			return this;
		}
	}


	public void refresh(){
		int labelColorIndex = project.getNumberOfLabels();
		labelColor = ColorMap.colors[ColorMap.defaultLabelColors[labelColorIndex]];
		colorBlock.setShowColor(labelColor);
		labelName.setText("");
		currentStep = 0;
		modifyStep(true);

		String title = 		frame.getNolResourceString(TITLE_LABEL) + " - " + setTitleForStep(currentStep);
		title = title + " - " + frame.getNolResourceString(STEP1_TITLE_LABEL);
		setTitle(title);

		Vector labels = project.getLabels();
		getLabelListModel().removeAllElements();
		for(int i=0;i<labels.size();i++){
			getLabelListModel().addElement(labels.elementAt(i));
		}
		labelDescript.setText("");
		stepPane.removeAll();
		stepPane.add((JPanel)stepPanes.elementAt(0));
		stepPane.validate();
		stepPane.repaint(0l);
		nextButton.setEnabled(false);
		finishButton.setEnabled(false);
	}

	public void setFocus(){
		labelName.requestFocus();
	}

	@Override
	protected void modifyStep(boolean isNext){
		super.modifyStep(isNext);
		String title = frame.getNolResourceString(TITLE_LABEL) + " - " + setTitleForStep(currentStep);
		if(currentStep == 1){
			title = title + " - " + frame.getNolResourceString(STEP1_TITLE_LABEL);
		}else if(currentStep == 2){
			title = title + " - " + frame.getNolResourceString(STEP2_TITLE_LABEL);
		}
		
		if(DEBUG.debugFlag){
			System.out.println(title);
		}
		setTitle(title);
	}

   	public String getLabelName(){
		return labelName.getText();
	}				

   	public String getLabelComment(){
		return labelDescript.getText();
	}				

/*	public void transformerMaskChanged(TransformerEvent e){}
	public void transformerVariableAdded(TransformerEvent e){}
	public void transformerVariableRemoved(TransformerEvent e){}
	public void transfomerTransformListChanged(TransformerEvent e){}
	public void transformerDataChanged(TransformerEvent e){	}
	public void transfomerLabelCategoryAdded(TransformerEvent e) {
		labelChanged();
	}
	public void transfomerLabelCategoryRemoved(TransformerEvent e){	
		labelChanged();
	}
	public void transfomerDataPointsLabeled(TransformerEvent e){	}
	public void transformerTransformerChanged(TransformerEvent e){	}

	private void labelChanged(){
		OfflineTransformer tfr = project.getTransformer(0);
		Vector labels = tfr.getLabelNames();
		getLabelListModel().removeAllElements();
		for(int i=0;i<labels.size();i++){
			getLabelListModel().addElement(labels.elementAt(i));
		}
		labelList.repaint(0l);
		labelList.validate();
	}

*/	
	public Color getLabelColor(){
		return labelColor;
	}

	private void setSelectedColor(Color c){
		labelColor = c;
		colorBlock.setShowColor(labelColor);
		colorBlock.repaint(0l);
		colorBlock.validate();
	}

 	class ControlAction extends AbstractAction implements DocumentListener{
		ControlAction() { super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
			String command = e.getActionCommand();
			if(command.equals("More...")){
				NolColorChooser colorChooser = new NolColorChooser((JFrame)frame, "Color Chooser");
				colorChooser.setBounds(200,200,300,300);
				colorChooser.setVisible(true);
				Color color = colorChooser.getSelectedColor();
				if(colorChooser.getResult()){
					colorChooser.dispose();		
				}else{
					colorChooser.dispose();	
					return;
				}
				setSelectedColor(color);
			}
		}	 
		@Override
		public void changedUpdate(DocumentEvent e){
			changeLabelName();
		}
		@Override
		public void insertUpdate(DocumentEvent e){
			changeLabelName();
		}
		@Override
		public void removeUpdate(DocumentEvent e){
			changeLabelName();
		}
		private void changeLabelName(){
			String n = labelName.getText();
			if(n == null || "".equals(n)){
				nextButton.setEnabled(false);
				finishButton.setEnabled(false);
			}else{
				nextButton.setEnabled(true);
				finishButton.setEnabled(true);
			}
		}
	}

	class ColorComponent extends JPanel implements MouseListener {
		private Color color;

		public ColorComponent(Color color) {
			super();
			this.color = color;
			setBackground(color);
			setForeground(color);
			setBorder(BorderFactory.createLoweredBevelBorder());
			this.addMouseListener(this);
		}

		@Override
		public boolean isOpaque(){return true;}
		@Override
		public void mousePressed(MouseEvent m) {}
		@Override
		public void mouseEntered(MouseEvent m) {}
		@Override
		public void mouseExited(MouseEvent m) {}
		@Override
		public void mouseReleased(MouseEvent m) {}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {
			if(color != null)
				setSelectedColor(color); 
		}
	}
	
	public boolean verifyLabelColor() {
		return labelColor != null;
	}
	
	public boolean verifyNextFinishButton() {
		return nextButton.isEnabled() && finishButton.isEnabled();
	}
}
