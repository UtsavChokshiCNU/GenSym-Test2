<%@ Page language="c#" Codebehind="login.aspx.cs" AutoEventWireup="false" Inherits="TWOnline.WebForm1" %>
<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>Telewindows Online</title>
		<meta name="GENERATOR" Content="Microsoft Visual Studio .NET 7.1">
		<meta name="CODE_LANGUAGE" Content="C#">
		<meta name="vs_defaultClientScript" content="JavaScript">
		<meta name="vs_targetSchema" content="http://schemas.microsoft.com/intellisense/ie5">
		<link rel="STYLESHEET" type="text/css" href="TWOnlineStyles.css">
	</HEAD>
	<body bottomMargin="0" leftMargin="2" topMargin="0" rightMargin="2">
		<form id="Form1" method="post" runat="server">
			<P>
				<user:main_header id="main_header1" RunAt="server" pageName="login.aspx" NAME="main_header1"></user:main_header><br>
				<TABLE id="Table1" cellSpacing="2" cellPadding="2" width="576" border="0" class="bodyText"
					style="WIDTH: 576px; HEIGHT: 86px">
					<TR>
						<TD style="WIDTH: 65px">Username:</TD>
						<TD align="right" style="WIDTH: 160px">
							<asp:TextBox id="txt_UserName" runat="server" Width="160px"></asp:TextBox></TD>
						<TD align="left" rowspan="3" vAlign="top">
							<asp:ValidationSummary id="ValidationSummary1" runat="server"></asp:ValidationSummary></TD>
					</TR>
					<TR>
						<TD style="WIDTH: 65px">Password:</TD>
						<TD align="right" style="WIDTH: 160px">
							<asp:TextBox id="txt_Password" runat="server" TextMode="Password" Width="160px"></asp:TextBox></TD>
					</TR>
					<TR>
						<TD style="WIDTH: 65px"></TD>
						<TD align="right" style="WIDTH: 160px">
							<asp:Button id="btn_Login" runat="server" Text="Login" Width="100px"></asp:Button></TD>
					</TR>
				</TABLE>
			</P>
			<P>
				<asp:RequiredFieldValidator id="userNameValidator" runat="server" ErrorMessage="Username  cannot be blank."
					ControlToValidate="txt_UserName" Display="None"></asp:RequiredFieldValidator><BR>
				<asp:RequiredFieldValidator id="passwordValidator" runat="server" ErrorMessage="Password cannot be blank." ControlToValidate="txt_Password"
					Display="None"></asp:RequiredFieldValidator></P>
		</form>
		<script language='javascript'>
			document.all['txt_UserName'].focus();
		</script>
	</body>
</HTML>
