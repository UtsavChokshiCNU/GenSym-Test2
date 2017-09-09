package com.gensym.nols.data;
/*		
 *  Replaced by Formula2 in V2.  Class is here for loading V1 projects only.
 */

import java.io.IOException;
import java.io.Serializable;
import java.util.Vector;

import com.gensym.nols.data.function.Abs;
import com.gensym.nols.data.function.CutHighValue;
import com.gensym.nols.data.function.CutLowValue;
import com.gensym.nols.data.function.Divide;
import com.gensym.nols.data.function.Exp;
import com.gensym.nols.data.function.Log;
import com.gensym.nols.data.function.Log10;
import com.gensym.nols.data.function.MovingAverage;
import com.gensym.nols.data.function.Multiply;
import com.gensym.nols.data.function.RandNormal;
import com.gensym.nols.data.function.ReplaceHighValue;
import com.gensym.nols.data.function.ReplaceLowValue;
import com.gensym.nols.data.function.Sign;
import com.gensym.nols.data.function.Sqrt;
import com.gensym.nols.data.function.Subtract;
import com.gensym.nols.data.function.Sum;

public class Formula implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected String name;
	protected String calculatorClass;
	protected String description;
	protected Vector inputs;  
	protected Vector outputs;
	protected Vector properties;

/** Create a null data Formula object. */	
	public Formula() {
		super();
	}

	public Formula2 convert_1_2() throws IOException {
		Formula2 newFormula;
		if(this instanceof InnerFormula){
			newFormula = (Formula2) new InnerFormula2();
		}
		else newFormula = new Formula2();
		newFormula.inputs = inputs;
		for(int i=0;i<inputs.size();i++) {
			Object obj = inputs.elementAt(i);
			if(obj instanceof InnerFormula) {
				// upgrade inner formula to innerFormula2
				InnerFormula oldInner = (InnerFormula) obj;
				Formula2 newInner = oldInner.convert_1_2();  // will be an InnerFormula2
				inputs.setElementAt(newInner, i);
			}
		}
		newFormula.outputs = outputs;
		newFormula.description = description;
//		try {
			if(name.equals("abs")) {
				newFormula.function = new Abs();
			} else if (name.equals("CUT_HIGH_VALUE")) {
				String[] propStrings1 = (String[])properties.elementAt(0);
				Double threshold = new Double(propStrings1[1]);
				newFormula.inputs.addElement(threshold);
				newFormula.function = new CutHighValue();
			} else if (name.equals("CUT_LOW_VALUE")) {
				String[] propStrings1 = (String[])properties.elementAt(0);
				Double threshold = new Double(propStrings1[1]);
				newFormula.inputs.addElement(threshold);
				newFormula.function = new CutLowValue();
			} else if (name.equals("divide")) {
				newFormula.function = new Divide();
			} else if (name.equals("exp")) {
				newFormula.function = new Exp();
			} else if (name.equals("log")) {
				newFormula.function = new Log();
			} else if (name.equals("log10")) {
				newFormula.function = new Log10();
			} else if (name.equals("MOVING_AVE")) {

				String[] propStrings1 = (String[])properties.elementAt(0);
				String[] propStrings2 = (String[])properties.elementAt(1);
				double sec = 0;
				if(propStrings1[1].equals("H")){
					sec = (new Double(propStrings2[1]).doubleValue())*3600.0;
				}else if(propStrings1[1].equals("M")){
					sec = (new Double(propStrings2[1]).doubleValue())*60.0;
				}else if(propStrings1[1].equals("S")){
					sec = (new Double(propStrings2[1]).doubleValue());
				}
				newFormula.inputs.addElement(new Double(sec));
				newFormula.function = new MovingAverage();
			} else if (name.equals("multiply")) {
				newFormula.function = new Multiply();
			} else if (name.equals("random")) {
				newFormula.function = new RandNormal();
			} else if (name.equals("REPLACE_HIGH_VALUE")) {
				String[] propStrings1 = (String[])properties.elementAt(0);
				Double threshold = new Double(propStrings1[1]);
				String[] propStrings2 = (String[])properties.elementAt(1);
				Double replacement = new Double(propStrings2[1]);
				newFormula.inputs.addElement(threshold);
				newFormula.inputs.addElement(replacement);
				newFormula.function = new ReplaceHighValue();
			} else if (name.equals("REPLACE_LOW_VALUE")) {
				String[] propStrings1 = (String[])properties.elementAt(0);
				Double threshold = new Double(propStrings1[1]);
				String[] propStrings2 = (String[])properties.elementAt(1);
				Double replacement = new Double(propStrings2[1]);
				newFormula.inputs.addElement(threshold);
				newFormula.inputs.addElement(replacement);
				newFormula.function = new ReplaceLowValue();
			} else if (name.equals("sign")) {
				newFormula.function = new Sign();
			} else if (name.equals("sqrt")) {
				newFormula.function = new Sqrt();
			} else if (name.equals("subtract")) {
				newFormula.function = new Subtract();
			} else if (name.equals("sum")) {
				newFormula.function = new Sum();
			}
//		} catch (Exception e) {
//			throw new IOException("Load failed: Could not load preprocessor formulas");
//		}
		return newFormula;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Formula cloned = (Formula) super.clone();
		cloned.inputs = inputs == null ? null : (Vector) inputs.clone();
		cloned.outputs = outputs == null ? null : (Vector) outputs.clone();
		cloned.properties = properties == null ? null : (Vector) properties.clone();
		
		return cloned;
	}
}