#pragma once
#include "IControlIniter.h"

extern "C" LPWSTR g2pvt_nms_help_string(int nId); /* Get help string for menu item id */

class ControlIniter: public IControlIniter {
public:
    virtual long initControl(CXTPControl* pControl, CXTPCommandBar* pMenu,
            long nId, long flags, LPWSTR label);

	virtual LPWSTR getHelpString(int nId) {
		return g2pvt_nms_help_string(nId);
	}

};
