package com.gensym.nols.deploy;
/*
 *		Gensym OnlineOptimizer Class.
 *		This class is extended from Object.class
 *		Created 3/18/99 by Gchen
 */

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.OptionalDataException;
import java.io.Serializable;
import java.io.StreamCorruptedException;
import java.util.Vector;
import java.util.zip.GZIPInputStream;

import com.gensym.math.MathException;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.EnsembleModelEvent;
import com.gensym.math.datafit.EnsembleModelListener;
import com.gensym.math.datafit.TrainableModel;
import com.gensym.math.datafit.ValidationParameters;
import com.gensym.math.matrix.Matlib;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.INolOptimizeModel;
import com.gensym.nols.data.IPreprocessor;
import com.gensym.nols.data.NolModelTrainThread;
import com.gensym.nols.data.NolOptimization;
import com.gensym.nols.data.Processor;
import com.gensym.nols.data.Variable;
import com.gensym.nols.data.VersionManagerForOnlineOptimizer;

/** An OnlineOptimizer object provides a way to run the NOLStudio optimization online.
* The object maintains a data buffer for storing the online data. 
* The steps for online deployment: 
* 1. Create a OnlineOptimizer using default constructor.
* 2. Load exported optimization parameters from data file using loadOptimization method.
* 3. You can check the variable names and tags by call corresponding methods. 
* 4. Follow the user's guide for setting the optimization parameters.
* 5. Calculate the optimization.
* 6. Follow the user's guide to get output values. 
*/
//MK -- should this extend Preprocessor??
public class OnlineOptimizer
 implements EnsembleModelListener,Processor, Cloneable, Serializable {
	static final long serialVersionUID = 1L;

	private static int onlineOptimizerInstanceCount = 0;
	protected String name;
	private String comment; //Defaults are "".
	private NolOptimization optimization;
	private DataSeries outputData;
	private DataSeries inputData;
	private Vector stateNames = null;
	private Vector manipNames = null;
	private Vector exogNames = null;
	private Vector outputNames = null;
	private Vector varNames = null;  // contains all variables
	private Vector varTags = null;
	private int itsHashCode;
	private boolean isCalculated;

// New fixed return objects

	private double[] reBounds;
	private double[] reWeights;
	private double[] manipValues;
	private double[] exogValues;
	private double[] stateValues;
	private double[] outputValues;
	private boolean outputModelRetrained = false;
	private boolean stateModelRetrained = false;

	protected transient Vector itsEventListeners;

	private static final int OUTPUT = 0;
	private static final int MANIPULATED = 1;
	private static final int EXOGENOUS = 2;
	private static final int STATE = 3;
	private static final int BOUNDS_ARRAY_SIZE = 7;
	private static final int WEIGHTS_ARRAY_SIZE = 4;

	private int statusFlag; //Added gchen 6.28.2000, for returning the status of optimization
	private String statusMessage = ""; //Added gchen 6.28.2000, for returning the message of optimization

	private double[] outputTestRMSE;
	private double[] outputTestCORR;
	private double[] outputTrainRMSE;
	private double[] outputTrainCORR;
	private double outputModelRateValue;

	private double[] stateTestRMSE;
	private double[] stateTestCORR;
	private double[] stateTrainRMSE;
	private double[] stateTrainCORR;
	private double stateModelRateValue;


/*
	private static Frame errorFrame;
	private static TextArea errorTA;
	private static SimpleDateFormat df;
	private static int iteration;
	private transient BufferedWriter target = null;
  */

	private boolean debugMode = false;

/** Create a null OnlineOptimizer with no argument */
	public OnlineOptimizer() {
		super();
		name = "OnlineOptimizer" + onlineOptimizerInstanceCount;
		comment = "";
		onlineOptimizerInstanceCount++;
		outputNames = new Vector(0,10);
		manipNames = new Vector(0,10);
		exogNames = new Vector(0,10);
		stateNames = new Vector(0,10);
		varNames = new Vector(0,10);
		varTags = new Vector(0,10);
		itsHashCode = hashCode();
		isCalculated = false;
		itsEventListeners = new Vector();

		statusFlag = 0;
		reBounds = new double[BOUNDS_ARRAY_SIZE];
		reWeights = new double[WEIGHTS_ARRAY_SIZE];

	}

/** Create a data OnlineOptimizer from a given name. This is not for online use.*/
	public OnlineOptimizer(String name, NolOptimization opt)
		throws MathException {
		this();
		optimization = opt;
		this.name = name;
		onlineOptimizerInstanceCount--;  // name is provided, decrement count that was incremented in this()
		initialize(opt);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		OnlineOptimizer cloned = (OnlineOptimizer) super.clone();
		
		cloned.optimization = optimization == null ? null : (NolOptimization) optimization.clone();
		cloned.outputData = outputData == null ? null : (DataSeries) outputData.clone();
		cloned.inputData = inputData == null ? null : (DataSeries) inputData.clone();
		cloned.stateNames = stateNames == null ? null : (Vector) stateNames.clone();
		cloned.manipNames = manipNames == null ? null : (Vector) manipNames.clone();
		cloned.exogNames = exogNames == null ? null : (Vector) exogNames.clone();
		cloned.outputNames = outputNames == null ? null : (Vector) outputNames.clone();
		cloned.varNames = varNames == null ? null : (Vector) varNames.clone();
		cloned.varTags = varTags == null ? null : (Vector) varTags.clone();
		cloned.itsEventListeners = itsEventListeners == null ? null : (Vector) itsEventListeners.clone();

		return cloned;
	}

/** Initialize the properties of the OnlineOptimizer. */
	private void initialize(NolOptimization opt) throws MathException {
		INolOptimizeModel model = opt.getModel();
		outputNames = (Vector)model.getOutputVarNames().clone();
		manipNames = (Vector)model.getManipulate().clone();
		exogNames = (Vector)model.getExogenous().clone();
		stateNames = (Vector)model.getState().clone();
		IPreprocessor prep = model.getPreprocessor();

		int no = outputNames.size();
		int nm = manipNames.size();
		int ne = exogNames.size();
		int ns = stateNames.size();
		int ni = nm+ne+ns;
		
		manipValues = new double[nm];
		exogValues = new double[ne];
		stateValues = new double[ns];
		outputValues = new double[no];

		outputData = new DataSeries(1,no);
		for(int i=0;i<no;i++){
			String varName = (String)outputNames.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			varNames.addElement(varName);
			String varTag = colObj.getTag();
			varTags.addElement(varTag);
			outputData.setVariableParameters(i,varTag,varName,"None");
			Variable colObjNew = outputData.getVarByIndex(i);
			colObjNew.setStatistics(colObj.getStatistics());
			colObjNew.setUnit(colObj.getUnit());
		}
		
		inputData = new DataSeries(1,ni);
		int cc = 0;
		for(int i=0;i<nm;i++){
			String varName = (String)manipNames.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			varNames.addElement(varName);
			String varTag = colObj.getTag();
			varTags.addElement(varTag);
			inputData.setVariableParameters(cc,varTag,varName,"None");
			inputData.setValueAt(0,cc,colObj.getMeanValue());
			Variable colObjNew = inputData.getVarByIndex(cc);
			colObjNew.setStatistics(colObj.getStatistics());
			colObjNew.setUnit(colObj.getUnit());
			cc++;
		}
		for(int i=0;i<ne;i++){
			String varName = (String)exogNames.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			varNames.addElement(varName);
			String varTag = colObj.getTag();
			varTags.addElement(varTag);
			inputData.setVariableParameters(cc,varTag,varName,"None");
			inputData.setValueAt(0,cc,colObj.getMeanValue());
			Variable colObjNew = inputData.getVarByIndex(cc);
			colObjNew.setStatistics(colObj.getStatistics());
			colObjNew.setUnit(colObj.getUnit());
			cc++;
		}

		for(int i=0;i<ns;i++){
			String varName = (String)stateNames.elementAt(i);
			Variable colObj = prep.getVariableFromVariableName(varName);
			varNames.addElement(varName);
			String varTag = colObj.getTag();
			varTags.addElement(varTag);
			inputData.setVariableParameters(cc,varTag,varName,"None");
			inputData.setValueAt(0,cc,colObj.getMeanValue());
			Variable colObjNew = inputData.getVarByIndex(cc);
			colObjNew.setStatistics(colObj.getStatistics());
			colObjNew.setUnit(colObj.getUnit());
			cc++;
		}
	}

/** Get the name of this optimization problem. */
  @Override
  public String getName(){
       return name;
	}
	
/** Set the name of this  optimization problem. */
	public void setName(String c){
		name = c;
	}	
	
/** Return the comment of this  optimization problem.*/
	public String getComment(){
		return comment;
	}

/** Set the comment of this  optimization problem.*/
	public void setComment(String c){
		comment = c;
	}

/** Get the hasCode for this optimization problem.*/
	public int getItsHashCode(){
		return itsHashCode;
	}


/** Load the model and formulas from a file. This is not recommended.
	It is better providing the directory name.*/ 
	public void loadOptimization(String fileName)throws	FileNotFoundException,IOException,StreamCorruptedException, OptionalDataException,ClassNotFoundException{
		loadOptimization(fileName,null);
	}

/** Load the model and formulas from a file.*/ 
	public void loadOptimization(String fileName, String directory)throws	FileNotFoundException,IOException,StreamCorruptedException, OptionalDataException,ClassNotFoundException{
		try{
			File sourceFile;
			if(directory==null)
				sourceFile = new File(fileName);	
			else
				sourceFile = new File(directory,fileName);
			FileInputStream fis = new FileInputStream(sourceFile); 
			GZIPInputStream gzis = new GZIPInputStream(fis);   
			ObjectInputStream in = new ObjectInputStream(gzis); 
			VersionManagerForOnlineOptimizer ver  = (VersionManagerForOnlineOptimizer)in.readObject();
			OnlineOptimizer opt = ver.getOptimizer();
			copyToThis(opt);
			in.close(); 
		}catch (StreamCorruptedException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (OptionalDataException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (FileNotFoundException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (IOException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}catch (ClassNotFoundException evt){
			System.err.println("Non-Fatal exception: " + evt.getMessage());
			evt.printStackTrace();
			throw evt;
		}
	}

	public void copyToThis(OnlineOptimizer opt) {
		name = opt.name;
		comment = opt.comment;
		optimization = opt.optimization;
		outputData = opt.outputData;
		inputData = opt.inputData;
		manipNames = opt.manipNames;
		exogNames = opt.exogNames;
		stateNames = opt.stateNames;
		outputNames = opt.outputNames;
		varNames = opt.varNames;
		varTags = opt.varTags;
		itsHashCode = hashCode();
		itsEventListeners = new Vector();
		if(outputData != null)
			outputData.initVarTransient();
		if(inputData != null)
			inputData.initVarTransient();
		isCalculated = false;

		int no = outputNames.size();
		int nm = manipNames.size();
		int ne = exogNames.size();
		int ns = stateNames.size();
		int ni = nm+ne+ns;
		
		manipValues = new double[nm];
		exogValues = new double[ne];
		stateValues = new double[ns];
		outputValues = new double[no];

		reBounds = new double[BOUNDS_ARRAY_SIZE];
		reWeights = new double[WEIGHTS_ARRAY_SIZE];

		statusFlag = 0;
//		iteration = 0;

	}

/** Calculate the optimization and return the status flag.*/
	public int optimize(){
		try{
			calculate();
		}catch(MathException evt){}
		return statusFlag;
	}

/** Calculate the optimization.*/
	public void calculate() throws MathException 
	/* eg - none of these are thrown?????   NoSuchMethodException, 
	   SecurityException,InstantiationException, ParseException,
	   IllegalAccessException,InvocationTargetException,  FormulaException*/ { 
//		iteration++;
		if(isCalculated) {
			return;  
		}
		try{
			// MK -- Illegal call, should signal a run-time error		
			Matrix initX = null;
			INolOptimizeModel optModel = optimization.getModel();
			if(optModel.getModel()!=null && optModel.getStateModel()==null){
				Vector inputs = optModel.getInputs();
				int nin = inputs.size();
				initX = Matlib.createMatrix(1,nin);
				for(int i=0;i<nin;i++){
					String varName = (String)inputs.elementAt(i);
					int cols = inputData.getVarIndexByName(varName);
					initX.set(0,i,inputData.getValueAt(0,cols));
				}
			}else if(optModel.getStateModel()!=null){
				Vector stateInputs = optModel.getStateInput();
				Vector inputs = optModel.getInputs();
				int nin = optModel.getNin();
				int sc = stateNames.size(); 
				int ic = inputs.size(); 
				int sic = stateInputs.size(); 
				initX = Matlib.createMatrix(1,nin);
				int cc=0;
				for(int i=0;i<sic+ic;i++){
				  if(i<sic){
					String varName = (String)stateInputs.elementAt(i);
					int cols = inputData.getVarIndexByName(varName);
					initX.set(0,i,inputData.getValueAt(0,cols));
				  }else{
					String varName = (String)inputs.elementAt(i-sic);
					if(!stateNames.contains(varName) && !stateInputs.contains(varName)){
					  int cols = inputData.getVarIndexByName(varName);
					  initX.set(0,sic+cc,inputData.getValueAt(0,cols));
					  cc++;
					}
				  }
				}
			}
			optimization.setInitX(initX);
			optimization.setCalculated(false);
			optimization.calculationOptimization();
			statusFlag = optimization.getStatusFlag();
			statusMessage = optimization.getStatusMessage();
			Matrix Y = optimization.getYResult();
			Matrix X = optimization.getXResult();

	//		try to clear memory. gchen 6.21.2000
			Matlib.clear(initX); 
			if(optModel.getStateModel()!=null){
			  int sc = stateNames.size(); 
			  for(int c=0;c<sc;c++){
				String varName = (String)stateNames.elementAt(c);
				int cols = inputData.getVarIndexByName(varName);
				inputData.setValueAt(0,cols,Y.get(0,c));
			  }
			  for(int c=0;c<outputNames.size();c++){
				outputData.setValueAt(0,c,Y.get(0,sc+c));
			  }
			}else{
			  for(int c=0;c<outputNames.size();c++){
				outputData.setValueAt(0,c,Y.get(0,c));
			  }
			}
			if(optModel.getModel()!=null && optModel.getStateModel()==null){
			  Vector inputs = optModel.getInputs();
			  int nin = inputs.size();
			  for(int i=0;i<nin;i++){
				String varName = (String)inputs.elementAt(i);
				int cols = inputData.getVarIndexByName(varName);
				inputData.setValueAt(0,cols,X.get(0,i));
			  }
			}else if(optModel.getStateModel()!=null){
			  Vector stateInputs = optModel.getStateInput();
			  Vector inputs = optModel.getInputs();
			  int ic = inputs.size(); 
			  int sic = stateInputs.size(); 
			  int cc=0;
			  for(int i=0;i<sic+ic;i++){
				if(i<sic){
				  String varName = (String)stateInputs.elementAt(i);
				  int cols = inputData.getVarIndexByName(varName);
				  inputData.setValueAt(0,cols,X.get(0,i));
				}else{
				  String varName = (String)inputs.elementAt(i-sic);
				  if(!stateNames.contains(varName) && !stateInputs.contains(varName)){
					int cols = inputData.getVarIndexByName(varName);
					inputData.setValueAt(0,cols,X.get(0,sic+cc));
					cc++;
				  }
				}
			  }
			}
		}catch(MathException evt){
			if(debugMode){ 
				String str = evt.getMessage()+"\n"+ com.gensym.nols.deployutil.DebugUtil.getStackTrace (evt);
				System.out.println(str);
			}
			throw evt;
		}
		isCalculated = true;
		if(statusFlag == 1){
			throw new MathException("Simplex.optimize: Reached maximum iteration number, failed to converge.");
		}
	}

/** Return the variable names of specified variable type. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/

	public String[] getVariableNames(int type){
	 if(type == OUTPUT){
	   int c = outputNames.size();
	   String[] names = new String[c];
	   for(int i=0;i<c;i++){
		 names[i] = (String)outputNames.elementAt(i);
	   }
	   return names;
	 }else if(type == MANIPULATED){
	   int c = manipNames.size();
	   String[] names = new String[c];
	   for(int i=0;i<c;i++){
		 names[i] = (String)manipNames.elementAt(i);
	   }
	   return names;
	 }else if(type == EXOGENOUS){
	   int c = exogNames.size();
	   String[] names = new String[c];
	   for(int i=0;i<c;i++){
		 names[i] = (String)exogNames.elementAt(i);
	   }
	   return names;
	 }else if(type == STATE){
	   int c = stateNames.size();
	   String[] names = new String[c];
	   for(int i=0;i<c;i++){
		 names[i] = (String)stateNames.elementAt(i);
	   }
	   return names;
	 }
	 return null;
	}
   
   /** Return the variable tags of specified variable type. 
     (0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
     */
  public String[] getVariableTags(int type){
    if(type == OUTPUT){
      int c = outputNames.size();
      String[] tags = new String[c];
      for(int i=0;i<c;i++){
	String outputName = (String)outputNames.elementAt(i);
	int index = varNames.indexOf(outputName);
	tags[i] = (String)varTags.elementAt(index);
      }
      return tags;
    }else if(type == MANIPULATED){
      int c = manipNames.size();
      String[] tags = new String[c];
      for(int i=0;i<c;i++){
	String manipName = (String)manipNames.elementAt(i);
	int index = varNames.indexOf(manipName);
	tags[i] = (String)varTags.elementAt(index);
      }
      return tags;
    }else if(type == EXOGENOUS){
      int c = exogNames.size();
      String[] tags = new String[c];
      for(int i=0;i<c;i++){
	String exogName = (String)exogNames.elementAt(i);
	int index = varNames.indexOf(exogName);
	tags[i] = (String)varTags.elementAt(index);
      }
      return tags;
    }else if(type == STATE){
      int c = stateNames.size();
      String[] tags = new String[c];
      for(int i=0;i<c;i++){
	String stateName = (String)stateNames.elementAt(i);
	int index = varNames.indexOf(stateName);
	tags[i] = (String)varTags.elementAt(index);
      }
      return tags;
    }
    return null;
  }


/** Return the variable units of specified variable type. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/

	public String[] getVariableUnits(int type){
		try{
			if(type == OUTPUT){
				int c = outputNames.size();
				String[] units = new String[c];
				for(int i=0;i<c;i++){
				   String n = (String)outputNames.elementAt(i);
				   Variable varObj = getVariableByName(n);
				   units[i] = varObj.getUnit();
				}
				return units;
			}else if(type == MANIPULATED){
				int c = manipNames.size();
				String[] units = new String[c];
				for(int i=0;i<c;i++){
				   String n = (String)manipNames.elementAt(i);
				   Variable varObj = getVariableByName(n);
				   units[i] = varObj.getUnit();
				}
				return units;
			}else if(type == EXOGENOUS){
				int c = exogNames.size();
				String[] units = new String[c];
				for(int i=0;i<c;i++){
				   String n = (String)exogNames.elementAt(i);
				   Variable varObj = getVariableByName(n);
				   units[i] = varObj.getUnit();
				}
				return units;
			}else if(type == STATE){
				int c = stateNames.size();
				String[] units = new String[c];
				for(int i=0;i<c;i++){
				   String n = (String)stateNames.elementAt(i);
				   Variable varObj = getVariableByName(n);
				   units[i] = varObj.getUnit();
				}
				return units;
			}
		}catch(MathException evt){

		}
	 return null;
	}
   


/** Return the number of variables for specified variable type.
  (0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
  */
  public int getNumberOfVariables(int type){
    if(type == OUTPUT){
      int c = outputNames.size();
      return c;
    }else if(type == MANIPULATED){
      int c = manipNames.size();
      return c;
    }else if(type == EXOGENOUS){
      int c = exogNames.size();
      return c;
    }else if(type == STATE){
      int c = stateNames.size();
      return c;
    }
    return 0;
  }

   /** Set the value by variable name. This method is used to set the initial
     values for manipulated variables and the values for exogenous variables.*/
  public void setValueByName(String varName, double val)throws MathException{
    int im = manipNames.indexOf(varName);
    int ie = exogNames.indexOf(varName);
    if(im != -1 && ie != -1){
      throw new MathException("Wrong variable name.");	
    }
    int cols = inputData.getVarIndexByName(varName);
    inputData.setValueAt(0,cols,val);
	if(ie != -1){
		double[] bvs = getBoundsByName(varName);
		bvs[2] = val;
		setBoundsByName(varName,bvs);
	}
	isCalculated = false;
  }

   /** Set the value by variable tag. This method is used to set the initial
     values for manipulated variables and the values for exogenous variables.*/
  public void setValueByTag(String tag, double Val)throws MathException{
    int index = varTags.indexOf(tag);
    if(index == -1) {
    	throw new MathException("Wrong variable tag.");	
    }
    String varName = (String)varNames.elementAt(index);
    setValueByName(varName,Val);
  }
   
   
   /** Return the value by variable tag. This method can be used to get the values of 
     each variable before calculation and after calculation. */
  public double getValueByName(String varName)throws MathException{
    int cols1 = inputData.getVarIndexByName(varName);
    int cols2 = outputData.getVarIndexByName(varName);
    double v = Double.NaN;
    if(cols1 != -1){
      v = inputData.getValueAt(0,cols1);
    }else if(cols2 != -1){
      v = outputData.getValueAt(0,cols2);
    }else{
      throw new MathException("Wrong variable name.");	
    }
    return v;
  }
   
/** Return the value by variable tag. This method can be used to get the values of 
  each variable before calculation and after calculation. */
  public double getValueByTag(String tag)throws MathException{
    int index = varTags.indexOf(tag);
    if(index == -1) {
    	throw new MathException("Wrong variable tag.");	
    }
    String varName = (String)varNames.elementAt(index);
    return getValueByName(varName);
  }
   
   /** Get the value array for specified variable type. The order of value array is the 
same as the order of name array. 
(0: outputs; 1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public double[] getValues(int type) throws MathException{
		if(type == OUTPUT){
			for(int i=0;i<outputValues.length;i++){
				outputValues[i] = outputData.getValueAt(0,i);
			}
			return outputValues;
		}else if(type == MANIPULATED){
			for(int i=0;i<manipValues.length;i++){
				String manipName = (String)manipNames.elementAt(i);
				int cols = inputData.getVarIndexByName(manipName);
				manipValues[i] = inputData.getValueAt(0,cols);
			}
			return manipValues;
		}else if(type == EXOGENOUS){
			for(int i=0;i<exogValues.length;i++){
				String exogName = (String)exogNames.elementAt(i);
				int cols = inputData.getVarIndexByName(exogName);
				exogValues[i] = inputData.getValueAt(0,cols);
			}
			return exogValues;
		}else if(type == STATE){
			for(int i=0;i<stateValues.length;i++){
				String stateName = (String)stateNames.elementAt(i);
				int cols = inputData.getVarIndexByName(stateName);
				stateValues[i] = inputData.getValueAt(0,cols);
			}
			return stateValues;
		}
		return null;
	}

/** Set the value array for specified variable type. The order of value array is the 
same as the order of name array. 
(1: manipulated variables; 2: exogenous variables; 3: state variables.)
*/
	public void setValues(int type, double[] vals)throws MathException{
		if(type == MANIPULATED){
			int c = manipNames.size();
			for(int i=0;i<c;i++){
				String manipName = (String)manipNames.elementAt(i);
				int cols = inputData.getVarIndexByName(manipName);
				inputData.setValueAt(0,cols,vals[i]);
			}
		}else if(type == EXOGENOUS){
			int c = exogNames.size();
			for(int i=0;i<c;i++){
				String exogName = (String)exogNames.elementAt(i);
				int cols = inputData.getVarIndexByName(exogName);
				inputData.setValueAt(0,cols,vals[i]);
				double[] bvs = getBoundsByName(exogName);
				bvs[2] = vals[i];
				setBoundsByName(exogName,bvs);
			}
		}else if(type == STATE){
			int c = stateNames.size();
			for(int i=0;i<c;i++){
				String stateName = (String)stateNames.elementAt(i);
				int cols = inputData.getVarIndexByName(stateName);
				inputData.setValueAt(0,cols,vals[i]);
			}
		}
		isCalculated = false;
	}
	
/** Set the bounds by variable name. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
	public void setBoundsByName(String varName, double[] bounds)throws MathException{
		int index = varNames.indexOf(varName);
		if(index == -1) {
			throw new MathException("Wrong variable name.");	
		}
		double[] bb = optimization.getBounds(varName);
		bb[0] = bounds[0];
		bb[1] = bounds[1];
		bb[2] = bounds[2];
		bb[3] = bounds[3];
		bb[4] = bounds[4];
		isCalculated = false;
	}

/** Set the bounds by variable tag. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
	public void setBoundsByTag(String tag, double[] bounds)throws MathException{
		int index = varTags.indexOf(tag);
		if(index == -1) {
			throw new MathException("Wrong variable tag.");	
		}
		String varName = (String)varNames.elementAt(index);
		setBoundsByName(varName,bounds);
		isCalculated = false;
	}

	
/** Return the bounds by variable name. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
	public double[] getBoundsByName(String varName)throws MathException{
		int index = varNames.indexOf(varName);
		if(index == -1) {
			throw new MathException("Wrong variable name.");
		}
		double[] bb = optimization.getBounds(varName);
		System.arraycopy(bb,0,reBounds,0,bb.length);
		return reBounds;
	}

/** Return the bounds by variable tag. This method if for all variables.
The order of the bounds is [hlBound, slBound, setpoint, suBound, huBound].
*/
	public double[] getBoundsByTag(String tag)throws MathException{
		int index = varTags.indexOf(tag);
		if(index == -1) {
			throw new MathException("Wrong variable tag.");	
		}
		String varName = (String)varNames.elementAt(index);
		return getBoundsByName(varName);
	}

	

/** Set the weights by variable name. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
	public void setWeightsByName(String varName, double[] weights)throws MathException{
		int index = varNames.indexOf(varName);
		if(index == -1) {
			throw new MathException("Wrong variable name.");
		}
		double[] ww = optimization.getWeights(varName);
		ww[0] = weights[0];
		ww[1] = weights[1];
		ww[2] = weights[2];
		ww[3] = weights[3];
		isCalculated = false;
	}

/** Set the weights by variable tag. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
	public void setWeightsByTag(String tag, double[] weights)throws MathException{
		int index = varTags.indexOf(tag);
		if(index == -1) {
			throw new MathException("Wrong variable tag.");
		}
		String varName = (String)varNames.elementAt(index);
		setWeightsByName(varName,weights);
	}

	
/** Return the weights by variable name. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
	public double[] getWeightsByName(String varName)throws MathException{
		int index = varNames.indexOf(varName);
		if(index == -1) {
			throw new MathException("Wrong variable name.");
		}
		double[] ww = optimization.getWeights(varName);
		System.arraycopy(ww,0,reWeights,0,ww.length);
		return reWeights;
	}

/** Return the weights by variable tag. This method if for all variables.
The order of the bounds is [linWeight, setpointWeight,subWeight,slbWeight].
*/
	public double[] getWeightsByTag(String tag)throws MathException{
		int index = varTags.indexOf(tag);
		if(index == -1) {
			throw new MathException("Wrong variable tag.");
		}
		String varName = (String)varNames.elementAt(index);
		return getWeightsByName(varName);
	}
	
	public String toStringForTest(){
		String s = "";
		return s;
	}


/** Get variable object from variable name.*/
	private Variable getVariableByName(String varName) throws MathException{
		Variable varObj = inputData.getVarByName(varName); 
		if(varObj == null){
			varObj = outputData.getVarByName(varName);
		}
		if(varObj == null){
		  throw new MathException("Wrong variable name.");	
		}
		return varObj;
	}

/** Get variable statistics from variable name.*/
	private double[] getVarStatisticsByName(String varName) throws MathException{
		Variable varObj = getVariableByName(varName);
		if(varObj == null) {
			throw new MathException("Wrong variable name.");	
		}
		double[] statistics = varObj.getStatistics();
		return statistics;
	}

/** Get the data max from variable name.*/
	public double getMaxValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[8];
	}

/** Get the data max from variable tag.*/
	public double getMaxValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMaxValueByName(varName);
	}

/** Get the data min from variable name.*/
	public double getMinValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[7];
	}

/** Get the data min from variable tag.*/
	public double getMinValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMinValueByName(varName);
	}

/** Get the data mean from variable name.*/
	public double getMeanValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[0];
	}

/** Get the data mean from variable tag.*/
	public double getMeanValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMeanValueByName(varName);
	}

/** Get the data median from variable name.*/
	public double getMedianValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[1];
	}

/** Get the data median from variable tag.*/
	public double getMedianValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getMedianValueByName(varName);
	}

/** Get the data sum from variable name.*/
	public double getSumValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[9];
	}

/** Get the data sum from variable tag.*/
	public double getSumValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSumValueByName(varName);
	}

/** Get the data std from variable name.*/
	public double getSTDValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[2];
	}

/** Get the data std from variable tag.*/
	public double getSTDValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSTDValueByName(varName);
	}

/** Get the data variance from variable name.*/
	public double getVarianceValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[3];
	}

/** Get the data variance from variable tag.*/
	public double getVarianceValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getVarianceValueByName(varName);
	}

/** Get the data kurt from variable name.*/
	public double getKurtValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[4];
	}

/** Get the data kurt from variable tag.*/
	public double getKurtValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getKurtValueByName(varName);
	}

/** Get the data skew from variable name.*/
	public double getSkewValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[5];
	}

/** Get the data skew from variable tag.*/
	public double getSkewValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getSkewValueByName(varName);
	}

/** Get the data range from variable name.*/
	public double getRangeValueByName(String varName) throws MathException{
		double[] statistics = getVarStatisticsByName(varName);
		return statistics[6];
	}

/** Get the data range from variable tag.*/
	public double getRangeValueByTag(String varTag) throws MathException{
		int index = varTags.indexOf(varTag);
		String varName = (String)varNames.elementAt(index);
		return getRangeValueByName(varName);
	}

/** Return the status flag of the optimization problem.*/
	public int getStatusFlag(){
		return statusFlag;
	}

/** Return the status message of the optimization problem.*/
	public String getStatusMessage(){
		return statusMessage;
	}

/** Return the model of the optimization problem.*/
	public INolOptimizeModel getModel(){
		return optimization.getModel();
	}

/** Return the input number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfOutputModelInputs(){
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getModel();
		return ensemble.getNin();
	}

/** Return the output number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfOutputModelOutputs(){
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getModel();
		return ensemble.getNout();
	}

/** Return the input number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfStateModelInputs(){
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getStateModel();
		if(ensemble == null) {
			return 0;
		}
		return ensemble.getNin();
	}

/** Return the output number of ensemble model. This is an internal method used for checking*/
	public int getNumberOfStateModelOutputs(){
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getStateModel();
		if(ensemble == null) {
			return 0;
		}
		return ensemble.getNout();
	}


/** Retrain the output model in this optimizer.*/
	public void trainOutputModel(Vector modelListeners, Matrix X, Matrix Y, double timeInMilli, boolean autoStop, boolean newTraining, boolean display) throws MathException{
		
		if(X.getRows() != Y.getRows()){
			throw new MathException("Input and Output don't have the same number of samples.");
		}
		if(X.getRows() <10){
			throw new MathException("There is not enough data for training.");
		}

		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getModel();
		int nin = ensemble.getNin();
		int nout = ensemble.getNout();

		if(X.getCols() != nin){
			throw new MathException("The input matrx does not match the model input.");
		}
		if(Y.getCols() != nout){
			throw new MathException("The output matrx does not match the model input.");
		}
		if(newTraining){
			ensemble.clearModels();
		}
		ensemble.setTrainingTime((long)timeInMilli);  
		ensemble.useAutomaticStopping(autoStop);
		ensemble.removeAllListeners();
		ensemble.addListener(this);

		NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
		Thread trainingthread = new Thread(trainerThread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY) {
			prior = Thread.MIN_PRIORITY;
		}
		trainingthread.setPriority(prior);
		trainerThread.setInput1(X);
		trainerThread.setOutput1(Y);
		
		if(display){
			if(modelListeners == null){
				OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
				ensemble.addListener(onlineModelListener);
				NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setOneModelMode(true);
				console.setVisible(true);
				console.toFront();	
			}else{
				OnlineModelListener foundListener = null;
				boolean found = false;
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
					if(listener instanceof OnlineModelListener && !found){
						found = true;
						foundListener = (OnlineModelListener) listener;
					}
				}
				if(!found){
					foundListener = new OnlineModelListener(this, display);
					ensemble.addListener(foundListener);
				}
				NolOnlineConsoleFrame console = foundListener.getOnlineConsole();
				console.setModel1TrainInput(X);
				console.setModel1TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100, 100, 750, 500);
				console.setReady(false);
				console.setOneModelMode(true);
				console.setVisible(true);
				console.toFront();
			}
		}else{
			if(modelListeners != null){
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
				}
			}
		}
		
		trainingthread.start();
		isCalculated = false;
	}

	/** Retrain the state model in this optimizer.*/
	public void trainStateModel(Vector modelListeners, Matrix X, Matrix Y, double timeInMilli, boolean autoStop, boolean newTraining, boolean display) throws MathException{
		
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getStateModel();
		if(ensemble == null){
			throw new MathException("There is no state model for training.");
		}

		if(X.getRows() != Y.getRows()){
			throw new MathException("Input and Output don't have the same number of samples.");
		}
		if(X.getRows() <10){
			throw new MathException("There is not enough data for training.");
		}

		int nin = ensemble.getNin();
		int nout = ensemble.getNout();
		if(X.getCols() != nin){
			throw new MathException("The input matrx does not match the model input.");
		}
		if(Y.getCols() != nout){
			throw new MathException("The output matrx does not match the model input.");
		}
		if(newTraining){
			ensemble.clearModels();
		}
		ensemble.setTrainingTime((long)timeInMilli);  
		ensemble.useAutomaticStopping(autoStop);
		ensemble.removeAllListeners();
		ensemble.addListener(this);

		NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble);
		Thread trainingthread = new Thread(trainerThread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		trainingthread.setPriority(prior);
		trainerThread.setInput1(X);
		trainerThread.setOutput1(Y);
		if(display){
			if(modelListeners == null){
				OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
				ensemble.addListener(onlineModelListener);
				NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
				console.setModel2TrainInput(X);
				console.setModel2TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100,100,750,500);
				console.setReady(false);
				console.setOneModelMode(true);
				console.setVisible(true);
				console.toFront();	
			}else{
				boolean found = false;
				OnlineModelListener foundOLModelListener = null;
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
					if(listener instanceof OnlineModelListener && found==false ){
						foundOLModelListener = (OnlineModelListener) listener;
						found = true;
					}
				}
				if(!found){
					foundOLModelListener = new OnlineModelListener(this, display);
					ensemble.addListener(foundOLModelListener);
				}
				NolOnlineConsoleFrame console = foundOLModelListener.getOnlineConsole();
				console.setModel2TrainInput(X);
				console.setModel2TrainOutput(Y);
				console.setOutputModelTrainingThread(trainingthread);
				console.setBounds(100, 100, 750, 500);
				console.setOneModelMode(true);
				console.setReady(false);
				console.setVisible(true);
				console.toFront();
			}
		}else{
			if(modelListeners != null){
				for (int i=0;i<modelListeners.size();i++){
					EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
					ensemble.addListener(listener);
				}
			}
		}
		trainingthread.start();
		isCalculated = false;
	}

/** Retrain the output model in this processor. The data is stored in two ascii file.*/
	public void trainOutputModelFromFile(Vector modelListeners, String inputFileName, String outputFileName, double timeInMilli, boolean autoStop, boolean newTraining, boolean display)
	throws IOException, MathException
	{
		Matrix X = Matrix.readFromFile(inputFileName);
		Matrix Y = Matrix.readFromFile(outputFileName);
		trainOutputModel(modelListeners, X, Y,timeInMilli,autoStop,newTraining,display);  
	}

/** Retrain the state model in this processor. The data is stored in two ascii file.*/
	public void trainStateModelFromFile(Vector modelListeners, String inputFileName, String outputFileName, double timeInMilli, boolean autoStop, boolean newTraining, boolean display)
	throws IOException, MathException
	{
		INolOptimizeModel optModel = optimization.getModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getStateModel();
		if(ensemble == null){
			throw new MathException("There is no state model for training.");
		}
		Matrix X = Matrix.readFromFile(inputFileName);
		Matrix Y = Matrix.readFromFile(outputFileName);
		trainStateModel(modelListeners, X, Y,timeInMilli,autoStop,newTraining,display);  
	}

/** Retrain the model in this processor. The data is stored in data series file format. If the 
	optimization has state model, the state model will be trained here.*/
	public void trainModelFromFile(Vector modelListeners, String[] dataSeriesFileNames, double timeInMilli, boolean autoStop, boolean newTraining, boolean display) throws MathException{
		Vector retraindataSeries = new Vector();
		for(int i=0;i<dataSeriesFileNames.length;i++){
			String dsFileName = dataSeriesFileNames[i];
			DataSeries ds = new DataSeries();
			ds.Load(dsFileName, 0);
			retraindataSeries.addElement(ds);
		}
		INolOptimizeModel model = optimization.getModel();
		Matrix X = Matlib.createMatrix();
		Matrix Y = Matlib.createMatrix();
		model.prepareTrainingSetFromDataSeries(retraindataSeries,X,Y);
		EnsembleModel ensemble1 = (EnsembleModel) model.getModel();
		if(newTraining){
			ensemble1.clearModels();
		}
		ensemble1.setTrainingTime((long)timeInMilli);  
		ensemble1.useAutomaticStopping(autoStop);
		ensemble1.removeAllListeners();
//		ensemble1.addListener(this);
		NolModelTrainThread trainerThread = new NolModelTrainThread(ensemble1);
		Thread trainingthread = new Thread(trainerThread);
		int prior = trainingthread.getPriority()-3;
		if(prior <Thread.MIN_PRIORITY){
			prior = Thread.MIN_PRIORITY;
		}
		trainingthread.setPriority(prior);
		trainerThread.setInput1(X);
		trainerThread.setOutput1(Y);


		EnsembleModel ensemble2 = (EnsembleModel)model.getStateModel();
		if(ensemble2 != null){
			Matrix I = Matlib.createMatrix();
			Matrix D = Matlib.createMatrix();
			model.prepareTrainingSet2FromDataSeries(retraindataSeries,I,D);
			ensemble2.setTrainingTime((long)timeInMilli);  
			ensemble2.useAutomaticStopping(autoStop);
			ensemble2.removeAllListeners();
			ensemble1.addListener(this);
			trainerThread.setEnsembleModel2(ensemble2);
			trainerThread.setInput2(I);
			trainerThread.setOutput2(D);			
			if(display){
				if(modelListeners == null){
					OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
					ensemble1.addListener(onlineModelListener);
					ensemble2.addListener(onlineModelListener);
					NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
					console.setModel1TrainInput(X);
					console.setModel1TrainOutput(Y);
					console.setModel2TrainInput(I);
					console.setModel2TrainOutput(D);
					console.setOutputModelTrainingThread(trainingthread);
					console.setBounds(100,100,750,500);
					console.setOneModelMode(false);
					console.setReady(false);
					console.setVisible(true);
					console.toFront();	
				}else{
					boolean found = false;
					for (int i=0;i<modelListeners.size();i++){
						EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
						ensemble1.addListener(listener);
						ensemble2.addListener(listener);
						if(listener instanceof OnlineModelListener ){
							OnlineModelListener onlineModelListener = (OnlineModelListener)listener;
							NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
							console.setModel1TrainInput(X);
							console.setModel1TrainOutput(Y);
							console.setModel2TrainInput(I);
							console.setModel2TrainOutput(D);
							console.setOutputModelTrainingThread(trainingthread);
							console.setBounds(100,100,750,500);
							console.setReady(false);
							console.setOneModelMode(false);
							console.setVisible(true);
							console.toFront();	
							found = true;
							break;
						}
					}
					if(!found){
						OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
						ensemble1.addListener(onlineModelListener);
						ensemble2.addListener(onlineModelListener);
						NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
						console.setModel1TrainInput(X);
						console.setModel1TrainOutput(Y);
						console.setModel2TrainInput(I);
						console.setModel2TrainOutput(D);
						console.setOutputModelTrainingThread(trainingthread);
						console.setBounds(100,100,750,500);
						console.setOneModelMode(false);
						console.setReady(false);
						console.setVisible(true);
						console.toFront();	
					}
				}
			}else{
				if(modelListeners != null){
					for (int i=0;i<modelListeners.size();i++){
						EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
						ensemble1.addListener(listener);
						ensemble2.addListener(listener);
					}
				}
			}

		}else{
			ensemble1.addListener(this);
			if(display){
				if(modelListeners == null){
					OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
					ensemble1.addListener(onlineModelListener);
					NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
					console.setModel1TrainInput(X);
					console.setModel1TrainOutput(Y);
					console.setOutputModelTrainingThread(trainingthread);
					console.setBounds(100,100,750,500);
					console.setReady(false);
					console.setOneModelMode(true);
					console.setVisible(true);
					console.toFront();	
				}else{
					boolean found = false;
					for (int i=0;i<modelListeners.size();i++){
						EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
						ensemble1.addListener(listener);
						if(listener instanceof OnlineModelListener ){
							OnlineModelListener onlineModelListener = (OnlineModelListener)listener;
							NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
							console.setModel1TrainInput(X);
							console.setModel1TrainOutput(Y);
							console.setOutputModelTrainingThread(trainingthread);
							console.setBounds(100,100,750,500);
							console.setReady(false);
							console.setOneModelMode(true);
							console.setVisible(true);
							console.toFront();	
							found = true;
							break;
						}
					}
					if(!found){
						OnlineModelListener onlineModelListener = new OnlineModelListener(this, display);
						ensemble1.addListener(onlineModelListener);
						NolOnlineConsoleFrame console = onlineModelListener.getOnlineConsole();
						console.setModel1TrainInput(X);
						console.setModel1TrainOutput(Y);
						console.setOutputModelTrainingThread(trainingthread);
						console.setBounds(100,100,750,500);
						console.setOneModelMode(true);
						console.setReady(false);
						console.setVisible(true);
						console.toFront();	
					}
				}
			}else{
				if(modelListeners != null){
					for (int i=0;i<modelListeners.size();i++){
						EnsembleModelListener listener = (EnsembleModelListener)modelListeners.elementAt(i);
						ensemble1.addListener(listener);
					}
				}
			}


		}
		
		trainingthread.start();
		isCalculated = false;

	}

	private void getModelStatistics(INolOptimizeModel optModel,EnsembleModelEvent e){ 
		EnsembleModel trainedEnsemble = e.getEnsembleModel();
		EnsembleModel ensemble = (EnsembleModel)optModel.getModel();
		if(ensemble.equals(trainedEnsemble)){
			int ensembleSize = ensemble.size();
			int nout = ensemble.getNout();
			outputTestRMSE = new double[nout];
			outputTestCORR = new double[nout];
			outputTrainRMSE = new double[nout];
			outputTrainCORR = new double[nout];
			outputModelRateValue =0;
			for(int j=0;j<nout;j++) {
				outputTestRMSE[j] = 0.0;
				outputTestCORR[j] = 0.0;
				for (int i = 0; i < ensembleSize; i++) {
					TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
					ValidationParameters VP = submodel.testingResults;
					outputTestRMSE[j] += VP.rmse.get(j);
					outputTestCORR[j] += VP.corrcoef.get(j);
					VP = submodel.trainingResults;
					outputTrainRMSE[j] += VP.rmse.get(j);
					outputTrainCORR[j] += VP.corrcoef.get(j);
				}
				outputTestRMSE[j] /= ensembleSize;
				outputTestCORR[j] /= ensembleSize; 
				outputTrainRMSE[j] /= ensembleSize;
				outputTrainCORR[j] /= ensembleSize; 
			}
			for(int i=0;i<nout;i++) {
				outputModelRateValue = outputModelRateValue+outputTestCORR[i];
			}
			outputModelRateValue = outputModelRateValue/nout;
			outputModelRetrained = true;
		}
		ensemble = (EnsembleModel)optModel.getStateModel();
		if(ensemble == null){
			return;
		}
		if(ensemble.equals(trainedEnsemble)){
			int ensembleSize = ensemble.size();
			int nout = ensemble.getNout();
			stateTestRMSE = new double[nout];
			stateTestCORR = new double[nout];
			stateTrainRMSE = new double[nout];
			stateTrainCORR = new double[nout];
			stateModelRateValue =0;
			for(int j=0;j<nout;j++) {
				stateTestRMSE[j] = 0.0;
				stateTestCORR[j] = 0.0;
				for (int i = 0; i < ensembleSize; i++) {
					TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
					ValidationParameters VP = submodel.testingResults;
					stateTestRMSE[j] += VP.rmse.get(j);
					stateTestCORR[j] += VP.corrcoef.get(j);
					VP = submodel.trainingResults;
					stateTrainRMSE[j] += VP.rmse.get(j);
					stateTrainCORR[j] += VP.corrcoef.get(j);
				}
				stateTestRMSE[j] /= ensembleSize;
				stateTestCORR[j] /= ensembleSize; 
				stateTrainRMSE[j] /= ensembleSize;
				stateTrainCORR[j] /= ensembleSize; 
			}
			for(int i=0;i<nout;i++) {
				stateModelRateValue = stateModelRateValue+stateTestCORR[i];
			}
			stateModelRateValue = stateModelRateValue/nout;
			stateModelRetrained = true;
		}
	}

/** Get the model rate after the retraining*/
	public double getOutputModelRate() throws MathException {
		if(!outputModelRetrained){
			throw new MathException("The Output Model is not Retrained!");
		}
		return outputModelRateValue;
	}

/** Get the testing RMSE after the retraining*/
	public double[] getOutputTestRmse() throws MathException {
		if(!outputModelRetrained){
			throw new MathException("The Output Model is not Retrained!");
		}
		return outputTestRMSE;
	}

/** Get the training RMSE after the retraining*/
	public double[] getOutputTrainingRmse()throws MathException{
		if(!outputModelRetrained){
			throw new MathException("The Output Model is not Retrained!");
		}
		return outputTrainRMSE;
	}

/** Get the testing correlation value after the retraining*/
	public double[] getOutputTestCorr() throws MathException {
		if(!outputModelRetrained){
			throw new MathException("The Output Model is not Retrained!");
		}
		return outputTestCORR;
	}

/** Get the training correlation value after the retraining.*/
	public double[] getOutputTrainingCorr() throws MathException {
		if(!outputModelRetrained){
			throw new MathException("The Output Model is not Retrained!");
		}
		return outputTrainCORR;
	}

/** Get the model rate after the retraining*/
	public double getStateModelRate() throws MathException {
		if(!stateModelRetrained){
			throw new MathException("The State Model is not Retrained!");
		}
		return stateModelRateValue;
	}

/** Get the testing RMSE after the retraining*/
	public double[] getStateTestRmse() throws MathException {
		if(!stateModelRetrained){
			throw new MathException("The State Model is not Retrained!");
		}
		return stateTestRMSE;
	}

/** Get the training RMSE after the retraining*/
	public double[] getStateTrainingRmse() throws MathException {
		if(!stateModelRetrained){
			throw new MathException("The State Model is not Retrained!");
		}
		return stateTrainRMSE;
	}

/** Get the testing correlation value after the retraining*/
	public double[] getStateTestCorr() throws MathException {
		if(!stateModelRetrained){
			throw new MathException("The State Model is not Retrained!");
		}
		return stateTestCORR;
	}

/** Get the training correlation value after the retraining.*/
	public double[] getStateTrainingCorr() throws MathException {
		if(!stateModelRetrained){
			throw new MathException("The State Model is not Retrained!");
		}
		return stateTrainCORR;
	}

	public void uncompleteTraining(){
		outputModelRetrained = false;
		stateModelRetrained = false;
	}
	@Override
	public void modelTrained(EnsembleModelEvent e) {}
	@Override
	public synchronized void modelAdded(EnsembleModelEvent e) {}
	@Override
	public void modelRemoved(EnsembleModelEvent e){}
	@Override
	public void trainingComplete(EnsembleModelEvent e){
		INolOptimizeModel optModel = optimization.getModel();
		getModelStatistics(optModel,e);
	}

	public double getObjectiveValue(){
		return optimization.getObjectiveValue();
	}

	
	/** Return the a array of names of variables that reach their hard bound after calculation.*/
	public String[] getVariableNameAtHardBound()throws MathException{
		if (!isCalculated){
			return new String[0];
		}
		Vector newVarNames = new Vector();
		for(int i=0;i<varNames.size();i++){
			String varName = (String)varNames.elementAt(i);
			double[] bs = getBoundsByName(varName);
			double val = getValueByName(varName);
			if (val <= bs[0]){
				newVarNames.addElement(varName);
			}
			if (val >= bs[4]){
				newVarNames.addElement(varName);
			}
		}
		if(newVarNames.isEmpty()){
			return new String[0];
		}
		String[] Vars = new String[newVarNames.size()];
		for(int i=0;i<newVarNames.size();i++){
			Vars[i]=(String)newVarNames.elementAt(i);
		}
		return Vars;
	}

	/** Return the number of variables that reach their hard bound after calculation.*/
	public int getNumberOfVariableNameAtHardBound(){
		try{
		   String[] vars = getVariableNameAtHardBound();
		   return vars.length;
		}catch(MathException evt){
		}
		return 0;
	}
}

