package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

import com.gensym.nols.main.*;
import com.gensym.nols.data.*;
import com.gensym.nols.dlg.*;

public class NolSpreadsheet  extends NolInternalFrame {
	private DataSeries dataSeries;
	private TableView view;
	private NolTableDataModel dataModel;
	private Action actionListener;
	protected JPopupMenu popUp;
	protected JMenuItem popUpItem;

	public NolSpreadsheet (DataSeries ds){
		super(ds.getDataSource());
		dataSeries = ds;
		String title = "Spreadsheet - "+ds.getDataSource().getName()+"."+ds.getName();
		setTitle(title);
		dataModel = new NolTableDataModel(dataSeries);
		dataModel.setSigDigits(5);
		view = new TableView(this,dataModel);
		this.setContentPane(view);
		actionListener = new ControlAction();

		popUp = new JPopupMenu();
		String propertyAction = "Table Properties...";
		popUpItem = new JMenuItem(propertyAction);
		popUpItem.setActionCommand(propertyAction);
		popUpItem.addActionListener(actionListener);
		popUp.add(popUpItem);
		this.getContentPane().add(popUp);
		this.addMouseListener(this);
	}

	public void refreshTitle(){
		String title = "Spreadsheet - "+dataSeries.getDataSource().getName()+"."+dataSeries.getName();
		setTitle(title);
	}

	public NolTableDataModel getDataModel(){
		return dataModel;
	}

	public DataSeries getDataSeries(){
		return dataSeries;
	}

	private void setProperty(Vector contents){

		String content = contents.elementAt(0).toString();
		try{
			int sig = (Integer.valueOf(content)).intValue(); 
			if(sig>0 && sig<22){
				dataModel.setSigDigits(sig);
	 			FontMetrics fm = view.getFontMetrics(view.getFont());
				String s = "";
				for(int i=0;i<sig;i++) {
					s=s+"8";
				}
				s = s+"E-888EEEE";
				int width = fm.stringWidth(s);
				view.setWidth(width);
				repaint(0l);
				validate();
//				refreshDisplay();
			}
		}catch(NumberFormatException evt){
			return;
//			System.err.println("Non-Fatal exception: " + evt.getMessage());
//			evt.printStackTrace();
		}

	}

/*	private void refreshDisplay(){
		Rectangle rv = this.getBounds();
		this.setBounds(rv.x,rv.y,rv.width+20,rv.height);
		this.paintImmediately(rv.x,rv.y,rv.width+20,rv.height);
		this.validate();
		this.setBounds(rv.x,rv.y,rv.width,rv.height);
		this.validate();
	}

*/	/**
	  * removeListeners()
	  * Remove listeners from raw data and/or preprocessors  
	  */
	public void removeListeners(){	
		DataSource source = dataSeries.getDataSource();
		source.removeListener(dataModel);
	}
					
/** Mouse clicked event ownership is checked by the component and handled */
	@Override
	public void mouseClicked(MouseEvent m) {
//		System.out.println("spread sheet  click in ");
		int c = m.getClickCount();
		int mod = m.getModifiers();
		if(c==1){
			if(mod==4){
				tableRightClicked(m);
			}
		}
	}

/** Mouse right click event handler */
	public void tableRightClicked(MouseEvent m) {
		popUp.show((Component)m.getSource(), m.getX(), m.getY());
		popUp.pack();
		popUp.setVisible(true);
	}

	
/** Clear the links in this spreadsheet for garbage collection.*/
	public void clearAll(){
		view = null;
		dataModel.clearAll();
		dataModel= null;
		actionListener = null;
	}

/** The inner control listener class.*/
    class ControlAction extends AbstractAction {

		ControlAction() {super("controlAction");}

        @Override
		public void actionPerformed(ActionEvent e) {
				
			String command = e.getActionCommand();
			if(command.equals("Table Properties...")){
				JFrame frame = getFrame();
				Vector contents = new Vector(1);
				contents.addElement("Significant Digits");
				NolTableDialog dg = new NolTableDialog
					(frame, "Define Property", 
					NolSpreadsheet.this.getTitle(), contents);
				dg.pack();
				dg.setLocation(new Point(200,200));
				dg.setVisible(true);
				if(dg.getResult()){
					Vector results = dg.getInputs();
					setProperty(results);
					dg.dispose();
				}else{
					dg.dispose();		
					return;
				}						
			}
		}
    }
}

