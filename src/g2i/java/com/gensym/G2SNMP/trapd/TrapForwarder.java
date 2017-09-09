package com.gensym.G2SNMP.trapd;

import com.gensym.jgi.G2Connection;
import com.gensym.G2SNMP.rpc.*;
import com.gensym.G2SNMP.Transactor;
import com.adventnet.snmp.snmp2.SnmpPDU;
import com.adventnet.snmp.snmp2.SnmpException;
import com.adventnet.snmp.snmp2.SnmpVarBind;
import com.adventnet.snmp.snmp2.SnmpAPI;
import com.adventnet.snmp.snmp2.SnmpTimeticks;
import com.adventnet.snmp.snmp2.SnmpOID;
import com.gensym.G2SNMP.JsnmpBridge;
import java.util.Enumeration;
import com.gensym.jgi.G2AccessException;
import com.gensym.G2SNMP.trapd.SnmpNotification;
import com.adventnet.snmp.snmp2.SecurityModelEntry;
import com.adventnet.snmp.snmp2.UDPProtocolOptions;
/**
   This class runs in the background, checking the trap queue
   every timeStep milliseconds. Any new traps found in the queue
   get sent to G2 via startRPC(ReceiveTrap).
*/

class TrapForwarder implements Runnable
{
	private int timeStep;
	private long lastForwardTime = 0;
	private TrapQueue trapQueue;
	private TrapFilter trapFilter;
	private Thread theThread;
	private G2Connection g2con;

	/**
	   This constructor creates a separate thread and starts running in it.
	   @roseuid 365D38B602F1
	 */
	public TrapForwarder( int timeStep, G2Connection g2connection, TrapQueue trapQueue, TrapFilter trapFilter )
	{
		this.timeStep = timeStep;
		this.g2con = g2connection;
		this.trapQueue = trapQueue;
		this.trapFilter = trapFilter;
		theThread = new Thread( this );
		theThread.start();
	}

	/**
	   This method is used to inform the TrapForwarder that it should
	   check the TrapQueue as it seems to have a new PDU.
	   @roseuid 365D3A660270
	 */
	public void lookForTrap()
	{
		JsnmpBridge.debugOut ( "TrapForwarder.lookForTrap()" );
		synchronized (this)
		{
			this.notifyAll();
		}
	}

	/**
	   @roseuid 365D3BD502D2
	 */
	public synchronized void run()
	{
		long timeBefore;
		long delay;
		JsnmpBridge.debugOut( "TrapForwarder.run()" );
		while ( true )
		{
			timeBefore = System.currentTimeMillis();
			if ( ( timeBefore - lastForwardTime) >= timeStep )
			{
				// thread can send a trap to G2 now
				synchronized ( trapQueue )
				{
					if ( trapQueue.getCount() > 0 )
					{
						try
						{
              JsnmpBridge.debugOut ("TrapForwarder: trapQueue.getCount" + trapQueue.getCount());
							SnmpPDU pdu = trapQueue.getFirst();
							forwardTrapToG2( pdu );
							lastForwardTime = System.currentTimeMillis();
						}
						catch ( Exception e )
						{
							System.err.println( "Warning (trap forwarder): Can't forward trap to G2" );
							JsnmpBridge.debugOut( e.getMessage() );
						}
					}
				}
				delay = timeStep;
			}
			else
			{
				// thread was awakened before it can send a trap to G2 - sleep for the remaining time
				delay = timeStep - ( timeBefore - lastForwardTime );
			}

			try
			{
				wait( delay );
			}
			catch ( InterruptedException e )
			{
				JsnmpBridge.debugOut( "Interrupted trapd thread " + e.toString() );
			}
		 }
	}

	/**
	   @roseuid 367778C10182
	   2/24/00 - Increased the parameters array to 12.  The twelveth item is
				 the community string.
	 */
	private synchronized void forwardTrapToG2(SnmpPDU pdu)
	{
          //APIv4
          UDPProtocolOptions opt = (UDPProtocolOptions)pdu.getProtocolOptions();

		JsnmpBridge.debugOut( "TrapForwarder.forwardTrapToG2(pdu)");

		Object[] parameters = new Object[12];

		SnmpNotification notification = new SnmpNotification( pdu );

		if ( ( pdu.getVersion() == SnmpAPI.SNMP_VERSION_1 ) ||
			 ( pdu.getVersion() == SnmpAPI.SNMP_VERSION_2C )||
			 ( pdu.getVersion() == SnmpAPI.SNMP_VERSION_3) )
		{
			// error_code: integer
      parameters[0] = notification.getErrorStatus();
      //System.out.println( "getErrorStatus() returned:" );
      //System.out.println( parameters[0] );

      // error_string: text
      parameters[1] = notification.getErrorString();
      //System.out.println( "getErrorString() returned:" );
      //System.out.println( parameters[1] );

      // request_id: text
      parameters[2] = notification.getRequestID();
      //System.out.println( "getRequestID() returned:" );
      //System.out.println( parameters[2] );

      // snmp-version
      parameters[3] = notification.getVersion();
      //System.out.println( "getVersion() returned:" );
      //System.out.println( parameters[3] );

      //  enterprise: text
      parameters[4] = notification.getEnterprise();
      //System.out.println( "getEnterprise() returned:" );
      //System.out.println( parameters[4] );
      if (parameters[4] == null)
        parameters[4] = "Unknown";

      // agent_address: text
      parameters[5] = notification.getAgentAddress();
      //System.out.println( "getAgentAddress() returned:" );
      //System.out.println( parameters[5] );
      JsnmpBridge.debugOut ("TrapForwarder:  AgentAddr = " + pdu.getAgentAddr());
      JsnmpBridge.debugOut ("TrapForwarder:  RemoteHost = " + opt.getRemoteHost());
      if ("Not supplied".equals(parameters[5]) || parameters[5] == null)
        parameters[5] = opt.getRemoteHost();

      // agent_hostname:text
      parameters[6] = notification.getAgentHostName();
      //System.out.println( "getAgentHostName() returned:" );
      //System.out.println( parameters[6] );
      if ("Not supplied".equals(parameters[6]) || parameters[6] == null)
        parameters[6] = opt.getRemoteHost();

      // generic_trap: integer
      parameters[7] = notification.getTrapType();
      //System.out.println( "getTrapType() returned:" );
      //System.out.println( parameters[7] );

      // specific_trap: quantity
      parameters[8] = notification.getSpecificType();
      //System.out.println( "getSpecificType() returned:" );
      //System.out.println( parameters[8] );

      // agent_act_time: quantity
      parameters[9] = notification.getUpTime();
      //System.out.println( "getUpTime() returned:" );
      //System.out.println( parameters[9] );

      // variable bindings: sequence
      parameters[10] = notification.getVariableBindings();
      //System.out.println( "getVariableBindings() returned:" );
      //System.out.println( parameters[10] );
      
      // community_string: text
			if ( pdu.getVersion() == SnmpAPI.SNMP_VERSION_3)
				parameters[11] = "";
			else
				parameters[11] = notification.getCommunity();
            //System.out.println( "getCommunity() returned:" );
            //System.out.println( parameters[11] );
            //System.out.flush();
    }
    else
    {
      System.err.println( "Warning (trap forwarder): unsupported SNMP version in received PDU" );
    }
    if ( g2con.isAlive() )
    {
      //System.err.println ("TrapForwarder: Sending the trap to G2");
      try
			{
				JsnmpBridge.debugOut( "TrapForwarder:  g2con.callRPC(G2Procedures.ReceiveTrap, parameters)");
				g2con.callRPC(G2Procedures.ReceiveTrap, parameters);
			}
      catch (Exception e)
      {
				System.err.println( "Warning (TrapForwarder): can't forward trap to G2" );
        //System.err.println("    Error Message: " + e.getMessage());
				JsnmpBridge.debugOut( e.getMessage() );
			}
		}
  }

    public void stop()
    {
		theThread.stop();
    }
}
