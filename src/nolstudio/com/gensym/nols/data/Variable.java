package com.gensym.nols.data;

import java.awt.Color;
import java.io.Serializable;

import com.gensym.nols.util.ColorMap;

 /**
 * Gensym Variable Class
 * @version     1.0 September 30, 1998
 * @author      Brian O. Bush, Gang Chen
 **/

public class Variable implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected String name;
	protected String tag;
	protected String unit; 
	private double[] statistics;
	private String comment;		//Defaults are "".
	private int columnIndex;	// Giving the index in the data series. Base at 0.

	private int plotSymbol;
	private Color plotColor;

	protected transient DataSeries dataSeries;  // reference to data series object
	protected int dataSeriesHashCode;  // reference to data series object used to restore the data series pointer at load time
	/*  This class provides a general-purpose data source */

	private int denpendencyFlag; // 0:independeng; 1:exogenous.
	private double hlb;
	private double hub;
	private double initValue;
	private double resultValue;

	/** Default constructor.*/
	public Variable() {
		super();
		columnIndex = -1;
		name = "None";
		tag = "None";
		unit = "None";
		comment = "";
		statistics = new double[10];
		plotColor = Color.green;
		plotSymbol = 1;

		denpendencyFlag = 0;
		hlb = Double.NEGATIVE_INFINITY;
		hub = Double.POSITIVE_INFINITY;
		initValue = 0.0;
		resultValue = 0.0;
	}

/** Constructor with name, dataseries reference and column index.*/
	public Variable(String name, DataSeries d, int index) {
		this();
		columnIndex = index;
		int nColors = ColorMap.defaultPlotColors.length;
		if(index <0){
			plotSymbol = 0;
			plotColor = Color.green;
		}else{
			plotSymbol = index%7;
			plotColor = ColorMap.colors[ColorMap.defaultPlotColors[index%nColors]];
		}
		this.name = new String(name); // why is this necessary?  For proper serialization?
		tag = this.name;
		dataSeries = d;
		dataSeriesHashCode = dataSeries.hashCode();
	}

/** Constructor with name, tag, unit,dataseries reference and column index.*/
	public Variable(String tag,String name, String unit, DataSeries d, int index) {
		this();
		columnIndex = index;
		int nColors = ColorMap.defaultPlotColors.length;
		plotSymbol = index%7;
		plotColor = ColorMap.colors[ColorMap.defaultPlotColors[index%nColors]];
		this.name = new String(name);
		this.tag = new String(tag);
		this.unit = new String(unit);
		dataSeries = d;
		dataSeriesHashCode = dataSeries.hashCode();
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		Variable cloned = (Variable) super.clone();
		
		if(plotColor != null){
			float[] hsb = Color.RGBtoHSB(plotColor.getRed(), plotColor.getGreen(), plotColor.getBlue(), null);
			cloned.plotColor = Color.getHSBColor(hsb[0], hsb[1], hsb[2]);
		}
		cloned.dataSeries = dataSeries == null ? null : (DataSeries) dataSeries.clone();
				
		return cloned;
	}
	
	public DataSource getDataSource() {
		return dataSeries.getDataSource();
	}

	public int getDataSeriesHashCode() {
		return dataSeriesHashCode;
	}

	public DataSeries getDataSeries() {
		return dataSeries;
	}

	public void setDataSeries(DataSeries ds ) {
		dataSeries =ds;
		dataSeriesHashCode = dataSeries.hashCode();
	}

	public void setName(String n) {
		name = n;
		// fire event
	}
	
	public String getName() {
		return name;
	}

	/** Set the data series tag.*/
	public void setTag(String n) {
		tag = n;
		// fire event
	}

	/** Get the data series tag.*/
	public String getTag() {
		return tag;
	}

	/** Get the data series unit.*/
	public String getUnit(){
		return unit;
	}

	/** Set the data series unit.*/
	public void setUnit(String n){
		unit = n;
		// fire event ???
	}

	/** Get the plotSymbol.*/
	public int getPlotSymbol(){
		return plotSymbol;
	}

	/** Set the plotSymbol.*/
	public void setPlotSymbol(int s){
		plotSymbol = s;
		// fire event ???
	}

	/** Get the plotSymbol.*/
	public Color getPlotColor(){
		return plotColor;
	}

	/** Set the plotSymbol.*/
	public void setPlotColor(Color s){
		plotColor = s;
		// fire event ???
	}

	/** Get the data max.*/
	public double getMaxValue(){
		return statistics[8];
	}

	/** Get the data min.*/
	public double getMinValue(){
		return statistics[7];
	}

	/** Get the data mean.*/
	public double getMeanValue(){
		return statistics[0];
	}

	/** Get the data median.*/
	public double getMedianValue(){
		return statistics[1];
	}

	/** Get the data sum.*/
	public double getSum(){
		return statistics[9];
	}

	/** Get the data std.*/
	public double getSTD(){
		return statistics[2];
	}

	/** Get the data std.*/
	public double getVariance(){
		return statistics[3];
	}

	/** Get the data kurt.*/
	public double getKurt(){
		return statistics[4];
	}

	/** Get the data skew.*/
	public double getSkew(){
		return statistics[5];
	}

	/** Get the data range.*/
	public double getRange(){
		return statistics[6];
	}

	/** Get the data statistics.*/
	public double[] getStatistics(){
		return statistics;
	}

	/** Set the data statistics.*/
	public void setStatistics(double[] s){
		statistics = s;
	}

	/** Return the comment of this column.*/
	public String getComment(){
		return comment;
	}

	/** Set the comment of this column.*/
	public void setComment(String c){
		comment = c;
	}

	/** Return the columnIndex of this column.*/
	public int getColumnIndex(){
		return columnIndex;
	}

	/** Set the columnIndex of this column.*/
	public void setColumnIndex(int c){
		columnIndex = c;
	}

/** Initialize the transient attributes.*/
	public void initTransient(DataSeries ds){
		dataSeries = ds;
		dataSeriesHashCode = dataSeries.hashCode();
	}

	/** Returns a String object representing this column value.  */
	@Override
	public String toString(){
		return name;
	}
   
	/** Returns a String object representing this column value.  */
	public String toString(boolean flag){
		String s = "Name=" + name + "  Index=" + columnIndex + "  Tag=" + tag 
			+ "  Unit = " + unit;
		return s;
	}

/** Get the dependency flag.*/
	public int getDependencyFlag(){
		return denpendencyFlag;
	}

/** Set the dependency flag.*/
	public void setDependencyFlag(int f){
		denpendencyFlag = f;
	}

/** Get the initial value of the value.*/
	public double getInitialValue(){
		return initValue;
	}

/** Set the initial value of the value.*/
	public void setInitialValue(double v){
		initValue = v;
	}

	/** Get the hard lower bound.*/
	public double getHardLowerBound(){
		return hlb;
	}


	public double getHardUpperBound(){
		return hub;
	}

	public void setHardUpperBound(double b){
		hub = b;
	}

	public void setHardLowerBound(double b){
		hlb = b;
	}

/** Set the result value of the value.*/
	public void setResultValue(double v){
		resultValue = v;
	}

/** Get the result value of the value.*/
	public double getResultValue(){
		return resultValue;
	}

/** Initialize the hard upper and lower bounds of the variable.*/
	public void initializeHardBounds(){
		hlb = Double.NEGATIVE_INFINITY;
		hub = Double.POSITIVE_INFINITY;
	}
}