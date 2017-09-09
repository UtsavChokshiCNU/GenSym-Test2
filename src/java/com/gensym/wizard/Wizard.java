package com.gensym.wizard;

import java.awt.Component;
import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Panel;
import java.awt.Label;
import java.awt.Font;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import java.util.Hashtable;
import java.util.Enumeration;

public class Wizard extends Panel 
                    implements WizardPeerListener 
{
  private Component title;
  private Component icon;
  private WizardPanel[] steps;
  private StartWizardPanel startPanel;
  private FinalWizardPanel finalPanel;
  private Panel stepPanel;
  private Panel buttonPanel;
  private Label stepLabel; 
  private int step = -1;

  private Button start;
  private Button back;
  private Button next;
  private Button finish;
  private Button cancel;
  private Button exit;
  private Button restart;

  private Hashtable listeners = new Hashtable();


  public Wizard(Component title,
                Component icon,
                WizardPanel[] steps,
                FinalWizardPanel finalPanel) 
  {
    this(title, icon, 
      new DefaultStartWizardPanel(((steps != null) ? steps.length +
                                  " Steps" :"") + "    ", steps),  
                                  steps, finalPanel);
  }

  public Wizard(Component title,
                Component icon,
                StartWizardPanel startPanel,
                WizardPanel[] steps,
                FinalWizardPanel finalPanel) 
  {
    this.startPanel = startPanel;
    buttonPanel = new Panel();
    
    start = new Button("Start>>");
    next = new Button("Next>>");
    back = new Button("<<Back");
    finish = new Button("Finish>>");
    cancel = new Button("Cancel");
    exit = new Button("Exit");
    restart = new Button("Restart");
    back.setEnabled(false);

    buttonPanel.add(start);
    buttonPanel.add(exit);

    stepLabel = new Label(startPanel.getTitle());
    stepLabel.setFont(new Font("TimesRoman", Font.BOLD, 18));

    stepPanel = new Panel();

    Panel centerLabel = new Panel();
    centerLabel.add(stepLabel);

    stepPanel.setLayout(new BorderLayout(0, 5));

    stepPanel.add(centerLabel, "North");
    stepPanel.add(buttonPanel, "South");
    stepPanel.setSize(100,300);

    this.finalPanel = finalPanel;
    this.steps = steps;

    if (startPanel != null) {
      stepPanel.add(startPanel, "Center");
    }
    setLayout(new BorderLayout(0, 5));
    add(title,"North");
    add(icon,"West");
    add(stepPanel,"Center");

    ActionListener listener = 
      new ActionListener() {
         @Override
		public void actionPerformed(ActionEvent e) {
           Button source = (Button)e.getSource();
           buttonPressed(source);
         }
    };

    start.addActionListener(listener);
    next.addActionListener(listener);
    back.addActionListener(listener);
    finish.addActionListener(listener);
    cancel.addActionListener(listener);
    exit.addActionListener(listener);
    restart.addActionListener(listener);
  }

  private void buttonPressed(Button pressed) {
      if (! fireBeforeEvents(pressed)) 
        return;
    
      if (pressed == start)
      {
        removeAllButtons();
        
        buttonPanel.add(back);
        buttonPanel.add(next);
        buttonPanel.add(exit);
        stepPanel.remove(startPanel);
        step++; 
        stepPanel.add(steps[step], "Center");
        stepPanel.validate();
      }
      else if (pressed == next)  
      {
        stepPanel.remove(steps[step]);
        step++;   
        stepPanel.add(steps[step], "Center");
      }
      else if (pressed == back)  {
        stepPanel.remove(steps[step]);
        step--;
        if (step == -1) {
          stepPanel.add(startPanel, "Center");
        }
        else {
          stepPanel.add(steps[step], "Center");
        }
      } 
      else if (pressed == finish) {  
          removeAllButtons();
          buttonPanel.add(cancel);
          cancel.setEnabled(true);
          buttonPanel.add(restart);
          restart.setEnabled(false);
          buttonPanel.add(exit);
          stepPanel.remove(steps[step]);
          stepPanel.add(finalPanel);
          stepLabel.setText(finalPanel.getTitle());  
          stepPanel.validate();
          step++;
      }
      else if (pressed == cancel) {
          swapForCompleted();          
          fireAfterEvents(pressed);
          return;
      }
      else if(pressed == exit) {
        fireAfterEvents(pressed);
      }
      else if (pressed == restart) {
          step = -1;
          stepPanel.remove(finalPanel);
          stepPanel.add(startPanel);
      }

      if (step == -1)
        stepLabel.setText(startPanel.getTitle());
      else if (step < steps.length)
            stepLabel.setText("Step " + (step + 1) + " of " + 
                steps.length);
      stepPanel.validate();
      back.setEnabled(true);
      
      if (step == -1) {
          removeAllButtons();
          buttonPanel.add(start);
          buttonPanel.add(exit);
          stepPanel.validate();
      }
      if (step == (steps.length - 1))
      {
        removeAllButtons();
        buttonPanel.add(back);
        buttonPanel.add(finish);
        buttonPanel.add(exit);
        buttonPanel.validate();
      }        
      else if (step == (steps.length - 2))
      {
        if (pressed == back) {
          removeAllButtons();
          buttonPanel.add(back);
          buttonPanel.add(next);
          buttonPanel.add(exit);
          buttonPanel.validate();
        }
      }
      fireAfterEvents(pressed);
  }

  private void removeAllButtons() {
    buttonPanel.remove(start);
    buttonPanel.remove(exit);
    buttonPanel.remove(back);
    buttonPanel.remove(next);
    buttonPanel.remove(finish);
    buttonPanel.remove(cancel);
    buttonPanel.remove(restart);
  }

  private void swapForCompleted() 
  {
    stepLabel.setText(getCurrentWizardPanel().getTitle());
    cancel.setEnabled(false);
    restart.setEnabled(true);
  }

  private boolean fireBeforeEvents(Button pressed)
  {
    Enumeration e;
    WizardListener l;
    WizardPanel panel = getCurrentWizardPanel();

    e = listeners.keys();
        
    while( e.hasMoreElements()) {
      l  = (WizardListener) e.nextElement();
      
      if (pressed == start) {
        if (! l.beforeWizardStart(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      else if (pressed == next) {
         if (! l.beforeWizardNext(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      else if (pressed == back) {
         if (! l.beforeWizardBack(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      if (pressed == cancel) {
         if (! l.beforeWizardCancel(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      else if (pressed == finish) {
         if (! l.beforeWizardFinish(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      else if (pressed == restart) {
         if (! l.beforeWizardRestart(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
      else if (pressed == exit) {
         if (! l.beforeWizardExit(new WizardEvent(this, 0, 
                                  panel)))
          return false;	
      }
    }
    return true;
  }

  private void fireAfterEvents(Button pressed) 
  {
    Enumeration e;
    WizardListener l;

    if (pressed == next)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardNext(new WizardEvent(this, 0, null));	
      }
      return;
    }

    if (pressed == back)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardBack(new WizardEvent(this, 0, null));	
      }
      return;
    }

    if (pressed == finish)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardFinish(new WizardEvent(this, 0, null));	
      }
      return;
    }

    if (pressed == cancel)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardCancel(new WizardEvent(this, 0, null));	
      }
      return;
    }

    if (pressed == exit)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardExit(new WizardEvent(this, 0, null));	
      }
      return;
    }

    if (pressed == restart)  {
      e = listeners.keys();
      
      while( e.hasMoreElements()) {
        l  = (WizardListener) e.nextElement();
        l.afterWizardRestart(new WizardEvent(this, 0, null));	
      }
      return;
    }

    // Default fire a WizardStart event
    e = listeners.keys();
        
    while( e.hasMoreElements()) {
      l  = (WizardListener) e.nextElement();
      l.afterWizardStart(new WizardEvent(this, 0, null));	
    }
  }

  public WizardPanel[] getStepWizardPanels()
  {
    WizardPanel[] newSteps = null;

    if (steps == null)
     return null;

    int length = steps.length;
    newSteps = new WizardPanel[length];

    for (int i = 0; i < length; i++) 
        newSteps[i] = steps[i];

    return newSteps;
  }

  public WizardPanel getCurrentWizardPanel() 
  {
    if (step == -1)
      return startPanel;
    if (step >= steps.length)
      return finalPanel;
    else return steps[step]; 
  }

  public FinalWizardPanel getFinalWizardPanel() 
  {
    return finalPanel;   
  }

  public Button getNextButton() 
  {
     return next;
  }

  public Button getFinishButton() 
  {
     return finish;
  }

  public Button getCancelButton() 
  {
     return cancel;
  }
  
  public Button getRestartButton() 
  {
     return restart;
  }

  @Override
  public Dimension getPreferredSize() {
      return new Dimension(600, 350);
  }

  @Override
  public Insets getInsets () {
      return new Insets(5, 10, 5, 10);
  }

  public void addWizardListener(WizardListener l)
  {
    synchronized (listeners) {
      if (! listeners.containsKey(l))
        listeners.put(l,l);	
    }
  }

  public void removeWizardListener(WizardListener l)
  {  
    synchronized (listeners) {
        if (listeners.containsKey(l))
			listeners.remove(l);  
    }
  }

  @Override
  public void wizardCompleted(WizardPeerEvent event)
  {
    if (getCurrentWizardPanel() == getFinalWizardPanel())
      swapForCompleted();
  }
}
