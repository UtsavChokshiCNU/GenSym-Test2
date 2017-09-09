package com.gensym.g2export;

import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2JavaStubController;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.ImplAccess;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.fida.RemoteObjectAccessException;
import com.gensym.fida.message.MessageException;
import com.gensym.fida.message.MessageNotHandledException;
import com.gensym.fida.ObjectContainer;

/**
 * Base class of G2 Proxy wrapper Impls, holds actual G2 item and context
 */
public class G2__ProxyBaseImpl extends G2__BaseImpl implements G2ProxyAccess
{

  protected transient G2Access context;
  public transient com.gensym.classes.G2__Base g2itemref;

  public G2__ProxyBaseImpl(com.gensym.classes.G2__Base proxy) 
  {
    g2itemref = proxy;
    context = ((ImplAccess)proxy).getContext();
  }

  public void onRegistration(ObjectContainer container)
  {
    this.container = container; 
    this.remoteProxy = container.getObjectProxy();
  }
  
  // Implement G2ProxyAccess
  @Override
  public com.gensym.classes.G2__Base _getG2Item()
  {
    return g2itemref;
  }

  public final java.lang.Object _callG2ProxyMethod(Symbol g2MethodName,
						   String classKey,
						   int remoteCallIndex,
						   java.lang.Object[] parameters)
       throws RemoteObjectAccessException,
	      MessageException,
	      MessageNotHandledException,
	      G2AccessException
  {
    if (g2itemref == null) {
      if (remoteProxy == null) {
	throw new RuntimeException("No RemoteProxy or G2proxy set to call Method !");
      } else {
	return invokeMyRemoteMethod(classKey, remoteCallIndex, parameters);
      }
    } else {
      java.lang.Object[] g2Params = new java.lang.Object[parameters.length + 1];

      if (g2ObjectConverter == null)
	throw new G2AccessException("C'ant convert G2 Parameters as no G2ObjectConverter is installed");

      g2Params[0] = g2itemref;
      for (int i=1; i<g2Params.length; i++) {
	g2Params[i] = g2ObjectConverter.toG2Parameter(parameters[i-1]);
	System.out.println("Passing " + g2Params[i]);
      }
      java.lang.Object ret = context.callRPC(g2MethodName, g2Params);
      return g2ObjectConverter.toLocalParameter(ret);
    }
  }

  public final java.lang.Object _getPropertyValue(Symbol g2VarName,
						  String classkey,
						  int remoteCallIndex)
       throws RemoteObjectAccessException,
	      MessageException,
	      MessageNotHandledException,
	      G2AccessException,
	      NoSuchAttributeException
  {
    if (g2itemref == null) {
      if (remoteProxy == null) {
	throw new RuntimeException("No RemoteProxy or G2proxy set");
      } else {
	return invokeMyRemoteMethod(classkey, remoteCallIndex, new java.lang.Object[0]);
      }
    } else {
      return g2itemref.getPropertyValue(g2VarName);
    }
  }

  public final void _setpropertyValue (Symbol g2VarName,
				       String classkey,
				       int remoteCallIndex,
				       java.lang.Object parameter)
	 throws RemoteObjectAccessException,
	        MessageException,
	        MessageNotHandledException,
	        G2AccessException,
		NoSuchAttributeException
  {
    if (g2itemref == null) {
      if (remoteProxy == null) {
	throw new RuntimeException("No RemoteProxy or G2proxy set");
      } else {
	invokeMyRemoteMethod(classkey, remoteCallIndex, new java.lang.Object[] {parameter});
      }
    } else {
      g2itemref.setPropertyValue(g2VarName, parameter);
    }
  }
						   

}
