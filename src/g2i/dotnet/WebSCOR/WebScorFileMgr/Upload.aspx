<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<%@ Page language="c#" Codebehind="Upload.aspx.cs" AutoEventWireup="false" Inherits="WebScorFileMgr.Upload" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebSCOR File Manager: Upload</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
		<LINK href="TWOnlineStyles.css" type="text/css" rel="STYLESHEET">
	</HEAD>
	<body bottomMargin="0" leftMargin="2" topMargin="0" rightMargin="2">
		<form id="Form1" method="post" encType="multipart/form-data" runat="server">
			<user:main_header id="main_header1" NAME="main_header1" pageName="upload.aspx" RunAt="server"></user:main_header><br>
			<asp:label id="lblMsg" Visible="False" ForeColor="Red" runat="server" CssClass="bodyText"></asp:label>
			<br>
			<STRONG>Note:</STRONG> The maximum size of an uploaded file is 8MB.
			<TABLE id="Table1" cellSpacing="1" cellPadding="1" width="400" border="0" class="bodyText">
				<TR>
					<TD align="right" width="200"><input id="file1" type="file" name="file1" runat="server"></TD>
					<TD align="left" colSpan="3"><asp:requiredfieldvalidator id="filenameValidator" runat="server" ErrorMessage="Filename cannot be blank." ControlToValidate="file1"
							CssClass="bodyText"></asp:requiredfieldvalidator></TD>
				</TR>
				<tr>
					<td>&nbsp;</td>
				</tr>
				<TR>
					<TD align="right"><asp:button id="btn_Upload" runat="server" Text="Upload" Width="80px"></asp:button></TD>
				</TR>
			</TABLE>
		</form>
	</body>
</HTML>
