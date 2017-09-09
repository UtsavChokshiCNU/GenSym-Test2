
package com.gensym.jgi.download;

import com.gensym.types.G2Type;
import com.gensym.util.*;

public class AttrInfo {
  public Symbol[] attrTypes, attrNames;
  public boolean[] systemDefined, readable, writable, staticP;
  public Symbol[] origNames, defClasses;
  public G2Type[] typeSpecifications;
  public Object[] initialValues;

  public AttrInfo (Symbol[] attrTypes, Symbol[] attrNames, boolean[] systemDefined, boolean[] readable, boolean[] writable, boolean[] staticP, Symbol[] origNames, Symbol[] definingClasses, G2Type[] typeSpecifications, Object[] initialValues) {
    this.attrTypes          = attrTypes;
    this.attrNames          = attrNames;
    this.systemDefined      = systemDefined;
    this.readable           = readable;
    this.writable           = writable;
    this.staticP            = staticP;
    this.origNames          = origNames;
    this.defClasses         = definingClasses;
    this.typeSpecifications = typeSpecifications;
    this.initialValues      = initialValues;
  }
}
