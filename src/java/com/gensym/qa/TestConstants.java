package com.gensym.qa;

import com.gensym.util.Symbol;

public interface TestConstants {
  public static final Symbol FAILED_ = Symbol.intern("FAILED");
  public static final Symbol PASSED_ = Symbol.intern ("PASSED");
  public static final Symbol TIMEOUT_ = Symbol.intern ("TIMEOUT");
  public static final Symbol ABORT_ = Symbol.intern ("ABORT");
}
