package com.gensym.uilcontrols;

import com.gensym.util.Symbol;

public class UilClientConstants{

  public static final Symbol UIL_INITIALIZE_GROBJ_METHOD_ = Symbol.intern("UIL-INITIALIZE-GROBJ-METHOD");
  public static final Symbol UIL_DELETE_GROBJ_METHOD_ = Symbol.intern("UIL-DELETE-GROBJ-METHOD");
  public static final Symbol UIL_CLONE_GROBJ_METHOD_ = Symbol.intern("UIL-CLONE-GROBJ-METHOD");
  public static final Symbol UIL_MANAGE_GROBJ_METHOD_ = Symbol.intern("UIL-MANAGE-GROBJ-METHOD");
  public static final Symbol UIL_CONFIGURE_GROBJ_METHOD_ = Symbol.intern("UIL-CONFIGURE-GROBJ-METHOD");
  public static final Symbol UIL_ENABLE_GROBJ_METHOD_ = Symbol.intern("UIL-ENABLE-GROBJ-METHOD");
  public static final Symbol UIL_DISABLE_GROBJ_METHOD_ = Symbol.intern("UIL-DISABLE-GROBJ-METHOD");
  public static final Symbol UIL_UPDATE_GROBJ_METHOD_ = Symbol.intern("UIL-UPDATE-GROBJ-METHOD");
  public static final Symbol UIL_CONCLUDE_GROBJ_METHOD_ = Symbol.intern("UIL-CONCLUDE-GROBJ-METHOD");
  public static final Symbol UIL_VALIDATE_GROBJ_METHOD_ = Symbol.intern("UIL-VALIDATE-GROBJ-METHOD");
  public static final Symbol UIL_EDIT_BOX_SELECTION_METHOD_ = Symbol.intern("UIL-EDIT-BOX-SELECTION-METHOD");
  public static final Symbol UIL_EDIT_BOX_UNSELECTION_METHOD_ = Symbol.intern("UIL-EDIT-BOX-UNSELECTION-METHOD");
  public static final Symbol UIL_CONTROL_DIALOG_CALLBACK_ = Symbol.intern("UIL-CONTROL-DIALOG-CALLBACK");
  public static final Symbol UIL_DO_NOTHING_ = Symbol.intern("UIL-DO-NOTHING");
  public static final Symbol UIL_HANDLE_BUTTON_METHOD_ = Symbol.intern("UIL-HANDLE-BUTTON-METHOD"); 
  public static final Symbol UIL_MESSAGE_SELECTION_METHOD_ = Symbol.intern("UIL-MESSAGE-SELECTION-METHOD");
  public static final Symbol UIL_MESSAGE_UNSELECTION_METHOD_ = Symbol.intern("UIL-MESSAGE-UNSELECTION-METHOD");

  public static final Symbol UIL_FORMAT_SPECIFICATION_CLASS_ = 
                                         Symbol.intern("UIL-FORMAT-SPECIFICATION-CLASS");

  public static final Symbol DATE_ = Symbol.intern("DATE");
  public static final Symbol TIME_ = Symbol.intern("TIME");
  public static final Symbol PROCEDURE_CALL_ = Symbol.intern("PROCEDURE-CALL");
  public static final Symbol FUNCTION_CALL_ = Symbol.intern("FUNCTION-CALL");

  public static final Symbol INITIATING_OBJECT_ = Symbol.intern("INITIATING-OBJECT");
  public static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");

  public static final Symbol NONE_ = Symbol.intern("NONE");

  public static final String OK = "ok";

  public static final Symbol HOST_DIALOG_ = Symbol.intern("HOST-DIALOG");

  public static final Symbol ON_ = Symbol.intern("ON");
  public static final Symbol OFF_ = Symbol.intern("OFF");

  public static final Class[] VALIDATION_ARG_TYPES = 
           new Class[]{com.gensym.uilcontrols.UilClientItem.class,
			 com.gensym.classes.UiClientItem.class,
			 com.gensym.uilcontrols.UilClientDialog.class,
			 java.lang.Object.class,
			 java.lang.Object.class};
  public static final String[] VALIDATION_ARGS = new String[]{"grobj", "win", "dlg", "buttonOrInitObj",
								"actionQueue"};
  public static final Class[] CONCLUDE_ARG_TYPES = 
           new Class[]{com.gensym.uilcontrols.UilClientItem.class,
			 com.gensym.classes.UiClientItem.class,
			 com.gensym.uilcontrols.UilClientDialog.class,
			 java.lang.Object.class,
			 java.lang.Object.class};
  public static final String[] CONCLUDE_ARGS = new String[]{"grobj", "win", "dlg", "buttonOrInitObj",
							      "actionQueue"};
  public static final Class[] UPDATE_ARG_TYPES = 
           new Class[]{com.gensym.uilcontrols.UilClientItem.class,
			 com.gensym.classes.UiClientItem.class,
			 com.gensym.uilcontrols.UilClientDialog.class,
			 java.lang.Object.class,
			 java.lang.Object.class};
  public static final String[] UPDATE_ARGS = new String[]{"grobj", "win", "dlg", "buttonOrInitObj",
							    "actionQueue"};
  
  public static final Class[] ENABLE_ARG_TYPES =
          new Class[]{com.gensym.uilcontrols.UilClientItem.class};
  public static final String[] ENABLE_ARGS = new String[]{"grobj"};
  
  public static final Class[] DISABLE_ARG_TYPES =
          new Class[]{com.gensym.uilcontrols.UilClientItem.class};
  public static final String[] DISABLE_ARGS = new String[]{"grobj"};

  public static final Class[] CALLBACK_ARG_TYPES =
             new Class[]{com.gensym.uilcontrols.UilClientButton.class,
		com.gensym.classes.UiClientItem.class,
		com.gensym.uilcontrols.UilClientDialog.class};
  public static final String[] CALLBACK_ARGS = new String[]{"button", "win", "dlg"};

  public static final Class[] SELECTION_ARG_TYPES = new Class[]{com.gensym.uilcontrols.UilClientMessageObject.class, com.gensym.uilcontrols.UilClientScrollArea.class, com.gensym.classes.UiClientItem.class};
  public static final String[] SELECTION_ARGS = new String[]{"msgObject", "scrollArea", "win"};

  public static final Class[] EDIT_BOX_SELECTION_ARG_TYPES = 
           new Class[]{com.gensym.uilcontrols.UilClientEditBox.class,
			 com.gensym.uilcontrols.UilClientDialog.class,
			 com.gensym.classes.UiClientItem.class};
  public static final String[] EDIT_BOX_SELECTION_ARGS = new String[]{"editBox", "dlg", "win"};
  public static final Class[] EDIT_BOX_UNSELECTION_ARG_TYPES = 
           new Class[]{com.gensym.uilcontrols.UilClientEditBox.class,
			 com.gensym.uilcontrols.UilClientDialog.class,
			 com.gensym.classes.UiClientItem.class,
			 Boolean.class};
  public static final String[] EDIT_BOX_UNSELECTION_ARGS = new String[]{"editBox", "dlg", "win", "confirmed"};

  public static final Class[] ACTION_ARG_TYPES = new Class[]{com.gensym.uilcontrols.UilClientDialog.class,
							       java.lang.Object.class, 
							       com.gensym.classes.UiClientItem.class,
							       java.lang.Object.class, 
							       java.lang.Object.class};
  public static final String[] ACTION_ARGS = new String[]{"dlg", "dlgLauncher", "win", 
							     "origDlgLauncher", "actionQueue"};  
}


