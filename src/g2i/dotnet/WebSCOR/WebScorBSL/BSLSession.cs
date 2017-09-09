using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLSession.
	/// </summary>
	public class BSLSession: DSLSession
	{
		private DSLUtils m_objDSLUtils = null;
		private int m_userId = 0;

		private BSLSession(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public BSLSession(int userId, string strConnStr): this(strConnStr)
		{	
			m_userId = userId;
		}

		public void Refresh(int serverId, int portNo)
		{
			if (TSessions.Count == 0)
				throw new Exception("Please populate the Session object using Fill before calling Refresh.");
			
			TSessions[0].serverId = serverId;
			TSessions[0].serverPortNo = portNo;
			TSessions[0].loginDate = System.DateTime.Now;
			TSessions[0].sessionGuid = Guid.NewGuid();
		}

		public void Fill()
		{
			m_objDSLUtils.GetSession(m_userId, (DSLSession)this);
			if (TSessions.Count == 0)
				TSessions.AddTSessionsRow(m_userId, Guid.NewGuid(), 
					System.DateTime.Now, 0, 0);
		}

		public void Save()
		{
			try
			{
				if ( (TSessions[0].serverId == 0) || (TSessions[0].serverPortNo == 0) )
					throw new Exception("Please supply a valid server ID and port number before calling Save.");

				m_objDSLUtils.UpdateSession((DSLSession)this);
				AcceptChanges();
			}
			catch (Exception ex)
			{
				throw ex;
			}
		}
	}
}
