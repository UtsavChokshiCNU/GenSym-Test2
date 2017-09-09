<%@ Page Language="C#" AutoEventWireup="true" CodeFile="eulalist.aspx.cs" Inherits="eulalist" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:GridView ID="GridView1" runat="server" AllowPaging="True" 
            AllowSorting="True" AutoGenerateColumns="False" DataKeyNames="id" 
            DataSourceID="SqlDataSource1" 
            EmptyDataText="There are no data records to display." Height="299px" 
            Width="893px">
            <Columns>
                <asp:BoundField DataField="agent" HeaderText="agent" SortExpression="agent" />
                <asp:BoundField DataField="name" HeaderText="name" SortExpression="name" />
                <asp:BoundField DataField="company" HeaderText="company" 
                    SortExpression="company" />
                <asp:BoundField DataField="eulaagreed" HeaderText="eulaagreed" 
                    SortExpression="eulaagreed" />
            </Columns>
        </asp:GridView>
    
    </div>
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
        ConnectionString="<%$ ConnectionStrings:GensymServerManagementConnectionString1 %>" 
        DeleteCommand="DELETE FROM [eula_agreements_table] WHERE [id] = @id" 
        InsertCommand="INSERT INTO [eula_agreements_table] ([agent], [name], [company], [eulaagreed]) VALUES (@agent, @name, @company, @eulaagreed)" 
        ProviderName="<%$ ConnectionStrings:GensymServerManagementConnectionString1.ProviderName %>" 
        SelectCommand="SELECT [id], [agent], [name], [company], [eulaagreed] FROM [eula_agreements_table]">
        <DeleteParameters>
            <asp:Parameter Name="id" Type="Object" />
        </DeleteParameters>
        <InsertParameters>
            <asp:Parameter Name="agent" Type="String" />
            <asp:Parameter Name="name" Type="String" />
            <asp:Parameter Name="company" Type="String" />
            <asp:Parameter Name="eulaagreed" Type="String" />
        </InsertParameters>
    </asp:SqlDataSource>
    </form>
</body>
</html>
