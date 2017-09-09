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
	/// Summary description for selectSession.
	/// </summary>
	public class selectSession : System.Web.UI.Page
	{
		protected System.Web.UI.WebControls.DataGrid dataGridServers;
		protected System.Web.UI.WebControls.Button btn_Refresh;
		private BSLUser m_objUser = null;

		private void Page_Load(object sender, System.EventArgs e)
		{
			try
			{
				m_objUser = (BSLUser)Session["objUser"];
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				if (m_objUser.TUsers[0].inactive)
					throw new Exception("Your account is inactive.");

				if (!IsPostBack)
				{
					//Initialize server list
					PopulateControls();
				}
			}
			catch (Exception ex)
			{
				Page.RegisterClientScriptBlock("errMsg", "<script for='window' event='onload' language='javascript'>alert(\"Error: " + ex.Message + " occurred.\");</script>");
			}
		}

		private void PopulateControls()
		{
			BindGrid();
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
			this.dataGridServers.ItemCommand += new System.Web.UI.WebControls.DataGridCommandEventHandler(this.OnGridItemCmd);
			this.btn_Refresh.Click += new System.EventHandler(this.OnRefresh);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void OnGridItemCmd(object source, System.Web.UI.WebControls.DataGridCommandEventArgs e)
		{
			string strCommand = e.CommandName;
			string coServerId = e.Item.Cells[1].Text;
			string strQuery = "sid="+coServerId;
			switch (strCommand.ToLower())
			{
				case "join":
				case "connect":
					Response.Redirect("launchTW.aspx?" + strQuery, true);
					break;
				default:
					return;
			}
		}

		private void BindGrid()
		{
			WebScorBSL.BSLCompanyServerList objServerList = m_objUser.GetUserServers();
			dataGridServers.DataSource = objServerList;
			dataGridServers.DataBind();
		}

		private void OnRefresh(object sender, System.EventArgs e)
		{
			BindGrid();
		}
	}
}
