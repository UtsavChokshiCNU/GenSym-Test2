#if !defined(AFX_ANIMATESTATIC_H__A27A4001_C7FC_4A9E_9D1F_1EA391390161__INCLUDED_)
#define AFX_ANIMATESTATIC_H__A27A4001_C7FC_4A9E_9D1F_1EA391390161__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimateStatic.h : header file
//

enum XTAnimation { animateNoise = 6, animateStretch, animateCircles };

/////////////////////////////////////////////////////////////////////////////
// CAnimateStatic window

class CAnimateStatic : public CStatic
{
public:
	CAnimateStatic();
	virtual ~CAnimateStatic();

public:
	void SetAnimationType(int nAnimationType) {
		m_nAnimationType = nAnimationType;
	}
	int GetAnimationType() const {
		return m_nAnimationType;
	}
	void SetAnimationDelay(int nAnimationDelay) {
		m_nAnimationDelay = nAnimationDelay;
	}
	int GetAnimationDelay() const {
		return m_nAnimationDelay;
	}
	void SetAnimationSteps(int nAnimationSteps) {
		m_nAnimationSteps = nAnimationSteps;
	}
	int GetAnimationSteps() const {
		return m_nAnimationSteps;
	}
	void Animate();

	//{{AFX_VIRTUAL(CAnimateStatic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAnimateStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	static void AFX_CDECL CustomAnimation(CRect rc, CDC* pDestDC, CDC* pSrcDC, int nType, int nSteps, int nAnimationTime);
	virtual void OnDraw(CDC* pDC);

	int     m_nAnimationType;
	int     m_nAnimationDelay;
	int     m_nAnimationSteps;
	BOOL    m_bAnimationFinished;
	CBitmap m_bmpGear;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMATESTATIC_H__A27A4001_C7FC_4A9E_9D1F_1EA391390161__INCLUDED_)
