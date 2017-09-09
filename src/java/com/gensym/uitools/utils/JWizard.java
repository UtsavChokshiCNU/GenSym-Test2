package com.gensym.uitools.utils;

import java.awt.*;
import java.awt.event.*;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.Vector;


import javax.swing.*;

import com.gensym.message.Resource;

/* This wizard's purpose is hold content panels which are supplied
 * by the StepListener. The wizard itself does not control the order
 * of steps, nor the availability of the back/next/finish/cancel buttons.
 * All of those are handled by the StepListener.*/

public class JWizard extends JDialog implements ActionListener{

  private Container contentPane;
  private Component currentComponent;
  private JPanel controlPanel;
  private JPanel insertablePanel;
  private JButton backButton, nextButton, cancelButton, finishButton;
  //listeners is populated by StepListeners
  private Vector listeners = new Vector();
  private boolean wasCancelled;

  private static final Resource i18ui = Resource.getBundle("com/gensym/uitools/utils/WizardResource");
  private static final int insertPanelIndex = 0;
  private static final int controlPanelIndex = 1;

  public JWizard(Frame parent, String title, boolean modal){
    super (parent,
	   title,
	   modal);
    dialogInit();
    //do I need this? Don't I handle this in stepCancel?
    //setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
    contentPane = getContentPane();
    buildUI();
  }

  /* The capability to add more than one steplistener
   * is implemented. However, I don't really see the purpose
   * of this yet. Since the Step Listener provides the content
   * panels, as well as serves as the state machine, how can
   * there be more than one? */

  public void addStepListener(StepListener listener){
    synchronized (listeners){
      if(! listeners.contains(listener))
	listeners.add(listener);
    }
  }

  public void removeStepListener(StepListener listener){
    synchronized(listeners){
      if(listeners.contains(listener))
	listeners.remove(listener);
    }
  }

  /* Need a method to start the wizard with the first panel.
   * This method should be called after the appropriate listeners
   * have been added. */
  public void startWizard(){
    Enumeration e;
    StepListener sl;
    e = listeners.elements();
    StepEvent stepEvent = new StepEvent(this, 0, null);

    while(e.hasMoreElements()){
      sl = (StepListener)e.nextElement();
      sl.stepForward(stepEvent);
    }
  }

  @Override
  public void setVisible (boolean showQ) {  // Fixes bug under Win95
    if (showQ) {
      Dimension frameSize = getParent().getSize();
      Point     frameLoc  = getParent().getLocation();
      Dimension mySize    = getSize();
      int       x,y;
      
      x = Math.max(0, frameLoc.x + (frameSize.width/2) -(mySize.width/2));
      y = Math.max(0,frameLoc.y + (frameSize.height/2)-(mySize.height/2));
     
      setBounds (x, y, mySize.width, mySize.height);
    }
    updateFocus();
    super.setVisible (showQ);
  }

  public void setComponent(Component display){
    if(currentComponent != null) {
      contentPane.remove(currentComponent);
    }
    currentComponent = display;
    if (display != null) {
      contentPane.add(currentComponent, BorderLayout.CENTER);
      updateFocus();
    }
    invalidate();
    validate();
    repaint();
  }

  protected void updateFocus()
  {
    if (currentComponent instanceof JComponent)
      ((JComponent)currentComponent).requestDefaultFocus();
    else
      currentComponent.requestFocus();
  }

  public void setButtonAvailability(boolean cancel,
				    boolean back,
				    boolean next,
				    boolean finish) {
    backButton.setEnabled(back);
    nextButton.setEnabled(next);
    finishButton.setEnabled(finish);
    cancelButton.setEnabled(cancel);
  }
  
  public void buildUI(){

    addWindowListener(
      new WindowAdapter() {
        @Override
        public void windowClosing(WindowEvent e)
        {
          cancel();                             
        }
      }
    );
    setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

    nextButton = new JButton(i18ui.getString("nextButton"));
    backButton = new JButton(i18ui.getString("backButton"));
    cancelButton = new JButton(i18ui.getString("cancelButton"));
    finishButton = new JButton(i18ui.getString("finishButton"));

    nextButton.addActionListener(this);
    backButton.addActionListener(this);
    cancelButton.addActionListener(this);
    finishButton.addActionListener(this);

    cancelButton.setDefaultCapable(false);
    backButton.setDefaultCapable(false);

    controlPanel = new JPanel();
    controlPanel.add(cancelButton);
    controlPanel.add(backButton);
    controlPanel.add(nextButton);
    controlPanel.add(finishButton);

    contentPane.setLayout(new BorderLayout(0,5));
    currentComponent = null;
    
    //trying to identify the index of the insertablePanel
    //so that I can remove it later????
    contentPane.add(controlPanel, BorderLayout.SOUTH);
  }

  @Override
  public void setTitle(String title) {
    setTitle(title);
  }

  public int  getControlPanelWidth(){
    int width = controlPanel.getPreferredSize().width;
    return width;
  }

  public int getControlPanelHeight(){
    return controlPanel.getPreferredSize().height;
  }

  //actionListener implementation
  @Override
  public void actionPerformed(ActionEvent ae){
    Vector stepListeners;
    synchronized(listeners){
      stepListeners = (Vector)listeners.clone();
    }    
    Enumeration e;
    StepListener sl;
    e = stepListeners.elements();
    StepEvent stepEvent = new StepEvent(this,0,null);
    
    while(e.hasMoreElements()){
      sl = (StepListener)e.nextElement();
      
      if(ae.getSource() == nextButton){
	sl.stepForward(stepEvent);
	
      }else if (ae.getSource() == backButton){
	sl.stepBack(stepEvent);
	
      }else if (ae.getSource() == cancelButton){
	sl.stepCancel(stepEvent);
	
      }else if (ae.getSource() == finishButton){
	sl.stepFinish(stepEvent);
	
      }
    }
  }  
  //end of ActionListener implementation

  // main added by bbush, July 19, 2000
  public static void main(String[] args) {

    class PanelProvider implements StepListener {
      int state = 0;
      
      @Override
      public void stepForward(StepEvent e) {
		Object src = e.getSource();
		if(src instanceof JWizard) {
		  JPanel p = new JPanel();
		  p.setLayout(new BorderLayout());
		  p.add(new JLabel("test" + state), BorderLayout.CENTER);
		  ((JWizard)src).setComponent(p);
		  state++;
		}
      }
      @Override
      public void stepBack(StepEvent e) {}
      @Override
      public void stepFinish(StepEvent e) {}
      @Override
      public void stepCancel(StepEvent e) {
	System.exit(0);
      } 
      public void setFirstPanel(boolean first) {}
    }

    StepListener stepListener = new PanelProvider();    
    JWizard wizard = new JWizard(null, "Test Wizard", true);
    wizard.addStepListener(stepListener);
    wizard.startWizard();
    wizard.setVisible(true);
  }

  public void cancel()
  {
    wasCancelled = true;
    dispose();
  }

  public boolean wasCancelled()
  {
    return wasCancelled;
  }
}  
    





