package com.gensym.demos.g2studiosample;     

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.border.CompoundBorder;
import javax.swing.border.LineBorder;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnection;
import com.gensym.uitools.utils.ComponentVisibilityListener;
import com.gensym.uitools.utils.ComponentVisibilityEvent;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;
import com.gensym.ui.ObjectCreator;
import com.gensym.util.Sequence;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.HideButton;
import com.gensym.wksp.PalettePane;

public final class PalettePanel extends JPanel implements ComponentVisibilityEventSource {

  private TwAccess cxn;
  private PalettePane palettePane;
  private Vector visibilityListeners = new Vector();
  
  static final Resource i18n = Resource.getBundle ("com/gensym/wksp/UiLabels");
  private static final int TEXT_AND_ICON = 2,
    ICON_ONLY = 0,
    TEXT_ONLY = 1;
  
  public PalettePanel() {
    super();

    setBorder(new LineBorder(Color.lightGray, 3));
    setLayout(new BorderLayout());

    JPanel headerPanel = new JPanel();
    JLabel panelLabel = new JLabel("New Item Palette");
    panelLabel.setFont(FontUtil.sanserifPlain11);
    headerPanel.setLayout(new BorderLayout());
    JButton hideButton = new HideButton();
    setName("New Item Palette");
    hideButton.addActionListener(new ActionListener() {
	@Override
	public void actionPerformed(ActionEvent ae) {
	  setVisible(false);
	  }
	});
    headerPanel.add(panelLabel);
    headerPanel.add(hideButton, "East");
    headerPanel.setBorder(new CompoundBorder(new EtchedBorder(),
					     new EmptyBorder(new Insets(3,10,3,3))));    
    add(headerPanel, "North");
  }
  
  void setPalettePane(PalettePane palettePane) {
    if (this.palettePane != null)
      remove(this.palettePane);
    this.palettePane = palettePane;
    if (palettePane != null) {
      JTabbedPane tabPane = palettePane.getTabbedPane();
      tabPane.setTabPlacement(SwingConstants.BOTTOM);
      tabPane.setFont(FontUtil.sanserifPlain11);
      add(palettePane, "Center");
    }
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

  @Override
  public void addComponentVisibilityListener(ComponentVisibilityListener listener) {
    visibilityListeners.addElement(listener);
  }

  @Override
  public void removeComponentVisibilityListener(ComponentVisibilityListener listener) {
    visibilityListeners.removeElement(listener);
  }

  private void fireComponentVisibilityEvent() {
    int listenerCount;
    Object[] listeners = null;
    synchronized (visibilityListeners) {
      listenerCount = visibilityListeners.size();
      if (listenerCount != 0){
	listeners = new Object[listenerCount];
	visibilityListeners.copyInto(listeners);
      }
    }
    if (listenerCount != 0) {
      ComponentVisibilityEvent visibilityEvent = new ComponentVisibilityEvent(this);
      if (listeners != null)
	for (int i=0; i<listenerCount; i++) 
	  ((ComponentVisibilityListener)listeners[i]).visibilityChanged(visibilityEvent);
    }
  }
}




