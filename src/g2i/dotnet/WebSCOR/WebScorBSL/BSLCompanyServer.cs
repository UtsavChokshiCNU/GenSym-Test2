using System;
using WebScorDSL;
using System.Xml;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLCompanyServer.
	/// </summary>
	public class BSLCompanyServer: DSLCompanyServer
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLCompanyServer(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public BSLCompanyServer(int serverId, string strServerName, string strIPAddress, 
			int coId, int iPortNo, string strConnStr): this(strConnStr)
		{
			this.TCompanyServers.AddTCompanyServersRow(serverId,
				strServerName, strIPAddress, 0, 0, false, coId, iPortNo, false, false);
		}

		public void Fill(int coServerId)
		{
			m_objDSLUtils.GetCompanyServer(coServerId, (DSLCompanyServer)this);
			if (TCompanyServers.Count == 0)
				throw new Exception("Invalid company server ID.");
		}

		/*public static DSLCompanyServer GetCompanyServer(int coServerId)
		{
			DSLUtils objDSLUtils = new DSLUtils();
			return objDSLUtils.GetCompanyServer(coServerId);
		}*/

		/// <summary>
		/// Returns true if server/port is available for use by company.
		/// </summary>
		public bool IsAvailable(string strUserName, string strPassword)
		{
			if (TCompanyServers.Count == 0)
				throw new Exception("You must populate the object before calling IsAvailable.");

			DSLCompanyServer.TCompanyServersRow r = this.TCompanyServers[0];
			
			//See if you can connect to the server/port
			G2Interrogator objClient = new G2Interrogator(strUserName, strPassword, 
				r.ipAddress.ToString() /*serverName */, r.portNo);
			if (!objClient.Ping())
			{
				return false;
				//Couldn't connect to it, so try to start if necessary.

				//Ask the G2 Manager if the server is running...
//				if (objClient.IsG2Running())
//					return false; //The manager thinks it's running, so return false.

				//Manager thinks it's stopped, so try to start it.
//				if (!objClient.StartServer())
//					return false; //unable to start it, so return false.
	
				//Manager thinks it started server, so try to connect again.
//				if (!objClient.Ping())
//					return false;
			}

			//Check to see that it's in use by the company.
//			if (!objClient.InUseByCompany(r.coId))
//				return false;

			return true;
		}

		/// <summary>
		/// Returns the number of users currently using server/port.
		/// </summary>
		public short GetNumCurrentUsers(string strUserName, string strPassword)
		{
			if (TCompanyServers.Count == 0)
				throw new Exception("You must populate the object before calling GetNumCurrentUsers.");

			DSLCompanyServer.TCompanyServersRow r = this.TCompanyServers[0];
			
			//See if you can connect to the server/port
			G2Interrogator objClient = new G2Interrogator(strUserName, strPassword, 
				r.serverName, r.portNo);
			if (!objClient.Ping())
				return 0; 

//			if (!objClient.InUseByCompany(r.coId))
//				return 0; 
//
//			short i = objClient.GetNumUsers(r.coId);
//			return i;
			return 0;
		}

	}
}
