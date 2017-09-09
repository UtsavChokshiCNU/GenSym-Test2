/*****************************************************************************
*                                                                            *
*  Copyright 1992, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
* $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/flat/finfotbl.c,v 1.1 1995-10-03 00:57:13 jra Exp $
*
* $Log: not supported by cvs2svn $
* Revision 1.2  1995/03/14 00:29:52  mhd
* Have this be up to date with my sandbox.  This is for me just an offline
* version of the font files in /bt/.../ext/c, for offline testing and
* development.
*
 * Revision 1.1  1993/05/04  20:12:33  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.2  1993/04/19  15:36:03  mpc
 * Removed {}'s from font name defines, per bitstream.
 * Changed numerous function defs to handle PROTOS_AVAIL convention.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:24  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 1.14  93/03/16  10:20:52  roberte
 * Changed comments of 8 TrueType emulators from SWA to SWM.
 * 
 * Revision 1.13  93/03/15  12:40:24  roberte
 * Release
 * 
 * Revision 1.12  93/02/12  16:26:53  roberte
 * Added #define of O_BINARY for non-INTEL builds, and use of
 * this bit flag in the "open" call.
 * 
 * Revision 1.11  93/02/01  14:22:25  roberte
 * Removed OLDWAY block fro Courier New, and left Courier
 * New having NEXT_NONE for support instead of SERIF.
 * 
 * Revision 1.10  93/01/12  12:50:36  roberte
 * Support typefaces now tagged as pdlSupport.
 * Changes for Arial and Times New Roman. New font IDs.
 * 
 * Revision 1.9  92/11/19  09:04:20  roberte
 * Corrected spelling of Helvetica-Narrow typeface industry names.
 * 
 * Revision 1.8  92/11/02  09:16:38  roberte
 * Changes within the nextSearchEncode field for the Couriers and Letter Gothics.
 * The contain all support within themselves.
 * 
 * Revision 1.7  92/10/29  15:34:06  roberte
 * Corrected nextSearchEncode for Coronet. 
 * 
 * Revision 1.6  92/10/29  09:19:16  roberte
 * Corrected number of fonts in menu.
 * 
 * Revision 1.5  92/10/28  08:55:58  roberte
 * Changes reflecting actual internal fonts in the LJIV printer.
 * No dingbats and no antique olive bold italic.
 * 
 * Revision 1.4  92/10/01  20:00:12  laurar
 * take out errno which is an illegal variable name on PC;
 * variable was not referenced anyway.
 * 
 * Revision 1.3  92/09/29  16:27:25  laurar
 * add header files for INTEL
 * 
 * Revision 1.2  92/09/26  14:13:18  roberte
 * Added copyright header and RCS markers.
 * 
*****************************************************************************/
/*****************************************************************************
    FILE:        FINFOTBL.C
    PROJECT:    4-in-1
    PURPOSE:    Builds a utility program to write out binary
                files (Font Information Tables) for various
                font configurations for the 4-in-1 project.
    METHOD:        Prompt the user with a menu of configuration
                possiblities, build the appropriate set
                from a "library" of all possibilities, and
                write out that custom set as a binary image file.
    AUTHOR:        RJE @ Bitstream Inc.
    CREATED:    08-14-92
******************************************************************************/

#include <fcntl.h>                /* get O_???? types */
#include <sys/types.h>            /* get size_t, S_I???? */
#include <sys/stat.h>
#ifdef INTEL
#include <stdio.h>
#include <stddef.h>
#else
#define O_BINARY 0
#endif
#include "stdef.h"                /* get Bitstream data types and constants */
#include "finfotbl.h"            /* data structure of Font Info Table */
#include "pclhdrs.h"            /* macros of PCL Header data */

#define PCLS1Name     "Line Printer"
#define PCLS2Name     "Plugin Roman Serif"
#define PCLS3Name     "Plugin Roman Serif Bold"
#define PCLS4Name     "Plugin Sanserif"
#define PCLS5Name     "Plugin Sanserif Bold"
#ifdef HAVE_STICK_FONT
#define PCLS6Name     "HP Stick Font"
#endif

#define PCL1Name     "CG-Times"
#define PCL2Name     "CG-Times Italic"
#define PCL3Name     "CG-Times Bold"
#define PCL4Name     "CG-Times Bold Italic"
#define PCL5Name     "Univers"
#define PCL6Name     "Univers Italic"
#define PCL7Name     "Univers Bold"
#define PCL8Name     "Univers Bold Italic"

#define PCL9Name     "Univers Condensed"
#define PCL10Name     "Univers Condensed Italic"
#define PCL11Name     "Univers Condensed Bold"
#define PCL12Name     "Univers Condensed Bold Italic"
#define PCL13Name     "ITC Zapf Dingbats"

#define PCL14Name     "ITC Souvenir Light"
#define PCL15Name     "ITC Souvenir Light Italic"
#define PCL16Name     "ITC Souvenir Demi"
#define PCL17Name     "ITC Souvenir Demi Italic"
#define PCL18Name     "CG Palacio"
#define PCL19Name     "CG Palacio Italic"
#define PCL20Name     "CG Palacio Bold"
#define PCL21Name     "CG Palacio Bold Italic"

#define PCL22Name     "Antique Olive"
#define PCL23Name     "Antique Olive Italic"
#define PCL24Name     "Antique Olive Bold"
#define PCL25Name     "Antique Olive Bold Italic"

#define PCL26Name     "CG Century Schoolbook"
#define PCL27Name     "CG Century Schoolbook Italic"
#define PCL28Name     "CG Century Schoolbook Bold"
#define PCL29Name     "CG Century Schoolbook Bold Italic"
#define PCL30Name     "Stymie"
#define PCL31Name     "Stymie Italic"
#define PCL32Name     "Stymie Bold"
#define PCL33Name     "Stymie Bold Italic"

#define PCL34Name     "CG Omega"
#define PCL35Name     "CG Omega Italic"
#define PCL36Name     "CG Omega Bold"
#define PCL37Name     "CG Omega Bold Italic"

#define PCL38Name     "CG Bodini"
#define PCL39Name     "CG Bodini Italic"
#define PCL40Name     "CG Bodini Bold"
#define PCL41Name     "CG Bodini Bold Italic"
#define PCL42Name     "ITC Benguiat"
#define PCL43Name     "ITC Benguiat Italic"
#define PCL44Name     "ITC Benguiat Bold"
#define PCL45Name     "ITC Benguiat Bold Italic"
#define PCL46Name     "ITC Bookman Light"
#define PCL47Name     "ITC Bookman Light Italic"
#define PCL48Name     "ITC Bookman Demi"
#define PCL49Name     "ITC Bookman Demi Italic"

#define PCL50Name     "Garamond"
#define PCL51Name     "Garamond Italic"
#define PCL52Name     "Garamond Bold"
#define PCL53Name     "Garamond Bold Italic"

#define PCL54Name     "Shannon"
#define PCL55Name     "Shannon Italic"
#define PCL56Name     "Shannon Bold"
#define PCL57Name     "Shannon Bold Italic"
#define PCL58Name     "Revue Light"
#define PCL59Name     "Cooper Black"

#define PCL60Name     "Courier Medium"
#define PCL61Name     "Courier Bold"
#define PCL62Name     "Courier Italic"
#define PCL63Name     "Courier Bold Italic"
#define PCL64Name     "Letter Gothic Regular"
#define PCL65Name     "Letter Gothic Bold"
#define PCL66Name     "Letter Gothic Italic"

#define PCL67Name     "Albertus Medium"
#define PCL68Name     "Albertus Extrabold"
#define PCL69Name     "Clarendon Condensed"
#define PCL70Name     "Coronet"
#define PCL71Name     "Marigold"

#define PS1Name     "Times-Roman"
#define PS2Name     "Times-Italic"
#define PS3Name     "Times-Bold"
#define PS4Name     "Times-BoldItalic"
#define PS5Name     "Helvetica"
#define PS6Name     "Helvetica-Oblique"
#define PS7Name     "Helvetica-Bold"
#define PS8Name     "Helvetica-BoldOblique"
#define PS9Name     "Courier"
#define PS10Name     "Courier-Oblique"
#define PS11Name     "Courier-Bold"
#define PS12Name     "Courier-BoldOblique"
#define PS13Name     "Symbol"
#define PS14Name     "Palatino-Roman"
#define PS15Name     "Palatino-Italic"
#define PS16Name     "Palatino-Bold"
#define PS17Name     "Palatino-BoldItalic"
#define PS18Name     "Bookman-Light"
#define PS19Name     "Bookman-LightItalic"
#define PS20Name     "Bookman-Demi"
#define PS21Name     "Bookman-DemiItalic"
#define PS22Name     "Helvetica-Narrow"
#define PS23Name     "Helvetica-Narrow-Oblique"
#define PS24Name     "Helvetica-Narrow-Bold"
#define PS25Name     "Helvetica-Narrow-BoldOblique"
#define PS26Name     "NewCenturySchlbk-Roman"
#define PS27Name     "NewCenturySchlbk-Italic"
#define PS28Name     "NewCenturySchlbk-Bold"
#define PS29Name     "NewCenturySchlbk-BoldItalic"
#define PS30Name     "AvantGarde-Book"
#define PS31Name     "AvantGarde-BookOblique"
#define PS32Name     "AvantGarde-Demi"
#define PS33Name     "AvantGarde-DemiOblique"
#define PS34Name     "ZapfChancery-MediumItalic"
#define PS35Name     "ZapfDingbats"

#define TT1Name     "Arial"
#define TT2Name     "Arial Italic"
#define TT3Name     "Arial Bold"
#define TT4Name     "Arial Bold Italic"
#define TT5Name     "Times New Roman"
#define TT6Name     "Times New Roman Italic"
#define TT7Name     "Times New Roman Bold"
#define TT8Name     "Times New Roman Bold Italic"

#define TT9Name      "Courier New"
#define TT10Name     "Courier New Italic"
#define TT11Name     "Courier New Bold"
#define TT12Name     "Courier New Bold Italic"

#define TT13Name     "Symbol"
#define TT14Name     "Wingdings"

int gCurFontIdx;
FontInfoType gFontInfoTable[N_LOGICAL_FONTS];


FontInfoType gSrcFontInfoTable[N_LOGICAL_FONTS] =
{
/*------------ Auxilliary or Background font support ----------------*/
    /* [font3162.spd]  -> Line Printer */
    {PCLS1Name, PCLS1Hdr, pdlSupport, NULLCHARPTR, NEXT_NONE},
    /* [font3158.spd]  -> Plugin Roman Serif */
    {PCLS2Name, PCLS2Hdr, pdlSupport, NULLCHARPTR, BUCKET},
    /* [font3159.spd]  -> Plugin Roman Serif Bold */
    {PCLS3Name, PCLS3Hdr, pdlSupport, NULLCHARPTR, BUCKET},
    /* [font3160.spd]  -> Plugin Sanserif */
    {PCLS4Name, PCLS4Hdr, pdlSupport, NULLCHARPTR, BUCKET},
    /* [font3161.spd]  -> Plugin Sanserif Bold */
    {PCLS5Name, PCLS5Hdr, pdlSupport, NULLCHARPTR, BUCKET},
#ifdef HAVE_STICK_FONT
    /* [font????.spd]  -> HP Stick Font */
    {PCLS6Name, PCLS6Hdr, pdlSupport, NULLCHARPTR, BUCKET},
#endif

/*------------ HP PCL emulators ----------------*/
    /* [font3150.spd] Dutch801 SWC -> CG-Times */
    {PCL1Name, PCL1Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3151.spd] Dutch801 SWC -> CG-Times Italic */
    {PCL2Name, PCL2Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3152.spd] Dutch801 SWC -> CG-Times Bold */
    {PCL3Name, PCL3Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3153.spd] Dutch801 SWC -> CG-Times Bold Italic */
    {PCL4Name, PCL4Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3154.spd] Swiss742 SWC -> Univers */
    {PCL5Name, PCL5Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3155.spd] Swiss742 SWC -> Univers Italic */
    {PCL6Name, PCL6Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3156.spd] Swiss742 SWC -> Univers Bold */
    {PCL7Name, PCL7Hdr, pdlPCL, NULLCHARPTR, SANS_BOLD},
    /* [font3157.spd] Swiss742 SWC -> Univers Bold Italic */
    {PCL8Name, PCL8Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3183.spd] Swiss742 Cn SWC -> Univers Condensed */
    {PCL9Name, PCL9Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3184.spd] Swiss742 Cn SWC -> Univers Condensed Italic */
    {PCL10Name, PCL10Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3185.spd] Swiss742 Cn SWC -> Univers Condensed Bold */
    {PCL11Name, PCL11Hdr, pdlPCL, NULLCHARPTR, SANS_BOLD},
    /* [font3186.spd] Swiss742 Cn SWC -> Univers Condensed Bold Italic */
    {PCL12Name, PCL12Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3213.spd] ZapfDingbats SWC -> ITC Zapf Dingbats */
    {PCL13Name, PCL13Hdr, pdlPCL, NULLCHARPTR, BUCKET},

    /* [font3163.spd] Souvenir SWC -> ITC Souvenir Light */
    {PCL14Name, PCL14Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3164.spd] Souvenir SWC -> ITC Souvenir Light Italic */
    {PCL15Name, PCL15Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3165.spd] Souvenir SWC -> ITC Souvenir Demi */
    {PCL16Name, PCL16Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3166.spd] Souvenir SWC -> ITC Souvenir Demi Italic */
    {PCL17Name, PCL17Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3167.spd] ZapfCallig SWC -> CG Palacio */
    {PCL18Name, PCL18Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3168.spd] ZapfCallig SWC -> CG Palacio Italic */
    {PCL19Name, PCL19Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3169.spd] ZapfCallig SWC -> CG Palacio Bold */
    {PCL20Name, PCL20Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3170.spd] ZapfCallig SWC -> CG Palacio Bold Italic */
    {PCL21Name, PCL21Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3179.spd] Incised901 SWC -> Antique Olive */
    {PCL22Name, PCL22Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3180.spd] Incised901 SWC -> Antique Olive Italic */
    {PCL23Name, PCL23Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3181.spd] Incised901 SWC -> Antique Olive Bold */
    {PCL24Name, PCL24Hdr, pdlPCL, NULLCHARPTR, SANS_BOLD},
    /* [font3182.spd] Incised901Ct SWC -> Antique Olive Bold Italic */
    {PCL25Name, PCL25Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3175.spd] CenturySchbk SWC -> CG Century Schoolbook */
    {PCL26Name, PCL26Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3176.spd] CenturySchbk SWC -> CG Century Schoolbook Italic */
    {PCL27Name, PCL27Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3177.spd] CenturySchbk SWC -> CG Century Schoolbook Bold */
    {PCL28Name, PCL28Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3178.spd] CenturySchbk SWC -> CG Century Schoolbook Bold Italic */
    {PCL29Name, PCL29Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3187.spd] Stymie SWC -> Stymie */
    {PCL30Name, PCL30Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3188.spd] Stymie SWC -> Stymie Italic */
    {PCL31Name, PCL31Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3189.spd] Stymie SWC -> Stymie Bold */
    {PCL32Name, PCL32Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3190.spd] Stymie SWC -> Stymie Bold Italic */
    {PCL33Name, PCL33Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3191.spd] ZapfHumst Dm SWC -> CG Omega */
    {PCL34Name, PCL34Hdr, pdlPCL, NULLCHARPTR, 	SANS},
    /* [font3192.spd] ZapfHumst Dm SWC -> CG Omega Italic */
    {PCL35Name, PCL35Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3193.spd] ZapfHumst Dm SWC -> CG Omega Bold */
    {PCL36Name, PCL36Hdr, pdlPCL, NULLCHARPTR, SANS_BOLD},
    /* [font3194.spd] ZapfHumst Dm SWC -> CG Omega Bold Italic */
    {PCL37Name, PCL37Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3195.spd] Bodoni Bk SWC -> CG Bodini */
    {PCL38Name, PCL38Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3196.spd] Bodoni Bk SWC -> CG Bodini Italic */
    {PCL39Name, PCL39Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3197.spd] Bodoni Bk SWC -> CG Bodini Bold */
    {PCL40Name, PCL40Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3198.spd] Bodoni Bk SWC -> CG Bodini Bold Italic */
    {PCL41Name, PCL41Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3199.spd] Benguiat SWC -> ITC Benguiat */
    {PCL42Name, PCL42Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3200.spd] Benguiat SWC -> ITC Benguiat Italic */
    {PCL43Name, PCL43Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3201.spd] Benguiat SWC -> ITC Benguiat Bold */
    {PCL44Name, PCL44Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3202.spd] Benguiat SWC -> ITC Benguiat Bold Italic */
    {PCL45Name, PCL45Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3171.spd] Bookman SWC -> ITC Bookman Light */
    {PCL46Name, PCL46Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3172.spd] Bookman SWC -> ITC Bookman Light Italic */
    {PCL47Name, PCL47Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3173.spd] Bookman SWC -> ITC Bookman Demi */
    {PCL48Name, PCL48Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3174.spd] Bookman SWC -> ITC Bookman Demi Italic */
    {PCL49Name, PCL49Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3203.spd] OrigGaramond SWC -> Garamond */
    {PCL50Name, PCL50Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3204.spd] OrigGaramond SWC -> Garamond Italic */
    {PCL51Name, PCL51Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3205.spd] OrigGaramond SWC -> Garamond Bold */
    {PCL52Name, PCL52Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3206.spd] OrigGaramond SWC -> Garamond Bold Italic */
    {PCL53Name, PCL53Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3209.spd] Chianti SWC -> Shannon */
    {PCL54Name, PCL54Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3210.spd] Chianti SWC -> Shannon Italic */
    {PCL55Name, PCL55Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3211.spd] Chianti SWC -> Shannon Bold */
    {PCL56Name, PCL56Hdr, pdlPCL, NULLCHARPTR, SANS_BOLD},
    /* [font3212.spd] Chianti XBd SWC -> Shannon Bold Italic */
    {PCL57Name, PCL57Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3208.spd] Revue Lt SWC -> Revue Light */
    {PCL58Name, PCL58Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3207.spd] Cooper Blk SWC -> Cooper Black */
    {PCL59Name, PCL59Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},

    /* [font3220.spd]  -> Courier Medium */
    {PCL60Name, PCL60Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3221.spd]  -> Courier Italic */
    {PCL62Name, PCL62Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3222.spd]  -> Courier Bold */
    {PCL61Name, PCL61Hdr, pdlPCL, NULLCHARPTR, UP_TWO},
    /* [font3223.spd]  -> Courier Bold Italic */
    {PCL63Name, PCL63Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3224.spd]  -> Letter Gothic Regular */
    {PCL64Name, PCL64Hdr, pdlPCL, NULLCHARPTR, SANS},
    /* [font3225.spd]  -> Letter Gothic Italic */
    {PCL66Name, PCL66Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3226.spd]  -> Letter Gothic Bold */
    {PCL65Name, PCL65Hdr, pdlPCL, NULLCHARPTR, UP_TWO},
    /* [font3215.spd]  -> Albertus Medium */
    {PCL67Name, PCL67Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3216.spd]  -> Albertus Extrabold */
    {PCL68Name, PCL68Hdr, pdlPCL, NULLCHARPTR, SERIF_BOLD},
    /* [font3214.spd]  -> Clarendon Condensed */
    {PCL69Name, PCL69Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3217.spd]  -> Coronet */
    {PCL70Name, PCL70Hdr, pdlPCL, NULLCHARPTR, SERIF},
    /* [font3218.spd]  -> Marigold */
    {PCL71Name, PCL71Hdr, pdlPCL, NULLCHARPTR, SERIF},

/*------------ PostScript 13 and 35 ----------------*/
    /* [font3000.spd] Dutch SWA -> Times */
    {PS1Name, PS1Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3001.spd] Dutch SWA -> Times Italic */
    {PS2Name, PS2Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3002.spd] Dutch SWA -> Times Bold */
    {PS3Name, PS3Hdr, pdlPostScript, NULLCHARPTR, SERIF_BOLD},
    /* [font3003.spd] Dutch SWA -> Times Bold Italic */
    {PS4Name, PS4Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3004.spd] Swiss SWA -> Helvetica */
    {PS5Name, PS5Hdr, pdlPostScript, NULLCHARPTR, SANS},
    /* [font3005.spd] Swiss SWA -> Helvetica Italic */
    {PS6Name, PS6Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3006.spd] Swiss SWA -> Helvetica Bold */
    {PS7Name, PS7Hdr, pdlPostScript, NULLCHARPTR, SANS_BOLD},
    /* [font3007.spd] Swiss SWA -> Helvetica Bold Italic */
    {PS8Name, PS8Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3008.spd] Courier SWA -> Courier */
    {PS9Name, PS9Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3009.spd] Courier SWA -> Courier Italic */
    {PS10Name, PS10Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3010.spd] Courier SWA -> Courier Bold */
    {PS11Name, PS11Hdr, pdlPostScript, NULLCHARPTR, SERIF_BOLD},
    /* [font3011.spd] Courier SWA -> Courier Bold Italic */
    {PS12Name, PS12Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3012.spd] Symbol Set SWA -> Symbol */
    {PS13Name, PS13Hdr, pdlPostScript, NULLCHARPTR, NEXT_NONE},

    /* [font3013.spd] ZapfCallig SWA -> Palatino */
    {PS14Name, PS14Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3014.spd] ZapfCallig SWA -> Palatino Italic */
    {PS15Name, PS15Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3015.spd] ZapfCallig SWA -> Palatino Bold */
    {PS16Name, PS16Hdr, pdlPostScript, NULLCHARPTR, SERIF_BOLD},
    /* [font3016.spd] ZapfCallig SWA -> Palatino Bold Italic */
    {PS17Name, PS17Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3021.spd] Bookman SWA -> ITC Bookman */
    {PS18Name, PS18Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3022.spd] Bookman SWA -> ITC Bookman Italic */
    {PS19Name, PS19Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3023.spd] Bookman SWA -> ITC Bookman Bold */
    {PS20Name, PS20Hdr, pdlPostScript, NULLCHARPTR, SERIF_BOLD},
    /* [font3024.spd] Bookman SWA -> ITC Bookman Bold Italic */
    {PS21Name, PS21Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3025.spd] SwissNarrow SWA -> Helvetica Narrow */
    {PS22Name, PS22Hdr, pdlPostScript, NULLCHARPTR, SANS},
    /* [font3026.spd] SwissNarrow SWA -> Helvetica Narrow Italic */
    {PS23Name, PS23Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3027.spd] SwissNarrow SWA -> Helvetica Narrow Bold */
    {PS24Name, PS24Hdr, pdlPostScript, NULLCHARPTR, SANS_BOLD},
    /* [font3028.spd] SwissNarrow SWA -> Helvetica Narrow Bold Italic */
    {PS25Name, PS25Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3031.spd] CenturySchbk SWA -> Century Schoolbook */
    {PS26Name, PS26Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3032.spd] CenturySchbk SWA -> Century Schoolbook Italic */
    {PS27Name, PS27Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3033.spd] CenturySchbk SWA -> Century Schoolbook Bold */
    {PS28Name, PS28Hdr, pdlPostScript, NULLCHARPTR, SERIF_BOLD},
    /* [font3034.spd] CenturySchbk SWA -> Century Schoolbook Bold Italic */
    {PS29Name, PS29Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3017.spd] AvantGarde SWA -> ITC Avant Garde */
    {PS30Name, PS30Hdr, pdlPostScript, NULLCHARPTR, SANS},
    /* [font3018.spd] AvantGarde SWA -> ITC Avant Garde Italic */
    {PS31Name, PS31Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3019.spd] AvantGarde SWA -> ITC Avant Garde Bold */
    {PS32Name, PS32Hdr, pdlPostScript, NULLCHARPTR, SANS_BOLD},
    /* [font3020.spd] AvantGarde SWA -> ITC Avant Garde Bold Italic */
    {PS33Name, PS33Hdr, pdlPostScript, NULLCHARPTR, UP_ONE},
    /* [font3029.spd] ZapfChancery SWA -> ITC Zapf Chancery */
    {PS34Name, PS34Hdr, pdlPostScript, NULLCHARPTR, SERIF},
    /* [font3030.spd] ZapfDingbats SWA -> ITC Zapf Dingbats */
    {PS35Name, PS35Hdr, pdlPostScript, NULLCHARPTR, NEXT_NONE},

/*------------ TrueType fonts ----------------*/
    /* [font3238.spd] Swiss SWM -> Arial */
    {TT1Name, TT1Hdr, pdlGDI, NULLCHARPTR, DOWN_FOUR},
    /* [font3239.spd] Swiss SWM -> Arial Italic */
    {TT2Name, TT2Hdr, pdlGDI, NULLCHARPTR, UP_ONE},
    /* [font3240.spd] Swiss SWM -> Arial Bold */
    {TT3Name, TT3Hdr, pdlGDI, NULLCHARPTR, UP_TWO},
    /* [font3241.spd] Swiss SWM -> Arial Bold Italic */
    {TT4Name, TT4Hdr, pdlGDI, NULLCHARPTR, UP_ONE},
    /* [font3234.spd] Dutch SWM -> Times New Roman */
    {TT5Name, TT5Hdr, pdlGDI, NULLCHARPTR, NEXT_NONE}, /* the buck stops here */
    /* [font3235.spd] Dutch SWM -> Times New Roman Italic */
    {TT6Name, TT6Hdr, pdlGDI, NULLCHARPTR, UP_ONE},
    /* [font3236.spd] Dutch SWM -> Times New Roman Bold */
    {TT7Name, TT7Hdr, pdlGDI, NULLCHARPTR, UP_TWO},
    /* [font3237.spd] Dutch SWM -> Times New Roman Bold Italic */
    {TT8Name, TT8Hdr, pdlGDI, NULLCHARPTR, UP_ONE},

    /* [font3220.spd]  -> Courier Medium */
    {PCL60Name, PCL60Hdr, pdlPCL, NULLCHARPTR, NEXT_NONE},
    /* [font3221.spd]  -> Courier Italic */
    {PCL62Name, PCL62Hdr, pdlPCL, NULLCHARPTR, UP_ONE},
    /* [font3222.spd]  -> Courier Bold */
    {PCL61Name, PCL61Hdr, pdlPCL, NULLCHARPTR, UP_TWO},
    /* [font3223.spd]  -> Courier Bold Italic */
    {PCL63Name, PCL63Hdr, pdlPCL, NULLCHARPTR, UP_ONE},

    /* [font3012.spd] Symbol Set SWA -> Symbol */
    {TT13Name, TT13Hdr, pdlGDI, NULLCHARPTR, NEXT_NONE},
    /* [font3219.spd] More Wingbats SWC -> Wingdings */
    {TT14Name, TT14Hdr, pdlGDI, NULLCHARPTR, NEXT_NONE}
};


/* possible ItemRet codes for the Menu Items: */
enum
{
    NO_ITEM_SEL = -1, 
    ITEM_LJIII,
    ITEM_LJIIISI,
    ITEM_HPCART1,
    ITEM_HPCART2,
    ITEM_HPCART3,
    ITEM_LJIV,
    ITEM_TRUETYPE14,
    ITEM_POSTSCRIPT13,
    ITEM_POSTSCRIPT35,
    ITEM_POSTSCRIPT13andTRUETYPE14,
    ITEM_POSTSCRIPT35andTRUETYPE14,
    ITEM_MAXITEMS    /* terminator, insert new items before */
};

/* current default file name, set based on menu choice: */
char gOutFileDefault[32];

/* current file name, set from default, or by gets(): */
char gCurFileName[128];

/* number of items in the Menu: */
int gNMenuItems = ITEM_MAXITEMS+1;

/* structure definition of the Menu: */
typedef struct
{
    char    *ItemStr;
    int        ItemRet;
}MenuType, *MenuTypePtr;

/* the Menu declaration itself: */
MenuType gTheMenu[] =
{
    {" 1) HP LaserJet III Compatible Core (13 fonts)",   ITEM_LJIII},
    {" 2) HP LaserJetIII Si Compatible Core (18 fonts)", ITEM_LJIIISI},
    {" 3) HP Cartridge 1 (25 fonts)",                    ITEM_HPCART1},
    {" 4) HP Cartridge 2 (26 fonts)",                    ITEM_HPCART2},
    {" 5) HP Cartridge 3 (51 fonts)",                    ITEM_HPCART3},
    {" 6) HP LJ-4 Compatible Core (50 fonts)",           ITEM_LJIV},
    {" 7) TrueType 14 (14 fonts)",                       ITEM_TRUETYPE14},
    {" 8) PostScript 13 (13 fonts)",                     ITEM_POSTSCRIPT13},
    {" 9) PostScript 35 (35 fonts)",                     ITEM_POSTSCRIPT35},
    {"10) PostScript 13 plus TrueType 14 (27 fonts)",
                                             ITEM_POSTSCRIPT13andTRUETYPE14},
    {"11) PostScript 35 plus TrueType 14 (49 fonts)",
                                             ITEM_POSTSCRIPT35andTRUETYPE14},
    {"12) Quit",       NO_ITEM_SEL} /* terminator, insert new items before */
};

/* default output file names for each non-quit choice in the Menu: */
char *gDefaultFileNames[] =
{
    "hplj3.bin",
    "hplj3si.bin",
    "hpcart1.bin",
    "hpcart2.bin",
    "hpcart3.bin",
    "hplj4.bin",
    "tt14.bin",
    "ps13.bin",
    "ps35.bin",
    "ps13-tt14.bin",
    "ps35-tt14.bin",
    NULLCHARPTR    /* terminator, insert new ones before */
};

/************************************************************************
    The main program.
    Process menu choices, writing out files, until finished.
************************************************************************/
main()
{
int choice, nFonts, fd;
char done = FALSE;
int Ok = TRUE;
size_t toWrite;
    while (!done && Ok)
        {
        nFonts = 0;
        done = ((choice = MenuSelect(gTheMenu, gNMenuItems)) == NO_ITEM_SEL);
        if (!done)
            {
            /* prepare gFontInfoTable[] based on choice: */
            nFonts = PrepareFontOutPut(choice);

            /* get the default file name for this menu choice: */
            strcpy(gOutFileDefault, gDefaultFileNames[choice]);

            /* let the user edit their own file name: */
            memset(gCurFileName, 0, sizeof(gCurFileName));
            fprintf(stderr,"\nOutput file name [default = %s]",
                                                           gOutFileDefault);
            if(!gets(gCurFileName) || !strlen(gCurFileName))
                {
                /* some error, or user just hit RETURN */
                strcpy(gCurFileName, gOutFileDefault);
                }
                
            /* create the file: */
            fd = open(gCurFileName, O_RDWR|O_CREAT|O_TRUNC|O_BINARY, S_IREAD|S_IWRITE);
            if (fd >= 0)
                {/* created OK */
                fprintf(stderr,"\nWriting %s...", gCurFileName);
                toWrite = (size_t)nFonts * (size_t)sizeof(FontInfoType);
                Ok = (write(fd, gFontInfoTable, toWrite) == toWrite);
                if (Ok)
                    fprintf(stderr,"Written Ok...");
                else
                    fprintf(stderr,"Failed write...");
                Ok = (!close(fd));
                if (Ok)
                    fprintf(stderr,"Closed Ok.");
                else
                    fprintf(stderr,"Failed closing.");
                }
            else
                {/* failed creating file */
                fprintf(stderr, "Unable to create %s.", gCurFileName);
                Ok = FALSE;
                }
            }
        }
    exit(Ok ? 0 : 1);    /* exit 0 on success, 1 on error */
}

/************************************************************************
    The menu subroutine
    Display the menu, get input strings, verify input,
    and return the ItemRet code for the choice made.
************************************************************************/
#if PROTOS_AVAIL
int MenuSelect(MenuTypePtr aMenu, int nItems)
#else
int MenuSelect(aMenu, nItems)
MenuTypePtr aMenu;
int nItems;
#endif
{
int i, theIdx, theChoice, Ok = TRUE;
char done, aStrBuf[128];

    theIdx = 0;
    done = FALSE;
    while (!done)
        {
        /* display menu items: */
        for (i = 0; i < nItems; i++)
            fprintf(stderr,"\n%s", aMenu[i].ItemStr);
        fprintf(stderr,"\n");

        /* set up for string edit: */
        memset(aStrBuf, 0, sizeof(aStrBuf));
        if (gets(aStrBuf) && strlen(aStrBuf))
            {
            theIdx =  atoi(aStrBuf);    /* see what integer was typed */
            Ok = ((theIdx >= 1) && (theIdx <= nItems));
            if (Ok)
                done = TRUE;    /* got a good one, we're finished! */
            theIdx--;
            }
        else
            {
            Ok = FALSE;
            done = TRUE;    /* empty string, or some error, we're done */
            }
        }
    theChoice = aMenu[theIdx].ItemRet;
    /* if all is well, return the ItemRet indicated by theChoice: */
    /* if not, pretend user chose quit: */
    return(Ok ? theChoice : NO_ITEM_SEL);
}

/************************************************************************
    Central processor for "Add" routines
    "Adds" (copies) data elements to gFontInfoTable, based on the menu 
    choice (one of ITEM_LJIII - ITEM_MAXITEMS-1)
************************************************************************/
#if PROTOS_AVAIL
int PrepareFontOutPut(int choice)
#else
int PrepareFontOutPut(choice)
int choice;
#endif
{
int nFonts;
    gCurFontIdx = 0;
    nFonts = 0;
    switch(choice)
        {
        case ITEM_LJIII:
            nFonts += AddSupportSet();
            nFonts += AddCore(8);
            break;
        case ITEM_LJIIISI:
            nFonts += AddSupportSet();
            nFonts += AddCore(13);
            break;
        case ITEM_HPCART1:
            nFonts += AddCart1();
            break;
        case ITEM_HPCART2:
            nFonts += AddCart2();
            break;
        case ITEM_HPCART3:
            nFonts += AddCart1();
            nFonts += AddCart2();
            break;
        case ITEM_LJIV:
            nFonts += AddSupportSet();
            nFonts += AddCore(12);
            nFonts += AddAntiqueOlive(3);
            nFonts += AddOmega();
            nFonts += AddGaramond();
            nFonts += AddPCL60toPCL71();
            nFonts += AddTrueType(8);
            nFonts += AddTrueTypeSymDings();
            break;
        case ITEM_TRUETYPE14:
            nFonts += AddTrueType(14);
            break;
        case ITEM_POSTSCRIPT13:
            nFonts += AddPostScript(13);
            break;
        case ITEM_POSTSCRIPT35:
            nFonts += AddPostScript(35);
            break;
        case ITEM_POSTSCRIPT13andTRUETYPE14:
            nFonts += AddPostScript(13);
            nFonts += AddTrueType(14);
            break;
        case ITEM_POSTSCRIPT35andTRUETYPE14:
            nFonts += AddPostScript(35);
            nFonts += AddTrueType(14);
            break;
        default:
            nFonts = 0;
            break;
        }
    return(nFonts);
}

/*--------------------------------------------------------------------------
                the "Add" routines - 
    copy data from gSrcFontInfoTable to gFontInfoTable, bumping gCurFontIdx 
--------------------------------------------------------------------------*/
#ifdef HAVE_STICK_FONT
#define N_SUPPORT_FONTS    6
#else
#define N_SUPPORT_FONTS    5
#endif

/******* Add Support/Aux Fonts *******/
int AddSupportSet()
{
int i, base, nFonts = N_SUPPORT_FONTS;

    base = 0;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add Core Fonts *******/
#if PROTOS_AVAIL
int AddCore(int howMany)
#else
int AddCore(howMany)
int howMany;
#endif
{
int i, base, nFonts = howMany;
    base = N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add Cartridge 1 Fonts *******/
int AddCart1()
{
int i, base, nFonts = 25;
    base = 8+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add Cartridge 2 Fonts *******/
int AddCart2()
{
int i, base, nFonts = 26;
    base = 33+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add Cartridge 3 (1+2) Fonts *******/
#if PROTOS_AVAIL
int AddAntiqueOlive(int nFonts)
#else
int AddAntiqueOlive(nFonts)
int nFonts;
#endif
{
int i, base;
    base = 21+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add CG Omega Fonts *******/
int AddOmega()
{
int i, base, nFonts = 4;
    base = 33+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add Garamond Fonts *******/
int AddGaramond()
{
int i, base, nFonts = 4;
    base = 49+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add PCL Fonts 60-71 *******/
int AddPCL60toPCL71()
{
int i, base, nFonts = 12;
    base = 59+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add TrueType Fonts 1-?? *******/
#if PROTOS_AVAIL
int AddTrueType(int howMany)
#else
int AddTrueType(howMany)
int howMany;
#endif
{
int i, base, nFonts = howMany;
    base = 106+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add TrueType Fonts13 and 14  *******/
int AddTrueTypeSymDings()
{
int i, base, nFonts = 2;
    base = 118+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/******* Add PostScript Fonts 1-?? *******/
#if PROTOS_AVAIL
int AddPostScript(int howMany)
#else
int AddPostScript(howMany)
int howMany;
#endif
{
int i, base, nFonts = howMany;
    base = 71+N_SUPPORT_FONTS;
    for (i = 0; i < nFonts; i++)
        gFontInfoTable[gCurFontIdx++] = gSrcFontInfoTable[i+base];
    return(nFonts);
}

/* eof finfotbl.c */
