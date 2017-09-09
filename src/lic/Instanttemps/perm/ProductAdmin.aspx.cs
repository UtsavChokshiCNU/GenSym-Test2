using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Data.OleDb;
using System.Text;
using System.Net;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using GensymLicense;

public partial class Default2 : System.Web.UI.Page
{ 
    okfile ok = new okfile();
    static StringBuilder main_form;
    static string previousChoosenProduct;
    string okentry_string, okquery_string, authrization_type;
    static StringBuilder g2package ;
    static StringBuilder twpackage ;
    static StringBuilder bridgepackage ;
    static StringBuilder g2packageuserentry ;
    static StringBuilder twpackageuserentry  ;
    static StringBuilder bridgepackageuserentry  ;
    static string G2version;
    static bool mailSent = true;

    string mailbody = "Please find the attached g2.ok file along with this mail.\n\nFollowing are the instructions for using the attached file.\n1) Download the ok file to your desired location and save it as g2.ok \n2) Ensure that G2 server, ActiveXLink or other G2 applications are not currently running\n3) Locate your original g2.ok file - the location of the file is\n\tWINDOWS OS: <G2 suite folder>\\g2\\g2.ok,  - for example, if you have installed the G2 suite to c:\\progra~1\\gensym\\g2-8.4r1, the location of g2.ok is  C:\\progra~1\\gensym\\g2-8.4r1\\g2\\g2.ok\n\tUNIX based OS: <G2 suite folder>/g2/g2.ok,  - for example, if you have installed the G2 suite to /home/user/gensym/g2-8.4r1, the location of g2.ok is  /home/user/gensym/g2/g2.ok\n4) Make a backup copy of your g2.ok file, and subsequently, delete it from the G2 suite folder\n5) Place the new downloaded g2.ok file in the \"<G2 suite folder>\\g2\\\"  folder if Windows based OS or \"<G2 suite folder>/g2/\" if it is a UNIX based OS.\n\n** Reverting the g2.ok**\nIf you wish to undo the patch procedure and to revert to the prior version of g2.ok, replace the g2.ok file with the one that was backed up in step 4.\nPlease let us know if you face any difficulty, If so do contact us at service@gensym.com with description of the problem and with a copy of downloaded and old ok files.";

    string errorcodes = "ERROR GENERATING CODES, PLEASE CONTACT service@gensym.com, will all the details which you had mentioned in Temporary License Generator (http://helpdesk2.trilogy.com)";


    protected void Page_Load(object sender, EventArgs e)
    {
        if (Request.Cookies["val"] == null)
            Response.Redirect("../admin.aspx");

        if (!this.IsPostBack)
        {
            string[] cookies = Response.Cookies.AllKeys;
            foreach (string cook in cookies)
                Response.Cookies[cook].Expires = DateTime.Now.AddDays(-1);
            startdate_pick.Text = DateTime.Today.ToShortDateString().ToString();           
            todate_pick.Text = DateTime.Today.AddDays(14).ToShortDateString().ToString();
            productname_cmbbox.SelectedIndex = 23;
            
            main_form = new StringBuilder();
            g2package = new StringBuilder();
            twpackage = new StringBuilder();
            bridgepackage = new StringBuilder();
            g2packageuserentry = new StringBuilder();
            twpackageuserentry = new StringBuilder();
            bridgepackageuserentry = new StringBuilder();
            ok.set_ispackage(false);
            
            Response.Cookies.Add(new HttpCookie("postback", "false"));
            //Response.Cookies.Add(new HttpCookie("requpdate", "1"));
            Response.Cookies.Add(new HttpCookie("updateui", "none#none"));

        }
        else
        {
            Response.Cookies.Set(new HttpCookie("postback", "true"));
            previousChoosenProduct = null;
            
        }

        startdate_pick.Attributes.Add("onchange", "setNewToDate(this);");
       
    }
    protected void productname_cmbbox_SelectedIndexChanged(object sender, EventArgs e)
    {
        
        AccessDataSource2.DataBind();
        version_cmbbox.DataBind();
        startdate_pick.Text = DateTime.Today.ToShortDateString().ToString();
        startdate_pick.ReadOnly = false;
        try
        {

          //  this.products_individiualTableAdapter.Fillversion(this.gensymDataSet11.products_individiual, productname_cmbbox.SelectedValue.ToString());
            if (productname_cmbbox.SelectedItem.Value == "G2")
            {                
                Response.Cookies.Add(new HttpCookie("updateui", "g2options#blinddown"));
            }
            else 
            {
                Response.Cookies.Add(new HttpCookie("updateui", "g2options#blindup"));
            }
           
        }
        catch { }
    }
    protected void version_cmbbox_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (productname_cmbbox.SelectedItem.Value == "G2")
        {
            startdate_pick.Text = "1/1/2009";
            startdate_pick.ReadOnly = true;            
            if (version_cmbbox.SelectedItem.Value[0] > '7')
            {
                if (Convert.ToDouble(version_cmbbox.SelectedItem.Value) > 8.2)
                {
                    startdate_pick.ReadOnly = false;
                    startdate_pick.Text = DateTime.Today.ToShortDateString();                    
                }
            }
            
        }
        
    }
    protected void gencodes_btn_Click(object sender, EventArgs e)
    {

        disable_permenent_products();
        bool valid = validataemmailid();
        if (valid == false)
            Response.Redirect("accounts.aspx");

        get_product();
        get_g2_options();

        ok.isbundle = false;

        if (string.IsNullOrEmpty(startdate_pick.Text) || string.IsNullOrEmpty(todate_pick.Text))
        {
            okfile.dates_are_null = true;
        }
        else
        {
            DateTime start = new DateTime();
            start = Convert.ToDateTime(startdate_pick.Text);
            DateTime todate = new DateTime();
            todate = Convert.ToDateTime(todate_pick.Text);


            ok.setExpirationDates(start, todate);

        }
        ok.setNoOfG2Process(processlmt_txt.Text);
        ok.setMachine_details(machinename_txt.Text, machine_id_cmbbox.Text);

        if (authrization_type == "G2-PACKAGE")
        {
            g2package.Append("\t(" + ok.get_package_autherization(okquery_string) + ")\n");
            if(ok.code_error)
                set_coderrormessage(ref g2package);
            g2packageuserentry.Append(productname_cmbbox.SelectedItem.Value+" - " +version_cmbbox.SelectedItem.Value + "\n");
        }
        else if (authrization_type == "BRIDGE")
        {
            bridgepackage.Append(ok.get_bridge_autherization(okquery_string) + "\n");
            if (ok.code_error)
                set_coderrormessage(ref bridgepackage);
            bridgepackageuserentry.Append(productname_cmbbox.SelectedItem.Value + " - " + version_cmbbox.SelectedItem.Value + "\n");           
        }
        else if (authrization_type == "TELEWINDOWS")
        {
            twpackage.Append(ok.get_tw_autherization(okquery_string) + "\n");
            if (ok.code_error)
                set_coderrormessage(ref twpackage);
            twpackageuserentry.Append(productname_cmbbox.SelectedItem.Value + " - " + version_cmbbox.SelectedItem.Value + "\n");
        }
        else
        {
            ok.set_ispackage(true);
            
            main_form.Insert(0, ok.GenerateOkFile());
            if (ok.code_error)
                set_coderrormessage(ref main_form);
            G2version = productname_cmbbox.SelectedItem.Value + " - " + version_cmbbox.SelectedItem.Value;
        }
        update_userresult();
        previousChoosenProduct = productname_cmbbox.SelectedItem.Value;
    }

    private void set_coderrormessage(ref StringBuilder package)
    {
        package.Remove(0,package.Length);
        package.AppendLine("ERROR");
        package.AppendLine("TEMPORARLY LICENSE SERVER IS CURRENTLY DOWN, YOUR REQUEST HAS BEEN MAILED TO OUR LICENSE MANAGER, WE WILL GET BACK TO YOU SOON");        
    }

    private void update_userresult()
    {
        output.Value = "";
        if (ok.get_ispackage())
        {
            output.Value = "Main Product Selected  : " + G2version + "\n\n";
        }
        if(g2package.Length >1)
        {
            output.Value = output.Value + "Packages Selected  : \n"+ g2packageuserentry.ToString() +"\n\n";
        }
        if (bridgepackage.Length > 1)
        {
            output.Value = output.Value + "Bridges Selected  : \n" +  bridgepackageuserentry.ToString() + "\n\n";
        }
        if (twpackage.Length > 1)
        {
            output.Value = output.Value + "TW/TWNG Selected  : \n" + twpackageuserentry.ToString() + "\n\n";
        }
    }
    protected void done_btn_Click(object sender, EventArgs e)
    {
        
        if (previousChoosenProduct != productname_cmbbox.SelectedItem.Value)
        {
            gencodes_btn_Click(sender,e);
        }
        
        if (ok.get_ispackage())
        {
             main_form.Insert(main_form.ToString().IndexOf("authorized-kb-packages: (") + 26, g2package.ToString());
        }
        else if(g2package.Length >1 &&!g2package.ToString().StartsWith("ERROR"))
        {           
            main_form.Insert(0,"Please add the following line to the authorized products list of your g2.ok File \n\n" + g2package.ToString() );
        }
        if(bridgepackage.Length > 1)        
        {
            string mailBridgeBody;
            mailBridgeBody = mailbody.Replace("g2.ok", "gsi.ok");
            mailBridgeBody = mailBridgeBody.Replace("\\g2\\", "\\<bridge_name>\\");
            mailBridgeBody = mailBridgeBody.Replace("/g2/", "/<bridge_name>/");
            if (bridgepackage.ToString().StartsWith("ERROR"))
                mailBridgeBody = errorcodes;
            if (!ok.sendmail(email_txt.Text, mailBridgeBody, "Gensym - Temporary Bridge License Codes","gsi.ok",bridgepackage.ToString()))
               mailSent = false;
        }
        if (twpackage.Length > 1)
        {
            string mailtwbody;
            mailtwbody = mailbody.Replace("g2.ok", "tw.ok");
            if (twpackage.ToString().StartsWith("ERROR"))
                mailtwbody = errorcodes;
            if(!ok.sendmail(email_txt.Text, mailtwbody,"Gensym - Temporary TW License Codes","tw.ok",twpackage.ToString()))
               mailSent = false; 
        }

        result.Visible = true;
       
        okout.Value = main_form.ToString();

        if (ok.code_error != true && main_form.ToString().Length>1)
        {
            if (!ok.sendmail(email_txt.Text, mailbody, "Gensym - G2 Temporary License Codes","g2.ok",main_form.ToString()))
               mailSent = false;          
        }
        else if(ok.code_error== true)
        {
            if (!ok.sendmail("ravindra.bg@versata.com", main_form.ToString(), "ERROR GENERATING CODE"))
               mailSent = false; ;
            output.Value= output.Value + "TEMPORARLY LICENSE SERVER IS CURRENTLY DOWN, YOUR REQUEST HAS BEEN MAILED TO OUR LICENSE MANAGER, WE WILL GET BACK TO YOU SOON";
            mailSent = false;
        }

        if (mailSent)
        {
            output.Value = output.Value + "Ok File has been E-Mailed to the given E-Mail ID, It may take a while to receive the Email. \nFor any further Queries please contact us at service@gensym.com \n\nRegards,\nGensym-Suppport";
        }
        else
        {
            output.Value = "UNABLE TO SEND MAIL TO THE GIVEN ID, PLEASE VERIFY THE EMAIL ID PROVIDED AND TRY AGAIN" ;
        }
        showoutput();
    }
    private void disable_permenent_products()
    {
        email_txt.Enabled = false;
        platform.Enabled = false;
        machinename_txt.Enabled = false;
        machine_id_cmbbox.Enabled = false;
    }

    private void showoutput()
    {        
        insertUserInputandOKfile();
        input.Visible = false;
    }   
    private void get_g2_options()
    {
        if (G2modules_grpbox.Enabled)
        {
            ok.setG2_version(productname_cmbbox.SelectedItem.Value + "-" + version_cmbbox.SelectedItem.Value);
            ok.setMinor_version(" Rev-Any ");
            ok.setok_file_format_version("2");
            ok.set_product(okquery_string);
            ok.setAuthorized_products(enumerate_auth_products());

            ok.setMakeg2Secure(false);
            ok.setNoTwProcess(TW_limit.Text);
            ok.setNoTw2Process(tw2_txt.Text);
        }
    }
    private string enumerate_auth_products()
    {
        string auth_products;
        auth_products = license_level_cmb.SelectedItem.ToString() + " ";

        auth_products = auth_products + licensemode_drpbox.SelectedItem.ToString() + " ";

        if (gsi_chk.Checked)
            auth_products = auth_products + "GSI ";
        if (gfi_chk.Checked)
            auth_products = auth_products + "GFI ";
        if (icp_chk.Checked)
            auth_products = auth_products + "ICP ";
        if (javalink_chk.Checked)
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
    private void get_product()
    {
        DataView dv = (DataView)AccessDataSource3.Select(DataSourceSelectArguments.Empty);

        DataTable myTable = new DataTable();
        myTable = dv.ToTable();
        okquery_string = myTable.Rows[0][3].ToString();
        okentry_string = myTable.Rows[0][4].ToString();
       
        authrization_type = myTable.Rows[0][1].ToString();
        


    }
    protected void nodate_chkBox_CheckedChanged(object sender, EventArgs e)
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
    private bool validataemmailid()
    {
        string emailid = email_txt.Text.Substring(email_txt.Text.IndexOf("@")+1);

        DataTable myTable = new DataTable();
        AccessDataSource AD = new AccessDataSource("~/gensym_accounts.mdb", "SELECT [company] AS [company], [valid] AS [valid]FROM useraccounts ORDER BY [company] DESC");
        DataView dv = (DataView)AD.Select(DataSourceSelectArguments.Empty);
        myTable = dv.ToTable();
        
        string companyname;
        for (int i=0; i < myTable.Rows.Count; i++)
        {
            companyname = myTable.Rows[i]["company"].ToString();
            if (emailid.Trim().ToUpper().Contains(companyname.Trim().ToUpper().ToString()))
            {
                if (myTable.Rows[i]["valid"].ToString()=="True")
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
        AD.InsertCommand = "INSERT INTO useraccounts(emailid, [password], company, valid) VALUES ('"+email_txt.Text+"',' ','"+ emailid.Trim()+"',0)";
        AD.Insert();
        
        return true;               
       
    }
    private void insertUserInputandOKfile()
    {
        SqlDataSource insertdata = new SqlDataSource();
        insertdata.ConnectionString = ConfigurationManager.ConnectionStrings["GensymServerManagement_ConnectionString"].ConnectionString.ToString();


        string insertcmd = "INSERT INTO queryandok (userid,company,product,version,type,platform,label,machinename,machineid,fromdate,todate,processlimit,twlimit,tw2limit,purpose,licenselevel,licensemode,optionalmodules,optionalkbs,okfileoutput) VALUES (' " + email_txt.Text + "', '" +email_txt.Text.Substring(email_txt.Text.IndexOf('@')+1) + "','" + productname_cmbbox.SelectedItem.Value + "','" + version_cmbbox.SelectedItem.Value + "','none','" + platform.SelectedItem.Value + "','none','" +machinename_txt.Text + "','" +machine_id_cmbbox.Text + "','" + startdate_pick.Text + "','" + todate_pick.Text + "','" + processlmt_txt.Text + "','" + TW_limit.Text + "','"+tw2_txt.Text+"','" + purpose.SelectedItem.Value + "','"+license_level_cmb.SelectedItem.Value+"','"+licensemode_drpbox.SelectedItem.Value+"','" + enumerate_auth_products() + "','none','" + okout.Value + "')";

        insertdata.InsertCommand = insertcmd;		
        try{
		insertdata.Insert();		
		}catch{}
    }
    
}
