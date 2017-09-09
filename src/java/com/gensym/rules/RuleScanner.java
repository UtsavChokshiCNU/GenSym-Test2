package com.gensym.rules;

import java.util.Vector;

public class RuleScanner implements Runnable
{
  long interval; // milliseconds
  Thread thread;
  Rule rule;
  boolean stop = false;

  public RuleScanner(Rule rule, long interval)
  {
    this.rule = rule;
    this.interval = interval;
    thread = new Thread(this);
    thread.start();
  }

  void stop()
  {
    stop = true;
  }

  @Override
  public void run()
  {
    try {
      while (!stop)
	{
	  Thread.sleep(interval);
	  rule.runAntecedents(rule.filterConditions,0,null,null,
			      new Vector(), new Vector(), -1);
	}
    } catch (Exception ie)
      {
	System.out.println("Rule Scan Problem");
	ie.printStackTrace();
      }
  }
}
