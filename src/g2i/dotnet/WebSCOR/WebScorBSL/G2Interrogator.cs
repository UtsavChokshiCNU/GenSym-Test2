using System;
using System.Net;
using System.Net.Sockets;
using System.Xml;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for G2Interrogator.
	/// </summary>
	public class G2Interrogator
	{
		private WebScorBSL.G2Mgr.G2Manager m_objMgr = null; 
		private string m_strUserName = "";
		private string m_strPassword = "";
		private string m_strServerName = "";
		private int m_portNo = 0;

		public G2Interrogator(string strUserName, string strPassword, 
			string strServerName, int portNo)
		{
			m_objMgr = new WebScorBSL.G2Mgr.G2Manager();
			m_objMgr.Url = "http://" + strServerName + "/G2MgrWebSvc/G2Mgr.asmx";
			m_strUserName = strUserName;
			m_strPassword = strPassword;
			m_strServerName = strServerName;
			m_portNo = portNo;
		}

		public bool Ping()
		{
			try
			{
				TcpClient objClient = new TcpClient();
				objClient.LingerState.Enabled = false;
				objClient.LingerState.LingerTime = 0;
				objClient.Connect(m_strServerName, m_portNo);
				objClient.GetStream().Close();
				objClient.Close();
				return true;
			}
			catch (Exception ex)
			{
				return false;
			}
		}

		private void GetMethodResult(string s, ref int errCode, ref string strResult)
		{
			DSResponse objResponse = new DSResponse();
			XmlDataDocument objXDoc = new XmlDataDocument(objResponse);
			objXDoc.LoadXml(s);
			errCode = objResponse.G2MgrResponse[0].errorCode;
			strResult = objResponse.G2MgrResponse[0].results;
		}

		public bool IsG2Running()
		{
			string s = m_objMgr.IsG2Running(m_strUserName, m_strPassword, m_portNo);
			int errCode = -1;
			string strResult = "";
			GetMethodResult(s, ref errCode, ref strResult);

			if (errCode != 0)
				return false;
				
			if (!strResult.Equals("true"))
				return false;

			return true;
		}

		public bool InUseByCompany(int companyId)
		{
			string s = m_objMgr.GetG2CompanyId(m_strUserName, m_strPassword, m_portNo);
			int errCode = -1;
			string strResult = "";
			GetMethodResult(s, ref errCode, ref strResult);
			
			if (errCode != 0)
				return false;
			
			if (int.Parse(strResult) != companyId)
				return false; 

			return true;
		}

		public bool StartServer()
		{
			string s = m_objMgr.StartG2(m_strUserName, m_strPassword, m_portNo);
			int errCode = -1;
			string strResult = "";
			GetMethodResult(s, ref errCode, ref strResult);

			if (errCode != 0)
				return false;
				
			return true;
		}

		public short GetNumUsers(int companyId)
		{
			string strResult = "";
			//SendData("NUMUSERS:" + companyId, ref strResult);
			//if (strResult.Equals("TRUE"))
			return 0;
		}
	}
}
