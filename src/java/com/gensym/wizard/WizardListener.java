package com.gensym.wizard;

public interface WizardListener
{
  public boolean beforeWizardStart(WizardEvent e);
  public void afterWizardStart(WizardEvent e);

  public boolean beforeWizardNext(WizardEvent e);
  public void afterWizardNext(WizardEvent e);

  public boolean beforeWizardBack(WizardEvent e);
  public void afterWizardBack(WizardEvent e);
  
  public boolean beforeWizardFinish(WizardEvent e);
  public void afterWizardFinish(WizardEvent e);

  public boolean beforeWizardCancel(WizardEvent e);
  public void afterWizardCancel(WizardEvent e);

  public boolean beforeWizardRestart(WizardEvent e);
  public void afterWizardRestart(WizardEvent e);

  public boolean beforeWizardExit(WizardEvent e);
  public void afterWizardExit(WizardEvent e);
 
}
