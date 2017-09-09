package com.gensym.gos.data;
/*
 *		Gensym Optimization Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.util.*;
import java.io.*;
import com.gensym.math.opt.*;
import com.gensym.math.matrix.*;
import com.gensym.math.MathException;
import com.gensym.nols.data.NolModel2;

public class Optimization extends DataSource implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

	protected boolean isCalculated;
	protected boolean useDeriv;
	protected Vector constraints;
	private Objective objective;
	private String name;
	private String comment;

	private int objsen;

	private int NMAX;
	private int statusFlag; //Added gchen 6.28.2000, for returning the status of optimization
	private String statusMessage = ""; //Added gchen 6.28.2000, for returning the message of optimization

	protected Vector variables;
	private int derivflag;
	private Vector usedModels;

/** Create a new Optimization containing no characters.*/
	public Optimization() {
		super();
		isCalculated = false;
		useDeriv = false;
		statusFlag = 0;
		constraints = new Vector();
		variables = new Vector();
		usedModels = new Vector();
		objsen = 1;
		derivflag = 1;
	}

/** Create a new optimization with a name.*/
	public Optimization(String n) {
		this();
		name = n;
	}

/** Get the name of this optimization. */	
	@Override
	public String getName(){
		return name;
	}

/** set the name of this optimization. */	
	@Override
	public void setName(String n){
		name = n;
	}


/** Return the comment of this optimization.*/
	@Override
	public String getComment(){
		return comment;
	}

/** Set the comment of this optimization.*/
	@Override
	public void setComment(String c){
		comment = c;
	}

/** Set the objsen of this optimization.*/
	public void setObjSen(int s){
		objsen = s;
	}

/** Return the status flag of the optimization problem.*/
	public int getStatusFlag(){
		return statusFlag;
	}

/** Return the status message of the optimization problem.*/
	public String getStatusMessage(){
		return statusMessage;
	}

/** Override the toString method. */	
	@Override
	public String toString(){
		return name;
	}

/** Set the objective for this optimization problem. */	
	public void setObjective(Objective objective){
		this.objective =  objective;
	}

/** Get the objective for this optimization problem. */	
	public Objective getObjective(){
		 return objective;
	}

/** Add constraint to this optimization problem. */	
	public void addConstraint(Constraint constraint){
		this.constraints.addElement(constraint);
	}

/** Remove constraint to this optimization problem. */	
	public void removeConstraint(Constraint constraint){
		this.constraints.removeElement(constraint);
	}

/** get constraint to this optimization problem. */	
	public Vector getConstraints(){
		return constraints;
	}

/** Add variable to this optimization problem. */	
	public void addVariable(GosVariable var){
		variables.addElement(var);
	}


/** Remove variable to this optimization problem. */	
	public void removeVariable(GosVariable var){
		variables.removeElement(var);
	}

/** get variable vector */
	public Vector getVariables(){
		return variables;
	}

/** set variable vector */
	public void setVariables(Vector vars){
		variables = vars;
	}

/** add model */
	public void addModel(PredictiveModel model){
		usedModels.addElement(model);
	}

/** set model vector */
	public void setModels(Vector models){
		usedModels = models;
	}


/** get model vector */
	public Vector getModels(){
		return usedModels;
	}


/** Get the sense of the constraints.*/
	public String getSense(Vector constrs){
		String sense = "";
		for(int i=0;i<constrs.size();i++){
			Constraint cstr = (Constraint)constrs.elementAt(i);
			sense = sense+cstr.getSense();
		}
		return sense;

	}

	private String getVariableName(GosVariable var){
		String name = var.getName();
		String newName = new String(name);
		newName=newName.replace('.','_');
		System.out.println("new name="+newName);
		return newName;
	}

/** Get the variables string. */	
	private String getVariableStringForFunc(){
		Vector indepVariables = new Vector();
		Vector extraVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] == 0){
				indepVariables.addElement(varObj);
			}else{
				extraVariables.addElement(varObj);
			}
		}

		StringBuffer sb = new StringBuffer (1000);
		for(int i=0;i<indepVariables.size();i++){
			sb.append( "double "+getVariableName((GosVariable)indepVariables.elementAt(i))+";\n");
		}
		for(int i=0;i<extraVariables.size();i++){
			sb.append( "double "+getVariableName((GosVariable)extraVariables.elementAt(i))+";\n");
		}
		for(int i=0;i<indepVariables.size();i++){
			sb.append(getVariableName((GosVariable)indepVariables.elementAt(i))+" = var["+i+"];\n");
		}
		for(int i=0;i<extraVariables.size();i++){
			sb.append(getVariableName((GosVariable)extraVariables.elementAt(i))+" = exog"+i+";\n");
		}
		return sb.toString();
	}
	
/** Get the variables string. */	
	private String getVariableStringForSolvenlp(){
		Vector extraVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] == 1){
				extraVariables.addElement(varObj);
			}
		}

		StringBuffer sb = new StringBuffer (1000);
		for(int i=0;i<extraVariables.size();i++){
			sb.append("exog"+i+" = exog["+i+"];\n");
		}
		return sb.toString();
	}
	
/** Get the variables string. */	
	private String getVariableStringForExtraDef(){
		Vector extraVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] == 1){
				extraVariables.addElement(varObj);
			}
		}
		StringBuffer sb = new StringBuffer (100);
		for(int i=0;i<extraVariables.size();i++){
			sb.append("double exog"+i+" = 0.0;\n");
		}
		return sb.toString();
	}
	
/** Get the content string for the problem c code. */	
	public String getCContent(){
		Vector indepVariables = new Vector();
		Vector extraVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] == 0){
				indepVariables.addElement(varObj);
			}else{
				extraVariables.addElement(varObj);
			}
		}

      StringBuffer sb = new StringBuffer (1000);

	  //header first.
	  sb.append (ProblemFixedContent.getIncludes());

	  //definition for the extra variables second.
	  getVariableStringForExtraDef();

	  //funceval third.
	  sb.append (ProblemFixedContent.getFuncevalSyn());
	  for (int i=0;i<constraints.size();i++){
		  sb.append (((Constraint)constraints.elementAt(i)).getInternalVarString());
		  sb.append ("\n");
	  }
	  sb.append (objective.getInternalVarString());

	  sb.append (getVariableStringForFunc());
	  sb.append (objective.getContent());
	  sb.append ("\n");
      
	  for (int i=0;i<constraints.size();i++){
		  sb.append (((Constraint)constraints.elementAt(i)).getContent());
		  sb.append ("\n");
	  }
	  sb.append ("return 0;\n}\n");

	     


	  sb.append (ProblemFixedContent.getJacobianSyn());
	  //jacobian fourth
	  if(useDeriv){

	  }
	  sb.append ("return 0;\n}\n");

	  //solvenlp fourth		
	  sb.append (ProblemFixedContent.getSolvenlpSyn());
	  int numberOfVariables = indepVariables.size();
	  int numberOfConstraints = constraints.size();
	  String sense = getSense(constraints);
	  
	  sb.append("INTARG numcols = "+ numberOfVariables+ ";\n");
	  sb.append("INTARG numrows = "+ numberOfConstraints+ ";\n");
	  sb.append("INTARG objsen = "+ objsen+ ";\n");
	  sb.append("double obj["+numberOfVariables+"];\n");
	  if( numberOfConstraints > 0 ) {
		  sb.append("double rhs["+numberOfConstraints+"];\n");
	  }
	  if( sense.length() > 0 ) {
		sb.append("char sense["+sense.length()+"] = \""+sense+"\";\n");
	  }
	  sb.append("LPINTARG matbeg = NULL;\n");
	  sb.append("LPINTARG matcnt = NULL;\n");
	  sb.append("HPINTARG matind = NULL;\n");
	  if( numberOfConstraints > 0 ) {
		sb.append("double matval["+(numberOfVariables*numberOfConstraints)+"];\n");
	  }
	  sb.append("LPREALARG rngval = NULL;\n");
	  sb.append("INTARG nzspace = "+(numberOfVariables*numberOfConstraints)+";\n");
	  if( numberOfConstraints > 0 ) {
		  sb.append("double piout["+numberOfConstraints+"], slack["+numberOfConstraints+"], dj["+numberOfVariables+"];\n");
	  }else{
		  sb.append("double dj["+numberOfVariables+"];\n");
	  }
	  sb.append("int derivflag = "+derivflag+";\n");
	  sb.append("HPROBLEM lp = NULL;\n");

	  for (int i=0;i<constraints.size();i++){
		  sb.append ("rhs["+i+"] = "+((Constraint)constraints.elementAt(i)).getRightHandValue()+";\n");
	  }

	  sb.append (getVariableStringForSolvenlp());
	  sb.append (ProblemFixedContent.getSolvenlpFinishedContent(numberOfConstraints,false));

	  //jsolveNLP fifth
	  sb.append (ProblemFixedContent.getJsolveNLPSyn());
	  sb.append (ProblemFixedContent.getJsolveNLPContent());
  	  sb.append ("}\n");
	  return sb.toString ();
	}

	public void writeToFile(String directory)throws IOException {
		File SourceFile = null;
		String fileName = "OptProb.c";
		if(directory == null)
			SourceFile = new File(fileName);
		else
			SourceFile = new File(directory,fileName);
		BufferedWriter Source = new BufferedWriter(new FileWriter(SourceFile));
		Source.write(getCContent());
		Source.close();

		String modelFileName = "models.c";
		if(directory == null)
			SourceFile = new File(modelFileName);
		else
			SourceFile = new File(directory,modelFileName);

		String modelsContents = "";
		if(usedModels.size()>0){
			modelsContents = getModelsContents();
		}
		Source = new BufferedWriter(new FileWriter(SourceFile));
		Source.write(modelsContents);
		Source.close();

		String modelHFileName = "models.h";
		if(directory == null)
			SourceFile = new File(modelHFileName);
		else
			SourceFile = new File(directory,modelHFileName);

		String modelsHeaderContents = "";
		if(usedModels.size()>0){
			modelsHeaderContents = getModelsHeaderContents();
		}
		Source = new BufferedWriter(new FileWriter(SourceFile));
		Source.write(modelsHeaderContents);
		Source.close();
	}

	private String getModelsContents(){
      StringBuffer sb = new StringBuffer (1000);
	  sb.append ("#include <math.h>\n");
	  sb.append ("#include <stdio.h>\n");
	  sb.append ("#include <stdlib.h>\n");
	  sb.append ("#include <ctype.h>\n");
	  sb.append ("#include \"nnet.h\"\n");
	  sb.append ("#include \"models.h\"\n");
	  
	  for(int i=0;i<usedModels.size();i++){
		  PredictiveModel model = (PredictiveModel)usedModels.elementAt(i);
		  sb.append (model.getModelContents()+"\n");
	  }
	  return sb.toString();
	}


	private String getModelsHeaderContents(){
      StringBuffer sb = new StringBuffer (100);
	  sb.append ("#include <math.h>\n");
	  for(int i=0;i<usedModels.size();i++){
		  PredictiveModel model = (PredictiveModel)usedModels.elementAt(i);
		  sb.append (model.getModelHeader()+";\n");
	  }
	  return sb.toString();
	}

	private Vector getIndepVariabes(){
		Vector indepVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] == 0){
				indepVariables.addElement(varObj);
			}
		}
		return indepVariables;
	}

	private Vector getExogenousVariables(){
		Vector exogVariables = new Vector();
		for(int i=0;i<variables.size();i++){
			GosVariable varObj = (GosVariable)variables.elementAt(i);
			int[] deps = varObj.getDependencyFlag();
			if(deps[0] != 0){
				exogVariables.addElement(varObj);
			}
		}
		return exogVariables;
	}

	public double[] getInits() {
		Vector indepVariables = getIndepVariabes();
		int numberOfVariables = indepVariables.size();
		double[] inits = new double[numberOfVariables];
		for(int i=0;i<numberOfVariables;i++){
			GosVariable varObj = (GosVariable)indepVariables.elementAt(i);
			double[] varInits = varObj.getInitialValue();
			inits[i] = varInits[0];
		}
		return inits;

	}

	public double[] getExogenousValues() {
		Vector exogVariables = getExogenousVariables();
		int numberOfVariables = exogVariables.size();
		double[] values = new double[numberOfVariables];
		for(int i=0;i<numberOfVariables;i++){
			GosVariable varObj = (GosVariable)exogVariables.elementAt(i);
			double[] varValues= varObj.getInitialValue();
			values[i] = varValues[0];
		}
		return values;
	}

	public double[] getIndependentUpperBounds() {
		Vector indepVariables = getIndepVariabes();
		int numberOfVariables = indepVariables.size();
		double[] ubs = new double[numberOfVariables];
		for(int i=0;i<numberOfVariables;i++){
			GosVariable varObj = (GosVariable)indepVariables.elementAt(i);
			double[] varInits = varObj.getHardUpperBound();
			ubs[i] = varInits[0];
		}
		return ubs;
	}

	public double[] getIndependentLowerBounds() {
		Vector indepVariables = getIndepVariabes();
		int numberOfVariables = indepVariables.size();
		double[] lbs = new double[numberOfVariables];
		for(int i=0;i<numberOfVariables;i++){
			GosVariable varObj = (GosVariable)indepVariables.elementAt(i);
			double[] varInits = varObj.getHardLowerBound();
			lbs[i] = varInits[0];
		}
		return lbs;
	}


}