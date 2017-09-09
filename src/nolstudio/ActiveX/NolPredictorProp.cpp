// NolPredictorProp.cpp : Implementation of CNolPredictorProp
#include "stdafx.h"
#include "NolOnline.h"
#include "NolPredictorProp.h"

/////////////////////////////////////////////////////////////////////////////
// CNolPredictorProp


LRESULT CNolPredictorProp::InitialDisplayVariables(){

	HWND hWnd = GetDlgItem(IDC_OUTPUTNAMEPRED);
	::SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
	DisplayVariables(0);
	return 0;
}

LRESULT CNolPredictorProp::DisplayVariables(short flag)
{
	USES_CONVERSION;
	BSTR varName;
	HWND hWnd = GetDlgItem(IDC_VARIABLELISTPRED);
	if (hWnd)
	{
		::SendMessage(hWnd, LB_RESETCONTENT , 0, 0);
		if(flag == 0){
			for (UINT i = 0; i < m_nObjects; i++)
			{
				CComQIPtr<INolPredictor, &IID_INolPredictor>pPre(m_ppUnk[i]);
				long vn =0;
				pPre->getNumberOfOutputs(&vn);
				for(long j=0;j<vn;j++){
					pPre->get_outputNames((short)j,&varName);
					::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
				}
			}
		}else if(flag == 1){
			for (UINT i = 0; i < m_nObjects; i++)
			{
				CComQIPtr<INolPredictor, &IID_INolPredictor>pPre(m_ppUnk[i]);
				long vn =0;
				pPre->getNumberOfOutputs(&vn);
				for(long j=0;j<vn;j++){
					pPre->get_outputTags((short)j,&varName);
					::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
				}
			}
		}else if(flag == 2){
			for (UINT i = 0; i < m_nObjects; i++)
			{
				CComQIPtr<INolPredictor, &IID_INolPredictor>pPre(m_ppUnk[i]);
				long vn =0;
				pPre->getNumberOfInputs(&vn);
				for(long j=0;j<vn;j++){
					pPre->get_inputNames((short)j,&varName);
					::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
				}
			}
		}else if(flag == 3){
			for (UINT i = 0; i < m_nObjects; i++)
			{
				CComQIPtr<INolPredictor, &IID_INolPredictor>pPre(m_ppUnk[i]);
				long vn =0;
				pPre->getNumberOfInputs(&vn);
				for(long j=0;j<vn;j++){
					pPre->get_inputTags((short)j,&varName);
					::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
				}
			}
		}
	}
	return 0;
}
