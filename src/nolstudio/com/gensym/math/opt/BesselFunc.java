package com.gensym.math.opt;

import java.io.*;
import java.lang.*;
import java.util.*;
import com.gensym.math.*;
import com.gensym.math.matrix.*;

public class BesselFunc implements Function {

	public BesselFunc() {
		super();
	}

	@Override
	public void evaluate(Matrix P, Matrix Y) throws MathException {
		double val;
		Y.redimension(P.getRows(),1);
		for (int i=0;i<P.getRows();i++) {
			val = 0.6-bessj0((P.get(i,0)-0.5)*(P.get(i,0)-0.5)+(P.get(i,1)-0.6)*(P.get(i,1)-0.6)+(P.get(i,2)-0.7)*(P.get(i,2)-0.7));
			Y.set(i,0,val);
		}
	}

	final static double bessj0(double x) {
		double ax,z,xx,y,ans,ans1,ans2;
		if ((ax=Math.abs(x)) < 8.0) {
			y=x*x;
			ans1=57568490574.0+y*(-13362590354.0+y*(651619640.7
			+y*(-11214424.18+y*(77392.33017+y*(-184.9052456)))));
			ans2=57568490411.0+y*(1029532985.0+y*(9494680.718
			+y*(59272.64853+y*(267.8532712+y*1.0))));
			ans=ans1/ans2;
		} else {
			z=8.0/ax;
			y=z*z;
			xx=ax-0.785398164;
			ans1=1.0+y*(-0.1098628627e-2+y*(0.2734510407e-4
			+y*(-0.2073370639e-5+y*0.2093887211e-6)));
			ans2 = -0.1562499995e-1+y*(0.1430488765e-3
			+y*(-0.6911147651e-5+y*(0.7621095161e-6
			-y*0.934935152e-7)));
			ans=Math.sqrt(0.636619772/ax)*(Math.cos(xx)*ans1-z*Math.sin(xx)*ans2);
		}
		return ans;
	}	

}