package com.gensym.nols.wksp;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/** TableRowHeader */
public class TableRowHeader extends JComponent implements MouseListener,
 KeyListener, TableModelListener{

 	private JComponent holder;			// container
	private Dimension displaySize;
	private boolean isEditable;
	private TableDataModel dataModel;
	private int defaultCellWidth;
	private int defaultCellHeight;

/** Constructor for Table Component - arguments are 
	row position in container, col position in container,
	label string and the container */
	public TableRowHeader(String n, 
		JComponent table, TableDataModel dataModel) {
		super();
		this.setName(n);
		this.holder = table;
		defaultCellWidth = 75;
		defaultCellHeight = 20;
		isEditable = false;
		this.dataModel = dataModel;
		int rowNumber = dataModel.getNumberOfRows();
		if(rowNumber <20){
			rowNumber = 20;
		}
		displaySize = new Dimension(defaultCellWidth,defaultCellHeight*rowNumber);
		this.addMouseListener(this);
//		this.addKeyListener(this);
	}

	@Override
	public boolean isOpaque(){
		return true;
	}

	public boolean isEditable(){
		return isEditable;
	}
	public void setIsEditable(boolean flag){
		isEditable = flag;
	}

	@Override
	public void setPreferredSize(Dimension size){
		super.setPreferredSize(size);
		this.displaySize = size;
	}

	@Override
	public void setMinimumSize(Dimension size){
		super.setMinimumSize(size);
		this.displaySize = size;
	}
	@Override
	public Dimension getPreferredSize(){
		return displaySize;
	}
	@Override
	public Dimension getMinimumSize(){
		return displaySize;
	}
/** Change the holder to new holder - Table Area */
	public void setHolder(JComponent table) {
		this.holder = table;
	}

/**  Get the holder */
	public JComponent getHolder() {
		return this.holder;
	}

	@Override
	protected void paintComponent(Graphics g) {
		JViewport view = ((JScrollPane)holder).getViewport();	
		Rectangle reg = view.getViewRect();
		int r0 = reg.y/defaultCellHeight;
		int r = reg.height/defaultCellHeight;
		g.clearRect(reg.x,reg.y,reg.width,reg.height);
		for(int rr=r0;rr<r+r0+2;rr++){
			g.setColor(Color.lightGray);
			g.fillRect(0, defaultCellHeight*rr, reg.width, defaultCellHeight*(rr+1));
			g.setColor(Color.gray);
			g.drawLine(0, defaultCellHeight*rr, reg.width, defaultCellHeight*rr);
			g.setColor(this.getForeground());
			g.drawString(dataModel.getRowName(rr), 2 ,defaultCellHeight*rr+15 );
		}
	}

	private void changeNameWith(String s){
		if(s.equals("BACK")){
			String newName = new String(getName());
			newName = newName.substring(0,newName.length()-1);
			setName(newName);
		}else{
			String newName = getName()+s;
			setName(newName);
		}
		repaint();
		validate();
	}


/** Mouse pressed event ownership is checked by the component and handled */
 	@Override
	public void mousePressed(MouseEvent m) {
//		System.out.println("mousePressed");	
	}

/** Mouse entered event ownership is checked by the component and handled */
	@Override
	public void mouseEntered(MouseEvent m) {
	}

/** Mouse exited event ownership is checked by the component and handled */
	@Override
	public void mouseExited(MouseEvent m) {
	}

/** Mouse released event ownership is checked by the component and handled */
	@Override
	public void mouseReleased(MouseEvent m) {
//		System.out.println("mouseReleased");	
	}

/** Mouse dragged event ownership is checked by the component and handled */
	public void mouseDragged(MouseEvent m) {
	}

/** Mouse moved event ownership is checked by the component and handled */
	public void mouseMoved(MouseEvent m) {
	}

/** Mouse clicked event ownership is checked by the component and handled */
	@Override
	public void mouseClicked(MouseEvent m) {
		int c = m.getClickCount();
		int mod = m.getModifiers();
			switch (c) {
				case 1 : 
					switch (mod) {
						case 18 : tableCtrlClicked(m);
							break;
						case 17 : tableShiftClicked(m);
							break;
						case 24 : tableAltClicked(m);
							break;
						case 4 :  tableRightClicked(m);
							break;
						default : tableMouseClicked(m);
							break;
					}
					break;
				case 2: tableDoubleClicked(m);
					break;
				default : //tableMouseClicked(m);
					break;
		}
	}

/** Mouse alt click event handler */
	public void tableAltClicked(MouseEvent m) {
	}

/** Mouse shift click event handler */
	public void tableShiftClicked(MouseEvent m) {
//System.out.println("shift click");
	}

/** Mouse ctrl click event handler */
	public void tableCtrlClicked(MouseEvent m) {
//System.out.println("ctrl click");
	}

/** Mouse right click event handler */
	public void tableRightClicked(MouseEvent m) {
//System.out.println("right click");
	}

/** Mouse pressed  event handler */
	public void tableMousePressed(MouseEvent m) {
//		System.out.println("tableMousePressed");	
	}

/** Mouse released event handler */
	public void tableMouseReleased(MouseEvent m) {	
//		System.out.println("tableMouseReleased");	
	}

/** Mouse entered event handler */
	public void tableMouseEntered(MouseEvent m) {} 

/** Mouse exited event handler */
	public void tableMouseExited(MouseEvent m) {} 

/** Mouse dragged event handler */
	public void tableMouseDragged(MouseEvent m) {}

/** Mouse moved event handler */
	public void tableMouseMoved(MouseEvent m) {} 
	
/** Mouse clicked event handler */
	public void tableMouseClicked(MouseEvent m) {
//		System.out.println("click in");
		int r = m.getY()/defaultCellHeight;
		dataModel.selectRow(r);
	}

/** Mouse double clicked event handler */
	public void tableDoubleClicked(MouseEvent m) {
//		System.out.println("Double click");
	}

/** Key type event handler */
	@Override
	public void keyTyped(KeyEvent e){
		if(isEditable){
		
			if(String.valueOf(e.getKeyChar()).equals("1")){
				changeNameWith("1");
			}else if(String.valueOf(e.getKeyChar()).equals("2")){
				changeNameWith("2");
			}else if(String.valueOf(e.getKeyChar()).equals("3")){
				changeNameWith("3");
			}else if(String.valueOf(e.getKeyChar()).equals("4")){
				changeNameWith("4");
			}else if(String.valueOf(e.getKeyChar()).equals("5")){
				changeNameWith("5");
			}else if(String.valueOf(e.getKeyChar()).equals("6")){
				changeNameWith("6");
			}else if(String.valueOf(e.getKeyChar()).equals("7")){
				changeNameWith("7");
			}else if(String.valueOf(e.getKeyChar()).equals("8")){
				changeNameWith("8");
			}else if(String.valueOf(e.getKeyChar()).equals("9")){
				changeNameWith("9");
			}else if(String.valueOf(e.getKeyChar()).equals("0")){
				changeNameWith("0");
			}else if(String.valueOf(e.getKeyChar()).equals(".")){
				changeNameWith(".");
			}
		}
	}
/** Key pressed event handler */
	@Override
	public void keyPressed(KeyEvent e){

		if(isEditable){
			if(e.getKeyCode() == KeyEvent.VK_BACK_SPACE ||
			   e.getKeyCode() == KeyEvent.VK_DELETE){
					changeNameWith("BACK");
			}
		}
	}
/** Key released event handler */
	@Override
	public void keyReleased(KeyEvent e){}

	@Override
	public void tableDataChanged(TableDataEvent e) {
	
		String id = e.getID();
		if(id.equals("dataChanged")){
			repaint();
		}
	}
}
