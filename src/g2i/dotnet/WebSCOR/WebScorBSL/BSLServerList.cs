using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLServer.
	/// </summary>
	public class BSLServerList: DSLServer
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLServerList(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public void Fill()
		{
			m_objDSLUtils.GetServerList((DSLServer)this);
		}
	}
}
