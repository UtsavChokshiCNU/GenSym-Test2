using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLServer.
	/// </summary>
	public class BSLServer: DSLServer
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLServer(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public void Fill(int serverId)
		{
			m_objDSLUtils.GetServer(serverId, (DSLServer)this);
			if (TServers.Count == 0)
				throw new Exception("Invalid server ID.");
		}

		/*public static DSLServer GetServer(int serverId)
		{
			DSLUtils objDSLUtils = new DSLUtils();
			return objDSLUtils.GetServer(serverId);
		}*/

	}
}
