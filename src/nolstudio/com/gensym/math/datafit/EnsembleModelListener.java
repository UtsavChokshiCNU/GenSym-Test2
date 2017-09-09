package com.gensym.math.datafit;

import java.lang.*;

public interface EnsembleModelListener {
	public void modelTrained(EnsembleModelEvent e);
	public void modelAdded(EnsembleModelEvent e);
	public void modelRemoved(EnsembleModelEvent e);
	public void trainingComplete(EnsembleModelEvent e);
}