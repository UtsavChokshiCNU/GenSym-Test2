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

namespace WebScorFileMgr
{
	/// <summary>
	/// Summary description for download.
	/// </summary>
	public class GetFile : System.Web.UI.Page
	{
		private void Page_Load(object sender, System.EventArgs e)
		{
			BSLUser objUser = (BSLUser)Session["objUser"];
			if ( (objUser == null) || (objUser.TUsers[0].inactive) )
				return;

			string strDir = Request["d"];
			if ( (strDir == null) || (strDir.Length == 0) )
				return;

			string strFilename = Request["f"];
			if ( (strFilename == null) || (strFilename.Length == 0) )
				return;

			BSLCompany objCompany = objUser.GetCompany();
			string strDataDirName = objCompany.TCompanies[0].rootDirName;
			string strInputDir = (string)Cache["G2_DATA_PATH"];
			strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
				strDataDirName;
			string strOutputDir = strInputDir;
			strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
				"Input";
			strOutputDir += (!strOutputDir.EndsWith("\\") ? "\\" : "") + 
				"Output";
			
			string strSourceDir = "";
			if (strDir.ToLower().Equals("i"))
				strSourceDir = strInputDir;
			else if (strDir.ToLower().Equals("o"))
				strSourceDir = strOutputDir;
			else
				return;

			Response.Clear();
			Response.AddHeader("content-disposition", "attachment; filename=" + strFilename);
			Response.ContentType = "application/download"; //"application/octet-stream"
			string filename = strSourceDir + "\\" + strFilename;
			System.IO.FileStream downloadFile = new System.IO.FileStream(filename, 
				System.IO.FileMode.Open, System.IO.FileAccess.Read, System.IO.FileShare.Read);
			byte[] byteArray = new byte[(int)downloadFile.Length];
			downloadFile.Read(byteArray, 0, (int)downloadFile.Length);
			downloadFile.Close();
			Response.BinaryWrite(byteArray);
			Response.Flush();
			Response.End();
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
