package com.gensym.classtools;
import java.util.Vector;

class ValueConstant extends Constant {
		
	public ValueConstant(ConstantPool pool, int value) {
		super(CONSTANT_INTEGER);
		rawData1 = (value >> 16) & 0xFFFF;
		rawData2 = (value & 0xFFFF);
		pool.add(this,true);
	}

	public ValueConstant(ConstantPool pool,float value) {
		super(CONSTANT_FLOAT);
		constantPool = pool;
		int intbits = Float.floatToIntBits(value);
		rawData1 = (intbits >> 16) & 0xFFFF;
		rawData2 = (intbits & 0xFFFF);
		pool.add(this,true);
	}

	public ValueConstant(ConstantPool pool,double value) {
		super(CONSTANT_DOUBLE);
		constantPool = pool;
		long longbits = Double.doubleToLongBits(value);
		rawData1 = (int) ((longbits >> 48) & 0xFFFF);
		rawData2 = (int) ((longbits >> 32) & 0xFFFF);
		rawData3 = (int) ((longbits >> 16) & 0xFFFF);
		rawData4 = (int) (longbits & 0xFFFF);
		if (pool.member(this) == -1) {
			pool.add(this,true);
			pool.add(null,true);    // Add null element to take up two indexes
		}
	}

	public ValueConstant(ConstantPool pool,long value) {
		super(CONSTANT_LONG);
		constantPool = pool;
		rawData1 = (int) ((value >> 48) & 0xFFFF);
		rawData2 = (int) ((value >> 32) & 0xFFFF);
		rawData3 = (int) ((value >> 16) & 0xFFFF);
		rawData4 = (int) (value & 0xFFFF);
		if (pool.member(this) == -1) {
			pool.add(this,true);
			pool.add(null,true); 	// Add null element to take up two indexes
		}
	}

	public ValueConstant(ConstantPool pool,String st) {
		super(CONSTANT_STRING);
		constantPool = pool;
		rawData1 = constantPool.add(new Utf8Constant(st),true);
		constantPool.add(this,true);
	}

	ValueConstant(int type) {
		super(type);
	}

	@Override
	public Object clone(boolean clonePool) {
		if (cloneInProgress != null)
			return cloneInProgress;
		Constant clone = new ValueConstant(type);		
		return cloneWork(clone,clonePool);
	}
}
