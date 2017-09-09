package com.gensym.rules;

import java.lang.reflect.Field;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Hashtable;

import com.gensym.core.IntHashtable;
import com.gensym.g2scriptruntime.NamingService;

public class RuleManager extends UnicastRemoteObject
  implements RemoteRuleManager
{
  IntHashtable installedRules = new IntHashtable();
  Hashtable installedAntecedents = new Hashtable();
  int highestRuleSerialNumber = 1;
  NamingService namingService;
  RuleClassManager classManager = new DefaultRuleClassManager();

  public RuleManager(NamingService namingService)
       throws RemoteException
  {
    this.namingService = namingService;
  }

  /** The classManager property getter.  The classManager mediates all classes
    stored, cached, and/or looked-up by the RuleManager for deployment flexability.
    */
  public RuleClassManager getClassManager()
  {
    return classManager;
  }
  
  /** The classManager property setter.  The classManager mediates all classes
    stored, cached, and/or looked-up by the RuleManager for deployment flexability.
    */
  public void setClassManager(RuleClassManager classManager)
  {
    this.classManager = classManager;
  }

  /** This is the implementation of the remote API to install
   *  a ruleAntecedent on some other node, that can fire consequents
   *  back to the "main" node.  This method should not be called directly
   *  by users.
   */

  @Override
  public synchronized void installAntecedent(Rule rule,
				RemoteRuleManager managerOfConsequent,
				int ruleSerialNumber)
       throws RemoteException
  {
    // the implementation of the remote antecedent installation API
    if (!isAntecedentInstalled(managerOfConsequent,ruleSerialNumber))
      {
	rule.ruleManager = this;
	rule.install();
	rule.remoteRuleSerialNumber = ruleSerialNumber;
	rule.remoteRuleManager = managerOfConsequent;
	installedAntecedents.put(new AntecedentEntry(managerOfConsequent,ruleSerialNumber),
			     rule);
      }
  }

  /** Remote interface implementation.  Do not call. */
  @Override
  public boolean isAntecedentInstalled(RemoteRuleManager remoteRuleManager,
				       int serialNumber)
  {
    return (installedAntecedents.get(new AntecedentEntry(remoteRuleManager,serialNumber))
	    != null);
  }

  /** Remote interface implementation.  Do not call. */
  @Override
  public void uninstallAntecedent(RemoteRuleManager remoteRuleManager,
				  int serialNumber)
  {
    Rule rule 
      = (Rule)installedAntecedents.get(new AntecedentEntry(remoteRuleManager,serialNumber));
    if (rule != null)
      {
	rule.uninstall();
	installedAntecedents.remove(new AntecedentEntry(remoteRuleManager,serialNumber));
      }
  }
  
  /** This method installs a rule (and it's antecedent) on a local VM
   */
  public void install(Rule rule)
  {
    if (Rule.debug)
      System.out.println("before install rule "+rule+" rsn = "+rule.ruleSerialNumber);
    ensureRuleInTable(rule);
    rule.install();
  }

  /** This method installs a rule consequent on the local VM, and 
   *  it's antecedent on the VM of the RemoteRuleManager.  This method
   *  can be called many times for the same rule paired with as many
   *  RemoteRuleManagers as desired.
   */

  public void install(Rule rule, RemoteRuleManager remoteRuleManager)
  {
    ensureRuleInTable(rule);
    try {
      remoteRuleManager.installAntecedent(rule, this, rule.ruleSerialNumber);
    } catch (RemoteException e)
      {
	throw new RuntimeException("Could not install rule remotely "+rule);
      }
  }

  private void ensureRuleInTable(Rule rule)
  {
    if (rule.ruleSerialNumber == 0)
      {
	System.out.println("putting rule in table etc "+rule);
	rule.ruleSerialNumber = highestRuleSerialNumber++;
	rule.ruleManager = this;
	installedRules.put(rule.ruleSerialNumber,rule);
      }
  }

  public boolean isRuleInstalled(Rule rule)
  {
    if (rule.ruleSerialNumber == 0)
      return false;
    else
      return (installedRules.get(rule.ruleSerialNumber) != null);
  }

  public boolean isRuleInstalled(Rule rule, RemoteRuleManager remoteRuleManager)
  {
    try {
      return remoteRuleManager.isAntecedentInstalled(this,rule.ruleSerialNumber);
    } catch (RemoteException e)
      {
	throw new RuntimeException("Could not test rule installation remotely "+rule);
      }
  }

  public void uninstallRule(Rule rule)
  {
    if (isRuleInstalled(rule))
      {
	rule.uninstall();
	installedRules.remove(rule.ruleSerialNumber);
      }
  }

  public void uninstallRule(Rule rule, RemoteRuleManager remoteRuleManager)
  {
    try {
      remoteRuleManager.uninstallAntecedent(this,rule.ruleSerialNumber);
      installedRules.remove(rule.ruleSerialNumber);
    } catch (RemoteException e)
      {
	throw new RuntimeException("Could not test rule installation remotely "+rule);
      }
  }

  /**
   *  Do not call.  Internal Remote interface.
   */

  @Override
  public void fireRemoteConsequent(int ruleSerialNumber, RuleEvent event)
  {
    Rule rule = (Rule) installedRules.get(ruleSerialNumber);
    try {
      Class instanceClass = rule.getInstanceClass();
      RuleInstance ruleInstance = (RuleInstance) instanceClass.newInstance();
      for (int i = 0; i<event.bindingNames.size(); i++)
	{
	  Field field = rule.cachedInstanceClass.getField((String)event.bindingNames.elementAt(i));
	  field.set(ruleInstance,event.boundValues.elementAt(i));
	}
      Thread thread = new Thread(ruleInstance);
      thread.start();
    } catch (Exception e)
      {
	System.out.println("fireRemoteConsequentFailed "+e.getMessage());
	e.printStackTrace();
      }
      
  }
}

class AntecedentEntry
{
  RemoteRuleManager remoteRuleManager;
  int serialNumber;

  AntecedentEntry(RemoteRuleManager remoteRuleManager,
		  int serialNumber)
  {
    this.remoteRuleManager = remoteRuleManager;
    this.serialNumber = serialNumber;
  }
  
  @Override
  public int hashCode()
  {
    return remoteRuleManager.hashCode() + serialNumber;
  }
  
  @Override
  public boolean equals(Object x)
  {
    if (x == null || !getClass().equals(x.getClass())){
    	return false;
    }
    
	AntecedentEntry otherEntry = (AntecedentEntry)x;
	return (serialNumber == otherEntry.serialNumber &&
		remoteRuleManager.equals(otherEntry.remoteRuleManager));
  }
}


