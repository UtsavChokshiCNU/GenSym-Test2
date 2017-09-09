using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using GensymLicense;

public partial class accounts : System.Web.UI.Page
{
    okfile ok = new okfile();
    protected void Page_Load(object sender, EventArgs e)
    {
        output.Visible = false;
        try
        {
            error_string.Text = Request.Cookies["errorstring"].Value;
            Response.Cookies.Remove("errorstring");           
        }
        catch { }
    }
    protected void apply_btn_Click(object sender, EventArgs e)
    {
       
        string bodydata;
        bodydata = "We have received your request with the following information. We will send you an update soon\n";
            bodydata = bodydata +  "\nEmail ID : " + email_txt.Text;
        bodydata = bodydata + "\nCompany : " + company_txt.Value;

        bodydata = bodydata + "\n\nNotes : " + notes_txt.Value;   
        ok.sendmail(email_txt.Text, bodydata, "Re:Gensym - Access Request");

        output.Visible = true;
        output.Value = bodydata.ToString();
        input.Visible = false;
        
    }
    
}
