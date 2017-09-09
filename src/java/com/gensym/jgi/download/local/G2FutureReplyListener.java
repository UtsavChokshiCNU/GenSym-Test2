package com.gensym.jgi.download.local;

import com.gensym.fida.message.*;
import com.gensym.classes.modules.g2runtime.G2rtFutureReply;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;

class G2FutureReplyListener implements FutureReplyListener
{

  private G2rtFutureReply g2FutureReply = null;

  G2FutureReplyListener(G2rtFutureReply g2FutureReply)
  {
    this.g2FutureReply = g2FutureReply;
  }

  public void isAvailable(FutureReplyEvent event)
  {
    FutureReply reply = event.getFutureReply();
    updateG2FutureReply(g2FutureReply, reply);
  }

  static void updateG2FutureReply(G2rtFutureReply g2FutureReply, FutureReply reply)
  {   
    try {
      Sequence seq = new Sequence();
      try {
	Object replyObj = reply.getReply();
	if (reply != null)
	  seq.addElement(replyObj);
	else 
	  seq.addElement(Symbol.intern("NONE"));
      } catch (MessageException e) {
	seq.addElement(Symbol.intern("NONE"));
      }
      g2FutureReply.set_replySeq(seq);
      // Cant map exception yet !
    } catch (G2AccessException e) {
      Trace.exception(e);
    }
    
  }

}
