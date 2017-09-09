<%@ Control Language="c#" AutoEventWireup="false" Codebehind="TWOnlineHeader.ascx.cs" Inherits="WebScorFileMgr.TWOnlineHeader" TargetSchema="http://schemas.microsoft.com/intellisense/ie5" %>
<TABLE id="Table2" cellSpacing="0" cellPadding="0" width="100%" border="0">
	<TR>
		<TD style="MARGIN-LEFT: 10px" bgColor="#000000"><IMG alt="" src="images/main_logo.gif"></TD>
		<td valign="bottom" align="right" bgColor="#000000"><asp:Label id="label_Welcome" runat="server" CssClass="headerWelcome" Visible="False"></asp:Label></td>
	</TR>
</TABLE>
<TABLE id="Table1" cellSpacing="1" cellPadding="2" width="100%" background="images/nav_tile.gif"
	border="0">
	<TR>
		<TD>
			<asp:HyperLink id="link_Upload" runat="server" CssClass="headerLink" NavigateUrl="upload.aspx"
				Visible="False">Upload Files</asp:HyperLink>
			&nbsp;<asp:Label id="separator2" runat="server" CssClass="headerLink" Visible="False">|</asp:Label>
			<asp:HyperLink id="link_Download" runat="server" CssClass="headerLink" NavigateUrl="download.aspx"
				Visible="False">Download Files</asp:HyperLink></TD>
	</TR>
</TABLE>
