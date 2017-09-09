using System;
using WebScorDSL;

namespace WebScorBSL
{
	/// <summary>
	/// Summary description for BSLUserList.
	/// </summary>
	public class BSLUserList: DSLUser
	{
		private DSLUtils m_objDSLUtils = null;

		public BSLUserList(string strConnStr): base()
		{
			m_objDSLUtils = new DSLUtils(strConnStr);
		}

		public void Fill()
		{
			m_objDSLUtils.GetUserList((DSLUser)this);
		}

//		public void Fill(int companyId)
//		{
//			m_objDSLUtils.GetUserList(companyId, (DSLUser)this);
//		}
	}
}
