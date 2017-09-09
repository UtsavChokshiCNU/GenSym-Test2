package com.gensym.nols.data;
import java.lang.*;

public interface ClassicModelTrainerListener {
	public void modelUpdated();
	public void trainingComplete();
	public void error(String message);
}