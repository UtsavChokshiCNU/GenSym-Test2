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

public partial class bundle : System.Web.UI.Page
{
    okfile ok = new okfile();
    string okfilename = "g2.ok";
    string mailbody = "Please find the attached g2.ok file along with this mail.\n\nFollowing are the instructions for using the attached file.\n1) Download the ok file to your desired location and save it as g2.ok \n2) Ensure that G2 server, ActiveXLink or other G2 applications are not currently running\n3) Locate your original g2.ok file - the location of the file is\n\tWINDOWS OS: <G2 suite folder>\\g2\\g2.ok,  - for example, if you have installed the G2 suite to c:\\progra~1\\gensym\\g2-8.4r1, the location of g2.ok is  C:\\progra~1\\gensym\\g2-8.4r1\\g2\\g2.ok\n\tUNIX based OS: <G2 suite folder>/g2/g2.ok,  - for example, if you have installed the G2 suite to /home/user/gensym/g2-8.4r1, the location of g2.ok is  /home/user/gensym/g2/g2.ok\n4) Make a backup copy of your g2.ok file, and subsequently, delete it from the G2 suite folder\n5) Place the new downloaded g2.ok file in the \"<G2 suite folder>\\g2\\\"  folder if Windows based OS or \"<G2 suite folder>/g2/\" if it is a UNIX based OS.\n\n** Reverting the g2.ok**\nIf you wish to undo the patch procedure and to revert to the prior version of g2.ok, replace the g2.ok file with the one that was backed up in step 4.\nPlease let us know if you face any difficulty, If so do contact us at service@gensym.com with description of the problem and with a copy of downloaded and old ok files.";
   
    
      protected void Page_Load(object sender, EventArgs e)
    {
        if (!this.IsPostBack)
        {
            string[] cookies = Response.Cookies.AllKeys;
            foreach (string cook in cookies)
                Response.Cookies[cook].Expires = DateTime.Now.AddDays(-1);
            result.Visible = false;
            startdate_pick.Text = DateTime.Today.ToShortDateString();
            todate_pick.Text = DateTime.Today.AddDays(14).ToShortDateString();
            Response.Cookies.Add(new HttpCookie("postback", "false"));
            Response.Cookies.Add(new HttpCookie("updateui", "none#none"));           
        }
        else
            Response.Cookies.Set(new HttpCookie("postback", "true"));

       startdate_pick.Attributes.Add("onchange", "setNewToDate(this);");
       
    }

    protected void btn_generateok_Click(object sender, EventArgs e)
    {
       
        bool valid = validataemmailid();
        if (valid == false)
            Response.Redirect("accounts.aspx");

        ok.setG2_version(product.Text + "-" + version.Text);
        ok.setMinor_version(" Rev-Any " + type.Text);
        ok.setok_file_format_version("2");

        set_query_product();

        ok.setMachine_details(txt_machine_name.Text, txt_machine_id.Text);
        ok.setAuthorized_products(enumerate_auth_products());

        DateTime startdate = new DateTime();
        startdate = Convert.ToDateTime(startdate_pick.Text);
        DateTime enddate = new DateTime();
        enddate = Convert.ToDateTime(todate_pick.Text);

        ok.setExpirationDates(startdate, enddate);
        ok.setMakeg2Secure(false);
        ok.setNoOfG2Process(process_limit.Text);
        ok.setNoTwProcess(TW_limit.Text);
        ok.setNoTw2Process("0");
        result.Visible = true;
        
        if (product.SelectedItem.Value == "G2")
            okout.Value = ok.GenerateOkFile();
        else
        {
            okout.Value = ok.get_tw_autherization("TELEWINDOWS-V8");
            mailbody = mailbody.Replace("g2.ok", "tw.ok");
            okfilename = "tw.ok";
        }

        if (ok.code_error != true)
        {
            if(!ok.sendmail(email_txt.Text, mailbody, "Gensym - G2 Temporary License Codes", okfilename, okout.Value.ToString()))
                    output.Value = "UNABLE TO SEND MAIL TO THIS ID,contact us at service@gensym.com";  
            else
                output.Value = "Ok File has been E-Mailed to the given E-Mail ID, It may take a while to receive the Email. \nFor any further Queries please contact us at service@gensym.com \n\nRegards,\nGensym-Suppport";
        }
        else
        {
            ok.sendmail("ravindra.bg@versata.com", okout.Value.ToString(), "ERROR GENERATING CODE");
            output.Value = "TEMPORARLY LICENSE SERVER IS CURRENTLY DOWN, YOUR REQUEST HAS BEEN MAILED TO OUR LICENSE MANAGER, WE WILL GET BACK TO YOU SOON";
        }


        showoutput();
    
    }
    private void showoutput()
    {
        //output.Value = "Ok File has been E-Mailed to the given E-Mail ID, It may take a while to receive the Email. \nFor any further Queries please contact us at service@gensym.com \n\nRegards,\nGensym-Suppport";
        insertUserInputandOKfile();
        input.Visible = false;
    } 
    protected string enumerate_auth_products()
    {
        string auth_products;
        auth_products = "online ";
        if (type.SelectedValue.ToString().Contains("Deploy"))
            auth_products = auth_products + "Restricted-use ";

        auth_products = auth_products + "JL ";
        if (lang_nupec.Checked)
            auth_products = auth_products + "NUPEC ";
        if (lang_chinese.Checked)
            auth_products = auth_products + "CHINESE ";
        if (lang_japanese.Checked)
            auth_products = auth_products + "JAPANESE ";
        if (lang_korean.Checked)
            auth_products = auth_products + "KOREAN";
        return auth_products;

    }

    protected void rethink_CheckedChanged(object sender, EventArgs e)
    {
        if (rethink.Checked)
            ok.add_layered_products("rethink");
    }

    protected void escor_CheckedChanged(object sender, EventArgs e)
    {
        if (escor.Checked)
            ok.add_layered_products("escor");
    }

    protected void neuroonline_CheckedChanged(object sender, EventArgs e)
    {
        if (neuroonline.Checked)
            ok.add_layered_products("nol");
    }

    protected void integrity_CheckedChanged(object sender, EventArgs e)
    {
        if (integrity.Checked)
        {
            ok.add_layered_products("integrity");
        }
    }

    protected void optegrity_CheckedChanged(object sender, EventArgs e)
    {
        if (optegrity.Checked)
        {
            ok.add_layered_products("optegrity");
        }
    }

    protected void gda_CheckedChanged(object sender, EventArgs e)
    {
        if (gda.Checked)
            ok.add_layered_products("gda");
    }

    protected void from_null_chkBox_CheckedChanged(object sender, EventArgs e)
    {
        if (nodate_chkBox.Checked)
        {
            startdate_pick.Enabled = false;
            todate_pick.Enabled = false;
            okfile.dates_are_null = true;
        }
        else
        {
            startdate_pick.Enabled = true;
            todate_pick.Enabled = true;
            okfile.dates_are_null = false;
        }

    }

    private void set_query_product()
    {
        DataView dv = (DataView)getoknameAccessDataSource.Select(DataSourceSelectArguments.Empty);

        DataTable myTable = new DataTable();
        myTable = dv.ToTable();        
        ok.set_product( myTable.Rows[0][1].ToString(),myTable.Rows[0][0].ToString());

    }
    private bool validataemmailid()
    {
        string emailid = email_txt.Text.Substring(email_txt.Text.IndexOf("@") + 1);

        DataTable myTable = new DataTable();
        AccessDataSource AD = new AccessDataSource("~/gensym_accounts.mdb", "SELECT [company] AS [company], [valid] AS [valid]FROM useraccounts ORDER BY [company] DESC");
        DataView dv = (DataView)AD.Select(DataSourceSelectArguments.Empty);
        myTable = dv.ToTable();

        string companyname;
        for (int i = 0; i < myTable.Rows.Count; i++)
        {
            companyname = myTable.Rows[i]["company"].ToString();
            if (emailid.Trim().ToUpper().Contains(companyname.Trim().ToUpper().ToString()))
            {
                if (myTable.Rows[i]["valid"].ToString() == "True")
                {
                    return true;
                }
                else
                {
                    HttpCookie str = new HttpCookie("errorstring", "THIS EMAIL ID IS CURRENTLY NOT ALLOWED BY INSTANT TEMP, PLEASE CONTACT US FOR MORE INFORMATION ");
                    Response.Cookies.Add(str);

                    return false;
                }

            }

        }
        AD.InsertCommand = "INSERT INTO useraccounts(emailid, [password], company, valid) VALUES ('" + email_txt.Text + "',' ','" + emailid.Trim() + "','0')";
        AD.Insert();
        return true;

    }


    protected void version_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (product.SelectedItem.Value == "G2")
        {
            startdate_pick.Text = "1/1/2009";
            startdate_pick.ReadOnly = true;
            if (Convert.ToDouble(version.SelectedItem.Value) > 8.2)
            {
                    startdate_pick.ReadOnly = false;
                    startdate_pick.Text = DateTime.Today.ToShortDateString();
            }

        }
    }

    private void insertUserInputandOKfile()
    {
        SqlDataSource insertdata = new SqlDataSource();
        insertdata.ConnectionString = ConfigurationManager.ConnectionStrings["GensymServerManagement_ConnectionString"].ConnectionString.ToString();


        string insertcmd = "INSERT INTO queryandok (userid,company,product,version,type,platform,label,machinename,machineid,fromdate,todate,processlimit,twlimit,tw2limit,purpose,licenselevel,licensemode,optionalmodules,optionalkbs,okfileoutput) VALUES(' " + email_txt.Text + "', '" + email_txt.Text.Substring(email_txt.Text.IndexOf('@')+1) +"','" + product.SelectedItem.Value + "','" + version.SelectedItem.Value + "','" + type.SelectedItem.Value + "','" + platform.SelectedItem.Value + "','" + txt_machine_label.Text + "','" + txt_machine_name.Text + "','" + txt_machine_id.Text + "','" + startdate_pick.Text + "','" + todate_pick.Text + "','" + process_limit.Text + "','" + TW_limit.Text + "','0','" + purpose.SelectedItem.Value + "','0','0','" + enumerate_auth_products() + "','" + ok.get_layered_product_names() + "','" + okout.Value + "')";

        insertdata.InsertCommand = insertcmd;
        try
        {
            insertdata.Insert();
        }
        catch { }
    }
    protected void product_SelectedIndexChanged(object sender, EventArgs e)
    {
        startdate_pick.Text = DateTime.Today.ToShortDateString().ToString();
        //fromdate.Enabled = true;
        try
        {
            if (product.SelectedItem.Value == "G2")
            {
                Response.Cookies.Add(new HttpCookie("updateui", "g2options#blinddown"));
                twtablerow.Visible = true;
            }
            else
            {
                Response.Cookies.Add(new HttpCookie("updateui", "g2options#blindup"));
                twtablerow.Visible = false;
            }

        }
        catch { }
    }
}
