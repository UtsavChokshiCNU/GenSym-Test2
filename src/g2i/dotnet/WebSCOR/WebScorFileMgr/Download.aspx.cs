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
using System.IO;
using WebScorBSL;

namespace WebScorFileMgr
{
	/// <summary>
	/// Summary description for Download.
	/// </summary>
	public class Download : System.Web.UI.Page
	{
		protected System.Web.UI.WebControls.DataGrid dataGridInput;
		protected System.Web.UI.WebControls.Label lblMsg;
		protected System.Web.UI.WebControls.DataGrid dataGridOutput;

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
					BindFileDataToGrids("fileName");
				}
			}
			catch (Exception ex)
			{
				lblMsg.Visible = true;
				lblMsg.Text = ex.Message;
			}
		}

		private void BindInputFileData(string strSortField)
		{
			try 
			{		
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				BSLCompany objCompany = m_objUser.GetCompany();
				string strDataDirName = objCompany.TCompanies[0].rootDirName;
				string strInputDir = (string)Cache["G2_DATA_PATH"];
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					strDataDirName;
				string strOutputDir = strInputDir;
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					"Input";
				strOutputDir += (!strOutputDir.EndsWith("\\") ? "\\" : "") + 
					"Output";

				DirectoryInfo  myDirInfo;
				FileInfo[] arrFileInfo;
				DataRow myDataRow;
				DataView myDataView;

				//Populate Input Grid
				DataTable tblInputFiles = new DataTable();
				tblInputFiles.Columns.Add("fileName", Type.GetType("System.String"));
				tblInputFiles.Columns.Add("fileSize", Type.GetType("System.Int32"));
				tblInputFiles.Columns.Add("modifyDate", Type.GetType("System.DateTime"));
				tblInputFiles.Columns.Add("fileExt", Type.GetType("System.String"));
				myDirInfo = new DirectoryInfo(strInputDir);
				// You can easily filter results by name... I just want a list
				// of all the files, but you could filter here if you wanted.
				//arrFileInfo = myDirInfo.GetFiles("s*.*")
				arrFileInfo = myDirInfo.GetFiles();
				// Loop through array of FileInfo objects placing the data we'll
				// be using into our DataTable for easy manipulation.
				for(int i = 0; i < arrFileInfo.Length; i++)
				{
					FileInfo myFileInfo = arrFileInfo[i];
					myDataRow = tblInputFiles.NewRow();
					myDataRow["fileName"]= myFileInfo.Name;
					myDataRow["fileSize"] = myFileInfo.Length;
					myDataRow["modifyDate"] = myFileInfo.LastWriteTime;
					myDataRow["fileExt"] = myFileInfo.Extension;
					tblInputFiles.Rows.Add(myDataRow);
				}
				// Create a new DataView and sort it.
				myDataView = tblInputFiles.DefaultView;
				myDataView.Sort = strSortField;
				dataGridInput.DataSource = myDataView;
				dataGridInput.DataBind();
			}
			catch ( System.Exception ex ) 
			{ 
				lblMsg.Visible = true;
				lblMsg.Text = ex.Message;
			}
		}

		private void BindOutputFileData(string strSortField)
		{
			try 
			{		
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				BSLCompany objCompany = m_objUser.GetCompany();
				string strDataDirName = objCompany.TCompanies[0].rootDirName;
				string strInputDir = (string)Cache["G2_DATA_PATH"];
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					strDataDirName;
				string strOutputDir = strInputDir;
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					"Input";
				strOutputDir += (!strOutputDir.EndsWith("\\") ? "\\" : "") + 
					"Output";

				DirectoryInfo  myDirInfo;
				FileInfo[] arrFileInfo;
				DataRow myDataRow;
				DataView myDataView;
	
				//Populate Ouptut Grid
				DataTable tblOutputFiles = new DataTable();
				tblOutputFiles.Columns.Add("fileName", Type.GetType("System.String"));
				tblOutputFiles.Columns.Add("fileSize", Type.GetType("System.Int32"));
				tblOutputFiles.Columns.Add("modifyDate", Type.GetType("System.DateTime"));
				tblOutputFiles.Columns.Add("fileExt", Type.GetType("System.String"));
				myDirInfo = new DirectoryInfo(strOutputDir);
				arrFileInfo = myDirInfo.GetFiles();

				for(int i = 0; i < arrFileInfo.Length; i++)
				{
					FileInfo myFileInfo = arrFileInfo[i];
					myDataRow = tblOutputFiles.NewRow();
					myDataRow["fileName"]= myFileInfo.Name;
					myDataRow["fileSize"] = myFileInfo.Length;
					myDataRow["modifyDate"] = myFileInfo.LastWriteTime;
					myDataRow["fileExt"] = myFileInfo.Extension;
					tblOutputFiles.Rows.Add(myDataRow);
				}
				// Create a new DataView and sort it based on the field passed in.
				myDataView = tblOutputFiles.DefaultView;
				myDataView.Sort = strSortField;
				dataGridOutput.DataSource = myDataView;
				dataGridOutput.DataBind();				
			}
			catch ( System.Exception ex ) 
			{ 
				lblMsg.Visible = true;
				lblMsg.Text = ex.Message;
			}
		}

		private void BindFileDataToGrids(string strSortField )
		{
			BindInputFileData(strSortField);
			BindOutputFileData(strSortField);
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
			this.dataGridInput.ItemCommand += new System.Web.UI.WebControls.DataGridCommandEventHandler(this.OnInputItemCmd);
			this.dataGridInput.SortCommand += new System.Web.UI.WebControls.DataGridSortCommandEventHandler(this.OnInputSort);
			this.dataGridInput.ItemDataBound += new System.Web.UI.WebControls.DataGridItemEventHandler(this.OnItemDataBound);
			this.dataGridOutput.ItemCommand += new System.Web.UI.WebControls.DataGridCommandEventHandler(this.OnOutputItemCmd);
			this.dataGridOutput.SortCommand += new System.Web.UI.WebControls.DataGridSortCommandEventHandler(this.OnOutputSort);
			this.dataGridOutput.ItemDataBound += new System.Web.UI.WebControls.DataGridItemEventHandler(this.OnItemDataBound);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void OnInputSort(object source, System.Web.UI.WebControls.DataGridSortCommandEventArgs e)
		{
			BindInputFileData(e.SortExpression);
		}

		private void OnOutputSort(object source, System.Web.UI.WebControls.DataGridSortCommandEventArgs e)
		{
			BindOutputFileData(e.SortExpression);
		}

		private void OnInputItemCmd(object source, System.Web.UI.WebControls.DataGridCommandEventArgs e)
		{
			try
			{
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				BSLCompany objCompany = m_objUser.GetCompany();
				string strDataDirName = objCompany.TCompanies[0].rootDirName;
				string strInputDir = (string)Cache["G2_DATA_PATH"];
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					strDataDirName;
				string strOutputDir = strInputDir;
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					"Input";
				strOutputDir += (!strOutputDir.EndsWith("\\") ? "\\" : "") + 
					"Output";
			
				// added by pcp 8/15/05 to ensure the command is not executed when sorting the table for example
				if (!e.CommandName.ToLower().Equals("delete"))
					return;

				string strFileName = (string)e.CommandArgument;

				System.IO.File.Delete(strInputDir + "\\" + strFileName);

				if (!System.IO.File.Exists(strInputDir + "\\" + strFileName))
				{
					// pcp modified this 8/15/05 to include the filename that was deleted
					string strScript = "<script for='window' event='onload' language='javascript'>alert('File " + strFileName + " deleted successfully.');</script>";
					RegisterStartupScript("SuccessMsg", strScript);
				}
				else
					throw new Exception("File was not deleted.");

				BindInputFileData("fileName");
			}
			catch (Exception ex)
			{
				lblMsg.Visible = true;
				lblMsg.Text = "Error '" + ex.Message + "' occurred.";
			}
		}

		private void OnOutputItemCmd(object source, System.Web.UI.WebControls.DataGridCommandEventArgs e)
		{
			try
			{
				if (m_objUser == null)
					throw new Exception("Your session has expired.");

				BSLCompany objCompany = m_objUser.GetCompany();
				string strDataDirName = objCompany.TCompanies[0].rootDirName;
				string strInputDir = (string)Cache["G2_DATA_PATH"];
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					strDataDirName;
				string strOutputDir = strInputDir;
				strInputDir += (!strInputDir.EndsWith("\\") ? "\\" : "") + 
					"Input";
				strOutputDir += (!strOutputDir.EndsWith("\\") ? "\\" : "") + 
					"Output";
			
				// added by pcp 8/15/05 to ensure the command is not executed when sorting the table for example
				if (!e.CommandName.ToLower().Equals("delete"))
					return;

				string strFileName = (string)e.CommandArgument;

				System.IO.File.Delete(strOutputDir + "\\" + strFileName);

				if (!System.IO.File.Exists(strOutputDir + "\\" + strFileName))
				{
					// pcp modified this 8/15/05 to include the filename that was deleted
					string strScript = "<script for='window' event='onload' language='javascript'>alert('File " + strFileName + " deleted successfully.');</script>";
					RegisterStartupScript("SuccessMsg", strScript);
				}
				else
					throw new Exception("File was not deleted.");

				BindOutputFileData("fileName");
			}
			catch (Exception ex)
			{
				lblMsg.Visible = true;
				lblMsg.Text = "Error '" + ex.Message + "' occurred.";
			}
		}

		private void OnItemDataBound(object sender, System.Web.UI.WebControls.DataGridItemEventArgs e)
		{
			try
			{
				if ( (e.Item.ItemType != ListItemType.Item) && 
					(e.Item.ItemType != ListItemType.AlternatingItem) )
					return;

				DataRowView drv = (DataRowView)e.Item.DataItem;
				string strFileName = (string)drv["fileName"];

				System.Web.UI.WebControls.TableCell tc = e.Item.Cells[4];
				if (tc.Controls.Count > 1)
				{
					WebControl objBtn = (WebControl)tc.Controls[1];
					objBtn.Attributes.Add ("onclick", "return confirm(\"Are you sure you want to delete '" + strFileName + "'?\");");
					objBtn.Attributes.Add ("title", "Click to delete '" + strFileName + "'");
				}
			}
			catch (Exception ex)
			{
				lblMsg.Visible = true;
				lblMsg.Text = "Error '" + ex.Message + "' occurred.";
			}
		}
	}
}
