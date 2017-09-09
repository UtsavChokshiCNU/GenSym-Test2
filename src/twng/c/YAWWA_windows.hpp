#if !defined INC_YAWWA_WINDOWS
#define      INC_YAWWA_WINDOWS


/** Helper class for the YAWWA, it measures the string
    using GetTextExtentPoint32() from WinAPI (on the given HDC).
*/
class TextExtentGetter {
public:
    TextExtentGetter(HDC dc) : hdc(dc) {}
    BOOL operator()(wchar_t const* wcs, int len, tagSIZE *pSize) {
        return GetTextExtentPoint32(hdc, wcs, len, pSize);
    }
private:
    HDC hdc;
};


/** Helper function, draws a (wrapped) string on Windows / MFC. Uses YAWWA.

    @param dc The MFC CDC to draw to
    @param text String (text) to display/draw
    @param max_width Max width of the string, in "logical units"
    @param left_margin Margin to skip on the left, in "logical units"
    @param top_margin Margin to skip on the top, in "logical units"
    @return 0: OK, otherwise: error
*/
int YAWWA_Draw(CDC &dc, CString &text, int max_width, int left_margin, int top_margin);


/** Helper function, calculates the height of the given @p text when
    displayed on the given @p dc, wrapped at given @p max_width.

    @param dc The MFC CDC to draw to
    @param text String (text) to display/draw
    @param max_width Max width of the string, in "logical units"
    @return 0: OK, otherwise: error
*/
int YAWWA_Calc(CDC &dc, CString &text, int max_width);


#endif // !defined INC_YAWWA_WINDOWS
