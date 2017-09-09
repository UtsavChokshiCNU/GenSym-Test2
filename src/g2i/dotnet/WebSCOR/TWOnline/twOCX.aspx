<%@ Page language="c#" Codebehind="twOCX.aspx.cs" AutoEventWireup="false" Inherits="TWOnline.twOCX" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>twOCX</title>
		<meta name="GENERATOR" Content="Microsoft Visual Studio .NET 7.1">
		<meta name="CODE_LANGUAGE" Content="C#">
		<meta name="vs_defaultClientScript" content="JavaScript">
		<meta name="vs_targetSchema" content="http://schemas.microsoft.com/intellisense/ie5">
		<script language="javascript">
			function onBodyLoad()
			{
				parent.loadFinished()
			}	
		</script>
	</HEAD>
	<body onload="onBodyLoad()">
		<form id="Form1" method="post" runat="server">
			<object name="twocx" id="twocx" codebase="<%=m_codeBase%>"
				classid="<%=m_classId%>" VIEWASTEXT>
				<param name="_ExtentX" value="8467">
				<param name="_ExtentY" value="6350">
				<param name="serverName" value="<%=m_serverName%>">
				<param name="serverPort" value="<%=m_portNo%>">
				<param name="userName" value="<%=m_userName%>">
				<param name="password" value="<%=m_password%>">
				<param name="sessionId" value="<%=m_sessionId%>">
				<param name="userMode" value="<%=m_userMode%>">
			</object>
		</form>
	</body>
</HTML>
