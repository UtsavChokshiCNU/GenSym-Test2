using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Web;
using System.Web.Services;
using WebScorBSL;

namespace G2MgrWebSvc
{
	/// <summary>
	/// Summary description for G2Mgr.
	/// </summary>
	[WebService(Namespace="http://www.escor.com/webservices",
		 Description="G2 Manager Web Service",
		 Name="G2 Manager")]
	public class G2Mgr : System.Web.Services.WebService
	{
		public G2Mgr()
		{
			//CODEGEN: This call is required by the ASP.NET Web Services Designer
			InitializeComponent();
		}

		#region Component Designer generated code
		
		//Required by the Web Services Designer 
		private IContainer components = null;
				
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if(disposing && components != null)
			{
				components.Dispose();
			}
			base.Dispose(disposing);		
		}
		
		#endregion

		//[WebMethod(Description="Retrieves list of active servers.", CacheDuration=60)]
		private string GetName()
		{
			string s = (string)Application["m_strName"];
			if (s == null)
				return "";
			else
				return s;
		}
		
		private BSLUser GetUser(string strUserName, string strPassword, ref string strErrMsg)
		{
			//Retrieve application constants
			string strConnStr = (string)Context.Cache["CONN_STR"];

			//Attempt to retrieve user from database
			BSLUser objUser = new BSLUser(strConnStr);
			try
			{
				objUser.Fill(strUserName, strPassword);
				return objUser;
			}
			catch (Exception ex)
			{
				strErrMsg = ex.Message;
				LogMsg("GetUser: " + ex.Message); 
				return null;
			}
		}

		private void LogMsg(string strMsg)
		{
			Trace.WriteLine(System.DateTime.Now.ToShortDateString() + 
				" " + DateTime.Now.ToShortTimeString() + ": " + strMsg); 
			Trace.Flush();
		}

		[WebMethod(Description="Starts G2 on specified port using ok file, log file, and data directory of supplied user.")]
		public string StartG2(string strUserName, string strPassword, int portNo)
		{
			LogMsg("StartG2: StartG2 called.");
			DSResponse response = new DSResponse();

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			LogMsg("StartG2: Successfully retrieved user."); 

			BSLCompany objCompany = objUser.GetCompany();
			
			LogMsg("StartG2: Successfully retrieved user's company."); 

			LogMsg("StartG2: About to call ShellG2."); 

			if (!ShellG2(portNo, objCompany, ref strErrMsg))
			{
				LogMsg("StartG2: " + strErrMsg + " occured in ShellG2."); 
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			LogMsg("StartG2: Successfully Shelled G2."); 

			response.G2MgrResponse.AddG2MgrResponseRow("Started", "", 0);
			return response.GetXml();

			//			XmlDocument xDoc = new XmlDocument();
			//			xDoc.LoadXml(response.GetXml());
			//			NameTable nt = new NameTable();
			//			XmlNamespaceManager nsmgr = new XmlNamespaceManager(nt);
			//			nsmgr.AddNamespace("dsresponse", "http://tempuri.org/DSResponse.xsd"); 
			//			XmlNode nodeErrCode = xDoc.DocumentElement.SelectSingleNode("//dsresponse:errorCode", nsmgr);
			//			if (nodeErrCode.InnerText.Equals("0"))
			//			{
			//				try
			//				{
			//					XmlNode nodeResults = xDoc.DocumentElement.SelectSingleNode("//dsresponse:results", nsmgr);
			//					if (nodeResults != null)
			//					{
			//						string s = nodeResults.InnerText;
			//						DSUser ds2 = new DSUser();
			//						System.Xml.XmlDataDocument xDataDoc = new XmlDataDocument(ds2);
			//						xDataDoc.LoadXml(s);
			//						if (ds2.TUsers.Count > 0)
			//							s = ds2.TUsers[0].firstName;
			//					}
			//				}
			//				catch(Exception ex)
			//				{
			//				}
			//			}
		}
		
		[WebMethod(Description="Starts G2 on specified port using ok file, log file, and data directory of supplied user.", 
			 MessageName="StartG2Admin")]
		public string StartG2(string strUserName, string strPassword, int portNo, int companyId)
		{
			DSResponse response = new DSResponse();

			//Retrieve application constants
			/*string strG2Path = (string)Context.Cache["G2_PATH"];
			string strOKPath = (string)Context.Cache["OK_PATH"];
			string strLogPath = (string)Context.Cache["LOG_PATH"];
			string strG2DataPath = (string)Context.Cache["G2_DATA_PATH"];*/
			string strConnStr = (string)Context.Cache["CONN_STR"];

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			if (!objUser.IsGensymAdmin)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", 
					"Method reserved for internal use.", 1);
				return response.GetXml();
			}
			
			BSLCompany objCompany = new BSLCompany(strConnStr);
			try
			{
				objCompany.Fill(companyId);
			}
			catch(Exception ex)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", ex.Message, 1);
				LogMsg("StartG2: " + ex.Message); 
				return response.GetXml();
			}

			try
			{
				if (!ShellG2(portNo, objCompany, ref strErrMsg))
				{
					response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
					return response.GetXml();
				}
			}
			catch(Exception ex)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", ex.Message, 1);
				LogMsg("Start G2: " + ex.Message); 
				return response.GetXml();
			}			

			response.G2MgrResponse.AddG2MgrResponseRow("Started", "", 0);
			return response.GetXml();
		}

		private bool ShellG2(int portNo, BSLCompany objCompany, ref string strErrMsg)
		{
			LogMsg("ShellG2: ShellG2 called."); 
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];

			//Retrieve application constants
			string strG2Path = (string)Context.Cache["G2_PATH"];
			string strOKPath = (string)Context.Cache["OK_PATH"];
			string strLogPath = (string)Context.Cache["LOG_PATH"];
			string strG2DataPath = (string)Context.Cache["G2_DATA_PATH"];
			string strG2KB = (string)Context.Cache["G2_KB"];
			//string strConnStr = (string)Context.Cache["CONN_STR"];

			LogMsg("ShellG2: Retrieved application constants."); 

			//Retrieve company-specific data from database.
			string strOKFileName = objCompany.TCompanies[0].okFileName;
			string strLogFileName = objCompany.TCompanies[0].logFileName;
			string strDataDirName = objCompany.TCompanies[0].rootDirName;

			string strRootDir = strG2DataPath + (!strG2DataPath.EndsWith("\\") ? "\\" : "") + 
				strDataDirName;

			LogMsg("ShellG2: Read company-specific data."); 

			//Build G2 command line arguments
			string strArgs = "-tcpport " + portNo + " -tcpipexact";
			//strArgs += " -ok \"" + strOKPath + (!strOKPath.EndsWith("\\") ? "\\" : "") + strOKFileName + "\"";
			strArgs += " -log \"" + strLogPath + (!strLogPath.EndsWith("\\") ? "\\" : "") + strLogFileName + "\"";
			strArgs += " -root-dir \"" + strRootDir + "\"";
			strArgs += " -kb \"" + strG2KB + "\"";
			strArgs += " -nowindow";

			try
			{
				ProcessStartInfo si = new ProcessStartInfo();
				si.FileName = "\"" + strG2Path + (!strG2Path.EndsWith("\\") ? "\\" : "") + "g2.exe\""; // "g2.exe\""; // "start-g2.bat\""
				si.WorkingDirectory = strG2Path; 
				si.Arguments = strArgs;

				LogMsg("ShellG2: Process command line: " + si.FileName); 

				LogMsg("ShellG2: Process command line args: " + strArgs); 

				LogMsg("ShellG2: Process Working Dir: " + si.WorkingDirectory); 

				si.WindowStyle = ProcessWindowStyle.Normal;
				si.UseShellExecute = false;
				si.EnvironmentVariables.Add("G2_OK", strOKPath + (!strOKPath.EndsWith("\\") ? "\\" : "") + strOKFileName);
				/*
				si.EnvironmentVariables.Add("G2_MODULE_SEARCH_PATH",
					" '%SITE_%' '%G2IHOME_%\sites\Optegrity\kbs'
				'%G2IHOME_%\sites\e-SCOR\kbs' '%G2IHOME_%\sites\ReThink\kbs'
				'%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' '%G2HOME_%\g2\kbs\utils'
				'%G2HOME_%\activexlink' '%G2HOME_%\odbc' '%G2HOME_%\pi'
				'%G2HOME_%\opclink\kbs' '%G2HOME_%\protools\kbs' '%G2HOME_%\gw'
				'%G2HOME_%\corbalink\kbs' '%G2HOME_%\javalink\kbs' '%G2HOME_%\tw2\kbs' "
				set G2_MODULE_SEARCH_PATH=" '%G2IHOME_%\sites\Optegrity\kbs'
				'%G2IHOME_%\sites\e-SCOR\kbs' '%G2IHOME_%\sites\ReThink\kbs'
				'%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' 'C:\bt\kbs'
				'%G2HOME_%\activexlink\kbs' '%G2HOME_%\odbc\kbs' '%G2HOME_%\pi'
				'%G2HOME_%\opclink\kbs' '%G2HOME_%\jmail\kbs' '%G2HOME_%\jms\kbs'
				'%G2HOME_%\protools\kbs' '%G2HOME_%\gw' '%G2HOME_%\corbalink\kbs'
				'%G2HOME_%\javalink\kbs' '%G2HOME_%\tw2\kbs' '%G2HOME_%\g2\kbs\utils'
				'%G2HOME_%\g2\kbs\demos' " />
				 */
				
				G2Process p = new G2Process(objCompany.TCompanies[0].coId, portNo);
				p.StartInfo = si;
				p.Exited += new EventHandler(p_Exited);
				p.EnableRaisingEvents = true;
				//p.SynchronizingObject = this.Contain;

				LogMsg("ShellG2: Calling Start."); 
				if (!p.Start())
				{
					LogMsg("ShellG2: Process failed to start."); 
					strErrMsg = "Process failed to start.";
					return false;
				}

				LogMsg("ShellG2: Calling WaitForInputIdle."); 
				p.WaitForInputIdle(20000);
				LogMsg("ShellG2: Adding process to list."); 
				sessionList.Add(portNo, p);
				LogMsg("ShellG2: Saving list."); 
				Application["m_sessionList"] = sessionList;
				LogMsg("ShellG2: Returning 'true'."); 
				return true;
			}
			catch(Exception ex)
			{
				strErrMsg = ex.Message;
				LogMsg("ShellG2: " + ex.Message); 
				return false;
			}
		}

		[WebMethod(Description="Stops G2 process running on specified port.")]
		public string StopG2(string strUserName, string strPassword, int portNo)
		{
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			DSResponse response = new DSResponse();

			//Retrieve application constants
			//string strConnStr = (string)Context.Cache["CONN_STR"];

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			if (!objUser.IsGensymAdmin)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", 
					"Method reserved for internal use.", 1);
				return response.GetXml();
			}

			G2Process p = (G2Process)sessionList[portNo];
			if (p == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("Stopped", "", 0);
				return response.GetXml();
			}

			/*BSLCompany objCompany = objUser.GetCompany();
			if (p.companyId != objCompany.TCompanies[0].coId)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", 
					"Process wasn't running under user's company Id.", 1);
				return response.GetXml();
			}*/

			if (p.HasExited)
			{
				sessionList.Remove(portNo);
				Application["m_sessionList"] = sessionList;
				response.G2MgrResponse.AddG2MgrResponseRow("Stopped", "", 0);
				return response.GetXml();
			}

			try
			{
				p.Kill();
				sessionList.Remove(portNo);
				Application["m_sessionList"] = sessionList;
				response.G2MgrResponse.AddG2MgrResponseRow("Stopped", "", 0);
			}
			catch(Exception ex)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", ex.Message, 1);
				LogMsg("StopG2 " + ex.Message); 
			}

			return response.GetXml();
		}

		[WebMethod(Description="Determines whether G2 process is running on specified port.")]
		public string IsG2Running(string strUserName, string strPassword, int portNo)
		{
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			DSResponse response = new DSResponse();

			//Retrieve application constants
			//string strConnStr = (string)Context.Cache["CONN_STR"];

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			G2Process p = (G2Process)sessionList[portNo];
			if ( (p == null) || (p.HasExited) )
				response.G2MgrResponse.AddG2MgrResponseRow("false", "", 0);
			else
				response.G2MgrResponse.AddG2MgrResponseRow("true", "", 0);

			return response.GetXml();
		}

		[WebMethod(Description="Returns attributes of G2 process running on specified port.")]
		public string GetG2CompanyId(string strUserName, string strPassword, int portNo)
		{
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			DSResponse response = new DSResponse();

			//Retrieve application constants
			string strConnStr = (string)Context.Cache["CONN_STR"];

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			G2Process p = (G2Process)sessionList[portNo];
			if ( (p == null) || (p.HasExited) )
				response.G2MgrResponse.AddG2MgrResponseRow("", "G2 is not running on specified port.", 1);
			else
				response.G2MgrResponse.AddG2MgrResponseRow(p.companyId.ToString(), "", 0);

			return response.GetXml();
		}
		
		[WebMethod(Description="Stops all running G2 processes.")]
		public string StopAll(string strUserName, string strPassword)
		{
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			DSResponse response = new DSResponse();

			//Retrieve application constants
			string strConnStr = (string)Context.Cache["CONN_STR"];

			string strErrMsg = "";
			BSLUser objUser = GetUser(strUserName, strPassword, ref strErrMsg);
			if (objUser == null)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", strErrMsg, 1);
				return response.GetXml();
			}

			if (!objUser.IsGensymAdmin)
			{
				response.G2MgrResponse.AddG2MgrResponseRow("", 
					"Method reserved for internal use.", 1);
				return response.GetXml();
			}

			foreach (object o in sessionList.Keys)
			{
				G2Process p = (G2Process)sessionList[o];
				if ( (p != null) && (!p.HasExited) )
				{
					try
					{
						p.Kill();
					}
					catch(Exception ex) {}
				}
			}
			
			sessionList.Clear();
			Application["m_sessionList"] = sessionList;

			response.G2MgrResponse.AddG2MgrResponseRow("Stopped all.", "", 0);
			return response.GetXml();
		}

		private void p_Exited(object sender, EventArgs e)
		{
			Hashtable sessionList = (Hashtable)Application["m_sessionList"];
			G2Process p = (G2Process)sender;
			int portNo = p.portNo;
			if (sessionList.Contains(portNo))
			{
				sessionList.Remove(portNo);
				Application["m_sessionList"] = sessionList;
			}
		}
	}
}
