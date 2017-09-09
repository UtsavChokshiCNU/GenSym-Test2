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
using System.IO;
using System.Text;
using System.Data.SqlClient;

public partial class okfiles : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
       if (Request.Cookies["val"]== null)
            Response.Redirect("admin.aspx");
    }
    protected void ButtonExportToExcel_Click(object sender, EventArgs e)
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
