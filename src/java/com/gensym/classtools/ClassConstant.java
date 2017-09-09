package com.gensym.classtools;

class ClassConstant extends Constant  {

  ClassConstant(ConstantPool pool, String className) throws ClassException {
    super(CONSTANT_CLASS);
    rawData1 
      = pool.add(new Utf8Constant(pool,
				  Type.canonicalizePackageSeparators(className)),
		 true);
    constantPool = pool;
  }

  ClassConstant(ConstantPool pool,int name_index) throws ClassException {
    super(CONSTANT_CLASS);
    constantPool = pool;
    rawData1 = name_index;
  }

  private ClassConstant() {
    super(CONSTANT_CLASS);
  }

  @Override

  public String getClassName() {	
    return constantPool.getPool(rawData1).getName();
  }

  @Override

  public Object clone(boolean clonePool) {
    if (cloneInProgress != null)
      return cloneInProgress;
    Constant clone = new ClassConstant();
    return cloneWork(clone,clonePool);
  }
}
