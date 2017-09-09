/*
 * Side menus used at the site.
 *
 * (C) Copyright 2003 Creativyst, Inc.
 *
*/

/* JSCpragma:StartCompress
*/

/*
 * History:
 * ------------
 * Ver      hrs     Date        Pgmr    Comment
 * --------+-------+-----------+-------+---------------------------------------
 * 1.0a       .5    07-Dec-2003 djr     - Change &#149; to &#186; to be
 *                                        compliant with ISO 8899-1.
 *                                      - Add This history section to comments
 *                                      - Change MSDetox management entry to
 *                                        Continous improvement
 *                                      - Add Agile Bridge Building to mgt
 *                                        section
*/

/*
 *
var mType = array();
var mCat = array();
var mText = array();
var mLink = array();
var mTitle = array();
var mStyle = array();
 *
*/


function GetDocMenu()
{
 var rv;

 rv = "";
 rv += '<br>';

 rv += '<!-- ============== -->';
 rv += '<!-- Documents      -->';
 rv += '<!-- ============== -->';
 rv += '<table WIDTH="100%" CELLSPACING="0" CELLPADDING="0" BORDER="0">';
 rv += '<tr>';
 rv += '<td WIDTH="1%">&nbsp;</td>';
 rv += '<td WIDTH="2%" ALIGN="CENTER" VALIGN="TOP" BGColor="#BBBBCC">';

 rv += '<font SIZE="3" FACE="Verdana, Arial, sans-serif" COLOR="#000033">';
 rv += 'D<br>o<br>c<br>u<br>m<br>e<br>n<br>t<br>s<br>';

    rv += '</font>';
 rv += '</td>';
 rv += '<td WIDTH="97%" VALIGN="TOP">';

    rv += '<table WIDTH="100%" CELLSPACING="0" CELLPADDING="0" BORDER="0">';
    rv += '<tr><td CLASS="SecDiv" BGColor="#AAAABB"';
    rv += '>&nbsp;</td></tr></table>';


rv += '<!-- List Content       -->';
rv += '<table WIDTH="100%" CELLSPACING="0" CELLPADDING="1px" BORDER="0">';

 rv += '<tr><td COLSPAN="2" CLASS="PedHead" ALIGN="LEFT">';
    rv += 'How To';
 rv += '</td></tr>';

 rv += '<tr>';
 rv += '<td WIDTH="10%" CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td WIDTH="90%" ALIGN="LEFT">';
    rv += '<a HREF="';
 rv += 'http://www.creativyst.com/Doc/Articles/SoundEx1/SoundEx1.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Evaluate Words that Sound Alike Using the SoundEx Algorithm"';
    rv += 'CLASS="Ped"';
    rv += '>Understanding SoundEx</a><br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
 rv += 'http://www.creativyst.com/Doc/Articles/CSV/CSV01.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="All About Comma Separated Values (w/XML converter)"';
    rv += 'CLASS="Ped"';
    rv += '>CSV File Format</a><br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Doc/Articles/RoundTbl/RouTable.htm"';
    rv += 'CLASS="Ped"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Use small graphics to create this popular effect"';
    rv += '>Round Table Corners</a><br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">';
    rv += '&#186;';
 rv += '</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
 rv += '<a HREF="';
 rv += 'http://www.creativyst.com/Doc/Articles/MFlwrs/MFlwrs.htm"';
 rv += 'STYLE="cursor:help"';
 rv += 'TITLE="Interesting Ways to Practice Table-Design Skills"';
    rv += 'CLASS="Ped"';
    rv += '>Menu Flowers (exercise)</a><br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td WIDTH="10%" CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td WIDTH="90%" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Doc/Articles/XMLhtmlT/XMLhtmlT.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="I.E. Only: Display XML data in your HTML documents"';
    rv += 'CLASS="Ped"';
    rv += '>Show XML w/I.E. Browsers</a><br><BR/>';
 rv += '</td>';
 rv += '</tr>';



 rv += '<tr><td COLSPAN="2" CLASS="PedHead">';
     rv += 'Conventions';
 rv += '</td></tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Prod/Glossary/Doc/XMLOut.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Proposed XML format for Glossary Transport"';
    rv += 'CLASS="Ped"';
    rv += '>Glosssary XML</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Prod/18/HelpJSM.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Share content in a true format-independent way using JavaScript"';
    rv += 'CLASS="Ped"';
    rv += '>The JSMsg Convention</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Doc/Std/CUF/"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Creativyst Universal Formatting Codes - CUF(tm)"';
    rv += 'CLASS="Ped"';
    rv += '>CUF&#153; Codes</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped" ALIGN="LEFT">';
    rv += '<a HREF="';
    rv += 'http://www.creativyst.com/Doc/Std/StableSW/v10a/StabSW01.htm"';
    rv += 'STYLE="cursor:help"';
    rv += 'TITLE="Separating stability from version maturity"';
    rv += 'CLASS="Ped"';
    rv += '>Software Stability Ratings</a>';

 rv += '<br><br>';
 rv += '</td>';
 rv += '</tr>';


 rv += '<tr><td COLSPAN="2" CLASS="PedHead">';
     rv += 'Managing IT';
 rv += '</td></tr>';

 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped">';
     rv += '<a ';
     rv += 'STYLE="cursor:help"';
     rv += 'TITLE="';
     rv += 'Reduce your shop\'s Microsoft dependency without changing religions"';
     rv += 'CLASS="Ped"';
     rv += 'HREF="http://www.creativyst.com/Doc/Articles/Mgt/MSDetox/MSDetox.htm"';
     rv += '>Continuous Independence</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';


 rv += '<TR>';
 rv += '<TD  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</TD>';
 rv += '<TD CLASS="Ped">';
 rv += '    <A';
 rv += '      STYLE="cursor:help"';
 rv += '      TITLE=';
 rv += '"Prerequisite: Knowing what it takes to complete a job well done"';
 rv += '      CLASS="Ped"';
 rv += '      HREF=';
 rv += 
 '"http://www.creativyst.com/Doc/Articles/Mgt/AgileBridges/AgileBridges.htm"';
 rv += '    >Agile Bridge Building</A>';
 rv += '<BR>';
 rv += '</TD>';
 rv += '</TR>';



 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped">';
     rv += '<a ';
     rv += 'STYLE="cursor:help"';
     rv += 'TITLE="';
     rv += 'The What, Why, and How of Platform Independent Computing"';
     rv += 'CLASS="Ped"';
     rv += 'HREF="http://www.creativyst.com/Doc/Articles/Mgt/PIC/PIC.htm"';
     rv += '>Platform Neutral Computing</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';



 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped">';
     rv += '<a ';
     rv += 'STYLE="cursor:help"';
     rv += 'TITLE="Don\'t just do it - Links for better decision-making"';
     rv += 'CLASS="Ped"';
     rv += 'HREF="http://www.creativyst.com/Doc/Articles/Mgt/Outsrc1.htm"';
     rv += '>When NOT to Outsource</a>';
 rv += '<br>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';



 rv += '<tr><td COLSPAN="2" CLASS="PedHead">';
     rv += 'Random Notes';
 rv += '</td></tr>';


/*
 *
 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped">';
     rv += '<a ';
       rv += 'STYLE="cursor:help"';
       rv += 'TITLE="';
      rv += 'Work In Progress -- A Simple CSS Cheat Sheet"';
       rv += 'CLASS="Ped"';
       rv += 'HREF="http://www.creativyst.com/Doc/RndNotes/CSSCheat/CSSTop.htm"';
     rv += '>CSS Quick Reference</a>';
 rv += '<br>';
 rv += '</td>';
 rv += '</tr>';
 *
*/



 rv += '<tr>';
 rv += '<td  CLASS="Ped" ALIGN="RIGHT" VALIGN="TOP">&#186;</td>';
 rv += '<td CLASS="Ped">';
     rv += '<a ';
       rv += 'STYLE="cursor:help"';
       rv += 'TITLE="';
      rv += 'The hype itself looks the same, whether the product is good or bad"';
       rv += 'CLASS="Ped"';
       rv += 'HREF="http://www.creativyst.com/Doc/RndNotes/HypeCut1.htm"';
     rv += '>Seeing Through Hype</a>';
 rv += '<br><br>';
 rv += '</td>';
 rv += '</tr>';


 rv += '</table>';
 rv += '<!-- end content list   -->';


 rv += '</td>';
 rv += '</tr>';
 rv += '</table>';
 rv += '<!-- ============== -->';
 rv += '<!-- End Documents  -->';
 rv += '<!-- ============== -->\n';



 return(rv);

}


