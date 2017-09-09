package com.gensym.gda.queues;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Dimension;
import java.awt.Color;
import java.awt.BorderLayout;
import java.util.Vector;
import java.util.Enumeration;
import java.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.modules.gqm.*;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import com.gensym.ui.menu.CPopupMenu;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.classes.modules.gqm.GqmEntry;
import com.gensym.cdggui.ui.UiSelectionEvent;
import com.gensym.cdggui.ui.UiSelectionEventGenerator;
import com.gensym.cdggui.ui.UiSelectionEventListener;         
import com.gensym.cdggui.VerticalFlowLayout;

public class MessageBrowser extends JPanel  implements  UiSelectionEventGenerator  
{
    JScrollPane scrollpane;
    CPopupMenu popupMenu;
    Vector filters = new Vector ();
    private MessageBrowserAdapter adapter;
    private JTabbedPane componentBox;
    private TwAccess cxn;
    private MessageBrowserTable table;
    private Hashtable selectionData = new Hashtable();
    private Vector listeners = new Vector();
    private Vector selectionEventListeners = new Vector();
    // private ToolbarBrowserCommand actionCommands;
    
    private java.awt.GridBagLayout gridBag;
    private static GridBagConstraints gbc = new GridBagConstraints();
    static 
    {
        gbc.gridwidth = gbc.REMAINDER;
        gbc.weightx = 1.0;
        gbc.fill = gbc.BOTH;
    }
    
    public MessageBrowser (TwAccess con, MessageBrowserColumnModel columnModel) 
    {
        cxn = con;
        setPreferredSize (new Dimension (500, 300));
        setLayout (new BorderLayout ());
        
        table = new MessageBrowserTable (con, columnModel);
        table.addMouseListener (new MousePressedListener ());
        table.addKeyListener (new KeyPressedListener ());
        
        scrollpane = new JScrollPane (table);
        scrollpane.setHorizontalScrollBarPolicy (ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        scrollpane.setPreferredSize (new Dimension (500, 300));
        
        MessageBrowserTableModel tableModel = table.getTableModel ();
        adapter = new MessageBrowserAdapter (tableModel);
        this.add (scrollpane, BorderLayout.CENTER);
    }

    public void addServer (GqmQueue queue)
    throws G2AccessException
    {
        MessageBrowserTableModel model = table.getTableModel ();
        model.removeMsgsForServerFromNonView (queue);

        //*** Set server state in hashtable ***
        model.setServerState (queue, new Boolean (true));

        QueueInfo.addQueueListener (queue, adapter);
        TableSorter sorter = table.getTableSorter ();
        sorter.sortByColumn (sorter.getLastSortedColumn(), sorter.isSortOrderAscending ());
    }

    public  JScrollPane getScrollpane()
    {
         return  scrollpane;
    }
    
    public void addUiSelectionEventListener (UiSelectionEventListener sel)
    {
        synchronized (selectionEventListeners) 
        {
            if (! selectionEventListeners.contains (sel))    //containsKey (gpl))
                selectionEventListeners.addElement (sel);
            selectionEventListeners.trimToSize ();
        }
    }

    public void removeUiSelectionEventListener (UiSelectionEventListener sel)
    {
        if (sel != null) 
        {
            synchronized (selectionEventListeners) 
            {
                if (selectionEventListeners.contains (sel))
                    selectionEventListeners.removeElement (sel);
                selectionEventListeners.trimToSize();
            }
        }
    }

     public void fireUiSelectionEvent ()
    {
        if (selectionEventListeners != null && selectionData != null) 
        {
            synchronized (selectionEventListeners) 
            {
                UiSelectionEvent evt = new UiSelectionEvent (this, 1, selectionData);
                for (int i = 0; i < selectionEventListeners.size(); i++) 
                {
                    if (selectionEventListeners.elementAt (i) != null)
                        ((UiSelectionEventListener) selectionEventListeners.elementAt (i)).selectionGained (evt);
                }
            }
        }
    }

   // public void setActionCommands (ToolbarBrowserCommand actionCommands)
   // {
    //    this.actionCommands = actionCommands;
   // }

    public TwAccess getConnection ()
    {
        return cxn;
    }

    public void removeComponent (Component component)
    {
        componentBox.remove (component);
        componentBox.repaint ();
    }

    public MessageBrowserTable getTableView ()
    {
        return table;
    }

    public MessageBrowserFilter getFilter (int ind) 
    {
        MessageBrowserTableModel model = table.getTableModel ();
        MessageBrowserFilter filter = model.getFilter (ind);
        return filter;
    }

    public void addOrRemoveFilter (MessageBrowserFilter filter) throws G2AccessException
    {
        Sequence names = filter.getAttributeNames ();
        Sequence values = filter.getAttributeValues ();
        if (names != null && values != null)
            addOrRemoveFilter (filter.getIndex(), names, values,filter.getState (),
                    filter.isFilterOR (), filter.getGroupName (),filter.getObjectFilterSubclass ());
        MessageBrowserFilter thefilter = getFilter (filter.getIndex ());    //### Combine with next line?
        thefilter.setEditable (filter.isEditable ());
    }

    public void addOrRemoveFilter (int ind, Sequence attrNames, Sequence attrVals,
        boolean filterOn, boolean orFilter, Symbol grp, String subclass) throws G2AccessException
    {
        if (subclass == null)
            subclass = "";
        MessageBrowserFilter filter = getFilter (ind);
        MessageBrowserTableModel model = table.getTableModel ();
        if (filter == null) 
        {
            filter = new MessageBrowserFilter (ind, attrNames, attrVals, filterOn, orFilter, grp);
            if (! subclass.equals (""))
                filter.setObjectFilterSubclass(subclass);
            model.addFilter (filter);
        }
        else 
        {
            filter.setState (filterOn);
            if (! subclass.equals (""))
                filter.setObjectFilterSubclass (subclass);
        }

        model.applyFiltering ();
        TableSorter sorter = table.getTableSorter ();
        sorter.sortByColumn (sorter.getLastSortedColumn (), sorter.isSortOrderAscending ());
    }

    public void removeServer (GqmQueue queue) throws G2AccessException
    {
        MessageBrowserTableModel model =  table.getTableModel ();
        Vector msgs = model.getMsgsForServer (queue);
        if (msgs != null)
            model.moveDataFromView (msgs);
        model.removeMsgsForServerFromNonView (queue);

        //*** Set server state in hashtable ***
        model.setServerState (queue, new Boolean (false));

        QueueInfo.removeQueueListener (queue, adapter);
        model.setDefBackgroundColorOfServerButton (queue);
        TableSorter sorter = table.getTableSorter ();
        sorter.sortByColumn (sorter.getLastSortedColumn (), sorter.isSortOrderAscending ());
    }

    private static boolean isPopupTrigger (MouseEvent e) 
    {
        return (e.getModifiers () == MouseEvent.BUTTON3_MASK);
    }

    class KeyPressedListener extends KeyAdapter 
    {
        public void keyPressed (KeyEvent e) 
        {
            //if (e.VK_DELETE == e.getKeyCode() && actionCommands != null &&
            //        actionCommands.isAvailable (actionCommands.OPCSRUI_DELETE_MESSAGE_BUTTON)) 
            //{
            //    actionCommands.deleteCurrentSelection();
            //}
        }
    }

    private static RepresentationConstraints menuConstraints =
        new RepresentationConstraints (RepresentationConstraints.TEXT_AND_ICON,
                                    SwingConstants.LEFT,
                                    SwingConstants.CENTER,
                                    SwingConstants.RIGHT,
                                    SwingConstants.CENTER);
    private CPopupMenu createPopupMenu () 
    {
        CPopupMenu menu = new CPopupMenu ();
        //menu.add (actionCommands, menuConstraints);
        return menu;
    }

   public void doAction () 
   {
       Vector v = new Vector ();
       GqmEntry message= null ;

        int [] selectedRows = table.getSelectedRows ();
        for (int i = 0; i < selectedRows.length; i++) 
        {
                int selectedRow = selectedRows[i];
                MessageBrowserMessageImpl selectedMessage = (MessageBrowserMessageImpl) table.getRow (selectedRow);
                message = selectedMessage.getMessage ();
                v.add (message);
          }

          v.trimToSize ();

          if (v.capacity () ==1)
          {       
              System.out.println("SINGLESELECTION " +v.elementAt(0));
                          //selectionData.put(UiSelectionEvent.SELECTED_OBJECT,v);
                        selectionData.put(UiSelectionEvent.SELECTED_OBJECT,message);
                        selectionData.put("SENT-FROM-MESSAGE-BROWSER",new Boolean(true));
                        selectionData.put(UiSelectionEvent.SINGLE_SELECTION,new Boolean(true));
                        fireUiSelectionEvent();
           }             
          else if (v.capacity () > 1)
          {
              System.out.println ("The value of Selection is " +v.elementAt (0));
              selectionData.put ("SENT-FROM-MESSAGE-BROWSER", new Boolean (true));
              selectionData.put (UiSelectionEvent.SELECTED_OBJECT, v);
              selectionData.put (UiSelectionEvent.SINGLE_SELECTION, new Boolean (false));
              fireUiSelectionEvent ();
          }
          else
          {
          }
    }

    class MousePressedListener extends MouseAdapter 
    {
        public void mouseClicked (MouseEvent e) 
        {
            doAction ();
            if (e.getClickCount () > 1) 
            {
                //actionCommands.describeCurrentSelection ();
            }
        }

        public void mouseReleased (MouseEvent e) 
        {
            if (e.isPopupTrigger ()) 
            {
                JTable table = (JTable) e.getSource ();
                int x = e.getX () + 1;
                int y = e.getY () + 1;
                if (popupMenu == null)
                    popupMenu = createPopupMenu ();
                popupMenu.setInvoker (table);
                popupMenu.show (table, x, y);
            }
        }
    }

}


