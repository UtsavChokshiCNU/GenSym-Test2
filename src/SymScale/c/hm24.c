/* hm24.c
 * Input file:  hm24.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hm24.h"


void hm24_INIT()
{
    Object string_constant_271, string_constant_270, string_constant_269;
    Object string_constant_268, string_constant_267, string_constant_266;
    Object string_constant_265, string_constant_1, string_constant_264;
    Object string_constant_263, string_constant_262, string_constant_261;
    Object string_constant_260, string_constant_259, string_constant_258;
    Object string_constant_257, string_constant_256, string_constant_255;
    Object string_constant_217, string_constant_216, string_constant_254;
    Object string_constant_253, string_constant_242, string_constant_252;
    Object string_constant_251, string_constant_250, string_constant_249;
    Object string_constant_248, string_constant_247, string_constant_246;
    Object string_constant_245, string_constant_244, string_constant_243;
    Object string_constant_241, string_constant_240, string_constant_239;
    Object string_constant_238, string_constant_237, string_constant_236;
    Object string_constant_235, string_constant_234, string_constant_233;
    Object string_constant_232, string_constant_231, string_constant_230;
    Object string_constant_229, string_constant_228, string_constant_227;
    Object string_constant_226, string_constant_224, string_constant_225;
    Object string_constant_223, string_constant_221, string_constant_222;
    Object string_constant_220, string_constant_219, string_constant_218;
    Object string_constant_215, string_constant_214, string_constant_213;
    Object string_constant_212, string_constant_211, string_constant_210;
    Object string_constant_209, string_constant_208, string_constant_207;
    Object string_constant_206, string_constant_205, string_constant_204;
    Object string_constant_203, string_constant_202, string_constant_201;
    Object string_constant_200, string_constant_199, string_constant_198;
    Object string_constant_197, string_constant_196, string_constant_195;
    Object string_constant_194, string_constant_193, string_constant_192;
    Object string_constant_191, string_constant_190, string_constant_51;
    Object string_constant_189, string_constant_188, string_constant_187;
    Object string_constant_186, string_constant_185, string_constant_184;
    Object string_constant_183, string_constant_50, string_constant_182;
    Object string_constant_181, string_constant_180, string_constant_179;
    Object string_constant_178, string_constant_177, string_constant_176;
    Object string_constant_175, string_constant_174, string_constant_173;
    Object string_constant_172, string_constant_171, string_constant_170;
    Object string_constant_169, string_constant_168, string_constant_167;
    Object string_constant_166, string_constant_165, string_constant_164;
    Object string_constant_163, string_constant_162, string_constant_161;
    Object string_constant_160, string_constant_159, string_constant_158;
    Object string_constant_157, string_constant_156, string_constant_155;
    Object string_constant_154, string_constant_153, string_constant_152;
    Object string_constant_49, string_constant_151, string_constant_149;
    Object string_constant_150, string_constant_148, string_constant_147;
    Object string_constant_146, string_constant_145, string_constant_144;
    Object string_constant_143, string_constant_142, string_constant_106;
    Object string_constant_141, string_constant_140, string_constant_139;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_80;
    Object string_constant_118, string_constant_117, string_constant_116;
    Object string_constant_115, string_constant_114, string_constant_113;
    Object string_constant_112, string_constant_111, string_constant_110;
    Object string_constant_109, string_constant_108, string_constant_107;
    Object string_constant_105, string_constant_104, string_constant_103;
    Object string_constant_102, string_constant_101, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_92, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object string_constant_81, string_constant_79, string_constant_74;
    Object string_constant_78, string_constant_77, string_constant_76;
    Object string_constant_75, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;
    Object string_constant_59, string_constant_58, string_constant_57;
    Object string_constant_56, string_constant_55, string_constant_54;
    Object string_constant_53, string_constant_52, string_constant_48;
    Object string_constant_47, string_constant_46, string_constant_45;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, string_constant_40, string_constant_39;
    Object string_constant_38, string_constant_37, string_constant_36;
    Object string_constant_35, string_constant_34, string_constant_33;
    Object string_constant_32, string_constant_31, string_constant_20;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, Qabove, AB_package, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant, Qroman;
    Object Qhm24;

    x_note_fn_call(67,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhm24 = STATIC_SYMBOL("HM24",AB_package);
    Qroman = STATIC_SYMBOL("ROMAN",AB_package);
    define_ab_font(16,Qhm24,Qroman,FIX((SI_Long)24L),FIX((SI_Long)19L),
	    FIX((SI_Long)31L),FIX((SI_Long)29L),Nil,Nil,Nil,
	    FIX((SI_Long)24L),FIX((SI_Long)75L),FIX((SI_Long)75L),
	    FIX((SI_Long)28L),FIX((SI_Long)24L),FIX((SI_Long)-3L),
	    FIX((SI_Long)-5L));
    string_constant = 
	    STATIC_STRING("43Hy3AJBKy38IAKy35H6Iy36G7Jy37F8Ky38E9Gy3ACBFy3C*Fy399AFy3-9=Cy30779y3869Cy3*609y37389y3=316y36176y35063y30023y34*60y31*30y32+5*");
    string_constant_1 = STATIC_STRING("y");
    add_character_description_1(9,FIX((SI_Long)5L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)15L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(LIST_2(string_constant,
	    string_constant_1)),FIX((SI_Long)4269L),Nil);
    string_constant_2 = 
	    STATIC_STRING("43Iy36F7Gy34E6Gy31D2Ey32C3Fy33B4Gy34A5Cy3687By3=82Ay32739y3*7=Ay33648y3*4=5y34-8y3-3*9y3*214y31143y35*6By33*4=y3-**0y34-59y3*-=0");
    string_constant_3 = STATIC_STRING("y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)6L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_2,
	    string_constant_3)),FIX((SI_Long)3558L),Nil);
    string_constant_4 = 
	    STATIC_STRING("43Ny36J7Ky31J2Ky32I6Ky39HAIy36H8Jy30H2Jy38G9Jy3=G0Jy39FBHy3*E=Iy3ADCFy36-Fy3A4B7y38495y3=405y3-4*Hy393A7y36374y31324y3*3=7y37294");
    string_constant_5 = STATIC_STRING("y3=214y31173y32=40y33*5=y34-6*y35+7-y");
    add_character_description_1(9,FIX((SI_Long)7L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(LIST_2(string_constant_4,
	    string_constant_5)),FIX((SI_Long)4621L),Nil);
    string_constant_6 = 
	    STATIC_STRING("43Ey34D5Ey30D3Fy33C4Fy3=C0Fy34B6Dy3*B=Ey35-By35365y33344y3=304y3-3*Dy34255y3*2=5y3=143y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)8L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_6),
	    FIX((SI_Long)3200L),Nil);
    string_constant_7 = 
	    STATIC_STRING("4u37J8Ky34J5Ky35I7Ky32H3Iy33G5Jy34F6Gy3*D8Fy3*476y3**Fy38*y");
    add_character_description_1(9,FIX((SI_Long)9L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_7),
	    FIX((SI_Long)4269L),Nil);
    string_constant_8 = 
	    STATIC_STRING("43Iy35E6Fy32E3Fy33D5Fy30C1Dy31B3Ey32A4By35869y3084Ay34759y3=709y35678y3*6=9y3*254y36074y30-6y34=50y3*==0y35*64y3-**8y33-5=y3*-0=");
    string_constant_9 = STATIC_STRING("y30+3*y");
    add_character_description_1(9,FIX((SI_Long)10L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_8,
	    string_constant_9)),FIX((SI_Long)3558L),Nil);
    string_constant_10 = 
	    STATIC_STRING("43Cy37H8Ky36F7Jy35D6Hy34B5Gy3394Ey3273Cy3152Ay30418y34*Ky3=206y381AKy31=4y31=30y32*4=y33-5*y34+6-y");
    add_character_description_1(9,FIX((SI_Long)11L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)25L),
	    regenerate_optimized_constant(string_constant_10),
	    FIX((SI_Long)4621L),Nil);
    string_constant_11 = 
	    STATIC_STRING("4u3446Fy3*3=5y33254y3=204y30133y31*Fy3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)12L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_11),
	    FIX((SI_Long)3558L),Nil);
    string_constant_12 = 
	    STATIC_STRING("43Oy30J1Ky31I6Ky36H7Jy3=H1Jy3-H*Iy37G8Jy3*G=Jy3E*Hy39CAHy37C8Dy38B9Iy35B6Cy36A8Cy3396By3083Ay3=709y37486y3=405y3-4*8y38396y3*3=9");
    string_constant_13 = 
	    STATIC_STRING("y36284y3=214y31163y31=30y32*4=y33-5*y34+6-y");
    add_character_description_1(9,FIX((SI_Long)13L),FIX((SI_Long)16L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(LIST_2(string_constant_12,
	    string_constant_13)),FIX((SI_Long)4269L),Nil);
    string_constant_14 = 
	    STATIC_STRING("43Iy3=D3Fy3-D*Ey33C4Fy3*C=Fy3A*Dy3596Dy3394Ay3485Ey30819y31749y3*618y34355y32334y3*3=4y33-7y33245y3-2*8y3*133y3==10y30*2=y31-3*y");
    string_constant_15 = STATIC_STRING("32+4-y");
    add_character_description_1(9,FIX((SI_Long)14L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_14,
	    string_constant_15)),FIX((SI_Long)3200L),Nil);
    string_constant_16 = 
	    STATIC_STRING("43Dy3=I9Ky3H=Ky3-F0Hy3*E1Fy3=C2Ey30B3Cy3194By32859y33668y34576y35485y36394y3193y30=20y31*3=y32-4*y33+5-y");
    add_character_description_1(9,FIX((SI_Long)15L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_16),
	    FIX((SI_Long)3910L),Nil);
    string_constant_17 = 
	    STATIC_STRING("4z3=D6Fy3C-Fy3-B*Fy3*9=Fy3=80By32637y3061Ay31529y32446y33354y3163y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)16L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_17),
	    FIX((SI_Long)3200L),Nil);
    string_constant_18 = 
	    STATIC_STRING("43Cy3=I9Ky3H=Ky3-F0Hy3*E1Fy3=C2Ey30B3Cy3194By32859y33668y34576y35485y36394y3193y33-4*y31-2*y32+3=y");
    add_character_description_1(9,FIX((SI_Long)17L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_18),
	    FIX((SI_Long)3910L),Nil);
    string_constant_19 = 
	    STATIC_STRING("4y3=D6Fy3C-Fy3-B*Fy3*9=Fy3=80By32637y3061Ay31529y32446y33354y3163y32-3*y30-1*y31+2=y");
    add_character_description_1(9,FIX((SI_Long)18L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_19),
	    FIX((SI_Long)3200L),Nil);
    string_constant_20 = 
	    STATIC_STRING("4q3=*1=y3**=y30-2*y3--=*y31+3-y3*+0-y");
    Qabove = STATIC_SYMBOL("ABOVE",AB_package);
    add_character_description_1(9,FIX((SI_Long)19L),FIX((SI_Long)9L),
	    FIX((SI_Long)1L),FIX((SI_Long)16L),FIX((SI_Long)7L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_20),
	    FIX((SI_Long)2131L),Qabove);
    string_constant_21 = 
	    STATIC_STRING("43Dy37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy381ABy31*By33=50y3==10y34*6=y30*2=y35-7*y31-3*y36+8-y32+4-y");
    add_character_description_1(9,FIX((SI_Long)20L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_21),
	    FIX((SI_Long)4621L),Nil);
    string_constant_22 = 
	    STATIC_STRING("4y3=D2Fy32C3Ey3-C=Ey33B4Dy3416Fy31*Cy31=30y3-==0y32*4=y3**0=y33-5*y3=-1*y34+6-y30+2-y");
    add_character_description_1(9,FIX((SI_Long)21L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_22),
	    FIX((SI_Long)3558L),Nil);
    string_constant_23 = 
	    STATIC_STRING("43Qy36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey399ADy3*9=Dy3B6CAy36-Ay3A4BCy38495y3=405y3-4*Cy393A7y36374y31324y3*3=7y37294y3=214");
    string_constant_24 = 
	    STATIC_STRING("y31173y35=70y31=30y36*8=y32*4=y37-9*y33-5*y38+A-y34+6-y");
    add_character_description_1(9,FIX((SI_Long)22L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_23,
	    string_constant_24)),FIX((SI_Long)4979L),Nil);
    string_constant_25 = 
	    STATIC_STRING("43Iy30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy33344y3=304y3-3*Dy34255y3*2=5y3=143y32=40y3*=00y33*5=y3=*1=y34-6*y30-2*y35+7-");
    string_constant_26 = STATIC_STRING("y31+3-y");
    add_character_description_1(9,FIX((SI_Long)23L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_25,
	    string_constant_26)),FIX((SI_Long)3558L),Nil);
    string_constant_27 = STATIC_STRING("4p3**20y32-3=y3--*=y33+4*y3-*y");
    add_character_description_1(9,FIX((SI_Long)24L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)15L),FIX((SI_Long)8L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_27),
	    FIX((SI_Long)2131L),Nil);
    string_constant_28 = STATIC_STRING("4q3==10y3**2=y31-3*y3--=*y32+4-y3*-y");
    add_character_description_1(9,FIX((SI_Long)25L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)15L),FIX((SI_Long)8L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_28),
	    FIX((SI_Long)2131L),Nil);
    string_constant_29 = 
	    STATIC_STRING("4r33=40y3=-0y32*30y3-**0y31-2=y3*-==y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)26L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)15L),FIX((SI_Long)8L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_29),
	    FIX((SI_Long)2131L),Nil);
    string_constant_30 = STATIC_STRING("4l3**y");
    add_character_description_1(9,FIX((SI_Long)27L),FIX((SI_Long)8L),
	    FIX((SI_Long)3L),FIX((SI_Long)16L),FIX((SI_Long)2L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_30),
	    FIX((SI_Long)2131L),Nil);
    add_character_description_1(9,FIX((SI_Long)28L),FIX((SI_Long)9L),
	    FIX((SI_Long)1L),FIX((SI_Long)16L),FIX((SI_Long)7L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_20),
	    FIX((SI_Long)2131L),Nil);
    string_constant_31 = STATIC_STRING("4p3-102y3*011y3**1y3--=*y3*+0-y");
    add_character_description_1(9,FIX((SI_Long)29L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)5L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_31),
	    FIX((SI_Long)2131L),Nil);
    string_constant_32 = STATIC_STRING("4o3-==1y3=-00y3--0y3-+=*y");
    add_character_description_1(9,FIX((SI_Long)30L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)14L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),
	    regenerate_optimized_constant(string_constant_32),
	    FIX((SI_Long)2131L),Nil);
    string_constant_33 = 
	    STATIC_STRING("4r30*2=y3*-=y32-3=y3=-1*y3-**y33+4*y3-+0-y");
    add_character_description_1(9,FIX((SI_Long)31L),FIX((SI_Long)10L),
	    FIX((SI_Long)1L),FIX((SI_Long)16L),FIX((SI_Long)8L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_33),
	    FIX((SI_Long)2131L),Nil);
    string_constant_34 = STATIC_STRING("4k");
    add_character_description_1(9,FIX((SI_Long)32L),FIX((SI_Long)6L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)1L),
	    FIX((SI_Long)1L),
	    regenerate_optimized_constant(string_constant_34),
	    FIX((SI_Long)1779L),Nil);
    string_constant_35 = STATIC_STRING("4n3C*Fy38-Ay3*8y");
    add_character_description_1(9,FIX((SI_Long)33L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_35),
	    FIX((SI_Long)1779L),Nil);
    string_constant_36 = STATIC_STRING("4o31122y3-1*2y30+21y3*1y");
    add_character_description_1(9,FIX((SI_Long)34L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)13L),FIX((SI_Long)6L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_36),
	    FIX((SI_Long)2272L),Nil);
    string_constant_37 = 
	    STATIC_STRING("4y31A3Dy3-A=Dy34678y30628y36*8y3244Ay3*40Ay35072y31032y30=2y33=54y3==14y34+6=y30+2=y");
    add_character_description_1(9,FIX((SI_Long)35L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)17L),
	    regenerate_optimized_constant(string_constant_37),
	    FIX((SI_Long)3558L),Nil);
    string_constant_38 = 
	    STATIC_STRING("43Iy33D4Fy3=D1Fy3-D*Ey34C5Fy3*C=Fy3A*Dy3687Dy34859y3576Ey33658y30517y3=406y3*3=6y36072y34051y3*0=1y30-4y35=62y3-=*5y33*50y3**10y");
    string_constant_39 = STATIC_STRING("31+3Hy");
    add_character_description_1(9,FIX((SI_Long)36L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)-2L),FIX((SI_Long)11L),
	    FIX((SI_Long)21L),
	    regenerate_optimized_constant(LIST_2(string_constant_38,
	    string_constant_39)),FIX((SI_Long)3558L),Nil);
    string_constant_40 = 
	    STATIC_STRING("43Iy31D2Ey39CDEy31B3Dy3294By3E8FCy3788Cy3D7EDy3879Dy33759y396D8y34567y35375y3*325y36183y37=91y33=43y3=-3y32*34y3-**4y38-A=y3*-2=");
    string_constant_41 = STATIC_STRING("y39+B-y");
    add_character_description_1(9,FIX((SI_Long)37L),FIX((SI_Long)22L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)19L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(LIST_2(string_constant_40,
	    string_constant_41)),FIX((SI_Long)5690L),Nil);
    string_constant_42 = 
	    STATIC_STRING("43Oy39CADy3=C3Ey38B9Dy33B4Dy3*B=Dy37A8Dy34A5Dy3697By36889y38-Cy3576Cy34659y32637y3-6*Dy37598y33548y3*5=8y3=407y31336y33244y30216");
    string_constant_43 = 
	    STATIC_STRING("y35*62y33*4=y30*1=y3**=2y34-53y3=-03y30+4*y");
    add_character_description_1(9,FIX((SI_Long)38L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(LIST_2(string_constant_42,
	    string_constant_43)),FIX((SI_Long)4269L),Nil);
    string_constant_44 = STATIC_STRING("4m3-1*2y3*1y");
    add_character_description_1(9,FIX((SI_Long)39L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)13L),FIX((SI_Long)2L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_44),
	    FIX((SI_Long)1222L),Nil);
    string_constant_45 = 
	    STATIC_STRING("4r3=I1Ky3*G0Iy3-D=Gy33*Dy3-0=3y3**00y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)40L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)5L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_45),
	    FIX((SI_Long)2131L),Nil);
    string_constant_46 = 
	    STATIC_STRING("4r3I*Ky3-G=Iy3*D0Gy3=31Dy3*003y3-*=0y3**y");
    add_character_description_1(9,FIX((SI_Long)41L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)5L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_46),
	    FIX((SI_Long)2131L),Nil);
    string_constant_47 = 
	    STATIC_STRING("4t31123y3-1*3y30012y3*0=2y30=20y3-==0y31*3=y3**=y3=+01y");
    add_character_description_1(9,FIX((SI_Long)42L),FIX((SI_Long)10L),
	    FIX((SI_Long)1L),FIX((SI_Long)12L),FIX((SI_Long)7L),
	    FIX((SI_Long)7L),
	    regenerate_optimized_constant(string_constant_47),
	    FIX((SI_Long)2490L),Nil);
    string_constant_48 = STATIC_STRING("4n33183y3113y31+38y");
    add_character_description_1(9,FIX((SI_Long)43L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)1L),FIX((SI_Long)12L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_48),
	    FIX((SI_Long)3738L),Nil);
    string_constant_49 = STATIC_STRING("4n31-2y3-=*1y3*=y");
    add_character_description_1(9,FIX((SI_Long)44L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-3L),FIX((SI_Long)2L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_49),
	    FIX((SI_Long)1779L),Nil);
    string_constant_50 = STATIC_STRING("4l32*y");
    add_character_description_1(9,FIX((SI_Long)45L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)6L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_50),
	    FIX((SI_Long)2131L),Nil);
    string_constant_51 = STATIC_STRING("4l3*=y");
    add_character_description_1(9,FIX((SI_Long)46L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_51),
	    FIX((SI_Long)1779L),Nil);
    string_constant_52 = 
	    STATIC_STRING("4q3C*Fy3-9=Cy3*609y3=216y30=22y31+3=y");
    add_character_description_1(9,FIX((SI_Long)47L),FIX((SI_Long)7L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)7L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_52),
	    FIX((SI_Long)1779L),Nil);
    string_constant_53 = 
	    STATIC_STRING("4y30C3Ey33B4Ey3=B0Ey3495Dy3*9=Dy36179y31-9y35*6Cy33*4=y3=*0=y3-**Cy34-51y3*-=1y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)48L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_53),
	    FIX((SI_Long)3558L),Nil);
    string_constant_54 = STATIC_STRING("4n3==1y3=*01y30+2Ey");
    add_character_description_1(9,FIX((SI_Long)49L),FIX((SI_Long)13L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_54),
	    FIX((SI_Long)3558L),Nil);
    string_constant_55 = 
	    STATIC_STRING("43Dy3*C7Ey3A-Ey3-9*Ey30819y3*8=By3=70Ay30628y32537y33447y34356y36073y34=50y3=*2y35*65y33-5=y3--==y3=+3*y");
    add_character_description_1(9,FIX((SI_Long)50L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_55),
	    FIX((SI_Long)3558L),Nil);
    string_constant_56 = 
	    STATIC_STRING("43Cy34C5Dy3=C3Ey33B4Ey3-B=Dy34A6Cy39*By3577Ay34567y30436y33346y35=63y3=*2y33*4=y34-54y3--==y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)51L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_56),
	    FIX((SI_Long)3558L),Nil);
    string_constant_57 = 
	    STATIC_STRING("4u3587Ay3*83Ay36-Ay3-5*Ay3*3=7y3=205y30014y31=22y32-31y33+5Ey");
    add_character_description_1(9,FIX((SI_Long)52L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_57),
	    FIX((SI_Long)3558L),Nil);
    string_constant_58 = 
	    STATIC_STRING("4y3=C3Ey3-C*Dy33B4Dy3*B=Dy34A5Dy39*Cy3667Ay34556y3546Cy3=405y33355y3=234y3-*=5y3-+6*y");
    add_character_description_1(9,FIX((SI_Long)53L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_58),
	    FIX((SI_Long)3558L),Nil);
    string_constant_59 = 
	    STATIC_STRING("43Fy30C3Ey33B4Ey3=B0Ey34A5Dy3*9=Dy3677By3556Dy33546y3*5=7y34457y3=406y30345y30-By35=71y3*==1y3-**Dy34-6=y3*-0=y30+4*y");
    add_character_description_1(9,FIX((SI_Long)54L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_59),
	    FIX((SI_Long)3558L),Nil);
    string_constant_60 = 
	    STATIC_STRING("4u3*B=Ey3091Cy3=80Ey30629y31436y32244y33052y34=60y34*7=y37*y");
    add_character_description_1(9,FIX((SI_Long)55L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_60),
	    FIX((SI_Long)3558L),Nil);
    string_constant_61 = 
	    STATIC_STRING("43Fy33D4Ey3=D0Ey30C3Ey33B5Dy3*B0Dy3677By37-By3566Dy3-6*Dy34558y3*5=8y3=446y33354y3*304y34=63y3-==3y33-5=y3*-0=y30+3*y");
    add_character_description_1(9,FIX((SI_Long)56L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_61),
	    FIX((SI_Long)3558L),Nil);
    string_constant_62 = 
	    STATIC_STRING("43Gy3=C3Ey3-C*Dy33B4Dy3*B=Dy35A6Cy3A*Cy3495Dy30638y33547y3=508y34456y3*4=7y3507Ay3-0*7y3=-5y33*4=y3=*0=y34-60y3--=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)57L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_62),
	    FIX((SI_Long)3558L),Nil);
    string_constant_63 = STATIC_STRING("4m37*Ay3*=y");
    add_character_description_1(9,FIX((SI_Long)58L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_63),
	    FIX((SI_Long)1779L),Nil);
    string_constant_64 = STATIC_STRING("4o3C-Dy3-A*Cy37*Ay3*=y");
    add_character_description_1(9,FIX((SI_Long)59L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-3L),FIX((SI_Long)2L),
	    FIX((SI_Long)17L),
	    regenerate_optimized_constant(string_constant_64),
	    FIX((SI_Long)1779L),Nil);
    string_constant_65 = 
	    STATIC_STRING("4v36788y34687y32566y30445y3*324y31=3y3*001y30=21y32*40y34-6=y36+8*y");
    add_character_description_1(9,FIX((SI_Long)60L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)1L),FIX((SI_Long)12L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_65),
	    FIX((SI_Long)3738L),Nil);
    string_constant_66 = STATIC_STRING("4m3=61y36*y");
    add_character_description_1(9,FIX((SI_Long)61L),FIX((SI_Long)15L),
	    FIX((SI_Long)2L),FIX((SI_Long)5L),FIX((SI_Long)10L),
	    FIX((SI_Long)5L),
	    regenerate_optimized_constant(string_constant_66),
	    FIX((SI_Long)3738L),Nil);
    string_constant_67 = 
	    STATIC_STRING("4v37*8y3607y3*526y30445y32364y35183y34061y32=41y30*20y3*-0=y3**y");
    add_character_description_1(9,FIX((SI_Long)62L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)1L),FIX((SI_Long)12L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_67),
	    FIX((SI_Long)3738L),Nil);
    string_constant_68 = 
	    STATIC_STRING("4x30C2Fy3061Ay3142Ay32336y33145y3-0*2y3=-2y35*62y33*4=y3=*0=y34-54y3--=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)63L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_68),
	    FIX((SI_Long)3558L),Nil);
    string_constant_69 = 
	    STATIC_STRING("43ay34HAJy3AGCIy32G4Iy31F2Iy30E1Hy3=D0Gy3ACDEy34C7Ey3DBEDy37B8Dy33B4Ey3*B=Fy3EAFDy3F8GCy3889Cy3172Cy3A5B8y3253Dy394ADy35465y3344");
    string_constant_70 = 
	    STATIC_STRING("7y34-Cy38394y34356y3H2I9y3A2C5y35284y3-2*Ey3G0HBy30011y3*0=4y3F=G2y3D=E0y3==02y3E*F0y3B*C=y30*20y3C-E=y32-4=y34+C*y");
    add_character_description_1(9,FIX((SI_Long)64L),FIX((SI_Long)25L),
	    FIX((SI_Long)2L),FIX((SI_Long)-4L),FIX((SI_Long)22L),
	    FIX((SI_Long)23L),
	    regenerate_optimized_constant(LIST_2(string_constant_69,
	    string_constant_70)),FIX((SI_Long)6496L),Nil);
    string_constant_71 = 
	    STATIC_STRING("4z3ACBFy3C*Fy399AFy3-9=Cy30779y3869Cy3*609y37389y3=316y36176y35063y30023y34*60y31*30y32+5*y");
    add_character_description_1(9,FIX((SI_Long)65L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_71),
	    FIX((SI_Long)4269L),Nil);
    string_constant_72 = 
	    STATIC_STRING("4x3*D6Fy36C7Ey37B8Ey397ACy3869Dy37587y3*476y36384y37=93y35*6=y3**Fy36-8=y36*y");
    add_character_description_1(9,FIX((SI_Long)66L),FIX((SI_Long)17L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_72),
	    FIX((SI_Long)4269L),Nil);
    string_constant_73 = 
	    STATIC_STRING("43Jy36E7Fy31E2Fy32D6Fy39CADy36C8Ey30C2Ey38B9Ey3=B0Ey39ABCy3*9=Dy3A8CAy31-Ay3A=B2y38=90y3==00y3-=*Cy39*A2y36*7=y31*2=y3**=2y37-9=");
    string_constant_74 = STATIC_STRING("y3=-1=y31+7*y");
    add_character_description_1(9,FIX((SI_Long)67L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_73,
	    string_constant_74)),FIX((SI_Long)4621L),Nil);
    string_constant_75 = 
	    STATIC_STRING("4x35E6Fy3*D5Fy35C7Ey37B8Ey3899Dy3A1BAy39=ACy37=80y38*92y35*6=y3**Fy36-8=y36*y");
    add_character_description_1(9,FIX((SI_Long)68L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_75),
	    FIX((SI_Long)4621L),Nil);
    string_constant_76 = STATIC_STRING("4o3*D8Fy3*476y3**Fy38*y");
    add_character_description_1(9,FIX((SI_Long)69L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_76),
	    FIX((SI_Long)4269L),Nil);
    string_constant_77 = STATIC_STRING("4n3*567y3**Fy37*y");
    add_character_description_1(9,FIX((SI_Long)70L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_77),
	    FIX((SI_Long)3910L),Nil);
    string_constant_78 = 
	    STATIC_STRING("43Jy36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey39AADy3*9=Dy3A7CFy355C7y31-Ay3A=B2y38=90y3==00y3-=*Cy39*A2y36*7=y31*2=y3**=2y37-9=");
    add_character_description_1(9,FIX((SI_Long)71L),FIX((SI_Long)19L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_78,
	    string_constant_74)),FIX((SI_Long)4979L),Nil);
    string_constant_79 = STATIC_STRING("4n3*486y38+AFy3*Fy");
    add_character_description_1(9,FIX((SI_Long)72L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_79),
	    FIX((SI_Long)4621L),Nil);
    string_constant_80 = STATIC_STRING("4l3*Fy");
    add_character_description_1(9,FIX((SI_Long)73L),FIX((SI_Long)8L),
	    FIX((SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_80),
	    FIX((SI_Long)1779L),Nil);
    string_constant_81 = 
	    STATIC_STRING("4r33E4Fy3*E=Fy3=D3Fy33C5Ey3-C=Ey38*Cy34+6Cy");
    add_character_description_1(9,FIX((SI_Long)74L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_81),
	    FIX((SI_Long)3200L),Nil);
    string_constant_82 = 
	    STATIC_STRING("43Gy3ADBFy39CAFy38B9Ey37A8Dy3697Cy3586By3475Ay33649y31627y32538y3*4=7y3=326y30233y31142y32051y33=60y34*7=y35-8*y36+9-y3*Fy");
    add_character_description_1(9,FIX((SI_Long)75L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_82),
	    FIX((SI_Long)4269L),Nil);
    string_constant_83 = STATIC_STRING("4m3*D7Fy3*Fy");
    add_character_description_1(9,FIX((SI_Long)76L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_83),
	    FIX((SI_Long)3558L),Nil);
    string_constant_84 = 
	    STATIC_STRING("4z34D5Fy35A6Fy33A4Fy3677Dy3273Dy3748Ay3142Ay38197y30117y39=A4y3==04y3A-B1y3*-=1y3B+DFy3*Fy");
    add_character_description_1(9,FIX((SI_Long)77L),FIX((SI_Long)21L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)17L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_84),
	    FIX((SI_Long)5331L),Nil);
    string_constant_85 = 
	    STATIC_STRING("4w37C8Fy36A7Ey3586Cy3465By33449y32237y31025y30=13y3=*Fy3=-01y38+AFy3==y");
    add_character_description_1(9,FIX((SI_Long)78L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_85),
	    FIX((SI_Long)4621L),Nil);
    string_constant_86 = 
	    STATIC_STRING("43Iy36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey399ADy3*9=Dy3B1CAy31-Ay3A=BCy38=90y3==00y3-=*Cy39*A2y36*7=y31*2=y3**=2y37-9=y3=-1=");
    string_constant_87 = STATIC_STRING("y31+7*y");
    add_character_description_1(9,FIX((SI_Long)79L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_86,
	    string_constant_87)),FIX((SI_Long)4979L),Nil);
    string_constant_88 = 
	    STATIC_STRING("4r3*466y36376y38=93y36*7=y3**Fy37-85y37*y");
    add_character_description_1(9,FIX((SI_Long)80L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_88),
	    FIX((SI_Long)4269L),Nil);
    string_constant_89 = 
	    STATIC_STRING("43Ky3BECFy31E2Fy3ADBFy32D7Fy37C9Ey30C2Ey35B9Cy3=B0Ey34A7By399AFy3*9=Dy3B1CAy31-Ay3A=BCy38=90y3==00y3-=*Cy39*A2y36*7=y31*2=y3**=2");
    string_constant_90 = STATIC_STRING("y37-9=y3=-1=y31+7*y");
    add_character_description_1(9,FIX((SI_Long)81L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_89,
	    string_constant_90)),FIX((SI_Long)4979L),Nil);
    string_constant_91 = 
	    STATIC_STRING("4u3889Fy3768Fy35667y3*466y36378y38=93y36*7=y3**Fy37-85y37*y");
    add_character_description_1(9,FIX((SI_Long)82L),FIX((SI_Long)17L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_91),
	    FIX((SI_Long)4621L),Nil);
    string_constant_92 = 
	    STATIC_STRING("43Ky30E1Fy31D6Fy36C7Ey3=C1Ey3-C*Dy37B8Ey3*B=Ey39*Cy397ACy37788y3869Dy35667y36587y33466y30335y3=204y37=81y3==00y3-=*3y38*91y3**=4");
    string_constant_93 = STATIC_STRING("y36-8=y3=-1=y31+6*y");
    add_character_description_1(9,FIX((SI_Long)83L),FIX((SI_Long)16L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_92,
	    string_constant_93)),FIX((SI_Long)4269L),Nil);
    string_constant_94 = STATIC_STRING("4m32*4Fy3A*y");
    add_character_description_1(9,FIX((SI_Long)84L),FIX((SI_Long)16L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_94),
	    FIX((SI_Long)3910L),Nil);
    string_constant_95 = 
	    STATIC_STRING("4t37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy38+ABy3*By");
    add_character_description_1(9,FIX((SI_Long)85L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_95),
	    FIX((SI_Long)4621L),Nil);
    string_constant_96 = 
	    STATIC_STRING("4z33C4Fy3495Fy3293Fy3566Cy3162Cy3637Ay3031Ay37087y3=007y39=A1y3-=*1y38*94y3**=4y39+B=y3*=y");
    add_character_description_1(9,FIX((SI_Long)86L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_96),
	    FIX((SI_Long)4269L),Nil);
    string_constant_97 = 
	    STATIC_STRING("43Fy3BCCFy30C1Fy3ABBFy31B2Fy3B9DCy3=91Cy396ADy3263Dy3C5E9y3*509y3819By3314By3D0F5y3-0=5y37=86y34=56y3E+G0y35+71y3*0y");
    add_character_description_1(9,FIX((SI_Long)87L),FIX((SI_Long)22L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)20L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_97),
	    FIX((SI_Long)6042L),Nil);
    string_constant_98 = 
	    STATIC_STRING("43Ny3ADBFy3D-Fy39CAFy3-C*Fy38A9Ey3*A=Ey3798Cy3=90Cy3677By3071By3566Ay3162Ay33347y34258y32238y35164y31124y36073y30013y39*A=y37*82");
    string_constant_99 = STATIC_STRING("y3=*02y3-**=y38-90y3*-=0y39+B*y3**y");
    add_character_description_1(9,FIX((SI_Long)88L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_98,
	    string_constant_99)),FIX((SI_Long)4269L),Nil);
    string_constant_100 = 
	    STATIC_STRING("4x3254Fy34358y31328y35166y30116y36=74y3==04y38*90y3-**0y37-82y3*-=2y38+A*y3**y");
    add_character_description_1(9,FIX((SI_Long)89L),FIX((SI_Long)16L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_100),
	    FIX((SI_Long)4269L),Nil);
    string_constant_101 = 
	    STATIC_STRING("4x3=D9Fy3C=Fy3-A0Cy3*91Ay3=729y30637y31446y32354y33163y34071y35=80y36*9=y39*y");
    add_character_description_1(9,FIX((SI_Long)90L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_101),
	    FIX((SI_Long)3910L),Nil);
    string_constant_102 = STATIC_STRING("4n3*I0Ky3**Ky30*y");
    add_character_description_1(9,FIX((SI_Long)91L),FIX((SI_Long)7L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)4L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_102),
	    FIX((SI_Long)1779L),Nil);
    string_constant_103 = 
	    STATIC_STRING("4q31C3Fy3092Cy3=619y3*206y3-==2y3*=y");
    add_character_description_1(9,FIX((SI_Long)92L),FIX((SI_Long)7L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)7L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_103),
	    FIX((SI_Long)1779L),Nil);
    string_constant_104 = STATIC_STRING("4n3I*Ky3**0Ky30*y");
    add_character_description_1(9,FIX((SI_Long)93L),FIX((SI_Long)7L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)4L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_104),
	    FIX((SI_Long)1779L),Nil);
    string_constant_105 = 
	    STATIC_STRING("4t35365y33-5y34155y3-1*5y33043y3*0=3y32*31y3=*01y30+2=y");
    add_character_description_1(9,FIX((SI_Long)94L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)10L),FIX((SI_Long)10L),
	    FIX((SI_Long)9L),
	    regenerate_optimized_constant(string_constant_105),
	    FIX((SI_Long)3002L),Nil);
    string_constant_106 = STATIC_STRING("4l3A*y");
    add_character_description_1(9,FIX((SI_Long)95L),FIX((SI_Long)14L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_106),
	    FIX((SI_Long)3558L),Nil);
    string_constant_107 = STATIC_STRING("4o3==10y3**0=y3--=*y3*-y");
    add_character_description_1(9,FIX((SI_Long)96L),FIX((SI_Long)7L),
	    FIX((SI_Long)1L),FIX((SI_Long)15L),FIX((SI_Long)5L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_107),
	    FIX((SI_Long)2131L),Nil);
    string_constant_108 = 
	    STATIC_STRING("43Cy3687Ay3=82Ay32739y3*7=Ay33648y3*4=5y34-8y3-3*9y3*214y31143y35*6Ay33*4=y3-**0y34-59y3*-=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)97L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_108),
	    FIX((SI_Long)3558L),Nil);
    string_constant_109 = 
	    STATIC_STRING("4x30D3Fy33C4Fy3=C0Ey34B5Ey3*B=Ey3657By3*4=5y3536Dy33344y34255y3*204y30143y3*Fy");
    add_character_description_1(9,FIX((SI_Long)98L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_109),
	    FIX((SI_Long)3558L),Nil);
    string_constant_110 = 
	    STATIC_STRING("4y34859y3083Ay3374Ay3=70Ay34668y3*6=9y30-6y35*60y33*4=y3=*0=y3-**8y34-50y3*-=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)99L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_110),
	    FIX((SI_Long)3200L),Nil);
    string_constant_111 = 
	    STATIC_STRING("4x30D3Fy33C4Ey3=C0Fy34B5Ey3*B=Ey35-By34455y3=304y3-3*Dy33254y3*2=5y3=133y35+7Fy");
    add_character_description_1(9,FIX((SI_Long)100L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_111),
	    FIX((SI_Long)3558L),Nil);
    string_constant_112 = 
	    STATIC_STRING("43Cy35869y3084Ay34759y3=709y35678y3*6=9y3*254y36074y30-6y34=50y3*==0y35*64y3-**8y33-5=y3*-0=y30+3*y");
    add_character_description_1(9,FIX((SI_Long)101L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_112),
	    FIX((SI_Long)3558L),Nil);
    string_constant_113 = STATIC_STRING("4p30123y31*3y3=*0Fy3*-=Fy3=+2*y");
    add_character_description_1(9,FIX((SI_Long)102L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_113),
	    FIX((SI_Long)1779L),Nil);
    string_constant_114 = 
	    STATIC_STRING("43Ey3=D4Fy3-D*Ey34C6Ey3*C=Ey3B*Dy3083Ay33749y3=70Ay34659y3*6=9y30-6y34=50y3=*0=y3-**8y33-5=y3*-=0y35+7Cy3=+3*y");
    add_character_description_1(9,FIX((SI_Long)103L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_114),
	    FIX((SI_Long)3558L),Nil);
    string_constant_115 = 
	    STATIC_STRING("4q3446Fy3*3=5y33254y3=204y30133y3*Fy");
    add_character_description_1(9,FIX((SI_Long)104L),FIX((SI_Long)13L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_115),
	    FIX((SI_Long)3558L),Nil);
    string_constant_116 = STATIC_STRING("4m31*Fy3*=y");
    add_character_description_1(9,FIX((SI_Long)105L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_116),
	    FIX((SI_Long)1421L),Nil);
    string_constant_117 = STATIC_STRING("4o3*J=Ky3I*Ky3*10Jy3*+0=y");
    add_character_description_1(9,FIX((SI_Long)106L),FIX((SI_Long)6L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)4L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_117),
	    FIX((SI_Long)1421L),Nil);
    string_constant_118 = 
	    STATIC_STRING("4x35D6Fy34B5Fy33A4Ey3283Cy3172By3*6=8y3=508y30419y33344y31326y32235y33153y3*Fy");
    add_character_description_1(9,FIX((SI_Long)107L),FIX((SI_Long)12L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_118),
	    FIX((SI_Long)3200L),Nil);
    add_character_description_1(9,FIX((SI_Long)108L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_80),
	    FIX((SI_Long)1421L),Nil);
    string_constant_119 = 
	    STATIC_STRING("4w3B*CAy39*A=y34*5Ay32*3=y3**==y3A-BAy35-6=y33-4Ay3*-0*y36+A*y30+3*y3*Ay");
    add_character_description_1(9,FIX((SI_Long)109L),FIX((SI_Long)20L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_119),
	    FIX((SI_Long)5331L),Nil);
    string_constant_120 = 
	    STATIC_STRING("4q34=6Ay3**=0y33-5=y3=-0=y30+3*y3*Ay");
    add_character_description_1(9,FIX((SI_Long)110L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_120),
	    FIX((SI_Long)3558L),Nil);
    string_constant_121 = 
	    STATIC_STRING("4y3083Ay3374Ay3=70Ay34659y3*6=9y36076y30-6y35*68y33*4=y3=*0=y3-**8y34-50y3*-=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)111L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_121),
	    FIX((SI_Long)3558L),Nil);
    string_constant_122 = 
	    STATIC_STRING("4x3083Ay3374Ay3=709y34659y3*6=9y36076y3*==0y35*68y33*4=y34-50y3*-0=y30+4*y3*Fy");
    add_character_description_1(9,FIX((SI_Long)112L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_122),
	    FIX((SI_Long)3558L),Nil);
    string_constant_123 = 
	    STATIC_STRING("4x3083Ay33749y3=70Ay34659y3*6=9y30-6y34=50y3=*0=y3-**8y33-5=y3*-=0y35+7Fy3=+3*y");
    add_character_description_1(9,FIX((SI_Long)113L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_123),
	    FIX((SI_Long)3558L),Nil);
    string_constant_124 = STATIC_STRING("4p30*1=y3**=1y3=-00y30+2*y3*Ay");
    add_character_description_1(9,FIX((SI_Long)114L),FIX((SI_Long)9L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_124),
	    FIX((SI_Long)2131L),Nil);
    string_constant_125 = 
	    STATIC_STRING("43Ey3=83Ay3-8*9y3374Ay3*7=Ay35*8y35468y33445y34359y30314y31244y3*113y34*50y32*3=y3**==y3*-2y33-40y3--*3y3*+3*y");
    add_character_description_1(9,FIX((SI_Long)115L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_125),
	    FIX((SI_Long)3200L),Nil);
    string_constant_126 = STATIC_STRING("4p3=D0Ey30C2Ey30022y30*2y3*+0Dy");
    add_character_description_1(9,FIX((SI_Long)116L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_126),
	    FIX((SI_Long)1779L),Nil);
    string_constant_127 = 
	    STATIC_STRING("4q3=82Ay32739y3-7=9y33648y34+6Ay3*7y");
    add_character_description_1(9,FIX((SI_Long)117L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_127),
	    FIX((SI_Long)3558L),Nil);
    string_constant_128 = 
	    STATIC_STRING("4v3172Ay3243Ay3041Ay34254y3*2=4y33147y3=107y34=62y3-==2y35+7=y3*=y");
    add_character_description_1(9,FIX((SI_Long)118L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_128),
	    FIX((SI_Long)3200L),Nil);
    string_constant_129 = 
	    STATIC_STRING("43Dy397AAy3071Ay3869Ay3162Ay394B7y3=417y37288y32238y3A1C4y3*104y3B*D1y36*75y33*45y3-*=1y3C+E*y34+61y3**y");
    add_character_description_1(9,FIX((SI_Long)119L),FIX((SI_Long)18L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_129),
	    FIX((SI_Long)4621L),Nil);
    string_constant_130 = 
	    STATIC_STRING("43Dy3586Ay38-Ay3465Ay3-6*Ay33549y3*5=9y32337y3=307y30025y32=32y3==02y34*5=y3-**=y33-41y3*-=1y34+6*y3**y");
    add_character_description_1(9,FIX((SI_Long)120L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_130),
	    FIX((SI_Long)3200L),Nil);
    string_constant_131 = 
	    STATIC_STRING("4z3*D0Fy30C1Fy31A2Ey3263Cy3344Ay31428y35264y34157y30116y3*0=2y35=72y3==04y3-*=0y36+8=y3**y");
    add_character_description_1(9,FIX((SI_Long)121L),FIX((SI_Long)13L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_131),
	    FIX((SI_Long)3200L),Nil);
    string_constant_132 = 
	    STATIC_STRING("4v3=86Ay37-Ay3-6*Ay3*4=Ay3=306y32132y30115y31024y32=41y33*5=y36*y");
    add_character_description_1(9,FIX((SI_Long)122L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_132),
	    FIX((SI_Long)3200L),Nil);
    string_constant_133 = 
	    STATIC_STRING("4t30J2Ky3=I1Jy3*A0Iy3-9=Ay37*9y3-6=7y3**06y3=-1*y30+2-y");
    add_character_description_1(9,FIX((SI_Long)123L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)6L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_133),
	    FIX((SI_Long)2138L),Nil);
    string_constant_134 = STATIC_STRING("4l3*Ky");
    add_character_description_1(9,FIX((SI_Long)124L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)2L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_134),
	    FIX((SI_Long)1664L),Nil);
    string_constant_135 = 
	    STATIC_STRING("4t3J*Ky3-I=Jy3*A0Iy3=91Ay30729y3=617y3**06y3--=*y3*-y");
    add_character_description_1(9,FIX((SI_Long)125L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)6L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_135),
	    FIX((SI_Long)2138L),Nil);
    string_constant_136 = 
	    STATIC_STRING("4r34=50y32*40y3-**0y30-2=y3--0y34+6=y3-+0*y");
    add_character_description_1(9,FIX((SI_Long)126L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)5L),FIX((SI_Long)10L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_136),
	    FIX((SI_Long)3738L),Nil);
    string_constant_137 = STATIC_STRING("4n3=-00y3--0y3-+=1y");
    add_character_description_1(9,FIX((SI_Long)128L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)6L),FIX((SI_Long)4L),
	    FIX((SI_Long)5L),
	    regenerate_optimized_constant(string_constant_137),
	    FIX((SI_Long)2240L),Nil);
    string_constant_138 = STATIC_STRING("4n33183y3113y31+3Ky");
    add_character_description_1(9,FIX((SI_Long)129L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_138),
	    FIX((SI_Long)3558L),Nil);
    string_constant_139 = STATIC_STRING("4p33D8Fy3D1Fy33183y3113y31+3Ky");
    add_character_description_1(9,FIX((SI_Long)130L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_139),
	    FIX((SI_Long)3558L),Nil);
    string_constant_140 = STATIC_STRING("4n3C+E=y34+6=y3*=y");
    add_character_description_1(9,FIX((SI_Long)131L),FIX((SI_Long)25L),
	    FIX((SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_140),
	    FIX((SI_Long)6400L),Nil);
    string_constant_141 = STATIC_STRING("4l3L*y");
    add_character_description_1(9,FIX((SI_Long)132L),FIX((SI_Long)25L),
	    FIX((SI_Long)0L),FIX((SI_Long)6L),FIX((SI_Long)25L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_141),
	    FIX((SI_Long)6400L),Nil);
    add_character_description_1(9,FIX((SI_Long)133L),FIX((SI_Long)14L),
	    FIX((SI_Long)0L),FIX((SI_Long)6L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_106),
	    FIX((SI_Long)3558L),Nil);
    string_constant_142 = 
	    STATIC_STRING("4u3H*Jy3*G=Jy3=E0Iy3041Hy33264y3-214y33*4=y31*2Ey32-34y33+7*y");
    add_character_description_1(9,FIX((SI_Long)134L),FIX((SI_Long)11L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)23L),
	    regenerate_optimized_constant(string_constant_142),
	    FIX((SI_Long)3558L),Nil);
    string_constant_143 = 
	    STATIC_STRING("4t3C*Ey3-A=Cy3*80Ay3=618y30426y31234y32042y33*50y34+6*y");
    add_character_description_1(9,FIX((SI_Long)135L),FIX((SI_Long)4L),
	    FIX((SI_Long)-3L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_143),
	    FIX((SI_Long)1069L),Nil);
    string_constant_144 = 
	    STATIC_STRING("4r3=314y3*203y3-1=2y3=*1y3-*==y3*-0*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)136L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)3L),FIX((SI_Long)5L),
	    FIX((SI_Long)8L),
	    regenerate_optimized_constant(string_constant_144),
	    FIX((SI_Long)2131L),Nil);
    string_constant_145 = 
	    STATIC_STRING("4r33*4y3-2=3y3*102y3==11y3**0=y3--=*y3*-y");
    add_character_description_1(9,FIX((SI_Long)137L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)5L),
	    FIX((SI_Long)8L),
	    regenerate_optimized_constant(string_constant_145),
	    FIX((SI_Long)2131L),Nil);
    string_constant_146 = STATIC_STRING("4l37*y");
    add_character_description_1(9,FIX((SI_Long)138L),FIX((SI_Long)15L),
	    FIX((SI_Long)2L),FIX((SI_Long)6L),FIX((SI_Long)11L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_146),
	    FIX((SI_Long)3878L),Nil);
    string_constant_147 = 
	    STATIC_STRING("43Py3CCFEy34C7Ey3-C*Ey3*A=Ey3G9HCy3A9BCy3899Cy3293Cy3091Ay3F8GDy3B8CDy3788Dy3384Dy3=80Cy3C7F9y34779y30729y31537y32345y33153y3*11");
    string_constant_148 = 
	    STATIC_STRING("3y34=61y32*31y3*-1y35-7=y31-22y3--*2y36+8-y3*+1*y");
    add_character_description_1(9,FIX((SI_Long)139L),FIX((SI_Long)23L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)21L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(LIST_2(string_constant_147,
	    string_constant_148)),FIX((SI_Long)6400L),Nil);
    string_constant_149 = STATIC_STRING("4q3=102y31-2y30=11y3-=*1y3=+1=y3*=y");
    add_character_description_1(9,FIX((SI_Long)140L),FIX((SI_Long)9L),
	    FIX((SI_Long)2L),FIX((SI_Long)-3L),FIX((SI_Long)5L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_149),
	    FIX((SI_Long)2131L),Nil);
    string_constant_150 = 
	    STATIC_STRING("4q30=12y3-=*2y3=-02y3--2y30+1-y3-+*-y");
    add_character_description_1(9,FIX((SI_Long)141L),FIX((SI_Long)9L),
	    FIX((SI_Long)2L),FIX((SI_Long)13L),FIX((SI_Long)5L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_150),
	    FIX((SI_Long)2131L),Nil);
    add_character_description_1(9,FIX((SI_Long)142L),FIX((SI_Long)9L),
	    FIX((SI_Long)2L),FIX((SI_Long)13L),FIX((SI_Long)5L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_149),
	    FIX((SI_Long)2131L),Nil);
    string_constant_151 = STATIC_STRING("4n3-=*2y3--2y3-+*-y");
    add_character_description_1(9,FIX((SI_Long)143L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)13L),FIX((SI_Long)2L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_151),
	    FIX((SI_Long)1421L),Nil);
    add_character_description_1(9,FIX((SI_Long)144L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)13L),FIX((SI_Long)2L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_49),
	    FIX((SI_Long)1421L),Nil);
    add_character_description_1(9,FIX((SI_Long)145L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-3L),FIX((SI_Long)2L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_49),
	    FIX((SI_Long)1421L),Nil);
    string_constant_152 = 
	    STATIC_STRING("4t391B6y3B=C2y38=92y3=*16y3C-D0y37-80y3D+F6y35+76y34*y");
    add_character_description_1(9,FIX((SI_Long)146L),FIX((SI_Long)21L),
	    FIX((SI_Long)1L),FIX((SI_Long)7L),FIX((SI_Long)19L),
	    FIX((SI_Long)10L),
	    regenerate_optimized_constant(string_constant_152),
	    FIX((SI_Long)5510L),Nil);
    string_constant_153 = 
	    STATIC_STRING("4r3416Fy30123y31*3y3=*0Fy3*-=Fy34+6=y3=+2*y");
    add_character_description_1(9,FIX((SI_Long)147L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_153),
	    FIX((SI_Long)3200L),Nil);
    string_constant_154 = 
	    STATIC_STRING("4q30123y31*3y3=*0Fy3*-=Fy34+6Fy3=+2*y");
    add_character_description_1(9,FIX((SI_Long)148L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_154),
	    FIX((SI_Long)3200L),Nil);
    string_constant_155 = 
	    STATIC_STRING("4s31DAFy36-7y3-5*7y3*4=6y31223y31132y32041y3=+1Fy");
    add_character_description_1(9,FIX((SI_Long)149L),FIX((SI_Long)14L),
	    FIX((SI_Long)-1L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_155),
	    FIX((SI_Long)3558L),Nil);
    string_constant_156 = 
	    STATIC_STRING("43Ey31E2Fy39DHFy32D6Fy36C7Ey30C2Ey3=B0Ey3*9=Dy395H7y31-Ay3==00y3-=*Cy37*9Fy31*2=y3**=2y36-7=y3=-1=y37+H*y31+6*y");
    add_character_description_1(9,FIX((SI_Long)150L),FIX((SI_Long)23L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)21L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_156),
	    FIX((SI_Long)6400L),Nil);
    string_constant_157 = 
	    STATIC_STRING("43Hy3=D6Fy3-D*Ey36C7Ey3*C=Ey3B*Dy37A8Ey3899Cy3688Ay30769y3=608y3*4=8y3-3*7y35274y3*204y30153y31=30y30*4=y33-5*y3=-1*y34+6-y3*+0-");
    add_character_description_1(9,FIX((SI_Long)151L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_157,
	    string_constant_1)),FIX((SI_Long)4269L),Nil);
    string_constant_158 = 
	    STATIC_STRING("4x3163Fy33548y30518y36374y34356y3=306y3-3*4y35265y3*2=5y36183y31*3y33+5*y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)152L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_158),
	    FIX((SI_Long)4269L),Nil);
    string_constant_159 = 
	    STATIC_STRING("43Ey3=D9Fy3C=Fy3-B0Cy3*A1By3=92Ay30839y31758y33667y34576y35485y36394y3193y31=30y30*4=y33-5*y3=-1*y34+6-y3*+0-y");
    add_character_description_1(9,FIX((SI_Long)153L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_159),
	    FIX((SI_Long)3910L),Nil);
    string_constant_160 = STATIC_STRING("4l3*Ay");
    add_character_description_1(9,FIX((SI_Long)154L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)2L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(string_constant_160),
	    FIX((SI_Long)1779L),Nil);
    string_constant_161 = STATIC_STRING("4p36-7y3-5*7y30415y30324y3*+0Fy");
    add_character_description_1(9,FIX((SI_Long)155L),FIX((SI_Long)6L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_161),
	    FIX((SI_Long)1421L),Nil);
    string_constant_162 = 
	    STATIC_STRING("43Ny3E8F9y398DAy3083Ay3D7E9y38799y3374Ay3=70Ay3E6G8y37689y34659y3*6=9y372E4y3F0G4y30-6y3D=E0y37=80y3E*F4y35*78y33*4=y3=*0=y3-**8");
    string_constant_163 = 
	    STATIC_STRING("y3C-E=y37-9=y34-50y3*-=0y39+C*y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)156L),FIX((SI_Long)22L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)20L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(LIST_2(string_constant_162,
	    string_constant_163)),FIX((SI_Long)6042L),Nil);
    string_constant_164 = 
	    STATIC_STRING("43Ky3=D3Fy3-D*Ey33C4Fy3*C=Fy3A*Dy3596Dy3394Ay3485Ey30819y31749y3*618y34355y32334y3*3=4y33-7y33245y3-2*8y3*133y30=20y3=*3=y32-4*y");
    string_constant_165 = STATIC_STRING("3*-0*y33+5-y3-+=-y");
    add_character_description_1(9,FIX((SI_Long)157L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_164,
	    string_constant_165)),FIX((SI_Long)3200L),Nil);
    string_constant_166 = 
	    STATIC_STRING("43Dy3=D6Fy3C-Fy3-B*Fy3*9=Fy3=80By32637y3061Ay31529y32446y33354y3163y30=20y3=*3=y32-4*y3*-0*y33+5-y3-+=-y");
    add_character_description_1(9,FIX((SI_Long)158L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_166),
	    FIX((SI_Long)3200L),Nil);
    string_constant_167 = STATIC_STRING("4n33-Fy3-1*Fy3*=y");
    add_character_description_1(9,FIX((SI_Long)161L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)2L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_167),
	    FIX((SI_Long)2131L),Nil);
    string_constant_168 = 
	    STATIC_STRING("43Ey3-C=Ey34A5By30A3Cy3394Cy3*90Cy3486Ay3=619y30326y32-9y31133y35062y32041y3=001y3-0*By34=52y3*==2y3=*40y33+5*y");
    add_character_description_1(9,FIX((SI_Long)162L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)-2L),FIX((SI_Long)10L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_168),
	    FIX((SI_Long)3558L),Nil);
    string_constant_169 = 
	    STATIC_STRING("43Gy36D7Ey3=D0Ey34C6Ey3=C1Dy3C-Ey36B8Dy31B4Dy3-B*Ey3*9=Ey31456y34=6y30319y3=10By36=70y37*80y3=*0=y3-**2y35-7=y3*-=3y3=+5*y");
    add_character_description_1(9,FIX((SI_Long)163L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_169),
	    FIX((SI_Long)3558L),Nil);
    string_constant_170 = 
	    STATIC_STRING("43Ey36678y36-8y35568y30537y3-5*8y33446y3=406y35064y3-0*4y35*6=y33*40y3=*00y3-**=y34-57y30-3=y3*-=7y35+7*y3**y");
    add_character_description_1(9,FIX((SI_Long)164L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)3L),FIX((SI_Long)11L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_170),
	    FIX((SI_Long)3558L),Nil);
    string_constant_171 = 
	    STATIC_STRING("43Dy34789y3*729y36486y3244Ey3*406y34256y31226y35066y30016y37=81y3*==1y36*73y3=*03y37-9=y3--==y37+A-y3=-y");
    add_character_description_1(9,FIX((SI_Long)165L),FIX((SI_Long)14L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_171),
	    FIX((SI_Long)3558L),Nil);
    string_constant_172 = STATIC_STRING("4m3A*Ky3*6y");
    add_character_description_1(9,FIX((SI_Long)166L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)2L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_172),
	    FIX((SI_Long)1664L),Nil);
    string_constant_173 = 
	    STATIC_STRING("43Sy30I3Ky3*I=Jy33H4Ky3=H0Ky35F6Iy33F4Gy3-F=Iy34E5Jy32C4Fy34B5Dy31B2Ey30A1Dy3=90Cy3687By3*8=By3566Cy34558y3-5*Ay33447y34-8y32336");
    string_constant_174 = 
	    STATIC_STRING("y3-3=5y31225y30114y3=004y35*61y33*4=y3=*0=y3-**1y34-51y3*-=2y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)167L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(LIST_2(string_constant_173,
	    string_constant_174)),FIX((SI_Long)3558L),Nil);
    string_constant_175 = STATIC_STRING("4m30+2*y3**y");
    add_character_description_1(9,FIX((SI_Long)168L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)16L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_175),
	    FIX((SI_Long)2131L),Nil);
    string_constant_176 = 
	    STATIC_STRING("43Ry31C8Dy37B9Cy30B2Cy39AACy3=A0Cy3A9BBy3*9=By33869y3B7CAy36779y32739y3-7*Ay37688y31628y30317y37283y30223y3C1D8y36182y31132y31-8");
    string_constant_177 = 
	    STATIC_STRING("y3B0C2y32071y3-0*2y3A=C0y3-==0y39*B=y3**0=y37-A*y3=-2*y31+8-y");
    add_character_description_1(9,FIX((SI_Long)169L),FIX((SI_Long)19L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)17L),
	    FIX((SI_Long)17L),
	    regenerate_optimized_constant(LIST_2(string_constant_176,
	    string_constant_177)),FIX((SI_Long)4781L),Nil);
    string_constant_178 = 
	    STATIC_STRING("4u3638y31435y3-4*5y3*305y31*4y3-0=1y3==01y30-24y3-*=y3-+1-y");
    add_character_description_1(9,FIX((SI_Long)170L),FIX((SI_Long)9L),
	    FIX((SI_Long)1L),FIX((SI_Long)7L),FIX((SI_Long)7L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_178),
	    FIX((SI_Long)2368L),Nil);
    string_constant_179 = 
	    STATIC_STRING("4y33354y3=314y32243y3*203y31132y3-1=2y30=21y3=*1y31*3=y3-*==y32-4*y3*-0*y33+5-y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)171L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)3L),FIX((SI_Long)9L),
	    FIX((SI_Long)8L),
	    regenerate_optimized_constant(string_constant_179),
	    FIX((SI_Long)3558L),Nil);
    string_constant_180 = STATIC_STRING("4m37*94y39*y");
    add_character_description_1(9,FIX((SI_Long)172L),FIX((SI_Long)15L),
	    FIX((SI_Long)1L),FIX((SI_Long)2L),FIX((SI_Long)13L),
	    FIX((SI_Long)8L),
	    regenerate_optimized_constant(string_constant_180),
	    FIX((SI_Long)3878L),Nil);
    string_constant_181 = 
	    STATIC_STRING("43Ny31C8Dy37B9Cy30B2Cy39AACy3=A0Cy3A9BBy3*9=By37889y3B7CAy3-7*Ay36678y35566y33475y3C1D8y37184y32139y31-8y3B0C2y32071y3-0*2y3A=C0");
    string_constant_182 = 
	    STATIC_STRING("y3-==0y39*B=y3**0=y37-A*y3=-2*y31+8-y");
    add_character_description_1(9,FIX((SI_Long)174L),FIX((SI_Long)19L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)17L),
	    FIX((SI_Long)17L),
	    regenerate_optimized_constant(LIST_2(string_constant_181,
	    string_constant_182)),FIX((SI_Long)4781L),Nil);
    add_character_description_1(9,FIX((SI_Long)175L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)16L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),
	    regenerate_optimized_constant(string_constant_50),
	    FIX((SI_Long)2131L),Nil);
    string_constant_183 = 
	    STATIC_STRING("4s3*223y31132y3-1=2y32*41y3**1y31-3*y3--=*y3*+2-y");
    add_character_description_1(9,FIX((SI_Long)176L),FIX((SI_Long)9L),
	    FIX((SI_Long)0L),FIX((SI_Long)11L),FIX((SI_Long)8L),
	    FIX((SI_Long)7L),
	    regenerate_optimized_constant(string_constant_183),
	    FIX((SI_Long)2560L),Nil);
    string_constant_184 = STATIC_STRING("4o3789y33082y3012y31+36y");
    add_character_description_1(9,FIX((SI_Long)177L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)13L),
	    regenerate_optimized_constant(string_constant_184),
	    FIX((SI_Long)3738L),Nil);
    string_constant_185 = 
	    STATIC_STRING("4v3=436y34-6y3-3*6y3*2=6y3=103y30012y31*21y3*-=y32-30y3--*=y3*+2*y");
    add_character_description_1(9,FIX((SI_Long)178L),FIX((SI_Long)7L),
	    FIX((SI_Long)0L),FIX((SI_Long)8L),FIX((SI_Long)7L),
	    FIX((SI_Long)10L),
	    regenerate_optimized_constant(string_constant_185),
	    FIX((SI_Long)3558L),Nil);
    string_constant_186 = 
	    STATIC_STRING("4u3-5*6y3*416y33*5y32235y3*012y31*26y3-**=y32-30y3--=y3-+2*y");
    add_character_description_1(9,FIX((SI_Long)179L),FIX((SI_Long)7L),
	    FIX((SI_Long)0L),FIX((SI_Long)8L),FIX((SI_Long)7L),
	    FIX((SI_Long)10L),
	    regenerate_optimized_constant(string_constant_186),
	    FIX((SI_Long)3558L),Nil);
    string_constant_187 = STATIC_STRING("4o3=*0y3-*==y3*-0*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)180L),FIX((SI_Long)7L),
	    FIX((SI_Long)1L),FIX((SI_Long)15L),FIX((SI_Long)5L),
	    FIX((SI_Long)4L),
	    regenerate_optimized_constant(string_constant_187),
	    FIX((SI_Long)2131L),Nil);
    string_constant_188 = 
	    STATIC_STRING("4q3=82Ay32739y3*7=9y33648y34+6Ay3*Fy");
    add_character_description_1(9,FIX((SI_Long)181L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_188),
	    FIX((SI_Long)3558L),Nil);
    string_constant_189 = 
	    STATIC_STRING("4r3082Ky3*7=8y3=-5y33*5Ky3=*28y3--=7y3=+6*y");
    add_character_description_1(9,FIX((SI_Long)182L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)10L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_189),
	    FIX((SI_Long)3437L),Nil);
    add_character_description_1(9,FIX((SI_Long)183L),FIX((SI_Long)6L),
	    FIX((SI_Long)2L),FIX((SI_Long)6L),FIX((SI_Long)2L),
	    FIX((SI_Long)3L),
	    regenerate_optimized_constant(string_constant_51),
	    FIX((SI_Long)1779L),Nil);
    string_constant_190 = STATIC_STRING("4p3-1=2y30=1y30*11y3=-02y3-+=*y");
    add_character_description_1(9,FIX((SI_Long)184L),FIX((SI_Long)7L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)5L),
	    FIX((SI_Long)6L),
	    regenerate_optimized_constant(string_constant_190),
	    FIX((SI_Long)2131L),Nil);
    string_constant_191 = STATIC_STRING("4m3**0y3*+06y");
    add_character_description_1(9,FIX((SI_Long)185L),FIX((SI_Long)7L),
	    FIX((SI_Long)0L),FIX((SI_Long)8L),FIX((SI_Long)4L),
	    FIX((SI_Long)10L),
	    regenerate_optimized_constant(string_constant_191),
	    FIX((SI_Long)3558L),Nil);
    string_constant_192 = 
	    STATIC_STRING("4v3638y3=305y30215y3*2=5y32*33y30*1=y3**==y3*-3y31-24y3--*4y3*+1*y");
    add_character_description_1(9,FIX((SI_Long)186L),FIX((SI_Long)9L),
	    FIX((SI_Long)1L),FIX((SI_Long)7L),FIX((SI_Long)7L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_192),
	    FIX((SI_Long)2336L),Nil);
    string_constant_193 = 
	    STATIC_STRING("4y30324y33*4y31233y3-2=3y32142y3*102y33=51y3==11y32*4=y3**0=y31-3*y3--=*y30+2-y3*-y");
    add_character_description_1(9,FIX((SI_Long)187L),FIX((SI_Long)14L),
	    FIX((SI_Long)3L),FIX((SI_Long)3L),FIX((SI_Long)9L),
	    FIX((SI_Long)8L),
	    regenerate_optimized_constant(string_constant_193),
	    FIX((SI_Long)3558L),Nil);
    string_constant_194 = 
	    STATIC_STRING("43Fy3=C1Ey3CAECy38AACy35A6Cy30A2Cy3697Cy3788Cy3183Ay38699y32648y395A8y3A4CEy33456y34264y35072y36*80y3**0y37+9*y3*+06y");
    add_character_description_1(9,FIX((SI_Long)188L),FIX((SI_Long)19L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_194),
	    FIX((SI_Long)1069L),Nil);
    string_constant_195 = 
	    STATIC_STRING("43Iy3ACEEy37C8Ey3=C1Ey38B9Ey39AAEy30A2Cy3A9BBy3B8CAy3183Ay3C6D9y37687y32648y3D5E8y38597y394D6y33456y34264y35072y36*80y3**0y37+9*");
    string_constant_196 = STATIC_STRING("y3*+06y");
    add_character_description_1(9,FIX((SI_Long)189L),FIX((SI_Long)19L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(LIST_2(string_constant_195,
	    string_constant_196)),FIX((SI_Long)1069L),Nil);
    string_constant_197 = 
	    STATIC_STRING("43Ny30C2Ey3DAFCy39ABCy36A7Cy31A3Cy3798Cy3889Cy3284Ay396A9y33658y3A5B8y3-5*6y3B4DEy34466y3*416y33*5y35274y32235y36082y3*012y37*90");
    string_constant_198 = 
	    STATIC_STRING("y31*26y3-**=y32-30y3--=y38+A*y3-+2*y");
    add_character_description_1(9,FIX((SI_Long)190L),FIX((SI_Long)19L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)19L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(LIST_2(string_constant_197,
	    string_constant_198)),FIX((SI_Long)1069L),Nil);
    string_constant_199 = 
	    STATIC_STRING("4x3=D2Fy34C5Ey32C3Fy3*C=Fy33B4Ey3496Cy39-Dy3=708y3-7*Ey3*6=Ay3=517y30125y30+2=y");
    add_character_description_1(9,FIX((SI_Long)191L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_199),
	    FIX((SI_Long)3910L),Nil);
    string_constant_200 = 
	    STATIC_STRING("43Gy3ADBFy3D-Fy39BAFy3-B*Fy37A8By3=A0By3899Dy3*9=Dy3186Ay3678Ay3=71Ay35577y30527y34365y31335y32153y33=50y32*4=y31-3*y30+2-y");
    add_character_description_1(9,FIX((SI_Long)192L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_200),
	    FIX((SI_Long)4269L),Nil);
    string_constant_201 = 
	    STATIC_STRING("43Gy3ADBFy3D-Fy39BAFy3-B*Fy37A8By3=A0By3899Dy3*9=Dy3186Ay3678Ay3=71Ay35577y30527y34365y31335y32153y32=40y33*5=y34-6*y35+7-y");
    add_character_description_1(9,FIX((SI_Long)193L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_201),
	    FIX((SI_Long)4269L),Nil);
    string_constant_202 = 
	    STATIC_STRING("43Jy3ADBFy3D-Fy39BAFy3-B*Fy37A8By3=A0By3899Dy3*9=Dy3186Ay3678Ay3=71Ay35577y30527y34365y31335y32153y36=70y3==00y35*60y30*10y34-5=");
    string_constant_203 = STATIC_STRING("y31-2=y32+4*y");
    add_character_description_1(9,FIX((SI_Long)194L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_202,
	    string_constant_203)),FIX((SI_Long)4269L),Nil);
    string_constant_204 = 
	    STATIC_STRING("43Jy3ADBFy3D-Fy39BAFy3-B*Fy37A8By3=A0By3899Dy3*9=Dy3186Ay3678Ay3=71Ay35577y30527y34365y31335y32153y34*6=y30*1=y36-7=y33-5*y30-2*");
    string_constant_205 = STATIC_STRING("y37+8*y31+4-y");
    add_character_description_1(9,FIX((SI_Long)195L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_204,
	    string_constant_205)),FIX((SI_Long)4269L),Nil);
    string_constant_206 = 
	    STATIC_STRING("43Ey3ADBFy3D-Fy39BAFy3-B*Fy37A8By3=A0By3899Dy3*9=Dy3186Ay3678Ay3=71Ay35577y30527y34365y31335y32153y34+6*y30+2*y");
    add_character_description_1(9,FIX((SI_Long)196L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_206),
	    FIX((SI_Long)4269L),Nil);
    string_constant_207 = 
	    STATIC_STRING("43Fy3ADBFy3D-Fy39BAFy3-B*Fy3=A0By3899Dy3*9=Dy3186Ay3778By3=71Ay3657Ay30527y35367y31335y34155y32=43y34-50y31-20y32+4*y");
    add_character_description_1(9,FIX((SI_Long)197L),FIX((SI_Long)17L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_207),
	    FIX((SI_Long)4269L),Nil);
    string_constant_208 = 
	    STATIC_STRING("4v37DHFy3C*Fy3-9=Cy30759y3*609y374H6y3=316y30023y35*7Fy31*30y32+H*y");
    add_character_description_1(9,FIX((SI_Long)198L),FIX((SI_Long)23L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)21L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_208),
	    FIX((SI_Long)6400L),Nil);
    string_constant_209 = 
	    STATIC_STRING("43Ny32J5Ky31I4Jy34G6Jy32F5Gy36E7Fy31E2Fy32D6Fy39CADy36C8Ey30C2Ey38B9Ey3=B0Ey39ABCy3*9=Dy3A8CAy31-Ay3A=B2y38=90y3==00y3-=*Cy39*A2");
    string_constant_210 = 
	    STATIC_STRING("y36*7=y31*2=y3**=2y37-9=y3=-1=y31+7*y");
    add_character_description_1(9,FIX((SI_Long)199L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)16L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(LIST_2(string_constant_209,
	    string_constant_210)),FIX((SI_Long)4621L),Nil);
    string_constant_211 = 
	    STATIC_STRING("4s3*D8Fy3*678y33*Fy3183y32=40y31*3=y30-2*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)200L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_211),
	    FIX((SI_Long)4269L),Nil);
    string_constant_212 = 
	    STATIC_STRING("4s3*D8Fy3*678y33*Fy3183y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)201L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_212),
	    FIX((SI_Long)4269L),Nil);
    string_constant_213 = 
	    STATIC_STRING("4v3*D8Fy3*678y33*Fy3183y35=60y3*==0y34*50y3=*00y33-4=y30-1=y31+3*y");
    add_character_description_1(9,FIX((SI_Long)202L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_213),
	    FIX((SI_Long)4269L),Nil);
    string_constant_214 = 
	    STATIC_STRING("4q3*D8Fy3*678y33*Fy3183y33+5*y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)203L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_214),
	    FIX((SI_Long)4269L),Nil);
    string_constant_215 = STATIC_STRING("4p3*10Fy3==10y3**0=y3--=*y3*-y");
    add_character_description_1(9,FIX((SI_Long)204L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)5L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_215),
	    FIX((SI_Long)1779L),Nil);
    string_constant_216 = STATIC_STRING("4p3-1=Fy3=*0y3-*==y3*-0*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)205L),FIX((SI_Long)8L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)5L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_216),
	    FIX((SI_Long)1779L),Nil);
    string_constant_217 = 
	    STATIC_STRING("4s3=11Fy33=40y3=-0y32*30y3-**0y31-2=y3*-==y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)206L),FIX((SI_Long)8L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)8L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_217),
	    FIX((SI_Long)1779L),Nil);
    string_constant_218 = STATIC_STRING("4n3*10Fy30+2*y3**y");
    add_character_description_1(9,FIX((SI_Long)207L),FIX((SI_Long)8L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_218),
	    FIX((SI_Long)1779L),Nil);
    string_constant_219 = 
	    STATIC_STRING("4z38E9Fy31D8Fy38CAEy3ABBEy3B9CDy31456y34=6y3D1EAy3C=DCy3A=B0y3B*C2y38*9=y3=*1Fy39-B=y3=+9*y");
    add_character_description_1(9,FIX((SI_Long)208L),FIX((SI_Long)18L),
	    FIX((SI_Long)-1L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_219),
	    FIX((SI_Long)4621L),Nil);
    string_constant_220 = 
	    STATIC_STRING("43Fy37C8Fy36B7Ey3596Dy3485Cy3374Ay32539y31427y34*Fy30316y3=205y381AFy31=4y33*5=y3=*0=y35-6=y32-4*y3=-1*y36+7*y30+3-y");
    add_character_description_1(9,FIX((SI_Long)209L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_220),
	    FIX((SI_Long)4621L),Nil);
    string_constant_221 = 
	    STATIC_STRING("43My36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey399ADy3*9=Dy3B6CAy36-Ay3A4BCy38495y3=405y3-4*Cy393A7y36374y31324y3*3=7y37294y3=214");
    string_constant_222 = STATIC_STRING("y31173y34=60y33*5=y32-4*y31+3-y");
    add_character_description_1(9,FIX((SI_Long)210L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_221,
	    string_constant_222)),FIX((SI_Long)4979L),Nil);
    string_constant_223 = STATIC_STRING("y31173y33=50y34*6=y35-7*y36+8-y");
    add_character_description_1(9,FIX((SI_Long)211L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_221,
	    string_constant_223)),FIX((SI_Long)4979L),Nil);
    string_constant_224 = 
	    STATIC_STRING("43Py36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey399ADy3*9=Dy3B6CAy36-Ay3A4BCy38495y3=405y3-4*Cy393A7y36374y31324y3*3=7y37294y3=214");
    string_constant_225 = 
	    STATIC_STRING("y31173y37=80y30=10y36*70y31*20y35-6=y32-3=y33+5*y");
    add_character_description_1(9,FIX((SI_Long)212L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_224,
	    string_constant_225)),FIX((SI_Long)4979L),Nil);
    string_constant_226 = 
	    STATIC_STRING("y31173y34*6=y30*1=y36-7=y33-5*y30-2*y37+8*y31+4-y");
    add_character_description_1(9,FIX((SI_Long)213L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_224,
	    string_constant_226)),FIX((SI_Long)4979L),Nil);
    string_constant_227 = 
	    STATIC_STRING("43Ky36E7Fy31E2Fy32D6Fy36C8Ey30C2Ey38B9Ey3=B0Ey399ADy3*9=Dy3B6CAy36-Ay3A4BCy38495y3=405y3-4*Cy393A7y36374y31324y3*3=7y37294y3=214");
    string_constant_228 = STATIC_STRING("y31173y35+7*y31+3*y");
    add_character_description_1(9,FIX((SI_Long)214L),FIX((SI_Long)18L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)16L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_227,
	    string_constant_228)),FIX((SI_Long)4979L),Nil);
    string_constant_229 = 
	    STATIC_STRING("43Hy37798y37*8y36687y3-6=7y35576y3*506y34465y3=415y33354y30324y31143y33051y30021y34=60y3==10y35*7=y3**0=y36-8*y3--=*y37+9-y3*-y");
    add_character_description_1(9,FIX((SI_Long)215L),FIX((SI_Long)14L),
	    FIX((SI_Long)0L),FIX((SI_Long)1L),FIX((SI_Long)13L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_229),
	    FIX((SI_Long)3738L),Nil);
    string_constant_230 = 
	    STATIC_STRING("43Uy37E8Fy32E3Fy33D7Fy3D-Fy37C9Ey31C3Ey3-C*Fy39BAEy3A9BDy3=90Dy3081Ey3172Ay32639y33548y34457y35366y36275y3C1DAy37184y3-1*Ay38093");
    string_constant_231 = 
	    STATIC_STRING("y39=A2y30=10y3*==Ey3C*D=y3A*B1y37*8=y32*3=y3=*02y3B-CCy38-A=y30-2=y3C+E*y32+8*y");
    add_character_description_1(9,FIX((SI_Long)216L),FIX((SI_Long)18L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)18L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_230,
	    string_constant_231)),FIX((SI_Long)4979L),Nil);
    string_constant_232 = 
	    STATIC_STRING("4x37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy381ABy31*By33=50y32*4=y31-3*y30+2-y");
    add_character_description_1(9,FIX((SI_Long)217L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_232),
	    FIX((SI_Long)4621L),Nil);
    string_constant_233 = 
	    STATIC_STRING("4x37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy381ABy31*By32=40y33*5=y34-6*y35+7-y");
    add_character_description_1(9,FIX((SI_Long)218L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_233),
	    FIX((SI_Long)4621L),Nil);
    string_constant_234 = 
	    STATIC_STRING("43Cy37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy381ABy31*By36=70y3==00y35*60y30*10y34-5=y31-2=y32+4*y");
    add_character_description_1(9,FIX((SI_Long)219L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_234),
	    FIX((SI_Long)4621L),Nil);
    string_constant_235 = 
	    STATIC_STRING("4v37D8Ey30D6Fy3*D=Ey36C7Ey3=C0Ey37B9Dy3-B=Dy381ABy31*By34+6*y30+2*y");
    add_character_description_1(9,FIX((SI_Long)220L),FIX((SI_Long)18L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)14L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_235),
	    FIX((SI_Long)4621L),Nil);
    string_constant_236 = 
	    STATIC_STRING("4z3163Fy33548y30518y36374y34356y3=306y3-3*4y35265y3*2=5y36183y31*3y31=30y32*4=y33-5*y34+6-y");
    add_character_description_1(9,FIX((SI_Long)221L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)12L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_236),
	    FIX((SI_Long)4269L),Nil);
    string_constant_237 = 
	    STATIC_STRING("4r3*86Ay3677Ay38397y36273y37189y3*072y3*Fy");
    add_character_description_1(9,FIX((SI_Long)222L),FIX((SI_Long)16L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_237),
	    FIX((SI_Long)4269L),Nil);
    string_constant_238 = 
	    STATIC_STRING("43Cy30D2Fy32C3Fy33B4Ey3586By3465Dy33548y32437y30416y31326y32244y33=52y3-=*Fy3*-Fy32-4=y3--==y3=+2*y");
    add_character_description_1(9,FIX((SI_Long)223L),FIX((SI_Long)15L),
	    FIX((SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_238),
	    FIX((SI_Long)3910L),Nil);
    string_constant_239 = 
	    STATIC_STRING("43Gy36D7Fy3=D2Fy32C3Ey3*C=Fy33B4Dy3*9=Ay39-Dy3-8*Ey3*719y31648y3536Fy33344y3-3*5y3425Ey3*2=5y3=143y32=40y31*3=y30-2*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)224L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_239),
	    FIX((SI_Long)3558L),Nil);
    string_constant_240 = 
	    STATIC_STRING("43Gy36D7Fy3=D2Fy32C3Ey3*C=Fy33B4Dy3*9=Ay39-Dy3-8*Ey3*719y31648y3536Fy33344y3-3*5y3425Ey3*2=5y3=143y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)225L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_240),
	    FIX((SI_Long)3558L),Nil);
    string_constant_241 = 
	    STATIC_STRING("43Jy36D7Fy3=D2Fy32C3Ey3*C=Fy33B4Dy3*9=Ay39-Dy3-8*Ey3*719y31648y3536Fy33344y3-3*5y3425Ey3*2=5y3=143y34=50y3-=*0y33*40y3**=0y32-3=");
    string_constant_242 = STATIC_STRING("y3=-0=y30+2*y");
    add_character_description_1(9,FIX((SI_Long)226L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_241,
	    string_constant_242)),FIX((SI_Long)3558L),Nil);
    string_constant_243 = 
	    STATIC_STRING("43Jy36D7Fy3=D2Fy32C3Ey3*C=Fy33B4Dy3*9=Ay39-Dy3-8*Ey3*719y31648y3536Fy33344y3-3*5y3425Ey3*2=5y3=143y31*3=y3-**=y33-4=y30-2*y3--=*");
    string_constant_244 = STATIC_STRING("y34+5*y3*+1-y");
    add_character_description_1(9,FIX((SI_Long)227L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_243,
	    string_constant_244)),FIX((SI_Long)3558L),Nil);
    string_constant_245 = 
	    STATIC_STRING("43Ey36C7Ey3=C2Ey32B3Dy3*B=Ey33A4Cy3*8=9y38-Cy3-7*Dy3*618y31547y3526Ey33243y3-2*4y3415Dy3*1=4y3=042y32+4*y3*+0*y");
    add_character_description_1(9,FIX((SI_Long)228L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_245),
	    FIX((SI_Long)3558L),Nil);
    string_constant_246 = 
	    STATIC_STRING("43Hy36D7Fy3=D2Fy32C3Ey3*C=Fy33B4Dy3*9=Ay39-Dy3-8*Ey3*719y31648y3536Fy33344y3-3*5y3425Ey3*2=5y32143y3=103y30=23y32-30y3=-00y30+2*");
    add_character_description_1(9,FIX((SI_Long)229L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_246,
	    string_constant_1)),FIX((SI_Long)3558L),Nil);
    string_constant_247 = 
	    STATIC_STRING("43Py3D8E9y388CAy3=82Ay3C7D9y37789y32739y3*7=Ay3D6F8y36679y33648y3*4=5y34-8y3-3*9y362D4y3*214y31143y3E0F4y3C=D0y36=70y3D*E4y35*68");
    string_constant_248 = 
	    STATIC_STRING("y33*4=y3-**0y3B-D=y36-8=y34-58y3*-=0y38+B*y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)230L),FIX((SI_Long)21L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)19L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(LIST_2(string_constant_247,
	    string_constant_248)),FIX((SI_Long)5690L),Nil);
    string_constant_249 = 
	    STATIC_STRING("43Ey3=E2Fy3*D1Ey31B3Ey30A2By34859y3083Ay3374Ay3=70By34668y3*6=9y30-6y35*60y33*4=y3=*0=y3-**8y34-50y3*-=0y3=+4*y");
    add_character_description_1(9,FIX((SI_Long)231L),FIX((SI_Long)12L),
	    FIX((SI_Long)1L),FIX((SI_Long)-5L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_249),
	    FIX((SI_Long)3200L),Nil);
    string_constant_250 = 
	    STATIC_STRING("43Gy35D6Ey30D4Fy34C5Ey3=C0Ey35B7Dy3*B=Ey3*759y36579y35-By34455y3*4=5y35369y3-3*Dy33254y3*204y30133y32=40y31*3=y30-2*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)232L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_250),
	    FIX((SI_Long)3558L),Nil);
    string_constant_251 = 
	    STATIC_STRING("43Gy35D6Ey30D4Fy34C5Ey3=C0Ey35B7Dy3*B=Ey3*759y36579y35-By34455y3*4=5y35369y3-3*Dy33254y3*204y30133y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)233L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_251),
	    FIX((SI_Long)3558L),Nil);
    string_constant_252 = 
	    STATIC_STRING("43Jy35D6Ey30D4Fy34C5Ey3=C0Ey35B7Dy3*B=Ey3*759y36579y35-By34455y3*4=5y35369y3-3*Dy33254y3*204y30133y34=50y3-=*0y33*40y3**=0y32-3=");
    add_character_description_1(9,FIX((SI_Long)234L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_252,
	    string_constant_242)),FIX((SI_Long)3558L),Nil);
    string_constant_253 = 
	    STATIC_STRING("43Ey35C6Dy30C4Ey34B5Dy3=B0Dy35A7Cy3*A=Dy3*658y36478y34-Ay34354y3*3=4y35268y3-2*Cy33153y3*103y30032y32+4*y3*+0*y");
    add_character_description_1(9,FIX((SI_Long)235L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_253),
	    FIX((SI_Long)3558L),Nil);
    string_constant_254 = STATIC_STRING("4p3-1=Fy3==10y3**0=y3--=*y3*-y");
    add_character_description_1(9,FIX((SI_Long)236L),FIX((SI_Long)6L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)5L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_254),
	    FIX((SI_Long)1779L),Nil);
    add_character_description_1(9,FIX((SI_Long)237L),FIX((SI_Long)6L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)5L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_216),
	    FIX((SI_Long)1779L),Nil);
    add_character_description_1(9,FIX((SI_Long)238L),FIX((SI_Long)6L),
	    FIX((SI_Long)-1L),FIX((SI_Long)0L),FIX((SI_Long)8L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_217),
	    FIX((SI_Long)1779L),Nil);
    string_constant_255 = STATIC_STRING("4n3*00Ey30+2*y3**y");
    add_character_description_1(9,FIX((SI_Long)239L),FIX((SI_Long)6L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)6L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_255),
	    FIX((SI_Long)1779L),Nil);
    string_constant_256 = 
	    STATIC_STRING("43Hy30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy3=304y3-3*Dy34255y3*2=5y33144y3=113y31033y30*1y3*=20y3=*3=y33-5*y3--0*y3*-y");
    add_character_description_1(9,FIX((SI_Long)240L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_256),
	    FIX((SI_Long)3558L),Nil);
    string_constant_257 = 
	    STATIC_STRING("4x3446Fy3*3=5y33254y3=204y30133y31*Fy31*3=y3-**=y33-4=y30-2*y3--=*y34+5*y3*+1-y");
    add_character_description_1(9,FIX((SI_Long)241L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_257),
	    FIX((SI_Long)3558L),Nil);
    string_constant_258 = 
	    STATIC_STRING("43Ey30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy33344y3=304y3-3*Dy34255y3*2=5y3=143y32=40y31*3=y30-2*y3=+1-y");
    add_character_description_1(9,FIX((SI_Long)242L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_258),
	    FIX((SI_Long)3558L),Nil);
    string_constant_259 = 
	    STATIC_STRING("43Ey30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy33344y3=304y3-3*Dy34255y3*2=5y3=143y3==10y30*2=y31-3*y32+4-y");
    add_character_description_1(9,FIX((SI_Long)243L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_259),
	    FIX((SI_Long)3558L),Nil);
    string_constant_260 = 
	    STATIC_STRING("43Hy30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy33344y3=304y3-3*Dy34255y3*2=5y3=143y34=50y3-=*0y33*40y3**=0y32-3=y3=-0=y30+2*");
    add_character_description_1(9,FIX((SI_Long)244L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_260,
	    string_constant_1)),FIX((SI_Long)3558L),Nil);
    string_constant_261 = 
	    STATIC_STRING("43Hy30D3Fy33C4Fy3=C0Fy34B5Ey3*B=Ey3657By35-By3536Dy33344y3=304y3-3*Dy34255y3*2=5y3=143y31*3=y3-**=y33-4=y30-2*y3--=*y34+5*y3*+1-");
    add_character_description_1(9,FIX((SI_Long)245L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(LIST_2(string_constant_261,
	    string_constant_1)),FIX((SI_Long)3558L),Nil);
    string_constant_262 = 
	    STATIC_STRING("43Cy30C3Ey33B4Ey3=B0Ey34A5Dy3*A=Dy3647Ay34-Ay3526Cy33243y3=203y3-2*Cy34154y3*1=4y3=042y32+4*y3*+0*y");
    add_character_description_1(9,FIX((SI_Long)246L),FIX((SI_Long)13L),
	    FIX((SI_Long)1L),FIX((SI_Long)0L),FIX((SI_Long)11L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_262),
	    FIX((SI_Long)3558L),Nil);
    string_constant_263 = STATIC_STRING("4n31538y3183y31+3=y");
    add_character_description_1(9,FIX((SI_Long)247L),FIX((SI_Long)14L),
	    FIX((SI_Long)1L),FIX((SI_Long)1L),FIX((SI_Long)12L),
	    FIX((SI_Long)12L),
	    regenerate_optimized_constant(string_constant_263),
	    FIX((SI_Long)3738L),Nil);
    string_constant_264 = 
	    STATIC_STRING("43Hy3184Ay38-Ay3475Ay3-7*Ay35669y3=509y3041Ay31326y36178y32134y37086y33043y3-0*6y37*8=y34*52y30*1=y3**=9y35-71y3=-00y37+9*y30+5*");
    add_character_description_1(9,FIX((SI_Long)248L),FIX((SI_Long)13L),
	    FIX((SI_Long)0L),FIX((SI_Long)0L),FIX((SI_Long)13L),
	    FIX((SI_Long)14L),
	    regenerate_optimized_constant(LIST_2(string_constant_264,
	    string_constant_1)),FIX((SI_Long)3910L),Nil);
    string_constant_265 = 
	    STATIC_STRING("4u3=D2Fy32C3Ey3-C=Ey33B4Dy3416Fy31*Cy31=30y30*2=y3=-1*y3*+0-y");
    add_character_description_1(9,FIX((SI_Long)249L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_265),
	    FIX((SI_Long)3558L),Nil);
    string_constant_266 = 
	    STATIC_STRING("4u3=D2Fy32C3Ey3-C=Ey33B4Dy3416Fy31*Cy3*=00y3=*1=y30-2*y31+3-y");
    add_character_description_1(9,FIX((SI_Long)250L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_266),
	    FIX((SI_Long)3558L),Nil);
    string_constant_267 = 
	    STATIC_STRING("4x3=D2Fy32C3Ey3-C=Ey33B4Dy3416Fy31*Cy34=50y3-=*0y33*40y3**=0y32-3=y3=-0=y30+2*y");
    add_character_description_1(9,FIX((SI_Long)251L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)19L),
	    regenerate_optimized_constant(string_constant_267),
	    FIX((SI_Long)3558L),Nil);
    string_constant_268 = 
	    STATIC_STRING("4s3=C2Ey32B3Dy3-B=Dy33A4Cy3406Ey30*By32+4*y3*+0*y");
    add_character_description_1(9,FIX((SI_Long)252L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)10L),
	    FIX((SI_Long)18L),
	    regenerate_optimized_constant(string_constant_268),
	    FIX((SI_Long)3558L),Nil);
    string_constant_269 = 
	    STATIC_STRING("43Fy3*I0Ky30H1Ky31F2Jy32B3Hy3394Fy3192Dy35769y3465Cy3061By3*5=7y35477y3=409y3-3=5y36184y31*3y31=30y32*4=y33-5*y34+6-y");
    add_character_description_1(9,FIX((SI_Long)253L),FIX((SI_Long)13L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_269),
	    FIX((SI_Long)3200L),Nil);
    string_constant_270 = 
	    STATIC_STRING("4x30D3Fy33C4Fy3=C0Ey34B5Ey3*B=Ey3657By3*4=5y3536Dy33344y34255y3*204y30143y3*Ky");
    add_character_description_1(9,FIX((SI_Long)254L),FIX((SI_Long)14L),
	    FIX((SI_Long)2L),FIX((SI_Long)-5L),FIX((SI_Long)11L),
	    FIX((SI_Long)24L),
	    regenerate_optimized_constant(string_constant_270),
	    FIX((SI_Long)3558L),Nil);
    string_constant_271 = 
	    STATIC_STRING("43Dy3*H0Jy30G1Jy31E2Iy32A3Gy3384Ey3182Cy35668y3455By3051Ay3*4=6y35376y3=308y3-2=4y36083y30*2y33+5*y3=+1*y");
    add_character_description_1(9,FIX((SI_Long)255L),FIX((SI_Long)13L),
	    FIX((SI_Long)0L),FIX((SI_Long)-5L),FIX((SI_Long)12L),
	    FIX((SI_Long)23L),
	    regenerate_optimized_constant(string_constant_271),
	    FIX((SI_Long)3200L),Nil);
}
