#pragma once

class IControlIniter {
public:
    virtual long initControl(CXTPControl* pControl, CXTPCommandBar* pMenu,
            long nId, long flags, LPWSTR label) = 0;
	virtual LPWSTR getHelpString(int nId) = 0;
};
