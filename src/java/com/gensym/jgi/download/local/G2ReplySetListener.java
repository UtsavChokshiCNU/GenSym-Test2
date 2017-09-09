package com.gensym.jgi.download.local;

import com.gensym.fida.message.*;
import com.gensym.classes.modules.g2runtime.G2rtReplySet;
import com.gensym.classes.modules.g2runtime.G2rtFutureReply;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.download.G2StubResolver;
import com.gensym.message.Trace;

/**
 *
 */
public class G2ReplySetListener implements ReplySetListener, ItemListener
{
  
  private G2rtReplySet g2ReplySet;
  private ReplySet replySet;
 
  public G2ReplySetListener(ReplySet replySet,
			    G2rtReplySet g2ReplySet)
  {
    this.replySet = replySet;
    this.g2ReplySet = g2ReplySet;
  }

  // Implemenet ReplySetListener

  public void receivedAvailableFutureReply(ReplySetEvent event) { 
    try {
      FutureReply reply = event.getFutureReply();
      G2rtFutureReply g2FutureReply = (G2rtFutureReply)G2StubResolver.createStubForG2Interface(G2rtFutureReply.class);
      G2FutureReplyListener.updateG2FutureReply(g2FutureReply, reply);
      g2ReplySet._receivedAvailableFutureReply(g2FutureReply);
    } catch (Exception e) {
      Trace.exception(e);
      e.printStackTrace();
    }
  }

  public void receivedUnavailableFutureReply(ReplySetEvent event) {
    try {
      FutureReply reply = event.getFutureReply();
      G2rtFutureReply g2FutureReply = (G2rtFutureReply)G2StubResolver.createStubForG2Interface(G2rtFutureReply.class);
      G2FutureReplyListener.updateG2FutureReply(g2FutureReply, reply);
      g2ReplySet._receivedUnavailableFutureReply(g2FutureReply);
    } catch (Exception e) {
      Trace.exception(e);
      e.printStackTrace();
    }
  }


  // Implement ItemListener

  /**
   * Invoked when the listener is added. It is called within the
   * context of the addItemListener method.
   */
  @Override
  public void receivedInitialValues (ItemEvent e)
  {
  }

  /**
   * Invoked when the denotation that the listener is interested
   * in changes.
   */
  @Override
  public void itemModified (ItemEvent e)
  {
  }

  /**
   * Invoked when the denotation that the listener is interested
   * in is no longer reachable.
   */
  @Override
  public void itemDeleted (ItemEvent e)
  {
    replySet.dispose(); // not interested in the relpyset any more
  }

}
