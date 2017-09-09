package com.gensym.ntw.rmi;

import com.gensym.jgi.rmi.*;
import netscape.security.PrivilegeManager;

public class TwRMIClientImplNS extends com.gensym.ntw.rmi.TwRMIClientImpl{

  public TwRMIClientImplNS(){
    super();
  }


  @Override
  public boolean initiateConnection(com.gensym.jgi.G2ConnectionInfo g2ConnectionInfo0)
  throws com.gensym.jgi.G2AccessInitiationException{
    boolean returnVar = false;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.initiateConnection(g2ConnectionInfo0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  protected com.gensym.classes.UiClientSession makeUiClientSession(com.gensym.ntw.LoginRequest loginRequest0)
  throws com.gensym.jgi.G2AccessException{
    com.gensym.classes.UiClientSession returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.makeUiClientSession(loginRequest0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public java.lang.String testCall(){
    java.lang.String returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.testCall();
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  protected void exportSelf(){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.exportSelf();
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public java.lang.Object callRPC(com.gensym.util.Symbol symbol0, java.lang.Object[] object1)
  throws com.gensym.jgi.G2AccessException{
    java.lang.Object returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.callRPC(symbol0, object1);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public java.lang.Object callRPC(com.gensym.util.Symbol symbol0, java.lang.Object[] object1, int int2)
  throws com.gensym.jgi.G2AccessException{
    java.lang.Object returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.callRPC(symbol0, object1, int2);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void startRPC(com.gensym.util.Symbol symbol0, java.lang.Object[] object1){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.startRPC(symbol0, object1);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public com.gensym.util.Structure subscribeToItem(com.gensym.classes.Item item0, com.gensym.util.Sequence sequence1, java.lang.Object object2)
  throws com.gensym.jgi.G2AccessException{
    com.gensym.util.Structure returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.subscribeToItem(item0, sequence1, object2);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public boolean unsubscribeToItem(int int0)
  throws com.gensym.jgi.G2AccessException{
    boolean returnVar = false;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.unsubscribeToItem(int0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void setInterfaceDebugOptions(boolean boolean0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.setInterfaceDebugOptions(boolean0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public com.gensym.classes.G2Definition getDefinition(com.gensym.util.Symbol symbol0)
  throws com.gensym.jgi.G2AccessException{
    com.gensym.classes.G2Definition returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.getDefinition(symbol0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void storeInterfaceForG2Class(java.lang.Class class0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.storeInterfaceForG2Class(class0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public java.lang.Class getInterfaceForG2Class(com.gensym.util.Symbol symbol0){
    java.lang.Class returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.getInterfaceForG2Class(symbol0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void dispatchG2ConnectionEvent(com.gensym.jgi.G2ConnectionEvent g2ConnectionEvent0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.dispatchG2ConnectionEvent(g2ConnectionEvent0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public void receiveServerDisconnectEvent(com.gensym.message.MessageEvent messageEvent0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.receiveServerDisconnectEvent(messageEvent0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public void setRemoteRPCReturnKind(com.gensym.util.Symbol symbol0, int int1){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.setRemoteRPCReturnKind(symbol0, int1);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public void processEventQueue(java.util.Vector vector0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.processEventQueue(vector0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public java.lang.Integer subscribeToWorkspaceShowing(com.gensym.classes.UiClientSession uiClientSession0)
  throws com.gensym.jgi.G2AccessException{
    java.lang.Integer returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.subscribeToWorkspaceShowing(uiClientSession0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void unsubscribeToWorkspaceShowing(java.lang.Integer integer0)
  throws com.gensym.jgi.G2AccessException{
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.unsubscribeToWorkspaceShowing(integer0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  protected com.gensym.util.Structure representWorkspace(com.gensym.classes.KbWorkspace kbWorkspace0, com.gensym.util.Symbol symbol1)
  throws com.gensym.jgi.G2AccessException{
    com.gensym.util.Structure returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.representWorkspace(kbWorkspace0, symbol1);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public boolean unrepresentWorkspace(int int0)
  throws com.gensym.jgi.G2AccessException{
    boolean returnVar = false;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.unrepresentWorkspace(int0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public com.gensym.util.Structure subscribeToModules()
  throws com.gensym.jgi.G2AccessException{
    com.gensym.util.Structure returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.subscribeToModules();
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

  @Override
  public void handleWorkspaceSubscriptions(com.gensym.util.WorkspaceEvent workspaceEvent0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.handleWorkspaceSubscriptions(workspaceEvent0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public void handleWorkspaceSubscriptions(com.gensym.ntw.rmi.RMIWorkspaceEvent rMIWorkspaceEvent0){
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      super.handleWorkspaceSubscriptions(rMIWorkspaceEvent0);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return;
  }

  @Override
  public com.gensym.util.Structure representTrendChart(com.gensym.classes.Item item0, com.gensym.classes.TrendChart trendChart1, java.lang.Object object2)
  throws com.gensym.jgi.G2AccessException{
    com.gensym.util.Structure returnVar = null;
    try {
      PrivilegeManager.enablePrivilege("UniversalListen");
      PrivilegeManager.enablePrivilege("UniversalSetFactory");
      PrivilegeManager.enablePrivilege("UniversalConnect");
      PrivilegeManager.enablePrivilege("UniversalPropertyRead");
      returnVar = super.representTrendChart(item0, trendChart1, object2);
    } catch (netscape.security.ForbiddenTargetException e) {
      throw new com.gensym.util.UnexpectedException(e);
    }
    return returnVar;
  }

}
