package com.gensym.nols.deploy;

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.datafit.ArchitectureParameters;
import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.DataSeries;
import com.gensym.nols.data.INolOptimizeModel;
import com.gensym.nols.data.IPreprocessor;

public class NolOptimizeModelStub implements INolOptimizeModel, Serializable {
	private static final long serialVersionUID = 1L;

	private EnsembleModel ensemble;
	private EnsembleModel stateEnsemble;
	private IPreprocessor preprocessor;
	private Matrix matrixI;
	private Matrix matrixD;
	private Matrix matrixX;
	private Matrix matrixY;
	private String name;
	private Vector<DataSeries> retraindataSeries;
	private Vector<DataSeries> retraindataSeries2;
	private Vector<String> exogNames;
	private Vector<String> manipulatedNames;
	private Vector<String> outputs;
	private Vector<String> stateInputs;

	public NolOptimizeModelStub(IPreprocessor preprocessor) {
		this.preprocessor = preprocessor;
		this.ensemble = null;
		this.stateEnsemble = null;
	}
	
	public Object clone() throws CloneNotSupportedException {
		NolOptimizeModelStub cloned = (NolOptimizeModelStub) super.clone();
		cloned.ensemble = ensemble == null ? null : (EnsembleModel) ensemble.clone();
		cloned.stateEnsemble = stateEnsemble == null ? null : (EnsembleModel) stateEnsemble.clone();
		cloned.matrixI = matrixI == null ? null : (Matrix) matrixI.clone();
		cloned.matrixD = matrixD == null ? null : (Matrix) matrixD.clone();
		cloned.matrixX = matrixX == null ? null : (Matrix) matrixX.clone();
		cloned.matrixY = matrixY == null ? null : (Matrix) matrixY.clone();
		cloned.retraindataSeries = retraindataSeries == null ? null : (Vector<DataSeries>) retraindataSeries.clone();
		cloned.retraindataSeries2 = retraindataSeries2 == null ? null : (Vector<DataSeries>) retraindataSeries2.clone();
		cloned.exogNames = exogNames == null ? null : (Vector<String>) exogNames.clone();
		cloned.manipulatedNames = manipulatedNames == null ? null : (Vector<String>) manipulatedNames.clone();
		cloned.outputs = outputs == null ? null : (Vector<String>) outputs.clone();
		cloned.stateInputs = stateInputs == null ? null : (Vector<String>) stateInputs.clone();
		
		return cloned;
	}

	@Override
	public String getComment() {
		return null;
	}

	@Override
	public Vector<Object> getInputDelays() {
		return null;
	}

	@Override
	public Vector<String> getInputs() {
		Vector<String> inputs = new Vector<String>();

		if (manipulatedNames != null) {
			inputs.addAll(manipulatedNames);
		}

		if (exogNames != null) {
			inputs.addAll(exogNames);
		}

		if (stateInputs != null) {
			inputs.addAll(stateInputs);
		}

		return inputs;
	}

	@Override
	public Object getModel() {
		return ensemble;
	}

	@Override
	public String getName() {
		return name;
	}

	@Override
	public Vector<Object> getOutputDelays() {
		return new Vector<Object>();
	}

	@Override
	public Vector<String> getOutputs() {
		return outputs;
	}

	@Override
	public boolean isTrained() {
		return false;
	}

	@Override
	public void setIsTrained(boolean b) {
	}

	@Override
	public boolean isRecursiveModel() {
		return false;
	}

	@Override
	public int getDelayTimeUnit() {
		return 0;
	}

	@Override
	public int getNin() {
		return getInputs() != null ? getInputs().size() : 0;
	}

	@Override
	public int getNout() {
		return 0;
	}

	@Override
	public ArchitectureParameters getArchitectureParameters() {
		return null;
	}

	@Override
	public void evaluate(Matrix X, Matrix Y) throws MathException {
	}

	@Override
	public Vector<String> getExogenous() {
		return exogNames;
	}

	@Override
	public Vector<String> getManipulate() {
		return manipulatedNames;
	}

	@Override
	public IPreprocessor getPreprocessor() {
		return preprocessor;
	}

	@Override
	public Vector<String> getState() {
		return stateInputs;
	}

	@Override
	public Vector<String> getStateInput() {
		return stateInputs;
	}

	@Override
	public Object getStateModel() {
		return stateEnsemble;
	}

	@Override
	public String parametersToString() {
		return null;
	}

	@Override
	public Vector<Object> getStateDelays() {
		return null;
	}

	@Override
	public Vector<String> getOutputVarNames() {
		return outputs;
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public long[] prepareTrainingSetFromDataSeries(Vector retraindataSeries, Matrix x, Matrix y) throws MathException {
		this.retraindataSeries = retraindataSeries;
		cloneMatrix(matrixX, x);
		cloneMatrix(matrixY, y);
		return null;
	}

	@SuppressWarnings({ "rawtypes", "unchecked" })
	@Override
	public long[] prepareTrainingSet2FromDataSeries(Vector retraindataSeries, Matrix i, Matrix d) throws MathException {
		this.retraindataSeries2 = retraindataSeries;
		cloneMatrix(matrixI, i);
		cloneMatrix(matrixD, d);
		return null;
	}

	@Override
	public Vector<long[]> getStateInputDelays() {
		return null;
	}

	public void setName(String value) {
		this.name = value;
	}

	public void setManipulate(Vector<String> value) {
		this.manipulatedNames = value;
	}

	public void setExogenous(Vector<String> value) {
		this.exogNames = value;
	}

	public void setStateInputs(Vector<String> value) {
		this.stateInputs = value;
	}

	public void setModel(EnsembleModel value) {
		this.ensemble = value;
	}

	public void setStateModel(EnsembleModel value) {
		this.stateEnsemble = value;
	}

	public void setOutputs(Vector<String> value) {
		this.outputs = value;
	}

	public Vector<DataSeries> getRetrainDataSeries() {
		return retraindataSeries;
	}

	private void cloneMatrix(Matrix sourceMatrix, Matrix destMatrix) {
		destMatrix.redimension(sourceMatrix.getRows(), sourceMatrix.getCols());
		for (int i = 0; i < sourceMatrix.getRows(); i++) {
			for (int j = 0; j < sourceMatrix.getCols(); j++) {
				destMatrix.set(i, j, sourceMatrix.get(i, j));
			}
		}
	}

	public Vector<DataSeries> getRetrainDataSeries2() {
		return retraindataSeries2;
	}

	public void setMatrices(Matrix matrixX, Matrix matrixY, Matrix matrixI, Matrix matrixD) {
		this.matrixX = matrixX;
		this.matrixY = matrixY;
		this.matrixI = matrixI;
		this.matrixD = matrixD;
	}
}