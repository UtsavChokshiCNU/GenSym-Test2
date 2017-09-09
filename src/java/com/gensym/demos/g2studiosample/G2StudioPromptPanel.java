package com.gensym.demos.g2studiosample;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.Insets;
import java.awt.Color;
import java.util.Vector;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JButton;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.border.BevelBorder;
import com.gensym.message.Resource;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.uitools.utils.HideButton;
import com.gensym.uitools.utils.ComponentVisibilityListener;
import com.gensym.uitools.utils.ComponentVisibilityEvent;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;
import com.gensym.editor.text.EditContext;

public class G2StudioPromptPanel extends JPanel 
implements ComponentVisibilityEventSource {
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");
  private static String LABEL = i18ui.getString("parsing");
  private static String parsingStatusDefault = i18ui.getString("noParsingStatus");  
  private PromptArea promptArea;
  private ShellParsingStatusManager parsingStatusManager;
  private Vector visibilityListeners = new Vector();
  
  public G2StudioPromptPanel() {
    promptArea = new PromptArea();
    EditContext.getContext().addPromptsUpdatedListener(promptArea);
    EditContext.getContext().setPrompter(promptArea);
    JLabel parsingStatusLabelLabel = new JLabel(LABEL+":  ");    
    JLabel parsingStatusLabel = new JLabel(parsingStatusDefault);
    JLabel parsingErrorLabel = new JLabel();
    parsingErrorLabel.setFont(FontUtil.sanserifPlain11);
    parsingStatusLabel.setFont(FontUtil.sanserifPlain11);
    parsingStatusLabelLabel.setFont(FontUtil.sanserifPlain11);

    parsingStatusManager = new ShellParsingStatusManager(parsingStatusLabel, parsingErrorLabel);
    parsingStatusManager.setParsingStatusDefaultValue(parsingStatusDefault);
    EditContext.getContext().addParsingStatusUpdatedListener(parsingStatusManager);
    EditContext.getContext().addPromptsUpdatedListener(parsingStatusManager);    
    JScrollPane promptScrollPane = new JScrollPane(promptArea);
    setLayout(new BorderLayout());
    JPanel parsingStatusHeader = new JPanel();
    JButton hideButton = new HideButton();
    setName(LABEL);
    hideButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent ae) {
	  setVisible(false);
	  }
	});
    parsingStatusHeader.setBorder(new CompoundBorder(new EtchedBorder(),
						     new EmptyBorder(new Insets(0,5,0,0))));

    parsingStatusHeader.setLayout(new BorderLayout());
    parsingStatusHeader.add(parsingStatusLabelLabel, BorderLayout.WEST);
    parsingStatusHeader.add(hideButton, BorderLayout.EAST);
    parsingStatusHeader.add(parsingStatusLabel);
    add(parsingStatusHeader, BorderLayout.NORTH);
    add(promptScrollPane);
    add(parsingErrorLabel, BorderLayout.SOUTH);
    setBorder(new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray));
  }

  @Override
  public void addComponentVisibilityListener(ComponentVisibilityListener listener) {
    visibilityListeners.addElement(listener);
  }
  @Override
  public void removeComponentVisibilityListener(ComponentVisibilityListener listener) {
    visibilityListeners.removeElement(listener);
  }

  @Override
  public void setVisible(boolean visible) {
    super.setVisible(visible);
    fireComponentVisibilityEvent();
    if (visible) {
      if (getParent() instanceof JSplitPane) 
	((JSplitPane)getParent()).resetToPreferredSizes();
    }
  }
  private void fireComponentVisibilityEvent() {
    int listenerCount;
    Object[] listeners = null;
    synchronized (visibilityListeners) {
      listenerCount = visibilityListeners.size();
      if (listenerCount != 0) {
	listeners = new Object[listenerCount];
	visibilityListeners.copyInto(listeners);
      }
    }
    if (listenerCount != 0) {
      ComponentVisibilityEvent visibilityEvent = new ComponentVisibilityEvent(this);
      if (listeners != null)
	for (int i=0; i<listeners.length; i++)
	  ((ComponentVisibilityListener)listeners[i]).visibilityChanged(visibilityEvent);
    }
  }
}
