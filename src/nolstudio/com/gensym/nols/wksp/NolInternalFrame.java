package com.gensym.nols.wksp;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.URL;
import java.util.*;
import java.awt.print.*; //1.2.2 gchen 2.2.2000
import java.beans.PropertyVetoException; //1.3 gchen 4.26.2000


import javax.swing.text.*;
import javax.swing.*;

import com.gensym.nols.data.*;
import com.gensym.nols.main.*;

public class NolInternalFrame extends JInternalFrame implements 
MouseListener,MouseMotionListener,Printable,Pageable{

	protected DataSource dataSource;
	private Component gp;  // the frame's glass pane
	private Container nativeContainer;  // the outer frame
	private Cursor outerCursor;
	private Font internalFont;
	
	public NolInternalFrame(){
		super();
		setFrameIcon(NolMainFrame.gensymLogo);
		gp = getGlassPane(); 
		gp.addMouseListener(new MouseAdapter(){});
		internalFont = null;
	}

	public NolInternalFrame(DataSource dataSource){
		this();
		this.dataSource = dataSource;
	}

	public DataSource getDataSource(){
		return dataSource;
	}

	public void setDataSource(DataSource dataSource){
		this.dataSource = dataSource;
	}

    public JFrame getFrame() {
		for (Container p = getParent(); p != null; p = p.getParent()) {
			if (p instanceof JFrame) {
				return (JFrame) p;
			}
		}
		return null;
    }
//Test fonts.

	@Override
	public void paint(Graphics g){
		if (g instanceof PrintGraphics && internalFont != null) {
			g.setFont(internalFont);
//		System.out.println("Print internalFont="+internalFont);
		}else{
			if(internalFont == null){
				internalFont = g.getFont();
//		System.out.println("Screen internalFont="+internalFont);
			}
		}
/*		if (g instanceof PrintGraphics) {
			Font f = g.getFont();
			System.out.println("PrintGraphics f="+f);
		}else{
			Font f = g.getFont();
			System.out.println("Screen f="+f);
		}
*/		super.paint(g);
	}

	@Override
	public void mousePressed(MouseEvent m) {}
	@Override
	public void mouseEntered(MouseEvent m) {}
	@Override
	public void mouseExited(MouseEvent m) {}
	@Override
	public void mouseReleased(MouseEvent m) {}	
	@Override
	public void mouseDragged(MouseEvent m) {}
	@Override
	public void mouseMoved(MouseEvent m) {	}
	@Override
	public void mouseClicked(MouseEvent m) {}

	public void setWaitCursor(boolean p) {
		if(p) {
			gp.setVisible(true);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			outerCursor = nativeContainer.getCursor();
			nativeContainer.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
		} else {
			gp.setVisible(false);
			gp.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
			// force immediate change of cursor (workaround for needing to jiggle the mouse)
			if(outerCursor!=null){
				nativeContainer.setCursor(outerCursor);
			}
		}
	}
	
	@Override
	public void addNotify() {
		super.addNotify();
		Container parent = this;
	    while (! ((parent instanceof Panel) ||
			(parent instanceof ScrollPane) ||
			(parent instanceof Window)))
			parent = parent.getParent();

			//if (debug) System.out.println("nativeContainer="+parent);
	   nativeContainer = parent;
	}

//Added routine for 1.3 gchen 4.26.2000

	@Override
	public void setSelected(boolean selected)throws PropertyVetoException{
		super.setSelected(selected);
		if(selected){
			setVisible(selected);
		}
	}


//Added printing routine for 1.2.2 gchen 2.2.2000
	
	@Override
	public int getNumberOfPages(){
//		System.out.println(" in getNumberOfPages");
		return 1;
/*		NolInternalFrameFormat pageFormat = getPageFormat();
		if (pageFormat.scaleToFit)
		  return 1;
		double printableWidth = pageFormat.getImageableWidth();
		double printableHeight = pageFormat.getImageableHeight();
		return ((int)Math.ceil((pageFormat.scale * schematicWidth) / printableWidth)) *
			((int)Math.ceil((pageFormat.scale * schematicHeight) / printableHeight)); 

*/	}


	@Override
	public PageFormat getPageFormat(int pageIndex){
//		System.out.println(" in getPageFormat");
		return getPageFormat();
	}
	
	private NolInternalFrameFormat pageFormat;

	public NolInternalFrameFormat getPageFormat(){
		if (pageFormat == null)
		  pageFormat = new NolInternalFrameFormat();
		return pageFormat;
	}

	@Override
	public Printable getPrintable(int pageIndex){
//		System.out.println(" in getPrintable");
		return this;
	}

	@Override
	public int print(Graphics g, PageFormat pageFormat, int pageIndex) throws PrinterException{
		int numberOfPages = getNumberOfPages();

//		System.out.println(" in print numberOfPages="+numberOfPages);
//		System.out.println(" in print pageIndex="+pageIndex);
		if(pageIndex >= numberOfPages)
			return NO_SUCH_PAGE;

		Graphics2D  g2 = (Graphics2D) g;

		g2.translate(pageFormat.getImageableX(), pageFormat.getImageableY()); 

		double pageHeight = pageFormat.getImageableHeight();
		double pageWidth = pageFormat.getImageableWidth();

		double scale = 1.0;
		int frameWidth = getSize().width;
		int frameHeight = getSize().height;
		if (pageFormat instanceof NolInternalFrameFormat){
			NolInternalFrameFormat NolInternalFrameFormat = (NolInternalFrameFormat)pageFormat;
			if (NolInternalFrameFormat.scaleToFit)
				scale = Math.min(pageWidth/frameWidth, pageHeight/frameHeight);
			else
				scale = NolInternalFrameFormat.scale;
		}

/*		if (pageFormat instanceof NolInternalFrameFormat){
			NolInternalFrameFormat NolInternalFrameFormat = (NolInternalFrameFormat)pageFormat;
			if (NolInternalFrameFormat.scaleToFit)
				scale = Math.min(pageWidth/schematicWidth, pageHeight/schematicHeight);
			else
				scale = NolInternalFrameFormat.scale;
		}
*/
		int numberOfPagesInRow = (int)Math.ceil((scale * frameWidth) / pageWidth);
		int row = pageIndex / numberOfPagesInRow;
		int col = pageIndex % numberOfPagesInRow;

		g2.translate(-(pageWidth * col), -(pageHeight * row));
		g2.scale(scale, scale);
		paint(g2);
		return Printable.PAGE_EXISTS;
	}

	public class NolInternalFrameFormat extends PageFormat{

	  double scale = 1;
	  boolean scaleToFit;

	  public NolInternalFrameFormat(){
	  }

	  public NolInternalFrameFormat(PageFormat pageFormat){
		this.setOrientation(pageFormat.getOrientation());
		this.setPaper(pageFormat.getPaper());
	  }

	  public double getScale(){
		if (scaleToFit)
		  return 0;
		return scale;
	  }

	  public void setScale(double scale){
		if (scale > 0)
		  this.scale = scale;
		else
		  throw new IllegalArgumentException("scale must be greater than 0");
	  }

	  public boolean isScaleToFit(){
		return scaleToFit;
	  }

	  public void setScaleToFit(boolean scaleToFit){
		this.scaleToFit = scaleToFit;
	  }

	}
	
	protected void closeSilently(Closeable obj){
		  try {
		      if (obj != null) 
		    	  obj.close();
	      } catch (IOException e) {
	    	  System.err.println(e.toString());
	      } 
	  }
}

