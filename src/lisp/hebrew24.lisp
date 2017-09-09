;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HEBREW24

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 46 54 13 12 1 2000 2 NIL 
;; 1/12/2000



(def-ab-font
  HEBREW24	; ab-font-name
  ROMAN	; ab-font-type
  24	; ab-font-size
  19	; ab-font-baseline
  31	; ab-font-maximum-width
  29	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  24	; ab-font-point-size
  70	; ab-font-x-resolution
  70	; ab-font-y-resolution

  5973	; ab-font-width-in-x
  5973	; ab-font-width-in-y
  -3	; ab-font-x-offset
  -5	; ab-font-y-offset
  )



;; Hebrew Font Code 0x14, Unicode 0x1E7
(add-character-description
  20 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x15, Unicode 0x1E6
(add-character-description
  21 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x16, Unicode 0x15F
(add-character-description
  22 12 0 -4 11 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2200521 #o6170720 #o5160621 #o3160417 #o4150517 #o3131015 #o10121114 #o1120314
    #o110212 #o11101214 #o12071313 #o6070710 #o7061210 #o3050707 #o2040307 #o1030206
    #o12021303 #o10021103 #o20105 #o11011203 #o1010303 #o3001102)
  2987)

;; Hebrew Font Code 0x17, Unicode 0x15E
(add-character-description
  23 16 0 -4 14 21
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5241025 #o11231224 #o10221125 #o6220723 #o7211023 #o5171221 #o12161320 #o3160520
    #o13151420 #o1150217 #o2140317 #o130215 #o15121616 #o13121413 #o14111517 #o10111112
    #o11101412 #o5100611 #o6071111 #o4060610 #o3050410 #o15041605 #o13031404 #o1030206
    #o14021505 #o4020503 #o2020307 #o12011403 #o3010403 #o4001202)
  3984)

;; Hebrew Font Code 0x18, Unicode 0x15D
(add-character-description
  24 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x19, Unicode 0x15C
(add-character-description
  25 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x1A, Unicode 0x130
(add-character-description
  26 6 2 0 2 20
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30224 #o202)
  1659)

;; Hebrew Font Code 0x1B, Unicode 0x11F
(add-character-description
  27 13 0 -5 10 22
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3240626 #o1240225 #o10231124 #o6230726 #o2230326 #o7221025 #o220224 #o4170721
    #o7161020 #o3160421 #o2150320 #o100115 #o3060407 #o1060217 #o7051007 #o2050310
    #o10041223 #o3040706 #o4020703 #o7011002 #o3010402 #o10001101 #o2000301)
  3322)

;; Hebrew Font Code 0x1C, Unicode 0x11E
(add-character-description
  28 18 0 0 17 21
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6240725 #o7231425 #o14221624 #o4220724 #o16211724 #o2210423 #o1170321 #o17162123
    #o12142116 #o120217 #o20102111 #o1100312 #o16062011 #o2060410 #o14051607 #o4050607
    #o6041406 #o10021303 #o13011402 #o7011002 #o14001501 #o6000701)
  4646)

;; Hebrew Font Code 0x1D, Unicode 0x20A3
(add-character-description
  29 13 0 0 12 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4141016 #o140216 #o4071311 #o2020421 #o2001402)
  3322)

;; Hebrew Font Code 0x1E, Unicode 0x20AA
(add-character-description
  30 19 2 0 17 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7141715 #o7132014 #o5050715 #o13021411 #o20215 #o12011311 #o17002113 #o1202)
  4871)

;; Hebrew Font Code 0x1F, Unicode 0x20AC
(add-character-description
  31 13 0 0 12 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6171321 #o13161420 #o5160620 #o3160417 #o4150520 #o2140416 #o3111213 #o110113
    #o3051307 #o50107 #o1040314 #o2020404 #o13011403 #o4010603 #o6001302)
  3322)

;; Hebrew Font Code 0x20, Unicode 0x5B0
(add-character-description
  32 8 3 -5 1 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o101)
  1989)

;; Hebrew Font Code 0x21, Unicode 0x5B1
(add-character-description
  33 8 1 -5 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1020203 #o4000501 #o2000301 #o101)
  1989)

;; Hebrew Font Code 0x22, Unicode 0x5B2
(add-character-description
  34 8 1 -5 6 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5020603 #o5000601 #o401)
  1989)

;; Hebrew Font Code 0x23, Unicode 0x5B3
(add-character-description
  35 8 2 -5 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1010202 #o4000501 #o301)
  1989)

;; Hebrew Font Code 0x24, Unicode 0x5B4
(add-character-description
  36 8 3 -4 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1989)

;; Hebrew Font Code 0x25, Unicode 0x5B5
(add-character-description
  37 8 2 -4 3 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2000301 #o101)
  1989)

;; Hebrew Font Code 0x26, Unicode 0x5B6
(add-character-description
  38 8 2 -5 3 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1020203 #o2000301 #o101)
  1989)

;; Hebrew Font Code 0x27, Unicode 0x5B7
(add-character-description
  39 8 2 -4 5 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o501)
  1989)

;; Hebrew Font Code 0x28, Unicode 0x5B8
(add-character-description
  40 8 1 -5 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2010303 #o501)
  1989)

;; Hebrew Font Code 0x29, Unicode 0x5B9
(add-character-description
  41 8 3 13 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1989)

;; Hebrew Font Code 0x2A, Unicode 0x5BA
(add-character-description
  42 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x2B, Unicode 0x5BB
(add-character-description
  43 8 1 -5 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o2010302 #o101)
  1989)

;; Hebrew Font Code 0x2C, Unicode 0x5BC
(add-character-description
  44 8 3 6 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1989)

;; Hebrew Font Code 0x2D, Unicode 0x5BD
(add-character-description
  45 8 3 -5 1 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o104)
  1989)

;; Hebrew Font Code 0x2E, Unicode 0x5BE
(add-character-description
  46 9 1 10 6 2
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o602)
  2287)

;; Hebrew Font Code 0x2F, Unicode 0x5BF
(add-character-description
  47 8 2 14 5 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o501)
  1989)

;; Hebrew Font Code 0x30, Unicode 0x5C0
(add-character-description
  48 6 2 0 2 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o217)
  1642)

;; Hebrew Font Code 0x31, Unicode 0x5C1
(add-character-description
  49 8 9 14 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1989)

;; Hebrew Font Code 0x32, Unicode 0x5C2
(add-character-description
  50 8 -2 14 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1989)

;; Hebrew Font Code 0x33, Unicode 0x5C3
(add-character-description
  51 6 2 0 2 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o120214 #o202)
  1659)

;; Hebrew Font Code 0x34, Unicode 0x5C4
(add-character-description
  52 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x35, Unicode 0x5C5
(add-character-description
  53 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x36, Unicode 0x5C6
(add-character-description
  54 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x37, Unicode 0x5C7
(add-character-description
  55 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x38, Unicode 0x5C8
(add-character-description
  56 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x39, Unicode 0x5C9
(add-character-description
  57 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3A, Unicode 0x5CA
(add-character-description
  58 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3B, Unicode 0x5CB
(add-character-description
  59 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3C, Unicode 0x5CC
(add-character-description
  60 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3D, Unicode 0x5CD
(add-character-description
  61 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3E, Unicode 0x5CE
(add-character-description
  62 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x3F, Unicode 0x5CF
(add-character-description
  63 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x40, Unicode 0x5D0
(add-character-description
  64 13 1 0 12 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o13141415 #o12131315 #o11121215 #o10101113 #o100115 #o6060711 #o3060407 #o1060215
    #o7051012 #o2050311 #o11041206 #o5040607 #o10031107 #o3030506 #o2020403 #o1010302
    #o11001304 #o301)
  3363)

;; Hebrew Font Code 0x41, Unicode 0x5D1
(add-character-description
  65 13 1 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10131215 #o130615 #o7031015 #o6020715 #o4020503 #o5010604 #o502)
  3237)

;; Hebrew Font Code 0x42, Unicode 0x5D2
(add-character-description
  66 9 0 0 8 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130115 #o7121015 #o3110412 #o1110215 #o2100313 #o3070511 #o6020715 #o4020503
    #o5010613 #o1000502)
  2383)

;; Hebrew Font Code 0x43, Unicode 0x5D3
(add-character-description
  67 12 1 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6021015 #o1202)
  3036)

;; Hebrew Font Code 0x44, Unicode 0x5D4
(add-character-description
  68 14 2 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o60215 #o10041115 #o11031215 #o6020703 #o7011104 #o702)
  3596)

;; Hebrew Font Code 0x45, Unicode 0x5D5
(add-character-description
  69 6 2 0 2 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o215)
  1473)

;; Hebrew Font Code 0x46, Unicode 0x5D6
(add-character-description
  70 9 1 0 7 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1040315 #o2030404 #o3020503 #o702)
  2284)

;; Hebrew Font Code 0x47, Unicode 0x5D7
(add-character-description
  71 14 2 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o11031215 #o10021115 #o20215 #o7011004 #o702)
  3576)

;; Hebrew Font Code 0x48, Unicode 0x5D8
(add-character-description
  72 14 2 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4130715 #o7121015 #o3120414 #o1120213 #o10111114 #o2110314 #o12021312 #o10021103
    #o5020603 #o11011213 #o4010503 #o5001102 #o212)
  3523)

;; Hebrew Font Code 0x49, Unicode 0x5D9
(add-character-description
  73 6 2 7 2 6
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o206)
  1473)

;; Hebrew Font Code 0x4A, Unicode 0x5DA
(add-character-description
  74 12 0 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o11031222 #o7031004 #o10021122 #o6011003 #o602)
  3042)

;; Hebrew Font Code 0x4B, Unicode 0x5DB
(add-character-description
  75 11 1 0 9 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130515 #o5120614 #o6110714 #o10041111 #o6030704 #o7021013 #o5010703 #o502)
  2753)

;; Hebrew Font Code 0x4C, Unicode 0x5DC
(add-character-description
  76 11 1 0 9 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4150521 #o6140715 #o5130621 #o6121014 #o7061112 #o2041106 #o206)
  2765)

;; Hebrew Font Code 0x4D, Unicode 0x5DD
(add-character-description
  77 14 2 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2131015 #o11031215 #o10021115 #o20215 #o7011004 #o702)
  3576)

;; Hebrew Font Code 0x4E, Unicode 0x5DE
(add-character-description
  78 14 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5131115 #o130115 #o1060215 #o2050312 #o11031315 #o1030305 #o3020406 #o10011203
    #o4010503 #o5001002 #o203)
  3590)

;; Hebrew Font Code 0x4F, Unicode 0x5DF
(add-character-description
  79 6 2 -5 2 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o222)
  1473)

;; Hebrew Font Code 0x50, Unicode 0x5E0
(add-character-description
  80 8 0 0 6 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130415 #o5020615 #o3020403 #o4010515 #o402)
  2106)

;; Hebrew Font Code 0x51, Unicode 0x5E1
(add-character-description
  81 13 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4130715 #o7121014 #o3120415 #o2110314 #o10101114 #o40111 #o12031311 #o10031104
    #o11021213 #o3020403 #o1020213 #o7011103 #o2010304 #o3000702)
  3430)

;; Hebrew Font Code 0x52, Unicode 0x5E2
(add-character-description
  82 12 0 -1 10 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o140216 #o5130714 #o2130315 #o6121013 #o7101112 #o3060515 #o2020406 #o10001210
    #o1000302)
  3161)

;; Hebrew Font Code 0x53, Unicode 0x5E3
(add-character-description
  83 13 1 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070511 #o11031222 #o10021122 #o6020703 #o7011004 #o10210 #o2000702)
  3383)

;; Hebrew Font Code 0x54, Unicode 0x5E4
(add-character-description
  84 13 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6140715 #o2130615 #o130114 #o6121014 #o1120215 #o10111114 #o2060510 #o12041311
    #o10031104 #o11021213 #o6020703 #o1020207 #o7011103 #o10107 #o1000702)
  3264)

;; Hebrew Font Code 0x55, Unicode 0x5E5
(add-character-description
  85 11 1 -5 9 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4060522 #o5050607 #o7041006 #o6030707 #o3030422 #o1020204 #o2010307 #o7001104
    #o202)
  2756)

;; Hebrew Font Code 0x56, Unicode 0x5E6
(add-character-description
  86 11 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o11131215 #o130715 #o7121115 #o6101012 #o7061007 #o5050710 #o7041106 #o4040507
    #o2030304 #o3020405 #o1010303 #o10001204 #o301)
  2858)

;; Hebrew Font Code 0x57, Unicode 0x5E7
(add-character-description
  87 13 2 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5110615 #o7101011 #o6070715 #o7061110 #o60222 #o10021206 #o1202)
  3284)

;; Hebrew Font Code 0x58, Unicode 0x5E8
(add-character-description
  88 12 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o11031215 #o7031004 #o10021115 #o6011003 #o602)
  3042)

;; Hebrew Font Code 0x59, Unicode 0x5E9
(add-character-description
  89 16 1 0 14 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12131314 #o5131115 #o11121214 #o4120515 #o2120313 #o12111413 #o3110414 #o1100312
    #o1060410 #o13051511 #o6050706 #o4050507 #o5040607 #o14001605 #o6001005 #o206)
  4147)

;; Hebrew Font Code 0x5A, Unicode 0x5EA
(add-character-description
  90 15 1 0 12 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3140415 #o1130315 #o120115 #o12041415 #o3020514 #o11011304 #o1102)
  3838)

;; Hebrew Font Code 0x5B, Unicode 0x5EB
(add-character-description
  91 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x5C, Unicode 0x5EC
(add-character-description
  92 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x5D, Unicode 0x5ED
(add-character-description
  93 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x5E, Unicode 0x5EE
(add-character-description
  94 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x5F, Unicode 0x5EF
(add-character-description
  95 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x60, Unicode 0x5F0
(add-character-description
  96 12 2 0 7 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000715 #o215)
  2946)

;; Hebrew Font Code 0x61, Unicode 0x5F1
(add-character-description
  97 12 2 0 7 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000715 #o207)
  2946)

;; Hebrew Font Code 0x62, Unicode 0x5F2
(add-character-description
  98 12 2 6 7 7
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000707 #o207)
  2946)

;; Hebrew Font Code 0x63, Unicode 0x5F3
(add-character-description
  99 6 1 9 3 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20104 #o1010203 #o1000301)
  1409)

;; Hebrew Font Code 0x64, Unicode 0x5F4
(add-character-description
  100 10 1 9 7 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020504 #o20104 #o5010603 #o1010203 #o5000701 #o1000301)
  2491)

;; Hebrew Font Code 0x65, Unicode 0xFB1D
(add-character-description
  101 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x66, Unicode 0xFB1E
(add-character-description
  102 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x67, Unicode 0xFB1F
(add-character-description
  103 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x68, Unicode 0xFB20
(add-character-description
  104 12 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7131014 #o5130615 #o130315 #o6120715 #o7071113 #o4060515 #o2020307 #o3010415
    #o10001207 #o1000302)
  3196)

;; Hebrew Font Code 0x69, Unicode 0xFB21
(add-character-description
  105 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6A, Unicode 0xFB22
(add-character-description
  106 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6B, Unicode 0xFB23
(add-character-description
  107 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6C, Unicode 0xFB24
(add-character-description
  108 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6D, Unicode 0xFB25
(add-character-description
  109 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6E, Unicode 0xFB26
(add-character-description
  110 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x6F, Unicode 0xFB27
(add-character-description
  111 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x70, Unicode 0xFB28
(add-character-description
  112 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x71, Unicode 0xFB29
(add-character-description
  113 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x72, Unicode 0xFB2A
(add-character-description
  114 16 1 0 14 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12161317 #o5161120 #o11151217 #o4150520 #o2150316 #o12141416 #o3140417 #o1130315
    #o1110413 #o13101514 #o6100711 #o4100512 #o5070612 #o14031610 #o6031010 #o30211
    #o14001501)
  4147)

;; Hebrew Font Code 0x73, Unicode 0xFB2B
(add-character-description
  115 16 1 0 14 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12161317 #o5161120 #o11151217 #o4150520 #o2150316 #o12141416 #o3140417 #o1130315
    #o1110413 #o13101514 #o6100711 #o4100512 #o5070612 #o14031610 #o6031010 #o30211
    #o101)
  4147)

;; Hebrew Font Code 0x74, Unicode 0xFB2C
(add-character-description
  116 16 1 0 14 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12161317 #o5161120 #o11151217 #o4150520 #o2150316 #o12141416 #o3140417 #o1130315
    #o10121113 #o1110413 #o13101514 #o6100711 #o4100512 #o5070612 #o14031610 #o6031010
    #o30211 #o14001501)
  4147)

;; Hebrew Font Code 0x75, Unicode 0xFB2D
(add-character-description
  117 16 1 0 14 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12161317 #o5161120 #o11151217 #o4150520 #o2150316 #o12141416 #o3140417 #o1130315
    #o10121113 #o1110413 #o13101514 #o6100711 #o4100512 #o5070612 #o14031610 #o6031010
    #o30211 #o101)
  4147)

;; Hebrew Font Code 0x76, Unicode 0xFB2E
(add-character-description
  118 13 1 -35 12 48
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3221023 #o13141415 #o12131315 #o11121215 #o10101113 #o100115 #o6060711 #o3060407
    #o1060215 #o7051012 #o2050311 #o11041206 #o5040607 #o10031107 #o3030506 #o2020403
    #o1010302 #o11001304 #o301)
  3363)

;; Hebrew Font Code 0x77, Unicode 0xFB2F
(add-character-description
  119 13 1 -37 12 50
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6221023 #o3220523 #o13141415 #o12131315 #o11121215 #o10101113 #o100115 #o6060711
    #o3060407 #o1060215 #o7051012 #o2050311 #o11041206 #o5040607 #o10031107 #o3030506
    #o2020403 #o1010302 #o11001304 #o301)
  3363)

;; Hebrew Font Code 0x78, Unicode 0xFB30
(add-character-description
  120 13 1 0 12 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o13141415 #o12131315 #o11121215 #o4120513 #o10101113 #o100115 #o6060711 #o3060407
    #o1060215 #o7051012 #o2050311 #o11041206 #o5040607 #o10031107 #o3030506 #o2020403
    #o1010302 #o11001304 #o301)
  3363)

;; Hebrew Font Code 0x79, Unicode 0xFB31
(add-character-description
  121 13 1 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10131215 #o130615 #o3060407 #o7031015 #o6020715 #o4020503 #o5010604 #o502)
  3237)

;; Hebrew Font Code 0x7A, Unicode 0xFB32
(add-character-description
  122 9 0 0 8 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130115 #o7121015 #o3110412 #o1110215 #o2100313 #o3070511 #o2040305 #o6020715
    #o4020503 #o5010613 #o1000502)
  2383)

;; Hebrew Font Code 0x7B, Unicode 0xFB33
(add-character-description
  123 12 1 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050406 #o6021015 #o1202)
  3036)

;; Hebrew Font Code 0x7C, Unicode 0xFB34
(add-character-description
  124 14 2 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5060607 #o60215 #o10041115 #o11031215 #o6020703 #o7011104 #o702)
  3596)

;; Hebrew Font Code 0x7D, Unicode 0xFB35
(add-character-description
  125 7 0 0 5 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o60107 #o3000515)
  1712)

;; Hebrew Font Code 0x7E, Unicode 0xFB36
(add-character-description
  126 10 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o50106 #o4040615 #o4030704 #o5021003 #o1001202)
  2456)

;; Hebrew Font Code 0x7F, Unicode 0xFB37
(add-character-description
  127 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x80, Unicode 0xFB38
(add-character-description
  128 14 2 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4130715 #o7121015 #o3120414 #o1120213 #o10111114 #o2110314 #o5060607 #o12021312
    #o10021103 #o5020603 #o11011213 #o4010503 #o5001102 #o212)
  3523)

;; Hebrew Font Code 0x81, Unicode 0xFB39
(add-character-description
  129 7 0 7 5 6
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30104 #o3000506)
  1712)

;; Hebrew Font Code 0x82, Unicode 0xFB3A
(add-character-description
  130 12 0 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4060507 #o11031222 #o7031004 #o10021122 #o6011003 #o602)
  3042)

;; Hebrew Font Code 0x83, Unicode 0xFB3B
(add-character-description
  131 11 1 0 9 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130515 #o5120614 #o6110714 #o3060407 #o10041111 #o6030704 #o7021013 #o5010703
    #o502)
  2753)

;; Hebrew Font Code 0x84, Unicode 0xFB3C
(add-character-description
  132 11 1 0 9 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4150521 #o6140715 #o5130621 #o6121014 #o3110412 #o7061112 #o2041106 #o206)
  2765)

;; Hebrew Font Code 0x85, Unicode 0xFB3D
(add-character-description
  133 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x86, Unicode 0xFB3E
(add-character-description
  134 14 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5131115 #o130115 #o6060707 #o1060215 #o2050312 #o11031315 #o1030305 #o3020406
    #o10011203 #o4010503 #o5001002 #o203)
  3590)

;; Hebrew Font Code 0x87, Unicode 0xFB3F
(add-character-description
  135 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x88, Unicode 0xFB40
(add-character-description
  136 8 0 0 6 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130415 #o2060307 #o5020615 #o3020403 #o4010515 #o402)
  2106)

;; Hebrew Font Code 0x89, Unicode 0xFB41
(add-character-description
  137 13 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4130715 #o7121014 #o3120415 #o2110314 #o10101114 #o5060607 #o40111 #o12031311
    #o10031104 #o11021213 #o3020403 #o1020213 #o7011103 #o2010304 #o3000702)
  3430)

;; Hebrew Font Code 0x8A, Unicode 0xFB42
(add-character-description
  138 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x8B, Unicode 0xFB43
(add-character-description
  139 13 1 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1100211 #o5070610 #o2070411 #o11031222 #o10021122 #o6020703 #o7011004 #o10210
    #o2000702)
  3383)

;; Hebrew Font Code 0x8C, Unicode 0xFB44
(add-character-description
  140 13 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6140715 #o2130615 #o130114 #o6121014 #o1120215 #o10111114 #o5070610 #o2060410
    #o12041311 #o10031104 #o11021213 #o6020703 #o1020207 #o7011103 #o10107 #o1000702)
  3264)

;; Hebrew Font Code 0x8D, Unicode 0xFB45
(add-character-description
  141 18 3 0 11 15
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1161217 #o12011317 #o10117 #o1301)
  4480)

;; Hebrew Font Code 0x8E, Unicode 0xFB46
(add-character-description
  142 11 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o11131215 #o130715 #o7121115 #o6101012 #o7061007 #o60107 #o5050710 #o7041106
    #o4040507 #o2030304 #o3020405 #o1010303 #o10001204 #o301)
  2858)

;; Hebrew Font Code 0x8F, Unicode 0xFB47
(add-character-description
  143 13 2 -5 10 18
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5110615 #o7101011 #o6070715 #o7061110 #o4060507 #o60222 #o10021206 #o1202)
  3284)

;; Hebrew Font Code 0x90, Unicode 0xFB48
(add-character-description
  144 12 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4060507 #o11031215 #o7031004 #o10021115 #o6011003 #o602)
  3042)

;; Hebrew Font Code 0x91, Unicode 0xFB49
(add-character-description
  145 16 1 0 14 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o12131314 #o5131115 #o11121214 #o4120515 #o2120313 #o12111413 #o3110414 #o1100312
    #o10071110 #o1060410 #o13051511 #o6050706 #o4050507 #o5040607 #o14001605 #o6001005
    #o206)
  4147)

;; Hebrew Font Code 0x92, Unicode 0xFB4A
(add-character-description
  146 15 1 0 12 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3140415 #o1130315 #o120115 #o7061007 #o12041415 #o3020514 #o11011304 #o1102)
  3838)

;; Hebrew Font Code 0x93, Unicode 0xFB4B
(add-character-description
  147 6 2 0 2 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30220 #o101)
  1473)

;; Hebrew Font Code 0x94, Unicode 0xFB4C
(add-character-description
  148 13 1 0 10 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10161220 #o160620 #o7061020 #o6050720 #o4050506 #o5040607 #o30505 #o1000601)
  3237)

;; Hebrew Font Code 0x95, Unicode 0xFB4D
(add-character-description
  149 11 1 0 9 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o160520 #o5150617 #o6140717 #o10071114 #o6060707 #o7051016 #o5040706 #o30505
    #o1000601)
  2753)

;; Hebrew Font Code 0x96, Unicode 0xFB4E
(add-character-description
  150 13 1 0 11 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6170720 #o2160620 #o160117 #o6151017 #o1150220 #o10141117 #o2110513 #o12071314
    #o10061107 #o11051216 #o6050706 #o1050212 #o7041106 #o40112 #o1030705 #o2000701)
  3264)

;; Hebrew Font Code 0x97, Unicode 0xFB4F
(add-character-description
  151 13 0 0 13 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o14171520 #o13161420 #o12151320 #o11131216 #o1130220 #o7111014 #o2110320 #o10101115
    #o6100713 #o3100413 #o12071311 #o11061212 #o5060611 #o4050512 #o3040406 #o12031407
    #o2030305 #o205)
  3439)
