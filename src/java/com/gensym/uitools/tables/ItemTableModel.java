package com.gensym.uitools.tables;

import java.util.Vector;
import java.util.Hashtable;
import java.util.Enumeration;
import javax.swing.table.AbstractTableModel;
import com.gensym.util.Symbol;
import com.gensym.message.Trace;
import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.SystemTable;
import com.gensym.classes.G2Definition;
import com.gensym.classes.KbWorkspace;
import com.gensym.ntw.util.BrowserIcons;
import com.gensym.ntw.util.uitools.IconKBTools;
import javax.swing.Icon;
import javax.swing.JTable;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.uitools.utils.JTableIconFactory;
import java.awt.Toolkit;
import javax.swing.ImageIcon;
import java.awt.Graphics;
import java.awt.Image;
import com.gensym.ntw.util.WindowUtil;
import java.awt.Point;
import java.util.StringTokenizer;

/**
 * A swing JTable table model designed for used with G2 Items.
 */
public class ItemTableModel extends AbstractTableModel
implements ItemListener, JTableIconFactory
{
  private Hashtable cachedValues = new Hashtable(101);
  private boolean viewAsText = false;
  private Vector data, filteredData;
  private Vector columns;
  private Vector filters;
  private boolean displayColumnNames = true;
  private boolean automaticAttributeUpdates = false;
  private static final Symbol IMAGE_ICON_ = Symbol.intern ("IMAGE-ICON");
  private  static final Symbol NAME_ = Symbol.intern("NAME");
  private static boolean WITH_COLOR_OVERRIDES = true;
  private Structure viewAsTexts = new Structure();
  private static final String NONE = "none";
  private static final Symbol TABLE_HEADER_ = Symbol.intern ("TABLE-HEADER");
  
  /**
   * The value used when an attribute is not available.
   * Cell renderers can check a value against this value in 
   * order to render the cell differently(ie perhaps grey it out).
   */
  public static final String ATTRIBUTE_NOT_AVAILABLE = "";

  /**
   * Constructs an ItemTableModel with no initial data.
   */
  public ItemTableModel()
  {
    data = new Vector();
    filteredData = new Vector();
    filters = new Vector();
    columns = new Vector();
  }

  /**
   * Adds an <code>ItemFilter</code> to be used when the <code>filter</code>
   * is called
   * @param filter The <code>ItemFilter</code> to be added to this model's list
   * of current filters
   */ 
  public void addFilter(ItemFilter filter)
  {
    filters.addElement(filter);
  }

  /**
   * Removes the <code>ItemFilter</code> currently being used when the <code>filter</code>
   * is called.
   * @param filter The <code>ItemFilter</code> to be removed from this model's list
   * of current filters   
   */  
  public boolean removeFilter(ItemFilter filter)
  {
    return filters.removeElement(filter);
  }

  private Vector concat(Vector v1, Vector v2)
  {
    Vector v = (Vector)v1.clone();
    Enumeration e = v2.elements();
    while(e.hasMoreElements())
      v.addElement(e.nextElement());
    return v;
  }

  private boolean isFiltered(Item item)
  {
    boolean filtered = false;
    Enumeration e = filters.elements();
    while (!filtered && e.hasMoreElements()) {
      ItemFilter filter = (ItemFilter)e.nextElement();
      filtered = (filter.isFiltered(item));
    }
    return filtered;
  }

  /**
   * Filters the current data(ie list of items) using all
   * current filters.  This not a destructive action and is 
   * only used when displaying.  Will automatically call
   * fireTableDataChanged.        
   */
  public void filter()
  {
    Vector tmpData = concat(data, filteredData);
    data.removeAllElements();
    filteredData.removeAllElements();
    Enumeration e = tmpData.elements();
    while (e.hasMoreElements()) {
      Object elt = e.nextElement();
      if (elt instanceof Item && isFiltered((Item)elt))
	filteredData.addElement((Item)elt);
      else
	data.addElement(elt);
    }
    fireTableDataChanged();        
  }

  /**
   * Adds <code>attributeName</code> as a column in the table model.
   * For each item row, the value of this attribute will be accessed
   * and displayed in its respective row/column.  If the attribute 
   * does not exist on an item, the value given by ATTRIBUTE_NOT_AVAILABLE
   * will be used.
   * @param attributeName the attributeName to be added as a column from this table model.
   */
  public void addColumn(Symbol attributeName)
  {
    columns.addElement(attributeName);
    fireTableDataChanged();    
  }

  public void addColumn(Symbol attributeName,
			boolean viewAsText) {
    addColumn(attributeName);
    viewAsTexts.setAttributeValue(attributeName, viewAsText?Boolean.TRUE:Boolean.FALSE);
  }
  
  /**
   * @param attributeName the attributeName to be removed as a column from this table model.
   */
  public void removeColumn(Symbol attributeName)
  {
    if (columns.removeElement(attributeName))
      fireTableDataChanged();
    viewAsTexts.setAttributeValue(attributeName, null);
  }

  public boolean addLabel(String label){
    StringTokenizer st = new StringTokenizer(label, "\n");
    boolean isFirstToken = true;
    while (st.hasMoreTokens()) {
      String token = st.nextToken();
      if (isFirstToken)
	setCachedValue(token,IMAGE_ICON_,bulletIcon);
      else
	setCachedValue(token,IMAGE_ICON_,grayBulletIcon);	
      data.addElement(token);
      isFirstToken=false;
    }
    return true;
  }
  
  /**
   * @param item An item to be added as data to this model.
   */
  public boolean addRow(Item item)
  {
    try {
      if (automaticAttributeUpdates)
	item.addItemListener(this);
      if (isFiltered(item)) 
	filteredData.addElement(item);
      else {
	data.addElement(item);
	return true;
      }
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return false;
  }

  /**
   * @param item An item to be removed as data to this model.
   */  
  public boolean removeRow(Item item)
  {
    cachedValues.remove(item);
    try {
      item.removeItemListener(this);
      if (!filteredData.removeElement(item))
	return data.removeElement(item);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return false;
  }

  /**
   * Removes all the data items from this table model.
   */
  public void removeAll()
  {
    Enumeration e = data.elements();
    while(e.hasMoreElements()) {
      Object elt = e.nextElement();
      if (elt instanceof Item) {
	Item item = (Item)elt;
	try {
	  item.removeItemListener(this);
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	}
      }
    }
    data.removeAllElements();
    e = filteredData.elements();
    while(e.hasMoreElements()) {
      Item item = (Item)e.nextElement();
      try {
	item.removeItemListener(this);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      }
    }
    filteredData.removeAllElements();    
  }

  @Override
  public int getColumnCount()
  {
    return columns.size();
  }
  
  @Override
  public int getRowCount()
  {
    return data.size();
  }

  /**
   * @return The <code>Item</code> at the indicated row.
   */
  public Item getRow(int row)
  {
    Object elt = data.elementAt(row);
    if (elt instanceof Item)
      return (Item)elt;
    else
      return null;
  }

  /**
   * @ return true if the table should display the names for each
   * column in the table header.
   */
  public boolean getDisplayColumnNames()
  {
    return displayColumnNames;
  }

  /**
   * @param displayColumnNames true if the table should display the names for each
   * column in the table header, false otherwise
   */  
  public void setDisplayColumnNames(boolean displayColumnNames)
  {
    this.displayColumnNames = displayColumnNames;
  }

  /**
   * @return the name of the column at index <code>column</code>
   */
  @Override
  public String getColumnName(int column) {
    if (displayColumnNames) {
      String name = columns.elementAt(column).toString().toLowerCase();
      name = name.replace('-', ' ');
      if (name.length() > 1)
	name = new String(new char[] {name.charAt(0)}).toUpperCase() + name.substring(1);
      return name;
    } else
      return "";
  }

  /**
   * Notifies the table that the data/format has changed.
   */
  public void update() {
    fireTableDataChanged();
  }

  /**
   * @param automaticAttributeUpdates whether the model should subscribe
   * each item when it is added.
   */
  public void setAutomaticAttributeUpdates(boolean automaticAttributeUpdates)
  {
    if (this.automaticAttributeUpdates == automaticAttributeUpdates) return;
    if (!this.automaticAttributeUpdates) {
      //subscribe to them all now
    }
    this.automaticAttributeUpdates = automaticAttributeUpdates;
  }

  /**
   * @return true if the model will subscribe to each item when it is added,
   * false otherwise.
   */  
  public boolean isAutomaticAttributeUpdates()
  {
    return automaticAttributeUpdates;
  }

  /**
   * @param viewAsText true if the model should get each attribute as text
   * instead of by value.
   */
  public void setViewAsText(boolean viewAsText)
  {
    this.viewAsText = viewAsText;
    fireTableDataChanged();
  }

  /**
   * @return true if the model will get each attribute as text
   * instead of by value, false otherwise.
   */  
  public boolean isViewAsText()
  {
    return viewAsText;
  }

  public Object getCachedValue(Item item, Symbol attributeName) {
    return getCachedValue((Object)item, attributeName);
  }
  
  private Object getCachedValue(Object object, Symbol attributeName) {  
    Structure cachedValuesForItem = (Structure)cachedValues.get(object);
    if (cachedValuesForItem != null) 
      return cachedValuesForItem.getAttributeValue(attributeName, null);
    else
      return null;
  }

  public void setCachedValue(Item item, Symbol attributeName, Object value) {
    setCachedValue((Object)item, attributeName, value);
  }
  private void setCachedValue(Object object, Symbol attributeName, Object value)       
  {
    Structure cachedValuesForItem = (Structure)cachedValues.get(object);
    if (cachedValuesForItem == null) {
      cachedValuesForItem = new Structure();
      cachedValues.put(object, cachedValuesForItem);
    }
    cachedValuesForItem.setAttributeValue(attributeName, value);
  }
  
  /**
   * @return the value at the indicated table cell.
   */
  @Override
  public Object getValueAt(int row, int col) {
    Symbol attributeName = (Symbol)columns.elementAt(col);
    Item item = getRow(row);
    if (item == null) {
      if (col == 0)
	return data.elementAt(row);
      else
	return null;
    }
    Object value = getCachedValue(item, attributeName);

    if (value == null) {
      value = ATTRIBUTE_NOT_AVAILABLE;
      Boolean getAsText = (Boolean)viewAsTexts.getAttributeValue(attributeName,
								 viewAsText?Boolean.TRUE:
								 Boolean.FALSE);
      try {
	if (getAsText.booleanValue()) {
	  //THERE IS A BUG IN getAttributeText (5/14/99)
	  Sequence attrs = new Sequence();
	  attrs.addElement(attributeName);
	  value = ((com.gensym.classes.ImplAccess)item).getAttributeTexts(attrs);
	  value = ((Structure)value).getAttributeValue(attributeName,
						       ATTRIBUTE_NOT_AVAILABLE);
	} else {
	  value = item.getPropertyValue(attributeName);
	  if (value instanceof Symbol ||
		    TABLE_HEADER_.equals(attributeName)) {
	    value = value.toString().toLowerCase();
	  }
	}
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      }
      if (NONE.equals(value))
	value = "";
      setCachedValue(item, attributeName, value);
    }
    
    return value;
  }


  private static final Class thisClass = com.gensym.uitools.tables.ItemTableModel.class;
  private static final Icon lockIcon
  = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("lock.gif")));
  private static final Icon bulletIcon
  = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("bullet.gif")));
  private static final Icon grayBulletIcon
  = new ImageIcon(Toolkit.getDefaultToolkit().getImage(thisClass.getResource("graybullet.gif")));  
  private static Icon mergeIcons(Icon icon1, Point p1, Icon icon2, Point p2) {
    Image image = WindowUtil.createImage(Math.max(icon1.getIconWidth(),
						  icon2.getIconWidth()),
					 Math.max(icon1.getIconHeight(),
						  icon2.getIconHeight()));
    Graphics g = image.getGraphics();
    icon2.paintIcon(null,g,p2.x,p2.y);
    icon1.paintIcon(null,g,p1.x,p1.y);
    return new ImageIcon(image);
  }
    
  private static Icon makeIcon(Item item) {
    Icon icon;
    if (item instanceof KbWorkspace)
      icon=BrowserIcons.kbWorkspaceIcon;
    else if (item instanceof ModuleInformation)
      icon=BrowserIcons.moduleIcon;
    else if (item instanceof SystemTable)
      icon=BrowserIcons.systemTableIcon;
    else
      icon=IconKBTools.getIconForItem(item, WITH_COLOR_OVERRIDES, 16,16);
    boolean proprietary = true;
    try {
      proprietary=item.isProprietaryThroughContainment();
    } catch (G2AccessException g2ae) {
      proprietary=true;
    }
    if (proprietary)
      icon=mergeIcons(lockIcon,
		      new Point(icon.getIconWidth()-lockIcon.getIconWidth(),
				icon.getIconHeight()-lockIcon.getIconHeight()),
		      icon, new Point(0,0));
    return icon;
  }

  @Override
  public Icon getIcon(int row, JTable table) {
    Item item = getRow(row);
    if (item == null) //its a label 
      return (Icon)getCachedValue(data.elementAt(row), IMAGE_ICON_);
    Icon icon = (Icon)getCachedValue(item, IMAGE_ICON_);
    if (icon == null) {
      icon = makeIcon(item);
      setCachedValue(item, IMAGE_ICON_, icon);
    }
    return icon;
  }
  
  @Override
  public void receivedInitialValues (ItemEvent e)
  {
    fireTableDataChanged();
  }

  @Override
  public void itemModified (ItemEvent e)
  {
    Item item = e.getItem();
    Sequence denotationSequence = e.getDenotation();    
    Structure denotation = (Structure) denotationSequence.elementAt(0);
    Symbol attributeName
      = (denotation!=null?(Symbol)denotation.getAttributeValue(NAME_, null):null);    
    if (getCachedValue(item, attributeName) != null)
      setCachedValue(item, attributeName, e.getNewValue());
    fireTableDataChanged();
  }

  @Override
  public void itemDeleted (ItemEvent e)
  {
    removeRow(e.getItem());
    fireTableDataChanged();
  }
  
}
