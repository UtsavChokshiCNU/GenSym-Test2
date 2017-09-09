package com.gensym.wizard;

import java.awt.Frame;
import java.awt.Panel;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class WizardFrame extends Frame 
                         implements WindowListener, 
                                    WizardListener

{
  private Wizard wizard;

  public WizardFrame(String name, Wizard wiz)
  {
    super(name);
    initialize(name, wiz);
  }

  private void initialize(String name, Wizard wiz)
  {
    setSize(wiz.getPreferredSize());
    add(wiz);
    addWindowListener(this);
    wiz.addWizardListener(this);
  }

  //****************** Window Events *****************

  @Override
  public void windowOpened(WindowEvent e) {
  }

  @Override
  public void windowClosing(WindowEvent e) {
    System.exit(0);
  }

  @Override
  public  void windowClosed(WindowEvent e) {
    System.exit(0);
  }

  @Override
  public void windowIconified(WindowEvent e) {
  }

 @Override
 public  void windowDeiconified(WindowEvent e) {
 }


 @Override
 public  void windowActivated(WindowEvent e) {
 }

 @Override
 public void windowDeactivated(WindowEvent e) {
 }

 //****************** Wizard Events *****************

 @Override
 public boolean beforeWizardStart(WizardEvent e)
 {
    return true;
 }

 @Override
 public void afterWizardStart(WizardEvent e)
 {}

 @Override
 public boolean beforeWizardNext(WizardEvent e)
 {
   return true;
 }
 @Override
 public void afterWizardNext(WizardEvent e)
 {}
 
 @Override
 public boolean beforeWizardBack(WizardEvent e)
 {
  return true;
 }

 @Override
 public void afterWizardBack(WizardEvent e)
 {}
 
 @Override
 public boolean beforeWizardFinish(WizardEvent e) {
    return true;
 }
 @Override
 public void afterWizardFinish(WizardEvent e) {}
 
 @Override
 public boolean beforeWizardCancel(WizardEvent e)
 {
  return true;
 }

 @Override
 public void afterWizardCancel(WizardEvent e) 
 {}
 
 @Override
 public boolean beforeWizardRestart(WizardEvent e) 
 {
  return true;
 }
 
 @Override
 public void afterWizardRestart(WizardEvent e) {}
 
 @Override
 public boolean beforeWizardExit(WizardEvent e)
 {
   return true;
 }
 @Override
 public void afterWizardExit(WizardEvent e) 
 {
   System.exit(0);
 } 
}
