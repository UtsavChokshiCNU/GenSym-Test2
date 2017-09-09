// NolOptimizerProp.h : Declaration of the CNolOptimizerProp

#ifndef __NOLOPTIMIZERPROP_H_
#define __NOLOPTIMIZERPROP_H_

#include "resource.h"       // main symbols
#include "jni.h"      
#include "jvm.h"      

EXTERN_C const CLSID CLSID_NolOptimizerProp;

/////////////////////////////////////////////////////////////////////////////
// CNolOptimizerProp
class ATL_NO_VTABLE CNolOptimizerProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNolOptimizerProp, &CLSID_NolOptimizerProp>,
	public IPropertyPageImpl<CNolOptimizerProp>,
	public CDialogImpl<CNolOptimizerProp>
{
protected:
	short radioFlag;
public:
	CNolOptimizerProp() 
	{
		m_dwTitleID = IDS_TITLENolOptimizerProp;
		m_dwHelpFileID = IDS_HELPFILENolOptimizerProp;
		m_dwDocStringID = IDS_DOCSTRINGNolOptimizerProp;
		radioFlag = 0;
	}

	enum {IDD = IDD_NOLOPTIMIZERPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_NOLOPTIMIZERPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNolOptimizerProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CNolOptimizerProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CNolOptimizerProp>)
	COMMAND_HANDLER(IDC_BROWSEOPT, BN_CLICKED, OnClickedBrowseopt)
	COMMAND_HANDLER(IDC_LOADOPT, BN_CLICKED, OnClickedLoadopt)
	COMMAND_HANDLER(IDC_OUTPUTOPT, BN_CLICKED, OnClickedOutputopt)
	COMMAND_HANDLER(IDC_MANIPULATEDOPT, BN_CLICKED, OnClickedManipulatedopt)
	COMMAND_HANDLER(IDC_EXOGENOUSOPT, BN_CLICKED, OnClickedExogenousopt)
	COMMAND_HANDLER(IDC_STATEOPT, BN_CLICKED, OnClickedStateopt)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{

		int nMAX = 200;
		TCHAR path[200]; 
		ATLTRACE(_T("CNolOptimizerProp::Apply\n"));
		USES_CONVERSION;
		for (UINT i = 0; i < m_nObjects; i++)
		{
			INolOptimizer* pOpt;
			m_ppUnk[i]->QueryInterface(IID_INolOptimizer, (void**)&pOpt);
			GetDlgItemText(IDC_LOCATIONOPT,path,nMAX);
			pOpt->put_optimizationFullPath(T2BSTR(path));
		}
		m_bDirty = FALSE;
		InitialDisplayVariables();
		return S_OK;
	}

	LRESULT OnClickedBrowseopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		jmethodID mid;
		JNIEnv *env;
		jclass fileDlgCls;
		jobject jfiledialog;
		jstring jpath;
		const char * path;
		env = getJavaEnvironment();
		if(env == NULL) {
			::MessageBox(NULL, "Environment is null", "Fatal Error", MB_OK);				
			return 0;
		}
		fileDlgCls = env->FindClass("com/gensym/nols/deploy/NolFileDialog");
		if (fileDlgCls == 0) {
			::MessageBox(NULL, "Can't find NolFileDialog class", "Fatal Error", MB_OK);	
			return 0;
		}
		mid = env->GetMethodID(fileDlgCls,"<init>","(Ljava/lang/String;)V");
		if (mid == 0) {
			::MessageBox(NULL, "can't find Frame init method", "Fatal Error", MB_OK);				
			return 0;
		}
		jstring fileType = env->NewStringUTF(_T("*.opt"));
		jfiledialog = env->NewObject(fileDlgCls,mid,fileType);	
		mid = env->GetMethodID(fileDlgCls,"getFlag","()I");
		if (mid == 0) {
			::MessageBox(NULL, "can't getFlag show", "Fatal Error", MB_OK);				
			return 0;
		}
		jint flag = (jint)env->CallIntMethod(jfiledialog,mid);
		if(flag == 1){
			mid = env->GetMethodID(fileDlgCls,"getPath","()Ljava/lang/String;");
			if (mid == 0) {
				::MessageBox(NULL, "can't find getPath", "Fatal Error", MB_OK);				
				return 0;
			}
			jpath = (jstring)env->CallObjectMethod(jfiledialog,mid);
			path = env->GetStringUTFChars(jpath, 0);
			SetDlgItemText(IDC_LOCATIONOPT,path);
			SetDirty(TRUE);
			env->DeleteLocalRef(jpath);
		}

		env->DeleteLocalRef(fileDlgCls);
		env->DeleteLocalRef(fileType);
		env->DeleteLocalRef(jfiledialog);
		return 0;
	}
	LRESULT OnClickedLoadopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		Apply();
		SetDirty(FALSE);
		return 0;
	}
	LRESULT OnClickedOutputopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if(radioFlag == 0){
			return 0;
		}
		radioFlag = 0;
		DisplayVariables(0);
		return 0;
	}
	LRESULT OnClickedManipulatedopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if(radioFlag == 1){
			return 0;
		}
		radioFlag = 1;
		DisplayVariables(1);
		return 0;
	}
	LRESULT OnClickedExogenousopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if(radioFlag == 2){
			return 0;
		}
		radioFlag = 2;
		DisplayVariables(2);
		return 0;
	}
	LRESULT OnClickedStateopt(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		if(radioFlag == 3){
			return 0;
		}
		radioFlag = 3;
		DisplayVariables(3);
		return 0;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE(_T("CNolOptimizerProp::OnInitDialog\n"));
		USES_CONVERSION;
		for (UINT i = 0; i < m_nObjects; i++)
		{
			BSTR path;
			CComQIPtr<INolOptimizer, &IID_INolOptimizer>pOpt(m_ppUnk[i]);
			if FAILED(pOpt->get_optimizationFullPath(&path))        {
				CComPtr<IErrorInfo> pError;            CComBSTR            strError;
				GetErrorInfo(0, &pError);
				pError->GetDescription(&strError);
				::MessageBox(NULL, _T("Error"), "Fatal Error", MB_OK);				
				return E_FAIL;        
			}
			SetDlgItemText(IDC_LOCATIONOPT, W2A(path));
		}
		m_bDirty = FALSE;
		InitialDisplayVariables();
		return 0;
	}
	LRESULT DisplayVariables(short);
	LRESULT InitialDisplayVariables();
};

#endif //__NOLOPTIMIZERPROP_H_
