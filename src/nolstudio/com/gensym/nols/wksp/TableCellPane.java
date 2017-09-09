package com.gensym.nols.wksp;
import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;

/** TableCellPane */
public class TableCellPane extends JComponent implements MouseListener,
 KeyListener, TableModelListener {

 	private JComponent holder;			// container
	private Dimension displaySize;
	private boolean isEditable;
	private int defaultCellWidth;
	private int defaultCellHeight;
	private int[] cellWidth;
	private TableDataModel dataModel;
	private int lastRow, lastColumn;
	private Image cellImage;
	private int areaTop;
	private int areaRight;
	private volatile int areaWidth;
	private volatile int areaHeight;
	private Vector dataStatusChangeCoords;
	private boolean isDataStatusChanging;
	private boolean isMousePressed;

/** Constructor for Table Component - arguments are 
	row position in container, col position in container,
	label string and the container */
	public TableCellPane(String n, JComponent table, TableDataModel dataModel) {
		super();
		this.setName(n);
		this.defaultCellWidth = 93;
		this.defaultCellHeight = 20;
		this.holder = table;
		this.dataModel = dataModel;
		int columnNumber = dataModel.getNumberOfColumns();
		int rowNumber = dataModel.getNumberOfRows();
		if(columnNumber <5){
			columnNumber = 5;
		}
		if(rowNumber <20) {
			rowNumber = 20;
		}
		this.cellWidth = new int[columnNumber];
		for(int c=0;c<columnNumber;c++){
			cellWidth[c] += defaultCellWidth;
		}
		isEditable = false;
		isDataStatusChanging = false;
		isMousePressed = false;
		displaySize = new Dimension(defaultCellWidth*columnNumber,defaultCellHeight*rowNumber);
		areaTop=0;
		areaRight=0;
		areaWidth=0;
		areaHeight=0;
		this.addMouseListener(this);
		dataStatusChangeCoords = new Vector();
//		this.addKeyListener(this);
	}

	public TableCellPane() {
		super();
		this.setName("");
		this.holder = null;
		isEditable = false;
		isDataStatusChanging = false;
		isMousePressed = false;
		displaySize = new Dimension(defaultCellWidth*5,
			defaultCellHeight*20);
		this.addMouseListener(this);
//		this.addKeyListener(this);
		areaTop=0;
		areaRight=0;
		areaWidth=0;
		areaHeight=0;
		dataStatusChangeCoords = new Vector();
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
		int c0 = reg.x/defaultCellWidth;
		int r = reg.height/defaultCellHeight;
		int c = reg.width/defaultCellWidth;
		g.clearRect(reg.x,reg.y,reg.width,reg.height);
		if(cellImage == null){
//System.out.println("Normal painting? 0");
			cellImage = createImage((c+2)*defaultCellWidth,(r+2)*defaultCellHeight);
			Graphics gg = cellImage.getGraphics();
			paintImage(gg,r+2,c+2,r0,c0);
			gg.dispose();
			gg = null;
		}else{
			if(isDataStatusChanging){
	// 		System.out.println("enter labeling paint");
				Graphics gg = cellImage.getGraphics();
				paintImage(gg,r+2,c+2,r0,c0);
				gg.dispose();
				gg = null;
				isDataStatusChanging = false;
				g.drawImage(cellImage, defaultCellWidth*c0, defaultCellHeight*(r0), this);
//System.out.println("Normal painting? 1");
				return;
			}
			
			if(r+2 != areaHeight || c+2 != areaWidth){
				cellImage.flush();
				cellImage = null;
				cellImage = createImage((c+2)*defaultCellWidth,(r+2)*defaultCellHeight);
//System.out.println("Normal painting? 3");
			}
//System.out.println("Normal painting? 2");
			Graphics gg = cellImage.getGraphics();
			paintImage(gg,r+2,c+2,r0,c0);
			gg.dispose();
			gg = null;
		}
		g.drawImage(cellImage, defaultCellWidth*c0, defaultCellHeight*(r0), this);
	}
		
	private synchronized void paintImage(Graphics g,int r,int c,int r0,int c0){

		if(isDataStatusChanging){
			for(int cn=0;cn< dataStatusChangeCoords.size();cn++){
				int[] dataCoords = (int[])dataStatusChangeCoords.elementAt(cn);
				if(dataCoords.length == 0){
					for(int rr=0;rr<r;rr++){
						for(int cc=0;cc<c;cc++){
							g.setColor(dataModel.getBackgroundColor(rr+r0,cc+c0));
							g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
							g.setColor(Color.gray);
							g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
							g.setColor(this.getForeground());
							g.drawString(dataModel.getValueAt(rr+r0,cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*rr+15 );
						}
					}
				}else if(dataCoords.length == 2){
					g.drawImage(cellImage,0,0, this);
					if(dataCoords[0] == -1){
						for(int cc=0;cc<c;cc++){
							g.setColor(dataModel.getBackgroundColor(dataCoords[1],cc+c0));
							g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(dataCoords[1]-r0), defaultCellWidth, defaultCellHeight);
							g.setColor(Color.gray);
							g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(dataCoords[1]-r0), defaultCellWidth, defaultCellHeight);
							g.setColor(this.getForeground());
							g.drawString(dataModel.getValueAt(dataCoords[1],cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*(dataCoords[1]-r0)+15 );
						}
					}else if(dataCoords[1] == -1){
						for(int rr=0;rr<r;rr++){
							g.setColor(dataModel.getBackgroundColor(rr+r0,dataCoords[0]));
							g.fillRect(defaultCellWidth*(dataCoords[0]-c0), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
							g.setColor(Color.gray);
							g.drawRect(defaultCellWidth*(dataCoords[0]-c0), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
							g.setColor(this.getForeground());
							g.drawString(dataModel.getValueAt(rr+r0,dataCoords[0]), defaultCellWidth*(dataCoords[0]-c0)+2 ,defaultCellHeight*rr+15 );
						}
					}else{
						g.setColor(dataModel.getBackgroundColor(dataCoords[1],dataCoords[0]));
						g.fillRect(defaultCellWidth*(dataCoords[0]-c0), defaultCellHeight*(dataCoords[1]-r0), 
							defaultCellWidth, defaultCellHeight);
						g.setColor(Color.gray);
						g.drawRect(defaultCellWidth*(dataCoords[0]-c0), defaultCellHeight*(dataCoords[1]-r0), 
							defaultCellWidth, defaultCellHeight);
						g.setColor(this.getForeground());
						g.drawString(dataModel.getValueAt(dataCoords[1],dataCoords[0]), 
							defaultCellWidth*(dataCoords[0]-c0)+2 ,defaultCellHeight*(dataCoords[1]-r0)+15 );
					}
				}else if(dataCoords.length == 4){
//					paintImmediately(coords[0]*defaultCellWidth,coords[1]*defaultCellHeight,(coords[2]-coords[0]+1)*defaultCellWidth,(coords[3]-coords[1]+1)*defaultCellHeight);
					for(int rr=0;rr<r;rr++){
						if(rr+r0>=dataCoords[1]&&rr+r0<=dataCoords[3]){
							for(int cc=0;cc<c;cc++){
								if(cc+c0>=dataCoords[0]&&cc+c0<=dataCoords[2]){
									g.setColor(dataModel.getBackgroundColor(rr+r0,cc+c0));
									g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
									g.setColor(Color.gray);
									g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
									g.setColor(this.getForeground());
									g.drawString(dataModel.getValueAt(rr+r0,cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*rr+15 );
								}
							}
						}
					}
				}
			}
			dataStatusChangeCoords.removeAllElements();
			isDataStatusChanging = false;
			areaTop=r0;
		 	areaRight=c0;
			areaWidth=c;
			areaHeight=r;
			return;
		}
/*		if(r != areaHeight || c != areaWidth){
System.out.println("paintImage not isDataStatusChanging 0 ");
			for(int rr=0;rr<r;rr++){
				for(int cc=0;cc<c;cc++){
					g.setColor(dataModel.getBackgroundColor(rr+r0,cc+c0));
					g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
					g.setColor(Color.gray);
					g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
					g.setColor(this.getForeground());
					g.drawString(dataModel.getValueAt(rr+r0,cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*rr+15 );
				}
			}
		}else if(areaTop !=r0 || areaRight!=c0){
System.out.println("paintImage not isDataStatusChanging 1");
			g.drawImage(cellImage,(areaRight-c0)*defaultCellWidth,(areaTop-r0)*defaultCellHeight, this);
			for(int rr=0;rr<r;rr++){
				for(int cc=0;cc<c;cc++){
					if((rr+r0>=areaTop+r || rr+r0<areaTop) || (cc+c0>=areaRight+c || cc+c0<areaRight)){
						g.setColor(dataModel.getBackgroundColor(rr+r0,cc+c0));
						g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
						g.setColor(Color.gray);
						g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
						g.setColor(this.getForeground());
						g.drawString(dataModel.getValueAt(rr+r0,cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*rr+15 );
					}
				}
			}
		}
*/		
		for(int rr=0;rr<r;rr++){
			for(int cc=0;cc<c;cc++){
				g.setColor(dataModel.getBackgroundColor(rr+r0,cc+c0));
				g.fillRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
				g.setColor(Color.gray);
				g.drawRect(defaultCellWidth*(cc), defaultCellHeight*(rr), defaultCellWidth, defaultCellHeight);
				g.setColor(this.getForeground());
				g.drawString(dataModel.getValueAt(rr+r0,cc+c0), defaultCellWidth*cc+2 ,defaultCellHeight*rr+15 );
			}
		}
		areaTop=r0;
		areaRight=c0;
		areaWidth=c;
		areaHeight=r;
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


 	@Override
	public void mousePressed(MouseEvent m) {
		isMousePressed = true;
		lastColumn = m.getX()/defaultCellWidth;
		lastRow = m.getY()/defaultCellHeight;
	}

	@Override
	public void mouseEntered(MouseEvent m) {}
	@Override
	public void mouseExited(MouseEvent m) {}
	@Override
	public void mouseReleased(MouseEvent m) {
		if(!isMousePressed) {
			return;
		}
		isMousePressed = true;
		int mod = m.getModifiers();
		if(mod == 4) {
			return;
		}
		int c = m.getX()/defaultCellWidth;
		int r = m.getY()/defaultCellHeight;
		if(c==lastColumn && r == lastRow) {
			return;
		}
		dataModel.selectArea(lastRow,lastColumn,r,c);
	}	
	public void mouseDragged(MouseEvent m) {}
	public void mouseMoved(MouseEvent m) {	}
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
	public void tableAltClicked(MouseEvent m) {}
/** Mouse shift click event handler */
	public void tableShiftClicked(MouseEvent m) {
//System.out.println("shift click");
		int c = m.getX()/defaultCellWidth;
		int r = m.getY()/defaultCellHeight;
		dataModel.shiftSelectCell(r,c);
	}
/** Mouse ctrl click event handler */
	public void tableCtrlClicked(MouseEvent m) {}
	public void tableRightClicked(MouseEvent m) {}
	public void tableDoubleClicked(MouseEvent m) {}
	public void tableMouseClicked(MouseEvent m) {
//		System.out.println("click in");
		int c = m.getX()/defaultCellWidth;
		int r = m.getY()/defaultCellHeight;
		dataModel.selectCell(r,c);
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
			int[] co = new int[0];
			dataStatusChangeCoords.addElement(co);
			isDataStatusChanging = true;
			int columnNumber = dataModel.getNumberOfColumns();
			int rowNumber = dataModel.getNumberOfRows();
			if(columnNumber <5){
				columnNumber = 5;
			}
			if(rowNumber <20) {
				rowNumber = 20;
			}
			displaySize = new Dimension(defaultCellWidth*columnNumber,defaultCellHeight*rowNumber);
			repaint();
		}else if(id.equals("labelChanged")){
			int[] co = new int[0];
			dataStatusChangeCoords.addElement(co);
			isDataStatusChanging = true;
			repaint();
		}else if(id.equals("labeling")){
			dataStatusChangeCoords.addElement(e.getCoords());
//		System.out.println("get labeling"+dataStatusChangeCoords.size());
			isDataStatusChanging = true;
			repaint();
		}
	}
	
/** Set the width of the cell panel. */
	public void setWidth(int width){
		defaultCellWidth = width;
		int[] co = new int[0];
		dataStatusChangeCoords.addElement(co);
		isDataStatusChanging = true;
//		int columnNumber = dataModel.getNumberOfColumns();
//		int rowNumber = dataModel.getNumberOfRows();
//		if(columnNumber <5) columnNumber = 5;
//		if(rowNumber <20) rowNumber = 20;
//		displaySize = new Dimension(defaultCellWidth*columnNumber,defaultCellHeight*rowNumber);
		repaint();
	}
}
