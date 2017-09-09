package com.gensym.cbu.mpe;

import com.gensym.denali.model.*;
import java.rmi.*;
import java.util.Enumeration;
import java.util.Stack;
import java.util.Hashtable;
import java.util.Vector;

public class DefinitionSchematicImpl extends SchematicImpl
  implements TestTypes
{
  DFADefinition definition;
  transient SharedDefinitionReference[] commands;
  transient boolean commandsAreCached = false;
  static boolean trace = true;

  public DefinitionSchematicImpl()
       throws RemoteException
  {
    super();
  }

  public DefinitionSchematicImpl(Object parent, String name)
       throws RemoteException
  {
    super(parent,name);
  }

  public DFADefinition getDefinition()
  {
    return definition;
  }

  public void setDefinition(DFADefinition definition)
  {
    this.definition = definition;
  }

  private void setupCommands()
       throws RemoteException
  {
    Module parent = getModule();
    JavaStatement js1 
      = new JavaStatement( "((com.gensym.cbu.mpe.DefinitionSchematicImpl)"+
			   "appContainer).compile();");
    
    JavaCommand command 
      = new JavaCommand (new String[] { "compile"},
      new JavaStatement[] { js1 },
      "com.gensym.cbu.mpe",
      "MenuLabels");
    
    try {
      parent.setSharedDefinition ("LexerCommands", command);
      commands 
	= new SharedDefinitionReference[] { new SharedDefinitionReference(parent.getName(),
									  "LexerCommands")};
    } catch (RemoteException e)
      {
	System.out.println("failed to set up commands");
	e.printStackTrace();
      }
  }

  protected SharedDefinitionReference[] getCommandReferences()
       throws RemoteException
  {
    if (!commandsAreCached)
      {
	setupCommands();
	commandsAreCached = true;
      }
    return commands;
  }

  public void compile()
       throws RemoteException
  {
    // 1 Find the (unique) start state
    Node startNode = null;
    if (trace)
      System.out.println("compiling...");
    Enumeration items = getItems();
    while (items.hasMoreElements())
      {
	RemoteItem item = (RemoteItem)items.nextElement();
	if (item instanceof Node)
	  {
	    Object bean = ((Node)item).getBean();
	    if (bean instanceof NDFAState)
	      {
		NDFAState state = (NDFAState)bean;
		if (trace)
		  System.out.println("state = "+state);
		if (state.isStart() && startNode != null)
		  throw new RuntimeException("duplicate start states");
		else if (state.isStart())
		  startNode = (Node)item;
	      }
	  }
      }
    if (startNode == null)
      throw new RuntimeException("no start state found");
    // 2 expand multi-char transitions and macro references
    NDFAState startState = expandNDFA(startNode);
    EpsilonClosure startClosure = null;
    // 3 make DFA
    if (trace)
      System.out.println("start state"+startState);
    if (true)
      {
	Stack stack = new Stack();
	Hashtable closureTable = new Hashtable();
	Hashtable testCache = new Hashtable();
	startClosure = getOrMakeEpsilonClosure(new NDFAState[] { startState },closureTable);
	stack.push(startClosure);
	while (!stack.isEmpty())
	  {
	    EpsilonClosure closure = (EpsilonClosure)stack.pop();
	    closure.visited = true;
	    Vector deterministicTransitions = findClosureTransitions(closure,testCache);
	    int i,len = deterministicTransitions.size();
	    if (trace)
	      System.out.println("Main loop dTrans count = "+len);
	    for (i=0; i<len; i++)
	      {
		DeterministicTransition dTransition = 
		  (DeterministicTransition)deterministicTransitions.elementAt(i);
		if (trace)
		  System.out.println("Main loop dTrans states = "+dTransition.states);
		NDFAState[] targetStates = new NDFAState[dTransition.states.size()];
		dTransition.states.copyInto(targetStates);
		EpsilonClosure targetClosure 
		  = getOrMakeEpsilonClosure(targetStates,closureTable);
		System.out.println("dtrans.states="+dTransition.states+" yields\n"+
				   targetClosure);
		closure.extendTransitions(dTransition.transition,targetClosure);
		if (!targetClosure.visited)
		  {
		    if (trace)
		      System.out.println("MAIN LOOP pushing target closure "+targetClosure);
		    stack.push(targetClosure);
		  }
	      }
	  }
	System.out.println("___NEAR RESULTS:_________________");
	definition = makeDefinition(closureTable,startClosure);
      }
  }

  NDFAState expandNDFA(Node startNode)
       throws RemoteException
  {
    NDFAState start = (NDFAState)startNode.getBean();
    NDFAState result = new NDFAState(start);
    Stack stack = new Stack();
    stack.push(startNode);
    Hashtable substituteTable = new Hashtable();
    substituteTable.put(start,result);
    while (!stack.isEmpty())
      {
	Node node = (Node)stack.pop();
	NDFAState state = (NDFAState)node.getBean();
	state = (NDFAState)substituteTable.get(state);
	if (trace)
	  System.out.println("working on state " + state);
	state.visited = true;
	int syntheticNodeCount = 0;
	Enumeration ports = node.getPorts();
	Vector transitions = new Vector();
	while (ports.hasMoreElements())
	  {
	    Port port = (Port)ports.nextElement();
	    if (trace)
	      System.out.println("Port "+port+" input "+port.isInput());
	    // ignore input ports
	    if (port.isInput())
	      continue;
	    Connection connection = port.getConnection();
	    TransitionSpecification transition 
	      = (TransitionSpecification)connection.getBean();
	    Terminal output = connection.getOutput();
	    if (trace)
	      System.out.println("output = "+output);
	    if (!(output instanceof Port))
	      continue;
	    Node nextNode = ((Port)output).getNode();
	    NDFAState nextState = (NDFAState)nextNode.getBean();
	    if (trace)
	      System.out.println("raw next state "+nextState);
	    NDFAState substitute = (NDFAState)substituteTable.get(nextState);
	    if (substitute == null)
	      {
		substitute = new NDFAState(nextState);
		substituteTable.put(nextState,substitute);
	      }
	    switch (transition.type)
	      {
	      case EQUAL:
		char[] charsToMatch = transition.stringToMatch.toCharArray();
		if (charsToMatch.length == 0)
		  // Here make transition for true
		  transitions.addElement(new TransitionSpecification(TRUE,' ',substitute));
		else 
		  // here make chain of transitions for each char
		  {
		    NDFAState previous = state;
		    for (int j=0; j<charsToMatch.length; j++)
		      {
			NDFAState next;
			if (j+1 == charsToMatch.length)
			  next = substitute;
			else
			  {
			    next = new NDFAState(null,
						 false,
						 null);
			    substituteTable.put(new Integer(syntheticNodeCount++),
						next);
			  }
			if (j==0)
			  transitions
			    .addElement(new TransitionSpecification(EQUAL,
								    charsToMatch[j],next));
			else
			  previous.transitions[0] 
			    = new TransitionSpecification(EQUAL,charsToMatch[j],next);
			previous = next;
		      }
		  }
		break;
	      case TRUE:
		break;
		// eventually to macro case here
	      default:
		throw new RuntimeException("Well, self, how did I get here?");
	      }
	    state.transitions = new TransitionSpecification[transitions.size()];
	    transitions.copyInto(state.transitions);
	    // deal with expanding transition
	    if (!substitute.visited)
	      stack.push(nextNode);
	  }
      }
    // Debugging 
    System.out.println("After expand startNode = "+result);
    Enumeration elements = substituteTable.elements();
    while (elements.hasMoreElements())
      {
	NDFAState state = (NDFAState)elements.nextElement();
	System.out.println("  "+state);
	if (state.transitions != null)
	  for (int i=0; i<state.transitions.length; i++)
	    System.out.println("    "+state.transitions[i]);
      }
    System.out.println("____________________________________");
    return result;
  }

  EpsilonClosure getOrMakeEpsilonClosure(NDFAState[] startStates, Hashtable closureTable)
  {
    Vector closureVector = new Vector();
    Stack stack = new Stack();
    int i,len = startStates.length;
    for (i=0; i<len; i++) stack.push(startStates[i]);
    while (!stack.isEmpty())
      {
	NDFAState state = (NDFAState)stack.pop();
	closureVector.addElement(state);
	System.out.println("considering closure state "+state);
	if (state.transitions != null)
	  {
	    TransitionSpecification[] transitions = state.transitions;
	    len = transitions.length;
	    for (i=0; i<len; i++)
	      {
		TransitionSpecification transition = transitions[i];
		System.out.println("  considering transition "+transition+
				   " non-consuming "+transition.isNonConsuming());
		if (transition.isNonConsuming())
		  {
		    if (!closureVector.contains(transition.next))
		      stack.push(transition.next);
		  }
	      }
	  }
      }
    NDFAState[] states = new NDFAState[closureVector.size()];
    closureVector.copyInto(states);
    EpsilonClosure lookupClosure = new EpsilonClosure(states);
    EpsilonClosure closure = (EpsilonClosure)closureTable.get(lookupClosure);
    if (closure == null)
      {
	closure = lookupClosure;
	closureTable.put(closure,closure);
      }
    return closure;
  }

  Vector findClosureTransitions(EpsilonClosure closure, Hashtable testCache)
  {
    // result is <unique-test-arg-pair> -> (list of NDFA states)
    // all tests are compaired pairwise and extended with
    // EXAMPLE
    // t1 digitChar -> (3)
    // t2 == '0' -> (1)
    //  (01|<digit>b)
    //  input 02
    //  0 needs transitions of digit
    //  <digit> cannot take transitions of 0 because not necessarily true
    NDFAState[] closureStates = closure.states;
    Vector deterministicTransitions = new Vector();
    int i,len = closureStates.length;
    for (i=0; i<len; i++)
      {
	NDFAState state = closureStates[i];
	if (trace)
	  System.out.println("FCT considering state "+state);
	if (state.transitions != null)
	  {
	    TransitionSpecification[] transitions = state.transitions;
	    int j,tranCount = transitions.length;
	    for (j=0; j<tranCount; j++)
	      {
		TransitionSpecification transition = transitions[j];
		if (transition.isNonConsuming())
		  continue;
		if (trace)
		  System.out.println("  FCT considering transition "+transition);
		boolean found = false;
		int k,deterministicTransitionCount = deterministicTransitions.size();
		for (k=0; k<deterministicTransitionCount; k++)
		  {
		    DeterministicTransition dTransition 
		      = (DeterministicTransition)deterministicTransitions.elementAt(k);
		    if (transition.simpleEquals(dTransition.transition))
		      {
			found = true;
			if (trace)
			  System.out.println("    FCT ADDING to set "+transition.next);
			dTransition.states.addElement(transition.next);
			break;
		      }
		  }
		if (!found)
		  {
		    if (trace)
		      System.out.println("  FCT making new set with "+transition);
		    deterministicTransitions.addElement(new DeterministicTransition(transition));
		  }
	      }
	  }
      }
    // HERE, do the pairwise test and extend and test compiler
    len = deterministicTransitions.size();

    int j;
    for (i=0; i<len; i++)
      for (j=0; j<i; j++)
	{
	  DeterministicTransition
	    dTransition1 = (DeterministicTransition)deterministicTransitions.elementAt(i),
	    dTransition2 = (DeterministicTransition)deterministicTransitions.elementAt(j);
	  if (dTransition1.transition.includes(dTransition2.transition))
	    dTransition2.addTransitions(dTransition1);
	  if (dTransition2.transition.includes(dTransition1.transition))
	    dTransition1.addTransitions(dTransition2);
	}    
    return deterministicTransitions;
  }

  DFADefinition makeDefinition(Hashtable closureTable, EpsilonClosure startClosure)
  {
    Vector tokenVector = new Vector();
    int closureCount = closureTable.size();
    Enumeration closureEnum = closureTable.elements();
    EpsilonClosure[] closures = new EpsilonClosure[closureCount];
    DFAState[] states = new DFAState[closureCount];
    int[] tokenIndices = new int[closureCount];
    int tokenIndex = 0,stateIndex = 0;
    while (closureEnum.hasMoreElements())
      {
	EpsilonClosure closure = (EpsilonClosure)closureEnum.nextElement();
	System.out.println(""+closure);
	closure.pprintTransitions();
	int i,len = closure.states.length;
	DFAToken token = null;
	for (i=0; i<len; i++)
	  if ((closure.states[i].terminalStateName != null) &&
	      !closure.states[i].terminalStateName.equals(""))
	    {
	      if (token == null)
		token = new DFAToken(closure.states[i].terminalStateName);
	      else
		throw new RuntimeException("How did that happen?");
	    }
	if (token != null)
	  {
	    tokenVector.addElement(token);
	    tokenIndices[stateIndex] = tokenIndex++;
	  }
	else
	  tokenIndices[stateIndex] = -1;
	System.out.println("tokenindices["+stateIndex+"]="+tokenIndices[stateIndex]);
	closures[stateIndex] = closure;
	stateIndex++;
      }
    stateIndex = 0;
    for (int closureIndex = 0; closureIndex<closureCount; closureIndex++)
      {
	EpsilonClosure closure = closures[closureIndex];
	int i,len = closure.transitions.size();
	DFATransition[] transitions = new DFATransition[len];
	for (i=0; i<len; i++)
	  {
	    TransitionSpecification transition 
	      = (TransitionSpecification)closure.transitions.elementAt(i);
	    EpsilonClosure targetClosure
	      = (EpsilonClosure)closure.targetClosures.elementAt(i);
	    transitions[i] 
	      = new DFATransition(transition.type,
				  transition.charArg,
				  getDFAStateIndex(closures,targetClosure));
	  }
	states[stateIndex] = new DFAState(transitions,tokenIndices[stateIndex]);
	addStartsAndStops(states[stateIndex],closure);
	System.out.println("DFA state tindex "+states[stateIndex].tokenIndex);
	stateIndex++;
      }
    DFAToken[] tokens = new DFAToken[tokenVector.size()];
    tokenVector.copyInto(tokens);
    return new DFADefinition(states,tokens,getDFAStateIndex(closures,startClosure));
  }

  private int getDFAStateIndex(EpsilonClosure[] closures, EpsilonClosure closure)
  {
    int i,len = closures.length;
    for (i=0; i<len; i++)
      {
	if (closures[i].equals(closure))
	  return i;
      }
    throw new RuntimeException("un-indexed closure");
  }

  private void addStartsAndStops(DFAState state, EpsilonClosure closure)
  {
    Vector startVector = new Vector();
    Vector endVector = new Vector();
    int i, len = closure.states.length;
    for (i=0; i<len; i++)
      {
	NDFAState ndfaState = closure.states[i];
	if (ndfaState.bindingStart != null &&
	    !ndfaState.bindingStart.equals("") &&
	    !startVector.contains(ndfaState.bindingStart))
	  startVector.addElement(ndfaState.bindingStart);
	if (ndfaState.bindingEnd != null &&
	    !ndfaState.bindingEnd.equals("") &&
	    !endVector.contains(ndfaState.bindingEnd))
	  endVector.addElement(ndfaState.bindingEnd);
      }
    System.out.println("*** addStarts and starts "+startVector+" ends "+endVector);
    if (startVector.size() > 0)
      {
	state.starts = new String[startVector.size()];
	startVector.copyInto(state.starts);
      }
    if (endVector.size() > 0)
      {
	state.ends = new String[endVector.size()];
	endVector.copyInto(state.ends);
      }
  }
}

class EpsilonClosure
{
  NDFAState[] states;
  Vector transitions = new Vector();
  Vector targetClosures = new Vector();
  boolean visited = false;

  EpsilonClosure(NDFAState[] states)
  {
    this.states = states;
  }

  void extendTransitions(TransitionSpecification transition,
			 EpsilonClosure targetClosure)
  {
    transitions.addElement(transition);
    targetClosures.addElement(targetClosure);
  }
  
  @Override
  public boolean equals(Object object)
  {
    boolean res = equals1(object);
    // System.out.println("EQ? "+this+" vs "+object+" = "+res);
    return res;
  }
  public boolean equals1(Object object)
  {
    if (object instanceof EpsilonClosure)
      {
	EpsilonClosure closure = (EpsilonClosure)object;
	int i,j,len = states.length;
	// System.out.println(" vs "+closure+" len "+ closure.states.length);
	if (len == closure.states.length)
	  {
	    for (i=0; i<len; i++)
	      {
		boolean found = false;
		for (j=0; j<len; j++)
		  {
		    if (states[i] == closure.states[j])
		      {
			found = true;
			break;
		    }
		  }
		if (!found)
		  return false;
	      }
	    return true;
	  }
	else
	  return false;
      }
    else
      return false;
  }

  @Override
  public int hashCode()
  {
    int res = 0;
    for (int i=0; i<states.length; i++)
      res += states[i].hashCode();
    // System.out.println(this+".hashCode()-> "+res);
    return res;
  }
 
  @Override
  public String toString()
  {
    StringBuffer buffer = new StringBuffer( "<EC: vis?="+visited+" ");
    for (int i=0; i<states.length; i++)
      buffer.append(" "+states[i]);
    buffer.append(">");
    return buffer.toString();
  }

  void pprintTransitions()
  {
    for (int i = 0; i<transitions.size(); i++)
      {
	System.out.println("  "+transitions.elementAt(i));
	System.out.println("  "+targetClosures.elementAt(i));
      }
  }

}

class DeterministicTransition
{
  Vector states = new Vector();
  TransitionSpecification transition;
  
  DeterministicTransition(TransitionSpecification transition)
  {
    this.transition = transition;
    states.addElement(transition.next);
  }

  void addTransitions(DeterministicTransition other)
  {
    int i,len = other.states.size();
    for (i=0; i<len; i++)
      {
	NDFAState state = (NDFAState) other.states.elementAt(i);
	if (!states.contains(state))
	  states.addElement(state);
      }
  }
}
