package com.gensym.nols.data;


public interface IPreprocessor extends Processor {

	Variable getVariableFromVariableName(String varName);

}
