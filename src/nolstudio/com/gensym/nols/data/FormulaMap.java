package com.gensym.nols.data;
import java.io.Serializable;

public class FormulaMap implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

	public static final String[] timeFunctions = {
		"Abs",
		"CutHighValue",
		"CutLowValue",
		"CutRepeatValue",
		"Delay",
		"DerivativePoly",
		"Divide",
		"Exp",
		"Log",
		"Log10",
		"Mean",
		"MovingAverage",
		"Multiply",
		"RandNormal",
		"RandUniform",
		"ReplaceHighValue",
		"ReplaceLowValue",
		"Sign",
		"Sqrt",
		"Subtract",
		"Sum" 
	};

	public static final String[] rowFunctions = {
		"Abs",
		"CutHighValue",
		"CutLowValue",
		"CutRepeatValue",
		"DerivativePoly",
		"Divide",
		"Exp",
		"Log",
		"Log10",
		"Mean",
		"Multiply",
		"RandNormal",
		"RandUniform",
		"ReplaceHighValue",
		"ReplaceLowValue",
		"Sign",
		"Sqrt",
		"Subtract",
		"Sum" 
	};

	public static String toQualifiedName(String funcName) {
		String qualifier = "com.gensym.nols.data.function.";
		for(int i=0;i<timeFunctions.length;i++) {
			if(funcName.equals(timeFunctions[i])){
				return qualifier+funcName;
			}
		}
		// if here, we have no clue as to the qualified name for this function
		return funcName;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}
