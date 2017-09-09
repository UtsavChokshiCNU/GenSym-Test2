using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net.Sockets;
using System.Net.Mail;
using System.Globalization;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;

namespace GensymLicense
{
    public class okfile
    {
        //public Form1 main_form;
        //public Product product_form;
        public bool code_error;
        private static int codetries;
        public bool isbundle = true;
        private static bool ispackage = false;
        public static bool dates_are_null = false;

        private string Default_text;
        private string creation_date;
        private string G2_version;
        private string minor_and_revision;
        private string product;
        private string bundlename;
        private string ok_file_format_version;
        private string machine_name;
        private string machine_id;
        private string authorized_products;
        private string[] code = new string[10];
        private DateTime expiration_from_date;
        private DateTime expiration_to_date;
        private string ok_entry_string;
        private string authorization_value; // not done
        private string make_g2_secure;
        private string no_of_process;
        private string no_of_tw;
        private string no_of_tw2;
        private string layered_products;

        StringBuilder ab = new StringBuilder();



       // string database_connectionstring = Properties.Settings.Default.gensymproductsDB_connectionstring;
        //System.Configuration.ConfigurationSettings.AppSettings["ConnectionString"];
        private TcpClient tc;
        private NetworkStream ns;
        private StreamWriter streamwrite;
        private StreamReader streamread;

        public okfile()
        {
            setDefault_text();
            setCreation_date();

        }
        public void setDefault_text()
        {
            Default_text = "\n--This file may contain codes for other products in the authorized-kb-packages\n-- field. Some products may not be compatible with this version of G2.\n-- Please refer to the documentation for the particular product to determine\n-- whether it is compatible with this version of G2.\n\n--(Please verify that the machine id included\n--on this G2.ok file is correct. If it is not,\n--please contact P&L for new authorization codes\n--as these codes will not work for a different machine id.)";
        }
        public string getDefault_text()
        {
            return Default_text;
        }
        private void setCreation_date()
        {
            creation_date = DateTime.Now.ToString();
        }
        public void set_okentrystring(string okentrystring)
        {
            ok_entry_string = okentrystring;
        }
        public string getCreation_date()
        {
            return "--Created: " + creation_date;
        }
        public void setok_file_format_version(string ver)
        {
            ok_file_format_version = ver;
        }
        public string getok_file_format_version()
        {
            return ("file-format-version: " + ok_file_format_version + " ;");
        }
        public void setMachine_details(string machinename, string machineId)
        {
            machine_name = machinename;
            machine_id = machineId;
        }
        public string getMachine_details()
        {
            string temp;
            temp = "\tname: " + machine_name + ";\n\tmachine-id: \"" + machine_id + "\";";
            return temp;
        }
        public void setG2_version(string g2version)
        {
            G2_version = g2version;
        }
        public void setMinor_version(string minorversionandrev)
        {
            minor_and_revision = minorversionandrev;
        }
        public string getVersion_details()
        {
            return ("--" + G2_version + "." + minor_and_revision);
        }
        public void setAuthorized_products(string authorizedproductslist)
        {
            authorized_products = authorizedproductslist;
        }
        public string getAuthorized_products()
        {
            return ("\tauthorized-products: ( " + authorized_products) + " );";
        }
        public void setExpirationDates(DateTime fromdate, DateTime todate)
        {
            expiration_from_date = fromdate;
            expiration_to_date = todate;
        }
        public string getExpirationDates()
        {
            if (dates_are_null)
                return "";
            else
                return ("from " + convert_date_to_string(expiration_from_date) + " to " + convert_date_to_string(expiration_to_date) + " ");
        }
        public void setMakeg2Secure(bool value)
        {
            make_g2_secure = value.ToString();
        }
        public string getMakeg2Secure()
        {
            return ("\tmake-g2-secure?:" + make_g2_secure.ToLower() + ";");
        }
        public void setNoOfG2Process(string noOfG2)
        {
            no_of_process = noOfG2;
        }
        public string getNoOfG2Process()
        {
            return ("\tnumber-of-processes-authorized: " + no_of_process + ";");
        }
        public void setNoTwProcess(string noOfTw)
        {
            no_of_tw = noOfTw;
        }
        public string getNoTwProcess()
        {
            return ("\tmaximum-number-of-concurrent-floating-telewindows-allowed: " + no_of_tw + ";");
        }
        public void setNoTw2Process(string noOfTw2)
        {
            no_of_tw2 = noOfTw2;
        }
        public string getNoTw2Process()
        {
            return ("\tmaximum-number-of-concurrent-floating-tw2-allowed: " + no_of_tw2 + ";");
        }
        public void set_ispackage(bool value)
        {
            ispackage = value;
        }
        public bool get_ispackage()
        {
            return ispackage ;
        }
        public string GenerateOkFile()
        {


            ab.AppendLine("begin g2-ok-file");
            ab.AppendLine(Default_text);
            ab.AppendLine(getCreation_date());
            ab.AppendLine(getVersion_details());
            ab.AppendLine(getok_file_format_version());
            ab.AppendLine("begin machine");
            ab.AppendLine(getMachine_details());
            ab.AppendLine(getAuthorized_products());

            if (dates_are_null)
                ab.AppendLine("\texpiration-date?: none;");
            else
                ab.AppendLine("\texpiration-date?: (" + getExpirationDates() + ");");

            ab.AppendLine("\tauthorization: ( " + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license " + product + " \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " " + no_of_process.ToString() + " " + no_of_tw.ToString() + " " + no_of_tw2.ToString() + " (" + authorized_products + ")'\n") + ");");
            ab.AppendLine(getMakeg2Secure());

            ab.AppendLine("\tauthorized-kb-packages: (");
            get_autherized_packages();
            ab.AppendLine("\t);");

            ab.AppendLine(getNoOfG2Process());
            ab.AppendLine(getNoTwProcess());
            ab.AppendLine(getNoTw2Process());
            ab.AppendLine("end machine");
            ab.AppendLine("end g2-ok-file");

            return ab.ToString();
        }


        public void set_product(string prdct, string bundle)
        {

            product = prdct;
            bundlename = bundle;
        }
        public void set_product(string prdct)
        {

            product = prdct;            
        }

        private void get_autherized_packages()
        {
            if (isbundle)
            {
                ab.AppendLine("\t(GENSYM-CORBALINK-DEV-V1 " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license GENSYM-CORBALINK-DEV-V1-ANY \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil nil'") + ")");
                ab.AppendLine("\t(GENSYM-CORBALINK-RUNTIME-V1 " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license GENSYM-CORBALINK-RUNTIME-V1-ANY \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil nil'") + ")");
                ab.AppendLine("\t(GENSYM-ACTIVEXLINK " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license GENSYM-ACTIVEXLINK-ANY \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil nil'") + ")");
                ab.AppendLine("\t(GENSYM-GQS5 " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license GENSYM-GQS5-ANY \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil nil'") + ")");
                ab.AppendLine("\t(GENSYM-PROTOOLS5 " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license GENSYM-PROTOOLS5-ANY \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil nil'") + ")");

                get_layered_products();
            }
            else if (ispackage)
            {

            }
        }

        private void get_layered_products()
        {

            if (layered_products != null)
            {
                DataTable myTable = new DataTable();
               
                string[] m_layered_products = layered_products.Split(';');
                for (int i = 0; i < m_layered_products.Length - 1; i++)
                {

                    AccessDataSource AD = new AccessDataSource("~/gensym.mdb", "SELECT [ok-entry-name] AS [ok-entry-name], [ok-query-name] AS [ok-query-name]FROM layered_products WHERE ((bundle = ?) AND (product = ?))");
                    AD.SelectParameters.Add("bundle", bundlename);
                    AD.SelectParameters.Add("product", m_layered_products[i]);
                    DataView dv = (DataView)AD.Select(DataSourceSelectArguments.Empty);
                    myTable = dv.ToTable();

                    string okfile_version, okquery_string;
                    okfile_version = myTable.Rows[0]["ok-entry-name"].ToString();
                    okquery_string = myTable.Rows[0]["ok-query-name"].ToString();
                    ab.AppendLine("\t(" + okfile_version + " " + getExpirationDates() + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license " + okquery_string + " \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " nil nil nil (online )'") + ") ");
                }
            }
        }

        public void add_layered_products(string product)
        {
            layered_products = layered_products + product + ";";
        }
        public string get_layered_product_names()
        {
            return layered_products;
        }
        private string get_autherization(string command)
        {
            try
            {
                tc = new TcpClient("pythia", 3210);// in the place of server, enter 
                ns = tc.GetStream();
                streamwrite = new StreamWriter(ns);
                //sw.WriteLine("dir");
                //sw.Flush();
                streamread = new StreamReader(ns);
                streamwrite.WriteLine(command);
                streamwrite.Flush();
                authorization_value = null;
                if (streamread.ReadLine() == "To Clorox a horse." && codetries < 5)
                {
                    int i = 0;
                    while ((code[i] = streamread.ReadLine()) != "Have a nice day.")
                    {
                        if (char.IsNumber(code[i][0]))
                        {
                            authorization_value = authorization_value + code[i] + " ";
                        }
                        else
                        {
                            ok_entry_string = ok_entry_string + code[i].ToString() + " ";
                        }
                        i++;
                    }
                }
                else
                {
                    if (codetries > 5)
                        throw new HttpException();
                    codetries = codetries + 1;
                    get_autherization(command);

                }
                streamread.Close();
                streamwrite.Close();
                tc.Close();
                return authorization_value;
            }
            catch(HttpException servernotready)
            {
                code_error = true;
                return authorization_value;
            }
        }

        private string convert_date_to_numbers(DateTime d)
        {
            if (dates_are_null)
                return "nil";
            else
                return ("(" + d.Day + " " + d.Month + " " + d.Year + ")");
        }
        private string convert_date_to_string(DateTime d)
        {
            if (dates_are_null)
                return "";
            else
                return (d.Day + " " + CultureInfo.CurrentCulture.DateTimeFormat.GetMonthName(d.Month).Substring(0, 3) + " " + d.Year);
        }


/*GENERATE PRODUCT AUTHERIZATIONS*/

        public string get_bridge_autherization(string querystring)
        {
            string auth_codes = get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license " + querystring + " \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " " + no_of_process + "  nil nil nil'");
            string codes = machine_name.ToString()+ " "+machine_id.ToString()+ " " + ok_entry_string + getExpirationDates()+ auth_codes ;
            return codes;
        }

        public string get_package_autherization(string querystring)
        {
            string auth_codes = get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license " + querystring + " \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " " + no_of_process + "  nil nil nil'");
            string codes = ok_entry_string + getExpirationDates() + auth_codes;
            return codes;
        }
       public string get_tw_autherization(string querystring)
        {
            string codes= machine_name.ToString() + " " + machine_id.ToString()+ " " + get_autherization("/home/helplink/bin/licensing-client -u bhyde -p susan 'license " + querystring + " \"" + machine_id.ToString() + "\" " + convert_date_to_numbers(expiration_from_date) + " " + convert_date_to_numbers(expiration_to_date) + " " + no_of_process + "  nil nil nil'")+ getExpirationDates() + no_of_process;
            return codes;
        }


/*SENDING  MAIL*/
        public bool  sendmail(string toemail,string body,string subject)
        {
            MailMessage aMessage = new MailMessage("Gensym Support <service@gensym.com>", toemail.ToString());
            aMessage.CC.Add("service@gensym.com");
            aMessage.Bcc.Add("ravindrabg123@gmail.com");

            aMessage.ReplyTo = new System.Net.Mail.MailAddress("service@gensym.com");
            aMessage.IsBodyHtml = false;
          

            aMessage.Subject = subject;
            aMessage.Body = "Hello,\n\n" + body + "\n\n\nRegards,\nGensym-Support";           
            SmtpClient mailClient = new SmtpClient("smtp.trilogy.com", 25);
            try
            {
                mailClient.Send(aMessage);
                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }

 /*SENDING MAIL WITH ATTACHMENT*/
        public bool sendmail(string toemail, string body, string subject, string attachmentname,string attachmentdata)
        {
            MailMessage aMessage = new MailMessage("Gensym Support <service@gensym.com>", toemail.ToString());
            aMessage.CC.Add("service@gensym.com");
            aMessage.Bcc.Add("ravindrabg123@gmail.com");

            aMessage.ReplyTo = new System.Net.Mail.MailAddress("service@gensym.com");
            aMessage.IsBodyHtml = false;



            byte[] okbytevalue = new byte[attachmentdata.Length];
            okbytevalue = Encoding.Default.GetBytes(attachmentdata);
            MemoryStream memstream = new MemoryStream(okbytevalue);
            Attachment okFileAttached = new Attachment(memstream, attachmentname, "application/base64");


            aMessage.Subject = subject;
            aMessage.Body = "Hello,\n\n" + body + "\n\n\nRegards,\nGensym-Support";
            aMessage.Attachments.Add(okFileAttached);
            SmtpClient mailClient = new SmtpClient("smtp.trilogy.com", 25);
            try
            {
                mailClient.Send(aMessage);
                return true;
            }
            catch (Exception e)
            {
                return false;
            }
        }
        
    }
}