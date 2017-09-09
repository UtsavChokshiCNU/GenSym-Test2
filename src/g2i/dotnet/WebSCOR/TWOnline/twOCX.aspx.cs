using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using WebScorBSL;

namespace TWOnline
{
	/// <summary>
	/// Summary description for twOCX.
	/// </summary>
	public class twOCX : System.Web.UI.Page
	{
		protected string m_serverName = "";
		protected string m_portNo = "";
		protected string m_userName = "";
		protected string m_password = "";
		protected string m_sessionId = "";
		protected string m_userMode = "";
		protected string m_codeBase = "";
		protected string m_classId = "";

		private void Page_Load(object sender, System.EventArgs e)
		{
			BSLUser objUser = (BSLUser)Session["objUser"];
			if (objUser == null)
				return;
	
			string strCoServerId = Request["sid"];
			if ( (strCoServerId == null) || (strCoServerId.Length == 0) )
				return;

			m_codeBase = (string)Cache["OCX_CODE_BASE"];
			m_classId = (string)Cache["OCX_CLASS_ID"];

			try
			{
				int coServerId = int.Parse(strCoServerId);
				BSLCompanyServer objCoServer = new BSLCompanyServer((string)Cache["CONN_STR"]);
				objCoServer.Fill(coServerId);
				int serverId = objCoServer.TCompanyServers[0].serverId;
//				m_serverName = objCoServer.TCompanyServers[0].serverName;
				m_serverName = objCoServer.TCompanyServers[0].ipAddress.ToString();
				
				int portNo = objCoServer.TCompanyServers[0].portNo;
				m_portNo = portNo.ToString();
				
				m_userName = objUser.TUsers[0].userName;

				BSLSession objSession = objUser.GetCurrentSession();
				objSession.Refresh(serverId, portNo); 
				objSession.Save();

				m_sessionId = objSession.TSessions[0].sessionGuid.ToString();

//				string strTempPwd = objUser.TUsers[0].password;
//				DateTime dt = objSession.TSessions[0].loginDate;
//				strTempPwd += dt.ToLongTimeString();
//				byte[] data = System.Text.Encoding.ASCII.GetBytes(strTempPwd.ToCharArray());
//				System.Security.Cryptography.SHA1CryptoServiceProvider sha = 
//					new System.Security.Cryptography.SHA1CryptoServiceProvider(); 
//				byte[] result = sha.ComputeHash(data);
//				m_password = System.Text.Encoding.ASCII.GetString(result);
				m_password = objUser.TUsers[0].password;
				m_userMode = objUser.TUsers[0].userMode;


				String connectString = m_serverName + ":" + m_portNo;
/*
				G2iControl g2iControl = new G2iControl();
				g2iControl.Connect(connectString);

				g2iControl.ServerLoginSetup(m_userName, m_sessionId);

				g2iControl.Disconnect();
				g2iControl = null;
*/
			}
			catch(Exception ex)
			{
				m_serverName = "";
				m_portNo = "";
				m_userName = "";
				m_password = "";
				m_sessionId = "";
				m_userMode = "";
				RegisterStartupScript("LaunchErr", "<script language='javascript'>parent.displayError('" + ex.Message + "');</script>");
				Response.End();
				return;
			}
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion
	}
}
