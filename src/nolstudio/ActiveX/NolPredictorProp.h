// NolPredictorProp.h : Declaration of the CNolPredictorProp

#ifndef __NOLPREDICTORPROP_H_
#define __NOLPREDICTORPROP_H_

#include "resource.h"       // main symbols
#include "jni.h"      
#include "jvm.h"      

EXTERN_C const CLSID CLSID_NolPredictorProp;

/////////////////////////////////////////////////////////////////////////////
// CNolPredictorProp
class ATL_NO_VTABLE CNolPredictorProp :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CNolPredictorProp, &CLSID_NolPredictorProp>,
	public IPropertyPageImpl<CNolPredictorProp>,
	public CDialogImpl<CNolPredictorProp>
{
protected:
	short radioFlag;

public:
	CNolPredictorProp() 
	{
		m_dwTitleID = IDS_TITLENolPredictorProp;
		m_dwHelpFileID = IDS_HELPFILENolPredictorProp;
		m_dwDocStringID = IDS_DOCSTRINGNolPredictorProp;
		radioFlag = 0;
	}

	enum {IDD = IDD_NOLPREDICTORPROP};

DECLARE_REGISTRY_RESOURCEID(IDR_NOLPREDICTORPROP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CNolPredictorProp) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CNolPredictorProp)
	CHAIN_MSG_MAP(IPropertyPageImpl<CNolPredictorProp>)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	COMMAND_HANDLER(IDC_BROWSEPRED, BN_CLICKED, OnClickedBrowsepred)
	COMMAND_HANDLER(IDC_INPUTNAMEPRED, BN_CLICKED, OnClickedInputnamepred)
	COMMAND_HANDLER(IDC_INPUTTAGPRED, BN_CLICKED, OnClickedInputtagpred)
	COMMAND_HANDLER(IDC_LOADPRED, BN_CLICKED, OnClickedLoadpred)
	COMMAND_HANDLER(IDC_LOCATIONPRED, EN_CHANGE, OnChangeLocationpred)
	COMMAND_HANDLER(IDC_OUTPUTNAMEPRED, BN_CLICKED, OnClickedOutputnamepred)
	COMMAND_HANDLER(IDC_OUTPUTTAGPRED, BN_CLICKED, OnClickedOutputtagpred)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		int nMAX = 200;
		TCHAR path[200]; 
		ATLTRACE(_T("CNolPredictorProp::Apply\n"));
		USES_CONVERSION;
		for (UINT i = 0; i < m_nObjects; i++)
		{
			INolPredictor* pPre;
			m_ppUnk[i]->QueryInterface(IID_INolPredictor, (void**)&pPre);
			GetDlgItemText(IDC_LOCATIONPRED,path,nMAX);
			pPre->put_modelFullPath(T2BSTR(path));
		}
		m_bDirty = FALSE;
		InitialDisplayVariables();
		return S_OK;
	}
	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLTRACE(_T("CNolPredictorProp::OnInitDialog\n"));
		USES_CONVERSION;
		for (UINT i = 0; i < m_nObjects; i++)
		{
			BSTR path;
			CComQIPtr<INolPredictor, &IID_INolPredictor>pPre(m_ppUnk[i]);
			if FAILED(pPre->get_modelFullPath(&path))        {
				CComPtr<IErrorInfo> pError;            CComBSTR            strError;
				GetErrorInfo(0, &pError);
				pError->GetDescription(&strError);
				::MessageBox(NULL, _T("Error"), "Fatal Error", MB_OK);				
				return E_FAIL;        
			}
			SetDlgItemText(IDC_LOCATIONPRED, W2A(path));
		}
		m_bDirty = FALSE;
		InitialDisplayVariables();
		return 0;
	}

	LRESULT OnClickedBrowsepred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		jmethodID mid;
		JNIEnv *env;
		jobject jfiledialog;
		jstring jpath;
		const char * path;
		env = getJavaEnvironment();
		if(env == NULL) {
			::MessageBox(NULL, "Environment is null", "Fatal Error", MB_OK);				
			return 0;
		}
		jclass fileDlgCls = env->FindClass("com/gensym/nols/deploy/NolFileDialog");
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 1"));

		if (fileDlgCls == 0) {
			::MessageBox(NULL, "Can't find NolFileDialog class", "Fatal Error", MB_OK);	
			return 0;
		}
		mid = env->GetMethodID(fileDlgCls,"<init>","(Ljava/lang/String;)V");
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 2"));
		if (mid == 0) {
			::MessageBox(NULL, "can't find Frame init method", "Fatal Error", MB_OK);				
			return 0;
		}
		jstring fileType = env->NewStringUTF(_T("*.mod"));
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 3"));
		jfiledialog = env->NewObject(fileDlgCls,mid,fileType);	
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 4"));

		mid = env->GetMethodID(fileDlgCls,"getFlag","()I");
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 5"));
		if (mid == 0) {
			::MessageBox(NULL, "can't find getFlag", "Fatal Error", MB_OK);				
			return 0;
		}
		jint flag = (jint)env->CallIntMethod(jfiledialog,mid);
		CheckJavaException(FALSE, _T("OnClickedBrowsepred 6"));
		
		if(flag == 1){
			mid = env->GetMethodID(fileDlgCls,"getPath","()Ljava/lang/String;");
			CheckJavaException(FALSE, _T("OnClickedBrowsepred 7"));
			if (mid == 0) {
				::MessageBox(NULL, "can't find getPath", "Fatal Error", MB_OK);				
				return 0;
			}
			jpath = (jstring)env->CallObjectMethod(jfiledialog,mid);
			CheckJavaException(FALSE, _T("OnClickedBrowsepred 8"));
			path = env->GetStringUTFChars(jpath, 0);
			CheckJavaException(FALSE, _T("OnClickedBrowsepred 9"));
			SetDlgItemText(IDC_LOCATIONPRED,path);
			SetDirty(TRUE);
			env->DeleteLocalRef(jpath);
		}
		
		env->DeleteLocalRef(jfiledialog);
		env->DeleteLocalRef(fileType);
		env->DeleteLocalRef(fileDlgCls);
		return 0;
	}
	LRESULT OnClickedInputnamepred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		radioFlag = 2;
		DisplayVariables(2);
		return 0;
	}
	LRESULT OnClickedInputtagpred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		radioFlag = 3;
		DisplayVariables(3);
		return 0;
	}
	LRESULT OnClickedLoadpred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		Apply();
		SetDirty(FALSE);
		return 0;
	}
	LRESULT OnChangeLocationpred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		// TODO : Add Code for control notification handler.
		return 0;
	}
	LRESULT OnClickedOutputnamepred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		radioFlag = 0;
		DisplayVariables(0);
		return 0;
	}
	LRESULT OnClickedOutputtagpred(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		radioFlag = 1;
		DisplayVariables(1);
		return 0;
	}
	LRESULT DisplayVariables(short);
	LRESULT InitialDisplayVariables();
};

#endif //__NOLPREDICTORPROP_H_
