<%@ Page language="c#" Codebehind="selectSession.aspx.cs" AutoEventWireup="false" Inherits="TWOnline.selectSession" %>
<%@ Register TagPrefix="user" TagName="main_header" src="TWOnlineHeader.ascx" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>Start Telewindows Session</title>
		<meta name="GENERATOR" Content="Microsoft Visual Studio .NET 7.1">
		<meta name="CODE_LANGUAGE" Content="C#">
		<meta name="vs_defaultClientScript" content="JavaScript">
		<meta name="vs_targetSchema" content="http://schemas.microsoft.com/intellisense/ie5">
		<link rel="STYLESHEET" type="text/css" href="TWOnlineStyles.css">
	</HEAD>
	<body bottomMargin="0" leftMargin="2" topMargin="0" rightMargin="2">
		<form id="Form1" method="post" runat="server">
			<user:main_header id="main_header1" RunAt="server" pageName="selectSession.aspx" NAME="main_header1"></user:main_header>
			<p>Select a server from the list below, and click the Connect button to start a new 
				session,&nbsp;or the Join button to join an existing one.</p>
			<TABLE id="Table1" cellSpacing="1" cellPadding="1" border="0">
				<TR>
					<TD align="center">
						<asp:DataGrid id="dataGridServers" runat="server" CssClass="bodyText" AutoGenerateColumns="False"
							AllowSorting="True">
							<Columns>
								<asp:BoundColumn Visible="False" DataField="serverId"></asp:BoundColumn>
								<asp:BoundColumn Visible="False" DataField="coServerId"></asp:BoundColumn>
								<asp:TemplateColumn SortExpression="inUse">
									<ItemTemplate>
										<asp:Button Enabled='<%# ((bool)DataBinder.Eval(Container.DataItem, "isRunning")==true?true:false)%>' CommandName='<%# ((bool)DataBinder.Eval(Container.DataItem, "inUse")==true?"Join":"Connect") %>' Runat="server" Text='<%#((bool)DataBinder.Eval(Container.DataItem, "inUse")==true?"Join":"Connect") %>' ID="btn_Start" NAME="btn_Start">
										</asp:Button>
									</ItemTemplate>
								</asp:TemplateColumn>
								<asp:BoundColumn ItemStyle-Width="150px" DataField="serverName" SortExpression="serverName" HeaderText="Server"></asp:BoundColumn>
								<asp:BoundColumn ItemStyle-Width="75px" DataField="portNo" SortExpression="portNo" HeaderText="Port"></asp:BoundColumn>
								<asp:TemplateColumn ItemStyle-Width="100px" HeaderText="Status" SortExpression="isRunning">
									<ItemTemplate>
										<asp:Label Runat="server">
											<%# ((bool)DataBinder.Eval(Container.DataItem, "isRunning")==true?((bool)DataBinder.Eval(Container.DataItem, "inUse")==true?"In Use":"Online"):"Stopped")%>
										</asp:Label>
									</ItemTemplate>
								</asp:TemplateColumn>
							</Columns>
						</asp:DataGrid></TD>
				</TR>
				<TR>
					<TD align="center">
						<asp:Button id="btn_Refresh" runat="server" Text="Refresh" ToolTip="Refresh the list of servers."></asp:Button>
					</TD>
				</TR>
			</TABLE>
		</form>
		<P>&nbsp;</P>
	</body>
</HTML>
