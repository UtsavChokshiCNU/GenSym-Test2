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
	/// Summary description for WebForm1.
	/// </summary>
	public class WebForm1 : System.Web.UI.Page
	{
		protected System.Web.UI.WebControls.TextBox txt_UserName;
		protected System.Web.UI.WebControls.TextBox txt_Password;
		protected System.Web.UI.WebControls.ValidationSummary ValidationSummary1;
		protected System.Web.UI.WebControls.RequiredFieldValidator userNameValidator;
		protected System.Web.UI.WebControls.RequiredFieldValidator passwordValidator;
		protected System.Web.UI.WebControls.Button btn_Login;

		private void Page_Load(object sender, System.EventArgs e)
		{
			//TWOnlineHeader hdr = (TWOnlineHeader)FindControl("main_header1");

			if (!IsPostBack)
			{
				Session["objUser"] = null;
				System.Web.HttpBrowserCapabilities objBrowsCap = 
					Request.Browser;
				if (!objBrowsCap.ActiveXControls)
				{
					string strScript = "<script language='javascript'>alert('Your browser does not support ActiveX controls.');</script>";
					RegisterStartupScript("NoActiveXSupport", strScript);
					this.btn_Login.Enabled = false;
				}
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
			this.btn_Login.Click += new System.EventHandler(this.btn_Login_Click);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void btn_Login_Click(object sender, System.EventArgs e)
		{
			BSLUser objUser = new BSLUser((string)Cache["CONN_STR"]);
			try
			{
				objUser.Fill(txt_UserName.Text, txt_Password.Text);
				if (objUser.TUsers[0].inactive)
					throw new Exception("User account is inactive.");
				Session["objUser"] = objUser;
				Response.Redirect("selectSession.aspx", true);
				//Server.Transfer(...);
			}
			catch (Exception ex)
			{
				this.userNameValidator.ErrorMessage = ex.Message;
				this.userNameValidator.IsValid = false;
			}
		}
	}
}
