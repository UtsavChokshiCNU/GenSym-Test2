using System;
using System.Collections;
using System.ComponentModel;
using System.Web;
using System.Web.SessionState;
using System.Configuration;
using System.Diagnostics;

namespace G2MgrWebSvc 
{
	/// <summary>
	/// Summary description for Global.
	/// </summary>
	public class Global : System.Web.HttpApplication
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		public Global()
		{
			InitializeComponent();
		}	
		
		protected void Application_Start(Object sender, EventArgs e)
		{
			string path = System.IO.Path.GetTempPath();
			path += (!path.EndsWith("\\") ? "\\" : "");

			Trace.Listeners.Add(new 
				TextWriterTraceListener(System.IO.File.Open(path + "G2MgrLog.txt", 
				System.IO.FileMode.Create, System.IO.FileAccess.ReadWrite, 
				System.IO.FileShare.ReadWrite)));
			Trace.WriteLine("");

			Context.Cache["CONN_STR"] = ConfigurationSettings.AppSettings["connString"];
			Context.Cache["G2_PATH"] = ConfigurationSettings.AppSettings["g2Path"];
			Context.Cache["OK_PATH"] = ConfigurationSettings.AppSettings["okPath"];
			Context.Cache["LOG_PATH"] = ConfigurationSettings.AppSettings["logPath"];
			Context.Cache["G2_DATA_PATH"] = ConfigurationSettings.AppSettings["g2DataPath"];
			Context.Cache["G2_KB"] = ConfigurationSettings.AppSettings["g2KB"];
			Application["m_sessionList"] = new Hashtable(4);
		}
 
		protected void Session_Start(Object sender, EventArgs e)
		{

		}

		protected void Application_BeginRequest(Object sender, EventArgs e)
		{

		}

		protected void Application_EndRequest(Object sender, EventArgs e)
		{

		}

		protected void Application_AuthenticateRequest(Object sender, EventArgs e)
		{

		}

		protected void Application_Error(Object sender, EventArgs e)
		{

		}

		protected void Session_End(Object sender, EventArgs e)
		{

		}

		protected void Application_End(Object sender, EventArgs e)
		{
			Trace.Close();

			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			foreach (object o in sessionList.Keys)
			{
				System.Diagnostics.Process p = 
					(System.Diagnostics.Process)sessionList[o];
				if ( (p != null) && (!p.HasExited) )
				{
					try
					{
						p.Kill();
					}
					catch(Exception ex) {}
				}
			}
		}
			
		#region Web Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.components = new System.ComponentModel.Container();
		}
		#endregion
	}
}

