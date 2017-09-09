package com.gensym.demos.docs.custompopups;

import com.gensym.wksp.SelectionCommandsFactory;
import com.gensym.wksp.SelectionCommand;
import com.gensym.wksp.WorkspaceView;
import com.gensym.wksp.UserMenuChoiceCommands;

//** Factory for generating a custom popup menu for selected items on workspaces*/

public class CustomSelectionCommandsFactory2 implements SelectionCommandsFactory
{

  public CustomSelectionCommandsFactory2()
  {}

  @Override
  public SelectionCommand[] createCommands (WorkspaceView view) {
    return new SelectionCommand[] {
	new EditCommandsImpl()
	};
  }

}
