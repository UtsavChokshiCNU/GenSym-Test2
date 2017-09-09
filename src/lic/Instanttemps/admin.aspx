<%@ Page Language="C#" AutoEventWireup="true" CodeFile="admin.aspx.cs" Inherits="admin" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>:: Gensym License Generator::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link href="style.css" rel="stylesheet" type="text/css" />
        <style type="text/css">
            #TextArea1
            {
                height: 698px;
                width: 682px;
            }
            #okout
            {
                width: 668px;
                height: 424px;
            }
            #form1
            {
                height: 511px;
            }
            .style14
            {
                width: 231px;
            }
            .style15
            {
                width: 94px;
            }
            .style16
            {
                width: 124px;
                color:Black;
            }
        </style>
      </head>
<body>
    <form id="form1" runat="server">
   
<div id="container" class="style8">
  <div id="banner">
    
  </div>
  <div id="navcontainer">
    <ul id="navlist">
      <li id="avtive"><a href="perm/bundleAdmin.aspx">Bundle</a></li>
      <li><a href="perm/ProductAdmin.aspx">Product</a></li>   
      <li><a href="accounts.aspx">Accounts</a></li>
      <li><a href="okfiles.aspx">Okfiles</a></li>  
      <li><a href="eulalist.aspx">EULA_List</a></li> 
    </ul>
  </div>
  <div id="login_div" runat="server">
      <table style="margin-left:20%;" style="width:60%;">
          <tr>
              <td  style="padding-left:40%;color:Black" colspan="2">
                  LOGIN</td>
                </tr>
                <tr>
                    <td class="style16">
                        Username :</td>
                    <td>
                        <asp:TextBox ID="username_txt" runat="server" Width="194px"></asp:TextBox>
                    </td>
                </tr>
                <tr>
                    <td class="style16">
                        Password</td>
                    <td>
                        <asp:TextBox ID="password_txt" runat="server" Width="194px" TextMode="Password"></asp:TextBox>&nbsp;&nbsp
                         <asp:Button ID="login_btn" runat="server" Text="Login" Width="94px" 
                            Height="33px" onclick="login_btn_Click" />
                    </td>
                </tr>
                <tr>
                    <td class="style16">
                        &nbsp;</td>
                    <td>
                        <asp:Label ID="error_lbl" runat="server" ForeColor="#CC3300"></asp:Label>
                    </td>
                </tr>
            </table>
  </div>
  <div id="content" runat="server">
    <div>
        <table style="width:100%;">
            <tr>
                <td class="style15">
                    Email :</td>
                        <td class="style14">
                            <asp:TextBox ID="email_txt" runat="server" Width="202px"></asp:TextBox>
                        </td>
                        <td style="padding-left:10%;">
                            <asp:Button ID="logout_btn" runat="server" Text="logout" Width="92px" 
                                onclick="logout_btn_Click" />
                        </td>
                    </tr>
                    <tr>
                        <td class="style15">
                            Company :
                        </td>
                        <td class="style14">
                            <asp:TextBox ID="company_txt" runat="server" Width="206px"></asp:TextBox>
                        </td>
                        <td>
                            &nbsp;</td>
                    </tr>
                    <tr>
                        <td class="style15">
                            &nbsp;</td>
                        <td class="style14">
                            <asp:Button ID="add_btn" runat="server" Text="ADD" onclick="add_btn_Click" 
                                Width="84px" />
                            <asp:Button ID="ButtonExportToXls" runat="server" 
                                Text="Export all OK files Generated to CVS" Visible="true" 
                                onclick="ButtonExportToXls_Click" Width="225px" />
                        </td>
                        <td>
                                <asp:SqlDataSource ID="SqlDataSource2" runat="server" 
        ConnectionString="<%$ ConnectionStrings:GensymServerManagement_ConnectionString %>" 
        ProviderName="<%$ ConnectionStrings:GensymServerManagement_ConnectionString.ProviderName %>" 
        SelectCommand="SELECT [creationdate], [userid], [company], [product], [version], [type], [platform], [label], [machinename], [machineid], [fromdate], [todate], [processlimit], [twlimit], [tw2limit], [purpose], [licenselevel], [licensemode], [optionalmodules], [optionalkbs] FROM [queryandok]">
    </asp:SqlDataSource>
                        </td>
                    </tr>
                </table>
    </div>
      <asp:GridView ID="GridView1" runat="server" AllowPaging="True" 
          AllowSorting="True" AutoGenerateColumns="False" 
          DataSourceID="AccessDataSource1" Width="616px" DataKeyNames="emailid" 
            DataMember="DefaultView">
          <Columns>
              <asp:CommandField ShowDeleteButton="True" ShowEditButton="True" 
                  ShowSelectButton="True" />
              <asp:BoundField DataField="emailid" HeaderText="emailid" 
                  SortExpression="emailid" />
              <asp:BoundField DataField="password" HeaderText="password" 
                  SortExpression="password" />
              <asp:BoundField DataField="company" HeaderText="company" 
                  SortExpression="company" />
              <asp:CheckBoxField DataField="valid" HeaderText="valid" 
                  SortExpression="valid" />
          </Columns>
      </asp:GridView>
    
    </div>
</div>
    <asp:AccessDataSource ID="AccessDataSource1" runat="server" 
        DataFile="~/gensym_accounts.mdb" 
        DeleteCommand="DELETE FROM useraccounts WHERE (emailid = ?)" 
        InsertCommand="INSERT INTO useraccounts(emailid, [password], company, valid) VALUES (?, ?, ?, ?)" 
        SelectCommand="SELECT [emailid], [password], [company], [valid] FROM [useraccounts]" 
        UpdateCommand="UPDATE useraccounts SET [password] = ?, company = ?, valid = ? WHERE (emailid = ?)">
        <DeleteParameters>
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" Type="String" />
        </DeleteParameters>
        <UpdateParameters>
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
        </UpdateParameters>
        <InsertParameters>
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
            <asp:ControlParameter ControlID="GridView1" Name="?" 
                PropertyName="SelectedValue" />
        </InsertParameters>
    </asp:AccessDataSource>
    <asp:AccessDataSource ID="AccessDataSource2" runat="server"
        DataFile="~/gensym_accounts.mdb" 
        
    InsertCommand="INSERT INTO useraccounts(emailid, company) VALUES (?, ?)" 
    SelectCommand="SELECT [emailid], [company] FROM [useraccounts]">
        <InsertParameters>
            <asp:ControlParameter ControlID="email_txt" Name="?" PropertyName="Text" />
            <asp:ControlParameter ControlID="company_txt" Name="?" PropertyName="Text" />
        </InsertParameters>
    </asp:AccessDataSource>
    </form>    
</body>
</html>
