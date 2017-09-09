package com.gensym.wizard;

import java.awt.Dialog;
import java.awt.Frame;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class WizardDialog extends Dialog 
                          implements WindowListener,
                                     WizardListener
{
  public WizardDialog(Frame parent, String title, 
                      Wizard wiz, boolean modal)
  {
    super(parent, title, modal);
    initialize(title, wiz);
  }

  private void initialize(String name, Wizard wiz)
  {
    setSize(wiz.getPreferredSize());
    add(wiz);
    addWindowListener(this);
    wiz.addWizardListener(this);
  }

  //*************** Window Events ************

  @Override
  public void windowOpened(WindowEvent e) {
  }

  @Override
  public void windowClosing(WindowEvent e) {
    setVisible(false);
  }

  @Override
  public  void windowClosed(WindowEvent e) {
    setVisible(false);
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

  //*************** Wizard Events ************

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
  public boolean beforeWizardCancel(WizardEvent e)
  {
    return true;
  }

  @Override
  public boolean beforeWizardBack(WizardEvent e)
  {
  return true;
  }

  @Override
  public void afterWizardBack(WizardEvent e)
  {}

  @Override
  public void afterWizardCancel(WizardEvent e) 
  {}
  
  @Override
  public boolean beforeWizardFinish(WizardEvent e) {
    return true;
  }
  @Override
  public void afterWizardFinish(WizardEvent e) {}

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
    setVisible(false);
  } 
}
