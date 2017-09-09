package com.gensym.nols.util;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;


public class NolSlider extends JPanel implements MouseListener, 
	ComponentListener {

	// added by Brian O. Bush to enhance readability, rather to make this code readable
	public static final int LOW_LIMIT = 0;
	public static final int SOFT_LOW_LIMIT = 1;
	public static final int SOFT_HIGH_LIMIT = 2;
	public static final int HIGH_LIMIT = 3;
		
	public static final int SETPOINT = 4;
	public static final int CURRENT = 5;
	
//	private Dimension displaySize;
	private Thumb lowLimitThumb;
	private Thumb highLimitThumb;
	private Thumb setpointThumb;
	private Thumb softLowThumb;
	private Thumb softHighThumb;
	private boolean showSetpoint;
	private boolean showSoftLow;
	private boolean showSoftHigh;
	private int majorTicks;
	private double minorTicks;
	private double min;
	private double max;
	private int margin;

	private int type; //0: with bounds 1: without bounds

	private double lowLimit;
	private double highLimit;
	private double setpoint;
	private double current;
	private double softLow;
	private double softHigh;
	
	private Vector nolSliderListeners;

	private static int THUMB_WIDTH = 12;
	private static int THUMB_HEIGHT = 10;

	private static int THUMB_TYPE_LOWLIMIT = 1;
	private static int THUMB_TYPE_HIGHTLIMIT = 2;
	private static int THUMB_TYPE_SETPOINT = 0;
	private static int THUMB_TYPE_SOFTLOW = 3;
	private static int THUMB_TYPE_SOFTHIGH = 4;
	private static int THUMB_TYPE_CURRENT = 5;
	private static int THUMB_TYPE_MIN = -1;
	private static int THUMB_TYPE_MAX = -2;


	private static int NO_BOUNDS = 1;

	private static Color normalValueColor = Color.green;
	private static Color lowBoundColor = new Color( 100 , 100 , 100);
	private static Color upBoundColor = Color.red;

	public NolSlider(int t){
		type = t;
		margin = 2;
		majorTicks = 2;
		minorTicks = 5.0;
		min = Double.NEGATIVE_INFINITY;
		max = Double.POSITIVE_INFINITY;
		lowLimit = Double.NEGATIVE_INFINITY;
		highLimit = Double.POSITIVE_INFINITY;
		softLow = Double.NEGATIVE_INFINITY;
		softHigh = Double.POSITIVE_INFINITY;
		setpoint = 50.0;
		current = 55.0;
		initLayout();
		addComponentListener(this);
		nolSliderListeners = new Vector();
		showSetpoint = true;
		showSoftLow = true;
		showSoftHigh = true;
	}
	
	public NolSlider(double min, double max, int t){
		this(t);
		this.min = min;
		this.max = max;	
		setpoint = (max+min)/2;
		current = setpoint +5;
		minorTicks = (max-min)/10.0;
		refreshSlider();
		showSetpoint = true;
		showSoftLow = true;
		showSoftHigh = true;
	}

	public NolSlider(double min, double max, double sp, int t){
		type = t;
//		displaySize = new Dimension(400,20);
		margin = 2;
		this.min = min;
		this.max = max;
		lowLimit = Double.NEGATIVE_INFINITY;
		highLimit = Double.POSITIVE_INFINITY;
		softLow = Double.NEGATIVE_INFINITY;
		softHigh = Double.POSITIVE_INFINITY;
		setpoint = sp;
		current = min;
		majorTicks = 2;
		minorTicks = (max-min)/10.0;
		initLayout();
		addComponentListener(this);
   		nolSliderListeners = new Vector();
		showSetpoint = true;
		showSoftLow = true;
		showSoftHigh = true;
	}

	public NolSlider(double min, double max, 
		double lb, double slb, double sub, double ub, double sp, int t){
		type = t;
//		displaySize = new Dimension(400,20);
		margin = 2;
		this.min = min;
		this.max = max;
		lowLimit = lb;
		highLimit = ub;
		softLow = slb;
		softHigh = sub;
		setpoint = sp;
		current = min;
		majorTicks = 2;
		minorTicks = (max-min)/10.0;
		initLayout();
		addComponentListener(this);
   		nolSliderListeners = new Vector();
		showSetpoint = true;
		showSoftLow = true;
		showSoftHigh = true;
	}

	public NolSlider(double min, double max, 
		double lb, double slb, double sub, double ub, double sp, double cu, int t){
		type = t;
//		displaySize = new Dimension(400,20);
		margin = 2;
		this.min = min;
		this.max = max;
		lowLimit = lb;
		highLimit = ub;
		softLow = slb;
		softHigh = sub;
		setpoint = sp;
		current = cu;
		majorTicks = 2;
		minorTicks = (max-min)/10.0;
		initLayout();
		addComponentListener(this);
   		nolSliderListeners = new Vector();
		showSetpoint = true;
		showSoftLow = true;
		showSoftHigh = true;
	}

	private void initLayout(){

		if(type!=NO_BOUNDS){
			lowLimitThumb = new Thumb(1,Color.blue);
			highLimitThumb = new Thumb(2,Color.red);
			softLowThumb = new Thumb(3,new Color(155,155,255));
			softHighThumb = new Thumb(4,new Color(255,155,155));
			setpointThumb = new Thumb(0,Color.yellow);
			lowLimitThumb.setToolTipText("Lower Bound");
			highLimitThumb.setToolTipText("Upper Bound");
			softLowThumb.setToolTipText("Soft Lower Bound");			
			softHighThumb.setToolTipText("Soft Upper Bound");			
			setpointThumb.setToolTipText("Setpoint");
		}else{
			setpointThumb = new Thumb(0,Color.green);
			setpointThumb.setToolTipText("Current Value");
		}
		
		setLayout(null);
		if(type!=NO_BOUNDS){
			add(highLimitThumb);
			add(softHighThumb);
			add(lowLimitThumb);
			add(softLowThumb);
		}
		add(setpointThumb);
		setBorder(BorderFactory.createBevelBorder(0));
		refreshSlider();
	}

	public boolean isShowSetpoint(){
		return showSetpoint;
	}

	public void setShowSetpoint(boolean b){
		showSetpoint = b;
	}

	public boolean isShowSoftLow(){
		return showSoftLow;
	}

	public void setShowSoftLow(boolean b){
		showSoftLow = b;
	}

	public boolean isShowSoftHigh(){
		return showSoftHigh;
	}

 	public void setShowSoftHigh(boolean b){
		showSoftHigh = b;
	}


	public int getType(){
		return type;
	}

	public void setMajorTicks(int t){
		if(t<0) {
			majorTicks = 0;
		}
		else majorTicks = t;
	}

	public void setMinorTicks(double t){
		if(t<0) {
			minorTicks = 0;
		}
		else minorTicks = t;
	}

	public void setRange(double min, double max){
		this.min = min;
		this.max = max;
	}

	public void setValues(int thumbType, double value){
		if(thumbType == THUMB_TYPE_LOWLIMIT){
			lowLimit = value;
		}else if(thumbType == THUMB_TYPE_HIGHTLIMIT){
			highLimit = value;
		}else if(thumbType == THUMB_TYPE_SETPOINT){
			setpoint = value;
		}else if(thumbType == THUMB_TYPE_SOFTLOW){
			softLow = value;
		}else if(thumbType == THUMB_TYPE_SOFTHIGH){
			softHigh = value;
		}else if(thumbType == THUMB_TYPE_CURRENT){
			current = value;
		}else if(thumbType == THUMB_TYPE_MIN){
			min = value;
		}else if(thumbType == THUMB_TYPE_MAX){
			max = value;
		}	
		refreshSlider();
		repaint(0l);
		validate();
	}



	public void setValues(int thumbType, int position){
		Dimension displaySize = getSize();
		int h = displaySize.height;
		int w = displaySize.width;
 		int disRange =w-margin*2;
		double range = max - min;
		if(thumbType == THUMB_TYPE_LOWLIMIT){
			lowLimit = position*range/disRange + min;
			highLimitThumb.setLow(position);
 			softLowThumb.setLow(position);
 			softHighThumb.setLow(position);
 			if(type!=NO_BOUNDS)
				setpointThumb.setLow(position);
		}else if(thumbType == THUMB_TYPE_HIGHTLIMIT){
			highLimit = position*range/disRange + min;
			lowLimitThumb.setUp(position);
 			if(type!=NO_BOUNDS)
	 			setpointThumb.setUp(position);
 			softLowThumb.setUp(position);
 			softHighThumb.setUp(position);
		}else if(thumbType == THUMB_TYPE_SETPOINT){
			setpoint = position*range/disRange + min;
		}else if(thumbType == THUMB_TYPE_SOFTLOW){
			softLow = position*range/disRange + min;
		}else if(thumbType == THUMB_TYPE_SOFTHIGH){
			softHigh = position*range/disRange + min;
		}

		NolSliderEvent evt = new NolSliderEvent(this, lowLimit,softLow, setpoint,
			softHigh,highLimit,current);
		fireEvent(evt);
	}

	public double[] getValues(){
		double[] vals = new double[6];
		vals[LOW_LIMIT] = lowLimit;
		vals[SOFT_LOW_LIMIT] = softLow;
		vals[SOFT_HIGH_LIMIT] = softHigh;
		vals[HIGH_LIMIT] = highLimit;
		vals[SETPOINT] = setpoint;
		vals[CURRENT] = current;
		return vals;
	}

	public void refreshSlider(){
		Dimension displaySize = getSize();
		int h = displaySize.height;
		int w = displaySize.width;
		int disRange =w-margin*2;
		double range = max - min;

		int setpointp = (int)((setpoint-min)*disRange/range)+margin;
		Component[] coms = getComponents();

		if(type!=NO_BOUNDS){
			int lowp = -12;
			if(!Double.isInfinite(lowLimit)){
				lowp = (int)((lowLimit-min)*disRange/range)+margin;
			}
			int highp = disRange + 24;
			if(!Double.isInfinite(highLimit)){
				highp = (int)((highLimit-min)*disRange/range)+margin;
			}
			int softlowp = -12;
			if(!Double.isInfinite(softLow)){
				softlowp = (int)((softLow-min)*disRange/range)+margin;
			}
			int softhighp = disRange + 24;
			if(!Double.isInfinite(softHigh)){
				softhighp = (int)((softHigh-min)*disRange/range)+margin;
			}
//			System.out.println("refreshSlider,lowp="+lowp); 
//			System.out.println("refreshSlider,softlowp="+softlowp); 
			lowLimitThumb.setLoc(lowp-THUMB_WIDTH/2,h-lowLimitThumb.getSize().height,THUMB_WIDTH,THUMB_HEIGHT);
			highLimitThumb.setLoc(highp-THUMB_WIDTH/2,h-highLimitThumb.getSize().height,THUMB_WIDTH,THUMB_HEIGHT);
			softLowThumb.setLoc(softlowp-THUMB_WIDTH/2,h-softLowThumb.getSize().height,THUMB_WIDTH,THUMB_HEIGHT);
			softHighThumb.setLoc(softhighp-THUMB_WIDTH/2,h-softHighThumb.getSize().height,THUMB_WIDTH,THUMB_HEIGHT);
			lowLimitThumb.setLowUp(0,highp);
			highLimitThumb.setLowUp(lowp,disRange);
			softLowThumb.setLowUp(0,highp);
			softHighThumb.setLowUp(lowp,disRange);
			setpointThumb.setLowUp(lowp,highp);
			if(showSoftLow){
				boolean found = false;
				for(int i=0;i<coms.length;i++){
					if(softLowThumb.equals(coms[i])){
						found = true;
						break;
					}
				}
				if(!found){
					add(softLowThumb);
				}

			}else{
				remove(softLowThumb);
			}

			if(showSoftHigh){
				boolean found = false;
				for(int i=0;i<coms.length;i++){
					if(softHighThumb.equals(coms[i])){
						found = true;
						break;
					}
				}
				if(!found){
					add(softHighThumb);
				}

			}else{
				remove(softHighThumb);
			}
		}
		setpointThumb.setLoc(setpointp-THUMB_WIDTH/2,0,THUMB_WIDTH,THUMB_HEIGHT);
		if(showSetpoint){
			boolean found = false;
			for(int i=0;i<coms.length;i++){
				if(setpointThumb.equals(coms[i])){
					found = true;
					break;
				}
			}
			if(!found){
				add(setpointThumb);
			}
		}else{
			remove(setpointThumb);
		}

	}

	@Override
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		refreshSlider();
		Dimension displaySize = getSize();
		int h = displaySize.height;
		int w = displaySize.width;
		if(type!=NO_BOUNDS){ 
			lowLimitThumb.setBounds();
			highLimitThumb.setBounds();
			softLowThumb.setBounds();
			softHighThumb.setBounds();
		}
		setpointThumb.setBounds();
		g.setColor(Color.white);
		g.fillRect(margin,h/2-6,w-margin*2,12);

		Color barColor = normalValueColor;
		if(current <= lowLimit){
			barColor = lowBoundColor;
		}else if(current >= highLimit){
			barColor = upBoundColor;
		}
		g.setColor(barColor);
		if(type!=NO_BOUNDS){
			int disRange =w-margin*2;  // if it is just w, it works better, but scales strangely
			double range = max - min;
			int currentp = (int)((current-min)*disRange/range)+margin;
			g.fillRect(margin,h/2-6,currentp-margin,12);
		}
		paintTicks(g);
	}
	
	private void paintTicks(Graphics g){
		Dimension displaySize = getSize();
		int h = displaySize.height;
		int w = displaySize.width;
		g.setColor(Color.black);
		int disRange =w-margin*2;
		double range = max - min;
//		g.drawLine(lowLimitThumb.getSize().width/2,h/2,disRange+highLimitThumb.getSize().width/2,h/2);
		if(minorTicks > 0 ) {
			double cutpoint = Math.floor((min+minorTicks)/minorTicks);
			cutpoint = minorTicks*cutpoint;
			int mc = 1;
			while(true){
				if(cutpoint<max){
					double dpx = (cutpoint - min)*disRange/range;
					int	px = (int) dpx + 4;
					if(mc == majorTicks){
						g.drawLine(px,h/2-2,px,h/2+2);
						mc = 0;
					}else{
						g.drawLine(px,h/2-1,px,h/2+1);
					}
					mc++;
					cutpoint = cutpoint+minorTicks;
				}else{
					break;
				}
			}
		}	 
	}

/** Register the event listener for this slider.*/
	public synchronized void addNolSliderListener(NolSliderListener l){
		this.nolSliderListeners.addElement(l);
	}

/** Deregister the event listener for the slider.*/
	public synchronized void removeNolSliderListener(NolSliderListener l){
		this.nolSliderListeners.removeElement(l);
	}

/** This method is to fire give data event.*/
	public void fireEvent(NolSliderEvent Evt){
		Vector targets;
		synchronized (this) {
			targets = (Vector) nolSliderListeners.clone();
		}
		for (int i = 0; i < targets.size(); i++) {
			NolSliderListener target = (NolSliderListener)targets.elementAt(i);
			target.valueChanged(Evt);
		}
	}

	@Override
	public void setPreferredSize(Dimension size){
		if(size.height>40) {
			size.height = 40;
		}
		super.setPreferredSize(size);
	}

	@Override
	public void setMinimumSize(Dimension size){
		if(size.height>40) {
			size.height = 40;
		}
		super.setMinimumSize(size);
	}

	@Override
	public Dimension getMaximumSize(){
		return new Dimension(400,40);
	}

	@Override
	public boolean isOpaque(){
		return true;
	}
	
	@Override
	public void componentResized(ComponentEvent e){
		refreshSlider();
		repaint(0l);
		validate();
	}
	@Override
	public void componentMoved(ComponentEvent e){}
	@Override
	public void componentShown(ComponentEvent e){}
	@Override
	public void componentHidden(ComponentEvent e){}

	@Override
	public void mousePressed(MouseEvent m) {
	}	
	@Override
	public void mouseEntered(MouseEvent m) {
	}
	@Override
	public void mouseExited(MouseEvent m) {
	}
	@Override
	public void mouseReleased(MouseEvent m) {
	}
	public void mouseDragged(MouseEvent m) {
	}
	public void mouseMoved(MouseEvent m) {
	}
	@Override
	public void mouseClicked(MouseEvent m) {
		NolSliderEvent evt = new NolSliderEvent(this, lowLimit,softLow, setpoint,
			softHigh,highLimit,current);
		fireEvent(evt);
	}

	class Thumb extends JComponent implements MouseListener,MouseMotionListener {
		private Dimension displaySize;
		private int type;  //0: low, 1: high, 2: setpoint, 3: current
		private Color thumbColor; 
		private int x,y,width,height;	 
		private int low,up;	 
		private boolean pressed;
		private boolean bounded;
		private boolean movable;
		
		public Thumb() {
			type = 0;
			pressed = false;
			bounded = false;
			movable = true;
			displaySize = new Dimension(12,10);
			thumbColor = Color.lightGray;
			addMouseListener(this);
			addMouseMotionListener(this);
			x = 0;
			y = 0;
			width = displaySize.width;
			height = displaySize.height;
		}

		public Thumb(int t) {
			this();
			type = t;
			thumbColor = Color.lightGray;
		}

		public Thumb(int t, Color c) {
			this();
			type = t;
			thumbColor = c;
		}

		@Override
		public boolean isOpaque(){
			return false;
		}

		public void setMovable(boolean m){
			movable = m;
		}

		public void setLoc(int x,int y, int w, int h){
			this.x = x;
			this.y = y;
			width = w;
			height = h;
		}

		public void setBounds(){
			setBounds(x,y,width,height);
		}

		public void setLowUp(int l, int u){
			low = l;
			up = u;
			bounded = true;
		}

		public void setLow(int l){
			low = l;
			if(x<(l-1)){
				x=l;
				NolSlider.this.setValues(type,x);
				NolSlider.this.repaint(0l);
				NolSlider.this.validate();
			}
			bounded = true;
		}

		public void setUp(int u){
			up = u;
			if(x>u){
				x = u;
				NolSlider.this.setValues(type,x);
				NolSlider.this.repaint(0l);
				NolSlider.this.validate();
			}
			bounded = true;
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

		@Override
		public Dimension getSize(){
			return displaySize;
		}

		@Override
		public void setSize(Dimension d){
			displaySize = d;
		}

		@Override
		protected void paintComponent(Graphics g){
			int h = displaySize.height;
			int w = displaySize.width;
			int[] xAxis = new int[5];
			int[] yAxis = new int[5];
			if(type != 0 ){
				xAxis[0] = 1;
				yAxis[0] = h-1;
				xAxis[1] = 1;
				yAxis[1] = h*3/5;
				xAxis[2] = w/2;
				yAxis[2] = 1;
				xAxis[3] = w-1;
				yAxis[3] = h*3/5;
				xAxis[4] = w-1;
				yAxis[4] = h-1;
			}else{
				xAxis[0] = 1;
				yAxis[0] = 1;
				xAxis[1] = 1;
				yAxis[1] = h*2/5;
				xAxis[2] = w/2;
				yAxis[2] = h-1;
				xAxis[3] = w-1;
				yAxis[3] = h*2/5;
				xAxis[4] = w-1;
				yAxis[4] = 1;
			}
			g.setColor(thumbColor);
			g.fillPolygon(xAxis,yAxis,5); 
			g.setColor(Color.black);
			g.drawPolygon(xAxis,yAxis,5); 
		}

	 	@Override
		public void mousePressed(MouseEvent m) {
			pressed = true;
		}
		@Override
		public void mouseEntered(MouseEvent m) {
		}
		@Override
		public void mouseExited(MouseEvent m) {
		}
		@Override
		public void mouseReleased(MouseEvent m) {
			pressed = false;
		}
		@Override
		public void mouseDragged(MouseEvent m) {
			if(pressed&&movable){
				int xnew = x + m.getX()-width/2;
//				int xnew = x + m.getX();
				if(bounded){
					if(xnew<low) {
						xnew = low;
					}
					if(xnew>up) {
						xnew = up;
					}
				}
				if(xnew != x){
					x = xnew;
					NolSlider.this.setValues(type,x);
					NolSlider.this.repaint(0l);
					NolSlider.this.validate();
				}
			}
		}
		@Override
		public void mouseMoved(MouseEvent m) {
		}
		@Override
		public void mouseClicked(MouseEvent m) {
		}
	}
}
