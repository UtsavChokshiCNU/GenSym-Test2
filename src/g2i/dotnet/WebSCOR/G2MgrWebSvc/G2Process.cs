using System;
using System.Diagnostics;

namespace G2MgrWebSvc
{
	/// <summary>
	/// Summary description for G2Process.
	/// </summary>
	public class G2Process : Process
	{
		private int m_companyId = 0;
		private int m_portNo = 0;

		public G2Process()
		{
		}

		public G2Process(int coId, int portNo) : base()
		{
			m_companyId = coId;
			m_portNo = portNo;
		}

		public int companyId
		{
			get { return m_companyId; }
			//set { m_companyId = value; }
		}

		public int portNo
		{
			get { return m_portNo; }
			//set { m_portNo = value; }
		}

		public string ToXML()
		{
			string strRetVal = "<G2Process>";
			strRetVal += "<processId>" + this.Id + "</processId>";
			strRetVal += "<portNo>" + m_portNo + "</portNo>";
			strRetVal += "<companyId>" + m_companyId + "</companyId>";
			strRetVal += "<startTime>" + this.StartTime.ToString("MM dd, yyyy HH:mm") + "</startTime>";
			strRetVal += "</G2Process>";
			return strRetVal;
		}
	}
}
