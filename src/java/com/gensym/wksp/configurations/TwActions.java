package com.gensym.wksp.configurations;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2CallbacksException;
import com.gensym.wksp.*;
import com.gensym.shell.*;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Message;
import com.gensym.classes.FreeformTable;
import com.gensym.classes.ClassDefinition;
import com.gensym.classes.UserMenuChoice;
import com.gensym.editor.icon.shell.IconEditor;
import com.gensym.editor.icon.g2.G2IconFormat;
import com.gensym.editor.icon.g2.G2IconEditor;
import com.gensym.editor.icon.g2.G2IconDescriptionFinder;
import com.gensym.editor.icon.g2.G2IconDescriptionSaver;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.g2.G2ExpressionEvaluator;
import com.gensym.editor.icon.g2.G2StaticIconDescriptionFinder;  

public class TwActions
implements java.io.Serializable
{
  private static final Symbol KB_WORKSPACE_ = Symbol.intern ("KB-WORKSPACE");
  private static final Symbol NONE_ = Symbol.intern ("NONE");
  private static final Symbol SHOW_ = Symbol.intern ("SHOW");
  private static final Symbol HIDE_ = Symbol.intern ("HIDE");
  private static final Symbol ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");
  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern ("GO-TO-ITEM");
  private static G2IconEditor iconEditor;
  private static MyWindowAdapter windowListener;
  
  protected TwAccess twAccess;
  protected TwCallbacks twCallbacks;
  protected Frame frame;
  protected Locale local;
  
  public TwActions()
  {
  }

  public void setLocal(Locale local)
  {
    this.local = local;
  }
  
  public void setFrame(Frame frame)
  {
   this.frame = frame;
  }

  public void setTwAccess(TwAccess twAccess)
  {
    this.twAccess = twAccess;
  }

  public void setTwCallbacks(TwCallbacks twCallbacks)
  {
    this.twCallbacks = twCallbacks;
  }


  // SIMPLE LOCAL ACTIONS
  public void print(Component component)
  {
    PrintJob pj
      = component.getToolkit().getPrintJob(frame,
					   "Printing",
					   null);
    if (pj != null) {
      Graphics g = pj.getGraphics();
      if (g != null) {
	component.paint(g);
	g.dispose();
      }
      pj.end();
    }
  }
  
  public void hideWorkspace(KbWorkspace wksp)
       throws G2AccessException
  {
    wksp.hide();
  }
  
  //SIMPLE G2 ACTIONS
  public void liftToTop(Item item)
       throws G2AccessException
  {
    item.liftToTop();
  }

  public void dropToBottom(Item item)
       throws G2AccessException
  {
    item.dropToBottom();
  }

  public void delete(Item item)
       throws G2AccessException
  {
    if (com.gensym.wksp.SystemMenuChoiceCommands.okayToDelete (item.getG2ClassName()))
      item.delete (true, false); 
  }

  public void enable(Item item)
       throws G2AccessException
  {
    item.enable (); 
  }

  public void disable(Item item)
       throws G2AccessException
  {
    item.disable(); 
  }    

  public void insertRow(FreeformTable table, int index)
       throws G2AccessException
  {
    Sequence tableCells = table.getTableCells();
    Sequence aRow = (Sequence)tableCells.elementAt(0);
    int length = aRow.size();
    Sequence newRow = new Sequence(length);
    for (int i=0;i<length;i++) {
      newRow.addElement(NONE_);
    }
    tableCells.insertElementAt(newRow, index);
    table.setTableCells(tableCells);
  }

  public void insertColumn(FreeformTable table, int index)
       throws G2AccessException
  {
    Sequence tableCells = table.getTableCells();
    Enumeration e = tableCells.elements();
    while(e.hasMoreElements()) {
      Sequence currentRow = (Sequence)e.nextElement();
      currentRow.insertElementAt(NONE_, index);
    }
    table.setTableCells(tableCells);
  }

  public void deleteRow(FreeformTable table, int index)
       throws G2AccessException
  {
    Sequence tableCells = table.getTableCells();
    tableCells.removeElementAt(index);
    table.setTableCells(tableCells);
  }

  public void deleteColumn(FreeformTable table, int index)
       throws G2AccessException
  {
    Sequence tableCells = table.getTableCells();
    Enumeration e = tableCells.elements();
    while(e.hasMoreElements()) {
      Sequence currentRow = (Sequence)e.nextElement();
      currentRow.removeElementAt(index);
    }
    table.setTableCells(tableCells);
  }

  public void createInstance(ClassDefinition definition,
			     KbWorkspace targetWorkspace)
       throws G2AccessException
  {
    createInstance(definition, targetWorkspace, twAccess);
  }

  static int TRANSFER_CONSTANT = 5;
  public static void createInstance(ClassDefinition definition,
				    KbWorkspace targetWorkspace,
				    TwAccess twAccess) 
       throws G2AccessException
  {
    Symbol className = definition.getClassName();
    Item inst = twAccess.createItem(className);
    if (inst instanceof KbWorkspace) 
      ((KbWorkspace)inst).show(new Structure());
    else {
      int x = definition.getItemXPosition();
      int y = definition.getItemYPosition();
      inst.transferTo(targetWorkspace, x+TRANSFER_CONSTANT, y-TRANSFER_CONSTANT);
    }
    inst.makePermanent ();
  }

  public void hideName(Entity entity)
       throws G2AccessException
  {
    //this actually doesn't work in G2!
    Item nameBox = (Item)entity.getNameBoxItem();
    if (nameBox != null)
      nameBox.delete(true, false);
    else
      System.out.println("NAME BOX WAS NULL");
  }

  public void shrinkWrap(KbWorkspace workspace)
       throws G2AccessException
  {
    workspace.shrinkWrap();
  }

  public void startG2()
       throws G2AccessException
  {
    twAccess.setG2State(TwGateway.RUNNING_);
  }

  public void resumeG2()
       throws G2AccessException
  {
    startG2();
  }

  public void resetG2()
       throws G2AccessException
  {
    twAccess.setG2State(TwGateway.RESET_);
  }

  public void restartG2()
       throws G2AccessException
  {
    resetG2();
    startG2();
  }
      
  public void pauseG2()
       throws G2AccessException
  {
    twAccess.setG2State(TwGateway.PAUSED_);
  }

  public void createSubworkspace(Entity entity)
       throws G2AccessException
  {
    createSubworkspace(entity, twAccess);
  }
  
  public static void createSubworkspace(Entity entity, TwAccess twAccess)
       throws G2AccessException
  {
    KbWorkspace subWksp = (KbWorkspace)twAccess.createItem(KB_WORKSPACE_);
    entity.setSubworkspace(subWksp);
    subWksp.show(new Structure());
    if (((Item)entity).getPermanent ())
      subWksp.makePermanent ();
  }

  public void goToReferencedItem(Message message)
       throws G2AccessException
  {
    goToMessageOrigin(message);
  }
  
  public void goToMessageOrigin(Message message)
       throws G2AccessException
  {
    Sequence referencedItems = message.getReferencedItems();
    if (referencedItems != null){
      Item itm = (Item)referencedItems.elementAt(0);//make dialog later
      Sequence containers = itm.getContainmentHierarchy();
      if (containers != null) {
	KbWorkspace wksp = (KbWorkspace)containers.elementAt(0);//analyze later
	Structure particulars = new Structure();
	particulars.setAttributeValue(ITEM_, itm);
	particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
	wksp.show(particulars);
      }
    }
  }

  public static void goToSubworkspace(Entity entity)
       throws G2AccessException
  {
    KbWorkspace subWksp = entity.getSubworkspace();
    if (subWksp != null)
      subWksp.show(new Structure());
  }

  public void describe(Item item)
  {
  }

  public void describeConfiguration(Item item)
  {
  }

  public void viewChangeLog(Item item)
  {
  }

  public void cloneAsTrendChart(Item item)
  {
    //obsolete
  }

  public static void cloneWorkspace(KbWorkspace workspace)
       throws G2AccessException
  {
    KbWorkspace clone = (KbWorkspace)workspace.g2Clone();
    clone.show(new Structure());
  }

  public void deleteWorkspace(Item item)
  {
    //delete(item.getWorkspace);
  }

  //public void start

  public void invokeUserMenuChoice(Symbol label, Item item)
       throws G2AccessException
  {
    UserMenuChoice umc =
      (UserMenuChoice)twAccess.getUserMenuChoice(label, item.getG2ClassName());
    if (umc != null)
      umc.invoke(item);
      //UserMenuChoiceCommands.executeMenuChoice (umc, item);
    else {
      //Trace.exception(new Exception("No UserMenuChoice for " + label));
    }
  }


  
  //Editor/Menu --->Actions
  public void editProperties(Component component, Item item, Symbol mode)
  {
    try {
      twAccess.getDialogManager().editItem(component, item, mode, local);
    } catch (java.net.MalformedURLException murle) {
      Trace.exception(murle);
    } catch (com.gensym.jgi.G2AccessException g2ae) {
      Trace.exception(g2ae);
    } catch (com.gensym.dlgruntime.ResourceInstantiationException rie) {
      Trace.exception(rie);
    }
  }

  public void editColor(Item item)
       throws G2AccessException
  {
    System.out.println("editColor " + item); 
  }
 
  public static void editTextProperty(Item item, Symbol attributeName)
  {
    new com.gensym.editor.text.Session (item, attributeName, null); 
  }

  public static void editIcon(ClassDefinition definition) {
    if (windowListener == null)
      windowListener = new MyWindowAdapter();
    if (iconEditor == null) {
      iconEditor = new G2IconEditor();
      iconEditor.addWindowListener(windowListener);
      iconEditor.setDefaultIconFormat(new G2IconFormat(definition));
      iconEditor.setIconFinder(new G2IconDescriptionFinder());
      iconEditor.setIconSaver(new G2IconDescriptionSaver());
      Parameter[] vars = new Parameter[2];
      vars[0] = new Parameter("WIDTH", Integer.class,new Integer(50));
      vars[1] = new Parameter("HEIGHT", Integer.class,new Integer(50));
      iconEditor.setDefaultEvaluator(new G2ExpressionEvaluator(vars));
      iconEditor.setVisible(true);  
    } else {
      iconEditor.setState(iconEditor.NORMAL);
      iconEditor.toFront();
    }
    iconEditor.openSession(new G2StaticIconDescriptionFinder(definition));    
  }

  private static class MyWindowAdapter extends WindowAdapter {
    @Override
    public void windowClosing(WindowEvent e) {
      iconEditor.removeWindowListener(this);
      iconEditor = null;
    }
    @Override
    public void windowClosed(WindowEvent e) {
      iconEditor.removeWindowListener(this);
      iconEditor = null;      
    }
  }
  
  public void editFreeformTable(FreeformTable table,
				Symbol attributeName)
  {
    //EDIT_CELL_EXPRESSION_
    //EDIT_CELL_FORMAT_
    //TABLE_CELLS_
  }

  public void tableOfValues(Item item)
  {
    //???
  }

  public void editOrientation(Entity entity)
  {
    //sub-menu????
  }

  public void changeMinSize(Item item)
  {
    //obsolete
  }

  public void changeSize(Item item)
  {
    //obsolete
  }

  public void newWorkspace()
       throws G2AccessException
  {
    KbWorkspace wksp = (KbWorkspace)twAccess.createItem(KB_WORKSPACE_);
    wksp.show(new Structure());
  }
  
  public void newObject()
  {
  }

  public void newRule()
  {
  }

  public void newDisplay()
  {
  }

  public void newDefinition()
  {
  }

  public void newFreeText()
  {
  }

  public void newButton()
  {
  }
  
  public void mainMenu()
  {
    //obsolete
  }
  public void operateOnArea()
  {
    //obsolete
  }

  public void miscellany()
  {
    //obsolete
  }
  
  public void changeMode()
  {
  }

  public void loadKb()
  {
  }

  public void saveKb()
  {
  }

  public void clearKb()
  {
  }

  public void createNewModule()
  {
  }

  public void deleteModule()
  {
  }

  //neatly-stack-windows
  //close-telewindows-connection

}
