<%@ Control Language="c#" AutoEventWireup="false" Codebehind="TWOnlineHeader.ascx.cs" Inherits="TWOnline.TWOnlineHeader" TargetSchema="http://schemas.microsoft.com/intellisense/ie5"%>
<TABLE id="Table2" cellSpacing="0" cellPadding="0" width="100%" border="0">
	<TR>
		<TD style="MARGIN-LEFT: 10px" bgColor="#000000"><IMG alt="" src="images/main_logo.gif"></TD>
		<td valign="bottom" align="right" bgColor="#000000"><asp:Label id="label_Welcome" runat="server" CssClass="headerWelcome" Visible="False"></asp:Label></td>
	</TR>
</TABLE>
<TABLE id="Table1" cellSpacing="1" cellPadding="2" width="100%" background="images/nav_tile.gif"
	border="0">
	<TR>
		<TD><asp:HyperLink id="link_Login" runat="server" CssClass="headerLink" NavigateUrl="login.aspx">Login</asp:HyperLink>
			&nbsp;<asp:Label id="separator1" runat="server" CssClass="headerLink" Visible="False">|</asp:Label>
			<asp:HyperLink id="link_StartSession" runat="server" CssClass="headerLink" NavigateUrl="selectSession.aspx"
				Visible="False">Start Session</asp:HyperLink>
			&nbsp;<asp:Label id="separator2" runat="server" CssClass="headerLink" Visible="False">|</asp:Label>
			<asp:HyperLink id="link_Admin" runat="server" CssClass="headerLink" NavigateUrl="admin.aspx" Visible="False">Administer</asp:HyperLink></TD>
	</TR>
</TABLE>
