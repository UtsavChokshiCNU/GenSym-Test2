<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<%@ Page language="c#" Codebehind="Download.aspx.cs" AutoEventWireup="false" Inherits="WebScorFileMgr.Download" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebSCOR File Manager: Download</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
		<LINK href="TWOnlineStyles.css" type="text/css" rel="STYLESHEET">
		<script language="javascript" src="includes/javascript.js"></script>
	</HEAD>
	<body bottomMargin="0" leftMargin="2" topMargin="0" rightMargin="2">
		<form id="Form1" method="post" runat="server">
			<user:main_header id="main_header1" RunAt="server" pageName="download.aspx" NAME="main_header1"></user:main_header><br>
			<asp:label id="lblMsg" runat="server" CssClass="bodyText" ForeColor="Red" Visible="False"></asp:label><br>
			<p>Click a filename below to download the file to your hard drive or&nbsp;click the 
				delete icon to delete&nbsp;a file. Input files are typically associated with 
				input reports, while output files are associated with output reports. Filenames 
				needs to match the report title to&nbsp;be associated with a report.<BR>
				&nbsp;<br>
				<STRONG>Input Files:</STRONG>
				<br>
				<asp:datagrid id="dataGridInput" runat="server" CssClass="bodyText" Width="600px" AllowSorting="True"
					AutoGenerateColumns="False">
					<Columns>
						<asp:HyperLinkColumn DataNavigateUrlField="fileName" DataNavigateUrlFormatString="getfile.aspx?d=i&amp;f={0}"
							DataTextField="fileName" SortExpression="fileName" HeaderText="Filename:">
							<ItemStyle Width="200px"></ItemStyle>
						</asp:HyperLinkColumn>
						<asp:BoundColumn DataField="fileSize" SortExpression="fileSize" HeaderText="File Size (bytes)" DataFormatString="{0:#,##0}">
							<ItemStyle HorizontalAlign="Right" Width="100px"></ItemStyle>
						</asp:BoundColumn>
						<asp:BoundColumn DataField="modifyDate" SortExpression="modifyDate" HeaderText="Date Modified" DataFormatString="{0:MM/dd/yyyy hh:mm tt}">
							<ItemStyle Width="150px"></ItemStyle>
						</asp:BoundColumn>
						<asp:BoundColumn DataField="fileExt" SortExpression="fileExt" HeaderText="File Type">
							<ItemStyle Width="50px"></ItemStyle>
						</asp:BoundColumn>
						<asp:TemplateColumn>
							<ItemStyle HorizontalAlign="Center" Width="30px"></ItemStyle>
							<ItemTemplate>
								<asp:ImageButton ID="btn_Delete" CommandName="Delete" Runat="server" CommandArgument='<%# DataBinder.Eval(Container.DataItem, "fileName")%>' ImageUrl="images\button_clear.gif">
								</asp:ImageButton>
							</ItemTemplate>
						</asp:TemplateColumn>
					</Columns>
				</asp:datagrid></p>
			<p><STRONG>Output Files:</STRONG>
				<br>
				<asp:datagrid id="dataGridOutput" runat="server" CssClass="bodyText" Width="600px" AllowSorting="True"
					AutoGenerateColumns="False">
					<Columns>
						<asp:HyperLinkColumn DataNavigateUrlField="fileName" DataNavigateUrlFormatString="getfile.aspx?d=o&amp;f={0}"
							DataTextField="fileName" SortExpression="fileName" HeaderText="Filename:">
							<ItemStyle Width="200px"></ItemStyle>
						</asp:HyperLinkColumn>
						<asp:BoundColumn DataField="fileSize" SortExpression="fileSize" HeaderText="File Size (bytes)" DataFormatString="{0:#,##0}">
							<ItemStyle HorizontalAlign="Right" Width="100px"></ItemStyle>
						</asp:BoundColumn>
						<asp:BoundColumn DataField="modifyDate" SortExpression="modifyDate" HeaderText="Date Modified" DataFormatString="{0:MM/dd/yyyy hh:mm tt}">
							<ItemStyle Width="150px"></ItemStyle>
						</asp:BoundColumn>
						<asp:BoundColumn DataField="fileExt" SortExpression="fileExt" HeaderText="File Type">
							<ItemStyle Width="50px"></ItemStyle>
						</asp:BoundColumn>
						<asp:TemplateColumn>
							<ItemStyle HorizontalAlign="Center" Width="30px"></ItemStyle>
							<ItemTemplate>
								<asp:ImageButton ID="btn_OutDelete" CommandName="Delete" Runat="server" CommandArgument='<%# DataBinder.Eval(Container.DataItem, "fileName")%>' ImageUrl="images\button_clear.gif">
								</asp:ImageButton>
							</ItemTemplate>
						</asp:TemplateColumn>
					</Columns>
				</asp:datagrid></p>
		</form>
	</body>
</HTML>
