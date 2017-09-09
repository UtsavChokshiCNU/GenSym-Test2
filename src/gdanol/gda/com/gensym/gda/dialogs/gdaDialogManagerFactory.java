
package com.gensym.gda.dialogs;

import com.gensym.dlgruntime.*;
import com.gensym.ntw.TwAccess;

/**
Implementation of DialogManagerFactory interface. Creates gdaDialogManager.
@see com.gensym.ntw.TwGateway#setDialogManagerFactory
*/
public class gdaDialogManagerFactory implements DialogManagerFactory {

    public gdaDialogManagerFactory(){}

	/**
	Implementation of DialogManagerFactory interface.
	*/
    public DialogManager makeDialogManager(TwAccess twaccess) {
        return new gdaDialogManager(twaccess);
    }
}