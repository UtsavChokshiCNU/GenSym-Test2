package com.gensym.rules;

/** 
 *  Subclass RuleInstance and override
 *  the doConsequentMethod
 */

public class RuleInstance
  implements Runnable
{
  public static final int MAX_WHENEVER_CONDITIONS = 10;

  public RuleInstance()
  {

  }
   
  @Override
  public void run()
  {
    doConsequent();
  }

  public static String nameWheneverTestMethod(int index)
  {
    return "wheneverTest"+index;
  }
 
  public boolean wheneverTest(int index)
  {
    switch (index)
      {
      case 0: return wheneverTest0();
      case 1: return wheneverTest1();
      case 2: return wheneverTest2();
      case 3: return wheneverTest3();
      case 4: return wheneverTest4();
      case 5: return wheneverTest5();
      case 6: return wheneverTest6();
      case 7: return wheneverTest7();
      case 8: return wheneverTest8();
      case 9: return wheneverTest9();
      default: throw new RuntimeException("Rule Failure:  whenever disjunct index out of range");
      }
  }

  public boolean wheneverTest0() { return false; }
  public boolean wheneverTest1() { return false; }
  public boolean wheneverTest2() { return false; }
  public boolean wheneverTest3() { return false; }
  public boolean wheneverTest4() { return false; }
  public boolean wheneverTest5() { return false; }
  public boolean wheneverTest6() { return false; }
  public boolean wheneverTest7() { return false; }
  public boolean wheneverTest8() { return false; }
  public boolean wheneverTest9() { return false; }

  public boolean filter()
  {
    return true;
  }

  public void pack(RuleEvent event)
  {
  }

  public void unpack(RuleEvent event)
  {
   
  }

  public void remoteDoConsequent(RuleEvent event)
  {
    // unpack the bindings
    Thread thread = new Thread(this);
    thread.start();
  }

  public void doConsequent()
  {
    System.out.println("Default Consequent taken from");
    Thread.dumpStack();
  }
}

