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
	/// Summary description for launchTW.
	/// </summary>
	public class launchTW : System.Web.UI.Page
	{
		protected string m_coServerId = "";

		private void Page_Load(object sender, System.EventArgs e)
		{
			try
			{
				BSLUser objUser = (BSLUser)Session["objUser"];
				if (objUser == null)
					throw new Exception("Your session has expired.");
				if (objUser.TUsers[0].inactive)
					throw new Exception("Your account is inactive.");
				objUser = null;

				string m_coServerId = Request["sid"];
				if ( (m_coServerId == null) || (m_coServerId.Length == 0) )
					throw new Exception("Invalid server ID supplied.");

				string strScript = "<script language='javascript'>function onBodyLoad(){document.all['frmcab'].src = 'twOCX.aspx?sid=" + m_coServerId + "';}</script>";
				RegisterStartupScript("populateIFrame", strScript);
			}
			catch (Exception ex)
			{
				Page.RegisterClientScriptBlock("errMsg", "<script for='window' event='onload' language='javascript'>alert(\"Error: " + ex.Message + " occurred.\");</script>");
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
