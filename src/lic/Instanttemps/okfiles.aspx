<%@ Page Language="C#" AutoEventWireup="true" CodeFile="okfiles.aspx.cs" Inherits="okfiles" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Untitled Page</title>
</head>
<body>
    <form id="form1" runat="server">
    <asp:Button ID="ButtonExportToExcel" runat="server" onclick="ButtonExportToExcel_Click" Text="Export To Excel" Width="145px" />                   
    <asp:SqlDataSource ID="SqlDataSource2" runat="server" 
        ConnectionString="<%$ ConnectionStrings:GensymServerManagement_ConnectionString %>" 
        ProviderName="<%$ ConnectionStrings:GensymServerManagement_ConnectionString.ProviderName %>" 
        SelectCommand="SELECT [creationdate], [userid], [company], [product], [version], [type], [platform], [label], [machinename], [machineid], [fromdate], [todate], [processlimit], [twlimit], [tw2limit], [purpose], [licenselevel], [licensemode], [optionalmodules], [optionalkbs] FROM [queryandok]">
    </asp:SqlDataSource>
    <div>
    
    </div>
    <asp:GridView ID="GridView1" runat="server" AllowPaging="True" 
        AllowSorting="True" AutoGenerateColumns="False" DataSourceID="SqlDataSource1" 
        EmptyDataText="There are no data records to display.">
        <Columns>
            <asp:CommandField ShowSelectButton="True" />
            <asp:BoundField DataField="creationdate" HeaderText="creationdate" 
                SortExpression="creationdate" />
            <asp:BoundField DataField="userid" HeaderText="userid" 
                SortExpression="userid" />
            <asp:BoundField DataField="company" HeaderText="company" 
                SortExpression="company" />
            <asp:BoundField DataField="product" HeaderText="product" 
                SortExpression="product" />
            <asp:BoundField DataField="version" HeaderText="version" 
                SortExpression="version" />
            <asp:BoundField DataField="type" HeaderText="type" SortExpression="type" />
            <asp:BoundField DataField="platform" HeaderText="platform" 
                SortExpression="platform" />
            <asp:BoundField DataField="label" HeaderText="label" SortExpression="label" />
            <asp:BoundField DataField="machinename" HeaderText="machinename" 
                SortExpression="machinename" />
            <asp:BoundField DataField="machineid" HeaderText="machineid" 
                SortExpression="machineid" />
            <asp:BoundField DataField="fromdate" HeaderText="fromdate" 
                SortExpression="fromdate" />
            <asp:BoundField DataField="todate" HeaderText="todate" 
                SortExpression="todate" />
            <asp:BoundField DataField="processlimit" HeaderText="processlimit" 
                SortExpression="processlimit" />
            <asp:BoundField DataField="twlimit" HeaderText="twlimit" 
                SortExpression="twlimit" />
            <asp:BoundField DataField="tw2limit" HeaderText="tw2limit" 
                SortExpression="tw2limit" />
            <asp:BoundField DataField="purpose" HeaderText="purpose" 
                SortExpression="purpose" />
            <asp:BoundField DataField="licenselevel" HeaderText="licenselevel" 
                SortExpression="licenselevel" />
            <asp:BoundField DataField="licensemode" HeaderText="licensemode" 
                SortExpression="licensemode" />
            <asp:BoundField DataField="optionalmodules" HeaderText="optionalmodules" 
                SortExpression="optionalmodules" />
            <asp:BoundField DataField="optionalkbs" HeaderText="optionalkbs" 
                SortExpression="optionalkbs" />
            <asp:BoundField DataField="okfileoutput" HeaderText="okfileoutput" 
                SortExpression="okfileoutput" />
        </Columns>
    </asp:GridView>
    <asp:SqlDataSource ID="SqlDataSource1" runat="server" 
        ConnectionString="<%$ ConnectionStrings:GensymServerManagement_ConnectionString %>" 
        ProviderName="<%$ ConnectionStrings:GensymServerManagement_ConnectionString.ProviderName %>" 
        SelectCommand="SELECT [ID], [creationdate], [userid], [company], [product], [version], [type], [platform], [label], [machinename], [machineid], [fromdate], [todate], [processlimit], [twlimit], [tw2limit], [purpose], [licenselevel], [licensemode], [optionalmodules], [optionalkbs], [okfileoutput] FROM [queryandok]">
    </asp:SqlDataSource>
    </form>
</body>
</html>
