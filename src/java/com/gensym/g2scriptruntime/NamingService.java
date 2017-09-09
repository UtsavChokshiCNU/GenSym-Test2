package com.gensym.g2scriptruntime;

import java.util.Enumeration;

/* 
   1. g2script, must have
   2. receives a value ok
   3. signals/raises/sends a named event, not anything yet
   4. would like new rule type
   4a   enable grammar off secret sys-proc
   4b   g2-send-event-to-inference-engine (event-object :class item,
                                           sender :class item
					   ListenerMethodName :text)


   Questions for Mike:
  
   1 How can the NamingService be given a standing order to make all 
   items of some class register with the rule engine.

   NamingServiceListener
     includes objectAdded
              objectRemoved
   
   2 Should the syntax of the event specification mention the eventSet name
     the listener method name within that set, both, or neither (not likely!!)
     
     Mike sez listenerMethod name within event set.

   */

public interface NamingService
{
  public Object lookup(String name, Class clazz);

  public Enumeration lookup(Class clazz);

  public void setRegistrationListener(RegistrationListener listener);

  public RegistrationListener getRegistrationListener();

}


