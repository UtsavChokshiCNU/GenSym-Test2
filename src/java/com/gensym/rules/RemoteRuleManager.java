package com.gensym.rules;

import java.rmi.*;

public interface RemoteRuleManager extends Remote
{
 
  public void installAntecedent(Rule rule, 
				RemoteRuleManager managerOfConsequent,
				int ruleSerialNumber)
       throws RemoteException;

  public boolean isAntecedentInstalled(RemoteRuleManager remoteRuleManager,
				       int serialNumber)
       throws RemoteException;
 
  public void uninstallAntecedent(RemoteRuleManager remoteRuleManager,
				  int serialNumber)
       throws RemoteException;

  public void fireRemoteConsequent(int ruleSerialNumber, RuleEvent event)
       throws RemoteException;
}


