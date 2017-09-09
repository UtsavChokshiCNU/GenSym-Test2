package com.gensym.nols.data;
/*
 *		Gensym NolRhoModel Class.
 *		This class is extended from NolRbfnModel.class
 *		Modified 3/25/98 by Gchen
 */

import java.util.*;
import java.io.*;
import com.gensym.math.datafit.*;
import com.gensym.math.matrix.*;
import com.gensym.math.*;

/** Model class. */
public class NolRhoModel extends NolRbfnModel{
	static final long serialVersionUID = 1L;
	private Matrix inputMean;
	private Matrix inputStd;
	private Matrix outputMean;
	private Matrix outputStd;

/** Create a NolRhoModel object.*/	
	public NolRhoModel(ClassicRbfn net, String name, Vector outs, 
		Vector ins, Vector oDelays, Vector iDelays, Preprocessor prep){
		super(net, name, outs, ins, oDelays, iDelays, prep);
		normalizeData = true;
	}

	@Override
	public void setRunningParameter(int method){
		this.trainingMethod = method;
//System.out.println("rho model setRunningParameter="+method);
		if(trainingMethod == 0){
			if(outputs.size() <= 1)	{
				return;
			}
			Object elem = outputs.elementAt(0);
			outputs.removeAllElements();
			outputs.addElement(elem);
			((ClassicRbfn)model).setNout(1);
			if(outputDelays.size() <= 1)	{
				return;
			}
			elem = outputDelays.elementAt(0);
			outputDelays.removeAllElements();
			outputDelays.addElement(elem);

		}
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolRhoModel cloned = (NolRhoModel) super.clone();
		cloned.inputMean = inputMean == null ? null : (Matrix) inputMean.clone();
		cloned.inputStd = inputStd == null ? null : (Matrix) inputStd.clone();
		cloned.outputMean = outputMean == null ? null : (Matrix) outputMean.clone();
		cloned.outputStd = outputStd == null ? null : (Matrix) outputStd.clone();
		
		return cloned;
	}

	@Override
	public void train(Matrix XTrain, Matrix YTrain)throws IOException,MathException{
		trainer.setFlag(NolClassicModelTrainer.RHOTRAINING);
		prepareDataStat(XTrain,YTrain);
		String [] fileNames = trainer.makeRPCfileNames(); 
		writeRbfnToFile(fileNames[0],XTrain,YTrain);
		int result = trainer.jrho_trainer(fileNames[0],fileNames[1]);
		if(result == 1){
			readRbfnFromFile(fileNames[1]);
			trainingResults = new ClassicValidationParameters(this,XTrain,YTrain);
			trainer.informListeners("complete","");
		}else{
			String message = trainer.readErrorFromFile(fileNames[1]);
			trainer.informListeners("error",message);
		}
		trainer.deleteFiles(fileNames);
	}

	@Override
	public void readPredictionFromFile(String infile, Matrix YPred)throws MathException, IOException{
		boolean saveflag = normalizeData;
		normalizeData = false;
		super.readPredictionFromFile(infile,YPred);
		normalizeData = saveflag;
	}

}

