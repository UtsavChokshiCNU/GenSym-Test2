package com.gensym.nols.data;
import java.io.Serializable;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.nols.util.DecimalParser;
import com.gensym.nols.util.Parser;

public class DataSeriesFileFormat implements Cloneable, Serializable{
	static final long serialVersionUID = 1L;
	private static Double NAN = new Double(Double.NaN);
	private String name;
	private String suffix;
	private String separator;
	private String comment;
	private int column;
	private int tagLine;
	private int nameLine;
	private int unitLine;
	private int dateTimeColumn;
	private int dateColumn;
	private int timeColumn;
	private int[] ignoredRows;
	private int[] ignoredColumns;
	private boolean[] ignoredColumnMask;
	private SimpleDateFormat dateTimeFormat;		
	private SimpleDateFormat dateFormat;		
	private SimpleDateFormat timeFormat;

	private Vector symbols;

	private String decFormatLocalString;
	
	public DataSeriesFileFormat() {
		super();
		column = 0;
		tagLine = -1;
		nameLine = -1;
		unitLine = -1;
		dateTimeColumn = -1;
		dateColumn = -1;
		timeColumn = -1; 
		
		ignoredRows = new int[0];
		ignoredColumns = new int[0];
		ignoredColumnMask = new boolean[0];
		
		separator =" ";
		suffix = "";
		comment = "";

		dateTimeFormat = new SimpleDateFormat("MM/dd/yy hh:mm");
		dateFormat = new SimpleDateFormat("MM/dd/yy");
		timeFormat = new SimpleDateFormat("hh:mm:ss");
		symbols = new Vector();
		decFormatLocalString = "English";
	}
 	public DataSeriesFileFormat(String n) {
		this();
		name = n;
	}

 	@Override
	public Object clone() throws CloneNotSupportedException {
 		DataSeriesFileFormat cloned = (DataSeriesFileFormat) super.clone();
		cloned.dateTimeFormat = dateTimeFormat == null ? null : (SimpleDateFormat) dateTimeFormat.clone();
		cloned.dateFormat = dateFormat == null ? null : (SimpleDateFormat) dateFormat.clone();
		cloned.timeFormat = timeFormat == null ? null : (SimpleDateFormat) timeFormat.clone();
		cloned.symbols = symbols == null ? null : (Vector) symbols.clone();
		
		return cloned;
	}
	
 /** Return the comment of this DataSeriesFileFormat.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this DataSeriesFileFormat.*/
	public void setComment(String c){
		comment = c;
	}

	public SimpleDateFormat getDateTimeFormat(){
		return dateTimeFormat;
	}

	public void setDateTimeFormat(SimpleDateFormat f){
		dateTimeFormat = f;
	}

	public SimpleDateFormat getDateFormat(){
		return dateFormat;
	}

	public void setDateFormat(SimpleDateFormat f){
		dateFormat = f;
	}

	public SimpleDateFormat getTimeFormat(){
		return timeFormat;
	}

	public void setTimeFormat(SimpleDateFormat f){
		timeFormat = f;
	}

	public String getSuffix(){
		return suffix;
	}

	public void setSuffix(String s){
		suffix = s;
	}

	public String getSeparator(){
		return separator;
	}

	public void setSeparator(String s){
		separator = s;
	}

	public int getColumns(){
		return column;
	}

	public void setColumns(int count){
		if(column!=count) {
			column = count;
			ignoredColumnMask = new boolean[count];
		}
	}

	public int getTagLine(){
		return tagLine;
	}

	public void setTagLine(int count){
		tagLine = count;
	}

	public int getNameLine(){
		return nameLine;
	}

	public void setNameLine(int count){
		nameLine = count;
	}

	public int getUnitLine(){
		return unitLine;
	}

	public void setUnitLine(int count){
		unitLine = count;
	}

	public int getDateTimeColumn(){
		return dateTimeColumn;
	}

	public void setDateTimeColumn(int count){
		dateTimeColumn = count;
	}

	public int getDateColumn(){
		return dateColumn;
	}

	public void setDateColumn(int count){
		dateColumn = count;
	}

	public int getTimeColumn(){
		return timeColumn;
	}

	public void setTimeColumn(int count){
		timeColumn = count;
	}

	public int[] getIgnoredColumns(){
		return ignoredColumns;
	}

	public void setIgnoredColumns(int[] counts){
		ignoredColumns = counts;
		for(int index=0;index<ignoredColumnMask.length;index++) {
			ignoredColumnMask[index] = false;
			for(int j=0;j<ignoredColumns.length;j++){
				if(index==ignoredColumns[j]) {
					ignoredColumnMask[index]=true;
				}
			}
		}
	}

	public int[] getIgnoredRows() {
		return ignoredRows;
	}

	public void setIgnoredRows(int[] counts){
		ignoredRows = counts;
	}

	public Vector getSymbols(){
		return symbols;
	}

	public void setSymbols(Vector s){
		symbols = s;
	}

	public String getName(){
		return name;
	}

	public void setName(String n){
		name = n;
	}
	
	public String getDecimalFormatLocalString(){
		return decFormatLocalString;
	}

	public void setDecimalFormatLocalString(String f){
		decFormatLocalString = f;
	}
	
	public int getDataColumn(){
		int nDate = 0;
		if(dateColumn == -1 && timeColumn ==-1 && dateTimeColumn ==-1){
			nDate = 0;
		}else if(dateColumn != -1 && timeColumn !=-1){
			nDate = 2;
		}else{
			nDate = 1;
		}
//		System.out.println("getDataColumn: column="+column+" nDate="+nDate);
		return column-ignoredColumns.length-nDate; 
	}

	public int getCount(final String S) {
		int len,count=0,endIndex,sep1;
		String str = S.trim();
		while(true) {
			sep1 = str.indexOf(separator);
			endIndex = str.length();
			if(sep1>0){
				endIndex = Math.min(endIndex,sep1);
			}
			count++;
			try {
				str = str.substring(endIndex+1);
			} catch (StringIndexOutOfBoundsException B) {
				break;
			}
			str = str.trim();
		}
		return count;
	}

/** Read tag, unit, or name line. */
	public void readNonDataLine(String S, String[] subStrings) throws MathException {
		if(column==-1){
			return;
		}
		Vector tokens = Parser.string2Strings(S, separator);
		int ntokens = tokens.size();
		// check to make sure the EXACT number of tokens are found -- we require an exact match with format
		// this is how we make sure the user hasn't made a mistake choosing the wrong pre-existing format
		if(ntokens!=column) {
			throw new MathException("Number of names, tags or units does not match the format specification");
		}
		int index=1;   // start writing at index 1 (!)
		for(int col = 0; col < column; col++) {
			if(col==dateTimeColumn||col==dateColumn||col==timeColumn||ignoredColumnMask[col]) {
				// skip it
			} else if(col<ntokens) {
				subStrings[index] = (String) tokens.elementAt(col);
				index++;
			} else { // no more tokens, pad with empty strings
				subStrings[index] = "";  
				index++;
			} 
		}
	}

	/** Convert a data string to a data array, returning a timestamp for the row (if any) */
	public long readDataLine(String S, double[] data) throws MathException {
		if(column==-1) {
			return -2;
		}
		Vector tokens = Parser.string2Strings(S, separator);
		int ntokens = tokens.size();
		// trim to fit format if extra entries are present
		while(ntokens>column) {
			ntokens--;
			tokens.removeElementAt(ntokens);
		} // or pad with empty entries if not enough tokens are found
		while(ntokens<column) {
			tokens.addElement("");
			ntokens++;
		}
		Calendar currentCalendar = Calendar.getInstance();
		boolean noDate = true;
		int index=0;
		for(int col = 0; col < column; col++) {
			String NumString = (String) tokens.elementAt(col);
			if (ignoredColumnMask[col]) {
				// skip this column
			} else if (col==dateTimeColumn) {
				if(NumString.length()==0){
					return -2;  // skip this row, no time stamp
				}
				Date date1 = symbol2Date(NumString,0);
				if(date1 == null){
					return -1;
				}
				currentCalendar.setTime(date1);
				noDate = false;				
			} else if (col==dateColumn) {
				if(NumString.length()==0){
					return -2;  // skip this row, no time stamp
				}
				Date date2 = symbol2Date(NumString,1);
				if(date2 == null){
					return -1;
				}
				Calendar dateCalendar = Calendar.getInstance();
				dateCalendar.setTime(date2);
				currentCalendar.set(dateCalendar.get(Calendar.YEAR),
				dateCalendar.get(Calendar.MONTH),dateCalendar.get(Calendar.DATE));
				noDate = false;	
			} else if (col==timeColumn) {
				if(NumString.length()==0){
					return -2;  // skip this row, no time stamp
				}
				Date date3 = symbol2Date(NumString,2);
				if(date3 == null){
					return -1;
				}
				Calendar timeCalendar = Calendar.getInstance();
				timeCalendar.setTime(date3);
				currentCalendar.set(Calendar.HOUR_OF_DAY,timeCalendar.get(Calendar.HOUR_OF_DAY));
				currentCalendar.set(Calendar.MINUTE,timeCalendar.get(Calendar.MINUTE));
				currentCalendar.set(Calendar.SECOND,timeCalendar.get(Calendar.SECOND));
				currentCalendar.set(Calendar.MILLISECOND,timeCalendar.get(Calendar.MILLISECOND));
				noDate = false;
			} else { // a data column
				if(decFormatLocalString.equals("English")){
					try {
						data[index] = Double.valueOf(NumString).doubleValue();
					} catch(Exception e) {
						Object obj = convertBadNumString(NumString);
						if(obj instanceof Double){
							data[index] = ((Double)obj).doubleValue();
						}
						else return -2;  // hit an 'ignore this row' symbol (obj was a string)
					}
				}else{
					try {
						data[index] = DecimalParser.parse(NumString,decFormatLocalString);
					} catch(Exception e) {
						Object obj = convertBadNumString(NumString);
						if(obj instanceof Double) {
							data[index] = ((Double)obj).doubleValue();
						}else {
							return -2;  // hit an 'ignore this row' symbol (obj was a string)
						}
					}
				}
				index++;
			}
		}
		if(noDate){
			return -2;  // must have a date!
		} else {
			return currentCalendar.getTime().getTime();
		}
	}

	private final Object convertBadNumString(String NumString){
		// see if this is a special symbol
		for(int i=0;i<symbols.size();i++){
			Vector conv = (Vector) symbols.elementAt(i);
			String sym = (String) conv.elementAt(0);
			if(NumString.equals(sym)){
				return (Object) conv.elementAt(1);  // get conversion object
			}
		}
		return NAN;  // if here, return default (Double with value NaN)
	}

	private Date symbol2Date(String NumString,int flag){
		Date dt = null;
		try{
			if(flag == 0)
				dt= dateTimeFormat.parse(NumString);
			else if(flag == 1)
				dt= dateFormat.parse(NumString);
			else if(flag == 2)
				dt= timeFormat.parse(NumString);
		} catch(ParseException e) {
			return null;
		}
		return dt;
	}

	@Override
	public String toString(){
		return name;
	}

	public String toStringForTest(){
		String s="suffix: " + suffix;
		s = s+ "\n"+"Separater: "+ separator;
		s = s+"\n"+"Column: "+ column;
		s = s+"\n"+"tagLine: "+ tagLine;
		s = s+"\n"+"nameLine: "+ nameLine;
		s = s+"\n"+"unitLine: "+ unitLine;
		s = s+"\n"+"dateTimeColumn: "+ dateTimeColumn;
		s = s+"\n"+"dateColumn: "+ dateColumn;
		s = s+"\n"+"timeColumn: "+ timeColumn;

		s =s+"\n"+"ignoredRows:[";
		for(int i=0;i<ignoredRows.length;i++)
			s = s + ignoredRows[i]+",";
		s =s+"]";

		s = s+ "\ndateTimeFormat="+dateTimeFormat.toPattern();
		s = s+ "\ndateFormat="+dateFormat.toPattern();
		s = s+ "\ntimeFormat="+timeFormat.toPattern();

		return s;
	}
}


































