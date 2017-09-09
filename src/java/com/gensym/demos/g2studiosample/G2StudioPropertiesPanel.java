package com.gensym.demos.g2studiosample;

import java.util.Locale;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Component;
import java.awt.Insets;
import java.util.Vector;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.DefaultListCellRenderer;
import javax.swing.JPanel;
import javax.swing.JList;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.JSplitPane;
import javax.swing.border.CompoundBorder;
import javax.swing.border.BevelBorder;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.SwingUtilities;
import com.gensym.controls.DialogCommand;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.uitools.utils.FontUtil;
import com.gensym.uitools.utils.VariableWidthBevelBorder;
import com.gensym.draw.BasicDrawElement;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.wksp.ItemView;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.WorkspaceElement;
import com.gensym.controls.ItemProxy;
import com.gensym.controls.SymbolVector;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.gcg.AttributePanelFactory;
import com.gensym.ntw.TwAccess;
import com.gensym.uitools.utils.HideButton;
import com.gensym.uitools.utils.ComponentVisibilityListener;
import com.gensym.uitools.utils.ComponentVisibilityEvent;
import com.gensym.uitools.utils.ComponentVisibilityEventSource;

public class G2StudioPropertiesPanel extends JPanel
implements ComponentVisibilityEventSource {
  private AttributePanelFactory panelFactory;
  private static UpdatePropertiesPanelRunnable updatePropertiesPanelRunnable;
  private ItemListener itemListener;
  private static final Resource i18ui = Resource.getBundle ("com/gensym/demos/g2studiosample/UiLabels");
  private static String LABEL = i18ui.getString("properties");
  private static JLabel waitLabel = new JLabel(i18ui.getString("waitForGeneratedDialog"));
  private static JTextField defaultPropertiesPage = new JTextField();  
  static {
    //defaultPropertiesPage.setEditable(false);
    defaultPropertiesPage.setText("");
    defaultPropertiesPage.setBorder(new CompoundBorder(defaultPropertiesPage.getBorder(),
						       new EmptyBorder(10,0,0,0)));
  }
  private JComboBox propertiesLabel;
  private boolean updateSelectionFromPropertiesComboBox = true;
  private DialogCommand propertiesPageDlgCmd = new DialogCommand();
  private Component currentPropertiesPage;
  private Vector visibilityListeners = new Vector();
  
  public G2StudioPropertiesPanel(AttributePanelFactory panelFactory) {
    itemListener = new ItemAdapter();
    this.panelFactory = panelFactory;
    setLayout(new BorderLayout());
    setPreferredSize(new Dimension(250,400));
    setBorder(new CompoundBorder
	      (new VariableWidthBevelBorder(BevelBorder.RAISED, Color.white, Color.gray),
	       new EmptyBorder(2,2,2,2)));
    JPanel headerPanel = new JPanel();
    JLabel header = new JLabel(LABEL);
    header.setFont(FontUtil.sanserifPlain11);
    headerPanel.setLayout(new BorderLayout());
    headerPanel.add(header, "Center");
    JButton hideButton = new HideButton();
    setName(LABEL);
    hideButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	G2StudioPropertiesPanel.this.setVisible(false);
      }
    });
    headerPanel.add(hideButton, BorderLayout.EAST);
    headerPanel.setBorder(new CompoundBorder(new EtchedBorder(),
					     new EmptyBorder(new Insets(0,5,0,0))));

    propertiesLabel = new JComboBox();
    propertiesLabel.setFont(FontUtil.sanserifPlain11);
    JPanel topPanel = new JPanel();
    topPanel.setLayout(new BorderLayout());
    topPanel.add(headerPanel, BorderLayout.NORTH);
    topPanel.add(propertiesLabel, BorderLayout.CENTER);    
    add(topPanel, BorderLayout.NORTH);
    propertiesLabel.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent ae) {
	if (!updateSelectionFromPropertiesComboBox) return;
	ItemView itemView = (ItemView)propertiesLabel.getSelectedItem();
	if (itemView != null) {
	  if (itemView instanceof WorkspaceView) 
	    ((WorkspaceView)itemView).clearSelection();
	  else if (itemView instanceof BasicDrawElement&&
		   itemView instanceof WorkspaceElement) {
	    //this is totally bogus to have to check both!
	    WorkspaceElement elt = (WorkspaceElement)itemView;
	    WorkspaceView wkspView = (WorkspaceView)((BasicDrawElement)elt).getParent();
	    wkspView.selectElements(new WorkspaceElement[] {elt});
	  }
	}
      }
    });
    propertiesLabel.setEditable(false);
    propertiesLabel.setRenderer(new ItemTableHeaderRenderer());
    setItemView(null);
  }
  
  public void setItemView(ItemView itemView) {      
    if (updatePropertiesPanelRunnable == null) 
      updatePropertiesPanelRunnable = new UpdatePropertiesPanelRunnable();
    updatePropertiesPanelRunnable.update(itemView);
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
    if (visible && updatePropertiesPanelRunnable != null)
      updatePropertiesPanelRunnable.update();        
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
	for (int i=0; i<listenerCount; i++)
	  ((ComponentVisibilityListener)listeners[i]).visibilityChanged(visibilityEvent);
    }
  }
  
  class UpdatePropertiesPanelRunnable implements Runnable {
    ItemView view;
    private void update() {
      SwingUtilities.invokeLater(this);
    }
    public void update(ItemView view) {
      this.view = view;
      if (isVisible()) 
	update();
    }
    private void doUpdatePropertiesPanel(ItemView itemView) {
      updateSelectionFromPropertiesComboBox = false;
      if (view != null) {
	try {
	  Item item = view.getItem();
	  item.removeItemListener(itemListener,
				  com.gensym.ntw.util.AttributeHelper.getNeededAttributes(item));
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}	  
	propertiesLabel.removeItem(view);
	try {
	  Item item = view.getItem();
	  item.addItemListener(itemListener,
			       com.gensym.ntw.util.AttributeHelper.getNeededAttributes(item));
	} catch (G2AccessException g2ae) {
	    Trace.exception(g2ae);
	}
	propertiesLabel.addItem(view);
      } 	
      propertiesLabel.setSelectedItem(view);
      updateSelectionFromPropertiesComboBox = true;      
      if (currentPropertiesPage != null) {
	remove(currentPropertiesPage);
	propertiesPageDlgCmd.close();
      }
      add(waitLabel);
      
      currentPropertiesPage = null;
      if (itemView != null)
      currentPropertiesPage = createPropertiesPage(itemView, propertiesPageDlgCmd);
      if (currentPropertiesPage == null)
	currentPropertiesPage = defaultPropertiesPage;       
      
      remove(waitLabel);
      add(currentPropertiesPage);
      
      validate();
      repaint();
    }
    
    @Override
    public void run() {
      doUpdatePropertiesPanel(view);
      /*while (true) {       
	doUpdatePropertiesPanel(view);
	try {
	  synchronized(this) {
	    wait();
	  }
	} catch (InterruptedException ie) {
	  Trace.exception(ie);
	}
      }*/
    }
  }
  
  public void setCurrentPropertiesPage(Component page) {
    if (currentPropertiesPage != null) {
      remove(currentPropertiesPage);
      propertiesPageDlgCmd.close();
    }
    currentPropertiesPage = page;
    add(currentPropertiesPage);
    validate();
    repaint();    
  }

  class ItemAdapter implements ItemListener {
    @Override
    public void itemModified(ItemEvent ie) {
      propertiesLabel.repaint();
    }
    @Override
    public void itemDeleted(ItemEvent ie) {}
    @Override
    public void receivedInitialValues(ItemEvent ie) {}
  }
  
  private Component createPropertiesPage(ItemView itemView, DialogCommand dlgCmd) {
    Component page = null;
    ItemProxy propertiesPageProxy = new ItemProxy();
    Item item = itemView.getItem();
    propertiesPageProxy.setProxy(item);
    dlgCmd.setProxies(new ItemProxy[]{propertiesPageProxy});
    propertiesPageProxy.setAttributes(new SymbolVector());//clear out names attribute
    TwAccess currentConnection = (TwAccess)((ImplAccess)item).getContext();
    try {
      page = panelFactory.generatePanel(currentConnection,
					propertiesPageProxy,
					dlgCmd,
					Locale.getDefault());
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return page;
  }
  
  class ItemTableHeaderRenderer extends DefaultListCellRenderer {
    @Override
    public Component getListCellRendererComponent(JList list,
						  Object value,
						  int index,
						  boolean isSelected,
						  boolean cellHasFocus)
    {
      super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
      try {
	Item item = null;
	if (value != null)
	  item = ((ItemView)value).getItem();
	if (item != null) {
	  String label = com.gensym.ntw.util.AttributeHelper.getTableHeader(item);
	  //String label = item.getTableHeader();//NOTE: attr not cached
	  setText(label);
	}
      } catch(G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
      return this;
    }
  }
  
}
