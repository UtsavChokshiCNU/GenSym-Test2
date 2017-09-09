// Scintilla source code edit control
/** @file CallTip.h
 ** Interface to the call tip control.
 **/
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef CALLTIP_H
#define CALLTIP_H

/**
 */
class CallTip {
	int startHighlight;    // character offset to start and...
	int endHighlight;      // ...end of highlighted text
	int argument;          //highlighted argument
	char *val;	           // currently need to show the calltip contents
	Font font;
	PRectangle rectUp;      // rectangle of last up angle in the tip
	PRectangle rectDown;    // rectangle of last down arrow in the tip
	int lineHeight;         // vertical line spacing
	int offsetMain;         // The alignment point of the call tip
	int tabSize;            // Tab size in pixels, <=0 no TAB expand
	bool useStyleCallTip;   // if true, STYLE_CALLTIP should be used
	//{{Suzsoft add for Gensym-563
	int currIndex;          // The currently index of  option method prototypes
	char *allVal;           // the all calltip contents
	int sumMethod;          // The sum of the method prototypes
	int numLines;           // The method need the line numbers.
	bool isAboveText;       // Whether the calltip show above the text, true; above; false: no
	//}}Suzsoft

	// Private so CallTip objects can not be copied
	CallTip(const CallTip &) {}
	CallTip &operator=(const CallTip &) { return *this; }
	void DrawChunk(Surface *surface, int &x, const char *s,
		int posStart, int posEnd, int ytext, PRectangle rcClient,
		bool highlight, bool draw);
	int PaintContents(Surface *surfaceWindow, bool draw);
	bool IsTabCharacter(char c);
	int NextTabPos(int x);

public:
	Window wCallTip;
	Window wDraw;
	bool inCallTipMode;
	int posStartCallTip;
	ColourPair colourBG;
	ColourPair colourUnSel;
	ColourPair colourSel;
	ColourPair colourShade;
	ColourPair colourLight;
	int codePage;
	int clickPlace;

	CallTip();
	~CallTip();

	/// Claim or accept palette entries for the colours required to paint a calltip.
	void RefreshColourPalette(Palette &pal, bool want);

	void PaintCT(Surface *surfaceWindow);

	void MouseClick(Point pt);

	/// Setup the calltip and return a rectangle of the area required.
	PRectangle CallTipStart(int pos, Point pt, const char *defn,
		const char *faceName, int size, int codePage_, 
		int characterSet, Window &wParent);

	void CallTipCancel();

	/// Set a range of characters to be displayed in a highlight style.
	/// Commonly used to highlight the current parameter.
	void SetHighlight(int start, int end);

	//{{suzsoft add for Gensym-347
	/// Set a range of characters to be displayed in a highlight style.
	/// Commonly used to highlight by argument.
	void SetHighlight(int arg);

	// Return positions in a CALLTIP which
	// delimit argument number and method number
	void DelimitArgInCalltip(char *calltip, int method, int arg, int *start, int *end);

	//judge whether the position is at the method range
	bool MethodArgOut(char *calltip, int method, int pos);
	//}}

	/// Set the tab size in pixels for the call tip. 0 or -ve means no tab expand.
	void SetTabSize(int tabSz);

	/// Used to determine which STYLE_xxxx to use for call tip information
	bool UseStyleCallTip() const { return useStyleCallTip;}

	// Modify foreground and background colours
	void SetForeBack(const ColourPair &fore, const ColourPair &back);

	//{{Suzsoft Add for Gensym-563
	// Cale the sum of method prototypes
	int GetSumMethod(char *calltip);

	// Get Calltip contents by the the currently method index
	void CurrCalltipContent();
	
	// Update the Calltip size when choice a new method
	PRectangle UpdateCalltipSize();

	void SetIsAboveText(bool above) { isAboveText = above; }

	// Set value for allVal variable 
	void SetAllCalltipContent(char* allCalltip);

	char* GetCurrCalltip() { return val; }
	//}}Suzsoft
};

#endif
