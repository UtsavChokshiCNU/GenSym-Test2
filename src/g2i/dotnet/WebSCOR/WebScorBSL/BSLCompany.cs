using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLCompany.
	/// </summary>
	public class BSLCompany: DSLCompany
	{
		private DSLUtils m_objDSLUtils = null;
		private BSLCompanyServerList m_objCoServerList = null;
		private int m_companyId = 0;
		private string m_strConnStr = "";

		public BSLCompany(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
			m_strConnStr = strConnStr;
		}

		public void Fill(int companyId)
		{
			m_objDSLUtils.GetCompany(companyId, (DSLCompany)this);
			if (this.TCompanies.Count == 0)
				throw new Exception("Invalid company ID.");
			m_companyId = companyId;
		}

		public BSLCompanyServerList GetCompanyServerList()
		{
			if (m_objCoServerList == null)
			{
				m_objCoServerList = new BSLCompanyServerList(m_strConnStr);
				m_objCoServerList.Fill(m_companyId);
			}
			return m_objCoServerList;
		}

		public void GetCurrentSessionStats(string strUserName, string strPassword, 
			ref int numCurrentSessions, ref int numCurrentUsers)
		{
			if (this.TCompanies.Count == 0)
				throw new Exception("BSLCompany must be populated before calling GetCurrentSessionStats.");

			numCurrentSessions = 0;
			numCurrentUsers = 0;

			BSLCompanyServerList objCoServerList = GetCompanyServerList();

			foreach (BSLCompanyServer.TCompanyServersRow r in objCoServerList.TCompanyServers.Rows)
			{
				if (r.inactive)
					continue;

				BSLCompanyServer objCoServer = new BSLCompanyServer(r.serverId, r.serverName,
					r.ipAddress, TCompanies[0].coId, r.portNo, m_strConnStr);
				
				if (!objCoServer.IsAvailable(strUserName, strPassword))
					continue;

				short i = objCoServer.GetNumCurrentUsers(strUserName, strPassword);
				if (i > 0)
				{
					numCurrentSessions++;
					numCurrentUsers += i;
				}
			}
		}
	}
}
