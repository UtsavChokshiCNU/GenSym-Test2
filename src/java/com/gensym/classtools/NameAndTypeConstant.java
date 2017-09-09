package com.gensym.classtools;

class NameAndTypeConstant extends Constant
{	

	public NameAndTypeConstant(ConstantPool pool, String name, String type) 
		throws ClassException{
			super(CONSTANT_NAME_AND_TYPE);
			rawData1 = pool.add(new Utf8Constant(pool,name),true);
			rawData2 = pool.add(new Utf8Constant(pool,type),true);
			constantPool = pool;
	}

  	public NameAndTypeConstant(ConstantPool pool,int name_index, int descriptor_index) 
	   throws ClassException {
		super(CONSTANT_NAME_AND_TYPE);
        constantPool = pool;
		rawData1 = name_index;
		rawData2 = descriptor_index;
	}

	protected NameAndTypeConstant() {
		super(CONSTANT_NAME_AND_TYPE);
	}

	@Override

	public String getName() {
			return constantPool.getPool(rawData1).getName();
	}

	@Override

	public Object clone(boolean clonePool) {
		if (cloneInProgress != null)
			return cloneInProgress;
		NameAndTypeConstant clone = new NameAndTypeConstant();	
		return cloneWork(clone,clonePool);
	}

}
