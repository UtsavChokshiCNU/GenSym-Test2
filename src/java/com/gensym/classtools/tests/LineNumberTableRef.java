package com.gensym.classtools.tests;

import com.gensym.classtools.*;
import java.util.*;
import java.io.*;

public class LineNumberTableRef implements TestExpressionInterface {


  @Override
  public void test() {
    try {
        throw new Exception();  // Line number 12
    }
    catch (Exception e) {
        e.printStackTrace();   // Line number 16
    }
  }
}
