package com.gensym.nols.data;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;

/** Preprocessor class */
public class Preprocessor extends DataSource implements RawDataSourceListener, IPreprocessor, Cloneable, Serializable{
	static final long serialVersionUID = 1L;
	private static int preprocessorInstanceCount = 0;
	private Vector varNames = null;   // input variable names
	private Vector varTags = null;	   // input variable tags
	private Vector derivedVarNames = null;
	private Vector allVarNames = null;
	private ViewFilter viewFilter = null;
	private int updatedIndex;  //0: new data not through formulas; nt: through formulas; -1 old data not through formulas.
	private Vector formulas;
	private int itsHashCode;
	private boolean hasTimeStamps;

/** Create a null Preprocessor with no argument */
	public Preprocessor() {
		super();
		name = "Preprocessor" + preprocessorInstanceCount;
		preprocessorInstanceCount++;
		varNames = new Vector(0,10);
		varTags = new Vector(0,10);
		formulas = new Vector(0,10);
		derivedVarNames = new Vector(0,10);
		allVarNames = new Vector(0,10);
		updatedIndex = 0;  //Start from 0.
		viewFilter = new ViewFilter();  // default view filter
		itsHashCode = hashCode();
		hasTimeStamps = true;
	}

/** Create a data Preprocessor from a project given name. */
	public Preprocessor(String name, Project p, Vector varObjs, ViewFilter filter) throws MathException {
		this();
		this.name = name;
		preprocessorInstanceCount--;
		initialize(p, varObjs, filter);
	}

	/** create a preprocessor that is identical to another, except lacking data */
	public Preprocessor(Preprocessor p) {
		this();
		name = p.name;
		comment = p.comment;
		dataSeries = null;
		varNames = (Vector) p.varNames.clone();
		varTags = (Vector) p.varTags.clone();
		derivedVarNames = (Vector) p.derivedVarNames.clone();
		allVarNames = (Vector) p.allVarNames.clone();
		viewFilter = null;  // need to make viewFilter cloneable!!
		updatedIndex = 0;
		formulas = (Vector) p.formulas.clone();
		hasTimeStamps = p.hasTimeStamps;
		itsHashCode = hashCode();
		itsEventListeners = new Vector();
	}

	/** create a preprocessor that is identical to another, except lacking data */
	public Preprocessor(String n, String c, Vector varNames, Vector varTags, 
		Vector derivedVarNames, Vector formulas, boolean hasTimeStamps) {
		this();
		this.name = n;
		comment = c;
		dataSeries = null;
		this.varNames = (Vector) varNames.clone();
		this.varTags = (Vector) varTags.clone();
		this.derivedVarNames = (Vector) derivedVarNames.clone();
		allVarNames = (Vector) varNames.clone();
		for(int i=0;i<derivedVarNames.size();i++){
			allVarNames.addElement(	derivedVarNames.elementAt(i));
		}
		viewFilter = null;  // need to make viewFilter cloneable!!
		updatedIndex = 0;
		this.formulas = (Vector)formulas.clone();
		this.hasTimeStamps = hasTimeStamps;
		itsHashCode = hashCode();
		itsEventListeners = new Vector();
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		Preprocessor cloned = (Preprocessor) super.clone();
		
		cloned.viewFilter = viewFilter == null ? null : (ViewFilter) viewFilter.clone();
		
		cloned.formulas = formulas == null ? null : (Vector) formulas.clone();
		cloned.allVarNames = allVarNames == null ? null : (Vector) allVarNames.clone();
		cloned.derivedVarNames = derivedVarNames == null ? null : (Vector) derivedVarNames.clone();
		cloned.varNames = varNames == null ? null : (Vector) varNames.clone();
		cloned.varTags = varTags == null ? null : (Vector) varTags.clone();
		
		return cloned;
	}
	
/** Initialize the properties of a new Preprocessor.*/
	private void initialize(Project p, Vector varObjs, ViewFilter filter) throws MathException {
		viewFilter = filter;
		project = p;
		p.getRawDataSource().addListener(this);  // preprocessor listens for changes in raw data
		projectHashCode = project.hashCode();
		updatedIndex = 0;  // Start from formula 0.
		hasTimeStamps = ((Variable)varObjs.elementAt(0)).getDataSeries().getHasTimeStamps();
		dataSeries = new Vector();  // attribute inherited from data source
		createProcessedDataSeries(varObjs, dataSeries);  // initializes data in the data source
		for(int i=0;i<varObjs.size();i++){
			Variable varObj = (Variable)varObjs.elementAt(i);
			varNames.addElement(varObj.toString());
			varTags.addElement(varObj.getTag());
		}
		verifyFormulaList(formulas); //Gchen: Initializes the all variable names and derived name.
		project.addPreprocessor(this);
		pushProcessedDataToProject(dataSeries);
	}

	/** Create the processed data series for the preprocessor */
	private void createProcessedDataSeries(Vector varObjs, Vector processedData) throws MathException {
		Hashtable varIndexHash = getVarIndexHash(varObjs);
		processedData.removeAllElements(); // maybe force some garbage collection here?
		Enumeration dskeys = varIndexHash.keys();
		while(dskeys.hasMoreElements()) {	
			DataSeries ds = (DataSeries) dskeys.nextElement();
			Vector vars = (Vector)varIndexHash.get(ds);
			boolean[][] nanMark = getNaNMarkForVariables(ds,vars);
			DataSeries ds1 = applyLabelFilter(ds,vars,nanMark);  // creates data series
			processedData.addElement(ds1);
			ds1.calculateVarStatistics();
			ds1.setDataSource(this);
		}
	}

	private Hashtable getVarIndexHash(Vector varObjs){
		Hashtable varIndexHash = new Hashtable();
		for(int i=0;i<varObjs.size();i++){
			Variable varObj = (Variable)varObjs.elementAt(i);
			DataSeries ds = varObj.getDataSeries();
			if(varIndexHash.containsKey(ds)){
				Vector vars = (Vector)varIndexHash.get(ds);
				if(!vars.contains(varObj))
					vars.addElement(varObj);
			}else{
				Vector vars = new Vector();
				vars.addElement(varObj);
				varIndexHash.put(ds,vars);
			}
		}
		return varIndexHash;
	}

/** Return the mark matrix.*/
	private boolean[][] getNaNMarkForVariables(DataSeries ds, Vector vars) {
		int col = vars.size();
		int row = ds.getRow();
		boolean[][] nanMarks = new boolean[col][row];
		if(project==null){
			return nanMarks;
		}
		RawDataSource rawData  =project.getRawDataSource();
		if(rawData==null){
			return nanMarks;
		}
		if(viewFilter==null){
			return nanMarks;
		}
		for(int c=0;c<col;c++){
			Variable varObj = (Variable)vars.elementAt(c);
  			boolean[][] labelMatrix = rawData.getLabelMatrix(varObj);
			for(int k=0;k<row;k++){
				if(!viewFilter.isVisible(labelMatrix,k)){
					nanMarks[c][k] = true;
				}
			}
		}
		return nanMarks;
	}

	private int getRowNaNMark(boolean[][] nanMark, boolean[] rowNaNMark){
		int nanCount = 0;
		int row = rowNaNMark.length;
		int col = nanMark.length;
		for(int r=0;r<row;r++){
			rowNaNMark[r] = true;
			for(int c=0;c<col;c++){
				if(!nanMark[c][r]){
					rowNaNMark[r] = false;
					break;
				}
			}
			if(rowNaNMark[r]){
				nanCount++;
			}
		}
		return nanCount;
	}

	private int getColumnNaNMark(boolean[][] nanMark, boolean[] columnNaNMark){
		int nanCount = 0;
		int col = columnNaNMark.length;
		int row = nanMark[0].length;
		for(int c=0;c<col;c++){
			columnNaNMark[c] = true;
			for(int r=0;r<row;r++){
				if(!nanMark[c][r]){
					columnNaNMark[c] = false;
					break;
				}
			}
			if(columnNaNMark[c]){
				nanCount++;
			}
		}
		return nanCount;
	}

	private DataSeries applyLabelFilter(DataSeries ds, Vector varObjs, boolean[][] nanMark) throws MathException {
		int col = varObjs.size();
		int row = ds.getRow();
		boolean[] rowNaNMark = new boolean[row];
		boolean[] columnNaNMark = new boolean[col];
		int nanRowCount = getRowNaNMark(nanMark,rowNaNMark);
		int nanColumnCount = getColumnNaNMark(nanMark,columnNaNMark);		
		if((row == nanRowCount)||(col == nanColumnCount)) {
			DataSeries newData = new DataSeries(0,col);
			newData.setName(ds.getName());		
			for(int c=0;c<col;c++){
				Variable varObj = (Variable)varObjs.elementAt(c);
				newData.setVariableParameters(c,new String(varObj.getTag()),
					new String(varObj.getName()),new String(varObj.getUnit()));
			}
			return newData;	  //Gchen changed 3/1/99
		}

		DataSeries newData = new DataSeries(row - nanRowCount,col);
		int rr = 0;
		newData.setName(ds.getName());		
		for(int c=0;c<col;c++){
			rr = 0;
			Variable varObj = (Variable)varObjs.elementAt(c);
			newData.setVariableParameters(c,new String(varObj.getTag()),
				new String(varObj.getName()),new String(varObj.getUnit()));
			for(int r=0;r<row;r++){
				if(!rowNaNMark[r]){
					if(!nanMark[c][r]){
						newData.setValueAt(rr,c,ds.getValueAt(r,varObj.getColumnIndex()));
					}else{
						newData.setValueAt(rr,c,Double.NaN);
					}
					rr++;
				}
			}
		}
		if(ds.getHasTimeStamps()){
			long[] timeStamps1 = ds.getTimeStamps();
			long[] timeStamps2 = new long[newData.getRow()];
			rr=0;
			for(int r=0;r<row;r++){
				if(!rowNaNMark[r]){
					timeStamps2[rr] = timeStamps1[r];
					rr++;
				}
			}
			newData.setTimeStamps(timeStamps2);
		}
		return newData;
	}

	/** Initialize output data from input data, prior to apply first formula.
	This method applies the label filter, if any.  */	 //Gchen added back. 3/1/99
	private void initializeProcessedData(Vector rawdss, Vector processedDataSeries) throws MathException {
		Vector varObjs = new Vector(varNames.size());	
		// find objects in rawdss corresponding to input variable names
		for(int i=0;i<varNames.size();i++){
 			String varName = (String)varNames.elementAt(i);
			// ?? WHY does this involve processedDataSeries?
			DataSeries ds = getDataSeriesFromVariableName(processedDataSeries,varName);
			for(int j=0;j<rawdss.size();j++) {
				if(ds.getName().equals(rawdss.elementAt(j).toString())) {
					DataSeries rds = (DataSeries)rawdss.elementAt(j);
					Variable varObj = rds.getVarByName(varName);
					if(varObj != null){
						varObjs.addElement(varObj);
					}
					break;
				}
			}
		}
		Hashtable varIndexHash = getVarIndexHash(varObjs);
		for(int i=0;i<rawdss.size();i++){
			DataSeries ds = (DataSeries)rawdss.elementAt(i);
			if(varIndexHash.containsKey(ds)){
				Vector vars = (Vector)varIndexHash.get(ds);
				boolean[][] nanMark = getNaNMarkForVariables(ds,vars);
				DataSeries nds = null;
				for(int j=0;j<processedDataSeries.size();j++){
					DataSeries d = (DataSeries)processedDataSeries.elementAt(j);
					if(ds.getName().equals(d.getName())){
						nds = d;
						break;
					}
				}
				applyLabelFilter(ds,vars,nanMark,nds);
				nds.calculateVarStatistics();
			}
		}
	}

/** Add processed data in project.*/
	private void pushProcessedDataToProject(Vector processedData){
		for(int i=0;i<processedData.size();i++){
			project.addProcessedDataSeries((DataSeries)processedData.elementAt(i));
		}
	}

/** Get the status of this timestamps. */
	public boolean getHasTimeStamps(){
		return hasTimeStamps;
	}
	

	/** Get the ViewFilter of this.*/
	public ViewFilter getViewFilter(){
		return viewFilter;
	}

	/** Set the ViewFilter of this.*/
	public void setViewFilter(ViewFilter filter){
		viewFilter = filter;
	}

/** Get the hasCode for this preprocessor.*/
	public int getItsHashCode(){
		return itsHashCode;
	}

	/** Return the names of original variables.*/
	public Vector getInputVariableNames() {
		return varNames;
	}

	/** Return the number of original variables.*/
	public int getNumberOfInputVariables() {
		return varNames.size();
	}

	/** Return the derived variable names. */
	public Vector getDerivedVariableNames() {
		if(derivedVarNames==null){
			verifyFormulaList(formulas);
		}
		return derivedVarNames;
	}

	/** Returns count of derived variables */
	public int getNumberOfDerivedVariables() {
		if(derivedVarNames==null){
			verifyFormulaList(formulas);
		}
		return derivedVarNames.size();
	}

	/** Returns ALL variables in this preprocessor (input + derived) */
	public Vector getVariableNames() {
		if(allVarNames==null){
			verifyFormulaList(formulas);
		}
		return allVarNames;
	}

	/** Returns count of ALL variables (input + derived) */
	public int getNumberOfVariables() {
		if(allVarNames==null){
			verifyFormulaList(formulas);
		}
		return allVarNames.size();
	}

/** Return the tags of input variables. DERIVED VARS DO NOT HAVE TAGS DEFINED BY PREPROCESSOR */
	public Vector getInputVariableTags() {
		return varTags;
	}

/** Return the data series which contains the variable name uding the processor's own data series.*/
	public DataSeries getDataSeriesFromVariableName(String varName){
		return getDataSeriesFromVariableName(dataSeries, varName);
	}

/** Return the data series which contains the variable name.*/
	public DataSeries getDataSeriesFromVariableName(Vector Data, String varName){
		for(int i=0;i<Data.size();i++){
			DataSeries ds = (DataSeries)Data.elementAt(i);
			int vIndex = ds.getVarIndexByName(varName);
			if(vIndex != -1){
				return ds;
			}
		}
		return null;
	}

/** Return variable object for the variable name.*/
	@Override
	public Variable getVariableFromVariableName(String varName){
//		System.out.println("varname="+varName);
		for(int i = 0; i < dataSeries.size(); i++){
			DataSeries ds = (DataSeries) dataSeries.elementAt(i);
//		System.out.println("ds="+ds.toString());
			Variable varObj = ds.getVarByName(varName);
			if(varObj != null){
				return varObj;
			}
		}
		return null;
	}

	public Vector getOriginalVarNames(Vector usedNames) {
		Vector vars = (Vector)usedNames.clone();
		Vector vars0 = getVarNamesUsedInFormulas();
		for(int i=0;i<vars0.size();i++){
			String varName = (String)vars0.elementAt(i);
			if(!vars.contains(varName)){
				vars.addElement(varName);
			}
		}
		for(int i=0;i<derivedVarNames.size();i++){
			String varName = (String)derivedVarNames.elementAt(i);
			if(vars.contains(varName)){
				vars.removeElement(varName);
			}
		}
		return vars;

/*		Vector vars = (Vector)newNames.clone();
		for(int i=0;i<formulas.size();i++){
			Formula2 fm = (Formula2)formulas.elementAt(i);
  			for(int j=0;j<newNames.size();j++){
				String newName = (String)newNames.elementAt(j);
				if(fm.getOutputs().contains(newName)){
					for(int k=0;k<varNames.size();k++){
						String varName = (String)varNames.elementAt(k);
						if(varIsUsedInFormulaInputs(fm,varName)){
							if(!vars.contains(varName)){
								vars.addElement(varName);
							}
						}
					}
				}
			}
		}
		
		for(int i=0;i<derivedVarNames.size();i++){
			String varName = (String)derivedVarNames.elementAt(i);
			if(vars.contains(varName)){
				vars.removeElement(varName);
			}
		}
		return vars;
*/
	}

/** Get original variable names used in formula. */
	public Vector getVarNamesUsedInFormulas() {
		Vector vars = new Vector();
		for(int i=0;i<varNames.size();i++){
			String varName = (String)varNames.elementAt(i);
			if(varIsUsedInFormulas(varName)){
				vars.addElement(varName);
			}
		}
		return vars;
	}

	/** returns true if the variable is used in formulas	*/
  	private boolean varIsUsedInFormulas(String varName){
		for(int i=0;i<formulas.size();i++){
			Formula2 fm = (Formula2)formulas.elementAt(i);
			// is variable used in inputs?
			if(varIsUsedInFormulaInputs(fm,varName)){
				return true;
			}
			// is variable used in outputs?
			if(fm.getOutputs().contains(varName)){
				return true;
			}
		}
		return false;
	}

/** Verify the inputs of a Formula2.	 */
 	private boolean varIsUsedInFormulaInputs(Formula2 fm, String varName){
		Vector ins = fm.getInputs();
		int ic = ins.size();
		for(int j=0;j<ic;j++){
			if(ins.elementAt(j) instanceof String){
				String newVar = (String) ins.elementAt(j);
				if(newVar.equals(varName)) {
					return true;		
				}
			} else if(ins.elementAt(j) instanceof InnerFormula2){
				if(varIsUsedInFormulaInputs((Formula2)ins.elementAt(j),varName)) {
					return true;
				}
			}
		} 
		return false;
	}


/** Initialize the transient attributes.*/
	@Override
	public void initTransient(Project p){
		super.initTransient(p);
	}

/** Initialize the hashcode attributes.*/
	public void initHasCode(){
		itsHashCode = hashCode();
	}

//Start Formula list here
/** Return the number of formulas.*/
	public int getNumberOfFormulas() {
		return formulas.size();
	}

/** Get the formula at given position. */	
	public Formula2 getFormula(int index){
		return (Formula2)formulas.elementAt(index);
	}

/** Get the formulas list. */	
	public Vector getFormulas(){
		return formulas;
	}

/**	Add a formula to the end of the formula list.*/ 
	public boolean addFormula(Formula2 formula){
		int index = formulas.size();
		return addFormula(formula,index);
	}

/**	Insert a Formula at given position of the Formula list.
	The index starts from 0.*/ 
	public boolean addFormula(Formula2 formula, int insertIndex) {
		if(insertIndex < 0){
			return false;
		}
		Vector tentativeFormulaList = (Vector)formulas.clone();
		if(insertIndex >= formulas.size()){
			tentativeFormulaList.addElement(formula);
		}else {
			tentativeFormulaList.insertElementAt(formula,insertIndex);
		}
		if(!verifyFormulaList(tentativeFormulaList)) {
			return false;
		}
		formulas = tentativeFormulaList;
		if(updatedIndex > insertIndex ) {
			updatedIndex = -1;
		}
//Dispatch the list change event
		PreprocessorEvent Evt = new PreprocessorEvent(this, "formulaListChanged");
		fireEvent(Evt);
		return true;
	}


/**	Add a set of formulas to the end of the formula list.*/ 
	public boolean addFormulas(Vector fms){
		int insertIndex = formulas.size();
		return addFormulas(fms,insertIndex);
	}

/**	Insert a set of formulas at given position of the formula list.
	The index starts from 0.*/ 
	public boolean addFormulas(Vector fms, int insertIndex){ 
		if(insertIndex < 0) {
			return false;
		}
		Vector tentativeFormulaList = (Vector)formulas.clone();
		if(insertIndex >= tentativeFormulaList.size()){
			for(int i=0;i<fms.size();i++){
				Formula2 fm = (Formula2)fms.elementAt(i);
				tentativeFormulaList.addElement(fm);
			}
		}else{
			for(int i=fms.size()-1;i>=0;i--){
				Formula2 fm = (Formula2)fms.elementAt(i);				
				tentativeFormulaList.insertElementAt(fm,insertIndex);
			}
		}
		if(!verifyFormulaList(tentativeFormulaList)) {
			return false;
		}
		formulas = tentativeFormulaList;
		if(updatedIndex > insertIndex ){
			updatedIndex = -1;
		}
		PreprocessorEvent Evt = new PreprocessorEvent(this, "formulaListChanged");
		fireEvent(Evt);
		return true;
	}

/**	Add a set of formulas read from file to the end of the formula list.*/ 
	public boolean addFormulas(String directory, String file){
		int insertIndex = formulas.size();
		return addFormulas(directory,file,insertIndex);	
	}

/**	Add a set of formulas read from file to the end of the formula list.*/ 
	public boolean addFormulas(String directory, String file, int insertIndex){
		try {
			File sourceFile;
			if(directory==null)
				sourceFile = new File(file);	
			else
				sourceFile = new File(directory,file);
			FileInputStream fis = new FileInputStream(sourceFile); // Read from file
			GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
			ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
        // Read in an object.  It should be a vector of scribbles
			Vector content = (Vector)in.readObject();
			in.close(); // Close the stream.
			return addFormulas(content,insertIndex);
		} catch (Exception e) { 
			System.err.println("Exception in addFormulas: "+e); 
			e.printStackTrace();
		}
		return false;
	}

/** Set a formula at given position of the formula list. 
	The index starts from 0. */	
	public boolean modifyFormula(Formula2 fm, int insertIndex){
		if(insertIndex < 0 || insertIndex >= formulas.size()) {
			return false;
		}
		Vector tentativeFormulaList = (Vector)formulas.clone();
		tentativeFormulaList.setElementAt(fm,insertIndex);
		if(!verifyFormulaList(tentativeFormulaList)) {
			return false;
		}
		if(updatedIndex > insertIndex ) {
			updatedIndex = -1;
		}
		formulas = tentativeFormulaList;
//Dispatch the list change event
		PreprocessorEvent Evt = new PreprocessorEvent(this, "formulaListChanged");
		fireEvent(Evt);
		return true;
	}

/**	Remove a Formula at given position from the Formula list.
	The index starts from 0.*/ 
	public boolean removeFormula(int insertIndex){
		if(insertIndex < 0 || insertIndex >= formulas.size())
			return false;
		Vector tentativeFormulaList = (Vector)formulas.clone();
		tentativeFormulaList.removeElementAt(insertIndex);
		if(!verifyFormulaList(tentativeFormulaList)) {
			return false;
		}
		if(	updatedIndex >= insertIndex) {
			updatedIndex = -1;
		}
		formulas = tentativeFormulaList;
//Dispatch the list change event
		PreprocessorEvent Evt = new PreprocessorEvent(this, "formulaListChanged");
		fireEvent(Evt);
		return true;
	}


/**	Move a column Formula from one position to another.
	The index starts from 0.*/ 
	public boolean moveFormula(final int from, final int to){ 
		int toIndex = to;
		if(from < 0 || from >= formulas.size()){
			return false;
		}
		if(toIndex < 0 || toIndex >= formulas.size()+1){
			return false;
		}
		if(toIndex == from){
			return true;
		}
		if(toIndex == formulas.size()+1){
			toIndex = formulas.size();
		}
		Vector tentativeFormulaList = (Vector)formulas.clone();
		if(from<toIndex){
			tentativeFormulaList.insertElementAt(tentativeFormulaList.elementAt(from),toIndex+1);
			tentativeFormulaList.removeElementAt(from);
		}else{
			tentativeFormulaList.insertElementAt(tentativeFormulaList.elementAt(from),toIndex);
			tentativeFormulaList.removeElementAt(from+1);
		}
		if(!verifyFormulaList(tentativeFormulaList)) {
			return false;
		}
		formulas = tentativeFormulaList;
		if(	updatedIndex >= Math.min(from,toIndex)) {
			updatedIndex = -1;
		}
//Dispatch the list change event
		PreprocessorEvent Evt = new PreprocessorEvent(this, "formulaListChanged");
		fireEvent(Evt);
		return true;
	}

 /** Verify the new Formula list.  This is done when new formulas are added or moved.
	This procedure checks that all variables defined in the input or in preceding formulas,
	as derived variables.  This updates the list of derived variables and all variables. */
	private boolean verifyFormulaList(Vector formulaList){
		Vector varStacks = (Vector)varNames.clone();
		Vector derivedVars = new Vector();
		for(int i=0;i<formulaList.size();i++){
			Formula2 fm = (Formula2)formulaList.elementAt(i);
			if(!verifyFormulaInputs(fm,varStacks)) {
				// always create derived and all var names vectors, or API might fail
				if(derivedVarNames==null) {
					derivedVarNames=derivedVars;	
				}
				if(allVarNames==null) {
					allVarNames=varStacks;
				}
				return false;
			}
  			Vector outs = fm.getOutputs();
			for(int j=0;j<outs.size();j++){
				String varName1 = (String)outs.elementAt(j); 
				if(!varStacks.contains(varName1)){
					varStacks.addElement(varName1);
					derivedVars.addElement(varName1);
				}
			}
		}
		derivedVarNames = derivedVars;
		allVarNames = varStacks;
		return true;
	}

/** Verify the inputs of a Formula.	 */
 	private boolean verifyFormulaInputs(Formula2 fm, Vector varStacks){
		Vector ins = fm.getInputs();
		int nc = varStacks.size();
		int ic = ins.size();
		for(int j=0;j<ic;j++){
			if(ins.elementAt(j) instanceof String){
				String newVar = (String) ins.elementAt(j);
				// System.out.println(" verifyFormulaInputs newVar = "+newVar);
				if(!varStacks.contains(newVar)){
					return false;		
				}
			} else if(ins.elementAt(j) instanceof InnerFormula2){
				if(!verifyFormulaInputs((Formula2)ins.elementAt(j),varStacks)) {
					return false;
				}
			}// else it will be a double 
		} 
		return true;
	}

	/** Update the formula list starting at current updatedIndex.  
	This is the entry point from NolFormulaListWKSP */ 
	public void updateFormulas() throws NoSuchMethodException,MathException,FormulaException,
		SecurityException,InstantiationException, IllegalAccessException{	
		int nt = formulas.size();
		if (updatedIndex == nt) {
			return;
		}
		// apply the formulas using the preprocessor's raw data source and processed data series
		RawDataSource rawDataSource = project.getRawDataSource();
		applyFormulaFromIndex(rawDataSource.getDataSeries(), dataSeries, updatedIndex);
		updatedIndex = nt;
	}
	
	/** Update the formula list starting at the beginning, without affecting the updatedIndex */
	public void reapplyPreprocessor() throws NoSuchMethodException, 
		SecurityException,InstantiationException,IllegalAccessException,
		MathException,FormulaException {
		// force evaluation from the beginning
		updatedIndex = -1;
		updateFormulas();
	}

	/** Applies preprocessor to input data as a transfer function.  The output data is not used
	except to contain the preprocessed data */
	public void applyPreprocessor(Vector inputData, Vector outputData) throws NoSuchMethodException, 
		SecurityException,InstantiationException, IllegalAccessException,MathException,FormulaException {
		Vector varObjs = new Vector();
		// collect variable objects from the inputData
		for(int i=0;i<varNames.size();i++){
			String name = (String)varNames.elementAt(i);
			for(int j=0;j<inputData.size();j++){
				DataSeries ds = (DataSeries)inputData.elementAt(j);
				Variable varObj = ds.getVarByName(name);
				if(varObj != null){
					varObjs.addElement(varObj);
					break;
				}
			}
		}
		// if we didn't find all the variables in the inputData, we have to throw an exception
		if (varObjs.size() != varNames.size()) {
			throw new MathException("Input data series did not contain all the variables needed by the preprocessor");
		}
		// Now apply the label filter
//System.out.println("applyPreprocessor 1varObjs.size() "+varObjs.size());
		createProcessedDataSeries(varObjs, outputData);   // this clears outputData of any existing ds before filling it up
//		System.out.println("applyPreprocessor 2");
		applyFormulaFromIndex(inputData, outputData, 0);  // note index=0 means we don't have to initialize the output data (done in createProcessedDataSeries)
//		System.out.println("applyPreprocessor 3");
	}


	private void applyFormulaFromIndex(final Vector rawDataSeries, final Vector processedDataSeries, final int index) throws NoSuchMethodException, 
		SecurityException,InstantiationException,IllegalAccessException,MathException,FormulaException {
		int nt = formulas.size();
		Object target;
		int indexLocal = index;
		if(indexLocal == -1){
			initializeProcessedData(rawDataSeries, processedDataSeries);  // applies labels
			indexLocal = 0;
		}
		for(int i=indexLocal;i<nt;i++){
			Formula2 formula = (Formula2)formulas.elementAt(i);
			try {
				formula.applyFormula(processedDataSeries);
			} catch (FormulaException e) {
				throw new FormulaException("Formula "+(i+1)+": "+e.getMessage());
			} catch (MathException e) {
				throw new FormulaException("Formula "+(i+1)+": "+e.getMessage());
			}
		}
		for(int i=0;i<processedDataSeries.size();i++){
			DataSeries ds = (DataSeries)processedDataSeries.elementAt(i);
			ds.calculateVarStatistics();
		}
		PreprocessorEvent Evt = new PreprocessorEvent(this, "DataChanged",processedDataSeries,0);
		fireEvent(Evt);
	}

/**Save the list of Formulas to a file.	*/
	public void saveFormulasBinary(String directory, String fileName, Vector contents){
		String fName;
		if(fileName ==null) {
			fName = name+".tfm";
		}
		else fName = fileName;
		try {
			File sourceFile;
			if(directory==null) {
				sourceFile = new File(fName);	
			}
			else sourceFile = new File(directory,fName);
			FileOutputStream fos = new FileOutputStream(sourceFile); // Read from file
        // Create the necessary output streams to save the data.
			GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
			ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
			out.writeObject(contents);      // Write the entire Vector of scribbles
			out.flush();                 // Always flush the output.
			out.close();                 // And close the stream.
		} catch (IOException e) { 
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
	}

/**Save the list of Formulas to a file.	*/
	public void saveFormulasBinary(String directory, String fileName){
		saveFormulasBinary(directory,fileName, formulas);
	}

	private void applyLabelFilter(DataSeries ds, Vector varObjs, boolean[][] nanMark, DataSeries newData) throws MathException {
		int col = varObjs.size();
		int row = ds.getRow();
		boolean[] rowNaNMark = new boolean[row];

		int nanRowCount = getRowNaNMark(nanMark,rowNaNMark);
		int rr = 0;
		try{
			newData.truncateColumn(col);
		}catch(MathException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
		}

		int newRows = row - nanRowCount;
		if(newRows == 0){
			newData.emptyDataSeries();
			return;
		}
		if(newData.getRow() != row - nanRowCount){
			Matrix M = newData.getDataMatrix();
			M.redimension(row - nanRowCount,col);
		}

		for(int c=0;c<col;c++){
			rr = 0;
			Variable varObj = (Variable)varObjs.elementAt(c);
			for(int r=0;r<row;r++){
				if(!rowNaNMark[r]){
					if(!nanMark[c][r]){
						newData.setValueAt(rr,c,ds.getValueAt(r,varObj.getColumnIndex()));
					}else{
						newData.setValueAt(rr,c,Double.NaN);
					}
					rr++;
				}
			}
		}
		if(ds.getHasTimeStamps()){
			long[] timeStamps1 = ds.getTimeStamps();
			long[] timeStamps2 = newData.getTimeStamps();
			if(timeStamps2.length != newRows){
				timeStamps2 = new long[newRows];
			}
			rr=0;
			for(int r=0;r<row;r++){
				if(!rowNaNMark[r]){
					timeStamps2[rr] = timeStamps1[r];
					rr++;
				}
			}
			newData.setTimeStamps(timeStamps2); //Gchen added 3.1.99
		}
	}

//End list 
	protected void fireEvent(PreprocessorEvent evt){
		Vector targets;
		synchronized (this) {
			if(itsEventListeners == null){
				itsEventListeners = new Vector();
				return;
			}
		
			targets = (Vector) itsEventListeners.clone();
		}
		for (int i = 0; i < targets.size(); i++) {
			PreprocessorListener pl = (PreprocessorListener)targets.elementAt(i);
			if(evt.getIdentifier().equals("formulaListChanged")){
				pl.FormulaListChanged(evt);
			}else if(evt.getIdentifier().equals("DataChanged")){
				pl.DataChanged(evt);
			}
		}

	}
	@Override
	public void LabelCategoryAdded(RawDataEvent e){}
	@Override
	public void LabelCategoryRemoved(RawDataEvent e){}
	@Override
	public void DataPointsLabeled(RawDataEvent e){}
	@Override
	public void LabelOrderChanged(RawDataEvent e){}
	@Override
	public void LabelNameChanged(RawDataEvent e){}
	@Override
	public void LabelColorChanged(RawDataEvent e){}
	@Override
	public void DataSeriesAdded(RawDataEvent e){}
	@Override
	public void DataSeriesRemoved(RawDataEvent e){}

/* Apply preprocessor to data series, creating output data, 
   and including the outputs in the project's data series

	public void applyPreprocessor(Vector inputData)throws NoSuchMethodException, 
		SecurityException,InstantiationException,IllegalAccessException,MathException,FormulaException {
		Vector outputData = new Vector();
		applyPreprocessor(inputData,outputData);
		pushProcessedDataToProject(outputData);
	}  */

	public void setTimeStamps(DataSeries ds){
		for(int i=0;i<dataSeries.size();i++){
			DataSeries ds1 = (DataSeries)dataSeries.elementAt(i);			
			if(ds1.getName().equals(ds.getName())){
				ds1.setTimeStamps(ds.getTimeStamps());
			}
		}
	}


	//Modified method for online preprocessor.
/** Get original input variable names used in formula. 	*/
	public void getInputNamesDerivedVarsFormulasForModel(
		Vector modelInputNames,
		Vector inputNamesForModel,
		Vector derivedVarNamesForModel,
		Vector formulasForModel) {

		inputNamesForModel.removeAllElements();
		derivedVarNamesForModel.removeAllElements();
		formulasForModel.removeAllElements();

		Vector allVarNamesForModel = (Vector)modelInputNames.clone();
		for(int i=formulas.size()-1;i>=0;i--){
			Formula2 fm = (Formula2)formulas.elementAt(i);
 			Vector fmOuts = fm.getOutputs();
 			boolean fmUsedForThisModel = false;
 			for(int k=0;k<fmOuts.size();k++){
				String fmOutName = (String)fmOuts.elementAt(k);
				if(allVarNamesForModel.contains(fmOutName)){
					fmUsedForThisModel = true;
					break;
				}
			}
			if(fmUsedForThisModel){
				for(int k=0;k<allVarNames.size();k++){
					String varName = (String)allVarNames.elementAt(k);
  					if(varIsUsedInFormulaInputs(fm,varName) || fm.getOutputs().contains(varName)) {
						if(!allVarNamesForModel.contains(varName)){
							allVarNamesForModel.addElement(varName);
						}
					}
				}
				formulasForModel.insertElementAt(fm,0);
			}
		}
		for(int i=0;i<varNames.size();i++){
			String varName = (String)varNames.elementAt(i);
			if(allVarNamesForModel.contains(varName)){
				inputNamesForModel.addElement(varName);	
			}
		}
		for(int i=0;i<derivedVarNames.size();i++){
			String varName = (String)derivedVarNames.elementAt(i);
			if(allVarNamesForModel.contains(varName)){
				derivedVarNamesForModel.addElement(varName);
			}
		}
	}

	public void resampleData(long startTime, long endTime, long interval){
		for(int i=0;i<dataSeries.size();i++){
			DataSeries ds = (DataSeries)dataSeries.elementAt(i);
			ds.resampleData(startTime,endTime,interval);
		}
	}
	public void resampleData(long startTime, long endTime, long interval, int dsIndex){
		if(dsIndex < 0 || dsIndex >(dataSeries.size()-1) ){
			return;
		}
		DataSeries ds = (DataSeries)dataSeries.elementAt(dsIndex);		    
		ds.resampleData(startTime,endTime,interval);
	}

	public void setDerivedVarNames(Vector names) {
		derivedVarNames = names;
	}

	@Override
	public void setDataSeries(Vector series) {
		dataSeries = series;
	}
}

