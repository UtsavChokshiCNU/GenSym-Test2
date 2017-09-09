package com.gensym.ntw.attrdisplays;

import java.util.Vector;
import com.gensym.uitools.attrdisplays.layoutmodel.LayoutStructure;
import com.gensym.uitools.attrdisplays.layoutmodel.VectorsNotSameLengthException;

public class G2GlobalLayout extends LayoutStructure {
  static Vector keys = new Vector();
  static Vector values = new Vector();
  static {
    keys.add(G2AttributeDisplayLayoutConverter.TEXT_COLOR);
    keys.add(G2AttributeDisplayLayoutConverter.POSITION);
    values.add(G2AttributeDisplayLayoutConverter.FOREGROUND_);
    values.add(G2AttributeDisplayLayoutConverter.AT_STANDARD_POSITION_);
  }

  public G2GlobalLayout() throws VectorsNotSameLengthException {
    super(null, keys, values);
  }
}
