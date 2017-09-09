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
using System.Data.SqlClient;
using System.Text;

public partial class admin : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (!IsPostBack)
            content.Visible = false;
        else
            content.Visible = true;
    }
    protected void add_btn_Click(object sender, EventArgs e)
    {
        AccessDataSource2.Insert();
        AccessDataSource1.DataBind();
        GridView1.DataBind();
       
        

    }
    protected void login_btn_Click(object sender, EventArgs e)
    {
        DataTable accountstable = new DataTable();
        AccessDataSource AD = new AccessDataSource("~/gensym_accounts.mdb", "SELECT username,password FROM admin_accounts WHERE ((username = ?) AND (password = ?))");
        AD.SelectParameters.Add("username", username_txt.Text);
        AD.SelectParameters.Add("password", password_txt.Text);
        DataView dv = (DataView)AD.Select(DataSourceSelectArguments.Empty);
        accountstable = dv.ToTable();

        if (accountstable.Rows.Count == 1)
        {

            content.Visible = true;
            login_div.Visible = false;
            string sec_cook = FormsAuthentication.HashPasswordForStoringInConfigFile(password_txt.Text, "sha1");
            HttpCookie sec = new HttpCookie("val",sec_cook);
            sec.Expires= DateTime.Now.AddHours(2);
            Response.Cookies.Set(sec);      
        }
        else
        {
            content.Visible = false;
            Response.Cookies["val"].Expires = DateTime.Now.AddHours(-1);
            error_lbl.Text = "INVALID USERNAME AND PASSWORD";
            
        }

    }
    protected void logout_btn_Click(object sender, EventArgs e)
    {
        Response.Redirect("admin.aspx");
    }
    protected void ButtonExportToXls_Click(object sender, EventArgs e)
    {
        ExportToExcel(SqlDataSource2, "okFileGenerated");
    }
    public void ExportToExcel(SqlDataSource dataSrc, string fileName)
    {
        //Add Response header 

        Response.Clear();
        Response.AddHeader("content-disposition", string.Format("attachment;filename={0}.csv", fileName));
        Response.Charset = "";
        Response.ContentType = "application/vnd.xls";
        //GET Data From Database                

        SqlConnection cn = new SqlConnection(dataSrc.ConnectionString);
        string query = dataSrc.SelectCommand.Replace("\r\n", " ").Replace("\t", " ");

        SqlCommand cmd = new SqlCommand(query, cn);

        cmd.CommandTimeout = 999999;
        cmd.CommandType = CommandType.Text;
        try
        {
            cn.Open();
            SqlDataReader dr = cmd.ExecuteReader();
            StringBuilder sb = new StringBuilder();
            //Add Header          

            for (int count = 0; count < dr.FieldCount; count++)
            {
                if (dr.GetName(count) != null)
                    sb.Append(dr.GetName(count));
                if (count < dr.FieldCount - 1)
                {
                    sb.Append(",");
                }
            }
            Response.Write(sb.ToString() + "\n");
            Response.Flush();
            //Append Data

            while (dr.Read())
            {
                sb = new StringBuilder();

                for (int col = 0; col < dr.FieldCount - 1; col++)
                {
                    if (!dr.IsDBNull(col))
                        sb.Append(dr.GetValue(col).ToString().Replace(",", " "));
                    sb.Append(",");
                }
                if (!dr.IsDBNull(dr.FieldCount - 1))
                    sb.Append(dr.GetValue(dr.FieldCount - 1).ToString().Replace(",", " "));
                Response.Write(sb.ToString() + "\n");
                Response.Flush();
            }
            dr.Dispose();
        }
        catch (Exception ex)
        {
            Response.Write(ex.Message);
        }
        finally
        {
            cmd.Connection.Close();
            cn.Close();
        }
        Response.End();

    }
}
