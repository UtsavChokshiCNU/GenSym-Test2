
package com.gensym.wksp;

import java.util.Locale;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.Transferable;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;
import com.gensym.message.Resource;

class WorkspaceClipboard extends Clipboard {

  /*
   * Standard Tracing Requirements
   */
  private static MessageKey traceKey =
    Trace.registerMessageKey ("com.gensym.wksp.clipboard", WorkspaceClipboard.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.wksp.TraceMessages", Locale.getDefault());
  private static final int DEF_TRACE_LEVEL     = 5;

  WorkspaceClipboard (String name) {
    super (name);
  }

  @Override
  public Transferable getContents (Object requestor) {
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "clipbdgetContents", requestor, owner);
    if (!(requestor instanceof WorkspaceView))
      return null;
    WorkspaceView requestingView = (WorkspaceView) requestor;
    Transferable clipboardContents = super.getContents (requestor);
    if (clipboardContents != null &&
	!((WorkspaceClipboardData)clipboardContents).checkPasteCompatibility (requestingView))
      return null;
    return clipboardContents;
  }

}
