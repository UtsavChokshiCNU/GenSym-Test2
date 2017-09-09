package com.gensym.nols.data;

/**
 *		Gensym Project2 Class.
 *		This class is extended from Object.class
 *		Modified 11/12/97 by Gchen
 */
import java.io.Serializable;
import java.util.Vector;

/** Project2 class */
public class Project2 extends Project implements Cloneable, Serializable {
  
  static final long serialVersionUID = 2L;
  private Vector bpnModels;
  private Vector annModels;
  private Vector rbfnModels;
  private Vector rhoModels;
  private Vector plsModels;
  private Vector pcaModels;
  private Vector genOptimizations;
  
  /** Create a null project with no argument */
	public Project2() {
		super();
		bpnModels = new Vector();
		annModels = new Vector();
		rbfnModels = new Vector();
		rhoModels = new Vector();
		plsModels = new Vector();
		pcaModels = new Vector();
		genOptimizations = new Vector();
	}

/** Create a data project with a given name. */
	public Project2(String name) {
		super(name);
		bpnModels = new Vector();
		annModels = new Vector();
		rbfnModels = new Vector();
		rhoModels = new Vector();
		plsModels = new Vector();
		pcaModels = new Vector();
		genOptimizations = new Vector();
	}
  
/** Create a data project2 from a old version project */
	public Project2(Project project) {
		super(project);
		bpnModels = new Vector();
		annModels = new Vector();
		rbfnModels = new Vector();
		rhoModels = new Vector();
		plsModels = new Vector();
		pcaModels = new Vector();
		genOptimizations = new Vector();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Project2 cloned = (Project2) super.clone();
		cloned.bpnModels = bpnModels == null ? null : (Vector) bpnModels.clone();
		cloned.annModels = annModels == null ? null : (Vector) annModels.clone();
		cloned.rbfnModels = rbfnModels == null ? null : (Vector) rbfnModels.clone();
		cloned.rhoModels = rhoModels == null ? null : (Vector) rhoModels.clone();
		cloned.plsModels = plsModels == null ? null : (Vector) plsModels.clone();
		cloned.pcaModels = pcaModels == null ? null : (Vector) pcaModels.clone();
		cloned.genOptimizations = genOptimizations == null ? null : (Vector) genOptimizations.clone();
		return cloned;
	}
  
/**  Add a new bpn model to the model list.*/
	public void addBpnModel(NolBpnModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getBpnModelIndexByName(((NolBpnModel)model).getName());
		if(mindex == -1)
			bpnModels.addElement(model);
		else
			bpnModels.setElementAt(model,mindex);
	}

/** Delete a bpn model from the bpn model list.*/
	public void deleteBpnModel(int index){
		if(index<0||index>=bpnModels.size()){
			return;
		}
		bpnModels.removeElementAt(index);
	}

/** Delete a bpn model from the bpn model list.*/
	public void deleteBpnModel(NolBpnModel model){
		bpnModels.removeElement(model);
	}

/** Return the bpn model list.*/
	public Vector getBpnModels(){
		return bpnModels;
	}

/** Return the number of bpn model list.*/
	public int getNumberOfBpnModels(){
		return bpnModels.size();
	}

/** Return the bpn model with the index.*/
	public NolBpnModel getBpnModel(int index){
		return (NolBpnModel)bpnModels.elementAt(index);
	}

/** Return model index in the bpn model list.*/
	public int getBpnModelIndexByName(String modelName){
		int c = bpnModels.size();
		for(int i=0;i<c;i++){
			NolBpnModel m = (NolBpnModel)bpnModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new ann model to the model list.*/
	public void addAnnModel(NolAnnModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getAnnModelIndexByName(((NolAnnModel)model).getName());
		if(mindex == -1)
			annModels.addElement(model);
		else
			annModels.setElementAt(model,mindex);
	}

/** Delete a ann model from the model list.*/
	public void deleteAnnModel(int index){
		if(index<0||index>=annModels.size()){
			return;
		}
		annModels.removeElementAt(index);
	}

/** Delete a ann model from the model list.*/
	public void deleteAnnModel(NolAnnModel model){
		annModels.removeElement(model);
	}

/** Return the ann model list.*/
	public Vector getAnnModels(){
		return annModels;
	}

/** Return the number of ann model list.*/
	public int getNumberOfAnnModels(){
		return annModels.size();
	}

/** Return the predictive ann model with the index.*/
	public NolAnnModel getAnnModel(int index){
		return (NolAnnModel)annModels.elementAt(index);
	}

/** Return model index in the ann model list.*/
	public int getAnnModelIndexByName(String modelName){
		int c = annModels.size();
		for(int i=0;i<c;i++){
			NolAnnModel m = (NolAnnModel)annModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new rbfn model to the model list.*/
	public void addRbfnModel(NolRbfnModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getRbfnModelIndexByName(((NolRbfnModel)model).getName());
		if(mindex == -1)
			rbfnModels.addElement(model);
		else
			rbfnModels.setElementAt(model,mindex);
	}

/** Delete a rbfn model from the rbfn model list.*/
	public void deleteRbfnModel(int index){
		if(index<0||index>=rbfnModels.size()){
			return;
		}
		rbfnModels.removeElementAt(index);
	}

/** Delete a rbfn model from the rbfn model list.*/
	public void deleteRbfnModel(NolRbfnModel model){
		rbfnModels.removeElement(model);
	}

/** Return the rbfn model list.*/
	public Vector getRbfnModels(){
		return rbfnModels;
	}

/** Return the number of rbfn model list.*/
	public int getNumberOfRbfnModels(){
		return rbfnModels.size();
	}

/** Return the rbfn model with the index.*/
	public NolRbfnModel getRbfnModel(int index){
		return (NolRbfnModel)rbfnModels.elementAt(index);
	}

/** Return model index in the rbfn model list.*/
	public int getRbfnModelIndexByName(String modelName){
		int c = rbfnModels.size();
		for(int i=0;i<c;i++){
			NolRbfnModel m = (NolRbfnModel)rbfnModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new rho model to the model list.*/
	public void addRhoModel(NolRhoModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getRhoModelIndexByName(((NolRhoModel)model).getName());
		if(mindex == -1)
			rhoModels.addElement(model);
		else
			rhoModels.setElementAt(model,mindex);
	}

/** Delete a rho model from the rho model list.*/
	public void deleteRhoModel(int index){
		if(index<0||index>=rhoModels.size()){
			return;
		}
		rhoModels.removeElementAt(index);
	}

/** Delete a rho model from the rho model list.*/
	public void deleteRhoModel(NolRhoModel model){
		rhoModels.removeElement(model);
	}

/** Return the rho model list.*/
	public Vector getRhoModels(){
		return rhoModels;
	}

/** Return the number of rho model list.*/
	public int getNumberOfRhoModels(){
		return rhoModels.size();
	}

/** Return the rho model with the index.*/
	public NolRhoModel getRhoModel(int index){
		return (NolRhoModel)rhoModels.elementAt(index);
	}

/** Return model index in the rho model list.*/
	public int getRhoModelIndexByName(String modelName){
		int c = rhoModels.size();
		for(int i=0;i<c;i++){
			NolRhoModel m = (NolRhoModel)rhoModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new rho model to the model list.*/
	public void addPlsModel(NolPlsModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getPlsModelIndexByName(((NolPlsModel)model).getName());
		if(mindex == -1)
			plsModels.addElement(model);
		else
			plsModels.setElementAt(model,mindex);
	}

/** Delete a pls model from the pls model list.*/
	public void deletePlsModel(int index){
		if(index<0||index>=plsModels.size()){
			return;
		}
		plsModels.removeElementAt(index);
	}

/** Delete a pls model from the pls model list.*/
	public void deletePlsModel(NolPlsModel model){
		plsModels.removeElement(model);
	}

/** Return the pls model list.*/
	public Vector getPlsModels(){
		return plsModels;
	}

/** Return the number of pls model list.*/
	public int getNumberOfPlsModels(){
		return plsModels.size();
	}

/** Return the pls model with the index.*/
	public NolPlsModel getPlsModel(int index){
		return (NolPlsModel)plsModels.elementAt(index);
	}

/** Return model index in the pls model list.*/
	public int getPlsModelIndexByName(String modelName){
		int c = plsModels.size();
		for(int i=0;i<c;i++){
			NolPlsModel m = (NolPlsModel)plsModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}

/**  Add a new pca model to the model list.*/
	public void addPcaModel(NolPcaModel model){		//gchen check  whether has the same name of a transforme 7.8.98
		int mindex = getPcaModelIndexByName(((NolPcaModel)model).getName());
		if(mindex == -1)
			pcaModels.addElement(model);
		else
			pcaModels.setElementAt(model,mindex);
	}

/** Delete a pca model from the pca model list.*/
	public void deletePcaModel(int index){
		if(index<0||index>=pcaModels.size()){
			return;
		}
		pcaModels.removeElementAt(index);
	}

/** Delete a pca model from the pca model list.*/
	public void deletePcaModel(NolPcaModel model){
		pcaModels.removeElement(model);
	}

/** Return the pca model list.*/
	public Vector getPcaModels(){
		return pcaModels;
	}

/** Return the number of pca model list.*/
	public int getNumberOfPcaModels(){
		return pcaModels.size();
	}

/** Return the pca model with the index.*/
	public NolPcaModel getPcaModel(int index){
		return (NolPcaModel)pcaModels.elementAt(index);
	}

/** Return model index in the pca model list.*/
	public int getPcaModelIndexByName(String modelName){
		int c = pcaModels.size();
		for(int i=0;i<c;i++){
			NolPcaModel m = (NolPcaModel)pcaModels.elementAt(i);
			if(m.getName().equals(modelName))
				return i;
		}
		return -1;
	}




/** reset the transient field of all the object inside the project. **/
	@Override
	public void initDataTreeForTransientField(){
		for(int i=0;i<bpnModels.size();i++){
			NolBpnModel m = (NolBpnModel)bpnModels.elementAt(i);
			m.initTransient(this);
		}
		for(int i=0;i<annModels.size();i++){
			NolAnnModel m = (NolAnnModel)annModels.elementAt(i);
			m.initTransient(this);
		}
		for(int i=0;i<rbfnModels.size();i++){
			NolRbfnModel m = (NolRbfnModel)rbfnModels.elementAt(i);
			m.initTransient(this);
		}
		for(int i=0;i<rhoModels.size();i++){
			NolRhoModel m = (NolRhoModel)rhoModels.elementAt(i);
			m.initTransient(this);
		}

		if(plsModels == null){
			plsModels = new Vector();
		}
		if(pcaModels == null){
			pcaModels = new Vector();
		}

		for(int i=0;i<plsModels.size();i++){
			NolPlsModel m = (NolPlsModel)plsModels.elementAt(i);
			m.initTransient(this);
		}
		for(int i=0;i<pcaModels.size();i++){
			NolPcaModel m = (NolPcaModel)pcaModels.elementAt(i);
			m.initTransient(this);
		}

		
		initGenOptimizations();
		for(int i=0;i<genOptimizations.size();i++){
			NolGenOptimization m = (NolGenOptimization)genOptimizations.elementAt(i);
			m.initTransient(this);
		}
		super.initDataTreeForTransientField();
	}

	private void initGenOptimizations(){
		if(genOptimizations == null)
			genOptimizations = new Vector();
	}

/**  Add a new general optimization to the optimization list.*/
	public void addGenOptimization(NolGenOptimization opt){	
		initGenOptimizations();
		int mindex = getGenOptimizationIndexByName(opt.getName());
		if(mindex == -1)
			genOptimizations.addElement(opt);
		else
			genOptimizations.setElementAt(opt,mindex);
	}

/** Delete a general optimization from the general optimization list.*/
	public void deleteGenOptimization(int index){
		initGenOptimizations();
		if(index<0||index>=genOptimizations.size()){
			return;
		}
		genOptimizations.removeElementAt(index);
	}

/** Delete a general optimization from the general optimization list.*/
	public void deleteGenOptimization(NolGenOptimization opt){
		initGenOptimizations();
		genOptimizations.removeElement(opt);
	}

/** Return the general optimization list.*/
	public Vector getGenOptimizations(){
		initGenOptimizations();
		return genOptimizations;
	}

/** Return the number of general optimization list.*/
	public int getNumberOfGenOptimizations(){
		initGenOptimizations();
		return genOptimizations.size();
	}

/** Return the general optimization with the index.*/
	public NolGenOptimization getGenOptimization(int index){
		initGenOptimizations();
		return (NolGenOptimization)genOptimizations.elementAt(index);
	}

/** Return opt index in the general optimization list.*/
	public int getGenOptimizationIndexByName(String optName){
		initGenOptimizations();
		int c = genOptimizations.size();
		for(int i=0;i<c;i++){
			NolGenOptimization m = (NolGenOptimization)genOptimizations.elementAt(i);
			if(m.getName().equals(optName))
				return i;
		}
		return -1;
	}

/** Initialize the hard upper and lower bounds of the variable.*/
	public void initializeHardBounds(){

		Vector processedData = getProcessedData();
		for(int i=0;i<processedData.size();i++){
			DataSeries ds = (DataSeries)processedData.elementAt(i);
			ds.initializeHardBounds();
		}
		Vector dds = getRawDataSource().getDataSeries();
		for(int i=0;i<dds.size();i++){
			DataSeries ds = (DataSeries)dds.elementAt(i);
			ds.initializeHardBounds();
		}
	}
}

