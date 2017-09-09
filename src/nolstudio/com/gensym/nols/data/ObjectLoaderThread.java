package com.gensym.nols.data;
/**
 *		Gensym ObjectLoaderThread Class.
 *		This class is extended from object.class
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
import java.io.Serializable;
import java.lang.reflect.Method;
import java.net.URL;
import java.util.Vector;
import java.util.zip.GZIPInputStream;

import com.gensym.math.MathException;
import com.gensym.nols.dlg.NolProgressBarDialog;
import com.gensym.nols.main.NolMainFrame;

public class ObjectLoaderThread implements Runnable, Cloneable, Serializable {
 	static final long serialVersionUID = 1L;

	private NolMainFrame frame;
	private NolProgressBarDialog progressDialog;
	private Object versionManager;  
	private Class versionManagerClass;
	private String fileName;
	private String dirName;
	private String objName;
	private String objComment;
	private DataSeries appendedDataSeries;
	private DataSeriesFileFormat format;
	private URL url;
	private int type;

	private static final int LOAD_TYPE_DS = 0;
	private static final int LOAD_TYPE_BDS = 1;
	private static final int LOAD_TYPE_PUREMATRIX = 2;
	private static final int LOAD_TYPE_FROMFORMAT = 3;

	private static final int URL_LOAD_TYPE_DS = 20;
	private static final int URL_LOAD_TYPE_BDS = 21;
	private static final int URL_LOAD_TYPE_PUREMATRIX = 22;
	private static final int URL_LOAD_TYPE_FROMFORMAT = 23;

	private static final int APPEND_TYPE_DS = 10;
	private static final int APPEND_TYPE_BDS = 11;
	private static final int APPEND_TYPE_PUREMATRIX = 12;
	private static final int APPEND_TYPE_FROMFORMAT = 13;

	private static final int LOAD_PROJECT = 100;

    private static final String LOADINGTEXT = "ObjectLoader_LoadingText";
	private static final boolean DEBUG = false;

	public ObjectLoaderThread(NolMainFrame frame){
		this.frame = frame;
		type = 0;
		fileName = "";
		dirName = "";
		objName = "";
		objComment = "";
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		ObjectLoaderThread cloned = (ObjectLoaderThread) super.clone();
		cloned.appendedDataSeries = appendedDataSeries == null ? null : (DataSeries) appendedDataSeries.clone();
		cloned.format = format == null ? null : (DataSeriesFileFormat) format.clone();

		return cloned;
	}


	@Override
	public void run (){
//		frame.setWaitCursor(true);
		switch (type){
		case LOAD_TYPE_DS :{
			if(DEBUG){
				System.out.println("case 0");
			}
			DataSeries ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			progressDialog = new NolProgressBarDialog(frame, "File Loading Progress", 
				frame.getNolResourceString(LOADINGTEXT), 20);
			ds.addListener(progressDialog);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 
			ds.Load(dirName, fileName, 0);		//*****
			ds.setComment(objComment);
			progressDialog.dispose();			//*****
			if(frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case LOAD_TYPE_BDS:{
			if(DEBUG) {
				System.out.println("case 1");
			}
			DataSeries ds = null;
			try {
				String dsN = fileName;
				int dotInd = fileName.indexOf(".");
				if(dotInd != -1){
					dsN = fileName.substring(0,dotInd);
				}
				File sourceFile = new File(dirName, fileName);	
				FileInputStream fis = new FileInputStream(sourceFile); // Read from file
				GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
				ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
			// Read in an object.  It should be a vector of scribbles
				VersionManagerForDataSeries versionForData = (VersionManagerForDataSeries)in.readObject();
				in.close(); // Close the stream.
				ds = versionForData.getDataSeries();
				ds.setName(dsN);
				Vector varObjects = ds.getVarObjects();
				for(int i=0;i<varObjects.size();i++){
					Variable varObj = (Variable)varObjects.elementAt(i);
					varObj.initTransient(ds);
				}
			} catch (Exception e) {
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
			if(ds != null && frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case LOAD_TYPE_PUREMATRIX:{
			if(DEBUG) {
				System.out.println("case 2");
			}
			DataSeries ds;
			ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			ds.Load(dirName, fileName, 2);
			ds.setComment(objComment);
			if(frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case LOAD_TYPE_FROMFORMAT:{
			if(DEBUG) {
				System.out.println("case 3");
			}
			DataSeries ds;
			ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			progressDialog = new NolProgressBarDialog(frame, "File Loading Progress", 
				frame.getNolResourceString(LOADINGTEXT), 20);
			ds.addListener(progressDialog);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 
			try{
				ds.LoadViaFormat(dirName, fileName, format, objName);
				ds.setComment(objComment);
				progressDialog.dispose();			//*****
				if(frame != null)
					frame.finishAddDataSeries(ds);
			} catch(MathException evt){
				progressDialog.dispose();
				frame.failLoadDataSeries(evt.getMessage());
			}
			break;
			   }
		case APPEND_TYPE_DS:{
			if(dirName == null){
				if(appendedDataSeries.appendRows(fileName,0)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);
				}
			}else{
				if(appendedDataSeries.appendRows(dirName, fileName,0)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);				
				}
			}
			break;
			   }
		case APPEND_TYPE_BDS:{
			if(dirName == null){
				if(appendedDataSeries.appendRows(fileName,1)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);
				}
			}else{
				if(appendedDataSeries.appendRows(dirName, fileName,1)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);				
				}
			}
			break;
			   }
		case APPEND_TYPE_PUREMATRIX:{
			if(dirName == null){
				if(appendedDataSeries.appendRows(fileName,2)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);
				}
			}else{
				if(appendedDataSeries.appendRows(dirName, fileName,2)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);				
				}
			}
			break;
			   }
		case APPEND_TYPE_FROMFORMAT:{
 			if(dirName == null){
				if(appendedDataSeries.appendRows(fileName,format,objName)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);
				}
			}else{
				if(appendedDataSeries.appendRows(dirName, fileName,format,objName)){
					if(frame != null){
						frame.finishAppendDataSeries(appendedDataSeries);
					}
				}else{
					frame.failLoadDataSeries("Failed in appending "+fileName);	
				}
			}
			break;
			   }
		case URL_LOAD_TYPE_DS:{
			if(DEBUG) {
				System.out.println("case 20");
			}
			DataSeries ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			progressDialog = new NolProgressBarDialog(frame, "File Loading Progress", 
				frame.getNolResourceString(LOADINGTEXT), 20);
			ds.addListener(progressDialog);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 

			ds.Load(url, 0);		//*****
			ds.setComment(objComment);
			progressDialog.dispose();			//*****
			if(frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case URL_LOAD_TYPE_BDS:{
			if(DEBUG) {
				System.out.println("case 21");
			}
			DataSeries ds = null;
			try {
				GZIPInputStream gzis = new GZIPInputStream(url.openStream());     // Uncompress
				ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
			// Read in an object.  It should be a vector of scribbles
				VersionManagerForDataSeries versionForData = (VersionManagerForDataSeries)in.readObject();
				in.close(); // Close the stream.
				ds = versionForData.getDataSeries();
				Vector varObjects = ds.getVarObjects();
				for(int i=0;i<varObjects.size();i++){
					Variable varObj = (Variable)varObjects.elementAt(i);
					varObj.initTransient(ds);
				}
			} catch (Exception e) {
				System.err.println("Non-Fatal exception: " + e.getMessage());
				e.printStackTrace();
			}
			if(ds != null && frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case URL_LOAD_TYPE_PUREMATRIX:{
			if(DEBUG) {
				System.out.println("case 22");
			}
			DataSeries ds;
			ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			ds.Load(url, 2);

			ds.setComment(objComment);
			if(frame != null)
				frame.finishAddDataSeries(ds);
			break;
			   }
		case URL_LOAD_TYPE_FROMFORMAT:{
			if(DEBUG) {
				System.out.println("case 3");
			}
			DataSeries ds;
			ds = new DataSeries();
			ds.setDataSource(frame.getProject().getRawDataSource());
			progressDialog = new NolProgressBarDialog(frame, "File Loading Progress", 
				frame.getNolResourceString(LOADINGTEXT), 20);
			ds.addListener(progressDialog);
			progressDialog.setLocation(300,300);
			progressDialog.setSize(250,150);
			progressDialog.setVisible(true);
			progressDialog.setThread(Thread.currentThread()); 

			try{
				ds.LoadViaFormat(url, format, objName);
				ds.setComment(objComment);
				progressDialog.dispose();			//*****
				if(frame != null)
					frame.finishAddDataSeries(ds);
			} catch(MathException evt){
				progressDialog.dispose();
				frame.failLoadDataSeries(evt.getMessage());
			}
			break;
			   }
		case LOAD_PROJECT:{
			try {
				File sourceFile;
				if(dirName==null)
					sourceFile = new File(fileName);	
				else
					sourceFile = new File(dirName,fileName);
//System.out.println("source="+ sourceFile);
				FileInputStream fis = new FileInputStream(sourceFile); // Read from file
				GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
				ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
        // Read in an object.  It should be a vector of scribbles
//System.out.println("start read");
				versionManager = in.readObject();
				versionManagerClass = versionManager.getClass();
				in.close(); // Close the stream
				Method method = versionManagerClass.getMethod("getProject",new Class[] {});
				frame.finishOpenProject((Project2) method.invoke(versionManager,new Object[] {}));
			} catch(ClassNotFoundException e) {
				// error message assumes it was the version manager class that wasn't found,
				// because JLT didn't load it due to lack of an authorization
				// However, this message might be misleading if something else goes wrong,
				// for example, an unknown class in the the serialized project
				frame.failLoadProject("You must have a valid authorization to load an existing project.");
//				frame.setWaitCursor(false);
			} catch (Exception e) {
				e.printStackTrace();
				frame.failLoadProject("Failed to load project from "+fileName+". Error:"+e.getMessage());
//				frame.setWaitCursor(false);
			}
			break;
			}
		  default:
		}
//		frame.setWaitCursor(false);
	}

	public void setFileName(String file){
		fileName = file;
	}
	public void setObjName(String n){
		objName = n;
	}

	public void setObjComment(String n){
		objComment = n;
	}

	public void setDirName(String dir){
		dirName = dir;
	}

	public void setType(int t){
		type = t;
	}

	public Project getProject() {
		try {
			Method method = versionManagerClass.getMethod("getProject",new Class[] {});
			return (Project) method.invoke(versionManager,new Object[] {});
		} catch (Exception e) {
			return null;
		}
		//return versionManager.getProject();
	}

	public void setAppendedDataSeries(DataSeries ds){
		appendedDataSeries = ds;
	}

	public void setFileFormat(DataSeriesFileFormat format){
		this.format = format;
	}

	public void setURL(URL url){
		this.url = url;
	}
}