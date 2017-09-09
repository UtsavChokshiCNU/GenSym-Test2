﻿//------------------------------------------------------------------------------
// <autogenerated>
//     This code was generated by a tool.
//     Runtime Version: 1.1.4322.2032
//
//     Changes to this file may cause incorrect behavior and will be lost if 
//     the code is regenerated.
// </autogenerated>
//------------------------------------------------------------------------------

// 
// This source code was auto-generated by Microsoft.VSDesigner, Version 1.1.4322.2032.
// 
namespace WebScorBSL.G2Mgr {
    using System.Diagnostics;
    using System.Xml.Serialization;
    using System;
    using System.Web.Services.Protocols;
    using System.ComponentModel;
    using System.Web.Services;
    
    
    /// <remarks/>
    [System.Diagnostics.DebuggerStepThroughAttribute()]
    [System.ComponentModel.DesignerCategoryAttribute("code")]
    [System.Web.Services.WebServiceBindingAttribute(Name="G2 ManagerSoap", Namespace="http://www.escor.com/webservices")]
    public class G2Manager : System.Web.Services.Protocols.SoapHttpClientProtocol {
        
        /// <remarks/>
        public G2Manager() {
            string urlSetting = System.Configuration.ConfigurationSettings.AppSettings["WebScorBSL.G2Mgr.G2 Manager"];
            if ((urlSetting != null)) {
                this.Url = string.Concat(urlSetting, "");
            }
            else {
                this.Url = "http://localhost/G2MgrWebSvc/G2Mgr.asmx";
            }
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/StartG2", RequestNamespace="http://www.escor.com/webservices", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string StartG2(string strUserName, string strPassword, int portNo) {
            object[] results = this.Invoke("StartG2", new object[] {
                        strUserName,
                        strPassword,
                        portNo});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginStartG2(string strUserName, string strPassword, int portNo, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("StartG2", new object[] {
                        strUserName,
                        strPassword,
                        portNo}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndStartG2(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        [System.Web.Services.WebMethodAttribute(MessageName="StartG21")]
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/StartG2Admin", RequestElementName="StartG2Admin", RequestNamespace="http://www.escor.com/webservices", ResponseElementName="StartG2AdminResponse", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        [return: System.Xml.Serialization.XmlElementAttribute("StartG2AdminResult")]
        public string StartG2(string strUserName, string strPassword, int portNo, int companyId) {
            object[] results = this.Invoke("StartG21", new object[] {
                        strUserName,
                        strPassword,
                        portNo,
                        companyId});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginStartG21(string strUserName, string strPassword, int portNo, int companyId, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("StartG21", new object[] {
                        strUserName,
                        strPassword,
                        portNo,
                        companyId}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndStartG21(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/StopG2", RequestNamespace="http://www.escor.com/webservices", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string StopG2(string strUserName, string strPassword, int portNo) {
            object[] results = this.Invoke("StopG2", new object[] {
                        strUserName,
                        strPassword,
                        portNo});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginStopG2(string strUserName, string strPassword, int portNo, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("StopG2", new object[] {
                        strUserName,
                        strPassword,
                        portNo}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndStopG2(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/IsG2Running", RequestNamespace="http://www.escor.com/webservices", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string IsG2Running(string strUserName, string strPassword, int portNo) {
            object[] results = this.Invoke("IsG2Running", new object[] {
                        strUserName,
                        strPassword,
                        portNo});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginIsG2Running(string strUserName, string strPassword, int portNo, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("IsG2Running", new object[] {
                        strUserName,
                        strPassword,
                        portNo}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndIsG2Running(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/GetG2CompanyId", RequestNamespace="http://www.escor.com/webservices", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string GetG2CompanyId(string strUserName, string strPassword, int portNo) {
            object[] results = this.Invoke("GetG2CompanyId", new object[] {
                        strUserName,
                        strPassword,
                        portNo});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginGetG2CompanyId(string strUserName, string strPassword, int portNo, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("GetG2CompanyId", new object[] {
                        strUserName,
                        strPassword,
                        portNo}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndGetG2CompanyId(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        [System.Web.Services.Protocols.SoapDocumentMethodAttribute("http://www.escor.com/webservices/StopAll", RequestNamespace="http://www.escor.com/webservices", ResponseNamespace="http://www.escor.com/webservices", Use=System.Web.Services.Description.SoapBindingUse.Literal, ParameterStyle=System.Web.Services.Protocols.SoapParameterStyle.Wrapped)]
        public string StopAll(string strUserName, string strPassword) {
            object[] results = this.Invoke("StopAll", new object[] {
                        strUserName,
                        strPassword});
            return ((string)(results[0]));
        }
        
        /// <remarks/>
        public System.IAsyncResult BeginStopAll(string strUserName, string strPassword, System.AsyncCallback callback, object asyncState) {
            return this.BeginInvoke("StopAll", new object[] {
                        strUserName,
                        strPassword}, callback, asyncState);
        }
        
        /// <remarks/>
        public string EndStopAll(System.IAsyncResult asyncResult) {
            object[] results = this.EndInvoke(asyncResult);
            return ((string)(results[0]));
        }
    }
}
