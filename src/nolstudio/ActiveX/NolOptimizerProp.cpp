// NolOptimizerProp.cpp : Implementation of CNolOptimizerProp
#include "stdafx.h"
#include "NolOnline.h"
#include "NolOptimizerProp.h"

/////////////////////////////////////////////////////////////////////////////
// CNolOptimizerProp

LRESULT CNolOptimizerProp::InitialDisplayVariables(){

	HWND hWnd = GetDlgItem(IDC_OUTPUTOPT);
	::SendMessage(hWnd, BM_SETCHECK, BST_CHECKED, 0);
	DisplayVariables(0);
	return 0;
}

LRESULT CNolOptimizerProp::DisplayVariables(short flag)
{
		USES_CONVERSION;
		BSTR varName;
		HWND hWnd = GetDlgItem(IDC_VARIABLELISTOPT);
		if (hWnd)
		{
			::SendMessage(hWnd, LB_RESETCONTENT , 0, 0);
			if(flag == 0){
				for (UINT i = 0; i < m_nObjects; i++)
				{
					CComQIPtr<INolOptimizer, &IID_INolOptimizer>pOpt(m_ppUnk[i]);
					short vn =0;
					pOpt->getNumberOfVariables(flag, &vn);
					for(int j=0;j<vn;j++){
						pOpt->get_outputNames(j,&varName);
						::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
					}
				}
			}else if(flag == 1){
				for (UINT i = 0; i < m_nObjects; i++)
				{
					CComQIPtr<INolOptimizer, &IID_INolOptimizer>pOpt(m_ppUnk[i]);
					short vn =0;
					pOpt->getNumberOfVariables(flag, &vn);
					for(int j=0;j<vn;j++){
						pOpt->get_manipulatedNames(j,&varName);
						::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
					}
				}
			}else if(flag == 2){
				for (UINT i = 0; i < m_nObjects; i++)
				{
					CComQIPtr<INolOptimizer, &IID_INolOptimizer>pOpt(m_ppUnk[i]);
					short vn =0;
					pOpt->getNumberOfVariables(flag, &vn);
					for(int j=0;j<vn;j++){
						pOpt->get_exogenousNames(j,&varName);
						::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
					}
				}
			}else if(flag == 3){
				for (UINT i = 0; i < m_nObjects; i++)
				{
					CComQIPtr<INolOptimizer, &IID_INolOptimizer>pOpt(m_ppUnk[i]);
					short vn =0;
					pOpt->getNumberOfVariables(flag, &vn);
					for(int j=0;j<vn;j++){
						pOpt->get_stateNames(j,&varName);
						::SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)W2A(varName));
					}
				}
			}
		}
		return 0;
}
