namespace TWOnline
{
	using System;
	using System.Data;
	using System.Drawing;
	using System.Web;
	using System.Web.UI.WebControls;
	using System.Web.UI.HtmlControls;
	using WebScorBSL;

	/// <summary>
	///		Summary description for TWOnlineHeader.
	/// </summary>
	public class TWOnlineHeader : System.Web.UI.UserControl
	{
		protected System.Web.UI.WebControls.HyperLink link_Login;
		protected System.Web.UI.WebControls.HyperLink link_Admin;
		protected System.Web.UI.WebControls.Label separator1;
		protected System.Web.UI.WebControls.HyperLink link_StartSession;
		protected System.Web.UI.WebControls.Label separator2;
		protected System.Web.UI.WebControls.Label label_Welcome;
		private string m_pageName = "";

		public string pageName
		{
			set { m_pageName = value; }
		}

		private void Page_Load(object sender, System.EventArgs e)
		{
			if (m_pageName.ToLower().Equals("login.aspx"))
			{
				link_Login.NavigateUrl = "";
			}
			else
			{
				BSLUser objUser = (BSLUser)Session["objUser"];

				//Set link visibility
				link_StartSession.Visible = true;
				separator1.Visible = true;

				if (objUser.TUsers[0].userRole >= 4)
				{
					link_Admin.Visible = true;
					separator2.Visible = true;
				}

				//Set Navigation URLs
				if (m_pageName.ToLower().Equals("selectsession.aspx"))
					link_StartSession.NavigateUrl = "";

				if (m_pageName.ToLower().Equals("admin.aspx"))
					link_Admin.NavigateUrl = "";
				
				//Set welcome label
				label_Welcome.Visible = true;
				label_Welcome.Text = "Welcome, " + objUser.TUsers[0].firstName + " " + 
					objUser.TUsers[0].lastName;
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
		///		Required method for Designer support - do not modify
		///		the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion
	}
}
