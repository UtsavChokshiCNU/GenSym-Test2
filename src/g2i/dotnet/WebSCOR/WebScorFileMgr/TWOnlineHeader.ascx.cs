namespace WebScorFileMgr
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
		protected System.Web.UI.WebControls.Label separator2;
		protected System.Web.UI.WebControls.Label label_Welcome;
		protected System.Web.UI.WebControls.HyperLink link_Upload;
		protected System.Web.UI.WebControls.HyperLink link_Download;
		private string m_pageName = "";

		public string pageName
		{
			set { m_pageName = value; }
		}

		public void setError(string strURL)
		{
			link_Upload.NavigateUrl = strURL;
			link_Download.NavigateUrl = strURL;
		}

		private void Page_Load(object sender, System.EventArgs e)
		{
			BSLUser objUser = (BSLUser)Session["objUser"];

			//Set link visibility
			link_Upload.Visible = true;
			link_Download.Visible = true;
			separator2.Visible = true;

			//Set Navigation URLs
			if (m_pageName.ToLower().Equals("upload.aspx"))
				link_Upload.NavigateUrl = "";

			if (m_pageName.ToLower().Equals("download.aspx"))
				link_Download.NavigateUrl = "";
			
			//Set welcome label
			label_Welcome.Visible = true;
			if (objUser != null)
				label_Welcome.Text = "Welcome, " + objUser.TUsers[0].firstName + " " + 
					objUser.TUsers[0].lastName;
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
