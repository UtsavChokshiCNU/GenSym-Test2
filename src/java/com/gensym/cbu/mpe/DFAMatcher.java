package com.gensym.cbu.mpe;

import java.io.*;
import java.rmi.RemoteException;
import java.util.Vector;
import com.gensym.denali.model.GraphElement;
import com.gensym.denali.model.ServerImpl;
import com.gensym.denali.model.Node;
import com.gensym.denali.model.Module;

// buffer should be circular 
// if buffer overflows throw 

// BUGZ
// 1 pat AB vs ABABE 
//   the pat is rejected after consuming the second AB and the second token is missed
// 2 (AB)+ vs ABABE
//   ????? 
// 3 EventPropagator don't activate until workspace hidden and shown
// 4 Matcher->Logger connection has persistent drawing problems.

public class DFAMatcher implements TestTypes, Serializable
{
  String definitionName;
  String loggerName;
  transient DFADefinition definition;
  transient StringBuffer buffer;
  transient int index = 0;
  Vector listeners = new Vector();

  // here, finish compiling and unit testing of runtime system here.

  public void initMatching()
  {
    buffer = new StringBuffer();
    index = 0;
  }

  public String getDefinitionName()
  {
    return definitionName;
  }

  public void setDefinitionName(String definitionName)
  {
    this.definitionName = definitionName;
  }

  private void cacheDefinition()
       throws RemoteException
  {
    if (definition == null && definitionName != null)
      {
	GraphElement[] nodes = ServerImpl.getGraphElementsContaining(this);
	if (nodes.length == 1 &&
	    nodes[0] instanceof Node)
	  {
	    try {
	      Node node = (Node)nodes[0];
	      Module module = node.getModule();
	      Node definitionNode = (Node)module.getNamedObject(definitionName);
	      if (definitionNode != null)
		definition 
		  = ((LexerDefinition)definitionNode.getBean()).getDefinition();
	    } catch (RemoteException e)
	      {
		e.printStackTrace();
		// I don't think this can fail.
	      }
	  }
	else
	  throw new IllegalStateException("lexer definition should be in one and only one node");
      }
  }

  public DFAResult match(Reader reader)
       throws IOException
  {
    cacheDefinition();
    int indexAtStart = index;
    DFAState[] states = definition.states;
    DFAState state = states[definition.initialStateIndex];
    int stopIndex = -1;
    int acceptedTokenIndex = -1;
    int acceptedPos = -1;
    int acceptedStopIndex = -1;
    DFAResult result = new DFAResult();
    char[] temp = new char[1];

    while (true)
      {
	if (state.isStop)
	  stopIndex = index;
	if (state.starts != null)
	  result.startBinding(state.starts,index);
	if (state.ends != null)
	  result.endBinding(state.ends,index);
	if (state.tokenIndex != -1)
	  {
	    System.out.println("potential match of "+state.tokenIndex+
			       " at "+index);
	    acceptedTokenIndex = state.tokenIndex;
	    acceptedPos = index;
	    acceptedStopIndex = stopIndex;
	  }
	if (state.transitions.length == 0)
	  break; // before consuming input
	int ch = reader.read();
	System.out.println("ch "+ch+" index "+index);
	if (ch == -1) // stream at end
	  break;
	else
	  {
	    DFATransition[] transitions = state.transitions;
	    int i,len = transitions.length;
	    DFATransition transitionTaken = null;
	    for (i=0; i<len; i++)
	      {
		DFATransition transition = transitions[i];
		System.out.println("trans type="+transition.testType+
				   " arg "+transition.arg);
		switch (transition.testType)
		  {
		  case EQUAL:
		    if ((char)ch == transition.arg)
		      transitionTaken = transition;
		    break;
		  case TRUE:
		    System.out.println("warning: non-consuming transition TRUE");
		    transitionTaken = transition;
		    break;
		  case FALSE:
		    System.out.println("warning: non-consuming transition FALSE");
		    break;
		  case METHODCALL:
		    if (transition.test.match((char)ch))
		      transitionTaken = transition;
		    break;
		  default:
		    throw new RuntimeException("Internal Error");
		  }
		if (transitionTaken != null)
		  break; // out of the for loop;
	      } // for loop
	    if (transitionTaken != null)
	      {
		temp[0] = (char)ch;
		buffer.append(temp,0,1);
		state = states[transitionTaken.nextStateIndex];
	      }
	    else
	      break; // out of the matcher main loop
	  }
	index++;
      } // match main loop end
    if (acceptedTokenIndex != -1)
      {
	if (stopIndex != -1 &&
	    definition.tokens[acceptedTokenIndex].isStop)
	  acceptedPos = acceptedStopIndex;
	result.matchedText = buffer.substring(indexAtStart,acceptedPos);
	// buffer.getChars(indexAtStart,acceptedPos,result.matchedText,0);
	result.tokenName = definition.tokens[acceptedTokenIndex].name;
      }
    else
      result.tokenName = null;
    return result;
  }

  public void matchAll(Reader reader, boolean startThread)
       throws IOException
  {
    if (startThread)
      {
	throw new RuntimeException("thread spawning not yet implemented");
      }
    initMatching();
    //Joe, I commented this next section out.  It seems to be the code that looked up the 
    // logger by name.  My current demo makes use of the event propagating connection to 
    // an odie publisher block. - this code causes a null pointer exception when there is no
    // logger with the given name.
    /*    Node loggerNode = null;
    GraphElement[] nodes = ServerImpl.getGraphElementsContaining(this);
    if (nodes.length == 1 &&
	nodes[0] instanceof Node)
      {
	Node node = (Node)nodes[0];
	System.out.println("i'm node "+node);
	if (loggerName != null && 
	    !loggerName.equals(""))
	  {
	    Module module = node.getModule();
	    System.out.println("module "+module+" lname "+loggerName);
	    loggerNode = (Node)module.getNamedObject(loggerName);
	  }
      }
    else
      throw new RuntimeException("huh?");*/
    while (true)
      {
	DFAResult result = match(reader);
	if (result.tokenName == null)
	  return;
	else
	  {
	    //	    System.out.println("matched token type "+result.tokenName+" text "+
	    //		       result.matchedText+" loggerNode "+loggerNode);
	    // HERE
	    // make matchEvent from result with bindings
	    MatchEvent event = result.makeMatchEvent(this);
	    int i,len = listeners.size();
	    for (i=0; i<len; i++)
	      ((MatchListener)listeners.elementAt(i)).matchFound(event);
	    /*	    if (loggerNode != null)
	      {
		((LoggingAdapter)loggerNode.getBean())
		  .extendLog("matched token type "+result.tokenName+" text "+
			     result.matchedText);
	      }*/
	  }
      }
  }

  public synchronized void addMatchListener(MatchListener listener)
  {
    listeners.addElement(listener);
  }

  public synchronized void removeMatchListener(MatchListener listener)
  {
    listeners.removeElement(listener);
  }
  
}
