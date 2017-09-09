package com.gensym.editor.icon.simulation;

import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JButton;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import com.gensym.editor.icon.simulation.SimulationExpression;
import com.gensym.editor.icon.simulation.Clock;
import com.gensym.editor.icon.simulation.TimeListener;
import javax.swing.ImageIcon;
import java.awt.Dimension;
import javax.swing.event.ChangeListener;
import javax.swing.event.ChangeEvent;
import java.util.Vector;

public class SimulationPlayControl extends JPanel
{
  private boolean autoReplay = false;
  private Clock clock = new Clock();
  private JButton playButton;
  private JSlider slider;
  private ClockButtonAdapter cba;
  private ExpressionEvaluationSpeedSliderAdapter eessa;
  private SliderClockAdapter sliderClockAdapter;
  private ImageIcon playIcon =
  new ImageIcon(getClass().getResource("play.gif"));
  private ImageIcon pauseIcon =
  new ImageIcon(getClass().getResource("pause.gif"));  

  public SimulationPlayControl() {
    playButton = new JButton(playIcon);
    playButton.setPreferredSize(new Dimension(20,20));
    slider = new JSlider(0, 100, 0);
    cba=new ClockButtonAdapter(Clock.START,clock);    
    eessa = new ExpressionEvaluationSpeedSliderAdapter(cba, playButton);
    slider.addChangeListener(eessa);
    sliderClockAdapter = new SliderClockAdapter(slider, cba, playButton);
    clock.addTimeListener(sliderClockAdapter);
    playButton.addActionListener(cba);
    add(playButton);
    add(slider);
  }

  public void addExpression(SimulationExpression expression) {
    eessa.addExpression(expression);
  }

  public boolean removeExpression(SimulationExpression expression) {
    return eessa.removeExpression(expression);
  }

  public void setAutoReplay(boolean autoReplay) {
    this.autoReplay = autoReplay;
  }

  public boolean getAutoReplay() {
    return autoReplay;
  }
  
  class ExpressionEvaluationSpeedSliderAdapter implements ChangeListener {
    private JButton playButton;
    private ClockButtonAdapter cba;
    private Vector expressions = new Vector();
    
    ExpressionEvaluationSpeedSliderAdapter(ClockButtonAdapter cba,
					   JButton playButton) {
      this.playButton = playButton;
      this.cba = cba;
    }

    public void addExpression(SimulationExpression expression) {
      expressions.addElement(expression);
    }

    public boolean removeExpression(SimulationExpression expression) {
      return expressions.removeElement(expression);
    }
    
    @Override
    public void stateChanged(ChangeEvent ce) {
      SimulationExpression[] ses = null; 
      synchronized(expressions) {
	ses=new SimulationExpression[expressions.size()];
	expressions.copyInto(ses);
      }
      JSlider slider = (JSlider)ce.getSource();            
      if (slider.getValueIsAdjusting()) {
	clock.pause();
	cba.actionType = Clock.RESUME;
	playButton.setIcon(playIcon);
      }
      int value = slider.getValue();
      clock.setTime(value);
      for (int i=0;i<ses.length;i++) 
	ses[i].setTime(value);
    }
  }

  class ClockButtonAdapter implements ActionListener {
    private Clock clock;
    int actionType;
    
    ClockButtonAdapter(int actionType,
		       Clock clock) {
      this.clock = clock;
    }

    @Override
    public void actionPerformed(ActionEvent ce) {
      JButton button = (JButton)ce.getSource();
      switch (actionType) {
      case Clock.RESUME:
	clock.performAction(actionType);      	
	actionType = Clock.PAUSE;
	button.setIcon(pauseIcon); break;
      case Clock.START:
	clock.reset();
	clock.performAction(actionType);      	
	actionType = Clock.PAUSE;
	button.setIcon(pauseIcon); break;
      case Clock.PAUSE:
	clock.performAction(actionType);      	
	actionType = Clock.RESUME;
	button.setIcon(playIcon); break;
      case Clock.RESET:
	clock.performAction(actionType);      	
	actionType = Clock.START;
	button.setIcon(playIcon); break;
      }
    }
  }

  class SliderClockAdapter implements TimeListener {
    private JSlider slider;
    private JButton clockButton;
    private ClockButtonAdapter cba;
    SliderClockAdapter(JSlider slider,
		       ClockButtonAdapter cba,
		       JButton clockButton) {
      this.slider = slider;
      this.clockButton = clockButton;
      this.cba = cba;
    }
    @Override
    public void setTime(int time) {
      if (time > slider.getMaximum()) {
	if (autoReplay) {
	  clock.reset();
	  clock.start();
	} else {
	  clock.pause();	
	  cba.actionType = Clock.START;
	  clockButton.setIcon(playIcon);
	}
      } else
	slider.setValue(time);
    }
  }
  
  
}

  
