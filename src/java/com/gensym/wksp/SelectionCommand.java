
package com.gensym.wksp;

import com.gensym.ui.StructuredCommand;
import com.gensym.classes.Item;

/**
 * An interface that defines a Command that will be used
 * to create a PopupMenu for a selection on a WorkspaceView.
 * It can be used as any other Command. In addition, it
 * has a method to set the WorkspaceView for which it
 * generates command keys.
 * @see com.gensym.ui.Command
 */
public interface SelectionCommand extends StructuredCommand {

  public void setWorkspaceView (WorkspaceView view);

}
