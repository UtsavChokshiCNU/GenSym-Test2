package com.gensym.nols.dlg;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.util.*;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.table.*;
import com.gensym.math.matrix.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;
import com.gensym.DEBUG;

public class NolReplaceDialog extends JDialog implements ActionListener {
	private NolMainFrame frame;
	private DataSource dataSource;
	private JComboBox dataSourceNames;
	private JComboBox dataChoice;
	private JTextField findText;
	private JTextField replaceText;
	private JPopupMenu findPopUp;
	private JPopupMenu replacePopUp;
	private JPopupMenu variablePopUp;
	private JButton findOption;
	private JButton replaceOption;
	private JButton findButton;
	private int findFlag;
	private int replaceFlag;

	private boolean noFire;
	private boolean noPopup;
	private Vector names;

	private ResultSummeryModel resultSummeryModel;
	private JTable resultView;

	private static final String DATASOURCE = "NolReplaceDialog_DataSource";
    private static final String DATASERIES = "NolReplaceDialog_DataSeries";
    private static final String FINDWHAT = "NolReplaceDialog_FindWhat";
    private static final String REPLACEWITH = "NolReplaceDialog_ReplaceWith";
    private static final String VALUE = "NolReplaceDialog_Value";
    private static final String PREVIOUSVALIDVALUE = "NolReplaceDialog_PreviousValidValue";
    private static final String GOTOSPREADSHEET = "NolReplaceDialog_GoToSpreadSheet";
    private static final String GOTOLINECHART = "NolReplaceDialog_GoToLineChart";
    private static final String REPLACEFIRSTONE = "NolReplaceDialog_ReplaceFirstOne";
    private static final String REPLACEALL = "NolReplaceDialog_ReplaceAll";
    private static final String ALLDATASERIES = "NolReplaceDialog_AllDataSeries";
    private static final String VARIABLE = "NolReplaceDialog_Variable";
    private static final String OCCURRENCE = "NolReplaceDialog_Occurence";
    private static final String FIND = "NolReplaceDialog_Find";
    private static final String REPLACECOUNTINFO1 = "NolReplaceDialog_ReplaceCountInfo1";
    private static final String REPLACECOUNTINFO2 = "NolReplaceDialog_ReplaceCountInfo2";

	public NolReplaceDialog(JFrame dw, String title) {
		super(dw, title, true);
        frame = (NolMainFrame)dw;	 
		names = new Vector();
		noFire = false;
		noPopup = false;
		initLayout();
		initPopupMenu();
		initDataDisplay();
        setBounds(150,150,500, 300);
	}

	private void initLayout(){

		JPanel caseNamePane = new JPanel(new GridLayout());
		caseNamePane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(DATASOURCE)+":", TitledBorder.LEFT , TitledBorder.TOP));
//			"Data Source:", TitledBorder.LEFT , TitledBorder.TOP));
		dataSourceNames = new JComboBox();
		dataSourceNames.addActionListener(this);
		caseNamePane.add(dataSourceNames);


		JPanel dataSeriesPane = new JPanel(new GridLayout());
		dataSeriesPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(DATASERIES)+":", TitledBorder.LEFT , TitledBorder.TOP));
//			"Data Series:", TitledBorder.LEFT , TitledBorder.TOP));
		dataChoice = new JComboBox();
		dataChoice.addActionListener(this);
		dataSeriesPane.add(dataChoice);

		JPanel choicePane = new JPanel(new GridLayout(1,2,5,5));
		choicePane.add(caseNamePane);
		choicePane.add(dataSeriesPane);

		URL url = this.getClass().getResource("searchOpt.gif");
		ImageIcon searchOpt = new ImageIcon(url);
			
		JPanel searchPane = new JPanel(new BorderLayout());
		searchPane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(FINDWHAT)+":", TitledBorder.LEFT , TitledBorder.TOP));
//			"Find what:", TitledBorder.LEFT , TitledBorder.TOP));
		findText = new JTextField("NaN");
		findText.addActionListener(this);
		findOption = new JButton(searchOpt){
			@Override
			public float getAlignmentY() { return 0.5f; }
			@Override
			public Dimension getPreferredSize() { return new Dimension(15,20); }
		};

		findOption.setActionCommand("findOption");
		findOption.addActionListener(this);
		searchPane.add("Center",findText);
		searchPane.add("East",findOption);

		JPanel replacePane = new JPanel(new BorderLayout());
		replacePane.setBorder(new TitledBorder(new EmptyBorder(1, 1, 1, 1),               
			frame.getNolResourceString(REPLACEWITH)+":", TitledBorder.LEFT , TitledBorder.TOP));
//			"Replace with:", TitledBorder.LEFT , TitledBorder.TOP));
		replaceText = new JTextField();
		replaceText.addActionListener(this);
		replaceOption = new JButton(searchOpt){
			@Override
			public float getAlignmentY() { return 0.5f; }
			@Override
			public Dimension getPreferredSize() { return new Dimension(15,20); }
		};
		replaceOption.setActionCommand("replaceOption");
		replaceOption.addActionListener(this);
		replacePane.add("Center",replaceText);
		replacePane.add("East",replaceOption);



		JPanel topPane = new JPanel(new GridLayout(3,1,5,5));
		topPane.add(choicePane);
		topPane.add(searchPane);
		topPane.add(replacePane);
				
		resultSummeryModel = new ResultSummeryModel();
		resultView = new JTable(resultSummeryModel);
		resultView.setDefaultRenderer(String.class, 
			new ResultTableCellRenderer());
		resultView.setSelectionMode(0);
		resultView.setCellSelectionEnabled(true);
		JScrollPane listScrollPane = new JScrollPane(resultView);
		listScrollPane.setBackground(Color.white);

		JPanel tablePane = new JPanel(new GridLayout());
		tablePane.setBorder(new EmptyBorder(10, 10, 10, 10));
		tablePane.add(listScrollPane);

		JPanel centerPane = new JPanel(new BorderLayout());
		centerPane.add("North",topPane);
 		centerPane.add("Center",tablePane);


		getContentPane().setLayout(new BorderLayout());    
		getContentPane().add("Center",centerPane);    
		getContentPane().add("East", getControlPanel());



		findPopUp = new JPopupMenu();
		JCheckBoxMenuItem popUpItem = new JCheckBoxMenuItem("NaN");
		popUpItem.setActionCommand("NaN");
		popUpItem.setSelected(true);
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);

/*		popUpItem = new JCheckBoxMenuItem("=");
		popUpItem.setActionCommand("=");
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);

		popUpItem = new JCheckBoxMenuItem("<");
		popUpItem.setActionCommand("<");
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);

		popUpItem = new JCheckBoxMenuItem("<=");
		popUpItem.setActionCommand("<=");
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);

		popUpItem = new JCheckBoxMenuItem(">");
		popUpItem.setActionCommand(">");
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);

		popUpItem = new JCheckBoxMenuItem(">=");
		popUpItem.setActionCommand(">=");
		popUpItem.addActionListener(this);
		findPopUp.add(popUpItem);
*/
//		popUpItem = new JCheckBoxMenuItem("String");
//		popUpItem.setActionCommand("Find string");
//		popUpItem.addActionListener(this);
//		findPopUp.add(popUpItem);

		replacePopUp = new JPopupMenu();
		popUpItem = new JCheckBoxMenuItem(frame.getNolResourceString(VALUE));
		popUpItem.setActionCommand("Value");
		popUpItem.setSelected(true);
		popUpItem.addActionListener(this);
		replacePopUp.add(popUpItem);

		popUpItem = new JCheckBoxMenuItem(frame.getNolResourceString(PREVIOUSVALIDVALUE));
		popUpItem.setActionCommand("Previous valid value");
		popUpItem.addActionListener(this);
		replacePopUp.add(popUpItem);

//		popUpItem = new JCheckBoxMenuItem("Interpolate value");
//		popUpItem.setActionCommand("Interpolate value");
//		popUpItem.addActionListener(this);
//		replacePopUp.add(popUpItem);

//		popUpItem = new JCheckBoxMenuItem("String");
//		popUpItem.setActionCommand("Replace string");
//		popUpItem.addActionListener(this);
//		replacePopUp.add(popUpItem);

		variablePopUp = new JPopupMenu();
		JMenuItem popUpAction = new JMenuItem(frame.getNolResourceString(GOTOSPREADSHEET));
		popUpAction.setActionCommand("Go to spreadsheet");
		popUpAction.addActionListener(this);
		variablePopUp.add(popUpAction);

		popUpAction = new JMenuItem(frame.getNolResourceString(GOTOLINECHART));
		popUpAction.setActionCommand("Go to line chart");
		popUpAction.addActionListener(this);
		variablePopUp.add(popUpAction);
	}

	private JPanel getControlPanel(){
		JPanel control = new JPanel();
		control.setBackground(getContentPane().getBackground());
		control.setLayout(new BoxLayout(control, BoxLayout.Y_AXIS));
		control.setBorder(new EmptyBorder(10, 10, 10, 10));

		JPanel pane0 = new JPanel(new GridLayout(3,1,10,10));
		findButton = new JButton(frame.getNolResourceString(FIND));
		findButton.setActionCommand("Find");
		findButton.addActionListener(this);			
		JButton replaceButton = new JButton(frame.getNolResourceString(REPLACEFIRSTONE));
		replaceButton.setActionCommand("Replace First One");
		replaceButton.addActionListener(this);	
		JButton replaceAllButton = new JButton(frame.getNolResourceString(REPLACEALL));
		replaceAllButton.setActionCommand("Replace All");
		replaceAllButton.addActionListener(this);	
//		JButton cancelButton = new JButton("Cancel");
 //		cancelButton.addActionListener(this);	
  		pane0.add(findButton);
  		pane0.add(replaceButton);
 		pane0.add(replaceAllButton);
//		pane0.add(cancelButton);
		control.add(Box.createRigidArea(NolMainFrame.vpad15));
		control.add(pane0);
		control.add(Box.createRigidArea(NolMainFrame.vpad300));
		control.add(Box.createVerticalGlue());
		return control;
	}

	private void initPopupMenu(){
	}


	public void resetData(){
		initDataDisplay();
	}

	private void initDataDisplay(){
		noFire = true;
		Project project = frame.getProject();
		RawDataSource rawdata = project.getRawDataSource();
		int rc = rawdata.getNumberOfDataSeries();
		if(rc<=0){
			noFire = false;
			return;
		}
		int n = project.getNumberOfPreprocessors();
		dataSourceNames.removeAllItems();
		dataSourceNames.addItem(rawdata.getName());
		for(int i=0;i<n;i++){
			Preprocessor prep = project.getPreprocessorByIndex(i);
			String name = prep.getName();
			dataSourceNames.addItem(name);
		}
		dataSource = (DataSource)project.getRawDataSource();
		n = dataSource.getNumberOfDataSeries();
		dataChoice.removeAllItems();
		dataChoice.addItem(frame.getNolResourceString(ALLDATASERIES));
//		dataChoice.addItem("All DataSeries");
		for(int i=0;i<n;i++){
			String name = dataSource.getDataSeriesName(i); 	
			dataChoice.addItem(name);
		}
		refreshPopupMenu("NaN");
		findText.setText("NaN");
		resultSummeryModel.setResults(new Vector(),new Vector());
		noFire = false;
	}
		
	@Override
	public void actionPerformed(ActionEvent e) {
		if(noFire){
			return;
		}
		String command = e.getActionCommand ();
		Object source = e.getSource ();
		if(command.equals("Find")){
			find(0);
		}else if(command.equals("Replace First One")){
			find(1);
		}else if(command.equals("Replace All")){
			find(2);
		}else if(command.equals("findOption")){
			findPopUp.show(findOption, 5, 5);
			findPopUp.pack();
			findPopUp.setVisible(true);
		}else if(command.equals("replaceOption")){
			replacePopUp.show(replaceOption, 5, 5);
			replacePopUp.pack();
			replacePopUp.setVisible(true);
		}else if(command.equals("Find string")){
			refreshPopupMenu("Find string");
		}else if(command.equals("NaN")){
			refreshPopupMenu("NaN");
		}else if(command.equals("=")){
			refreshPopupMenu("=");
		}else if(command.equals("<")){
			refreshPopupMenu("<");
		}else if(command.equals("<=")){
			refreshPopupMenu("<=");
		}else if(command.equals(">")){
			refreshPopupMenu(">");
		}else if(command.equals(">=")){
			refreshPopupMenu(">=");
		}else if(command.equals("Replace string")){
			refreshPopupMenu("Replace string");
		}else if(command.equals("Value")){
			refreshPopupMenu("Value");
		}else if(command.equals("Previous valid value")){
			refreshPopupMenu("Previous valid value");
//		}else if(command.equals("Interpolate value")){
//			refreshPopupMenu("Interpolate value");
		}else if(command.equals("Go to spreadsheet") || command.equals("Go to line chart")){
			noPopup = true;
		}else if(command.equals("Cancel")){
			setVisible(false);
		}else if(source.equals(dataSourceNames)){
			noFire = true;
			String sourceString = (String)dataSourceNames.getSelectedItem();
			Project project = frame.getProject();
			RawDataSource rawdata = project.getRawDataSource();
			dataChoice.removeAllItems();
			dataChoice.addItem(frame.getNolResourceString(ALLDATASERIES));
//			dataChoice.addItem("All DataSeries");
			if(sourceString.equals(rawdata.getName())){
				for(int i=0;i<rawdata.getNumberOfDataSeries();i++){
					String name = rawdata.getDataSeriesName(i); 	
					dataChoice.addItem(name);
				}
			}else{
				int pi = project.getPreprocessorIndexByName(sourceString);
				if(pi>0){
					Preprocessor prep = project.getPreprocessorByIndex(pi);
					for(int i=0;i<prep.getNumberOfDataSeries();i++){
						String name = prep.getDataSeriesName(i); 	
						dataChoice.addItem(name);
					}
				}
			}
			noFire = false;
		}
	}

	private void find(int flag){
		String findString = findText.getText();
		String replaceString = replaceText.getText();
		double value =0;
		double previousValue = 0;
		if(flag>0){
			if(replaceString.equals("") || replaceString == null){
				return;
			}
			if(replaceFlag == 0){
				try{
					value = new Double(replaceString).doubleValue();
				}catch(NumberFormatException evt){
					replaceText.setText("");
					return;
				}
			}
		}
		int sourceIndex = dataSourceNames.getSelectedIndex();
		int dsIndex = dataChoice.getSelectedIndex();
		names.removeAllElements();
		Vector occurs = new Vector();
		Project project = frame.getProject();
		if(sourceIndex == 0)
			dataSource = (DataSource)project.getRawDataSource();
		else
			dataSource = (DataSource)project.getPreprocessorByIndex(sourceIndex-1);
		boolean foundInFirstRow = false;
		int foundInFirstRowCount = 0;
		boolean firstEncounter = true;
		boolean found = false;
		int totalReplaceCount = 0;
		if(dsIndex == 0){
			int nd = dataSource.getNumberOfDataSeries();
			for(int i=0;i<nd;i++){
				DataSeries ds = dataSource.getDataSeries(i);
				Matrix X = ds.getDataMatrix();
				Vector varObjs = ds.getVarObjects();
				for(int c=0;c<X.getCols();c++){
					int count = 0;
					if(flag == 0){
						for(int r=0;r<X.getRows();r++){
							if(findFlag == 0){
								if(Double.isNaN(X.get(r,c)))
									count++	;
							}else if(findFlag == 1){
								if(Double.compare(X.get(r,c), value) == 0)
									count++	;
							}else if(findFlag == 2){
								if(X.get(r,c) < value)
									count++	;
							}else if(findFlag == 3){
								if(X.get(r,c) <= value)
									count++	;
							}else if(findFlag == 4){
								if(X.get(r,c) > value)
									count++	;
							}else if(findFlag == 5){
								if(X.get(r,c) >= value)
									count++	;
							}
						}
					}else if(replaceFlag == 0){
						for(int r=0;r<X.getRows();r++){
							found = false;
							if(findFlag == 0){
								if(Double.isNaN(X.get(r,c)))
									found = true;
							}else if(findFlag == 1){
								if(Double.compare(X.get(r,c), value) == 0)
									found = true;
							}else if(findFlag == 2){
								if(X.get(r,c) < value)
									found = true;
							}else if(findFlag == 3){
								if(X.get(r,c) <= value)
									found = true;
							}else if(findFlag == 4){
								if(X.get(r,c) > value)
									found = true;
							}else if(findFlag == 5){
								if(X.get(r,c) >= value)
									found = true;
							}
							if(found){						
								count++	;
								if(flag == 1){
									if(firstEncounter){
										X.set(r,c,value);
										count--;	
										totalReplaceCount++;
										firstEncounter = false;
									}
								}else if(flag == 2){
									X.set(r,c,value);
									totalReplaceCount++;
									count--;	
								}
							}
						}
					}else if(replaceFlag == 1){
						previousValue = X.get(0,c);
						for(int r=0;r<X.getRows();r++){
							found = false;
							if(findFlag == 0){
								if(Double.isNaN(X.get(r,c)))
									found = true;
							}else if(findFlag == 1){
								if(Double.compare(X.get(r,c), value) == 0)
									found = true;
							}else if(findFlag == 2){
								if(X.get(r,c) < value)
									found = true;
							}else if(findFlag == 3){
								if(X.get(r,c) <= value)
									found = true;
							}else if(findFlag == 4){
								if(X.get(r,c) > value)
									found = true;
							}else if(findFlag == 5){
								if(X.get(r,c) >= value)
									found = true;
							}
							if(found){						
								count++	;
								if(r==0){
									foundInFirstRow = true;
								}
								if(!foundInFirstRow){
									if(flag == 1){
										if(firstEncounter){
											X.set(r,c,previousValue);
											count--;	
											totalReplaceCount++;
											firstEncounter = false;
										}
									}else if(flag == 2){
										X.set(r,c,previousValue);
										totalReplaceCount++;
										count--;	
									}
								}
							}else{
								previousValue = X.get(r,c);
								if(foundInFirstRow){
									foundInFirstRow = false;
									if(flag == 1){
										if(firstEncounter){
											X.set(0,c,previousValue);
											count--;	
											totalReplaceCount++;
											firstEncounter = false;
										}
									}else{
										for(int rr=0;rr<r;rr++){
											totalReplaceCount++;
											X.set(rr,c,previousValue);
											count--;	
										}
									}
								}
							}
						}

					}
		if(DEBUG.debugFlag){
			System.out.println("count="+count);
			System.out.println("replaceFlag="+replaceFlag);
			System.out.println("flag="+flag);
		}
					if(count>0){
						names.addElement(varObjs.elementAt(c));
						occurs.addElement(String.valueOf(count));
					}
				}
			}
		}else{
			DataSeries ds = dataSource.getDataSeries(dsIndex-1);
			Vector varObjs = ds.getVarObjects();
			Matrix X = ds.getDataMatrix();			
			int row = X.getRows();
			for(int c=0;c<X.getCols();c++){
				int count = 0;
				if(flag == 0){
					for(int r=0;r<row;r++){
						if(findFlag == 0){
							if(Double.isNaN(X.get(r,c)))
								count++;
						}else if(findFlag == 1){
							if(Double.compare(X.get(r,c), value) == 0)
								count++;
						}else if(findFlag == 2){
							if(X.get(r,c) < value)
								count++;
						}else if(findFlag == 3){
							if(X.get(r,c) <= value)
								count++;
						}else if(findFlag == 4){
							if(X.get(r,c) > value)
								count++;
						}else if(findFlag == 5){
							if(X.get(r,c) >= value)
								count++;
						}
					}
				}else if(replaceFlag == 0){						
					for(int r=0;r<row;r++){
						found = false;
						if(findFlag == 0){
							if(Double.isNaN(X.get(r,c)))
								found = true;
						}else if(findFlag == 1){
							if(Double.compare(X.get(r,c), value) == 0)
								found = true;
						}else if(findFlag == 2){
							if(X.get(r,c) < value)
								found = true;
						}else if(findFlag == 3){
							if(X.get(r,c) <= value)
								found = true;
						}else if(findFlag == 4){
							if(X.get(r,c) > value)
								found = true;
						}else if(findFlag == 5){
							if(X.get(r,c) >= value)
								found = true;
						}
						if(found){						
							count++	;
							if(flag == 1){
								if(firstEncounter){
									X.set(r,c,value);
									count--;	
									totalReplaceCount++;
									firstEncounter = false;
								}
							}else if(flag == 2){
								X.set(r,c,value);
								totalReplaceCount++;
								count--;	
							}
						}
					}
				}else if(replaceFlag == 1){
					previousValue = X.get(0,c);
					for(int r=0;r<row;r++){
						found = false;
						if(findFlag == 0){
							if(Double.isNaN(X.get(r,c)))
								found = true;
						}else if(findFlag == 1){
							if(Double.compare(X.get(r,c), value) == 0)
								found = true;
						}else if(findFlag == 2){
							if(X.get(r,c) < value)
								found = true;
						}else if(findFlag == 3){
							if(X.get(r,c) <= value)
								found = true;
						}else if(findFlag == 4){
							if(X.get(r,c) > value)
								found = true;
						}else if(findFlag == 5){
							if(X.get(r,c) >= value)
								found = true;
						}
						if(found){						
							count++	;
							if(r==0){
								foundInFirstRow = true;
							}
							if(!foundInFirstRow){
								if(flag == 1){
									if(firstEncounter){
										X.set(r,c,previousValue);
										totalReplaceCount++;
										count--;	
										firstEncounter = false;
									}
								}else if(flag == 2){
									X.set(r,c,previousValue);
									totalReplaceCount++;
									count--;	
								}
							}
						}else{
							previousValue = X.get(r,c);
							if(foundInFirstRow){
								foundInFirstRow = false;
								if(flag == 1){
									if(firstEncounter){
										X.set(0,c,previousValue);
										totalReplaceCount++;
										count--;	
										firstEncounter = false;
									}
								}else if(flag == 2){
									for(int rr=0;rr<r;rr++){
										X.set(rr,c,previousValue);
										totalReplaceCount++;
										count--;	
									}
								}
							}
						}
					}
				}
				if(count>0){
					names.addElement(varObjs.elementAt(c));
					occurs.addElement(String.valueOf(count));
				}
			}
		}
		if(DEBUG.debugFlag){
			System.out.println("names.size()="+names.size());
			System.out.println("occurs.size()="+occurs.size());
		}

		resultSummeryModel.setResults(names,occurs);
		resultView.setModel(resultSummeryModel);
		resultView.sizeColumnsToFit(-1);
		resultView.validate();
		resultView.repaint(0l);
		if(totalReplaceCount>0 && flag>0){
			frame.showOKDialog(
				frame.getNolResourceString(REPLACECOUNTINFO1)+" "+totalReplaceCount+" "+
				frame.getNolResourceString(REPLACECOUNTINFO2)
				);
		}
	}

	private void refreshPopupMenu(String command){
		noFire = true;
		JCheckBoxMenuItem cme0 = (JCheckBoxMenuItem)replacePopUp.getComponent(0);
		JCheckBoxMenuItem cme1 = (JCheckBoxMenuItem)replacePopUp.getComponent(1);
//		JCheckBoxMenuItem cme2 = (JCheckBoxMenuItem)replacePopUp.getComponentAtIndex(2);
//		JCheckBoxMenuItem cme3 = (JCheckBoxMenuItem)replacePopUp.getComponentAtIndex(3);

		JCheckBoxMenuItem fme0 = (JCheckBoxMenuItem)findPopUp.getComponent(0);
//		JCheckBoxMenuItem fme1 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(1);
//		JCheckBoxMenuItem fme2 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(2);
//		JCheckBoxMenuItem fme3 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(3);
//		JCheckBoxMenuItem fme4 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(4);
//		JCheckBoxMenuItem fme5 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(5);
//		JCheckBoxMenuItem fme4 = (JCheckBoxMenuItem)findPopUp.getComponentAtIndex(4);

		if(command.equals("Value") || command.equals("Previous valid value") || command.equals("Interpolate value")){
			cme0.setSelected(false);
			cme1.setSelected(false);	
//			cme2.setSelected(false);	
//			cme3.setSelected(false);
			if(command.equals("Value")){
				replaceText.setText("");
				cme0.setSelected(true);
				replaceFlag = 0;
			}else if(command.equals("Previous valid value")){
				replaceText.setText("Previous valid value");
 				cme1.setSelected(true);
				replaceFlag = 1;
//			}else if(command.equals("Interpolate value")){
//				replaceText.setText("Interpolate value");
// 				cme2.setSelected(true);
//				replaceFlag = 2;
			}
//			if(fme4.isSelected()){
//				fme4.setSelected(false);
//				fme0.setSelected(true);
//				findText.setText("NaN");
//				findFlag = 0;
//			}
			noFire = false;
			return;
		}else if(command.equals("Replace string")){
			replaceFlag = 3;
			cme0.setSelected(false);
			cme1.setSelected(false);
//			cme2.setSelected(false);
//			cme3.setSelected(true);
			fme0.setSelected(false);
//			fme1.setSelected(false);
//			fme2.setSelected(false);
//			fme3.setSelected(false);
//			fme4.setSelected(true);
			findText.setText("");
			findFlag = 4;
			noFire = false;
			return;
		}
		fme0.setSelected(false);
//		fme1.setSelected(false);
//		fme2.setSelected(false);
//		fme3.setSelected(false);
//		fme4.setSelected(false);
//		fme5.setSelected(false);
//		fme4.setSelected(false);
		if(fme0.getActionCommand().equals(command)){ 
			findText.setText("NaN");
			fme0.setSelected(true);
			findFlag = 0;
		}
/*			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
		}else if(fme1.getActionCommand().equals(command)){ 
			findText.setText("");
			fme1.setSelected(true);
			findFlag = 1;
			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
		}else if(fme2.getActionCommand().equals(command)){ 
			findText.setText("");
			fme2.setSelected(true);
			findFlag = 2;
			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
		}else if(fme3.getActionCommand().equals(command)){ 
			findText.setText("");
			fme3.setSelected(true);
			findFlag = 3;
			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
		}else if(fme4.getActionCommand().equals(command)){ 
			findText.setText("");
			fme4.setSelected(true);
			findFlag = 4;
			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
		}else if(fme5.getActionCommand().equals(command)){ 
			findText.setText("");
			fme5.setSelected(true);
			findFlag = 5;
			if(replaceFlag == 3){
				replaceFlag = 0;
				replaceText.setText("");
 				cme0.setSelected(true);
				cme1.setSelected(false);
				cme2.setSelected(false);
//				cme3.setSelected(false);
			}
 //		}else if(fme4.getActionCommand().equals(command)){ 
//			findText.setText("");
//			fme4.setSelected(true);
//			findFlag = 4;
//			if(replaceFlag != 3){
//				replaceFlag = 3;
//				replaceText.setText("");
 //				cme0.setSelected(false);
//				cme1.setSelected(false);
//				cme2.setSelected(false);
//				cme3.setSelected(true);
//			}
		}
		*/

		noFire = false;
	}

	@Override
	public void setVisible(boolean s){
		super.setVisible(s);
		if(s)
			findButton.requestFocus();
	}

	class ResultSummeryModel extends AbstractTableModel{
		private int row,col;
		private Vector names;
		private Vector occurs;
		private String[] colHd = {frame.getNolResourceString(VARIABLE),
			frame.getNolResourceString(OCCURRENCE)};
//		private String[] colHd = {"Variable","Occurrence"};
		public ResultSummeryModel(){
			row = 0;
			col = 2;
			names = null;
			occurs = new Vector();
		}
		public void setResults(Vector names, Vector occurs){
			this.names = names;
			this.occurs = occurs;
			row = names.size();
			fireTableDataChanged();
		}

		@Override
		public int getColumnCount() { return col; }
		@Override
		public int getRowCount() { return row;}
		@Override
		public Object getValueAt(int r, int c){
			if(c == 0){
				Variable varObj = (Variable)names.elementAt(r);
				String s = varObj.getDataSource().getName()+"."+
					varObj.getDataSeries().getName()+"."+varObj.getName();
				return s;
			}else if(c == 1){
				return occurs.elementAt(r);
			}
			return null;
		}
		@Override
		public String getColumnName(int c) {
			return colHd[c];
		}
		@Override
		public Class getColumnClass(int c) {
			return getValueAt(0, c).getClass();
		}
		@Override
		public boolean isCellEditable(int r, int c) {
			return false;
		}
		@Override
		public void setValueAt(Object aValue, int r, int c) {
		}
	}

		
	class ResultTableCellRenderer extends JComponent implements TableCellRenderer, java.io.Serializable{
		@Override
		public Component getTableCellRendererComponent(JTable table,
                                               Object value,
                                               boolean isSelected,
                                               boolean hasFocus,
                                               int row,
                                               int column){
			if(value instanceof String){
				if(isSelected && hasFocus){
/*					if(!noPopup){
//						System.out.println("value="+value);
						variablePopUp.show(resultView, 5, 5);
						variablePopUp.pack();
						variablePopUp.setVisible(true);
						noPopup = true;
					}else{
						noPopup = false;
					}*/
				}
				return new JLabel((String)value);
			}
			return null;
		}
	}

}

