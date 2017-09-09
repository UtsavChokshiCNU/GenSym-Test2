package com.gensym.controls;

import java.util.Vector;
import java.io.Serializable;

import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.ntw.TwConnectionEvent;

public class TwActiveXConnector extends java.lang.Object implements Serializable {

  static final long serialVersionUID = 2L;
  
  private com.gensym.controls.TwConnector wrapped = new com.gensym.controls.TwConnector();
  public TwActiveXConnector(){
    initializeInternalListener();
  }

  private void initializeInternalListener() {
    twConnectionListener = new TwActiveXConnectionAdapter(this);
    wrapped.addTwConnectionListener(twConnectionListener);
  }


  public void createConnection()
       throws com.gensym.jgi.G2AccessException{
	 wrapped.createConnection();
	 return;
  }

  public void addWorkspaceShowingListener(com.gensym.ntw.WorkspaceShowingListener workspaceShowingListener0)
       throws com.gensym.jgi.G2AccessException{
	 wrapped.addWorkspaceShowingListener(workspaceShowingListener0);
	 return;
  }

  public void removeWorkspaceShowingListener(com.gensym.ntw.WorkspaceShowingListener workspaceShowingListener0)
       throws com.gensym.jgi.G2AccessException{
	 wrapped.removeWorkspaceShowingListener(workspaceShowingListener0);
	 return;
  }

  public void setConnectionClassName(java.lang.String string0){
    wrapped.setConnectionClassName(string0);
    return;
  }

  public void setGsiInterfaceClassName(java.lang.String string0){
    wrapped.setGsiInterfaceClassName(string0);
    return;
  }

  public com.gensym.util.Structure getDialog(com.gensym.classes.Item item0, com.gensym.util.Symbol symbol1, com.gensym.util.Structure structure2)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Structure returnVar = null;
	 returnVar = wrapped.getDialog(item0, symbol1, structure2);
	 return returnVar;
  }

  public com.gensym.classes.Item createItem(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.classes.Item returnVar = null;
	 returnVar = wrapped.createItem(symbol0);
	 return returnVar;
  }

  public void setUserMode(java.lang.String string0)
       throws com.gensym.jgi.G2AccessException{
	 wrapped.setUserMode(string0);
	 return;
  }

  public java.lang.String getUserMode()
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.getUserMode();
	 return returnVar;
  }

  public void setUserName(java.lang.String string0){
    wrapped.setUserName(string0);
    return;
  }

  public java.lang.String getUserName(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getUserName();
    return returnVar;
  }

  public void setUserPassword(java.lang.String string0){
    wrapped.setUserPassword(string0);
    return;
  }

  public com.gensym.util.Sequence getNamedWorkspaces()
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Sequence returnVar = null;
	 returnVar = wrapped.getNamedWorkspaces();
	 return returnVar;
  }

  public com.gensym.util.Structure getFormatInfo(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Structure returnVar = null;
	 returnVar = wrapped.getFormatInfo(symbol0);
	 return returnVar;
  }

  public com.gensym.irm.IconRenderingManager getIconManager(){
    com.gensym.irm.IconRenderingManager returnVar = null;
    returnVar = wrapped.getIconManager();
    return returnVar;
  }

  public com.gensym.util.Structure subscribeToModules()
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Structure returnVar = null;
	 returnVar = wrapped.subscribeToModules();
	 return returnVar;
  }

  public void unsubscribeToModules()
       throws com.gensym.jgi.G2AccessException{
	 wrapped.unsubscribeToModules();
	 return;
  }

  public com.gensym.dlgruntime.DialogManager getDialogManager(){
    com.gensym.dlgruntime.DialogManager returnVar = null;
    returnVar = wrapped.getDialogManager();
    return returnVar;
  }

  public com.gensym.classes.Kb getKb(){
    com.gensym.classes.Kb returnVar = null;
    returnVar = wrapped.getKb();
    return returnVar;
  }

  public com.gensym.classes.UserMenuChoice getUserMenuChoice(com.gensym.util.Symbol symbol0, com.gensym.util.Symbol symbol1)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.classes.UserMenuChoice returnVar = null;
	 returnVar = wrapped.getUserMenuChoice(symbol0, symbol1);
	 return returnVar;
  }

  // begin hand code

  TwConnectionListener twConnectionListener;

  void redispatchTwConnectionEvent(TwConnectionEvent evt) {
    Vector list;
    synchronized(listeners) {
      list = (Vector)listeners.clone();
    }

    TwActiveXConnectionEvent e = new TwActiveXConnectionEvent(this, evt);
    int id = e.getId();
    int len = list.size();
    for(int i = 0; i < len; i++) {
      TwActiveXConnectionListener l = (TwActiveXConnectionListener)list.elementAt(i);
      switch(id) {
      case TwConnectionEvent.CONNECTION_LOGGED_IN:
	l.loggedIn(e);
	break;
      case TwConnectionEvent.CONNECTION_LOGGED_OUT:
	l.loggedOut(e);
	break;
      case TwConnectionEvent.USER_MODE_CHANGED:
	l.userModeChanged(e);
      }
    }
  }

  private Vector listeners = new Vector();	 

  public void addTwActiveXConnectionListener(TwActiveXConnectionListener TwActiveXConnectionListener0){
    listeners.addElement(TwActiveXConnectionListener0);
  }

  public void removeTwActiveXConnectionListener(TwActiveXConnectionListener TwActiveXConnectionListener0){
    listeners.removeElement(TwActiveXConnectionListener0);
  }

  // end hand code

  public java.lang.Object callRPCForVB(com.gensym.util.Symbol symbol0, com.gensym.util.Sequence sequence1, int int2)
       throws com.gensym.jgi.G2AccessException{
	 java.lang.Object returnVar = null;
	 returnVar = wrapped.callRPCForVB(symbol0, sequence1, int2);
	 return returnVar;
  }

  public void startRPCForVB(com.gensym.util.Symbol symbol0, com.gensym.util.Sequence sequence1){
    wrapped.startRPCForVB(symbol0, sequence1);
    return;
  }

  public java.lang.Object getThis(){
    java.lang.Object returnVar = null;
    returnVar = wrapped.getThis();
    return returnVar;
  }

  // from G2Connector
  public java.lang.String getBrokerURL(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getBrokerURL();
    return returnVar;
  }

  public void setBrokerURL(java.lang.String string0){
    wrapped.setBrokerURL(string0);
    return;
  }

  public java.lang.String getLogicalName(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getLogicalName();
    return returnVar;
  }

  public void setLogicalName(java.lang.String string0){
    wrapped.setLogicalName(string0);
    return;
  }

  public java.lang.String getHost(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getHost();
    return returnVar;
  }

  public void setHost(java.lang.String string0){
    wrapped.setHost(string0);
    return;
  }

  public java.lang.String getPort(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getPort();
    return returnVar;
  }

  public void setPort(java.lang.String string0){
    wrapped.setPort(string0);
    return;
  }

  public java.lang.String getConnectionClassName(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getConnectionClassName();
    return returnVar;
  }

  public java.lang.String getGsiInterfaceClassName(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getGsiInterfaceClassName();
    return returnVar;
  }

  public boolean isPermanent(){
    boolean returnVar = false;
    returnVar = wrapped.isPermanent();
    return returnVar;
  }

  public void setPermanent(boolean boolean0){
    wrapped.setPermanent(boolean0);
    return;
  }

  public boolean isSharable(){
    boolean returnVar = false;
    returnVar = wrapped.isSharable();
    return returnVar;
  }

  public void setSharable(boolean boolean0){
    wrapped.setSharable(boolean0);
    return;
  }

  public boolean isForceNew(){
    boolean returnVar = false;
    returnVar = wrapped.isForceNew();
    return returnVar;
  }

  public void setForceNew(boolean boolean0){
    wrapped.setForceNew(boolean0);
    return;
  }

  public java.lang.String getGsiInterfaceName(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getGsiInterfaceName();
    return returnVar;
  }

  public void setGsiInterfaceName(java.lang.String string0){
    wrapped.setGsiInterfaceName(string0);
    return;
  }

  public java.lang.String getRemoteProcessInitString(){
    java.lang.String returnVar = null;
    returnVar = wrapped.getRemoteProcessInitString();
    return returnVar;
  }

  public void setRemoteProcessInitString(java.lang.String string0){
    wrapped.setRemoteProcessInitString(string0);
    return;
  }

  public com.gensym.jgi.G2Connection getConnection(){
    com.gensym.jgi.G2Connection returnVar = null;
    returnVar = wrapped.getConnection();
    return returnVar;
  }

  public void addG2ConnectionListener(com.gensym.jgi.G2ConnectionListener g2ConnectionListener0){
    wrapped.addG2ConnectionListener(g2ConnectionListener0);
    return;
  }

  public void removeG2ConnectionListener(com.gensym.jgi.G2ConnectionListener g2ConnectionListener0){
    wrapped.removeG2ConnectionListener(g2ConnectionListener0);
    return;
  }

  public void returnMessage(java.lang.String string0){
    wrapped.returnMessage(string0);
    return;
  }

  public void reportLogBookErrorMessage(com.gensym.util.Symbol symbol0, java.lang.String string1){
    wrapped.reportLogBookErrorMessage(symbol0, string1);
    return;
  }

  public void closeConnection(){
    wrapped.closeConnection();
    return;
  }

  public void registerJavaMethod(java.lang.Object object0, java.lang.String string1, com.gensym.util.Symbol symbol2){
    wrapped.registerJavaMethod(object0, string1, symbol2);
    return;
  }

  public void registerJavaMethod(java.lang.Object object0, java.lang.reflect.Method method1, com.gensym.util.Symbol symbol2, boolean boolean3){
    wrapped.registerJavaMethod(object0, method1, symbol2, boolean3);
    return;
  }

  public java.lang.Object callRPC(com.gensym.util.Symbol symbol0, java.lang.Object[] object1, int int2)
       throws com.gensym.jgi.G2AccessException{
	 java.lang.Object returnVar = null;
	 returnVar = wrapped.callRPC(symbol0, object1, int2);
	 return returnVar;
  }

  public java.lang.Object callRPC(com.gensym.util.Symbol symbol0, com.gensym.util.Sequence sequence1, int int2)
       throws com.gensym.jgi.G2AccessException{
	 java.lang.Object returnVar = null;
	 returnVar = wrapped.callRPC(symbol0, sequence1, int2);
	 return returnVar;
  }

  public void startRPC(com.gensym.util.Symbol symbol0, java.lang.Object[] object1){
    wrapped.startRPC(symbol0, object1);
    return;
  }

  public void startRPC(com.gensym.util.Symbol symbol0, com.gensym.util.Sequence sequence1){
    wrapped.startRPC(symbol0, sequence1);
    return;
  }

  public boolean canCallRPC(){
    boolean returnVar = false;
    returnVar = wrapped.canCallRPC();
    return returnVar;
  }

  public void setRemoteRPCReturnKind(com.gensym.util.Symbol symbol0, int int1){
    wrapped.setRemoteRPCReturnKind(symbol0, int1);
    return;
  }

  public com.gensym.classes.Item getUniqueNamedItem(com.gensym.util.Symbol symbol0, com.gensym.util.Symbol symbol1)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.classes.Item returnVar = null;
	 returnVar = wrapped.getUniqueNamedItem(symbol0, symbol1);
	 return returnVar;
  }

  public java.lang.String getAttributeAsText(com.gensym.classes.Item item0, com.gensym.util.Symbol symbol1, com.gensym.util.Symbol symbol2)
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.getAttributeAsText(item0, symbol1, symbol2);
	 return returnVar;
  }

  public com.gensym.util.Sequence getAttributeDescriptions(com.gensym.util.Symbol symbol0, com.gensym.util.Sequence sequence1)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Sequence returnVar = null;
	 returnVar = wrapped.getAttributeDescriptions(symbol0, sequence1);
	 return returnVar;
  }

  public double g2UnixTime()
       throws com.gensym.jgi.G2AccessException{
	 double returnVar = (double)0;
	 returnVar = wrapped.g2UnixTime();
	 return returnVar;
  }

  public double g2UnixTimeAtStart()
       throws com.gensym.jgi.G2AccessException{
	 double returnVar = (double)0;
	 returnVar = wrapped.g2UnixTimeAtStart();
	 return returnVar;
  }

  public java.lang.String g2GetHostName()
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.g2GetHostName();
	 return returnVar;
  }

  public java.lang.String g2GetPortNumberOrName()
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.g2GetPortNumberOrName();
	 return returnVar;
  }

  public java.lang.String g2GetPortNumberOrNameGivenIndex(int int0)
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.g2GetPortNumberOrNameGivenIndex(int0);
	 return returnVar;
  }

  public java.lang.String g2GetSoftwareVersion()
       throws com.gensym.jgi.G2AccessException{
	 java.lang.String returnVar = null;
	 returnVar = wrapped.g2GetSoftwareVersion();
	 return returnVar;
  }

  public com.gensym.util.Symbol getG2State()
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Symbol returnVar = null;
	 returnVar = wrapped.getG2State();
	 return returnVar;
  }

  public com.gensym.util.Symbol setG2State(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Symbol returnVar = null;
	 returnVar = wrapped.setG2State(symbol0);
	 return returnVar;
  }

  public com.gensym.util.Sequence getStrictInstancesOfClass(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Sequence returnVar = null;
	 returnVar = wrapped.getStrictInstancesOfClass(symbol0);
	 return returnVar;
  }

  public com.gensym.util.Sequence getDirectSubclasses(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.util.Sequence returnVar = null;
	 returnVar = wrapped.getDirectSubclasses(symbol0);
	 return returnVar;
  }

  public void setInterfaceDebugOptions(boolean boolean0){
    wrapped.setInterfaceDebugOptions(boolean0);
    return;
  }

  public com.gensym.classes.G2Definition getDefinition(com.gensym.util.Symbol symbol0)
       throws com.gensym.jgi.G2AccessException{
	 com.gensym.classes.G2Definition returnVar = null;
	 returnVar = wrapped.getDefinition(symbol0);
	 return returnVar;
  }

  private void readObject (java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException{
    stream.defaultReadObject();
    initializeInternalListener();
  }

}
