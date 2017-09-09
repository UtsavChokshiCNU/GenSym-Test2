package com.gensym.nols.data;
/*
 *		Gensym DataSeries Class.
 *		This class is extended from Object.class
 *		Modified 3/6/97 by Gchen
 */

import java.util.*;
import java.io.*;
import java.net.*;
import java.nio.charset.Charset;
import java.util.zip.*;
import java.text.*;
import com.gensym.nols.dlg.ProgressListener;
import com.gensym.nols.dlg.ProgressEvent;
//import com.gensym.nols.dlg.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

import com.gensym.DEBUG;

/** DataSeries class */
public class DataSeries implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private Matrix data;
	private String name; //Defaults are "unTitled".
	private Vector varObjects;
	private long[] timeStamps;  //Defaults are the times when this data series is created.
	private boolean locked; // used to lock this data series for model training.
	private boolean hasTimeStamps; 
	private boolean emptyData; 
 	private String comment; //Defaults are "".
	private transient Vector itsListeners;
	private transient DataSource dataSource;
	private int dataSourceHashCode;
	private int variableCounter;

	private static final boolean dsDEBUG = false;


/** Create a null data series with empty body.*/
	public DataSeries() {
		super();
		itsListeners = new Vector(0,10);
		this.data = Matlib.createMatrix();
		this.name = "";
		this.comment = "";
		this.timeStamps = new long[0];
		this.varObjects = new Vector();
		locked = false;
		hasTimeStamps = true;
		emptyData = false;
		variableCounter = 0;
	}
	
/** Create a data series from a Matrix and set other fields 
	to their defaults. */
	public DataSeries(Matrix M) {
		this();
		initialFromMatrix(M);
	}

	// added by MK, 5/21/99, for convenience
	public DataSeries(long[] t, Matrix M) {
		this();
		initialFromMatrix(M);
		setTimeStamps(t);
	}

/** Create a null data series with given # of variable and # 
	of samples. The name, tag, and etc. are set to defaults.*/
	public DataSeries(int row, int col) {
		this();
		if(row == 0){
			this.data = null;
			this.timeStamps = new long[0];
			for(int i=0;i<col;i++){
				Variable varObj = new Variable(makeVariableName(),this,i);
				varObjects.addElement(varObj);
			}
			locked = false;
			hasTimeStamps = false;
			emptyData = true;
		}else{
			initialFromMatrix(Matlib.createMatrix(row, col));
		}
	}

	private void initialFromMatrix(Matrix M) {
		this.data = M;
		int ns = M.getRows();
		int nv = M.getCols();
		this.timeStamps = new long[0];
		for(int i=0;i<nv;i++){
			Variable varObj = new Variable(makeVariableName(),this,i);
			varObjects.addElement(varObj);
		}
		calculateVarStatistics();
		locked = false;
		hasTimeStamps = false;
	}

/** Create a data series from a file. The file format is specified by the
format flag. format:  0: default ascii format; 1:
default binary format from deserialization. Note that NO directory name is specified. */
	public void Load(String fileName, int format){
		Load(null,fileName,format);
	}

/** Create a data series from a file. The file format is specified by the
format flag. format:  0: default ascii format; 1:
default binary format from deserialization. */
	public void Load(String directory, String fileName, int format){
		this.comment = "";
		int dotInd = fileName.indexOf(".");
		if(dotInd == -1){
			this.name = fileName;
		}else{
			this.name = fileName.substring(0,dotInd);
		}
		switch (format){
			case 0 :{  // *.ds format
				//if(dsDEBUG) System.out.println("Loading .ds file");
				File sourceFile;
				if(directory==null)
					sourceFile = new File(fileName);	
				else
					sourceFile = new File(directory,fileName);
				BufferedRandomAccessFile Source = null;
				//String dataString = "";
				StringBuffer dataStringBuffer;
				try{
					if (!sourceFile.exists() || !sourceFile.isFile())
						throw new IOException();
					if (!sourceFile.canRead())
						throw new IOException();
// If we've gotten this far, then everything is okay; we can
// read the file.	
					Source = new BufferedRandomAccessFile(sourceFile, "r", 65536);  // power of two size   
					if(dsDEBUG) {
						System.out.println("Reading the number of rows... ");
					}
					int rows = 0;
					while(true) {
						if(Source.getNextLine() == null) {
							break;
						}else{
							rows++;
						}
					}
					if(dsDEBUG) {
						System.out.println("Done, " + rows + " read in.");
					}
					
					Source = new BufferedRandomAccessFile(sourceFile, "r", 65536);  // power of two size    
					
					dataStringBuffer = Source.getNextLine();
					if(dataStringBuffer == null) {
						break;
					}

					///////////////////////////////////////////////////
					// DETERMINE THE NUMBER OF COLUMNS IN THE DATA FILE
					int cols = 0;
					char aCharArray [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < aCharArray.length; i++) // copy string buffer to character array
						aCharArray[i] = dataStringBuffer.charAt(i);
					int beginIndex = 0, endIndex = 0;  // start index into character array
					for(int j = 0; j < aCharArray.length; j++) {
						if(aCharArray[j] ==  '\u0009')  { 
							beginIndex++; 
						}else {
							break;
						}
					}
					int sep2 = 0, 
						sep3 = 0;
					while(true) {
						for(int i = beginIndex; i < aCharArray.length; i++) 
							if (aCharArray[i] == '\u0009') { 
								sep2 = i; 
								break; 
							} /* TAB */
						for(int i = beginIndex; i < aCharArray.length; i++) 
							if (aCharArray[i] == ',')  { 
								sep3 = i;	
								break; 
							}
						endIndex = aCharArray.length;
						if(sep2 > 0) {
							endIndex = Math.min(endIndex,sep2);
						}
						if(sep3 > 0) {
							endIndex = Math.min(endIndex,sep3);
						}
						cols++;
						beginIndex = endIndex;
						if(beginIndex >= aCharArray.length) {
							break;
						}
						for(int j = beginIndex; j < aCharArray.length; j++) {
							if(aCharArray[j] == '\u0009') {
								beginIndex++; }
							else break;
						}
//						System.out.println("cols = " + cols);
						sep2 = 0; 
						sep3 = 0;
					}				

					//////////////////////////////////////
					// READ IN THE TAGNAMES
					String[] tags = new String[cols];

					beginIndex = 0;
					endIndex = 0; 
					// TRIM THE FRONT
					for(int j = 0; j < aCharArray.length; j++) {
						if(aCharArray[j] ==  '\u0009')  {
							beginIndex++;
						}else {
							break;
						}
					}
					boolean noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals) {
							tags[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == '\u0009') {
									sep2 = i; 
									break; 
								} /* TAB */
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == ',')  {
									sep3 = i;	
									break; 
								}
							endIndex = aCharArray.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							tags[z] = new String(aCharArray, beginIndex, endIndex-beginIndex);
//							System.out.println("tag at " + z+ " = <" + tags[z] + ">");
							beginIndex = endIndex;
							if(beginIndex >= aCharArray.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < aCharArray.length; j++) {
								if(aCharArray[j] ==  '\u0009')  {
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}

					//////////////////////////////////////
					// READ IN THE NAMES
					dataStringBuffer = Source.getNextLine();
					if(dataStringBuffer == null) {
						break;
					}
					String[] names = new String[cols];
					
					char cArrayForNames [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < cArrayForNames.length; i++) // copy string buffer to character array
						cArrayForNames[i] = dataStringBuffer.charAt(i);

					beginIndex = 0;
					endIndex = 0; 
					
					// TRIM THE FRONT
					for(int j = 0; j < cArrayForNames.length; j++) {
						if(cArrayForNames[j] ==  '\u0009')  { 
							beginIndex++; 
						}else {
							break;
						}
					}
					noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals){
							names[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < cArrayForNames.length; i++) 
								if (cArrayForNames[i] == '\u0009') { 
									sep2 = i;
									break; 
								} /* TAB */
							for(int i = beginIndex; i < cArrayForNames.length; i++) 
								if (cArrayForNames[i] == ',')  { 
									sep3 = i;	
									break; 
								}
							endIndex = cArrayForNames.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							names[z] = new String(cArrayForNames, beginIndex, endIndex-beginIndex);
							if(dsDEBUG) {
								System.out.println("names at " + z+ " = <" + names[z] + ">");
							}
							beginIndex = endIndex;
							if(beginIndex >= cArrayForNames.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < cArrayForNames.length; j++) {
								if(cArrayForNames[j] ==  '\u0009')  { 
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}

					//////////////////////////////////////
					// READ IN THE UNITS
					dataStringBuffer = Source.getNextLine();
					if(dataStringBuffer == null){
						break;
					}

					String[] units = new String[cols];
					
					char [] charArrayForUnits = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < charArrayForUnits.length; i++) // copy string buffer to character array
						charArrayForUnits[i] = dataStringBuffer.charAt(i);

					beginIndex = 0;
					endIndex = 0; 
					
					// TRIM THE FRONT
					for(int j = 0; j < charArrayForUnits.length; j++) {
						if(charArrayForUnits[j] ==  '\u0009')  { 
							beginIndex++; 
						}else {
							break;
						}
					}
					noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals){
							units[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < charArrayForUnits.length; i++) 
								if (charArrayForUnits[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} /* TAB */
							for(int i = beginIndex; i < charArrayForUnits.length; i++) 
								if (charArrayForUnits[i] == ',')  { 
									sep3 = i;	
									break; 
								}
							endIndex = charArrayForUnits.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							units[z] = new String(charArrayForUnits, beginIndex, endIndex-beginIndex);
							if(dsDEBUG) {
								System.out.println("units at " + z+ " = <" + units[z] + ">");
							}
							beginIndex = endIndex;
							if(beginIndex >= charArrayForUnits.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < charArrayForUnits.length; j++) {
								if(charArrayForUnits[j] ==  '\u0009')  { 
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}
		
					rows = rows - 3; // since the top three rows are column headers and such...
					boolean regularRowCountMethod = true;
					if(rows < 20)
						regularRowCountMethod = false;

					if(tags[0].equals("Time")){
						hasTimeStamps = true;
						this.timeStamps = new long[rows];
						//System.out.println("This data Series has time stamps");
					}else{
						hasTimeStamps = false;
						this.timeStamps = null;
						//System.out.println("This data Series has NO time stamps");
					}

					int dcols = cols-1;
					if(!hasTimeStamps){
						dcols = cols;
					}
					int rr=0;
					this.data = Matlib.createMatrix(rows, dcols);
					while(true) {
						dataStringBuffer = Source.getNextLine();
						if (dataStringBuffer == null){
							break;
						}
						char charArray [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
						for(int i = 0; i < charArray.length; i++) // copy string buffer to character array
							charArray[i] = dataStringBuffer.charAt(i);
						beginIndex = 0; 
						endIndex = 0;
						sep2 = 0; 
						sep3 = 0;
	
						if(hasTimeStamps) {					
							for(int i = 0; i < charArray.length; i++)
								if (charArray[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} /* tab */
							for(int i = 0; i < charArray.length; i++)
								if (charArray[i] == ',') { 
									sep3 = i; 
									break; 
								} /* comma */
							endIndex = charArray.length;  // assume the largest possible end index
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2); // tab
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3); // comma
							}
							
							String cs = new String(charArray, 0, endIndex);
						//	if(dsDEBUG) System.out.println("string for time = <" + cs + ">");
							beginIndex = endIndex;
							this.timeStamps[rr] = Long.valueOf(cs).longValue();
						//	if(dsDEBUG) System.out.println("time added: " + Long.valueOf(cs));
						}

						// trim the front of the buffer beginning with beginIndex
						for(int j = beginIndex; j < charArray.length; j++) {
							if(charArray[j] ==  '\u0009') { 
								beginIndex++; 
							}else {
								break;
							}
						}

						noMoreVals = false;
						for(int z = 0 ; z < dcols; z++) {
							if(noMoreVals) 
								this.data.set(rr, z, 0.0);
							else {
								sep2 = 0;
								sep3 = 0;
								for(int i = beginIndex; i < charArray.length; i++)
									if (charArray[i] == '\u0009') {
										sep2 = i; 
										break; 
									} /* tab */
								for(int i = beginIndex; i < charArray.length; i++)
									if (charArray[i] == ',') { 
										sep3 = i; 
										break; 
									} /* comma */
								
								// check here to see if there are more tabs, which would
								// indicate that there was a blank value in this column at this time.

								endIndex = charArray.length;  // assume the largest possible end index
								if(sep2 > 0) {
									endIndex = Math.min(endIndex,sep2); // tab
								}
								if(sep3 > 0) {
									endIndex = Math.min(endIndex,sep3); // comma
								}
							//	if(dsDEBUG) System.out.println("beginIndex = " + beginIndex + " endIndex = " + endIndex);
								String cs = new String(charArray, beginIndex, endIndex-beginIndex);
							//	if(dsDEBUG) System.out.println("string = <" + cs + ">");
								if(cs.indexOf("NaN") != -1){
									this.data.set(rr, z, Double.NaN);
								}else{
									this.data.set(rr, z, Double.valueOf(cs).doubleValue());
								}
								beginIndex = endIndex;
								if(beginIndex >= charArray.length) {
									noMoreVals = true;
								}

								// trim the front of the buffer beginning with beginIndex
								for(int j = beginIndex; j < charArray.length; j++) {
									if(charArray[j] ==  '\u0009') { 
										beginIndex++; 
									}else {
										break;
									}
								}
							}
						}
						rr++;
						if(regularRowCountMethod) {
							if((rr % (rows/20)) == 0) 
								informListeners();
						}
						else informListeners();
					}
					if(tags != null){
						CheckAndModifyForSameString(tags);
					}
					if(names != null){
						CheckAndModifyForSameString(names);
					}
					varObjects = new Vector(dcols);
					for(int i=0;i<dcols;i++){
						int ii = i;
						if(hasTimeStamps){
							ii = i + 1;
						}
						Variable varObj = new Variable(tags[ii], names[ii], units[ii], this, i);
						varObjects.addElement(varObj);
					}
					calculateVarStatistics();
// No matter what happens, always close any streams we've opened.
				}catch(IOException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}
				finally {
					if (Source != null) 
						try { 
							Source.close(); 
						} 
						catch (IOException e) {
								System.err.println("Non-Fatal exception: " + e.getMessage());
								e.printStackTrace();
						}
				}
				break;	
					}
			case 1: { // *.bds file format
				ObjectInputStream in = null;
				try {
					File sourceFile;
					if(directory==null)
						sourceFile = new File(fileName);	
					else
						sourceFile = new File(directory,fileName);
					FileInputStream fis = new FileInputStream(sourceFile); // Read from file
					GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
					in = new ObjectInputStream(gzis);  // Read objects
				// Read in an object.  It should be a vector of scribbles
					VersionManagerForDataSeries versionForData = (VersionManagerForDataSeries)in.readObject();
					in.close(); // Close the stream.
					DataSeries ds = versionForData.getDataSeries();
					this.data = ds.data;
					this.timeStamps = ds.timeStamps;
					this.varObjects = ds.varObjects;
					this.comment = ds.comment;
					this.locked = ds.locked;
					this.hasTimeStamps = ds.hasTimeStamps;
					this.dataSourceHashCode = ds.dataSourceHashCode;
					for(int i=0;i<varObjects.size();i++){
						Variable varObj = (Variable)varObjects.elementAt(i);
						varObj.initTransient(this);
					}
				}catch(Exception evt) { 
					System.err.println(evt.getMessage()); 
					evt.printStackTrace(); 
				}finally {
					if (in != null) 
						try {
							in.close(); 
						} catch (IOException e) { 
							System.err.println(e.getMessage());  
							e.printStackTrace(); 
						}
				}
				break;	
					}
			case 2 :{
					try{
						Matrix M = Matlib.createMatrix(directory,fileName);
						initialFromMatrix(M);
					}catch(IOException evt){ 
						System.err.println(evt.getMessage());  
						evt.printStackTrace();
					}
					break;
				}
		    default:
		}
		locked = false;
	}



/** Create a data series from a url. The file format is specified by the
format flag. format:  0: default ascii format; 1:
default binary format from deserialization. */
	public void Load(URL url, int format){

		this.comment = "";
		String fileName = url.getFile();
		int dotInd = fileName.indexOf(".");
		if(dotInd == -1){
			this.name = fileName;
		}else{
			this.name = fileName.substring(0,dotInd);
		}
		switch (format){
			case 0 :{  // *.ds format
				//if(dsDEBUG) System.out.println("Loading .ds file");
				Reader streamReader1 = null;
				BufferedReader Source1 = null;
				
				Reader streamReader2 = null;
				BufferedReader Source2 = null;
				
				//String dataString = "";
				Charset charset = Charset.defaultCharset();
				StringBuffer dataStringBuffer;
				try{
					
			    	streamReader1 = new InputStreamReader(url.openStream(), charset);
			    	Source1 = new BufferedReader(streamReader1);  // power of two size   
					if(dsDEBUG) 
						System.out.println("Reading the number of rows... ");
					int rows = 0;
					while (Source1.readLine() != null)
						rows++;

					if(dsDEBUG) 
						System.out.println("Done, " + rows + " read in.");
					
					streamReader2 = new InputStreamReader(url.openStream(), charset);
			    	Source2 = new BufferedReader(streamReader2);  // power of two size   
					
					dataStringBuffer = new StringBuffer(Source2.readLine());
					if(dataStringBuffer == null) {
						break;
					}

					///////////////////////////////////////////////////
					// DETERMINE THE NUMBER OF COLUMNS IN THE DATA FILE
					int cols = 0;
					char aCharArray [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < aCharArray.length; i++) // copy string buffer to character array
						aCharArray[i] = dataStringBuffer.charAt(i);
					int beginIndex = 0, endIndex = 0;  // start index into character array
					for(int j = 0; j < aCharArray.length; j++) {
						if(aCharArray[j] ==  '\u0009')  { 
							beginIndex++; 
						}else{
							break;
						}
					}
					int sep2 = 0, 
						sep3 = 0;
					while(true) {
						for(int i = beginIndex; i < aCharArray.length; i++) 
							if (aCharArray[i] == '\u0009') { 
								sep2 = i; 
								break; 
							} 
						for(int i = beginIndex; i < aCharArray.length; i++) 
							if (aCharArray[i] == ',')  {
								sep3 = i;	
								break; 
							}
						endIndex = aCharArray.length;
						if(sep2 > 0) {
							endIndex = Math.min(endIndex,sep2);
						}
						if(sep3 > 0) {
							endIndex = Math.min(endIndex,sep3);
						}
						cols++;
						beginIndex = endIndex;
						if(beginIndex >= aCharArray.length){
							break;
						}
						for(int j = beginIndex; j < aCharArray.length; j++) {
							if(aCharArray[j] == '\u0009') {
								beginIndex++; }
							else break;
						}
//						System.out.println("cols = " + cols);
						sep2 = 0; 
						sep3 = 0;
					}				

					//////////////////////////////////////
					// READ IN THE TAGNAMES
					String[] tags = new String[cols];

					beginIndex = 0;
					endIndex = 0; 
					// TRIM THE FRONT
					for(int j = 0; j < aCharArray.length; j++) {
						if(aCharArray[j] ==  '\u0009')  {
							beginIndex++; 
						}else {
							break;
						}
					}
					boolean noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals){
							tags[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} // TAB 
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == ',')  { 
									sep3 = i;	
									break; 
								}
							endIndex = aCharArray.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							tags[z] = new String(aCharArray, beginIndex, endIndex-beginIndex);
//							System.out.println("tag at " + z+ " = <" + tags[z] + ">");
							beginIndex = endIndex;
							if(beginIndex >= aCharArray.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < aCharArray.length; j++) {
								if(aCharArray[j] ==  '\u0009')  {
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}

					//////////////////////////////////////
					// READ IN THE NAMES
					dataStringBuffer = new StringBuffer(Source2.readLine());
					if(dataStringBuffer == null) {
						break;
					}
					String[] names = new String[cols];
					
					char cArray [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < cArray.length; i++) // copy string buffer to character array
						cArray[i] = dataStringBuffer.charAt(i);

					beginIndex = 0;
					endIndex = 0; 
					
					// TRIM THE FRONT
					for(int j = 0; j < aCharArray.length; j++) {
						if(aCharArray[j] ==  '\u0009')  { 
							beginIndex++; 
						}else {
							break;
						}
					}
					noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals){
							names[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} // TAB 
							for(int i = beginIndex; i < aCharArray.length; i++) 
								if (aCharArray[i] == ',')  { 
									sep3 = i;	
									break; 
								}
							endIndex = aCharArray.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							names[z] = new String(aCharArray, beginIndex, endIndex-beginIndex);
							if(dsDEBUG) {
								System.out.println("names at " + z+ " = <" + names[z] + ">");
							}
							beginIndex = endIndex;
							if(beginIndex >= aCharArray.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < aCharArray.length; j++) {
								if(aCharArray[j] ==  '\u0009')  { 
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}

					//////////////////////////////////////
					// READ IN THE UNITS
					dataStringBuffer = new StringBuffer(Source2.readLine());
					if(dataStringBuffer == null) {
						break;
					}

					String[] units = new String[cols];
					
					char [] charArrayForUnits = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
					for(int i = 0; i < charArrayForUnits.length; i++) // copy string buffer to character array
						charArrayForUnits[i] = dataStringBuffer.charAt(i);

					beginIndex = 0;
					endIndex = 0; 
					
					// TRIM THE FRONT
					for(int j = 0; j < charArrayForUnits.length; j++) {
						if(charArrayForUnits[j] ==  '\u0009')  { 
							beginIndex++; 
						}else {
							break;
						}
					}
					noMoreVals = false;
					for(int z = 0; z < cols; z++) {
						if(noMoreVals) {
							units[z] = "";
						}else {
							sep2 = 0; 
							sep3 = 0;
							for(int i = beginIndex; i < charArrayForUnits.length; i++) 
								if (charArrayForUnits[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} // TAB 
							for(int i = beginIndex; i < charArrayForUnits.length; i++) 
								if (charArrayForUnits[i] == ',')  { 
									sep3 = i;	
									break; 
								}
							endIndex = charArrayForUnits.length;
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2);
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3);
							}
							units[z] = new String(charArrayForUnits, beginIndex, endIndex-beginIndex);
							if(dsDEBUG) {
								System.out.println("units at " + z+ " = <" + units[z] + ">");
							}
							beginIndex = endIndex;
							if(beginIndex >= charArrayForUnits.length) {
								noMoreVals = true;
							}

							// TRIM THE REAR
							for(int j = beginIndex; j < charArrayForUnits.length; j++) {
								if(charArrayForUnits[j] ==  '\u0009')  { 
									beginIndex++; 
								}else {
									break;
								}
							}
						}
					}
		
					rows = rows - 3; // since the top three rows are column headers and such...
					boolean regularRowCountMethod = true;
					if(rows < 20)
						regularRowCountMethod = false;

					if(tags[0].equals("Time")){
						hasTimeStamps = true;
						this.timeStamps = new long[rows];
						//System.out.println("This data Series has time stamps");
					}else{
						hasTimeStamps = false;
						this.timeStamps = null;
						//System.out.println("This data Series has NO time stamps");
					}

					int dcols = cols-1;
					if(!hasTimeStamps){
						dcols = cols;
					}
					int rr=0;
					this.data = Matlib.createMatrix(rows, dcols);
					while(true) {
						String dstr = Source2.readLine();
						if (dstr == null) {
							break;
						}
						dataStringBuffer = new StringBuffer(dstr);
						char charArray [] = new char[dataStringBuffer.length()]; // create character array to hold string buffer contents
						for(int i = 0; i < charArray.length; i++) // copy string buffer to character array
							charArray[i] = dataStringBuffer.charAt(i);
						beginIndex = 0; 
						endIndex = 0;
						sep2 = 0; 
						sep3 = 0;
	
						if(hasTimeStamps) {					
							for(int i = 0; i < charArray.length; i++)
								if (charArray[i] == '\u0009') { 
									sep2 = i; 
									break; 
								} // tab
							for(int i = 0; i < charArray.length; i++)
								if (charArray[i] == ',') { 
									sep3 = i; 
									break; 
								} // comma 
							endIndex = charArray.length;  // assume the largest possible end index
							if(sep2 > 0) {
								endIndex = Math.min(endIndex,sep2); // tab
							}
							if(sep3 > 0) {
								endIndex = Math.min(endIndex,sep3); // comma
							}
							
							String cs = new String(charArray, 0, endIndex);
						//	if(dsDEBUG) System.out.println("string for time = <" + cs + ">");
							beginIndex = endIndex;
							this.timeStamps[rr] = Long.valueOf(cs).longValue();
						//	if(dsDEBUG) System.out.println("time added: " + Long.valueOf(cs));
						}

						// trim the front of the buffer beginning with beginIndex
						for(int j = beginIndex; j < charArray.length; j++) {
							if(charArray[j] ==  '\u0009') { 
								beginIndex++; 
							}else{
								break;
							}
						}

						noMoreVals = false;
						for(int z = 0 ; z < dcols; z++) {
							if(noMoreVals) 
								this.data.set(rr, z, 0.0);
							else {
								sep2 = 0;
								sep3 = 0;
								for(int i = beginIndex; i < charArray.length; i++)
									if (charArray[i] == '\u0009') { 
										sep2 = i; 
										break; 
									} // tab  
								for(int i = beginIndex; i < charArray.length; i++)
									if (charArray[i] == ',') { 
										sep3 = i; 
										break; 
									} // comma  
								
								// check here to see if there are more tabs, which would
								// indicate that there was a blank value in this column at this time.

								endIndex = charArray.length;  // assume the largest possible end index
								if(sep2 > 0) {
									endIndex = Math.min(endIndex,sep2); // tab
								}
								if(sep3 > 0) {
									endIndex = Math.min(endIndex,sep3); // comma
								}
							//	if(dsDEBUG) System.out.println("beginIndex = " + beginIndex + " endIndex = " + endIndex);
								String cs = new String(charArray, beginIndex, endIndex-beginIndex);
							//	if(dsDEBUG) System.out.println("string = <" + cs + ">");
								if(cs.indexOf("NaN") != -1){
									this.data.set(rr, z, Double.NaN);
								}else{
									this.data.set(rr, z, Double.valueOf(cs).doubleValue());
								}
								beginIndex = endIndex;
								if(beginIndex >= charArray.length) {
									noMoreVals = true;
								}

								// trim the front of the buffer beginning with beginIndex
								for(int j = beginIndex; j < charArray.length; j++) {
									if(charArray[j] ==  '\u0009') { 
										beginIndex++; 
									}else {
										break;
									}
								}
							}
						}
						rr++;
						if(regularRowCountMethod) {
							if((rr % (rows/20)) == 0) 
								informListeners();
						}
						else informListeners();
					}
					if(tags != null){
						CheckAndModifyForSameString(tags);
					}
					if(names != null){
						CheckAndModifyForSameString(names);
					}
					varObjects = new Vector(dcols);
					for(int i=0;i<dcols;i++){
						int ii = i;
						if(hasTimeStamps){
							ii = i + 1;
						}
						Variable varObj = new Variable(tags[ii], names[ii], units[ii], this, i);
						varObjects.addElement(varObj);
					}
					calculateVarStatistics();
// No matter what happens, always close any streams we've opened.
				}catch(IOException e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}
				finally {
					closeSilently(Source1);
					closeSilently(Source2);
					closeSilently(streamReader1);
					closeSilently(streamReader2);
				}
				break;	
					}
			case 2 :{
					try{
						Matrix M = Matlib.createMatrix(url);
						initialFromMatrix(M);
					}catch(IOException evt){ 
						System.err.println(evt.getMessage());  
						evt.printStackTrace();
					}
					break;
				}
		    default:
		}
		locked = false;	  
	}
	
	private void closeSilently(Closeable obj){
	  try {
	      if (obj != null) 
	    	  obj.close();
      } catch (IOException e) {
    	  System.err.println("NON-FATAL exception: Error while closing stream : " + e.getMessage());
      } 
    }


/** Create a data series from a file. The file format is specified by 
	a file format object. */
	public void LoadViaFormat(String directory, String fileName, 
		DataSeriesFileFormat format, String dsName) throws MathException{

		File sourceFile;
		if(directory==null)
			sourceFile = new File(fileName);	
		else
			sourceFile = new File(directory,fileName);
		BufferedRandomAccessFile Source = null;
		String dataString;
		name = dsName;

		int dataCols = format.getDataColumn();
		int tagLine = format.getTagLine();
		int nameLine = format.getNameLine();
		int unitLine = format.getUnitLine();
		int[] ignoredRows = format.getIgnoredRows();

		int nonDataRows = ignoredRows.length;
		if(tagLine!=-1){
			nonDataRows++;
		}
		if(nameLine!=-1){
			nonDataRows++;
		}
		if(unitLine!=-1){
			nonDataRows++;
		}

		String[] tags = new String[dataCols+1];
		String[] names = new String[dataCols+1];
		String[] units = new String[dataCols+1];
		double[] dataRow = new double[dataCols];
		
		if ((format.getDateTimeColumn() != -1) || (format.getDateColumn() != -1) || (format.getTimeColumn() != -1)) {
			hasTimeStamps = true;	
			if(DEBUG.debugFlag) {
				System.out.println("This dataSeries has time stamps");
			}
		}
		else {
			hasTimeStamps = false;
			if(DEBUG.debugFlag) {
				System.out.println("This dataSeries has NO time stamps");
			}
		}

		try {
			if (!sourceFile.exists() || !sourceFile.isFile())
				throw new IOException();
			if (!sourceFile.canRead())
				throw new IOException();
			// If we've gotten this far, then everything is okay; we can read the file
			Source = new BufferedRandomAccessFile(sourceFile, "r", 65536);    // try 65536, 32768, 16384, 8192 

			// find out approximate dimensions
			int totalrows=0;
			totalrows = Source.countLines();
			totalrows -= nonDataRows;
			if(totalrows<=0) 
				throw new MathException("No data rows");
//System.out.println("Total rows = "+totalrows+", cols = "+dataCols);
			Matrix matrix = Matlib.createMatrix(totalrows, dataCols);
			long[] timeStampsArray = null;
			if(hasTimeStamps) 
				timeStampsArray = new long[totalrows];
			boolean regularRowCountMethod = true;  // for progress bar
			if(totalrows < 20) 
				regularRowCountMethod = false;
			int rr=0,r=0;
// Now, actually read the file
			Source.reset();  // rewind to top of file
			while(true){
				dataString = Source.getNextLineAsString();
				if (dataString == null){
					break;
				}
				if(r==tagLine) {
					format.readNonDataLine(dataString,tags);
				}else if(r==nameLine) {
					format.readNonDataLine(dataString,names);
				}else if(r==unitLine) {
					format.readNonDataLine(dataString,units);
				}else {  // check if this row is to be ignored
					boolean ignored = false;
					for(int j=0;j<ignoredRows.length;j++){
						if(r==ignoredRows[j]){
							ignored = true;
							break;
						}
					}
					if(!ignored) {
						long date = 0L;
						date = format.readDataLine(dataString,dataRow);
					//} catch (MathException me) {throw new MathException("Load failure on line "+r+": "+me.getMessage());}
						if(hasTimeStamps) {
							if(date == -1){
								throw new MathException("Load failed! Could not parse date/time on line "+r+".");
							}else if(date != -2){
								timeStampsArray[rr] = date;
								for(int i=0;i<dataRow.length;i++){
									matrix.set(rr,i,dataRow[i]);
								}
								rr++;
							}
						} else { // no time stamps
							for(int i=0;i<dataRow.length;i++) {
								matrix.set(rr,i,dataRow[i]);
							}
							rr++;						
						}
					}
				}
				r++;
				if(regularRowCountMethod) {
					if((rr % (totalrows/20)) == 0) 
						informListeners();
				}
				else informListeners();
			}
			// now cut matrix down to actual size
			//System.out.println("r = "+r+" rr = "+rr);
			if(rr==totalrows) {
				this.data = matrix;
				this.timeStamps = timeStampsArray;
			} else {
				this.data = Matlib.createMatrix();
				Matlib.getRows(matrix,0,rr-1,this.data);
				Matlib.clear(matrix);
				Matlib.pack();
				if(hasTimeStamps){
					this.timeStamps = new long[rr];
				}
				System.arraycopy(timeStampsArray,0,this.timeStamps,0,rr);
				timeStampsArray = null;
			}
			if(tagLine == -1 && nameLine == -1){
				for(int i=1;i<=dataCols;i++){
					String variableName = makeVariableName();
					tags[i] = variableName;
					names[i] = variableName;
				}  		
			} else if(tagLine == -1){
				for(int i=1;i<=dataCols;i++){
					tags[i] = names[i];
				}  		
			} else if(nameLine == -1){
				for(int i=1;i<=dataCols;i++) {
					names[i] = tags[i];
				}  		
			}
			if(unitLine == -1){
				for(int i=1;i<=dataCols;i++){
					units[i] = "None";
				}
			}
			if(tags != null){
				CheckAndModifyForSameString(tags);
			}
			if(names != null){
				CheckAndModifyForSameString(names);
			}
			varObjects = new Vector(dataCols);
			for(int i=0;i<dataCols;i++){
//System.out.println("tags[i+1]= "+tags[i+1]);
//System.out.println("names[i+1]= "+names[i+1]);
//System.out.println("units[i+1]= "+units[i+1]);
				Variable varObj = new Variable(tags[i+1],names[i+1],units[i+1],this,i);
				varObjects.addElement(varObj);
			}
			calculateVarStatistics();
		} catch (IOException e) {
			System.err.println(e.getMessage());
			e.printStackTrace();
		} finally {
			if (Source != null) 
				try { 
					Source.close(); 
				} catch (IOException e) { 
					System.err.println(e.getMessage());  
					e.printStackTrace(); 
				}		
		}	
		locked = false;
	}

/** Create a data series from a file. The file format is specified by 
	a file format object. */
	public void LoadViaFormat(URL url, DataSeriesFileFormat format, String dsName) throws MathException{

		String dataString;
		name = dsName;

		int dataCols = format.getDataColumn();
		int tagLine = format.getTagLine();
		int nameLine = format.getNameLine();
		int unitLine = format.getUnitLine();
		int[] ignoredRows = format.getIgnoredRows();

		int nonDataRows = ignoredRows.length;
		if(tagLine!=-1) {
			nonDataRows++;
		}
		if(nameLine!=-1) {
			nonDataRows++;
		}
		if(unitLine!=-1){
			nonDataRows++;
		}

		String[] tags = new String[dataCols+1];
		String[] names = new String[dataCols+1];
		String[] units = new String[dataCols+1];
		double[] dataRow = new double[dataCols];
		
		if ((format.getDateTimeColumn() != -1) || (format.getDateColumn() != -1) || (format.getTimeColumn() != -1)) {
			hasTimeStamps = true;	
			if(DEBUG.debugFlag) {
				System.out.println("This dataSeries has time stamps");
			}
		}
		else {
			hasTimeStamps = false;
			if(DEBUG.debugFlag) {
				System.out.println("This dataSeries has NO time stamps");
			}
		}
		
		Charset charset = Charset.defaultCharset();
		
		Reader streamReader1 = null;
		BufferedReader Source1 = null;
		
		Reader streamReader2 = null;
		BufferedReader Source2 = null;

		try {
			
			streamReader1 = new InputStreamReader(url.openStream(), charset);
	    	Source1 = new BufferedReader(streamReader1);		// try 65536, 32768, 16384, 8192 
			// find out approximate dimensions
			int totalrows=0;
			while (Source1.readLine() != null)
				totalrows++;
			totalrows -= nonDataRows;
			if(totalrows<=0) 
				throw new MathException("No data rows");
//System.out.println("Total rows = "+totalrows+", cols = "+dataCols);
			Matrix matrix = Matlib.createMatrix(totalrows, dataCols);
			long[] timeStampsArray = null;
			if(hasTimeStamps) 
				timeStampsArray = new long[totalrows];
			boolean regularRowCountMethod = true;  // for progress bar
			if(totalrows < 20) 
				regularRowCountMethod = false;
			int rr=0,r=0;
// Now, actually read the file
			streamReader2 = new InputStreamReader(url.openStream(), charset);
	    	Source2 = new BufferedReader(streamReader2);    // try 65536, 32768, 16384, 8192 
			while(true){
				dataString = Source2.readLine();
				if (dataString == null) {
					break;
				}
				if(r==tagLine) {
					format.readNonDataLine(dataString,tags);
				}else if(r==nameLine) {
					format.readNonDataLine(dataString,names);
				}else if(r==unitLine) {
					format.readNonDataLine(dataString,units);
				}else {  // check if this row is to be ignored
					boolean ignored = false;
					for(int j=0;j<ignoredRows.length;j++){
						if(r==ignoredRows[j]){
							ignored = true;
							break;
						}
					}
					if(!ignored) {
						long date = 0L;
						date = format.readDataLine(dataString,dataRow);
					//} catch (MathException me) {throw new MathException("Load failure on line "+r+": "+me.getMessage());}
						if(hasTimeStamps) {
							if(date == -1) {
								throw new MathException("Load failed! Could not parse date/time on line "+r+".");
							}else if(date != -2){
								timeStampsArray[rr] = date;
								for(int i=0;i<dataRow.length;i++){
									matrix.set(rr,i,dataRow[i]);
								}
								rr++;
							}
						} else { // no time stamps
							for(int i=0;i<dataRow.length;i++) {
								matrix.set(rr,i,dataRow[i]);
							}
							rr++;						
						}
					}
				}
				r++;
				if(regularRowCountMethod) {
					if((rr % (totalrows/20)) == 0) 
						informListeners();
				}
				else informListeners();
			}
			// now cut matrix down to actual size
			//System.out.println("r = "+r+" rr = "+rr);
			if(rr==totalrows) {
				this.data = matrix;
				this.timeStamps = timeStampsArray;
			} else {
				this.data = Matlib.createMatrix();
				Matlib.getRows(matrix,0,rr-1,this.data);
				Matlib.clear(matrix);
				Matlib.pack();
				if(hasTimeStamps){
					this.timeStamps = new long[rr];
				}
				System.arraycopy(timeStampsArray,0,this.timeStamps,0,rr);
				timeStampsArray = null;
			}
			if(tagLine == -1 && nameLine == -1){
				for(int i=1;i<=dataCols;i++){
					String variableName = makeVariableName();
					tags[i] = variableName;
					names[i] = variableName;
				}  		
			} else if(tagLine == -1){
				for(int i=1;i<=dataCols;i++){
					tags[i] = names[i];
				}  		
			} else if(nameLine == -1){
				for(int i=1;i<=dataCols;i++) {
					names[i] = tags[i];
				}  		
			}
			if(unitLine == -1){
				for(int i=1;i<=dataCols;i++){
					units[i] = "None";
				}
			}
			if(tags != null){
				CheckAndModifyForSameString(tags);
			}
			if(names != null){
				CheckAndModifyForSameString(names);
			}
			varObjects = new Vector(dataCols);
			for(int i=0;i<dataCols;i++){
//System.out.println("tags[i+1]= "+tags[i+1]);
//System.out.println("names[i+1]= "+names[i+1]);
//System.out.println("units[i+1]= "+units[i+1]);
				Variable varObj = new Variable(tags[i+1],names[i+1],units[i+1],this,i);
				varObjects.addElement(varObj);
			}
			calculateVarStatistics();
		} catch (IOException e) {
			System.err.println(e.getMessage());
			e.printStackTrace();
		} finally {
			closeSilently(Source1);
			closeSilently(Source2);
			closeSilently(streamReader1);
			closeSilently(streamReader2);
		}	
		locked = false;
	}


	private void CheckAndModifyForSameString(String[] names){


		for(int i=0;i<names.length;i++){
			if(names[i] == null){
				names[i] = "";
			}
		}
		for(int i=0;i<names.length;i++){
			boolean[] sameNameFlag = new boolean[names.length];
			boolean found = false;
			for(int j=i+1;j<names.length;j++){
				if(names[i].equals(names[j])){
					sameNameFlag[i] = true;
					sameNameFlag[j] = true;
					found = true;
				}
			}
			if(found){
				int c = 1;
				for(int j=i;j<names.length;j++){
					if(sameNameFlag[j]){
						String newName = names[j]+"_"+c;						
						while(true){
							boolean isNew = true;
							for(int k=0;k<names.length;k++){
								if(newName.equals(names[k])){
									isNew = false;
									break;
								}
							}
							c++;
							if(isNew){
								break;
							}
							newName = names[j]+"_"+c;
						}
						names[j] = newName;
					}
				}
			}
		}
	}
/** add listener.*/
	public void addListener(ProgressListener l) {
		if(itsListeners == null){
			itsListeners = new Vector();
		}
		itsListeners.addElement(l);
	}

/** inform listeners that an event has happened.*/
	private void informListeners() {
		if(itsListeners == null){
			return;
		}
		ProgressEvent e;
		ProgressListener l;
		e = new ProgressEvent();
		for (int i=0; i<itsListeners.size(); ++i) {
			l = (ProgressListener) itsListeners.elementAt(i);
			l.valueChanged(e);
		}
		//if(DEBUG.debug) System.out.println("informed listeners.");
	}

/** remove listener.*/
	public void removeListener(ProgressListener l) {
		if(itsListeners == null){
			itsListeners = new Vector();
		}else{
			itsListeners.removeElement(l);
		}
	}

/** Return the dataSource of this dataseries.*/
	public DataSource getDataSource() {
		if(dataSource == null){
			return null;
		}
		return dataSource;
	}

/** Get the data matrix out of this data series. */
	public Matrix getDataMatrix() {
		return data;
	}	 

/** Set the dataSource of this dataseries.*/
	public void setDataSource(DataSource dataSource) {
		this.dataSource = dataSource;
		if(dataSource != null)
			dataSourceHashCode = dataSource.hashCode();
	}

/** Get the name of this dataseries. */
	public String getName(){
		return this.name;
	}
	
/** Set the name of this dataseries. */
	public void setName(String dsName){
		this.name = dsName;
	}	
	
/** Return the comment of this dataseries.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this dataseries.*/
	public void setComment(String c){
		comment = c;
	}

/** Get the status of this timestamps. */
	public boolean getHasTimeStamps() {
		return hasTimeStamps;
	}
	
	/** Get the timeStamps of this dataseries. */
	public long[] getTimeStamps(){
		return this.timeStamps;
	}
	
/** Set the timeStamps of this dataseries. */
	public void setTimeStamps(long[] timeStamps){
		this.timeStamps = timeStamps;
		hasTimeStamps = true;
		if(dataSource == null){
			return;
		}
		if(dataSource instanceof RawDataSource){
			((RawDataSource)dataSource).setTimeStamps(this);
		}
	}	

/** Set the timeStamps of this dataseries. */
	public void setTimeStamps(long startTime, long interval){
		int row = getRow();
		timeStamps = new long[row];
		for(int i=0;i<row;i++){
			timeStamps[i] = startTime + interval*i;
		}
		hasTimeStamps = true;
		if(dataSource == null){
			return;
		}
		if(dataSource instanceof RawDataSource){
			((RawDataSource)dataSource).setTimeStamps(this);
		}
	}	

/** Return the row number of this data series.*/
	public int getRow(){
		if(data == null){
			return 0;
		}
		return data.getRows();
	}

/** Return the column number of this data series.*/
	public int getColumn(){
		if(data == null){
			return varObjects.size();
		}
		return data.getCols();

	}

/** Return the empty status of the data series.*/
	public boolean isEmpty(){
		return emptyData;
	}

/** Set the data series to empty one.*/
	public void emptyDataSeries(){
		Matlib.clear(data);
		data = null;
		emptyData = true;
		timeStamps = new long[0];
		locked = false;
		hasTimeStamps = false;
	}

/** Return the variable objects of this dataseries.*/
	public Vector getVarObjects(){
		return varObjects;
	}

/** Get variable index by name.*/
	public int getVarIndexByName(String varName){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			//System.out.println("getVarIndexByName:  var = "+varObj.toString());
			if(varObj.getName().equals(varName)){
				return i;
			}
		}
		return -1;
	}

/** Get variable index by variable object.*/
	public int getVarIndex(Variable varObj){
		int index = varObjects.indexOf(varObj);
		return index;
	}

/** Get variable index by tag.*/
	public int getVarIndexByTag(String varTag){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			if(varObj.getTag().equals(varTag))
				return i;
		}
		return -1;
	}

/** Get variable by name.*/
	public Variable getVarByName(String varName){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			if(varObj.getName().equals(varName))
				return varObj;
		}
		return null;
	}

/** Get variable by tag.*/
	public Variable getVarByTag(String varTag){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			if(varObj.getTag().equals(varTag))
				return varObj;
		}
		return null;
	}

/** Get variable by index.*/
	public Variable getVarByIndex(int index){
		if(index<varObjects.size())
			return (Variable)varObjects.elementAt(index);
		return null;
	}

/** Get variable array by name.*/
	public double[] getVarArrayByName(String varName){
		Variable varObj = getVarByName(varName);
		return getVarArray(varObj);
	}

/** Get variable Array by tag.*/
	public double[] getVarArrayByTag(String varTag){
		Variable varObj = getVarByTag(varTag);
		return getVarArray(varObj);
	}

/** Copy values from the data series to a double array */
	public double[] getVarArray(Variable varObj){
		if(emptyData) {
			return null;
		}
		int colIndex = varObjects.indexOf(varObj);
		if(colIndex != -1){
			int row = data.getRows();
			double[] dat = new double[row];
			for(int r=0;r<row;r++)
				dat[r] = data.get(r,colIndex);
			return dat;
		}
		return null;
	}

	
 /** Set the tag, name and unit of a variable with given infor.*/
	public void setVariableParameters(int col, String tag, String name,String unit) throws MathException {
		//System.out.println(" data.getCols()="+data.getCols());
		//System.out.println(" varObjects="+varObjects.size());
		if (col < 0 || col >= varObjects.size()) {
			throw new MathException("Column out of bounds: "+col);
		}
		Variable varObj = (Variable)varObjects.elementAt(col);
		varObj.setTag(tag);
		varObj.setName(name);
		varObj.setUnit(unit);
	}

	/** Set the values of a column */
	public void setColumnValues(int column, double[] v) throws MathException {
		if (column < 0 || column >= varObjects.size()) 
			throw new MathException("Column out of bounds: "+column);
		if(v.length != data.getRows()) 
			throw new MathException("Data length ("+v.length+") did not match row dimension ("+data.getRows()+")");
		for(int row=0;row<data.getRows();row++) {
			data.set(row,column,v[row]);
		}
	}

/** Set the value of the cell with given row and column.*/
	public void setValueAt(int row, int column, double v) throws MathException {
		data.set(row,column,v);
	}

 /** Get the value of the cell with given row and column.*/
	public double getValueAt(int row, int column) throws MathException {
		return data.get(row,column);
	}

/** Get column for a variable object, as a Matrix.*/
	public void getVarMatrix(Variable varObj, Matrix M) throws MathException {
		int colIndex = varObjects.indexOf(varObj);
		if(colIndex != -1) {
			Matlib.getColumn(data, colIndex, M);
		}else {
			throw new MathException("getVarMatrix: variable object was not a member of this data series");
		}
	}

/** Add empty columns of data to this data series. */
 	public void addColumns(int n) throws MathException {
		if(n==0) {
			return;
		}
		if(n<0) {
			throw new MathException("Negative argument in addColumns");
		}
		Matrix D = Matlib.createMatrix(data.getRows(),n);
		appendColumn(D);
		Matlib.clear(D);
	}

/** Add columns of data to this data series. */
 	public void appendColumn(Matrix D) throws MathException {
		if(this.timeStamps.length == 0) {
			int ns = D.getRows();
			this.timeStamps = new long[ns];
			for(int i=0;i<ns;i++)
			   this.timeStamps[i] = System.currentTimeMillis();
		} else if(this.timeStamps.length != D.getRows()){
			throw new MathException("Unequal number of rows");
		}
		int newCol = D.getCols();
		if(data.getCols() == 0){
			Matlib.copy(D,data);
		}
		else Matlib.appendColumns(data,D,data);
		int oldCol = varObjects.size();
		int column = data.getCols();
		// create variable objects with unique names
		for(int c=oldCol;c<column;c++){
			String varName = makeVariableName();
			Variable varObj = new Variable(varName,this,c);
			varObjects.addElement(varObj);
		}
	}

/** Append rows from another file.*/
	public boolean appendRows(String fileName, int format){
		return appendRows(null,fileName,format);
	}

/** Append rows from another file.*/
	public boolean appendRows(String directory, String fileName, int format){
//		DataSeries ds = new DataSeries(directory, fileName, format);
		DataSeries ds = new DataSeries();
		ds.Load(directory, fileName, format);
		return appendRows(ds);
	}

/** Append rows from another file.*/
	public boolean appendRows(String fileName, DataSeriesFileFormat format, 
		String dsName) {
		return appendRows(null,fileName, format,dsName);
	}

/** Append rows from another file.*/
	public boolean appendRows(String directory, String fileName, 
		DataSeriesFileFormat format, String dsName) {
		try{
//			DataSeries ds = new DataSeries(directory, fileName, format, dsName);
			DataSeries ds = new DataSeries();
			ds.LoadViaFormat(directory, fileName, format, dsName);
			return appendRows(ds);
		} catch(MathException evt){
			return false;
		}
	}

	public boolean appendRows(DataSeries sourceData){
//		System.out.println("this="+this.toString());
//		System.out.println("sourceData="+sourceData.toString());

		if(hasTimeStamps != sourceData.hasTimeStamps){
			return false;
		}
		if(dataSource == null){
			return false;
		}
		if(!(dataSource instanceof RawDataSource)){
			return false;
		}

		if(hasTimeStamps){		
			boolean later = true;
			int rowOld = this.timeStamps.length;
			long startTimeOld = this.timeStamps[0];
			long endTimeOld = this.timeStamps[rowOld-1];
			int rowNew =  sourceData.timeStamps.length;
			//System.out.println("rowNew="+rowNew);
			long startTimeNew = sourceData.timeStamps[0];
			long endTimeNew = sourceData.timeStamps[rowNew-1];

			if(endTimeOld< startTimeNew) 
				later = true;
			else if(startTimeOld > endTimeNew)
				later = false;
			else{
//				System.out.println("time error");
				return false;
			}

			int colOld = this.varObjects.size();
			int colNew = sourceData.varObjects.size();

			int newColumn = 0;
			int[] matchIndex = new int[colNew];
			for(int i=0;i<colNew;i++) {
				matchIndex[i] = -1;
			}

			for(int i=0;i<colNew;i++){
				for(int j=0;j<colOld;j++){
					if(sourceData.varObjects.elementAt(i).toString().equals(
						this.varObjects.elementAt(j).toString())){
						matchIndex[i] = j;
						break;
					}
				}
				if(matchIndex[i] == -1){
					newColumn++;
					matchIndex[i] = -newColumn;
				}
			}

			long[] longIndex = new long[rowNew+rowOld];
			for(int i=0;i<rowOld;i++){
				if(later)
					longIndex[i] = timeStamps[i];
				else
					longIndex[i+rowNew] = timeStamps[i];
			}
			for(int i=0;i<rowNew;i++){
				if(later)
					longIndex[i+rowOld] = sourceData.timeStamps[i];
				else
					longIndex[i] = sourceData.timeStamps[i];
			}
			
			if(newColumn>0){
				for(int i=0;i<colNew;i++){
					if(matchIndex[i]<0){
						String tag = ((Variable)sourceData.varObjects.elementAt(i)).getTag();
						String varName = ((Variable)sourceData.varObjects.elementAt(i)).getName();
						String unit = ((Variable)sourceData.varObjects.elementAt(i)).getUnit();
						Variable varObj = new Variable(tag,varName,unit,this,colOld-matchIndex[i]-1);
						varObjects.addElement(varObj);
					}
				}
			}
			Matrix newData = Matlib.createMatrix(rowNew+rowOld, colOld+newColumn);
			for(int r=0;r<rowOld;r++){
				if(later){
					for(int c=0;c<colOld+newColumn;c++){
						if(c<colOld){
							newData.set(r,c,data.get(r,c));
						}else{
							newData.set(r,c,Double.NaN);
						}
					}
				}else{
					for(int c=0;c<colOld+newColumn;c++){
						if(c<colOld){
							newData.set(r+rowNew,c,data.get(r,c));
						}else{
							newData.set(r+rowNew,c,Double.NaN);
						}
					}
				}
			}
			for(int r=0;r<rowNew;r++){
				if(later){
					for(int c=0;c<colOld+newColumn;c++){
						newData.set(r+rowOld,c,Double.NaN); 
					}
					for(int c=0;c<colNew;c++){
						if(matchIndex[c]>=0){
							newData.set(r+rowOld,matchIndex[c],sourceData.data.get(r,c));
						}else{
							newData.set(r+rowOld,colOld-matchIndex[c]-1,sourceData.data.get(r,c));
						}
					}
				}else{
					for(int c=0;c<colOld+newColumn;c++) {
						newData.set(r,c,Double.NaN); 
					}
					for(int c=0;c<colNew;c++){
						if(matchIndex[c]>=0){
							newData.set(r,matchIndex[c],sourceData.data.get(r,c));
						}else{
							newData.set(r,colOld-matchIndex[c]-1,sourceData.data.get(r,c));
						}
					}
				}
			}
			Matlib.clear(data);
			data = newData;
			long[] oldTimeStamps = timeStamps;
			timeStamps = longIndex;
			((RawDataSource)dataSource).modifyLabelMaskForDataSeries(this,oldTimeStamps,longIndex);
		}else{

			int rowOld = this.data.getRows();
			int rowNew = sourceData.data.getRows();
			int colOld = this.varObjects.size();
			int colNew = sourceData.varObjects.size();

			int newColumn = 0;
			int[] matchIndex = new int[colNew];
			for(int i=0;i<colNew;i++){
				matchIndex[i] = -1;
			}

			for(int i=0;i<colNew;i++){
				for(int j=0;j<colOld;j++){
					if(sourceData.varObjects.elementAt(i).toString().equals(
						this.varObjects.elementAt(j).toString())){
						matchIndex[i] = j;
						break;
					}
				}
				if(matchIndex[i] == -1){
					newColumn++;
					matchIndex[i] = -newColumn;  //wrong
				}
			}
			if(newColumn>0){
				for(int i=0;i<colNew;i++){
					if(matchIndex[i]<0){
						String tag = ((Variable)sourceData.varObjects.elementAt(i)).getTag();
						String varName = ((Variable)sourceData.varObjects.elementAt(i)).getName();
						String unit = ((Variable)sourceData.varObjects.elementAt(i)).getUnit();
						Variable varObj = new Variable(tag,varName,unit,this,colOld-matchIndex[i]-1);
						varObjects.addElement(varObj);
					}
				}
			}
			Matrix newData = Matlib.createMatrix(rowNew+rowOld, colOld+newColumn);
			for(int r=0;r<rowOld;r++){
				for(int c=0;c<colOld+newColumn;c++){
					if(c<colOld){
						newData.set(r,c,data.get(r,c));
					}else{
						newData.set(r,c,Double.NaN);
					}
				}
			}
			for(int r=0;r<rowNew;r++){
				for(int c=0;c<colOld+newColumn;c++){
					newData.set(r+rowOld,c,Double.NaN); 
				}
				for(int c=0;c<colNew;c++){
					if(matchIndex[c]>=0){
						newData.set(r+rowOld,matchIndex[c],sourceData.data.get(r,c));
					}else{
						newData.set(r+rowOld,colOld-matchIndex[c]-1,sourceData.data.get(r,c));
					}
				}
			}
			Matlib.clear(data);
			data = newData;
			((RawDataSource)dataSource).modifyLabelMaskForDataSeries(this);
		}
		return true;
	}

	public void setDataMatrix(Matrix M){
		if(M.getCols() != varObjects.size()){
			return;
		}
		Matlib.clear(data);
		data = M;
		if(timeStamps.length != M.getRows()){
			timeStamps = new long[0];
			hasTimeStamps = false;
		}
	}

/** Get the row index with given sample index.*/
	public int findRowAtTime(long x){ 
		int nData = timeStamps.length;
		if (x < timeStamps[0]){
			return -1;
		}else if (x > timeStamps[nData-1]){
			return nData - 1;
		}
		int lowerBound = 0;
		int upperBound = nData - 1;
		int midPt;
		while (upperBound - lowerBound - 1 > 0) {
			midPt = (upperBound + lowerBound)/2;  // TO DO -- improve by right shifting bits
			if (x >= timeStamps[midPt]){
				lowerBound = midPt;
			}
			else {
				upperBound = midPt;
			}
		}
		return lowerBound;
	}

/** Calculation the statistics for all the variables.*/
	public void calculateVarStatistics(){
		if(emptyData) {
			return;
		}
		int col = varObjects.size();
		double[] dat;
		for(int c=0;c<col;c++){
			Variable varObj = (Variable)varObjects.elementAt(c);
			int row = data.getRows();
			dat = new double[row];
			for(int r=0;r<row;r++)
				dat[r] = data.get(r,c);
			double[] stat = varObj.getStatistics();
			if(row == 0){
				for(int m=0;m<stat.length;m++){
					stat[m]=Double.NaN;
				}
			}else{
				double sum	= 0.0;
				double min	= Double.POSITIVE_INFINITY;
				double max	= Double.NEGATIVE_INFINITY;
				int validCount = 0;
				for(int r=0;r<row;r++){
					if(!Double.isNaN(dat[r])){
						sum += dat[r];
						if(dat[r]>max){
							max = dat[r];
						}
						if(dat[r]<min) {
							min = dat[r];
						}
						validCount++;
					}
				}
				if(Double.isInfinite(min) || Double.isInfinite(max)){
					min = Double.NaN;
					max = Double.NaN;
				}

				double mean = Double.NaN;
				if(validCount>0){
					mean = sum/validCount;
				}
				stat[0] = mean;
				stat[6] = max-min;
				stat[7] = min;
				stat[8] = max;
				stat[9] = sum;
				double err = Double.NaN;
				double vari = Double.NaN;
				double kurt = Double.NaN;
				double skew = Double.NaN;
				double std = Double.NaN; 
				if(validCount>0){
					err = 0;
					vari = 0;
					kurt = 0;
					skew = 0;
					for(int r=0;r<row;r++){
						if(!Double.isNaN(dat[r])){
							double dif = dat[r] - mean;
							err += Math.abs(dif);
							vari += dif*dif;
							skew += dif*dif*dif;
							kurt += dif*dif*dif*dif;
						}
					}
					err = err/validCount;
					int nn = validCount;
					if(validCount==1) {
						nn=2;
					}
					vari = vari/(nn-1);
					std = Math.sqrt(vari);
					skew = skew/(validCount*std*std*std);
					kurt = kurt/(validCount*std*std*std*std) - 3.0;
				}
				stat[2] = std;
				stat[3] = vari;
				stat[4] = kurt;
				stat[5] = skew;
				stat[1]	= DataUtilities.median(dat);
			}
			varObj.setStatistics(stat);
		}

	}

/** Save this data series into an ascii file. */
	public void saveAscii(String directory, String fileName,int type,
		SimpleDateFormat dateFormat, SimpleDateFormat timeFormat){ 

	//type:	ds=1; csv=2; txt=3. 
		File targetFile;
		if(directory==null)
			targetFile = new File(fileName);	
		else
			targetFile = new File(directory,fileName);
		
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
		BufferedWriter target = null;
		try { 
			outStream = new FileOutputStream(targetFile);
			streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			target = new BufferedWriter(streamWriter);

			if (type == 4 ){
				saveAsMatrixWithFiniteData(target);		
			}else{
				saveAsString(target,type,dateFormat,timeFormat);	
			}
			target.flush();
		}catch (Exception e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
		finally {
			closeSilently(target);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	} 

/** Save this data series into an ascii file in gnne data set format. */
	public void saveGNNEDataSet(String directory, String fileName,Vector usedNames,Vector outputNames){ 

		File targetFile;
		if(directory==null)
			targetFile = new File(fileName);	
		else
			targetFile = new File(directory,fileName);
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
		BufferedWriter target = null;
		try { 
			outStream = new FileOutputStream(targetFile);
			streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			target = new BufferedWriter(streamWriter);

			int cols = varObjects.size();
			Matrix inB = Matlib.zeros(1,cols);
			Matrix outB = Matlib.zeros(1,cols);
			for (int i=0;i<cols;i++){
				String varName = varObjects.elementAt(i).toString();
				if (usedNames.contains(varName)){
					if(outputNames.contains(varName)){
						outB.set(i,1.0);
					}else{
						inB.set(i,1.0);
					}
				}
			}
			Matrix inD = Matlib.createMatrix();
			Matrix outD = Matlib.createMatrix();
			Matrix B = Matlib.createMatrix();
			Matrix validData = Matlib.createMatrix();
			Matlib.findFiniteRows(data,B);
			Matlib.getRows(data,B,validData);
			int rr = validData.getRows();
			int counter = 0;
			long[] newTimeStamps = new long[rr];
			if(hasTimeStamps){
				for (int i=0;i<data.getRows();i++){
					if(B.get(i) > 0 ) {
						newTimeStamps[counter] = timeStamps[i];
						counter = counter + 1;
					}
				}
			}
			Matlib.getColumns(validData,outB, outD);
			Matlib.getColumns(validData,inB, inD);

			Matlib.clear(validData);
			Matlib.clear(B);
			Matlib.clear(outB);
			Matlib.clear(inB);
		
			String dataString =  "1; Version of this save/restore protocol for data sets \n";
			target.write(dataString,0,dataString.length());
			dataString = outD.getRows()+" ; Number of samples in this data-set \n";
			target.write(dataString,0,dataString.length());
			dataString = inD.getCols()+" ; ; Length of each input data vector \n";
			target.write(dataString,0,dataString.length());
			dataString = outD.getCols()+" ; Length of each output data vector \n";
			target.write(dataString,0,dataString.length());

			int row = outD.getRows();
			int col1 = inD.getCols();
			int col2 = outD.getCols();
			long baseTime = 10000;
			for(int r=0;r<row;r++){
				StringBuffer s = new StringBuffer((col1 + col2 + 2)*8);  // estimate size
				s.append(r);
				s.append(",");
				if(hasTimeStamps){
					s.append(newTimeStamps[r] / 1000.0);
					s.append(", OK, ");
				}else{
					s.append(baseTime+r*10);
					s.append(", OK, ");
				}
				
				for(int c=0;c<col1;c++)	{
		 			s.append(inD.get(r,c));
					s.append(",");
				}
				for(int c=0;c<col2-1;c++)	{
		 			s.append(outD.get(r,c));
					s.append(",");
				}
				s.append(outD.get(r,col2-1));
				s.append("\n");
 				dataString =  s.toString();
				target.write(dataString,0,dataString.length());
			}
			Matlib.clear(outD);
			Matlib.clear(inD);
		}catch (IOException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}catch (MathException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}catch (RuntimeException e){
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
		finally {
			closeSilently(target);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	} 

/** Save this data series into a binary file. */
	public void saveBinary(String fileName){
		saveBinary(null, fileName);
	}	
	
/** Save this data series into a binary file. */
	public void saveBinary(String directory, String fileName){
		String fName, oldName = this.name;
		if(fileName !=null){
			int dotInd = fileName.indexOf(".");
			if(dotInd == -1){
				this.name = fileName;
			}else{
				this.name = fileName.substring(0,dotInd);
			}
			fName = fileName;
		}else{
			 fName = this.name+".bds";
		}
		try {
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fName);	
			else
				sourceFile = new File(directory,fileName);
        // Create the necessary output streams to save the data.
			FileOutputStream fos = new FileOutputStream(sourceFile); // Save to file
			GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
			ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
			out.writeObject(this);      // Write the entire Vector of scribbles
			out.flush();                 // Always flush the output.
			out.close();                 // And close the stream.
		}catch (IOException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage()); 
			e.printStackTrace(); 
		}
		this.name = oldName;
	}

/** Initialize the transient attributes.*/
	public void initTransient(DataSource dataSource){
		this.dataSource =dataSource;
		dataSourceHashCode = dataSource.hashCode();
		initVarTransient();
	}

/** Initialize the transient attributes.*/
	public void initVarTransient(){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			varObj.initTransient(this);
		}
	}

	public void initTransient(Project p){
		Vector preps = p.getPreprocessors();
		for(int i=0;i<preps.size();i++){
			Preprocessor prep = (Preprocessor)preps.elementAt(i);
			//System.out.println("dataSourceHashCode="+dataSourceHashCode);
			//System.out.println("prep.hashCode()="+prep.getItsHashCode());
			if(dataSourceHashCode == prep.getItsHashCode()){
				dataSource = prep;
				break;
			}
		}
		dataSourceHashCode = dataSource.hashCode();
	}

	@Override
	public String toString() {
		return name;
	}
	public void saveAsMatrixWithFiniteData(BufferedWriter target) throws IOException,MathException {
	//type:	ds=1; csv=2; txt=3. 
		StringBuffer s = new StringBuffer(this.data.getCols()*8);  // estimate size
		String dataString;
		Matrix B = Matlib.createMatrix();
		Matrix Temp = Matlib.createMatrix();
		Matlib.findFiniteRows(data,B);
		Matlib.getRows(data,B,Temp);
		Matlib.clear(B);

		int row = Temp.getRows();
		int col = Temp.getCols();
		for(int r=0;r<row;r++){
			for(int c=0;c<col-1;c++)	{
		 		s.append(Temp.get(r,c));
				s.append(",");
			}
			s.append(Temp.get(r,col-1));
			s.append("\n");
 			dataString =  s.toString();
			target.write(dataString,0,dataString.length());
			s = new StringBuffer(this.data.getCols()*8);  // estimate size
		}
		Matlib.clear(Temp);
	}

	/** saveAsString modified by Brian Bush, Nov 12, 1998 */
	public void saveAsString(BufferedWriter target, int type,SimpleDateFormat dateFormat, SimpleDateFormat timeFormat) throws IOException {
	//type:	ds=1; csv=2; txt=3. 
		StringBuffer s = new StringBuffer(this.data.getCols()*8);  // estimate size
		String dataString;		
		if(hasTimeStamps){
			s.append("Time");
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		
		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getTag());	
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getTag());	
		s.append("\n");
		dataString =  s.toString();
		target.write(dataString,0,dataString.length());
		s = new StringBuffer(this.data.getCols()*8);  // estimate size
		if(hasTimeStamps){
			s.append("Time");
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		
		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getName());
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
  		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getName());
		s.append("\n");
 		dataString =  s.toString();
		target.write(dataString,0,dataString.length());
		s = new StringBuffer(this.data.getCols()*8);  // estimate size

		String dateTimeStr = dateFormat.toPattern()+" "+timeFormat.toPattern();
		if(hasTimeStamps){
			if(type == 2){
				s.append(dateTimeStr);
				s.append(",");
			}else if(type == 3){
				s.append(dateTimeStr);
				s.append("\t");
			}else{
				s.append("Millisecond");
				s.append("\t");
			}
		}

		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getUnit());
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getUnit());
		s.append("\n");
 		dataString =  s.toString();
		target.write(dataString,0,dataString.length());
		s = new StringBuffer(this.data.getCols()*8);  // estimate size
		int row = this.data.getRows();
		int col = this.data.getCols();
		for(int r=0;r<row;r++){
			if(hasTimeStamps){
				if(type == 2){
					s.append(dateFormat.format(new Date(timeStamps[r]))+" "+
						timeFormat.format(new Date(timeStamps[r])));
					s.append(",");
				}else if(type == 3){
					s.append(
						dateFormat.format(new Date(timeStamps[r]))+" "+
						timeFormat.format(new Date(timeStamps[r])));
					s.append("\t");
				}else{
					s.append(timeStamps[r]);
					s.append("\t");
				}
			}
			for(int c=0;c<col-1;c++)	{
		 		s.append(data.get(r,c));
				if(type == 2){
					s.append(",");
				}else{
					s.append("\t");
				}
			}
			s.append(data.get(r,col-1));
			s.append("\n");
 			dataString =  s.toString();
			target.write(dataString,0,dataString.length());
			s = new StringBuffer(this.data.getCols()*8);  // estimate size
		}
	}

	/** toStringForSave modified by Brian Bush, Nov 12, 1998 */
	public String toStringForSave(int type,SimpleDateFormat dateFormat, SimpleDateFormat timeFormat) throws IOException {
	//type:	ds=1; csv=2; txt=3. 
		StringBuffer s = new StringBuffer(this.data.getRows()*this.data.getCols()*8);  // estimate size
		
		if(hasTimeStamps){
			s.append("Time");
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		
		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getTag());	
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getTag());	
		s.append("\n");
		if(hasTimeStamps){
			s.append("Time");
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		
		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getName());
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
  		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getName());
		s.append("\n");

		String dateTimeStr = dateFormat.toPattern()+" "+timeFormat.toPattern();
		if(hasTimeStamps){
			if(type == 2){
				s.append(dateTimeStr);
				s.append(",");
			}else if(type == 3){
				s.append(dateTimeStr);
				s.append("\t");
			}else{
				s.append("Millisecond");
				s.append("\t");
			}
		}

		for(int c=0;c<varObjects.size()-1;c++){
			s.append(((Variable)varObjects.elementAt(c)).getUnit());
			if(type == 2){
				s.append(",");
			}else{
				s.append("\t");
			}
		}
		s.append(((Variable)varObjects.elementAt(varObjects.size()-1)).getUnit());
		s.append("\n");

		int row = this.data.getRows();
		int col = this.data.getCols();
		for(int r=0;r<row;r++){
			if(hasTimeStamps){
				if(type == 2){
					s.append(dateFormat.format(new Date(timeStamps[r]))+" "+
						timeFormat.format(new Date(timeStamps[r])));
					s.append(",");
				}else if(type == 3){
					s.append(
						dateFormat.format(new Date(timeStamps[r]))+" "+
						timeFormat.format(new Date(timeStamps[r])));
					s.append("\t");
				}else{
					s.append(timeStamps[r]);
					s.append("\t");
				}
			}
			for(int c=0;c<col-1;c++)	{
		 		s.append(data.get(r,c));
				if(type == 2){
					s.append(",");
				}else{
					s.append("\t");
				}
			}
			s.append(data.get(r,col-1));
			s.append("\n");
		}
		return s.toString();
	}

	public void truncateColumn(int numberOfCol) throws MathException{

		int cc = varObjects.size();
		for(int i=0;i<cc-numberOfCol;i++){
			Object obj = varObjects.lastElement();
			varObjects.removeElement(obj);
		}
		Matlib.getColumns(data,0,numberOfCol-1, data);
	}

	public void truncateRow(int startRow, int endRow) throws MathException{
		long[] newTs = new long[endRow-startRow+1];
		for(int r=0;r<newTs.length;r++){
			newTs[r] = timeStamps[r+startRow];
		}
		Matlib.getRows(data, startRow, endRow, data);
	}

	public void clearMemory(){
		boolean ispack = false;
		if(data.getRows()*data.getCols() > 10000){
			ispack = true;
		}
		Matlib.clear(data);
		if(ispack){
			Matlib.pack();
		}
		name = null;
		timeStamps = null; 
		varObjects.removeAllElements();
		varObjects = null;
	}

	@Override
	public Object clone() {
		Matrix newData = Matlib.createMatrix(data.getRows(),data.getCols());
		Matlib.copy(data,newData);
		DataSeries ds = new DataSeries(newData);
		ds.name = new String(name);
		for(int c=0;c<varObjects.size();c++){
			Variable varObj = (Variable)varObjects.elementAt(c);
			try {
 				ds.setVariableParameters(c,varObj.getTag(),varObj.getName(),varObj.getUnit());
			} catch (MathException e) {
				System.err.println(""+e); // should never end up here
			}
		}
		ds.hasTimeStamps = hasTimeStamps;
		ds.timeStamps = new long[timeStamps.length];
		for(int i=0;i<timeStamps.length;i++){
			ds.timeStamps[i] = timeStamps[i]; 
		}
		ds.comment = new String(comment);
		ds.dataSource = dataSource;
		if(itsListeners == null){
			itsListeners = new Vector();
		}else{
			for(int c=0;c<itsListeners.size();c++){
				ds.itsListeners.addElement(itsListeners.elementAt(c));
			}
		}
		ds.dataSourceHashCode = dataSourceHashCode;
		return ds;
	}


	private String makeVariableName() {
		if(dataSource==null) {
			variableCounter++;
			return "Var"+variableCounter;
		} else {
			Project project = dataSource.getProject();
			if(project==null) {
				variableCounter++;
				return "Var"+variableCounter;
			} else return project.makeUniqueNameForVariable();
		}
	}

	public DataSeries createScaledDataSeries(){
		DataSeries ds = (DataSeries)this.clone();
		return ds;
	}

	public void writeVariableStatistics(String outfile)throws IOException{
		File SourceFile = new File(outfile);
		FileOutputStream outStream = null;
	    Writer streamWriter = null;
	    BufferedWriter Source = null;
		try {
	        outStream = new FileOutputStream(SourceFile);
	        streamWriter = new OutputStreamWriter(outStream, Charset.defaultCharset());
			Source = new BufferedWriter(streamWriter);
			Source.write("Variable, MINIMUM,MAXIMUM,RANGE,MEAN,MEDIAN,STDDEV,VARIANCE,SKEWNESS,KURTOSIS");
			Source.newLine();
			int row = varObjects.size();
			for(int i=0;i<row;i++){
				Variable varObj = (Variable)varObjects.elementAt(i);
				Source.write(varObj.toString()+","+varObj.getMinValue()+","+varObj.getMaxValue()+","+varObj.getRange()+","+varObj.getMeanValue()+","+ varObj.getMedianValue()+","+varObj.getSTD()+","+varObj.getVariance()+","+varObj.getSkew()+","+varObj.getKurt());
				Source.newLine();
			}
		} finally {
			closeSilently(Source);
			closeSilently(streamWriter);
			closeSilently(outStream);
		}
	}

	public void resampleData(long startTime, long endTime, long interval){
		int newRow =(int)((endTime - startTime)/interval);
		int row = getRow();
		if(newRow > row) {
			return;
		}
		int col = getColumn();
		long[] ts = new long[newRow];
		for(int i=0;i<newRow;i++){
			ts[i] = startTime + interval*i;
		}
		Matrix newData = Matlib.createMatrix(newRow,col);
		int rcount = 0;
		boolean reachEnd = false;
		for(int r=0;r<newRow;r++){
			long t1 = ts[r];
			while (true){
				long t2 = timeStamps[rcount];
				if(t1 < t2){
					for(int c=0;c<col;c++) {
						newData.set(r,c,Double.NaN);
					}
					break;
				}else if (t1 == t2){
					for(int c=0;c<col;c++) {
						newData.set(r,c,data.get(rcount,c));
					}
					break;
				}else{
					rcount++;
					if(rcount >= row){
						reachEnd = true;
						break;
					}
				}				
			}
			if (reachEnd){
				for(int rr=r;rr<newRow;rr++){
					for(int c=0;c<col;c++) {
						newData.set(rr,c,Double.NaN);
					}
				}
				r = newRow;
				break;
			}
		}
		timeStamps = null;
		timeStamps = ts;
		Matlib.clear(data);
		data = newData;
	}
/** Initialize the hard upper and lower bounds of the variable.*/
	public void initializeHardBounds(){
		for(int i=0;i<varObjects.size();i++){
			Variable varObj = (Variable)varObjects.elementAt(i);
			varObj.initializeHardBounds();
		}
	}

/** Return arrays of finite data from this data series.*/
	public double[][] getFiniteData()throws MathException{
		Matrix B = Matlib.createMatrix();
		Matrix Temp = Matlib.createMatrix();
		Matlib.findFiniteRows(data,B);
		Matlib.getRows(data,B,Temp);
		double[][] dd = Matlib.create2DArray(Temp);
		Matlib.clear(B);
		Matlib.clear(Temp);
		return dd;
	}

/** Test whether the dataseries contains finiteData.*/
	public boolean hasFiniteData()throws MathException{
		Matrix B = Matlib.createMatrix();
		Matlib.findFiniteRows(data,B);
		double sum = Matlib.sum(B);
		Matlib.clear(B);
		if (sum > 0 ) {
			return true;
		}
		return false;
	}

}
