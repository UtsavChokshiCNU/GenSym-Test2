using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLUser.
	/// </summary>
	public class BSLUser: DSLUser
	{
		private DSLUtils m_objDSLUtils = null;
		private BSLCompany m_objBSLCompany = null;
		private BSLSession m_objBSLSession = null;
		private string m_strConnStr;

		public BSLUser(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
			m_strConnStr = strConnStr;
		}

		public void Fill(int userId)
		{
			m_objDSLUtils.GetUser(userId, (DSLUser)this);
			if (this.TUsers.Count == 0)
				throw new Exception("Invalid user ID.");
		}

		public void Fill(string userName)
		{		
			m_objDSLUtils.GetUser(userName, (DSLUser)this);
			if (this.TUsers.Count == 0)
				throw new Exception("Invalid username.");
		}

		public void Fill(string userName, string password)
		{		
			m_objDSLUtils.GetUser(userName, password, (DSLUser)this);
			if (this.TUsers.Count == 0)
				throw new Exception("Invalid username or password.");
		}

		/*public static DSLUser GetUser(string userName, string password)
		{
			DSLUtils objDSLUtils = new DSLUtils();
			return objDSLUtils.GetUser(userName, password);
		}

		public static DSLUser GetUser(int userId)
		{
			DSLUtils objDSLUtils = new DSLUtils();
			return objDSLUtils.GetUser(userId);
		}*/

		public BSLCompany GetCompany()
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling GetCompany.");
			
			if (m_objBSLCompany == null)
			{
				m_objBSLCompany = new BSLCompany(m_strConnStr);
				m_objBSLCompany.Fill(this.TUsers[0].coId);
			}
			return m_objBSLCompany;
		}

		public BSLSession GetCurrentSession()
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling GetCurrentSession.");
			
			if (m_objBSLSession == null)
			{
				m_objBSLSession = new BSLSession(TUsers[0].userId, m_strConnStr);
				m_objBSLSession.Fill();
			}
			return m_objBSLSession;
		}

		public BSLCompanyServerList GetUserServers()
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling GetUserServers.");
			
			BSLCompanyServerList ds = GetCompany().GetCompanyServerList();

			foreach (DSLCompanyServer.TCompanyServersRow r in ds.TCompanyServers.Rows)
			{
				if (r.inactive)
				{
					r.Delete();
					continue;
				}

				BSLCompanyServer objCoServer = new BSLCompanyServer(r.serverId, r.serverName,
					r.ipAddress, this.TUsers[0].coId, r.portNo, m_strConnStr);
				
				if (!objCoServer.IsAvailable(this.TUsers[0].userName, this.TUsers[0].password))
					r.isRunning = false;
				else
					r.isRunning = true;

				if (objCoServer.GetNumCurrentUsers(this.TUsers[0].userName, this.TUsers[0].password) > 0)
					r.inUse = true;
			}

			ds.AcceptChanges();
			return ds;
		}

		public bool CanStartNewSession()
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling CanStartNewSession.");

			BSLCompany objCompany = GetCompany();
			short maxConcurrentSessions = objCompany.TCompanies[0].numConcurrentSessions;
			short numLicenses = objCompany.TCompanies[0].numLicenses;

			int numCurrentSessions = 0;
			int numCurrentUsers = 0;

			objCompany.GetCurrentSessionStats(TUsers[0].userName, TUsers[0].password, 
				ref numCurrentSessions, ref numCurrentUsers);

			if ( (numCurrentSessions >= maxConcurrentSessions) ||
				(numCurrentUsers >= numLicenses) )
				return false;

			return true;
		}

		public bool CanJoinExistingSession(int serverId, string strServerName, 
			string strIPAddress, int iPortNo)
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling CanJoinExistingSession.");

			BSLCompanyServer objCoServer = new BSLCompanyServer(serverId, strServerName,
				strIPAddress, this.TUsers[0].coId, iPortNo, m_strConnStr);

			return CanJoinExistingSession(objCoServer);
		}

		public bool CanJoinExistingSession(BSLCompanyServer objCoServer)
		{
			if (this.TUsers.Count == 0)
				throw new Exception("BSLUser must be populated before calling CanJoinExistingSession.");

			BSLCompany objCompany = GetCompany();
			short maxCollaborators = objCompany.TCompanies[0].numCollaborators;
			short numLicenses = objCompany.TCompanies[0].numLicenses;

			int numCurrentSessions = 0;
			int numCurrentUsers = 0;

			objCompany.GetCurrentSessionStats(TUsers[0].userName, TUsers[0].password, 
				ref numCurrentSessions, ref numCurrentUsers);

			if (numCurrentUsers >= numLicenses)
				return false;

			if (objCoServer.GetNumCurrentUsers(TUsers[0].userName, TUsers[0].password) >= maxCollaborators)
				return false;

			return true;
		}

		public bool IsClientAdmin
		{
			get
			{	
				if (this.TUsers[0].userRole >= 3)
					return true;
				else
					return false;
			}
		}

		public bool IsGensymAdmin
		{
			get
			{
				if (this.TUsers[0].userRole >= 4)
					return true;
				else
					return false;
			}
		}
	}
}
