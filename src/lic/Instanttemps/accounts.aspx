<%@ Page Language="C#" AutoEventWireup="true" CodeFile="accounts.aspx.cs" Inherits="accounts" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title>:: Gensym License Generator::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<script src="javascripts/prototype.js" type="text/javascript"></script>
 <script src="javascripts/scriptaculous.js" type="text/javascript"></script>
  <script src="javascripts/gensym.js" type="text/javascript"></script>
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
            }
            #Text3
            {
                height: 304px;
                width: 452px;
            }
            #Button1
            {
                width: 138px;
            }
            #notes
            {
                height: 298px;
                width: 442px;
            }
            #notes_txt
            {
                height: 280px;
                width: 386px;
            }
            .style15
            {
                width: 391px;
            }
            #output
            {
                width: 623px;
                height: 343px;
            }
        </style>
</head>
<body>
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
  <div id="hiddenLayer" class="POP_LAYER_NONE"> 
      <img style="padding-top:10%;padding-left:250px" src="img/ajax-loader1.gif" /><br /><img style="padding-left:250px" src="img/ajax-loader.gif" />
  </div>      
      <div id="input" runat="server">
      <asp:Label ID="error_string" runat="server" Font-Size="Medium" ForeColor="Red"></asp:Label>
          <table style="width:101%;">
              <tr>
                  <td class="style14">
                      E - Mail ID * :</td>
                  <td class="style15">
                      <asp:TextBox ID="email_txt" runat="server"></asp:TextBox>
                  </td>
                  <td>
                      <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server" 
                          ControlToValidate="email_txt" ErrorMessage="Enter Valid Email Address" 
                          ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*"></asp:RegularExpressionValidator>
                  </td>
              </tr>
              <tr>
                  <td class="style14">
                      Company * :</td>
                  <td class="style15">
                      <input id="company_txt" type="text" runat="server" /></td>
                  <td>
                      &nbsp;</td>
              </tr>
              <tr>
                  <td class="style14">
                      Extra Note :</td>
                  <td class="style15">
                      <textarea id="notes_txt" name="S1" runat="server" rows="2"></textarea></td>
                  <td>
                      &nbsp;</td>
              </tr>
              <tr>
                  <td class="style14">
                      &nbsp;</td>
                        <td class="style15">
                            <asp:Button ID="apply_btn" OnClientClick="Effect.BlindUp('input');" runat="server" onclick="apply_btn_Click" 
                                Text="APPLY" />
                  </td>
                        <td>
                            &nbsp;</td>
                    </tr>
              <tr>
                  <td class="style14" colspan="3">
                      &nbsp;* - Fields are mandatory&nbsp;</td>
                    </tr>
                </table>
      
      </div>
    </div>
        <div id="result"   style="padding-left:50px">
            <textarea id="output" runat="server" name="S2"></textarea></div>
    </div>
    </form>
</body>
</html>
