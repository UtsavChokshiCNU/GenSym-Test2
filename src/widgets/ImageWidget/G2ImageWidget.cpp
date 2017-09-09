// CG2ImageWidget.cpp : implementation file
//

#include "stdafx.h"
#include "G2ImageWidget.h"

BEGIN_MESSAGE_MAP(CG2ImageWidget, CStatic)
END_MESSAGE_MAP()

void CG2ImageWidget::PostNcDestroy() 
{
  CStatic::PostNcDestroy();
  delete this;
}
