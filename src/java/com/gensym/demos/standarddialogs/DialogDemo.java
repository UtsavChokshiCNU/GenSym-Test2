
package com.gensym.demos.standarddialogs;

import com.gensym.dlg.*;
import java.awt.*;
import java.net.*;
import java.io.IOException;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;
import com.sun.java.accessibility.*;

public class DialogDemo implements HyperlinkListener {

  public static void main (String[] args) throws Exception {
    new DialogDemo ();
  }

  private JEditorPane html;

  public DialogDemo () throws Exception {
    JFrame f = new JFrame ("Dialog Demo");
    

    JPanel commandsPanel = new JPanel ();
    f.getContentPane().add (commandsPanel, BorderLayout.WEST);
    commandsPanel.setLayout (new GridLayout (0, 1));
    commandsPanel.add (new JButton ("Show Message Dialog"));
    commandsPanel.add (new JButton ("Show Warning Dialog"));

    //html = new JEditorPane ("file:///bt/vkp-sol/sequoia/common/doc/packages.html");
    html = new JEditorPane ();
    html.setEditable(false);
    html.addHyperlinkListener(this);
    JScrollPane scroller0 = makeScrollPane (600, 500);
    JViewport vp = scroller0.getViewport();
    vp.add (html);
    vp.setBackingStoreEnabled (true);

    JTextArea infoPanel = new JTextArea ("Hello there");
    JScrollPane scroller1 = makeScrollPane (600, 300);
    vp = scroller1.getViewport ();
    vp.add (infoPanel);
    vp.setBackingStoreEnabled (true);
    
    JSplitPane splitPane = new JSplitPane (JSplitPane.VERTICAL_SPLIT,
					   scroller0,
					   scroller1);
    f.getContentPane().add (splitPane, BorderLayout.CENTER);
    f.pack ();
    f.setVisible (true);
  }


  private static JScrollPane makeScrollPane (int x, int y) {
    final int paneWidth = x, paneHeight = y;
    return new JScrollPane(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED) {
      @Override
      public Dimension getPreferredSize() {
	return new Dimension(paneWidth, paneHeight);
      }
      @Override
      public Dimension getMinimumSize () {
	return new Dimension (100, 100);
      }
      @Override
      public float getAlignmentX() {
	return LEFT_ALIGNMENT;
      }
    };
  }


    /**
     * Notification of a change relative to a 
     * hyperlink.
     */
    @Override
    public void hyperlinkUpdate(HyperlinkEvent e) {
	if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
	    linkActivated(e.getURL());
	}
    }

    /**
     * Follows the reference in an
     * link.  The given url is the requested reference.
     * By default this calls <a href="#setPage">setPage</a>,
     * and if an exception is thrown the original previous
     * document is restored and a beep sounded.  If an 
     * attempt was made to follow a link, but it represented
     * a malformed url, this method will be called with a
     * null argument.
     *
     * @param u the URL to follow
     */
    protected void linkActivated(URL u) {
	Cursor c = html.getCursor();
	Cursor waitCursor = Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR);
	html.setCursor(waitCursor);
	SwingUtilities.invokeLater(new PageLoader(u, c));
    }

    /**
     * temporary class that loads synchronously (although
     * later than the request so that a cursor change
     * can be done).
     */
    class PageLoader implements Runnable {
	
	PageLoader(URL u, Cursor c) {
	    url = u;
	    cursor = c;
	}

        @Override
        public void run() {
	    if (url == null) {
		// restore the original cursor
		html.setCursor(cursor);

		// PENDING(prinz) remove this hack when 
		// automatic validation is activated.
		Container parent = html.getParent();
		parent.repaint();
	    } else {
		Document doc = html.getDocument();
		try {
		    html.setPage(url);
		} catch (IOException ioe) {
		    html.setDocument(doc);
		    html.getToolkit().beep();
		} finally {
		    // schedule the cursor to revert after
		    // the paint has happended.
		    url = null;
		    SwingUtilities.invokeLater(this);
		}
	    }
	}

	URL url;
	Cursor cursor;
    }

}
