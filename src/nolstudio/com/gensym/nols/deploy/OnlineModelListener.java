package com.gensym.nols.deploy;

import java.util.*;

import com.gensym.math.*;
import com.gensym.math.datafit.*;

import com.gensym.nols.data.*;

public class OnlineModelListener implements EnsembleModelListener{
	private String theModelName;
	private OnlineProcessor onlineProcessor;
	private OnlineOptimizer onlineOptimizer;
	private Thread outputModelTrainingThread;
	private Thread stateModelTrainingThread;
	private NolOnlineConsoleFrame console;
	private NolOnlineSimpleConsoleFrame simpleConsole;
	private boolean progressDisplay = false;
	private OnlineProcessorAPIG2 onlineProcessorAPIG2 = null;
	private OnlineOptimizerAPIG2 onlineOptimizerAPIG2 = null;

	private NolG2Gateway g2Gateway = null;
	private NolModel2 trainingModel = null;
	private boolean exportXML = false;
	private String xmlFilePath;

	/** The Console Frame */
	public OnlineModelListener(String m) {
		super();
		theModelName = m;
		xmlFilePath = null;
	}

	public OnlineModelListener(OnlineProcessor onlineProcessor) {
		this(onlineProcessor.getName());
		this.onlineProcessor = onlineProcessor;
		this.onlineOptimizer = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
	}

	public OnlineModelListener(OnlineProcessorAPIG2 onlineProcessorAPIG2) {
		this(onlineProcessorAPIG2.getName());
		this.onlineProcessorAPIG2 = onlineProcessorAPIG2;
		this.onlineOptimizer = null;
		this.onlineProcessor = null;
		this.onlineOptimizerAPIG2 = null;
	}

	public OnlineModelListener(OnlineOptimizer onlineOptimizer) {
		this(onlineOptimizer.getName());
		this.onlineOptimizer = onlineOptimizer;
		this.onlineProcessor = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
	}

	public OnlineModelListener(OnlineOptimizerAPIG2 onlineOptimizerAPIG2) {
		this(onlineOptimizerAPIG2.getName());
		this.onlineOptimizerAPIG2 = onlineOptimizerAPIG2;
		this.onlineOptimizer = null;
		this.onlineProcessor = null;
		this.onlineProcessorAPIG2 = null;
	}

	public OnlineModelListener(OnlineProcessor onlineProcessor, boolean display) {
		this(onlineProcessor.getName());
		this.onlineProcessor = onlineProcessor;
		this.onlineOptimizer = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
		setProgressDisplay(display);
		setModel(onlineProcessor.getModel());
	}

	public OnlineModelListener(OnlineOptimizer onlineOptimizer, boolean display) {
		this(onlineOptimizer.getName());
		this.onlineOptimizer = onlineOptimizer;
		this.onlineProcessor = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
		setProgressDisplay(display);
		setModel(onlineOptimizer.getModel());
	}

	public void setModel(INolModel2 m) {
 		if(progressDisplay){
			if(console == null){
				if(onlineProcessor != null){
					console = new NolOnlineConsoleFrame(onlineProcessor);
				}else{
					console = new NolOnlineConsoleFrame(onlineOptimizer);
				}
			}
			console.setModel(m);
		}

	}

	public NolOnlineConsoleFrame getOnlineConsole(){
		if(console == null){
			if(onlineProcessor != null){
				console = new NolOnlineConsoleFrame(onlineProcessor);
			}else{
				console = new NolOnlineConsoleFrame(onlineOptimizer);
			}
			progressDisplay = true;
			if(onlineProcessor != null){
				setModel(onlineProcessor.getModel());
			}else{
				setModel(onlineOptimizer.getModel());
			}
		}
		return console;
	}

	public void setProgressDisplay(boolean display){
		progressDisplay = display;
		if(progressDisplay){
			if(console == null){
				if(onlineProcessor != null){
					console = new NolOnlineConsoleFrame(onlineProcessor);
				}else{
					console = new NolOnlineConsoleFrame(onlineOptimizer);
				}
			}
		}
	}

	public void setStateModelTrainingThread(Thread t){
		stateModelTrainingThread = t;
		if(progressDisplay){
			if(console == null){
				if(onlineProcessor != null){
					console = new NolOnlineConsoleFrame(onlineProcessor);
				}else{
					console = new NolOnlineConsoleFrame(onlineOptimizer);
				}
			}
			console.setStateModelTrainingThread(t);
		}
	}

	public void setOutputModelTrainingThread(Thread t){
		outputModelTrainingThread = t;
		if(progressDisplay){
			if(console == null){
				if(onlineProcessor != null){
					console = new NolOnlineConsoleFrame(onlineProcessor);
				}else{
					console = new NolOnlineConsoleFrame(onlineOptimizer);
				}
			}
			console.setOutputModelTrainingThread(t);
		}
	}
	
	@Override
	public void modelTrained(EnsembleModelEvent e) {
		if(console != null){
			console.modelTrained(e);
		}
	}

	@Override
	public synchronized void modelAdded(EnsembleModelEvent e) {
		EnsembleModel ensemble = e.getEnsembleModel();
		double mpe = ensemble.getMeanPredictionError();
		System.out.println("Ensemble model mean squared error: "+mpe);
		if(console != null){
			console.modelAdded(e);
		}
	}
	
	@Override
	public void modelRemoved(EnsembleModelEvent e){
		if(console != null){
			console.modelRemoved(e);
		}
	}

	@Override
	public void trainingComplete(EnsembleModelEvent e) {
		EnsembleModel ensemble = e.getEnsembleModel();
//		TrainableModel model = (TrainableModel)e.getModel();
		System.out.println("Finished training "+theModelName+" !");	
		if(console != null){
			console.trainingComplete(e);
		}
		if(onlineProcessorAPIG2 != null){
			onlineProcessorAPIG2.trainingComplete();
		}
		if (onlineProcessor != null) {
			onlineProcessor.trainingComplete(e);
		}
		if(onlineOptimizerAPIG2 != null){
			onlineOptimizerAPIG2.trainingComplete();
		}
		if (onlineOptimizer != null) {
			onlineOptimizer.trainingComplete(e);
		}
		if(g2Gateway != null){
			try{
				if(trainingModel!= null){
					trainingModel.setIsTrained(true);
					g2Gateway.informG2TrainingComplete(theModelName, true, trainingModel.getWholeParametersVector());
					if(exportXML){
						NolModelXMLHandler handler = new NolModelXMLHandler();
						handler.setModel(trainingModel);
						handler.saveToFile(xmlFilePath);
					}
				}else{
					g2Gateway.informG2SimpleTrainingComplete(theModelName, true, getSimpleModelParameters(ensemble));
				}
			}catch(Exception evt){
				System.out.println("evt =  "+evt.getMessage());	
			}
		}
	}

	public OnlineModelListener(String uuid, NolG2Gateway g2Gateway, NolModel2 model, boolean display) {
		this(uuid);
		this.g2Gateway = g2Gateway;
		this.trainingModel = model;
		this.onlineProcessor = null;
		this.onlineOptimizer = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
		setSimpleProgressDisplay(display);
	}
	public OnlineModelListener(String uuid, NolG2Gateway g2Gateway, boolean display) {
		this(uuid);
		this.g2Gateway = g2Gateway;
		this.trainingModel = null;
		this.onlineProcessor = null;
		this.onlineOptimizer = null;
		this.onlineProcessorAPIG2 = null;
		this.onlineOptimizerAPIG2 = null;
		setSimpleProgressDisplay(display);
	}

	private void setSimpleProgressDisplay(boolean display){
		progressDisplay = display;
		if(progressDisplay){
			if(simpleConsole == null){
				simpleConsole = new NolOnlineSimpleConsoleFrame();
			}
		}
	}
	public NolOnlineSimpleConsoleFrame getSimpleOnlineConsole(){
		if(simpleConsole == null){
			progressDisplay = true;
			simpleConsole = new NolOnlineSimpleConsoleFrame();
		}
		return simpleConsole;
	}

	private Vector getSimpleModelParameters(EnsembleModel ensemble)throws MathException{
		double modelRateValue = 0.0;
		int nout = ensemble.getNout();
		Vector TrainingRmse = new Vector();
		Vector TestingRmse = new Vector();
		Vector TrainingCorrcoef = new Vector();
		Vector TestingCorrcoef = new Vector();
		double r1 = getModelStatistics(ensemble,TrainingRmse, TrainingCorrcoef,0);
		double r2 = getModelStatistics(ensemble,TestingRmse, TestingCorrcoef,1);
		modelRateValue = (r1+r2)/2;
		Vector params = new Vector();
		params.addElement(modelRateValue);
		params.addElement(nout);
		params.addAll(TrainingRmse);
		params.addAll(TestingRmse);
		params.addAll(TrainingCorrcoef);
		params.addAll(TestingCorrcoef);
		params.addAll(ensemble.getParametersVector());
		return params;
	}

	private double getModelStatistics(EnsembleModel ensemble, Vector rmse, Vector corrcoef, int type) {
		int digits = 4;
		int ensembleSize = ensemble.size();
		int nout = ensemble.getNout();
		double[] rmseAve = new double[nout];
		double[] corrAve = new double[nout];
		double rate =0;
		for(int j=0;j<nout;j++) {
			rmseAve[j] = 0.0;
			corrAve[j] = 0.0;
			for (int i = 0; i < ensembleSize; i++) {
				TrainableModel submodel = (TrainableModel) ensemble.getModel(i);
				ValidationParameters VP = null;
				if(type==1){
					VP = submodel.testingResults;
				}else{
					VP = submodel.trainingResults;
				}
				rmseAve[j] += VP.rmse.get(j);
				corrAve[j] += VP.corrcoef.get(j);
			}
			rmseAve[j] /= ensembleSize;
			corrAve[j] /= ensembleSize; 
		}
		for(int i=0;i<nout;i++) {
			rmse.addElement(String.valueOf(rmseAve[i]));
			corrcoef.addElement(String.valueOf(corrAve[i]));
			rate = rate+corrAve[i];
		}
		rate = rate/nout;
		return rate;
	}
	public void setXmlFilePath(String xmlFilePath){
		this.xmlFilePath = xmlFilePath;
		exportXML = true;
	}
}

