<%@ Page language="c#" Codebehind="Welcome.aspx.cs" AutoEventWireup="false" Inherits="WebScorFileMgr.Welcome" %>
<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebSCOR File Manager</title>
		<meta name="GENERATOR" Content="Microsoft Visual Studio .NET 7.1">
		<meta name="CODE_LANGUAGE" Content="C#">
		<meta name="vs_defaultClientScript" content="JavaScript">
		<meta name="vs_targetSchema" content="http://schemas.microsoft.com/intellisense/ie5">
		<link rel="STYLESHEET" type="text/css" href="TWOnlineStyles.css">
	</HEAD>
	<body bottomMargin="0" leftMargin="2" topMargin="0" rightMargin="2">
		<form id="Form1" method="post" runat="server">
			<P>
				<user:main_header id="main_header1" RunAt="server" pageName="welcome.aspx" NAME="main_header1"></user:main_header><br>
				Welcome to webSCOR! You&nbsp;may manage your model input and output files from 
				this web application.
			</P>
		</form>
	</body>
</HTML>
