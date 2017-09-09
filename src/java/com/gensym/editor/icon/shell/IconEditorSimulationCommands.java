package com.gensym.editor.icon.shell;

import java.awt.event.*;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.mdi.MDIListener;
import com.gensym.mdi.MDIFrame;
import com.gensym.mdi.MDIEvent;
import com.gensym.mdi.MDIDocument;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.Savable;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.editor.icon.core.Finder;
import com.gensym.editor.icon.core.Evaluator;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.ValueListener;
import com.gensym.editor.icon.core.ValueChangedEvent;
import javax.swing.JPanel;
import javax.swing.JDialog;
import javax.swing.JScrollPane;
import java.awt.Component;
import java.awt.BorderLayout;
import java.awt.GridLayout;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import java.awt.Frame;
import javax.swing.JLabel;
import com.gensym.editor.icon.shapes.IconElement;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.util.Vector;
import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;
import com.gensym.editor.icon.simulation.SimulationExpression;
import com.gensym.editor.icon.simulation.SimulationPlayControl;
import com.gensym.editor.icon.dlgs.CanvasPropertiesDialog;
import java.util.Hashtable;
import com.gensym.editor.icon.simulation.SimulationExpression;
import com.gensym.editor.icon.simulation.SinusoidalSimulationExpression;
import com.gensym.editor.icon.simulation.TimeSimulationExpression;
import com.gensym.editor.icon.simulation.TanSimulationExpression;
import com.gensym.editor.icon.simulation.SecSimulationExpression;
import com.gensym.editor.icon.simulation.SqrSimulationExpression;
import com.gensym.editor.icon.simulation.SqrtSimulationExpression;

public class IconEditorSimulationCommands extends AbstractCommand
implements MDIListener, PropertyChangeListener
{
  private IconEditor iconEditor;
  private IconEditorSessionDocument currentDoc;  
  private static final String shortResource = "IconEditorShortResource";
  private static final String longResource = "IconEditorShortResource";
  public static final String SIMULATE = "Simulate";
  public static final String PREFERENCES = "Preferences";
  public static Hashtable expressionKeyMap = new Hashtable();
  public static final String SCALAR = "scalar";
  public static final String TIME = "t";
  private static Vector expressions = new Vector();
  static {
    expressionKeyMap.put(SCALAR, SCALAR);
    addExpression(new TimeSimulationExpression());
    addExpression(new TanSimulationExpression(1,25,25));
    addExpression(new SqrtSimulationExpression(1,25,25));
    addExpression(new SqrSimulationExpression(1,25,25));    
    addExpression(new SecSimulationExpression(5,25,25));    
    addExpression(new SinusoidalSimulationExpression(15,25,25));
  }
  private static String imageDir = "images/";
  
  public IconEditorSimulationCommands(IconEditor iconEditor)
  {
    super(new CommandInformation[]{
      new CommandInformation(SIMULATE, true, shortResource, longResource, 
			     imageDir+"switch.gif",
			     null, null, true),
	new CommandInformation(PREFERENCES, true, shortResource, longResource, 
			       imageDir+"preferences.gif",
			       null, null, false)});
    if (iconEditor != null){
      iconEditor.getManager().addMDIListener(this);
      MDIDocument[] docs = iconEditor.getManager().getDocuments();
      for (int i=0; i<docs.length; i++){
	if (docs[i] instanceof IconEditorSessionDocument)
	  docs[i].addPropertyChangeListener(this);
      }
    }    
    this.iconEditor = iconEditor;
  }

  public static void addExpression(SimulationExpression expression) 
  {
    expressions.addElement(expression);
    String[] variableKeys = expression.getVariableKeys();
    for(int i=0;i<variableKeys.length;i++)      
      expressionKeyMap.put(variableKeys[i], expression);
  }
  
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (SIMULATE.equals(cmdKey)) {
      if (currentDoc != null) {
	simulateCanvas(currentDoc.getCanvas());
      }
    } else if (PREFERENCES.equals(cmdKey)) {
      if (currentDoc != null) {
	editCanvasSimulationPreferences(currentDoc);
      }
    }
  }   
  class CanvasParameterAdapter implements ValueListener {
    private IconEditorCanvas canvas;
    CanvasParameterAdapter(IconEditorCanvas canvas) {
      this.canvas = canvas;
    }
    @Override
    public void valueChanged(ValueChangedEvent vce) {
      Layer[] layers = canvas.getLayers();
      for (int i=0;i<layers.length;i++) {
	Layer layer = layers[i];
	IconElement[] ies = layer.getElementsSnapshot();
	for (int j=0;j<ies.length;j++) {
	  IconElement ie = ies[j];
	  ie.evaluateExpressions();
	}
      }
      canvas.repaint();
    }
    
  }
  
  public void editCanvasSimulationPreferences(IconEditorSessionDocument doc) {
    IconEditorCanvas canvas = doc.getCanvas();
    CanvasPropertiesDialog cpd = new CanvasPropertiesDialog(iconEditor, canvas);
    cpd.setSelectedTab(CanvasPropertiesDialog.SIMULATION_PARAMETERS_TAB);
    cpd.setTitle(doc.getTitle() + " properties");
    cpd.setVisible(true);
  }

  private SimulationPlayControl playControl;
  private Component createCustomEditComponent(SimulationExpression expression)
  {
    if (playControl == null)
      playControl = new SimulationPlayControl();
    playControl.setAutoReplay(true);
    playControl.addExpression(expression);    
    return playControl;
  }
  
  private static Insets firstLabelInsets = new Insets (10, 0, 5, 0);
  private static Insets labelInsets = new Insets (5, 0, 5, 0);
  private static Insets firstTextInsets = new Insets (10, 10, 5, 0);
  private static Insets textInsets = new Insets (5, 10, 5, 0);
  
  public void simulateCanvas(IconEditorCanvas canvas) {
    IconEditorCanvas origCanvas = canvas;
    canvas = canvas.copy();
    Evaluator evaluator = canvas.getEvaluator();
    if (evaluator != null) {
      
      Parameter[] params = evaluator.getParameters();
      JPanel controlsPanel = new JPanel();
      CanvasParameterAdapter cpa = new CanvasParameterAdapter(canvas);
      
      GridBagLayout gbl = new GridBagLayout ();
      GridBagConstraints gbc = new GridBagConstraints ();
      gbc.insets = new Insets (5, 0, 5, 0);
      gbc.anchor = GridBagConstraints.CENTER;
      gbc.weighty = 0.5;
      controlsPanel.setLayout (gbl);

      Vector components = new Vector();
      Vector labels = new Vector();
      Vector currentExpressions = new Vector();
      for (int i=0; i<params.length; i++) {
	Parameter param = params[i];
	String simulationPreferenceKey = param.getSimulationPreferenceKey();
	Component component = null;
	JLabel label = null;
	Object expression = expressionKeyMap.get(simulationPreferenceKey);
	if (expression instanceof SimulationExpression) {
	  if (!currentExpressions.contains(expression)) {
	    currentExpressions.addElement(expression);
	    ((SimulationExpression)expression).setTime(0);
	    component = createCustomEditComponent((SimulationExpression)expression);
	    label = new JLabel("Time",JLabel.RIGHT);
	  }
	} else {
	  label = new JLabel(param.getName(),JLabel.RIGHT);
	  component = evaluator.createEditComponent(param);
	}

	if (component != null && !(components.contains(component))) {
	  param.addValueListener(cpa);
	  components.addElement(component);
	  labels.addElement(label);
	}
      }
      
      for (int i=0; i<components.size(); i++) {
	Component component = (Component)components.elementAt(i);
	JLabel label = (JLabel)labels.elementAt(i);
	if (i == 0)
	  gbc.insets = firstLabelInsets;
	else
	  gbc.insets = labelInsets;
	if (i == 0)
	  gbc.insets = firstTextInsets;
	else
	  gbc.insets = textInsets;
	
	// add Label
	gbc.gridwidth = 50;
	gbc.weightx = 0.0;
	gbc.fill = GridBagConstraints.NONE;
	gbc.anchor = GridBagConstraints.EAST;
	gbl.setConstraints (label, gbc);
	controlsPanel.add (label);

	// add TextField
	gbc.weightx = 1.0;
	gbc.gridwidth = 200;
	gbc.gridwidth = GridBagConstraints.REMAINDER;
	gbc.fill = GridBagConstraints.HORIZONTAL;
	gbc.anchor = GridBagConstraints.WEST;
	gbl.setConstraints (component, gbc);
	controlsPanel.add(component);
      }      
      
      JScrollPane scrollingCanvas = new JScrollPane(canvas);
      JPanel mainPanel = new JPanel();
      mainPanel.setLayout(new BorderLayout());
      mainPanel.add(controlsPanel, "West");
      mainPanel.add(scrollingCanvas, "Center");

      MyStandardDialog dlg = new MyStandardDialog(iconEditor, mainPanel);
      dlg.setVisible(true);
    }
  }
  
  @Override
  protected void setAvailable(String key, boolean available){
    super.setAvailable(key, available);
  }

  private void setCurrentDocument(IconEditorSessionDocument doc) {
    currentDoc = doc;
    updateAvailability();
  }

  @Override
  public void documentAdded(MDIEvent event) {
    MDIDocument document = (MDIDocument)event.getDocument();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      iconDoc.addPropertyChangeListener(this);
      setCurrentDocument(iconDoc);      
    }
  }

  private void updateAvailability() {
    setAvailable(SIMULATE, (currentDoc != null));
  }
    
  @Override
  public void propertyChange(PropertyChangeEvent e) {
    MDIDocument document = (MDIDocument)e.getSource();
    if (document instanceof IconEditorSessionDocument) {
      IconEditorSessionDocument iconDoc = (IconEditorSessionDocument)document;
      if (e.getPropertyName().equals(IconEditorSessionDocument.IS_SELECTED_PROPERTY)){
	Boolean selected = (Boolean)e.getNewValue();
	if (selected.booleanValue()) {
	  setCurrentDocument(iconDoc);	  
	} 
      }
    }
  }
  

}

class MyStandardDialog extends StandardDialog
implements CommandConstants
{
  public MyStandardDialog(Frame frame, Component panel) {
    super(frame, "Simulate", true,
	  new String[] {OK_LABEL},
	  new int[] {OK},
	  panel,
	  null);
  }
}
