using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLCompanyList.
	/// </summary>
	public class BSLCompanyList: DSLCompany
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLCompanyList(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public void Fill()
		{
			m_objDSLUtils.GetCompanyList((DSLCompany)this);
		}
	}
}
