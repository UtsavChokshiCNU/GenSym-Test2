#if !defined INC_YAWWA
#define      INC_YAWWA

/** Yet Another Word Wrapping Algorithm.

    This one is minimal and generic, geared towards speed, yet
    keeping readability. It:

    - breaks lines on spaces, dashes, slashes and newlines
    - if a word is too wide to fit in @p max_width, it will be wrapped,
      but there are no guarantees where - though it won't be "silly"
    
    This version works with wide strings, but we could make it even
    more generic - to work with any strings.

    The @p fm should observe the following interface:

    bool(wchar_t const* wcs, int length, SIZE *pSize);

    Returning 0 on failure and anything else on success, `wcs` being the
    string to measure, `length` the length of the string to measure
    and `pSize` pointer to a struct containing two members: `cx` and
    `cy`, being the measured width and height, respectively.

    The @p fout should observe the following interface:

    void(int cy, wchar_t const* wcs, int length);

    With `cy` being the heigth of the string to to display, `wcs`
    the string to display and `length` the length of the string to
    display.

    In this way, YAWWA is device independent.

    @param wcs The string to "wrap"
    @param text_len Number of characters in the string to wrap. Should
    be <= the length of @p wcs
    @param max_width Maximum width of the output, after which we should wrap
    @param fm Callable which measures the width and height of a given string
    @param fout Callable that "displays" a line of text - given with a string
    @return 0: OK, otherwise: error

*/
template <typename SIZE, typename FM, typename FOUT>
int YAWWA(wchar_t const* wcs, int text_len, int max_width, FM fm, FOUT &fout)
{
    int line_start = 0;
    int start = 0;
    int width = 0;
    SIZE size = { 0, 0 };
    while (start < text_len) {
        wchar_t const* pos = wcspbrk(wcs + start, L" \n\\/-");
        if (NULL == pos) {
            pos = wcs + text_len - 1;
        }
        int i = pos-wcs;
        if (!fm(wcs + start, i-start+1, &size)) {
            break;
        }
        if (size.cx >= max_width) {
            while (i > start) {
                const int overshot = width + size.cx - max_width;
                const int cut_pos = i - (overshot * (i-start)) / size.cx;
                if (!fm(wcs + start, cut_pos-start+1, &size)) {
                    break;
                }
                if (width + size.cx < max_width) {
                    fout(size.cy, wcs+line_start, cut_pos - line_start);
                    width = 0;
                    line_start = cut_pos;
                    i = cut_pos-1;
                    break;
                }
                i = cut_pos - 1;
            }
            if (i < start) {
                return -1;
            }
        }
        else if (width + size.cx >= max_width) {
            fout(size.cy, wcs+line_start, start - line_start);
            if (*pos == L'\n') {
                fout(size.cy, wcs + start, i - start + 1);
                width = 0;
                line_start = i + 1;
            }
            else {
                width = size.cx;
                line_start = start;
            }
        }
        else if (*pos == L'\n') {
            fout(size.cy, wcs+line_start, i - line_start+1);
            width = 0;
            line_start = i + 1;
        }
        else {
            width += size.cx;
        }
        start = i + 1;
    }
    fout(size.cy, wcs+line_start, text_len - line_start);
    return 0;
}


#endif // !defined INC_YAWWA