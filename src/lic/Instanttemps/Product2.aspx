<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Product2.aspx.cs" Inherits="Default2" %>

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
            .style14
            {
                width: 263px;
            }
            .style15
            {
                width: 162px;
            }
            .style16
            {
                width: 178px;
            }
            #output
            {
                width: 638px;
                height: 253px;
            }
            .style18
            {
                width: 192px;
            }
            .style19
            {
                width: 181px;
            }
        </style>
        
<script src="javascripts/prototype.js" type="text/javascript"></script>
 <script src="javascripts/scriptaculous.js" type="text/javascript"></script>
  <script src="javascripts/gensym.js" type="text/javascript"></script>
</head>
<body onload="page_laod(); return false;">
     <form id="form1" onsubmit="return popHiddenLayer();" runat="server">
<div id="container" class="style8">
  <div id="banner" onclick="Effect.SlideDown('content'); return false;">
    
  </div>
  <div id="navcontainer">
    <ul id="navlist">
      <li id="active"><a href="bundle.aspx">Bundle</a></li>
      <li><a href="Product.aspx">Product</a></li>     
    </ul>
  </div>  
  <div id="content">
  <div id="hiddenLayer" class="POP_LAYER_NONE"> 
      <img style="padding-top:10%;padding-left:250px" src="img/ajax-loader1.gif" /><br /><img style="padding-left:250px" src="img/ajax-loader.gif" />
  </div>
 <div id="input" runat="server">

   <table class="style5">
                <tr>
                    <td class="style15">
                        E - mail :</td>
                    <td class="style14">
                        <asp:TextBox ID="email_txt" runat="server" CssClass="control_width"></asp:TextBox>
                    </td>
                    <td>
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" 
                            ControlToValidate="email_txt" ErrorMessage="Enter Valid Email Adress" 
                            ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*"></asp:RegularExpressionValidator>
                        <div><asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" 
                            ControlToValidate="email_txt" ErrorMessage="Enter Email ID"></asp:RequiredFieldValidator></div>
                    </td>
                </tr>
                <tr>
                    <td class="style15">
                        Company :                     </td>
                    <td class="style14">
                        <asp:DropDownList ID="company_drp" runat="server" CssClass="control_width"
                            DataSourceID="useraccountsAccessDataSource4" DataTextField="company" 
                            DataValueField="company">
                        </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;</td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label1" runat="server" Text="Product : "></asp:Label>
                    </td>
                    <td class="style14">
      <asp:DropDownList ID="productname_cmbbox" runat="server" Height="22px" CssClass="control_width" 
               DataSourceID="AccessDataSource1" DataTextField="productname" 
               DataValueField="productname" 
               onselectedindexchanged="productname_cmbbox_SelectedIndexChanged" AutoPostBack="True">
      </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;</td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label2" runat="server" Text="Version  : "></asp:Label>
                    </td>
                    <td class="style14">
      <asp:DropDownList ID="version_cmbbox" runat="server" Height="22px" CssClass="control_width" 
              DataSourceID="AccessDataSource2" DataTextField="Version" 
              DataValueField="Version" onselectedindexchanged="version_cmbbox_SelectedIndexChanged" 
                            AutoPostBack="True">
      </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;</td>
                </tr>
                <tr>
                    <td class="style15">
                        <span lang="en-us">Platform :</span></td>
                    <td class="style14">
                  <asp:DropDownList ID="platform" runat="server" Height="22px" 
                      CssClass="control_width" DataSourceID="AccessDataSource5" 
                      DataTextField="operatingsystem" DataValueField="operatingsystem">
                  </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;</td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label3" runat="server" Text="Machine Name  : "></asp:Label>
                    </td>
                    <td class="style14">
          <asp:TextBox ID="machinename_txt" runat="server" CssClass="control_width" ></asp:TextBox></td>
                    <td>
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" 
                            ControlToValidate="machine_id_cmbbox" ErrorMessage="Machine Id is mandatory"></asp:RequiredFieldValidator>
                    </td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label4" runat="server" Text="Machine ID  : "></asp:Label>
                    </td>
                    <td class="style14">
      <asp:TextBox ID="machine_id_cmbbox" runat="server" CssClass="control_width" ></asp:TextBox></td>
                    <td>
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                            ControlToValidate="machine_id_cmbbox" ErrorMessage="Enter Machine Name"></asp:RequiredFieldValidator>
                        </td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label5" runat="server" Text="From (MM/DD/YYYY)  : "></asp:Label>
                    </td>
                    <td class="style14">
      <asp:TextBox ID="startdate_pick" runat="server" CssClass="control_width" Enabled="False" ></asp:TextBox></td>
                    <td>
                        <asp:CheckBox ID="nodate_chkBox" CssClass="control_width" runat="server" AutoPostBack="True" 
                            CausesValidation="True" oncheckedchanged="nodate_chkBox_CheckedChanged" 
                            Text="No Expiration Dates" Visible="False" />
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator5" runat="server" 
                            ControlToValidate="startdate_pick" ErrorMessage="Enter Valid Date" 
                            ValidationExpression="\d{1,2}/\d{1,2}/\d{4}"></asp:RegularExpressionValidator>
                    </td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label6" runat="server" Text="To (MM/DD/YYYY)  : "></asp:Label>
                    </td>
                    <td class="style14">
      <asp:TextBox ID="todate_pick" runat="server" CssClass="control_width" Enabled="False" ></asp:TextBox></td>
                    <td>
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator4" runat="server" 
                            ControlToValidate="todate_pick" ErrorMessage="Enter Valid Date" 
                            ValidationExpression="\d{1,2}/\d{1,2}/\d{4}"></asp:RegularExpressionValidator>
                    </td>
                </tr>
                <tr>
                    <td class="style15">
      <asp:Label ID="Label7" runat="server" Text="Process Limit  : " CssClass="control_width" ></asp:Label>
                    </td>
                    <td class="style14">
      <asp:TextBox ID="processlmt_txt" runat="server" CssClass="control_width" >1</asp:TextBox></td>
                    <td>
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator2" runat="server" 
                            ControlToValidate="processlmt_txt" ErrorMessage="Enter valid number" 
                            ToolTip="Number" ValidationExpression="[1-9][0-9]{0,2}"></asp:RegularExpressionValidator>
                    </td>
                </tr>
                <tr>
                    <td class="style15">
           <asp:Label ID="Label8" runat="server" Text="Purpose  : "></asp:Label>
                    </td>
                    <td class="style14">
           <asp:DropDownList ID="purpose" runat="server" Height="22px" CssClass="control_width" >
           <asp:ListItem>Permanent</asp:ListItem>
                      <asp:ListItem>Demo</asp:ListItem>
                      <asp:ListItem>Evaluation</asp:ListItem>
                      <asp:ListItem>Training</asp:ListItem>
                      <asp:ListItem>Emergency</asp:ListItem>
                      <asp:ListItem>Other</asp:ListItem>
           </asp:DropDownList>
                    </td>
                    <td>
                        &nbsp;</td>
                </tr>
                </table>
                     <div id="g2options"><asp:Panel ID="G2modules_grpbox" runat="server" GroupingText="G2 - Options" 
                Height="340px"><p>
                    <table class="style7" cellspacing="2">
                        <tr>
                            <td class="style16">
                                <span lang="en-us">
                                <asp:Label ID="Label10" runat="server" Text="Float TW Process Limit : "></asp:Label>
                                </span>
                            </td>
                            <td colspan="2">
                                <span lang="en-us">
                                <asp:TextBox ID="TW_limit" runat="server" CssClass="control_width" Text="1"></asp:TextBox>
                                &nbsp;<asp:RegularExpressionValidator ID="RegularExpressionValidator6" 
                                    runat="server" ControlToValidate="TW_limit" ErrorMessage="Enter valid number" 
                                    ToolTip="Number" ValidationExpression="[0-9][0-9]{0,2}"></asp:RegularExpressionValidator>
                                </span>
                            </td>
                            <td>
                                &nbsp;</td>
                        </tr>
                        <tr>
                            <td class="style16">
                                <span lang="en-us">
                                <asp:Label ID="Label11" runat="server" Text="Float TW2 Process Limit : "></asp:Label>
                                </span>
                            </td>
                            <td colspan="2">
                                <span lang="en-us">
                                <asp:TextBox ID="tw2_txt" runat="server" CssClass="control_width" >0</asp:TextBox>
                                &nbsp;<asp:RegularExpressionValidator ID="RegularExpressionValidator7" 
                                    runat="server" ControlToValidate="tw2_txt" ErrorMessage="Enter valid number" 
                                    ToolTip="Number" ValidationExpression="[0-9]{1,3}"></asp:RegularExpressionValidator>
                                </span>
                            </td>
                            <td>
                                &nbsp;</td>
                        </tr>
                        <tr>
                            <td class="style16">
                                <span lang="en-us">
                                <asp:Label ID="Label12" runat="server" Text="License Level : "></asp:Label>
                                </span>
                            </td>
                            <td colspan="2">
                                <span lang="en-us">
                                <asp:DropDownList ID="license_level_cmb" runat="server" Height="22px" 
                                    CssClass="control_width" >
                                    <asp:ListItem Value="offline"></asp:ListItem>
                                    <asp:ListItem>online</asp:ListItem>
                                </asp:DropDownList>
                                </span>
                            </td>
                            <td>
                                &nbsp;</td>
                        </tr>
                        <tr>
                            <td class="style16">
                                <span lang="en-us">
                                <asp:Label ID="Label13" runat="server" Text="License Mode : "></asp:Label>
                                </span>
                            </td>
                            <td colspan="2">
                                <span lang="en-us">
                                <asp:DropDownList ID="licensemode_drpbox" runat="server" Height="22px" 
                                    CssClass="control_width" >
                                    <asp:ListItem Value="Embedded"></asp:ListItem>
                                    <asp:ListItem>Restricted-use</asp:ListItem>
                                    <asp:ListItem Value="Runtime"></asp:ListItem>
                                </asp:DropDownList>
                                </span>
                            </td>
                            <td>
                                &nbsp;</td>
                        </tr>
                        <tr>
                            <td rowspan="4" class="style16">
                                <span lang="en-us">
                                <asp:Label ID="Label14" runat="server" Text="Optional Modules :"></asp:Label>
                                </span>
                            </td>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="gsi_chk" runat="server" Text="GSI" />
                                </span></td>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="gfi_chk" runat="server" Text="GFI"/>
                                </span></td>
                            <td rowspan="4">
                                &nbsp;</td>
                        </tr>
                        <tr>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="icp_chk" runat="server" Text="ICP" />
                                </span>
                            </td>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="javalink_chk" runat="server"  Text="JAVALINK"/>
                                </span>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="lang_nupec" runat="server" Text="Nupec"/>
                                </span>
                            </td>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="lang_chinese" runat="server" Text="Chinese" />
                                </span>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="lang_japanese" runat="server" Text="Japanese" 
                                    />
                                </span>
                            </td>
                            <td>
                                <span lang="en-us">
                                <asp:CheckBox ID="lang_korean" runat="server" Text="Korean"/>
                                </span>
                            </td>
                        </tr>
                    </table>
                </p>
            </asp:Panel></div>
            
          
        <table class="style6">
            <tr>
                <td class="style19">
                    &nbsp;</td>
                <td class="style18">
                    <span>
                    <asp:Button ID="gencodes_btn" runat="server" Height="32px" 
                        onclick="gencodes_btn_Click" Text="Add Component" Width="158px" 
                        style="margin-left: 0px" />
                    </span>
                </td>
                <td>
                    <asp:Button ID="done_btn" runat="server" onclick="done_btn_Click" 
                        Text="Done And Email -&gt;" Width="163px" Height="32px" />
                        </td>
            </tr>
            </table></div>
        <br />
        <div id="result" runat="server">
            <textarea id="output"  runat ="server"></textarea>
            <textarea id="okout" style="visibility:hidden" runat ="server"></textarea></div>
        <br />
          <asp:AccessDataSource ID="AccessDataSource3" runat="server" 
              DataFile="~/gensym.mdb" 
              SelectCommand="SELECT [productname], [authorization-method] AS column1, [Version], [ok-query-name] AS column2, [ok-entry-name] AS column3 FROM [products_individiual] WHERE (([productname] = ?) AND ([Version] = ?))">
              <SelectParameters>
                  <asp:ControlParameter ControlID="productname_cmbbox" Name="productname" 
                      PropertyName="SelectedValue" Type="String" />
                  <asp:ControlParameter ControlID="version_cmbbox" Name="Version" 
                      PropertyName="SelectedValue" Type="String" />
              </SelectParameters>
          </asp:AccessDataSource>
                <asp:AccessDataSource ID="AccessDataSource1" runat="server" 
                    DataFile="~/gensym.mdb" 
                    
                    
              SelectCommand="SELECT DISTINCT [productname] FROM [products_individiual] ORDER BY [productname]">
                </asp:AccessDataSource>
        </span>
            
      
      <span lang="en-us">&nbsp;&nbsp;
        <asp:AccessDataSource ID="AccessDataSource5" runat="server" 
            DataFile="~/gensym_accounts.mdb" 
            SelectCommand="SELECT DISTINCT [operatingsystem] FROM [OS] ORDER BY [operatingsystem] DESC">
        </asp:AccessDataSource>
                <asp:AccessDataSource ID="AccessDataSource2" runat="server" 
                    DataFile="~/gensym.mdb" 
                    
                    
              SelectCommand="SELECT [Version] FROM [products_individiual] WHERE ([productname] = ?) ORDER BY [Version] DESC">
                    <SelectParameters>
                        <asp:ControlParameter ControlID="productname_cmbbox" Name="productname" 
                            PropertyName="SelectedValue" Type="String" />
                    </SelectParameters>
                </asp:AccessDataSource>
                        <asp:AccessDataSource ID="useraccountsAccessDataSource4" runat="server" 
                            DataFile="~/gensym_accounts.mdb" 
                            SelectCommand="SELECT DISTINCT [company] FROM [useraccounts] WHERE ([valid] = true)">
                        </asp:AccessDataSource>
          </span>

        <asp:AccessDataSource ID="AccessDataSource4" runat="server" 
            DataFile="~/gensym_accounts.mdb" 
            SelectCommand="SELECT [operatingsystem] FROM [OS] ORDER BY [operatingsystem] DESC">
        </asp:AccessDataSource>

  </div>
</div>      
</form>
 
</body>
</html>
