using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLCompanyServerList.
	/// </summary>
	public class BSLCompanyServerList: DSLCompanyServer
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLCompanyServerList(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public void Fill(int companyId)
		{
			m_objDSLUtils.GetCompanyServerList(companyId, (DSLCompanyServer)this);
		}
	}
}
