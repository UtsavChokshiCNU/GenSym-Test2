package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.Hashtable;
import java.util.Enumeration;
import javax.swing.JList;
import javax.swing.ListCellRenderer;
import javax.swing.DefaultListModel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JScrollBar;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import com.gensym.util.Sorter;
import com.gensym.beansruntime.BeanSheet;

public class ColorMapEditor extends JPanel implements PropertyEditor, ItemListener, ActionListener, ListSelectionListener{

  private static final Font stdFont = new Font ("SansSerif", Font.PLAIN, 12);

  private ColorMap map = new ColorMap();

  private JList list;
  private ColorMapCellRenderer cellRenderer;
  private DefaultListModel model;
  private JScrollBar vScrollBar;
  private Button addButton, editButton, deleteButton;
  private int cachedIndex;
  private PropertyChangeSupport support = new PropertyChangeSupport(this);

  public ColorMapEditor(){
    //setLayout (new BorderLayout ());
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints constraints = new GridBagConstraints();
    setLayout(gridbag);
    list = new JList();
    list.addListSelectionListener(this);
    model = new DefaultListModel();
    list.setModel(model);
    cellRenderer = new ColorMapCellRenderer();
    list.setCellRenderer(cellRenderer);
    JScrollPane scrollPane = new JScrollPane(list);
    vScrollBar = scrollPane.getVerticalScrollBar();
    //add("Center", scrollPane);
    constraints.ipady = 4;
    constraints.insets = new Insets(4, 4, 4, 4);
    constraints.weightx = 1.0;
    constraints.weighty = 1.0;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.fill = GridBagConstraints.BOTH;
    gridbag.setConstraints(scrollPane, constraints);
    add(scrollPane);
    list.setSize(list.getPreferredSize());
    
    Panel commandPanel = new Panel();
    commandPanel.setLayout(new FlowLayout());
    
    addButton = new Button("Add...");
    commandPanel.add(addButton);
    addButton.setSize(addButton.getPreferredSize());
    addButton.addActionListener(this);
    
    editButton = new Button("Edit...");
    commandPanel.add(editButton);
    editButton.setSize(editButton.getPreferredSize());
    editButton.addActionListener(this);
    
    deleteButton = new Button("Delete");
    commandPanel.add(deleteButton);
    deleteButton.setSize(deleteButton.getPreferredSize());
    deleteButton.addActionListener(this);
    
    //add("South",commandPanel); 
    constraints.weightx = 0;
    constraints.weighty = 0;
    gridbag.setConstraints(commandPanel, constraints);
    add(commandPanel);    
    updateButtonAvailability(); 
  }
  
  
  @Override
  public void actionPerformed(ActionEvent event){
    Object button = event.getSource();
    if (button.equals(addButton)){
      ColorMapRecord rec = new ColorMapRecord();
      model.addElement(rec);
      vScrollBar.setValue(vScrollBar.getMaximum());//scroll to bottom to see new entry - but it don't work
      list.setSelectedIndex(model.getSize() - 1);      
      editSelection(rec);
    }
    else if (button.equals(editButton)){
      int index = list.getSelectedIndex();
      ColorMapRecord rec = (ColorMapRecord)model.elementAt(index);
      editSelection(rec);
    }
    else{
      int index = list.getSelectedIndex();
      model.removeElementAt(index);
    }

    support.firePropertyChange("",null,null);
    updateButtonAvailability();
  }

  private void editSelection(ColorMapRecord rec){
    Frame frame = findParentFrame();
    if (frame != null) {
      Rectangle r = frame.getBounds();
      int woffset = r.width /3; 
      int hoffset = r.height /3; 
      new BeanSheet(rec ,frame, woffset, hoffset);   
    }
  }

  private void updateButtonAvailability(){
    if ((model.getSize() == 0) || (list.getSelectionModel().isSelectionEmpty())){
      deleteButton.setEnabled(false);
      editButton.setEnabled(false);
    }
   else{
      deleteButton.setEnabled(true);
      editButton.setEnabled(true);
    }
  }
      

  private Frame findParentFrame() {
    Component component;
    
    component = getParent();
    while ((component != null) && (! (component instanceof Frame))) {
      component = component.getParent();
    }
    return (Frame) component;
  }
  
  @Override
  public void itemStateChanged(ItemEvent event){
  }

  //PropertyEditor methods
  @Override
  public void setValue(Object value){
    Hashtable table = (Hashtable) value;
    model.removeAllElements();
    int length = table.size();
    Enumeration elements = table.keys();
    String events[] = new String[length];
    int c = 0;
    while (elements.hasMoreElements()){
      events[c] = (String)elements.nextElement();
      c++;
    }
    Sorter.sort(events, Sorter.ASCENDING);
    for (int i=0; i<length; i++)
      model.addElement(new ColorMapRecord(events[i], (Color)table.get(events[i])));
  } 

  @Override
  public Object getValue(){
    int length = model.getSize();
    map.clear();
    for(int i = 0; i < length; i++) {
      ColorMapRecord rec = (ColorMapRecord)model.elementAt(i);
      map.put(rec.getEventName(), rec.getColor());
    }
    return map;
  } 

  @Override
  public String getAsText(){
    return null;
  } 

  @Override
  public void setAsText(String text) throws IllegalArgumentException{
    throw new IllegalArgumentException("setAsText not supported");
  } 

  @Override
  public String[] getTags(){
    return null;
  } 

  @Override
  public boolean isPaintable(){
    return true;
  } 

  @Override
  public void paintValue(Graphics g , Rectangle bounds) {
    //g.drawString("---event color mapping---", 10, 10);
    //connection
    g.setColor(Color.yellow);
    g.fillRect(bounds.x + bounds.width/4, bounds.y + (bounds.height/3), bounds.width - bounds.width/4 - (bounds.x + bounds.width/4), (bounds.y + 2*bounds.height/3) - (bounds.y + bounds.height/3));
    g.setColor(Color.black);
    //box outline
    g.drawRect(bounds.x, bounds.y, bounds.width - 1, bounds.height - 1);
    //connection outline
    g.drawLine(bounds.x + bounds.width/4, bounds.y + bounds.height/3, bounds.width - bounds.width/4, bounds.y + bounds.height/3);
    g.drawLine(bounds.x + bounds.width/4, bounds.y + 2*bounds.height/3, bounds.width - bounds.width/4, bounds.y + 2*bounds.height/3);
    //ports
    g.setColor(Color.gray);
    int inset = 3;
    int portSize = bounds.height - 2*inset;
    g.fillRect(bounds.width/4 - portSize + 1, bounds.y + inset, portSize, portSize);
    g.fillRect(3*bounds.width/4, bounds.y + inset, portSize, portSize);
    //ports outline
    g.setColor(Color.black);
    g.drawRect(bounds.width/4 - portSize + 1, bounds.y + inset - 1, portSize, portSize);
    g.drawRect(3*bounds.width/4, bounds.y + inset, portSize, portSize);
  }

  @Override
  public String getJavaInitializationString(){
    return ColorMap.class+".getDefaultTable()";
  }

  @Override
  public void addPropertyChangeListener(PropertyChangeListener listener){
    support.addPropertyChangeListener(listener);
  } 
  @Override
  public void removePropertyChangeListener(PropertyChangeListener listener){
    support.removePropertyChangeListener(listener);
  } 

  @Override
  public boolean supportsCustomEditor(){
    return true;
  } 

  @Override
  public Component getCustomEditor(){
    return this;
  } 
  
  //ListSelectionListener
  @Override
  public void valueChanged(ListSelectionEvent event){
    updateButtonAvailability();
  }

  class ColorMapCellRenderer extends Component implements ListCellRenderer{
        
    private Color color;
    private String event;
    private boolean isSelected;
    private boolean cellHasFocus;

    @Override
    public Component getListCellRendererComponent(JList list, Object value, int index,
						  boolean isSelected, 
						  boolean cellHasFocus){

      ColorMapRecord rec = (ColorMapRecord)model.elementAt(index);
      this.color = rec.getColor();
      this.event = rec.getEventName();
      this.isSelected = isSelected;
      this.cellHasFocus = cellHasFocus;
      return this;
    }
    
    @Override
    public Dimension getPreferredSize(){
      return new Dimension(60, 20);
    }
    
    @Override
    public void paint(Graphics g){
      Dimension size = getSize();
      
      if (isSelected){
	g.setColor(Color.blue);
	g.fillRect(0, 0, size.width, size.height);
      }
      
      if (isSelected)
	g.setColor(Color.white);
      else
	g.setColor(Color.black);
      
      g.setFont(stdFont);
      int textHeight = g.getFontMetrics().getHeight();
      g.drawString(event, 24, size.height - ((size.height - textHeight)/2));
      
      
      g.setColor(color);
      int insetX = 2;
      int insetY = (size.height - 10)/2;
      g.fillRect(insetX, insetY, 10, 10);
      
      if (isSelected)
	g.setColor(Color.white);
      else
	g.setColor(Color.black);
      
      g.drawRect(insetX, insetY, 10, 10);
      
    }
  }

}
  
