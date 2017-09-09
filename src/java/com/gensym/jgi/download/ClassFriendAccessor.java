package com.gensym.jgi.download;

import com.gensym.util.Symbol;
import com.gensym.util.Sequence;

public interface ClassFriendAccessor {

  public boolean register (Symbol className_, Class clazz);

  public void register (Symbol className,
			Symbol[] inheritancePath,
			Symbol[] staticAttributes);

  public Sequence getStaticAttributes (Symbol g2ClassName);

  public Symbol[] getClassInheritancePath (Symbol g2ClassName);

  public Symbol[] getDirectSuperiorClasses (Symbol g2ClassName);


}

