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

public partial class service : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        string agent, username, company, redirectpage;
        agent = Request.QueryString["agent"].ToString();
        username = Request.QueryString["name"].ToString();
        company = Request.QueryString["company"].ToString();
        redirectpage = Request.QueryString["redirect"].ToString();

        SqlDataSource insertdata = new SqlDataSource();
        insertdata.ConnectionString = ConfigurationManager.ConnectionStrings["GensymServerManagement_ConnectionString"].ConnectionString.ToString();

        string insertcmd = "INSERT INTO eula_agreements_table(agent,name,company, eulaagreed) VALUES ('" + agent + "','" + username + "','" + company + "','yes')";
        insertdata.InsertCommand = insertcmd;

        try
        {
            if(username!="")
            insertdata.Insert();
        }
        catch { }

        Response.Redirect("http://instanttemps.gensym.com");
    }
}
