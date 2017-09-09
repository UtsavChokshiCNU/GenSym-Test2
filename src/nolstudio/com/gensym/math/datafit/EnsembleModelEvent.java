package com.gensym.math.datafit;

public class EnsembleModelEvent {
	public static final int MODEL_ADDED = 0;
	public static final int MODEL_REMOVED = 1;
	public static final int TRAINING_COMPLETE = 2;
	public static final int MODEL_TRAINED = 3;
	
	private EnsembleModel ensemble;
	private Model model;
	private int type;


	EnsembleModelEvent(EnsembleModel ensemble, Model model, int eventType) {
		this.ensemble = ensemble;
		this.model = model;  // can be null for event type TRAINING_COMPLETE
		type = eventType;
	}

	public EnsembleModel getEnsembleModel() {
		return ensemble;
	}

	public Model getModel() {
		return model;
	}

	public int getType() {
		return type;
	}
}