package com.gensym.nols.data;

import java.awt.Color;

/**
 *		Gensym Project Class.
 *		This class is extended from Object.class
 *		Modified 11/12/97 by Gchen
 */
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.Vector;
import java.util.zip.GZIPInputStream;
import java.util.zip.GZIPOutputStream;

/** Project class */
public class Project implements Cloneable, Serializable {
  
  static final long serialVersionUID = 1L;
  private static int projectInstanceCount = 1;
  private String name;
  private String comment;
  private Vector labelCategory;
  private Vector joinedLabels;  //need to consider delete the labelcategory effects
  private RawDataSource rawDataSource;
  private Vector preprocessors;
  private Vector processedData;
  private Vector predictiveModels;
  private Vector optimizationModels;
  private Vector simulations;
  private Vector optimizations;
  private Vector customTimeFormats;
  private Vector customDateFormats;
  private Vector customDateTimeFormats;
  
  private transient Vector dataSeriesInputFormats;
  private transient Vector projectListeners;
  private transient int variableNameCounter;

  private String projectDirectory;
  
  /** Create a null project with no argument */
  public Project() {
    super();
    name = "Project" + projectInstanceCount;
    comment = "";
    projectInstanceCount++;
    rawDataSource = new RawDataSource(this);
    labelCategory = new Vector(0,4);
    joinedLabels = new Vector();
    preprocessors = new Vector(0,4);
    processedData = new Vector(0,4);
    predictiveModels = new Vector(0,4);
    optimizationModels = new Vector(0,4);
    simulations = new Vector(0,4);
    optimizations = new Vector(0,4);
    dataSeriesInputFormats = new Vector(0,4);
    customTimeFormats = new Vector(0,4);
    customDateFormats = new Vector(0,4);
    customDateTimeFormats = new Vector(0,4);
    projectListeners = new Vector(0,4);
    variableNameCounter = 1;
	projectDirectory = "";
    loadFileFormat();
  }

/** Create a data project with a given name. */
	public Project(String name) {
		this();
		this.name = name;
		projectInstanceCount--;
	}

	@Override
	public synchronized Object clone() throws CloneNotSupportedException {
		Project cloned = (Project) super.clone();
		cloned.rawDataSource = rawDataSource == null ? null : (RawDataSource) rawDataSource.clone();
		cloned.labelCategory = labelCategory == null ? null : (Vector) labelCategory.clone();
		cloned.joinedLabels = joinedLabels == null ? null : (Vector) joinedLabels.clone();
		cloned.preprocessors = preprocessors == null ? null : (Vector) preprocessors.clone();
		cloned.processedData = processedData == null ? null : (Vector) processedData.clone();
		cloned.predictiveModels = predictiveModels == null ? null : (Vector) predictiveModels.clone();
		cloned.optimizationModels = optimizationModels == null ? null : (Vector) optimizationModels.clone();
		cloned.simulations = simulations == null ? null : (Vector) simulations.clone();
		cloned.optimizations = optimizations == null ? null : (Vector) optimizations.clone();
		cloned.customTimeFormats = customTimeFormats == null ? null : (Vector) customTimeFormats.clone();
		cloned.customDateFormats = customDateFormats == null ? null : (Vector) customDateFormats.clone();
		cloned.customDateTimeFormats = customDateTimeFormats == null ? null : (Vector) customDateTimeFormats.clone();
		cloned.dataSeriesInputFormats = dataSeriesInputFormats == null ? null : (Vector) dataSeriesInputFormats.clone();
		cloned.projectListeners = projectListeners == null ? null : (Vector) projectListeners.clone();
		
		return cloned;
	}

/** Get the name of this data project. */	
	public String getName(){
		return name;
	}

/** Set the name of this data project. */	
	public void setName(String n){
		name = new String(n);
	}

/** Return the comment of this project.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this project.*/
	public void setComment(String c){
		comment = c;
	}

/** Return the rawDataSource of this project.*/
	public RawDataSource getRawDataSource(){
		return rawDataSource;
	}

/** Get number of data series file formats*/
	public int getNumberOfDataSeriesFileFormat(){
		return dataSeriesInputFormats.size();
	}

/** Get all data series file formats*/
	public Vector getDataSeriesFileFormats(){
		return dataSeriesInputFormats;
	}

	/** Create a unique name for a variable.  Added by MK, 2/15/99 */
	public String makeUniqueNameForVariable() {
		RawDataSource rawSource = getRawDataSource();
		boolean isUnique = false;
		String varName = "";
		while(!isUnique) {
			varName = "Var"+variableNameCounter;
			variableNameCounter++;
			isUnique = variableNameIsUnique(varName);
		}
		return varName;
	}

	/** Checks if a proposed name for a variable is unique.  Added by MK, 2/15/99 */
	public boolean variableNameIsUnique(String name) {
		// only checks raw data source for now
		// needs to also check preprocessors for derived variables
		Vector rawData = rawDataSource.getDataSeries();
		for(int i=0;i<rawData.size();i++) {
			DataSeries ds = (DataSeries) rawData.elementAt(i);
			Vector vars = ds.getVarObjects();
			for(int j=0;j<vars.size();j++) {
				Variable var = (Variable) vars.elementAt(j);
				if(name.equals(var.getName())){
					return false;
				}
			}
		}
		return true;
	}
  public Vector getCustomTimeFormats(){
	if(customTimeFormats==null){
		customTimeFormats = new Vector(0,4);
	}
    return customTimeFormats;
  }
  public Vector getCustomDateFormats(){
	if(customDateFormats==null){
		customDateFormats = new Vector(0,4);
	}
    return customDateFormats;
  }
  public Vector getCustomDateTimeFormats(){
	if(customDateTimeFormats==null){
		customDateTimeFormats = new Vector(0,4);
	}
    return customDateTimeFormats;
  }
  public void setCustomTimeFormats(Vector timeFormats){
    customTimeFormats = ((Vector)(timeFormats.clone()));
  }
  public void setCustomDateFormats(Vector dateFormats){
    customDateFormats = ((Vector)(dateFormats.clone()));
  }
  public void setCustomDateTimeFormats(Vector dateTimeFormats){
    customDateTimeFormats = ((Vector)(dateTimeFormats.clone()));
  }


/** Get data series file format based on name*/
	public DataSeriesFileFormat getDataSeriesFileFormat(String n){
		int c = dataSeriesInputFormats.size();
		for(int i=0;i<c;i++){
			DataSeriesFileFormat format = 
				(DataSeriesFileFormat)dataSeriesInputFormats.elementAt(i);
			if(format.getName().equals(n)){
				return format;
			}
		}
		return null;
	}

/** Set data series file format based on suffix*/
	public void setDataSeriesFileFormat(DataSeriesFileFormat format){
		int c = dataSeriesInputFormats.size();
		boolean nofound = true;
		for(int i=0;i<c;i++){
			DataSeriesFileFormat format1 = 
				(DataSeriesFileFormat)dataSeriesInputFormats.elementAt(i);
			if(format1.getName().equals(format.getName())){
				dataSeriesInputFormats.setElementAt(format,i);
				nofound=false;
				break;
			}
		}
		if(nofound)
			dataSeriesInputFormats.addElement(format);
		saveFileFormat();
		ProjectEvent evt = new ProjectEvent(this,"dataFileFormatSetted");
		fireEvent(evt);
	}

  
/** Set data series file format based on suffix*/
	public void removeDataSeriesFileFormat(DataSeriesFileFormat format){
		if(dataSeriesInputFormats.contains(format)){
			dataSeriesInputFormats.removeElement(format);
			ProjectEvent evt = new ProjectEvent(this,"dataFileFormatRemoved");
			fireEvent(evt);
			saveFileFormat();
		}
	}

/** Add a data series to this data project. */	
	public void addDataSeries(DataSeries ds){
		rawDataSource.addDataSeries(ds);
	}

/** Add a processed data series to this data project. */	
	public void addProcessedDataSeries(DataSeries ds){
		if(processedData.contains(ds)){
			return;
		}
		processedData.addElement(ds);
	}

/** Remove a processed data series from this data project. */	
	public void removeProcessedDataSeries(DataSeries ds){
		if(processedData.contains(ds)) {
			processedData.removeElement(ds);
		}
	}

/** Return the processed data in project by given preprocessor.*/
	public Vector getProcessedDataByPreprocessor(Preprocessor prep){
		Vector pds = new Vector();
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			if(ds.getDataSource().equals(prep)){
				pds.addElement(ds);
			}
		}
		return pds;
	}


/** Return the processed data in project.*/
	public Vector getProcessedData(){
		return processedData;
	}


/** Check whether this data series is used by other data source.
	public boolean checkUsageOfDataSeries(DataSeries ds){
		if(getNumberOfPreprocessors()==0){
			return false;
		}else{
			for(int i=0;i<getNumberOfPreprocessors();i++){
				Preprocessor prep = (Preprocessor)preprocessors.elementAt(i);
				int dc = prep.getNumberOfDataSeries();
				for(int j=0;j<dc;j++){
					DataSeries ds1 = prep.getDataSeries(j);
					if(ds.getName().equals(ds1.getName()))
						return true;
				}
			}
		}
		return false;
	}
/** Return label of all labels.*/
	public Vector getLabels() {
		return labelCategory;
	}

/** Return label by index.*/
	public NolLabel getLabel(int index) {
		if(index<labelCategory.size())
			return (NolLabel)labelCategory.elementAt(index);
		return null;
	}

/** Return the number of labels in this project.*/
	public int getNumberOfLabels(){
		return labelCategory.size();
	}

/** Return label index from label name*/
	public int getLabelIndex(String labelName){
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			if(lab.getName().equals(labelName))
				return i;
		}
		return -1;
	}

/** Return label index from label object*/
	public int getLabelIndex(NolLabel lab){
		return labelCategory.indexOf(lab);
	}

/** Return label index of the label which order is zero.*/
	public int getTopLabelIndex(){
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			if(lab.getLabelOrder()==0)
				return i;
		}
		return -1;
	}

/** Return the label color of the top label.*/
	public Color getLabelColor(boolean[] labelArray){
		if(labelArray.length != labelCategory.size())
			return Color.white;
		int index = -1;
		int order = Integer.MAX_VALUE;
		for(int i=0;i<labelArray.length;i++){
			if(labelArray[i]){
				NolLabel lab = (NolLabel)labelCategory.elementAt(i);
				int or = lab.getLabelOrder();
//		if(DEBUG.debug){
//			System.out.println("lab="+lab.getName()+" or="+or+"  order="+order);
//		}
				if(or<order){
					index = i;
					order = or;
				}
			}
		}
		if(index != -1){
			NolLabel lab = (NolLabel)labelCategory.elementAt(index);
			return lab.getLabelColor();
		}
		return Color.white;
	}

/** Add a new label category to this project.*/
	public int addLabelCategory(String labelName, String comment, Color labelColor){
		int old = getLabelIndex(labelName);
		if (old != -1){
			return old;
		}
		NolLabel lab = new NolLabel(labelName, comment, labelColor);
		lab.setProject(this);
		for(int i=0;i<labelCategory.size();i++){
			NolLabel oldLab = (NolLabel)labelCategory.elementAt(i);
			int oldOrder = oldLab.getLabelOrder();
			oldLab.setLabelOrder(oldOrder+1);
		}
		labelCategory.addElement(lab);
		lab.setLabelOrder(0); //Add new label as the first one gchen 10.4.1999

//		lab.setLabelOrder(labelCategory.size() - 1); //add new label as the last one
		rawDataSource.addLabelCategory();
//		ProjectEvent evt = new ProjectEvent(this,"labelCategoryAdded");
//		fireEvent(evt);
		return labelCategory.size() - 1;
	}	

/** remove a label category from this project.*/
	public void removeLabelCategory(final NolLabel lab){
		NolLabel labelBean = lab;
		int labelIndex =labelCategory.indexOf(labelBean); 
		if(labelIndex == -1){
			return;  
		}
		int order0 = labelBean.getLabelOrder();
		labelCategory.removeElement(labelBean);
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab0 = (NolLabel)labelCategory.elementAt(i);
			int order = lab0.getLabelOrder();
			if(order>order0)
				lab0.setLabelOrder(order-1);
		}
		labelBean.setProject(null);
		labelBean = null;
		rawDataSource.removeLabelCategory(labelIndex);
//		ProjectEvent evt = new ProjectEvent(this,"labelCategoryRemoved");
//		fireEvent(evt);
	}

/** */
	public void changeLabelOrder(int[] index){
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			lab.setLabelOrder(index[i]);
		}
/*		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			int o = lab.getLabelOrder();
			if(o<index)
				lab.setLabelOrder(o+1);
			else if(o==index)
				lab.setLabelOrder(0);
		}
*/
		rawDataSource.changeLabelOrder();
//		ProjectEvent evt = new ProjectEvent(this,"labelOrderChanged");
//		fireEvent(evt);
	}

	public void labelNameChanged(NolLabel lab){
		rawDataSource.labelNameChanged(lab);
	}

	public void labelColorChanged(NolLabel lab){
		rawDataSource.labelColorChanged(lab);
	}

/** Return the label order. */
	public int[] getLabelOrder(){
		int lc = labelCategory.size();
		int[] order = new int[lc];
		for(int i=0;i<lc;i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			order[lab.getLabelOrder()] = i;
		}
		return order;

/* 		int[] order = new int[labelCategory.size()];
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			order[i] = lab.getLabelOrder();
		}
		return order;
*/	}

/** return the number of preprocessors.*/
	public int getNumberOfPreprocessors(){
		return preprocessors.size();
	}

/* The event model for data event.*/
/** Register the data event listener for this project.*/
	public synchronized void addProjectListener(ProjectListener l){
		if(!projectListeners.contains(l))
			projectListeners.addElement(l);
	}

/** Deregister the data event listener for the project.*/
	public synchronized void removeProjectListener(ProjectListener l){
		projectListeners.removeElement(l);
	}

/** Clear the data event listener for the project.*/
	public synchronized void clearProjectListener(ProjectListener l){
		projectListeners.removeAllElements();
	}

/** This method is to fire give data event.*/
	private void fireEvent(ProjectEvent Evt){
		Vector targets;
		synchronized (this) {
			targets = (Vector) projectListeners.clone();
		}
		for (int i = 0; i < targets.size(); i++) {
			if(Evt.getIdentifier().equals("dataFileFormatSetted")){
				ProjectListener pl = (ProjectListener)targets.elementAt(i);
				pl.DataFileFormatSetted(Evt);
			}else if(Evt.getIdentifier().equals("dataFileFormatRemoved")){
				ProjectListener pl = (ProjectListener)targets.elementAt(i);
				pl.DataFileFormatRemoved(Evt);
			} 
		}
	}

/** Return Preprocessor index in the Preprocessor list.*/
	public int getPreprocessorIndexByName(String name){
		int c = preprocessors.size();
		for(int i=0;i<c;i++){
			Preprocessor m = (Preprocessor)preprocessors.elementAt(i);
			if(m.getName().equals(name))
				return i;
		}
		return -1;
	}	

/** Return Preprocessor in the Preprocessor list by index.*/
	public Preprocessor getPreprocessorByIndex(int index){
		return (Preprocessor)preprocessors.elementAt(index);
	}	

/** Return Preprocessor list.*/
	public Vector getPreprocessors(){
		return preprocessors;
	}	

/** Add new  Preprocessor in the Preprocessor list.*/
	public void addPreprocessor(Preprocessor pr){
		if(!preprocessors.contains(pr)){
			preprocessors.addElement(pr);
//			ProjectEvent evt = new ProjectEvent(this,"PreprocessorAdded");
//			fireEvent(evt);
		}
	}	

/** Remove  Preprocessor in the Preprocessor list.*/
	public void removePreprocessor(Preprocessor pr){
		if(preprocessors.contains(pr)){
			preprocessors.removeElement(pr);
			Vector ddss = getProcessedDataByPreprocessor(pr);
			for(int i=0;i<ddss.size();i++){
				processedData.removeElement(ddss.elementAt(i));
			}
//			ProjectEvent evt = new ProjectEvent(this,"PreprocessorRemoved");
//			fireEvent(evt);
		}
	}	

/** Remove  Preprocessor in the Preprocessor list by index.*/
	public void removePreprocessor(int index){
		if(index <preprocessors.size() && index >=0){
			Preprocessor pr = (Preprocessor)preprocessors.elementAt(index);
			removePreprocessor(pr);
//			ProjectEvent evt = new ProjectEvent(this,"PreprocessorRemoved");
//			fireEvent(evt);
		}
	}	

/**  Add a new model to the model list.*/
	public void addPredictiveModel(NolModel2 model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getPredictiveModelIndexByName(((NolModel2)model).getName());
		if(mindex == -1)
			predictiveModels.addElement(model);
		else
			predictiveModels.setElementAt(model,mindex);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Delete a model from the model list.*/
	public void deletePredictiveModel(int index){
		if(index<0||index>=predictiveModels.size()){
			return;
		}
		predictiveModels.removeElementAt(index);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Delete a model from the model list.*/
	public void deletePredictiveModel(NolModel2 model){
		predictiveModels.removeElement(model);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Return the model list.*/
	public Vector getPredictiveModels(){
		return predictiveModels;
	}

/** Return the number of model list.*/
	public int getNumberOfPredictiveModels(){
		return predictiveModels.size();
	}

/** Return the predictive model with the index.*/
	public NolModel2 getPredictiveModel(int index){
		return (NolModel2)predictiveModels.elementAt(index);
	}

/** Return model index in the model list.*/
	public int getPredictiveModelIndexByName(String modelName){
		int c = predictiveModels.size();
		for(int i=0;i<c;i++){
			NolModel2 m = (NolModel2)predictiveModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new model to the model list.*/
	public void addOptimizationModel(INolOptimizeModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getOptimizationModelIndexByName(model.getName());
		if(mindex == -1)
			optimizationModels.addElement(model);
		else
			optimizationModels.setElementAt(model,mindex);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Delete a model from the model list.*/
	public void deleteOptimizationModel(int index){
		if(index<0||index>=optimizationModels.size()){
			return;
		}
		optimizationModels.removeElementAt(index);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Delete a model from the model list.*/
	public void deleteOptimizationModel(NolOptimizeModel model){
		optimizationModels.removeElement(model);
//		ProjectEvent evt = new ProjectEvent(this,"modelChanged");
//		fireEvent(evt);
	}

/** Return the model list.*/
	public Vector getOptimizationModels(){
		return optimizationModels;
	}

/** Return the number of model list.*/
	public int getNumberOfOptimizationModels(){
		return optimizationModels.size();
	}

/** Return the optimization model with the index.*/
	public NolOptimizeModel getOptimizationModel(int index){
		return (NolOptimizeModel)optimizationModels.elementAt(index);
	}

/** Return model index in the model list.*/
	public int getOptimizationModelIndexByName(String modelName){
		int c = optimizationModels.size();
		for(int i=0;i<c;i++){
			NolOptimizeModel m = (NolOptimizeModel)optimizationModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}
	
/**  Add a new model to the Simulation list.*/
	public void addSimulation(ResponseSurfaceSimulation sim){		//gchen check  whether has the same name of a transforme 7.8.98
		int sindex = getSimulationIndexByName(sim.getName());
		if(sindex == -1)
			simulations.addElement(sim);
		else
			simulations.setElementAt(sim,sindex);
//		ProjectEvent evt = new ProjectEvent(this,"simulationChanged");
//		fireEvent(evt);	   //  simulationChanged" hasn't been implemented gchen 9/17/98
	}

/** Delete a model from the Simulation list.*/
	public void deleteSimulation(int index){
		if(index<0||index>=simulations.size()){
			return;
		}
		simulations.removeElementAt(index);
//		ProjectEvent evt = new ProjectEvent(this,"simulationChanged");
//		fireEvent(evt);
	}

/** Delete a model from the Simulation list.*/
	public void deleteSimulation(ResponseSurfaceSimulation sim){
		simulations.removeElement(sim);
//		ProjectEvent evt = new ProjectEvent(this,"simulationChanged");
//		fireEvent(evt);
	}

/** Return the simulation list.*/
	public Vector getSimulations(){
		return simulations;
	}

/** Return the number of simulation list.*/
	public int getNumberOfSimulations(){
		return simulations.size();
	}

/** Return the simulation with the index.*/
	public ResponseSurfaceSimulation getSimulation(int index){
		return (ResponseSurfaceSimulation)simulations.elementAt(index);
	}

/** Return model index in the simulation list.*/
	public int getSimulationIndexByName(String simulationName){
		int c = simulations.size();
		for(int i=0;i<c;i++){
			ResponseSurfaceSimulation m = (ResponseSurfaceSimulation)simulations.elementAt(i);
			if(m.getName().equals(simulationName))
				return i;
		}
		return -1;
	}
	
/**  Add a new Optimization to the Optimization list.*/
	public void addOptimization(NolOptimization opt){		//gchen check  whether has the same name of a transforme 7.8.98
		int index = getOptimizationIndexByName(opt.getName());
		if(index == -1)
			optimizations.addElement(opt);
		else
			optimizations.setElementAt(opt,index);
//		ProjectEvent evt = new ProjectEvent(this,"optimizationChanged");
//		fireEvent(evt);	   //  simulationChanged" hasn't been implemented gchen 9/17/98
	}

/** Delete a model from the Optimization list.*/
	public void deleteOptimization(int index){
		if(index<0||index>=optimizations.size()){
			return;
		}
		optimizations.removeElementAt(index);
//		ProjectEvent evt = new ProjectEvent(this,"optimizationChanged");
//		fireEvent(evt);
	}

/** Delete a model from the Optimization list.*/
	public void deleteOptimization(NolOptimization opt){
		optimizations.removeElement(opt);
//		ProjectEvent evt = new ProjectEvent(this,"optimizationChanged");
//		fireEvent(evt);
	}

/** Return the Optimization list.*/
	public Vector getOptimizations(){
		return optimizations;
	}

/** Return the number of Optimization list.*/
	public int getNumberOfOptimizations(){
		return optimizations.size();
	}

/** Return the Optimization with the index.*/
	public NolOptimization getOptimization(int index){
		return (NolOptimization)optimizations.elementAt(index);
	}

/** Return Optimization index in the Optimization list.*/
	public int getOptimizationIndexByName(String optimizationName){
		int c = optimizations.size();
		for(int i=0;i<c;i++){
			NolOptimization m = (NolOptimization)optimizations.elementAt(i);
			if(m.getName().equals(optimizationName))
				return i;
		}
		return -1;
	}	

/**Save the file formats to a file.*/
	public void saveFileFormat(){
		VersionManagerForFileFormat versionForFileFormat = new VersionManagerForFileFormat();
		versionForFileFormat.setFileFormats(dataSeriesInputFormats);
		versionForFileFormat.saveToFile("fileformat.fmt");

// System.out.println("projectDirectory="+projectDirectory);
/*		if (projectDirectory == "") { 
			versionForFileFormat.saveToFile("fileformat.fmt");
		}else{
			versionForFileFormat.saveToFile(projectDirectory,"fileformat.fmt");
		}
/*		try {
			File sourceFile = new File("fileformat.fmt");	
        // Create the necessary output streams to save the data.
			FileOutputStream fos = new FileOutputStream(sourceFile); // Save to file
			GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
			ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
			out.writeObject(dataSeriesInputFormats);      // Write the entire Vector of scribbles
			out.flush();                 // Always flush the output.
			out.close();                 // And close the stream.
		}catch (IOException e) { System.out.println(e); }
*/	}

/**Load the file formats from a file.*/
	public void loadFileFormat(){
		try {
			File sourceFile = new File("fileformat.fmt");	
			FileInputStream fis = new FileInputStream(sourceFile); // Read from file
			GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
			ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
        // Read in an object.  It should be a vector of scribbles
			VersionManagerForFileFormat versionForFileFormat = (VersionManagerForFileFormat)in.readObject();
			in.close(); // Close the stream.
			this.dataSeriesInputFormats = versionForFileFormat.getFileFormats();
		} catch (IOException e) { 
			this.dataSeriesInputFormats = new Vector();
		} catch (ClassNotFoundException e) { 
			this.dataSeriesInputFormats = new Vector();
		} catch (RuntimeException e) { 
			this.dataSeriesInputFormats = new Vector();
		}
	}

	public void loadFileFormat(String dirFile){
		try {
			String fileName = dirFile+"\\fileformat.fmt";
			File sourceFile = new File(fileName);	
			FileInputStream fis = new FileInputStream(sourceFile); // Read from file
			GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
			ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
        // Read in an object.  It should be a vector of scribbles
			VersionManagerForFileFormat versionForFileFormat = (VersionManagerForFileFormat)in.readObject();
			in.close(); // Close the stream.
			this.dataSeriesInputFormats = versionForFileFormat.getFileFormats();
		} catch (IOException e) { 
			this.dataSeriesInputFormats = new Vector();
		} catch (ClassNotFoundException e) { 
			this.dataSeriesInputFormats = new Vector();
		} catch (RuntimeException e) { 
			this.dataSeriesInputFormats = new Vector();
		}
	}
/**Save the project to a file.*/
	public void saveBinary(String fileName){
		saveBinary(null,fileName);
	}

/**Save the project to a file.*/
	public void saveBinary(String directory, String fileName){

		Vector content = new Vector(11);

		content.addElement(name);
		content.addElement(rawDataSource);
		content.addElement(labelCategory);	
		content.addElement(joinedLabels);
		content.addElement(preprocessors);
		content.addElement(processedData);
		content.addElement(predictiveModels);
		content.addElement(optimizationModels);
		content.addElement(simulations);
		content.addElement(optimizations);
		content.addElement(dataSeriesInputFormats);

		String fName;
		if(fileName ==null){
			 fName = name+".prj";
		}else{
			fName = fileName;
		}
		try {
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fName);	
			else
				sourceFile = new File(directory,fName);
        // Create the necessary output streams to save the data.
			FileOutputStream fos = new FileOutputStream(sourceFile); // Save to file
			GZIPOutputStream gzos = new GZIPOutputStream(fos);     // Compresse
			ObjectOutputStream out = new ObjectOutputStream(gzos); // Save object
			out.writeObject(content);      // Write the entire Vector of scribbles
			out.flush();                 // Always flush the output.
			out.close();                 // And close the stream.
		}catch (IOException e) { 
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
	}

/**Load the content of the project from a file.*/
	public void loadBinary(String fileName){
		loadBinary(null,fileName);
	}
/**Load the content of the project from a file.*/

	// **** THIS IS DEAD CODE.  PROJECTS ARE NOW LOADED IN THE OBJECT LOADER THREAD ****
	public void loadBinary(String directory, String fileName){
		try {
        // Create necessary input streams
					
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fileName);	
			else
				sourceFile = new File(directory,fileName);
			FileInputStream fis = new FileInputStream(sourceFile); // Read from file
			GZIPInputStream gzis = new GZIPInputStream(fis);     // Uncompress
			ObjectInputStream in = new ObjectInputStream(gzis);  // Read objects
        // Read in an object.  It should be a vector of scribbles
			Vector content = (Vector)in.readObject();
			in.close(); // Close the stream.
			name = (String)content.elementAt(0);
			rawDataSource = (RawDataSource)content.elementAt(1);
			labelCategory = (Vector)content.elementAt(2);
			joinedLabels = (Vector)content.elementAt(3);
			preprocessors = (Vector)content.elementAt(4);
			processedData = (Vector)content.elementAt(5);
			predictiveModels = (Vector)content.elementAt(6);
			optimizationModels = (Vector)content.elementAt(7);
			simulations = (Vector)content.elementAt(8);
			optimizations = (Vector)content.elementAt(9);
			dataSeriesInputFormats = (Vector)content.elementAt(10);
		
			rawDataSource.initTransient(this);
			for(int i=0;i<preprocessors.size();i++){
				Preprocessor pre = (Preprocessor)preprocessors.elementAt(i);
				pre.initTransient(this);
			}
			for(int i=0;i<simulations.size();i++){
				ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)simulations.elementAt(i);
				sim.initTransient(this);
			}
			for(int i=0;i<optimizations.size();i++){
				NolOptimization opt = (NolOptimization)optimizations.elementAt(i);
				opt.initTransient(this);
			}
			for(int i=0;i<predictiveModels.size();i++){
				NolModel2 model = (NolModel2)predictiveModels.elementAt(i);
				model.initTransient(this);
			}
			for(int i=0;i<optimizationModels.size();i++){
				NolModel2 model = (NolModel2)optimizationModels.elementAt(i);
				model.initTransient(this);
			}
			
			for(int i=0;i<labelCategory.size();i++){
				NolLabel lab = (NolLabel)labelCategory.elementAt(i);
				lab.initTransient(this);
			}

			for(int i=0;i<preprocessors.size();i++){
				Preprocessor pre = (Preprocessor)preprocessors.elementAt(i);
				pre.initHasCode();
			}

			loadFileFormat();
		} catch (IOException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} catch (ClassNotFoundException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		} catch (RuntimeException e) { 
			System.err.println("Non-Fatal exception: " + e.getMessage());
			e.printStackTrace();
		}
	}

/** reset the transient field of all the object inside the project. **/
	public synchronized void initDataTreeForTransientField(){
		projectListeners  = new Vector(0,4);
		rawDataSource.initTransient(this);
		for(int i=0;i<preprocessors.size();i++){
			Preprocessor pre = (Preprocessor)preprocessors.elementAt(i);
			pre.initTransient(this);
		}
		for(int i=0;i<simulations.size();i++){
			ResponseSurfaceSimulation sim = (ResponseSurfaceSimulation)simulations.elementAt(i);
			sim.initTransient(this);
		}
		for(int i=0;i<optimizations.size();i++){
			NolOptimization opt = (NolOptimization)optimizations.elementAt(i);
			opt.initTransient(this);
		}
		for(int i=0;i<predictiveModels.size();i++){
			NolModel2 model = (NolModel2)predictiveModels.elementAt(i);
			model.initTransient(this);
		}
		for(int i=0;i<optimizationModels.size();i++){
			NolModel2 model = (NolModel2)optimizationModels.elementAt(i);
			model.initTransient(this);
		}
		
		for(int i=0;i<labelCategory.size();i++){
			NolLabel lab = (NolLabel)labelCategory.elementAt(i);
			lab.initTransient(this);
		}

		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			if(ds.getDataSource() == null){
				ds.initTransient(this);
			}
		}

		for(int i=0;i<preprocessors.size();i++){
			Preprocessor pre = (Preprocessor)preprocessors.elementAt(i);
			pre.initHasCode();
		}
		loadFileFormat();
	}


	public void changeDataSeriesName(DataSeries ds, String n){
		String oldName = ds.getName();
		for(int i=0;i<processedData.size();i++){
			DataSeries ds1 = (DataSeries)processedData.elementAt(i);
			if(ds1.getName().equals(oldName)){
				ds1.setName(n);
			}
		}
	}

/** Create a data project with a old version project. */
	public Project(Project project) {
		this.name = project.name;
		this.rawDataSource = project.rawDataSource;
		this.labelCategory = project.labelCategory;
		this.joinedLabels = project.joinedLabels;
		this.preprocessors = project.preprocessors;	  
		this.processedData = project.processedData;
		this.predictiveModels = project.predictiveModels;
		this.optimizationModels = project.optimizationModels;
		this.simulations = project.simulations;
		this.optimizations = project.optimizations;
		this.dataSeriesInputFormats = project.dataSeriesInputFormats;	 
		this.projectDirectory = project.projectDirectory;	 
	}

	public void setProjectDirectory(String dir){
		projectDirectory = dir;
	}

	public void setRawDataSource(RawDataSource dataSource){
		rawDataSource = dataSource;
	}
}

