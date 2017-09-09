using System;
using System.ComponentModel;
using System.Collections;
using System.Diagnostics;

namespace WebScorDSL
{
	/// <summary>
	/// Summary description for DSLUtils.
	/// </summary>
	public class DSLUtils : System.ComponentModel.Component
	{
		private System.Data.SqlClient.SqlCommand sqlSelectCommand1;
		private System.Data.SqlClient.SqlCommand sqlInsertCommand1;
		private System.Data.SqlClient.SqlCommand sqlUpdateCommand1;
		private System.Data.SqlClient.SqlCommand sqlDeleteCommand1;
		private System.Data.SqlClient.SqlConnection sqlConnection1;
		private System.Data.SqlClient.SqlDataAdapter sqlDAUser;
		private System.Data.SqlClient.SqlDataAdapter sqlDACompany;
		private System.Data.SqlClient.SqlCommand sqlSelectCommand2;
		private System.Data.SqlClient.SqlCommand sqlInsertCommand2;
		private System.Data.SqlClient.SqlCommand sqlUpdateCommand2;
		private System.Data.SqlClient.SqlCommand sqlDeleteCommand2;
		private System.Data.SqlClient.SqlConnection sqlConnection2;
		private System.Data.SqlClient.SqlDataAdapter sqlDACompanyServer;
		private System.Data.SqlClient.SqlCommand sqlSelectCommand3;
		private System.Data.SqlClient.SqlCommand sqlInsertCommand3;
		private System.Data.SqlClient.SqlCommand sqlUpdateCommand3;
		private System.Data.SqlClient.SqlCommand sqlDeleteCommand3;
		private System.Data.SqlClient.SqlDataAdapter sqlDAServer;
		private System.Data.SqlClient.SqlCommand sqlSelectCommand4;
		private System.Data.SqlClient.SqlCommand sqlInsertCommand4;
		private System.Data.SqlClient.SqlCommand sqlUpdateCommand4;
		private System.Data.SqlClient.SqlCommand sqlDeleteCommand4;
		private System.Data.SqlClient.SqlDataAdapter sqlDASession;
		private System.Data.SqlClient.SqlCommand sqlSelectCommand5;
		private System.Data.SqlClient.SqlCommand sqlInsertCommand5;
		private System.Data.SqlClient.SqlCommand sqlUpdateCommand5;
		private System.Data.SqlClient.SqlCommand sqlDeleteCommand5;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components = null;

		public DSLUtils(System.ComponentModel.IContainer container)
		{
			///
			/// Required for Windows.Forms Class Composition Designer support
			///
			container.Add(this);
			InitializeComponent();
		}

		public DSLUtils()
		{
			///
			/// Required for Windows.Forms Class Composition Designer support
			///
			InitializeComponent();
		}

		public DSLUtils(string strConnStr)
		{
			///
			/// Required for Windows.Forms Class Composition Designer support
			///
			InitializeComponent();
			sqlConnection1.ConnectionString = strConnStr;
		}

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if(components != null)
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}


		#region Component Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.sqlDAUser = new System.Data.SqlClient.SqlDataAdapter();
			this.sqlDeleteCommand1 = new System.Data.SqlClient.SqlCommand();
			this.sqlConnection1 = new System.Data.SqlClient.SqlConnection();
			this.sqlInsertCommand1 = new System.Data.SqlClient.SqlCommand();
			this.sqlSelectCommand1 = new System.Data.SqlClient.SqlCommand();
			this.sqlUpdateCommand1 = new System.Data.SqlClient.SqlCommand();
			this.sqlDACompany = new System.Data.SqlClient.SqlDataAdapter();
			this.sqlDeleteCommand2 = new System.Data.SqlClient.SqlCommand();
			this.sqlInsertCommand2 = new System.Data.SqlClient.SqlCommand();
			this.sqlSelectCommand2 = new System.Data.SqlClient.SqlCommand();
			this.sqlUpdateCommand2 = new System.Data.SqlClient.SqlCommand();
			this.sqlConnection2 = new System.Data.SqlClient.SqlConnection();
			this.sqlDACompanyServer = new System.Data.SqlClient.SqlDataAdapter();
			this.sqlDeleteCommand3 = new System.Data.SqlClient.SqlCommand();
			this.sqlInsertCommand3 = new System.Data.SqlClient.SqlCommand();
			this.sqlSelectCommand3 = new System.Data.SqlClient.SqlCommand();
			this.sqlUpdateCommand3 = new System.Data.SqlClient.SqlCommand();
			this.sqlDAServer = new System.Data.SqlClient.SqlDataAdapter();
			this.sqlDeleteCommand4 = new System.Data.SqlClient.SqlCommand();
			this.sqlInsertCommand4 = new System.Data.SqlClient.SqlCommand();
			this.sqlSelectCommand4 = new System.Data.SqlClient.SqlCommand();
			this.sqlUpdateCommand4 = new System.Data.SqlClient.SqlCommand();
			this.sqlDASession = new System.Data.SqlClient.SqlDataAdapter();
			this.sqlDeleteCommand5 = new System.Data.SqlClient.SqlCommand();
			this.sqlInsertCommand5 = new System.Data.SqlClient.SqlCommand();
			this.sqlSelectCommand5 = new System.Data.SqlClient.SqlCommand();
			this.sqlUpdateCommand5 = new System.Data.SqlClient.SqlCommand();
			// 
			// sqlDAUser
			// 
			this.sqlDAUser.DeleteCommand = this.sqlDeleteCommand1;
			this.sqlDAUser.InsertCommand = this.sqlInsertCommand1;
			this.sqlDAUser.SelectCommand = this.sqlSelectCommand1;
			this.sqlDAUser.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																								new System.Data.Common.DataTableMapping("Table", "TUsers", new System.Data.Common.DataColumnMapping[] {
																																																		  new System.Data.Common.DataColumnMapping("userId", "userId"),
																																																		  new System.Data.Common.DataColumnMapping("coId", "coId"),
																																																		  new System.Data.Common.DataColumnMapping("firstName", "firstName"),
																																																		  new System.Data.Common.DataColumnMapping("lastName", "lastName"),
																																																		  new System.Data.Common.DataColumnMapping("userName", "userName"),
																																																		  new System.Data.Common.DataColumnMapping("password", "password"),
																																																		  new System.Data.Common.DataColumnMapping("anyServer", "anyServer"),
																																																		  new System.Data.Common.DataColumnMapping("inactive", "inactive"),
																																																		  new System.Data.Common.DataColumnMapping("userRole", "userRole"),
																																																		  new System.Data.Common.DataColumnMapping("userMode", "userMode")})});
			this.sqlDAUser.UpdateCommand = this.sqlUpdateCommand1;
			// 
			// sqlDeleteCommand1
			// 
			this.sqlDeleteCommand1.CommandText = "[DeleteUser]";
			this.sqlDeleteCommand1.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlDeleteCommand1.Connection = this.sqlConnection1;
			this.sqlDeleteCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlDeleteCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_userId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "userId", System.Data.DataRowVersion.Original, null));
			// 
			// sqlConnection1
			// 
			this.sqlConnection1.ConnectionString = "workstation id=SYRACUSE;packet size=4096;user id=gensymuser;data source=SYRACUSE;" +
				"persist security info=True;initial catalog=GensymG2Users;password=gensym";
			// 
			// sqlInsertCommand1
			// 
			this.sqlInsertCommand1.CommandText = "[AddUser]";
			this.sqlInsertCommand1.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlInsertCommand1.Connection = this.sqlConnection1;
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coId", System.Data.SqlDbType.Int, 4, "coId"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@firstName", System.Data.SqlDbType.VarChar, 50, "firstName"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@lastName", System.Data.SqlDbType.VarChar, 50, "lastName"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userName", System.Data.SqlDbType.VarChar, 50, "userName"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@password", System.Data.SqlDbType.VarChar, 50, "password"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@anyServer", System.Data.SqlDbType.Bit, 1, "anyServer"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userRole", System.Data.SqlDbType.Int, 4, "userRole"));
			this.sqlInsertCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userMode", System.Data.SqlDbType.VarChar, 50, "userMode"));
			// 
			// sqlSelectCommand1
			// 
			this.sqlSelectCommand1.CommandText = "[SelectUsers]";
			this.sqlSelectCommand1.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlSelectCommand1.Connection = this.sqlConnection1;
			this.sqlSelectCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlSelectCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@password", System.Data.SqlDbType.VarChar, 50));
			this.sqlSelectCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userName", System.Data.SqlDbType.VarChar, 50));
			this.sqlSelectCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userId", System.Data.SqlDbType.Int, 4));
			// 
			// sqlUpdateCommand1
			// 
			this.sqlUpdateCommand1.CommandText = "[UpdateUser]";
			this.sqlUpdateCommand1.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlUpdateCommand1.Connection = this.sqlConnection1;
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coId", System.Data.SqlDbType.Int, 4, "coId"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@firstName", System.Data.SqlDbType.VarChar, 50, "firstName"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@lastName", System.Data.SqlDbType.VarChar, 50, "lastName"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userName", System.Data.SqlDbType.VarChar, 50, "userName"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@password", System.Data.SqlDbType.VarChar, 50, "password"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@anyServer", System.Data.SqlDbType.Bit, 1, "anyServer"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_userId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "userId", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userId", System.Data.SqlDbType.Int, 4, "userId"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userRole", System.Data.SqlDbType.Int, 4, "userRole"));
			this.sqlUpdateCommand1.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userMode", System.Data.SqlDbType.VarChar, 50, "userMode"));
			// 
			// sqlDACompany
			// 
			this.sqlDACompany.DeleteCommand = this.sqlDeleteCommand2;
			this.sqlDACompany.InsertCommand = this.sqlInsertCommand2;
			this.sqlDACompany.SelectCommand = this.sqlSelectCommand2;
			this.sqlDACompany.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																								   new System.Data.Common.DataTableMapping("Table", "TCompanies", new System.Data.Common.DataColumnMapping[] {
																																																				 new System.Data.Common.DataColumnMapping("coId", "coId"),
																																																				 new System.Data.Common.DataColumnMapping("coName", "coName"),
																																																				 new System.Data.Common.DataColumnMapping("coStreet", "coStreet"),
																																																				 new System.Data.Common.DataColumnMapping("coStreet2", "coStreet2"),
																																																				 new System.Data.Common.DataColumnMapping("coCity", "coCity"),
																																																				 new System.Data.Common.DataColumnMapping("coState", "coState"),
																																																				 new System.Data.Common.DataColumnMapping("coZip", "coZip"),
																																																				 new System.Data.Common.DataColumnMapping("numLicenses", "numLicenses"),
																																																				 new System.Data.Common.DataColumnMapping("numConcurrentSessions", "numConcurrentSessions"),
																																																				 new System.Data.Common.DataColumnMapping("numCollaborators", "numCollaborators"),
																																																				 new System.Data.Common.DataColumnMapping("inactive", "inactive"),
																																																				 new System.Data.Common.DataColumnMapping("rootDirName", "rootDirName"),
																																																				 new System.Data.Common.DataColumnMapping("logFileName", "logFileName"),
																																																				 new System.Data.Common.DataColumnMapping("okFileName", "okFileName")})});
			this.sqlDACompany.UpdateCommand = this.sqlUpdateCommand2;
			// 
			// sqlDeleteCommand2
			// 
			this.sqlDeleteCommand2.CommandText = "[DeleteCompany]";
			this.sqlDeleteCommand2.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlDeleteCommand2.Connection = this.sqlConnection1;
			this.sqlDeleteCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlDeleteCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_coId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "coId", System.Data.DataRowVersion.Original, null));
			// 
			// sqlInsertCommand2
			// 
			this.sqlInsertCommand2.CommandText = "[AddCompany]";
			this.sqlInsertCommand2.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlInsertCommand2.Connection = this.sqlConnection1;
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coName", System.Data.SqlDbType.VarChar, 50, "coName"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coStreet", System.Data.SqlDbType.VarChar, 50, "coStreet"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coStreet2", System.Data.SqlDbType.VarChar, 50, "coStreet2"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coCity", System.Data.SqlDbType.VarChar, 50, "coCity"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coState", System.Data.SqlDbType.VarChar, 50, "coState"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coZip", System.Data.SqlDbType.VarChar, 25, "coZip"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numLicenses", System.Data.SqlDbType.SmallInt, 2, "numLicenses"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numConcurrentSessions", System.Data.SqlDbType.SmallInt, 2, "numConcurrentSessions"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numCollaborators", System.Data.SqlDbType.SmallInt, 2, "numCollaborators"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@rootDirName", System.Data.SqlDbType.VarChar, 50, "rootDirName"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@logFileName", System.Data.SqlDbType.VarChar, 50, "logFileName"));
			this.sqlInsertCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@okFileName", System.Data.SqlDbType.VarChar, 50, "okFileName"));
			// 
			// sqlSelectCommand2
			// 
			this.sqlSelectCommand2.CommandText = "[SelectCompany]";
			this.sqlSelectCommand2.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlSelectCommand2.Connection = this.sqlConnection1;
			this.sqlSelectCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlSelectCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@companyId", System.Data.SqlDbType.Int, 4));
			// 
			// sqlUpdateCommand2
			// 
			this.sqlUpdateCommand2.CommandText = "[UpdateCompany]";
			this.sqlUpdateCommand2.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlUpdateCommand2.Connection = this.sqlConnection1;
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coName", System.Data.SqlDbType.VarChar, 50, "coName"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coStreet", System.Data.SqlDbType.VarChar, 50, "coStreet"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coStreet2", System.Data.SqlDbType.VarChar, 50, "coStreet2"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coCity", System.Data.SqlDbType.VarChar, 50, "coCity"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coState", System.Data.SqlDbType.VarChar, 50, "coState"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coZip", System.Data.SqlDbType.VarChar, 25, "coZip"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numLicenses", System.Data.SqlDbType.SmallInt, 2, "numLicenses"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numConcurrentSessions", System.Data.SqlDbType.SmallInt, 2, "numConcurrentSessions"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@numCollaborators", System.Data.SqlDbType.SmallInt, 2, "numCollaborators"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_coId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "coId", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coId", System.Data.SqlDbType.Int, 4, "coId"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@rootDirName", System.Data.SqlDbType.VarChar, 50, "rootDirName"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@logFileName", System.Data.SqlDbType.VarChar, 50, "logFileName"));
			this.sqlUpdateCommand2.Parameters.Add(new System.Data.SqlClient.SqlParameter("@okFileName", System.Data.SqlDbType.VarChar, 50, "okFileName"));
			// 
			// sqlConnection2
			// 
			this.sqlConnection2.ConnectionString = "workstation id=SYRACUSE;packet size=4096;user id=sa;data source=SYRACUSE;persist " +
				"security info=False;initial catalog=GensymG2Users";
			// 
			// sqlDACompanyServer
			// 
			this.sqlDACompanyServer.DeleteCommand = this.sqlDeleteCommand3;
			this.sqlDACompanyServer.InsertCommand = this.sqlInsertCommand3;
			this.sqlDACompanyServer.SelectCommand = this.sqlSelectCommand3;
			this.sqlDACompanyServer.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																										 new System.Data.Common.DataTableMapping("Table", "TCompanyServers", new System.Data.Common.DataColumnMapping[] {
																																																							new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																							new System.Data.Common.DataColumnMapping("serverName", "serverName"),
																																																							new System.Data.Common.DataColumnMapping("ipAddress", "ipAddress"),
																																																							new System.Data.Common.DataColumnMapping("minPort", "minPort"),
																																																							new System.Data.Common.DataColumnMapping("maxPort", "maxPort"),
																																																							new System.Data.Common.DataColumnMapping("inactive", "inactive"),
																																																							new System.Data.Common.DataColumnMapping("coServerId", "coServerId"),
																																																							new System.Data.Common.DataColumnMapping("coId", "coId"),
																																																							new System.Data.Common.DataColumnMapping("portNo", "portNo")}),
																										 new System.Data.Common.DataTableMapping("Table1", "Table1", new System.Data.Common.DataColumnMapping[0]),
																										 new System.Data.Common.DataTableMapping("Table2", "Table2", new System.Data.Common.DataColumnMapping[0]),
																										 new System.Data.Common.DataTableMapping("Table3", "Table3", new System.Data.Common.DataColumnMapping[0])});
			this.sqlDACompanyServer.UpdateCommand = this.sqlUpdateCommand3;
			// 
			// sqlDeleteCommand3
			// 
			this.sqlDeleteCommand3.CommandText = "[DeleteCompanyServer]";
			this.sqlDeleteCommand3.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlDeleteCommand3.Connection = this.sqlConnection1;
			this.sqlDeleteCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlDeleteCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_coId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "coId", System.Data.DataRowVersion.Original, null));
			this.sqlDeleteCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_serverId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "serverId", System.Data.DataRowVersion.Original, null));
			this.sqlDeleteCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_portNo", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "portNo", System.Data.DataRowVersion.Original, null));
			// 
			// sqlInsertCommand3
			// 
			this.sqlInsertCommand3.CommandText = "[AddCompanyServer]";
			this.sqlInsertCommand3.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlInsertCommand3.Connection = this.sqlConnection1;
			this.sqlInsertCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlInsertCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coId", System.Data.SqlDbType.Int, 4, "coId"));
			this.sqlInsertCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverId", System.Data.SqlDbType.Int, 4, "serverId"));
			this.sqlInsertCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@portNo", System.Data.SqlDbType.Int, 4, "portNo"));
			// 
			// sqlSelectCommand3
			// 
			this.sqlSelectCommand3.CommandText = "[SelectCompanyServers]";
			this.sqlSelectCommand3.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlSelectCommand3.Connection = this.sqlConnection1;
			this.sqlSelectCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlSelectCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coServerId", System.Data.SqlDbType.Int, 4));
			this.sqlSelectCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@coId", System.Data.SqlDbType.Int, 4));
			this.sqlSelectCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@includeInactive", System.Data.SqlDbType.Bit, 1));
			// 
			// sqlUpdateCommand3
			// 
			this.sqlUpdateCommand3.CommandText = "[UpdateCompanyServer]";
			this.sqlUpdateCommand3.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlUpdateCommand3.Connection = this.sqlConnection1;
			this.sqlUpdateCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlUpdateCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_coId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "coId", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_serverId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "serverId", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_portNo", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "portNo", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand3.Parameters.Add(new System.Data.SqlClient.SqlParameter("@portNo", System.Data.SqlDbType.Int, 4, "portNo"));
			// 
			// sqlDAServer
			// 
			this.sqlDAServer.DeleteCommand = this.sqlDeleteCommand4;
			this.sqlDAServer.InsertCommand = this.sqlInsertCommand4;
			this.sqlDAServer.SelectCommand = this.sqlSelectCommand4;
			this.sqlDAServer.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																								  new System.Data.Common.DataTableMapping("Table", "TServers", new System.Data.Common.DataColumnMapping[] {
																																																			  new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																			  new System.Data.Common.DataColumnMapping("serverName", "serverName"),
																																																			  new System.Data.Common.DataColumnMapping("ipAddress", "ipAddress"),
																																																			  new System.Data.Common.DataColumnMapping("minPort", "minPort"),
																																																			  new System.Data.Common.DataColumnMapping("maxPort", "maxPort"),
																																																			  new System.Data.Common.DataColumnMapping("inactive", "inactive")}),
																								  new System.Data.Common.DataTableMapping("Table1", "Table1", new System.Data.Common.DataColumnMapping[] {
																																																			 new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																			 new System.Data.Common.DataColumnMapping("serverName", "serverName"),
																																																			 new System.Data.Common.DataColumnMapping("ipAddress", "ipAddress"),
																																																			 new System.Data.Common.DataColumnMapping("minPort", "minPort"),
																																																			 new System.Data.Common.DataColumnMapping("maxPort", "maxPort"),
																																																			 new System.Data.Common.DataColumnMapping("inactive", "inactive")}),
																								  new System.Data.Common.DataTableMapping("Table2", "Table2", new System.Data.Common.DataColumnMapping[] {
																																																			 new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																			 new System.Data.Common.DataColumnMapping("serverName", "serverName"),
																																																			 new System.Data.Common.DataColumnMapping("ipAddress", "ipAddress"),
																																																			 new System.Data.Common.DataColumnMapping("minPort", "minPort"),
																																																			 new System.Data.Common.DataColumnMapping("maxPort", "maxPort"),
																																																			 new System.Data.Common.DataColumnMapping("inactive", "inactive")}),
																								  new System.Data.Common.DataTableMapping("Table3", "Table3", new System.Data.Common.DataColumnMapping[] {
																																																			 new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																			 new System.Data.Common.DataColumnMapping("serverName", "serverName"),
																																																			 new System.Data.Common.DataColumnMapping("ipAddress", "ipAddress"),
																																																			 new System.Data.Common.DataColumnMapping("minPort", "minPort"),
																																																			 new System.Data.Common.DataColumnMapping("maxPort", "maxPort"),
																																																			 new System.Data.Common.DataColumnMapping("inactive", "inactive")})});
			this.sqlDAServer.UpdateCommand = this.sqlUpdateCommand4;
			// 
			// sqlDeleteCommand4
			// 
			this.sqlDeleteCommand4.CommandText = "[DeleteServer]";
			this.sqlDeleteCommand4.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlDeleteCommand4.Connection = this.sqlConnection1;
			this.sqlDeleteCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlDeleteCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_serverId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "serverId", System.Data.DataRowVersion.Original, null));
			// 
			// sqlInsertCommand4
			// 
			this.sqlInsertCommand4.CommandText = "[AddServer]";
			this.sqlInsertCommand4.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlInsertCommand4.Connection = this.sqlConnection1;
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverName", System.Data.SqlDbType.VarChar, 50, "serverName"));
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@ipAddress", System.Data.SqlDbType.VarChar, 20, "ipAddress"));
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@minPort", System.Data.SqlDbType.Int, 4, "minPort"));
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@maxPort", System.Data.SqlDbType.Int, 4, "maxPort"));
			this.sqlInsertCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			// 
			// sqlSelectCommand4
			// 
			this.sqlSelectCommand4.CommandText = "[SelectServers]";
			this.sqlSelectCommand4.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlSelectCommand4.Connection = this.sqlConnection1;
			this.sqlSelectCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlSelectCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverId", System.Data.SqlDbType.Int, 4));
			this.sqlSelectCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@includeInactive", System.Data.SqlDbType.Bit, 1));
			// 
			// sqlUpdateCommand4
			// 
			this.sqlUpdateCommand4.CommandText = "[UpdateServer]";
			this.sqlUpdateCommand4.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlUpdateCommand4.Connection = this.sqlConnection1;
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverName", System.Data.SqlDbType.VarChar, 50, "serverName"));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@ipAddress", System.Data.SqlDbType.VarChar, 20, "ipAddress"));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@minPort", System.Data.SqlDbType.Int, 4, "minPort"));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@maxPort", System.Data.SqlDbType.Int, 4, "maxPort"));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@inactive", System.Data.SqlDbType.Bit, 1, "inactive"));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_serverId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "serverId", System.Data.DataRowVersion.Original, null));
			this.sqlUpdateCommand4.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverId", System.Data.SqlDbType.Int, 4, "serverId"));
			// 
			// sqlDASession
			// 
			this.sqlDASession.DeleteCommand = this.sqlDeleteCommand5;
			this.sqlDASession.InsertCommand = this.sqlInsertCommand5;
			this.sqlDASession.SelectCommand = this.sqlSelectCommand5;
			this.sqlDASession.TableMappings.AddRange(new System.Data.Common.DataTableMapping[] {
																								   new System.Data.Common.DataTableMapping("Table", "TSessions", new System.Data.Common.DataColumnMapping[] {
																																																				new System.Data.Common.DataColumnMapping("userId", "userId"),
																																																				new System.Data.Common.DataColumnMapping("sessionGuid", "sessionGuid"),
																																																				new System.Data.Common.DataColumnMapping("loginDate", "loginDate"),
																																																				new System.Data.Common.DataColumnMapping("serverId", "serverId"),
																																																				new System.Data.Common.DataColumnMapping("serverPortNo", "serverPortNo")})});
			this.sqlDASession.UpdateCommand = this.sqlUpdateCommand5;
			// 
			// sqlDeleteCommand5
			// 
			this.sqlDeleteCommand5.CommandText = "[DeleteSession]";
			this.sqlDeleteCommand5.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlDeleteCommand5.Connection = this.sqlConnection1;
			this.sqlDeleteCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlDeleteCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_userId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "userId", System.Data.DataRowVersion.Original, null));
			// 
			// sqlInsertCommand5
			// 
			this.sqlInsertCommand5.CommandText = "[AddSession]";
			this.sqlInsertCommand5.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlInsertCommand5.Connection = this.sqlConnection1;
			this.sqlInsertCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlInsertCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userId", System.Data.SqlDbType.Int, 4, "userId"));
			this.sqlInsertCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@sessionGuid", System.Data.SqlDbType.UniqueIdentifier, 16, "sessionGuid"));
			this.sqlInsertCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverId", System.Data.SqlDbType.Int, 4, "serverId"));
			this.sqlInsertCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverPortNo", System.Data.SqlDbType.Int, 4, "serverPortNo"));
			// 
			// sqlSelectCommand5
			// 
			this.sqlSelectCommand5.CommandText = "[SelectSessions]";
			this.sqlSelectCommand5.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlSelectCommand5.Connection = this.sqlConnection1;
			this.sqlSelectCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlSelectCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userId", System.Data.SqlDbType.Int, 4, "userId"));
			// 
			// sqlUpdateCommand5
			// 
			this.sqlUpdateCommand5.CommandText = "[UpdateSession]";
			this.sqlUpdateCommand5.CommandType = System.Data.CommandType.StoredProcedure;
			this.sqlUpdateCommand5.Connection = this.sqlConnection1;
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@RETURN_VALUE", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.ReturnValue, false, ((System.Byte)(0)), ((System.Byte)(0)), "", System.Data.DataRowVersion.Current, null));
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@userId", System.Data.SqlDbType.Int, 4, "userId"));
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@sessionGuid", System.Data.SqlDbType.UniqueIdentifier, 16, "sessionGuid"));
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverId", System.Data.SqlDbType.Int, 4, "serverId"));
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@serverPortNo", System.Data.SqlDbType.Int, 4, "serverPortNo"));
			this.sqlUpdateCommand5.Parameters.Add(new System.Data.SqlClient.SqlParameter("@Original_userId", System.Data.SqlDbType.Int, 4, System.Data.ParameterDirection.Input, false, ((System.Byte)(0)), ((System.Byte)(0)), "userId", System.Data.DataRowVersion.Original, null));

		}
		#endregion

		/// <summary>
		/// Retrieve user by username and password.
		/// </summary>
		public DSLUser GetUser(string userName, string password)
		{
			DSLUser ds = new DSLUser();
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = userName;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = password;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
			if (ds.TUsers.Count == 1)
				return ds;
			else
				return null;
		}

		/// <summary>
		/// Retrieve user by username and password.
		/// </summary>
		public void GetUser(string userName, string password, DSLUser ds)
		{
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = userName;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = password;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
		}

		/// <summary>
		/// Retrieve user by username.
		/// </summary>
		public DSLUser GetUser(string userName)
		{
			DSLUser ds = new DSLUser();
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = userName;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
			if (ds.TUsers.Count == 1)
				return ds;
			else
				return null;
		}

		/// <summary>
		/// Retrieve user by username.
		/// </summary>
		public void GetUser(string userName, DSLUser ds)
		{
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = userName;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
		}

		/// <summary>
		/// Retrieve user by user ID.
		/// </summary>
		public DSLUser GetUser(int userId)
		{
			DSLUser ds = new DSLUser();
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = userId;
			sqlDAUser.Fill(ds);
			return ds;
		}

		public void GetUser(int userId, DSLUser ds)
		{
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = userId;
			sqlDAUser.Fill(ds);
		}

		public DSLUser GetUserList()
		{
			DSLUser ds = new DSLUser();
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
			return ds;
		}

		public void GetUserList(DSLUser ds)
		{
			sqlDAUser.SelectCommand.Parameters["@userName"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@password"].Value = null;
			sqlDAUser.SelectCommand.Parameters["@userId"].Value = null;
			sqlDAUser.Fill(ds);
		}

		public DSLCompany GetCompany(int companyId)
		{
			DSLCompany ds = new DSLCompany();
			sqlDACompany.SelectCommand.Parameters["@companyId"].Value = companyId;
			sqlDACompany.Fill(ds);
			if (ds.TCompanies.Count == 1)
				return ds;
			else
				return null;
		}

		public void GetCompany(int companyId, DSLCompany ds)
		{
			sqlDACompany.SelectCommand.Parameters["@companyId"].Value = companyId;
			sqlDACompany.Fill(ds);
		}

		public DSLCompany GetCompanyList()
		{
			DSLCompany ds = new DSLCompany();
			sqlDACompany.SelectCommand.Parameters["@companyId"].Value = null;
			sqlDACompany.Fill(ds);
			return ds;
		}

		public void GetCompanyList(DSLCompany ds)
		{
			sqlDACompany.SelectCommand.Parameters["@companyId"].Value = null;
			sqlDACompany.Fill(ds);
		}

		public DSLServer GetServer(int serverId)
		{
			DSLServer ds = new DSLServer();
			sqlDAServer.SelectCommand.Parameters["@serverId"].Value = serverId;
			sqlDAServer.Fill(ds);
			if (ds.TServers.Count == 1)
				return ds;
			else
				return null;
		}

		public void GetServer(int serverId, DSLServer ds)
		{
			sqlDAServer.SelectCommand.Parameters["@serverId"].Value = serverId;
			sqlDAServer.Fill(ds);
		}

		public DSLServer GetServerList()
		{
			DSLServer ds = new DSLServer();
			sqlDAServer.SelectCommand.Parameters["@serverId"].Value = null;
			sqlDAServer.Fill(ds);
			return ds;
		}

		public void GetServerList(DSLServer ds)
		{
			sqlDAServer.SelectCommand.Parameters["@serverId"].Value = null;
			sqlDAServer.Fill(ds);
		}

		public DSLCompanyServer GetCompanyServer(int coServerId)
		{
			DSLCompanyServer ds = new DSLCompanyServer();
			sqlDACompanyServer.SelectCommand.Parameters["@coServerId"].Value = coServerId;
			sqlDACompanyServer.SelectCommand.Parameters["@coId"].Value = null;
			sqlDACompanyServer.Fill(ds);
			if (ds.TCompanyServers.Count == 1)
				return ds;
			else
				return null;
		}

		public void GetCompanyServer(int coServerId, DSLCompanyServer ds)
		{
			sqlDACompanyServer.SelectCommand.Parameters["@coServerId"].Value = coServerId;
			sqlDACompanyServer.SelectCommand.Parameters["@coId"].Value = null;
			sqlDACompanyServer.Fill(ds);
		}

		public DSLCompanyServer GetCompanyServerList(int companyId)
		{
			DSLCompanyServer ds = new DSLCompanyServer();
			sqlDACompanyServer.SelectCommand.Parameters["@coServerId"].Value = null;
			sqlDACompanyServer.SelectCommand.Parameters["@coId"].Value = companyId;
			sqlDACompanyServer.Fill(ds);
			return ds;
		}

		public void GetCompanyServerList(int companyId, 
			DSLCompanyServer ds)
		{
			sqlDACompanyServer.SelectCommand.Parameters["@coServerId"].Value = null;
			sqlDACompanyServer.SelectCommand.Parameters["@coId"].Value = companyId;
			sqlDACompanyServer.Fill(ds);
		}

		public DSLSession GetSession(int userId)
		{
			DSLSession ds = new DSLSession();
			sqlDASession.SelectCommand.Parameters["@userId"].Value = userId;
			sqlDASession.Fill(ds);
			return ds;
		}

		public void GetSession(int userId, DSLSession ds)
		{
			sqlDASession.SelectCommand.Parameters["@userId"].Value = userId;
			sqlDASession.Fill(ds);
		}

		public DSLSession GetSessionList()
		{
			DSLSession ds = new DSLSession();
			sqlDASession.SelectCommand.Parameters["@userId"].Value = null;
			sqlDASession.Fill(ds);
			return ds;
		}

		public void GetSessionList(DSLSession ds)
		{
			sqlDASession.SelectCommand.Parameters["@userId"].Value = null;
			sqlDASession.Fill(ds);
		}

		public void UpdateSession(DSLSession ds)
		{
			sqlDASession.Update(ds);
		}
	}
}
