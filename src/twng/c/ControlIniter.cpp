#include "stdafx.h"
#include "ControlIniter.h"

void set_control_caption(CXTPCommandBar *pMenu,
                         CXTPControl *pControl, LPWSTR caption);
void g2pvt_nms_set_id_enabled(int id, int enabled);
int add_control(CXTPCommandBar* pBar, CXTPControl* pControl);

long ControlIniter::initControl(CXTPControl* pControl, CXTPCommandBar* pMenu,
        long nId, long flags, LPWSTR label) {
    BOOL enabled = (flags&(MF_GRAYED|MF_DISABLED)) == 0;
    if(flags&MF_RIGHTJUSTIFY)
        pControl->SetFlags(xtpFlagRightAlign);
    
    pControl->SetID(nId);
    set_control_caption(pMenu, pControl, label);
    pControl->SetEnabled(enabled);
    g2pvt_nms_set_id_enabled(nId, enabled);
    
    return add_control(pMenu, pControl);
}
