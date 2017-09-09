package com.gensym.beaneditor;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Vector;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.CommandGroupInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.uiutil.LayoutTools;

class LayoutCommands extends AbstractStructuredCommand
{
  private static final String ALIGN = "LayoutAlign";
  private static final String ALIGN_LEFTS = "LayoutAlignLefts";
  private static final String ALIGN_CENTERS = "LayoutAlignCenters";
  private static final String ALIGN_RIGHTS = "LayoutAlignRights";
  private static final String ALIGN_TOPS = "LayoutAlignTops";
  private static final String ALIGN_MIDDLES = "LayoutAlignMiddles";
  private static final String ALIGN_BOTTOMS = "LayoutAlignBottoms";
  private static final String MAKE_SAME_SIZE = "LayoutMakeSameSize";
  private static final String MAKE_SAME_SIZE_WIDTH = "LayoutMakeSameSizeWidth";
  private static final String MAKE_SAME_SIZE_HEIGHT = "LayoutMakeSameSizeHeight";
  private static final String MAKE_SAME_SIZE_BOTH = "LayoutMakeSameSizeBoth";
  private static final String DISTRIBUTE = "LayoutDistribute";
  private static final String DISTRIBUTE_HORIZONTALLY = "LayoutDistributeHorizontally";
  private static final String DISTRIBUTE_VERTICALLY = "LayoutDistributeVertically";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final Resource errorResource = Resource.getBundle("com.gensym.beaneditor.Errors");

  private EditorFrame frame;

  LayoutCommands(EditorFrame editorFrame){
    super(new StructuredCommandInformation[]{
      new SubCommandInformation(ALIGN, true, shortResource, longResource, null, 
				null, null, 
				new StructuredCommandInformation[]{
	new CommandGroupInformation("HorizontalAlignment", new CommandInformation[]{
          new CommandInformation(ALIGN_LEFTS, true, shortResource, longResource, 
				 null, null, null, true),
	  new CommandInformation(ALIGN_CENTERS, true, shortResource, longResource, 
				 null, null, null, true),
	  new CommandInformation(ALIGN_RIGHTS, true, shortResource, longResource, 
				 null, null, null, true)}),
	new CommandGroupInformation("VerticalAlignment", new CommandInformation[]{
          new CommandInformation(ALIGN_TOPS, true, shortResource, longResource, 
				 null, null, null, true),
          new CommandInformation(ALIGN_MIDDLES, true, shortResource, longResource, 
				 null, null, null, true),
          new CommandInformation(ALIGN_BOTTOMS, true, shortResource, longResource, 
				 null, null, null, true)})}),
      new SubCommandInformation(MAKE_SAME_SIZE, true, shortResource, longResource, 
				null, null, null,
				new StructuredCommandInformation[]{
        new CommandInformation(MAKE_SAME_SIZE_WIDTH, true, shortResource, 
			       longResource, null, null, null, true),
        new CommandInformation(MAKE_SAME_SIZE_HEIGHT, true, shortResource, 
			       longResource, null, null, null, true),
        new CommandInformation(MAKE_SAME_SIZE_BOTH, true, shortResource, longResource,
			       null, null, null, true)}),
      new SubCommandInformation(DISTRIBUTE, true, shortResource, longResource, 
				null, null, null, new CommandInformation[]{
        new CommandInformation(DISTRIBUTE_HORIZONTALLY, true, shortResource, 
			       longResource, null, null, null, true),
        new CommandInformation(DISTRIBUTE_VERTICALLY, true, shortResource, 
			       longResource, null, null, null, true)})});

    frame = editorFrame;


    updateAvailability();
  }

  @Override
  public void actionPerformed(ActionEvent actionEvent)
  {
    String cmdKey = actionEvent.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(errorResource.format("CommandIsUnavailable", cmdKey));
    
    Component[] selection = frame.getBeanEditTool().getSelection();
    frame.getBeanEditTool().dirtyBit = true;
    if (cmdKey.equals(ALIGN_LEFTS)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_LEFTS);
    else if (cmdKey.equals(ALIGN_CENTERS)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_CENTERS); 
    else if (cmdKey.equals(ALIGN_RIGHTS)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_RIGHTS);
    else if (cmdKey.equals(ALIGN_TOPS)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_TOPS);
    else if (cmdKey.equals(ALIGN_MIDDLES)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_MIDDLES);
    else if (cmdKey.equals(ALIGN_BOTTOMS)) 
      LayoutTools.align(selection, LayoutTools.ALIGN_BOTTOMS);
    else if (cmdKey.equals(MAKE_SAME_SIZE_WIDTH))
      LayoutTools.size(selection, LayoutTools.MAKE_SAME_SIZE_WIDTH);
    else if (cmdKey.equals(MAKE_SAME_SIZE_HEIGHT)) 
      LayoutTools.size(selection, LayoutTools.MAKE_SAME_SIZE_HEIGHT);
    else if (cmdKey.equals(MAKE_SAME_SIZE_BOTH)) 
       LayoutTools.size(selection, LayoutTools.MAKE_SAME_SIZE_BOTH);
    else if (cmdKey.equals(DISTRIBUTE_HORIZONTALLY))
      LayoutTools.distribute(selection, LayoutTools.DISTRIBUTE_HORIZONTALLY);
    else if (cmdKey.equals(DISTRIBUTE_VERTICALLY))
      LayoutTools.distribute(selection, LayoutTools.DISTRIBUTE_VERTICALLY);

    //selection contains wrappers, need to update the actual beans in the wrappers
    for (int i=0; i<selection.length; i++)
      if (selection[i] instanceof Wrapper){
	Wrapper w = (Wrapper)selection[i];
	w.ensureBeanBounds();
	w.updateForScroll();
        w.reestablishPortPositions();
      }
    frame.getCanvas().repaintIt();
  }

  void updateAvailability(){
    BeanCanvas canvas = frame.getCanvas();
    if (canvas != null && frame.application.inDesignMode()){
      setAvailable(ALIGN, (frame.getBeanEditTool().selectionCount() >= 2));
      setAvailable(MAKE_SAME_SIZE, (frame.getBeanEditTool().selectionCount() >= 2)); 
      setAvailable(DISTRIBUTE, (frame.getBeanEditTool().selectionCount() >= 3));
    }
    else{
      setAvailable(ALIGN, false);
      setAvailable(MAKE_SAME_SIZE, false); 
      setAvailable(DISTRIBUTE, false);
    }    
  }
   
}



