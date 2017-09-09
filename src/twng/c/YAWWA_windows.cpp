#include "stdafx.h"

#include "YAWWA_windows.hpp"

#include "YAWWA.hpp"


int YAWWA_Draw(CDC &dc, CString &text, int max_width, int left_margin, int top_margin)
{
    int y = top_margin;
    return YAWWA<tagSIZE>(text.GetBuffer(), text.GetLength(), max_width, TextExtentGetter(dc), 
        [&](int cy, wchar_t const *wcs, int len) { 
        dc.TextOutW(left_margin, y, wcs, len);
        y += cy;
    });
}


int YAWWA_Calc(CDC &dc, CString &text, int max_width)
{
    int height = 0;
    YAWWA<tagSIZE>(text.GetBuffer(), text.GetLength(), max_width, TextExtentGetter(dc), 
        [&](int cy, wchar_t const *, int) { height += cy; }
        );
    return height;
}
