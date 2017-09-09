<%@ Page language="c#" Codebehind="launchTW.aspx.cs" AutoEventWireup="false" Inherits="TWOnline.launchTW" %>
<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>Telewindows Launcher</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
		<LINK href="TWOnlineStyles.css" type="text/css" rel="STYLESHEET">
		<script language="javascript">
			function loadFinished()
			{
				//document.all["frmcab"].src = ""
				document.all["progress"].style.display = 'none'
				document.all["msgProgress"].innerText = 'Launching Telewindows...'
			}
			function displayError(strMsg)
			{
				alert(strMsg);
			}
		</script>
	</HEAD>
	<body onload="onBodyLoad()">
		<form id="Form1" method="post" runat="server">
			<user:main_header id="main_header1" NAME="main_header1" pageName="launchtw.aspx" RunAt="server"></user:main_header><br>
			<table class="bodyText" cellSpacing="0" cellPadding="0" border="0">
				<tr>
					<td id="msgProgress">
						<P><FONT size="4">Checking for the latest version of the software...</FONT></P>
						<P>Depending on your connection speed, this might take a minute. During this time, 
							you may<BR>
							receive one or more security warnings. Review each security warning to ensure 
							that the<BR>
							content is signed by Gensym, and then click <STRONG>Yes</STRONG> to install the 
							software.<BR>
						</P>
					</td>
				</tr>
				<tr>
					<td align="center"><IMG id="progress" src="images\polling2.gif" name="progress"></td>
				</tr>
			</table>
			<iframe id="frmcab" name="frmcab" src="" frameBorder="no" scrolling="no"></iframe>
		</form>
	</body>
</HTML>
