package com.gensym.nols.deploy;

import java.io.Serializable;
import java.util.HashMap;

import com.gensym.nols.data.IPreprocessor;
import com.gensym.nols.data.Variable;

public class PreprocessorStub implements IPreprocessor, Serializable {
	private static final long serialVersionUID = 1L;

	private HashMap<String, Variable> variablesMap;
	private String name;

	@Override
	public String getName() {
		return name;
	}

	@Override
	public Variable getVariableFromVariableName(String varName) {
		if (variablesMap == null || variablesMap.containsKey(varName) == false) {
			return null;
		}

		return variablesMap.get(varName);
	}

	public void setName(String value) {
		this.name = value;
	}

	public void setVariablesFromVariableName(HashMap<String, Variable> value) {
		variablesMap = value;
	}
}