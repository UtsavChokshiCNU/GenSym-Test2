// Scintilla source code edit control
/** @file CallTip.cxx
 ** Code for displaying call tips.
 **/
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Platform.h"

#include "Scintilla.h"
#include "CallTip.h"

static const int insetX = 5;    // text inset in x from calltip border
static const int widthArrow = 14;

CallTip::CallTip() {
	wCallTip = 0;
	inCallTipMode = false;
	posStartCallTip = 0;
	val = 0;
	allVal = 0;
	rectUp = PRectangle(0,0,0,0);
	rectDown = PRectangle(0,0,0,0);
	lineHeight = 1;
	startHighlight = 0;
	endHighlight = 0;
	argument = 0;
	tabSize = 0;
	useStyleCallTip = false;    // for backwards compatibility	

	currIndex = 0;
	sumMethod = 0;
	numLines = 0;
	isAboveText = false;

	colourBG.desired = ColourDesired(0xff, 0xff, 0xff);
	colourUnSel.desired = ColourDesired(0x80, 0x80, 0x80);
	colourSel.desired = ColourDesired(0, 0, 0x80);
	colourShade.desired = ColourDesired(0, 0, 0);
	colourLight.desired = ColourDesired(0xc0, 0xc0, 0xc0);
}

CallTip::~CallTip() {
	font.Release();
	wCallTip.Destroy();
	//{{suzsoft change for Gensym-563
	// delete the methods content from memory. avoid memory leak
	if (val)
	{
		delete []val;
		val = 0;
	}

	if (allVal)
	{
		delete []allVal;
		allVal = 0;
	}
	//}}Suzsoft
	
}

void CallTip::RefreshColourPalette(Palette &pal, bool want) {
	pal.WantFind(colourBG, want);
	pal.WantFind(colourUnSel, want);
	pal.WantFind(colourSel, want);
	pal.WantFind(colourShade, want);
	pal.WantFind(colourLight, want);
}

// Although this test includes 0, we should never see a \0 character.
static bool IsArrowCharacter(char ch) {
	return (ch == 0) || (ch == '\001') || (ch == '\002');
}

// We ignore tabs unless a tab width has been set.
bool CallTip::IsTabCharacter(char ch) {
	return (tabSize > 0) && (ch == '\t');
}

int CallTip::NextTabPos(int x) {
	if (tabSize > 0) {              // paranoia... not called unless this is true
		x -= insetX;                // position relative to text
		x = (x + tabSize) / tabSize;  // tab "number"
		return tabSize*x + insetX;  // position of next tab
	} else {
		return x + 1;                 // arbitrary
	}
}

// Draw a section of the call tip that does not include \n in one colour.
// The text may include up to numEnds tabs or arrow characters.
void CallTip::DrawChunk(Surface *surface, int &x, const char *s,
	int posStart, int posEnd, int ytext, PRectangle rcClient,
	bool highlight, bool draw) {
	s += posStart;
	int len = posEnd - posStart;

	// Divide the text into sections that are all text, or that are
	// single arrows or single tab characters (if tabSize > 0).
	int maxEnd = 0;
	const int numEnds = 10;
	int ends[numEnds + 2];
	for (int i=0;i<len;i++) {
		if ((maxEnd < numEnds) &&
		        (IsArrowCharacter(s[i]) || IsTabCharacter(s[i])) ) {
			if (i > 0)
				ends[maxEnd++] = i;
			ends[maxEnd++] = i+1;
		}
	}
	ends[maxEnd++] = len;
	int startSeg = 0;
	int xEnd;
	for (int seg = 0; seg<maxEnd; seg++) {
		int endSeg = ends[seg];
		if (endSeg > startSeg) {
			if (IsArrowCharacter(s[startSeg])) {
				bool upArrow = s[startSeg] == '\001';
				rcClient.left = x;
				rcClient.right = rcClient.left + widthArrow;
				if (draw) {
					const int halfWidth = widthArrow / 2 - 3;
					const int centreX = rcClient.left + widthArrow / 2 - 1;
					const int centreY = (rcClient.top + rcClient.bottom) / 2;
					surface->FillRectangle(rcClient, colourBG.allocated);
					PRectangle rcClientInner(rcClient.left + 1, rcClient.top + 1,
					                         rcClient.right - 2, rcClient.bottom - 1);
					surface->FillRectangle(rcClientInner, colourUnSel.allocated);

					if (upArrow) {      // Up arrow
						Point pts[] = {
    						Point(centreX - halfWidth, centreY + halfWidth / 2),
    						Point(centreX + halfWidth, centreY + halfWidth / 2),
    						Point(centreX, centreY - halfWidth + halfWidth / 2),
						};
						surface->Polygon(pts, sizeof(pts) / sizeof(pts[0]),
                 						colourBG.allocated, colourBG.allocated);
					} else {            // Down arrow
						Point pts[] = {
    						Point(centreX - halfWidth, centreY - halfWidth / 2),
    						Point(centreX + halfWidth, centreY - halfWidth / 2),
    						Point(centreX, centreY + halfWidth - halfWidth / 2),
						};
						surface->Polygon(pts, sizeof(pts) / sizeof(pts[0]),
                 						colourBG.allocated, colourBG.allocated);
					}
				}
				xEnd = rcClient.right;
				offsetMain = xEnd;
				if (upArrow) {
					rectUp = rcClient;
				} else {
					rectDown = rcClient;
				}
			} else if (IsTabCharacter(s[startSeg])) {
				xEnd = NextTabPos(x);
			} else {
				xEnd = x + surface->WidthText(font, s + startSeg, endSeg - startSeg);
				if (draw) {
					rcClient.left = x;
					rcClient.right = xEnd;
					surface->DrawTextTransparent(rcClient, font, ytext,
										s+startSeg, endSeg - startSeg,
					                             highlight ? colourSel.allocated : colourUnSel.allocated);
				}
			}
			x = xEnd;
			startSeg = endSeg;
		}
	}
}

int CallTip::PaintContents(Surface *surfaceWindow, bool draw) {
	PRectangle rcClientPos = wCallTip.GetClientPosition();
	PRectangle rcClientSize(0, 0, rcClientPos.right - rcClientPos.left,
	                        rcClientPos.bottom - rcClientPos.top);
	PRectangle rcClient(1, 1, rcClientSize.right - 1, rcClientSize.bottom - 1);

	// To make a nice small call tip window, it is only sized to fit most normal characters without accents
	int ascent = surfaceWindow->Ascent(font) - surfaceWindow->InternalLeading(font);

	// For each line...
	// Draw the definition in three parts: before highlight, highlighted, after highlight
	int ytext = rcClient.top + ascent + 1;
	rcClient.bottom = ytext + surfaceWindow->Descent(font) + 1;
	char *chunkVal = val;
	bool moreChunks = true;
	int maxWidth = 0;
	//{{Suzsoft add for gensym 347
	int startHL = 0;    //start highlight argument
	int endHL = 0;      //end highlight argument
	int method = 1;
	//get the argument start and end position of the first method 
	DelimitArgInCalltip(val, method, argument, &startHL, &endHL);
	//}}
	while (moreChunks) {
		char *chunkEnd = strchr(chunkVal, '\n');
		if (chunkEnd == NULL) {
			chunkEnd = chunkVal + strlen(chunkVal);
			moreChunks = false;
		}
		int chunkOffset = chunkVal - val;
		int chunkLength = chunkEnd - chunkVal;
		int chunkEndOffset = chunkOffset + chunkLength;
		int thisStartHighlight = Platform::Maximum(startHL, chunkOffset);
		thisStartHighlight = Platform::Minimum(thisStartHighlight, chunkEndOffset);
		thisStartHighlight -= chunkOffset;
		int thisEndHighlight = Platform::Maximum(endHL, chunkOffset);
		thisEndHighlight = Platform::Minimum(thisEndHighlight, chunkEndOffset);
		thisEndHighlight -= chunkOffset;
		rcClient.top = ytext - ascent - 1;

		int x = insetX;     // start each line at this inset

		DrawChunk(surfaceWindow, x, chunkVal, 0, thisStartHighlight,
			ytext, rcClient, false, draw);
		DrawChunk(surfaceWindow, x, chunkVal, thisStartHighlight, thisEndHighlight,
			ytext, rcClient, true, draw);
		DrawChunk(surfaceWindow, x, chunkVal, thisEndHighlight, chunkLength,
			ytext, rcClient, false, draw);

		chunkVal = chunkEnd + 1;
		ytext += lineHeight;
		rcClient.bottom += lineHeight;
		maxWidth = Platform::Maximum(maxWidth, x);

		//{{Suzsoft add for gensym 347
		//whether the "chunkEndOffset" has arrived the method end.
		if(MethodArgOut(val, method, chunkEndOffset))
		{
			//if yes, to get the argument start and end position of the next method
			method ++;
			DelimitArgInCalltip(val, method, argument, &startHL, &endHL);
		}
		//}}
	}
	return maxWidth;
}

void CallTip::PaintCT(Surface *surfaceWindow) {	
	if (!val)
		return;
	PRectangle rcClientPos = wCallTip.GetClientPosition();
	PRectangle rcClientSize(0, 0, rcClientPos.right - rcClientPos.left,
	                        rcClientPos.bottom - rcClientPos.top);
	PRectangle rcClient(1, 1, rcClientSize.right - 1, rcClientSize.bottom - 1);

	surfaceWindow->FillRectangle(rcClient, colourBG.allocated);

	offsetMain = insetX;    // initial alignment assuming no arrows
	PaintContents(surfaceWindow, true);

	// Draw a raised border around the edges of the window
	surfaceWindow->MoveTo(0, rcClientSize.bottom - 1);
	surfaceWindow->PenColour(colourShade.allocated);
	surfaceWindow->LineTo(rcClientSize.right - 1, rcClientSize.bottom - 1);
	surfaceWindow->LineTo(rcClientSize.right - 1, 0);
	surfaceWindow->PenColour(colourLight.allocated);
	surfaceWindow->LineTo(0, 0);
	surfaceWindow->LineTo(0, rcClientSize.bottom - 1);
}

void CallTip::MouseClick(Point pt) {
	clickPlace = 0;
	if (rectUp.Contains(pt))
		clickPlace = 1;
	if (rectDown.Contains(pt))
		clickPlace = 2;

	//{{suzsoft add for gensym-563
	// if it is only a method, not need to refresh the calltip
	if (sumMethod > 1)
	{
		currIndex = (currIndex == sumMethod) ? 1 : ++currIndex;
		CurrCalltipContent();   
		PRectangle rc = UpdateCalltipSize();
		wCallTip.MoveWindow(rc, true);
		wCallTip.InvalidateAll();
	}
	//}}suzsoft
}

PRectangle CallTip::CallTipStart(int pos, Point pt, const char *defn,
                                 const char *faceName, int size,
                                 int codePage_, int characterSet, Window &wParent) {
	clickPlace = 0;
	//{{suzsoft change for Gensym-563	
	//First, delete the all content of old methods from memory
	if (allVal)
	{
		delete []allVal;
		allVal = NULL;
	}
	allVal = new char[strlen(defn) + 1];
	if (!allVal)
		return PRectangle();
	strcpy(allVal, defn);
	
	currIndex = 1;
	sumMethod = GetSumMethod(allVal);
	//Get the currently method that need to be displayed
	CurrCalltipContent();
	if (!val)
		return PRectangle(); 
	//}}Suzsoft
	codePage = codePage_;
	Surface *surfaceMeasure = Surface::Allocate();
	if (!surfaceMeasure)
		return PRectangle();
	surfaceMeasure->Init(wParent.GetID());
	surfaceMeasure->SetUnicodeMode(SC_CP_UTF8 == codePage);
	surfaceMeasure->SetDBCSMode(codePage);
	startHighlight = 0;
	endHighlight = 0;
	argument = 0;
	inCallTipMode = true;
	posStartCallTip = pos;
	int deviceHeight = surfaceMeasure->DeviceHeightFont(size);
	font.Create(faceName, characterSet, deviceHeight, false, false);
	// Look for multiple lines in the text
	// Only support \n here - simply means container must avoid \r!
	numLines = 1;
	const char *newline;
	const char *look = val;
	rectUp = PRectangle(0,0,0,0);
	rectDown = PRectangle(0,0,0,0);
	offsetMain = insetX;            // changed to right edge of any arrows
	int width = PaintContents(surfaceMeasure, false) + insetX;
	while ((newline = strchr(look, '\n')) != NULL) {
		look = newline + 1;
		numLines++;
	}
	lineHeight = surfaceMeasure->Height(font);

	// Extra line for border and an empty line at top and bottom. The returned
	// rectangle is aligned to the right edge of the last arrow encountered in
	// the tip text, else to the tip text left edge.
	int height = lineHeight * numLines - surfaceMeasure->InternalLeading(font) + 2 + 2;
	delete surfaceMeasure;
	return PRectangle(pt.x - offsetMain, pt.y + 1, pt.x + width - offsetMain, pt.y + 1 + height);
}

void CallTip::CallTipCancel() {
	inCallTipMode = false;
	if (wCallTip.Created()) {
		wCallTip.Destroy();
	}
}

void CallTip::SetHighlight(int start, int end) {
	// Avoid flashing by checking something has really changed
	if ((start != startHighlight) || (end != endHighlight)) {
		startHighlight = start;
		endHighlight = end;
 		if (wCallTip.Created()) {
			wCallTip.InvalidateAll();
		}
	}
}

//{{Suzsoft add for gensym 347
//give the argument number that need to highlight
void CallTip::SetHighlight(int arg) {
	// Avoid flashing by checking something has really changed
	if (arg != argument) {
		argument = arg;
		if (wCallTip.Created()) {
			wCallTip.InvalidateAll();
		}
	}
}
//}}

// Set the tab size (sizes > 0 enable the use of tabs). This also enables the
// use of the STYLE_CALLTIP.
void CallTip::SetTabSize(int tabSz) {
	tabSize = tabSz;
	useStyleCallTip = true;
}

// It might be better to have two access functions for this and to use
// them for all settings of colours.
void CallTip::SetForeBack(const ColourPair &fore, const ColourPair &back) {
	colourBG = back;
	colourUnSel = fore;
}

//{{Suzsoft add for gensym 347
// Return positions in a CALLTIP (i.e., NOT something in the edit buffer) which
// delimit argument number(arg) and method number(method) , counting from 1. Calltip is ALWAYS of the form:
//
//    fun (arg:type, ..., arg:type) => (type, ... type)
//
// where the return types are optional
// start and end highlight equal 0 if the method do not exist
void CallTip::DelimitArgInCalltip(char *calltip, int method, int arg, int *start, int *end)
{
	char *s, *e, *methodEnd;
	
	s = calltip;
	e = strchr(calltip, '(');
	methodEnd = strchr(calltip, ')');
	while (method > 1)
	{
		e++;
		e = strchr(e, '(');
		methodEnd++;
		methodEnd = strchr(methodEnd, ')');
		if (e == NULL)
		{
			start = 0;
			end = 0;
			return;
		}
		method --;
	}
	
	while(e != NULL && arg>0) {
		s=e+1;
		e=strchr(s,',');
		arg--;

		//not the argument at the method
		if (e > methodEnd)
		{
			e = methodEnd;
			break;
		}
	}
	if(e == NULL) e = strchr(methodEnd,')');
	if(e == NULL) e = calltip + strlen(calltip); // This should never happen.
	*start = s - calltip;
	*end   = e - calltip;
}

//judge whether the position is at the method range
//true: at the method range,  
bool CallTip::MethodArgOut(char *calltip, int method, int pos)
{
	char *methodEnd;

	methodEnd = strchr(calltip, ')');
	while (method > 1)
	{
		methodEnd++;
		methodEnd = strchr(methodEnd, ')');
		if (methodEnd == NULL)
		{
			return true;
		}
		method --;
	}

	if ((methodEnd -calltip) < pos)
		return true;
	else
		return false;
}
//}}

//{{Suzsoft add for Gensym-563

// GENSYMCID-1094: TW Crashes
// We never thought in GENSYMCID-1058, that \n could appear in the middle of a method tooltip
// when it's too long. Now there's a more complicated algorithm for detecting method ends.

char* searchForMethodEnd(char* methodStart)
{
	char *falseEnd, *nextEnd, *p;
	int numLeft, numRight, fullBody = 0;

	// 1. directly return NULL if there's no EOL
	falseEnd = strchr(methodStart, '\n');
	if (!falseEnd)
		return falseEnd;

	// 2. test the grammar of current line: fun (a, b, c) => (), '\n' may in it.
	do {
		numLeft = numRight = 0;
		for (p = methodStart; p < falseEnd; p++) {
			if (*p == '(') numLeft ++;
			if (*p == ')') numRight ++;
			if (*p == '=' && *(p+1) == '>') fullBody = 1;
		}
		if (numLeft == numRight)
			break;
		else
			falseEnd = strchr(falseEnd+1, '\n');
	} while (falseEnd);

	if (!falseEnd || fullBody)
		return falseEnd;

	// 3. check potential rest of body (start with "=>")
	p = falseEnd + 1;
	if (!(*p == '=' && *(p+1) == '>'))
		return falseEnd;

	nextEnd = strchr(falseEnd+1, '\n');
	if (!nextEnd)
		return nextEnd;

	do {
		numLeft = numRight = 0;
		for (p = falseEnd; p < nextEnd; p++) {
			if (*p == '(') numLeft ++;
			if (*p == ')') numRight ++;
		}
		if (numLeft == numRight)
			break;
		else
			nextEnd = strchr(nextEnd+1, '\n');
	} while (nextEnd);

	return nextEnd;
}

// GENSYMCID-1058: Tooltips issue in text editror (Minor update to Request #54443)
// We should delect the number of '\n' in the general form "proc() => ()\n".
int CallTip::GetSumMethod(char *calltip)
{
	int sum = 1;
	char *methodEnd;
	methodEnd = searchForMethodEnd(calltip);
	while (methodEnd)
	{
		sum ++;
		methodEnd ++;
		methodEnd = searchForMethodEnd(methodEnd);
	}
	return sum;
}

void CallTip::CurrCalltipContent()
{
	//First, delete the current the calltip Content
	if (val)
	{
		delete [] val;
		val = NULL;
	}
	if (!allVal)
		return ;
	//Calc the sum of the methods
	sumMethod = sumMethod ? sumMethod : GetSumMethod(allVal);	
	if (sumMethod == 0)
		return ;
	else if (sumMethod == 1)
	{
		// if it is only a method, not show the [(index) of (sum)] (eg, [2 of 4])
		val = new char[strlen(allVal) + 1];
		if (!val)
			return ;
		strcpy(val, allVal);
	}
	else
	{
		// GENSYMCID-1058: Tooltips issue in text editror (Minor update to Request #54443)
		char *methodEnd;
		char *methodStart;
		methodStart = allVal;
		methodEnd = searchForMethodEnd(allVal);
		int index = currIndex;
		// find the method that need to be displayed
		while (index > 1)
		{
			methodStart = ++methodEnd;
			methodEnd = searchForMethodEnd(methodEnd);
			if (methodEnd == NULL)
			{
				methodEnd = allVal + strlen(allVal); // This should never happen.
				break;
			}
			index --;
		}
		methodEnd--; // remove '\n' from results
		int contentLen = methodEnd-methodStart+1;
		char content[1000] = {0};
		for (int n = 0; n < contentLen; n++)
		{
			content[n] = *methodStart;
			methodStart++;
		}

		char buf[1024] = {0};
		//Format the method for display
		sprintf(buf, "[%d of %d] %s", currIndex, sumMethod, content);

		val = new char[strlen(buf) + 1];
		if (!val)
			return ;
		strcpy(val, buf);
	}
}

PRectangle CallTip::UpdateCalltipSize()
{
	const char *newline;
	const char *look = val;
	int oldNumLines = numLines;
	numLines = 1;
	while ((newline = strchr(look, '\n')) != NULL) {
		look = newline + 1;
		numLines++;
	}

	// GENSYMCID-936: Tooltips are truncated in text editor (Disadvantage of text-editor)
	// We need to calculate new width for next val, just update height is NOT enough.
	Surface *surfaceMeasure = Surface::Allocate();
	surfaceMeasure->Init(wDraw.GetID());
	surfaceMeasure->SetUnicodeMode(SC_CP_UTF8 == codePage);
	surfaceMeasure->SetDBCSMode(codePage);
	int width = PaintContents(surfaceMeasure, false) + insetX;
	surfaceMeasure->Release();
	delete surfaceMeasure;

	PRectangle rc = wCallTip.GetPosition(); // Get the old calltip rectangle
	//expand the calltip up or down
	if (isAboveText)
		rc.top -= (numLines - oldNumLines) * lineHeight;
	else
		rc.bottom += (numLines - oldNumLines) * lineHeight;	
	//update new width
	rc.right = rc.left + width; 
	return rc;
}

void CallTip::SetAllCalltipContent(char* allCalltip)
{
	if (allCalltip == NULL)
		return;

	if (allVal)
		delete [] allVal;
	allVal = new char[strlen(allCalltip) + 1];
	if (!allVal)
		return ;
	strcpy(allVal, allCalltip);
}
//}}
