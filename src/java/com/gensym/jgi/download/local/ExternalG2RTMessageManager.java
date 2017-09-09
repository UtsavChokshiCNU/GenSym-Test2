package com.gensym.jgi.download.local;

import com.gensym.fida.*;
import com.gensym.fida.message.*;
import com.gensym.fida.support.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.classes.modules.g2runtime.*;
import com.gensym.g2export.G2__Base;
import com.gensym.g2export.G2ProxyAccess;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.jgi.G2JavaStubController;


public class ExternalG2RTMessageManager extends MessageManagerImpl {

  private static final Symbol HANDLE_MESSAGE_ = Symbol.intern("HANDLE-MESSAGE");

  protected ExternalG2RTMessageManager(ObjectContainer container)
  {
    super(container);
  }

  protected boolean handleMessage(MessageEvent mevent)
  {

    Message message = mevent.getMessage();
    if (message instanceof CallIndexedMethodMessage ||
	message instanceof CallReflectiveMethodMessage)
      return super.handleMessage(mevent);
    
    Object obj = getContainer().getRegisteredObject();
    if (obj instanceof G2ProxyAccess) {
      if (message instanceof com.gensym.g2export.G2__Base) {
	try {
	  FIDARuntime runtime = getContainer().getApplicationEnvironment().getRuntime();
	  G2RTExportManager exportManager = ((ExternalG2RTRuntime)runtime).getExportManager();
	  G2rtMessage g2Message = 
	    (G2rtMessage)exportManager.createG2ItemVersionOfLocalItem((com.gensym.g2export.G2__Base)message);
	  Item g2Proxy = (Item)((G2ProxyAccess)obj)._getG2Item();
	  Boolean handled = 
	    (Boolean)G2JavaStubController.getG2JavaStubController().callG2ProxyFromJava(
					 exportManager.getConnection(), 
					 HANDLE_MESSAGE_, 
					 new Object[] {g2Proxy, g2Message});
	  Sequence replySeq = g2Message.get_replySeq();
	  if (replySeq.size() > 0) {
	    Object reply = replySeq.elementAt(0);
	    message.setReply(exportManager.toLocalParameter(reply));
	    System.out.println("Received reply from G2 " + message.getReply());
	  }
	  g2Message.delete(true, true);
	  return handled.booleanValue();
	} catch (Exception ex) {
	  ex.printStackTrace();
	  message.setException(ex);
	  return true;
	}
      }
    } 

    return super.handleMessage(mevent);
  }

  private static final MessageManagerImplFactory messageManagerFactory = 
  new MessageManagerImplFactory() {
    public MessageManagerImpl createMessageManagerImpl(ObjectContainer container) {
      return new ExternalG2RTMessageManager(container);
    }
  }; 

  public static void setMessageManagerImplFactory() 
       throws FIDARuntimeException
  {
    MessageManagerImpl.setMessageManagerImplFactory(messageManagerFactory);
  }

  public static void sendOnewayMessage(FIDARuntime runtime, 
				       ObjectProxy proxy, 
				       G2rtMessage g2Message)
       throws MessageException, RemoteObjectAccessException
  {
    Message localMessage = getMessageFromG2MessageItem(runtime, g2Message);
    proxy.sendOnewayMessage(localMessage);
  }

  public static Object sendMessage(FIDARuntime runtime, 
				   ObjectProxy proxy, 
				   G2rtMessage g2Message)
       throws MessageException, RemoteObjectAccessException, MessageNotHandledException
  {
    Message localMessage = getMessageFromG2MessageItem(runtime, g2Message);
    Object obj = proxy.sendMessage(localMessage);
    // NOTE: THIS OBJ MUST BE CONVERTED BACK INTO A G2 AWARE OBJECT
    return obj;
  }

  /**
   * Dispatch a message from proxy.
   * @param runtime The LocalRuntime to perform any export as required
   * @param proxy The proxy to call dispatchMessage on
   * @param g2message The Item that must represent a G2RT-MESSAGE in G2
   */
  public static void dispatchMessage(FIDARuntime runtime, 
				ObjectProxy proxy, 
				G2rtMessage g2Message, 
				G2rtFutureReply g2FutureReply)
       throws MessageException, RemoteObjectAccessException
  {
    Message localMessage = getMessageFromG2MessageItem(runtime, g2Message);
    FutureReply reply = proxy.dispatchMessage(localMessage);
    reply.addFutureReplyListener(new G2FutureReplyListener(g2FutureReply));
  }

  /**
   * Multicast message from G2 using a DomainService.
   */
  public static void multicastMessage(DomainService domainService,
				      String domain,
				      G2rtMessage g2Message,
				      G2rtReplySet g2ReplySet)
       throws MessageException, RemoteObjectAccessException, DomainServiceException
  {
    ExternalG2RTRuntime runtime = 
      (ExternalG2RTRuntime)domainService.getApplicationEnvironment().getRuntime();
    Message localMessage = getMessageFromG2MessageItem(runtime, g2Message);
    ReplySet relpySet = domainService.multicastMessage(domain, localMessage);
    relpySet.addReplySetListener(new G2ReplySetListener(relpySet, 
							g2ReplySet));
  }

  /**
   * Clone a G2 Message as a com.gensym.g2export.Message, copying atts over.
   */
  public static Message getMessageFromG2MessageItem(FIDARuntime runtime, 
						    G2rtMessage g2Message)
       throws MessageException, RemoteObjectAccessException
  {
    // Export the g2Message to a standlone local version
    G2RTExportManager exportManager = ((ExternalG2RTRuntime)runtime).getExportManager();
    com.gensym.g2export.Item localMessage = null;
    try {
      Class localClazz = exportManager.getJavaClassFromExportIfNecessary((G2Definition)g2Message.getDefinition(), false);
      localMessage = (com.gensym.g2export.Item)localClazz.newInstance();
      exportManager.updateLocalItemFromG2Item(g2Message, localMessage);
    } catch (Exception e) {
      throw new MessageException(e, e.toString());
    } 
    try {
      // If you are wondering how we can cast this to Message...There is a SpecialImpl for the
      // local exported class that adds Message as an implemented Interface.
      return(Message)localMessage;
    } catch (ClassCastException e) {
      throw new MessageException("Exported G2 Message did not implement the com.gensym.fida.message.Message interface");
    }
  } 

}
