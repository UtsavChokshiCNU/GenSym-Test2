; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProxySettingsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WebSCORax.h"
CDK=Y

ClassCount=3
Class1=CWebSCORaxCtrl
Class2=CWebSCORaxPropPage

ResourceCount=3
Resource1=IDD_PROPPAGE_WEBSCORAX
LastPage=0
Resource2=IDD_ABOUTBOX_WEBSCORAX
Class3=CProxySettingsDlg
Resource3=IDD_PROPPAGE_SMALL

[CLS:CWebSCORaxCtrl]
Type=0
HeaderFile=WebSCORaxCtl.h
ImplementationFile=WebSCORaxCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CWebSCORaxCtrl

[CLS:CWebSCORaxPropPage]
Type=0
HeaderFile=WebSCORaxPpg.h
ImplementationFile=WebSCORaxPpg.cpp
Filter=D

[DLG:IDD_ABOUTBOX_WEBSCORAX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROPPAGE_WEBSCORAX]
Type=1
Class=CWebSCORaxPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_SMALL]
Type=1
Class=CProxySettingsDlg
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_CHECK_USEAUTOCONFIG,button,1342242819
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SCRIPT,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_CHECK_USEPROXY,button,1342242819
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PROXY,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_PORT,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_CHECK_USEAUTHENTICATION,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_USERNAME,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_PASSWORD,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_DOMAIN,edit,1350631552
Control19=IDOK,button,1342242816
Control20=IDCANCEL,button,1342242816

[CLS:CProxySettingsDlg]
Type=0
HeaderFile=ProxySettingsDlg.h
ImplementationFile=ProxySettingsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CProxySettingsDlg

