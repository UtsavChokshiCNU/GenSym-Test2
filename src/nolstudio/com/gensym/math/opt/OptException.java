package com.gensym.math.opt;
import com.gensym.math.MathException;
import com.gensym.math.matrix.*;


public class OptException extends MathException {

	private int flag; // 0:reach max iteration
	private Matrix simplexP;

	public OptException (String ErrorDetails) {
		super(ErrorDetails);
	}

	public void setFlag(int f){
		flag = f;
	}

	public int getFlag(){
		return flag;
	}

	public void setSimplexMatrix(Matrix p){
		simplexP = p;
	}

	public Matrix getSimplexMatrix(){
		if(simplexP != null){
			return simplexP;
		}else{
			return null;
		}
	}

	@Override
	public String toString () {
		return (""+ super.toString());
	}

}
