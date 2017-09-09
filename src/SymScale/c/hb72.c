/* hb72.c
 * Input file:  hb72.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "hb72.h"


void hb72_INIT()
{
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object string_constant, Qroman, Qhb72, AB_package;

    x_note_fn_call(64,0);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qhb72 = STATIC_SYMBOL("HB72",AB_package);
    Qroman = STATIC_SYMBOL("ROMAN",AB_package);
    define_ab_font(16,Qhb72,Qroman,FIX((SI_Long)95L),FIX((SI_Long)78L),
	    FIX((SI_Long)97L),FIX((SI_Long)112L),Nil,Nil,Nil,
	    FIX((SI_Long)72L),FIX((SI_Long)75L),FIX((SI_Long)75L),
	    FIX((SI_Long)86L),FIX((SI_Long)95L),FIX((SI_Long)-11L),
	    FIX((SI_Long)-17L));
    string_constant = 
	    STATIC_STRING("43ry3j-oy3-g*oy3*e=oy3=c0oy3Hbeoy30b1oy31a2oy32Z3oy33Y4oy34X5oy35W6oy36V7oy3PURVy37U9oy39TAoy3SSUTy3ASBoy3BRDoy3DQEoy3EPGoy3GOHo");
    string_constant_1 = 
	    STATIC_STRING("y3HNJay3JMKZy3KLLYy3LKMYy3MJNXy3NHOWy3OEPWy3AEBIy3-D*Iy3PCSUy3ABCEy3AADBy3N9OAy3*9=Iy3d8eIy3L8O9y3E8G9y3c6dKy3=60Iy3b4cMy3041Iy3");
    string_constant_2 = 
	    STATIC_STRING("a3bNy3132Iy3Z2aOy3223Iy3Y1ZPy3314Iy3X0YQy3405Iy3V=XRy35=7Iy3S*VSy37*AIy3O-SCy3A-EAy3E+O8y");
    add_character_description_1(9,FIX((SI_Long)50L),FIX((SI_Long)50L),
	    FIX((SI_Long)4L),FIX((SI_Long)0L),FIX((SI_Long)44L),
	    FIX((SI_Long)54L),
	    regenerate_optimized_constant(LIST_3(string_constant,
	    string_constant_1,string_constant_2)),FIX((SI_Long)12806L),Nil);
    string_constant_3 = 
	    STATIC_STRING("43ry3conpy3WmYny38mAny3WlZmy3bknoy3Wkaly3LdRqy3RcTpy3IcLqy3TbUpy3HbIqy3UaVoy3GaHqy3VZWoy3FZGqy3WXnky3EXFpy3DTEpy3PLnXy3I-Wy3WFXG");
    string_constant_4 = 
	    STATIC_STRING("y3DFELy3-E*Zy3lDmGy3VDXFy3DDFFy3UCXDy3DCGDy3*B=cy3kAlGy3SATBy3HAIBy3Q9TAy3H9KAy3=90ey3j8kGy3071gy3i6jGy3162hy3h5iGy3253iy3344jy3");
    string_constant_5 = 
	    STATIC_STRING("f3hGy3435ky3e2fGy3526ly3d1eGy3617my3c0dGy370Amy3a=cGy3A=Coy3X*aGy3C*Dpy3T-XCy3D-HCy3H+T9y");
    add_character_description_1(9,FIX((SI_Long)71L),FIX((SI_Long)62L),
	    FIX((SI_Long)3L),FIX((SI_Long)-1L),FIX((SI_Long)53L),
	    FIX((SI_Long)56L),
	    regenerate_optimized_constant(LIST_3(string_constant_3,
	    string_constant_4,string_constant_5)),FIX((SI_Long)15994L),Nil);
    string_constant_6 = STATIC_STRING("4m3CAToy3jAy");
    add_character_description_1(9,FIX((SI_Long)84L),FIX((SI_Long)54L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)49L),
	    FIX((SI_Long)54L),
	    regenerate_optimized_constant(string_constant_6),
	    FIX((SI_Long)13862L),Nil);
    string_constant_7 = 
	    STATIC_STRING("43Wy3FoIpy3PnQoy3JnKoy35n6oy3NkOly3Qicoy3NiPky3FeJoy3JdLny3DdFpy3LcMny3CcDpy3MaNmy3BZCpy3Y-by38RBpy38PCRy3P-Wy38NDPy3KMLNy38MFNy");
    string_constant_8 = 
	    STATIC_STRING("3-L*fy3*J=hy3=H0iy30G1ky31F2ly3MENQy32E3my3LDMOy33D4my3JCLMy34C6ny3HBJMy36B8oy38AHMy3N+ciy");
    add_character_description_1(9,FIX((SI_Long)100L),FIX((SI_Long)50L),
	    FIX((SI_Long)3L),FIX((SI_Long)-1L),FIX((SI_Long)42L),
	    FIX((SI_Long)55L),
	    regenerate_optimized_constant(LIST_2(string_constant_7,
	    string_constant_8)),FIX((SI_Long)12806L),Nil);
    string_constant_9 = 
	    STATIC_STRING("43ly3OZSay39ZAay3OYUZy3OXWYy3OWYXy3OVZWy3OTaVy3OSbTy3=S0Ty3FRMby3OQcSy3MQNby3EQFby3NPOay3DPEby3OOdQy3CODby3BLCay3dDeKy3BCPKy3B-M");
    string_constant_10 = 
	    STATIC_STRING("y3PAQKy3AABay3c9dKy3O8QAy3A8CAy3-8*Py3b7cKy3N7Q8y3A7D8y3*7=Qy3a6bKy3E6F7y3=50Ry3Z4aKy3041Uy3Y3ZKy3132Vy3X2YKy3223Wy3W1XKy3314Xy3");
    string_constant_11 = 
	    STATIC_STRING("U0WKy3405Xy3S=UKy35=7Yy3Q*SKy37*AZy3L-Q7y3A-E7y3E+L6y");
    add_character_description_1(9,FIX((SI_Long)101L),FIX((SI_Long)50L),
	    FIX((SI_Long)2L),FIX((SI_Long)-1L),FIX((SI_Long)44L),
	    FIX((SI_Long)41L),
	    regenerate_optimized_constant(LIST_3(string_constant_9,
	    string_constant_10,string_constant_11)),FIX((SI_Long)12806L),Nil);
    string_constant_12 = STATIC_STRING("4m3CBpy3B7y");
    add_character_description_1(9,FIX((SI_Long)105L),FIX((SI_Long)24L),
	    FIX((SI_Long)5L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)55L),
	    regenerate_optimized_constant(string_constant_12),
	    FIX((SI_Long)6394L),Nil);
    string_constant_13 = STATIC_STRING("4l3Boy");
    add_character_description_1(9,FIX((SI_Long)108L),FIX((SI_Long)24L),
	    FIX((SI_Long)5L),FIX((SI_Long)0L),FIX((SI_Long)15L),
	    FIX((SI_Long)54L),
	    regenerate_optimized_constant(string_constant_13),
	    FIX((SI_Long)6394L),Nil);
    string_constant_14 = 
	    STATIC_STRING("43Vy3MDRay3mCsay3lAsCy3LARDy3k9sAy3K9RAy3j8s9y3E8F9y1o3-*yu3-=y3ay1o3--yr3-*y3ay3Y2aay3A2Bay1o3-+yp3--y3ay3a1bay3X1Yay3B1CDy1o3x");
    string_constant_15 = 
	    STATIC_STRING("yo3-+y3ay3b0cDy3W0Xay3C0DAy3w=xay3c=dAy3V=Way3D=E9y3u*way3d*f9y3U*Vay3E*G8y3s-uay3f-i8y3R-Uay3G-I8y3-Aay3i+s8y3I+R9y");
    add_character_description_1(9,FIX((SI_Long)109L),FIX((SI_Long)75L),
	    FIX((SI_Long)3L),FIX((SI_Long)0L),FIX((SI_Long)67L),
	    FIX((SI_Long)40L),
	    regenerate_optimized_constant(LIST_2(string_constant_14,
	    string_constant_15)),FIX((SI_Long)19200L),Nil);
    string_constant_16 = 
	    STATIC_STRING("43Ey3MCRay3LARCy3K9RAy3a6bay3Z3aay3Y2Zay3A2Bay3B1CCy3X0Yay3C0DAy3W=Xay3D=E9y3U*Way3E*F9y3R-Uay3F-I8y3-Aay3I+R9y");
    add_character_description_1(9,FIX((SI_Long)110L),FIX((SI_Long)50L),
	    FIX((SI_Long)4L),FIX((SI_Long)0L),FIX((SI_Long)41L),
	    FIX((SI_Long)40L),
	    regenerate_optimized_constant(string_constant_16),
	    FIX((SI_Long)12806L),Nil);
    string_constant_17 = 
	    STATIC_STRING("43Wy3EQLby3LPMby3DPEby3MNNay3CNDay3NLOay3BKCay39DBay3OCQay3cBdMy3B-My3NAQCy39ACDy3b8cPy3M8QAy3-8*Qy3D7F8y3a6bRy3*6=Ry3Z4aTy3=40T");
    string_constant_18 = 
	    STATIC_STRING("y3Y3ZUy3031Uy3X2YVy3122Vy3W1XWy3213Wy3U0WXy3305Xy3S=UYy35=7Yy3Q*SZy37*9Zy3L-Q8y39-DAy3D+L7y");
    add_character_description_1(9,FIX((SI_Long)111L),FIX((SI_Long)50L),
	    FIX((SI_Long)3L),FIX((SI_Long)-1L),FIX((SI_Long)43L),
	    FIX((SI_Long)41L),
	    regenerate_optimized_constant(LIST_2(string_constant_17,
	    string_constant_18)),FIX((SI_Long)12806L),Nil);
    string_constant_19 = 
	    STATIC_STRING("43ny38aBby3QZRay35ZBay33YBZy31XBYy30WBXy3=VBWy3*TBVy3DSJby3JRKby3CRDby3-RBTy3KQLby3BQCby3LONby3OBRy3KNNOy3JMNNy3ZKaSy3BKCLy37J9K");
    string_constant_20 = 
	    STATIC_STRING("y3YIZUy34I5Jy3XHYVy3WGXWy3VFWXy3TEVYy3QDTZy3NCQay3IBNMy3FAIMy3D9FLy3C8DLy3K6N8y396CKy3-6*By3J5N6y395D6y3X4Y8y3*3=Ey3W2X8y3=20Fy3");
    string_constant_21 = 
	    STATIC_STRING("V1W8y3011Gy3U0V8y3102Hy3T=U8y32=3Iy3Q*T8y33*5Iy3N-Q8y35-9Jy39+N5y");
    add_character_description_1(9,FIX((SI_Long)115L),FIX((SI_Long)45L),
	    FIX((SI_Long)2L),FIX((SI_Long)-1L),FIX((SI_Long)40L),
	    FIX((SI_Long)41L),
	    regenerate_optimized_constant(LIST_3(string_constant_19,
	    string_constant_20,string_constant_21)),FIX((SI_Long)11731L),Nil);
    string_constant_22 = 
	    STATIC_STRING("43vy3lXoZy3ZXaZy38WBZy3NVOZy3lUpXy3YUaXy37TBWy3lRqUy3NRPVy3XQaUy36QBTy3lOrRy35NBQy3WMaQy3NMQRy3lKsOy3fKgZy34KBNy3GJHZy3VIaMy3NIR");
    string_constant_23 = 
	    STATIC_STRING("My3lHtKy3gHhZy3HHIZy33HBKy3eFfZy3FFGZy3lEuHy3UEaIy3NESIy3hDiZy3IDJZy32DBHy3lBvEy3dBeZy3EBFZy31ABDy3J9KZy3l8wBy3i8jZy3c7dZy3D7EZy");
    string_constant_24 = 
	    STATIC_STRING("307BAy3l5x8y3K5LZy3j4kZy3=4B7y3b3cZy3C3DZy1o3lyp3-+yt3L1MZy3*1B4y3k0lZy3a=bZy3B=CZy1o3lym3--yp3-*B1y3M-NZy1o3lyk3-*ym3N+aEy3B*y");
    add_character_description_1(9,FIX((SI_Long)119L),FIX((SI_Long)70L),
	    FIX((SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)66L),
	    FIX((SI_Long)39L),
	    regenerate_optimized_constant(LIST_3(string_constant_22,
	    string_constant_23,string_constant_24)),FIX((SI_Long)18125L),Nil);
    string_constant_25 = 
	    STATIC_STRING("43cy30b7my37a8my3OZPcy3OWQZy38VBmy3OTRWy37SBVy3OQSTy36PBSy3ONTQy35MBPy3OLUNy3HJIly34JBMy3OIVLy3GHHly33HBJy3IGJky3OFWIy32EBHy3FDG");
    string_constant_26 = 
	    STATIC_STRING("ly3OCXFy3JCKjy31BBEy3EAFmy3O9YCy3K9Ljy308BBy3O6Z9y3D6Emy3L5Mhy3=5B8y3O3a6y3C3Dmy3*3B5y3M2Ngy3O0b3y3-0B3y3B=Cmy3N*Oey3O+c0y3B0y");
    add_character_description_1(9,FIX((SI_Long)121L),FIX((SI_Long)45L),
	    FIX((SI_Long)1L),FIX((SI_Long)-13L),FIX((SI_Long)42L),
	    FIX((SI_Long)52L),
	    regenerate_optimized_constant(LIST_2(string_constant_25,
	    string_constant_26)),FIX((SI_Long)11731L),Nil);
    string_constant_27 = 
	    STATIC_STRING("43Ly3fChQy3hAiQy3eAfQy3n8oBy3Y8ZBy3i7jPy3d7ePy3n5p8y3j5kMy3c5dMy3X5Z8y3r2xQy3n2q5y3k2lJy3b2cJy3W2Z5y3P2VQy352CQy3l=mGy3a=bGy3m-n");
    string_constant_28 = STATIC_STRING("Ey3Z-aEy3n+x2y3P+Z2y3L2y");
    add_character_description_1(9,FIX((SI_Long)146L),FIX((SI_Long)71L),
	    FIX((SI_Long)2L),FIX((SI_Long)24L),FIX((SI_Long)63L),
	    FIX((SI_Long)30L),
	    regenerate_optimized_constant(LIST_2(string_constant_27,
	    string_constant_28)),FIX((SI_Long)18240L),Nil);
    string_constant_29 = 
	    STATIC_STRING("43-Oy3JpSqy3CnDoy3IjSpy3SiWpy3FiIpy3WhYoy3DhFoy3YgZoy3BgDny3Zfany3AfBny3aecmy39eAmy3cddly38d9my3acbdy37c8ly3dbely3Zbady3TbVdy3ea");
    string_constant_30 = 
	    STATIC_STRING("fky36a7ky3YZZdy3SZVby35Z6jy3fYgjy3XXYdy3RXVZy3gWhiy34W5iy3WVXdy3QVVXy3VUWdy3PTVVy33T4hy3OSVTy3hRihy3NRUSy3IMURy3ULVRy3VKWQy3oIpU");
    string_constant_31 = 
	    STATIC_STRING("y3I-Uy3WGYQy3nFoYy3bFcMy3-F*Yy3UEVFy3CEIdy3aDbOy3mCnay3*C=ay3lBmcy3YBaPy3dAeBy3VAYGy3=A0cy3k9ley3C9VEy3798Ay3b8c9y3081ey3j7kfy31");
    string_constant_32 = 
	    STATIC_STRING("72fy3i6jgy3Z6a7y3A6B7y3263gy3h5iMy3X5Y6y3C5D6y3354Ky3g4hHy3V4W5y3445Gy3f3gEy3S3W4y3F3I4y3536Ey3e2fCy3627Cy3c1eAy37199y3a0c8y390A");
    string_constant_33 = 
	    STATIC_STRING("8y3Y=a6y3A=C6y3W*Y5y3C*F5y3R-W3y3F-J3y3J+R3y");
    add_character_description_1(9,FIX((SI_Long)174L),FIX((SI_Long)60L),
	    FIX((SI_Long)2L),FIX((SI_Long)-1L),FIX((SI_Long)55L),
	    FIX((SI_Long)56L),
	    regenerate_optimized_constant(LIST_5(string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33)),FIX((SI_Long)15360L),Nil);
}
