/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PageCommands.java
 *
 */
package com.gensym.beaneditor;

import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.util.Vector;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.CommandConstants;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.menu.awt.CMenu;

//Commands to add:
//  - Duplictate Page
//  - Page from File...
//  - Next Page
//  - Previous Page
//  - First Page
//  - Last Page
class PageCommands extends AbstractCommand implements ItemListener, 
StandardDialogClient{

  static final String NEW_PAGE = "InsertNewPage";
  static final String DELETE_PAGE = "EditDeletePage";
  static final String PAGE_PROPERTIES = "EditPageProperties";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;
  private CMenu pageMenu;
  private PageNode firstPage = null;
  private PageNode currentPage = null;
  private PageNode lastPage = null;
  private boolean newPage;
  private int pageCounter;

  PageCommands(EditorFrame frame, CMenu pageMenu){
    super(new CommandInformation[]{
      new CommandInformation(NEW_PAGE, true, shortResource, longResource, 
			     null, null, null, false),
      new CommandInformation(DELETE_PAGE, true, shortResource, longResource, 
			     null, null, null, true),
      new CommandInformation(PAGE_PROPERTIES, true, shortResource, longResource, 
			     null, null, null, false)});

    newPage = false;
    pageCounter = 1;
    this.frame = frame;
    this.pageMenu = pageMenu;
    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    }
    
    //System.out.println("PagesCommand handling command key:"+cmdKey);
    if (cmdKey.equals(NEW_PAGE)) doNewPage();
    else if (cmdKey.equals(DELETE_PAGE)) doDeletePage();
    else if (cmdKey.equals(PAGE_PROPERTIES)) doPageProperties();
  }

  private PageNode createPage(BeanCanvas beanCanvas, String name){
    PageNode pageNode = new PageNode(name, beanCanvas);
    new PageMenuItem(pageNode, this);
    return pageNode;
  }

  void extendPages(BeanCanvas newCanvas, String name){
    pageCounter++;
    PageNode pageNode = createPage(newCanvas, name);
    setCurrentPage(pageNode);
    if (firstPage == null)
      firstPage = currentPage;
    else{
      lastPage.next = currentPage;
      currentPage.previous = lastPage;
    }
    lastPage = currentPage;
    updatePageMenu();
    updateAvailability();
  }

  private void insertPage(BeanCanvas beanCanvas, String string)
  {
    if (firstPage == null){
      extendPages(beanCanvas, string);
      return;
    }

    pageCounter++;
    PageNode pageNode = createPage(beanCanvas, string);
    if (!currentPage.equals(firstPage)){
      pageNode.previous = currentPage.previous;
      currentPage.previous.next = pageNode;
    }
    else
      firstPage = pageNode;
    pageNode.next = currentPage;
    currentPage.previous = pageNode;
    setCurrentPage(pageNode);
    updatePageMenu();
    updateAvailability();
  }

 private void doNewPage(){
   newPage = true;
   new InputDialog(frame, "Create Page", true, new String[]{"Name:"}, new String[]{"Page "+(1 + pageCounter)}, null, this).setVisible (true);
 }

  private void executeDeletePageCommand()
  {
    frame.getBeanEditTool().dirtyBit = true;
    PageNode pageNode = currentPage;
    if (currentPage.next == null)
      {
	lastPage = currentPage.previous;
	currentPage.previous.next = null;
	setCurrentPage(currentPage.previous);
      }
    else if (currentPage.previous == null)
      {
	firstPage = currentPage.next;
	currentPage.next.previous = null;
	setCurrentPage(currentPage.next);
      }
    else
      {
	currentPage.next.previous = currentPage.previous;
	currentPage.previous.next = currentPage.next;
	setCurrentPage(currentPage.next);
      }
    pageNode.reset();
    updatePageMenu();
    updateAvailability();
    frame.validate();
  }

  @Override
  public void dialogDismissed(StandardDialog d, int code)
  {
    if (d instanceof QuestionDialog){//Delete
      if (code == CommandConstants.YES)
	executeDeletePageCommand();
    }
    else{//Insert Page or Page Properties
      InputDialog multiEditDialog = (InputDialog)d;
      if (multiEditDialog.wasCancelled())
	{
	  if (newPage)
	    newPage = false;
	  return;
	}
      frame.getBeanEditTool().dirtyBit = true;
      String results[] = multiEditDialog.getResults();
      if (newPage)
	{
	  BeanCanvas beanCanvas = createBeanCanvas();
	  if ((results[0] != null) && (!results[0].equals("")))
	    insertPage(beanCanvas, results[0]);
	  else
	    insertPage(beanCanvas, "Page "+(1 + pageCount()));
	  newPage = false;
	}
      else{
	currentPage.name = results[0];
	currentPage.pageMenuItem.setLabel(currentPage.name);
	frame.getStatusBar().setPageName(currentPage.name);
      }
    }
  }

    private void doDeletePage(){
      QuestionDialog QuestionDialog = null;
      if (currentPage.canvas.containsNonTrivialComponents()){
	QuestionDialog = new QuestionDialog(frame, "Confirm Delete", true, "Are you sure you wish to delete \'"+currentPage.name+"\'?", this);
	QuestionDialog.setVisible(true);
	return;
      }
      else executeDeletePageCommand();
    }

  private void doPageProperties(){
    new InputDialog(frame, "Page Properties", true, new String[]{"Name:"}, new String[]{currentPage.name}, null, this);
  }
  
  int pageCount(){
    int c = 0;
    PageNode node = firstPage;
    while (node != null){
      c++;
      node = node.next;
    }
    return c;
  }

  private BeanCanvas createBeanCanvas(){
    BeanCanvas beanCanvas = new BeanCanvas();
    beanCanvas.setBackgroundColor(java.awt.Color.white);
    Preferences preferences = Preferences.currentPreferences;
    beanCanvas.setContainerSize(preferences.getDefaultContainerWidth(), preferences.getDefaultContainerHeight());
    return beanCanvas;
  }

  void makeFirstPages(){
    firstPage = createPage(frame.getCanvas(), "Page 1");
    lastPage = firstPage;
    extendPages(createBeanCanvas(), "Page 2");
    extendPages(createBeanCanvas(), "Page 3");
    setCurrentPage(firstPage);
    updatePageMenu();
    updateAvailability();
  }

  PageNode getFirstPage(){
    return firstPage;
  }

  void setFirstPage(PageNode page){
    firstPage = page;
  }

  PageNode getCurrentPage(){
    return currentPage;
  }

  void setCurrentPage(PageNode page){
    if (currentPage != null)
      currentPage.pageMenuItem.setState(false);
    currentPage = page;
    currentPage.pageMenuItem.setState(true);
    frame.getBeanEditTool().clearSelection();
    frame.setCanvas(page.canvas);
    frame.getStatusBar().setPageName(page.name);
  }

  void updatePageMenu(){
    pageMenu.removeAll();
    for (PageNode pageNode = firstPage; pageNode != null; pageNode = pageNode.next)
      pageMenu.add(pageNode.pageMenuItem);
  }

  void reset(){
    pageMenu.removeAll();
    firstPage = null;
    currentPage = null;
    lastPage = null;
    pageCounter = 1;
    frame.getStatusBar().setPageName("");
  }

  @Override
  public void itemStateChanged(ItemEvent event){
    PageMenuItem pageMenuItem = (PageMenuItem)event.getSource();
    PageNode node = pageMenuItem.node;
    if (pageMenuItem.getState()){
      if (node.equals(currentPage)) return;
      else setCurrentPage(node);
    }
    else{
      if (node.equals(currentPage)) currentPage.pageMenuItem.setState(true);
      //else do nothing
    }
  }  

  void updateAvailability(){
    if (frame.getDialogType() == frame.SIMPLE_DIALOG){
      setAvailable(NEW_PAGE, false);
      setAvailable(DELETE_PAGE, false);
      setAvailable(PAGE_PROPERTIES, false);
    }
    else{
      setAvailable(NEW_PAGE, true);
      if ((firstPage != null) && (firstPage.equals(lastPage)))
	setAvailable(DELETE_PAGE, false);
      else 
	setAvailable(DELETE_PAGE, true);
      setAvailable(PAGE_PROPERTIES, true);
    }
  }

}

  

