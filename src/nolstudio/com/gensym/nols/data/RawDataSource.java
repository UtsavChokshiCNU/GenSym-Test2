package com.gensym.nols.data;

import java.util.*;
import java.awt.Dimension;

import com.gensym.DEBUG;
/**
 * Gensym RawDataSource Class
 * @version     1.0 September 30, 1998
 * @author      Brian O. Bush, Gang Chen
 **/

public class RawDataSource extends DataSource{
	
	static final long serialVersionUID = 1L;

	private boolean selectStatus;

	private Hashtable pointLabelMask;
	private boolean undoFlag;
	private Hashtable pointLabelMaskCache;
	private Hashtable pointLabelMaskRedoCache;

	public RawDataSource() {
		super();
		name = "RawData";
		pointLabelMask = new Hashtable(); 
		pointLabelMaskCache = new Hashtable();
		undoFlag = false;
		pointLabelMaskRedoCache = new Hashtable();
   		selectStatus = true;
	}

	public RawDataSource(Project p) {
		super(p);
		name = "RawData";
		pointLabelMask = new Hashtable(); 
		pointLabelMaskCache = new Hashtable();
		undoFlag = false;
		pointLabelMaskRedoCache = new Hashtable();
   		selectStatus = true;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		RawDataSource cloned = (RawDataSource) super.clone();
		cloned.pointLabelMask = pointLabelMask == null ? null : (Hashtable) pointLabelMask.clone();
		cloned.pointLabelMaskCache = pointLabelMaskCache == null ? null : (Hashtable) pointLabelMaskCache.clone();
		cloned.pointLabelMaskRedoCache = pointLabelMaskRedoCache == null ? null : (Hashtable) pointLabelMaskRedoCache.clone();

		return cloned;
	}

/** Add a data series to this raw data. */	
	public void addDataSeries(DataSeries ds){
		//check name comflict
		if(getDataSeriesIndex(ds.getName()) != -1){
			RawDataEvent evt = new RawDataEvent(this,"errorAddDataSeries",ds);
			fireEvent(evt);
			return;
		}
		dataSeries.addElement(ds);
		ds.setDataSource(this);
		addLabelMaskForDataSeries(ds);
		if(DEBUG.debugFlag)
			System.out.println("add dataseries before event ");
		RawDataEvent evt = new RawDataEvent(this,"dataSeriesAdded",ds);
		fireEvent(evt);
	}

/** remove the data series from this data project. */	
	public void removeDataSeries(int dataSeriesIndex){
		DataSeries ds = (DataSeries)dataSeries.elementAt(dataSeriesIndex);
		removeDataSeries(ds);
	}

/** remove the data series from this data project. */	
	public void removeDataSeries(DataSeries ds){
		dataSeries.removeElement(ds);
		ds.setDataSource(null);
		removeLabelMaskForDataSeries(ds);
		RawDataEvent evt = new RawDataEvent(this,"dataSeriesRemoved",ds);
		fireEvent(evt);
	}

/** add default labels for new data series*/
	private void addLabelMaskForDataSeries(DataSeries ds){
		int lc = project.getNumberOfLabels();
		if( lc == 0){
			return;
		}
		int c = ds.getColumn();
		int r = ds.getRow();
		for(int i=0;i<c;i++){
			Vector labelMatrix = new Vector(lc);
			Vector labelMatrixCache = new Vector(lc);
			Variable varObj = ds.getVarByIndex(i);
			for(int j=0;j<lc; j++){
				boolean[] labelArray = new boolean[r];
				boolean[] labelArrayCache = new boolean[r];
				labelMatrix.addElement(labelArray);
				labelMatrixCache.addElement(labelArrayCache);
			}
			pointLabelMask.put(varObj,labelMatrix);
			pointLabelMaskCache.put(varObj,labelMatrixCache);
		}
	}

/** modify default labels for data series*/
	public void modifyLabelMaskForDataSeries(DataSeries ds,
		long[] oldTimes, long[] newTimes){
		int lc = project.getNumberOfLabels();
		if( lc == 0){
			return;
		}
		int c = ds.getColumn();
		int r = ds.getRow();
		for(int i=0;i<c;i++){
			Variable varObj = ds.getVarByIndex(i);
			Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
			Vector labelMatrixCache = (Vector)pointLabelMaskCache.get(varObj);
			for(int j=0;j<lc; j++){
				boolean[] labelArray = new boolean[r];
				boolean[] labelArrayCache = new boolean[r];
				boolean[] labelArrayOld = (boolean[])labelMatrix.elementAt(j);
				boolean[] labelArrayCacheOld = (boolean[])labelMatrixCache.elementAt(j);
				
				for(int rr=0;rr<r;rr++){
					int oldIndex = getOldIndex(rr,oldTimes,newTimes);
					if(oldIndex>0){
						labelArray[rr] = labelArrayOld[oldIndex];
						labelArrayCache[rr] = labelArrayCacheOld[oldIndex];
					}
				}
				labelMatrix.setElementAt(labelArray,j);
				labelMatrixCache.setElementAt(labelArrayCache,j);
			}
			pointLabelMask.put(varObj,labelMatrix);
			pointLabelMaskCache.put(varObj,labelMatrixCache);
		}
	}

	private int getOldIndex(int r,long[] oldTimes, long[] newTimes){
		if(r>=newTimes.length) {
			return -1;
		}
		long nt = newTimes[r];
		for(int i=0;i<oldTimes.length;i++){
			if(nt == oldTimes[i]) {
				return i;
			}
		}
		return -1;
	}


	public void modifyLabelMaskForDataSeries(DataSeries ds){
		int lc = project.getNumberOfLabels();
		if( lc == 0) {
			return;
		}
		int c = ds.getColumn();
		int r = ds.getRow();
		for(int i=0;i<c;i++){
			Variable varObj = ds.getVarByIndex(i);
			Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
			Vector labelMatrixCache = (Vector)pointLabelMaskCache.get(varObj);
			for(int j=0;j<lc; j++){
				boolean[] labelArray = new boolean[r];
				boolean[] labelArrayCache = new boolean[r];
				boolean[] labelArrayOld = (boolean[])labelMatrix.elementAt(j);
				boolean[] labelArrayCacheOld = (boolean[])labelMatrixCache.elementAt(j);
				for(int rr=0;rr<labelArrayOld.length;rr++){
					labelArray[rr] = labelArrayOld[rr];
					labelArrayCache[rr] = labelArrayCacheOld[rr];
				}
				labelMatrix.setElementAt(labelArray,j);
				labelMatrixCache.setElementAt(labelArrayCache,j);
			}
			pointLabelMask.put(varObj,labelMatrix);
			pointLabelMaskCache.put(varObj,labelMatrixCache);
		}
	}

 /** remove label mask for data series*/
	private void removeLabelMaskForDataSeries(DataSeries ds){
		int lc = project.getNumberOfLabels();
		if( lc == 0) {
			return;
		}
		int c = ds.getColumn();
		int r = ds.getRow();
		for(int i=0;i<c;i++){
			Variable varObj = ds.getVarByIndex(i);
			pointLabelMask.remove(varObj);
			pointLabelMaskCache.remove(varObj);
		}
	}


	protected void fireEvent(RawDataEvent evt){
		Vector targets;
		synchronized (this) {
			targets = (Vector) itsEventListeners.clone();
		}
		for (int i = 0; i < targets.size(); i++) {
			RawDataSourceListener rl = (RawDataSourceListener)targets.elementAt(i);
			if(evt.getIdentifier().equals("labelCategoryAdded")){
				rl.LabelCategoryAdded(evt);
			}else if(evt.getIdentifier().equals("labelCategoryRemoved")){
				rl.LabelCategoryRemoved(evt);
			}else if(evt.getIdentifier().equals("labelOrderChanged")){
				rl.LabelOrderChanged(evt);
			}else if(evt.getIdentifier().equals("labelNameChanged")){
				rl.LabelNameChanged(evt);
			}else if(evt.getIdentifier().equals("labelColorChanged")){
				rl.LabelColorChanged(evt);
			}else if(evt.getIdentifier().equals("dataPointsLabeled")){
				rl.DataPointsLabeled(evt);
			}else if(evt.getIdentifier().equals("dataSeriesAdded")){
				rl.DataSeriesAdded(evt);
			}else if(evt.getIdentifier().equals("dataSeriesRemoved")){
				rl.DataSeriesRemoved(evt);
			}
		}

	}

/** Reflect the change of label category of this project.*/
	public void addLabelCategory(){
		int lc = project.getNumberOfLabels();
		if(lc == 1){
			pointLabelMask.clear(); 
			int dc = getNumberOfDataSeries();
			for(int i=0;i<dc;i++){
				DataSeries ds = (DataSeries)dataSeries.elementAt(i);
				int rows = ds.getRow();				
				int cols = ds.getColumn();				
				Vector varObjs = ds.getVarObjects();
				for(int j=0;j<cols;j++){
					Variable varObj = (Variable)varObjs.elementAt(j);
					Vector labelMatrix = new Vector(1);
					boolean[] labelArray = new boolean[rows];
					labelMatrix.addElement(labelArray);
					pointLabelMask.put(varObj,labelMatrix);
				}
			}
			clonePointLabel(pointLabelMask, pointLabelMaskCache);
		}else{ 
			for (Enumeration enu = pointLabelMask.elements() ; enu.hasMoreElements() ;) {
				Vector labelMatrix = (Vector)enu.nextElement();
				int row = ((boolean[])labelMatrix.elementAt(0)).length;
				boolean[] labelArray = new boolean[row];
				labelMatrix.addElement(labelArray);
			}
			for (Enumeration enu = pointLabelMaskCache.elements() ; enu.hasMoreElements() ;) {
				Vector labelMatrixCache = (Vector)enu.nextElement();
				int row = ((boolean[])labelMatrixCache.elementAt(0)).length;
				boolean[] labelArrayCache = new boolean[row];
				labelMatrixCache.addElement(labelArrayCache);
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"labelCategoryAdded");
		fireEvent(evt);
	}

	public void removeLabelCategory(int labelIndex){

		if(project.getNumberOfLabels() == 0){
			pointLabelMask.clear();
			pointLabelMaskCache.clear();
		}else{
			for (Enumeration enu = pointLabelMask.elements() ; enu.hasMoreElements() ;) {
				Vector labelMatrix = (Vector)enu.nextElement();
				labelMatrix.removeElementAt(labelIndex);
			}
			for (Enumeration enu = pointLabelMaskCache.elements() ; enu.hasMoreElements() ;) {
				Vector labelMatrix = (Vector)enu.nextElement();
				labelMatrix.removeElementAt(labelIndex);
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"labelCategoryRemoved");
		fireEvent(evt);
	}

	public void changeLabelOrder(){
		RawDataEvent evt = new RawDataEvent(this,"labelOrderChanged");
		fireEvent(evt);
	}

	public void labelNameChanged(NolLabel lab){
		RawDataEvent evt = new RawDataEvent(this,"labelNameChanged",(Object)lab);
		fireEvent(evt);
	}

	public void labelColorChanged(NolLabel lab){
		RawDataEvent evt = new RawDataEvent(this,"labelColorChanged",(Object)lab);
		fireEvent(evt);
	}

/** Clone the pointlabel to cache or back.*/
	private void clonePointLabel(Hashtable labels, Hashtable newLabels){
		newLabels.clear();
		for (Enumeration enu = labels.keys() ; enu.hasMoreElements() ;) {
			Object key = enu.nextElement();
			Vector labelMatrix = (Vector)labels.get(key);
			int nlabels = labelMatrix.size();
			Vector newLabelMatrix = new Vector(nlabels);
			for(int j=0;j<nlabels;j++){
				try{
					boolean[] aa = (boolean[])labelMatrix.elementAt(j);
					boolean[] bb = (boolean[])aa.clone();
					newLabelMatrix.addElement(bb);
				}catch(Exception e){
					System.err.println("Non-Fatal exception: " + e.getMessage());
					e.printStackTrace();
				}
			}
			newLabels.put(key,newLabelMatrix);
		}
	}

/** undo the last labeling action.*/
	public synchronized void undoLabeling(){
		clonePointLabel(pointLabelMask, pointLabelMaskRedoCache);
		clonePointLabel(pointLabelMaskCache, pointLabelMask);
		undoFlag = true;
		Vector vars = new Vector(0);
		for(int i=0;i<dataSeries.size();i++){
			DataSeries ds = (DataSeries)dataSeries.elementAt(i);
			Vector varObjs = ds.getVarObjects();
			for(int j=0;j<varObjs.size();j++){
				vars.addElement(varObjs.elementAt(j));
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",vars);
		fireEvent(evt);
	}

 /** redo the last labeling action.*/
	public synchronized void redoLabeling(){
		if(!undoFlag){
			return;
		}
		clonePointLabel(pointLabelMaskRedoCache, pointLabelMask);
		undoFlag = false;
		Vector vars = new Vector(0);
		for(int i=0;i<dataSeries.size();i++){
			DataSeries ds = (DataSeries)dataSeries.elementAt(i);
			Vector varObjs = ds.getVarObjects();
			for(int j=0;j<varObjs.size();j++){
				vars.addElement(varObjs.elementAt(j));
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",vars);
		fireEvent(evt);
	}


 /** Label the point for given variable.*/
	public synchronized void labelPoints(int labelNumber, Variable varObj, 
		boolean newLabel){
		if(project.getNumberOfLabels() == 0){
			return;
		}
		undoFlag = false;
		clonePointLabel(pointLabelMask,pointLabelMaskCache);
		Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
		boolean[] labelArray = (boolean[])labelMatrix.elementAt(labelNumber);
		for(int i=0;i<labelArray.length;i++){
			labelArray[i] = newLabel;
		}
		Vector vars = new Vector(1);
		vars.addElement(varObj);
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",vars);
		fireEvent(evt);
	}

 /** Label the point for given variable at given points.*/
	public synchronized void labelPoints(int labelNumber, Variable varObj, int[] rowNumbers, 
		boolean newLabel){
		if(project.getNumberOfLabels() == 0) {
			return;
		}
		undoFlag = false;
		clonePointLabel(pointLabelMask,pointLabelMaskCache);
		Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
		boolean[] labelArray = (boolean[])labelMatrix.elementAt(labelNumber);
		for(int i=0;i<rowNumbers.length;i++){
			labelArray[rowNumbers[i]] = newLabel;
		}
		Vector vars = new Vector(1);
		vars.addElement(varObj);
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",vars);
		fireEvent(evt);
	}

 /** Label the point for given variable at given points.*/
	public synchronized void labelPoints(int labelNumber, Hashtable varObjsAndRowNumber,
		boolean newLabel){
		if(project.getNumberOfLabels() == 0){
			return;
		}
		undoFlag = false;
		clonePointLabel(pointLabelMask,pointLabelMaskCache);
		Vector vars = new Vector(1);
		for (Enumeration enu = varObjsAndRowNumber.keys() ; enu.hasMoreElements() ;) {
			Object key = enu.nextElement();
			vars.addElement(key);
			Vector labelMatrix = (Vector)pointLabelMask.get(key);
			Object content = varObjsAndRowNumber.get(key);
			boolean[] labelArray = (boolean[])labelMatrix.elementAt(labelNumber);
			if(content instanceof Dimension){
 				Dimension dim  = (Dimension)content;
				for(int i=dim.width;i<=dim.height;i++){	//dim.width: start row number; dim.height: end row number
					labelArray[i] = newLabel;
				}
			}else if(content instanceof int[]){
				int[] rowNumbers  = (int[])varObjsAndRowNumber.get(key);
				for(int i=0;i<rowNumbers.length;i++){
					labelArray[rowNumbers[i]] = newLabel;
				}
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",vars);
		fireEvent(evt);
	}

 /** Label the point for given variable at given ranges.*/
	public synchronized void labelPoints(int labelNumber, Vector varObjs,
		int row1,int row2, boolean newLabel){
		if(project.getNumberOfLabels() == 0){
			return;
		}
		if(varObjs.isEmpty()) 
			return;
		undoFlag = false;
		clonePointLabel(pointLabelMask,pointLabelMaskCache);
		for(int i=0;i<varObjs.size();i++){
			Variable varObj = (Variable)varObjs.elementAt(i);
			Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
			boolean[] labelArray = (boolean[])labelMatrix.elementAt(labelNumber);
			for(int j=row1;j<=row2;j++)
				labelArray[j] = newLabel;
		}
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",varObjs);
		fireEvent(evt);
	}

 /** Label the point for given variable at given points.*/
	public synchronized void labelPoints(int labelNumber, Vector varObjs, int[] rowNumbers, 
		boolean newLabel){
		if(project.getNumberOfLabels() == 0){
			return;
		}
		if(varObjs.isEmpty()) 
			return;
		undoFlag = false;
		clonePointLabel(pointLabelMask,pointLabelMaskCache);

		for(int i=0;i<varObjs.size();i++){
			Variable varObj = (Variable)varObjs.elementAt(i);
			Vector labelMatrix = (Vector)pointLabelMask.get(varObj);
			boolean[] labelArray = (boolean[])labelMatrix.elementAt(labelNumber);
			for(int j=0;j<rowNumbers.length;j++){
				labelArray[rowNumbers[j]] = newLabel;
			}
		}
		RawDataEvent evt = new RawDataEvent(this,"dataPointsLabeled",varObjs);
		fireEvent(evt);
	}

/** Return the label matrix of given variable.*/
	public boolean[][] getLabelMatrix(Variable varObj) {
		Vector labelVector = (Vector)pointLabelMask.get(varObj);
		if(labelVector == null){
			return null;
		}
		int n =  labelVector.size();
		boolean[][] labelMatrix =  new boolean[n][];
		for(int i=0;i<n;i++)
			labelMatrix[i] = (boolean[])labelVector.elementAt(i);
		return labelMatrix;
	}

 /** Return the label matrix of given point.*/
	public boolean[] getPointLabels(Variable varObj, int rowNumber) {
		boolean[][] lm = getLabelMatrix(varObj);
		if(lm == null){
			return new boolean[project.getNumberOfLabels()];
		}
		boolean[] ls = new boolean[lm.length];
		for(int i=0;i<lm.length;i++)
			ls[i] = lm[i][rowNumber];
		return ls;
	}

/** Return the label array of given variable.*/
	public boolean[] getLabelArray(NolLabel label, Variable varObj){
		Vector labelVector = (Vector)pointLabelMask.get(varObj);
		int labelNumber = project.getLabelIndex(label);
		return (boolean[])labelVector.elementAt(labelNumber);
	}

/** Return the selection status for labeling.*/
	public boolean getSelectStatus(){
		return selectStatus;
	}

/** Set the selection status for labeling.*/
	public void setSelectStatus(boolean flag){
		selectStatus = flag;
	}

/** Propagate time stamps change of the dataseries. */
	public void setTimeStamps(DataSeries ds){
		RawDataEvent evt = new RawDataEvent(this,"setTimeStamps",ds);
		fireEvent(evt);
	  //Temp code gchen 1/21/99
		Vector preps = project.getPreprocessors();
		for(int i=0;i<preps.size();i++){
			Preprocessor prep = (Preprocessor)preps.elementAt(i);
			prep.setTimeStamps(ds);
		}
	}	

}
