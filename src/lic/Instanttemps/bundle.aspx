<%@ Page Language="C#" AutoEventWireup="true" CodeFile="bundle.aspx.cs" Inherits="bundle" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>:: Gensym's Instant Temps::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
 <script src="javascripts/prototype.js" type="text/javascript"></script>
 <script src="javascripts/scriptaculous.js" type="text/javascript"></script>
  <script src="javascripts/gensym.js" type="text/javascript"></script>
<link href="style.css" rel="stylesheet" type="text/css" />        
       
        <style type="text/css">
            #okout
            {
                width: 684px;
                height: 929px;
            }
            .style18
            {
                width: 163px;
            }
            .style27
            {
            }
            .style29
            {
                width: 131px;
            }
            .style32
            {
                width: 175px;
            }
            .style34
            {
                width: 95px;
            }
            .style35
            {
                width: 159px;
            }
            .style36
            {
                width: 129px;
            }
            .style38
            {
                width: 374px;
            }
            .style39
            {
                width: 187px;
            }
            #output
            {
                width: 680px;
                height: 265px;
            }
            </style>
</head>
<body onload="page_laod(); return false;">
    <form id="form1" onsubmit="return popHiddenLayer();" runat="server">
    <div id="container" class="style8">
  <div id="banner">
      </div>
  <div id="navcontainer">
    <ul id="navlist">
      <li id="avtive"><a href="bundle.aspx">Bundle</a></li>
      <li><a href="Product.aspx">Product</a></li>     
    </ul>
  </div>
  <div id="content">
  <div id="hiddenLayer" class="POP_LAYER_NONE" style="height: 800px;"> 
      <img style="padding-top:10%;padding-left:250px" src="img/ajax-loader1.gif" /><br /><img style="padding-left:250px" src="img/ajax-loader.gif" />
  </div>
       <div id="input" runat="server"><table class="style7">
      
          <tr>
              <td class="style32">
                        E - mail :</td>
              <td colspan="2" class="style27">
                        <asp:TextBox ID="email_txt" runat="server" CssClass="control_width"></asp:TextBox>
              </td>
              <td class="style18">
                        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" 
                            ControlToValidate="email_txt" ErrorMessage="Enter Valid Email Adress" 
                            ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*"></asp:RegularExpressionValidator>
                        <br /><asp:RequiredFieldValidator ID="RequiredFieldValidator3" runat="server" 
                            ControlToValidate="email_txt" ErrorMessage="Enter Email ID"></asp:RequiredFieldValidator>
                    </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Product :</span></td>
              <td colspan="2" class="style27">
                  <asp:DropDownList ID="product" runat="server" Height="22px"  
                      CssClass="control_width" AutoPostBack="True" 
                      DataSourceID="bundleAccessDataSource1" DataTextField="product_name" 
                      DataValueField="product_name" 
                      onselectedindexchanged="product_SelectedIndexChanged">
                  </asp:DropDownList>
              </td>
              <td class="style18">
                  </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Version :</span></td>
              <td colspan="2">
                  <asp:DropDownList ID="version" runat="server" Height="22px" 
                      CssClass="control_width" AutoPostBack="True" 
                      DataSourceID="bundleAccessDataSourceversion" DataTextField="version" 
                      onselectedindexchanged="version_SelectedIndexChanged">
                  </asp:DropDownList>
              </td>
              <td class="style18">
                  &nbsp;</td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Type :</span></td>
              <td colspan="2">
                  <asp:DropDownList ID="type" runat="server" Height="22px" 
                      CssClass="control_width" AutoPostBack="True" 
                      DataSourceID="bundleAccessDataSourcetype" DataTextField="product_type">
                  </asp:DropDownList>
              </td>
              <td class="style18">
                  &nbsp;</td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Platform :</span></td>
              <td colspan="2">
                  <asp:DropDownList ID="platform" runat="server" Height="22px" 
                      CssClass="control_width" DataSourceID="AccessDataSource1" 
                      DataTextField="operatingsystem" DataValueField="operatingsystem">
                  </asp:DropDownList>
              </td>
              <td class="style18">
                  &nbsp;</td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Label : </span>
              </td>
              <td colspan="2">
                  <asp:TextBox ID="txt_machine_label" runat="server" CssClass="control_width"></asp:TextBox>
              </td>
              <td class="style18">
                  &nbsp;</td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Machine Name :</span></td>
              <td colspan="2">
                  <asp:TextBox ID="txt_machine_name" runat="server" CssClass="control_width"></asp:TextBox>
              </td>
              <td class="style18">
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator1" runat="server" 
                            ControlToValidate="txt_machine_name" 
                      ErrorMessage="Enter Machine Name"></asp:RequiredFieldValidator>
                        </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Machine ID :</span></td>
              <td colspan="2">
                  <asp:TextBox ID="txt_machine_id" runat="server" CssClass="control_width"></asp:TextBox>
              </td>
              <td class="style18">
                        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" runat="server" 
                            ControlToValidate="txt_machine_id" 
                      ErrorMessage="Machine Id is mandatory"></asp:RequiredFieldValidator>
                    </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">From :(MM/DD/YYYY)</span></td>
              <td colspan="2">
                  <asp:TextBox ID="startdate_pick" runat="server" CssClass="control_width"></asp:TextBox>
              </td>
              <td class="style18">
                  <asp:CheckBox ID="nodate_chkBox" runat="server" 
                      oncheckedchanged="from_null_chkBox_CheckedChanged" 
                      Text="No Expiration Dates" AutoPostBack="True" Visible="False" />
                  <asp:RegularExpressionValidator ID="RegularExpressionValidator5" runat="server" 
                      ControlToValidate="startdate_pick" ErrorMessage="Enter Valid Date" 
                      ValidationExpression="\d{1,2}/\d{1,2}/\d{4}"></asp:RegularExpressionValidator>
              </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">To :(MM/DD/YYYY)</span></td>
              <td colspan="2">
                  <asp:TextBox ID="todate_pick" runat="server" CssClass="control_width" 
                      ReadOnly="True"></asp:TextBox>
              </td>
              <td class="style18">
                  <asp:RegularExpressionValidator ID="RegularExpressionValidator4" runat="server" 
                      ControlToValidate="todate_pick" ErrorMessage="Enter Valid Date" 
                      ValidationExpression="\d{1,2}/\d{1,2}/\d{4}"></asp:RegularExpressionValidator>
                        </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Process Limit :</span></td>
              <td colspan="2">
                  <asp:TextBox ID="process_limit" runat="server" CssClass="control_width" 
                      Height="20px">1</asp:TextBox>
              </td>
              <td class="style18">
                  <asp:RegularExpressionValidator ID="RegularExpressionValidator2" runat="server" 
                      ControlToValidate="process_limit" ErrorMessage="Enter valid number" 
                      ToolTip="Number" ValidationExpression="[1-9][0-9]{0,2}"></asp:RegularExpressionValidator>
                        </td>
          </tr>
          <tr id ="twtablerow" runat="server">
              <td  class="style32">
                  <span lang="en-us">Float Tw Process Limit :</span></td>
              <td colspan="2">
                  <asp:TextBox ID="TW_limit" runat="server" CssClass="control_width">0</asp:TextBox>
              </td>
              <td class="style18">
                  <asp:RegularExpressionValidator ID="RegularExpressionValidator3" runat="server" 
                      ControlToValidate="TW_limit" ErrorMessage="Enter valid number" ToolTip="Number" 
                      ValidationExpression="[0-9][0-9]{0,2}"></asp:RegularExpressionValidator>
                        </td>
          </tr>
          <tr>
              <td class="style32">
                  <span lang="en-us">Purpose :</span></td>
              <td colspan="2">
                  <asp:DropDownList ID="purpose" runat="server" CssClass="control_width
                  " Height="22px">
                      <asp:ListItem>Permanent</asp:ListItem>
                      <asp:ListItem>Demo</asp:ListItem>
                      <asp:ListItem>Evaluation</asp:ListItem>
                      <asp:ListItem>Training</asp:ListItem>
                      <asp:ListItem>Emergency</asp:ListItem>
                      <asp:ListItem>Other</asp:ListItem>
                  </asp:DropDownList>
              </td>
              <td class="style18">
                  &nbsp;</td>
          </tr>
          <tr>
              <td class="style32" rowspan="2">
                  <span lang="en-us">Optional G2 Modules :</span></td>
              <td class="style29">
                  <asp:CheckBox ID="lang_nupec" runat="server" Text="Nupec" />
              </td>
              <td class="style34">
                  <asp:CheckBox ID="lang_chinese" runat="server" Text="Chinese" />
              </td>
              <td rowspan="2" class="style18">
                  &nbsp;</td>
                    </tr>
                    <tr>
                        <td class="style29">
                            <asp:CheckBox ID="lang_japanese" runat="server" Text="Japanese" />
                        </td>
                        <td class="style34">
                            <asp:CheckBox ID="lang_korean" runat="server" Text="Korean " />
                        </td>
                    </tr>
                    </table>
                <div id="g2options"><table style="width: 79%;">
                    <tr>
                        <td class="style35">
                            &nbsp;</td>
                        <td class="style36">
                            <asp:CheckBox ID="rethink" runat="server" Text="ReThink " 
                                oncheckedchanged="rethink_CheckedChanged" />
                        </td>
                        <td>
                            <asp:CheckBox ID="escor" runat="server" Text="e-SCOR" 
                                oncheckedchanged="escor_CheckedChanged" />
                        </td>
                    </tr>
                    <tr>
                        <td class="style35">
                            <span lang="en-us">Optional KBs :</span></td>
               <td class="style36">
                            <asp:CheckBox ID="neuroonline" runat="server" Text="NeurOn-Line" 
                                oncheckedchanged="neuroonline_CheckedChanged" />
                        </td>
               <td>
                            <asp:CheckBox ID="gda" runat="server" Text="GDA" 
                                oncheckedchanged="gda_CheckedChanged" />
                        </td>
           </tr>
           <tr>
               <td class="style35">
                   &nbsp;</td>
               <td class="style36">
                            <asp:CheckBox ID="optegrity" runat="server" Text="Optegrity " 
                                oncheckedchanged="optegrity_CheckedChanged" />
                        </td>
               <td>
                            <asp:CheckBox ID="integrity" runat="server" Text="Integrity " 
                                oncheckedchanged="integrity_CheckedChanged" />
                        </td>
           </tr>
       </table></div>       
            <table style="width:100%;">
                <tr>
                    <td class="style39">
                        &nbsp;</td>
                    <td class="style38">
                        <asp:Button ID="btn_generateok" runat="server" Height="40px" Text="Generate OK File" 
                      Width="150px"  onclick="btn_generateok_Click" style="text-align: center" />
                        </td>
                    <td>
                        &nbsp;</td>
                </tr>
            </table></div>
            <br />
                <div id="result" runat="server">   
                    <textarea id="output" runat ="server"></textarea>                 
                    <textarea id="okout" runat="server" style="visibility:hidden"></textarea></div></div>
  </div>
                  <asp:AccessDataSource ID="bundleAccessDataSourceversion" runat="server" 
                      DataFile="~/gensym.mdb" 
                      SelectCommand="SELECT DISTINCT [version] FROM [products] WHERE ([product_name] = ?) ORDER BY [version] DESC">
                      <SelectParameters>
                          <asp:ControlParameter ControlID="product" Name="product_name" 
                              PropertyName="SelectedValue" Type="String" />
                      </SelectParameters>
                  </asp:AccessDataSource>
                  <asp:AccessDataSource ID="bundleAccessDataSource1" runat="server" 
                      DataFile="~/gensym.mdb" 
                      SelectCommand="SELECT DISTINCT [product_name] FROM [products] ORDER BY [product_name]">
                  </asp:AccessDataSource>
                  <asp:AccessDataSource ID="bundleAccessDataSourcetype" runat="server" 
                      DataFile="~/gensym.mdb" 
                      SelectCommand="SELECT DISTINCT [product_type] FROM [products] WHERE (([product_name] = ?) AND ([version] = ?)) ORDER BY [product_type]">
                      <SelectParameters>
                          <asp:ControlParameter ControlID="product" Name="product_name" 
                              PropertyName="SelectedValue" Type="String" />
                          <asp:ControlParameter ControlID="version" Name="version" 
                              PropertyName="SelectedValue" Type="Decimal" />
                      </SelectParameters>
                  </asp:AccessDataSource>
              <asp:AccessDataSource ID="getoknameAccessDataSource" runat="server" 
            DataFile="~/gensym.mdb" 
            SelectCommand="SELECT [bundle-name] AS column1, [ok-name] AS column2 FROM [products] WHERE (([product_name] = ?) AND ([product_type] = ?) AND ([version] = ?))">
                  <SelectParameters>
                      <asp:ControlParameter ControlID="product" Name="product_name" 
                          PropertyName="SelectedValue" Type="String" />
                      <asp:ControlParameter ControlID="type" Name="product_type" 
                          PropertyName="SelectedValue" Type="String" />
                      <asp:ControlParameter ControlID="version" Name="version" 
                          PropertyName="SelectedValue" Type="Decimal" />
                  </SelectParameters>
        </asp:AccessDataSource>
        
      
      <span lang="en-us">
                        <asp:AccessDataSource ID="useraccountsAccessDataSource4" runat="server" 
                            DataFile="~/gensym_accounts.mdb" 
                            SelectCommand="SELECT DISTINCT [company] FROM [useraccounts] WHERE ([valid] = true)">
                        </asp:AccessDataSource>
          <asp:AccessDataSource ID="AccessDataSource1" runat="server" 
            DataFile="~/gensym_accounts.mdb" 
            SelectCommand="SELECT [operatingsystem] FROM [OS] ORDER BY [operatingsystem] DESC">
        </asp:AccessDataSource>
          </span>

    </form>
</body>
</html>
