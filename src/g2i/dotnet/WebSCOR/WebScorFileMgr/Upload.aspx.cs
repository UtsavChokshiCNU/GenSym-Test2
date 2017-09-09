using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;
using WebScorBSL;

namespace WebScorFileMgr
{
	/// <summary>
	/// Summary description for Upload.
	/// </summary>
	public class Upload : System.Web.UI.Page
	{
		protected System.Web.UI.HtmlControls.HtmlInputFile file1;
		protected System.Web.UI.WebControls.Button btn_Upload;
		protected System.Web.UI.WebControls.RequiredFieldValidator FilenameValidator;
		protected System.Web.UI.WebControls.RequiredFieldValidator filenameValidator;
		protected System.Web.UI.WebControls.Label lblMsg;

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
			}
			catch (Exception ex)
			{
				lblMsg.Visible = true;
				lblMsg.Text = ex.Message;
				btn_Upload.Enabled = false;
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
			this.btn_Upload.Click += new System.EventHandler(this.OnUpload);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void OnUpload(object sender, System.EventArgs e)
		{		
			try 
			{		
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				System.Web.HttpFileCollection uploadedFiles = Request.Files;
				BSLCompany objCompany = m_objUser.GetCompany();
				string strDataDirName = objCompany.TCompanies[0].rootDirName;
				string strInputDir = (string)Cache["G2_DATA_PATH"];
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					strDataDirName;
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					"Input";

				for (int i = 0; i < uploadedFiles.Count; i++)
				{
					System.Web.HttpPostedFile postedFile = uploadedFiles[i];
					string strFileName = System.IO.Path.GetFileName(postedFile.FileName);
					postedFile.SaveAs(strInputDir + "\\" + strFileName);
				}
				string strScript = "<script for='window' event='onload' language='javascript'>alert('File(s) uploaded successfully.');</script>";
				RegisterStartupScript("SuccessMsg", strScript);
			}
			catch (Exception ex) 
			{ 
				lblMsg.Visible = true;
				lblMsg.Text = ex.Message;
			}
		}
	}
}
