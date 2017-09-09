/* pshdr.c
 * Input file:  ps-header.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "pshdr.h"


Object Postscript_paper_sizes = UNBOUND;

void ps_header_INIT()
{
    Object svref_arg_1;
    Object list_constant_35, list_constant_34, list_constant_33;
    Object list_constant_32, list_constant_31, list_constant_30;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_23, list_constant_22, list_constant_21;
    Object list_constant_20, list_constant_18, list_constant_19, Qb5;
    Object list_constant_5, AB_package, list_constant_17, Qb4;
    Object list_constant_16, Qb3, list_constant_15, Qb2, list_constant_13, Qb1;
    Object list_constant_14, Qb0, list_constant_11, list_constant_12, Qa5;
    Object list_constant_10, Qa4, list_constant_9, Qa3, list_constant_8, Qa2;
    Object list_constant_6, Qa1, list_constant_7, Qa0, Qmm, list_constant_4;
    Object list_constant_2, Qledger, list_constant, float_constant_3;
    Object list_constant_3, list_constant_1, Qlegal, float_constant_2, Qletter;
    Object float_constant_1, float_constant, Qinch, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, string_constant_8;
    Object string_constant_7, string_constant_6, string_constant_5;
    Object string_constant_4, string_constant_3, string_constant_2;
    Object string_constant_1, string_constant;

    x_note_fn_call(95,0);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("/A{exchB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = string_constant;
    string_constant_1 = STATIC_STRING("/inch{/inchesAinches 72L}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)1L)) = string_constant_1;
    string_constant_2 = STATIC_STRING("/max{/_bA/_aA_a _b gt{_a}{_b}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)2L)) = string_constant_2;
    string_constant_3 = STATIC_STRING("/min{/_bA/_aA_a _b gt{_b}{_a}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant_3;
    string_constant_4 = 
	    STATIC_STRING("/clip-to-rectangle{/OA/TA/_topA/PAnewpathP_topQT_topITOIPOI\nclosepath clip newpath}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)4L)) = string_constant_4;
    string_constant_5 = 
	    STATIC_STRING("/show-with-wordspacing{/$eiA$da 256 div\nwidth-of-space-character sub 0 32 $ei widthshow}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)5L)) = string_constant_5;
    string_constant_6 = STATIC_STRING("/$bq matrix currentmatrixB");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)6L)) = string_constant_6;
    string_constant_7 = STATIC_STRING("/$bp matrixB");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)7L)) = string_constant_7;
    string_constant_8 = STATIC_STRING("/savectm{$bp currentmatrix pop}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)8L)) = string_constant_8;
    string_constant_9 = STATIC_STRING("/restorectm{$bp setmatrix}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)9L)) = string_constant_9;
    string_constant_10 = STATIC_STRING("/$eg matrixB");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)10L)) = string_constant_10;
    string_constant_11 = 
	    STATIC_STRING("/$bx{$eg currentmatrix pop $bq setmatrix stroke $eg\nsetmatrix}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)11L)) = string_constant_11;
    string_constant_12 = string_appendn(4,
	    STATIC_STRING("/bitmap-buildchar{/charA/fontdictA/charname fontdict/@Encoding\nget char getB/charinfo fontdict/@Char@Data get charname get\nB/wx charinfo 0 getB/imm fontdict/imagemaskmatrix ge"),
	    STATIC_STRING("tB/resolution\nimm 0 getB/bits-wide charinfo 1 getB/bits-high charinfo 2\ngetB/x-imm-offset charinfo 3 getB/y-imm-offset charinfo 4\ngetBwx resolution div 0 x-imm-offset resoluti"),
	    STATIC_STRING("on div neg\ny-imm-offset resolution div neg x-imm-offset bits-wide add\nresolution div bits-high resolution div setcachedevice imm 4\nx-imm-offset put imm 5 y-imm-offset put bits"),
	    STATIC_STRING("-wide bits-high\ntrue imm charinfo 5 1 getinterval cvx imagemask}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)12L)) = string_constant_12;
    string_constant_13 = string_appendn(3,
	    STATIC_STRING("/setup-blob-font{/blob-font 11 dictBblob-font begin/@Font@Type\n3B/@Font@Matrix[1 0 0 1 0 0]B/@Encoding @Standard@Encoding\n@Standard@Encoding length array copyB0 1 255{@Encodin"),
	    STATIC_STRING("g exch\n/.notdef put}for/@Build@Char/bitmap-buildchar loadB/imagemaskmatrix\n[16 0 0 -16 0 0]B/@Font@B@Box[-2 -2 20 20]B/@Char@Data 25\ndictB@Char@Data begin/X[15 12 12 0 12<ffff"),
	    STATIC_STRING(" ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff>]Bend end/blob-font\nblob-font definefont pop}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)13L)) = string_constant_13;
    string_constant_14 = 
	    STATIC_STRING("/begin-kanji-font{/kanji-font-vector-nameA/current-kanji-font-vector\n100 arrayBkanji-font-vector-name current-kanji-font-vectorB\n}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)14L)) = string_constant_14;
    string_constant_15 = 
	    STATIC_STRING("/end-kanji-font{/kanji-font-vector-nameA}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)15L)) = string_constant_15;
    string_constant_16 = string_appendn(3,
	    STATIC_STRING("/begin-kanji-microfont{/microfont-numberA/kanji-microfont-name\nA/current-microfont 25 dictBkanji-microfont-name\ncurrent-microfontBcurrent-microfont begin/@Font@Type 3B/@Font@M"),
	    STATIC_STRING("atrix\n[1 0 0 1 0 0]B/@Encoding microfont-encoding-vectorB/@Build@Char\n/bitmap-buildchar loadB/imagemaskmatrix[16 0 0 -16 0 0]B/@Font@B@Box\n[-2 -2 20 20]B/@Char@Data 256 dictB}"),
	    STATIC_STRING("B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)16L)) = string_constant_16;
    string_constant_17 = 
	    string_append2(STATIC_STRING("/end-kanji-microfont{/microfont-numberA/kanji-microfont-name\nAkanji-microfont-name microfont-number end/microfont-number\nA/kanji-microfont-nameAcurrent-kanji-font-vector\nmicro"),
	    STATIC_STRING("font-number kanji-microfont-name current-microfont\ndefinefont put}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)17L)) = string_constant_17;
    string_constant_18 = 
	    string_append2(STATIC_STRING("/def-kanji-character{/bitsA/bits-y-offsetA/bits-x-offsetA/bit-height\nA/bit-widthA/widthA/character-nameA@Char@Data begin\ncharacter-name [ width bit-width bit-height bits-x-off"),
	    STATIC_STRING("set\nbits-y-offset bits ]Bend}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)18L)) = string_constant_18;
    string_constant_19 = 
	    STATIC_STRING("/def-unknown-kanji-character{/character-nameAcharacter-name\n[15 12 12 0 12<ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff ffff>]B}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)19L)) = string_constant_19;
    string_constant_20 = string_appendn(3,
	    STATIC_STRING("/def-kanji-correspondence{/magnificationA/sizeA/kanji-font-vector-name\nA/fontA/scale-factor 16 magnification 256 divLB/kanji-font-vector\nkanji-dictionary kanji-font-vector-nam"),
	    STATIC_STRING("e getB/new-font-vector\nkanji-font-vector length arrayB0 1 kanji-font-vector length\n1 sub{/iA/microfont kanji-font-vector i getBnull microfont\neq{exit}if new-font-vector i micr"),
	    STATIC_STRING("ofont scale-factorVput}for\ncorresponding-kanji-font font new-font-vector put}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)20L)) = string_constant_20;
    string_constant_21 = string_appendn(3,
	    STATIC_STRING("/kanji-show{/kanji-text-lineA{kanji-text-line (\\033) search\n{show-with-wordspacing pop/kanji-text-lineA/microfont-number\nkanji-text-line 0 getB/kanji-bit kanji-text-line 1 1\ng"),
	    STATIC_STRING("etintervalB/kanji-text-line kanji-text-line 2\nkanji-text-line length 2 sub getintervalB\ncurrent-corresponding-kanji-font-vector microfont-number get\nsetfont kanji-bit show cur"),
	    STATIC_STRING("rent-primary-font setfont}{\nshow-with-wordspacing exit}ifelse}loop}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)21L)) = string_constant_21;
    string_constant_22 = 
	    STATIC_STRING("/set-corresponding-kanji-font{/font-nameA/current-corresponding-kanji-font-vector\ncorresponding-kanji-font font-name getB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)22L)) = string_constant_22;
    string_constant_23 = 
	    STATIC_STRING("/set-appropriate-font{/current-primary-font $by 0 get cvx\nexecBcurrent-primary-font setfont/width-of-space-character\n( )stringwidth popB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)23L)) = string_constant_23;
    string_constant_24 = 
	    STATIC_STRING("/$be{/$boA/$esA/$euA/$dyA/$epA/$ckA/$eoA/$cjA/$czA}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)24L)) = string_constant_24;
    string_constant_25 = STATIC_STRING("/$en{/NA/number-of-rasters-neededA}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)25L)) = string_constant_25;
    string_constant_26 = string_appendn(11,
	    STATIC_STRING("/g2-encoding[/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef"),
	    STATIC_STRING("/.notdef/.notdef\n/.notdef/.notdef/breve/caron/circumflex/dotaccent/hungarumlaut\n/ogonek/ring/tilde/space/exclam/quotedbl/numbersign/dollar/percent\n/ampersand/quotesingle/paren"),
	    STATIC_STRING("left/parenright/asterisk/plus/comma\n/hyphen/period/slash/zero/one/two/three/four/five/six/seven\n/eight/nine/colon/semicolon/less/equal/greater/question/at/@A\n/@B/@C/@D/@E/@F/@"),
	    STATIC_STRING("G/@H/@I/@J/@K/@L/@M/@N/@O/@P/@Q/@R/@S/@T/@U\n/@V/@W/@X/@Y/@Z/bracketleft/backslash/bracketright/asciicircum\n/underscore/grave/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u\n/v/w/x/y"),
	    STATIC_STRING("/z/braceleft/bar/braceright/asciitilde/.notdef/bullet\n/dagger/daggerdbl/ellipsis/emdash/endash/florin/fraction/guilsinglleft\n/guilsinglright/minus/perthousand/quotedblbase/quo"),
	    STATIC_STRING("tedblleft\n/quotedblright/quoteleft/quoteright/quotesinglbase/trademark\n/fi/fl/@Lslash/@O@E/@Scaron/@Ydieresis/@Zcaron/dotlessi/lslash\n/oe/scaron/zcaron/.notdef/.notdef/exclamd"),
	    STATIC_STRING("own/cent/sterling/currency\n/yen/brokenbar/section/dieresis/copyright/ordfeminine/guillemotleft\n/logicalnot/.notdef/registered/macron/degree/plusminus/twosuperior\n/threesuperio"),
	    STATIC_STRING("r/acute/mu/paragraph/periodcentered/cedilla/onesuperior\n/ordmasculine/guillemotright/onequarter/onehalf/threequarters\n/questiondown/@Agrave/@Aacute/@Acircumflex/@Atilde/@Adier"),
	    STATIC_STRING("esis\n/@Aring/@A@E/@Ccedilla/@Egrave/@Eacute/@Ecircumflex/@Edieresis\n/@Igrave/@Iacute/@Icircumflex/@Idieresis/@Eth/@Ntilde/@Ograve\n/@Oacute/@Ocircumflex/@Otilde/@Odieresis/mult"),
	    STATIC_STRING("iply/@Oslash/@Ugrave\n/@Uacute/@Ucircumflex/@Udieresis/@Yacute/@Thorn/germandbls/agrave\n/aacute/acircumflex/atilde/adieresis/aring/ae/ccedilla/egrave\n/eacute/ecircumflex/ediere"),
	    STATIC_STRING("sis/igrave/iacute/icircumflex/idieresis\n/eth/ntilde/ograve/oacute/ocircumflex/otilde/odieresis/divide\n/oslash/ugrave/uacute/ucircumflex/udieresis/yacute/thorn/ydieresis\n]B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)26L)) = string_constant_26;
    string_constant_27 = string_appendn(4,
	    STATIC_STRING("/reencode-font{/metricsA/base-font-nameA/new-font-nameA/base-font-dictionary\nbase-font-name findfontB/new-font-dictionary 1\nbase-font-dictionary maxlength add dictB/new-encodi"),
	    STATIC_STRING("ng 256\narrayB/new-metrics 256 dictBbase-font-dictionary {1 index/@F@I@D\neq 2 index/@Unique@I@D eq or {pop pop} {new-font-dictionary\n3 1 roll put}ifelse}forall new-font-diction"),
	    STATIC_STRING("ary/@Font@Name\nnew-font-name put base-font-dictionary/@Encoding get\nnew-encoding copy pop new-encoding 0 g2-encoding putinterval\nnew-font-dictionary/@Encoding new-encoding put"),
	    STATIC_STRING("\nnew-font-dictionary/@Metrics new-metrics put 0 1 255{/iA\nnew-metrics new-encoding i get metrics i get put}for\nnew-font-name new-font-dictionary definefont pop}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)27L)) = string_constant_27;
    string_constant_28 = 
	    STATIC_STRING("/define-g2-font{/base-fontA/metricsA/sizeA/nameAname\nbase-font metrics reencode-font name name findfont sizeVB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)28L)) = string_constant_28;
    string_constant_29 = 
	    STATIC_STRING("/$bs{/metricsA/sizeA/nameAname size metrics/@Helvetica\ndefine-g2-font}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)29L)) = string_constant_29;
    string_constant_30 = 
	    STATIC_STRING("/$br{/sizeA/nameAname/blob-font findfont sizeVB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)30L)) = string_constant_30;
    string_constant_31 = 
	    STATIC_STRING("/$bu{/sizeA/nameAname/@Courier-@Bold@Oblique findfont sizeV\nB}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)31L)) = string_constant_31;
    string_constant_32 = STATIC_STRING("/bw-color-map[[255 255 255][0 0 0]]B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)32L)) = string_constant_32;
    string_constant_33 = 
	    STATIC_STRING("/C{D0 lt{0.5 setgray}{Dcurrent-color-map length ge{0.5\nsetgray}{current-color-mapDget aload/arrayA/_bA/_gA/_rA_r _g\n_b setrgbcolor}ifelse}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)33L)) = string_constant_33;
    string_constant_34 = 
	    string_append2(STATIC_STRING("/set-up-color-map{/current-color-map/black-and-white\nglobal-color-conversion eq{bw-color-map}{/grays\nglobal-color-conversion eq{gray-color-map}{full-color-map}\nifelse}ifelseBc"),
	    STATIC_STRING("urrent-color-map{/WAW0W0 get 255 div putW1W1\nget 255 div putW2W2 get 255 div put}forall}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)34L)) = string_constant_34;
    string_constant_35 = 
	    STATIC_STRING("/$bw{/indexAindex 0 lt{D}{index $cx length ge{D}{$cx index\nget}ifelse}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)35L)) = string_constant_35;
    string_constant_36 = 
	    STATIC_STRING("/Y{/$hA/DA/_y2A/_x2A/_y1A/WAD-1 eq{}{CW_x2 eq{/WW0.5 addB/_x2\n_x2 0.5 addB}{_y1 _y2 eq{/_y1 _y1 0.5 addB/_y2 _y2 0.5 addB\n}if}ifelseW_y1Q_x2 _y2Istroke}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)36L)) = string_constant_36;
    string_constant_37 = 
	    STATIC_STRING("/$dk{/DA/OA/TA/_topA/PAD-1 eq{}{CnewpathP_topQT_topITOIPOIP\n_topIfill}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)37L)) = string_constant_37;
    string_constant_38 = 
	    STATIC_STRING("/$dd{/$bcA/MA/$etA/$erA/DA/$byA/$daA/$eiA/JA/KA/HA/GAD-1 eq\n{}{CgsaveG$bcS0 0Q1.0 -1.0 scale set-appropriate-font $ei\nshow-with-wordspacing grestore}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)38L)) = string_constant_38;
    string_constant_39 = 
	    string_append2(STATIC_STRING("/$cq{/$bcA/MA/$etA/$erA/DA/$byA/$daA/$eiA/JA/KA/HA/GAD-1 eq\n{}{CgsaveG$bcS0 0Q1.0 -1.0 scale set-appropriate-font $by 0\nget set-corresponding-kanji-font $ei kanji-show grestor"),
	    STATIC_STRING("e}\nifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)39L)) = string_constant_39;
    string_constant_40 = 
	    STATIC_STRING("/$dc{/DA/_y3A/_x3A/_y2A/_x2A/_y1A/WAD-1 eq{}{CnewpathW_y1Q\n_x2 _y2I_x3 _y3Ifill}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)40L)) = string_constant_40;
    string_constant_41 = 
	    STATIC_STRING("/paint-filled-polygon-in-current-scratchpad-raster{/DA/unsigned-polygon-point-list\nA}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)41L)) = string_constant_41;
    string_constant_42 = 
	    STATIC_STRING("/$dj{/DA/_y1A/WAD-1 eq{}{CnewpathW_y1Q0 1 rlineto 1 0\nrlineto 0 -1 rlineto fill}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)42L)) = string_constant_42;
    string_constant_43 = 
	    string_append2(STATIC_STRING("/$dm{/$cwA/$dgA/DA/_y2A/_x2A/_y1A/WAD-1 eq{}{CnewpathW_x2 eq\n{/WW0.5 addB/_x2 _x2 0.5 addB}{_y1 _y2 eq{/_y1 _y1 0.5 addB\n/_y2 _y2 0.5 addB}if}ifelseW_y1Q_x2 _y2I$cw setlinewid"),
	    STATIC_STRING("th\nstroke 1 setlinewidth}ifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)43L)) = string_constant_43;
    string_constant_44 = 
	    STATIC_STRING("/$bb{/$eA/$cA/$dA/$bA$e $d sub $c $b sub atan}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)44L)) = string_constant_44;
    string_constant_45 = string_appendn(5,
	    STATIC_STRING("/$db{/_filled\?A/_circle\?A/DA/$rA/$pA/_y3A/_x3A/_y2A/_x2A/_y1\nA/WAD-1 eq{}{C/_filled\? 1 _filled\? eqB/_circle\? 1 _circle\?\neqB/_a1 _x2WsubB/_b1 _y2 _y1 subB/_a2 _x3 _x2 subB/_b2 "),
	    STATIC_STRING("_y3\n_y2 subB/_c1 _x2 _x2L_y2 _y2LaddWWL_y1 _y1Ladd sub 2.0 divB\n/_c2 _x3 _x3L_y3 _y3Ladd _x2 _x2L_y2 _y2Ladd sub 2.0 divB/_determinant\n_a1 _b2L_a2 _b1LsubBnewpathW_y1Q0 _deter"),
	    STATIC_STRING("minant eq{W_y1 _x3\n_y3D1Y}{/F_c1 _b2L_c2 _b1Lsub _determinant divB/E_a1 _c2L\n_a2 _c1Lsub _determinant divB/_d1WFsubB/_d2 _y1EsubB/_radius\n_d1 _d1L_d2 _d2Ladd sqrtB/_angle1FEW_"),
	    STATIC_STRING("y1 $bbB/_angle2\n_circle\?{360 _angle1 add}{FE_x3 _y3 $bb}ifelseB_determinant\n0 lt{FE_radius _circle\?{_angle2}{_angle1}ifelse _circle\?{\n_angle1}{_angle2}ifelse arcn}{FE_radius _"),
	    STATIC_STRING("angle1 _angle2 arc\n}ifelse _circle\?{closepath}if _filled\?{fill}{stroke}ifelse}\nifelse}ifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)45L)) = string_constant_45;
    string_constant_46 = 
	    string_append2(STATIC_STRING("/$ed{/$gA/_reflectionA/$rA/$pA/_heightA/_widthA/_dx _width 2\ndivB/_dy _height 2 divB$p 4096 div $r 4096 div scale _dx _dy\n$g matrix rotate transform exch abs exch absS1 _refle"),
	    STATIC_STRING("ction\neq{-1 1 scale}if $g rotate _dx neg _dy negS}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)46L)) = string_constant_46;
    string_constant_47 = 
	    STATIC_STRING("/$dl{/DA/OA/TA/_topA/PAD-1 eq{}{CnewpathP_topQT_topITOIPOIP\n_topIfill}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)47L)) = string_constant_47;
    string_constant_48 = 
	    STATIC_STRING("/paint-image-in-current-window{/$etA/$erA/JA/KA/HA/GA/_yA/_x\nAgsave savectmGHKJclip-to-rectangle $er 4096 div $et 4096\ndiv scale _x _ySimage restorectm grestore}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)48L)) = string_constant_48;
    string_constant_49 = string_appendn(3,
	    STATIC_STRING("/$df{/image-dataA/DA/$etA/$erA/_image-heightA/_image-widthA\n/icon-heightA/icon-widthA/y-in-iconA/x-in-iconAD-1 eq{}{\ngsaveC0 0 icon-width icon-height clip-to-rectangle x-in-ic"),
	    STATIC_STRING("on\ny-in-iconS_image-width $er 4096 divL_image-height $et 4096\ndivLscale _image-width _image-height true [ _image-width 0 0\n_image-height 0 0 ] image-data imagemask grestore}if"),
	    STATIC_STRING("else}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)49L)) = string_constant_49;
    string_constant_50 = 
	    STATIC_STRING("/$u{/$cxA/$ekA/$csA/$clA/DA/JA/KA/HA/GAgsaveCsavectmGHKJ\nclip-to-rectangleG$cs subH$ek subS$cl cvx exec restorectm\ngrestore}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)50L)) = string_constant_50;
    string_constant_51 = 
	    STATIC_STRING("/U{/$bnA/DA/$ejA/$crA/NA/$ciA/JA/KA/HA/GAgsaveGHKJ\nclip-to-rectangleG$cr subH$ej subSNcvx exec grestore}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)51L)) = string_constant_51;
    string_constant_52 = STATIC_STRING("/graph-erase-dateline 0B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)52L)) = string_constant_52;
    string_constant_53 = 
	    STATIC_STRING("/$em{/graph-erase-datelineA/datelineAgraph-erase-dateline\nneg 0S}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)53L)) = string_constant_53;
    string_constant_54 = 
	    STATIC_STRING("/cleanup-after-graph-rendering{graph-erase-dateline 0S}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)54L)) = string_constant_54;
    string_constant_55 = 
	    STATIC_STRING("/$w{/DA/OA/TA/_topA/PAD-1 eq{}{CnewpathP_topQT_topITOIPOIP\n_topIfill}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)55L)) = string_constant_55;
    string_constant_56 = 
	    STATIC_STRING("/$v{/$bcA/MA/$etA/$erA/DA/$byA/$daA/$eiA/OA/TA/_topA/PAD-1\neq{}{CgsaveM$bcS0 0Q$er $et scale set-appropriate-font $ei\nshow-with-wordspacing grestore}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)56L)) = string_constant_56;
    string_constant_57 = 
	    string_append2(STATIC_STRING("/$cp{/$bcA/MA/$etA/$erA/DA/$byA/$daA/$eiA/OA/TA/_topA/PAD-1\neq{}{CgsaveM$bcS0 0Q$er $et scale set-appropriate-font $by 0\nget set-corresponding-kanji-font $ei kanji-show gresto"),
	    STATIC_STRING("re}\nifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)57L)) = string_constant_57;
    string_constant_58 = 
	    STATIC_STRING("/$x{/$cvA/$eaA/$ebA/$cuA/DAD-1 eq{}{C$cu $cvQ$ea $ebIstroke\n}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)58L)) = string_constant_58;
    string_constant_59 = 
	    STATIC_STRING("/$s{/$cvA/$cuA/$ebA/$eaA/DAD-1 eq{}{C$cu $cvQ$ea $ebIstroke\n}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)59L)) = string_constant_59;
    string_constant_60 = 
	    string_append2(STATIC_STRING("/$y{/verticesA/dashesA/line-joinA/line-capA/$cwA/DAD-1 eq{}\n{gsave 0 2 vertices length 1 sub{/iAi 0 eq{vertices i get\nvertices i 1 add getQ}{vertices i get vertices i 1 add ge"),
	    STATIC_STRING("tI\n}ifelse}forC$cw setlinewidth line-cap setlinecap line-join\nsetlinejoin dashes 0 setdash stroke grestore}ifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)60L)) = string_constant_60;
    string_constant_61 = 
	    string_append2(STATIC_STRING("/$z{/verticesA/fill-patternA/fill-colorA/$cwA/DAD-1 eq{}{\ngsave 0 2 vertices length 1 sub{/iAi 0 eq{vertices i get\nvertices i 1 add getQ}{vertices i get vertices i 1 add getI\n"),
	    STATIC_STRING("}ifelse}forC$cw setlinewidth stroke grestore}ifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)61L)) = string_constant_61;
    string_constant_62 = 
	    STATIC_STRING("/$ba{/y2A/x2A/y1A/x1A/fill-patternA/fill-colorA/$cwA/DAD-1\neq{}{gsaveC$cw setlinewidth stroke grestore}ifelse}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)62L)) = string_constant_62;
    string_constant_63 = 
	    STATIC_STRING("/define-paper-1{/$dnA/$dqA/$drA/$dpA/$doA/$dsA}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)63L)) = string_constant_63;
    string_constant_64 = string_appendn(3,
	    STATIC_STRING("/$bt{/paper-bottom-margin-1A/paper-right-margin-1A/paper-top-margin-1\nA/paper-left-margin-1A/paper-height-1A/paper-width-1A/$cdA/$ce\nA/portrait $cd eq{paper-width-1 paper-heig"),
	    STATIC_STRING("ht-1\npaper-left-margin-1 paper-top-margin-1 paper-right-margin-1\npaper-bottom-margin-1 define-paper-1}{paper-height-1\npaper-width-1 paper-top-margin-1 paper-right-margin-1\npap"),
	    STATIC_STRING("er-bottom-margin-1 paper-left-margin-1 define-paper-1}\nifelse}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)64L)) = string_constant_64;
    string_constant_65 = 
	    string_append2(STATIC_STRING("/$cb{/global-color-conversionA/$caA/$cfA/$cgA/$ccA/postscript-units-per-workspace-unit\nAset-up-color-map/$dw $cf $dq maxB/$dx $cg $dr maxB/$dv $cc\n$dp maxB/$du $ca $dn maxB/$c"),
	    STATIC_STRING("m $do $dx $du add subB/$cn $ds\n$dw $dv add subB}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)65L)) = string_constant_65;
    string_constant_66 = 
	    STATIC_STRING("/set-up-page{/landscape $cd eq{0 $dsS-90 rotate}if}B");
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)66L)) = string_constant_66;
    string_constant_67 = 
	    string_append2(STATIC_STRING("/$ee{/_tile-heightA/_tile-widthA/_tile-topA/_tile-leftA$dv\n$duS0.0 $cmSpostscript-units-per-workspace-unit\npostscript-units-per-workspace-unit neg scale 0 0\n_tile-width _tile-"),
	    STATIC_STRING("height clip-to-rectangle}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)67L)) = string_constant_67;
    string_constant_68 = string_appendn(3,
	    STATIC_STRING("/draw-multipage-legend{/pageA/columnsA/rowsA/extra-space 5B\n/yspace $du $dn sub extra-space sub rows divB/yscale yspace\n72 4 div minB/xscale yscale $ds $do divLB/i 1Byscale 0."),
	    STATIC_STRING("01\ninch gt{gsave $dp extra-space 2 div add $dn extra-space 2\ndiv addSxscale yscale scale 0 setlinewidth rows 1 sub -1 0{\n/yA0 1 columns 1 sub{/xAnewpath x yQ1 0 rlineto 0 1 rl"),
	    STATIC_STRING("ineto\n-1 0 rlineto closepath i page eq{gsave 0.75 setgray fill\ngrestore}if stroke/i 1 i addB}for}for grestore}if}B"));
    svref_arg_1 = Postscript_header_array;
    SVREF(svref_arg_1,FIX((SI_Long)68L)) = string_constant_68;
    AB_package = STATIC_PACKAGE("AB");
    Qletter = STATIC_SYMBOL("LETTER",AB_package);
    float_constant = STATIC_FLOAT(8.5);
    Qinch = STATIC_SYMBOL("INCH",AB_package);
    list_constant = STATIC_CONS(Qinch,Qnil);
    list_constant_1 = STATIC_CONS(float_constant,list_constant);
    float_constant_1 = STATIC_FLOAT(11.0);
    list_constant_2 = STATIC_CONS(float_constant_1,list_constant);
    list_constant_20 = STATIC_LIST((SI_Long)3L,Qletter,list_constant_1,
	    list_constant_2);
    Qlegal = STATIC_SYMBOL("LEGAL",AB_package);
    float_constant_2 = STATIC_FLOAT(14.0);
    list_constant_3 = STATIC_CONS(float_constant_2,list_constant);
    list_constant_21 = STATIC_LIST((SI_Long)3L,Qlegal,list_constant_1,
	    list_constant_3);
    Qledger = STATIC_SYMBOL("LEDGER",AB_package);
    float_constant_3 = STATIC_FLOAT(17.0);
    list_constant_4 = STATIC_CONS(float_constant_3,list_constant);
    list_constant_22 = STATIC_LIST((SI_Long)3L,Qledger,list_constant_2,
	    list_constant_4);
    Qa0 = STATIC_SYMBOL("A0",AB_package);
    Qmm = STATIC_SYMBOL("MM",AB_package);
    list_constant_5 = STATIC_CONS(Qmm,Qnil);
    list_constant_6 = STATIC_CONS(FIX((SI_Long)841L),list_constant_5);
    list_constant_7 = STATIC_CONS(FIX((SI_Long)1189L),list_constant_5);
    list_constant_23 = STATIC_LIST((SI_Long)3L,Qa0,list_constant_6,
	    list_constant_7);
    Qa1 = STATIC_SYMBOL("A1",AB_package);
    list_constant_8 = STATIC_CONS(FIX((SI_Long)594L),list_constant_5);
    list_constant_24 = STATIC_LIST((SI_Long)3L,Qa1,list_constant_8,
	    list_constant_6);
    Qa2 = STATIC_SYMBOL("A2",AB_package);
    list_constant_9 = STATIC_CONS(FIX((SI_Long)420L),list_constant_5);
    list_constant_25 = STATIC_LIST((SI_Long)3L,Qa2,list_constant_9,
	    list_constant_8);
    Qa3 = STATIC_SYMBOL("A3",AB_package);
    list_constant_10 = STATIC_CONS(FIX((SI_Long)297L),list_constant_5);
    list_constant_26 = STATIC_LIST((SI_Long)3L,Qa3,list_constant_10,
	    list_constant_9);
    Qa4 = STATIC_SYMBOL("A4",AB_package);
    list_constant_11 = STATIC_CONS(FIX((SI_Long)210L),list_constant_5);
    list_constant_27 = STATIC_LIST((SI_Long)3L,Qa4,list_constant_11,
	    list_constant_10);
    Qa5 = STATIC_SYMBOL("A5",AB_package);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)148L),list_constant_5);
    list_constant_28 = STATIC_LIST((SI_Long)3L,Qa5,list_constant_12,
	    list_constant_11);
    Qb0 = STATIC_SYMBOL("B0",AB_package);
    list_constant_13 = STATIC_CONS(FIX((SI_Long)1000L),list_constant_5);
    list_constant_14 = STATIC_CONS(FIX((SI_Long)1414L),list_constant_5);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qb0,list_constant_13,
	    list_constant_14);
    Qb1 = STATIC_SYMBOL("B1",AB_package);
    list_constant_15 = STATIC_CONS(FIX((SI_Long)707L),list_constant_5);
    list_constant_30 = STATIC_LIST((SI_Long)3L,Qb1,list_constant_15,
	    list_constant_13);
    Qb2 = STATIC_SYMBOL("B2",AB_package);
    list_constant_16 = STATIC_CONS(FIX((SI_Long)500L),list_constant_5);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qb2,list_constant_16,
	    list_constant_15);
    Qb3 = STATIC_SYMBOL("B3",AB_package);
    list_constant_17 = STATIC_CONS(FIX((SI_Long)353L),list_constant_5);
    list_constant_32 = STATIC_LIST((SI_Long)3L,Qb3,list_constant_17,
	    list_constant_16);
    Qb4 = STATIC_SYMBOL("B4",AB_package);
    list_constant_18 = STATIC_CONS(FIX((SI_Long)250L),list_constant_5);
    list_constant_33 = STATIC_LIST((SI_Long)3L,Qb4,list_constant_18,
	    list_constant_17);
    Qb5 = STATIC_SYMBOL("B5",AB_package);
    list_constant_19 = STATIC_CONS(FIX((SI_Long)176L),list_constant_5);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qb5,list_constant_19,
	    list_constant_18);
    list_constant_35 = STATIC_LIST((SI_Long)15L,list_constant_20,
	    list_constant_21,list_constant_22,list_constant_23,
	    list_constant_24,list_constant_25,list_constant_26,
	    list_constant_27,list_constant_28,list_constant_29,
	    list_constant_30,list_constant_31,list_constant_32,
	    list_constant_33,list_constant_34);
    Postscript_paper_sizes = list_constant_35;
}
