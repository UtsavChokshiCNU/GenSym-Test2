package com.gensym.nols.wksp;

import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;

/** TableColumnHeader Class*/
public class TableColumnHeader extends JPanel implements TableModelListener{
 	private JComponent holder;			// container
	private Dimension displaySize;
	private boolean isEditable;
	private TableDataModel dataModel;
	private int defaultCellWidth;
	private int defaultCellHeight;
	private int[] cellWidth;
	private boolean first;

	public TableColumnHeader(String n, JComponent table, TableDataModel dataModel) {
		super.setName(n);
		this.defaultCellWidth = 93;
		this.defaultCellHeight = 20;
		this.holder = table;
		this.dataModel = dataModel;
		int columnNumber = dataModel.getNumberOfColumns();
		if(columnNumber <5) {
			columnNumber = 5;
		}
		displaySize = new Dimension(defaultCellWidth*columnNumber,defaultCellHeight);
		setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
		for(int c=0;c<columnNumber+1;c++){
			JPanel columnPane = new JPanel();
			columnPane.setLayout(new BoxLayout(columnPane, BoxLayout.X_AXIS));
			Header header = new Header(c,dataModel.getColumnName(c),table);
			Dimension size = new Dimension(defaultCellWidth,defaultCellHeight);
//			Dimension size = new Dimension(defaultCellWidth-1,defaultCellHeight);
			header.setPreferredSize(size);
			header.setMinimumSize(size);
//			TableSeparator separater = new TableSeparator();
			columnPane.add(header);
//			columnPane.add(separater);
			add(columnPane);
		}
		first = true;
		addComponentListener(new TableGridShapeListener());
	}
	private void updateView(){
		Dimension d = getSize();
//		System.out.println("workPane size = "+d);
		int visibleColumn = (d.width+defaultCellWidth-1)/defaultCellWidth;
		int columnNumber = dataModel.getNumberOfColumns();
		if(columnNumber <visibleColumn) {
			columnNumber = visibleColumn;
		}
		displaySize = new Dimension(defaultCellWidth*columnNumber,defaultCellHeight);
		removeAll();
		for(int c=0;c<columnNumber;c++){
			JPanel columnPane = new JPanel();
			columnPane.setLayout(new BoxLayout(columnPane, BoxLayout.X_AXIS));
			Header header = new Header(c,dataModel.getColumnName(c),this.holder);
			Dimension size = new Dimension(defaultCellWidth,defaultCellHeight);
//			Dimension size = new Dimension(defaultCellWidth-1,defaultCellHeight);
			header.setPreferredSize(size);
			header.setMinimumSize(size);
//			TableSeparator separater = new TableSeparator();
			columnPane.add(header);
//			columnPane.add(separater);
			add(columnPane);
		}
	}

	public void setWidth(int width){
		defaultCellWidth = width;
		updateView();
	}

	class TableGridShapeListener extends ComponentAdapter {
		public TableGridShapeListener()	{
			super();
		}
		@Override
		public void componentResized(ComponentEvent e){
//			System.out.println("get the size change");
			if(!first){
				updateView();
			}
			first = false;
		}
	}
	class Header extends JComponent implements MouseListener,KeyListener {

		private JComponent holder;
		private int col;
		private Dimension displaySize;
		private boolean isEditable;

		public Header(int c, String name, JComponent table) {
			super();
			this.setName(name);
			this.col = c;
			this.holder = table;
			isEditable = false;
			displaySize = new Dimension(defaultCellWidth-1,defaultCellHeight);
			setBorder(BorderFactory.createBevelBorder(BevelBorder.RAISED));
			this.addMouseListener(this);
			this.addKeyListener(this);
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

/** Set the col position of component in container */
		public void setCol(int c) {
			this.col = c;
		}

/** Get the col position of component in container */
		public int getCol() {
			return this.col;
		}

		@Override
		protected void paintComponent(Graphics g) {
			Dimension d = getSize();
			g.setColor(this.getBackground());
			g.fillRect(1, 1, d.width-1, d.height-1);
			g.setColor(this.getForeground());
			g.drawString(this.getName(), 2 ,15 );
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
			tableMousePressed(m);
		}

/** Mouse entered event ownership is checked by the component and handled */
	@Override
	public void mouseEntered(MouseEvent m) {
		tableMouseEntered(m);
	}

/** Mouse exited event ownership is checked by the component and handled */
	@Override
	public void mouseExited(MouseEvent m) {
		tableMouseExited(m);
	}

/** Mouse released event ownership is checked by the component and handled */
	@Override
	public void mouseReleased(MouseEvent m) {
//		System.out.println("mouseReleased");	
		tableMouseReleased(m);
	}

/** Mouse dragged event ownership is checked by the component and handled */
	public void mouseDragged(MouseEvent m) {
		tableMouseDragged(m);
	}

/** Mouse moved event ownership is checked by the component and handled */
	public void mouseMoved(MouseEvent m) {
		tableMouseMoved(m);
	}

/** Mouse clicked event ownership is checked by the component and handled */
	@Override
	public void mouseClicked(MouseEvent m) {
//		System.out.println("mouseClicked");	
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
//System.out.println("alt click ["+ row+","+col+"]");
	}

/** Mouse shift click event handler */
	public void tableShiftClicked(MouseEvent m) {
//System.out.println("shift click ["+ row+","+col+"]");
//		holder.getTableDataModel().shiftClickIn(row,col);
	}

/** Mouse ctrl click event handler */
	public void tableCtrlClicked(MouseEvent m) {
//System.out.println("ctrl click ["+ row+","+col+"]");
	}

/** Mouse right click event handler */
	public void tableRightClicked(MouseEvent m) {
//S/ystem.out.println("right click ["+ row+","+col+"]");
		this.requestFocus();
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
//		System.out.println("click in"+getName()+" ["+ row+","+col+"]");
//		TableColumnHeader.this.dataModel.selectColumn(col);
	}

/** Mouse double clicked event handler */
	public void tableDoubleClicked(MouseEvent m) {
//		System.out.println("Double click in"+getName()+" ["+ row+","+col+"]");
	}

/** Key type event handler */
	@Override
	public void keyTyped(KeyEvent e){
		if(isEditable){
//			System.out.println("key typed in"+getName()+" ["+ row+","+col+"]");
		
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
	}
	/** Separator class*/
	class TableSeparator extends JComponent	implements MouseListener{
		
		Dimension size = new Dimension(1,defaultCellHeight);

		TableSeparator(){
			this.addMouseListener(this);
		}
		@Override
		public void setPreferredSize(Dimension size){
			super.setPreferredSize(size);
			this.size = size;
		}

		@Override
		public void setMinimumSize(Dimension size){
			super.setMinimumSize(size);
			this.size = size;
		}
		@Override
		public Dimension getPreferredSize(){
			return size;
		}
		@Override
		public Dimension getMinimumSize(){
			return size;
		}

		@Override
		public void mousePressed(MouseEvent m) {}
		@Override
		public void mouseEntered(MouseEvent m) {
			this.setCursor(new java.awt.Cursor(java.awt.Cursor.W_RESIZE_CURSOR));
		}
		@Override
		public void mouseExited(MouseEvent m) {
			this.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
		}
		@Override
		public void mouseReleased(MouseEvent m) {}
		public void mouseDragged(MouseEvent m) {}
		public void mouseMoved(MouseEvent m) {}
		@Override
		public void mouseClicked(MouseEvent m) {
System.out.println("sep mouseClicked");
		}
	} 

	@Override
	public void tableDataChanged(TableDataEvent e) {
	
		String id = e.getID();
		if(id.equals("dataChanged")){
			updateView();
		}
	}

}
