
package com.gensym.wksp;

import com.gensym.ui.Command;

/**
 * An interface that defines the factory that
 * will be used to determine the initial list
 * of Commands used by SelectionCommandGenerator
 * to create PopupMenus for WorkspaceView
 * selections
 * @see com.gensym.wksp.SelectionCommandGenerator
 */
public interface SelectionCommandsFactory {

  public SelectionCommand[] createCommands (WorkspaceView view);

}
